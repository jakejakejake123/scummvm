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

enum kRC03Loops {
	kRC03LoopInshot   = 0, // frames:  0 -  59
	kRC03LoopMainLoop = 1  // frames: 60 - 120
};

void SceneScriptRC03::InitializeScene() {
	if (Game_Flag_Query(kFlagRC01toRC03)) {
		Setup_Scene_Information(298.0f, -4.0f, 405.0f, 800);
		Game_Flag_Reset(kFlagRC01toRC03);
	} else if (Game_Flag_Query(kFlagAR02toRC03)) {
		Setup_Scene_Information(-469.0f, -4.0f, 279.0f, 250);
	} else if (Game_Flag_Query(kFlagUG01toRC03)) {
		Setup_Scene_Information(147.51f, -4.0f, 166.48f, 500);
		if (!Game_Flag_Query(kFlagRC03UnlockedToUG01)) {
			Game_Flag_Set(kFlagRC03UnlockedToUG01);
		}
	} else if (Game_Flag_Query(kFlagHC04toRC03)) {
		Setup_Scene_Information(-487.0f, 1.0f, 116.0f, 400);
	} else if (Game_Flag_Query(kFlagRC04toRC03)) {
		Setup_Scene_Information(-22.0f, 1.0f, -63.0f, 400);
	} else {
		Setup_Scene_Information(0.0f, 0.0f, 0.0f, 0);
	}

	Scene_Exit_Add_2D_Exit(0, 610, 0, 639, 479, 1);
	Scene_Exit_Add_2D_Exit(1,   0, 0,  30, 479, 3);
	if (Game_Flag_Query(kFlagRC03UnlockedToUG01)) {
#if BLADERUNNER_ORIGINAL_BUGS
		Scene_Exit_Add_2D_Exit(2, 524, 350, 573, 359, 2);
#else
		// prevent Izo's corpse from blocking the exit hot-spot area
		Scene_Exit_Add_2D_Exit(2, 524, 340, 573, 359, 2);
#endif // BLADERUNNER_ORIGINAL_BUGS
	}
	Scene_Exit_Add_2D_Exit(3,  85, 255, 112, 315, 0);
	Scene_Exit_Add_2D_Exit(4, 428, 260, 453, 324, 0);

	Ambient_Sounds_Add_Looping_Sound(kSfxCTRAIN1, 50, 0, 1);
	Ambient_Sounds_Add_Sound(kSfxRCCARBY1,  5,  30, 40,  70, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxRCCARBY2,  5,  30, 40,  75, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxRCCARBY3,  5,  30, 40,  70, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Speech_Sound(kActorBlimpGuy,  0, 10u, 260u, 17, 24, -100, 100, -101, -101, 1, 1);
	Ambient_Sounds_Add_Speech_Sound(kActorBlimpGuy, 20, 10u, 260u, 17, 24, -100, 100, -101, -101, 1, 1);
	Ambient_Sounds_Add_Speech_Sound(kActorBlimpGuy, 40, 10u, 260u, 17, 24, -100, 100, -101, -101, 1, 1);
	Ambient_Sounds_Add_Speech_Sound(kActorBlimpGuy, 50, 10u, 260u, 17, 24, -100, 100, -101, -101, 1, 1);
	Ambient_Sounds_Add_Sound(kSfxSPIN2B,   60, 180, 16,  25,    0,   0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSPIN3A,   60, 180, 16,  25,    0,   0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxTHNDER2,  60, 180, 50, 100,    0,   0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxTHNDER3,  50, 180, 50, 100,    0,   0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxTHNDER4,  50, 180, 50, 100,    0,   0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0470R,  5,  70, 12,  12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0480R,  5,  70, 12,  12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0500R,  5,  70, 12,  12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0540R,  5,  70, 12,  12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0560R,  5,  70, 12,  12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0870R,  5,  70, 12,  12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0900R,  5,  70, 12,  12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0940R,  5,  70, 12,  12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0960R,  5,  70, 12,  12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_1070R,  5,  70, 12,  12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_1080R,  5,  70, 12,  12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_1100R,  5,  70, 12,  12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_1140R,  5,  70, 12,  12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_1160R,  5,  70, 12,  12, -100, 100, -101, -101, 0, 0);

	if (Game_Flag_Query(kFlagHC04toRC03)
	 && Actor_Query_Goal_Number(kActorIzo) != kGoalIzoWaitingAtRC03
#if !BLADERUNNER_ORIGINAL_BUGS
	 && Actor_Query_Goal_Number(kActorIzo) != kGoalIzoEscape
#endif // !BLADERUNNER_ORIGINAL_BUGS
	) {
		if (Random_Query(1, 3) == 1) {
			// enhancement: don't always play this scene when exiting Hawker's Circle
			Scene_Loop_Start_Special(kSceneLoopModeLoseControl, kRC03LoopInshot, false);
			// Pause generic walkers while special loop is playing
			// to prevent glitching over background (walkers coming from Hawker's Circle)
			// This is done is a similar way to CT01
#if !BLADERUNNER_ORIGINAL_BUGS
			Actor_Set_Goal_Number(kActorGenwalkerA, kGoalGenwalkerDefault);
			Actor_Set_Goal_Number(kActorGenwalkerB, kGoalGenwalkerDefault);
			Actor_Set_Goal_Number(kActorGenwalkerC, kGoalGenwalkerDefault);
			Global_Variable_Set(kVariableGenericWalkerConfig, -1);
#endif // !BLADERUNNER_ORIGINAL_BUGS
		}
	}
	Scene_Loop_Set_Default(kRC03LoopMainLoop);
}

void SceneScriptRC03::SceneLoaded() {
	Obstacle_Object("Box-Streetlight01", true);
	Obstacle_Object("Box-Streetlight02", true);
	Obstacle_Object("Parking Meter 01", true);
	Obstacle_Object("Parking Meter 02", true);
	Obstacle_Object("Parking Meter 03", true);
	Obstacle_Object("Trash can with fire", true);
	Obstacle_Object("Baricade01", true);
	Obstacle_Object("Foreground Junk01", true);
	Obstacle_Object("Steam01", true);
	Obstacle_Object("Steam02", true);
	Obstacle_Object("Box-BBcolumn01", true);
	Obstacle_Object("Box-BBcolumn02", true);
	Obstacle_Object("Box-BBcolumn03", true);
	Obstacle_Object("Box-BBcolumn04", true);
	Obstacle_Object("Box-BBbuilding01", true);
	Obstacle_Object("Box-BBbuilding02", true);
	Obstacle_Object("Box-BBbuilding03", true);
	Obstacle_Object("Box-BBbuilding04", true);
	Unclickable_Object("BOX-BBBUILDING01");
	Unclickable_Object("BOX-BBBUILDING02");
	Unclickable_Object("BOX-BBBUILDING03");
	Unclickable_Object("BOX-BBBUILDING04");
	Unclickable_Object("BOX-STREETLIGHT01");
	Unclickable_Object("BOX-STREETLIGHT02");
	Unclickable_Object("BOX-BBCOLUMN01");
	Unclickable_Object("BOX-BBCOLUMN02");
	Unclickable_Object("BOX-BBCOLUMN03");
	Unclickable_Object("BOX-BBCOLUMN04");
#if BLADERUNNER_ORIGINAL_BUGS
#else
	Unclickable_Object("PARKING METER 01");
#endif // BLADERUNNER_ORIGINAL_BUGS
	Unclickable_Object("PARKING METER 02");
	Unclickable_Object("PARKING METER 03");
	Unclickable_Object("TRASH CAN WITH FIRE");
	Unclickable_Object("BARICADE01");
	Unclickable_Object("FOREGROUND JUNK01");
}

bool SceneScriptRC03::MouseClick(int x, int y) {
	return false;
}

bool SceneScriptRC03::ClickedOn3DObject(const char *objectName, bool a2) {
	return false;
}

bool SceneScriptRC03::ClickedOnActor(int actorId) {
	return false;
}

bool SceneScriptRC03::ClickedOnItem(int itemId, bool a2) {
	return false;
}

bool SceneScriptRC03::ClickedOnExit(int exitId) {
	if (exitId == 0) { // To Runciter's shop
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, 298.0f, -4.0f, 405.0f, 0, true, false, false)) {
			if (Game_Flag_Query(kFlagRC04McCoyShotBob)) {
				Game_Flag_Set(kFlagBulletBobDead);
			}
			Game_Flag_Set(kFlagRC03toRC01);
			Set_Enter(kSetRC01, kSceneRC01);
#if BLADERUNNER_ORIGINAL_BUGS
			Actor_Set_Goal_Number(kActorDektora, kGoalDektoraStartWalkingAround);
#else
			// Restrict Dektora's "walking around" goal only in Chapter 2
			// this is a bug fix for the case where Dektora's goal gets reset from kGoalDektoraGone in Chapter 4/5
			if (Global_Variable_Query(kVariableChapter) == 2 ) {
				Actor_Set_Goal_Number(kActorDektora, kGoalDektoraStartWalkingAround);
			}
#endif // BLADERUNNER_ORIGINAL_BUGS
		}
		return true;
	}
	if (exitId == 1) { // to Animoid Row (Scorpion/Insect Lady)
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -469.0f, -4.0f, 279.0f, 0, true, false, false)) {
			if (Game_Flag_Query(kFlagRC04McCoyShotBob)) {
				Game_Flag_Set(kFlagBulletBobDead);
			}
			Game_Flag_Set(kFlagRC03toAR02);
			Game_Flag_Reset(kFlagMcCoyInRunciters);
			Game_Flag_Set(kFlagMcCoyInAnimoidRow);
			Set_Enter(kSetAR01_AR02, kSceneAR02);
		}
		return true;
	}
	if (exitId == 2) { // to sewers
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, 147.51f, -4.0f, 166.48f, 0, true, false, false)) {
			Game_Flag_Set(kFlagRC03toUG01);
			Game_Flag_Reset(kFlagMcCoyInRunciters);
			Game_Flag_Set(kFlagMcCoyInUnderground);
			if (Game_Flag_Query(kFlagRC04McCoyShotBob)) {
				Game_Flag_Set(kFlagBulletBobDead);
			}
			Set_Enter(kSetUG01, kSceneUG01);
#if BLADERUNNER_ORIGINAL_BUGS
			Actor_Set_Goal_Number(kActorDektora, kGoalDektoraStartWalkingAround);
#else
			// Restrict Dektora's "walking around" goal only in Chapter 2
			// this is a bug fix for the case where Dektora's goal gets reset from kGoalDektoraGone in Chapter 4/5
			if (Global_Variable_Query(kVariableChapter) == 2 ) {
				Actor_Set_Goal_Number(kActorDektora, kGoalDektoraStartWalkingAround);
			}
#endif // BLADERUNNER_ORIGINAL_BUGS
		}
		return true;
	}
	if (exitId == 3) { // to Hawker's Circle (Mama Izabella's Kingston Kitchen)
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -487.0f, 1.0f, 116.0f, 0, true, false, false)) {
			Game_Flag_Set(kFlagRC03toHC04);
			Game_Flag_Reset(kFlagMcCoyInRunciters);
			Game_Flag_Set(kFlagMcCoyInHawkersCircle);
			if (Game_Flag_Query(kFlagRC04McCoyShotBob)) {
				Game_Flag_Set(kFlagBulletBobDead);
			}
			Set_Enter(kSetHC01_HC02_HC03_HC04, kSceneHC04);
#if BLADERUNNER_ORIGINAL_BUGS
			Actor_Set_Goal_Number(kActorDektora, kGoalDektoraStartWalkingAround);
#else
			// Restrict Dektora's "walking around" goal only in Chapter 2
			// this is a bug fix for the case where Dektora's goal gets reset from kGoalDektoraGone in Chapter 4/5
			if (Global_Variable_Query(kVariableChapter) == 2 ) {
				Actor_Set_Goal_Number(kActorDektora, kGoalDektoraStartWalkingAround);
			}
#endif // BLADERUNNER_ORIGINAL_BUGS
		}
		return true;
	}
	if (exitId == 4) { // To Bullet Bob's
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -22.0f, 1.0f, -63.0f, 0, true, false, false)) {
			// Made it so Bobs shop is open in act 3
			if (_vm->_cutContent)  {
				if (Global_Variable_Query(kVariableChapter) == 5
				|| Game_Flag_Query(kFlagOfficerLearyKilledByBob)
				) {
				Actor_Says(kActorMcCoy, 8522, 14);
			} else {
				Game_Flag_Set(kFlagRC03toRC04);
				Set_Enter(kSetRC04, kSceneRC04);
			}
			} else if (Global_Variable_Query(kVariableChapter) == 3
			 || Global_Variable_Query(kVariableChapter) == 5
			 || Game_Flag_Query(kFlagBulletBobDead)
			) {
				Actor_Says(kActorMcCoy, 8522, 14);
			} else {
				Game_Flag_Set(kFlagRC03toRC04);
				Set_Enter(kSetRC04, kSceneRC04);
			}
		}
		return true;
	}
	return false;
}

