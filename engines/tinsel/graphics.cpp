/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * Low level graphics interface.
 */

#include "tinsel/graphics.h"
#include "tinsel/handle.h"	// LockMem()
#include "tinsel/object.h"
#include "tinsel/palette.h"
#include "tinsel/scene.h"
#include "tinsel/tinsel.h"
#include "tinsel/scn.h"

#include "common/textconsole.h"

namespace Tinsel {

//----------------- LOCAL DEFINES --------------------

// Defines used in graphic drawing
#define CHARPTR_OFFSET 16
#define CHAR_WIDTH 4
#define CHAR_HEIGHT 4

extern uint8 g_transPalette[MAX_COLORS];

//----------------- SUPPORT FUNCTIONS ---------------------

// using ScummVM pixel format functions is too slow on some ports because of runtime overhead, let the compiler do the optimizations instead
static inline void t3getRGB(uint16 color, uint8 &r, uint8 &g, uint8 &b) {
	r = (color >> 11) & 0x1F;
	g = (color >>  5) & 0x3F;
	b = (color      ) & 0x1F;
}

static inline uint16 t3getColor(uint8 r, uint8 g, uint8 b) {
	return ((r & 0x1F) << 11) | ((g & 0x3F) << 5) | (b & 0x1F);
}

/**
 * PSX/Saturn Block list unwinder.
 * Chunk type 0x0003 (CHUNK_CHARPTR) in PSX version of DW 1 & 2 is compressed (original code
 * calls the compression PJCRLE), thus we need to decompress it before passing data to drawing functions
 */
uint8* psxSaturnPJCRLEUnwinder(uint16 imageWidth, uint16 imageHeight, uint8 *srcIdx) {
	uint32 remainingBlocks = 0;

	uint16 compressionType = 0; // Kind of decompression to apply
	uint16 controlBits = 0; // Control bits used to calculate the number of decompressed indexes
	uint16 baseIndex = 0; // Base index to be repeated / incremented.

	uint16 controlData;

	uint8* dstIdx = nullptr;
	uint8* destinationBuffer = nullptr;

	if (!imageWidth || !imageHeight)
		return NULL;

	// Calculate needed index numbers, align width and height not next multiple of four
	imageWidth = (imageWidth % 4) ? ((imageWidth / 4) + 1) * 4 : imageWidth;
	imageHeight = (imageHeight % 4) ? ((imageHeight / 4) + 1) * 4 : imageHeight;
	destinationBuffer = (uint8 *)malloc((imageWidth * imageHeight) / 8);
	dstIdx = destinationBuffer;
	remainingBlocks = (imageWidth * imageHeight) / 16;

	while (remainingBlocks) { // Repeat until all blocks are decompressed
		if (!controlBits) {
			controlData = READ_LE_UINT16(srcIdx);
			srcIdx += 2;

			// If bit 15 of controlData is enabled, compression data is type 1.
			// else if controlData has bit 16 enabled, compression type is 2,
			// else there is no compression.
			if (controlData & 0x4000)
				compressionType = 2;
			else if (controlData & 0x8000)
				compressionType = 1;
			else
				compressionType = 0;

			// Fetch control bits from controlData
			controlBits = controlData & 0x3FFF;

			// If there is compression, we need to fetch an index
			// to be treated as "base" for compression.
			if (compressionType != 0) {
				controlData = READ_LE_UINT16(srcIdx);
				srcIdx += 2;
				baseIndex = controlData;
			}
		}

		uint32 decremTiles; // Number of blocks that will be decompressed
		if (remainingBlocks < controlBits) {
			controlBits = controlBits - remainingBlocks;
			decremTiles = remainingBlocks;
		} else {
			decremTiles = controlBits;
			controlBits = 0;
		}

		// Decrement remaining blocks
		remainingBlocks -= decremTiles;

		// Manage different compressions
		switch (compressionType) {
			case 0: // No compression, plain copy of indexes
				while (decremTiles) {
					WRITE_LE_UINT16(dstIdx, READ_LE_UINT16(srcIdx));
					srcIdx += 2;
					dstIdx += 2;
					decremTiles--;
				}
				break;
			case 1: // Compression type 1, repeat a base index
				while (decremTiles) {
					WRITE_LE_UINT16(dstIdx, baseIndex);
					dstIdx += 2;
					decremTiles--;
				}
				break;
			case 2: // Compression type 2, increment a base index
				while (decremTiles) {
					WRITE_LE_UINT16(dstIdx, baseIndex);
					baseIndex++;
					dstIdx += 2;
					decremTiles--;
				}
				break;
			default:
				break;
		}
	}

	// End.
	return destinationBuffer;
}

/**
 * Straight rendering of uncompressed data
 */
static void t0WrtNonZero(DRAWOBJECT *pObj, uint8 *srcP, uint8 *destP, bool applyClipping) {
	int yClip = 0;

	if (applyClipping) {
		// Adjust the height down to skip any bottom clipping
		pObj->height -= pObj->botClip;
		yClip = pObj->topClip;
	}

	// Vertical loop
	for (int y = 0; y < pObj->height; ++y) {
		// Get the start of the next line output
		uint8 *tempDest = destP;

		int leftClip = applyClipping ? pObj->leftClip : 0;
		int rightClip = applyClipping ? pObj->rightClip : 0;

		// Horizontal loop
		for (int x = 0; x < pObj->width; ) {
			uint32 numBytes = READ_LE_UINT32(srcP);
			srcP += sizeof(uint32);
			bool repeatFlag = (numBytes & 0x80000000L) != 0;
			numBytes &= 0x7fffffff;

			uint clipAmount = MIN((int)numBytes & 0xff, leftClip);
			leftClip -= clipAmount;
			x += clipAmount;

			if (repeatFlag) {
				// Repeat of a given color
				uint8 color = (numBytes >> 8) & 0xff;
				int runLength = (numBytes & 0xff) - clipAmount;

				int rptLength = MAX(MIN(runLength, pObj->width - rightClip - x), 0);
				if (yClip == 0) {
					if (color != 0)
						memset(tempDest, color, rptLength);
					tempDest += rptLength;
				}

				x += runLength;
			} else {
				// Copy a specified sequence length of pixels
				srcP += clipAmount;

				int runLength = numBytes - clipAmount;
				int rptLength = MAX(MIN(runLength, pObj->width - rightClip - x), 0);
				if (yClip == 0) {
					memmove(tempDest, srcP, rptLength);
					tempDest += rptLength;
				}

				int overflow = (numBytes % 4) == 0 ? 0 : 4 - (numBytes % 4);
				x += runLength;
				srcP += runLength + overflow;
			}
		}

		// Move to next line
		if (yClip > 0)
			--yClip;
		else
			destP += SCREEN_WIDTH;
	}
}

/**
 * Straight rendering with transparency support, Mac variant
 */
static void MacDrawTiles(DRAWOBJECT *pObj, uint8 *srcP, uint8 *destP, bool applyClipping) {
	int yClip = 0;

	if (applyClipping) {
		// Adjust the height down to skip any bottom clipping
		pObj->height -= pObj->botClip;
		yClip = pObj->topClip;
	}

	// Simple RLE-like scheme: the two first bytes of each data chunk determine
	// if bytes should be repeated or copied.
	// Example: 10 00 00 20 will repeat byte 0x0 0x10 times, and will copy 0x20
	// bytes from the input stream afterwards

	// Vertical loop
	for (int y = 0; y < pObj->height; ++y) {
		// Get the start of the next line output
		uint8 *tempDest = destP;

		int leftClip = applyClipping ? pObj->leftClip : 0;
		int rightClip = applyClipping ? pObj->rightClip : 0;

		// Horizontal loop
		for (int x = 0; x < pObj->width; ) {
			byte repeatBytes = *srcP++;

			if (repeatBytes) {
				uint clipAmount = MIN<int>(repeatBytes, leftClip);
				leftClip -= clipAmount;
				x += clipAmount;

				// Repeat of a given color
				byte color = *srcP++;
				int runLength = repeatBytes - clipAmount;
				int rptLength = MAX(MIN(runLength, pObj->width - rightClip - x), 0);
				if (yClip == 0) {
					if (color != 0)
						memset(tempDest, color, rptLength);
					tempDest += rptLength;
				}

				x += runLength;
			} else {
				// Copy a specified sequence length of pixels
				byte copyBytes = *srcP++;

				uint clipAmount = MIN<int>(copyBytes, leftClip);
				leftClip -= clipAmount;
				x += clipAmount;
				srcP += clipAmount;

				int runLength = copyBytes - clipAmount;
				int rptLength = MAX(MIN(runLength, pObj->width - rightClip - x), 0);
				if (yClip == 0) {
					memmove(tempDest, srcP, rptLength);
					tempDest += rptLength;
				}

				int overflow = (copyBytes & 1);
				x += runLength;
				srcP += runLength + overflow;
			}
		}	// horizontal loop

		// Move to next line
		if (yClip > 0)
			--yClip;
		else
			destP += SCREEN_WIDTH;
	}	// vertical loop
}


/**
 * Straight rendering with transparency support, PSX/Saturn variant supporting also 4-BIT clut data for PSX
 */
static void psxSaturnDrawTiles(DRAWOBJECT *pObj, uint8 *srcP, uint8 *destP, bool applyClipping, bool fourBitClut, uint32 psxSkipBytes, byte *psxMapperTable, bool transparency) {
	// Set up the offset between destination blocks
	int rightClip = applyClipping ? pObj->rightClip : 0;
	Common::Rect boxBounds;

	if (applyClipping) {
		// Adjust the height down to skip any bottom clipping
		pObj->height -= pObj->botClip;

		// Make adjustment for the top clipping row
		srcP += sizeof(uint16) * ((pObj->width + 3) >> 2) * (pObj->topClip >> 2);
		pObj->height -= pObj->topClip;
		pObj->topClip %= 4;
	}

	// Vertical loop
	while (pObj->height > 0) {
		// Get the start of the next line output
		uint8 *tempDest = destP;

		// Get the line width, and figure out which row range within the 4 row high blocks
		// will be displayed if clipping is to be taken into account
		int width = pObj->width;

		if (!applyClipping) {
			// No clipping, so so set box bounding area for drawing full 4x4 pixel blocks
			boxBounds.top = 0;
			boxBounds.bottom = 3;
			boxBounds.left = 0;
		} else {
			// Handle any possible clipping at the top of the char block.
			// We already handled topClip partially at the beginning of this function.
			// Hence the only non-zero values it can assume at this point are 1,2,3,
			// and that only during the very first iteration (i.e. when the top char
			// block is drawn only partially). In particular, we set topClip to zero,
			// as all following blocks are not to be top clipped.
			boxBounds.top = pObj->topClip;
			pObj->topClip = 0;

			boxBounds.bottom = MIN(boxBounds.top + pObj->height - 1, 3);

			// Handle any possible clipping at the start of the line
			boxBounds.left = pObj->leftClip;
			if (boxBounds.left >= 4) {
				srcP += sizeof(uint16) * (boxBounds.left >> 2);
				width -= boxBounds.left & 0xfffc;
				boxBounds.left %= 4;
			}

			width -= boxBounds.left;
		}

		// Horizontal loop
		while (width > rightClip) {
			boxBounds.right = MIN(boxBounds.left + width - rightClip - 1, 3);
			assert(boxBounds.bottom >= boxBounds.top);
			assert(boxBounds.right >= boxBounds.left);

			int16 indexVal = READ_LE_UINT16(srcP);
			srcP += sizeof(uint16);

			// Draw a 4x4 block based on the opcode as in index into the block list
			// In case we have a 4-bit CLUT image, blocks are 2x4 bytes, then expanded into 4x4
			const uint8 *p;
			if (fourBitClut)
				p = (uint8 *)pObj->charBase + psxSkipBytes + (indexVal << 3);
			else
				p = (uint8 *)pObj->charBase + psxSkipBytes + (indexVal << 4);

			p += boxBounds.top * (fourBitClut ? sizeof(uint16) : sizeof(uint32));
			for (int yp = boxBounds.top; yp <= boxBounds.bottom; ++yp, p += (fourBitClut ? sizeof(uint16) : sizeof(uint32))) {
				if (!fourBitClut) {
					if (!transparency)
						Common::copy(p + boxBounds.left, p + boxBounds.right + 1, tempDest + (SCREEN_WIDTH * (yp - boxBounds.top)));
					else
						for (int xp = boxBounds.left; xp <= boxBounds.right; ++xp) {
							if (*(p + xp))
								*(tempDest + SCREEN_WIDTH * (yp - boxBounds.top) + (xp - boxBounds.left)) = *(p + xp);
						}
				} else {
					for (int xp = boxBounds.left; xp <= boxBounds.right; ++xp) {
						// Extract pixel value from byte
						byte pixValue =  (*(p + (xp / 2)) & ((xp % 2) ? 0xf0 : 0x0f)) >> ((xp % 2) ? 4 : 0);
						if (pixValue || !transparency)
							*(tempDest + SCREEN_WIDTH * (yp - boxBounds.top) + (xp - boxBounds.left)) = psxMapperTable[pixValue];
					}
				}
			}

			tempDest += boxBounds.right - boxBounds.left + 1;
			width -= 3 - boxBounds.left + 1;

			// None of the remaining horizontal blocks should be left clipped
			boxBounds.left = 0;
		}

		// If there is any width remaining, there must be a right edge clipping
		if (width >= 0)
			srcP += sizeof(uint16) * ((width + 3) >> 2);

		// Move to next line line
		pObj->height -= boxBounds.bottom - boxBounds.top + 1;
		destP += (boxBounds.bottom - boxBounds.top + 1) * SCREEN_WIDTH;
	}
}

/**
 * Straight rendering with transparency support
 */
static void WrtNonZero(DRAWOBJECT *pObj, uint8 *srcP, uint8 *destP, bool applyClipping) {
	// Set up the offset between destination blocks
	int rightClip = applyClipping ? pObj->rightClip : 0;
	Common::Rect boxBounds;

	if (applyClipping) {
		// Adjust the height down to skip any bottom clipping
		pObj->height -= pObj->botClip;

		// Make adjustment for the top clipping row
		srcP += sizeof(uint16) * ((pObj->width + 3) >> 2) * (pObj->topClip >> 2);
		pObj->height -= pObj->topClip;
		pObj->topClip %= 4;
	}

	// Vertical loop
	while (pObj->height > 0) {
		// Get the start of the next line output
		uint8 *tempDest = destP;

		// Get the line width, and figure out which row range within the 4 row high blocks
		// will be displayed if clipping is to be taken into account
		int width = pObj->width;

		if (!applyClipping) {
			// No clipping, so so set box bounding area for drawing full 4x4 pixel blocks
			boxBounds.top = 0;
			boxBounds.bottom = 3;
			boxBounds.left = 0;
		} else {
			// Handle any possible clipping at the top of the char block.
			// We already handled topClip partially at the beginning of this function.
			// Hence the only non-zero values it can assume at this point are 1,2,3,
			// and that only during the very first iteration (i.e. when the top char
			// block is drawn only partially). In particular, we set topClip to zero,
			// as all following blocks are not to be top clipped.
			boxBounds.top = pObj->topClip;
			pObj->topClip = 0;

			boxBounds.bottom = MIN(boxBounds.top + pObj->height - 1, 3);

			// Handle any possible clipping at the start of the line
			boxBounds.left = pObj->leftClip;
			if (boxBounds.left >= 4) {
				srcP += sizeof(uint16) * (boxBounds.left >> 2);
				width -= boxBounds.left & 0xfffc;
				boxBounds.left %= 4;
			}

			width -= boxBounds.left;
		}

		// Horizontal loop
		while (width > rightClip) {
			boxBounds.right = MIN(boxBounds.left + width - rightClip - 1, 3);
			assert(boxBounds.bottom >= boxBounds.top);
			assert(boxBounds.right >= boxBounds.left);

			int16 indexVal = READ_LE_UINT16(srcP);
			srcP += sizeof(uint16);

			if (indexVal >= 0) {
				// Draw a 4x4 block based on the opcode as in index into the block list
				const uint8 *p = (uint8 *)pObj->charBase + (indexVal << 4);
				p += boxBounds.top * sizeof(uint32);
				for (int yp = boxBounds.top; yp <= boxBounds.bottom; ++yp, p += sizeof(uint32)) {
					Common::copy(p + boxBounds.left, p + boxBounds.right + 1, tempDest + (SCREEN_WIDTH * (yp - boxBounds.top)));
				}

			} else {
				// Draw a 4x4 block with transparency support
				indexVal &= 0x7fff;

				// If index is zero, then skip drawing the block completely
				if (indexVal > 0) {
					// Use the index along with the object's translation offset
					const uint8 *p = (uint8 *)pObj->charBase + ((pObj->transOffset + indexVal) << 4);

					// Loop through each pixel - only draw a pixel if it's non-zero
					p += boxBounds.top * sizeof(uint32);
					for (int yp = boxBounds.top; yp <= boxBounds.bottom; ++yp) {
						p += boxBounds.left;
						for (int xp = boxBounds.left; xp <= boxBounds.right; ++xp, ++p) {
							if (*p)
								*(tempDest + SCREEN_WIDTH * (yp - boxBounds.top) + (xp - boxBounds.left)) = *p;
						}
						p += 3 - boxBounds.right;
					}
				}
			}

			tempDest += boxBounds.right - boxBounds.left + 1;
			width -= 3 - boxBounds.left + 1;

			// None of the remaining horizontal blocks should be left clipped
			boxBounds.left = 0;
		}

		// If there is any width remaining, there must be a right edge clipping
		if (width >= 0)
			srcP += sizeof(uint16) * ((width + 3) >> 2);

		// Move to next line line
		pObj->height -= boxBounds.bottom - boxBounds.top + 1;
		destP += (boxBounds.bottom - boxBounds.top + 1) * SCREEN_WIDTH;
	}
}

/**
 * Tinsel 2 Straight rendering with transparency support
 */
static void t2WrtNonZero(DRAWOBJECT *pObj, uint8 *srcP, uint8 *destP, bool applyClipping, bool horizFlipped) {
	// Setup for correct clipping of object edges
	int yClip = applyClipping ? pObj->topClip : 0;
	if (applyClipping)
		pObj->height -= pObj->botClip;
	int numBytes;
	int clipAmount;

	// WORKAROUND: One of the mortician frames has several corrupt bytes in the Russian version
	if ((pObj->hBits == 2517583660UL) && (_vm->getLanguage() == Common::RU_RUS)) {
		uint8 correctBytes[5] = {0xA3, 0x00, 0x89, 0xC0, 0xA6};
		Common::copy(&correctBytes[0], &correctBytes[5], srcP);
	}

	for (int y = 0; y < pObj->height; ++y) {
		// Get the position to start writing out from
		uint8 *tempP = !horizFlipped ? destP :
			destP + (pObj->width - pObj->leftClip - pObj->rightClip) - 1;
		int leftClip = applyClipping ? pObj->leftClip : 0;
		int rightClip = applyClipping ? pObj->rightClip : 0;
		if (horizFlipped)
			SWAP(leftClip, rightClip);

		int x = 0;
		while (x < pObj->width) {
			// Get the next opcode
			numBytes = *srcP++;
			if (numBytes & 0x80) {
				// Run length following
				numBytes &= 0x7f;
				clipAmount = MIN(numBytes, leftClip);
				leftClip -= clipAmount;
				x+= clipAmount;

				int runLength = numBytes - clipAmount;
				uint8 color = *srcP++;

				if ((yClip == 0) && (runLength > 0) && (color != 0)) {
					runLength = MIN(runLength, pObj->width - rightClip - x);

					if (runLength > 0) {
						// Non-transparent run length
						color += pObj->constant;
						if (horizFlipped)
							Common::fill(tempP - runLength + 1, tempP + 1, color);
						else
							Common::fill(tempP, tempP + runLength, color);
					}
				}

				if (horizFlipped)
					tempP -= runLength;
				else
					tempP += runLength;

				x += numBytes - clipAmount;

			} else {
				// Dump a length of pixels
				clipAmount = MIN(numBytes, leftClip);
				leftClip -= clipAmount;
				srcP += clipAmount;
				int runLength = numBytes - clipAmount;
				x += numBytes - runLength;

				for (int xp = 0; xp < runLength; ++xp) {
					if ((yClip > 0) || (x >= (pObj->width - rightClip)))
						++srcP;
					else if (horizFlipped)
						*tempP-- = pObj->constant + *srcP++;
					else
						*tempP++ = pObj->constant + *srcP++;
					++x;
				}
			}
		}
		assert(x == pObj->width);

		if (yClip > 0)
			--yClip;
		else
			destP += SCREEN_WIDTH;
	}
}


static void t3WrtNonZero(DRAWOBJECT *pObj, uint8 *srcP, uint8 *destP) {
	bool applyClipping = (pObj->flags & DMA_CLIP) != 0;
	bool horizFlipped = (pObj->flags & DMA_FLIPH) != 0;

	if (pObj->isRLE)
	{
		int yClip = applyClipping ? pObj->topClip : 0;
		if (applyClipping) {
			pObj->height -= pObj->botClip;
		}

		for (int y = 0; y < pObj->height; ++y) {
			uint8 *tempP = destP;
			int leftClip = applyClipping ? pObj->leftClip : 0;
			int rightClip = applyClipping ? pObj->rightClip : 0;

			if (horizFlipped) {
				SWAP(leftClip, rightClip);
			}

			int x = 0;
			while (x < pObj->width) {
				int numPixels = READ_LE_UINT16(srcP);
				srcP += 2;

				if (numPixels & 0x8000) {
					numPixels &= 0x7FFF;

					int clipAmount = MIN(numPixels, leftClip);
					leftClip -= clipAmount;
					x += clipAmount;

					int runLength = numPixels - clipAmount;

					uint16 color = READ_LE_UINT16(srcP);
					srcP += 2;

					if ((yClip == 0) && (runLength > 0)) {
						runLength = MIN(runLength, pObj->width - rightClip - x);

						for (int xp = 0; xp < runLength; ++xp) {
							if (color != 0xF81F) { // "zero" for Tinsel 3 - magenta in 565
								WRITE_UINT16(tempP, color);
							}
							tempP += (horizFlipped ? -2 : 2);
						}
					}

					x += numPixels - clipAmount;
				} else {
					int clipAmount = MIN(numPixels, leftClip);
					leftClip -= clipAmount;
					srcP += clipAmount * 2;
					int runLength = numPixels - clipAmount;
					x += numPixels - runLength;

					for (int xp = 0; xp < runLength; ++xp) {
						if ((yClip == 0) && (x < (pObj->width - rightClip))) {
							uint16 color = READ_LE_UINT16(srcP);

							if (color != 0xF81F) { // "zero" for Tinsel 3 - magenta in 565
								WRITE_UINT16(tempP, color);
							}

							tempP += (horizFlipped ? -2 : 2);
						}
						srcP += 2;
						++x;
					}
				}
			}
			// assert(x == pObj->width);

			if (yClip > 0) {
				--yClip;
			} else {
				destP += SCREEN_WIDTH * 2;
			}
		}
		return;
	}

	if (applyClipping) {
		srcP += (pObj->topClip * pObj->width * 2);

		pObj->height -= pObj->topClip + pObj->botClip;
		pObj->width -= pObj->leftClip + pObj->rightClip;
	}

	for (int y = 0; y < pObj->height; ++y) {
		uint8 *tempP = destP;
		srcP += pObj->leftClip * 2;
		for (int x = 0; x < pObj->width; ++x) {
			uint16 color = READ_LE_UINT16(srcP);
			srcP += 2;

			if (color != 0xF81F) { // "zero" for Tinsel 3 - magenta in 565
				WRITE_UINT16(tempP, color);
			}

			tempP += 2;
		}
		srcP += pObj->rightClip * 2;
		destP += SCREEN_WIDTH * 2;
	}
}

/**
 * Fill the destination area with a constant color
 */
static void WrtConst(DRAWOBJECT *pObj, uint8 *destP, bool applyClipping) {
	if (applyClipping) {
		pObj->height -= pObj->topClip + pObj->botClip;
		pObj->width -= pObj->leftClip + pObj->rightClip;

		if (pObj->width <= 0)
			return;
	}

	// Loop through any remaining lines
	while (pObj->height > 0) {
		Common::fill(destP, destP + pObj->width, pObj->constant);

		--pObj->height;
		destP += SCREEN_WIDTH;
	}
}

/**
 * Tinsel 3 Rendering with transparency support, run-length is not supported
 */
static void t3TransWNZ(DRAWOBJECT *pObj, uint8 *srcP, uint8 *destP) {
	bool applyClipping = (pObj->flags & DMA_CLIP) != 0;

	if (applyClipping) {
		srcP += (pObj->topClip * pObj->width * 2);

		pObj->height -= pObj->topClip + pObj->botClip;
		pObj->width -= pObj->leftClip + pObj->rightClip;
	}

	for (int y = 0; y < pObj->height; ++y) {
		// Get the position to start writing out from
		uint8 *tempP = destP;
		srcP += pObj->leftClip * 2;
		for (int x = 0; x < pObj->width; ++x) {
			uint32 color = READ_LE_UINT16(srcP); //uint32 for checking overflow in blending
			if (color != 0xF81F) { // "zero" for Tinsel 3 - magenta in 565
				uint8 srcR, srcG, srcB;
				t3getRGB(color, srcR, srcG, srcB);

				uint16 dstColor = READ_LE_UINT16(tempP);
				uint8 dstR, dstG, dstB;
				t3getRGB(dstColor, dstR, dstG, dstB);

				if ((pObj->colorFlags & 4) != 0) { // additive blending
					// original algo:
					// color &= 0b1111011111011111;
					// color += dstColor & 0b1111011111011111;
					// if (color > 0xFFFF) {
					// 	color |= 0b1111000000000000;
					// }
					// if (color &  0b0000100000000000) {
					// 	color |= 0b0000011111000000;
					// }
					// if (color &  0b0000000000100000) {
					// 	color |= 0b0000000000011111;
					// }
					// color     &= 0b1111011111011111;
					color = t3getColor(
						MIN(srcR + dstR, 0x1F),
						MIN(srcG + dstG, 0x3F),
						MIN(srcB + dstB, 0x1F)
					);
				} else {
					// original algo looks simple but does not check for overflow
					// color += (dstColor & 0b1111011111011111) >> 1;
					color = t3getColor(
						MIN(srcR + (dstR / 2), 0x1F),
						MIN(srcG + (dstG / 2), 0x3F),
						MIN(srcB + (dstB / 2), 0x1F)
					);
				}
				WRITE_UINT16(tempP, color);
			}
			tempP += 2;
			srcP += 2;
		}
		srcP += pObj->rightClip * 2;
		destP += SCREEN_WIDTH * 2;
	}
}

/**
 * Translates the destination surface within the object's bounds using the transparency
 * lookup table from transpal.cpp (the contents of which have been moved into palette.cpp)
 */
static void WrtTrans(DRAWOBJECT *pObj, uint8 *destP, bool applyClipping) {
	if (applyClipping) {
		pObj->height -= pObj->topClip + pObj->botClip;
		pObj->width -= pObj->leftClip + pObj->rightClip;

		if (pObj->width <= 0)
			return;
	}

	// Set up the offset between destination lines
	int lineOffset = SCREEN_WIDTH - pObj->width;

	// Loop through any remaining lines
	while (pObj->height > 0) {
		for (int i = 0; i < pObj->width; ++i, ++destP)
			*destP = g_transPalette[*destP];

		--pObj->height;
		destP += lineOffset;
	}
}

/**
 * Copies an uncompressed block of data straight to the screen
 */
static void WrtAll(DRAWOBJECT *pObj, uint8 *srcP, uint8 *destP, bool applyClipping) {
	int objWidth = pObj->width;

	if (applyClipping) {
		srcP += (pObj->topClip * pObj->width) + pObj->leftClip;

		pObj->height -= pObj->topClip + pObj->botClip;
		pObj->width -= pObj->leftClip + pObj->rightClip;

		if (pObj->width <= 0)
			return;
	}

	for (int y = 0; y < pObj->height; ++y) {
		Common::copy(srcP, srcP + pObj->width, destP);
		srcP += objWidth;
		destP += SCREEN_WIDTH;
	}
}

/**
 * Copies an uncompressed block of data straight to the screen, Tinsel 3 is using 16bpp, hence "* 2"
 */
static void t3WrtAll(DRAWOBJECT *pObj, uint8 *srcP, uint8 *destP) {
	bool applyClipping = (pObj->flags & DMA_CLIP) != 0;
	int objWidth = pObj->width;

	if (applyClipping) {
		srcP += (pObj->topClip * pObj->width * 2) + (pObj->leftClip * 2);

		pObj->height -= pObj->topClip + pObj->botClip;
		pObj->width -= pObj->leftClip + pObj->rightClip;

		if (pObj->width <= 0)
			return;
	}

	for (int y = 0; y < pObj->height; ++y) {
		Common::copy(srcP, srcP + (pObj->width * 2), destP);
		srcP += objWidth * 2;
		destP += SCREEN_WIDTH * 2;
	}
}


/**
 * Renders a packed data stream with a variable sized palette
 */
static void PackedWrtNonZero(DRAWOBJECT *pObj, uint8 *srcP, uint8 *destP,
							 bool applyClipping, bool horizFlipped, int packingType) {
	uint8 numColors = 0;
	uint8 *colorTable = nullptr;
	int topClip = 0;
	int xOffset = 0;
	int numBytes, color;
	int v;

	if (_vm->getLanguage() == Common::RU_RUS) {
		// WORKAROUND: One of the mortician frames has several corrupt bytes in the Russian version
		if (pObj->hBits == 2517583393UL) {
			uint8 correctBytes[5] = {0x00, 0x00, 0x17, 0x01, 0x00};
			Common::copy(&correctBytes[0], &correctBytes[5], srcP + 267);
		}
		// WORKAROUND: One of Dibbler's frames in the end sequence has corrupt bytes in the Russian version
		if (pObj->hBits == 33651742) {
			uint8 correctBytes[40] = {
				0x06, 0xc0, 0xd6, 0xc1, 0x09, 0xce, 0x0d, 0x24, 0x02, 0x12, 0x01, 0x00, 0x00, 0x23, 0x21, 0x32,
				0x12, 0x00, 0x00, 0x20, 0x01, 0x11, 0x32, 0x12, 0x01, 0x00, 0x00, 0x1b, 0x02, 0x11, 0x34, 0x11,
				0x00, 0x00, 0x18, 0x01, 0x11, 0x35, 0x21, 0x01
			};
			Common::copy(&correctBytes[0], &correctBytes[40], srcP);
		}
	}

	if (applyClipping) {
		pObj->height -= pObj->botClip;
		topClip = pObj->topClip;
	}

	if (packingType == 3) {
		// Variable colors
		numColors = *srcP++;
		colorTable = srcP;
		srcP += numColors;
	}

	for (int y = 0; y < pObj->height; ++y) {
		// Get the position to start writing out from
		uint8 *tempP = !horizFlipped ? destP :
			destP + (pObj->width - pObj->leftClip - pObj->rightClip) - 1;
		int leftClip = applyClipping ? pObj->leftClip : 0;
		int rightClip = applyClipping ? pObj->rightClip : 0;
		if (horizFlipped)
			SWAP(leftClip, rightClip);
		bool eolFlag = false;

		// Get offset for first pixels in next line
		xOffset = *srcP++;

		int x = 0;
		while (x < pObj->width) {
			// Get next run size and color to use
			for (;;) {
				if (xOffset > 0) {
					x += xOffset;

					// Reduce offset amount by any remaining left clipping
					v = MIN(xOffset, leftClip);
					xOffset -= v;
					leftClip -= v;

					if (horizFlipped) tempP -= xOffset; else tempP += xOffset;
					xOffset = 0;
				}

				v = *srcP++;
				numBytes = v & 0xf;	// No. bytes 1-15
				if (packingType == 3)
					color = colorTable[v >> 4];
				else
					color = pObj->baseCol + (v >> 4);

				if (numBytes != 0)
					break;

				numBytes = *srcP++;
				if (numBytes >= 16)
					break;

				xOffset = numBytes + v;
				if (xOffset == 0) {
					// End of line encountered
					eolFlag = true;
					break;
				}
			}

			if (eolFlag)
				break;

			// Apply clipping on byte sequence
			v = MIN(numBytes, leftClip);
			leftClip -= v;
			numBytes -= v;
			x += v;

			while (numBytes-- > 0) {
				if ((topClip == 0) && (x < (pObj->width - rightClip))) {
					*tempP = color;
					if (horizFlipped) --tempP; else ++tempP;
				}
				++x;
			}
		}
		assert(x <= pObj->width);

		if (!eolFlag) {
			// Assert that the next bytes signal a line end
			uint8 d = *srcP++;
			assert((d & 0xf) == 0);
			d = *srcP++;
			assert(d == 0);
		}

		if (topClip > 0)
			--topClip;
		else
			destP += SCREEN_WIDTH;
	}
}

static void t3WrtText(DRAWOBJECT *pObj, uint8 *srcP, uint8 *destP) {
	bool applyClipping = (pObj->flags & DMA_CLIP) != 0;

	if (applyClipping) {
		srcP += (pObj->topClip * pObj->width * 2);

		pObj->height -= pObj->topClip + pObj->botClip;
		pObj->width -= pObj->leftClip + pObj->rightClip;
	}

	uint32 baseColor = t3GetBaseColor();

	for (int y = 0; y < pObj->height; ++y) {
		// Get the position to start writing out from
		uint8 *tempP = destP;
		srcP += pObj->leftClip * 2;
		for (int x = 0; x < pObj->width; ++x) {
			uint32 color = READ_LE_UINT16(srcP);
			if (color != 0xF81F) { // "zero" for Tinsel 3 - magenta in 565
				if (color == baseColor) {
					color = pObj->constant;
				}
				WRITE_UINT16(tempP, color);
			}
			tempP += 2;
			srcP += 2;
		}
		srcP += pObj->rightClip * 2;
		destP += SCREEN_WIDTH * 2;
	}
}

//----------------- MAIN FUNCTIONS ---------------------

/**
 * Clears both the screen surface buffer and screen to the specified value
 */
void ClearScreen() {
	byte blackColorIndex = (!TinselV1Mac) ? 0 : 255;
	void *pDest = _vm->screen().getPixels();
	memset(pDest, blackColorIndex, SCREEN_WIDTH * SCREEN_HEIGHT);
	g_system->fillScreen(blackColorIndex);
	g_system->updateScreen();
}

/**
 * Updates the screen surface within the following rectangle
 */
void UpdateScreenRect(const Common::Rect &pClip) {
	int yOffset = TinselV2 ? (g_system->getHeight() - SCREEN_HEIGHT) / 2 : 0;
	byte *pSrc = (byte *)_vm->screen().getBasePtr(pClip.left, pClip.top);
	g_system->copyRectToScreen(pSrc, _vm->screen().pitch, pClip.left, pClip.top + yOffset,
		pClip.width(), pClip.height());
}

/**
 * Draws the specified object onto the screen surface buffer
 */
void DrawObject(DRAWOBJECT *pObj) {
	uint8 *srcPtr = nullptr;
	uint8 *destPtr;
	byte psxMapperTable[16];

	bool psxFourBitClut = false; // Used by Tinsel PSX, true if an image using a 4bit CLUT is rendered
	bool psxSaturnRLEindex = false; // Used by Tinsel PSX/Saturn, true if an image is using PJCRLE compressed indexes
	uint32 psxSkipBytes = 0; // Used by Tinsel PSX, number of bytes to skip before counting indexes for image tiles

	if ((pObj->width <= 0) || (pObj->height <= 0))
		// Empty image, so return immediately
		return;

	// If writing constant data, don't bother locking the data pointer and reading src details
	if (((pObj->flags & DMA_CONST) == 0) || (TinselV3 && ((pObj->flags & 0x05) == 0x05))) {
		if (TinselV2) {
			srcPtr = (byte *)_vm->_handle->LockMem(pObj->hBits);
			pObj->charBase = nullptr;
			pObj->transOffset = 0;
		} else {
			byte *p = (byte *)_vm->_handle->LockMem(pObj->hBits & HANDLEMASK);

			srcPtr = p + (pObj->hBits & OFFSETMASK);
			pObj->charBase = (char *)p + READ_32(p + 0x10);
			pObj->transOffset = READ_32(p + 0x14);

			// Decompress block indexes for Discworld PSX/Saturn
			if (TinselV1PSX || TinselV1Saturn) {
				uint8 paletteType = TinselV1PSX ? *(srcPtr) : *(srcPtr + 1); // if 0x88 we are using an 8bit palette type, if 0x44 we are using a 4 bit PSX CLUT
				uint8 indexType = TinselV1PSX ? *(srcPtr + 1) : *(srcPtr); // if 0xCC indexes for this image are compressed with PCJRLE, if 0xDD indexes are not compressed

				switch (paletteType) {
					case 0x00: // Normal 8-bit palette (Saturn)
					case 0x88: // Normal 8-bit palette (PSX)
						psxFourBitClut = false;
						psxSkipBytes = 0;
						switch (indexType) {
							case 0xDD: // Normal uncompressed indexes
								psxSaturnRLEindex = false;
								srcPtr += sizeof(uint16); // Get to the beginning of index data
								break;
							case 0xCC: // PJCRLE compressed indexes
								psxSaturnRLEindex = true;
								srcPtr = psxSaturnPJCRLEUnwinder(pObj->width, pObj->height, srcPtr + sizeof(uint16));
								break;
							default:
								error("Unknown PSX/Saturn index type 0x%.2X", indexType);
								break;
						}
						break;
					case 0x44: // PSX 4-bit CLUT
						psxPaletteMapper(pObj->pPal, srcPtr + sizeof(uint16), psxMapperTable);

						psxFourBitClut = true;
						psxSkipBytes = READ_32(p + sizeof(uint32) * 5) << 4; // Fetch number of bytes we have to skip
						switch (indexType) {
							case 0xDD: // Normal uncompressed indexes
								psxSaturnRLEindex = false;
								srcPtr += sizeof(uint16) * 17; // Skip image type and clut, and get to beginning of index data
								break;
							case 0xCC: // PJCRLE compressed indexes
								psxSaturnRLEindex = true;
								srcPtr = psxSaturnPJCRLEUnwinder(pObj->width, pObj->height, srcPtr + sizeof(uint16) * 17);
								break;
							default:
								error("Unknown PSX index type 0x%.2X", indexType);
								break;
						}
						break;
					default:
						error("Unknown PSX/Saturn palette type 0x%.2X", paletteType);
						break;
				}
			}
		}

	}

	// Get destination starting point
	destPtr = (byte *)_vm->screen().getBasePtr(pObj->xPos, pObj->yPos);

	// Handle various draw types
	uint8 typeId = pObj->flags & 0xff;
	int packType = pObj->flags >> 14;	// TinselV2

	if (TinselV2 && packType != 0) {
		// Color packing for TinselV2

		if (packType == 1)
			pObj->baseCol = 0xF0;	// 16 from 240
		else if (packType == 2)
			pObj->baseCol = 0xE0;	// 16 from 224
		// 3 = variable color

		PackedWrtNonZero(pObj, srcPtr, destPtr, (pObj->flags & DMA_CLIP) != 0,
			(pObj->flags & DMA_FLIPH), packType);
	} else {
		switch (typeId) {
		case 0x01:	// all versions, draw sprite without clipping
		case 0x41:	// all versions, draw sprite with clipping
		case 0x02:	// TinselV2, draw sprite without clipping
		case 0x11:	// TinselV2, draw sprite without clipping, flipped horizontally
		case 0x42:	// TinselV2, draw sprite with clipping
		case 0x51:	// TinselV2, draw sprite with clipping, flipped horizontally
			assert(TinselV2 || (typeId == 0x01 || typeId == 0x41));

			if (TinselV3)
				t3WrtNonZero(pObj, srcPtr, destPtr);
			else if (TinselV2)
				t2WrtNonZero(pObj, srcPtr, destPtr, (typeId & DMA_CLIP) != 0, (typeId & DMA_FLIPH) != 0);
			else if (TinselV1PSX || TinselV1Saturn)
				psxSaturnDrawTiles(pObj, srcPtr, destPtr, typeId == 0x41, psxFourBitClut, psxSkipBytes, psxMapperTable, true);
			else if (TinselV1Mac)
				MacDrawTiles(pObj, srcPtr, destPtr, typeId == 0x41);
			else if (TinselV1)
				WrtNonZero(pObj, srcPtr, destPtr, typeId == 0x41);
			else if (TinselV0)
				t0WrtNonZero(pObj, srcPtr, destPtr, typeId == 0x41);
			break;
		case 0x08:	// draw background without clipping
		case 0x48:	// draw background with clipping
			if (TinselV3)
				t3WrtAll(pObj, srcPtr, destPtr);
			else if (TinselV2 || TinselV1Mac || TinselV0)
				WrtAll(pObj, srcPtr, destPtr, typeId == 0x48);
			else if (TinselV1PSX || TinselV1Saturn)
				psxSaturnDrawTiles(pObj, srcPtr, destPtr, typeId == 0x48, psxFourBitClut, psxSkipBytes, psxMapperTable, false);
			else if (TinselV1)
				WrtNonZero(pObj, srcPtr, destPtr, typeId == 0x48);
			break;
		case 0x04:	// fill with constant color without clipping
		case 0x44:	// fill with constant color with clipping
			WrtConst(pObj, destPtr, typeId == 0x44);
			break;
		case 0x81:	// TinselV3, draw sprite with transparency
		case 0xC1:	// TinselV3, draw sprite with transparency & clipping
			if (TinselV3)
				t3TransWNZ(pObj, srcPtr, destPtr);
			else if (TinselV2)
				t2WrtNonZero(pObj, srcPtr, destPtr, (typeId & DMA_CLIP) != 0, (typeId & DMA_FLIPH) != 0);
			break;
		case 0x84:	// draw transparent surface without clipping
		case 0xC4:	// draw transparent surface with clipping
			WrtTrans(pObj, destPtr, typeId == 0xC4);
			break;
		case 0x05:	// TinselV3, draw text with color replacement without clipping
		case 0x45:	// TinselV3, draw text with color replacement with clipping
			assert(TinselV3);
			t3WrtText(pObj, srcPtr, destPtr);
			break;
		default:
			error("Unknown drawing type %d", typeId);
		}
	}

	// If we were using Discworld PSX/Saturn, free the memory allocated
	// for decompressed block indexes.
	if ((TinselV1PSX || TinselV1Saturn) && psxSaturnRLEindex)
		free(srcPtr);
}

} // End of namespace Tinsel
