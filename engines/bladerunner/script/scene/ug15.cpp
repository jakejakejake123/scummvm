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

enum UG15Loops {
	kUG15LoopMainLoop             = 0,
	kUG15LoopBridgeBreaks         = 2,
	kUG15LoopMainLoopBridgeBroken = 3
};

void SceneScriptUG15::InitializeScene() {
	if (Game_Flag_Query(kFlagUG17toUG15)) {
		Setup_Scene_Information( -25.0f, 26.31f, -434.0f, 520);
	} else if (Game_Flag_Query(kFlagUG16toUG15a)) {
		Setup_Scene_Information( -17.0f, 26.31f, -346.0f, 711);
	} else if (Game_Flag_Query(kFlagUG16toUG15b)) {
		Setup_Scene_Information( -18.0f, 48.07f,   62.0f, 650);
	} else {
		Setup_Scene_Information(-238.0f, 48.07f,  222.0f, 180);
		if (Game_Flag_Query(kFlagUG15RatShot)
		 && (Random_Query(1, 10) == 10)
		 && !(_vm->_cutContent && Query_Difficulty_Level() == kGameDifficultyEasy)
		) {
			Game_Flag_Reset(kFlagUG15RatShot);
		}
	}

	if (Game_Flag_Query(kFlagUG15BridgeBroken)) {
		Scene_Loop_Set_Default(kUG15LoopMainLoopBridgeBroken);
	}

	if (Game_Flag_Query(kFlagUG17toUG15)
	 || Game_Flag_Query(kFlagUG16toUG15a)
	) {
		Scene_Exit_Add_2D_Exit(0, 260,   0, 307, 298, 0);
		Scene_Exit_Add_2D_Exit(1, 301, 147, 337, 304, 1);
		Game_Flag_Reset(kFlagUG17toUG15);
		Game_Flag_Reset(kFlagUG16toUG15a);
	} else {
		Scene_Exit_Add_2D_Exit(2, 406, 128, 480, 316, 1);
		Scene_Exit_Add_2D_Exit(3,   0,   0,  30, 479, 3);
	}

	Ambient_Sounds_Add_Looping_Sound(kSfxCTRUNOFF, 71, 0, 1);
	Ambient_Sounds_Add_Looping_Sound(kSfxBOILPOT2, 45, 0, 1);
	Ambient_Sounds_Add_Looping_Sound(kSfxUGBED1,   76, 0, 1);
	Ambient_Sounds_Add_Sound(kSfxBBDRIP1,  2,  20, 25, 33, -100, 100, -100,  100, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBBDRIP2,  2,  20, 25, 33, -100, 100, -100,  100, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBBDRIP3,  2,  20, 25, 33, -100, 100, -100,  100, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBBDRIP4,  2,  20, 25, 33, -100, 100, -100,  100, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBBDRIP5,  2,  20, 25, 33, -100, 100, -100,  100, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxYELL1M2,  2, 120, 11, 12, -100, 100, -100,  100, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxYELL1M3,  2, 120, 11, 12, -100, 100, -100,  100, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxGRUNT1M1, 2, 120, 11, 12, -100, 100, -100,  100, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxGRUNT2M2, 2, 120, 11, 12, -100, 100, -100,  100, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxGRUNT2M3, 2, 120, 11, 12, -100, 100, -100,  100, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBBGRN1,   5,  50, 47, 57, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBBGRN2,   5,  50, 47, 57, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBBGRN3,   5,  50, 47, 57, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSTEAM1,   5,  50, 47, 57, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSTEAM3,   5,  50, 17, 37, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSTEAM6A,  5,  50, 17, 37, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBBMOVE1,  5,  50, 27, 37, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBBMOVE2,  5,  50, 27, 37, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBBMOVE3,  5,  50, 27, 37, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxZUBWLK1,  5,  50, 27, 37, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxZUBWLK2,  5,  50, 27, 37, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxZUBWLK3,  5,  50, 27, 37, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxZUBWLK4,  5,  50, 27, 37, -100, 100, -101, -101, 0, 0);
}

