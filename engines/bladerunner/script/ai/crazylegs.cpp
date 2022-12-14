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


enum kCrazylegsStates {
	kCrazylegsStateIdle       = 0,
	kCrazylegsStateHandsUp    = 1,
	kCrazylegsStateMobileCall = 2
	// TODO fill in the rest of the animationStates
};

AIScriptCrazylegs::AIScriptCrazylegs(BladeRunnerEngine *vm) : AIScriptBase(vm) {
	_resumeIdleAfterFramesetCompletesFlag = false;
}

void AIScriptCrazylegs::Initialize() {
	_animationFrame = 0;
	_animationState = kCrazylegsStateIdle;
	_animationStateNext = kCrazylegsStateIdle;
	_animationNext = 0;

	_resumeIdleAfterFramesetCompletesFlag = false;

	World_Waypoint_Set(360, kSetHF05, -103.0f, 40.63f, -53.0f);
	Actor_Put_In_Set(kActorCrazylegs, kSetHF05);
	Actor_Set_At_XYZ(kActorCrazylegs, -33.0f, 40.63f, 16.0f, 845);
}

bool AIScriptCrazylegs::Update() {
	if (Actor_Query_Goal_Number(kActorCrazylegs) == 10)
		Actor_Set_Goal_Number(kActorCrazylegs, 11);

	return false;
}

void AIScriptCrazylegs::TimerExpired(int timer) {
	//return false;
}

void AIScriptCrazylegs::CompletedMovementTrack() {
	//return false;
}

void AIScriptCrazylegs::ReceivedClue(int clueId, int fromActorId) {
	//return false;
}

void AIScriptCrazylegs::ClickedByPlayer() {
	if (_vm->_cutContent) {
		if (Actor_Query_In_Set(kActorCrazylegs, kSetKP07)) {
			Loop_Actor_Walk_To_Actor(kActorMcCoy, kActorCrazylegs, 24, false, false);
			Actor_Face_Actor(kActorMcCoy, kActorCrazylegs, true);
			Actor_Face_Actor(kActorCrazylegs, kActorMcCoy, true);
			Actor_Says(kActorMcCoy, 1730, kAnimationModeTalk); //00-1730.AUD	You’re a stand up guy, Crazy.
			Actor_Says(kActorCrazylegs, 80, 23); //09-0080.AUD	That I am.
		}
	}
}

void AIScriptCrazylegs::EnteredSet(int setId) {
	// return false;
}

void AIScriptCrazylegs::OtherAgentEnteredThisSet(int otherActorId) {
	// return false;
}

void AIScriptCrazylegs::OtherAgentExitedThisSet(int otherActorId) {
	// return false;
}

