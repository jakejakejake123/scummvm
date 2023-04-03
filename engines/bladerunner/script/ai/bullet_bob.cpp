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

AIScriptBulletBob::AIScriptBulletBob(BladeRunnerEngine *vm) : AIScriptBase(vm) {
	// _varChooseIdleAnimation can have valid values: 0, 1
	_varChooseIdleAnimation = 0;
	_var2 = 6;
	_var3 = 1;
	_varNumOfTimesToHoldCurrentFrame = 0;
}

void AIScriptBulletBob::Initialize() {
	_animationFrame = 0;
	_animationState = 0;
	_animationStateNext = 0;
	_animationNext = 0;

	_varChooseIdleAnimation = 0;
	_var2 = 6;
	_var3 = 1;
	_varNumOfTimesToHoldCurrentFrame = 0;

	Actor_Set_Goal_Number(kActorBulletBob, kGoalBulletBobDefault);
	if (!_vm->_cutContent) {
		Actor_Set_Targetable(kActorBulletBob, true);
	}
}

bool AIScriptBulletBob::Update() {
	if (Game_Flag_Query(kFlagRC04McCoyShotBob)
	 && Actor_Query_Goal_Number(kActorBulletBob) != kGoalBulletBobDead
	) {
		Actor_Set_Goal_Number(kActorBulletBob, kGoalBulletBobDead);
	}

	if ( Player_Query_Combat_Mode()
	 &&  Player_Query_Current_Scene() == kSceneRC04
	 && !Game_Flag_Query(kFlagRC04McCoyCombatMode)
	 &&  Global_Variable_Query(kVariableChapter) < 4
	) {
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagBulletBobIsReplicant)) {
				AI_Countdown_Timer_Reset(kActorBulletBob, kActorTimerAIScriptCustomTask2);
				AI_Countdown_Timer_Start(kActorBulletBob, kActorTimerAIScriptCustomTask2, 10);
			}
		} else {
			AI_Countdown_Timer_Reset(kActorBulletBob, kActorTimerAIScriptCustomTask2);
			AI_Countdown_Timer_Start(kActorBulletBob, kActorTimerAIScriptCustomTask2, 10);
			Actor_Modify_Friendliness_To_Other(kActorBulletBob, kActorMcCoy, -15);
		}
		Actor_Set_Goal_Number(kActorBulletBob, kGoalBulletBobWarningMcCoy);
		Game_Flag_Set(kFlagRC04McCoyCombatMode);
	} else if ( Actor_Query_Goal_Number(kActorBulletBob) == kGoalBulletBobWarningMcCoy
	        && !Player_Query_Combat_Mode()
	) {
		AI_Countdown_Timer_Reset(kActorBulletBob, kActorTimerAIScriptCustomTask2);
		Game_Flag_Reset(kFlagRC04McCoyCombatMode);
		Game_Flag_Set(kFlagRC04McCoyWarned);
		Actor_Set_Goal_Number(kActorBulletBob, kGoalBulletBobDefault);
	}

	if ( Actor_Query_Goal_Number(kActorBulletBob) == kGoalBulletBobShootMcCoy
	 && !Game_Flag_Query(kFlagRC04BobShootMcCoy)
	 &&  _animationState == 0
	) {
		Actor_Face_Heading(kActorBulletBob, 208, false);
		_animationFrame = 0;
		_animationState = 2;
		Actor_Set_Goal_Number(kActorBulletBob, kGoalBulletBobWillShotMcCoy);
		Game_Flag_Set(kFlagRC04BobShootMcCoy);
		return true;
	}

	if (Game_Flag_Query(kFlagRC04McCoyWarned)
	 && Player_Query_Combat_Mode()
	 && Actor_Query_Goal_Number(kActorBulletBob) != kGoalBulletBobDead
	) {
		// Since Bob is going to be a potential replicant in the restored content cut I made it so if he is a human he never shoots McCoy even if he pulls his gun out.
		// This is done to further differentiate the difference between the characters when they are either a replicant or a human. If a character is human they will never try to
		// hurt McCoy no matter what and if they are replicant they will have no problem with killing McCoy. Human Bob will only shoot McCoy in act 4 when he believes McCoy is a rep.
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagBulletBobIsReplicant)) {
				Actor_Set_Goal_Number(kActorBulletBob, kGoalBulletBobShootMcCoy);
			} else {
				Actor_Says(kActorBulletBob, 120, 37); //14-0120.AUD	Hey, put that away!
				Actor_Modify_Friendliness_To_Other(kActorBulletBob, kActorMcCoy, -5);
			}
		} else {
			Actor_Set_Goal_Number(kActorBulletBob, kGoalBulletBobShootMcCoy);
		}
		return true;
	}

	return false;
}

