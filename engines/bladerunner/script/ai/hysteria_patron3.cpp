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

AIScriptHysteriaPatron3::AIScriptHysteriaPatron3(BladeRunnerEngine *vm) : AIScriptBase(vm) {
}

void AIScriptHysteriaPatron3::Initialize() {
	_animationFrame = 0;
	_animationState = 0;
	_animationStateNext = 0;
	_animationNext = 0;
	if (_vm->_cutContent) {
		Actor_Put_In_Set(kActorHysteriaPatron3, kSetNR05_NR08);
		Actor_Set_At_XYZ(kActorHysteriaPatron3, -600.0f, 0.0f, -245.0f, 880);
	}
}

bool AIScriptHysteriaPatron3::Update() {
	return false;
}

void AIScriptHysteriaPatron3::TimerExpired(int timer) {
	//return false;
}

void AIScriptHysteriaPatron3::CompletedMovementTrack() {
	//return false;
}

void AIScriptHysteriaPatron3::ReceivedClue(int clueId, int fromActorId) {
	//return false;
}

void AIScriptHysteriaPatron3::ClickedByPlayer() {
	if (_vm->_cutContent) {
		Actor_Face_Actor(kActorMcCoy, kActorHysteriaPatron3, true);
		if (Player_Query_Agenda() == kPlayerAgendaSurly 
		|| Player_Query_Agenda() == kPlayerAgendaErratic) {
			if (Global_Variable_Query(kVariableChinyen) >= 5
			|| Query_Difficulty_Level() == kGameDifficultyEasy) {
				Actor_Says(kActorMcCoy, 3970, 13); //00-3970.AUD	Hey.
				Actor_Says(kActorMcCoy, 345, 16); //00-0345.AUD	Wanna make some money?
				Delay(1000);
				Actor_Change_Animation_Mode(kActorMcCoy, 23);
				Delay(2000);
				Actor_Says(kActorMcCoy, 8170, 13); //00-8170.AUD	There you go.
				if (Query_Difficulty_Level() != kGameDifficultyEasy) {
					Global_Variable_Decrement(kVariableChinyen, 5);
				}
			} else {
				Actor_Says(kActorMcCoy, 8518, kAnimationModeTalk); // Hey, can I lick...
				if (!Game_Flag_Query(kFlagHanoiDead)
				&& Game_Flag_Query(kFlagHanoiIsReplicant)) {
					Actor_Change_Animation_Mode(kActorMcCoy, 23);
					Game_Flag_Set(kFlagNR08TouchedDektora);
					Delay(1000);
					AI_Movement_Track_Flush(kActorHanoi);
					Actor_Force_Stop_Walking(kActorMcCoy);
					Actor_Set_Goal_Number(kActorHanoi, kGoalHanoiThrowOutMcCoy);
				}
			}
		} else {
			Actor_Says(kActorMcCoy, 8935, kAnimationModeTalk);
		}
	} else {
		Actor_Says(kActorMcCoy, 8935, kAnimationModeTalk);
	}
	//return false;
}

void AIScriptHysteriaPatron3::EnteredSet(int setId) {
	// return false;
}

void AIScriptHysteriaPatron3::OtherAgentEnteredThisSet(int otherActorId) {
	// return false;
}

void AIScriptHysteriaPatron3::OtherAgentExitedThisSet(int otherActorId) {
	// return false;
}

void AIScriptHysteriaPatron3::OtherAgentEnteredCombatMode(int otherActorId, int combatMode) {
	// return false;
}

void AIScriptHysteriaPatron3::ShotAtAndMissed() {
	// return false;
}

bool AIScriptHysteriaPatron3::ShotAtAndHit() {
	return false;
}

void AIScriptHysteriaPatron3::Retired(int byActorId) {
	// return false;
}

int AIScriptHysteriaPatron3::GetFriendlinessModifierIfGetsClue(int otherActorId, int clueId) {
	return 0;
}

bool AIScriptHysteriaPatron3::GoalChanged(int currentGoalNumber, int newGoalNumber) {
	return false;
}

const int kAnimationsCount = 3;
const int animationList[kAnimationsCount] = {
	kModelAnimationHysteriaPatron3DanceHandsDownLeanBackForth,
	kModelAnimationHysteriaPatron3DanceHandsDownToHandsUp,
	kModelAnimationHysteriaPatron3DanceHandsDownToHandsUp,
};

bool AIScriptHysteriaPatron3::UpdateAnimation(int *animation, int *frame) {
	if (_vm->_cutContent) {
		*animation = animationList[_animationState];

		if (_animationState == 2) {
			--_animationFrame;
			if (_animationFrame == 0) {
				_animationState = Random_Query(0, 1); // restart the cycle from 0 or 1 state
				_animationFrame = 0;
				*animation = animationList[_animationState];
			}
		} else {
			++_animationFrame;
			if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(*animation)) {
				_animationFrame = 0;

				if (_animationState == 0 && Random_Query(0, 2) == 0) {
					_animationState = 0; // restart same 0 state, with a small random chance
				} else {
					++_animationState;
					if (_animationState == 2) {
						_animationFrame = Slice_Animation_Query_Number_Of_Frames(animationList[_animationState]) - 1;
					} else if (_animationState >= kAnimationsCount) {
						_animationState = Random_Query(0, 1); // restart the cycle from 0 or 1 state
					}
				}
				*animation = animationList[_animationState];
			}
		}
		*frame = _animationFrame;
	}
	return true;
}

bool AIScriptHysteriaPatron3::ChangeAnimationMode(int mode) {
	return true;
}

void AIScriptHysteriaPatron3::QueryAnimationState(int *animationState, int *animationFrame, int *animationStateNext, int *animationNext) {
	*animationState     = _animationState;
	*animationFrame     = _animationFrame;
	*animationStateNext = _animationStateNext;
	*animationNext      = _animationNext;
}

void AIScriptHysteriaPatron3::SetAnimationState(int animationState, int animationFrame, int animationStateNext, int animationNext) {
	_animationState     = animationState;
	_animationFrame     = animationFrame;
	_animationStateNext = animationStateNext;
	_animationNext      = animationNext;
}

bool AIScriptHysteriaPatron3::ReachedMovementTrackWaypoint(int waypointId) {
	return true;
}

void AIScriptHysteriaPatron3::FledCombat() {
	// return false;
}

} // End of namespace BladeRunner
