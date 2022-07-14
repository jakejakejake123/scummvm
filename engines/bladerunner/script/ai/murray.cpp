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

AIScriptMurray::AIScriptMurray(BladeRunnerEngine *vm) : AIScriptBase(vm) {
	_resumeIdleAfterFramesetCompletesFlag = false;
}

void AIScriptMurray::Initialize() {
	_animationFrame = 0;
	_animationState = 0;
	_animationStateNext = 0;
	_animationNext = 0;

	_resumeIdleAfterFramesetCompletesFlag = false;
	Actor_Put_In_Set(kActorMurray, kSetHF01);
	Actor_Set_At_XYZ(kActorMurray, 566.07f, -0.01f, -205.43f, 271);
	Actor_Set_Goal_Number(kActorMurray, 0);
}

bool AIScriptMurray::Update() {
	if (Global_Variable_Query(kVariableChapter) == 4
	 && Actor_Query_Goal_Number(kActorMurray) != 300
	) {
		Actor_Set_Goal_Number(kActorMurray, 300);
	}

	if (Player_Query_Current_Set() != kSetHF01) {
		return true;
	}

	if ( Actor_Query_In_Set(kActorMcCoy, kSetHF01)
	 &&  Actor_Query_In_Set(kActorMurray, kSetHF01)
	 &&  Actor_Query_Inch_Distance_From_Actor(kActorMcCoy, kActorMurray) < 48
	 && !Game_Flag_Query(kFlagHF01MurrayMiaIntro)
	) {
		Actor_Set_Goal_Number(kActorMurray, 1);
		return true;
	}

	return false;
}

void AIScriptMurray::TimerExpired(int timer) {
	//return false;
}

void AIScriptMurray::CompletedMovementTrack() {
	//return false;
}

void AIScriptMurray::ReceivedClue(int clueId, int fromActorId) {
	//return false;
}

void AIScriptMurray::ClickedByPlayer() {
	if (_vm->_cutContent) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -473.0f, 0.2f, -133.0f, 12, false, false, false)) {
			Actor_Face_Actor(kActorMcCoy, kActorMurray, true);
			Actor_Face_Actor(kActorMurray, kActorMcCoy, true);
			Actor_Says(kActorMcCoy, 3970, 14);
			Actor_Says(kActorMurray, 310, 13); //31-0310.AUD	McCoy, we've been friends for years. How dare you accuse us?
			Actor_Face_Actor(kActorMia, kActorMcCoy, true);
			Actor_Says(kActorMia, 230, 12); //22-0230.AUD	Hmph! No more free ‘dogs for you, young man.
			if (Player_Query_Agenda() == kPlayerAgendaSurly 
			|| Player_Query_Agenda() == kPlayerAgendaErratic) {
				if (!Actor_Clue_Query(kActorMcCoy, kClueSpecialIngredient)) {
					Actor_Says(kActorMcCoy, 8519, 14);//00-8519.AUD	What do you say we dish each other the straight goods.
					Delay(2000);
					Actor_Says(kActorMia, 180, 12); //22-0180.AUD	Well, we did hear something, Ray. I hope this won't get anybody into trouble.
					Actor_Says(kActorMcCoy, 1845, 19); //00-1845.AUD	I’ll have to think about it.
					Actor_Says(kActorMia, 250, 12); //22-0250.AUD	All right, then. Ray, here's the truth.
					Delay(1000);
					Actor_Says(kActorMurray, 210, 13);
					Actor_Says(kActorMurray, 220, 13);
					Actor_Says(kActorMia, 140, 12);
					Actor_Says(kActorMurray, 230, 13);
					Actor_Clue_Acquire(kActorMcCoy, kClueSpecialIngredient, false, kActorMurray);
				}
			}
		}
	}
}

void AIScriptMurray::EnteredSet(int setId) {
	// return false;
}

void AIScriptMurray::OtherAgentEnteredThisSet(int otherActorId) {
	// return false;
}

void AIScriptMurray::OtherAgentExitedThisSet(int otherActorId) {
	// return false;
}

void AIScriptMurray::OtherAgentEnteredCombatMode(int otherActorId, int combatMode) {
	// return false;
}

void AIScriptMurray::ShotAtAndMissed() {
	// return false;
}

bool AIScriptMurray::ShotAtAndHit() {
	return false;
}

