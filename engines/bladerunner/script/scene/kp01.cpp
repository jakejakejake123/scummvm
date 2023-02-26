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

void SceneScriptKP01::InitializeScene() {
	if (Game_Flag_Query(kFlagKP04toKP01)) {
		Setup_Scene_Information(-125.0f, -12.2f,  -61.0f, 400);
	} else if (Game_Flag_Query(kFlagKP03toKP01)) {
		Setup_Scene_Information(-284.0f, -12.2f, -789.0f, 445);
	} else {
		Setup_Scene_Information( 239.0f, -12.2f, -146.0f, 820);
		if (!Game_Flag_Query(kFlagKP01Entered)
		 && !Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)
		) {
			Game_Flag_Set(kFlagKP01Entered);
			Actor_Set_Goal_Number(kActorSteele, kGoalSteeleKP01Wait);
		}
	}

	Scene_Exit_Add_2D_Exit(0,   0, 0,  30, 479, 3);
	Scene_Exit_Add_2D_Exit(1, 150, 0, 200, 276, 0);
	Scene_Exit_Add_2D_Exit(2, 589, 0, 639, 479, 1);

	Ambient_Sounds_Add_Looping_Sound(kSfxKPAMB1,   34, 1, 1);
	Ambient_Sounds_Add_Looping_Sound(kSfxSKINBED1, 27, 1, 1);
	Ambient_Sounds_Add_Looping_Sound(kSfxRUMLOOP1, 90, 1, 1);
	Ambient_Sounds_Add_Sound(kSfxSCARY1,  2, 100, 25,  33, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSCARY2,  2, 100, 25,  33, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSCARY3,  2, 100, 25,  33, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxTHNDER2, 5, 180, 50, 100, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxTHNDER4, 5, 180, 50, 100, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSCARY4,  2, 100, 25,  33, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSCARY5,  2, 100, 25,  33, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSCARY6,  2, 100, 25,  33, -100, 100, -101, -101, 0, 0);
}

void SceneScriptKP01::SceneLoaded() {
	Unobstacle_Object("TRAINCAR-1", true);
	Unobstacle_Object("FORE-JUNK-02", true);
	Obstacle_Object("OBSTACLE1", true);
	Obstacle_Object("TUBE1", true);
	Unclickable_Object("OBSTACLE1");
}

bool SceneScriptKP01::MouseClick(int x, int y) {
	return false;
}

bool SceneScriptKP01::ClickedOn3DObject(const char *objectName, bool a2) {
	return false;
}

bool SceneScriptKP01::ClickedOnActor(int actorId) {
	return false;
}

bool SceneScriptKP01::ClickedOnItem(int itemId, bool a2) {
	return false;
}

bool SceneScriptKP01::ClickedOnExit(int exitId) {
	if (exitId == 0) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -125.0f, -12.2f, -61.0f, 0, true, false, false)) {
			Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
			Ambient_Sounds_Remove_All_Looping_Sounds(1u);
			Set_Enter(kSetKP04, kSceneKP04);
		}
		return true;
	}

	if (exitId == 1) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -284.0f, -12.2f, -789.0f, 0, true, false, false)) {
			Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
			Ambient_Sounds_Remove_All_Looping_Sounds(1u);
			Game_Flag_Set(kFlagKP01toKP03);
			Set_Enter(kSetKP03, kSceneKP03);
		}
		return true;
	}

	if (exitId == 2) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, 239.0f, 12.2f, -146.0f, 0, true, false, false)) {
			Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
			Ambient_Sounds_Remove_All_Looping_Sounds(1u);
			Game_Flag_Set(kFlagKP01toKP02);
			Set_Enter(kSetKP02, kSceneKP02);
		}
		return true;
	}
	return false;
}


bool SceneScriptKP01::ClickedOn2DRegion(int region) {
	return false;
}

void SceneScriptKP01::SceneFrameAdvanced(int frame) {
}

void SceneScriptKP01::ActorChangedGoal(int actorId, int newGoal, int oldGoal, bool currentSet) {
	if (actorId == kActorSteele) {
		if (newGoal == kGoalSteeleKP01Leave) {
			if (!_vm->_cutContent) {
				if (Game_Flag_Query(kFlagDirectorsCut)) {
					Delay(500);
					Actor_Change_Animation_Mode(kActorMcCoy, 75);
					Delay(4500);
					Actor_Face_Current_Camera(kActorMcCoy, true);
					Actor_Says(kActorMcCoy, 510, kAnimationModeTalk);
				} else {
					Delay(3000);
				}
			} else {
				Delay(3000);
			}
			Async_Actor_Walk_To_XYZ(kActorMcCoy, 76.56f, -12.2f, -405.48f, 0, false);
			//return true;
		} else if (newGoal == kGoalSteeleKP01Left) {
			Player_Gains_Control();
			Actor_Force_Stop_Walking(kActorMcCoy);
			Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
			Ambient_Sounds_Remove_All_Looping_Sounds(1u);
			Game_Flag_Set(kFlagKP01toKP03);
			Set_Enter(kSetKP03, kSceneKP03);
			//return true;
		}
	}
	//return false;
}

