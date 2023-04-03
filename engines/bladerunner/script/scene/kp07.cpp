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

void SceneScriptKP07::InitializeScene() {
	Setup_Scene_Information(-12.0f, -41.58f, 72.0f, 0);

	Game_Flag_Reset(kFlagKP06toKP07);

	Scene_Exit_Add_2D_Exit(0, 315, 185, 381, 285, 0);

	if (Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
		if (Game_Flag_Query(kFlagDektoraIsReplicant)
		 && Actor_Query_Goal_Number(kActorDektora) < kGoalDektoraGone
		) {
#if BLADERUNNER_ORIGINAL_BUGS
#else
			if (Game_Flag_Query(kFlagNR11DektoraBurning)) {
				Game_Flag_Reset(kFlagNR11DektoraBurning); // resolves a bug of the original game, where Dektora would default to burning state
				Actor_Change_Animation_Mode(kActorDektora, kAnimationModeTalk); // dummy animation change to ensure that the next will trigger the mode change case
				Actor_Change_Animation_Mode(kActorDektora, kAnimationModeIdle);
			}
			AI_Movement_Track_Flush(kActorDektora);
			Actor_Set_Goal_Number(kActorDektora, kGoalDektoraKP07Wait); // new clear goal
#endif // BLADERUNNER_ORIGINAL_BUGS
			Actor_Set_Targetable(kActorDektora, true);
			Global_Variable_Increment(kVariableReplicantsSurvivorsAtMoonbus, 1);
			Actor_Put_In_Set(kActorDektora, kSetKP07);
			Actor_Set_At_XYZ(kActorDektora, -52.0f, -41.52f, -5.0f, 289);
		}
		// If McCoy got both Crystal and the reps to trust him Maggie will be alive and in the moonbus. The reps took her but instead wanted to take her with them along with McCoy.
		if (_vm->_cutContent) {
			if (Actor_Query_Goal_Number(kActorMaggie) < kGoalMaggieDead) {
				Actor_Put_In_Set(kActorMaggie, kSetKP07);
				Actor_Set_At_XYZ(kActorMaggie, 19.85f, -42.80f, -152.90f, 659);	
			}
		}
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagZubenIsReplicant)) {
				if (Actor_Query_Goal_Number(kActorZuben) < kGoalZubenGone) {
					AI_Movement_Track_Flush(kActorZuben);
					Actor_Set_Goal_Number(kActorZuben, kGoalZubenKP07Wait); // new clear goal
					Global_Variable_Increment(kVariableReplicantsSurvivorsAtMoonbus, 1);
					Actor_Set_Targetable(kActorZuben, true);
					Actor_Put_In_Set(kActorZuben, kSetKP07);
					Actor_Set_At_XYZ(kActorZuben, -26.0f, -41.52f, -135.0f, 0);
				}
			}
		} else {
			if (Actor_Query_Goal_Number(kActorZuben) < kGoalZubenGone) {
#if BLADERUNNER_ORIGINAL_BUGS
#else
				AI_Movement_Track_Flush(kActorZuben);
				Actor_Set_Goal_Number(kActorZuben, kGoalZubenKP07Wait); // new clear goal
#endif // BLADERUNNER_ORIGINAL_BUGS
				Global_Variable_Increment(kVariableReplicantsSurvivorsAtMoonbus, 1);
				Actor_Set_Targetable(kActorZuben, true);
				Actor_Put_In_Set(kActorZuben, kSetKP07);
				Actor_Set_At_XYZ(kActorZuben, -26.0f, -41.52f, -135.0f, 0);
			}
		}

		if (Game_Flag_Query(kFlagIzoIsReplicant)
		 && Actor_Query_Goal_Number(kActorIzo) < 599
		) {
#if BLADERUNNER_ORIGINAL_BUGS
#else
			AI_Movement_Track_Flush(kActorIzo);
			Actor_Set_Goal_Number(kActorIzo, kGoalIzoKP07Wait); // new clear goal
#endif // BLADERUNNER_ORIGINAL_BUGS
			Global_Variable_Increment(kVariableReplicantsSurvivorsAtMoonbus, 1);
			Actor_Set_Targetable(kActorIzo, true);
			Actor_Put_In_Set(kActorIzo, kSetKP07);
			Actor_Set_At_XYZ(kActorIzo, -38.0f, -41.52f, -175.0f, 500);
		}

		if (Game_Flag_Query(kFlagGordoIsReplicant)
		 && Actor_Query_Goal_Number(kActorGordo) < kGoalGordoGone
		) {
#if BLADERUNNER_ORIGINAL_BUGS
#else
			AI_Movement_Track_Flush(kActorGordo);
			Actor_Set_Goal_Number(kActorGordo, kGoalGordoKP07Wait); // new clear goal
#endif // BLADERUNNER_ORIGINAL_BUGS
			Global_Variable_Increment(kVariableReplicantsSurvivorsAtMoonbus, 1);
			Actor_Set_Targetable(kActorGordo, true);
			Actor_Put_In_Set(kActorGordo, kSetKP07);
			Actor_Set_At_XYZ(kActorGordo, 61.0f, -41.52f, -3.0f, 921);
		}

		if (Game_Flag_Query(kFlagLucyIsReplicant)
		 && Actor_Query_Goal_Number(kActorLucy) < kGoalLucyGone
		) {
#if BLADERUNNER_ORIGINAL_BUGS
#else
			AI_Movement_Track_Flush(kActorLucy);
			Actor_Set_Goal_Number(kActorLucy, kGoalLucyKP07Wait); // new clear goal
#endif // BLADERUNNER_ORIGINAL_BUGS
			Global_Variable_Increment(kVariableReplicantsSurvivorsAtMoonbus, 1);
			Actor_Put_In_Set(kActorLucy, kSetKP07);
			Actor_Set_At_XYZ(kActorLucy, 78.0f, -41.52f, -119.0f, 659);
		}
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagLutherLanceIsReplicant)) {
				if (Actor_Query_Goal_Number(kActorLuther) < kGoalLutherGone) {
					AI_Movement_Track_Flush(kActorLuther);
					Actor_Set_Goal_Number(kActorLuther, kGoalLutherKP07Wait); // new goal to avoid resuming his walking around routine
					Global_Variable_Increment(kVariableReplicantsSurvivorsAtMoonbus, 1);
					Actor_Put_In_Set(kActorLuther, kSetKP07);
					Actor_Set_At_XYZ(kActorLuther, -47.0f, 0.0f, 151.0f, 531);
				}
			} else {
				if (!Game_Flag_Query(kFlagTwinsConvinced)) {
					AI_Movement_Track_Flush(kActorLuther);
					Actor_Set_Goal_Number(kActorLuther, kGoalLutherKP07Wait); // new goal to avoid resuming his walking around routine
					Global_Variable_Increment(kVariableReplicantsSurvivorsAtMoonbus, 1);
					Actor_Put_In_Set(kActorLuther, kSetKP07);
					Actor_Set_At_XYZ(kActorLuther, -47.0f, 0.0f, 151.0f, 531);
				}
			}
		} else {
			if (Actor_Query_Goal_Number(kActorLuther) < kGoalLutherGone) {
#if BLADERUNNER_ORIGINAL_BUGS
#else
				AI_Movement_Track_Flush(kActorLuther);
				Actor_Set_Goal_Number(kActorLuther, kGoalLutherKP07Wait); // new goal to avoid resuming his walking around routine
#endif // BLADERUNNER_ORIGINAL_BUGS
				Global_Variable_Increment(kVariableReplicantsSurvivorsAtMoonbus, 1);
				Actor_Put_In_Set(kActorLuther, kSetKP07);
				Actor_Set_At_XYZ(kActorLuther, -47.0f, 0.0f, 151.0f, 531);
			}
		}
		// Made it so Bullet bob will now be in the moonbus if he is a replicant and is alive. He will be leaning against a slanted
		// wall at the front of the moobus.
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagBulletBobIsReplicant)) {
				if (Actor_Query_Goal_Number(kActorBulletBob) < kGoalBulletBobGone) {
					AI_Movement_Track_Flush(kActorBulletBob);
					Global_Variable_Increment(kVariableReplicantsSurvivorsAtMoonbus, 1);
					Actor_Set_Targetable(kActorBulletBob, true);
					Actor_Put_In_Set(kActorBulletBob, kSetKP07);
					Actor_Set_At_XYZ(kActorBulletBob, -85.71f, -41.29f, 65.11f, 240);
				}
			}
		}
		// Made it so Crazylegs appears in the moonbus if he is a replicant and is alive.
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagCrazylegsIsReplicant)) {
				if (!Game_Flag_Query(kFlagCrazylegsDead)) {
					AI_Movement_Track_Flush(kActorCrazylegs);
					Actor_Put_In_Set(kActorCrazylegs, kSetKP07);
					Actor_Set_At_XYZ(kActorCrazylegs, 34.43f, -41.62f, 13.16f, 921);
				}
			}
		}
		// Made it so Early Q appears in the moonbus if he is a replicant and is alive.
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagEarlyQIsReplicant)) {
				if (!Game_Flag_Query(kFlagEarlyQDead)
				&& !Game_Flag_Query(kFlagNR04EarlyQStungByScorpions)) {
					Global_Variable_Increment(kVariableReplicantsSurvivorsAtMoonbus, 1);
					Actor_Set_Targetable(kActorEarlyQ, true);
					Actor_Put_In_Set(kActorEarlyQ, kSetKP07);
					Actor_Set_At_XYZ(kActorEarlyQ, -59.70f, -42.72f, -150.90f, 240);
				}
			}
		}
		// Made it so Hanoi appears in the moonbus if he is a replicant and is alive.
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagHanoiIsReplicant)) {
				if (!Game_Flag_Query(kFlagHanoiDead)) {
					AI_Movement_Track_Flush(kActorHanoi);
					Global_Variable_Increment(kVariableReplicantsSurvivorsAtMoonbus, 1);
					Actor_Set_Targetable(kActorHanoi, true);
					Actor_Put_In_Set(kActorHanoi, kSetKP07);
					Actor_Set_At_XYZ(kActorHanoi, 50.69f, -41.28f, 62.09f, 0);
				}
			}
		}
		// Made it so Runciter appears in the moonbus if he is a replicant and is alive.
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagRunciterIsReplicant)) {
				if (Actor_Query_Goal_Number(kActorRunciter) < kGoalRunciterDead) {
					AI_Movement_Track_Flush(kActorRunciter);
					Actor_Set_Goal_Number(kActorRunciter, kGoalRunciterStill);
					Actor_Put_In_Set(kActorRunciter, kSetKP07);
					Actor_Set_At_XYZ(kActorRunciter, 16.95f, -42.92f, 1.50f, 0);
				}
			}
		}
		// Made it so Grigorian appears in the moonbus if he is a replicant and is alive.
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagGrigorianIsReplicant)) {
				if (!Game_Flag_Query(kFlagGrigorianDead)) {
					Actor_Put_In_Set(kActorGrigorian, kSetKP07);
					Actor_Set_At_XYZ(kActorGrigorian, -40.38f, -41.29f, 47.27f, 921);
				}
			}
		}
	}