bool SceneScriptRC03::ClickedOn2DRegion(int region) {
	return false;
}

void SceneScriptRC03::SceneFrameAdvanced(int frame) {
	if (frame == 1) {
		Sound_Play(kSfxTRUCKBY1, Random_Query(33, 33), 100, -100, 50);
	}
	if (frame == 15) {
		Sound_Play(kSfxCHEVBY1,  Random_Query(50, 50), -100, 100, 50);
	}
#if !BLADERUNNER_ORIGINAL_BUGS
	if (frame == 59) {
		// end of special loop
		// Resume walkers
		if (Global_Variable_Query(kVariableGenericWalkerConfig) < 0 ) {
			Global_Variable_Set(kVariableGenericWalkerConfig, 2);
		}
	}
#endif // BLADERUNNER_ORIGINAL
}

void SceneScriptRC03::ActorChangedGoal(int actorId, int newGoal, int oldGoal, bool currentSet) {
}

void SceneScriptRC03::talkWithSteele() {
	Actor_Face_Actor(kActorSteele, kActorMcCoy, true);
	Actor_Says(kActorSteele, 1820, kAnimationModeTalk);
	Actor_Face_Actor(kActorMcCoy, kActorSteele, true);
	Actor_Says(kActorMcCoy, 4815, 14);
	Actor_Says(kActorSteele, 1830, kAnimationModeTalk);
	Actor_Says(kActorSteele, 1840, kAnimationModeTalk);
	Actor_Says(kActorMcCoy, 4820, 12);
	Actor_Says(kActorSteele, 1850, kAnimationModeTalk);
	if (_vm->_cutContent) {
		Actor_Says(kActorMcCoy, 4825, 13);
	}
	Actor_Says(kActorSteele, 1950, kAnimationModeTalk);
	Actor_Says(kActorMcCoy, 4835, 14);
	Actor_Says(kActorSteele, 1960, kAnimationModeTalk);
	Actor_Says(kActorSteele, 1980, kAnimationModeTalk);
	Actor_Says(kActorMcCoy, 4840, 15);
	Actor_Says(kActorSteele, 1990, kAnimationModeTalk);
	Actor_Says(kActorSteele, 2000, kAnimationModeTalk);
}

