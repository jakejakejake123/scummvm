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

AIScriptSteele::AIScriptSteele(BladeRunnerEngine *vm) : AIScriptBase(vm) {
	_resumeIdleAfterFramesetCompletesFlag = false;
	// _varChooseIdleAnimation can have valid values: 0, 1, 3 (value 2 is skipped)
	_varChooseIdleAnimation = 0;
	_varNumOfTimesToHoldCurrentFrame = 0;
}

void AIScriptSteele::Initialize() {
	_animationFrame = 0;
	_animationState = 0;
	_animationStateNext = 0;
	_animationNext = 0;

	_resumeIdleAfterFramesetCompletesFlag = false;
	_varChooseIdleAnimation = 0;
	_varNumOfTimesToHoldCurrentFrame = 0;

	Actor_Put_In_Set(kActorSteele, kSetFreeSlotG);
	Actor_Set_At_Waypoint(kActorSteele, 39, 0);
	Actor_Set_Goal_Number(kActorSteele, kGoalSteeleDefault);
	Actor_Clue_Acquire(kActorSteele, kClueCrimeSceneNotes, true, -1);
}

bool AIScriptSteele::Update() {
	if ( Global_Variable_Query(kVariableMcCoyEvidenceMissed) > 5
	 && !Actor_Clue_Query(kActorSteele, kClueMcCoyIsStupid)
	) {
		Actor_Clue_Acquire(kActorSteele, kClueMcCoyIsStupid, true, -1);
		return true;
	}

	switch (Global_Variable_Query(kVariableChapter)) {
	case 1:
		if (Game_Flag_Query(kFlagMcCoyInRunciters)
		 && Game_Flag_Query(kFlagSteeleInRunciters)
		) {
			Actor_Set_Goal_Number(kActorSteele, kGoalSteeleGoToFreeSlotC1);
			return true;
		}

		if (Game_Flag_Query(kFlagMcCoyInChinaTown)
		 && Game_Flag_Query(kFlagSteeleInChinaTown)
		) {
			Actor_Set_Goal_Number(kActorSteele, kGoalSteeleGoToFreeSlotC2);
			return true;
		}

		if (Game_Flag_Query(kFlagMcCoyInPoliceStation)
		 && Game_Flag_Query(kFlagSteeleInPoliceStation)
		) {
			Actor_Set_Goal_Number(kActorSteele, kGoalSteeleGoToFreeSlotG3);
			return true;
		}

		if ( Actor_Query_Goal_Number(kActorSteele) == kGoalSteeleDefault
		 && !Game_Flag_Query(kFlagMcCoyInRunciters)
		 &&  Player_Query_Current_Scene() != kSceneRC01
		) {
			Actor_Set_Goal_Number(kActorSteele, kGoalSteeleGoToRC01);
			Game_Flag_Set(kFlagSteeleInRunciters);
			return true;
		}

		if (Actor_Query_Goal_Number(kActorSteele) == kGoalSteeleInterviewGrigorian) {
			Actor_Set_Goal_Number(kActorSteele, kGoalSteeleDefault);
			return true;
		}

		break;

	case 2:
		if ( Game_Flag_Query(kFlagTB05Entered)
		 && !Game_Flag_Query(kFlagTB02SteeleEnter)
		) {
			Actor_Set_Goal_Number(kActorSteele, kGoalSteeleGoToTB02);
			Game_Flag_Set(kFlagTB02SteeleEnter);
			return true;
		}

		if (Actor_Query_Goal_Number(kActorSteele) == kGoalSteeleGoToTB02
		 && Game_Flag_Query(kFlagTB02SteeleTalk)) {
			Actor_Set_Goal_Number(kActorSteele, kGoalSteeleLeaveTB02);
			return true;
		 }

		if (!Game_Flag_Query(kFlagSteeleWalkingAround)
		 && Actor_Query_Goal_Number(kActorSteele) == kGoalSteeleGoToPoliceStation
		) {
			Actor_Set_Goal_Number(kActorSteele, kGoalSteeleWalkAround);
			Game_Flag_Set(kFlagSteeleWalkingAround);
			return true;
		}

		if (Actor_Query_Goal_Number(kActorSteele) == kGoalSteeleWalkAroundRestart) {
			Game_Flag_Reset(kFlagSteeleWalkingAround);
			Actor_Set_Goal_Number(kActorSteele, kGoalSteeleGoToPoliceStation);
			return true;
		}

		break;

	case 3:
		if (Global_Variable_Query(kVariableChapter) != 3) { // why is this here? double check?
			break;
		}

		if (Actor_Query_Goal_Number(kActorSteele) < kGoalSteeleStartChapter3) {
			Actor_Set_Goal_Number(kActorSteele, kGoalSteeleStartChapter3);
		}

		if (Actor_Query_Goal_Number(kActorSteele) == kGoalSteeleNR01TalkToGordo
		 && Player_Query_Current_Scene() == kSceneNR01
		 && Actor_Query_In_Between_Two_Actors(kActorMcCoy, kActorSteele, kActorGordo)
		) {
			Actor_Set_Goal_Number(kActorSteele, kGoalSteeleNR01ShootMcCoy);
		}

		if (Actor_Query_Goal_Number(kActorSteele) == kGoalSteeleNR11Entered) {
			Actor_Set_Goal_Number(kActorSteele, kGoalSteeleNR11Decide);
			return true;
		}

		if (Actor_Query_Goal_Number(kActorSteele) == kGoalSteeleNR01PrepareTalkAboutShotGun) {
			Actor_Set_Goal_Number(kActorSteele, kGoalSteeleNR01TalkAboutShotGun);
			return true;
		}

		if (Actor_Query_Goal_Number(kActorSteele) == kGoalSteeleNR01PrepareShotByMcCoy) {
			Actor_Set_Goal_Number(kActorSteele, kGoalSteeleNR01ShotByMcCoy);
			return true;
		}

		break;

	case 4:
		if (Actor_Query_Goal_Number(kActorSteele) < kGoalSteeleStartChapter4) {
			Actor_Set_Goal_Number(kActorSteele, kGoalSteeleStartChapter4);
		}

		break;

	case 5:
		if (Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)
		 && Actor_Query_Goal_Number(kActorSteele) < kGoalSteeleStartChapter5
		) {
			Actor_Set_Goal_Number(kActorSteele, kGoalSteeleStartChapter5);
			return true;
		}

		break;

	default:
		break;
	}

	if ( Actor_Query_Goal_Number(kActorSteele) == kGoalSteeleGone
		&& !Actor_Query_In_Set(kActorSteele, kSetFreeSlotI)
	) {
		if (Actor_Query_Which_Set_In(kActorMcCoy) != Actor_Query_Which_Set_In(kActorSteele)) {
			AI_Movement_Track_Flush(kActorSteele);
			AI_Movement_Track_Append(kActorSteele, 41, 100);
			AI_Movement_Track_Repeat(kActorSteele);
		}
	}
	return false;

}

void AIScriptSteele::TimerExpired(int timer) {
	if (timer == kActorTimerAIScriptCustomTask0
	 && Actor_Query_Goal_Number(kActorSteele) == kGoalSteeleNR11StartWaiting
	) {
		if (Player_Query_Current_Scene() == kSceneNR11) {
			Actor_Set_Goal_Number(kActorSteele, kGoalSteeleNR11Enter);
		} else {
			Actor_Set_Goal_Number(kActorSteele, kGoalSteeleNR11StopWaiting);
		}
		return; // true;
	}

	if (timer == kActorTimerAIScriptCustomTask1) {
		int goal = Actor_Query_Goal_Number(kActorSteele);

		AI_Countdown_Timer_Reset(kActorSteele, kActorTimerAIScriptCustomTask1);

		if (goal == kGoalSteeleKP03Exploded) {
			Actor_Set_Goal_Number(kActorSteele, kGoalSteeleKP03Dying);
		} else if (goal == kGoalSteeleKP03Dying) {
			Actor_Set_Goal_Number(kActorSteele, kGoalSteeleKP03Dead);
		}
	}
	return; // false;
}

void AIScriptSteele::CompletedMovementTrack() {
	switch (Actor_Query_Goal_Number(kActorSteele)) {
	case kGoalSteeleGoToRC01:
		Actor_Set_Goal_Number(kActorSteele, kGoalSteeleGoToRC02);
		break;

	case kGoalSteeleGoToRC02:
		Actor_Set_Goal_Number(kActorSteele, kGoalSteeleGoToFreeSlotC1);
		break;

	case kGoalSteeleGoToFreeSlotC1:
		if (Random_Query(1, 3) == 1) {
			Actor_Clues_Transfer_New_To_Mainframe(kActorSteele);
			Actor_Clues_Transfer_New_From_Mainframe(kActorSteele);
		}

		if (!_vm->_cutContent) {
			if (Query_Score(kActorMcCoy) > Query_Score(kActorSteele)
			&& Query_Score(kActorMcCoy) < 75
			) {
				Set_Score(kActorSteele, Random_Query(2, 5) + Query_Score(kActorMcCoy));
			}
		}

		Actor_Set_Goal_Number(kActorSteele, kGoalSteeleGoToFreeSlotG1);
		break;

	case kGoalSteeleGoToFreeSlotG1:
		Actor_Set_Goal_Number(kActorSteele, kGoalSteeleGoToCT01);
		break;

	case kGoalSteeleGoToCT01:
		Actor_Set_Goal_Number(kActorSteele, kGoalSteeleGoToFreeSlotC2);
		break;

	case kGoalSteeleGoToFreeSlotC2:
		if (Random_Query(1, 3) == 1) {
			Actor_Clues_Transfer_New_To_Mainframe(kActorSteele);
			Actor_Clues_Transfer_New_From_Mainframe(kActorSteele);
		}

		if (!_vm->_cutContent) {
			if (Query_Score(kActorMcCoy) > Query_Score(kActorSteele)
			&& Query_Score(kActorMcCoy) < 75
			) {
				Set_Score(kActorSteele, Random_Query(2, 5) + Query_Score(kActorMcCoy));
			}
		}

		Actor_Set_Goal_Number(kActorSteele, kGoalSteeleGoToFreeSlotG2);
		break;

	case kGoalSteeleGoToFreeSlotG2:
		Actor_Set_Goal_Number(kActorSteele, kGoalSteeleGoToPoliceShootingRange);
		break;

	case kGoalSteeleGoToPoliceShootingRange:
		Actor_Set_Goal_Number(kActorSteele, kGoalSteeleGoToPS02);
		break;

	case kGoalSteeleGoToPS02:
		Actor_Set_Goal_Number(kActorSteele, kGoalSteeleGoToFreeSlotG3);
		break;

	case kGoalSteeleGoToFreeSlotG3:
		Actor_Set_Goal_Number(kActorSteele, kGoalSteeleInterviewGrigorian);
		break;

	case kGoalSteeleApprehendIzo:
		if (Actor_Query_Goal_Number(kActorSteele) == kGoalSteeleApprehendIzo) { //why is this here? double check?
			Player_Set_Combat_Mode(false);

			if (Actor_Query_Goal_Number(kActorIzo) != kGoalIzoDie) {
				if (Actor_Query_In_Between_Two_Actors(kActorMcCoy, kActorSteele, kActorIzo)) {
					Actor_Set_Goal_Number(kActorSteele, kGoalSteeleIzoBlockedByMcCoy);
				} else if (Game_Flag_Query(kFlagIzoIsReplicant)) {
					Actor_Set_Goal_Number(kActorSteele, kGoalSteeleShootIzo);
				} else {
					Actor_Set_Goal_Number(kActorSteele, kGoalSteeleArrestIzo);
				}
			}
		}
		break;

	case kGoalSteeleLeaveTB02:
		Actor_Set_Goal_Number(kActorSteele, kGoalSteeleGoToPoliceStation);
		break;

	case kGoalSteeleWalkAround:
		Actor_Set_Goal_Number(kActorSteele, kGoalSteeleWalkAroundRestart);
		break;

	case kGoalSteeleHF02ShootLucy:
		Actor_Set_Goal_Number(kActorSteele, kGoalSteeleHF02LucyShotBySteele);
		break;

	case kGoalSteeleKP01Leave:
		Actor_Set_Goal_Number(kActorSteele, kGoalSteeleKP01Left);
		break;

	case kGoalSteeleKP06Enter:
		Player_Set_Combat_Mode(false);
		Actor_Face_Actor(kActorMcCoy, kActorSteele, true);
		Actor_Says(kActorMcCoy, 2265, 11);
		if (_vm->_cutContent) {
			if (Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) < 60) {
				Actor_Says(kActorSteele, 640, 58); //01-0640.AUD	No chance.
				if (Player_Query_Agenda() == kPlayerAgendaSurly 
				|| (Player_Query_Agenda() == kPlayerAgendaErratic)) {
					if (!Game_Flag_Query(kFlagSadikIsReplicant)) {
						Actor_Says(kActorMcCoy, 2270, 12); //00-2270.AUD	The bastard killed my dog. He tried to convince me I wasn’t human.
						Actor_Says(kActorSteele, 650, 59); //01-0650.AUD	The job ain’t about revenge, McCoy.
					}
				}
				Actor_Says(kActorMcCoy, 2275, 16); //00-2275.AUD	If it’s the money you’re worried about, you can have it.
				Actor_Says(kActorMcCoy, 2280, 15); //00-2280.AUD	But I’m doing this one alone.
				// Added in a line.
				if (Player_Query_Agenda() == kPlayerAgendaSurly 
				|| (Player_Query_Agenda() == kPlayerAgendaErratic)) {
					Actor_Says(kActorMcCoy, 2285, 16);	//00-2285.AUD	All I need is one shot and it’ll all be over.
				}
				if (Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) < 60) {
					Actor_Says(kActorSteele, 660, 60); //01-0660.AUD	You’re a stubborn son of a bitch.
				}
			}
		} else {
			Actor_Says(kActorSteele, 640, 58); //01-0640.AUD	No chance.
			Actor_Says(kActorMcCoy, 2270, 12);
			Actor_Says(kActorSteele, 650, 59); //01-0650.AUD	The job ain’t about revenge, McCoy.
			Actor_Says(kActorMcCoy, 2275, 16);
			Actor_Says(kActorMcCoy, 2280, 15); //00-2280.AUD	But I’m doing this one alone.
			Actor_Says(kActorSteele, 660, 60); //01-0660.AUD	You’re a stubborn son of a bitch.
		}
		Actor_Says(kActorSteele, 670, 59);
		Actor_Set_Goal_Number(kActorSteele, kGoalSteeleKP06Leave);
		Player_Set_Combat_Mode(true);
		if (_vm->_cutContent) {
			Delay(2000);
		}
		Loop_Actor_Walk_To_XYZ(kActorMcCoy, -731.0f, 8.26f, -657.0f, 0, false, false, false);
		Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
		Ambient_Sounds_Remove_All_Looping_Sounds(1u);
		Game_Flag_Set(kFlagKP06toKP07);
		Set_Enter(kSetKP07, kSceneKP07);
		break;
	}
	return; //true;
}

void AIScriptSteele::ReceivedClue(int clueId, int fromActorId) {
	//return false;
}

void AIScriptSteele::ClickedByPlayer() {
	int goal = Actor_Query_Goal_Number(kActorSteele);

	if (goal == kGoalSteeleGone) {
		Actor_Face_Actor(kActorMcCoy, kActorSteele, true);
		Actor_Says(kActorMcCoy, 8630, 14);
		return; //true;
	}

	if (goal > 399
	 || Global_Variable_Query(kVariableChapter) > 2
	) {
		return; //true;
	}

	if (goal == kGoalSteeleHF02ShootLucy) {
		Actor_Set_Goal_Number(kActorSteele, kGoalSteeleHF02LucyShotBySteele);
		return; //true;
	}

	if (goal == kGoalSteeleNR01ConfrontGordo) {
		return; //true;
	}

#if BLADERUNNER_ORIGINAL_BUGS
#else
	if (goal == kGoalSteeleApprehendIzo
	    || goal == kGoalSteeleArrestIzo
	    || goal == kGoalSteeleShootIzo
	) {
		// don't interrupt Steele before she apprehends Izo
		return; //true;
	}
#endif // BLADERUNNER_ORIGINAL_BUGS

	AI_Movement_Track_Pause(kActorSteele);
	Actor_Face_Actor(kActorSteele, kActorMcCoy, true);
	Actor_Face_Actor(kActorMcCoy, kActorSteele, true);

	if (_vm->_cutContent) {
		if (Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) > 50) {
			Actor_Says(kActorMcCoy, 3970, 15);
			Actor_Says(kActorSteele, 1750, 15); //01-1750.AUD	Been pretty busy haven’t you, Slim?
		} else if (Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) < 50) { 
			Actor_Says(kActorMcCoy, 3970, 15);
			Actor_Says(kActorSteele, 2700, 15); //01-2700.AUD	You're horning in on my action, rookie. Take a stroll.
		} else {
			Actor_Says(kActorMcCoy, 3970, 15);
			Actor_Says(kActorSteele, 2060, 15); //01-2060.AUD	What are you doing here, Slim?
		}
	} else {

		switch (Random_Query(1, 3)) {
		
		case 1:
			Actor_Says(kActorMcCoy, 3970, 15);
			Actor_Says(kActorSteele, 2700, 15); //01-2700.AUD	You're horning in on my action, rookie. Take a stroll.
			break;

		case 2:
			Actor_Says(kActorMcCoy, 3970, 15);
			Actor_Says(kActorSteele, 2060, 15); //01-2060.AUD	What are you doing here, Slim?
			break;

		case 3:
			Actor_Says(kActorMcCoy, 3970, 15);
			Actor_Says(kActorSteele, 1750, 15); //01-1750.AUD	Been pretty busy haven’t you, Slim?
			break;
		}
		AI_Movement_Track_Unpause(kActorSteele);

		return; //false;
	}
}

