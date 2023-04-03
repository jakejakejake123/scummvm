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

#include "bladerunner/script/scene_script.h"

namespace BladeRunner {

void SceneScriptHC02::InitializeScene() {
	int loop = kMusicLoopRepeat;
	if (_vm->_cutContent && Random_Query(0, 2) == 1) {
		loop = kMusicLoopRepeatRandomStart;
	}
	Music_Play(kMusicOneTime, 45, -60, 1, -1, loop, 3);
	if (Game_Flag_Query(kFlagHC04toHC02)) {
		Setup_Scene_Information(-88.0f, 0.14f, -463.0f, 540);
	} else {
		Setup_Scene_Information(-57.0f, 0.14f,   83.0f, 746);
	}

	Scene_Exit_Add_2D_Exit(0, 589, 255, 639, 479, 1);
	Scene_Exit_Add_2D_Exit(1, 505,   0, 639, 170, 0);

	Ambient_Sounds_Add_Looping_Sound(kSfxRAINAWN1, 50, 50, 0);
	Ambient_Sounds_Add_Looping_Sound(kSfxBARAMB1,  50, 50, 0);
	if (_vm->_cutContent) {
		Ambient_Sounds_Add_Looping_Sound(kSfxHCSING1,  50, 50, 0);
	}
	Ambient_Sounds_Add_Sound(kSfxBARSFX1,  3, 60, 33, 33,  -60,   0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBARSFX3,  3, 60, 33, 33,  -60,   0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBARSFX4,  3, 60, 33, 33,  -60,   0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBARSFX5,  3, 60, 33, 33,  -60,   0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBARSFX6,  3, 60, 33, 33,  -60,   0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBARSFX7,  3, 60, 33, 33,  -60,   0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxCLINK1,   3, 60, 33, 33, -100,  20, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxCLINK2,   3, 60, 33, 33, -100,  20, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxCLINK3,   3, 60, 33, 33, -100,  20, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxCLINK4,   3, 60, 33, 33, -100,  20, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0480R, 5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0540R, 5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0560R, 5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0870R, 5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0900R, 5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0940R, 5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_1070R, 5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_1080R, 5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_1160R, 5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxHCANM8,   3, 30, 14, 14,   30, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxHCANM2,   3, 30, 14, 14,   30, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxHCANM3,   3, 30, 14, 14,   30, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxHCANM4,   3, 30, 14, 14,   30, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxHCANM5,   3, 30, 14, 14,   30, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxHCANM6,   3, 30, 14, 14,   30, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxHCANM7,   3, 30, 14, 14,   30, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxHCANM1,   3, 30, 14, 14,   30, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxHCBELL1,  3, 50, 20, 20, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxINDFLUT1, 3, 50, 25, 25, -100, 100, -101, -101, 0, 0);

	if (Game_Flag_Query(kFlagHC01toHC02)) {
		Scene_Loop_Start_Special(kSceneLoopModeLoseControl, 0, false);
		Scene_Loop_Set_Default(1);
		Game_Flag_Reset(kFlagHC01toHC02);
	} else {
		Scene_Loop_Set_Default(1);
	}
}

void SceneScriptHC02::SceneLoaded() {
	Obstacle_Object("BARSTOOL01", true);
}

bool SceneScriptHC02::MouseClick(int x, int y) {
	return false;
}

bool SceneScriptHC02::ClickedOn3DObject(const char *objectName, bool a2) {
	return false;
}

bool SceneScriptHC02::ClickedOnActor(int actorId) {
	if (actorId == kActorHawkersBarkeep) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -150.51f, 0.14f, 62.74f, 0, true, false, false)) {
			Actor_Face_Actor(kActorMcCoy, kActorHawkersBarkeep, true);
			if (!Game_Flag_Query(kFlagHC02HawkersBarkeepIntroduction)) {
				if (_vm->_cutContent) {
					if (Actor_Clue_Query(kActorMcCoy, kClueChinaBarSecurityCamera)
					|| (Actor_Clue_Query(kActorMcCoy, kClueHomelessManInterview2)
					&& !Actor_Clue_Query(kActorMcCoy, kClueBigManLimping))) {
						Actor_Says(kActorMcCoy, 1225, 13); //00-1225.AUD	I got a couple of questions for you, Captain.
					} else {
						Actor_Says(kActorMcCoy, 6980, 16); //00-6980.AUD	What's the word on the street.
					}
				} else {
					Actor_Says(kActorMcCoy, 1225, 13); //00-1225.AUD	I got a couple of questions for you, Captain.
				}
				Actor_Says_With_Pause(kActorHawkersBarkeep, 0, 0.0f, 13); //32-0000.AUD	First one's on the house. The rest you pay for.
				Actor_Says(kActorHawkersBarkeep, 10, 16); //32-0010.AUD	You want chit chat you hire a hooker. This ain't no social club.
				if (_vm->_cutContent) {
					if (Player_Query_Agenda() == kPlayerAgendaSurly 
					|| Player_Query_Agenda() == kPlayerAgendaErratic) {
						Actor_Says(kActorMcCoy, 4320, 14); //00-4320.AUD	Save the pitch for someone who gives a shit.
						Delay(2000);
						Actor_Says(kActorMcCoy, 1250, 13); //00-1250.AUD	Pour me one.
					} else if (Player_Query_Agenda() == kPlayerAgendaPolite) { 
						if (Global_Variable_Query(kVariableChinyen) >= 10
						|| Query_Difficulty_Level() == kGameDifficultyEasy) {	
							Actor_Says(kActorMcCoy, 345, 16); //00-0345.AUD	Wanna make some money?
							Delay(1000);
							Actor_Change_Animation_Mode(kActorMcCoy, 23);
							Delay(2000);
							Actor_Says(kActorMcCoy, 8170, 13); //00-8170.AUD	There you go.
							Delay(1000);							 
							Game_Flag_Set(kFlagHawkersBarkeepHappy);
							if (Query_Difficulty_Level() != kGameDifficultyEasy) {
								Global_Variable_Decrement(kVariableChinyen, 10);
							}		
							Actor_Says(kActorMcCoy, 1250, 13); //00-1250.AUD	Pour me one.				
						} else {
							Actor_Says(kActorMcCoy, 1250, 13); //00-1250.AUD	Pour me one.
						}
					} else {
						Actor_Says(kActorMcCoy, 4880, 18); //00-4880.AUD	Is that right?
						Delay(1000);
						Actor_Says(kActorMcCoy, 1250, 13); //00-1250.AUD	Pour me one.
					}
				}
				Actor_Set_Goal_Number(kActorHawkersBarkeep, 1);
				Actor_Change_Animation_Mode(kActorMcCoy, 23);
				if (_vm->_cutContent) {
					Actor_Change_Animation_Mode(kActorHawkersBarkeep, 23);
				}
				Delay(1500);
				Actor_Change_Animation_Mode(kActorMcCoy, 75);
				Delay(1500);
				Global_Variable_Increment(kVariableMcCoyDrinks, 1);
				Game_Flag_Set(kFlagHC02HawkersBarkeepIntroduction);
			} else if ( Actor_Clue_Query(kActorMcCoy, kClueChinaBarSecurityCamera)
			&& !Game_Flag_Query(kFlagMcCoyAsksBarkeepForDisk)
			// Made it so McCoy only asks the barkeep for the disc in acts 2 and 3. It doesn't make any sense for McCoy to ask for it when he is currently investigating the 
			// conspiracy and is on the run from the cops, heck he doesn't even have access to the esper at this point.
			&& Global_Variable_Query(kVariableChapter) < 4) {
				// Added in some dialogue for the barkeep and McCoy. Made it so McCoys response is different based on his agenda.
				Actor_Says(kActorMcCoy, 4545, 11); //00-4545.AUD	You got any discs from that camera?
				Game_Flag_Set(kFlagMcCoyAsksBarkeepForDisk);
				if (_vm->_cutContent) {	
					if (!Game_Flag_Query(kFlagHawkersBarkeepHappy)) {
						Actor_Says(kActorHawkersBarkeep, 120, 12); //32-0120.AUD	I just serve drinks, pal.
						if (Player_Query_Agenda() != kPlayerAgendaPolite) {
							Actor_Says(kActorMcCoy, 3910, 16); //00-3910.AUD	You’re lying.
							Actor_Says(kActorHawkersBarkeep, 150, 16); //32-0150.AUD	Hey, you can always ask someone who cares what you think.
						}
					} else {
						Actor_Says(kActorHawkersBarkeep, 110, 12); // 32-0110.AUD	You've been a good customer, so I'll bent the rules just this once and tell you.
						Actor_Says(kActorHawkersBarkeep, 170, 13); //32-0170.AUD	The truth ain't gonna do you no good.
						Actor_Says(kActorHawkersBarkeep, 180, 14); //32-0180.AUD	But if you're gonna sit there until I cough it up, well, here it is.
						Actor_Change_Animation_Mode(kActorMcCoy, 23);
						Actor_Change_Animation_Mode(kActorHawkersBarkeep, 23);
						Delay(800);
						Item_Pickup_Spin_Effect_From_Actor(kModelAnimationVideoDisc, kActorMcCoy, 0, 0);
						Delay(800);
						Actor_Clue_Acquire(kActorMcCoy, kClueChinaBarSecurityDisc, true, kActorHawkersBarkeep);
						if (Player_Query_Agenda() == kPlayerAgendaPolite) {
							Actor_Says(kActorMcCoy, 1345, 13); //00-1345.AUD	Thanks.
						}
					}
				} else {
					Actor_Says(kActorHawkersBarkeep, 120, 12); //32-0120.AUD	I just serve drinks, pal.
					Actor_Says(kActorHawkersBarkeep, 180, 15); //32-0180.AUD	But if you're gonna sit there until I cough it up, well, here it is.
					Actor_Clue_Acquire(kActorMcCoy, kClueChinaBarSecurityDisc, true, kActorHawkersBarkeep);
					Item_Pickup_Spin_Effect(kModelAnimationVideoDisc, 229, 215);
				}
			} else if (Actor_Clue_Query(kActorMcCoy, kClueHomelessManInterview1)
			           && !Actor_Clue_Query(kActorMcCoy, kClueFlaskOfAbsinthe)
					   && !_vm->_cutContent
#if !BLADERUNNER_ORIGINAL_BUGS
			           // don't re-get the flask if McCoy already gave it to the transient (he loses the kClueFlaskOfAbsinthe clue when he does)
			           && !Actor_Clue_Query(kActorTransient, kClueFlaskOfAbsinthe)
#endif // !BLADERUNNER_ORIGINAL_BUGS
			           && (Global_Variable_Query(kVariableChinyen) > 20
			               || Query_Difficulty_Level() == kGameDifficultyEasy)
			) {
				Actor_Clue_Acquire(kActorMcCoy, kClueFlaskOfAbsinthe, true, kActorHawkersBarkeep);
				Actor_Says(kActorMcCoy, 1230, 13);
				Actor_Says(kActorHawkersBarkeep, 20, 12);
				Actor_Says(kActorMcCoy, 1235, 13);
				Actor_Says(kActorHawkersBarkeep, 30, 15);
				Actor_Says(kActorMcCoy, 1240, 13);
				Actor_Says(kActorHawkersBarkeep, 40, 14);
				Item_Pickup_Spin_Effect(kModelAnimationFlaskOfAbsinthe, 229, 215);
				Actor_Set_Goal_Number(kActorHawkersBarkeep, 2);
				Actor_Change_Animation_Mode(kActorMcCoy, 23);
				Delay(1500);
				Actor_Says_With_Pause(kActorHawkersBarkeep, 50, 1.6f, 17);
				if (Query_Difficulty_Level() != kGameDifficultyEasy) {
					Global_Variable_Decrement(kVariableChinyen, 20);
				}
				Actor_Says(kActorMcCoy, 1245, 13);
			} else if (Actor_Clue_Query(kActorMcCoy, kClueHomelessManInterview2)
			&& !Game_Flag_Query(kFlagObtainedFlask)
			&& !Actor_Clue_Query(kActorMcCoy, kClueBigManLimping)
			&& _vm->_cutContent) {	
				Actor_Says(kActorMcCoy, 1230, 13);
				Actor_Says(kActorHawkersBarkeep, 20, 12);
				Actor_Says(kActorMcCoy, 1235, 13);
				Actor_Says(kActorHawkersBarkeep, 30, 15);
				Actor_Says(kActorMcCoy, 1240, 13);
				if (!Game_Flag_Query(kFlagHawkersBarkeepHappy)) {
					Actor_Says(kActorHawkersBarkeep, 40, 14);  //32-0040.AUD	Cost you extra.
					if (Global_Variable_Query(kVariableChinyen) >= 20
					|| Query_Difficulty_Level() == kGameDifficultyEasy) {
						Actor_Says(kActorMcCoy, 4940, 13); //00-4940.AUD	Okay, let's have it.
						Actor_Change_Animation_Mode(kActorHawkersBarkeep, 23);
						Actor_Change_Animation_Mode(kActorMcCoy, 23);
						Delay(800);
						Item_Pickup_Spin_Effect_From_Actor(kModelAnimationFlaskOfAbsinthe, kActorMcCoy, 0, 0);
						Actor_Clue_Acquire(kActorMcCoy, kClueFlaskOfAbsinthe, true, kActorHawkersBarkeep);
						Game_Flag_Set(kFlagObtainedFlask);
						Delay(800);
						Actor_Says_With_Pause(kActorHawkersBarkeep, 50, 1.6f, 17);
						if (Query_Difficulty_Level() != kGameDifficultyEasy) {
							Global_Variable_Decrement(kVariableChinyen, 20);
						}
						if (Player_Query_Agenda() != kPlayerAgendaSurly 
						&& Player_Query_Agenda() != kPlayerAgendaErratic) {
							Actor_Says(kActorMcCoy, 1245, 13); //00-1245.AUD	It's for a friend.
						}
					} else {
						Actor_Says(kActorMcCoy, 125, 13); //00-0125.AUD	I'm a little strapped for cash right now.
						Actor_Says(kActorMcCoy, 1260, 13); // 00-1260.AUD	How about you run a tab?
						Actor_Says(kActorHawkersBarkeep, 70, 15); //32-0070.AUD	This ain't a non-profit operation, buddy. No kale, no sale.
						Actor_Says(kActorMcCoy, 8445, 14); //00-8445.AUD	Cough it up!
						Delay(1000);
						Actor_Says(kActorHawkersBarkeep, 180, 14); //32-0180.AUD	But if you're gonna sit there until I cough it up, well, here it is.
						Actor_Change_Animation_Mode(kActorHawkersBarkeep, 23);
						Actor_Change_Animation_Mode(kActorMcCoy, 23);
						Delay(800);
						Item_Pickup_Spin_Effect_From_Actor(kModelAnimationFlaskOfAbsinthe, kActorMcCoy, 0, 0);
						Actor_Clue_Acquire(kActorMcCoy, kClueFlaskOfAbsinthe, true, kActorHawkersBarkeep);
						Game_Flag_Set(kFlagObtainedFlask);
						Delay(800);
					}
				} else {
					Delay(1000);
					Actor_Change_Animation_Mode(kActorHawkersBarkeep, 23);
					Actor_Change_Animation_Mode(kActorMcCoy, 23);
					Delay(800);
					Item_Pickup_Spin_Effect_From_Actor(kModelAnimationFlaskOfAbsinthe, kActorMcCoy, 0, 0);
					Actor_Clue_Acquire(kActorMcCoy, kClueFlaskOfAbsinthe, true, kActorHawkersBarkeep);
					Delay(800);
					Actor_Says(kActorMcCoy, 3935, 14); // 00-3935.AUD	Thanks.
				}
			} else {
				if (_vm->_cutContent) {
					if (Actor_Clue_Query(kActorMcCoy, kClueMaggieBracelet)
					&& !Game_Flag_Query(kFlagHC02HawkersBarkeepBraceletTalk)
					) {
						if (!Game_Flag_Query(kFlagHawkersBarkeepHappy)) {
							Actor_Says(kActorHawkersBarkeep, 80, 16);
							Actor_Says(kActorMcCoy, 1265, 13);
							Actor_Says(kActorHawkersBarkeep, 90, 13);
							Game_Flag_Set(kFlagHC02HawkersBarkeepBraceletTalk);
							if (Player_Query_Agenda() != kPlayerAgendaPolite) {
								Actor_Says(kActorMcCoy, 700, 14); //00-0700.AUD	I'm starting to understand.
								Delay (3000);
								Actor_Says(kActorHawkersBarkeep, 150, 13); //32-0150.AUD	Hey, you can always ask someone who cares what you think.
							} else {
								Actor_Says(kActorMcCoy, 5065, 18); //00-5065.AUD	Is that right?
							}
						} else {
							Actor_Says(kActorMcCoy, 1250, 13);
							Actor_Change_Animation_Mode(kActorHawkersBarkeep, 23);
							Actor_Change_Animation_Mode(kActorMcCoy, 23);
							Delay(1500);
							Actor_Change_Animation_Mode(kActorMcCoy, 75);
							Delay(1500);
							Game_Flag_Set(kFlagHC02HawkersBarkeepBraceletTalk);
						}
					} else if (!Game_Flag_Query(kFlagHC02HawkersBarkeepTalk2)
					) {
						if (Game_Flag_Query(kFlagHawkersBarkeepHappy)) {
							Actor_Says(kActorMcCoy, 8615, 13); //00-8615.AUD	Heard anything on the street?
							Actor_Says(kActorHawkersBarkeep, 120, 12); //32-0120.AUD	I just serve drinks, pal.
							Actor_Says(kActorHawkersBarkeep, 130, 16); //32-0130.AUD	I don't pay a whole lot attention to what goes on around here. Nor do I want to.
							Actor_Says(kActorMcCoy, 5065, 18); //00-5065.AUD	Is that right?
							Game_Flag_Set(kFlagHC02HawkersBarkeepTalk2);
						} else {
							Actor_Says(kActorMcCoy, 8615, 13); //00-8615.AUD	Heard anything on the street?
							Actor_Says(kActorHawkersBarkeep, 100, 12); //32-0100.AUD	Yeah, I heard something.
							Actor_Says(kActorMcCoy, 2635, 18); //00-2635.AUD	I’m all ears.
							Actor_Says(kActorHawkersBarkeep, 140, 13); //32-0140.AUD	I ain't a cheap date, pal. I don't put out. Especially not for chumps like you.
							Game_Flag_Set(kFlagHC02HawkersBarkeepTalk2);
						}
					}
				} else if ( Actor_Clue_Query(kActorMcCoy, kClueMaggieBracelet)
				&& !Game_Flag_Query(kFlagHC02HawkersBarkeepBraceletTalk)
				) {
					Actor_Says(kActorHawkersBarkeep, 80, 16);
					Actor_Says(kActorMcCoy, 1265, 13);
					Actor_Says(kActorHawkersBarkeep, 90, 13);
					Game_Flag_Set(kFlagHC02HawkersBarkeepBraceletTalk);
				}
				if (Global_Variable_Query(kVariableChinyen) >= 5
				 || Query_Difficulty_Level() == kGameDifficultyEasy
				) {
					if (Query_Difficulty_Level() != kGameDifficultyEasy) {
						Global_Variable_Decrement(kVariableChinyen, 5);
					}
					Global_Variable_Increment(kVariableMcCoyDrinks, 1);
					Actor_Says(kActorMcCoy, 1250, 13);
					if (_vm->_cutContent) {
						if (!Game_Flag_Query(kFlagHawkersBarkeepHappy)) {
							Actor_Says_With_Pause(kActorHawkersBarkeep, 60, 0.8f, 14);
							Actor_Says(kActorMcCoy, 1255, 13);
						}
					} else {
						Actor_Says_With_Pause(kActorHawkersBarkeep, 60, 0.8f, 14);
						Actor_Says(kActorMcCoy, 1255, 13);
					}
					Actor_Set_Goal_Number(kActorHawkersBarkeep, 1);
					Actor_Change_Animation_Mode(kActorMcCoy, 23);
					Delay(1500);
					Actor_Change_Animation_Mode(kActorMcCoy, 75);
					Delay(1500);
					if (_vm->_cutContent) {
						if (Player_Query_Agenda() == kPlayerAgendaPolite) {
							if (Global_Variable_Query(kVariableChapter) < 4) {
								if (Actor_Clue_Query(kActorMcCoy, kClueChinaBarSecurityDisc)
								&& Actor_Clue_Query(kActorMcCoy, kClueChinaBarSecurityPhoto)) {
									Actor_Says(kActorMcCoy, 5150, 18); //00-5150.AUD	One more thing.
									Actor_Change_Animation_Mode(kActorMcCoy, 23);
									Actor_Change_Animation_Mode(kActorHawkersBarkeep, 23);
									Delay(800);
									Item_Pickup_Spin_Effect_From_Actor(kModelAnimationVideoDisc, kActorHawkersBarkeep, 0, 0);		
									Delay(800);
									Actor_Clue_Lose(kActorMcCoy, kClueChinaBarSecurityDisc);
									Actor_Clue_Acquire(kActorHawkersBarkeep, kClueChinaBarSecurityDisc, true, -1);
									Actor_Says(kActorMcCoy, 8170, 13); //00-8170.AUD	There you go.	
								}
							}
						}
					}
				} else {
					if (_vm->_cutContent) {
						Actor_Says(kActorMcCoy, 125, 13); //00-0125.AUD	I'm a little strapped for cash right now.
					}
					Actor_Says_With_Pause(kActorMcCoy, 1260, 0.3f, 13);
					if (_vm->_cutContent) {
						if (!Game_Flag_Query(kFlagHawkersBarkeepHappy)) {
							Actor_Says(kActorHawkersBarkeep, 70, 14);
						} else {
							Delay(1000);
							Global_Variable_Increment(kVariableMcCoyDrinks, 1);
							Actor_Change_Animation_Mode(kActorHawkersBarkeep, 23);
							Actor_Change_Animation_Mode(kActorMcCoy, 23);
							Delay(1500);
							Actor_Change_Animation_Mode(kActorMcCoy, 75);
							Delay(1500);
							Actor_Says(kActorMcCoy, 3935, 14); // 00-3935.AUD	Thanks.
						}
						if (Player_Query_Agenda() == kPlayerAgendaPolite) {
							if (Actor_Clue_Query(kActorMcCoy, kClueChinaBarSecurityDisc)
							&& Actor_Clue_Query(kActorMcCoy, kClueChinaBarSecurityPhoto)) {
								Actor_Says(kActorMcCoy, 5150, 18); //00-5150.AUD	One more thing.
								Actor_Change_Animation_Mode(kActorMcCoy, 23);
								Actor_Change_Animation_Mode(kActorHawkersBarkeep, 23);
								Delay(800);
								Item_Pickup_Spin_Effect_From_Actor(kModelAnimationVideoDisc, kActorHawkersBarkeep, 0, 0);		
								Delay(800);
								Actor_Clue_Lose(kActorMcCoy, kClueChinaBarSecurityDisc);
								Actor_Clue_Acquire(kActorHawkersBarkeep, kClueChinaBarSecurityDisc, true, -1);
								Actor_Says(kActorMcCoy, 8170, 13); //00-8170.AUD	There you go.	
							}
						}
					} else {
						Actor_Says(kActorHawkersBarkeep, 70, 14);
					}
				}
			}
		}
		return true;
	}
	return false;
}