void AIScriptCrazylegs::OtherAgentEnteredCombatMode(int otherActorId, int combatMode) {
	if (Actor_Query_Goal_Number(kActorCrazylegs) != kGoalCrazyLegsLeavesShowroom && otherActorId == kActorMcCoy) {
		if (combatMode && Global_Variable_Query(kVariableChapter) < 5
		    && (!_vm->_cutContent || Actor_Query_In_Set(kActorCrazylegs, kSetHF05))) {
			Actor_Face_Actor(kActorCrazylegs, kActorMcCoy, true);
			Actor_Face_Actor(kActorMcCoy, kActorCrazylegs, true);
			// Since Crazylegs can now be a potential replicant in the cut content version his reaction to McCoy pulling out his gun will be a little different if Crazylegs is a replicant.
			// First off when McCoy pulls his gun out Crazylegs will be a little calmer about it. However if the player has enough clues that indicate Crazylegs guilt McCoy confronts Crazylegs
			// on this. This leads to Crazylegs trying to flee and the player will have a brief window of time to shoot Crazylegs before he gets away. 
			if (_vm->_cutContent) {
				if (!Game_Flag_Query(kFlagCrazylegsIsReplicant)) {
					Actor_Says(kActorCrazylegs, 430, 3);
					Actor_Says_With_Pause(kActorCrazylegs, 440, 0.0f, 3);
					if (Actor_Clue_Query(kActorMcCoy, kClueGrigoriansResources) 
	   				&& Actor_Clue_Query(kActorMcCoy, kClueGrigoriansNote)
					&& Global_Variable_Query(kVariableChapter) == 3) {
					    if (Actor_Clue_Query(kActorMcCoy, kClueCarRegistration1) 
	   					|| Actor_Clue_Query(kActorMcCoy, kClueCarRegistration3)) {
							Actor_Says(kActorMcCoy, 6865, -1); //00-6865.AUD	You're a Replicant. 
							Actor_Says(kActorCrazylegs, 540, 12); //09-0540.AUD	Huh, what--?
							Delay(500);
							Actor_Says(kActorCrazylegs, 550, 13); //09-0550.AUD	That’s impossible.
							Actor_Says(kActorMcCoy, 7835, -1); //00-7835.AUD	Is that so?
							Actor_Says(kActorCrazylegs, 790, 14); //09-0790.AUD	Gotta be a thousand dealers in the city and you’re picking on me.
							Actor_Set_Targetable(kActorCrazylegs, true);
							Actor_Set_Goal_Number(kActorCrazylegs, kGoalCrazyLegsMcCoyDrewHisGun);
							Player_Gains_Control();
						}
					} else if (Actor_Clue_Query(kActorMcCoy, kClueCrazysInvolvement)
					&& Global_Variable_Query(kVariableChapter) == 3) {
						Actor_Says(kActorMcCoy, 6865, -1); //00-6865.AUD	You're a Replicant. 
						Actor_Says(kActorCrazylegs, 540, 12); //09-0540.AUD	Huh, what--?
						Delay(500);
						Actor_Says(kActorCrazylegs, 550, 13); //09-0550.AUD	That’s impossible.
						Actor_Says(kActorMcCoy, 7835, -1); //00-7835.AUD	Is that so?
						Actor_Says(kActorCrazylegs, 790, 14); //09-0790.AUD	Gotta be a thousand dealers in the city and you’re picking on me.
						Actor_Set_Targetable(kActorCrazylegs, true);
						Actor_Set_Goal_Number(kActorCrazylegs, kGoalCrazyLegsMcCoyDrewHisGun);
						Player_Gains_Control();
					} else {
					 	if (Global_Variable_Query(kVariableChapter) == 3) {
							Actor_Says(kActorMcCoy, 1870, -1);
						}
						Actor_Says(kActorCrazylegs, 450, 3);
						Actor_Set_Goal_Number(kActorCrazylegs, kGoalCrazyLegsMcCoyDrewHisGun);
						Player_Gains_Control();
					}
				} else {
					Actor_Says(kActorCrazylegs, 480, 13); //09-0480.AUD	Hey, keep your paws off that, Ray!
					if (Actor_Clue_Query(kActorMcCoy, kClueCrazysInvolvement)	
					&& Global_Variable_Query(kVariableChapter) == 3) {
						Actor_Says(kActorMcCoy, 525, -1); //00-0525.AUD	I've seen you before...
						Actor_Says(kActorCrazylegs, 540, 12); //09-0540.AUD	Huh, what--?
						Actor_Says(kActorMcCoy, 7260, -1); //00-7260.AUD	Didn't I see an incept tape at the—
						Actor_Says(kActorCrazylegs, 1120, 14); //09-1120.AUD	I don’t know what you’re talking about.
						Delay (1000);
						Actor_Says(kActorMcCoy, 6865, -1); //00-6865.AUD	You're a Replicant.
						Actor_Says(kActorCrazylegs, 550, 13); //09-0550.AUD	That’s impossible.
						Delay (1000);
						Actor_Says(kActorMcCoy, 2755, -1); //00-2755.AUD	You all right? You look a little pale.
						Delay (2000);
						Actor_Says(kActorCrazylegs, 1000, 12); //09-1000.AUD	I got customers on the line, so I ain’t got time to chit chat.
						Actor_Set_Goal_Number(kActorCrazylegs, kGoalCrazyLegsLeavesShowroom);
						Actor_Says(kActorMcCoy, 8955, -1); //00-8955.AUD	Stop!
						Actor_Clue_Acquire(kActorMcCoy, kClueMcCoyPulledAGun, false, kActorCrazylegs);
						Actor_Set_Targetable(kActorCrazylegs, true);
						Player_Gains_Control();
					} else if (Actor_Clue_Query(kActorMcCoy, kClueGrigoriansResources) 
	   				&& Actor_Clue_Query(kActorMcCoy, kClueGrigoriansNote)
					&& Global_Variable_Query(kVariableChapter) == 3)  {
					    if (Actor_Clue_Query(kActorMcCoy, kClueCarRegistration1) 
	   					|| Actor_Clue_Query(kActorMcCoy, kClueCarRegistration3)) {
							Actor_Says(kActorMcCoy, 525, -1); //00-0525.AUD	I've seen you before...
							Actor_Says(kActorCrazylegs, 540, 12); //09-0540.AUD	Huh, what--?
							Actor_Says(kActorMcCoy, 7260, -1); //00-7260.AUD	Didn't I see an incept tape at the—
							Actor_Says(kActorCrazylegs, 1120, 14); //09-1120.AUD	I don’t know what you’re talking about.
							Delay (1000);
							Actor_Says(kActorMcCoy, 6865, -1); //00-6865.AUD	You're a Replicant.
							Actor_Says(kActorCrazylegs, 550, 13); //09-0550.AUD	That’s impossible.
							Delay (1000);
							Actor_Says(kActorMcCoy, 2755, -1); //00-2755.AUD	You all right? You look a little pale.
							Delay (2000);
							Actor_Says(kActorCrazylegs, 1000, 12); //09-1000.AUD	I got customers on the line, so I ain’t got time to chit chat.
							Actor_Set_Goal_Number(kActorCrazylegs, kGoalCrazyLegsLeavesShowroom);
							Actor_Says(kActorMcCoy, 8955, -1); //00-8955.AUD	Stop!
							Actor_Clue_Acquire(kActorMcCoy, kClueMcCoyPulledAGun, false, kActorCrazylegs);
							Actor_Set_Targetable(kActorCrazylegs, true);
							Player_Gains_Control();
						}
					} else {
						if (Global_Variable_Query(kVariableChapter) == 3) {
							Actor_Says(kActorMcCoy, 1870, -1);
						}
						Actor_Says(kActorCrazylegs, 450, 3);
						Actor_Set_Goal_Number(kActorCrazylegs, kGoalCrazyLegsMcCoyDrewHisGun);
						Player_Gains_Control();
					}
				}
			} else {
				Actor_Says(kActorCrazylegs, 430, 3);
				Actor_Says_With_Pause(kActorCrazylegs, 440, 0.0f, 3);
				Actor_Says(kActorMcCoy, 1870, -1);
				Actor_Says(kActorCrazylegs, 450, 3);
			}
			Actor_Set_Goal_Number(kActorCrazylegs, kGoalCrazyLegsMcCoyDrewHisGun);
		} else if (Actor_Query_Goal_Number(kActorCrazylegs) == kGoalCrazyLegsMcCoyDrewHisGun) {
			Actor_Face_Actor(kActorCrazylegs, kActorMcCoy, true);
			Actor_Says(kActorCrazylegs, 460, 3);
			Actor_Says(kActorCrazylegs, 470, 3);
			Actor_Set_Goal_Number(kActorCrazylegs, kGoalCrazyLegsLeavesShowroom);
		}
	}
}

