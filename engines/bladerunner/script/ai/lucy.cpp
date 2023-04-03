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

#include "bladerunner/script/ai_script.h"

namespace BladeRunner {

enum kLucyStates {
	kLucyStateIdle            = 0,
	kLucyStateWalking         = 1,
	kLucyStateRunning         = 2,
	kLucyStateClimbStairsUp   = 3,
	kLucyStateClimbStairsDown = 4,
	kLucyStateGotShotA        = 5,
	kLucyStateGotShotB        = 6,
	kLucyStateDie             = 7
	// TODO fill in the rest of the animationStates
};

AIScriptLucy::AIScriptLucy(BladeRunnerEngine *vm) : AIScriptBase(vm) {
	_resumeIdleAfterFramesetCompletesFlag = false;
}

void AIScriptLucy::Initialize() {
	_animationFrame = 0;
	_animationState = 0;
	_animationStateNext = 0;
	_animationNext = 0;

	_resumeIdleAfterFramesetCompletesFlag = false;

	Actor_Set_Goal_Number(kActorLucy, kGoalLucyDefault);
}

bool AIScriptLucy::Update() {
	float x, y, z;

	if (Global_Variable_Query(kVariableChapter) == 3
	 && Actor_Query_Goal_Number(kActorLucy) < kGoalLucyMoveAround
	) {
		Actor_Set_Goal_Number(kActorLucy, kGoalLucyMoveAround);
	}

	if (Actor_Query_Goal_Number(kActorLucy) == kGoalLucyHF04Start
	 && Player_Query_Current_Scene() == kSceneHF04
	) {
		Actor_Set_Goal_Number(kActorLucy, kGoalLucyHF04Run1);
	}

	if (Global_Variable_Query(kVariableChapter) == 4
	 && Actor_Query_Goal_Number(kActorLucy) < kGoalLucyStartChapter4
	) {
		Actor_Set_Goal_Number(kActorLucy, kGoalLucyStartChapter4);
	}

	if (Global_Variable_Query(kVariableChapter) == 4
	 && Actor_Query_Goal_Number(kActorLucy) == kGoalLucyGone
	 && Actor_Query_Which_Set_In(kActorLucy) != kSetFreeSlotI
	) {
		if (Actor_Query_Which_Set_In(kActorLucy) != Player_Query_Current_Set()) {
			Actor_Put_In_Set(kActorLucy, kSetFreeSlotI);
			Actor_Set_At_Waypoint(kActorLucy, 41, 0);
		}
	}

	if (Game_Flag_Query(kFlagMcCoyCapturedByHolloway)
	 && Actor_Query_Goal_Number(kActorLucy) == kGoalLucyWillReturnToHF03
	) {
		Actor_Put_In_Set(kActorLucy, kSetHF03);
		Actor_Set_At_Waypoint(kActorLucy, 371, 156);
		Actor_Set_Goal_Number(kActorLucy, kGoalLucyReturnToHF03);
	}

	if ( Actor_Query_Goal_Number(kActorLucy) > 229
	 &&  Actor_Query_Goal_Number(kActorLucy) < 239
	 &&  Actor_Query_Goal_Number(kActorLucy) != kGoalLucyHF04TalkToMcCoy
	 &&  Player_Query_Current_Scene() == kSceneHF04
	 &&  Actor_Query_Which_Set_In(kActorLucy) == kSetHF04
	 && !Game_Flag_Query(kFlagMcCoyAttackedLucy)
	 &&  Actor_Query_Inch_Distance_From_Actor(kActorLucy, kActorMcCoy) < 84
	 && !Player_Query_Combat_Mode()
	 &&  Actor_Query_Friendliness_To_Other(kActorLucy, kActorMcCoy) > 40
	) {
		Actor_Set_Goal_Number(kActorLucy, kGoalLucyHF04TalkToMcCoy); // TODO how can this be triggered?
	}

	if (Actor_Query_Goal_Number(kActorLucy) == kGoalLucyHF04WaitForMcCoy1) {
		Actor_Query_XYZ(kActorMcCoy, &x, &y, &z);
		if (z < -875.0f) {
			Game_Flag_Set(kFlagHF04OpenDoors);
			Actor_Set_Goal_Number(kActorLucy, kGoalLucyHF04Run3);
		}
	}

	if (Actor_Query_Goal_Number(kActorLucy) == kGoalLucyHF04WaitForMcCoy2) {
		Actor_Query_XYZ(kActorMcCoy, &x, &y, &z);
		if (x > 350.0f) {
			Game_Flag_Set(kFlagHF04CloseDoors);
			Actor_Set_Goal_Number(kActorLucy, kGoalLucyHF04Run4);
		}
	}

	return false;
}

void AIScriptLucy::TimerExpired(int timer) {
	if (timer == kActorTimerAIScriptCustomTask0) { // rephrased this to be more expandable (if required)
		AI_Countdown_Timer_Reset(kActorLucy, kActorTimerAIScriptCustomTask0);
		if (Actor_Query_Goal_Number(kActorLucy) == kGoalLucyGoToHF03) {
			if (Player_Query_Current_Scene() == kSceneHF03) {
				AI_Countdown_Timer_Start(kActorLucy, kActorTimerAIScriptCustomTask0, 20);
			} else {
				Actor_Set_Goal_Number(kActorLucy, kGoalLucyMoveAround);
			}
		}
	}
}

void AIScriptLucy::CompletedMovementTrack() {
	switch (Actor_Query_Goal_Number(kActorLucy)) {
	case kGoalLucyGoToHF03:
		if (Game_Flag_Query(kFlagMcCoyCapturedByHolloway)
		 && Global_Variable_Query(kVariableHollowayArrest) == 3
		) {
			Actor_Set_Goal_Number(kActorLucy, kGoalLucyReturnToHF03);
			return; //true;
		}
		AI_Countdown_Timer_Reset(kActorLucy, kActorTimerAIScriptCustomTask0);
		AI_Countdown_Timer_Start(kActorLucy, kActorTimerAIScriptCustomTask0, 30);
		break;

	case kGoalLucyHF03RunOutPhase1:
		Actor_Set_Goal_Number(kActorLucy, kGoalLucyHF03RunOutPhase2);
		break;

	case kGoalLucyHF03RunOutPhase2:
		Game_Flag_Set(kFlagLucyRanAway);
		Actor_Set_Goal_Number(kActorLucy, kGoalLucyHF03RanAway);
		break;

	case kGoalLucyHF03RunToHF041:
		Actor_Set_Goal_Number(kActorLucy, kGoalLucyHF03RunToHF042);
		break;

	case kGoalLucyHF03RunToHF042:
		if (Actor_Clue_Query(kActorLucy, kClueMcCoyHelpedLucy)
		 && Global_Variable_Query(kVariableHollowayArrest) != 3
		) {
			Game_Flag_Set(kFlagLucyRanAway);
		} else {
			Actor_Set_Goal_Number(kActorLucy, kGoalLucyHF04Start);
			Game_Flag_Reset(kFlagHF04DoorsClosed);
		}
		break;

	case kGoalLucyHF03RunAwayWithHelp1:
		Actor_Set_Goal_Number(kActorLucy, kGoalLucyHF03RunAwayWithHelp2);
		break;

	case kGoalLucyHF03RunAwayWithHelp2:
		Actor_Set_Goal_Number(kActorLucy, kGoalLucyWillReturnToHF03);
		break;

	case kGoalLucyGoToFreeSlotGAG:
		// fall through
	case kGoalLucyGoToFreeSlotGAHJ:
		Actor_Set_Goal_Number(kActorLucy, kGoalLucyMoveAround);
		break;

	case kGoalLucyHF04Run1:
		Game_Flag_Set(kFlagHF04CloseDoors);
		Actor_Set_Goal_Number(kActorLucy, kGoalLucyHF04Run2);
		break;

	case kGoalLucyHF04Run2:
		Actor_Set_Goal_Number(kActorLucy, kGoalLucyHF04WaitForMcCoy1);
		break;

	case kGoalLucyHF04Run3:
		Actor_Set_Goal_Number(kActorLucy, kGoalLucyHF04WaitForMcCoy2);
		break;

	case kGoalLucyHF04Run4:
		Game_Flag_Set(kFlagLucyRanAway);
		Actor_Put_In_Set(kActorLucy, kSetFreeSlotA);
		Actor_Set_At_Waypoint(kActorLucy, 33, 0);
		Actor_Set_Health(kActorLucy, 30, 30);

		if (Global_Variable_Query(kVariableHollowayArrest) == 3) {
			Actor_Set_Goal_Number(kActorSteele, kGoalSteeleHF02ConfrontLucy);
		}
		break;

	case kGoalLucyHF04WalkAway:
		Game_Flag_Set(kFlagLucyRanAway);
		break;

	default:
		break;
	}
	return; //false;
}

void AIScriptLucy::ReceivedClue(int clueId, int fromActorId) {
	//return false;
}

void AIScriptLucy::ClickedByPlayer() {
	if (_vm->_cutContent) {
		if (Actor_Query_In_Set(kActorLucy, kSetKP07)) {
			if (Actor_Query_Goal_Number(kActorLucy) < kGoalLucyGone) {
				Loop_Actor_Walk_To_Actor(kActorMcCoy, kActorLucy, 24, false, false);
				Actor_Face_Actor(kActorMcCoy, kActorLucy, true);
				Actor_Face_Actor(kActorLucy, kActorMcCoy, true);
				Actor_Says(kActorMcCoy, 4775, kAnimationModeTalk); //00-4775.AUD	Lucy.
				Actor_Says(kActorLucy, 0, 17); //06-0000.AUD	I knew you’d come.
				if (Player_Query_Agenda() != kPlayerAgendaSurly 
				&& Player_Query_Agenda() != kPlayerAgendaErratic) {
					if (Actor_Clue_Query(kActorMcCoy, kClueToyDog)
					|| Actor_Clue_Query(kActorMcCoy, kClueRagDoll)
					|| Actor_Clue_Query(kActorMcCoy, kClueCandy)
					|| Actor_Clue_Query(kActorMcCoy, kClueHysteriaToken)) {
						Actor_Says(kActorMcCoy, 5150, 18); //00-5150.AUD	One more thing.	
						Actor_Change_Animation_Mode(kActorMcCoy, 23);
						Actor_Change_Animation_Mode(kActorLucy, 23);
						Delay(800);
						if (Actor_Clue_Query(kActorMcCoy, kClueToyDog)) {
							Actor_Clue_Lose(kActorMcCoy, kClueToyDog);
							Actor_Clue_Acquire(kActorLucy, kClueToyDog, true, -1);
							Item_Pickup_Spin_Effect_From_Actor(kModelAnimationToyDog, kActorLucy, 0, 0);
							Delay(1500);
						}
						if (Actor_Clue_Query(kActorMcCoy, kClueRagDoll)) {
							Actor_Clue_Lose(kActorMcCoy, kClueRagDoll);
							Actor_Clue_Acquire(kActorLucy, kClueRagDoll, true, -1);
							Item_Pickup_Spin_Effect_From_Actor(kModelAnimationRagDoll, kActorLucy, 0, 0);
							Delay(1500);
						}
						if (Actor_Clue_Query(kActorMcCoy, kClueCandy)) {
							Actor_Clue_Lose(kActorMcCoy, kClueCandy);
							Actor_Clue_Acquire(kActorLucy, kClueCandy, true, -1);
							Item_Pickup_Spin_Effect_From_Actor(kModelAnimationCandy, kActorLucy, 0, 0);
							Delay(1500);
						}
						if (Actor_Clue_Query(kActorMcCoy, kClueHysteriaToken)) {
							Actor_Clue_Lose(kActorMcCoy, kClueHysteriaToken);
							Actor_Clue_Acquire(kActorLucy, kClueHysteriaToken, true, -1);
							Item_Pickup_Spin_Effect_From_Actor(kModelAnimationHysteriaToken, kActorLucy, 0, 0);
							Delay(1500);
						}
						Actor_Says(kActorMcCoy, 8170, 13); //00-8170.AUD	There you go.
						Actor_Says(kActorLucy, 230, 14); //06-0230.AUD	Thank you.
					}
				}
			}
		}
	}
	if (Actor_Query_Goal_Number(kActorLucy) == kGoalLucyGone) {
		Actor_Face_Actor(kActorMcCoy, kActorLucy, true);
		if (_vm->_cutContent) {
			if (Player_Query_Agenda() == kPlayerAgendaSurly 
			|| Player_Query_Agenda() == kPlayerAgendaErratic) {
				Actor_Says(kActorMcCoy, 8665, 13); //00-8665.AUD	Disgusting.	
			} else { 	
				Actor_Says(kActorMcCoy, 8630, 12);  // What a waste
			}
		} else {
			Actor_Says(kActorMcCoy, 8665, 14);
		}
	}
}

void AIScriptLucy::EnteredSet(int setId) {
	// return false;
}

void AIScriptLucy::OtherAgentEnteredThisSet(int otherActorId) {
	// return false;
}

void AIScriptLucy::OtherAgentExitedThisSet(int otherActorId) {
	// return false;
}

void AIScriptLucy::OtherAgentEnteredCombatMode(int otherActorId, int combatMode) {
	// return false;
}

void AIScriptLucy::ShotAtAndMissed() {
	checkCombat();
}

bool AIScriptLucy::ShotAtAndHit() {
	checkCombat();

	return false;
}

void AIScriptLucy::Retired(int byActorId) {

#if BLADERUNNER_ORIGINAL_BUGS
#else
	if (Actor_Query_In_Set(kActorLucy, kSetKP07)) {
		Global_Variable_Decrement(kVariableReplicantsSurvivorsAtMoonbus, 1);
		Actor_Set_Goal_Number(kActorLucy, kGoalLucyGone);
		if (_vm->_cutContent) {
			Actor_Modify_Friendliness_To_Other(kActorSteele, kActorMcCoy, 2);
			Game_Flag_Reset(kFlagMcCoyIsHelpingReplicants);
			if (Query_Difficulty_Level() != kGameDifficultyEasy) {
				Global_Variable_Increment (kVariableChinyen, 200);
			}
			Actor_Modify_Friendliness_To_Other(kActorGaff, kActorMcCoy, 2);
		}

		if (Global_Variable_Query(kVariableReplicantsSurvivorsAtMoonbus) == 0) {
			Player_Loses_Control();
			// Made it so if Crazylegs is in the moonbus, after all the reps are retired he flees and is never seen again.
			// This was done because he has no death animation so this seemed to be a reasonable solution.
			if (_vm->_cutContent) {
				if (Actor_Query_In_Set(kActorRunciter, kSetKP07)) {
					Loop_Actor_Walk_To_XYZ(kActorRunciter, -12.0f, -41.58f, 72.0f, 0, true, false, false);
					Actor_Put_In_Set(kActorRunciter, kSceneKP06);
				}
				if (Actor_Query_In_Set(kActorCrazylegs, kSetKP07)) {
					Loop_Actor_Walk_To_XYZ(kActorCrazylegs, -12.0f, -41.58f, 72.0f, 0, true, false, false);
					Actor_Put_In_Set(kActorCrazylegs, kSceneKP06);	
				}
				if (Actor_Query_In_Set(kActorGrigorian, kSetKP07)) {
					Actor_Face_Heading(kActorGrigorian, 900, false);
					Delay(1000);
					Actor_Put_In_Set(kActorGrigorian, kSceneKP06);
				}
				if (Game_Flag_Query(kFlagRunciterIsReplicant)) {
					if (Actor_Query_Goal_Number(kActorRunciter) < kGoalRunciterDead) {
						Delay(1000);
						Sound_Play(kSfxSMCAL3, 100, 0, 0, 50);
						Actor_Set_Goal_Number(kActorRunciter, kGoalRunciterDead);
					}
				}
				if (Game_Flag_Query(kFlagCrazylegsIsReplicant)) {
					if (!Game_Flag_Query(kFlagCrazylegsDead)) {
						Delay(1000);
						Sound_Play(kSfxSMCAL3, 100, 0, 0, 50);
						Game_Flag_Set(kFlagCrazylegsDead);
					}
				}
				if (Game_Flag_Query(kFlagGrigorianIsReplicant)) {
					if (!Game_Flag_Query(kFlagGrigorianDead)) {
						Delay(1000);
						Sound_Play(kSfxSMCAL3, 100, 0, 0, 50);
						Game_Flag_Set(kFlagGrigorianDead);
					}
				}
				Delay(2000);
				Player_Set_Combat_Mode(false);
				Delay(2000);  
				Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
				Ambient_Sounds_Remove_All_Looping_Sounds(1u);
				Game_Flag_Set(kFlagKP07toKP06);
				Game_Flag_Reset(kFlagMcCoyIsHelpingReplicants);
				Set_Enter(kSetKP05_KP06, kSceneKP06);
			} else {
				Delay(2000);
				Player_Set_Combat_Mode(false);
				Loop_Actor_Walk_To_XYZ(kActorMcCoy, -12.0f, -41.58f, 72.0f, 0, true, false, false);
				Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
				Ambient_Sounds_Remove_All_Looping_Sounds(1u);
				Game_Flag_Set(kFlagKP07toKP06);
				Game_Flag_Reset(kFlagMcCoyIsHelpingReplicants);
				Set_Enter(kSetKP05_KP06, kSceneKP06);
			}
			return; //true;
		}
	}
#endif // BLADERUNNER_ORIGINAL_BUGS

	if ((byActorId == kActorSteele
	  || byActorId == kActorMcCoy
	 )
	 && Actor_Query_In_Set(kActorSteele, kSetHF06)
	 && Actor_Query_In_Set(kActorMcCoy, kSetHF06)
	) {
		Non_Player_Actor_Combat_Mode_On(kActorSteele, kActorCombatStateUncover, true, kActorMcCoy, 15, kAnimationModeCombatIdle, kAnimationModeCombatWalk, kAnimationModeCombatRun, 0, 0, 100, 25, 300, false);
	}

	if (_vm->_cutContent) {
		if (byActorId == kActorMcCoy
		&& Actor_Query_In_Set(kActorLucy, kSetHF04)
		&& Game_Flag_Query(kFlagLucyIsReplicant)) { 
			if (Query_Difficulty_Level() != kGameDifficultyEasy) {
				Global_Variable_Increment(kVariableChinyen, 200);
			}
			// Sad music will play when Lucy dies.
			Music_Stop(1u);
			Delay(1000);
			Actor_Voice_Over(930, kActorVoiceOver); // 99-0930.AUD	Hope I was right about her.
			Delay(1000);
			Music_Play(kMusicCrysDie1, 25, 0, 1, -1, kMusicLoopPlayOnce, 0);	
			Delay(2000);
			Actor_Voice_Over(1410, kActorVoiceOver); //99-1410.AUD	I’d retired another Replicant so more money was headed my way but I didn’t feel so good about it.
			Delay(2000);
			Actor_Says(kActorMcCoy, 170, 19); //00-0170.AUD	Damn.
			Delay(2000);
			Actor_Clue_Acquire(kActorClovis, kClueMcCoyRetiredLucy, true, -1);
			Actor_Clue_Acquire(kActorDektora, kClueMcCoyRetiredLucy, true, -1);
			Actor_Modify_Friendliness_To_Other(kActorClovis, kActorMcCoy, -4);
			Game_Flag_Set(kFlagMcCoyRetiredReplicant);
			Game_Flag_Reset(kFlagMcCoyIsHelpingReplicants);
			Actor_Modify_Friendliness_To_Other(kActorSteele, kActorMcCoy, 2);
			Actor_Modify_Friendliness_To_Other(kActorGuzza, kActorMcCoy, 2);
			Actor_Modify_Friendliness_To_Other(kActorGaff, kActorMcCoy, 2);
			Actor_Set_Goal_Number(kActorLucy, kGoalLucyGone);
		} else if (byActorId == kActorMcCoy
		&& Actor_Query_In_Set(kActorLucy, kSetHF04)
		&& !Game_Flag_Query(kFlagLucyIsReplicant)) { 
			Music_Stop(1u);
			Delay(1000);
			Music_Play(kMusicCrysDie1, 25, 0, 1, -1, kMusicLoopPlayOnce, 0);
			Delay(1000);
			Player_Set_Combat_Mode(false);
			Actor_Voice_Over(2100, kActorVoiceOver); //99-2100.AUD	I'd crossed the line.
			Delay(1000);
			Actor_Says(kActorMcCoy, 2390, kAnimationModeIdle); //00-2390.AUD	Oh, God. No.
			Delay(1000);
			Actor_Voice_Over(300, kActorVoiceOver); //99-0300.AUD	I'd screwed up. Plain and simple.
			Delay(2000);
			Actor_Says(kActorMcCoy, 2305, 13); //00-2305.AUD	I’m sorry.
			Delay(2000);
			Actor_Set_Goal_Number(kActorLucy, kGoalLucyGone);
			Music_Stop(1u);
			Outtake_Play(kOuttakeAway1, true, -1);
			Actor_Set_Goal_Number(kActorMcCoy, kGoalMcCoyArrested);	
		}
	} else {
		if (byActorId == kActorMcCoy
		&& Actor_Query_In_Set(kActorLucy, kSetHF04)
		&& Game_Flag_Query(kFlagLucyIsReplicant)) { 
			if (Query_Difficulty_Level() != kGameDifficultyEasy) {
				Global_Variable_Increment(kVariableChinyen, 200);
			}
			Music_Stop(1u);
			Actor_Set_Goal_Number(kActorLucy, kGoalLucyGone);
		}
	}
}

int AIScriptLucy::GetFriendlinessModifierIfGetsClue(int otherActorId, int clueId) {
	return 0;
}

bool AIScriptLucy::GoalChanged(int currentGoalNumber, int newGoalNumber) {
	if (newGoalNumber == kGoalLucyDefault) {
		Actor_Put_In_Set(kActorLucy, kSetFreeSlotA);
		return false;
	}

	switch (newGoalNumber) {
	case kGoalLucyMoveAround:
		if (Global_Variable_Query(kVariableHollowayArrest) == 3) {
			if (Game_Flag_Query(kFlagDektoraRanAway)
			 && Game_Flag_Query(kFlagGordoRanAway)
			 && Player_Query_Current_Scene() != kSceneHF03
			) {
				Actor_Set_Goal_Number(kActorLucy, kGoalLucyGoToHF03);
			} else {
				if (Random_Query(0, 1) == 1) {
					Actor_Set_Goal_Number(kActorLucy, kGoalLucyGoToFreeSlotGAHJ);
				} else {
					Actor_Set_Goal_Number(kActorLucy, kGoalLucyGoToFreeSlotGAG);
				}
			}
		} else {
			if (_vm->_cutContent) {
				Actor_Set_Goal_Number(kActorLucy, kGoalLucyGoToHF03);
			} else {
				int rnd = Random_Query(0, 3);

				if (rnd == 0) {
					Actor_Set_Goal_Number(kActorLucy, kGoalLucyGoToFreeSlotGAG);
				} else if (rnd == 1) {
					Actor_Set_Goal_Number(kActorLucy, kGoalLucyGoToFreeSlotGAHJ);
				} else if (Player_Query_Current_Scene() == kSceneHF03) {
					Actor_Set_Goal_Number(kActorLucy, kGoalLucyGoToFreeSlotGAG);
				} else {
					Actor_Set_Goal_Number(kActorLucy, kGoalLucyGoToHF03);
				}
			}
		}
		break;

	case kGoalLucyGoToHF03:
		AI_Movement_Track_Flush(kActorLucy);
		AI_Movement_Track_Append_With_Facing(kActorLucy, 371, 0, 156);
		AI_Movement_Track_Repeat(kActorLucy);
		break;

	case kGoalLucyHF03RunOutPhase1:
		Actor_Set_Immunity_To_Obstacles(kActorLucy, true);
		AI_Movement_Track_Flush(kActorLucy);
		AI_Movement_Track_Append_Run(kActorLucy, 377, 0);
		AI_Movement_Track_Repeat(kActorLucy);
		break;

	case kGoalLucyHF03RunOutPhase2:
		Actor_Set_Immunity_To_Obstacles(kActorLucy, false);
		AI_Movement_Track_Flush(kActorLucy);
		AI_Movement_Track_Append_Run(kActorLucy, 372, 0);
		AI_Movement_Track_Append(kActorLucy, 33, 0);
		AI_Movement_Track_Repeat(kActorLucy);
		break;

	case kGoalLucyHF03RunToHF041:
		Actor_Set_Immunity_To_Obstacles(kActorLucy, true);
		AI_Movement_Track_Flush(kActorLucy);
		AI_Movement_Track_Append_Run(kActorLucy, 378, 0);
		AI_Movement_Track_Repeat(kActorLucy);
		break;

	case kGoalLucyHF03RunToHF042:
		Actor_Set_Immunity_To_Obstacles(kActorLucy, false);
		AI_Movement_Track_Flush(kActorLucy);
		AI_Movement_Track_Append_Run(kActorLucy, 373, 0);
		AI_Movement_Track_Append(kActorLucy, 33, 0);
		AI_Movement_Track_Repeat(kActorLucy);
		break;

	case kGoalLucyHF03RunAwayWithHelp1:
		Actor_Says(kActorLucy, 320, 16);
		Actor_Set_Goal_Number(kActorHolloway, kGoalHollowayGoToHF03);
		Actor_Set_Immunity_To_Obstacles(kActorLucy, true);
		AI_Movement_Track_Flush(kActorLucy);
		AI_Movement_Track_Append(kActorLucy, 378, 0);
		AI_Movement_Track_Repeat(kActorLucy);
		break;

	case kGoalLucyHF03RunAwayWithHelp2:
		Actor_Set_Immunity_To_Obstacles(kActorLucy, false);
		AI_Movement_Track_Flush(kActorLucy);
		AI_Movement_Track_Append_Run(kActorLucy, 373, 0);
		AI_Movement_Track_Append(kActorLucy, 33, 30);
		AI_Movement_Track_Repeat(kActorLucy);
		break;

	case kGoalLucyGoToFreeSlotGAG:
		AI_Movement_Track_Flush(kActorLucy);
		AI_Movement_Track_Append(kActorLucy, 39, Random_Query(5, 10));
		AI_Movement_Track_Append(kActorLucy, 33, Random_Query(5, 10));
		AI_Movement_Track_Append(kActorLucy, 39, Random_Query(5, 10));
		AI_Movement_Track_Repeat(kActorLucy);
		break;

	case kGoalLucyGoToFreeSlotGAHJ:
		AI_Movement_Track_Flush(kActorLucy);
		AI_Movement_Track_Append(kActorLucy, 39, Random_Query(5, 15));
		AI_Movement_Track_Append(kActorLucy, 33, Random_Query(10, 30));
		AI_Movement_Track_Append(kActorLucy, 40, Random_Query(15, 30));
		AI_Movement_Track_Append(kActorLucy, 42, Random_Query(10, 20));
		AI_Movement_Track_Repeat(kActorLucy);
		break;

	case kGoalLucyHF04Start:
		AI_Movement_Track_Flush(kActorLucy);
		Actor_Put_In_Set(kActorLucy, kSetHF04);
		Actor_Set_At_Waypoint(kActorLucy, 518, 0);
		Actor_Set_Targetable(kActorLucy, true);
		Actor_Set_Health(kActorLucy, 5, 5);
		break;

	case kGoalLucyHF04TalkToMcCoy:
		Player_Loses_Control();
		// Added in a line and made it so Lucy approaches McCoy when he talks to her in the maze.
		if (_vm->_cutContent) {
			Actor_Says(kActorMcCoy, 1695, 16); //00-1695.AUD	Lucy? Come on out. I’m not the hunter anymore.
		}
		if (_vm->_cutContent) {
			if (!Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)
			&& Player_Query_Agenda() != kPlayerAgendaPolite
			&& Global_Variable_Query(kVariableAffectionTowards) != kAffectionTowardsLucy) {
				Actor_Says(kActorMcCoy, 1700, 16); //00-1700.AUD	I put my gun away.
			}
		} else {
			Actor_Says(kActorMcCoy, 1700, 16); //00-1700.AUD	I put my gun away.
		}
		if (_vm->_cutContent) {
			Actor_Modify_Friendliness_To_Other(kActorClovis, kActorMcCoy, 2);
			Actor_Modify_Friendliness_To_Other(kActorSteele, kActorMcCoy, -2);
			Actor_Modify_Friendliness_To_Other(kActorGuzza, kActorMcCoy, -2);
			Game_Flag_Set(kFlagMcCoyIsHelpingReplicants);
			if (!Actor_Clue_Query(kActorLucy, kClueMcCoyRetiredZuben)
			&& !Actor_Clue_Query(kActorLucy, kClueMcCoyRetiredDektora)
			&& !Actor_Clue_Query(kActorLucy, kClueMcCoyRetiredGordo)
			&& Global_Variable_Query(kVariableAffectionTowards) == kAffectionTowardsNone) {
				Global_Variable_Set(kVariableAffectionTowards, kAffectionTowardsLucy);
			}
		}
		AI_Movement_Track_Flush(kActorLucy);
		if (_vm->_cutContent) {
			Loop_Actor_Walk_To_Actor(kActorLucy, kActorMcCoy, 24, true, true);
		}
		Actor_Face_Actor(kActorLucy, kActorMcCoy, true);
		Actor_Face_Actor(kActorMcCoy, kActorLucy, true);
		if (_vm->_cutContent) {
			if (Global_Variable_Query(kVariableHollowayArrest) == 3) {
				Actor_Says(kActorLucy, 350, 13);
				Actor_Says(kActorMcCoy, 1705, 13); //00-1705.AUD	I have to deal with her just to keep up appearances. I can be more effective that way. 
				Actor_Says(kActorLucy, 360, 13);
				Actor_Says(kActorMcCoy, 1710, 13);
			}
		} else {
			Actor_Says(kActorLucy, 350, 13);
			Actor_Says(kActorMcCoy, 1705, 13);
			Actor_Says(kActorLucy, 360, 13);
			Actor_Says(kActorMcCoy, 1710, 13);
		}
		if (Global_Variable_Query(kVariableAffectionTowards) == kAffectionTowardsLucy) { // cut feature? if this is set lucy will not run into hf04
			Actor_Says(kActorLucy, 940, 13);
			Actor_Says(kActorMcCoy, 6780, 12); //00-6780.AUD	Don’t jump to any conclusions.
			Actor_Says(kActorLucy, 950, 12);
			Actor_Says(kActorLucy, 960, 14);
			Actor_Says(kActorMcCoy, 6785, 13);
			Actor_Says(kActorLucy, 970, 16);
			Actor_Says(kActorLucy, 980, 13);
			if (Game_Flag_Query(kFlagDektoraIsReplicant)) {
				Actor_Says(kActorLucy, 990, 15);
			}
			Actor_Says(kActorMcCoy, 6790, 15); //00-6790.AUD	That must be tough on you.
			if (Game_Flag_Query(kFlagDektoraIsReplicant)
			 && Game_Flag_Query(kFlagLucyIsReplicant)
			) {
				Actor_Says(kActorLucy, 1000, 12);
			}
			Actor_Says(kActorLucy, 1010, 17);
			Actor_Says(kActorLucy, 1020, 18);
			Actor_Says(kActorMcCoy, 6795, 14); //00-6795.AUD	I agree.		
			Actor_Says(kActorLucy, 1030, 17);
			Actor_Says(kActorMcCoy, 6800, 14); //00-6800.AUD	You’ll see them with your own eyes one day.
			if (_vm->_cutContent) {
				Actor_Clue_Acquire(kActorMcCoy, kClueMcCoyIsKind, true, kActorLucy);
				Actor_Says(kActorLucy, 1040, 18); //06-1040.AUD	Will I?
				Actor_Says(kActorMcCoy, 6805, 13); //00-6805.AUD	I-- I promise you. But for now we gotta be careful. You should stay hidden for a while.
				Actor_Says(kActorMcCoy, 6810, 14); //00-6810.AUD	Go. I’ll find you when it’s safe.
				if (Game_Flag_Query(kFlagLucyIsReplicant)) {
					Actor_Says(kActorLucy, 230, 14); //06-0230.AUD	Thank you.
				} else {
					Actor_Says(kActorLucy, 1050, 17); //06-1050.AUD	Oh, thank you. Thank you for everything.
				}
			}
		}
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagLucyIsReplicant)) {
				Actor_Says(kActorLucy, 370, 14);
			}
		} else {
			Actor_Says(kActorLucy, 370, 14);
		}
		if (_vm->_cutContent) {
			Actor_Says(kActorMcCoy, 1650, 13); //00-1650.AUD	Take care of yourself, kid.
		}
		Actor_Set_Goal_Number(kActorLucy, kGoalLucyHF04WalkAway);

		if (Global_Variable_Query(kVariableHollowayArrest) == 3) {
			Actor_Set_Goal_Number(kActorSteele, kGoalSteeleHF02LucyRanAway);
			Game_Flag_Set(kFlagLucyRanAway);
		}

		Player_Gains_Control();
		break;

	case kGoalLucyHF04Run1:
		AI_Movement_Track_Flush(kActorLucy);
		AI_Movement_Track_Append_Run(kActorLucy, 519, 0);
		AI_Movement_Track_Repeat(kActorLucy);
		Actor_Set_Health(kActorLucy, 5, 5);
		break;

	case kGoalLucyHF04Run2:
		AI_Movement_Track_Flush(kActorLucy);
		AI_Movement_Track_Append_Run(kActorLucy, 520, 0);
		AI_Movement_Track_Repeat(kActorLucy);
		break;

	case kGoalLucyHF04Run3:
		AI_Movement_Track_Flush(kActorLucy);
		AI_Movement_Track_Append_Run(kActorLucy, 521, 0);
		AI_Movement_Track_Repeat(kActorLucy);
		break;

	case kGoalLucyHF04Run4:
		AI_Movement_Track_Flush(kActorLucy);
		AI_Movement_Track_Append_Run(kActorLucy, 522, 0);
		AI_Movement_Track_Repeat(kActorLucy);
		break;

	case kGoalLucyHF04WalkAway:
		AI_Movement_Track_Flush(kActorLucy);
		AI_Movement_Track_Append_Run(kActorLucy, 523, 0);
		AI_Movement_Track_Append(kActorLucy, 33, 0);
		AI_Movement_Track_Repeat(kActorLucy);
		Player_Gains_Control();
		Actor_Set_Health(kActorLucy, 30, 30);
		break;

	case 240: // not used anywhere
		if (Global_Variable_Query(kVariableHollowayArrest) == 3) {
			Actor_Set_Goal_Number(kActorLucy, kGoalLucyGone);
			Actor_Set_Goal_Number(kActorSteele, kGoalSteeleHF02ConfrontLucy);
		} else {
			Actor_Set_Goal_Number(kActorLucy, kGoalLucyHF03RanAway);
			Game_Flag_Set(kFlagLucyRanAway);
		}
		break;

	case kGoalLucyReturnToHF03:
		AI_Movement_Track_Flush(kActorLucy);
		AI_Movement_Track_Append(kActorLucy, 372, 0);
		AI_Movement_Track_Append_With_Facing(kActorLucy, 371, 0, 156);
		AI_Movement_Track_Repeat(kActorLucy);
		break;

	case kGoalLucyStartChapter4:
		Actor_Put_In_Set(kActorLucy, kSetFreeSlotA);
		Actor_Set_At_Waypoint(kActorLucy, 33, 0);
		if (_vm->_cutContent) {
			if (!Actor_Clue_Query(kActorLucy, kClueMcCoyRetiredZuben)
			&& !Actor_Clue_Query(kActorLucy, kClueMcCoyRetiredDektora)
			&& !Actor_Clue_Query(kActorLucy, kClueMcCoyRetiredGordo)
			&& Global_Variable_Query(kVariableAffectionTowards) == kAffectionTowardsLucy) {
				Actor_Set_Goal_Number(kActorLucy, kGoalLucyUG01Wait);
			}
		} else {
			if (Global_Variable_Query(kVariableAffectionTowards) == kAffectionTowardsLucy) {
				Actor_Set_Goal_Number(kActorLucy, kGoalLucyUG01Wait);
			}
		}
		break;

	case kGoalLucyUG01Wait:
		Actor_Put_In_Set(kActorLucy, kSetUG01);
		Actor_Set_At_Waypoint(kActorLucy, 544, 651);
		break;

	case kGoalLucyUG01VoightKampff:
		voightKampffTest();
		break;

	case kGoalLucyUG01RunAway:
		AI_Movement_Track_Flush(kActorLucy);
		AI_Movement_Track_Append_Run(kActorLucy, 545, 0);
		AI_Movement_Track_Append(kActorLucy, 33, 0); // kSetFreeSlotA
		AI_Movement_Track_Repeat(kActorLucy);
		break;

	case kGoalLucyGone:
		Game_Flag_Set(kFlagLucyRanAway);
		break;
	}

	return false;
}

