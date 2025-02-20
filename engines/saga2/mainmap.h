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
 * aint32 with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 *
 * Based on the original sources
 *   Faery Tale II -- The Halls of the Dead
 *   (c) 1993-1996 The Wyrmkeep Entertainment Co.
 */

#ifndef SAGA2_MAINMAP_H
#define SAGA2_MAINMAP_H 1

namespace Saga2 {

void main_saga2();

// command line parsing
//extern char *commandLineHelp;
void parseCommandLine(int argc, char *argv[]);

// initialization & cleanup
void initCleanup();

bool initializeGame();
void shutdownGame();

bool initSystemTimer();
void cleanupSystemTimer();

void cleanupSystemTasks();
void cleanupPaletteData();

// major parts of main that are actually in main.cpp
void cleanupGame();                  // auto-cleanup function
bool setupGame();
void cleanupPalettes();

} // end of namespace Saga2

#endif