void AIScriptSteele::EnteredSet(int setId) {
#if BLADERUNNER_ORIGINAL_BUGS
#else
	if (Actor_Query_Goal_Number(kActorSteele) == kGoalSteeleGoToRC01) {
		if (!Actor_Clue_Query(kActorMcCoy, kClueOfficersStatement))
		{
			// no random factor here, Steele will definitely get this clue in this case
			// McCoy can still get this clue on his own (directly from the officer, if the officer is still at Runciters) -- even if McCoy got it from the mainframe via Steele
			Actor_Clue_Acquire(kActorSteele, kClueOfficersStatement, true, kActorOfficerLeary); // Steele will upload this to the mainframe when she heads to the Police Station
			Global_Variable_Increment(kVariableMcCoyEvidenceMissed, 1); // unused? but consistent with missing the other clues
			return;  //true;
		}
	}
#endif // BLADERUNNER_ORIGINAL_BUGS
	//Added in all the unused Crystal clues. Essentially when McCoy puts a certain clue in the mainframe Crystal will receive it and when she does the correlating clue will appear
	// in her database and she will then later put it in the mainframe.
	
	if (Actor_Query_Goal_Number(kActorSteele) == kGoalSteeleGoToRC02) {
		if (_vm->_cutContent) {
			if (!Game_Flag_Query(kFlagRC51ChopstickWrapperTaken)
			) {		
				if (Game_Flag_Query(kFlagZubenIsReplicant)) {
					Actor_Clue_Acquire(kActorSteele, kClueChopstickWrapper, true, -1);
					Game_Flag_Set(kFlagRC51ChopstickWrapperTaken);

					if (Game_Flag_Query(kFlagRC51Discovered)) {
						Item_Remove_From_World(kItemChopstickWrapper);
					}

					Global_Variable_Increment(kVariableMcCoyEvidenceMissed, 1);
					return;  //true;
				}
			}
		} else {
			if (!Game_Flag_Query(kFlagRC51ChopstickWrapperTaken)
			&&  Random_Query(1, 3) == 1
				) {		
				Actor_Clue_Acquire(kActorSteele, kClueChopstickWrapper, true, -1);
				Game_Flag_Set(kFlagRC51ChopstickWrapperTaken);

				if (Game_Flag_Query(kFlagRC51Discovered)) {
					Item_Remove_From_World(kItemChopstickWrapper);
				}

				Global_Variable_Increment(kVariableMcCoyEvidenceMissed, 1);
				return;  //true;
			}
		}
		if (_vm->_cutContent) {
			if (!Game_Flag_Query(kFlagRC51CandyTaken)
			) {
				Actor_Clue_Acquire(kActorSteele, kClueCandy, true, -1);
				Game_Flag_Set(kFlagRC51CandyTaken);

				if (Game_Flag_Query(kFlagRC51Discovered)) {
					Item_Remove_From_World(kItemCandy);
				}
				return;  //true;
			}		
		} else {
			if (!Game_Flag_Query(kFlagRC51CandyTaken)
			&&  Random_Query(1, 3) == 1
			) {
				Actor_Clue_Acquire(kActorSteele, kClueCandy, true, -1);
				Game_Flag_Set(kFlagRC51CandyTaken);

				if (Game_Flag_Query(kFlagRC51Discovered)) {
					Item_Remove_From_World(kItemCandy);
				}
				return; //true;
			}
		}

		if (_vm->_cutContent) {
			if (!Game_Flag_Query(kFlagRC51ToyDogTaken)
			) {
				Actor_Clue_Acquire(kActorSteele, kClueToyDog, true, -1);
				Game_Flag_Set(kFlagRC51ToyDogTaken);

				if (Game_Flag_Query(kFlagRC51Discovered)) {
					Item_Remove_From_World(kItemToyDog);
				}
				return; //true;
			}
		} else {
			if (!Game_Flag_Query(kFlagRC51ToyDogTaken)
			&&  Random_Query(1, 20) == 1
			) {
				Actor_Clue_Acquire(kActorSteele, kClueToyDog, true, -1);
				Game_Flag_Set(kFlagRC51ToyDogTaken);

				if (Game_Flag_Query(kFlagRC51Discovered)) {
					Item_Remove_From_World(kItemToyDog);
				}	
				return; //true;
			}
		}
	}

	if ( Actor_Query_Goal_Number(kActorSteele) == kGoalSteeleGoToCT01
	 &&  Actor_Query_In_Set(kActorSteele, kSetCT03_CT04)
	 &&  Game_Flag_Query(kFlagCT04HomelessKilledByMcCoy)
	 && !Game_Flag_Query(kFlagCT04HomelessBodyInDumpster)
#if BLADERUNNER_ORIGINAL_BUGS
#else
	 && !Game_Flag_Query(kFlagCT04HomelessBodyThrownAway)
#endif // BLADERUNNER_ORIGINAL_BUGS
	 && !Game_Flag_Query(kFlagCT04HomelessBodyFound)
	) {
		Game_Flag_Set(kFlagCT04HomelessBodyFound);
		return; //true;
	}

	return; //false;
}

void AIScriptSteele::OtherAgentEnteredThisSet(int otherActorId) {
	// return false;
}

void AIScriptSteele::OtherAgentExitedThisSet(int otherActorId) {
	// return false;
}

void AIScriptSteele::OtherAgentEnteredCombatMode(int otherActorId, int combatMode) {
	if (otherActorId == kActorMcCoy
	 && Actor_Query_Goal_Number(kActorSteele) == 410
	)
		Actor_Set_Goal_Number(kActorSteele, kGoalSteeleKP03ShootMcCoy);
}

void AIScriptSteele::ShotAtAndMissed() {
	// return false;
}

bool AIScriptSteele::ShotAtAndHit() {
	if (Actor_Query_Goal_Number(kActorSteele) == kGoalSteeleNR01TalkToGordo) {
		Actor_Set_Goal_Number(kActorSteele, kGoalSteeleNR01PrepareShotByMcCoy);
	}

	if (/* !a1 && */ Actor_Query_In_Set(kActorSteele, kSetHF06))
		Non_Player_Actor_Combat_Mode_On(kActorSteele, kActorCombatStateUncover, true, kActorMcCoy, 15, kAnimationModeCombatIdle, kAnimationModeCombatWalk, kAnimationModeCombatRun, 0, 0, 100, 25, 300, false);

	return false;
}

void AIScriptSteele::Retired(int byActorId) {
	Game_Flag_Set(kFlagSteeleDead);

	if (Actor_Query_Goal_Number(kActorSteele) == 450) {
		Scene_Exits_Enable();
		Game_Flag_Set(kFlagKP03BombDisarmed);
	}

	if (Actor_Query_Goal_Number(kActorSteele) != kGoalSteeleGone) {
		Actor_Change_Animation_Mode(kActorSteele, kAnimationModeCombatDie);
		Actor_Set_Goal_Number(kActorSteele, kGoalSteeleGone);
	}
}

int AIScriptSteele::GetFriendlinessModifierIfGetsClue(int otherActorId, int clueId) {
	if (otherActorId != kActorMcCoy) {
		return 0;
	}

	switch (clueId) {
	case kClueMcCoyRecoveredHoldensBadge:
		// fall through
	case kClueMcCoyRetiredLucy:
		// fall through
	case kClueMcCoyRetiredDektora:
		// fall through
	case kClueMcCoyRetiredSadik:
		// fall through
	case kClueMcCoyShotZubenInTheBack:
		// fall through
	case kClueMcCoyRetiredLutherLance:
		// fall through
	case kClueClovisOrdersMcCoysDeath:
		// fall through
	case kClueMcCoyIsKind:
		// fall through
	if (!_vm->_cutContent) {
		case kClueMcCoyIsInsane:
			return 5;

		case kClueMcCoyKilledRunciter1:
			// fall through
		case kClueMcCoyShotGuzza:
			// fall through
		case kClueMcCoyKilledRunciter2:
			return 0; // TODO shouldn't this be a negative number?

		case kClueMcCoyLetZubenEscape:
			return -4;

		case kClueMcCoyWarnedIzo:
			// fall through
		case kClueMcCoyHelpedIzoIzoIsAReplicant:
			// fall through
		case kClueMcCoyHelpedDektora:
			// fall through
		case kClueMcCoyHelpedLucy:
			// fall through
		case kClueMcCoyHelpedGordo:
			return -5;

		case kClueMcCoyRetiredZuben:
			return 4;

		case kClueMcCoyIsStupid:
			return -3;

		case kClueMcCoyIsAnnoying:
			return -2;
		}
	}

	return 0;
}

double AIScriptSteele::comp_distance(int actorId, float a5, float a6, int a1, float a2, float a3, float a4) {
	float actorZ;
	float actorX;
	float actorY;

	Actor_Query_XYZ(actorId, &actorX, &actorY, &actorZ);
	return sqrt((a4 - actorZ) * (a4 - actorZ) + (a2 - actorX) * (a2 - actorX) + (a3 - actorY) * (a3 - actorY));
}

bool AIScriptSteele::GoalChanged(int currentGoalNumber, int newGoalNumber) {
	if (currentGoalNumber == kGoalSteeleGone) {
		return false;
	}

	switch (newGoalNumber) {
	// Chapter 1

	case kGoalSteeleGoToRC01:
		AI_Movement_Track_Flush(kActorSteele);
		AI_Movement_Track_Append(kActorSteele, 12, 5);
		AI_Movement_Track_Repeat(kActorSteele);
		return true;

	case kGoalSteeleGoToRC02:
		AI_Movement_Track_Flush(kActorSteele);
		AI_Movement_Track_Append(kActorSteele, 61, 30);
		AI_Movement_Track_Repeat(kActorSteele);
		return true;

	case kGoalSteeleGoToFreeSlotC1:
		AI_Movement_Track_Flush(kActorSteele);
		AI_Movement_Track_Append(kActorSteele, 35, 45);
		AI_Movement_Track_Repeat(kActorSteele);
		return true;

	case kGoalSteeleGoToFreeSlotG1:
		AI_Movement_Track_Flush(kActorSteele);
		Game_Flag_Set(kFlagSteeleInChinaTown);
		Game_Flag_Reset(kFlagSteeleInRunciters);
		AI_Movement_Track_Append(kActorSteele, 39, 45);
		AI_Movement_Track_Repeat(kActorSteele);
		return true;

	case kGoalSteeleGoToCT01:
		AI_Movement_Track_Flush(kActorSteele);
		if (_vm->_cutContent) {
			if (Random_Query(1, 2) == 1) {
				AI_Movement_Track_Append(kActorSteele, 63, 20);
			} else {
				AI_Movement_Track_Append(kActorSteele, 64, 10);
			}
		} else {
			if (Random_Query(1, 10) == 1) {
				AI_Movement_Track_Append(kActorSteele, 63, 20);
			} else {
				AI_Movement_Track_Append(kActorSteele, 64, 10);
			}
		}
		AI_Movement_Track_Repeat(kActorSteele);
		return true;

	case kGoalSteeleGoToFreeSlotC2:
		AI_Movement_Track_Flush(kActorSteele);
		AI_Movement_Track_Append(kActorSteele, 35, 45);
		AI_Movement_Track_Repeat(kActorSteele);
		return true;

	case kGoalSteeleGoToFreeSlotG2:
		AI_Movement_Track_Flush(kActorSteele);
		Game_Flag_Set(kFlagSteeleInPoliceStation);
		Game_Flag_Reset(kFlagSteeleInChinaTown);
		AI_Movement_Track_Append(kActorSteele, 39, 45);
		AI_Movement_Track_Repeat(kActorSteele);
		return true;

	case kGoalSteeleGoToPoliceShootingRange:
		AI_Movement_Track_Flush(kActorSteele);
		if (Random_Query(1, 2) == 1) {
			AI_Movement_Track_Append(kActorSteele, 19, 10);
		} else {
			AI_Movement_Track_Append(kActorSteele, 35, 30);
		}
		AI_Movement_Track_Repeat(kActorSteele);
		return true;

	case kGoalSteeleGoToPS02:
		AI_Movement_Track_Flush(kActorSteele);
		AI_Movement_Track_Append(kActorSteele, 62, 1);
		AI_Movement_Track_Repeat(kActorSteele);
		return true;

	case kGoalSteeleGoToFreeSlotG3:
		AI_Movement_Track_Flush(kActorSteele);
		Game_Flag_Reset(kFlagSteeleInPoliceStation);
		AI_Movement_Track_Append(kActorSteele, 39, 30);
		AI_Movement_Track_Repeat(kActorSteele);
		return true;

	case kGoalSteeleInterviewGrigorian:
		Actor_Clue_Acquire(kActorSteele, kClueGrigorianInterviewA, true, kActorGrigorian);
		if (Game_Flag_Query(kFlagIzoIsReplicant)) {
			Actor_Clue_Acquire(kActorSteele, kClueGrigorianInterviewB1, true, kActorGrigorian);
		} else {
			Actor_Clue_Acquire(kActorSteele, kClueGrigorianInterviewB2, true, kActorGrigorian);
		}
		Actor_Set_Goal_Number(kActorSteele, kGoalSteeleDefault);
		return true;

	// Chapter 2

	case kGoalSteeleApprehendIzo:
		AI_Movement_Track_Flush(kActorSteele);
		if (Game_Flag_Query(kFlagIzoIsReplicant)) {
			AI_Movement_Track_Append_Run(kActorSteele, 202, 0);
			AI_Movement_Track_Append_Run(kActorSteele, 203, 0);
		} else {
			AI_Movement_Track_Append(kActorSteele, 174, 0);
			AI_Movement_Track_Append_Run(kActorSteele, 175, 0);
		}
		AI_Movement_Track_Repeat(kActorSteele);
		return true;

	case kGoalSteeleGoToTB02:
		AI_Movement_Track_Flush(kActorSteele);
		AI_Movement_Track_Append(kActorSteele, 192, 0);
		AI_Movement_Track_Repeat(kActorSteele);
		return true;

	case kGoalSteeleLeaveTB02:
		Loop_Actor_Walk_To_XYZ(kActorSteele, -187.82f, 0.08f, 1460.74f, 0, false, false, false);
		Actor_Face_Heading(kActorSteele, 802, false);
		Loop_Actor_Travel_Stairs(kActorSteele, 10, false, kAnimationModeIdle);
		AI_Movement_Track_Flush(kActorSteele);
		AI_Movement_Track_Append(kActorSteele, 35, 0);
		AI_Movement_Track_Repeat(kActorSteele);
		return true;

	case kGoalSteeleGoToPoliceStation:
		if (Random_Query(1, 2) == 1) {
			Actor_Clues_Transfer_New_To_Mainframe(kActorSteele);
			Actor_Clues_Transfer_New_From_Mainframe(kActorSteele);
		}
		if (Query_Score(kActorMcCoy) > Query_Score(kActorSteele)
		 && Query_Score(kActorMcCoy) < 75
		) {
			Set_Score(kActorSteele, Random_Query(2, 5) + Query_Score(kActorMcCoy));
		}
		AI_Movement_Track_Flush(kActorSteele);
		AI_Movement_Track_Append(kActorSteele, 35, Random_Query(45, 120));
		AI_Movement_Track_Repeat(kActorSteele);
		return true;

	case kGoalSteeleWalkAround:
		AI_Movement_Track_Flush(kActorSteele);
		if (Random_Query(1, 5) == 1) { // Animoid row & Bradbury building
			AI_Movement_Track_Append(kActorSteele, 222, 0);
			AI_Movement_Track_Append_With_Facing(kActorSteele, 223, 3, 973);
			AI_Movement_Track_Append(kActorSteele, 224, 5);
			AI_Movement_Track_Append(kActorSteele, 216, 5);
			AI_Movement_Track_Append(kActorSteele, 217, 0);
			AI_Movement_Track_Append(kActorSteele, 218, 0);
			AI_Movement_Track_Append(kActorSteele, 210, 0);
			AI_Movement_Track_Append(kActorSteele, 211, 0);
			AI_Movement_Track_Append(kActorSteele, 204, 0);
			AI_Movement_Track_Append(kActorSteele, 205, 0);
			AI_Movement_Track_Append(kActorSteele, 206, 0);
			AI_Movement_Track_Append(kActorSteele, 39, 20);
			AI_Movement_Track_Append(kActorSteele, 35, 60);
			AI_Movement_Track_Append(kActorSteele, 39, 20);
			AI_Movement_Track_Append(kActorSteele, 228, 0);
			AI_Movement_Track_Append(kActorSteele, 229, 10);
			AI_Movement_Track_Repeat(kActorSteele);
		} else if (Random_Query(1, 3) == 1) { // Chinatown & DNA row
			AI_Movement_Track_Append(kActorSteele, 232, 0);
			AI_Movement_Track_Append(kActorSteele, 233, 0);
			AI_Movement_Track_Append(kActorSteele, 234, 3);
			AI_Movement_Track_Append(kActorSteele, 237, 0);
			AI_Movement_Track_Append(kActorSteele, 238, 0);
			AI_Movement_Track_Append(kActorSteele, 239, 0);
			AI_Movement_Track_Append(kActorSteele, 240, 10);
			AI_Movement_Track_Append(kActorSteele, 39, 120);
			AI_Movement_Track_Append(kActorSteele, 243, 0);
			AI_Movement_Track_Append(kActorSteele, 244, 10);
			AI_Movement_Track_Repeat(kActorSteele);
		} else { // Police station
			AI_Movement_Track_Append(kActorSteele, 248, 0);
			AI_Movement_Track_Append(kActorSteele, 249, 0);
			AI_Movement_Track_Append(kActorSteele, 250, 10);
			AI_Movement_Track_Append(kActorSteele, 253, 0);
			AI_Movement_Track_Append_With_Facing(kActorSteele, 254, 3, 1015);
			AI_Movement_Track_Append_With_Facing(kActorSteele, 255, 2, 1015);
			AI_Movement_Track_Append_With_Facing(kActorSteele, 256, 3, 1015);
			AI_Movement_Track_Append(kActorSteele, 257, 0);
			AI_Movement_Track_Append(kActorSteele, 39, 30);
			AI_Movement_Track_Append(kActorSteele, 35, 120);
			AI_Movement_Track_Append(kActorSteele, 39, 30);
			AI_Movement_Track_Repeat(kActorSteele);
		}
		return true;

	case kGoalSteeleShootIzo:
		if (_vm->_cutContent) {
			Actor_Force_Stop_Walking(kActorMcCoy);
			Sound_Play(kSfxSMCAL3, 100, 0, 0, 50);
			// Scene_Exits_Enable() is done in Izo's kGoalIzoDie - CompletedMovementTrack() case
			Actor_Set_Goal_Number(kActorIzo, kGoalIzoDie);
			Actor_Change_Animation_Mode(kActorMcCoy, kAnimationModeIdle);
			Actor_Face_Actor(kActorMcCoy, kActorSteele, true);
			Loop_Actor_Walk_To_Actor(kActorSteele, 0, 48, false, true);
			// Made it so Crystal is a 'little' nicer to McCoy if you have high friendliness with her.
			Actor_Face_Actor(kActorMcCoy, kActorSteele, true);
			Actor_Face_Actor(kActorSteele, kActorMcCoy, true);
			if (Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) > 52) {
				Actor_Says(kActorSteele, 2600, kAnimationModeTalk); //-	01-2600.AUD	Hey, Slim!
			} else {
				Actor_Says(kActorSteele, 1860, kAnimationModeTalk); //01-1860.AUD	You blew your retirement loot this time, Slim.	
				Actor_Says(kActorSteele, 2650, kAnimationModeTalk); //01-2650.AUD	No wonder you can’t afford a better suit.
				Actor_Says(kActorSteele, 2660, kAnimationModeTalk); //01-2660.AUD	Ever think of a new line of work?
				Actor_Says(kActorSteele, 2670, kAnimationModeTalk); //01-2670.AUD	Maybe you’ll have better luck finding that than all those skin-jobs that are running roughshod over you.
			}
			Actor_Says(kActorMcCoy, 4825, 18); //00-4825.AUD	What are you doing here?
			Actor_Face_Actor(kActorSteele, kActorIzo, true);
			Actor_Face_Actor(kActorMcCoy, kActorIzo, true);
			Actor_Says(kActorSteele, 1870, kAnimationModeTalk); //01-1870.AUD	Tracking this piece of shit.
			Actor_Face_Actor(kActorSteele, kActorMcCoy, true);
			Actor_Face_Actor(kActorMcCoy, kActorSteele, true);
			if (Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) > 52) {
				Actor_Says(kActorSteele, 2060, kAnimationModeTalk); //01-2060.AUD	What are you doing here, Slim?
			} else {
				Actor_Says(kActorSteele, 1880, kAnimationModeTalk); //01-1880.AUD	What are you doing here besides putting your nuts on the chopping block?
			}
			Actor_Says(kActorMcCoy, 4830, 13); //00-4830.AUD	Investigating Izo. Maybe we should compare notes.
			if (Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) > 52) {
				Actor_Says(kActorSteele, 2620, kAnimationModeTalk); //-	01-2620.AUD	There’s a first for everything.
			} else {
				Actor_Says(kActorSteele, 1890, kAnimationModeTalk); //01-1890.AUD	Maybe you should find another line of work.
				Actor_Says(kActorSteele, 1900, kAnimationModeTalk); //01-1900.AUD	Just in case I'm not around to bail you out next time.		
			}	
			Actor_Says(kActorSteele, 1910, kAnimationModeTalk); //01-1910.AUD	I'll wait for the uniforms. Why don't you grab yourself a slice of quiche or something.
			if (Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) > 52) {
				Actor_Face_Actor(kActorMcCoy, kActorIzo, true);
				Actor_Face_Actor(kActorSteele, kActorIzo, true);
				Actor_Says(kActorSteele, 90, kAnimationModeTalk); //01-0090.AUD	Just another stroll in the park.
				Actor_Clue_Acquire(kActorMcCoy, kClueCrystalRetiredIzo, true, kActorSteele);
			} else {
				Actor_Face_Actor(kActorSteele, kActorIzo, true);
				Actor_Face_Actor(kActorMcCoy, kActorIzo, true);
				Actor_Says(kActorSteele, 1920, kAnimationModeTalk); //01-1920.AUD	And pick up a bottle of scotch for the real Blade Runner, will ya?
				Actor_Face_Actor(kActorMcCoy, kActorSteele, true);
				Actor_Face_Actor(kActorSteele, kActorMcCoy, true); 
				if (Player_Query_Agenda() == kPlayerAgendaSurly
				||  Player_Query_Agenda() == kPlayerAgendaErratic) {
					Actor_Says(kActorMcCoy, 6295, 18); //00-6295.AUD	Who made you queen of the world?
				} else {
					Actor_Says(kActorMcCoy, 855, 18); //00-0855.AUD	What?
				}
				Actor_Says(kActorSteele, 1930, kAnimationModeTalk); //01-1930.AUD	Just kidding, Slim.
				Actor_Clue_Acquire(kActorMcCoy, kClueCrystalRetiredIzo, true, kActorSteele);
				Actor_Modify_Friendliness_To_Other(kActorSteele, kActorMcCoy, -1);
				Actor_Modify_Friendliness_To_Other(kActorGuzza, kActorMcCoy, -1);
				Actor_Modify_Friendliness_To_Other(kActorClovis, kActorMcCoy, -1);
			}
			Actor_Set_Goal_Number(kActorSteele, kGoalSteeleLeaveRC03);
		} else {
			Actor_Force_Stop_Walking(kActorMcCoy);
			Sound_Play(kSfxSMCAL3, 100, 0, 0, 50);
			// Scene_Exits_Enable() is done in Izo's kGoalIzoDie - CompletedMovementTrack() case
			Actor_Set_Goal_Number(kActorIzo, kGoalIzoDie);
			Actor_Change_Animation_Mode(kActorMcCoy, kAnimationModeIdle);
			Actor_Face_Actor(kActorMcCoy, kActorSteele, true);
			Loop_Actor_Walk_To_Actor(kActorSteele, 0, 48, false, true);
			Actor_Says(kActorSteele, 1860, kAnimationModeTalk); //01-1860.AUD	You blew your retirement loot this time, Slim.
			Actor_Face_Actor(kActorMcCoy, kActorSteele, true);
			Actor_Says(kActorMcCoy, 4825, 18); //00-4825.AUD	What are you doing here?
			Actor_Face_Actor(kActorSteele, kActorMcCoy, true);
			Actor_Says(kActorSteele, 1870, kAnimationModeTalk); //01-1870.AUD	Tracking this piece of shit.
			Actor_Says(kActorSteele, 1880, kAnimationModeTalk); //01-1880.AUD	What are you doing here besides putting your nuts on the chopping block?
			Actor_Says(kActorMcCoy, 4830, 13); //00-4830.AUD	Investigating Izo. Maybe we should compare notes.
			Actor_Says(kActorSteele, 1890, kAnimationModeTalk); //01-1890.AUD	Maybe you should find another line of work.
			Actor_Says(kActorSteele, 1900, kAnimationModeTalk); //01-1900.AUD	Just in case I'm not around to bail you out next time.
			Actor_Says(kActorSteele, 1910, kAnimationModeTalk); //01-1910.AUD	I'll wait for the uniforms. Why don't you grab yourself a slice of quiche or something.
			Actor_Face_Actor(kActorSteele, kActorIzo, true);
			Actor_Says(kActorSteele, 1920, kAnimationModeTalk); //01-1920.AUD	And pick up a bottle of scotch for the real Blade Runner, will ya?
			Actor_Face_Actor(kActorMcCoy, kActorSteele, true);
			Actor_Face_Actor(kActorSteele, kActorMcCoy, true); 
			Actor_Says(kActorSteele, 1930, kAnimationModeTalk); //01-1930.AUD	Just kidding, Slim.
			Actor_Set_Goal_Number(kActorSteele, kGoalSteeleLeaveRC03);
		}
