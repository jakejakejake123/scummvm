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

void SceneScriptCT07::InitializeScene() {
	Setup_Scene_Information(202.32f, -58.23f, -12.86f, 225);
	Actor_Put_In_Set(kActorZuben, kSetCT07);
	Actor_Set_At_XYZ(kActorZuben, -9.68f, -58.23f, 11.14f, 250);

	Ambient_Sounds_Add_Looping_Sound(kSfxCTRAIN1,  30,  90, 1);
	Ambient_Sounds_Add_Looping_Sound(kSfxCTDRONE1, 20,   1, 1);
	Ambient_Sounds_Add_Looping_Sound(kSfxCTAMBR1,  40, 100, 1);
	Ambient_Sounds_Add_Speech_Sound(kActorBlimpGuy,  0, 10u, 260u, 17, 24, -100, 100, -101, -101, 1, 1);
	Ambient_Sounds_Add_Speech_Sound(kActorBlimpGuy, 20, 10u, 260u, 17, 24, -100, 100, -101, -101, 1, 1);
	Ambient_Sounds_Add_Speech_Sound(kActorBlimpGuy, 40, 10u, 260u, 17, 24, -100, 100, -101, -101, 1, 1);
	Ambient_Sounds_Add_Speech_Sound(kActorBlimpGuy, 50, 10u, 260u, 17, 24, -100, 100, -101, -101, 1, 1);
	Ambient_Sounds_Add_Sound(kSfxSPIN2A,  80, 180, 16,  25,   0,   0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSPIN2B,  50, 180, 16,  25,   0,   0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxTHNDR2,  10,  60, 50, 100,   0,   0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxTHNDER2,  6,  50, 50, 100,   0,   0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxTHNDER4, 10,  70, 50, 100,   0,   0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxDISH1,   10,  30, 12,  14, 100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxDISH2,   10,  30, 12,  14, 100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxDISH3,   10,  30, 12,  14, 100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxDISH4,   10,  30, 12,  14, 100, 100, -101, -101, 0, 0);
	if (_vm->_cutContent) {
		Ambient_Sounds_Add_Sound(kSfxDISH5,   10,  30, 12,  14, 100, 100, -101, -101, 0, 0);
	}
}

void SceneScriptCT07::SceneLoaded() {
	Obstacle_Object("BOX01", true);
	Obstacle_Object("BOX02", true);
	Obstacle_Object("BOX03", true);
	Obstacle_Object("BOX04", true);
	Unclickable_Object("BOX01");
	Unclickable_Object("BOX02");
	Unclickable_Object("BOX03");
	Unclickable_Object("BOX04");
}

bool SceneScriptCT07::MouseClick(int x, int y) {
	return true;
}

bool SceneScriptCT07::ClickedOn3DObject(const char *objectName, bool a2) {
	return false;
}

bool SceneScriptCT07::ClickedOnActor(int actorId) {
	return false;
}

bool SceneScriptCT07::ClickedOnItem(int itemId, bool a2) {
	return false;
}

bool SceneScriptCT07::ClickedOnExit(int exitId) {
	return false;
}

bool SceneScriptCT07::ClickedOn2DRegion(int region) {
	return false;
}

void SceneScriptCT07::SceneFrameAdvanced(int frame) {
}

void SceneScriptCT07::ActorChangedGoal(int actorId, int newGoal, int oldGoal, bool currentSet) {
}

void SceneScriptCT07::PlayerWalkedIn() {
	Player_Gains_Control();
	Non_Player_Actor_Combat_Mode_On(kActorZuben, kActorCombatStateIdle, false, kActorMcCoy, 2, kAnimationModeCombatIdle, kAnimationModeCombatWalk, kAnimationModeCombatRun, 0, 0, 100, 15, 300, false);
	Game_Flag_Set(kFlagCT07ZubenAttack);
	Actor_Face_Actor(kActorMcCoy, kActorZuben, true);
	if (_vm->_cutContent) {
		if (Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)	
		&& !Game_Flag_Query(kFlagMcCoyShotAtZuben)) {
			Delay(1000);
			Non_Player_Actor_Combat_Mode_Off(kActorZuben);
			Game_Flag_Reset(kFlagCT07ZubenAttack);
			AI_Movement_Track_Flush(kActorZuben);
			Actor_Modify_Friendliness_To_Other(kActorZuben, kActorMcCoy, 5);
			Actor_Set_Goal_Number(kActorZuben, kGoalZubenCT07Spared);
			Game_Flag_Set(kFlagCT01ZubenGone);
			AI_Movement_Track_Flush(kActorZuben);
			Actor_Face_Actor(kActorZuben, kActorMcCoy, true);
			Music_Stop(3u);
			Player_Set_Combat_Mode(false);
			Actor_Says(kActorMcCoy, 455, -1); //00-0455.AUD	Relax. Nobody's gonna get retired. Okay?
			Actor_Says(kActorZuben, 100, 19);
			Actor_Says(kActorMcCoy, 470, 12); //00-0470.AUD	Just talk. That's all.
			Actor_Says(kActorZuben, 110, 18);
			Actor_Says(kActorMcCoy, 475, 12);
			Actor_Says(kActorZuben, 120, 15);
			Actor_Says(kActorMcCoy, 480, 16);
			Actor_Says(kActorZuben, 130, 17);
			Actor_Says(kActorMcCoy, 485, 14);
			Game_Flag_Set(kFlagZubenSpared);
			Game_Flag_Set(kFlagMcCoyIsHelpingReplicants);
			Actor_Modify_Friendliness_To_Other(kActorSteele, kActorMcCoy, -2);
			Actor_Modify_Friendliness_To_Other(kActorGuzza, kActorMcCoy, -2);
			Actor_Modify_Friendliness_To_Other(kActorClovis, kActorMcCoy, 2);
			Actor_Set_Goal_Number(kActorGordo, kGoalGordoCT05WalkThrough);
		}
		if (Random_Query(1, 3) < 3) {
			Actor_Clue_Acquire(kActorZuben, kClueMcCoysDescription, true, -1);
		}
		if (Random_Query(1, 5) < 5) {
			Actor_Clue_Acquire(kActorZuben, kClueMcCoyIsABladeRunner, true, -1);
		}
		Actor_Clue_Acquire(kActorZuben, kClueMcCoyLetZubenEscape, true, -1);
		Actor_Set_Goal_Number(kActorZuben, kGoalZubenCT07RunToFreeSlotA);
	}
}

void SceneScriptCT07::PlayerWalkedOut() {
	Music_Stop(2u);
}

void SceneScriptCT07::DialogueQueueFlushed(int a1) {
}

} // End of namespace BladeRunner