void AIScriptMurray::Retired(int byActorId) {
	// return false;
}

int AIScriptMurray::GetFriendlinessModifierIfGetsClue(int otherActorId, int clueId) {
	return 0;
}

bool AIScriptMurray::GoalChanged(int currentGoalNumber, int newGoalNumber) {
	if (newGoalNumber == 300) {
		Actor_Put_In_Set(kActorMurray, kSetFreeSlotH);
		Actor_Set_At_Waypoint(kActorMurray, 40, 0);
	}

	return false;
}

bool AIScriptMurray::UpdateAnimation(int *animation, int *frame) {
	switch (_animationState) {
	case 0:
		*animation = kModelAnimationMurrayIdle;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationMurrayIdle))
			_animationFrame = 0;
		break;

	case 1:
		*animation = kModelAnimationMurrayCalmTalk;
		if (_animationFrame == 0 && _resumeIdleAfterFramesetCompletesFlag) {
			_animationState = 0;
		} else {
			++_animationFrame;
			if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationMurrayCalmTalk))
				_animationFrame = 0;
		}
		break;

	case 2:
		*animation = kModelAnimationMurrayMoreCalmTalk;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationMurrayMoreCalmTalk)) {
			_animationFrame = 0;
			_animationState = 1;
			*animation = kModelAnimationMurrayCalmTalk;
		}
		break;

	case 3:
		*animation = kModelAnimationMurrayExplainTalk;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationMurrayExplainTalk)) {
			_animationFrame = 0;
			_animationState = 1;
			*animation = kModelAnimationMurrayCalmTalk;
		}
		break;

	case 4:
		*animation = kModelAnimationMurrayMoreExplainTalk;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationMurrayMoreExplainTalk)) {
			_animationFrame = 0;
			_animationState = 1;
			*animation = kModelAnimationMurrayCalmTalk;
		}
		break;

	case 5:
		*animation = kModelAnimationMurrayCautionTalk;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationMurrayCautionTalk)) {
			_animationFrame = 0;
			_animationState = 1;
			*animation = kModelAnimationMurrayCalmTalk;
		}
		break;

	case 6:
		*animation = kModelAnimationMurrayGestureGive;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelAnimationMurrayGestureGive)) {
			*animation = kModelAnimationMurrayIdle;
			_animationFrame = 0;
			_animationState = 0;
		}
		break;

	default:
		break;
	}

	*frame = _animationFrame;

	return true;
}

bool AIScriptMurray::ChangeAnimationMode(int mode) {
	switch (mode) {
	case kAnimationModeIdle:
		if (_animationState > 0 && _animationState <= 5) {
			_resumeIdleAfterFramesetCompletesFlag = true;
		} else {
			_animationState = 0;
			_animationFrame = 0;
		}
		break;

	case kAnimationModeTalk:
		_animationState = 1;
		_animationFrame = 0;
		_resumeIdleAfterFramesetCompletesFlag = false;
		break;

	case 12:
		_animationState = 2;
		_animationFrame = 0;
		_resumeIdleAfterFramesetCompletesFlag = false;
		break;

	case 13:
		_animationState = 3;
		_animationFrame = 0;
		_resumeIdleAfterFramesetCompletesFlag = false;
		break;

	case 14:
		_animationState = 4;
		_animationFrame = 0;
		_resumeIdleAfterFramesetCompletesFlag = false;
		break;

	case 15:
		_animationState = 5;
		_animationFrame = 0;
		_resumeIdleAfterFramesetCompletesFlag = false;
		break;
	}

	return true;
}

void AIScriptMurray::QueryAnimationState(int *animationState, int *animationFrame, int *animationStateNext, int *animationNext) {
	*animationState     = _animationState;
	*animationFrame     = _animationFrame;
	*animationStateNext = _animationStateNext;
	*animationNext      = _animationNext;
}

void AIScriptMurray::SetAnimationState(int animationState, int animationFrame, int animationStateNext, int animationNext) {
	_animationState     = animationState;
	_animationFrame     = animationFrame;
	_animationStateNext = animationStateNext;
	_animationNext      = animationNext;
}

bool AIScriptMurray::ReachedMovementTrackWaypoint(int waypointId) {
	return true;
}

void AIScriptMurray::FledCombat() {
	// return false;
}

} // End of namespace BladeRunner
