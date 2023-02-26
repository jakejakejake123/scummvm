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

enum kNR11Loops {
	kNR11LoopMainLoop         = 0,
	kNR11LoopGunshots         = 2,
	kNR11LoopMainLoopFires    = 3,
	kNR11LoopMainLoopBurnedUp = 5
};

void SceneScriptNR11::InitializeScene() {
	Setup_Scene_Information(100.0f, 1.75f, -4.0f, 0);

	Scene_Exit_Add_2D_Exit(0, 450, 305, 565, 345, 2);

	if (!Game_Flag_Query(kFlagNR10CameraDestroyed)) {
		Ambient_Sounds_Adjust_Looping_Sound(kSfx35MM, 22, 0, 1u);
	}

	Ambient_Sounds_Add_Looping_Sound(kSfxCTDRONE1, 22, 0, 1);
	Ambient_Sounds_Add_Looping_Sound(kSfxBRBED5,   33, 0, 1);
	Ambient_Sounds_Add_Sound(kSfxBBGRN1,  2, 50, 7, 17, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBBGRN2,  2, 50, 7, 17, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBBGRN3,  2, 50, 7, 17, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBBMOVE1, 2, 50, 7, 17, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBBMOVE2, 2, 50, 7, 17, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBBMOVE3, 2, 50, 7, 17, -100, 100, -101, -101, 0, 0);

	if (Game_Flag_Query(kFlagNR01DektoraFall)) {
		Scene_Loop_Set_Default(kNR11LoopMainLoopFires);
		Ambient_Sounds_Add_Looping_Sound(kSfxRAIN10, 83, 0, 1);
	} else if (Game_Flag_Query(kFlagNR11BurnedUp)) {
		Scene_Loop_Set_Default(kNR11LoopMainLoopBurnedUp);
		Ambient_Sounds_Add_Looping_Sound(kSfxRAIN10, 83, 0, 1);
	} else {
		Scene_Loop_Set_Default(kNR11LoopMainLoop);
		Overlay_Play("NR11OVER", 0, true, false, 0);
	}
}

void SceneScriptNR11::SceneLoaded() {
	Obstacle_Object("COATRACK", true);
	Unobstacle_Object("BOX13", true);
	Clickable_Object("LOFT04");
	Unclickable_Object("LOFT04");
	if (Actor_Query_Goal_Number(kActorDektora) == kGoalDektoraNR11Hiding) {
		Clickable_Object("CLOTHING02");
		Clickable_Object("BOX27");
		Clickable_Object("BOX39");
#if BLADERUNNER_ORIGINAL_BUGS
		// in our bugfixes this object is removed
		Clickable_Object("BOX44");
#endif // BLADERUNNER_ORIGINAL_BUGS
		Clickable_Object("DRESS");
		Clickable_Object("COATRACK");
		Clickable_Object("COLUMN3 DETS");
		Clickable_Object("COLUMN PIPE01");
		Clickable_Object("RECTANGLE02");
		Clickable_Object("COLUMN04");
		Clickable_Object("COATRACK01");
		Clickable_Object("SHIRT");
		Clickable_Object("SKIRT 02");
		Clickable_Object("CLOTHING B 03");
		Clickable_Object("BUST BUST");
		Combat_Target_Object("CLOTHING02");
		Combat_Target_Object("BOX27");
		Combat_Target_Object("BOX39");
#if BLADERUNNER_ORIGINAL_BUGS
		// in our bugfixes this object is removed
		Combat_Target_Object("BOX44");
#endif // BLADERUNNER_ORIGINAL_BUGS
		Combat_Target_Object("DRESS");
		Combat_Target_Object("COATRACK");
		Combat_Target_Object("COLUMN3 DETS");
		Combat_Target_Object("COLUMN PIPE01");
		Combat_Target_Object("RECTANGLE02");
		Combat_Target_Object("COLUMN04");
		Combat_Target_Object("COATRACK01");
		Combat_Target_Object("SHIRT");
		Combat_Target_Object("SKIRT 02");
		Combat_Target_Object("CLOTHING B 03");
		Combat_Target_Object("BUST BUST");
	} else {
		Unclickable_Object("CLOTHING02");
		Unclickable_Object("BOX27");
		Unclickable_Object("BOX39");
#if BLADERUNNER_ORIGINAL_BUGS
		// in our bugfixes this object is removed
		Unclickable_Object("BOX44");
#endif
		Unclickable_Object("DRESS");
		Unclickable_Object("COATRACK");
		Unclickable_Object("COLUMN3 DETS");
		Unclickable_Object("COLUMN PIPE01");
		Unclickable_Object("RECTANGLE02");
		Unclickable_Object("COLUMN04");
		Unclickable_Object("COATRACK01");
		Unclickable_Object("SHIRT");
		Unclickable_Object("SKIRT 02");
		Unclickable_Object("CLOTHING B 03");
		Unclickable_Object("BUST BUST");
	}
}