void AIScriptBulletBob::TimerExpired(int timer) {
	if (timer == kActorTimerAIScriptCustomTask2
	 && Actor_Query_Goal_Number(kActorBulletBob) == kGoalBulletBobWarningMcCoy
	) {
		Actor_Set_Goal_Number(kActorBulletBob, kGoalBulletBobShootMcCoy);
		AI_Countdown_Timer_Reset(kActorBulletBob, kActorTimerAIScriptCustomTask2);
		return; //true;
	}
	return; //false;
}

void AIScriptBulletBob::CompletedMovementTrack() {
	//return false;
}

void AIScriptBulletBob::ReceivedClue(int clueId, int fromActorId) {
	//return false;
}

void AIScriptBulletBob::ClickedByPlayer() {
	// This is the dialogue between Bob and McCoy after McCoy arrests Bob and you click on him in one of the prison cells.
	if (_vm->_cutContent) {
		if (Actor_Query_In_Set(kActorBulletBob, kSetPS09)) {
			if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -473.0f, 0.2f, -133.0f, 12, false, false, false)) {
				Actor_Face_Actor(kActorMcCoy, kActorBulletBob, true);
				Actor_Says(kActorMcCoy, 8920, 16); //00-8920.AUD	I gotta ask you a question.
				Actor_Says(kActorBulletBob, 1820, 34); //14-1820.AUD	You want to make it as a Blade Runner, you ought to do your own investigations.
			}
			// This is the dialogue between Bob and McCoy if you click on him in the moonbus which is now posible since Bob can now be a potential replicant.
		} else if (Actor_Query_In_Set(kActorBulletBob, kSetKP07)) {
			if (Actor_Query_Goal_Number(kActorBulletBob) < kGoalBulletBobGone) {
				Loop_Actor_Walk_To_Actor(kActorMcCoy, kActorBulletBob, 24, false, false);
				Actor_Face_Actor(kActorMcCoy, kActorBulletBob, true);
				Actor_Says(kActorMcCoy, 3970, 13); //00-3970.AUD	Hey.
				Actor_Says(kActorBulletBob, 0, 31); //14-0000.AUD	That a .45 blaster under your coat or you're just happy to be here?
				if (Player_Query_Agenda() != kPlayerAgendaSurly 
				&& Player_Query_Agenda() != kPlayerAgendaErratic) {
					Actor_Says(kActorMcCoy, 2685, 13); //00-2685.AUD	Hmph. Very funny.
					if (Actor_Clue_Query(kActorMcCoy, kClueBobRobbed)) {
						if (Actor_Clue_Query(kActorMcCoy, kClueGoldfish) 
						||  Actor_Clue_Query(kActorMcCoy, kClueGarterSnake)
						||	Actor_Clue_Query(kActorMcCoy, kClueSlug)) {
							Actor_Says(kActorMcCoy, 5150, 18); //00-5150.AUD	One more thing.
							Actor_Change_Animation_Mode(kActorMcCoy, 23);
							Actor_Change_Animation_Mode(kActorBulletBob, 23);
							Delay(800);
							if (Actor_Clue_Query(kActorMcCoy, kClueGoldfish)) {
								Actor_Clue_Lose(kActorMcCoy, kClueGoldfish);
								Actor_Clue_Acquire(kActorBulletBob, kClueGoldfish, true, -1);
								Item_Pickup_Spin_Effect_From_Actor(kModelAnimationGoldfish, kActorBulletBob, 0, 0);
								Delay(1500);
							} 
							if (Actor_Clue_Query(kActorMcCoy, kClueGarterSnake)) {
								Actor_Clue_Lose(kActorMcCoy, kClueGarterSnake);
								Actor_Clue_Acquire(kActorBulletBob, kClueGarterSnake, true, -1);
								Item_Pickup_Spin_Effect_From_Actor(kModelAnimationGarterSnake, kActorBulletBob, 0, 0);
								Delay(1500);
							} 
							if (Actor_Clue_Query(kActorMcCoy, kClueSlug)) {
								Actor_Clue_Lose(kActorMcCoy, kClueSlug);
								Actor_Clue_Acquire(kActorBulletBob, kClueSlug, true, -1);
								Item_Pickup_Spin_Effect_From_Actor(kModelAnimationSlug, kActorBulletBob, 0, 0);
								Delay(1500);
							} 
							Actor_Says(kActorMcCoy, 8170, 13); //00-8170.AUD	There you go.
						}
					}
				} else {
					Actor_Says(kActorMcCoy, 665, 16); //00-0665.AUD	Real funny, pal.
				}
			}
		}
	}
	//return false;
}

void AIScriptBulletBob::EnteredSet(int setId) {
	// return false;
}

void AIScriptBulletBob::OtherAgentEnteredThisSet(int otherActorId) {
	// return false;
}

void AIScriptBulletBob::OtherAgentExitedThisSet(int otherActorId) {
	// return false;
}

void AIScriptBulletBob::OtherAgentEnteredCombatMode(int otherActorId, int combatMode) {
	// return false;
}

void AIScriptBulletBob::ShotAtAndMissed() {
	// return false;
}