bool AIScriptLucy::UpdateAnimation(int *animation, int *frame) {
	switch (_animationState) {
	case kLucyStateIdle:
		*animation = kModelAnimationLucyIdle;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationLucyIdle)) {
			_animationFrame = 0;
		}
		break;

	case kLucyStateWalking:
		// fall through
	case kLucyStateRunning:
		// fall through
	case kLucyStateClimbStairsUp:
		// fall through
	case kLucyStateClimbStairsDown:
		if (_animationState == kLucyStateWalking) {
			*animation = kModelAnimationLucyWalking;
		}
		if (_animationState == kLucyStateRunning) {
			*animation = kModelAnimationLucyRunning;
		}
		if (_animationState == kLucyStateClimbStairsUp) {
			*animation = kModelAnimationLucyClimbStairsUp;
		}
		if (_animationState == kLucyStateClimbStairsDown) {
			*animation = kModelAnimationLucyClimbStairsDown;
		}
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(*animation)) {
			_animationFrame = 0;
		}
		break;

	case kLucyStateGotShotA:
		// fall through
	case kLucyStateGotShotB:
		if (_animationState == kLucyStateGotShotA) {
			*animation = kModelAnimationLucyGotHitBendsForward;
		}
		if (_animationState == kLucyStateGotShotB) {
			*animation = kModelAnimationLucyGotHitBendsBackward;
		}
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(*animation)) {
			*animation = kModelAnimationLucyIdle;
			_animationFrame = 0;
			_animationState = kLucyStateIdle;
			Actor_Change_Animation_Mode(kActorLucy, kAnimationModeIdle);
		}
		break;

	case kLucyStateDie:
		*animation = kModelAnimationLucyShotDead;
		if (_animationFrame < Slice_Animation_Query_Number_Of_Frames(kModelAnimationLucyShotDead) - 1) {
			++_animationFrame;
		}
		break;

	case 8:
		if (_animationFrame == 0 && _resumeIdleAfterFramesetCompletesFlag) {
			*animation = kModelAnimationLucyIdle;
			_animationState = kLucyStateIdle;
			_resumeIdleAfterFramesetCompletesFlag = false;
		} else {
			*animation = kModelAnimationLucyCalmShortRightwardsNodTalk;
			++_animationFrame;
			if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationLucyCalmShortRightwardsNodTalk)) {
				_animationFrame = 0;
			}
		}
		break;

	case 9:
		// fall through
	case 10:
		// fall through
	case 11:
		// fall through
	case 12:
		// fall through
	case 13:
		// fall through
	case 14:
		// fall through
	case 15:
		// fall through
	case 16:
		if (_animationState == 9) {
			*animation = kModelAnimationLucyComplainingTalk;
		}
		if (_animationState == 10) {
			*animation = kModelAnimationLucyIntenseTalk;
		}
		if (_animationState == 11) {
			*animation = kModelAnimationLucyPointingTalk;
		}
		if (_animationState == 12) {
			*animation = kModelAnimationLucySelfPointingTalk;
		}
		if (_animationState == 13) {
			*animation = kModelAnimationLucyVeryUpsetTalk;
		}
		if (_animationState == 14) {
			*animation = kModelAnimationLucyCalmLongRightwardsNodTalk;
		}
		if (_animationState == 15) {
			*animation = kModelAnimationLucySubtleThrowKissTalk;
		}
		if (_animationState == 16) {
			*animation = kModelAnimationLucyHappyHopTalk;
		}
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(*animation)) {
			_animationFrame = 0;
			_animationState = 8;
			*animation = kModelAnimationLucyCalmShortRightwardsNodTalk;
		}
		break;

	case 17:
		*animation = kModelAnimationLucyCombatIdle;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationLucyCombatIdle)) {
			_animationFrame = 0;
		}
		break;

	case 18:
		if (_animationFrame == 0 && _resumeIdleAfterFramesetCompletesFlag) {
			_animationState = 17;
			_resumeIdleAfterFramesetCompletesFlag = false;
			*animation = kModelAnimationLucyCombatIdle;
		} else {
			*animation = kModelAnimationLucyCombatBlocksUp;
			++_animationFrame;
			if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationLucyCombatBlocksUp)) {
				_animationFrame = 0;
			}
		}
		break;

	case 19:
		*animation = kModelAnimationLucyCombatResumeNonCombat;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationLucyCombatResumeNonCombat)) {
			*animation = kModelAnimationLucyIdle;
			_animationFrame = 0;
			_animationState = kLucyStateIdle;
		}
		break;

	case 20:
		*animation = kModelAnimationLucyCombatDropsDead;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationLucyCombatDropsDead)) {
			_animationFrame = 0;
		}
		break;

	case 21:
		*animation = kModelAnimationLucyRemovesNeckletDiesFromExplosion;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationLucyRemovesNeckletDiesFromExplosion)) {
			_animationFrame = 0;
		}
		break;

	default:
		break;
	}
	*frame = _animationFrame;

	return true;
}