bool SceneScriptNR11::MouseClick(int x, int y) {
	return false;
}

bool SceneScriptNR11::ClickedOn3DObject(const char *objectName, bool combatMode) {

	if (Object_Query_Click("CLOTHING02", objectName)
	 || Object_Query_Click("BOX27", objectName)
	 || Object_Query_Click("BOX39", objectName)
#if BLADERUNNER_ORIGINAL_BUGS
	 // in our bugfixes this object is removed
	 || Object_Query_Click("BOX44", objectName)
#endif // BLADERUNNER_ORIGINAL_BUGS
	 || Object_Query_Click("DRESS", objectName)
	 || Object_Query_Click("COATRACK", objectName)
	 || Object_Query_Click("COLUMN3 DETS", objectName)
	 || Object_Query_Click("COLUMN PIPE01", objectName)
	 || Object_Query_Click("RECTANGLE02", objectName)
	 || Object_Query_Click("COLUMN04", objectName)
	 || Object_Query_Click("COATRACK01", objectName)
	 || Object_Query_Click("SHIRT", objectName)
	 || Object_Query_Click("SKIRT 02", objectName)
	 || Object_Query_Click("CLOTHING B 03", objectName)
	 || Object_Query_Click("BUST BUST", objectName)
	) {
		if (combatMode) {
			Actor_Set_Goal_Number(kActorSteele, kGoalSteeleNR11StopWaiting);
			Scene_Exits_Disable();
			untargetEverything();
			Player_Loses_Control();
			if (!Player_Query_Combat_Mode()) {
				Player_Set_Combat_Mode(true);
			}
			Actor_Set_Goal_Number(kActorMcCoy, kGoalMcCoyNR11Shoot);
			Scene_Loop_Set_Default(kNR11LoopMainLoopFires);
			Scene_Loop_Start_Special(kSceneLoopModeOnce, kNR11LoopGunshots, true);
		} else if (Actor_Query_Goal_Number(kActorDektora) == kGoalDektoraNR11Hiding) {
			if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, 24.0f, 0.33f, 0.0f, 0, true, false, false)) {
				Actor_Face_XYZ(kActorMcCoy, -180.0f, 0.0f, -170.0f, true);
				untargetEverything();
				Actor_Set_Goal_Number(kActorSteele, kGoalSteeleNR11StopWaiting);
				if (Actor_Query_Friendliness_To_Other(kActorDektora, kActorMcCoy) < 30) {
					Actor_Set_At_XYZ(kActorDektora, 0.5f, 0.33f, -162.0f, 0);
					Loop_Actor_Walk_To_XYZ(kActorDektora, -24.0f, 0.33f, -35.4f, 0, false, true, false);
					Actor_Face_Actor(kActorMcCoy, kActorDektora, true);
					Actor_Change_Animation_Mode(kActorDektora, 71);
					Delay(500);
					Actor_Change_Animation_Mode(kActorMcCoy, kAnimationModeDie);
					Delay(2000);
					Actor_Set_Goal_Number(kActorMcCoy, kGoalMcCoyNR10Fall);
				} else {
					Actor_Says(kActorMcCoy, 3840, 18);
					Delay(1000);
					if (_vm->_cutContent) {
						if (Global_Variable_Query(kVariableAffectionTowards) == kAffectionTowardsDektora
						) {
							Music_Play(kMusicLoveSong, 35, 0, 3, -1, kMusicLoopPlayOnce, 0);
						}
					} else if (Actor_Query_Friendliness_To_Other(kActorDektora, kActorMcCoy) > 59
					 && Global_Variable_Query(kVariableAffectionTowards) == kAffectionTowardsNone
					) {
						Music_Play(kMusicLoveSong, 35, 0, 3, -1, kMusicLoopPlayOnce, 0);
					}
					Loop_Actor_Walk_To_XYZ(kActorDektora, -135.0f, 0.33f, -267.0f, 0, false, false, false);
					Actor_Face_Actor(kActorDektora, kActorMcCoy, true);
					Actor_Face_Actor(kActorMcCoy, kActorDektora, true);
					//Repurposed the Dektora interview 4 clue for reasons I mentioned in NR07.
					if (_vm->_cutContent) {
						Actor_Clue_Acquire(kActorMcCoy, kClueMcCoyHelpedDektora, true, kActorDektora);
					} else {
						Actor_Clue_Acquire(kActorMcCoy, kClueDektoraInterview4, true, kActorDektora);
					}
					if (_vm->_cutContent) {
						if (!Actor_Clue_Query(kActorDektora, kClueMcCoyHelpedDektora)) {
							Actor_Says(kActorDektora, 990, 13); //03-0990.AUD	You say a lot of things, Mr. McCoy.
							Actor_Says(kActorDektora, 1000, 14); //03-1000.AUD	But you’re a Blade Runner. It’s hard to know what’s real.
						}
						Loop_Actor_Walk_To_Actor(kActorDektora, kActorMcCoy, 108, false, false);
						Actor_Says(kActorMcCoy, 3845, 13); //00-3845.AUD	One of my associates is after you and your friends.
						Actor_Says(kActorMcCoy, 2090, 13); //03-2090.AUD	Oh.
						Delay(1000);
						if (Game_Flag_Query(kFlagDektoraIsReplicant)) {
							Actor_Says(kActorMcCoy, 3850, 15); //00-3850.AUD	I’m not sure I can hold her off much longer.
							Actor_Says(kActorDektora, 1010, 14); //03-1010.AUD	I’m not worried. She may kill some of us but not all of us. Clovis will see to that.		
						} else { 
							Actor_Says(kActorMcCoy, 6535, 15); //00-6535.AUD	I need to see Clovis ASAP.
							Actor_Says(kActorMcCoy, 3870, 3); //00-3870.AUD	Can you take me to him?
							if (!Actor_Clue_Query(kActorDektora, kClueMcCoyHelpedDektora)) {
								Actor_Says(kActorDektora, 2060, 14);//03-2060.AUD	No.
								Delay(1000);
							} else {
								Actor_Says(kActorDektora, 1070, 14); //03-1070.AUD	I’m afraid that’s impossible right now.
								Actor_Says(kActorDektora, 1080, 14); //03-1080.AUD	Clovis will find you, when he’s ready.
								Delay(1000);
							}
						}
						if (!Actor_Clue_Query(kActorMcCoy, kClueClovisFlowers)) {
							Actor_Says(kActorMcCoy, 3855, 13); //00-3855.AUD	Is he the one that sent you the flowers?
							if (!Actor_Clue_Query(kActorDektora, kClueMcCoyHelpedDektora)) {
								Actor_Says(kActorDektora, 2060, 14);//03-2060.AUD	No.
								Delay(1000);
							} else {
								Actor_Says(kActorDektora, 1020, 12); //03-1020.AUD	Yes.
								Actor_Says(kActorMcCoy, 3860, 12);
								Actor_Says_With_Pause(kActorDektora, 1030, 1.0f, 14); //03-1030.AUD	We were once. But now we’ve evolved beyond that.
								Delay(1000);
							}
						}
						if (Actor_Clue_Query(kActorDektora, kClueMcCoyHelpedDektora)) {
							Actor_Says(kActorDektora, 1040, 13); //03-1040.AUD	They are still my family. Clovis and Lucy.
							Actor_Says(kActorMcCoy, 3865, 15); //00-3865.AUD	What’s Clovis looking for?
							Actor_Says_With_Pause(kActorDektora, 1050, 0.8f, 14); //03-1050.AUD	Information. Data. Four years isn’t enough time, Mr. McCoy.
							Actor_Says(kActorDektora, 1060, 13); //03-1060.AUD	If anyone deserves more than four years, it’s Clovis. If you could only meet him.
							Actor_Says(kActorMcCoy, 3870, 3); //00-3870.AUD	Can you take me to him?
							Actor_Says(kActorDektora, 1070, 14);
							Actor_Says(kActorDektora, 1080, 14);
							Delay(1000);
						} 
						Actor_Says(kActorMcCoy, 3875, 14);
						if (_vm->_cutContent) {
							if (!Actor_Clue_Query(kActorDektora, kClueMcCoyRetiredZuben)
							&& !Actor_Clue_Query(kActorDektora, kClueMcCoyRetiredLucy)
							&& !Actor_Clue_Query(kActorDektora, kClueMcCoyRetiredGordo)) {
								Actor_Says(kActorDektora, 1090, 17);     // I... appreciate it, Mr. McCoy.
							} else {
								Delay(2000);
								Actor_Says(kActorMcCoy, 1660, 15); //00-1660.AUD	Go! Quickly.
								Delay(1000);
							}
						} else {
							Actor_Says(kActorDektora, 1090, 17);     // I... appreciate it, Mr. McCoy.
						}
						Game_Flag_Set(kFlagMcCoyIsHelpingReplicants);
						Actor_Modify_Friendliness_To_Other(kActorSteele, kActorMcCoy, -2);
						Actor_Modify_Friendliness_To_Other(kActorClovis, kActorMcCoy, 2);
						Actor_Modify_Friendliness_To_Other(kActorGuzza, kActorMcCoy, -2);
						Actor_Modify_Friendliness_To_Other(kActorDektora, kActorMcCoy, 2);
						if (Actor_Query_Friendliness_To_Other(kActorDektora, kActorMcCoy) > 49
						&& Global_Variable_Query(kVariableAffectionTowards) == kAffectionTowardsNone
						&& !Actor_Clue_Query(kActorDektora, kClueMcCoyRetiredZuben)
						&& !Actor_Clue_Query(kActorDektora, kClueMcCoyRetiredLucy)
						&& !Actor_Clue_Query(kActorDektora, kClueMcCoyRetiredGordo)) {
							Global_Variable_Set(kVariableAffectionTowards, kAffectionTowardsDektora);
						}
						if (Global_Variable_Query(kVariableAffectionTowards) == kAffectionTowardsDektora) {
							Actor_Says(kActorMcCoy, 3880, -1);   // Call me Ray.
							Actor_Says(kActorDektora, 1100, 12); // Okay. Ray.
						}
					} else {
						Actor_Says(kActorDektora, 990, 13);
						Actor_Says(kActorDektora, 1000, 14);
						Loop_Actor_Walk_To_Actor(kActorDektora, kActorMcCoy, 108, false, false);
						Actor_Says(kActorMcCoy, 3845, 13);
						Actor_Says(kActorMcCoy, 3850, 15);
						Actor_Says(kActorDektora, 1010, 14);
						Actor_Says(kActorMcCoy, 3855, 13);
						Actor_Says(kActorDektora, 1020, 12);
						Actor_Says(kActorMcCoy, 3860, 12);
						Actor_Says_With_Pause(kActorDektora, 1030, 1.0f, 14);
						Actor_Says(kActorDektora, 1040, 13);
						Actor_Says(kActorMcCoy, 3865, 15);
						Actor_Says_With_Pause(kActorDektora, 1050, 0.8f, 14);
						Actor_Says(kActorDektora, 1060, 13);
						Actor_Says(kActorMcCoy, 3870, 3); //00-3870.AUD	Can you take me to him?
						Actor_Says(kActorDektora, 1070, 14);
						Actor_Modify_Friendliness_To_Other(kActorDektora, kActorMcCoy, 5);
						if (Actor_Query_Friendliness_To_Other(kActorDektora, kActorMcCoy) > 55
						&& Global_Variable_Query(kVariableAffectionTowards) == kAffectionTowardsNone
						) {
							Global_Variable_Set(kVariableAffectionTowards, kAffectionTowardsDektora);
							Actor_Says(kActorDektora, 1130, 17); 
							Actor_Says(kActorMcCoy, 6365, 12); //00-6365.AUD	Jealous, huh? On top of everything else?
							Actor_Says(kActorDektora, 1140, 14);
							Actor_Says(kActorMcCoy, 6370, 14); //00-6370.AUD	Then he’s no different from anybody else.
							Actor_Says(kActorDektora, 1150, 12);
							Actor_Says(kActorDektora, 1160, 16);
						}
						Actor_Says(kActorDektora, 1080, 13);
						Actor_Says(kActorMcCoy, 3875, 14);
						Actor_Says(kActorDektora, 1090, 17);     // I... appreciate it, Mr. McCoy.
						if (_vm->_cutContent
						&& Global_Variable_Query(kVariableAffectionTowards) == kAffectionTowardsDektora) {
							Actor_Says(kActorMcCoy, 3880, -1);   // Call me Ray.
							Actor_Says(kActorDektora, 1100, 12); // Okay. Ray.
						}
					}
					Music_Stop(4u);
					Actor_Set_Goal_Number(kActorDektora, kGoalDektoraNR11WalkAway);
#if !BLADERUNNER_ORIGINAL_BUGS
					Unclickable_Object("CLOTHING02");
					Unclickable_Object("BOX27");
					Unclickable_Object("BOX39");
					Unclickable_Object("DRESS");
					Unclickable_Object("COATRACK");
					Unclickable_Object("COLUMN3 DETS");
					Unclickable_Object("COLUMN PIPE01");
					Unclickable_Object("RECTANGLE02");
					Unclickable_Object("COLUMN04");
					Unclickable_Object("COATRACK01");
					Unclickable_Object("SHIRT");
					Unclickable_Object("SKIRT 02");
					Unclickable_Object("CLOTHING B 03");
					Unclickable_Object("BUST BUST");
#endif // !BLADERUNNER_ORIGINAL_BUGS
					if (_vm->_cutContent) {
						if (Game_Flag_Query(kFlagDektoraIsReplicant)) {
							if (Global_Variable_Query(kVariableHollowayArrest) == 1) {
								Actor_Set_Goal_Number(kActorSteele, kGoalSteeleNR10Wait);
							}
						}
					} else if (Global_Variable_Query(kVariableHollowayArrest) == 1) {
						Actor_Set_Goal_Number(kActorSteele, kGoalSteeleNR10Wait);
					}
					Game_Flag_Set(kFlagDektoraRanAway);
				}
			} else {
				// TODO why put this here? Could be a bug.
				// There's a chance that McCoy will say this while "searching" for hidden Dektora
				if (Random_Query(1, 2) == 1) {
					Actor_Says(kActorMcCoy, 8575, 14); // More useless junk.
				} else {
					Actor_Says(kActorMcCoy, 8580, 14); // Nothing else there
				}
			}
		}
		return true;
	}
	return false;
}