bool AIScriptBulletBob::ShotAtAndHit() {
	Global_Variable_Increment(kVariableBobShot, 1);
	if (Global_Variable_Query(kVariableBobShot) > 0) {
		Actor_Set_Targetable(kActorBulletBob, false);
		Actor_Set_Goal_Number(kActorBulletBob, kGoalBulletBobGone);
		_animationFrame = 0;
 		_animationState = 3;
		Ambient_Sounds_Play_Speech_Sound(kActorGordo, 9000, 100, 0, 0, 0); // not a typo, it's really from Gordo
		Actor_Face_Heading(kActorBulletBob, 281, false);
		//Made it so the clickable 2D region for the bullet proof vest is removed after you shoot Bob.
		Scene_2D_Region_Remove(0);
	}
	//  Code for Bob being retired in the moonbus if he is a rep.
	if (_vm->_cutContent) {
		if (Actor_Query_In_Set(kActorBulletBob, kSetKP07)) {
			AI_Movement_Track_Flush(kActorBulletBob);
			Actor_Retired_Here(kActorBulletBob, 6, 6, true, kActorMcCoy);
			Actor_Set_Goal_Number(kActorBulletBob, kGoalBulletBobGone);
			return true;
		}
	}

	return false;
}

void AIScriptBulletBob::Retired(int byActorId) {
	Actor_Set_Goal_Number(kActorBulletBob, kGoalBulletBobGone);
	// Made it so the replicant survivors at moonbus variable goes up when Bob is at the moonbus and then goes down when he is retired..
	if (_vm->_cutContent) {
		if (Actor_Query_In_Set(kActorBulletBob, kSetKP07)) {
			Global_Variable_Decrement(kVariableReplicantsSurvivorsAtMoonbus, 1);
			Actor_Modify_Friendliness_To_Other(kActorSteele, kActorMcCoy, 2);
			Game_Flag_Reset(kFlagMcCoyIsHelpingReplicants);
			// Made it so the player receives 200 chinyen when retiring Bob or anyother replicant in the moonbus. 
			if (Query_Difficulty_Level() != kGameDifficultyEasy) {
				Global_Variable_Increment (kVariableChinyen, 200);
			}
			// Gaffs friendliness will go up whenever a replicant is killed. His friendliness will act as a replicant kill tally. This is because some dialogues will be different based on
			// how many replicants McCoy retires and this tally will be used determine how these dialogues play out..
			Actor_Modify_Friendliness_To_Other(kActorGaff, kActorMcCoy, 2);

			if (Global_Variable_Query(kVariableReplicantsSurvivorsAtMoonbus) == 0) {
				Player_Loses_Control();
				// Made it so if Crazylegs is in the moonbus, after all the reps are retired he flees and is shot offscreen by Crystal or Gaff.
				// This was done because he has no death animation so this seemed to be a reasonable solution.
				
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
				return; //true;
			}
		}
	}
	// return false;
}

int AIScriptBulletBob::GetFriendlinessModifierIfGetsClue(int otherActorId, int clueId) {
	return 0;
}