#if BLADERUNNER_ORIGINAL_BUGS
		Player_Gains_Control(); // redundant - causes "WARNING: Unbalanced call to BladeRunnerEngine::playerGainsControl"
#endif // BLADERUNNER_ORIGINAL_BUGS
		return true;

	case kGoalSteeleArrestIzo:
		Actor_Force_Stop_Walking(kActorMcCoy);
		Actor_Face_Actor(kActorSteele, kActorIzo, true);
		Actor_Change_Animation_Mode(kActorIzo, kAnimationModeIdle);
		Actor_Face_Actor(kActorIzo, kActorSteele, true);
		Actor_Says_With_Pause(kActorSteele, 2010, 0.0f, kAnimationModeCombatIdle);
		Actor_Change_Animation_Mode(kActorSteele, kAnimationModeCombatIdle);
		Loop_Actor_Walk_To_Actor(kActorSteele, kActorIzo, 60, false, false);
		Actor_Change_Animation_Mode(kActorSteele, kAnimationModeCombatIdle);
		_animationState = 23;
		_animationFrame = 0;
		Actor_Says(kActorIzo, 660, kAnimationModeTalk);
		Actor_Says_With_Pause(kActorSteele, 2020, 0.0f, kAnimationModeCombatIdle);
		Actor_Says_With_Pause(kActorSteele, 2030, 0.0f, kAnimationModeCombatIdle);
		Actor_Change_Animation_Mode(kActorSteele, kAnimationModeCombatIdle);
		Actor_Says(kActorIzo, 670, kAnimationModeTalk);
		Actor_Says(kActorSteele, 2040, kAnimationModeCombatIdle);
		Actor_Says(kActorIzo, 680, kAnimationModeTalk);
		Actor_Says(kActorSteele, 2050, kAnimationModeTalk);
		Actor_Face_Actor(kActorSteele, kActorMcCoy, true);
		if (_vm->_cutContent) {
			Actor_Face_Actor(kActorMcCoy, kActorSteele, true);
		}
		Actor_Says(kActorSteele, 2060, kAnimationModeTalk); //01-2060.AUD	What are you doing here, Slim?
		if (_vm->_cutContent) {
			Loop_Actor_Walk_To_Actor(kActorMcCoy, kActorIzo, 36, false, true);
			Actor_Face_Actor(kActorMcCoy, kActorSteele, true);
			Actor_Face_Actor(kActorSteele, kActorMcCoy, true);
		}
		Actor_Says(kActorMcCoy, 4845, kAnimationModeTalk);
		Actor_Says(kActorSteele, 2070, kAnimationModeTalk); //01-2070.AUD	I've been tracking this boy for a week. He thinks he's pretty clever.
		if (_vm->_cutContent) {
			if (Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) > 52) {
				Actor_Says(kActorSteele, 2080, kAnimationModeTalk); //01-2080.AUD	He's a material witness in a case I'm working.
			}
		} else {
			Actor_Says(kActorSteele, 2080, kAnimationModeTalk); //01-2080.AUD	He's a material witness in a case I'm working.
		}
		Actor_Face_Actor(kActorSteele, kActorIzo, true);
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagSadikIsReplicant)) {
				Actor_Face_Actor(kActorMcCoy, kActorIzo, true);
				Actor_Says(kActorSteele, 2090, kAnimationModeTalk); //01-2090.AUD	In fact your best buddy's a Replicant, isn't he?
				Actor_Says_With_Pause(kActorSteele, 2100, 1.0f, kAnimationModeTalk);
				Actor_Says(kActorIzo, 690, kAnimationModeTalk);
				Actor_Says(kActorSteele, 2110, kAnimationModeTalk);
				Actor_Says(kActorSteele, 2120, kAnimationModeTalk); //01-2120.AUD	You'll be giving him up to me soon enough.
			}
		} else {
			Actor_Says(kActorSteele, 2090, kAnimationModeTalk); //01-2090.AUD	In fact your best buddy's a Replicant, isn't he?
			Actor_Says_With_Pause(kActorSteele, 2100, 1.0f, kAnimationModeTalk);
			Actor_Says(kActorIzo, 690, kAnimationModeTalk);
			Actor_Says(kActorSteele, 2110, kAnimationModeTalk);
			Actor_Says(kActorSteele, 2120, kAnimationModeTalk); //01-2120.AUD	You'll be giving him up to me soon enough.
		}
		Actor_Face_Actor(kActorSteele, kActorMcCoy, true); 
		if (_vm->_cutContent) {
			Actor_Face_Actor(kActorMcCoy, kActorSteele, true);
			if (Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) < 53) {
				Actor_Says(kActorSteele, 2140, kAnimationModeTalk); //01-2140.AUD	I can handle it from here, Slim. Why don't you go buy yourself a lollipop? Something else to suck on.
				if (Player_Query_Agenda() != kPlayerAgendaSurly 
				&& Player_Query_Agenda() != kPlayerAgendaErratic) {
					Actor_Says(kActorMcCoy, 4850, kAnimationModeTalk);
				} else {
					Actor_Says(kActorMcCoy, 665, 16); //00-0665.AUD	Real funny, pal.
				}
				Actor_Says(kActorSteele, 2150, kAnimationModeTalk); //01-2150.AUD	But I wasn't trying to be.
			} else {
				Actor_Says(kActorSteele, 90, kAnimationModeTalk); //01-0090.AUD	Just another stroll in the park.
			}
		} else {
			Actor_Says(kActorSteele, 2140, kAnimationModeTalk); //01-2140.AUD	I can handle it from here, Slim. Why don't you go buy yourself a lollipop? Something else to suck on.
			Actor_Says(kActorMcCoy, 4850, kAnimationModeTalk);
			Actor_Says(kActorSteele, 2150, kAnimationModeTalk); //01-2150.AUD	But I wasn't trying to be.
		}
		// Scene_Exits_Enable() is done in Izo's kGoalIzoGetArrested - CompletedMovementTrack() case
		Actor_Set_Goal_Number(kActorIzo, kGoalIzoGetArrested);
		Actor_Set_Goal_Number(kActorSteele, kGoalSteeleLeaveRC03);
		if (_vm->_cutContent) {
			Game_Flag_Set(kFlagIzoArrested);
		}
#if BLADERUNNER_ORIGINAL_BUGS
		Actor_Set_Goal_Number(kActorSteele, kGoalSteeleDefault); // TODO - a bug? why set to default here?