void SceneScriptUG15::SceneLoaded() {
	Unobstacle_Object("CATWALK_01_RAIL02", true);
	Unobstacle_Object("LOFT01", true);
	Obstacle_Object("NUT1", true);
	Clickable_Object("NUT1");
#if BLADERUNNER_ORIGINAL_BUGS
#else
	Unclickable_Object("NUT1");
#endif // BLADERUNNER_ORIGINAL_BUGS
}

bool SceneScriptUG15::MouseClick(int x, int y) {
	return false;
}

bool SceneScriptUG15::ClickedOn3DObject(const char *objectName, bool a2) {
	return false;
}

bool SceneScriptUG15::ClickedOnActor(int actorId) {
	return false;
}

bool SceneScriptUG15::ClickedOnItem(int itemId, bool a2) {
	return false;
}

bool SceneScriptUG15::ClickedOnExit(int exitId) {
	if (exitId == 0) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -25.0f, 26.31f, -434.0f, 0, true, false, false)) {
			Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
			Ambient_Sounds_Remove_All_Looping_Sounds(1u);
			Game_Flag_Set(kFlagUG15toUG17);
			Set_Enter(kSetUG17, kSceneUG17);
		}
		return true;
	}

	if (exitId == 1) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -17.0f, 26.31f, -346.0f, 0, true, false, false)) {
			Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
			Ambient_Sounds_Remove_All_Looping_Sounds(1u);
			Game_Flag_Set(kFlagUG15toUG16a);
			Set_Enter(kSetUG16, kSceneUG16);
		}
		return true;
	}

	if (exitId == 2) {
		int ratGoal = Actor_Query_Goal_Number(kActorFreeSlotA);
		if (ratGoal >= 300 // kGoalFreeSlotAUG15Wait
		 && ratGoal <= 303 // kGoalFreeSlotAUG15RunBack
		) {
			Loop_Actor_Walk_To_XYZ(kActorMcCoy, -137.61f, 48.07f, 147.12f, 0, true, false, false);
			if (_vm->_cutContent) {
				Player_Set_Combat_Mode(true);
				Sound_Play(kSfxRATTY1, 50, 0, 0, 50);
			}
		} else if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, 18.0f, 52.28f, 46.0f, 0, true, false, false)) {
			Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
			Ambient_Sounds_Remove_All_Looping_Sounds(1u);
			Set_Enter(kSetUG16, kSceneUG16);
		}
		return true;
	}

	if (exitId == 3) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -238.0f, 52.46f, 222.0f, 0, true, false, false)) {
			Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
			Ambient_Sounds_Remove_All_Looping_Sounds(1u);
			Game_Flag_Set(kFlagUG15toUG13);
			Set_Enter(kSetUG13, kSceneUG13);
		}
		return true;
	}
	return false;
}

bool SceneScriptUG15::ClickedOn2DRegion(int region) {
	return false;
}

void SceneScriptUG15::SceneFrameAdvanced(int frame) {
	if (Actor_Query_Goal_Number(kActorFreeSlotA) == kGoalFreeSlotAUG15Wait) {
		float x, y, z;
		Actor_Query_XYZ(kActorMcCoy, &x, &y, &z);
		if (-160.0f <= x
		 &&  220.0f > z
		) {
			Actor_Set_Goal_Number(kActorFreeSlotA, kGoalFreeSlotAUG15WalkOut);
		}
	}

	if (frame == 61) {
		Ambient_Sounds_Play_Sound(kSfxPLANKDWN, 80, 0, 0, 99);
	}
	if (!_vm->_cutContent) {
		if ( Game_Flag_Query(kFlagUG15BridgeWillBreak)
		&& !Game_Flag_Query(kFlagUG15BridgeBroken)
		) {
			float x, y, z;
			Actor_Query_XYZ(kActorMcCoy, &x, &y, &z);
			if ( -180.0f <= x
			&&   220.0f > z
			&& !Game_Flag_Query(kFlagUG15BridgeBreaks)
			) {
				Game_Flag_Set(kFlagUG15BridgeBreaks);
				Game_Flag_Set(kFlagUG15BridgeBroken);
				Scene_Loop_Set_Default(kUG15LoopMainLoopBridgeBroken);
				Scene_Loop_Start_Special(kSceneLoopModeOnce, kUG15LoopBridgeBreaks, true);
				Actor_Set_Goal_Number(kActorMcCoy, kGoalMcCoyUG15Fall);
				Actor_Query_XYZ(kActorFreeSlotA, &x, &y, &z);

				if (-200.0f < x
				&&  -62.0f > x
				) {
					Actor_Set_Goal_Number(kActorFreeSlotA, kGoalFreeSlotAUG15Fall);
				}
			}
		}
	}
	//	return false;
}

