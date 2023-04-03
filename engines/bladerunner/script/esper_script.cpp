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
 */

#include "bladerunner/script/esper_script.h"

#include "bladerunner/bladerunner.h"
#include "bladerunner/mouse.h"

namespace BladeRunner {

void ESPERScript::initialize() {
	_vm->_mouse->disable();
	SCRIPT_ESPER_DLL_Initialize();
	_vm->_mouse->enable();
}

void ESPERScript::photoSelected(int photoId) {
	_vm->_mouse->disable();
	SCRIPT_ESPER_DLL_Photo_Selected(photoId);
	_vm->_mouse->enable();
}

void ESPERScript::specialRegionSelected(int photoId, int regionId) {
	_vm->_mouse->disable();
	SCRIPT_ESPER_DLL_Special_Region_Selected(photoId, regionId);
	_vm->_mouse->enable();
}

void ESPERScript::SCRIPT_ESPER_DLL_Initialize() {
	int v0 = 0;
	if (Actor_Clue_Query(kActorMcCoy, kClueRuncitersVideo)) {
		if (!Actor_Clue_Query(kActorMcCoy, kClueRuncitersViewA)) {
			Actor_Says(kActorAnsweringMachine, 160, kAnimationModeTalk);
			Actor_Says(kActorAnsweringMachine, 180, kAnimationModeTalk);
			Actor_Clue_Acquire(kActorMcCoy, kClueRuncitersViewA, true, kActorRunciter);
			v0 = 1;
		}
		ESPER_Add_Photo("RC02_FA.IMG", 0, 0);
		if (!Actor_Clue_Query(kActorMcCoy, kClueRuncitersViewB)) {
			Actor_Clue_Acquire(kActorMcCoy, kClueRuncitersViewB, true, kActorRunciter);
		}
		ESPER_Add_Photo("RC02_RA.IMG", 1, 1);
	}
	// When Early Q is a replicant he is not hiding a disc that contains an image of him assaulting Lucy since that event never happened. Since he is helping the reps 
	// the image on the disc is of Dektoras dressing room where Clovis is giving Dektora flowers. Early Q is trying to cover for the other replicants by hiding 
	// the video evidence of them being there.
	if (_vm->_cutContent) {
		if (Game_Flag_Query(kFlagEarlyQIsReplicant)) { 
			if (Actor_Clue_Query(kActorMcCoy, kClueEarlyQsClub)) {
				if (!Actor_Clue_Query(kActorMcCoy, kClueDektorasDressingRoom)) {
					Actor_Says(kActorAnsweringMachine, 160, kAnimationModeTalk);
					Actor_Says(kActorAnsweringMachine, 170, kAnimationModeTalk);
					Actor_Clue_Acquire(kActorMcCoy, kClueDektorasDressingRoom, true, -1);
					v0 = 1;
				}
				ESPER_Add_Photo("NR070000.IMG", 3, 3);
			}
		} else { 
			if (Actor_Clue_Query(kActorMcCoy, kClueEarlyQsClub)) {
				if (!Actor_Clue_Query(kActorMcCoy, kClueOuterDressingRoom)) {
					Actor_Says(kActorAnsweringMachine, 160, kAnimationModeTalk);
					Actor_Says(kActorAnsweringMachine, 170, kAnimationModeTalk);
					Actor_Clue_Acquire(kActorMcCoy, kClueOuterDressingRoom, true, -1);
					v0 = 1;
				}
				ESPER_Add_Photo("NR060000.IMG", 2, 2);
			}
		}
	} else if (Actor_Clue_Query(kActorMcCoy, kClueEarlyQsClub)) {
		if (!Actor_Clue_Query(kActorMcCoy, kClueOuterDressingRoom)) {
			Actor_Says(kActorAnsweringMachine, 160, kAnimationModeTalk);
			Actor_Says(kActorAnsweringMachine, 170, kAnimationModeTalk);
			Actor_Clue_Acquire(kActorMcCoy, kClueOuterDressingRoom, true, -1);
			v0 = 1;
		}
		ESPER_Add_Photo("NR060000.IMG", 2, 2);
	}
	if (_vm->_cutContent) {
		if (!Game_Flag_Query(kFlagEarlyQIsReplicant)) { 
			if (Actor_Clue_Query(kActorMcCoy, kClueDektorasDressingRoom)) {
				ESPER_Add_Photo("NR070000.IMG", 3, 3);
			}
		}
	} else if (Actor_Clue_Query(kActorMcCoy, kClueDektorasDressingRoom)) {
		ESPER_Add_Photo("NR070000.IMG", 3, 3);

	}
	if (Actor_Clue_Query(kActorMcCoy, kCluePhotoOfMcCoy1)) {
		ESPER_Add_Photo("HC01AR11.IMG", 4, 4);
	}
	if (Actor_Clue_Query(kActorMcCoy, kCluePhotoOfMcCoy2)) {
		ESPER_Add_Photo("HC01AR12.IMG", 5, 5);
	}
	if (Actor_Clue_Query(kActorMcCoy, kClueChinaBar)) {
		ESPER_Add_Photo("HC02CB1.IMG", 6, 6);
	}
	if (Actor_Clue_Query(kActorMcCoy, kClueChinaBarSecurityDisc)) {
		if (!Actor_Clue_Query(kActorMcCoy, kClueChinaBarSecurityPhoto)) {
			Actor_Says(kActorAnsweringMachine, 160, kAnimationModeTalk);
			Actor_Says(kActorAnsweringMachine, 170, kAnimationModeTalk);
			Actor_Clue_Acquire(kActorMcCoy, kClueChinaBarSecurityPhoto, true, kActorHawkersBarkeep);
			v0 = 1;
		}
		ESPER_Add_Photo("HC02CB2.IMG", 7, 7);
	}
	if (Actor_Clue_Query(kActorMcCoy, kClueTyrellSecurity)) {
		if (!Actor_Clue_Query(kActorMcCoy, kClueTyrellSecurityPhoto)) {
			Actor_Says(kActorAnsweringMachine, 160, kAnimationModeTalk);
			Actor_Says(kActorAnsweringMachine, 170, kAnimationModeTalk);
			Actor_Clue_Acquire(kActorMcCoy, kClueTyrellSecurityPhoto, true, kActorTyrellGuard);
			v0 = 1;
		}
		ESPER_Add_Photo("TB060000.IMG", 8, 8);
	}
	if (Actor_Clue_Query(kActorMcCoy, kClueMoonbus1)) {
		ESPER_Add_Photo("KP06.IMG", 9, 9);
	}
	if (v0) {
		Actor_Says(kActorAnsweringMachine, 200, kAnimationModeTalk);
	}
}

void ESPERScript::SCRIPT_ESPER_DLL_Photo_Selected(int photo) {
	switch (photo) {
	case 0:
		Actor_Says(kActorAnsweringMachine, 220, kAnimationModeTalk);
		if (!_vm->_cutContent) {
			ESPER_Define_Special_Region(0, 490, 511, 496, 517, 400, 440, 580, 580, 380, 260, 900, 710, "RC02ESP1");
			ESPER_Define_Special_Region(1, 473, 342, 479, 349, 400, 300, 580, 580, 350, 250, 900, 710, "RC02ESP2");
		}
		ESPER_Define_Special_Region(2, 444, 215, 461, 223, 380, 120, 570, 340, 354, 160, 577, 354, "RC02ESP3");
		break;

	case 1:
		Actor_Says(kActorAnsweringMachine, 220, kAnimationModeTalk);
		ESPER_Define_Special_Region(3, 560, 210, 580, 220, 450, 130, 680, 540, 0, 0, 1279, 959, "RC02ESP4");
		ESPER_Define_Special_Region(4, 584, 482, 595, 493, 460, 400, 660, 540, 0, 0, 1279, 959, "RC02ESP5");
		ESPER_Define_Special_Region(5, 669, 322, 675, 329, 620, 230, 740, 390, 0, 0, 1279, 959, "RC02ESP6");
		ESPER_Define_Special_Region(6, 698, 236, 748, 274, 600, 160, 850, 420, 160, 0, 1279, 750, "RC02ESP7");
		break;

	case 2:
		Actor_Says(kActorAnsweringMachine, 260, kAnimationModeTalk);
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagAR02DektoraBoughtScorpions)) {
				ESPER_Define_Special_Region(7, 102, 809, 108, 861, 20, 720, 200, 930, 191, 95, 1085, 870, "NR06ESP1");
			}
		} else {
			ESPER_Define_Special_Region(7, 102, 809, 108, 861, 20, 720, 200, 930, 191, 95, 1085, 870, "NR06ESP1");
		}
		ESPER_Define_Special_Region(8, 661, 437, 664, 443, 530, 320, 720, 600, 330, 200, 945, 750, "NR06ESP2");
		break;

	case 3:
		Actor_Says(kActorAnsweringMachine, 260, kAnimationModeTalk);
		ESPER_Define_Special_Region(9, 479, 381, 482, 385, 430, 320, 520, 470, 265, 200, 815, 720, "NR07ESP2");
		ESPER_Define_Special_Region(10, 893, 298, 901, 306, 770, 230, 980, 500, 340, 216, 942, 747, "NR07ESP1");
		break;

	case 4:
		Actor_Says(kActorAnsweringMachine, 240, kAnimationModeTalk);
		ESPER_Define_Special_Region(11, 420, 436, 434, 450, 350, 380, 520, 680, 257, 94, 1013, 804, "HC01ESP1");
		ESPER_Define_Special_Region(12, 407, 489, 410, 509, 370, 450, 500, 560, 257, 94, 1013, 804, "HC01ESP2");
		break;

	case 5:
		Actor_Says(kActorAnsweringMachine, 240, kAnimationModeTalk);
		ESPER_Define_Special_Region(13, 720, 485, 728, 491, 640, 390, 780, 630, 257, 94, 1013, 804, "HC01ESP3");
		break;

	case 6:
		Actor_Says(kActorAnsweringMachine, 250, kAnimationModeTalk);
		ESPER_Define_Special_Region(14, 879, 221, 882, 225, 640, 0, 1000, 512, 265, 146, 1014, 813, "HC02ESP5");
		ESPER_Define_Special_Region(15, 660, 550, 678, 572, 560, 480, 850, 910, 265, 146, 1014, 813, "HC02ESP2");
		break;

	case 7:
		Actor_Says(kActorAnsweringMachine, 250, kAnimationModeTalk);
		ESPER_Define_Special_Region(16, 1171, 457, 1184, 466, 1060, 370, 1279, 730, 910, 300, 1279, 678, "HC02ESP3");
		ESPER_Define_Special_Region(17, 328, 398, 340, 413, 250, 350, 460, 640, 100, 236, 530, 612, "HC02ESP4");
		break;

	case 8:
		Actor_Says(kActorAnsweringMachine, 230, kAnimationModeTalk);
		ESPER_Define_Special_Region(18, 166, 623, 177, 632, 38, 528, 320, 770, 26, 530, 313, 771, "TB06ESP1");
		ESPER_Define_Special_Region(19, 156, 356, 164, 360, 60, 280, 250, 460, 14, 251, 257, 459, "TB06ESP2");
		ESPER_Define_Special_Region(20, 395, 158, 410, 185, 270, 70, 760, 640, 125, 0, 560, 307, "TB06ESP3");
		ESPER_Define_Special_Region(21, 343, 269, 352, 276, 290, 200, 410, 340, 157, 118, 565, 405, "TB06ESP4");
		break;

	case 9:
		Actor_Says(kActorAnsweringMachine, 270, kAnimationModeTalk);
		ESPER_Define_Special_Region(22, 1208, 330, 1218, 340, 1050, 160, 1279, 550, 956, 203, 1278, 497, "KP06ESP1");
		ESPER_Define_Special_Region(23, 854, 371, 858, 375, 790, 320, 940, 560, 722, 220, 1000, 505, "KP06ESP2");
		ESPER_Define_Special_Region(24, 615, 325, 648, 365, 440, 220, 820, 959, 326, 140, 948, 474, "KP06ESP3");
		ESPER_Define_Special_Region(25, 373, 417, 382, 426, 310, 370, 480, 560, 228, 323, 493, 509, "KP06ESP4");
		break;

	default:
		break;
	}
}

