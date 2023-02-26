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

void SceneScriptBB03::InitializeScene() {
	Setup_Scene_Information(20.0f, 60.16f, 0.0f, 0);
	if (Game_Flag_Query(kFlagBB04toBB03)) {
		Setup_Scene_Information(176.0f, 60.16f,    0.0f, 900);
	}
	if (Game_Flag_Query(kFlagBB05toBB03)) {
		Setup_Scene_Information(204.0f, 60.16f, -164.0f, 740);
	}

	Scene_Exit_Add_2D_Exit(0, 589,   0, 639, 479, 1);
	Scene_Exit_Add_2D_Exit(1, 167, 372, 439, 479, 2);
	Scene_Exit_Add_2D_Exit(2, 451, 115, 547, 320, 1);

	Ambient_Sounds_Add_Looping_Sound(kSfxCTRAIN1,  20,   0, 1);
	Ambient_Sounds_Add_Looping_Sound(kSfxRAINAWN1, 40,   0, 1);
	Ambient_Sounds_Add_Looping_Sound(kSfxCTRUNOFF, 34, 100, 1);
	Ambient_Sounds_Add_Sound(kSfxSCARY4,  2, 180, 14, 16, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSCARY5,  2, 180, 14, 16, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSCARY6,  2, 180, 14, 16, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSCARY7,  2, 180, 14, 16, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBBGRN1,  5,  50, 17, 27, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBBGRN2,  5,  50, 17, 27, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBBGRN3,  5,  50, 17, 27, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBBMOVE1, 5,  50, 17, 27, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBBMOVE2, 5,  50, 17, 27, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBBMOVE3, 5,  50, 17, 27, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxHAUNT1,  5,  50, 17, 27, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxHAUNT2,  5,  50, 17, 27, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxPSDOOR1, 5,  50, 17, 17, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxPSDOOR2, 5,  50, 17, 17, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxTHNDER2, 5, 180, 25, 25, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxTHNDER3, 5, 180, 25, 25, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxTHNDER4, 5, 180, 25, 25, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSWEEP2,  5,  80, 20, 20, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSWEEP3,  5,  80, 20, 20, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSWEEP4,  5,  80, 20, 20, -100, 100, -101, -101, 0, 0);
}

void SceneScriptBB03::SceneLoaded() {
	Obstacle_Object("BACKWALL", true);
	Unobstacle_Object("BOX08", true);
}

bool SceneScriptBB03::MouseClick(int x, int y) {
	return false;
}

bool SceneScriptBB03::ClickedOn3DObject(const char *objectName, bool a2) {
	return false;
}

bool SceneScriptBB03::ClickedOnActor(int actorId) {
	return false;
}

bool SceneScriptBB03::ClickedOnItem(int itemId, bool a2) {
	return false;
}