void AIScriptCrazylegs::ShotAtAndMissed() {
	if (Actor_Query_Goal_Number(kActorCrazylegs) == kGoalCrazyLegsLeavesShowroom)
		return;

	Actor_Set_Goal_Number(kActorCrazylegs, kGoalCrazyLegsLeavesShowroom);
}

bool AIScriptCrazylegs::ShotAtAndHit() {
	if (Player_Query_Current_Scene() == kSceneHF05) {
		Actor_Set_Goal_Number(kActorCrazylegs, kGoalCrazyLegsShotAndHit);
		// Made it so when you shoot Crazylegs McCoy immediately appears outside the shop. This is because Crazylegs has no death animation.
		// McCoy will say a couple of things and the player will receive 200 chinyen, the code for this will be in the HF01.cpp sheet.
		Game_Flag_Set(kFlagCrazylegsDead);
		Game_Flag_Set(kFlagCrazylegsShot);
		Player_Set_Combat_Mode(false);
		Game_Flag_Set(kFlagHF05toHF01);
		Set_Enter(kSetHF01, kSceneHF01);
	}
	return false;
}

void AIScriptCrazylegs::Retired(int byActorId) {
	// return false;
}

int AIScriptCrazylegs::GetFriendlinessModifierIfGetsClue(int otherActorId, int clueId) {
	return 0;
}