bool AIScriptBulletBob::GoalChanged(int currentGoalNumber, int newGoalNumber) {
	if (newGoalNumber == kGoalBulletBobDefault
	 && Game_Flag_Query(kFlagRC04McCoyWarned)
	 && Player_Query_Current_Scene() == kSceneRC04
	) {
		Actor_Says(kActorBulletBob, 140, 16); //14-0140.AUD	Little boys shouldn't play with guns.
		return true;
	}

	if ( newGoalNumber == kGoalBulletBobWarningMcCoy
	 && !Game_Flag_Query(kFlagRC04McCoyWarned)
	 &&  Player_Query_Current_Scene() == kSceneRC04
	) {
		if (_vm->_cutContent) {
			if (!Game_Flag_Query(kFlagBulletBobWarned)) {
				Actor_Face_Actor(kActorBulletBob, kActorMcCoy, true);
				Actor_Says(kActorBulletBob, 120, 37); //14-0120.AUD	Hey, put that away!
			}
		} else {
			Actor_Says(kActorBulletBob, 120, 37); //14-0120.AUD	Hey, put that away!
		}
		// Made it so McCoy can only shoot Bob and says he is going to put something away if he suspects Bob of being a replicant.
		// This will be if McCoy has the clues Hasan interview or VKBobGorskyReplicant. Also when Bob is a replicant a new cutscene will
		// play of McCoy pointing his gun at Bob and Bob trying to reason with McCoy. McCoy reveals that he knows that Bob is a replicant which
		// will lead to Bob trying to kill the player. When Bob says 'I guess I chose the right line of work' an extended action scene between Bob and Ray will
		// play where they get into a firefight with each other and Ray shooting and killing Bob.
		if (_vm->_cutContent) {
			if (!Game_Flag_Query(kFlagBulletBobWarned)
			&& !Game_Flag_Query(kFlagBulletBobReplicantTalk)) {
				if (Actor_Clue_Query(kActorMcCoy, kClueHasanInterview)) {
					Actor_Face_Actor(kActorMcCoy, kActorBulletBob, true);
					if (Player_Query_Agenda() == kPlayerAgendaSurly 
					|| (Player_Query_Agenda() == kPlayerAgendaErratic)) {
						Actor_Says(kActorMcCoy, 4915, -1); //00-4915.AUD	I'm gonna put something away, but it ain't gonna be my gun.
					} else {
						Actor_Says(kActorMcCoy, 7860, -1); //00-7860.AUD	Stay right where you are.
					}	
					// If Bullet Bob is a replicant and McCoy has discovered this when McCoy pulls his gun out this exchange will happen.
					if (Game_Flag_Query(kFlagBulletBobIsReplicant)) {
						Actor_Clue_Acquire(kActorMcCoy, kClueBobShotInSelfDefense, true, kActorBulletBob);
						Actor_Says(kActorBulletBob, 1610, 33); //14-1610.AUD	I've had enough McCoy.
						Actor_Face_Heading(kActorBulletBob, 240, true);
						Delay(500);
						Actor_Face_Actor(kActorBulletBob, kActorMcCoy, true);
						Actor_Change_Animation_Mode(kActorMcCoy, 5); // McCoy points his gun at Bob.
						if (Player_Query_Agenda() == kPlayerAgendaSurly 
						|| (Player_Query_Agenda() == kPlayerAgendaErratic)) {
							Actor_Says(kActorMcCoy, 8950, -1); //00-8950.AUD	Hold it right there!
						} else {
							Actor_Says(kActorMcCoy, 460, -1); //00-0460.AUD	Hold it right there!
						}
						Actor_Says(kActorBulletBob, 1780, 31); //14-1780.AUD	That's supposed to scare me?
						Actor_Says(kActorMcCoy, 2215, -1); //00-2215.AUD	That’s right.
						Delay (500);
						Actor_Says(kActorBulletBob, 1440, -1); //14-1440.AUD	Why?
						Delay (1000);
						Actor_Says(kActorMcCoy, 6865, -1); //00-6865.AUD	You're a Replicant.
						Delay (2000);
						Actor_Says(kActorMcCoy, 840, 13); //00-0840.AUD	Did you hear me?
						Loop_Actor_Walk_To_Waypoint(kActorMcCoy, 104, 0, false, false);
						Actor_Face_Actor(kActorBulletBob, kActorMcCoy, true);
						Actor_Face_Actor(kActorMcCoy, kActorBulletBob, true);
						Delay (2000);
						Actor_Says(kActorMcCoy, 180, -1); //00-0180.AUD	Bob?
						Actor_Says (kActorBulletBob, 1270, 37); //14-1270.AUD	(Laughing) I guess I picked the right line of work.
						Delay (200);
						Music_Play(kMusicMoraji, 71, 0, 0, -1, kMusicLoopPlayOnce, 2);
						Actor_Face_Actor(kActorBulletBob, kActorMcCoy, true);
						Actor_Change_Animation_Mode(kActorBulletBob, 4);
						Delay(1500);
						Sound_Play(kSfxSHOTCOK1, 75, 0, 0, 50);
						Loop_Actor_Walk_To_XYZ(kActorMcCoy, 78.14, 0.31, -21.27, 0, false, true, false);
						Actor_Face_Actor(kActorBulletBob, kActorMcCoy, true);
						Actor_Face_Actor(kActorMcCoy, kActorBulletBob, true);
						Sound_Play(kSfxGUNH1A, 100, 0, 0, 50);
						Actor_Change_Animation_Mode(kActorMcCoy, 6);
						Delay(1000);
						Loop_Actor_Walk_To_XYZ(kActorMcCoy, 67.26, 0.24, -111.65, 0, false, true, false);
						Actor_Face_Actor(kActorBulletBob, kActorMcCoy, true);
						Ambient_Sounds_Play_Sound(kSfxSHOTGUN1, 97, 0, 0, 20);
						Actor_Change_Animation_Mode(kActorBulletBob, 6);
						Actor_Change_Animation_Mode(kActorMcCoy, 21);
						Delay(1000);
						Actor_Face_Actor(kActorMcCoy, kActorBulletBob, true);
						Sound_Play(kSfxGUNH1A, 100, 0, 0, 50);
						Actor_Change_Animation_Mode(kActorMcCoy, 6);
						Delay(1500);
						Loop_Actor_Walk_To_XYZ(kActorMcCoy, -3.38, 0.27, -48.37, 0, false, true, false);
						Actor_Face_Actor(kActorBulletBob, kActorMcCoy, true);
						Sound_Play(kSfxGUNH1A, 100, 0, 0, 50);
						Actor_Change_Animation_Mode(kActorMcCoy, 6);
						Actor_Start_Speech_Sample(kActorMcCoy, 490); //00-0490.AUD	Suck on this, skin-job!
						_animationFrame = 0;
						_animationState = 3;
						Ambient_Sounds_Play_Speech_Sound(kActorGordo, 9000, 100, 0, 0, 0); // not a typo, it's really from Gordo
						Actor_Face_Heading(kActorBulletBob, 281, false);
						//Made it so the clickable 2D region for the bullet proof vest is removed after you shoot Bob.
						Actor_Set_Targetable(kActorBulletBob, false);
						Actor_Set_Goal_Number(kActorBulletBob, kGoalBulletBobGone);
						Player_Set_Combat_Mode (false);
						Delay (2000);
						if (Player_Query_Agenda() == kPlayerAgendaSurly 
						|| (Player_Query_Agenda() == kPlayerAgendaErratic)) {
							Loop_Actor_Walk_To_XYZ(kActorMcCoy, 28.04, 0.32, 7.86, 0, false, false, true);
							Actor_Face_Actor(kActorMcCoy, kActorBulletBob, true);
							Delay (1000);
							Actor_Says(kActorMcCoy, 8600, 18); //00-8600.AUD	You keeping busy, pal?
						}
						Scene_Exits_Enable();
						Game_Flag_Reset (kFlagMcCoyIsHelpingReplicants);
						Game_Flag_Set(kFlagBulletBobReplicantTalk);
						Game_Flag_Set(kFlagMcCoyRetiredReplicant);
						Actor_Modify_Friendliness_To_Other(kActorSteele, kActorMcCoy, 2);
						Actor_Modify_Friendliness_To_Other(kActorClovis, kActorMcCoy, -2);
						Actor_Modify_Friendliness_To_Other(kActorGuzza, kActorMcCoy, 2);
						Actor_Modify_Friendliness_To_Other(kActorGaff, kActorMcCoy, 2);
						Scene_2D_Region_Remove(0);
						if (Query_Difficulty_Level() != kGameDifficultyEasy) {
							Global_Variable_Increment (kVariableChinyen, 200);
						}
						// If Bob is not a replicant he doesn't attack McCoy and the player will have the option to shoot him.
					} else {
						Actor_Set_Targetable(kActorBulletBob, true);
						Actor_Says(kActorBulletBob, 1840, 34); //14-1840.AUD	Okay, okay, look.
						Actor_Says(kActorBulletBob, 1850, 35); //14-1850.AUD	I didn't want to get you riled up for no reason but here's the real skinny.
						Actor_Says(kActorMcCoy, 4320, -1); //00-4320.AUD	Save the pitch for someone who gives a shit.
						Actor_Says(kActorBulletBob, 1600, 33); //14-1600.AUD	Is that right?
						Actor_Says(kActorMcCoy, 2215, 13); //00-2215.AUD	That’s right.
						Delay (500);
						Actor_Says(kActorBulletBob, 1440, 36); //14-1440.AUD	Why?
						Delay (1000);
						Actor_Says(kActorMcCoy, 6865, -1); //00-6865.AUD	You're a Replicant.
						Delay (1000);
						Actor_Says(kActorBulletBob, 790, 36); //14-0790.AUD	It's funny. You thinking I'm a Rep.
						Game_Flag_Reset (kFlagMcCoyIsHelpingReplicants);
						Game_Flag_Set(kFlagBulletBobReplicantTalk);
					}
				}
			} else {
				Actor_Set_Targetable(kActorBulletBob, false);
			}
		} else {
			Actor_Says(kActorMcCoy, 4915, 13);
		}
		return true;
	}
	// Made it so McCoy will willingly turn himself in for shooting human Bob depening on hs agenda.
	if (_vm->_cutContent) {
		if ( newGoalNumber == kGoalBulletBobDead
		&& !Game_Flag_Query(kFlagBulletBobIsReplicant)
		&& Player_Query_Current_Scene() == kSceneRC04
		&& !Actor_Clue_Query(kActorMcCoy, kClueBobShotInColdBlood)) {
			Delay(2000);
			if (Player_Query_Agenda() == kPlayerAgendaSurly 
			&& Player_Query_Agenda() == kPlayerAgendaErratic) {
				Actor_Voice_Over(2110, kActorVoiceOver);
				Delay(1000);
				Actor_Voice_Over(2080, kActorVoiceOver); //99-2080.AUD	I’d done the city a favor.
				Game_Flag_Set(kFlagMcCoyRetiredHuman);
				Actor_Modify_Friendliness_To_Other(kActorClovis, kActorMcCoy, 2);
				Actor_Modify_Friendliness_To_Other(kActorSteele, kActorMcCoy, -2);
				Actor_Modify_Friendliness_To_Other(kActorGuzza, kActorMcCoy, -2);
			} else if (Player_Query_Agenda() == kPlayerAgendaPolite) {
				Actor_Voice_Over(2100, kActorVoiceOver);
				Actor_Voice_Over(2110, kActorVoiceOver); //99-2110.AUD	Bob was a psychopath but I was almost sure he wasn't a Replicant.
				Actor_Voice_Over(2420, kActorVoiceOver); //99-2420.AUD	I got the cold cut boys down here and they performed a bone-marrow on him.
				Delay(1000);
				Outtake_Play(kOuttakeAway1, true, -1);
				Actor_Set_Goal_Number(kActorMcCoy, kGoalMcCoyArrested);
			} else {
				Actor_Voice_Over(2100, kActorVoiceOver);
				Actor_Voice_Over(2110, kActorVoiceOver);
				Actor_Voice_Over(2120, kActorVoiceOver);
				Actor_Voice_Over(2130, kActorVoiceOver);
				Game_Flag_Set(kFlagMcCoyRetiredHuman);
				Actor_Modify_Friendliness_To_Other(kActorClovis, kActorMcCoy, 2);
				Actor_Modify_Friendliness_To_Other(kActorSteele, kActorMcCoy, -2);
				Actor_Modify_Friendliness_To_Other(kActorGuzza, kActorMcCoy, -2);
			}
		}
	} else if ( newGoalNumber == kGoalBulletBobDead
	 && !Actor_Clue_Query(kActorMcCoy, kClueVKBobGorskyReplicant)
	) {
		Delay(2000);
		Actor_Voice_Over(2100, kActorVoiceOver);
		Actor_Voice_Over(2110, kActorVoiceOver);
		Actor_Voice_Over(2120, kActorVoiceOver);
		Actor_Voice_Over(2130, kActorVoiceOver);
		return true;
	}

	if (newGoalNumber == kGoalBulletBobShotMcCoy) {
		Scene_Exits_Disable();
		Actor_Force_Stop_Walking(kActorMcCoy);
		Ambient_Sounds_Play_Speech_Sound(kActorMcCoy, 9900, 100, 0, 0, 0);
		Actor_Change_Animation_Mode(kActorMcCoy, kAnimationModeDie);
		Actor_Retired_Here(kActorMcCoy, 6, 6, 1, -1);
		Scene_Exits_Enable();
		return true;
	}

	return false;
}