#if BLADERUNNER_ORIGINAL_BUGS
#else
	// Additional fix for saves with bad state (goal 513) for Clovis
	// which resulted in him standing, clipping through his moonbus bed
	// when McCoy is not helping the Replicants
	else {
		// McCoy is not helping the Replicants
		if (Actor_Query_Goal_Number(kActorClovis) == kGoalClovisKP07Wait
			&& !Game_Flag_Query(kFlagClovisLyingDown)) {
			// this goal set is only for the purpose of switch Clovis goal out of kGoalClovisKP07Wait
			Actor_Set_Goal_Number(kActorClovis, kGoalClovisStartChapter5);
			// And explicitly switching back to kGoalClovisKP07Wait in order
			// to trigger the bug-fixed GoalChanged() case in his AI
			Actor_Set_Goal_Number(kActorClovis, kGoalClovisKP07Wait);
			if (Global_Variable_Query(kVariableAffectionTowards) == kAffectionTowardsDektora
			&& Actor_Query_Goal_Number(kActorDektora) < kGoalDektoraGone) {
				AI_Movement_Track_Flush(kActorDektora);
				Actor_Set_Goal_Number(kActorDektora, kGoalDektoraKP07Wait); 
				Actor_Put_In_Set(kActorDektora, kSetKP07);
				Actor_Set_At_XYZ(kActorDektora, -52.0f, -41.52f, -5.0f, 289);
			} else if (Global_Variable_Query(kVariableAffectionTowards) == kAffectionTowardsLucy
			&& Actor_Query_Goal_Number(kActorLucy) < kGoalLucyGone) {
				AI_Movement_Track_Flush(kActorLucy);
				Actor_Set_Goal_Number(kActorLucy, kGoalLucyKP07Wait); // new clear goal
				Actor_Put_In_Set(kActorLucy, kSetKP07);
				Actor_Set_At_XYZ(kActorLucy, 78.0f, -41.52f, -119.0f, 659);
			}
		}
	}