bool AIScriptCrazylegs::GoalChanged(int currentGoalNumber, int newGoalNumber) {
	if (newGoalNumber == kGoalCrazyLegsDefault) {
		return true;
	}

	if (newGoalNumber == kGoalCrazyLegsShotAndHit) {
		AI_Movement_Track_Flush(kActorCrazylegs);
		Actor_Set_Targetable(kActorCrazylegs, false);
		return true;
	}

	if (newGoalNumber == kGoalCrazyLegsLeavesShowroom) {
		AI_Movement_Track_Flush(kActorCrazylegs);
		AI_Movement_Track_Append(kActorCrazylegs, 360, 0);
		AI_Movement_Track_Append(kActorCrazylegs, 40, 0);
		AI_Movement_Track_Repeat(kActorCrazylegs);
		return true;
	}

	return false;
}

bool AIScriptCrazylegs::UpdateAnimation(int *animation, int *frame) {
	switch (_animationState) {
	case kCrazylegsStateIdle:
		*animation = kModelAnimationCrazylegsIdle;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationCrazylegsIdle))
			_animationFrame = 0;
		break;

	case kCrazylegsStateHandsUp:
		*animation = kModelAnimationCrazylegsHandsUpIdle;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationCrazylegsHandsUpIdle))
			_animationFrame = 0;
		break;

	case kCrazylegsStateMobileCall:
		*animation = kModelAnimationCrazylegsMobileIdle;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationCrazylegsMobileIdle))
			_animationFrame = 0;
		break;

	case 3:
		*animation = kModelAnimationCrazylegsGestureGive;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationCrazylegsGestureGive)) {
			*animation = kModelAnimationCrazylegsIdle;
			_animationFrame = 0;
			_animationState = kCrazylegsStateIdle;
		}
		break;

	case 4:
		*animation = kModelAnimationCrazylegsRollSlow;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationCrazylegsRollSlow))
			_animationFrame = 0;
		break;

	case 5:
		*animation = kModelAnimationCrazylegsRollFast;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationCrazylegsRollFast))
			_animationFrame = 0;
		break;

	case 6:
		if (_animationFrame == 0 && _resumeIdleAfterFramesetCompletesFlag) {
			*animation = kModelAnimationCrazylegsIdle;
			_animationState = kCrazylegsStateIdle;
			_resumeIdleAfterFramesetCompletesFlag = false;
		} else {
			*animation = kModelAnimationCrazylegsCalmTalk;
			++_animationFrame;
			if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationCrazylegsCalmTalk))
				_animationFrame = 0;
		}
		break;

	case 7:
		*animation = kModelAnimationCrazylegsSmallHandMoveTalk;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationCrazylegsSmallHandMoveTalk)) {
			_animationFrame = 0;
			_animationState = 6;
			*animation = kModelAnimationCrazylegsCalmTalk;
		}
		break;

	case 8:
		*animation = kModelAnimationCrazylegsPointingAtSelfTalk;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationCrazylegsPointingAtSelfTalk)) {
			_animationFrame = 0;
			_animationState = 6;
			*animation = kModelAnimationCrazylegsCalmTalk;
		}
		break;

	case 9:
		*animation = kModelAnimationCrazylegsDisagreeTalk;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationCrazylegsDisagreeTalk)) {
			_animationFrame = 0;
			_animationState = 6;
			*animation = kModelAnimationCrazylegsCalmTalk;
		}
		break;

	case 10:
		*animation = kModelAnimationCrazylegsFastTalk;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationCrazylegsFastTalk)) {
			_animationFrame = 0;
			_animationState = 6;
			*animation = kModelAnimationCrazylegsCalmTalk;
		}
		break;

	case 11:
		*animation = kModelAnimationCrazylegsProtestTalk;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationCrazylegsProtestTalk)) {
			_animationFrame = 0;
			_animationState = 6;
			*animation = kModelAnimationCrazylegsCalmTalk;
		}
		break;

	case 12:
		*animation = kModelAnimationCrazylegsMobileCalmTalk;
		++_animationFrame;
		// This is probably an untriggered animation
		// TODO This animation has a faulty last frame which "breaks" its looping consistency
		// TODO It should not lead to kModelAnimationCrazylegsCalmTalk but to one of Crazylegs mobile animations
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationCrazylegsMobileCalmTalk)) {
			_animationFrame = 0;
			_animationState = 6;
			*animation = kModelAnimationCrazylegsCalmTalk;
		}
		break;

	case 13:
		*animation = kModelAnimationCrazylegsMobileIntenseTalk;
		++_animationFrame;
		// This is probably an untriggered animation
		// TODO It should not lead to kModelAnimationCrazylegsCalmTalk but to one of Crazylegs mobile animations
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationCrazylegsMobileIntenseTalk)) {
			_animationFrame = 0;
			_animationState = 6;
			*animation = kModelAnimationCrazylegsCalmTalk;
		}
		break;

	case 14:
		*animation = kModelAnimationCrazylegsHandsUpTalk;
		++_animationFrame;
		// This is probably an untriggered animation
		// TODO It should not lead to kModelAnimationCrazylegsCalmTalk but to one of Crazylegs hands-up animations
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationCrazylegsHandsUpTalk)) {
			_animationFrame = 0;
			_animationState = 6;
			*animation = kModelAnimationCrazylegsCalmTalk;
		}
		break;

	case 15:
		if (_animationFrame == 0 && _resumeIdleAfterFramesetCompletesFlag) {
			Actor_Change_Animation_Mode(kActorCrazylegs, 43);
			_animationState = kCrazylegsStateMobileCall;
			_resumeIdleAfterFramesetCompletesFlag = false;
			*animation = kModelAnimationCrazylegsMobileIdle;
		} else {
			*animation = kModelAnimationCrazylegsMobileIdle;
			++_animationFrame;
			if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationCrazylegsMobileIdle))
				_animationFrame = 0;
		}
		break;

	case 16:
		*animation = kModelAnimationCrazylegsHandsUpRaisesHands;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationCrazylegsHandsUpRaisesHands)) {
			_animationFrame = 0;
			_animationState = kCrazylegsStateHandsUp;
			*animation = kModelAnimationCrazylegsHandsUpIdle;
		}
		break;

	case 17:
		*animation = kModelAnimationCrazylegsHandsUpLowersHands;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationCrazylegsHandsUpLowersHands)) {
			*animation = kModelAnimationCrazylegsIdle;
			_animationFrame = 0;
			_animationState = kCrazylegsStateIdle;
		}
		break;

	case 18:
		// This animation plays in reverse
		// TODO Code seems wrong (especially the if clause condition).
		//      Probably left like this because the animation is untriggered
		*animation = kModelAnimationCrazylegsHangsUpMobile;
		--_animationFrame;
		if (_animationFrame <= Slice_Animation_Query_Number_Of_Frames(kModelAnimationCrazylegsHangsUpMobile)) { // matches original
			_animationFrame = 0;
			_animationState = kCrazylegsStateMobileCall;
			*animation = kModelAnimationCrazylegsIdle;
		}
		break;

	case 19:
		*animation = kModelAnimationCrazylegsHangsUpMobile;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationCrazylegsHangsUpMobile)) {
			*animation = kModelAnimationCrazylegsIdle;
			_animationFrame = 0;
			_animationState = kCrazylegsStateIdle;
			if (Actor_Query_Goal_Number(kActorCrazylegs) == 10) {
				Actor_Set_Goal_Number(kActorCrazylegs, 11);
			}
		}
		break;

	default:
		break;
	}
	*frame = _animationFrame;

	return true;
}