bool ESPERScript::SCRIPT_ESPER_DLL_Special_Region_Selected(int photo, int region) {
	bool retValue = false;

	switch (photo) {
	case 0:
		if (region == 0) {
			Actor_Voice_Over(4050, kActorVoiceOver);
			if (!Actor_Clue_Query(kActorMcCoy, kClueDragonflyAnklet)) {
				Actor_Says(kActorMcCoy, 6945, 3);
				Sound_Play(kSfxBR034_1A, 50, 0, 0, 50);
				Actor_Clue_Acquire(kActorMcCoy, kClueDragonflyAnklet, true, -1);			
			}
		} else if (region == 1) {
			Actor_Voice_Over(4040, kActorVoiceOver);
			if (!Actor_Clue_Query(kActorMcCoy, kClueLucy)) {
				Actor_Says(kActorMcCoy, 6945, 3);
				Sound_Play(kSfxBR034_1A, 50, 0, 0, 50);
				Actor_Clue_Acquire(kActorMcCoy, kClueLucy, true, -1);
			}
		} else if (region == 2) {
			Actor_Voice_Over(4060, kActorVoiceOver);
			//Added in some dialogue so McCoy makes a comment on the sushi menu clue when he finds it.
			if (_vm->_cutContent) {
				Delay(500);
				Actor_Voice_Over(2010, kActorVoiceOver); //99-2010.AUD	Howie Lee's. In Chinatown. I'd eaten there myself.
				Actor_Voice_Over(2030, kActorVoiceOver); //99-2030.AUD	Bryant once got food poisoning there so he shut it down for a couple of months.
				Actor_Voice_Over(2040, kActorVoiceOver); //99-2040.AUD	Now it was always good for a freebie.
			}
			if (!Actor_Clue_Query(kActorMcCoy, kClueSushiMenu)) {
				Actor_Says(kActorMcCoy, 6945, 3);
				Sound_Play(kSfxBR034_1A, 50, 0, 0, 50);
				Actor_Clue_Acquire(kActorMcCoy, kClueSushiMenu, true, -1);
			}
		}
		retValue = true;
		break;

	case 1:
		if (region == 3) {
			Actor_Voice_Over(4080, kActorVoiceOver);
			if (!Actor_Clue_Query(kActorMcCoy, kClueAnimalMurderSuspect)) {
				Actor_Says(kActorMcCoy, 6945, 3);
				Sound_Play(kSfxBR034_1A, 50, 0, 0, 50);
				Actor_Clue_Acquire(kActorMcCoy, kClueAnimalMurderSuspect, true, -1);
			}
		} else if (region == 4) {
			if (_vm->_cutContent) {
				if (Actor_Clue_Query(kActorMcCoy, kClueAnimalMurderSuspect)) {
					Actor_Voice_Over(4110, kActorVoiceOver);
					if (!Actor_Clue_Query(kActorMcCoy, kClueMilitaryBoots)) {
						Actor_Says(kActorMcCoy, 6945, 3);
						Sound_Play(kSfxBR034_1A, 50, 0, 0, 50);
						Actor_Clue_Acquire(kActorMcCoy, kClueMilitaryBoots, true, -1);
					}
				} else {
					Actor_Says(kActorMcCoy, 8525, 3); // 00-8525.AUD	Hmph.
				}
			} else {
				Actor_Voice_Over(4110, kActorVoiceOver);
				if (!Actor_Clue_Query(kActorMcCoy, kClueMilitaryBoots)) {
					Actor_Says(kActorMcCoy, 6945, 3);
					Sound_Play(kSfxBR034_1A, 50, 0, 0, 50);
					Actor_Clue_Acquire(kActorMcCoy, kClueMilitaryBoots, true, -1);
				} 
			}		
		} else if (region == 5) {
			Actor_Voice_Over(4120, kActorVoiceOver);	
			if (!Actor_Clue_Query(kActorMcCoy, kCluePartialLicenseNumber)) {
				if (_vm->_cutContent) {
					if (Actor_Clue_Query(kActorMcCoy, kClueCarColorAndMake)) {
						Actor_Says(kActorMcCoy, 6935, 3); //00-6935.AUD	Enhance.
						Actor_Says(kActorAnsweringMachine, 210, kAnimationModeTalk); //39-0210.AUD	Unable to enhance further.
						Actor_Says(kActorMcCoy, 170, 3); //00-0170.AUD	Damn.
						Delay(1000);
						Actor_Says(kActorMcCoy, 6945, 3);
						Sound_Play(kSfxBR034_1A, 50, 0, 0, 50);
						Actor_Clue_Acquire(kActorMcCoy, kCluePartialLicenseNumber, true, -1);
					} else {
						Actor_Says(kActorMcCoy, 8525, 13); // 00-8525.AUD	Hmph.
					}
				} else {
					Actor_Says(kActorMcCoy, 6945, 3);
					Sound_Play(kSfxBR034_1A, 50, 0, 0, 50);
					Actor_Clue_Acquire(kActorMcCoy, kCluePartialLicenseNumber, true, -1);
				}
			}
		} else if (region == 6) {
			Actor_Voice_Over(4070, kActorVoiceOver);
			if (!Actor_Clue_Query(kActorMcCoy, kClueCarColorAndMake)) {
				if (_vm->_cutContent) {
					if (Actor_Clue_Query(kActorMcCoy, kClueCrowdInterviewB)) {
						Actor_Says(kActorMcCoy, 6945, 3);
						Sound_Play(kSfxBR034_1A, 50, 0, 0, 50);
						Actor_Clue_Acquire(kActorMcCoy, kClueCarColorAndMake, true, -1);
					} else {
						Actor_Says(kActorMcCoy, 8525, 13); // 00-8525.AUD	Hmph.
					}
				} else {
					Actor_Says(kActorMcCoy, 6945, 3);
					Sound_Play(kSfxBR034_1A, 50, 0, 0, 50);
					Actor_Clue_Acquire(kActorMcCoy, kClueCarColorAndMake, true, -1);
				}
			}
		}
		retValue = true;
		break;

	case 2:
		if (region == 8) {
			Actor_Voice_Over(4260, kActorVoiceOver);
			if (!Actor_Clue_Query(kActorMcCoy, kClueEarlyQAndLucy)) {
				Actor_Says(kActorMcCoy, 6945, 3);
				Sound_Play(kSfxBR034_1A, 50, 0, 0, 50);
				Actor_Clue_Acquire(kActorMcCoy, kClueEarlyQAndLucy, true, -1);
			}
		} else if (region == 7) {
			if (_vm->_cutContent) {
				if (Game_Flag_Query(kFlagAR02ScorpionsChecked)
				|| Actor_Clue_Query(kActorMcCoy, kClueScorpions)) {
					Actor_Voice_Over(4190, kActorVoiceOver);
				} else {
					Actor_Says(kActorMcCoy, 8527, 3); //00-8527.AUD	Strange.
				}
				if (!Actor_Clue_Query(kActorMcCoy, kClueScorpionbox)) {
					if (Actor_Clue_Query(kActorMcCoy, kCluePurchasedScorpions)
					|| Actor_Clue_Query(kActorMcCoy, kClueScorpions)) {
						Actor_Says(kActorMcCoy, 6945, 3);
						Sound_Play(kSfxBR034_1A, 50, 0, 0, 50);
						Actor_Clue_Acquire(kActorMcCoy, kClueScorpionbox, true, -1);
					}
				}		
			} else {
				Actor_Voice_Over(4190, kActorVoiceOver);
				if (!Actor_Clue_Query(kActorMcCoy, kClueScorpionbox)) {
					Actor_Says(kActorMcCoy, 6945, 3);
					Sound_Play(kSfxBR034_1A, 50, 0, 0, 50);
					Actor_Clue_Acquire(kActorMcCoy, kClueScorpionbox, true, -1);
				}
			}		
		}
		retValue = true;
		break;

	case 3:
		if (region == 9) {
			Actor_Voice_Over(4230, kActorVoiceOver);
			if (!Actor_Clue_Query(kActorMcCoy, kClueClovisFlowers)) {
				Actor_Says(kActorMcCoy, 6945, 3);
				Sound_Play(kSfxBR034_1A, 50, 0, 0, 50);
				Actor_Clue_Acquire(kActorMcCoy, kClueClovisFlowers, true, -1);
			}
			retValue = true;
		} else if (region == 10) {
			Actor_Voice_Over(4040, kActorVoiceOver);
			if (!Actor_Clue_Query(kActorMcCoy, kClueLucyWithDektora)) {
				Actor_Says(kActorMcCoy, 6945, 3);
				Sound_Play(kSfxBR034_1A, 50, 0, 0, 50);
				Actor_Clue_Acquire(kActorMcCoy, kClueLucyWithDektora, true, -1);
			}
			retValue = true;
		}
		break;

	case 4:
		if (region == 11) {
			if (!_vm->_cutContent) {
				Actor_Voice_Over(4090, kActorVoiceOver);
			}
			if (_vm->_cutContent) {
				if (Actor_Clue_Query(kActorMcCoy, kClueScorpions)
				&& !Actor_Clue_Query(kActorMcCoy, kClueWomanInAnimoidRow)) {
					if (Game_Flag_Query(kFlagNR07McCoyIsCop)
					|| Game_Flag_Query(kFlagDektoraIdentified)) {
						Actor_Says(kActorMcCoy, 7960, 3); //00-7960.AUD	Dektora?
					} else {
						Actor_Says(kActorMcCoy, 8935, 3);
					}
					Actor_Says(kActorMcCoy, 6945, 3);
					Sound_Play(kSfxBR034_1A, 50, 0, 0, 50);
					Actor_Clue_Acquire(kActorMcCoy, kClueWomanInAnimoidRow, true, -1);
					Game_Flag_Set(kFlagDektoraIdentified);
				} else {
					Actor_Says(kActorMcCoy, 8525, 3); // 00-8525.AUD	Hmph.
				}		
			} else if (!Actor_Clue_Query(kActorMcCoy, kClueWomanInAnimoidRow)) {
				Actor_Says(kActorMcCoy, 6945, 3);
				Sound_Play(kSfxBR034_1A, 50, 0, 0, 50);
				Actor_Clue_Acquire(kActorMcCoy, kClueWomanInAnimoidRow, true, -1);
			}
		} else if (region == 12) {
			Actor_Voice_Over(4180, kActorVoiceOver); //99-4180.AUD	Scorpions.
			//Added in some dialogue.
			if (_vm->_cutContent) {
				if (Game_Flag_Query(kFlagAR02ScorpionsChecked)) {
					Actor_Voice_Over(4200, kActorVoiceOver); //99-4200.AUD	Where have I seen those before?
				} else {
					Actor_Says(kActorMcCoy, 8527, 3); //00-8527.AUD	Strange.
				}
			}
			if (!Actor_Clue_Query(kActorMcCoy, kClueScorpions)) {
				Actor_Says(kActorMcCoy, 6945, 3);			
				Sound_Play(kSfxBR034_1A, 50, 0, 0, 50);
				Actor_Clue_Acquire(kActorMcCoy, kClueScorpions, true, -1);
			}
		}
		break;

	case 5:
		if (region == 13) {
			Actor_Says(kActorMcCoy, 8830, 3);
			if (!Actor_Clue_Query(kActorMcCoy, kClueStrangeScale2)) {
				Actor_Says(kActorMcCoy, 6945, 3);
				Sound_Play(kSfxBR034_1A, 50, 0, 0, 50);
				Actor_Clue_Acquire(kActorMcCoy, kClueStrangeScale2, true, -1);
			}
		}
		break;

	case 6:
		if (region == 14) {
			Actor_Says(kActorMcCoy, 6975, 3);
			if (!Actor_Clue_Query(kActorMcCoy, kClueChinaBarSecurityCamera)) {
				Actor_Says(kActorMcCoy, 6945, 3);
				Sound_Play(kSfxBR034_1A, 50, 0, 0, 50);
				Actor_Clue_Acquire(kActorMcCoy, kClueChinaBarSecurityCamera, true, -1);
			}
		} else if (region == 15) {
			if (_vm->_cutContent) {
				if (Actor_Clue_Query(kActorMcCoy, kClueAnimalMurderSuspect)
				|| Actor_Clue_Query(kActorMcCoy, kClueMoonbus1)
				|| Actor_Clue_Query(kActorMcCoy, kClueDektorasDressingRoom)) {
					Actor_Voice_Over(4220, kActorVoiceOver); //99-4220.AUD	That guy sure gets around.
				} else {
					Actor_Voice_Over(4080, kActorVoiceOver);
				}
			} else {
				Actor_Voice_Over(4220, kActorVoiceOver); //99-4220.AUD	That guy sure gets around.
			}
			if (!Actor_Clue_Query(kActorMcCoy, kClueIzosFriend)) {
				Actor_Says(kActorMcCoy, 6945, 3);
				Sound_Play(kSfxBR034_1A, 50, 0, 0, 50);
				Actor_Clue_Acquire(kActorMcCoy, kClueIzosFriend, true, -1);
			}
		}
		break;

	case 7:
		if (region == 16) {
			Actor_Voice_Over(4080, kActorVoiceOver);
			if (!Actor_Clue_Query(kActorMcCoy, kClueIzo)) {
				Actor_Says(kActorMcCoy, 6945, 3);
				Sound_Play(kSfxBR034_1A, 50, 0, 0, 50);
				Actor_Clue_Acquire(kActorMcCoy, kClueIzo, true, -1);
			}
		} else if (region == 17) {
			Actor_Voice_Over(4210, kActorVoiceOver);
			if (!Actor_Clue_Query(kActorMcCoy, kClueGuzza)) {
				Actor_Says(kActorMcCoy, 6945, 3);
				Sound_Play(kSfxBR034_1A, 50, 0, 0, 50);
				Actor_Clue_Acquire(kActorMcCoy, kClueGuzza, true, -1);
			}
		}
		break;

	case 8:
		switch (region) {
		case 18:
			Actor_Says(kActorMcCoy, 8775, 3);
			if (_vm->_cutContent) {
				if (!Actor_Clue_Query(kActorMcCoy, kClueTyrellGuardInterview)) {	
					Actor_Says(kActorMcCoy, 8525, 13); // 00-8525.AUD	Hmph.
				} else {
					if (!Actor_Clue_Query(kActorMcCoy, kClueKingstonKitchenBox1)
					&& !Actor_Clue_Query(kActorMcCoy, kClueKingstonKitchenBox2)) {
						Actor_Says(kActorMcCoy, 6945, 3);
						Sound_Play(kSfxBR034_1A, 50, 0, 0, 50);
						Actor_Clue_Acquire(kActorMcCoy, kClueKingstonKitchenBox2, true, -1);
					}
				}
			} else {
				if (!Actor_Clue_Query(kActorMcCoy, kClueKingstonKitchenBox2)) {
					Actor_Says(kActorMcCoy, 6945, 3);
					Sound_Play(kSfxBR034_1A, 50, 0, 0, 50);
					Actor_Clue_Acquire(kActorMcCoy, kClueKingstonKitchenBox2, true, -1);
				}
			}
			break;

		case 19:
			if (_vm->_cutContent) {
				if (!Actor_Clue_Query(kActorMcCoy, kClueAttemptedFileAccess)) {
					Actor_Says(kActorMcCoy, 8790, 3); //00-8790.AUD	A dog collar.
					Actor_Says(kActorMcCoy, 8525, 13); // 00-8525.AUD	Hmph.
				} else {
					if (Actor_Clue_Query(kActorMcCoy, kClueDNAMarcus)) {
						Actor_Says(kActorMcCoy, 8790, 3); //00-8790.AUD	A dog collar.
					} else {
						Actor_Voice_Over(4160, kActorVoiceOver);
						if (!Actor_Clue_Query(kActorMcCoy, kClueDogCollar1)
						&& !Actor_Clue_Query(kActorMcCoy, kClueDogCollar2)) {
							Actor_Says(kActorMcCoy, 6945, 3);
							Sound_Play(kSfxBR034_1A, 50, 0, 0, 50);
							Actor_Clue_Acquire(kActorMcCoy, kClueDogCollar2, true, -1);
						}
					}
				}
			} else {
				Actor_Voice_Over(4160, kActorVoiceOver);
				if (!Actor_Clue_Query(kActorMcCoy, kClueDogCollar2)) {
					Actor_Says(kActorMcCoy, 6945, 3);
					Sound_Play(kSfxBR034_1A, 50, 0, 0, 50);
					Actor_Clue_Acquire(kActorMcCoy, kClueDogCollar2, true, -1);
				}
			}
			break;

		case 20:
			Actor_Voice_Over(2140, kActorVoiceOver);
			Actor_Voice_Over(2150, kActorVoiceOver);
			Actor_Voice_Over(2160, kActorVoiceOver);
			if (!Actor_Clue_Query(kActorMcCoy, kClueBombingSuspect)) {
				Actor_Says(kActorMcCoy, 6945, 3);
				Sound_Play(kSfxBR034_1A, 50, 0, 0, 50);
				Actor_Clue_Acquire(kActorMcCoy, kClueBombingSuspect, true, -1);
			}
			break;

		case 21:
			Actor_Says(kActorMcCoy, 8890, 3);
			if (!Actor_Clue_Query(kActorMcCoy, kCluePlasticExplosive)) {
				Actor_Says(kActorMcCoy, 6945, 3);
				Sound_Play(kSfxBR034_1A, 50, 0, 0, 50);
				Actor_Clue_Acquire(kActorMcCoy, kCluePlasticExplosive, true, -1);
			}
			break;

		default:
			break;
		}
		break;

	case 9:
		switch (region) {
		case 22:
			if (_vm->_cutContent) {
				if (Actor_Clue_Query(kActorMcCoy, kClueMcCoyAtMoonbus)) {
					Actor_Says(kActorMcCoy, 8705, 3);
					if (!Actor_Clue_Query(kActorMcCoy, kClueMoonbusReflection)) {
						Actor_Says(kActorMcCoy, 6945, 3);
						Sound_Play(kSfxBR034_1A, 50, 0, 0, 50);
						Actor_Clue_Acquire(kActorMcCoy, kClueMoonbusReflection, true, -1);
					}
				} else {
					Actor_Says(kActorMcCoy, 8525, 13); // 00-8525.AUD	Hmph.
					Game_Flag_Set(kFlagMoonbusReflectionChecked);
				}
			} else {
				Actor_Says(kActorMcCoy, 8705, 3);
				if (!Actor_Clue_Query(kActorMcCoy, kClueMoonbusReflection)) {
					Actor_Says(kActorMcCoy, 6945, 3);
					Sound_Play(kSfxBR034_1A, 50, 0, 0, 50);
					Actor_Clue_Acquire(kActorMcCoy, kClueMoonbusReflection, true, -1);
				}
			}
			break;

		case 23:			
			//Added in some dialogue where McCoy theorizes what the other McCoy at the moonbus could really be. Also McCoy concludes that it's not
			//him if he found the moonbus reflection clue
			if (_vm->_cutContent) {
				if (Game_Flag_Query(kFlagMoonbusReflectionChecked)) {
					Actor_Voice_Over(4250, kActorVoiceOver); //99-4250.AUD	That's not me.
					Actor_Voice_Over(4010, kActorVoiceOver); //99-4010.AUD	A cardboard cutout or maybe a mannequin.
					Actor_Voice_Over(4020, kActorVoiceOver); //99-4020.AUD	I didn't know what it was but I did know it wasn't me.
				} else {
					Actor_Voice_Over(4240, kActorVoiceOver);
					if (!Actor_Clue_Query(kActorMcCoy, kClueMcCoyAtMoonbus)) {
						Actor_Says(kActorMcCoy, 6945, 3);
						Sound_Play(kSfxBR034_1A, 50, 0, 0, 50);
						Actor_Clue_Acquire(kActorMcCoy, kClueMcCoyAtMoonbus, true, -1);
					}
				}
			} else {
				Actor_Voice_Over(4240, kActorVoiceOver);
				if (!Actor_Clue_Query(kActorMcCoy, kClueMcCoyAtMoonbus)) {
					Actor_Says(kActorMcCoy, 6945, 3);
					Sound_Play(kSfxBR034_1A, 50, 0, 0, 50);
					Actor_Clue_Acquire(kActorMcCoy, kClueMcCoyAtMoonbus, true, -1);
				}
			}
			break;

		case 24:
			if (_vm->_cutContent) {
				if (Actor_Clue_Query(kActorMcCoy, kClueAnimalMurderSuspect)
				|| Actor_Clue_Query(kActorMcCoy, kClueIzosFriend)
				|| Actor_Clue_Query(kActorMcCoy, kClueDektorasDressingRoom)) {
					Actor_Voice_Over(4220, kActorVoiceOver);
				} else {
					Actor_Voice_Over(4080, kActorVoiceOver);
				}
			} else {
				Actor_Voice_Over(4220, kActorVoiceOver); //99-4220.AUD	That guy sure gets around.
			}
			if (!Actor_Clue_Query(kActorMcCoy, kClueClovisAtMoonbus)) {
				Actor_Says(kActorMcCoy, 6945, 3);
				Sound_Play(kSfxBR034_1A, 50, 0, 0, 50);
				Actor_Clue_Acquire(kActorMcCoy, kClueClovisAtMoonbus, true, -1);
			}
			break;

		case 25:
			if (_vm->_cutContent) {
				Actor_Voice_Over(4170, kActorVoiceOver); //99-4170.AUD	I've seen that guy around town.
			}
			if (!Actor_Clue_Query(kActorMcCoy, kClueSadikAtMoonbus)) {
				Actor_Says(kActorMcCoy, 6945, 3);
				Sound_Play(kSfxBR034_1A, 50, 0, 0, 50);
				Actor_Clue_Acquire(kActorMcCoy, kClueSadikAtMoonbus, true, -1);
			}
			break;

		default:
			break;
		}
		break;

	default:
		break;
	}

	return retValue;
}

} // End of namespace BladeRunner