bool AIScriptLucy::ChangeAnimationMode(int mode) {
	switch (mode) {
	case kAnimationModeIdle:
		if (_animationState >= 8 && _animationState <= 16) {
			_resumeIdleAfterFramesetCompletesFlag = true;
		} else {
			_animationState = kLucyStateIdle;
			_animationFrame = 0;
		}
		break;

	case kAnimationModeWalk:
		_animationState = kLucyStateWalking;
		_animationFrame = 0;
		break;

	case kAnimationModeRun:
		_animationState = kLucyStateRunning;
		_animationFrame = 0;
		break;

	case kAnimationModeTalk:
		_resumeIdleAfterFramesetCompletesFlag = false;
		_animationState = 8;
		_animationFrame = 0;
		break;

	case kAnimationModeCombatIdle:
		if (_animationState >= 8 && _animationState <= 16) {
			_resumeIdleAfterFramesetCompletesFlag = true;
		} else {
			_animationState = kLucyStateIdle;
			_animationFrame = 0;
		}
		break;

	case kAnimationModeCombatWalk:
		_animationState = kLucyStateWalking;
		_animationFrame = 0;
		break;

	case kAnimationModeCombatRun:
		_animationState = kLucyStateRunning;
		_animationFrame = 0;
		break;

	case 12:
		_resumeIdleAfterFramesetCompletesFlag = false;
		_animationState = 9;
		_animationFrame = 0;
		break;

	case 13:
		_resumeIdleAfterFramesetCompletesFlag = false;
		_animationState = 10;
		_animationFrame = 0;
		break;

	case 14:
		_resumeIdleAfterFramesetCompletesFlag = false;
		_animationState = 11;
		_animationFrame = 0;
		break;

	case 15:
		_resumeIdleAfterFramesetCompletesFlag = false;
		_animationState = 12;
		_animationFrame = 0;
		break;

	case 16:
		_resumeIdleAfterFramesetCompletesFlag = false;
		_animationState = 13;
		_animationFrame = 0;
		break;

	case 17:
		_resumeIdleAfterFramesetCompletesFlag = false;
		_animationState = 14;
		_animationFrame = 0;
		break;

	case 18:
		_resumeIdleAfterFramesetCompletesFlag = false;
		_animationState = 15;
		_animationFrame = 0;
		break;

	case 19:
		_resumeIdleAfterFramesetCompletesFlag = false;
		_animationState = 16;
		_animationFrame = 0;
		break;

	case kAnimationModeHit:
		if (Random_Query(1, 2) == 1) {
			_animationState = kLucyStateGotShotA;
		} else {
			_animationState = kLucyStateGotShotB;
		}
		_animationFrame = 0;
		break;

	case kAnimationModeCombatHit:
		if (Random_Query(1, 2) == 1) {
			_animationState = kLucyStateGotShotA;
		} else {
			_animationState = kLucyStateGotShotB;
		}
		_animationFrame = 0;
		break;

	case kAnimationModeDie:
		_animationState = kLucyStateDie;
		_animationFrame = 0;
		break;
	}

	return true;
}