bool AIScriptCrazylegs::ChangeAnimationMode(int mode) {
	switch (mode) {
	case kAnimationModeIdle:
		switch (_animationState) {
		case kCrazylegsStateIdle:
			// fall through
		case 3:
			return true;

		case kCrazylegsStateHandsUp:
			_animationState = 17;
			_animationFrame = 0;
			break;

		case kCrazylegsStateMobileCall:
			_animationState = 19;
			_animationFrame = 0;
			break;

		case 4:
			// fall through
		case 5:
			_animationState = kCrazylegsStateIdle;
			_animationFrame = 0;
			break;

		case 6:
			// fall through
		case 7:
			// fall through
		case 8:
			// fall through
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
			_resumeIdleAfterFramesetCompletesFlag = true;
			break;

		default:
			break;
		}
		break;

	case kAnimationModeWalk:
		_animationState = 4;
		_animationFrame = 0;
		break;

	case kAnimationModeTalk:
		if (_animationState == kCrazylegsStateMobileCall) {
			_animationState = 15;
		} else {
			_animationState = 6;
		}
		_animationFrame = 0;
		_resumeIdleAfterFramesetCompletesFlag = false;
		break;

	case 12:
		_animationState = 7;
		_animationFrame = 0;
		_resumeIdleAfterFramesetCompletesFlag = false;
		break;

	case 13:
		_animationState = 8;
		_animationFrame = 0;
		_resumeIdleAfterFramesetCompletesFlag = false;
		break;

	case 14:
		_animationState = 9;
		_animationFrame = 0;
		_resumeIdleAfterFramesetCompletesFlag = false;
		break;

	case 15:
		_animationState = 10;
		_animationFrame = 0;
		_resumeIdleAfterFramesetCompletesFlag = false;
		break;

	case 16:
		_animationState = 11;
		_animationFrame = 0;
		_resumeIdleAfterFramesetCompletesFlag = false;
		break;

	case 17:
		_animationState = 12;
		_animationFrame = 0;
		_resumeIdleAfterFramesetCompletesFlag = false;
		break;

	case 18:
		_animationState = 13;
		_animationFrame = 0;
		_resumeIdleAfterFramesetCompletesFlag = false;
		break;

	case 19:
		_animationState = 14;
		_animationFrame = 0;
		_resumeIdleAfterFramesetCompletesFlag = false;
		break;

	case 23:
		_animationState = 3;
		_animationFrame = 0;
		break;

	case 43:
		// picks up mobile phone call
		if (_animationState != kCrazylegsStateMobileCall) {
			_animationState = 18;
			_animationFrame = Slice_Animation_Query_Number_Of_Frames(kModelAnimationCrazylegsHangsUpMobile) - 1;
		}
		break;

	default:
		break;
	}

	return true;
}

void AIScriptCrazylegs::QueryAnimationState(int *animationState, int *animationFrame, int *animationStateNext, int *animationNext) {
	*animationState     = _animationState;
	*animationFrame     = _animationFrame;
	*animationStateNext = _animationStateNext;
	*animationNext      = _animationNext;
}

void AIScriptCrazylegs::SetAnimationState(int animationState, int animationFrame, int animationStateNext, int animationNext) {
	_animationState     = animationState;
	_animationFrame     = animationFrame;
	_animationStateNext = animationStateNext;
	_animationNext      = animationNext;
}

bool AIScriptCrazylegs::ReachedMovementTrackWaypoint(int waypointId) {
	return true;
}

void AIScriptCrazylegs::FledCombat() {
	// return false;
}

} // End of namespace BladeRunner