#endif // BLADERUNNER_ORIGINAL_BUGS

	Ambient_Sounds_Add_Looping_Sound(kSfxCOMPBED1,  7, 1, 1);
	Ambient_Sounds_Add_Looping_Sound(kSfxMOONBED2, 52, 1, 1);
	Ambient_Sounds_Add_Looping_Sound(kSfxBRBED3,   38, 1, 1);

	if (Game_Flag_Query(kFlagKP07BusActive)) {
		Scene_Loop_Set_Default(2);
	} else {
		Scene_Loop_Set_Default(0);
	}
}

void SceneScriptKP07::SceneLoaded() {
	// Added the Clovis incept photo into the scene.
	if (_vm->_cutContent 
	&& !Actor_Clue_Query(kActorMcCoy, kClueClovisIncept)) {
		Item_Add_To_World(kItemPhoto, kModelAnimationPhoto, kSetKP07, 78.84, -41.37, -116.75, 0, 12, 12, false, true, false, true);
	}
	if (!Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
		Music_Play(kMusicClovDie1, 25, 0, 0, -1, kMusicLoopRepeat, 0);
	}
	Obstacle_Object("BUNK_TRAY01", true);
	Unobstacle_Object("BUNK_TRAY01", true);
	if (Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
		Player_Set_Combat_Mode(false);
		Scene_Exits_Disable();
	}
}