void AIScriptLucy::QueryAnimationState(int *animationState, int *animationFrame, int *animationStateNext, int *animationNext) {
	*animationState     = _animationState;
	*animationFrame     = _animationFrame;
	*animationStateNext = _animationStateNext;
	*animationNext      = _animationNext;
}

void AIScriptLucy::SetAnimationState(int animationState, int animationFrame, int animationStateNext, int animationNext) {
	_animationState     = animationState;
	_animationFrame     = animationFrame;
	_animationStateNext = animationStateNext;
	_animationNext      = animationNext;
}

bool AIScriptLucy::ReachedMovementTrackWaypoint(int waypointId) {
	return true;
}

void AIScriptLucy::FledCombat() {
	if (Global_Variable_Query(kVariableChapter) == 5
	 && Actor_Query_Goal_Number(kActorLucy) == 450
	) {
		Actor_Put_In_Set(kActorLucy, kSetFreeSlotG);
		Actor_Set_At_Waypoint(kActorLucy, 39, 0);
		Actor_Set_Goal_Number(kActorLucy, kGoalLucyGone);
	}

	return; //true;
}

void AIScriptLucy::voightKampffTest() {
	Player_Loses_Control();
	Actor_Face_Actor(kActorMcCoy, kActorLucy, true);
	// Added in some lines for Lucy and McCoy.
	if (_vm->_cutContent) {
		Actor_Face_Actor(kActorLucy, kActorMcCoy, true);
		Actor_Says(kActorMcCoy, 1600, 11); //00-1600.AUD	Lucy? 
	}
	if (_vm->_cutContent) {
		if (Player_Query_Agenda() != kPlayerAgendaPolite) {
			Actor_Says(kActorMcCoy, 6815, 11); //00-6815.AUD	I told you to stay hidden
			Actor_Says(kActorLucy, 650, 16); //06-0650.AUD	Haven’t we already been through this?
			Actor_Says(kActorLucy, 660, 13); //06-0660.AUD	Why would I have any dealings with those people? 
			Actor_Says(kActorMcCoy, 630, 11); //00-0630.AUD	What?
			Actor_Says(kActorLucy, 1060, 13); //06-1060.AUD	I can’t stay there anymore.
			Actor_Says(kActorLucy, 1070, 17); //06-1070.AUD	I don’t want to be with father. Not when he’s so angry. Besides…
			Delay(1000);
		} else {
			Actor_Says(kActorLucy, 380, 13); //06-0380.AUD	Ray.
			Delay(1000);
			Actor_Says(kActorMcCoy, 6185, 19); //00-6185.AUD	(sighs) You got any idea how glad I am to see ya?
			Actor_Says(kActorLucy, 390, 13); //06-0390.AUD	I’m scared, Ray.
			Actor_Says(kActorMcCoy, 8320, 11); //00-8320.AUD	Really?
			Delay(500);
			Actor_Says(kActorLucy, 1530, 16); //06-1530.AUD	I'm always afraid.
			Actor_Says(kActorMcCoy, 8190, -1);	// 00-8190.AUD	Why?
			Delay(1000);
			Actor_Says(kActorLucy, 1750, 13); //06-1750.AUD	I don't wanna tell you.
			Delay(1000);
			Actor_Says(kActorMcCoy, 7985, 13); //00-7985.AUD	It's okay.
			Delay(1000);
		}
	}
	Actor_Says(kActorLucy, 1080, 14); //06-1080.AUD	I need something.
#if BLADERUNNER_ORIGINAL_BUGS
	Actor_Says(kActorMcCoy, 6820, 16);
#else
	// McCoy is interrupted here
	if (_vm->_cutContent) {
		if (Player_Query_Agenda() != kPlayerAgendaPolite) {
			Actor_Says_With_Pause(kActorMcCoy, 6820, 0.0f, 16); //00-6820.AUD	We don't have time for an--
		}
	} else {
		Actor_Says_With_Pause(kActorMcCoy, 6820, 0.0f, 16); //00-6820.AUD	We don't have time for an--
	}
#endif // BLADERUNNER_ORIGINAL_BUGS
	Actor_Says(kActorLucy, 1090, 13); //06-1090.AUD	That thing you do to see if a person is human?
	if (_vm->_cutContent) {
		Actor_Says(kActorMcCoy, 6825, 13);
	} else if (!Game_Flag_Query(kFlagDirectorsCut)) {
		Actor_Says(kActorMcCoy, 6825, 13);
	}
	Actor_Says(kActorMcCoy, 6830, 12); //00-6830.AUD	You want it?
	if (Actor_Query_Intelligence(kActorLucy) == 70) {
		Actor_Says(kActorLucy, 1100, 14); //06-1100.AUD	Is it always right?
		Actor_Says(kActorMcCoy, 6835, 14); //00-6835.AUD	Usually.
	}
	Actor_Says(kActorLucy, 1110, 15); //06-1110.AUD	Give it to me. Father won’t tell me anything anymore.
	// Made it so McCoy only VKs Lucy if he is not Surly or Erratic.
	if (_vm->_cutContent) {
		if (Player_Query_Agenda() != kPlayerAgendaPolite) {	
			Actor_Says_With_Pause(kActorMcCoy, 6840, 0.0f, 13); //00-6840.AUD	Is that why he was angry? Because you asked him--
			Delay(1000);
			Actor_Says(kActorMcCoy, 6905, 13); //00-6905.AUD	Now is not a good time.
			Actor_Says(kActorLucy, 1230, 17); //06-1230.AUD	It’s never a good time!
			Actor_Says(kActorMcCoy, 6910, 13); //00-6910.AUD	Listen! You have to be patient, you have to trust me. It's not safe here.
			Game_Flag_Set(kFlagLucyMeetingAct4);
			Delay(2000);
			Player_Gains_Control();
			Actor_Set_Goal_Number(kActorLucy, kGoalLucyUG01RunAway);
		} else {
			Actor_Says_With_Pause(kActorMcCoy, 6840, 0.0f, 13); //00-6840.AUD	Is that why he was angry? Because you asked him--
			Delay(1000);
			Actor_Says(kActorMcCoy, 6845, 12); //00-6845.AUD	You deserve it.
			Delay(500);
			Actor_Says(kActorMcCoy, 6850, 12); //00-6850.AUD	You know how this works? I set up situations and you respond.
			if (Actor_Query_Intelligence(kActorLucy) == 70) {
				Actor_Says(kActorLucy, 1120, 14); //06-1120.AUD	Okay. Is it hard? Like a test in school?
				Actor_Says(kActorMcCoy, 6855, 13); //00-6855.AUD	No. Sometimes it can be disturbing.
			} else if (Actor_Query_Intelligence(kActorLucy) == 50) {
				Delay(1000);
			}
			Actor_Says(kActorMcCoy, 6860, 13); //00-6860.AUD	Are you ready?
			Actor_Says(kActorLucy, 1130, 14); //06-1130.AUD	Uh-huh.
			Player_Gains_Control();
			Voight_Kampff_Activate(kActorLucy, 40);
			Player_Loses_Control();
			if (Actor_Clue_Query(kActorMcCoy, kClueVKLucyReplicant)
			&& Game_Flag_Query(kFlagLucyIsReplicant)) {
				Delay(250);
				Actor_Says(kActorLucy, 1140, 14); //06-1140.AUD	Tell me.
				Actor_Says(kActorMcCoy, 6865, 14);
				Delay(1000);
				Actor_Says(kActorLucy, 1150, 16); //06-1150.AUD	Then father was right. I shouldn’t have taken the test.
				if (Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
					Actor_Says(kActorMcCoy, 6870, 14); //00-6870.AUD	No. But you had to know.
				}
				Delay(500);
			} else if (Actor_Clue_Query(kActorMcCoy, kClueVKLucyHuman)
			&& !Game_Flag_Query(kFlagLucyIsReplicant)) {
				Actor_Says(kActorMcCoy, 6880, 13);
				Actor_Says(kActorLucy, 1170, 13); //06-1170.AUD	Really?
				if (Actor_Query_Intelligence(kActorLucy) == 50) { 
					Actor_Says(kActorLucy, 1180, 16); //06-1180.AUD	Why didn’t father tell me?
					if (Actor_Query_Friendliness_To_Other(kActorClovis, kActorMcCoy) > 50) {
						Actor_Says(kActorMcCoy, 6890, 15); //00-6890.AUD	Maybe he wanted to keep his... family together.
						Actor_Says(kActorLucy, 1190, 15); //06-1190.AUD	I’m not a little girl anymore.
						Actor_Says(kActorLucy, 1200, 17); //06-1200.AUD	It’s not fair!
						Actor_Says(kActorMcCoy, 6885, 13); //00-6885.AUD	No. But it's understandable.
					} else {
						Actor_Says(kActorMcCoy, 5450, 15); //00-5450.AUD	I'm not sure.
						Delay(1000);
					}
				} else if (Actor_Query_Intelligence(kActorLucy) == 70) { 
					Actor_Says(kActorMcCoy, 1625, 15); //00-1625.AUD	Yes.
					Delay(1000);
				}
			} else {
				Delay(250);
				Actor_Says(kActorAnsweringMachine, 450, -1); //39-0450.AUD	Inconclusive result.
				Delay(1000);
				Actor_Says(kActorMcCoy, 2305, 13); //00-2305.AUD	I’m sorry.
				Delay(500);
				Actor_Says(kActorLucy, 1200, 17); //06-1200.AUD	It’s not fair!
				Delay(2000);
			}
			Actor_Says(kActorMcCoy, 6875, 13); //00-6875.AUD	I gotta go.
			if (Actor_Query_Intelligence(kActorLucy) == 50) { 
				if (Game_Flag_Query(kFlagLucyIsReplicant)) {
					Actor_Says(kActorLucy, 1160, 16); //06-1160.AUD	I wanna stay with you.
				} else {
					Actor_Says(kActorLucy, 1210, 17); //06-1210.AUD	I’m gonna stay with you.
				}
				Actor_Says(kActorMcCoy, 6895, 15); //00-6895.AUD	Don't you understand? It's not safe.
				if (Actor_Clue_Query(kActorMcCoy, kClueVKLucyReplicant)
				&& Game_Flag_Query(kFlagLucyIsReplicant)) {
					Actor_Says_With_Pause(kActorMcCoy, 6900, 0.0f, 11); //00-6900.AUD	There's a hunter out here. If she finds out where you are--
				}
			}
			Actor_Says(kActorLucy, 1220, 16); //06-1220.AUD	Can’t you come back with me?
			Actor_Says(kActorMcCoy, 6910, 13); //00-6910.AUD	Listen! You have to be patient, you have to trust me. It's not safe here.
			Game_Flag_Set(kFlagLucyMeetingAct4);
			Delay(2000);
			Player_Gains_Control();
			Actor_Set_Goal_Number(kActorLucy, kGoalLucyUG01RunAway);
		}
	} else {
	#if BLADERUNNER_ORIGINAL_BUGS
		Actor_Says(kActorMcCoy, 6840, 13);
	#else
		// McCoy cuts his sentence short here.
		// He is not interrupted, but still we should use Actor_Says_With_Pause 0.0f
		Actor_Says_With_Pause(kActorMcCoy, 6840, 0.0f, 13); //00-6840.AUD	Is that why he was angry? Because you asked him--
		Delay(1000);
	#endif // BLADERUNNER_ORIGINAL_BUGS
		Actor_Says(kActorMcCoy, 6845, 12); //00-6845.AUD	You deserve it.
		Delay(500);
		Actor_Says(kActorMcCoy, 6850, 12); //00-6850.AUD	You know how this works? I set up situations and you respond.
		Actor_Says(kActorLucy, 1120, 14); //06-1120.AUD	Okay. Is it hard? Like a test in school?
		Actor_Says(kActorMcCoy, 6855, 13); //00-6855.AUD	No. Sometimes it can be disturbing.
		Actor_Says(kActorMcCoy, 6860, 13); //00-6860.AUD	Are you ready?
		Actor_Says(kActorLucy, 1130, 14); //06-1130.AUD	Uh-huh.
		Music_Stop(2u);
		Player_Gains_Control();

		Voight_Kampff_Activate(kActorLucy, 40);

		Player_Loses_Control();
		if (Actor_Clue_Query(kActorMcCoy, kClueVKLucyReplicant)) {
	#if BLADERUNNER_ORIGINAL_BUGS
			Actor_Says(kActorMcCoy, 6865, 13);
	#else
			// don't repeat the result, just delay
			Delay(250);
	#endif // BLADERUNNER_ORIGINAL_BUGS
			Actor_Says(kActorLucy, 1140, 14); //06-1140.AUD	Tell me.
			Actor_Says(kActorMcCoy, 6865, 14);
			Actor_Says(kActorLucy, 1150, 16); //06-1150.AUD	Then father was right. I shouldn’t have taken the test.
			Actor_Says(kActorMcCoy, 6870, 14); //00-6870.AUD	No. But you had to know.
			Delay(500);
			Actor_Says(kActorMcCoy, 6875, 13); //00-6875.AUD	I gotta go.
			Actor_Says(kActorLucy, 1160, 16); //06-1160.AUD	I wanna stay with you.
		} else {
			Actor_Says(kActorMcCoy, 6880, 13);
			Actor_Says(kActorLucy, 1170, 13); //06-1170.AUD	Really?
			Actor_Says(kActorLucy, 1180, 16); //06-1180.AUD	Why didn’t father tell me?
			Actor_Says(kActorMcCoy, 6890, 15); //00-6890.AUD	Maybe he wanted to keep his... family together.
			Actor_Says(kActorLucy, 1190, 15); //06-1190.AUD	I’m not a little girl anymore.
			Actor_Says(kActorLucy, 1200, 17); //06-1200.AUD	It’s not fair!
			Actor_Says(kActorMcCoy, 6885, 13); //00-6885.AUD	No. But it's understandable.
			Actor_Says(kActorLucy, 1210, 17); //06-1210.AUD	I’m gonna stay with you.
		}
		Actor_Says(kActorMcCoy, 6895, 15); //00-6895.AUD	Don't you understand? It's not safe.
	#if BLADERUNNER_ORIGINAL_BUGS
		Actor_Says(kActorMcCoy, 6900, 11);
	#else
		// McCoy is interrupted here
		Actor_Says_With_Pause(kActorMcCoy, 6900, 0.0f, 11); //00-6900.AUD	There's a hunter out here. If she finds out where you are--
	#endif // BLADERUNNER_ORIGINAL_BUGS
		Actor_Says(kActorLucy, 1220, 16); //06-1220.AUD	Can’t you come back with me?
		Actor_Says(kActorMcCoy, 6905, 13); //00-6905.AUD	Now is not a good time.
		Actor_Says(kActorLucy, 1230, 17); //06-1230.AUD	It’s never a good time!
		Actor_Says(kActorMcCoy, 6910, 13); //00-6910.AUD	Listen! You have to be patient, you have to trust me. It's not safe here.
		Delay(2000);
		Player_Gains_Control();
		Actor_Set_Goal_Number(kActorLucy, kGoalLucyUG01RunAway);
	}
}

void AIScriptLucy::checkCombat() {
	Game_Flag_Set(kFlagMcCoyAttackedLucy);

	if (Actor_Query_In_Set(kActorLucy, kSetHF01)
	 && Global_Variable_Query(kVariableChapter) == 5
	 && Actor_Query_Goal_Number(kActorLucy) != 450
	) {
		if (Global_Variable_Query(kVariableAffectionTowards) == kAffectionTowardsLucy) {
			Global_Variable_Set(kVariableAffectionTowards, kAffectionTowardsNone);
		}
		Actor_Set_Goal_Number(kActorLucy, 450);
		Non_Player_Actor_Combat_Mode_On(kActorLucy, kActorCombatStateIdle, false, kActorMcCoy, 4, kAnimationModeIdle, kAnimationModeWalk, kAnimationModeRun, -1, 0, 0, 10, 300, false);
	}
}

} // End of namespace BladeRunner