bool SceneScriptNR11::ClickedOnActor(int actorId) {
	return false;
}

bool SceneScriptNR11::ClickedOnItem(int itemId, bool a2) {
	return false;
}

bool SceneScriptNR11::ClickedOnExit(int exitId) {
	if (exitId == 0) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, 100.0f, 1.75f, -8.0f, 0, true, false, false)) {
			Set_Enter(kSetNR10, kSceneNR10);
			return true;
		}
	}
	return false;
}

bool SceneScriptNR11::ClickedOn2DRegion(int region) {
	return false;
}

void SceneScriptNR11::SceneFrameAdvanced(int frame) {
	//Made it so this soundtrack plays when McCoy shoots the place up.
	if (frame == 62) {
		Ambient_Sounds_Play_Sound(kSfxMCGUN1,  40, 100, 100, 10);
		if (_vm->_cutContent) {
			Music_Play(kMusicMoraji, 71, 0, 0, -1, kMusicLoopPlayOnce, 2);
		}
	}

	if (frame == 67) {
		Ambient_Sounds_Play_Sound(kSfxMCGUN1,  30,  90,  90, 10);
	}

	if (frame == 74) {
		Ambient_Sounds_Play_Sound(kSfxMCGUN2,  50,  83,  83, 10);
	}

	if (frame == 80) {
		Ambient_Sounds_Play_Sound(kSfxMCGUN1,  60,  65,  65, 10);
	}

	if (frame == 92) {
		Ambient_Sounds_Play_Sound(kSfxMCGUN2,  30,  50,  50, 10);
	}

	if (frame == 97) {
		Ambient_Sounds_Play_Sound(kSfxMCGUN1,  50, -40, -40, 10);
	}

	if (frame == 103) {
		Ambient_Sounds_Play_Sound(kSfxMCGUN2,  40, -27, -27, 10);
	}

	if (frame == 109) {
		Ambient_Sounds_Play_Sound(kSfxMCGUN1,  60, -20, -20, 10);
	}

	if (frame == 62) {
		Ambient_Sounds_Play_Sound(kSfxMTLHIT1, 80, 100, 100, 15);
	}

	if (Game_Flag_Query(kFlagNR11BreakWindow)) {
		Game_Flag_Reset(kFlagNR11BreakWindow);
		Overlay_Remove("NR11OVER");
		Overlay_Play("NR11OVER", 1, false, true, 0);
	}

	if (Game_Flag_Query(kFlagNR11SteeleShoot)) {
		untargetEverything();
		Player_Loses_Control();
		if (_vm->_cutContent) {
			if (!Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)
			&& !Actor_Clue_Query(kActorDektora, kClueMcCoyHelpedDektora)) {
				if (!Player_Query_Combat_Mode()) {
					Player_Set_Combat_Mode(true);
				}
				Actor_Set_Goal_Number(kActorMcCoy, kGoalMcCoyNR11Shoot);
			} 
		} else {
			if (!Player_Query_Combat_Mode()) {
				Player_Set_Combat_Mode(true);
			}
			Actor_Set_Goal_Number(kActorMcCoy, kGoalMcCoyNR11Shoot);
		}
		Scene_Loop_Set_Default(kNR11LoopMainLoopFires);
		Scene_Loop_Start_Special(kSceneLoopModeOnce, kNR11LoopGunshots, true);
		Game_Flag_Reset(kFlagNR11SteeleShoot);
	} else {
		if (frame < 61
		 || frame > 120
		) {
			//return false;
			return;
		}
		actorSweepArea(kActorMcCoy, frame);
		if (Actor_Query_Goal_Number(kActorSteele) == kGoalSteeleNR11Shoot) {
			actorSweepArea(kActorSteele, frame);
		}
		if (frame == 120) {
			Actor_Set_Goal_Number(kActorMcCoy, kGoalMcCoyDefault);
			Player_Gains_Control();
			if (Actor_Query_Goal_Number(kActorSteele) == kGoalSteeleNR11Shoot) {
				Actor_Set_Goal_Number(kActorSteele, kGoalSteeleNR11StopShooting);
			}
			Actor_Set_Goal_Number(kActorDektora, kGoalDektoraNR11PrepareBurning);
		}
	}
	//return true;
}