void SceneScriptUG15::ActorChangedGoal(int actorId, int newGoal, int oldGoal, bool currentSet) {
}

void SceneScriptUG15::PlayerWalkedIn() {
	if (_vm->_cutContent) {
		Music_Stop(1u);
		if (Actor_Clue_Query(kActorMcCoy, kClueFolder)) {
			if (Game_Flag_Query(kFlagHanoiIsReplicant)
			&& !Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
				Loop_Actor_Walk_To_XYZ(kActorMcCoy, -62.0f, 48.07f, 102.0f, 0, false, false, false);
				Game_Flag_Reset(kFlagUG16toUG15b);
				Player_Loses_Control();
				Loop_Actor_Walk_To_XYZ(kActorMcCoy, -141.79f, 48.67f, 155.42f, 0, true, false, true);
				Actor_Put_In_Set(kActorHanoi, kSetUG15);
				Actor_Set_At_XYZ(kActorHanoi, -38.07, 48.53, 70.34, 0);
				Actor_Change_Animation_Mode(kActorHanoi, 1);
				Loop_Actor_Walk_To_XYZ(kActorHanoi, -62.0f, 48.07f, 102.0f, 0, false, false, false);
				Actor_Face_Actor(kActorMcCoy, kActorHanoi, true);
				Actor_Face_Actor(kActorHanoi, kActorMcCoy, true);
				Actor_Change_Animation_Mode(kActorHanoi, 4);
				Sound_Play(kSfxSHOTCOK1, 77, 0, 0, 20);
				Delay(500);
				if (!Game_Flag_Query(kFlagHanoiDead)) {
					Actor_Says(kActorHanoi, 160, 4); //25-0160.AUD	Here, what’s this then?
				}
				Actor_Change_Animation_Mode(kActorHanoi, 4);
				if (!Game_Flag_Query(kFlagHanoiDead)) {
					Actor_Says(kActorMcCoy, 525, 13); //00-0525.AUD	I've seen you before...
					Actor_Says(kActorMcCoy, 7260, 14); //00-7260.AUD	Didn't I see an incept tape at the—
				} else {
					Actor_Says(kActorMcCoy, 5690, -1); //00-5690.AUD	Huh?
				}	
				Player_Set_Combat_Mode(true);
				Actor_Change_Animation_Mode(kActorHanoi, 4);
				Delay(1000);
				if (!Game_Flag_Query(kFlagHanoiDead)) {
					Music_Play(kMusicBeating1, 71, 0, 0, -1, kMusicLoopPlayOnce, 2);
				} else {
					Music_Play(kMusicMoraji, 71, 0, 0, -1, kMusicLoopPlayOnce, 2);
				}
				Actor_Change_Animation_Mode(kActorMcCoy, 21);
				Actor_Change_Animation_Mode(kActorHanoi, 6);
				Ambient_Sounds_Play_Sound(kSfxSHOTGUN1, 97, 0, 0, 20);
				Delay(1000);
				Sound_Play(kSfxGUNH1A, 100, 0, 0, 50);
				Actor_Change_Animation_Mode(kActorMcCoy, 6);
				Actor_Change_Animation_Mode(kActorHanoi, 21);
				Delay(1000);
				Actor_Change_Animation_Mode(kActorHanoi, 6);
				Ambient_Sounds_Play_Sound(kSfxSHOTGUN1, 97, 0, 0, 20);
				Loop_Actor_Walk_To_XYZ(kActorMcCoy, -186.41f, 48.54f, 179.28f, 0, false, true, false);
				Actor_Face_Actor(kActorMcCoy, kActorHanoi, true);
				Sound_Play(kSfxGUNH1A, 100, 0, 0, 50);
				Actor_Change_Animation_Mode(kActorMcCoy, 6);
				Loop_Actor_Walk_To_Actor(kActorHanoi, kActorMcCoy, 24, true, false);
				Actor_Face_Actor(kActorMcCoy, kActorHanoi, true);
				Actor_Face_Actor(kActorHanoi, kActorMcCoy, true);
				Actor_Change_Animation_Mode(kActorHanoi, 71);
				Delay(500);
				Actor_Change_Animation_Mode(kActorMcCoy, 21);
				Ambient_Sounds_Play_Sound(kSfxKICK2, 90, 99, 0, 0);
				Delay(1000);
				Loop_Actor_Walk_To_XYZ(kActorMcCoy, -214.64f, 38.21f, 245.40f, 0, false, true, false);
				Actor_Face_Actor(kActorMcCoy, kActorHanoi, true);
				Actor_Face_Actor(kActorHanoi, kActorMcCoy, true);
				Actor_Change_Animation_Mode(kActorMcCoy, 21);
				Actor_Change_Animation_Mode(kActorHanoi, 6);
				Ambient_Sounds_Play_Sound(kSfxSHOTGUN1, 97, 0, 0, 20);
				Delay(1000);
				Sound_Play(kSfxGUNH1A, 100, 0, 0, 50);
				Actor_Change_Animation_Mode(kActorMcCoy, 6);
				Actor_Change_Animation_Mode(kActorHanoi, 21);
				Delay(1000);
				Actor_Change_Animation_Mode(kActorHanoi, 6);
				Delay(500);
				Game_Flag_Set(kFlagUG15BridgeBreaks);
				Game_Flag_Set(kFlagUG15BridgeBroken);
				Scene_Loop_Set_Default(kUG15LoopMainLoopBridgeBroken);
				Scene_Loop_Start_Special(kSceneLoopModeOnce, kUG15LoopBridgeBreaks, true);
				Actor_Put_In_Set(kActorHanoi, kSetUG13);
				Delay(3000);
				Player_Set_Combat_Mode(false);
				Delay(2000);
				Loop_Actor_Walk_To_XYZ(kActorMcCoy, -238.0f, 52.46f, 222.0f, 0, false, true, false);
				Player_Gains_Control();
				if (!Game_Flag_Query(kFlagHanoiDead)) {
					Game_Flag_Set(kFlagHanoiDead);
					Actor_Modify_Friendliness_To_Other(kActorGaff, kActorMcCoy, 2);
					Actor_Modify_Friendliness_To_Other(kActorSteele, kActorMcCoy, 2);
					Actor_Modify_Friendliness_To_Other(kActorGuzza, kActorMcCoy, 2);
					Actor_Modify_Friendliness_To_Other(kActorClovis, kActorMcCoy, -2);
					if (Query_Difficulty_Level() != kGameDifficultyEasy) {
						Global_Variable_Increment (kVariableChinyen, 200);
					}
				}
				Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
				Ambient_Sounds_Remove_All_Looping_Sounds(1u);
				Game_Flag_Set(kFlagUG15toUG13);
				Set_Enter(kSetUG13, kSceneUG13);
			} else if (Random_Query(1, 2) == 1) {
				Loop_Actor_Walk_To_XYZ(kActorMcCoy, -62.0f, 48.07f, 102.0f, 0, false, false, false);
				Game_Flag_Reset(kFlagUG16toUG15b);
				Actor_Face_Heading(kActorMcCoy, 400, false);
				Sound_Play(kSfxYELL1M2, 100, 0, 100, 50);
				Delay(4000);
				Actor_Says(kActorMcCoy, 6875, -1); //00-6875.AUD	I gotta go.
				Player_Loses_Control();
				Loop_Actor_Walk_To_XYZ(kActorMcCoy, -141.79f, 48.67f, 155.42f, 0, true, true, true);
				Music_Play(kMusicBeating1, 71, 0, 0, -1, kMusicLoopPlayOnce, 2);
				Actor_Put_In_Set(kActorMutant1, kSetUG15);
				Actor_Set_At_XYZ(kActorMutant1, -38.07, 48.53, 70.34, 0);
				Actor_Face_Actor(kActorMcCoy, kActorMutant1, true);
				Actor_Face_Actor(kActorMutant1, kActorMcCoy, true);
				Loop_Actor_Walk_To_XYZ(kActorMutant1, -62.0f, 48.07f, 102.0f, 0, false, false, false);
				Actor_Says(kActorMcCoy, 2980, 12);
				Delay(1000);
				Player_Set_Combat_Mode(true);
				Delay(1000);
				Sound_Play(kSfxGUNH1A, 100, 0, 0, 50);
				Actor_Change_Animation_Mode(kActorMcCoy, 6);
				Actor_Change_Animation_Mode(kActorMutant1, 21);
				Delay(1000);
				Loop_Actor_Walk_To_XYZ(kActorMcCoy, -186.41f, 48.54f, 179.28f, 0, true, true, true);
				Actor_Face_Actor(kActorMcCoy, kActorMutant1, true);
				Actor_Face_Actor(kActorMutant1, kActorMcCoy, true);
				Sound_Play(kSfxGUNH1A, 100, 0, 0, 50);
				Actor_Change_Animation_Mode(kActorMcCoy, 6);
				Loop_Actor_Walk_To_Actor(kActorMutant1, kActorMcCoy, 24, true, false);
				Actor_Face_Actor(kActorMcCoy, kActorMutant1, true);
				Actor_Face_Actor(kActorMutant1, kActorMcCoy, true);
				Actor_Change_Animation_Mode(kActorMutant1, 6);
				Delay(500);
				Actor_Change_Animation_Mode(kActorMcCoy, 21);
				Delay(1000);
				Loop_Actor_Walk_To_XYZ(kActorMcCoy, -214.64f, 38.21f, 245.40f, 0, true, true, true);
				Actor_Face_Actor(kActorMcCoy, kActorMutant1, true);
				Actor_Face_Actor(kActorMutant1, kActorMcCoy, true);
				Sound_Play(kSfxGUNH1A, 100, 0, 0, 50);
				Actor_Change_Animation_Mode(kActorMcCoy, 6);
				Actor_Change_Animation_Mode(kActorMutant1, 21);
				Delay(1000);
				Game_Flag_Set(kFlagUG15BridgeBreaks);
				Game_Flag_Set(kFlagUG15BridgeBroken);
				Scene_Loop_Set_Default(kUG15LoopMainLoopBridgeBroken);
				Scene_Loop_Start_Special(kSceneLoopModeOnce, kUG15LoopBridgeBreaks, true);
				Actor_Put_In_Set(kActorMutant1, kSetUG13);
				Sound_Play(kSfxYELL1M1, 100, 0, 0, 50);
				Delay(3000);
				Player_Set_Combat_Mode(false);
				Delay(5000);
				Loop_Actor_Walk_To_XYZ(kActorMcCoy, -238.0f, 52.46f, 222.0f, 0, false, true, false);
				Player_Gains_Control();
				Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
				Ambient_Sounds_Remove_All_Looping_Sounds(1u);
				Game_Flag_Set(kFlagUG15toUG13);
				Set_Enter(kSetUG13, kSceneUG13);
			} else {
				Loop_Actor_Walk_To_XYZ(kActorMcCoy, -62.0f, 48.07f, 102.0f, 0, false, false, false);
				Game_Flag_Reset(kFlagUG16toUG15b);
				Actor_Face_Heading(kActorMcCoy, 400, false);
				Sound_Play(kSfxYELL1M2, 100, 0, 100, 50);
				Delay(4000);
				Actor_Says(kActorMcCoy, 6875, -1); //00-6875.AUD	I gotta go.
				Player_Loses_Control();
				Loop_Actor_Walk_To_XYZ(kActorMcCoy, -141.79f, 48.67f, 155.42f, 0, true, true, true);
				Music_Play(kMusicBeating1, 71, 0, 0, -1, kMusicLoopPlayOnce, 2);
				Actor_Put_In_Set(kActorMutant2, kSetUG15);
				Actor_Set_At_XYZ(kActorMutant2, -38.07, 48.53, 70.34, 0);
				Actor_Face_Actor(kActorMcCoy, kActorMutant2, true);
				Actor_Face_Actor(kActorMutant2, kActorMcCoy, true);
				Loop_Actor_Walk_To_XYZ(kActorMutant2, -62.0f, 48.07f, 102.0f, 0, false, false, false);
				Actor_Says(kActorMcCoy, 2980, 12);
				Delay(1000);
				Player_Set_Combat_Mode(true);
				Delay(1000);
				Sound_Play(kSfxGUNH1A, 100, 0, 0, 50);
				Actor_Change_Animation_Mode(kActorMcCoy, 6);
				Actor_Change_Animation_Mode(kActorMutant2, 21);
				Delay(1000);
				Loop_Actor_Walk_To_XYZ(kActorMcCoy, -186.41f, 48.54f, 179.28f, 0, true, true, true);
				Actor_Face_Actor(kActorMcCoy, kActorMutant2, true);
				Actor_Face_Actor(kActorMutant2, kActorMcCoy, true);
				Sound_Play(kSfxGUNH1A, 100, 0, 0, 50);
				Actor_Change_Animation_Mode(kActorMcCoy, 6);
				Loop_Actor_Walk_To_Actor(kActorMutant2, kActorMcCoy, 24, true, false);
				Actor_Face_Actor(kActorMcCoy, kActorMutant2, true);
				Actor_Face_Actor(kActorMutant2, kActorMcCoy, true);
				Actor_Change_Animation_Mode(kActorMutant2, 6);
				Delay(500);
				Actor_Change_Animation_Mode(kActorMcCoy, 21);
				Delay(1000);
				Sound_Play(kSfxGUNH1A, 100, 0, 0, 50);
				Actor_Change_Animation_Mode(kActorMcCoy, 6);
				Actor_Change_Animation_Mode(kActorMutant2, 21);
				Delay(1000);
				Loop_Actor_Walk_To_XYZ(kActorMcCoy, -214.64f, 38.21f, 245.40f, 0, true, true, true);
				Actor_Face_Actor(kActorMcCoy, kActorMutant2, true);
				Actor_Face_Actor(kActorMutant2, kActorMcCoy, true);
				Sound_Play(kSfxGUNH1A, 100, 0, 0, 50);
				Actor_Change_Animation_Mode(kActorMcCoy, 6);
				Actor_Change_Animation_Mode(kActorMutant2, 21);
				Delay(1000);
				Game_Flag_Set(kFlagUG15BridgeBreaks);
				Game_Flag_Set(kFlagUG15BridgeBroken);
				Scene_Loop_Set_Default(kUG15LoopMainLoopBridgeBroken);
				Scene_Loop_Start_Special(kSceneLoopModeOnce, kUG15LoopBridgeBreaks, true);
				Actor_Put_In_Set(kActorMutant2, kSetUG13);
				Sound_Play(kSfxYELL1M1, 100, 0, 0, 50);
				Delay(3000);
				Player_Set_Combat_Mode(false);
				Delay(5000);
				Loop_Actor_Walk_To_XYZ(kActorMcCoy, -238.0f, 52.46f, 222.0f, 0, false, true, false);
				Player_Gains_Control();
				Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
				Ambient_Sounds_Remove_All_Looping_Sounds(1u);
				Game_Flag_Set(kFlagUG15toUG13);
				Set_Enter(kSetUG13, kSceneUG13);
			}
		}
	}
	if (Game_Flag_Query(kFlagUG16toUG15b)) {
		Loop_Actor_Walk_To_XYZ(kActorMcCoy, -62.0f, 48.07f, 102.0f, 0, false, false, false);
		Game_Flag_Reset(kFlagUG16toUG15b);
	} else if (Game_Flag_Query(kFlagUG13toUG15)) {
		Game_Flag_Reset(kFlagUG13toUG15);
		if (!Game_Flag_Query(kFlagUG15RatShot)) {
			Actor_Set_Goal_Number(kActorFreeSlotA, kGoalFreeSlotAUG15Prepare);
		}
	}
}

void SceneScriptUG15::PlayerWalkedOut() {
}

void SceneScriptUG15::DialogueQueueFlushed(int a1) {
}

} // End of namespace BladeRunner