bool SceneScriptHC02::ClickedOnItem(int itemId, bool a2) {
	return false;
}

bool SceneScriptHC02::ClickedOnExit(int exitId) {
	if (exitId == 0) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, 7.0f, 0.14f, 79.0f, 0, true, false, false)) {
			Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
			Ambient_Sounds_Remove_All_Looping_Sounds(1u);
			Game_Flag_Set(kFlagHC02toHC01);
			Set_Enter(kSetHC01_HC02_HC03_HC04, kSceneHC01);
		}
		return true;
	}

	if (exitId == 1) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -76.0f, 0.14f, -339.0f, 0, true, false, false)) {
			Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
			Ambient_Sounds_Remove_All_Looping_Sounds(1u);
			Game_Flag_Set(kFlagHC02toHC04);
			Async_Actor_Walk_To_XYZ(kActorMcCoy, -88.0f, 0.14f, -463.0f, 0, false);
			Set_Enter(kSetHC01_HC02_HC03_HC04, kSceneHC04);
		}
		return true;
	}
	return false;
}

bool SceneScriptHC02::ClickedOn2DRegion(int region) {
	return false;
}

void SceneScriptHC02::SceneFrameAdvanced(int frame) {
	if (frame == 70) {
		Sound_Play(kSfxSWEEP3, 11, 50, -90, 50);
	}

	if (frame == 58) {
		Sound_Play(kSfxSWEEP3, 11, 50, -90, 50);
	}

	if (frame == 69
	 || frame == 77
	 || frame == 86
	 || frame == 95
	 || frame == 104
	 || frame == 113
	 || frame == 119
	) {
		Sound_Play(kSfxNEON6, Random_Query(6, 7), -20, 20, 50);
	}
}