void SceneScriptKP01::PlayerWalkedIn() {
	if (_vm->_cutContent) {
		Player_Set_Combat_Mode(false);
		if (Game_Flag_Query(kFlagMcCoyIsInnocent) 
		&& Global_Variable_Query(kVariableAffectionTowards) != kAffectionTowardsDektora
		&& Global_Variable_Query(kVariableAffectionTowards) != kAffectionTowardsLucy 
		&& !Game_Flag_Query(kFlagMcCoyRetiredHuman)) {
			Actor_Set_At_XYZ(kActorMcCoy, 211.0f, -12.2f, -146.0f, 0);
		}
	} else if (Game_Flag_Query(kFlagKP04toKP01)) {
		Loop_Actor_Walk_To_XYZ(kActorMcCoy, -93.0f, -12.2f, -61.0f, 0, false, false, false);
		Game_Flag_Reset(kFlagKP04toKP01);
		return;
	}
	if (Game_Flag_Query(kFlagKP03toKP01)) {
		Loop_Actor_Walk_To_XYZ(kActorMcCoy, -240.0f, -12.2f, -789.0f, 0, false, false, false);
		Game_Flag_Reset(kFlagKP03toKP01);
		return;
	}
	// Altered the conditions for Crystal meeting McCoy in the Kipple.
	if (_vm->_cutContent) {
		Player_Set_Combat_Mode(false);
		if (Game_Flag_Query(kFlagMcCoyIsInnocent) 
		&& Global_Variable_Query(kVariableAffectionTowards) != kAffectionTowardsDektora
		&& Global_Variable_Query(kVariableAffectionTowards) != kAffectionTowardsLucy 
		&& !Game_Flag_Query(kFlagMcCoyRetiredHuman)) {
			Actor_Put_In_Set(kActorSteele, kSetKP01);
			Actor_Set_At_XYZ(kActorSteele, 20.0f, -12.2f, -97.0f, 907);
			Actor_Change_Animation_Mode(kActorSteele, 43);
			Player_Loses_Control();
			Actor_Set_Goal_Number(kActorSteele, kGoalSteeleKP01TalkToMcCoy);
		}
	} else if (!Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)
	 && !Game_Flag_Query(kFlagMcCoyAttackedReplicants)
	 &&  Actor_Query_Goal_Number(kActorSteele) == kGoalSteeleKP01Wait
	 &&  Actor_Query_Goal_Number(kActorSteele) != kGoalSteeleGone
	) {
		Player_Loses_Control();
		Actor_Set_Goal_Number(kActorSteele, kGoalSteeleKP01TalkToMcCoy);
	}
	if (_vm->_cutContent) {
		Player_Set_Combat_Mode(false);
		if (Game_Flag_Query(kFlagHanoiIsReplicant)
		&& !Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)
		&& !Actor_Query_Is_In_Current_Set(kActorSteele)
		&& !Game_Flag_Query(kFlagKP03BombExploded)) {
			Loop_Actor_Walk_To_XYZ(kActorMcCoy, 70.56f, -11.81f, -176.38f, 0, false, false, false);
			Actor_Face_Heading(kActorMcCoy, 300, false);
			Actor_Put_In_Set(kActorHanoi, kSetKP01);
			Actor_Set_At_XYZ(kActorHanoi, -125.0f, -12.2f, -61.0f, 0);
			Actor_Change_Animation_Mode(kActorHanoi, 1);
			Loop_Actor_Walk_To_Actor(kActorHanoi, kActorMcCoy, 24, true, false);
			Actor_Change_Animation_Mode(kActorHanoi, 4);
			Actor_Face_Actor(kActorHanoi, kActorMcCoy, true);
			Actor_Face_Actor(kActorMcCoy, kActorHanoi, true);
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
			Delay(500);
			Actor_Change_Animation_Mode(kActorHanoi, 71);
			Delay(500);
			Actor_Change_Animation_Mode(kActorMcCoy, 21);
			Ambient_Sounds_Play_Sound(kSfxKICK2, 90, 99, 0, 0);
			Music_Play(kMusicBeating1, 71, 0, 0, -1, kMusicLoopPlayOnce, 2);			
			Delay(1000);
			Actor_Change_Animation_Mode(kActorHanoi, 6);
			Ambient_Sounds_Play_Sound(kSfxSHOTGUN1, 97, 0, 0, 20);
			Loop_Actor_Walk_To_XYZ(kActorMcCoy, 15.06f, -11.75f, -274.50f, 0, false, true, false);
			Actor_Face_Actor(kActorHanoi, kActorMcCoy, true);
			Actor_Face_Actor(kActorMcCoy, kActorHanoi, true);
			Sound_Play(kSfxGUNH1A, 100, 0, 0, 50);
			Actor_Change_Animation_Mode(kActorMcCoy, 6);
			Actor_Change_Animation_Mode(kActorHanoi, 21);
			Delay(1000);
			Loop_Actor_Walk_To_XYZ(kActorMcCoy, 87.68, -11.67, -396.62, 0, false, true, false);
			Actor_Face_Actor(kActorHanoi, kActorMcCoy, true);
			Actor_Face_Actor(kActorMcCoy, kActorHanoi, true);
			Actor_Change_Animation_Mode(kActorMcCoy, 21);
			Actor_Change_Animation_Mode(kActorHanoi, 6);
			Ambient_Sounds_Play_Sound(kSfxSHOTGUN1, 97, 0, 0, 20);
			Delay(1000);
			Loop_Actor_Walk_To_XYZ(kActorMcCoy, 47.20, -11.58, -549.87, 0, false, true, false);
			Actor_Face_Actor(kActorHanoi, kActorMcCoy, true);
			Actor_Face_Actor(kActorMcCoy, kActorHanoi, true);
			Sound_Play(kSfxGUNH1A, 100, 0, 0, 50);
			Actor_Change_Animation_Mode(kActorMcCoy, 6);
			Actor_Change_Animation_Mode(kActorHanoi, 21);
			Delay(1000);
			Actor_Change_Animation_Mode(kActorHanoi, 6);
			Ambient_Sounds_Play_Sound(kSfxSHOTGUN1, 97, 0, 0, 20);
			Actor_Change_Animation_Mode(kActorMcCoy, 22);
			Delay(1000);
			Loop_Actor_Walk_To_XYZ(kActorMcCoy, 18.87, -11.52, -631.33, 0, false, true, false);
			Actor_Face_Actor(kActorHanoi, kActorMcCoy, true);
			Actor_Face_Actor(kActorMcCoy, kActorHanoi, true);
			Sound_Play(kSfxGUNH1A, 100, 0, 0, 50);
			Actor_Change_Animation_Mode(kActorMcCoy, 6);
			Actor_Change_Animation_Mode(kActorHanoi, 21);
			Delay(1000);
			Actor_Change_Animation_Mode(kActorHanoi, 6);
			Ambient_Sounds_Play_Sound(kSfxSHOTGUN1, 97, 0, 0, 20);
			Actor_Change_Animation_Mode(kActorMcCoy, 22);
			Delay(1000);
			Sound_Play(kSfxGUNH1A, 100, 0, 0, 50);
			Actor_Change_Animation_Mode(kActorMcCoy, 6);
			Actor_Change_Animation_Mode(kActorHanoi, 48);
			Delay(2000);
			Player_Set_Combat_Mode(false);
			Delay(1000);
			Player_Loses_Control();
			Loop_Actor_Walk_To_XYZ(kActorMcCoy, -284.0f, -12.2f, -789.0f, 0, true, false, false);
			Player_Gains_Control();
			Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
			Ambient_Sounds_Remove_All_Looping_Sounds(1u);
			Game_Flag_Set(kFlagKP01toKP03);
			Set_Enter(kSetKP03, kSceneKP03);
		} else if (Game_Flag_Query(kFlagKP04toKP01)) {
			Player_Set_Combat_Mode(false);
			Loop_Actor_Walk_To_XYZ(kActorMcCoy, -93.0f, -12.2f, -61.0f, 0, false, false, false);
			Game_Flag_Reset(kFlagKP04toKP01);
			return;
		}
		if (Game_Flag_Query(kFlagKP03toKP01)) {
			Player_Set_Combat_Mode(false);
			Loop_Actor_Walk_To_XYZ(kActorMcCoy, -240.0f, -12.2f, -789.0f, 0, false, false, false);
			Game_Flag_Reset(kFlagKP03toKP01);
			return;
		}
	}
}

void SceneScriptKP01::PlayerWalkedOut() {
}

void SceneScriptKP01::DialogueQueueFlushed(int a1) {
}

} // End of namespace BladeRunner