bool SceneScriptKP07::MouseClick(int x, int y) {
	return false;
}

bool SceneScriptKP07::ClickedOn3DObject(const char *objectName, bool a2) {
	return false;
}

bool SceneScriptKP07::ClickedOnActor(int actorId) {
	if (actorId == kActorClovis) {
#if BLADERUNNER_ORIGINAL_BUGS
#else
		Actor_Face_Actor(kActorMcCoy, kActorClovis, true);
#endif // BLADERUNNER_ORIGINAL_BUGS
		if (!Game_Flag_Query(kFlagKP07McCoyPulledGun)
		 &&  Actor_Query_Goal_Number(kActorClovis) != kGoalClovisGone
		 &&  Actor_Query_Goal_Number(kActorClovis) != kGoalClovisKP07SayFinalWords
		) {
			if (Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
				Actor_Set_Goal_Number(kActorClovis, kGoalClovisKP07FlyAway);
			} else {
				Music_Play(kMusicClovDies, 31, 0, 0, -1, kMusicLoopRepeat, 0);
				Actor_Set_Goal_Number(kActorClovis, kGoalClovisKP07TalkToMcCoy);
			}
			return true;
		}
		#if BLADERUNNER_ORIGINAL_BUGS
		Actor_Face_Actor(kActorMcCoy, actorId, true);
		Actor_Says(kActorMcCoy, 8590, 14);
		return true;
	#else
		if (!_vm->_cutContent) {
			if (!Player_Query_Combat_Mode()) {
				Actor_Face_Actor(kActorMcCoy, actorId, true);
				Actor_Says(kActorMcCoy, 8590, 14);
				return true;
			}
#endif // BLADERUNNER_ORIGINAL_BUGS
		}
	}
	return false;
}