void SceneScriptNR11::ActorChangedGoal(int actorId, int newGoal, int oldGoal, bool currentSet) {
}

void SceneScriptNR11::PlayerWalkedIn() {
	if (_vm->_cutContent) {
		Music_Stop(4u);
	}
	if (Actor_Query_Goal_Number(kActorDektora) == kGoalDektoraNR11Hiding) {
		if (_vm->_cutContent) {
			if (Global_Variable_Query(kVariableHollowayArrest) == 1
			|| !Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
				Player_Set_Combat_Mode(true);
			}
		} else {
			Player_Set_Combat_Mode(true);
		}
		if (Game_Flag_Query(kFlagDektoraIsReplicant)) {
			Actor_Set_Goal_Number(kActorSteele, kGoalSteeleNR11StartWaiting);
		}
	}

	if (Game_Flag_Query(kFlagNR01DektoraFall)) {
		Game_Flag_Reset(kFlagNR01DektoraFall);
		Game_Flag_Set(kFlagNR11BurnedUp);
		Actor_Put_In_Set(kActorDektora, kSetFreeSlotI);
		Actor_Set_At_Waypoint(kActorDektora, 41, 0);
		Actor_Set_Invisible(kActorMcCoy, false);
		Player_Set_Combat_Mode(false);
		Player_Gains_Control();
		if (Game_Flag_Query(kFlagDektoraIsReplicant)) {
			if (Actor_Query_Goal_Number(kActorSteele) == kGoalSteeleNR11StopWaiting) {
				Actor_Set_At_XYZ(kActorMcCoy, -37.41f, 0.33f, -86.0f, 26);
				Delay(500);
				Actor_Face_Current_Camera(kActorMcCoy, true);
				Delay(750);
				Actor_Says(kActorMcCoy, 5290, 12); // Jesus
				Delay(1000);
				Actor_Set_Goal_Number(kActorSteele, kGoalSteeleNR11Enter);
				Actor_Face_Actor(kActorMcCoy, kActorSteele, true);
			} else {
				Actor_Set_At_XYZ(kActorMcCoy, -15.53f, 0.33f, 73.49f, 954);
				if (!_vm->_cutContent) {
					Actor_Modify_Friendliness_To_Other(kActorSteele, kActorMcCoy, 3);
				}
				Delay(1500);
				if (_vm->_cutContent) {
					if (!Game_Flag_Query(kFlagEarlyQDead)
					&& !Game_Flag_Query(kFlagNR04EarlyQStungByScorpions)) {
						Actor_Says(kActorMcCoy, 3805, 12); //00-3805.AUD	Hope Early’s got insurance.
						Actor_Face_Actor(kActorMcCoy, kActorSteele, true);
						Actor_Face_Actor(kActorSteele, kActorMcCoy, true);
						Actor_Says_With_Pause(kActorSteele, 1720, 0.3f, 16); //01-1720.AUD	Putz employs Replicants, you gotta expect the worst.
					} else {
						Actor_Face_Actor(kActorMcCoy, kActorSteele, true);
						Actor_Face_Actor(kActorSteele, kActorMcCoy, true);
					}
				} else {
					Actor_Says(kActorMcCoy, 3805, 12); //00-3805.AUD	Hope Early’s got insurance.
					Actor_Face_Actor(kActorMcCoy, kActorSteele, true);
					Actor_Face_Actor(kActorSteele, kActorMcCoy, true);
					Actor_Says_With_Pause(kActorSteele, 1720, 0.3f, 16); //01-1720.AUD	Putz employs Replicants, you gotta expect the worst.
				}
				if (_vm->_cutContent) {
					if (Player_Query_Agenda() != kPlayerAgendaPolite
					&& !Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)
					&& !Actor_Clue_Query(kActorDektora, kClueMcCoyHelpedDektora)) {
						Actor_Says(kActorMcCoy, 1570, 13); //00-1570.AUD	You sure aired that sucker out.
						Actor_Modify_Friendliness_To_Other(kActorClovis, kActorMcCoy, -2);
						Delay(500);
					} else {
						Actor_Says(kActorMcCoy, 3810, 16); //00-3810.AUD	You could have taken her out in a more discrete way.
						Actor_Modify_Friendliness_To_Other(kActorSteele, kActorMcCoy, -1);
						Actor_Modify_Friendliness_To_Other(kActorClovis, kActorMcCoy, -1);
						Actor_Modify_Friendliness_To_Other(kActorGuzza, kActorMcCoy, -1);
						if (Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) < 60) {
							Actor_Says_With_Pause(kActorSteele, 1730, 0.2f, 14); //01-1730.AUD	What’s this "her" crap? It’s an "it", remember? A goddamn machine.
						} else {
							Delay(1000);
						}
					}
				} else {
					Actor_Says(kActorMcCoy, 3810, 16); //00-3810.AUD	You could have taken her out in a more discrete way.
					Actor_Says_With_Pause(kActorSteele, 1730, 0.2f, 14); //01-1730.AUD	What’s this "her" crap? It’s an "it", remember? A goddamn machine.
				}
				Actor_Says(kActorSteele, 1740, 15); //01-1740.AUD	Come on, let’s blow while the getting's good.
				Actor_Set_Goal_Number(kActorDektora, kGoalDektoraGone);
				Actor_Put_In_Set(kActorDektora, kSetFreeSlotI);
				Actor_Set_At_Waypoint(kActorDektora, 41, 0);
				Actor_Set_Goal_Number(kActorSteele, kGoalSteeleNRxxGoToSpinner);
			}
		} else {
			if (_vm->_cutContent) {
				Delay(2000);
				Actor_Voice_Over(2100, kActorVoiceOver); //99-2100.AUD	I'd crossed the line.
				Player_Set_Combat_Mode(false);
				Delay(1000);
				Actor_Voice_Over(300, kActorVoiceOver); //99-0300.AUD	I'd screwed up. Plain and simple.
				Delay(2000);
				if (Player_Query_Agenda() == kPlayerAgendaSurly 
				|| Player_Query_Agenda() == kPlayerAgendaErratic) {
					Actor_Says(kActorMcCoy, 170, 19); //00-0170.AUD	Damn.
					Delay(2000);
					Actor_Voice_Over(2120, kActorVoiceOver); //99-2120.AUD	I didn't have a lot of time and my options were pretty lousy.
					Actor_Voice_Over(2130, kActorVoiceOver); //99-2130.AUD	Stay and face the music or take off and hope I didn't get caught.
					Game_Flag_Set(kFlagMcCoyRetiredHuman);
					Game_Flag_Reset(kFlagMcCoyIsHelpingReplicants);
					Actor_Clue_Acquire(kActorLucy, kClueMcCoyRetiredDektora, true, -1);
					Actor_Modify_Friendliness_To_Other(kActorClovis, kActorMcCoy, -2);
					Actor_Modify_Friendliness_To_Other(kActorSteele, kActorMcCoy, -2);
					Actor_Modify_Friendliness_To_Other(kActorGuzza, kActorMcCoy, -2);
				} else {
					Actor_Says(kActorMcCoy, 2305, 13); //00-2305.AUD	I’m sorry.
					Delay(2000);
					Outtake_Play(kOuttakeAway1, true, -1);
					Actor_Set_Goal_Number(kActorMcCoy, kGoalMcCoyArrested);
				}
			} else {
				Actor_Set_Goal_Number(kActorMcCoy, kGoalMcCoyArrested);
			}	
		}
	}
	// return true;
}