void SceneScriptRC03::PlayerWalkedIn() {
	if (_vm->_cutContent) {
		if (Actor_Query_Goal_Number(kActorIzo) == kGoalIzoWaitingAtRC03) {
			Scene_Exits_Disable();
			if (Game_Flag_Query(kFlagUG01toRC03)) {
				// Music will play during the confrontation with Izo.
				if (Game_Flag_Query(kFlagIzoIsReplicant)) {
					Music_Play(kMusicBeating1, 71, 0, 0, -1, kMusicLoopPlayOnce, 2);
					Player_Set_Combat_Mode(false);
					Player_Loses_Control();
					Actor_Set_At_XYZ(kActorMcCoy, 147.51f, -4.0f, 166.48f, 500);
					Actor_Put_In_Set(kActorIzo, kSetRC03);
					Actor_Set_At_XYZ(kActorIzo, 196.0f, -4.0f, 184.0f, 775);
					Actor_Face_Actor(kActorIzo, kActorMcCoy, true);
					Actor_Face_Actor(kActorMcCoy, kActorIzo, true);
					Actor_Change_Animation_Mode(kActorIzo, kAnimationModeCombatIdle);
					Actor_Says_With_Pause(kActorIzo, 630, 0.0f, -1); // TODO: A bug? why is animation mode set as -1? and why is "With_Pause" version used?
					Actor_Says_With_Pause(kActorIzo, 640, 0.0f, -1); // TODO: A bug? why is animation mode set as -1? and why is "With_Pause" version used?
					Actor_Says_With_Pause(kActorIzo, 650, 0.0f, -1); // TODO: A bug? why is animation mode set as -1? and why is "With_Pause" version used?
					if (Game_Flag_Query(kFlagIzoIsReplicant) ) {
						if (Actor_Query_Goal_Number(kActorIzo) != kGoalIzoDie
							&& Actor_Query_Goal_Number(kActorIzo) != kGoalIzoDieHidden
							&& Actor_Query_Goal_Number(kActorIzo) != kGoalIzoRC03RanAwayDone
							&& Actor_Query_Goal_Number(kActorIzo) != kGoalIzoEscape
							&& Actor_Query_Goal_Number(kActorSteele) != kGoalSteeleShootIzo
							&& Actor_Query_Goal_Number(kActorSteele) != kGoalSteeleIzoBlockedByMcCoy
							&& Actor_Query_Goal_Number(kActorSteele) != kGoalSteeleLeaveRC03
							&& Actor_Query_Goal_Number(kActorSteele) != kGoalSteeleGoToPoliceStation
						) {
							Actor_Set_Goal_Number(kActorSteele, kGoalSteeleApprehendIzo);
						}
						Player_Gains_Control();
					}
					Actor_Change_Animation_Mode(kActorMcCoy, kAnimationModeDodge);
					Loop_Actor_Walk_To_XYZ(kActorIzo, 180.0f, -4.0f, 184.0f, 0, false, false, false);
					Actor_Change_Animation_Mode(kActorIzo, kAnimationModeCombatAttack);
				} else {
					Player_Set_Combat_Mode(false);
					Player_Loses_Control();
					Actor_Set_At_XYZ(kActorMcCoy, 147.51f, -4.0f, 166.48f, 500);
					Actor_Put_In_Set(kActorIzo, kSetRC03);
					Actor_Set_At_XYZ(kActorIzo, 196.0f, -4.0f, 184.0f, 775);
					Actor_Face_Actor(kActorIzo, kActorMcCoy, true);
					Actor_Face_Actor(kActorMcCoy, kActorIzo, true);
					Actor_Says(kActorMcCoy, 8950, 14); //00-8950.AUD	Hold it right there!
					if (Actor_Query_Goal_Number(kActorIzo) != kGoalIzoDie
						&& Actor_Query_Goal_Number(kActorIzo) != kGoalIzoDieHidden
						&& Actor_Query_Goal_Number(kActorIzo) != kGoalIzoRC03RanAwayDone
						&& Actor_Query_Goal_Number(kActorIzo) != kGoalIzoEscape
						&& Actor_Query_Goal_Number(kActorSteele) != kGoalSteeleShootIzo
						&& Actor_Query_Goal_Number(kActorSteele) != kGoalSteeleIzoBlockedByMcCoy
						&& Actor_Query_Goal_Number(kActorSteele) != kGoalSteeleLeaveRC03
						&& Actor_Query_Goal_Number(kActorSteele) != kGoalSteeleGoToPoliceStation
					) {
						Actor_Set_Goal_Number(kActorSteele, kGoalSteeleApprehendIzo);
					}
					Player_Gains_Control();
				}
			} else {
				Actor_Put_In_Set(kActorIzo, kSetRC03);
				Actor_Set_At_XYZ(kActorIzo, -226.0f, 1.72f, 86.0f, 0);
				Actor_Set_Targetable(kActorIzo, true);
				Actor_Set_Goal_Number(kActorIzo, kGoalIzoRC03Walk);
			}
		}
	} else if (Actor_Query_Goal_Number(kActorIzo) == kGoalIzoWaitingAtRC03) {
		Scene_Exits_Disable();
		if (Game_Flag_Query(kFlagUG01toRC03)) {
			if (Game_Flag_Query(kFlagIzoIsReplicant)) {
				Player_Set_Combat_Mode(false);
				Player_Loses_Control();
				Actor_Set_At_XYZ(kActorMcCoy, 147.51f, -4.0f, 166.48f, 500);
				Actor_Put_In_Set(kActorIzo, kSetRC03);
				Actor_Set_At_XYZ(kActorIzo, 196.0f, -4.0f, 184.0f, 775);
				Actor_Face_Actor(kActorIzo, kActorMcCoy, true);
				Actor_Face_Actor(kActorMcCoy, kActorIzo, true);
				Actor_Change_Animation_Mode(kActorIzo, kAnimationModeCombatIdle);
				Actor_Says_With_Pause(kActorIzo, 630, 0.0f, -1); // TODO: A bug? why is animation mode set as -1? and why is "With_Pause" version used?
				Actor_Says_With_Pause(kActorIzo, 640, 0.0f, -1); // TODO: A bug? why is animation mode set as -1? and why is "With_Pause" version used?
				Actor_Says_With_Pause(kActorIzo, 650, 0.0f, -1); // TODO: A bug? why is animation mode set as -1? and why is "With_Pause" version used?
				if (Game_Flag_Query(kFlagIzoIsReplicant) ) {
	#if BLADERUNNER_ORIGINAL_BUGS
					Actor_Set_Goal_Number(kActorSteele, kGoalSteeleApprehendIzo);
	#else
					// prevent re-apprehending of Izo
					if (Actor_Query_Goal_Number(kActorIzo) != kGoalIzoDie
						&& Actor_Query_Goal_Number(kActorIzo) != kGoalIzoDieHidden
						&& Actor_Query_Goal_Number(kActorIzo) != kGoalIzoRC03RanAwayDone
						&& Actor_Query_Goal_Number(kActorIzo) != kGoalIzoEscape
						&& Actor_Query_Goal_Number(kActorSteele) != kGoalSteeleShootIzo
						&& Actor_Query_Goal_Number(kActorSteele) != kGoalSteeleIzoBlockedByMcCoy
						&& Actor_Query_Goal_Number(kActorSteele) != kGoalSteeleLeaveRC03
						&& Actor_Query_Goal_Number(kActorSteele) != kGoalSteeleGoToPoliceStation
					) {
						Actor_Set_Goal_Number(kActorSteele, kGoalSteeleApprehendIzo);
					}
	#endif // BLADERUNNER_ORIGINAL_BUGS
				}
				Actor_Change_Animation_Mode(kActorMcCoy, kAnimationModeDodge);
				Loop_Actor_Walk_To_XYZ(kActorIzo, 180.0f, -4.0f, 184.0f, 0, false, false, false);
				Actor_Change_Animation_Mode(kActorIzo, kAnimationModeCombatAttack);
				if (!Game_Flag_Query(kFlagIzoIsReplicant)) {
	#if BLADERUNNER_ORIGINAL_BUGS
					Actor_Set_Goal_Number(kActorSteele, kGoalSteeleApprehendIzo);
	#else
					// prevent re-apprehending of Izo
					if (Actor_Query_Goal_Number(kActorIzo) != kGoalIzoGetArrested
						&& Actor_Query_Goal_Number(kActorIzo) != kGoalIzoGotArrested
						&& Actor_Query_Goal_Number(kActorIzo) != kGoalIzoRC03RanAwayDone
						&& Actor_Query_Goal_Number(kActorIzo) != kGoalIzoEscape
						&& Actor_Query_Goal_Number(kActorSteele) != kGoalSteeleApprehendIzo
						&& Actor_Query_Goal_Number(kActorSteele) != kGoalSteeleArrestIzo
						&& Actor_Query_Goal_Number(kActorSteele) != kGoalSteeleIzoBlockedByMcCoy
						&& Actor_Query_Goal_Number(kActorSteele) != kGoalSteeleLeaveRC03
						&& Actor_Query_Goal_Number(kActorSteele) != kGoalSteeleGoToPoliceStation
					) {
						Actor_Set_Goal_Number(kActorSteele, kGoalSteeleApprehendIzo);
					}
	#endif // BLADERUNNER_ORIGINAL_BUGS
				}
				Player_Gains_Control();
			}
		} else {
			Actor_Put_In_Set(kActorIzo, kSetRC03);
			Actor_Set_At_XYZ(kActorIzo, -226.0f, 1.72f, 86.0f, 0);
			Actor_Set_Targetable(kActorIzo, true);
			Actor_Set_Goal_Number(kActorIzo, kGoalIzoRC03Walk);
		}
	}

	if (Game_Flag_Query(kFlagIzoEscaped)) {
		Player_Loses_Control();
		Actor_Set_Goal_Number(kActorSteele, 200);
		Actor_Put_In_Set(kActorSteele, kSetRC03);
		if (Game_Flag_Query(kFlagUG01toRC03)
		 || Game_Flag_Query(kFlagRC04toRC03)
		) {
			Actor_Set_At_Waypoint(kActorSteele, 175, 0);
		} else {
			Actor_Set_At_Waypoint(kActorSteele, 203, 0);
		}
		// Code for the scene where you talk to Crystal after Izo has escaped. The scene will play out differently depending on whether
		// or not you warned Izo about Crystal.
		Player_Set_Combat_Mode(false);
		Async_Actor_Walk_To_Waypoint(kActorSteele, 174, 0, false);
		Actor_Face_Actor(kActorSteele, kActorMcCoy, true);
		Actor_Face_Actor(kActorMcCoy, kActorSteele, true);
		Actor_Says(kActorSteele, 1820, 58); //01-1820.AUD	Where's Izo?
		Actor_Says(kActorMcCoy, 4815, 13); //00-4815.AUD	You're looking for him, too?
		Actor_Says(kActorSteele, 1830, 59); //01-1830.AUD	I was at the bar over in Hawker's circle. I saw him pop that flash in your face.
		Actor_Says(kActorSteele, 1840, 59); //01-1840.AUD	Then some lummox got in my way and I didn't see where it disappeared to.
		Actor_Says(kActorMcCoy, 4820, 16); //00-4820.AUD	He probably went down in the sewers.
		Actor_Says(kActorSteele, 1850, 59); //01-1850.AUD	Right where that dirt-bag belongs.
		Actor_Says(kActorSteele, 1950, 59); //01-1950.AUD	I've been tracking Izo for a week and you ruined my whole plan in two seconds.
		Game_Flag_Reset(kFlagIzoEscaped);
		Game_Flag_Reset(kFlagIzoWarnedAboutCrystal);
		if (!Game_Flag_Query(kFlagIzoWarned)) {
			Actor_Says(kActorMcCoy, 4835, 13); //00-4835.AUD	Sorry, I bet you can still catch him if you want.
			Actor_Says(kActorSteele, 1960, 60); //01-1960.AUD	Crawl down that hole and ruin a twenty thousand chinyen Yamamoto suit? I don't think so.
			Actor_Says(kActorSteele, 1980, 60); //01-1980.AUD	If I didn't know any better, I'd think you wanted him to get away.
			Actor_Says(kActorMcCoy, 4840, 16); //00-4840.AUD	You crazy? I've been tailing him myself.
			Actor_Says(kActorSteele, 1990, 60); //01-1990.AUD	A little word of advice, Slim. Stay out of my way.
			Player_Gains_Control();
			Actor_Set_Goal_Number(kActorSteele, kGoalSteeleLeaveRC03);
		} else {
			Actor_Says(kActorMcCoy, 8565, 15); //00-8565.AUD	Really?
			Actor_Says(kActorSteele, 1990, 60); //01-1990.AUD	A little word of advice, Slim. Stay out of my way.
			Actor_Says(kActorMcCoy, 5150, 15); //00-5150.AUD	One more thing.
			Actor_Says(kActorSteele, 670, 60); //01-0670.AUD	Look. I’ll give you two minutes. That’s all.
			Actor_Set_Goal_Number(kActorSteele, kGoalSteeleRC03GoToAR02);
		}
	}
	Game_Flag_Reset(kFlagUG01toRC03);
	Game_Flag_Reset(kFlagAR02toRC03);
	Game_Flag_Reset(kFlagHC04toRC03);
	Game_Flag_Reset(kFlagRC04toRC03);

	if (Global_Variable_Query(kVariableChapter) == 1
	 || Global_Variable_Query(kVariableChapter) == 2
	) {
		Actor_Set_Goal_Number(kActorDektora, kGoalDektoraStopWalkingAround);
	}
}

void SceneScriptRC03::PlayerWalkedOut() {
	if (Actor_Query_Goal_Number(kActorIzo) == kGoalIzoDie) {
		Actor_Set_Goal_Number(kActorIzo, kGoalIzoDieHidden);
	}
	Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
	Ambient_Sounds_Remove_All_Looping_Sounds(1u);
}

void SceneScriptRC03::DialogueQueueFlushed(int a1) {
}

} // End of namespace BladeRunner