bool SceneScriptKP07::ClickedOnItem(int itemId, bool a2) {
	// Code for picking up the Clovis incept photo.
	if (_vm->_cutContent) {
		if (itemId ==  kItemPhoto) {
			if (!Loop_Actor_Walk_To_Item(kActorMcCoy,  kItemPhoto, 12, true, false)) {
				Actor_Face_Item(kActorMcCoy,  kItemPhoto, true);
				Actor_Clue_Acquire(kActorMcCoy, kClueClovisIncept, true, kActorClovis);
				Item_Pickup_Spin_Effect(kModelAnimationPhoto, 83, 390);
				Item_Remove_From_World(kItemPhoto);
				return true;	
			}	
		}	
	}
	return false;
}

bool SceneScriptKP07::ClickedOnExit(int exitId) {
	if (exitId == 0) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -12.0f, -41.58f, 72.0f, 0, true, false, false)) {
			Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
			Ambient_Sounds_Remove_All_Looping_Sounds(1u);
			Game_Flag_Set(kFlagKP07toKP06);
			Set_Enter(kSetKP05_KP06, kSceneKP06);
		}
		return true;
	}
	return false;
}

bool SceneScriptKP07::ClickedOn2DRegion(int region) {
	return false;
}

void SceneScriptKP07::SceneFrameAdvanced(int frame) {
}

void SceneScriptKP07::ActorChangedGoal(int actorId, int newGoal, int oldGoal, bool currentSet) {
}