bool AIScriptBulletBob::UpdateAnimation(int *animation, int *frame) {
	switch (_animationState) {
	case 0:
		if (_varChooseIdleAnimation == 1) {
#if BLADERUNNER_ORIGINAL_BUGS
			// TODO a bug? Why use kModelAnimationBulletBobSittingHeadMoveDownThink (516) here
			//             and leave kModelAnimationBulletBobSittingHeadMoveAround (515) unused?
			//             Also below kModelAnimationBulletBobSittingHeadMoveAround (515) is used
			//             in Slice_Animation_Query_Number_Of_Frames(),
			//             even though the count of frames is identical in both 515 and 516 framesets
			*animation = kModelAnimationBulletBobSittingHeadMoveDownThink;
#else
			*animation = kModelAnimationBulletBobSittingHeadMoveAround;
#endif
			if (_varNumOfTimesToHoldCurrentFrame > 0) {
				--_varNumOfTimesToHoldCurrentFrame;
			} else {
				if (++_animationFrame == 6) {
					_varNumOfTimesToHoldCurrentFrame = Random_Query(4, 8);
				}
				if (_animationFrame == 11) {
					_varNumOfTimesToHoldCurrentFrame = Random_Query(2, 6);
				}
				// frames in frameset kModelAnimationBulletBobSittingHeadMoveAround    (515): 16
				// frames in frameset kModelAnimationBulletBobSittingHeadMoveDownThink (kModelAnimationBulletBobSittingHeadMoveDownThink): 16
				if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationBulletBobSittingHeadMoveAround)) {
					_animationFrame = 0;
					_varChooseIdleAnimation = 0;
					_var3 = 2 * Random_Query(0, 1) - 1;
					_var2 = Random_Query(3, 7);
					_varNumOfTimesToHoldCurrentFrame = Random_Query(0, 4);
				}
			}
		} else if (_varChooseIdleAnimation == 0) {
			*animation = kModelAnimationBulletBobSittingIdle;
			if (_varNumOfTimesToHoldCurrentFrame > 0) {
				--_varNumOfTimesToHoldCurrentFrame;
			} else {
				_animationFrame += _var3;
				if (_animationFrame < 0) {
					_animationFrame = Slice_Animation_Query_Number_Of_Frames(kModelAnimationBulletBobSittingIdle) - 1;
				} else if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationBulletBobSittingIdle)) {
					_animationFrame = 0;
				}
				if (!--_var2) {
					_var3 = 2 * Random_Query(0, 1) - 1;
					_var2 = Random_Query(3, 7);
					_varNumOfTimesToHoldCurrentFrame = Random_Query(0, 4);
				}
				if (_animationFrame == 0) {
					_varChooseIdleAnimation = Random_Query(0, 1);
				}
			}
		}
		break;

	case 1:
		*animation = kModelAnimationBulletBobSittingCombatIdle;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationBulletBobSittingCombatIdle)) {
			_animationFrame = 0;
		}
		break;

	case 2:
		*animation = kModelAnimationBulletBobSittingCombatFiresGun;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationBulletBobSittingCombatFiresGun)) {
			_animationFrame = 0;
			_animationState = 1;
			*animation = kModelAnimationBulletBobSittingCombatIdle;
		}
		if (_animationFrame == 10) {
			Sound_Play(kSfxSHOTCOK1, 75, 0, 0, 50);
		}
		if (_animationFrame == 5) {
			Sound_Play(kSfxSHOTGUN1, 90, 0, 0, 50);
			if (_vm->_cutContent) {
				if (!Actor_Clue_Query(kActorMcCoy, kClueBobShotInSelfDefense)) {
					Actor_Set_Goal_Number(kActorBulletBob, kGoalBulletBobShotMcCoy);
				}
			} else {
				Actor_Set_Goal_Number(kActorBulletBob, kGoalBulletBobShotMcCoy);
			}
		}
		break;

	case 3:
		*animation = kModelAnimationBulletBobSittingCombatShotDead;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationBulletBobSittingCombatShotDead) - 1) {
			_animationFrame = Slice_Animation_Query_Number_Of_Frames(kModelAnimationBulletBobSittingCombatShotDead) - 1;
			_animationState = 16;
			Game_Flag_Set(kFlagRC04McCoyShotBob);
		}
		break;

	case 4:
		break;

	case 5:
		*animation = kModelAnimationBulletBobSittingThumbsUp;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationBulletBobSittingThumbsUp)) {
			*animation = kModelAnimationBulletBobSittingIdle;
			_animationFrame = 0;
			_animationState = 0;
		}
		break;

	case 6:
		*animation = kModelAnimationBulletBobSittingCalmTalk;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationBulletBobSittingCalmTalk)) {
			_animationFrame = 0;
		}
		break;

	case 7:
		*animation = kModelAnimationBulletBobSittingDismissiveTalk;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationBulletBobSittingDismissiveTalk)) {
			_animationFrame = 0;
			_animationState = 6;
			*animation = kModelAnimationBulletBobSittingCalmTalk;
		}
		break;

	case 8:
		*animation = kModelAnimationBulletBobSittingSuggestTalk;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationBulletBobSittingSuggestTalk)) {
			_animationFrame = 0;
			_animationState = 6;
			*animation = kModelAnimationBulletBobSittingCalmTalk;
		}
		break;

	case 9:
		*animation = kModelAnimationBulletBobSittingQuickSuggestTalk;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationBulletBobSittingQuickSuggestTalk)) {
			_animationFrame = 0;
			_animationState = 6;
			*animation = kModelAnimationBulletBobSittingCalmTalk;
		}
		break;

	case 10:
		*animation = kModelAnimationBulletBobSittingExplainTalk;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationBulletBobSittingExplainTalk)) {
			_animationFrame = 0;
			_animationState = 6;
			*animation = kModelAnimationBulletBobSittingCalmTalk;
		}
		break;

	case 11:
		*animation = kModelAnimationBulletBobSittingGossipTalk;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationBulletBobSittingGossipTalk)) {
			_animationFrame = 0;
			_animationState = 6;
			*animation = kModelAnimationBulletBobSittingCalmTalk;
		}
		break;

	case 12:
		*animation = kModelAnimationBulletBobSittingHeadNodLeftTalk;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationBulletBobSittingHeadNodLeftTalk)) {
			_animationFrame = 0;
			_animationState = 6;
			*animation = kModelAnimationBulletBobSittingCalmTalk;
		}
		break;

	case 13:
		*animation = kModelAnimationBulletBobSittingPersistentTalk;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationBulletBobSittingPersistentTalk)) {
			_animationFrame = 0;
			_animationState = 6;
			*animation = kModelAnimationBulletBobSittingCalmTalk;
		}
		break;

	case 14:
		*animation = kModelAnimationBulletBobSittingCombatRetrievesGun;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationBulletBobSittingCombatRetrievesGun)) {
			_animationFrame = 0;
			_animationState = 1;
			*animation = kModelAnimationBulletBobSittingCombatIdle;
		}
		break;

	case 15:
		if (_varChooseIdleAnimation == 1) {
			*animation = kModelAnimationBulletBobSittingHeadMoveDownThink;
			if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationBulletBobSittingHeadMoveDownThink)) {
				_animationFrame += 2;
				if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationBulletBobSittingHeadMoveDownThink)) {
					_animationFrame = 0;
					*animation = _animationNext;
					_animationState = _animationStateNext;
				}
			} else {
				_animationFrame -= 2;
				if (_animationFrame <= 0) {
					_animationFrame = 0;
					*animation = _animationNext;
					_animationState = _animationStateNext;
				}
			}
		} else if (_varChooseIdleAnimation == 0) {
			*animation = kModelAnimationBulletBobSittingIdle;
			if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationBulletBobSittingIdle)) {
				_animationFrame += 2;
				if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationBulletBobSittingIdle)) {
					_animationFrame = 0;
					*animation = _animationNext;
					_animationState = _animationStateNext;
				}
			} else {
				_animationFrame -= 2;
				if (_animationFrame <= 0) {
					_animationFrame = 0;
					*animation = _animationNext;
					_animationState = _animationStateNext;
				}
			}
		}
		break;

	case 16:
		*animation = kModelAnimationBulletBobSittingCombatShotDead;
		_animationFrame = Slice_Animation_Query_Number_Of_Frames(kModelAnimationBulletBobSittingCombatShotDead) - 1;
		break;

	default:
		break;
	}
	*frame = _animationFrame;

	return true;
}