#endif // BLADERUNNER_ORIGINAL_BUGS
		return true;

	case kGoalSteeleIzoBlockedByMcCoy:
		Actor_Force_Stop_Walking(kActorMcCoy);
		Actor_Set_Goal_Number(kActorIzo, kGoalIzoRC03RunAway);
		Actor_Says(kActorSteele, 1940, kAnimationModeTalk);
		Loop_Actor_Walk_To_Actor(kActorSteele, kActorMcCoy, 60, false, true);
		Actor_Face_Actor(kActorSteele, kActorMcCoy, true);
		Actor_Face_Actor(kActorMcCoy, kActorSteele, true);
		Actor_Says(kActorSteele, 1950, kAnimationModeTalk);
		if (_vm->_cutContent) {
			if (Player_Query_Agenda() == kPlayerAgendaPolite) {
				Actor_Says(kActorMcCoy, 4835, 13); //00-4835.AUD	Sorry, I bet you can still catch him if you want.
				if (Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) > 52) {
					Delay(2000);
					Actor_Says(kActorSteele, 2110, 15); //01-2110.AUD	That's okay.
				} else {
					Actor_Says(kActorSteele, 1980, 60); //01-1980.AUD	If I didn't know any better, I'd think you wanted him to get away.
					if (Player_Query_Agenda() == kPlayerAgendaSurly 
					|| Player_Query_Agenda() == kPlayerAgendaErratic) { 
						Actor_Says(kActorMcCoy, 4840, 15); //00-4840.AUD	You crazy? I've been tailing him myself.
					} else {
						Actor_Says(kActorMcCoy, 7815, 13); //00-7815.AUD	No.
					}
					Actor_Says(kActorSteele, 1990, 60); //01-1990.AUD	A little word of advice, Slim. Stay out of my way.
					Actor_Says(kActorSteele, 2000, kAnimationModeTalk); //01-2000.AUD	Next time I'm not gonna worry about who's in my line of fire, understand?
					Actor_Modify_Friendliness_To_Other(kActorSteele, kActorMcCoy, -2);
					Actor_Modify_Friendliness_To_Other(kActorGuzza, kActorMcCoy, -2);
					Actor_Modify_Friendliness_To_Other(kActorClovis, kActorMcCoy, 2);
				}
			} else {
				Actor_Says(kActorMcCoy, 7835, 18); //00-7835.AUD	Is that so?
				if (Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) < 53) {
					Actor_Says(kActorSteele, 1980, 60); //01-1980.AUD	If I didn't know any better, I'd think you wanted him to get away.
					if (Player_Query_Agenda() == kPlayerAgendaSurly 
					|| Player_Query_Agenda() == kPlayerAgendaErratic) { 
						Actor_Says(kActorMcCoy, 4840, 15); //00-4840.AUD	You crazy? I've been tailing him myself.
					} else {
						Actor_Says(kActorMcCoy, 7815, 13); //00-7815.AUD	No.
					}
				}
				Actor_Says(kActorSteele, 1990, 60); //01-1990.AUD	A little word of advice, Slim. Stay out of my way.
				if (Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) < 53) {
					Actor_Says(kActorSteele, 2000, kAnimationModeTalk); //01-2000.AUD	Next time I'm not gonna worry about who's in my line of fire, understand?
				}
				Actor_Modify_Friendliness_To_Other(kActorSteele, kActorMcCoy, -2);
				Actor_Modify_Friendliness_To_Other(kActorGuzza, kActorMcCoy, -2);
				Actor_Modify_Friendliness_To_Other(kActorClovis, kActorMcCoy, 2);
			}
		} else {
			Actor_Says(kActorSteele, 1980, 60); //01-1980.AUD	If I didn't know any better, I'd think you wanted him to get away.
			Actor_Says(kActorMcCoy, 4840, 15); //00-4840.AUD	You crazy? I've been tailing him myself.		
			Actor_Says(kActorSteele, 1990, kAnimationModeTalk); //01-1990.AUD	A little word of advice, Slim. Stay out of my way.
			Actor_Says(kActorSteele, 2000, kAnimationModeTalk); //01-2000.AUD	Next time I'm not gonna worry about who's in my line of fire, understand?
		}
		Player_Gains_Control();
		Actor_Set_Goal_Number(kActorSteele, kGoalSteeleLeaveRC03);
		if (_vm->_cutContent) {
			Player_Gains_Control();
			Game_Flag_Set(kFlagIzoBlockedByMcCoy);
			Game_Flag_Set(kFlagIzoGotAway);
		}
		Scene_Exits_Enable();
		return true;

	case 126: // not used anywhere
		return true;

	case kGoalSteeleLeaveRC03:
		AI_Movement_Track_Flush(kActorSteele);
		AI_Movement_Track_Append(kActorSteele, 174, 0);
		AI_Movement_Track_Append(kActorSteele, 35, 0);
		AI_Movement_Track_Repeat(kActorSteele);
		return true;

	// Chapter 3

	case 200:
		AI_Movement_Track_Flush(kActorSteele);
		return true;

	case kGoalSteeleStartChapter3:
		if (Query_Score(kActorMcCoy) > Query_Score(kActorSteele)
		 && Query_Score(kActorMcCoy) < 75
		) {
			Set_Score(kActorSteele, Random_Query(2, 5) + Query_Score(kActorMcCoy));
		}

		if (Game_Flag_Query(kFlagBulletBobDead)) {
			Game_Flag_Set(kFlagSteeleKnowsBulletBobIsDead);
		}

		AI_Movement_Track_Flush(kActorSteele);
		Actor_Put_In_Set(kActorSteele, kSetFreeSlotC);
		Actor_Set_At_Waypoint(kActorSteele, 35, 0);
		return true;

	case kGoalSteeleNR11StartWaiting:
		AI_Countdown_Timer_Reset(kActorSteele, kActorTimerAIScriptCustomTask0);
		AI_Countdown_Timer_Start(kActorSteele, kActorTimerAIScriptCustomTask0, 15);
		return true;

	case kGoalSteeleNR11StopWaiting:
		AI_Countdown_Timer_Reset(kActorSteele, kActorTimerAIScriptCustomTask0);
		return true;

	case kGoalSteeleNR11Enter:
		if (comp_distance(kActorMcCoy, -4.0, 0.33f, 0.0f, 100.0f, 0.33f, -4.0f) < 48.0f) {
			Loop_Actor_Walk_To_XYZ(kActorMcCoy, 32.0f, 0.33f, 17.0f, 0, false, false, false);
		}
		AI_Countdown_Timer_Reset(kActorSteele, kActorTimerAIScriptCustomTask0);
		Player_Loses_Control();
		if (Actor_Query_Goal_Number(kActorDektora) == kGoalSteeleNR01ConfrontGordo) {
			Async_Actor_Walk_To_XYZ(kActorMcCoy, -15.53f, 0.33f, 73.49f, 0, false);
		}
		Actor_Put_In_Set(kActorSteele, kSetNR11);
		Actor_Set_At_XYZ(kActorSteele, 100.0f, -51.56f, 0.0, 0);
		_animationState = 10;
		_animationFrame = 0;
		return true;

	case kGoalSteeleNR11Entered:
		// fall through
	case 216:
		// fall through
	case kGoalSteeleNR01PrepareShotByMcCoy:
		return true;

	case kGoalSteeleNR11Decide:
		Player_Gains_Control();
		switch (Actor_Query_Goal_Number(kActorDektora)) {
		case kGoalDektoraNR11Hiding:
			Actor_Face_Heading(kActorMcCoy, 954, false);
			Actor_Change_Animation_Mode(kActorSteele, kAnimationModeCombatIdle);
			Delay(2000);
			Actor_Says(kActorSteele, 1700, 58);
			if (_vm->_cutContent) {
				if (!Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)
				&& !Actor_Clue_Query(kActorDektora, kClueMcCoyHelpedDektora)) {
					Actor_Says(kActorMcCoy, 3800, 3); //00-3800.AUD	It’s gotta be around here somewhere.
				} else {
					Actor_Says(kActorMcCoy, 7815, 13); //00-7815.AUD	No.
				}
			} else {
				Actor_Says(kActorMcCoy, 3800, 3);
			}
			Actor_Says(kActorSteele, 1710, 59);
			Actor_Set_Goal_Number(kActorSteele, kGoalSteeleNR11Shoot);
			break;

		case kGoalDektoraNR11WalkAway:
			Actor_Face_Actor(kActorSteele, kActorDektora, true);
			Actor_Says(kActorSteele, 1790, 3); //01-1790.AUD	We having fun yet?
			Actor_Face_Actor(kActorMcCoy, kActorSteele, true);
			Actor_Face_Actor(kActorSteele, kActorMcCoy, true);
			Actor_Says(kActorMcCoy, 3830, 17); //00-3830.AUD	Oh, yeah.
			Actor_Says(kActorSteele, 1800, 17); //01-1800.AUD	You should have waited for me, Slim.
			Actor_Says(kActorMcCoy, 3835, 18); //00-3835.AUD	I had the shot, so I took it.
			Actor_Says(kActorSteele, 1810, 16); //01-1810.AUD	(smacks lips) We’ll see who has it next time.
			Game_Flag_Set(kFlagDektoraRanAway);
			Actor_Set_Goal_Number(kActorDektora, kGoalDektoraGone);
			Actor_Set_Goal_Number(kActorSteele, kGoalSteeleNRxxGoToSpinner);
			break;

		case kGoalDektoraNR11FallThroughWindow:
			if (!_vm->_cutContent) {
				Actor_Modify_Friendliness_To_Other(kActorSteele, kActorMcCoy, 6);
			}
			if (_vm->_cutContent) {
				Music_Play(kMusicBRBlues, 52, 0, 2, -1, kMusicLoopPlayOnce, 1);
			}
			Actor_Says(kActorSteele, 1750, 12);
			if (_vm->_cutContent) {
				if (Player_Query_Agenda() == kPlayerAgendaSurly 
				|| Player_Query_Agenda() == kPlayerAgendaErratic) {
					Actor_Says(kActorMcCoy, 3815, 19); //00-3815.AUD	I think we can safely say that one’s in bio-mechanical purgatory.
				} else {
					Actor_Says(kActorMcCoy, 5705, 19); //00-5705.AUD	Uh-huh.
				}
			} else {
				Actor_Says(kActorMcCoy, 3815, 19);
			}
			Actor_Says(kActorSteele, 1760, 13); //01-1760.AUD	You had to clear out everything else up here too.
			if (_vm->_cutContent) {
				if (Player_Query_Agenda() == kPlayerAgendaSurly 
				|| Player_Query_Agenda() == kPlayerAgendaErratic) {
					Actor_Voice_Over(180, kActorVoiceOver); //99-0180.AUD	Sometimes my trigger finger starts to itch.
				} else if (Player_Query_Agenda() == kPlayerAgendaPolite) { 
					Actor_Says(kActorMcCoy, 7980, 19); //00-7980.AUD	Yeah. Maybe.
				} else {
					Actor_Says(kActorMcCoy, 8535, 13); //00-8535.AUD	Yeah.
				}
				Delay(500);
				Actor_Says(kActorSteele, 2110, 14); //01-2110.AUD	That's okay.
				Delay(1000);
				Actor_Clue_Acquire(kActorClovis, kClueMcCoyRetiredDektora, true, kActorSteele);
				Actor_Clue_Acquire(kActorMcCoy, kClueMcCoyRetiredDektora, true, kActorSteele);
				Actor_Clue_Acquire(kActorLucy, kClueMcCoyRetiredDektora, true, kActorSteele);
				Game_Flag_Reset(kFlagMcCoyIsHelpingReplicants);
				Game_Flag_Set(kFlagMcCoyRetiredReplicant);
				Actor_Modify_Friendliness_To_Other(kActorSteele, kActorMcCoy, 2);
				Actor_Modify_Friendliness_To_Other(kActorClovis, kActorMcCoy, -4);
				Actor_Modify_Friendliness_To_Other(kActorGuzza, kActorMcCoy, 2);
				Actor_Modify_Friendliness_To_Other(kActorGaff, kActorMcCoy, 2);
				if (Query_Difficulty_Level() != kGameDifficultyEasy) {
					Global_Variable_Increment(kVariableChinyen, 200);
				}
			}
			if (_vm->_cutContent) {
				if (!Game_Flag_Query(kFlagEarlyQDead)
				&& !Game_Flag_Query(kFlagNR04EarlyQStungByScorpions)) {
					Actor_Says(kActorMcCoy, 3820, 18); //00-3820.AUD	Hope Early’s got insurance.
					Actor_Says(kActorSteele, 1770, 14); 
				}
			} else {
				Actor_Says(kActorMcCoy, 3820, 18); //00-3820.AUD	Hope Early’s got insurance.
				Actor_Says(kActorSteele, 1770, 14); 
			}
			if (_vm->_cutContent) {
				if (Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) > 59) {
					Actor_Says(kActorSteele, 1780, 15); 
					if (Player_Query_Agenda() == kPlayerAgendaSurly 
					|| Player_Query_Agenda() == kPlayerAgendaErratic) {
						Actor_Says(kActorMcCoy, 3825, 14); //00-3825.AUD	Next time.
					}
				}
			} else {
				Actor_Says(kActorSteele, 1780, 15); 
				Actor_Says(kActorMcCoy, 3825, 14);		
			}
			if (_vm->_cutContent) {
				Actor_Says(kActorSteele, 1740, 15); //01-1740.AUD	Come on, let’s blow while the getting's good.
				Actor_Says(kActorSteele, 140, 14); //01-0140.AUD	Maybe Guzza's got some answers about those guys who grabbed you up.
			}
			Game_Flag_Set(kFlagDektoraRanAway);
			Actor_Set_Goal_Number(kActorDektora, kGoalDektoraGone);
			Actor_Set_Goal_Number(kActorSteele, kGoalSteeleNRxxGoToSpinner);
		}
		return true;

	case kGoalSteeleNR11Shoot:
		Game_Flag_Set(kFlagNR11SteeleShoot);
		Actor_Change_Animation_Mode(kActorSteele, kAnimationModeCombatAttack);
		Scene_Exits_Disable();
		return true;

	case kGoalSteeleNR01WaitForMcCoy:
		AI_Movement_Track_Flush(kActorSteele);
		Actor_Put_In_Set(kActorSteele, kSetNR01);
		Actor_Set_At_XYZ(kActorSteele, 94.03f, 23.88f, -794.46f, 685);
		return true;

	case kGoalSteeleNR01GoToNR08:
		AI_Movement_Track_Flush(kActorSteele);
		Actor_Put_In_Set(kActorSteele, kSetNR05_NR08);
		Actor_Set_At_XYZ(kActorSteele, -1034.09f, 0.32f, 224.77f, 440);
		Game_Flag_Set(kFlagChapter4Starting);
		Set_Enter(kSetNR05_NR08, kSceneNR08);
		return true;

	case kGoalSteeleRC03GoToAR02:
		AI_Movement_Track_Flush(kActorSteele);
		Actor_Put_In_Set(kActorSteele, kSetAR01_AR02);
		Actor_Set_At_XYZ(kActorSteele, -250.43, 0.57, -741.23, 372);
		Set_Enter(kSetAR01_AR02, kSceneAR02);
		return true;
		
	case kGoalSteeleNR01GoToNR02:
		Game_Flag_Set(kFlagNR01toNR02);
		Set_Enter(kSetNR02, kSceneNR02);
		return true;

	case kGoalSteeleNR01GoToHF03:
		Game_Flag_Set(kFlagHF01toHF03);
		Game_Flag_Reset(kFlagMcCoyInNightclubRow);
		Game_Flag_Set(kFlagMcCoyInHysteriaHall);
		Actor_Put_In_Set(kActorSteele, kSetHF03);
		Actor_Set_At_XYZ(kActorSteele, 291.0f, 47.76f, -892.0f, 453);
		Set_Enter(kSetHF03, kSceneHF03);
		return true;

	case kGoalSteeleHF03McCoyChasingLucy:
		AI_Movement_Track_Flush(kActorSteele);
		AI_Movement_Track_Append_Run(kActorSteele, 372, 0);
		AI_Movement_Track_Append(kActorSteele, 35, 0);
		AI_Movement_Track_Repeat(kActorSteele);
		return true;

	case kGoalSteeleNR08WalkOut:
		AI_Movement_Track_Flush(kActorSteele);
		AI_Movement_Track_Append_Run(kActorSteele, 467, 0);
		AI_Movement_Track_Append(kActorSteele, 35, 0);
		AI_Movement_Track_Repeat(kActorSteele);
		return true;

	case kGoalSteeleNR10Wait:
		Actor_Put_In_Set(kActorSteele, kSetNR10);
		Actor_Set_At_XYZ(kActorSteele, -118.13f, 2.84f, -197.90f, 305);
		return true;

	case kGoalSteeleHF02ConfrontLucy:
		AI_Movement_Track_Flush(kActorSteele);
		AI_Movement_Track_Flush(kActorLucy);
		Actor_Put_In_Set(kActorSteele, kSetHF02);
		Actor_Set_At_XYZ(kActorSteele, 254.94f, 47.76f, -262.58f, 210);
		Actor_Put_In_Set(kActorLucy, kSetHF02);
		Actor_Set_At_XYZ(kActorLucy, 596.49f, 47.76f, -260.04f, 731);
		return true;

	case kGoalSteeleHF02ShootLucy:
		if (_vm->_cutContent) {
			Music_Stop(1u);
			if (!Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
				Actor_Says(kActorMcCoy, 1595, 14); //00-1595.AUD	Everybody out of the way!
			} else {
				Actor_Says(kActorMcCoy, 8955, 16); //00-8955.AUD	Stop!
			}
			Actor_Says(kActorLucy, 330, 16); //06-0330.AUD	Please, please don’t!
		}
		Actor_Change_Animation_Mode(kActorSteele, kAnimationModeCombatAttack);
		Delay(500);
		Actor_Change_Animation_Mode(kActorLucy, kAnimationModeDie);
		Actor_Set_Targetable(kActorLucy, false);
		Actor_Retired_Here(kActorLucy, 36, 18, true, -1);
		Delay(1000);
		AI_Movement_Track_Flush(kActorSteele);
		AI_Movement_Track_Append_Run(kActorSteele, 380, 0);
		AI_Movement_Track_Repeat(kActorSteele);
		Delay(500);
		if (_vm->_cutContent) {
			Music_Play(kMusicCrysDie1, 25, 0, 1, -1, kMusicLoopPlayOnce, 0);
		}
		ADQ_Add(kActorLucy, 340, kAnimationModeDie);
		return true;

	case kGoalSteeleHF02LucyShotBySteele:
		AI_Movement_Track_Flush(kActorSteele);
		Player_Loses_Control();
		Delay(500);
		if (_vm->_cutContent) {
			if (Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) < 60) {
				Actor_Says(kActorSteele, 0, 14); //01-0000.AUD	Easy money. You missed the boat this time, Slim.
			} else {
				Actor_Says(kActorSteele, 1080, 17); //01-1080.AUD	I really must be sick. I actually live for those moments.
			}
		} else {
			Actor_Says(kActorSteele, 1080, 17); //01-1080.AUD	I really must be sick. I actually live for those moments.
		}
		Actor_Face_Actor(kActorMcCoy, kActorSteele, true);
		Actor_Says(kActorMcCoy, 1540, 16); //00-1540.AUD	Hope we were right about her.
		Actor_Says(kActorSteele, 10, 13); //01-0010.AUD	I wouldn’t worry about ‘em.
		Actor_Says(kActorSteele, 20, 18); //01-0020.AUD	No matter how smart the make ‘em, they just ain’t smart enough.
		Actor_Says(kActorMcCoy, 1545, 13); //00-1545.AUD	What'd it say?
		Actor_Face_Actor(kActorSteele, kActorMcCoy, true);
		Actor_Says(kActorSteele, 30, 18); //01-0030.AUD	The last gasp? Something about a lake and trees.
		Actor_Says(kActorSteele, 40, 18); //01-0040.AUD	Maybe she’ll see ‘em in the next life.
		Actor_Says(kActorMcCoy, 1550, 13); //00-1550.AUD	You’re cruel and unusual.
		if (_vm->_cutContent) {
			if (Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) > 59) {
				Actor_Face_Actor(kActorSteele, kActorLucy, true);
				Actor_Face_Actor(kActorMcCoy, kActorLucy, true);
				Actor_Says(kActorSteele, 50, 12); //01-0050.AUD	That’s funny. Sometimes I actually feel bad for these poor Lolita models. 
				if (Player_Query_Agenda() != kPlayerAgendaSurly 
				&& Player_Query_Agenda() != kPlayerAgendaErratic) {
					Actor_Says(kActorMcCoy, 1555, 13); //00-1555.AUD	You do?
				} else {
					Actor_Says(kActorMcCoy, 8190, -1);	// 00-8190.AUD	Why?
				}
				Actor_Says(kActorSteele, 60, 12); //01-0060.AUD	There ain’t nothing in this world, even a skin-job, who deserves to be sold into sexual slavery.
				Actor_Face_Actor(kActorSteele, kActorMcCoy, true);
				Actor_Face_Actor(kActorMcCoy, kActorSteele, true);
				Actor_Says(kActorSteele, 80, 16); //01-0080.AUD	That Tyrell is one sick dude.
				Delay(1000);
			}
		} else {
			Actor_Face_Actor(kActorSteele, kActorLucy, true);
			Actor_Says(kActorSteele, 50, 12); //01-0050.AUD	That’s funny. Sometimes I actually feel bad for these poor Lolita models. 
			Actor_Says(kActorMcCoy, 1555, 13); //00-1555.AUD	You do?
			Actor_Says(kActorSteele, 60, 12); //01-0060.AUD	There ain’t nothing in this world, even a skin-job, who deserves to be sold into sexual slavery.
			Actor_Face_Actor(kActorSteele, kActorMcCoy, true);
			Actor_Says(kActorSteele, 80, 16); //01-0080.AUD	That Tyrell is one sick dude.
			Actor_Says(kActorMcCoy, 1560, 13); //00-1560.AUD	Commerce is our business.
		}
		if (_vm->_cutContent) {
			Delay(1000);
			Actor_Says(kActorSteele, 1740, 15); //01-1740.AUD	Come on, let’s blow while the getting's good.
			Actor_Says(kActorSteele, 140, 14); //01-0140.AUD	Maybe Guzza's got some answers about those guys who grabbed you up.
			Actor_Modify_Friendliness_To_Other(kActorSteele, kActorMcCoy, -1);
			Actor_Modify_Friendliness_To_Other(kActorClovis, kActorMcCoy, -1);
			Actor_Modify_Friendliness_To_Other(kActorGuzza, kActorMcCoy, -1);
		}
		Delay(500);
		Game_Flag_Set(kFlagSpinnerMissing);
		Player_Gains_Control();
		if (Game_Flag_Query(kFlagSpinnerAtNR01)) {
			Actor_Put_In_Set(kActorSteele, kSetNR01);
			Actor_Set_At_XYZ(kActorSteele, 12.17f, 23.88f, -533.37f, 674);
			Game_Flag_Reset(kFlagSpinnerAtNR01);
			Game_Flag_Reset(kFlagSpinnerAtHF01);
			Set_Enter(kSetNR01, kSceneNR01);
		} else {
			Actor_Put_In_Set(kActorSteele, kSetHF01);
			Actor_Set_At_XYZ(kActorSteele, 324.32f, 8.0f, -465.87f, 674);
			Game_Flag_Reset(kFlagSpinnerAtNR01);
			Game_Flag_Reset(kFlagSpinnerAtHF01);
			if (_vm->_cutContent) {
				Game_Flag_Set(kFlagHF02toHF01);
				Set_Enter(kSetHF01, kSceneHF01);
			} else {
				Set_Enter(kSetHF01, kSceneHF04);
			}
		}
		return true;

	case kGoalSteeleHF02LucyRanAway:
		Player_Loses_Control();
		Delay(500);
		Actor_Put_In_Set(kActorSteele, kSetHF02);
		Actor_Set_At_XYZ(kActorSteele, 254.94f, 47.76f, -262.58f, 210);
		return true;

	case kGoalSteeleHF02LucyShotByMcCoy:
		Actor_Face_Actor(kActorMcCoy, kActorSteele, true);
		// Added in some dialogue along with the McCoy retired Lucy clue.
		Actor_Says(kActorMcCoy, 1560, 14); //00-1560.AUD	Commerce is our business.
		Actor_Face_Actor(kActorSteele, kActorMcCoy, true);
		if (_vm->_cutContent) {
			Actor_Says(kActorSteele, 90, 13); //01-0090.AUD	Just another stroll in the park.
		}
		Actor_Says(kActorSteele, 100, 13); //01-0100.AUD	Unless Tyrell can design a faster brain processor, I’m gonna get pretty damn bored with this gig.
		if (_vm->_cutContent) {
			Actor_Says(kActorMcCoy, 1575, 13); //00-1575.AUD	You don’t feel bad about juicing a little girl?
			if (Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) < 60) {
				Actor_Says(kActorSteele, 120, 15); //She was an it, Slim. Don’t you forget that.
			} else {
				Actor_Says(kActorSteele, 50, 12); //01-0050.AUD	That’s funny. Sometimes I actually feel bad for these poor Lolita models. 
				Actor_Says(kActorMcCoy, 1555, 13); //00-1555.AUD	You do?
				Actor_Says(kActorSteele, 60, 12); //01-0060.AUD	There ain’t nothing in this world, even a skin-job, who deserves to be sold into sexual slavery.
				Actor_Says(kActorSteele, 80, 16); //01-0080.AUD	That Tyrell is one sick dude.
			}
		} else {
			Actor_Says(kActorMcCoy, 1575, 13); //00-1575.AUD	You don’t feel bad about juicing a little girl?
			Actor_Says(kActorSteele, 120, 15); //She was an it, Slim. Don’t you forget that.
		}
		if (_vm->_cutContent) {
			Delay(1000);
			Actor_Says(kActorSteele, 1740, 15); //01-1740.AUD	Come on, let’s blow while the getting's good.
			Actor_Says(kActorSteele, 140, 14); //01-0140.AUD	Maybe Guzza's got some answers about those guys who grabbed you up.
			Actor_Clue_Acquire(kActorMcCoy, kClueMcCoyRetiredLucy, true, kActorSteele);
		}
		Actor_Set_Goal_Number(kActorSteele, kGoalSteeleHFxxGoToSpinner);
		return true;

	case kGoalSteeleHF02LucyLostByMcCoy:
		Actor_Face_Actor(kActorSteele, kActorMcCoy, true);
		Actor_Says(kActorSteele, 150, 13);
		Actor_Face_Actor(kActorMcCoy, kActorSteele, true);
		Actor_Says(kActorMcCoy, 1580, 13); //00-1580.AUD	She got away.
		if (_vm->_cutContent) {
			if (Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) < 60) {
				Actor_Says(kActorSteele, 160, 14); //01-0160.AUD	How the hell did it get away? We had it cornered.
				Actor_Says(kActorMcCoy, 1585, 16); //00-1585.AUD	This one must be pretty damn clever.
			} else {
				Delay(1000);
				Actor_Says(kActorSteele, 2110, 14); //01-2110.AUD	That's okay.
				Actor_Voice_Over(190, kActorVoiceOver); //99-0190.AUD	If only we had a target range worth a damn back at the station.
			}
		} else {
			Actor_Says(kActorSteele, 160, 14); //01-0160.AUD	How the hell did it get away? We had it cornered.
			Actor_Says(kActorMcCoy, 1585, 16); //00-1585.AUD	This one must be pretty damn clever.
		}	
		if (_vm->_cutContent) {
			if (Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) < 60) {
				Delay(1000);
				Actor_Says(kActorSteele, 170, 16); //01-0170.AUD	What’s the problem, Slim?
				Actor_Says(kActorSteele, 180, 17); //01-0180.AUD	If you can’t even retire a freaking Lolita, how do you expect to dance with a combat Six?
				Actor_Says(kActorMcCoy, 1590, 17);
				Actor_Says(kActorSteele, 200, 15); //01-0200.AUD	Don’t even ask me who’d be doing the leading, Rookie.
			}
		} else {
			Actor_Says(kActorSteele, 170, 16); //01-0170.AUD	What’s the problem, Slim?
			Actor_Says(kActorSteele, 180, 17); //01-0180.AUD	If you can’t even retire a freaking Lolita, how do you expect to dance with a combat Six?
			Actor_Says(kActorMcCoy, 1590, 17);
			Actor_Says(kActorSteele, 200, 15); //01-0200.AUD	Don’t even ask me who’d be doing the leading, Rookie.
		}
		Actor_Set_Goal_Number(kActorSteele, kGoalSteeleHFxxGoToSpinner);
		return true;

	case kGoalSteeleHFxxGoToSpinner:
		Actor_Says(kActorSteele, 130, 13); //01-0130.AUD	Let’s go find your Spinner. Report in.
		Actor_Says(kActorSteele, 140, 13); //01-0140.AUD	Maybe Guzza's got some answers about those guys who grabbed you up.

		Delay(500);
		Game_Flag_Set(kFlagSpinnerMissing);
		Player_Gains_Control();
		if (Game_Flag_Query(kFlagSpinnerAtNR01)) {
			Actor_Put_In_Set(kActorSteele, kSetNR01);
			Actor_Set_At_XYZ(kActorSteele, 12.17f, 23.88f, -533.37f, 674);
			Game_Flag_Reset(kFlagSpinnerAtNR01);
			Game_Flag_Reset(kFlagSpinnerAtHF01);
			Set_Enter(kSetNR01, kSceneNR01);
		} else {
			Actor_Put_In_Set(kActorSteele, kSetHF01);
			Actor_Set_At_XYZ(kActorSteele, 324.32f, 8.0f, -465.87f, 674);
			Game_Flag_Reset(kFlagSpinnerAtNR01);
			Game_Flag_Reset(kFlagSpinnerAtHF01);
			Set_Enter(kSetHF01, kSceneHF01);
		}
		return true;

	case kGoalSteeleNR01ConfrontGordo:
		AI_Movement_Track_Flush(kActorSteele);
		Actor_Put_In_Set(kActorSteele, kSetNR01);
		Actor_Set_At_XYZ(kActorSteele, 94.03f, 23.88f, -794.46f, 685);
		if (Game_Flag_Query(kFlagSpinnerAtNR01)) {
			Game_Flag_Reset(kFlagSpinnerAtNR01);
			Game_Flag_Reset(kFlagSpinnerAtHF01);
		}
		Game_Flag_Set(kFlagSteeleAimingAtGordo);
		Actor_Change_Animation_Mode(kActorSteele, kAnimationModeIdle);
		_varChooseIdleAnimation = 3;
		return true;

	case kGoalSteeleNR01TalkToGordo:
		Actor_Set_Targetable(kActorSteele, true);
		return true;

	case kGoalSteeleNR01ShootGordo:
		Player_Loses_Control();
		Actor_Change_Animation_Mode(kActorSteele, kAnimationModeCombatAttack);
		Sound_Play(kSfxSMCAL3, 100, 0, 0, 50);
		Game_Flag_Reset(kFlagSteeleAimingAtGordo);
		Actor_Set_Targetable(kActorSteele, false);
		Actor_Set_Goal_Number(kActorGordo, kGoalGordoNR01Die);
		Delay(1500);
		Player_Set_Combat_Mode(false);
		Actor_Says(kActorSteele, 1070, 14);
		Actor_Face_Actor(kActorSteele, kActorMcCoy, true);
		if (_vm->_cutContent) {
			if (Player_Query_Agenda() == kPlayerAgendaSurly 
			|| Player_Query_Agenda() == kPlayerAgendaErratic) {
				Actor_Says(kActorMcCoy, 3065, 18); //00-3065.AUD	Sure took your time with him.
			}
		}
		if (_vm->_cutContent) {
			if (Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) < 60) {
				Actor_Says(kActorSteele, 1260, 16); //01-1260.AUD	Screwed the pooch, Slim.
			} else {
				Delay(1000);
			} 
		} else {
			Actor_Says(kActorSteele, 1260, 16); //01-1260.AUD	Screwed the pooch, Slim.
		}
		Actor_Says(kActorSteele, 1270, 13); //01-1270.AUD	If you were just a little faster, the retirement money would have been yours.
		Actor_Face_Actor(kActorMcCoy, kActorSteele, true);
		if (_vm->_cutContent) {
			if (!Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
				Actor_Says(kActorMcCoy, 3065, 18);
				if (Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) < 60) {
					Actor_Says(kActorSteele, 1280, 13); //01-1280.AUD	This is the real world, Slim. Not some candy-ass video game.
				} else {
					Actor_Says(kActorSteele, 2620, kAnimationModeTalk); //01-2620.AUD	There’s a first for everything.
					Actor_Says(kActorMcCoy, 3935, 13);	// Thanks.
					if (Query_Difficulty_Level() != kGameDifficultyEasy) {
						Global_Variable_Increment(kVariableChinyen, 100);
					}
				}
			}
		} else {
			Actor_Says(kActorMcCoy, 3065, 18);
			Actor_Says(kActorSteele, 1280, 13); //01-1280.AUD	This is the real world, Slim. Not some candy-ass video game.
		}
		Actor_Says(kActorSteele, 1290, 13); 
		//Added in a clue.
		if (_vm->_cutContent) {
			Actor_Modify_Friendliness_To_Other(kActorSteele, kActorMcCoy, -1);
			Actor_Modify_Friendliness_To_Other(kActorClovis, kActorMcCoy, -1);
			Actor_Modify_Friendliness_To_Other(kActorGuzza, kActorMcCoy, -1);
			Actor_Clue_Acquire(kActorMcCoy, kClueCrystalRetiredGordo, true, kActorSteele);
		}
		Game_Flag_Set(kFlagGordoRanAway);
		Player_Gains_Control();
		if (Game_Flag_Query(kFlagSpinnerAtHF01)) {
			Actor_Put_In_Set(kActorSteele, kSetHF01);
			Actor_Set_At_XYZ(kActorSteele, 324.32f, 8.0f, -465.87f, 674);
			Game_Flag_Set(kFlagSpinnerMissing);
			Game_Flag_Reset(kFlagSpinnerAtNR01);
			Game_Flag_Reset(kFlagSpinnerAtHF01);
			Set_Enter(kSetHF01, kSceneHF01);
		} else {
			Actor_Set_Goal_Number(kActorSteele, kGoalSteeleTalkAboutMissingSpinner);
		}
		return true;

	case kGoalSteeleNR01ShootMcCoy:
		ADQ_Flush();
		Actor_Change_Animation_Mode(kActorSteele, kAnimationModeCombatAttack);
		Sound_Play(kSfxSMCAL3, 100, 0, 0, 50);
		Actor_Force_Stop_Walking(kActorMcCoy);
		Actor_Change_Animation_Mode(kActorMcCoy, kAnimationModeDie);
		Actor_Retired_Here(kActorMcCoy, 12, 12, true, -1);
		Actor_Set_Goal_Number(kActorGordo, kGoalGordoNR01ReleaseHostage);
		if (_vm->_cutContent) {
			Actor_Says(kActorSteele, 1240, kAnimationModeTalk); //01-1240.AUD	Move!
		}
		Actor_Says(kActorSteele, 1250, kAnimationModeTalk);
		return true;

	case kGoalSteeleNR01McCoyShotGordo:
		Game_Flag_Reset(kFlagSteeleAimingAtGordo);
		ADQ_Flush();
		Game_Flag_Set(kFlagGordoRanAway);
		Actor_Set_Targetable(kActorSteele, false);
		Delay(1000);
		Player_Set_Combat_Mode(false);
		Player_Loses_Control();
		_animationState = 40;
		_animationFrame = 0;
		Delay(2000);
		Actor_Change_Animation_Mode(kActorSteele, kAnimationModeIdle);
		Actor_Change_Animation_Mode(kActorMcCoy, kAnimationModeIdle);
		Actor_Face_Actor(kActorSteele, kActorMcCoy, true);
		Actor_Says(kActorSteele, 1080, 17); //01-1080.AUD	I really must be sick. I actually live for those moments.
		Actor_Face_Actor(kActorMcCoy, kActorSteele, true);
		if (_vm->_cutContent) {
			if (Player_Query_Agenda() != kPlayerAgendaSurly 
			&& Player_Query_Agenda() != kPlayerAgendaErratic) {
				Actor_Says(kActorMcCoy, 3025, 14);
				if (Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) < 60) {
					Actor_Says(kActorSteele, 2620, kAnimationModeTalk); //01-2620.AUD	There’s a first for everything.
					if (Query_Difficulty_Level() > kGameDifficultyEasy) {
						Global_Variable_Increment(kVariableChinyen, 100);
					}
				} else {
					Actor_Says(kActorSteele, 1090, 16); //01-1090.AUD	Nah, you nailed it. This one’s yours, Slim.
					if (Query_Difficulty_Level() > kGameDifficultyEasy) {
						Global_Variable_Increment(kVariableChinyen, 200);
					}
				}
			}	
		} else {
			Actor_Says(kActorMcCoy, 3025, 14);
			Actor_Says(kActorSteele, 1090, 16); //01-1090.AUD	Nah, you nailed it. This one’s yours, Slim.
		}
		Actor_Face_Actor(kActorSteele, kActorGordo, true);
		if (_vm->_cutContent) {
			Actor_Face_Actor(kActorMcCoy, kActorGordo, true);
		}
		Actor_Says(kActorSteele, 1100, 13); //01-1100.AUD	Pathetic. Maybe he wasn’t a combat model after all.
		Actor_Says(kActorSteele, 1110, 17); //01-1110.AUD	Heard Tyrell was making a few lounge act versions. You know, for the troop shows Off-World.
		if (_vm->_cutContent) {
			if (Player_Query_Agenda() == kPlayerAgendaSurly 
			|| Player_Query_Agenda() == kPlayerAgendaErratic) {
				Actor_Says(kActorMcCoy, 3030, 19); //00-3030.AUD	His act certainly left room for improvement.
				Actor_Face_Actor(kActorSteele, kActorMcCoy, true);
				Actor_Face_Actor(kActorMcCoy, kActorSteele, true);
				Actor_Says(kActorSteele, 1130, 15);
		 	} else {
				Actor_Face_Actor(kActorSteele, kActorMcCoy, true);
				Actor_Face_Actor(kActorMcCoy, kActorSteele, true);
			}
		} else {
			Actor_Says(kActorMcCoy, 3030, 19); //00-3030.AUD	His act certainly left room for improvement.
			Actor_Face_Actor(kActorSteele, kActorMcCoy, true);
			Actor_Says(kActorSteele, 1130, 15);
		}
		Actor_Says(kActorSteele, 1140, 12);
		// Flag is reset and friendliness towards Steele is altered when McCoy shoots Gordo.
		if (_vm->_cutContent) {
			Game_Flag_Set(kFlagMcCoyShotGordoHostage);
			Game_Flag_Set(kFlagMcCoyRetiredReplicant);
			Game_Flag_Reset(kFlagMcCoyIsHelpingReplicants);
			Actor_Clue_Acquire(kActorMcCoy, kClueMcCoyRetiredGordo, true, kActorSteele);
			Actor_Clue_Acquire(kActorLucy, kClueMcCoyRetiredGordo, true, -1);
			Actor_Clue_Acquire(kActorDektora, kClueMcCoyRetiredGordo, true, -1);
			Actor_Modify_Friendliness_To_Other(kActorSteele, kActorMcCoy, 2);
			Actor_Modify_Friendliness_To_Other(kActorClovis, kActorMcCoy, -2);
			Actor_Modify_Friendliness_To_Other(kActorGuzza, kActorMcCoy, 2);
			Actor_Modify_Friendliness_To_Other(kActorGaff, kActorMcCoy, 2);
		}
		Player_Gains_Control();
		Actor_Set_Goal_Number(kActorSteele, kGoalSteeleTalkAboutMissingSpinner);
		return true;

	case kGoalSteeleNR01McCoyShotGun:
		ADQ_Flush();
		Actor_Change_Animation_Mode(kActorMcCoy, kAnimationModeCombatAttack);
		Sound_Play(kSfxSMCAL3, 100, 0, 0, 50);
		_animationState = 38;
		_animationFrame = 0;
		Actor_Set_Goal_Number(kActorGordo, kGoalGordoNR01ReleaseHostage);
		Game_Flag_Reset(kFlagSteeleAimingAtGordo);
		Game_Flag_Set(kFlagGordoRanAway);
		Actor_Set_Targetable(kActorSteele, false);
		Player_Loses_Control();
		return true;

	case kGoalSteeleNR01TalkAboutShotGun:
		Actor_Face_Actor(kActorSteele, kActorMcCoy, true);
		Actor_Says(kActorSteele, 1160, 15); //01-1160.AUD	Dah! What the hell?! Now we’ll never catch it.
		Actor_Face_Actor(kActorMcCoy, kActorSteele, true);
		Actor_Says(kActorMcCoy, 3035, 14); //00-3035.AUD	You were gonna shoot!
		if (_vm->_cutContent) {
			if (Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) < 60) {
				Actor_Says(kActorSteele, 1170, 16); //01-1170.AUD	Damn straight!
				if (Player_Query_Agenda() == kPlayerAgendaPolite) {
					Actor_Says(kActorMcCoy, 3040, 15); //00-3040.AUD	What about the hostage?
					Actor_Says(kActorSteele, 1180, 16); //01-1180.AUD	A small price to pay to juice that skin-job.
				}
			} else {
				Delay(1000);
			}
		} else {
			Actor_Says(kActorSteele, 1170, 16); //01-1170.AUD	Damn straight!
			Actor_Says(kActorMcCoy, 3040, 15); //00-3040.AUD	What about the hostage?
			Actor_Says(kActorSteele, 1180, 16); //01-1180.AUD	A small price to pay to juice that skin-job.
		}
		Actor_Says(kActorMcCoy, 3045, 15); //00-3045.AUD	You think Bryant is gonna keep you on if you start wasting civilians in the middle of the street?
		Actor_Says(kActorMcCoy, 3055, 15); //00-3055.AUD	I just saved your job, Steele.
		if (_vm->_cutContent) {
			if (Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) < 60) {
				Actor_Says(kActorSteele, 1190, 16); //01-1190.AUD	I can’t believe you took a shot at me!
				Actor_Says(kActorMcCoy, 3060, 15); //00-3060.AUD	At your gun. There’s a difference.
				Actor_Says(kActorSteele, 1200, 16); //01-1200.AUD	Yeah, about three inches!
			} else {
				Delay(2000);
			}
		} else {
			Actor_Says(kActorSteele, 1190, 16); //01-1190.AUD	I can’t believe you took a shot at me!
			Actor_Says(kActorMcCoy, 3060, 15); //00-3060.AUD	At your gun. There’s a difference.
			Actor_Says(kActorSteele, 1200, 16); //01-1200.AUD	Yeah, about three inches!
		}
		Actor_Says(kActorSteele, 1210, 14); //01-1210.AUD	We’d better call this in. Maybe we can seal off the sewers and get a search team out here. Your vehicle close by?
		if (_vm->_cutContent) {
			Actor_Clue_Acquire(kActorMcCoy, kClueMcCoyHelpedGordo, true, kActorSteele);
			Game_Flag_Set(kFlagMcCoyIsHelpingReplicants);
			Game_Flag_Set(kFlagGordoEscaped);
			Actor_Modify_Friendliness_To_Other(kActorSteele, kActorMcCoy, -2);
			Actor_Modify_Friendliness_To_Other(kActorClovis, kActorMcCoy, 2);
			Actor_Modify_Friendliness_To_Other(kActorGuzza, kActorMcCoy, -2);
		} else {
			Actor_Modify_Friendliness_To_Other(kActorSteele, kActorMcCoy, -5);
			Actor_Modify_Friendliness_To_Other(kActorClovis, kActorMcCoy, 2);
		}
		Player_Set_Combat_Mode(false);
		Music_Stop(2u);
		Player_Gains_Control();
		Actor_Set_Goal_Number(kActorSteele, kGoalSteeleTalkAboutMissingSpinner);
		return true;

	case kGoalSteeleNR01ShotByMcCoy:
		ADQ_Flush();
		Player_Loses_Control();
		Game_Flag_Reset(kFlagSteeleAimingAtGordo);
		Actor_Set_Targetable(kActorSteele, false);
		Actor_Set_Goal_Number(kActorGordo, kGoalGordoNR01ReleaseHostage);
		Actor_Start_Speech_Sample(kActorSteele, 1150);
		Actor_Change_Animation_Mode(kActorSteele, kAnimationModeCombatDie);
		Delay(5000);
		Actor_Set_Goal_Number(kActorMcCoy, kGoalMcCoyArrested);
		return true;

	case kGoalSteeleNRxxGoToSpinner:
		Delay(500);
		
		Game_Flag_Set(kFlagSpinnerMissing);
		Player_Gains_Control();
		if (Game_Flag_Query(kFlagSpinnerAtNR01)) {
			Actor_Put_In_Set(kActorSteele, kSetNR01);
			Actor_Set_At_XYZ(kActorSteele, 12.17f, 23.88f, -533.37f, 674);
			Game_Flag_Reset(kFlagSpinnerAtNR01);
			Game_Flag_Reset(kFlagSpinnerAtHF01);
			Set_Enter(kSetNR01, kSceneNR01);
		} else {
			Actor_Put_In_Set(kActorSteele, kSetHF01);
			Actor_Set_At_XYZ(kActorSteele, 324.32f, 8.0f, -465.87f, 674);
			Game_Flag_Reset(kFlagSpinnerAtNR01);
			Game_Flag_Reset(kFlagSpinnerAtHF01);
			Set_Enter(kSetHF01, kSceneHF01);
		}
		return true;

	case kGoalSteeleTalkAboutMissingSpinner:
		Actor_Says(kActorMcCoy, 2970, 15);
		if (_vm->_cutContent) {
			Music_Play(kMusicBRBlues, 52, 0, 2, -1, kMusicLoopPlayOnce, 1);
		}
		Actor_Face_Actor(kActorSteele, kActorMcCoy, true);
		Actor_Says(kActorSteele, 840, 16);
		Actor_Says(kActorMcCoy, 2975, 15);
		if (_vm->_cutContent) {
			if (Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) < 60) {
				Actor_Says(kActorSteele, 850, 16); //01-0850.AUD	Maybe you’re living in an alternate reality, Slim.
			}
		} else {
			Actor_Says(kActorSteele, 850, 16); //01-0850.AUD	Maybe you’re living in an alternate reality, Slim.
		}
		Actor_Says(kActorDispatcher, 0, kAnimationModeTalk);
		Actor_Says(kActorDispatcher, 10, kAnimationModeTalk);
		//Added in a dispatcher line and a clue.
		if (_vm->_cutContent) {
			Actor_Says(kActorDispatcher, 20, kAnimationModeTalk); //38-0020.AUD	Photo and descriptive information available on ESPER.
			Actor_Clue_Acquire(kActorMcCoy, kClueMcCoysDescription, true, kActorDispatcher);
		}
		Actor_Face_Actor(kActorMcCoy, kActorSteele, true);
		Actor_Says(kActorMcCoy, 2980, 12); 	
		if (_vm->_cutContent) {
			if (Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) > 59) {
				Actor_Says(kActorSteele, 860, 14); //01-0860.AUD	Maybe they just want to bring you in for questioning.
			} else {
				Actor_Says(kActorSteele, 1380, 14); //01-1380.AUD	Is it true, Slim? Did you kill somebody?
			}
		} else {
			Actor_Says(kActorSteele, 860, 14); //01-0860.AUD	Maybe they just want to bring you in for questioning.
		}
		// Made it so if McCoy actually did shoot Izo he won't say the line I didn't kill Izo.
		if (_vm->_cutContent) {
			if (!Game_Flag_Query(kFlagMcCoyShotIzo)) {
				Actor_Says(kActorMcCoy, 2985, 13); //00-2985.AUD	I didn’t kill Izo.
			} else {
				Actor_Says(kActorMcCoy, 8320, 15); //00-8320.AUD	Really?
			}
		} else {
			Actor_Says(kActorMcCoy, 2985, 13); //00-2985.AUD	I didn’t kill Izo.
		}
		Actor_Says(kActorSteele, 870, 15); //01-0870.AUD	Hm, maybe they... think you’re not what you think you are.
		Actor_Says(kActorMcCoy, 2990, 16);
		if (_vm->_cutContent) {
			Delay(2000);
			if (Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
				Actor_Says(kActorSteele, 880, 17); //01-0880.AUD	The look on your face after that last one?
				Actor_Says(kActorSteele, 890, 18); //01-0890.AUD	The minute you start to feel something for skin-jobs you’re in big trouble.
				if (Player_Query_Agenda() == kPlayerAgendaPolite) { 
					Actor_Says(kActorMcCoy, 2995, 12); //00-2995.AUD	Maybe I just got too much empathy.
					if (Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) < 60) {
						Actor_Says(kActorSteele, 900, 13); //01-0900.AUD	In all the wrong places.
					}
				}
			}
		} else {
			Actor_Says(kActorSteele, 880, 17);
			Actor_Says(kActorSteele, 890, 18);
			Actor_Says(kActorMcCoy, 2995, 12);
			Actor_Says(kActorSteele, 900, 13);
		}
		if (_vm->_cutContent) {
			Actor_Says(kActorSteele, 1370, 12); //01-1370.AUD	The uniforms know you’re down here. They already towed your Spinner.
			Actor_Says(kActorMcCoy, 3125, 15); //00-3125.AUD	I was wondering where it went.
			Delay(1000);
		}
		Actor_Says(kActorMcCoy, 3000, 13); //00-3000.AUD	You wanna put me on the Machine?
		if (_vm->_cutContent) {
			if (Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) < 60) {
				Actor_Says(kActorSteele, 1390, 13); //01-1390.AUD	I ain’t sure yet. I like to be sure.
			} else {
				Actor_Says(kActorSteele, 920, 12); //01-0920.AUD	Hey! I don’t want anything, Slim. You’re the one they want.
			}
		} else {
			Actor_Says(kActorSteele, 920, 12); //01-0920.AUD	Hey! I don’t want anything, Slim. You’re the one they want.
		}
		Actor_Says(kActorDispatcher, 30, kAnimationModeTalk);
		Actor_Says(kActorMcCoy, 3005, 14); //00-3005.AUD	What are you gonna do? Take me in?
		if (_vm->_cutContent) {
			if (Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) < 60) {
				Actor_Says(kActorSteele, 930, 16); //01-0930.AUD	No matter what they say, you’re not on my list yet, Slim. You know what that means.
				Actor_Says(kActorSteele, 950, 13); //01-0950.AUD	And there’s no use juicing you, if I can’t make some honest chinyen off it, you know?
				if (Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
					Actor_Says(kActorMcCoy, 3010, 15); //00-3010.AUD	I never appreciated your baser instincts so much.
				}
			} else if (Global_Variable_Query(kVariableAffectionTowards) == kAffectionTowardsDektora 
			&& Game_Flag_Query(kFlagDektoraIsReplicant)) {
				Actor_Says(kActorSteele, 930, 16); //01-0930.AUD	No matter what they say, you’re not on my list yet, Slim. You know what that means.
				Actor_Says(kActorSteele, 950, 13); //01-0950.AUD	And there’s no use juicing you, if I can’t make some honest chinyen off it, you know?
				if (Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
					Actor_Says(kActorMcCoy, 3010, 15); //00-3010.AUD	I never appreciated your baser instincts so much.
				}
			} else if (Global_Variable_Query(kVariableAffectionTowards) == kAffectionTowardsLucy 
			&& Game_Flag_Query(kFlagLucyIsReplicant)) {
				Actor_Says(kActorSteele, 930, 16); //01-0930.AUD	No matter what they say, you’re not on my list yet, Slim. You know what that means.
				Actor_Says(kActorSteele, 950, 13); //01-0950.AUD	And there’s no use juicing you, if I can’t make some honest chinyen off it, you know?
				if (Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
					Actor_Says(kActorMcCoy, 3010, 15); //00-3010.AUD	I never appreciated your baser instincts so much.
				}
			} else {
				Actor_Says(kActorSteele, 640, 12); //01-0640.AUD	No chance.
				Actor_Says(kActorSteele, 1420, 12); //01-1420.AUD	Go, if you’re going. I’m gonna talk to Guzza before I do anything.
				Actor_Says(kActorMcCoy, 8565, 15); //00-8565.AUD	Really?
				Actor_Says(kActorSteele, 960, 15); //01-0960.AUD	Guzza must have messed up somehow. I’ll check it out, see what’s going on and then...
			}
		} else {
			Actor_Says(kActorSteele, 930, 16); //01-0930.AUD	No matter what they say, you’re not on my list yet, Slim. You know what that means.
			Actor_Says(kActorSteele, 950, 13); //01-0950.AUD	And there’s no use juicing you, if I can’t make some honest chinyen off it, you know?
			Actor_Says(kActorMcCoy, 3010, 15); //00-3010.AUD	I never appreciated your baser instincts so much.
			Actor_Says(kActorSteele, 960, 15); //01-0960.AUD	Guzza must have messed up somehow. I’ll check it out, see what’s going on and then...
		}		
		Actor_Says(kActorSteele, 970, 13); //01-0970.AUD	We’ll be meeting again, Slim. You can bank on it.
		// If McCoy has establshed an affection rating with eiher Dektora or Lucy and is heading towards the car ending Crystal will say this ominous line. 
		// Some foreshadowing for the events of the car ending.
		if (_vm->_cutContent) {
			if (Global_Variable_Query(kVariableAffectionTowards) == kAffectionTowardsDektora 
			&& Game_Flag_Query(kFlagDektoraIsReplicant)) {
				Actor_Says(kActorMcCoy, 3140, 15); //00-3140.AUD	Thanks.
				Actor_Says(kActorSteele, 1430, 12); //01-1430.AUD	Don’t thank me yet. The next time you see me... (smacks lips twice) 
			} else if (Global_Variable_Query(kVariableAffectionTowards) == kAffectionTowardsLucy
			&& Game_Flag_Query(kFlagLucyIsReplicant)) {
				Actor_Says(kActorMcCoy, 3140, 15); //00-3140.AUD	Thanks.
				Actor_Says(kActorSteele, 1430, 12); //01-1430.AUD	Don’t thank me yet. The next time you see me... (smacks lips twice) 
			} else {
				Actor_Says(kActorMcCoy, 3015, 12); // 00-3015.AUD	You got a deal.	
				Actor_Says(kActorSteele, 980, 17); //01-0980.AUD	Now get cracking. Before I change my mind.
			}
			Music_Stop(1u);
		} else {
			Actor_Says(kActorMcCoy, 3015, 12); // 00-3015.AUD	You got a deal.	
			Actor_Says(kActorSteele, 980, 17); //01-0980.AUD	Now get cracking. Before I change my mind.
		}
		if (Player_Query_Current_Scene() == kSceneNR01) {
			Actor_Set_Goal_Number(kActorSteele, kGoalSteeleNR01StartChapter4);
		} else {
			Actor_Set_Goal_Number(kActorSteele, kGoalSteeleHF01StartChapter4);
		}
		return true;

	case kGoalSteeleImmediatelyStartChapter4:
		Actor_Set_Goal_Number(kActorSteele, kGoalSteeleNR01StartChapter4);
		return true;

	case kGoalSteeleNR01StartChapter4:
		Loop_Actor_Walk_To_XYZ(kActorMcCoy, -281.0f, 31.93f, -1061.0f, 0, false, true, false);
		Actor_Face_Heading(kActorMcCoy, 45, false);
		Loop_Actor_Travel_Stairs(kActorMcCoy, 3, false, kAnimationModeIdle);
		Global_Variable_Set(kVariableChapter, 4);
		Scene_Exits_Enable();
		Actor_Set_Health(kActorMcCoy, 50, 50);
		Game_Flag_Set(kFlagMutantsActive);
		Game_Flag_Set(kFlagNR01toUG06);
		Game_Flag_Set(kFlagChapter4Intro);
		Chapter_Enter(4, kSetUG06, kSceneUG06);
		return true;

	case kGoalSteeleHF01StartChapter4:
		Game_Flag_Set(kFlagChapter4Starting);
		Global_Variable_Set(kVariableChapter, 4);
		Scene_Exits_Enable();
		Game_Flag_Set(kFlagMutantsActive);
		Game_Flag_Set(kFlagChapter4Intro);
		Chapter_Enter(4, kSetUG06, kSceneUG06);
		return true;

	case kGoalSteeleStartChapter4:
		if (Query_Score(kActorMcCoy) > Query_Score(kActorSteele) && Query_Score(kActorMcCoy) < 75) {
			Set_Score(kActorSteele, Random_Query(2, 5) + Query_Score(kActorMcCoy));
		}
		if (Query_Score(kActorMcCoy) > Query_Score(kActorSteele) && Query_Score(kActorMcCoy) > 74) {
			Actor_Modify_Friendliness_To_Other(kActorSteele, kActorMcCoy, 3);
		}
		Actor_Set_Goal_Number(kActorSteele, 305);
		return true;

	case 305:
		Actor_Put_In_Set(kActorSteele, kSetFreeSlotC);
		Actor_Set_At_Waypoint(kActorSteele, 35, 0);
		return true;

	case kGoalSteeleStartChapter5:
		// fall through
	case 401:
		// fall through
	case kGoalSteeleKP01Left:
		return true;

	case 410:
		Actor_Set_Targetable(kActorSteele, true);
		Actor_Face_Actor(kActorSteele, kActorMcCoy, true);
		Actor_Start_Speech_Sample(kActorSteele, 2510);
		Actor_Change_Animation_Mode(kActorSteele, kAnimationModeCombatIdle);
		Actor_Face_Actor(kActorMcCoy, kActorSteele, true);
		Delay(3000);
		Async_Actor_Walk_To_XYZ(kActorSteele, -109.0f, -36.55f, 26.0f, 0, false);
		return true;

	case kGoalSteeleKP03Walk:
		Actor_Face_Actor(kActorMcCoy, kActorSteele, true);
		Actor_Says(kActorSteele, 430, 14);
		// If McCoy is on the Crystal betrayal path he will automatically let Crystal trigger the bomb.
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
				Player_Loses_Control();
			}
		}
		Actor_Change_Animation_Mode(kActorSteele, kAnimationModeCombatIdle);
		Delay(4000);
		Async_Actor_Walk_To_XYZ(kActorSteele, -109.0f, -36.55f, 26.0f, 0, false);
		return true;

	case kGoalSteeleKP03StopWalking:
		Actor_Force_Stop_Walking(kActorSteele);
		return true;

	case kGoalSteeleKP03Leave:
		Async_Actor_Walk_To_XYZ(kActorSteele, 1.0, -36.55f, 111.0f, 0, false);
		return true;

	case kGoalSteeleKP03Exploded:
		Actor_Force_Stop_Walking(kActorSteele);
		Actor_Change_Animation_Mode(kActorSteele, 51);
		AI_Countdown_Timer_Start(kActorSteele, kActorTimerAIScriptCustomTask1, 2);
		return true;

	case kGoalSteeleKP03Dying:
		Actor_Set_At_XYZ(kActorSteele, -48.83f, -36.55f, 69.98f, 280);
		Loop_Actor_Walk_To_Actor(kActorMcCoy, kActorSteele, 36, false, true);
		Actor_Face_Actor(kActorMcCoy, kActorSteele, true);
		// Fixed the code here. I forgot to make sure the betrayal dialogue only plays in cut content mode.
		// Also made it so McCoy receives the McCoy betrayal clue when he betrays Crystal.
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
				Actor_Says(kActorSteele, 400, 3); //01-0400.AUD	How could you… double cross me?
				Actor_Says(kActorMcCoy, 2165, 14);
				Actor_Says(kActorSteele, 410, 3);
				// Removed this line because it makes no sense for Crystal to kill Maggie if she likes McCoy and legitimately trusted him.
				Actor_Says(kActorSteele, 420, 3);
				// Made it so Sadik receives this clue so when you talk with him next Crystal getting blown up is mentioned in the conversation.
				// Also the player will now gain control.
				Actor_Clue_Acquire(kActorSadik, kClueMcCoyBetrayal, true, kActorSteele);
				Actor_Clue_Acquire(kActorMcCoy, kClueMcCoyBetrayal, true, kActorSteele);
				Actor_Set_Goal_Number(kActorSteele, kGoalSteeleGone);
				Player_Gains_Control();
			} else {
				Actor_Says(kActorSteele, 440, 3);
				if (Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) > 59) {
					Actor_Says(kActorMcCoy, 2175, 14); //00-2175.AUD	Hold on, I’ll get an ambulance out here.
				} else if (Player_Query_Agenda() != kPlayerAgendaSurly 
				&& Player_Query_Agenda() != kPlayerAgendaErratic) {
					Actor_Says(kActorMcCoy, 2175, 14); //00-2175.AUD	Hold on, I’ll get an ambulance out here.
				}
				Actor_Says(kActorSteele, 450, 3);
				Actor_Says(kActorSteele, 460, 3); //01-0460.AUD	Promise you’ll waste Clovis.
				if (Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) > 59) {
					Actor_Says(kActorMcCoy, 6805, 13); //00-6805.AUD	I-- I promise you. But for now we gotta be careful. You should stay hidden for a while.
				} else if (Player_Query_Agenda() != kPlayerAgendaSurly 
				&& Player_Query_Agenda() != kPlayerAgendaErratic) {
					Actor_Says(kActorMcCoy, 6805, 13); //00-6805.AUD	I-- I promise you. But for now we gotta be careful. You should stay hidden for a while.
				} else {
					Delay(1000);
				}
				if (Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) > 59) {
					Actor_Says(kActorSteele, 470, 3); //01-0470.AUD	Taught you pretty well, didn’t I?
				}
				Delay(2000);
				Actor_Says(kActorMcCoy, 3970, 14); //00-3970.AUD	Hey.
				Delay(2000);
				if (Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) > 59) {
					Actor_Says(kActorMcCoy, 2390, kAnimationModeIdle); //00-2390.AUD	Oh, God. No.
					Delay(2000);
				} else if (Player_Query_Agenda() != kPlayerAgendaSurly 
				&& Player_Query_Agenda() != kPlayerAgendaErratic) {
					Actor_Says(kActorMcCoy, 2390, kAnimationModeIdle); //00-2390.AUD	Oh, God. No.
					Delay(2000);
				}
				if (Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) > 59) {
					Actor_Says(kActorMcCoy, 2305, 13); //00-2305.AUD	I’m sorry.
				} else if (Player_Query_Agenda() != kPlayerAgendaSurly 
				&& Player_Query_Agenda() != kPlayerAgendaErratic) {
					Actor_Says(kActorMcCoy, 2305, 13); //00-2305.AUD	I’m sorry.
				} else {
					Actor_Says(kActorMcCoy, 170, 19); //00-0170.AUD	Damn.
				}
				Actor_Set_Goal_Number(kActorSteele, kGoalSteeleGone);
			}
		} else {
			Actor_Says(kActorSteele, 440, 3);
			Actor_Says(kActorMcCoy, 2175, 14);
			Actor_Says(kActorSteele, 450, 3);
			Actor_Says(kActorSteele, 460, 3);
			Actor_Says(kActorSteele, 470, 3);
		}
		AI_Countdown_Timer_Start(kActorSteele, kActorTimerAIScriptCustomTask1, 3);
		return true;

	case kGoalSteeleKP03ShootMcCoy:
		Actor_Face_Actor(kActorSteele, kActorMcCoy, true);
		Actor_Change_Animation_Mode(kActorSteele, kAnimationModeCombatAttack);
		Actor_Change_Animation_Mode(kActorMcCoy, kAnimationModeDie);
		Actor_Retired_Here(kActorMcCoy, 72, 18, true, -1);
		return true;

	case kGoalSteeleKP03Dead:
		Actor_Set_Targetable(kActorSteele, false);
		Game_Flag_Set(kFlagSteeleDead);
		Actor_Set_Goal_Number(kActorSteele, kGoalSteeleGone);
		Actor_Retired_Here(kActorSteele, 60, 12, true, -1);
		return true;

	case kGoalSteeleKP01Wait:
		if (!_vm->_cutContent) {
			Actor_Put_In_Set(kActorSteele, kSetKP01);
			Actor_Set_At_XYZ(kActorSteele, 20.0f, -12.2f, -97.0f, 907);
			Actor_Change_Animation_Mode(kActorSteele, 43);
		}
		return true;

	case kGoalSteeleKP01TalkToMcCoy:
		Game_Flag_Reset(kFlagSteeleSmoking);
		// Removed the delay so the conversation happens immediately.
		if (!_vm->_cutContent) {
			Delay(2000);
		}
		Actor_Face_Actor(kActorSteele, kActorMcCoy, true);
		if (_vm->_cutContent) {
			if (Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) < 60) {
				Actor_Says(kActorSteele, 360, -1); //01-0360.AUD	About time you got here.
				Loop_Actor_Walk_To_Actor(kActorMcCoy, kActorSteele, 48, false, false);
			} else {
				Actor_Says(kActorSteele, 2600, kAnimationModeTalk); //01-2600.AUD	Hey, Slim!
				Loop_Actor_Walk_To_Actor(kActorMcCoy, kActorSteele, 48, false, false);
			}
		} else {
			Actor_Says(kActorSteele, 360, -1); //01-0360.AUD	About time you got here.
			Loop_Actor_Walk_To_Actor(kActorMcCoy, kActorSteele, 48, false, false);
		}
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)
			|| Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) < 60) {
				Actor_Says(kActorMcCoy, 2150, 14);
				Actor_Says(kActorSteele, 370, 15);
			} else {
				Actor_Says(kActorMcCoy, 6185, 19); //00-6185.AUD	(sighs) You got any idea how glad I am to see ya?
				Actor_Says(kActorSteele, 2350, 13); //01-2350.AUD	Ditto.
				Delay(1000);
			}	
		} else {
			Actor_Says(kActorMcCoy, 2150, 14);
			Actor_Says(kActorSteele, 370, 15);
		}
		Actor_Says(kActorMcCoy, 2155, 12); //00-2155.AUD	I got a little hung up. Where’s the moonbus?
		Actor_Says(kActorSteele, 380, 16);
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
				Actor_Says(kActorMcCoy, 8535, 13); //00-8535.AUD	Yeah.
			} else {
				Actor_Says(kActorMcCoy, 2160, 18); //00-2160.AUD	Hell, yeah.
			}
		} else {
			Actor_Says(kActorMcCoy, 2160, 18); //00-2160.AUD	Hell, yeah.
		}
		Actor_Says(kActorSteele, 390, 13);
		Actor_Set_Goal_Number(kActorSteele, kGoalSteeleKP01Leave);
		return true;

	case kGoalSteeleKP01Leave:
		AI_Movement_Track_Flush(kActorSteele);
		AI_Movement_Track_Append(kActorSteele, 530, 0);
		AI_Movement_Track_Repeat(kActorSteele);
		return true;

	case kGoalSteeleKP05Enter:
		Actor_Put_In_Set(kActorSteele, kSetKP05_KP06);
		Actor_Set_At_XYZ(kActorSteele, -1110.0f, 0.0f, 952.0f, 155);
		Actor_Change_Animation_Mode(kActorSteele, kAnimationModeCombatIdle);
		return true;

	case kGoalSteeleKP05Leave:
		AI_Movement_Track_Flush(kActorSteele);
		AI_Movement_Track_Append_Run(kActorSteele, 541, 0);
		AI_Movement_Track_Repeat(kActorSteele);
		return true;

	case kGoalSteeleKP06Enter:
		Actor_Set_At_Waypoint(kActorSteele, 542, 0);
		AI_Movement_Track_Flush(kActorSteele);
		AI_Movement_Track_Append_Run(kActorSteele, 543, 0);
		AI_Movement_Track_Repeat(kActorSteele);
		return true;

	case kGoalSteeleKP06Leave:
		AI_Movement_Track_Flush(kActorSteele);
		AI_Movement_Track_Append_Run(kActorSteele, 542, 0);
		AI_Movement_Track_Repeat(kActorSteele);
		return true;

	case 450:
		if (!_vm->_cutContent) {
			Actor_Put_In_Set(kActorSteele, kSetKP05_KP06);
			Actor_Set_At_XYZ(kActorSteele, -947.39f, 0.0f, 728.89f, 0);
		}
		return true;

	case 499:
		AI_Movement_Track_Flush(kActorSteele);
		Actor_Put_In_Set(kActorSteele, kSetKP05_KP06);
		Actor_Set_At_XYZ(kActorSteele, -782.15f, 8.26f, -263.64f, 52);
		return true;

	default:
		return false;
	}
}