bool SceneScriptBB03::ClickedOnExit(int exitId) {
	if (exitId == 0) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, 176.0f, 60.16f, -64.0f, 0, true, false, false)) {
			Loop_Actor_Walk_To_XYZ(kActorMcCoy, 176.0f, 60.16f, 0.0f, 0, false, false, false);
			Game_Flag_Set(kFlagBB03toBB04);
			Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
			Ambient_Sounds_Remove_All_Looping_Sounds(1u);
			Set_Enter(kSetBB02_BB04_BB06_BB51, kSceneBB04);
		}
		return true;
	}

	if (exitId == 1) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, 20.0f, 60.16f, 0.0f, 0, true, false, false)) {
			Game_Flag_Set(kFlagBB03toBB02);
			Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
			Ambient_Sounds_Remove_All_Looping_Sounds(1u);
			Set_Enter(kSetBB02_BB04_BB06_BB51, kSceneBB02);
		}
		return true;
	}

	if (exitId == 2) {
		// Added in dialogue where McCoy makes a comment on Sebastians door which has been busted open.
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, 204.0f, 60.16f, -164.0f, 0, true, false, false)) {
			if (_vm->_cutContent) {	
				if (!Game_Flag_Query(kFlagBB05Visited)) {
					Actor_Voice_Over(1870, kActorVoiceOver); //99-1870.AUD	Whoever did it showed some serious strength. They busted the lock clean off.
					Actor_Clue_Acquire(kActorMcCoy, kClueDoorForced2, true, -1);
					Delay(1000);
					Game_Flag_Set(kFlagBB05Visited);
					Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
					Ambient_Sounds_Remove_All_Looping_Sounds(1u);
					Set_Enter(kSetBB05, kSceneBB05);;
				} else if (Actor_Clue_Query(kActorSebastian, kClueMcCoyIsABladeRunner)) {
					Actor_Says(kActorMcCoy, 6985, 16); //00-6985.AUD	Got the straight scoop for me or what?
					Actor_Says(kActorSebastian, 610, 14); //56-0610.AUD	I think you should leave now, Mr. McCoy.
				} else if (Actor_Query_Goal_Number(kActorSebastian) != 200) {
					Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
					Ambient_Sounds_Remove_All_Looping_Sounds(1u);
					Set_Enter(kSetBB05, kSceneBB05);
				}
			} else {
				Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
				Ambient_Sounds_Remove_All_Looping_Sounds(1u);
				Set_Enter(kSetBB05, kSceneBB05);
			}
		}
		if (Global_Variable_Query(kVariableChapter) < 4) {
			if (Actor_Query_Goal_Number(kActorSebastian) == 200) {
				Actor_Says(kActorSebastian, 70, kAnimationModeTalk);
				Actor_Says(kActorMcCoy, 7010, 13);
				Actor_Says(kActorSebastian, 80, kAnimationModeTalk);
				if (_vm->_cutContent) {
					Actor_Says(kActorMcCoy, 7015, 23);
				} else {
					Actor_Says(kActorMcCoy, 7015, 12);
				}
				Actor_Says(kActorSebastian, 90, kAnimationModeTalk);
				Actor_Says(kActorMcCoy, 7020, 14);
				Actor_Says(kActorSebastian, 100, kAnimationModeTalk); //56-0100.AUD	Well, everything's all right now. I'm pretty sure I can handle it.
				if (_vm->_cutContent) {
					if (Player_Query_Agenda() != kPlayerAgendaSurly 
					&& Player_Query_Agenda() != kPlayerAgendaErratic) {
						Actor_Says(kActorMcCoy, 7025, 15); //00-7025.AUD	You may think you can but believe me you can't. Better if I check it out.
					} else {
						Player_Set_Combat_Mode(true);
						Actor_Says(kActorSebastian, 680, 12); //56-0680.AUD	Hey, you don't need to do that.
						Delay(500);
						Actor_Says(kActorSebastian, 700, 15); //56-0700.AUD	Please! You don't have to pull your gun in here.
						Actor_Says_With_Pause(kActorMcCoy, 7265, 0.0f, -1); //00-7265.AUD	Think real hard JF. You got anything here that someone would want?
						Actor_Says(kActorSebastian, 690, 16);//56-0690.AUD	There's nothing in here. People don't even like to come inside my building.
						Actor_Says(kActorMcCoy, 8519, -1);//00-8519.AUD	What do you say we dish each other the straight goods.
						Actor_Modify_Friendliness_To_Other(kActorSebastian, kActorMcCoy, -2);
						Delay(2000);
						Player_Set_Combat_Mode(false);
					}
				} else {
					Actor_Says(kActorMcCoy, 7025, 15); //00-7025.AUD	You may think you can but believe me you can't. Better if I check it out.
				}
				Actor_Says(kActorSebastian, 110, kAnimationModeTalk); //56-0110.AUD	Well, if you insist…
				Actor_Set_Targetable(kActorBryant, false);
				Actor_Set_Targetable(kActorGeneralDoll, false);
				Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
				Ambient_Sounds_Remove_All_Looping_Sounds(1u);
				Set_Enter(kSetBB05, kSceneBB05);
			}
		} else {
			if (_vm->_cutContent) {	
				Actor_Says(kActorMcCoy, 7815, 13); //00-7815.AUD	No.
			} else {
				Actor_Says(kActorMcCoy, 8522, kAnimationModeTalk);
			}
		}
		return true;
	}
	return false;
}

bool SceneScriptBB03::ClickedOn2DRegion(int region) {
	return false;
}

void SceneScriptBB03::SceneFrameAdvanced(int frame) {
}

void SceneScriptBB03::ActorChangedGoal(int actorId, int newGoal, int oldGoal, bool currentSet) {
}

void SceneScriptBB03::PlayerWalkedIn() {
	if (Game_Flag_Query(kFlagBB05toBB03)) {
		Loop_Actor_Walk_To_XYZ(kActorMcCoy, 164.0f, 60.16f, -164.0f, 0, false, false, false);
		Game_Flag_Reset(kFlagBB05toBB03);
	}

	if (Game_Flag_Query(kFlagBB04toBB03)) {
		Loop_Actor_Walk_To_XYZ(kActorMcCoy, 176.0f, 60.16f, -64.0f, 0, false, false, false);
		Game_Flag_Reset(kFlagBB04toBB03);
	}
}

void SceneScriptBB03::PlayerWalkedOut() {
}

void SceneScriptBB03::DialogueQueueFlushed(int a1) {
}

} // End of namespace BladeRunner