bool AIScriptBulletBob::ChangeAnimationMode(int mode) {
	switch (mode) {
	case kAnimationModeIdle:
		if (_animationState > 4 || _animationState) {
			// TODO "|| _animationState" part of the clause does not make sense (makes the first part redundant). A bug?
			_animationState = 0;
			_animationFrame = 0;
		}
		break;

	case kAnimationModeTalk:
		// fall through
	case 9:
		// fall through
	case 30:
		if (_animationState < 6 || _animationState > 13) {
			_animationState = 15;
			_animationStateNext = 6;
			_animationNext = kModelAnimationBulletBobSittingCalmTalk;
		}
		break;

	case kAnimationModeCombatIdle:
		if (_animationState <= 4 && _animationState == 0) {
			_animationState = 14;
			_animationFrame = 0;
		}
		break;

	case kAnimationModeCombatAttack:
		_animationState = 2;
		_animationFrame = 0;
		break;

	case 10:
		// fall through
	case 31:
		if (_animationState < 6 || _animationState > 13) {
			_animationState = 15;
			_animationStateNext = 7;
			_animationNext = kModelAnimationBulletBobSittingDismissiveTalk;
		}
		break;

	case 11:
		// fall through
	case 33:
		if (_animationState < 6 || _animationState > 13) {
			_animationState = 15;
			_animationStateNext = 9;
			_animationNext = kModelAnimationBulletBobSittingQuickSuggestTalk;
		}
		break;

	case kAnimationModeHit:
		// fall through
	case kAnimationModeCombatHit:
		_animationState = 3;
		_animationFrame = 0;
		break;

	case 23:
		_animationState = 5;
		_animationFrame = 0;
		break;

	case 32:
		if (_animationState < 6 || _animationState > 13) {
			_animationState = 15;
			_animationStateNext = 8;
			_animationNext = kModelAnimationBulletBobSittingSuggestTalk;
		}
		break;

	case 34:
		if (_animationState < 6 || _animationState > 13) {
			_animationState = 15;
			_animationStateNext = 10;
			_animationNext = kModelAnimationBulletBobSittingExplainTalk;
		}
		break;

	case 35:
		if (_animationState < 6 || _animationState > 13) {
			_animationState = 15;
			_animationStateNext = 11;
			_animationNext = kModelAnimationBulletBobSittingGossipTalk;
		}
		break;

	case 36:
		if (_animationState < 6 || _animationState > 13) {
			_animationState = 15;
			_animationStateNext = 12;
			_animationNext = kModelAnimationBulletBobSittingHeadNodLeftTalk;
		}
		break;

	case 37:
		if (_animationState < 6 || _animationState > 13) {
			_animationState = 15;
			_animationStateNext = 13;
			_animationNext = kModelAnimationBulletBobSittingPersistentTalk;
		}
		break;

	case kAnimationModeDie:
		_animationState = 4;
		_animationFrame = 0;
		break;

	case 88:
		_animationState = 16;
		_animationFrame = Slice_Animation_Query_Number_Of_Frames(kModelAnimationBulletBobSittingCombatShotDead) - 1;
		break;

	default:
		_animationState = 0;
		_animationFrame = 0;
		break;
	}
	return true;
}

void AIScriptBulletBob::QueryAnimationState(int *animationState, int *animationFrame, int *animationStateNext, int *animationNext) {
	*animationState     = _animationState;
	*animationFrame     = _animationFrame;
	*animationStateNext = _animationStateNext;
	*animationNext      = _animationNext;
}

void AIScriptBulletBob::SetAnimationState(int animationState, int animationFrame, int animationStateNext, int animationNext) {
	_animationState     = animationState;
	_animationFrame     = animationFrame;
	_animationStateNext = animationStateNext;
	_animationNext      = animationNext;
}

bool AIScriptBulletBob::ReachedMovementTrackWaypoint(int waypointId) {
	return true;
}

void AIScriptBulletBob::FledCombat() {
	// return false;
}

} // End of namespace BladeRunner