void SceneScriptNR11::PlayerWalkedOut() {

}

void SceneScriptNR11::DialogueQueueFlushed(int a1) {
}

void SceneScriptNR11::actorSweepArea(int actorId, signed int frame) {
	float x;
	float y;
	float z;
	float coef;

	if (frame < 80) {
		coef = (frame - 60) / 20.0f;
		x = -106.66f * coef + 126.0f;
		y = 57.79f * coef + 0.85f;
		z = 42.0f * coef + -151.0f;
	} else {
		coef = (frame - 80) / 40.0f;
		x = -97.87f * coef + -150.0f;
		y = -10.8f * coef + 52.0f;
		z = 57.0f * coef + -232.0f;
	}
	Actor_Face_XYZ(actorId, x, y, z, true);
}

void SceneScriptNR11::untargetEverything() {
	Un_Combat_Target_Object("CLOTHING02");
	Un_Combat_Target_Object("BOX27");
	Un_Combat_Target_Object("BOX39");
#if BLADERUNNER_ORIGINAL_BUGS
	// in our bugfixes this object is removed
	Un_Combat_Target_Object("BOX44");
#endif // BLADERUNNER_ORIGINAL_BUGS
	Un_Combat_Target_Object("DRESS");
	Un_Combat_Target_Object("COATRACK");
	Un_Combat_Target_Object("COLUMN3 DETS");
	Un_Combat_Target_Object("COLUMN PIPE01");
	Un_Combat_Target_Object("RECTANGLE02");
	Un_Combat_Target_Object("COLUMN04");
	Un_Combat_Target_Object("COATRACK01");
	Un_Combat_Target_Object("SHIRT");
	Un_Combat_Target_Object("SKIRT 02");
	Un_Combat_Target_Object("CLOTHING B 03");
	Un_Combat_Target_Object("BUST BUST");
}

} // End of namespace BladeRunner