void SceneScriptKP07::PlayerWalkedIn() {
	Loop_Actor_Walk_To_XYZ(kActorMcCoy, 9.0f, -41.88f, -81.0f, 0, false, false, false);
	if (!Game_Flag_Query(kFlagKP07Entered)) {
		if (Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
			if (_vm->_cutContent) {
				Player_Set_Combat_Mode(false);
				Music_Stop(1u);
				Music_Play(kMusicBRBlues, 52, 0, 3, -1, kMusicLoopPlayOnceRandomStart, 0);
			}	
			// If Maggie is alive and in the set McCoy will call her and Maggie will look at him.
			if (_vm->_cutContent) {
				if (Actor_Query_Is_In_Current_Set(kActorMaggie)) {
					Actor_Face_Actor(kActorMcCoy, kActorMaggie, true);
					Actor_Face_Actor(kActorMaggie, kActorMcCoy, true);
					Actor_Says(kActorMcCoy, 2395, 18); //00-2395.AUD	Hey, Maggie!
				}
			}
			// Added in some dialogue for McCoy, Lucy and Dektora. If McCoy enters the moonbus and is helping the replicants and has an affection rating
			// towards either Dektora or Lucy the will say I told you he'd come and McCoy will say I promised you didn't I.
			if (_vm->_cutContent) {
				if (Actor_Query_Is_In_Current_Set(kActorDektora) 
				&& Global_Variable_Query(kVariableAffectionTowards) ==  kAffectionTowardsDektora) {
					Actor_Face_Actor(kActorDektora, kActorClovis, true);
					Actor_Face_Actor(kActorClovis, kActorDektora, true);
					Actor_Face_Actor(kActorMcCoy, kActorDektora, true);
					Actor_Says(kActorDektora, 2650, 3); //03-2650.AUD	I told you he’d come!
					Actor_Face_Actor(kActorDektora, kActorMcCoy, true);
					Actor_Face_Actor(kActorClovis, kActorMcCoy, true);
					Actor_Says(kActorMcCoy, 1400, kAnimationModeTalk); //00-1400.AUD	I promised you, didn't I?
					Delay (1000);
					Actor_Face_Actor(kActorDektora, kActorClovis, true);
				}
				if (Actor_Query_Is_In_Current_Set(kActorLucy)
				&& Global_Variable_Query(kVariableAffectionTowards) == kAffectionTowardsLucy) {
					Actor_Face_Actor(kActorLucy, kActorClovis, true);
					Actor_Face_Actor(kActorMcCoy, kActorLucy, true);
					Actor_Face_Actor(kActorClovis, kActorLucy, true);
					Actor_Says(kActorLucy, 3040, 3); //06-3040.AUD	I told you he’d come!
					Actor_Face_Actor(kActorLucy, kActorMcCoy, true);
					Actor_Face_Actor(kActorClovis, kActorMcCoy, true);
					Actor_Says(kActorMcCoy, 1425, kAnimationModeTalk); //00-1425.AUD	I promised you, didn't I?
					Delay (1000);
					Actor_Face_Actor(kActorLucy, kActorClovis, true);
				}
			}
			Actor_Face_Actor(kActorMcCoy, kActorClovis, true);
			if (_vm->_cutContent) {
				if (Actor_Query_Friendliness_To_Other(kActorClovis, kActorMcCoy) < 51
				|| Game_Flag_Query(kFlagMcCoyRetiredReplicant)) {
					Actor_Face_Actor(kActorClovis, kActorMcCoy, true);
					Actor_Says(kActorClovis, 160, 3); //05-0160.AUD	I’ve been expecting you.
					Actor_Says(kActorMcCoy, 2130, 14); //00-2130.AUD	You’re the coldest person I’ve ever seen when it comes to killing.
					Delay(1000);
					Actor_Says(kActorClovis, 190, 3); //05-0190.AUD	And what about you, Ray McCoy?(coughs) After what you did to my family.
					Actor_Says(kActorClovis, 200, kAnimationModeTalk); //05-0200.AUD	To my friends. Do you not also seek forgiveness?
					if (Player_Query_Agenda() == kPlayerAgendaSurly 
					&& Player_Query_Agenda() == kPlayerAgendaErratic) {
						Music_Stop(1u);
						Delay(1000);
						Actor_Says(kActorMcCoy, 2360, 18); //00-2360.AUD	I don’t need to.
						Delay(1000);
						Actor_Says(kActorMcCoy, 5150, 18); //00-5150.AUD	One more thing.
						Delay(500);
						Actor_Says(kActorMcCoy, 6180, 14); //00-6180.AUD	Your breath smells like you wiped your ass with your teeth..
						Actor_Says(kActorClovis, 10, 3); //05-0010.AUD	Enough!
						Game_Flag_Set(kFlagKP07BusActive);
						if (Game_Flag_Query(kFlagSadikIsReplicant)) {
							if (Actor_Query_Goal_Number(kActorSadik) == kGoalSadikKP06NeedsReactorCoreFromMcCoy) {
								Actor_Put_In_Set(kActorSadik, kSetKP07);
								Global_Variable_Increment(kVariableReplicantsSurvivorsAtMoonbus, 1);
								Actor_Set_At_XYZ(kActorSadik, -12.0f, -41.58f, 72.0f, 0);
								Actor_Face_Actor(kActorSadik, kActorClovis, true);
								// Made it so Sadik is now targetable when he enters the moonbus.
								Actor_Set_Targetable(kActorSadik, true);
							}
						}
						Player_Set_Combat_Mode(true);
						Actor_Set_Goal_Number(kActorClovis, kGoalClovisKP07ReplicantsAttackMcCoy);
						Game_Flag_Set(kFlagKP07ReplicantsAttackMcCoy);
						Music_Play(kMusicMoraji, 71, 0, 0, -1, kMusicLoopPlayOnce, 2);
						Player_Gains_Control();
					} else {	
						Delay (2000);
						Actor_Says(kActorMcCoy, 2305, 17); //00-2305.AUD	I’m sorry.
						Delay (2000);
						Actor_Says(kActorClovis, 1280, kAnimationModeTalk); //05-1280.AUD	You are here. That’s enough for 
						Delay (1000);
						Actor_Says(kActorMcCoy, 8500, 3);
						Actor_Says(kActorClovis, 1250, 3);
						Game_Flag_Set(kFlagKP07BusActive);
						if (Game_Flag_Query(kFlagSadikIsReplicant)) {
							if (Actor_Query_Goal_Number(kActorSadik) == kGoalSadikKP06NeedsReactorCoreFromMcCoy) {
								Actor_Put_In_Set(kActorSadik, kSetKP07);
								Global_Variable_Increment(kVariableReplicantsSurvivorsAtMoonbus, 1);
								Actor_Set_At_XYZ(kActorSadik, -12.0f, -41.58f, 72.0f, 0);
								Actor_Face_Actor(kActorSadik, kActorClovis, true);
								// Made it so Sadik is now targetable when he enters the moonbus.
								Actor_Set_Targetable(kActorSadik, true);
							}
						}
					}
				} else {
					Actor_Face_Actor(kActorClovis, kActorMcCoy, true);
					Actor_Says(kActorClovis, 1240, 3); //05-1240.AUD	Welcome, brother. We have very little time.
					Actor_Says(kActorMcCoy, 8500, 13);
					Actor_Says(kActorClovis, 1250, 3);
					Game_Flag_Set(kFlagKP07BusActive);
					if (Game_Flag_Query(kFlagSadikIsReplicant)) {
						if (Actor_Query_Goal_Number(kActorSadik) == kGoalSadikKP06NeedsReactorCoreFromMcCoy) {
							Actor_Put_In_Set(kActorSadik, kSetKP07);
							Global_Variable_Increment(kVariableReplicantsSurvivorsAtMoonbus, 1);
							Actor_Set_At_XYZ(kActorSadik, -12.0f, -41.58f, 72.0f, 0);
							Actor_Face_Actor(kActorSadik, kActorClovis, true);
							// Made it so Sadik is now targetable when he enters the moonbus.
							Actor_Set_Targetable(kActorSadik, true);
						}
					}
				}
			} else {
				Actor_Says(kActorClovis, 1240, 3); //05-1240.AUD	Welcome, brother. We have very little time.
				Actor_Says(kActorMcCoy, 8500, 3);
				Actor_Says(kActorClovis, 1250, 3);
				if (Actor_Query_Goal_Number(kActorSadik) == kGoalSadikKP06NeedsReactorCoreFromMcCoy) {
					Actor_Put_In_Set(kActorSadik, kSetKP07);
					Global_Variable_Increment(kVariableReplicantsSurvivorsAtMoonbus, 1);
					Actor_Set_At_XYZ(kActorSadik, -12.0f, -41.58f, 72.0f, 0);
					Actor_Face_Actor(kActorSadik, kActorClovis, true);
					// Made it so Sadik is now targetable when he enters the moonbus.
					Actor_Set_Targetable(kActorSadik, true);
				}
			}			
		} else {
			if (_vm->_cutContent) {
				if (Actor_Query_Is_In_Current_Set(kActorDektora)) {
					Actor_Face_Actor(kActorMcCoy, kActorDektora, true);
					Actor_Face_Actor(kActorDektora, kActorMcCoy, true);
					Delay(1000);
					Actor_Says(kActorMcCoy, 7960, 13); //00-7960.AUD	Dektora?
					Actor_Says(kActorDektora, 1480, kAnimationModeTalk); //03-1480.AUD	Yes.
					Delay(1000);
					Actor_Says(kActorMcCoy, 6610, 14); //00-6610.AUD	Been messing with peoples’ lives lately?
					Delay(2000);
					Actor_Says(kActorMcCoy, 8395, 18); //00-8395.AUD	You don't have anything to say?
					Delay(1000);
					Actor_Says_With_Pause(kActorDektora, 910, 1.0f, 30);
					Actor_Says(kActorMcCoy, 2660, 18); //00-2660.AUD	That breaks my heart.
					Delay(2000);
					Actor_Says(kActorMcCoy, 1655, 14); //0-1655.AUD	You’ve got to get out of here.
					Actor_Says(kActorDektora, 90, kAnimationModeTalk); //03-0090.AUD	Ray!?
					Actor_Says(kActorMcCoy, 1660, 15); //00-1660.AUD	Go! Quickly.
					Delay(1000);
					Actor_Says(kActorMcCoy, 1805, 14); //00-1805.AUD	Now!
					Loop_Actor_Walk_To_XYZ(kActorDektora, -102.0f, -73.5f, -233.0f, 0, false, true, false);
					Actor_Put_In_Set(kActorDektora, kSceneKP06);
				} else if (Actor_Query_Is_In_Current_Set(kActorLucy)) {
					Actor_Face_Actor(kActorMcCoy, kActorLucy, true);
					Actor_Face_Actor(kActorLucy, kActorMcCoy, true);
					Delay(1000);
					Actor_Says(kActorMcCoy, 1600, 11); //00-1600.AUD	Lucy? 
					if (Game_Flag_Query(kFlagLucyIsReplicant)) {
						Actor_Says(kActorLucy, 90, 13); //06-0090.AUD	Leave me alone.		
					} else {
						Actor_Says(kActorLucy, 110, 13); //06-0110.AUD	Please, leave me alone.
					}
					Delay(1000);
					Actor_Says(kActorMcCoy, 6610, 14); //00-6610.AUD	Been messing with peoples’ lives lately?
					Delay(2000);
					Actor_Says(kActorMcCoy, 8395, 18); //00-8395.AUD	You don't have anything to say?
					Delay(1000);
					Actor_Says(kActorLucy, 2190, 13); //06-2190.AUD	You're cruel.
					Actor_Says(kActorMcCoy, 4880, 13); //00-4880.AUD	Is that right?
					Delay(2000);
					Actor_Says(kActorMcCoy, 1655, 14); //0-1655.AUD	You’ve got to get out of here.
					Actor_Says(kActorLucy, 380, 13); //06-0380.AUD	Ray.
					Actor_Says(kActorMcCoy, 1660, 15); //00-1660.AUD	Go! Quickly.
					Delay(1000);
					Actor_Says(kActorMcCoy, 1805, 14); //00-1805.AUD	Now!
					Loop_Actor_Walk_To_XYZ(kActorLucy, -102.0f, -73.5f, -233.0f, 0, false, true, false);
					Actor_Put_In_Set(kActorLucy, kSceneKP06);
				}
				Actor_Face_Actor(kActorMcCoy, kActorClovis, true);
				if (Game_Flag_Query(kFlagSadikIsReplicant)
				&& Actor_Clue_Query(kActorMcCoy, kClueMcCoyRetiredSadik)) {
					Actor_Says(kActorClovis, 160, 3); //05-0160.AUD	I’ve been expecting you.
				}
			} else {
				Actor_Says(kActorClovis, 160, 3);
			}
			if (_vm->_cutContent) {
				Actor_Set_Goal_Number(kActorMaggie, kGoalMaggieDead);
				if (Player_Query_Agenda() != kPlayerAgendaSurly 
				&& Player_Query_Agenda() != kPlayerAgendaErratic) {
					Player_Set_Combat_Mode(false);
				}
			}
			Actor_Retired_Here(kActorClovis, 72, 60, 0, -1);
		}
		Game_Flag_Set(kFlagKP07Entered);
	}
}

void SceneScriptKP07::PlayerWalkedOut() {
	Music_Stop(3u);
}

void SceneScriptKP07::DialogueQueueFlushed(int a1) {
	// Made sure that this code only plays in the origianl mode since it interferes with the scene where Clovis shoots McCoy by making
	// Clovis die before he has a chance to shoot.
	if (!_vm->_cutContent) {
		if (Actor_Query_Goal_Number(kActorClovis) == kGoalClovisKP07SayFinalWords) {
			Actor_Set_Targetable(kActorClovis, false);
			Actor_Change_Animation_Mode(kActorClovis, kAnimationModeHit);
			Actor_Retired_Here(kActorClovis, 12, 48, true, -1);
			Actor_Set_Goal_Number(kActorClovis, kGoalClovisGone);
		}
	}
}

} // End of namespace BladeRunner