bool AIScriptSteele::UpdateAnimation(int *animation, int *frame) {
	switch (_animationState) {
	case 0:
		switch (_varChooseIdleAnimation) {
		case 0:
			*animation = kModelAnimationSteeleIdle;
			++_animationFrame;
			if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationSteeleIdle)) {
				_animationFrame = 0;
				if (Game_Flag_Query(kFlagSteeleSmoking)) {
					_animationState = 41;
					_varChooseIdleAnimation = 1;
					_varNumOfTimesToHoldCurrentFrame = 0;
				}
			}
			break;

		case 1:
			Game_Flag_Set(kFlagSteeleSmoking);
			_animationState = 41;
			_varChooseIdleAnimation = 1;
			_varNumOfTimesToHoldCurrentFrame = 0;
			break;

		case 3:
			*animation = kModelAnimationSteeleWithGunAimingToRightIdle;
			++_animationFrame;
			if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationSteeleWithGunAimingToRightIdle)) {
				_animationFrame = 0;
			}
			break;
		}
		break;

	case 1:
		_animationFrame = 0;
		*animation = _animationNext;
		_animationState = _animationStateNext;
		break;

	case 2:
		*animation = kModelAnimationSteeleWalking;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(*animation)) {
			_animationFrame = 0;
		}
		break;

	case 3:
		*animation = kModelAnimationSteeleRunning;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(*animation)) {
			_animationFrame = 0;
		}
		break;

	case 4:
		*animation = kModelAnimationSteeleWithGunWalking;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(*animation)) {
			_animationFrame = 0;
		}
		break;

	case 5:
		*animation = kModelAnimationSteeleWithGunRunning;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(*animation)) {
			_animationFrame = 0;
		}
		break;

	case 6:
		*animation = kModelAnimationSteeleClimbStairsUp;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(*animation)) {
			_animationFrame = 0;
		}
		break;

	case 7:
		*animation = kModelAnimationSteeleClimbStairsDown;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(*animation)) {
			_animationFrame = 0;
		}
		break;

	case 8:
		*animation = kModelAnimationSteeleWithGunClimbStairsUp;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(*animation)) {
			_animationFrame = 0;
		}
		break;

	case 9:
		*animation = kModelAnimationSteeleWithGunClimbStairsDown;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(*animation)) {
			_animationFrame = 0;
		}
		break;

	case 10:
		*animation = kModelAnimationSteeleClimbUpTrapDoor;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(*animation)) {
			Actor_Change_Animation_Mode(kActorSteele, kAnimationModeIdle);
			*animation = kModelAnimationSteeleIdle;
			_animationFrame = 0;
			_animationState = 0;
			if (Actor_Query_Goal_Number(kActorSteele) == kGoalSteeleNR11Enter) {
				Actor_Set_Goal_Number(kActorSteele, kGoalSteeleNR11Entered);
			}
		}
		break;

	case 11:
		*animation = kModelAnimationSteeleClimbLadderUp;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(*animation)) {
			_animationFrame = 0;
		}
		break;

	case 12:
		*animation = kModelAnimationSteeleClimbLadderDown;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(*animation)) {
			_animationFrame = 0;
		}
		break;

	case 13:
		*animation = kModelAnimationSteeleHopOffLadderDown;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(*animation)) {
			_animationFrame = 0;
			_animationState = 0;
		}
		break;

	case 14:
		*animation = kModelAnimationSteeleATalk;
		if (_animationFrame == 0 && _resumeIdleAfterFramesetCompletesFlag
		) {
			*animation = kModelAnimationSteeleIdle;
			_animationFrame = 0;
			_animationState = 0;
			_resumeIdleAfterFramesetCompletesFlag = false;
		} else {
			++_animationFrame;
			if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(*animation) - 1) {
				_animationFrame = 0;
			}
		}
		break;

	case 15:
		*animation = kModelAnimationSteeleBTalk;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(*animation) - 1) {
			_animationFrame = 0;
			_animationState = 14;
			*animation = kModelAnimationSteeleATalk;
		}
		break;

	case 16:
		*animation = kModelAnimationSteeleSmallLeftHandMoveTalk;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(*animation) - 1) {
			_animationFrame = 0;
			_animationState = 14;
			*animation = kModelAnimationSteeleATalk;
		}
		break;

	case 17:
		*animation = kModelAnimationSteeleProtestTalk;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(*animation) - 1) {
			_animationFrame = 0;
			_animationState = 14;
			*animation = kModelAnimationSteeleATalk;
		}
		break;

	case 18:
		*animation = kModelAnimationSteeleDismissTalk;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(*animation) - 1) {
			_animationFrame = 0;
			_animationState = 14;
			*animation = kModelAnimationSteeleATalk;
		}
		break;

	case 19:
		*animation = kModelAnimationSteeleDismissTalk;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(*animation) - 1) {
			_animationFrame = 0;
			_animationState = 14;
			*animation = kModelAnimationSteeleATalk;
		}
		break;

	case 20:
		*animation = kModelAnimationSteeleWithGunAimingTalk;
		if (_animationFrame == 0 && _resumeIdleAfterFramesetCompletesFlag
		) {
			_animationFrame = 0;
			_animationState = 23;
			*animation = kModelAnimationSteeleWithGunShooting;
			Actor_Change_Animation_Mode(kActorSteele, kAnimationModeCombatIdle);
			_resumeIdleAfterFramesetCompletesFlag = false;
		} else {
			++_animationFrame;
			if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(*animation) - 1) {
				_animationFrame = 0;
			}
		}
		break;

	case 21:
		*animation = kModelAnimationSteeleWithGunAimingTalk;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(*animation) - 1) {
			_animationFrame = 0;
			_animationState = 20;
			*animation = kModelAnimationSteeleWithGunAimingTalk;
		}
		break;

	case 22:
		*animation = kModelAnimationSteeleWithGunAimingTalk;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(*animation) - 1) {
			_animationFrame = 0;
			_animationState = 20;
			*animation = kModelAnimationSteeleWithGunAimingTalk;
		}
		break;

	case 23:
		*animation = kModelAnimationSteeleWithGunIdle;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(*animation) - 1) {
			_animationFrame = 0;
		}
		break;

	case 24:
		*animation = kModelAnimationSteeleWithGunHolsterGun;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(*animation) - 1) {
			*animation = kModelAnimationSteeleIdle;
			_animationFrame = 0;
			_animationState = 0;
		}
		break;

	case 25:
		*animation = kModelAnimationSteeleWithGunUnholsterGun;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(*animation) - 1) {
			_animationFrame = 0;
			_animationState = 23;
			*animation = kModelAnimationSteeleWithGunIdle;
		}
		break;

	case 26:
		*animation = kModelAnimationSteeleWithGunShooting;
		++_animationFrame;
		if (_animationFrame == 3) {
			int snd;
			if (Random_Query(1, 2) == 1) {
				snd = 9010;
			} else {
				snd = 9015;
			}
			Sound_Play_Speech_Line(kActorSteele, snd, 75, 0, 99);
		}

		if (_animationFrame == 4) {
			Actor_Combat_AI_Hit_Attempt(kActorSteele);
		}

		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(*animation) - 1) {
			_animationFrame = 0;
			_animationState = 23;
			*animation = kModelAnimationSteeleWithGunIdle;
			Actor_Change_Animation_Mode(kActorSteele, kAnimationModeCombatIdle);
			if (Actor_Query_Goal_Number(kActorSteele) == kGoalSteeleNR11Shoot) {
				Actor_Change_Animation_Mode(kActorSteele, kAnimationModeCombatAttack);
				_animationState = 26;
				_animationFrame = 0;
				*animation = kModelAnimationSteeleWithGunShooting;
			}
		}
		break;

	case 27:
		*animation = kModelAnimationSteeleWithGunStrafeFast;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(*animation) - 1) {
			_animationFrame = 0;
			_animationState = 23;
			*animation = kModelAnimationSteeleWithGunIdle;
			Actor_Change_Animation_Mode(kActorSteele, kAnimationModeCombatIdle);
		}
		break;

	case 28:
		*animation = kModelAnimationSteeleWithGunStrafeSlow;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(*animation) - 1) {
			_animationFrame = 0;
			_animationState = 23;
			*animation = kModelAnimationSteeleWithGunIdle;
			Actor_Change_Animation_Mode(kActorSteele, kAnimationModeCombatIdle);
		}
		break;

	case 29:
		*animation = kModelAnimationSteeleWithGunGotHitRight;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(*animation) - 1) {
			_animationFrame = 0;
			_animationState = 23;
			*animation = kModelAnimationSteeleWithGunIdle;
			Actor_Change_Animation_Mode(kActorSteele, kAnimationModeCombatIdle);
		}
		break;

	case 30:
		*animation = kModelAnimationSteeleWithGunGotHitLeft;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(*animation) - 1) {
			_animationFrame = 0;
			_animationState = 23;
			*animation = kModelAnimationSteeleWithGunIdle;
			Actor_Change_Animation_Mode(kActorSteele, kAnimationModeCombatIdle);
		}
		break;

	case 31:
		*animation = kModelAnimationSteeleGotHitRight;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(*animation) - 1) {
			*animation = kModelAnimationSteeleIdle;
			_animationFrame = 0;
			_animationState = 0;
			Actor_Change_Animation_Mode(kActorSteele, kAnimationModeIdle);
		}
		break;

	case 32:
		*animation = kModelAnimationSteeleGotHitLeft;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(*animation) - 1) {
			*animation = kModelAnimationSteeleIdle;
			_animationFrame = 0;
			_animationState = 0;
			Actor_Change_Animation_Mode(kActorSteele, kAnimationModeIdle);
		}
		break;

	case 33:
		*animation = kModelAnimationSteeleWithGunShotDead;
		if (_animationFrame < Slice_Animation_Query_Number_Of_Frames(*animation) - 1)
			++_animationFrame;
		break;

	case 34:
		*animation = kModelAnimationSteeleShotDead;
		if (_animationFrame < Slice_Animation_Query_Number_Of_Frames(*animation) - 1)
			++_animationFrame;
		break;

	case 35:
		*animation = kModelAnimationSteeleWithGunShotDead;
		if (_animationFrame < Slice_Animation_Query_Number_Of_Frames(*animation) - 1)
			++_animationFrame;
		break;

	case 36:
		*animation = kModelAnimationSteeleWithGunAimingToRightIdle;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(*animation) - 1) {
			_animationFrame = 0;
		}
		break;

	case 37:
		if (_animationFrame == 0 && _resumeIdleAfterFramesetCompletesFlag
		) {
			_animationFrame = 0;
			_animationState = 0;
			_varChooseIdleAnimation = 3;
			_resumeIdleAfterFramesetCompletesFlag = false;
			*animation = kModelAnimationSteeleWithGunAimingToRightTalk;
		} else {
			*animation = kModelAnimationSteeleWithGunAimingToRightTalk;
			++_animationFrame;
			if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(*animation) - 1) {
				_animationFrame = 0;
			}
		}
		break;

	case 38:
		*animation = kModelAnimationSteeleWithGunAimingToRightHandHit;
		++_animationFrame;
		if (_animationFrame > 5) {
			Actor_Change_Animation_Mode(kActorSteele, kAnimationModeIdle);
			_animationState = 0;
			_animationFrame = 0;
			*animation = kModelAnimationSteeleIdle;
			Actor_Set_Goal_Number(kActorSteele, kGoalSteeleNR01PrepareTalkAboutShotGun);
		}
		break;

	case 39:
		*animation = kModelAnimationSteeleWithGunAimingToRightShoot;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(*animation) - 1) {
			_animationFrame = 0;
			_animationState = 36;
			*animation = kModelAnimationSteeleWithGunAimingToRightIdle;
		}
		break;

	case 40:
		*animation = kModelAnimationSteeleWithGunAimingToRightHolster;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(*animation) - 1) {
			*animation = kModelAnimationSteeleIdle;
			_animationFrame = 0;
			_animationState = 0;
			_varChooseIdleAnimation = 0;
		}
		break;

	case 41:
		switch (_varChooseIdleAnimation) {
		case 0:
			*animation = kModelAnimationSteeleIdle;
			++_animationFrame;
			if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationSteeleIdle)) {
				_animationFrame = 0;
				if (!Game_Flag_Query(kFlagSteeleSmoking)) {
					_varChooseIdleAnimation = 3;
				} else if (Random_Query(1, 3) == 1) {
					_varChooseIdleAnimation = 1;
				}
			}
			break;

		case 1:
			*animation = kModelAnimationSteeleTakeCigPuff;
			if (_varNumOfTimesToHoldCurrentFrame != 0) {
				--_varNumOfTimesToHoldCurrentFrame;
			} else {
				++_animationFrame;
				if (_animationFrame >= 6
				 && _animationFrame <= 9
				) {
					_varNumOfTimesToHoldCurrentFrame = Random_Query(1, 3);
					break;
				}

				if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(*animation)) {
					_animationFrame = 0;
					if (Game_Flag_Query(kFlagSteeleSmoking)) {
						_varChooseIdleAnimation = 0;
					} else {
						_varChooseIdleAnimation = 3;
					}
				}
			}
			break;

		case 3:
			*animation = kModelAnimationSteeleThrowCigAndStepOnIt;
			++_animationFrame;
			if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(*animation) - 1) {
				_animationState = 0;
				_animationFrame = 0;
				_varChooseIdleAnimation = 0;
				Game_Flag_Reset(kFlagSteeleSmoking);
			}
			break;
		}

		break;

	default:
		// Dummy placeholder, kModelAnimationZubenIdle (406) is a Zuben animation
		*animation = kModelAnimationZubenIdle;
		_animationFrame = 0;
		break;
	}
	*frame = _animationFrame;

	return true;
}