void SceneScriptHC02::ActorChangedGoal(int actorId, int newGoal, int oldGoal, bool currentSet) {
}

void SceneScriptHC02::PlayerWalkedIn() {
	if (Game_Flag_Query(kFlagHC04toHC02)) {
		Loop_Actor_Walk_To_XYZ(kActorMcCoy, -76.0f, 0.14f, -339.0f, 0, false, false, false);
		Game_Flag_Reset(kFlagHC04toHC02);
	}
	if (_vm->_cutContent) {
		if (Actor_Clue_Query(kActorMcCoy, kClueHomelessManInterview2)
		&& !Game_Flag_Query(kFlagObtainedFlask)
		&& !Actor_Clue_Query(kActorMcCoy, kClueBigManLimping)) {
			Player_Loses_Control();
			Loop_Actor_Walk_To_XYZ(kActorMcCoy, -150.51f, 0.14f, 62.74f, 0, true, false, false);
			Player_Gains_Control();
			Actor_Face_Actor(kActorMcCoy, kActorHawkersBarkeep, true);
			Actor_Face_Actor(kActorHawkersBarkeep, kActorMcCoy, true);
			Actor_Says(kActorMcCoy, 1230, 13);
			Actor_Says(kActorHawkersBarkeep, 20, 12);
			Actor_Says(kActorMcCoy, 1235, 13);
			Actor_Says(kActorHawkersBarkeep, 30, 15);
			Actor_Says(kActorMcCoy, 1240, 13);
			if (!Game_Flag_Query(kFlagHawkersBarkeepHappy)) {
				Actor_Says(kActorHawkersBarkeep, 40, 14);  //32-0040.AUD	Cost you extra.
				if (Global_Variable_Query(kVariableChinyen) >= 20
				|| Query_Difficulty_Level() == kGameDifficultyEasy) {
					Actor_Says(kActorMcCoy, 4940, 13); //00-4940.AUD	Okay, let's have it.
					Actor_Change_Animation_Mode(kActorHawkersBarkeep, 23);
					Actor_Change_Animation_Mode(kActorMcCoy, 23);
					Delay(800);
					Item_Pickup_Spin_Effect_From_Actor(kModelAnimationFlaskOfAbsinthe, kActorMcCoy, 0, 0);
					Actor_Clue_Acquire(kActorMcCoy, kClueFlaskOfAbsinthe, true, kActorHawkersBarkeep);
					Game_Flag_Set(kFlagObtainedFlask);
					Delay(800);
					Actor_Says_With_Pause(kActorHawkersBarkeep, 50, 1.6f, 17);
					if (Query_Difficulty_Level() != kGameDifficultyEasy) {
						Global_Variable_Decrement(kVariableChinyen, 20);
					}
					if (Player_Query_Agenda() != kPlayerAgendaSurly 
					&& Player_Query_Agenda() != kPlayerAgendaErratic) {
						Actor_Says(kActorMcCoy, 1245, 13); //00-1245.AUD	It's for a friend.
					}
				} else {
					Actor_Says(kActorMcCoy, 125, 13); //00-0125.AUD	I'm a little strapped for cash right now.
					Actor_Says(kActorMcCoy, 1260, 13); // 00-1260.AUD	How about you run a tab?
					Actor_Says(kActorHawkersBarkeep, 70, 15); //32-0070.AUD	This ain't a non-profit operation, buddy. No kale, no sale.
					Actor_Says(kActorMcCoy, 8445, 14); //00-8445.AUD	Cough it up!
					Delay(1000);
					Actor_Says(kActorHawkersBarkeep, 180, 14); //32-0180.AUD	But if you're gonna sit there until I cough it up, well, here it is.
					Actor_Change_Animation_Mode(kActorHawkersBarkeep, 23);
					Actor_Change_Animation_Mode(kActorMcCoy, 23);
					Delay(800);
					Item_Pickup_Spin_Effect_From_Actor(kModelAnimationFlaskOfAbsinthe, kActorMcCoy, 0, 0);
					Actor_Clue_Acquire(kActorMcCoy, kClueFlaskOfAbsinthe, true, kActorHawkersBarkeep);
					Game_Flag_Set(kFlagObtainedFlask);
					Delay(800);
				}
			}
		}
	}
}

void SceneScriptHC02::PlayerWalkedOut() {
}

void SceneScriptHC02::DialogueQueueFlushed(int a1) {
}

} // End of namespace BladeRunner