bool AIScriptSteele::ChangeAnimationMode(int mode) {
	switch (mode) {
	case kAnimationModeIdle:
		if (Game_Flag_Query(kFlagSteeleAimingAtGordo)) {
			_varChooseIdleAnimation = 3;
		} else {
			_varChooseIdleAnimation = 0;
		}

		switch (_animationState) {
		case 0:
			// fall through
		case 24:
			// fall through
		case 34:
			// fall through
		case 35:
			// fall through
		case 41:
			return true;

		case 4:
			_animationState = 23;
			_animationFrame = 0;
			break;

		case 14:
			// fall through
		case 15:
			// fall through
		case 16:
			// fall through
		case 17:
			// fall through
		case 18:
			// fall through
		case 19:
			_resumeIdleAfterFramesetCompletesFlag = true;
			break;

		case 20:
			// fall through
		case 21:
			// fall through
		case 22:
			// fall through
		case 37:
			_resumeIdleAfterFramesetCompletesFlag = true;
			_animationState = 23;
			_animationFrame = 0;
			break;

		case 23:
			// fall through
		case 26:
			_animationState = 24;
			_animationFrame = 0;
			break;

		default:
			_animationFrame = 0;
			if (Game_Flag_Query(kFlagSteeleSmoking)) {
				_animationState = 41;
				_varChooseIdleAnimation = 1;
			} else {
				_animationState = 0;
			}
			break;
		}
		break;

	case kAnimationModeWalk:
		if ((_animationState != 4
		  && _animationState != 23
		  && _animationState != 25
		  && _animationState != 26
		 )
		 || _animationState > 26
		) {
			if (Actor_Query_Goal_Number(kActorSteele) != kGoalSteeleApprehendIzo
			 && Actor_Query_Goal_Number(kActorSteele) != kGoalSteeleArrestIzo
			) {
				_animationState = 2;
				_animationFrame = 0;
			} else {
				_animationState = 4;
				_animationFrame = 0;
			}
		} else {
			_animationState = 4;
			_animationFrame = 0;
		}
		break;

	case kAnimationModeRun:
		if (Actor_Query_Goal_Number(kActorSteele) != kGoalSteeleApprehendIzo
		 && Actor_Query_Goal_Number(kActorSteele) != kGoalSteeleArrestIzo
		 && _animationState != 23
		) {
			_animationState = 3;
			_animationFrame = 0;
		} else {
			_animationState = 5;
			_animationFrame = 0;
		}
		break;

	case kAnimationModeTalk:
		if (_animationState != 35) {
			if (Game_Flag_Query(kFlagSteeleAimingAtGordo)) {
				_animationState = 37;
				_animationFrame = 0;
				_resumeIdleAfterFramesetCompletesFlag = false;
			} else {
				if (_animationState > 0) {
					_animationState = 14;
					_animationFrame = 0;
				} else {
					_animationState = 1;
					_animationFrame = 0;
					_animationStateNext = 14;
					_animationNext = kModelAnimationSteeleATalk;
				}
				_resumeIdleAfterFramesetCompletesFlag = false;
			}
		}
		break;

	case kAnimationModeCombatIdle:
		if (_animationState > 0) {
			if (_animationState > 25
			 || (_animationState != 23
			  && _animationState != 25)
			) {
				_animationState = 23;
				_animationFrame = 0;
			}
		} else {
			_animationState = 25;
			_animationFrame = 0;
		}
		break;

	case kAnimationModeCombatAttack:
		if (Game_Flag_Query(kFlagSteeleAimingAtGordo)) {
			_animationState = 39;
		} else {
			_animationState = 26;
		}
		_animationFrame = 0;
		break;

	case kAnimationModeCombatWalk:
		_animationState = 4;
		_animationFrame = 0;
		break;

	case kAnimationModeCombatRun:
		_animationState = 5;
		_animationFrame = 0;
		break;

	case 12:
		if (_animationState > 0) {
			_animationState = 15;
			_animationFrame = 0;
		} else {
			_animationState = 1;
			_animationFrame = 0;
			_animationStateNext = 15;
			_animationNext = kModelAnimationSteeleBTalk;
		}
		_resumeIdleAfterFramesetCompletesFlag = false;
		break;

	case 13:
		if (_animationState > 0) {
			_animationState = 16;
			_animationFrame = 0;
		} else {
			_animationState = 1;
			_animationFrame = 0;
			_animationStateNext = 16;
			_animationNext = kModelAnimationSteeleSmallLeftHandMoveTalk;
		}
		_resumeIdleAfterFramesetCompletesFlag = false;
		break;

	case 14:
		if (_animationState > 0) {
			_animationState = 17;
			_animationFrame = 0;
		} else {
			_animationState = 1;
			_animationFrame = 0;
			_animationStateNext = 17;
			_animationNext = kModelAnimationSteeleProtestTalk;
		}
		_resumeIdleAfterFramesetCompletesFlag = false;
		break;

	case 15:
		if (_animationState > 0) {
			_animationState = 18;
			_animationFrame = 0;
		} else {
			_animationState = 1;
			_animationFrame = 0;
			_animationStateNext = 18;
			_animationNext = kModelAnimationSteeleDismissTalk;
		}
		_resumeIdleAfterFramesetCompletesFlag = false;
		break;

	case 16:
		if (_animationState > 0) {
			_animationState = 19;
			_animationFrame = 0;
		} else {
			_animationState = 1;
			_animationFrame = 0;
			_animationStateNext = 19;
			_animationNext = kModelAnimationSteeleDismissTalk;
		}
		_resumeIdleAfterFramesetCompletesFlag = false;
		break;

	case kAnimationModeHit:
		if (_animationState > 28) {
			if (Random_Query(0, 1)) {
				_animationState = 31;
			} else {
				_animationState = 32;
			}
		} else if (Random_Query(0, 1)) {
			_animationState = 29;
		} else {
			_animationState = 30;
		}
		_animationFrame = 0;
		break;

	case kAnimationModeCombatHit:
		if (Random_Query(0, 1)) {
			_animationState = 29;
		} else {
			_animationState = 30;
		}
		_animationFrame = 0;
		break;

	case 43:
		Game_Flag_Set(kFlagSteeleSmoking);
		_animationState = 41;
		_animationFrame = 0;
		_varNumOfTimesToHoldCurrentFrame = 0;
		_varChooseIdleAnimation = 1;
		break;

	case kAnimationModeWalkUp:
		_animationState = 6;
		_animationFrame = 0;
		break;

	case kAnimationModeWalkDown:
		_animationState = 7;
		_animationFrame = 0;
		break;

	case kAnimationModeCombatWalkUp:
		_animationState = 8;
		_animationFrame = 0;
		break;

	case kAnimationModeCombatWalkDown:
		_animationState = 9;
		_animationFrame = 0;
		break;

	case kAnimationModeDie:
		if (_animationState != 33
		 && _animationState != 34
		) {
			if (_animationState > 26
			 || (_animationState != 23
			  && _animationState != 25
			  && _animationState != 26
			 )
			) {
				_animationState = 34;
				_animationFrame = 0;
			} else {
				_animationState = 33;
				_animationFrame = 0;
			}
		}
		break;

	case kAnimationModeCombatDie:
		if (_animationState != 33) {
			_animationState = 33;
			_animationFrame = 0;
		}
		break;

	case 51:
		_animationState = 35;
		_animationFrame = 0;
		break;

	case 58:
		_animationState = 20;
		_animationFrame = 0;
		_resumeIdleAfterFramesetCompletesFlag = false;
		break;

	case 59:
		_animationState = 21;
		_animationFrame = 0;
		_resumeIdleAfterFramesetCompletesFlag = false;
		break;

	case 60:
		_animationState = 22;
		_animationFrame = 0;
		_resumeIdleAfterFramesetCompletesFlag = false;
		break;

	case 86:
		_animationState = 10;
		_animationFrame = 0;
		break;
	}

	return true;
}

void AIScriptSteele::QueryAnimationState(int *animationState, int *animationFrame, int *animationStateNext, int *animationNext) {
	*animationState     = _animationState;
	*animationFrame     = _animationFrame;
	*animationStateNext = _animationStateNext;
	*animationNext      = _animationNext;
}

void AIScriptSteele::SetAnimationState(int animationState, int animationFrame, int animationStateNext, int animationNext) {
	_animationState     = animationState;
	_animationFrame     = animationFrame;
	_animationStateNext = animationStateNext;
	_animationNext      = animationNext;
}

bool AIScriptSteele::ReachedMovementTrackWaypoint(int waypointId) {
	if (waypointId == 174
	 && Actor_Query_Goal_Number(kActorSteele) == kGoalSteeleLeaveRC03
	) {
		Actor_Set_Goal_Number(kActorSteele, kGoalSteeleGoToPoliceStation);
	}
	return true;
}

void AIScriptSteele::FledCombat() {
	// return false;
}

} // End of namespace BladeRunner
