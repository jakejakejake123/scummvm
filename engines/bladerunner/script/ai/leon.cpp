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

AIScriptLeon::AIScriptLeon(BladeRunnerEngine *vm) : AIScriptBase(vm) {
	_mcCoyPositionX = 0.0f;
	_mcCoyPositionY = 0.0f;
	_mcCoyPositionZ = 0.0f;
	_resumeIdleAfterFramesetCompletesFlag = false;
}

void AIScriptLeon::Initialize() {
	_mcCoyPositionX = 0.0f;
	_mcCoyPositionY = 0.0f;
	_mcCoyPositionZ = 0.0f;
	_resumeIdleAfterFramesetCompletesFlag = false;
	_animationStateNext = 0;
	_animationNext = 0;
	_animationFrame = 0;
	_animationState = 0;
}

bool AIScriptLeon::Update() {
	int goalNumber = Actor_Query_Goal_Number(kActorLeon);

	if (goalNumber == kGoalLeonPrepareTalkToMcCoy) {
		Actor_Set_Goal_Number(kActorLeon, kGoalLeonTalkToMcCoy);
		return true;
	}

	if (goalNumber == kGoalLeonApproachMcCoy) {
		if (Player_Query_Combat_Mode()) {
			Actor_Set_Goal_Number(kActorLeon, kGoalLeonLeave);
			return true;
		}

		if ( Actor_Query_Inch_Distance_From_Actor(kActorLeon, kActorMcCoy) <= 36
		 && !Player_Query_Combat_Mode()
		) {
			Actor_Set_Goal_Number(kActorLeon, kGoalLeonPunchMcCoy);
			return true;
		}

		if (distanceTo(kActorLeon, _mcCoyPositionX, _mcCoyPositionY, _mcCoyPositionZ) > 12.0f) {
			Actor_Query_XYZ(kActorMcCoy, &_mcCoyPositionX, &_mcCoyPositionY, &_mcCoyPositionZ);
			Async_Actor_Walk_To_XYZ(kActorLeon, _mcCoyPositionX, _mcCoyPositionY, _mcCoyPositionZ, 24, false);
		}
		return true;
	}
	return false;
}

void AIScriptLeon::TimerExpired(int timer) {
	if (timer == kActorTimerAIScriptCustomTask0
	 && Actor_Query_Goal_Number(kActorLeon) == kGoalLeonLeave
	) {
		AI_Countdown_Timer_Reset(kActorLeon, kActorTimerAIScriptCustomTask0);
		Actor_Set_Goal_Number(kActorLeon, kGoalLeonGone);
	}
}

void AIScriptLeon::CompletedMovementTrack() {
	if (Actor_Query_Goal_Number(kActorLeon) == kGoalLeonLeave) {
		AI_Countdown_Timer_Reset(kActorLeon, kActorTimerAIScriptCustomTask0);
		AI_Countdown_Timer_Start(kActorLeon, kActorTimerAIScriptCustomTask0, 8);
		//return true;
	}
	//return false;
}

void AIScriptLeon::ReceivedClue(int clueId, int fromActorId) {}

void AIScriptLeon::ClickedByPlayer() {
	if (Actor_Query_Goal_Number(kActorLeon) == kGoalLeonHoldingDeskClerk) {
		Game_Flag_Set(kFlagCT09LeonInterrupted);
		Player_Loses_Control();
		Actor_Face_Actor(kActorMcCoy, kActorLeon, true);
		ADQ_Flush();
		Actor_Says(kActorMcCoy, 495, kAnimationModeTalk);
		Actor_Set_Goal_Number(kActorLeon, kGoalLeonReleaseDeskClerk);
		//return true;
	}
	//return false;
}

void AIScriptLeon::EnteredSet(int setId) {}

void AIScriptLeon::OtherAgentEnteredThisSet(int otherActorId) {
	if (otherActorId == kActorMcCoy
	 && Actor_Query_Goal_Number(kActorLeon) == kGoalLeonLeave
	) {
		AI_Countdown_Timer_Reset(kActorLeon, kActorTimerAIScriptCustomTask0);
		AI_Movement_Track_Flush(kActorLeon);
		AI_Movement_Track_Append(kActorLeon, 353, 0);
		AI_Movement_Track_Repeat(kActorLeon);
		//return true;
	}
	///return false;
}

void AIScriptLeon::OtherAgentExitedThisSet(int otherActorId) {
	if (otherActorId == kActorMcCoy
	 && Actor_Query_Which_Set_In(kActorLeon) != kSetCT11
	) {
		AI_Movement_Track_Flush(kActorLeon);
		ADQ_Flush();
		Actor_Set_Goal_Number(kActorLeon, kGoalLeonGone);
		Actor_Set_Goal_Number(kActorDeskClerk, kGoalDeskClerkKnockedOut);
		//return true;
	}
	///return false;
}

void AIScriptLeon::OtherAgentEnteredCombatMode(int otherActorId, int combatMode) {
	if (otherActorId == kActorMcCoy
	 && combatMode == 1
	 && Actor_Query_Goal_Number(kActorLeon) == kGoalLeonHoldingDeskClerk
	) {
		Game_Flag_Set(kFlagCT09LeonInterrupted);
		Player_Loses_Control();
		Actor_Face_Actor(kActorMcCoy, kActorLeon, true);
		Actor_Says(kActorMcCoy, 500, kAnimationModeCombatAim);
		Actor_Set_Goal_Number(kActorLeon, kGoalLeonReleaseDeskClerk);
		//return true;
	}
	//return false;
}

void AIScriptLeon::ShotAtAndMissed() {}

bool AIScriptLeon::ShotAtAndHit() {
	if (Actor_Query_Goal_Number(kActorLeon) != kGoalLeonLeave) {
		Actor_Set_Goal_Number(kActorLeon, kGoalLeonLeave);
	}
	return false;
}

void AIScriptLeon::Retired(int byActorId) {}

int AIScriptLeon::GetFriendlinessModifierIfGetsClue(int otherActorId, int clueId) {
	return 0;
}

bool AIScriptLeon::GoalChanged(int currentGoalNumber, int newGoalNumber) {
	switch (newGoalNumber) {
	case kGoalLeonDefault:
		Actor_Put_In_Set(kActorLeon, kSetFreeSlotA);
		Actor_Change_Animation_Mode(kActorLeon, kAnimationModeIdle);
		return true;

	case kGoalLeonHoldingDeskClerk:
		Actor_Change_Animation_Mode(kActorDeskClerk, 72);
		Actor_Change_Animation_Mode(kActorLeon, 72);
		Actor_Put_In_Set(kActorLeon, kSetCT09);
		Actor_Set_At_XYZ(kActorLeon, 264.0f, 348.52f, 827.0f, 0);
		Actor_Face_Actor(kActorDeskClerk, kActorLeon, true);
		ADQ_Add(kActorLeon, 0, 16);
		ADQ_Add(kActorDeskClerk, 0, 58);
		ADQ_Add(kActorLeon, 10, 15);
		ADQ_Add(kActorDeskClerk, 10, 58);
		ADQ_Add(kActorLeon, 20, 16);
		return true;

	case kGoalLeonReleaseDeskClerk:
		Actor_Change_Animation_Mode(kActorLeon, 26);
		Actor_Change_Animation_Mode(kActorDeskClerk, 26);
		return true;

	case kGoalLeonTalkToMcCoy:
		Actor_Face_Actor(kActorLeon, kActorMcCoy, true);
		Player_Set_Combat_Mode(false);
		Actor_Says(kActorLeon, 30, 12);
		Actor_Face_Actor(kActorMcCoy, kActorLeon, true);
		if (Player_Query_Combat_Mode()) {
			Player_Set_Combat_Mode(false);
		}
		Actor_Says(kActorMcCoy, 505, 23);
		Actor_Says(kActorLeon, 60, 13);
		Player_Gains_Control();
		Loop_Actor_Walk_To_XYZ(kActorLeon, 233.0f, 349.0f, 849.0f, 0, false, false, false);
		Actor_Face_Actor(kActorLeon, kActorMcCoy, true);
		Actor_Face_Actor(kActorMcCoy, kActorLeon, true);
		Actor_Says(kActorMcCoy, 515, 18);
		Actor_Says_With_Pause(kActorLeon, 70, 0.3f, 12);
		Actor_Says(kActorMcCoy, 520, 15);
		Actor_Says(kActorLeon, 80, 12);
		Loop_Actor_Walk_To_XYZ(kActorLeon, 198.0f, 349.0f, 865.0f, 0, false, false, false);
		Actor_Face_Actor(kActorLeon, kActorMcCoy, true);
		Actor_Face_Actor(kActorMcCoy, kActorLeon, true);
		if (Actor_Clue_Query(kActorMcCoy, kClueWantedPoster)) { // there is no way how to obtain this poster
			Actor_Says_With_Pause(kActorMcCoy, 525, 0.2f, 14);
			Actor_Says(kActorLeon, 90, 13);
			Actor_Says(kActorMcCoy, 530, 16);
			Actor_Set_Goal_Number(kActorLeon, kGoalLeonApproachMcCoy);
		} else {
			// Made it McCoys conversation with Leon will be different based upon whether or not McCoy helped the desk clerk.
			// If McCoy helped the clerk he will be concerned about him and if he didn't he couldn't care less.
			Actor_Says_With_Pause(kActorMcCoy, 535, 0.8f, 17); //00-0535.AUD	What about him?
			Actor_Says(kActorLeon, 100, 13); //62-0100.AUD	Nothing, I just thought you were gonna arrest me. That's all.
			if (_vm->_cutContent) {
				if (!Game_Flag_Query(kFlagCT09LeonInterrupted)) {
					Actor_Says_With_Pause(kActorMcCoy, 540, 0.0f, 19); //00-0540.AUD	I don't care about your little run-in with the manager, okay? I'm looking for a couple of Replicants.
					Actor_Says(kActorLeon, 110, kAnimationModeTalk); //62-0110.AUD	Can't help you there, friend.
				}
			} else {
				Actor_Says_With_Pause(kActorMcCoy, 540, 0.0f, 19); //00-0540.AUD	I don't care about your little run-in with the manager, okay? I'm looking for a couple of Replicants.
				Actor_Says(kActorLeon, 110, kAnimationModeTalk); //62-0110.AUD	Can't help you there, friend.
			}
			Actor_Says(kActorMcCoy, 550, 17); //00-0550.AUD	Maybe the clerk can tell me who was renting that room back there.
			if (_vm->_cutContent) {
				if (Game_Flag_Query(kFlagCT09LeonInterrupted)) {
					Actor_Says(kActorMcCoy, 555, 18); //00-0555.AUD	Why were you hassling him?
					Actor_Says(kActorLeon, 120, 13); //62-0120.AUD	He let these creeps in my room. I'm a very private person.
					Actor_Says(kActorMcCoy, 560, kAnimationModeTalk);
					Actor_Says_With_Pause(kActorLeon, 130, 0.8f, kAnimationModeTalk); //62-0130.AUD	Nothing, friend. I ain't done nothing.
					Actor_Face_Current_Camera(kActorMcCoy, true);
					if (Player_Query_Agenda() == kPlayerAgendaSurly 
					|| Player_Query_Agenda() == kPlayerAgendaErratic) {
						Actor_Says(kActorMcCoy, 565, 18); //00-0565.AUD	We're all innocents, aren't we?
					} else {
						Actor_Says(kActorMcCoy, 4880, 13); //00-4880.AUD	Is that right?
					}
					Actor_Face_Actor(kActorMcCoy, kActorLeon, true);
				}
			} else {
				Actor_Says(kActorMcCoy, 555, 18); //00-0555.AUD	Why were you hassling him?
				Actor_Says(kActorLeon, 120, 13); //62-0120.AUD	He let these creeps in my room. I'm a very private person.
				Actor_Says(kActorMcCoy, 560, kAnimationModeTalk);
				Actor_Says_With_Pause(kActorLeon, 130, 0.8f, kAnimationModeTalk); //62-0130.AUD	Nothing, friend. I ain't done nothing.
				Actor_Face_Current_Camera(kActorMcCoy, true);
				Actor_Says(kActorMcCoy, 565, 18);
				Actor_Face_Actor(kActorMcCoy, kActorLeon, true);
			}
			Actor_Says(kActorLeon, 140, 12);
			Actor_Says_With_Pause(kActorMcCoy, 570, 0.0f, 17); //00-0570.AUD	Just help me out here a little more. You seen a big Rasta guy around here?
			// Made it so McCoy only mentions Clovis' description if he has a clue which gave him that information.
			if (_vm->_cutContent) {
				if (Actor_Clue_Query(kActorMcCoy, kClueAnimalMurderSuspect)
				|| Actor_Clue_Query(kActorMcCoy, kClueMorajiInterview)) {
					Actor_Says_With_Pause(kActorMcCoy, 575, 1.2f, 13); //00-0575.AUD	Or a guy with a beard and dark eyes?
				}
			} else {
				Actor_Says_With_Pause(kActorMcCoy, 575, 1.2f, 13); //00-0575.AUD	Or a guy with a beard and dark eyes?
			}
			Actor_Says(kActorLeon, 150, kAnimationModeTalk);
			Actor_Says(kActorMcCoy, 580, kAnimationModeTalk);
			Actor_Says(kActorLeon, 160, 13);
			Actor_Says(kActorLeon, 170, 12);
			Actor_Set_Goal_Number(kActorLeon, kGoalLeonLeave);
		}
		return true;

	case kGoalLeonApproachMcCoy:
		return true;

	case kGoalLeonPunchMcCoy:
	// Made it so Leon now punches McCoy twice. McCoy seems to struggle a bit when he says 'I'm thinking of changing jobs' so it makes sense for
	// him to be hit here. Also made other improvements to this encounter.
		Player_Loses_Control();
		Actor_Face_Actor(kActorMcCoy, kActorLeon, true);
		Actor_Face_Actor(kActorLeon, kActorMcCoy, true);
		Actor_Says(kActorLeon, 40, kAnimationModeTalk); //62-0040.AUD	LPD, huh? You wouldn't be a Blade Runner would ya?
		Actor_Says(kActorMcCoy, 7895, kAnimationModeTalk); //00-7895.AUD	No. I--
		Actor_Change_Animation_Mode(kActorLeon, kAnimationModeCombatAttack);
		Music_Play(kMusicBeating1, 71, 0, 0, -1, kMusicLoopPlayOnce, 2);
		Delay (500);
		Ambient_Sounds_Play_Sound(kSfxKICK2, 90, 99, 0, 0);
		Actor_Says(kActorMcCoy, 8670, 21); //00-8670.AUD	(grunts)
		Delay (500);
		Actor_Says(kActorMcCoy, 510, kAnimationModeTalk); //00-0510.AUD	I'm thinking of changing jobs.
		Actor_Says(kActorLeon, 50, kAnimationModeTalk); //62-0050.AUD	You should have done it long ago. Now you're out of time, LPD. Good night!
		Actor_Start_Speech_Sample(kActorMcCoy, 8509); //00-8509.AUD	Wait a minute.
		Delay (500);
		Actor_Change_Animation_Mode(kActorLeon, kAnimationModeCombatAttack);
		Delay (500);
		Ambient_Sounds_Play_Sound(kSfxKICK2, 90, 99, 0, 0);
		Actor_Change_Animation_Mode(kActorMcCoy, kAnimationModeDie);
		Actor_Retired_Here(kActorMcCoy, 12, 12, true, -1);
		return false;

	case kGoalLeonLeave:
		if (_vm->_cutContent) {
			Scene_Exits_Enable();
		}
		Actor_Force_Stop_Walking(kActorLeon);
		AI_Movement_Track_Flush(kActorLeon);
		AI_Movement_Track_Append(kActorLeon, 351, 0);
		AI_Movement_Track_Append(kActorLeon, 352, 0);
		AI_Movement_Track_Repeat(kActorLeon);
		return true;

	case kGoalLeonGone:
		Actor_Put_In_Set(kActorLeon, kSetFreeSlotA);
		AI_Movement_Track_Flush(kActorLeon);
		return true;
	}
	return false;
}

bool AIScriptLeon::UpdateAnimation(int *animation, int *frame) {
	switch (_animationState) {
	case 0:
		*animation = kModelLeonIdle;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelLeonIdle)) {
			_animationFrame = 0;
		}
		break;

	case 1:
		*animation = kModelLeonWalking;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelLeonWalking)) {
			_animationFrame = 0;
		}
		break;

	case 2:
		if (_animationFrame == 0 && _resumeIdleAfterFramesetCompletesFlag) {
			*animation = kModelLeonIdle;
			_animationState = 0;
		} else {
			*animation = kModelLeonCalmTalk;
			++_animationFrame;
			if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelLeonCalmTalk)) {
				_animationFrame = 0;
			}
		}
		break;

	case 3:
		*animation = kModelLeonComplainTalk;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelLeonComplainTalk)) {
			_animationFrame = 0;
			_animationState = 2;
			*animation = kModelLeonCalmTalk;
		}
		break;

	case 4:
		*animation = kModelLeonAwkwardTalk;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelLeonAwkwardTalk)) {
			_animationFrame = 0;
			_animationState = 2;
			*animation = kModelLeonCalmTalk;
		}
		break;

	case 5:
		*animation = kModelLeonDenyTalk;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelLeonDenyTalk)) {
			_animationFrame = 0;
			_animationState = 2;
			*animation = kModelLeonCalmTalk;
		}
		break;

	case 6:
		if (_animationFrame == 0 && _resumeIdleAfterFramesetCompletesFlag) {
			Actor_Change_Animation_Mode(kActorLeon, 72);
			*animation = kModelLeonGrabHoldHigh;
		} else {
			*animation = kModelLeonGrabTalk;
			++_animationFrame;
			if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelLeonGrabTalk)) {
				_animationFrame = 0;
			}
		}
		break;

	case 7:
		*animation = kModelLeonGrabAndGutPunchTalk;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelLeonGrabAndGutPunchTalk)) {
			_animationFrame = 0;
			_animationState = 6;
			*animation = kModelLeonGrabTalk;
		}
		break;

	case 8:
		*animation = kModelLeonGrabTalk;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelLeonGrabTalk)) {
			_animationFrame = 0;
		}
		break;

	case 9:
		*animation = kModelLeonGrabLetsGo;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelLeonGrabLetsGo)) {
			Actor_Change_Animation_Mode(kActorLeon, kAnimationModeIdle);
			*animation = kModelLeonIdle;
			_animationFrame = 0;
			_animationState = 0;
			if (Actor_Query_Goal_Number(kActorLeon) == kGoalLeonReleaseDeskClerk) {
				Actor_Set_Goal_Number(kActorLeon, kGoalLeonPrepareTalkToMcCoy);
			}
		}
		break;

	case 10:
		*animation = kModelLeonPunchAttack;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(*animation)) {
			*animation = kModelLeonIdle;
			_animationFrame = 0;
			Actor_Change_Animation_Mode(kActorLeon, kAnimationModeIdle);
		}
		break;
	}
	*frame = _animationFrame;
	return true;
}

bool AIScriptLeon::ChangeAnimationMode(int mode) {
	switch (mode) {
	case kAnimationModeIdle:
		switch (_animationState) {
		case 2:
			// fall through
		case 3:
			// fall through
		case 4:
			// fall through
		case 5:
			// fall through
		case 6:
			// fall through
		case 7:
			_resumeIdleAfterFramesetCompletesFlag = true;
			break;

		case 8:
			Actor_Change_Animation_Mode(kActorLeon, 72);
			break;

		default:
			_animationState = 0;
			_animationFrame = 0;
			break;
		}
		break;

	case kAnimationModeWalk:
		_animationState = 1;
		_animationFrame = 0;
		break;

	case kAnimationModeTalk:
		_animationState = 2;
		_animationFrame = 0;
		_resumeIdleAfterFramesetCompletesFlag = false;
		break;

	case kAnimationModeCombatAttack:
		_animationState = 10;
		_animationFrame = 0;
		break;

	case 12:
		_animationState = 3;
		_animationFrame = 0;
		_resumeIdleAfterFramesetCompletesFlag = false;
		break;

	case 13:
		_animationState = 4;
		_animationFrame = 0;
		_resumeIdleAfterFramesetCompletesFlag = false;
		break;

	case 14:
		_animationState = 5;
		_animationFrame = 0;
		_resumeIdleAfterFramesetCompletesFlag = false;
		break;

	case 15:
		_animationState = 6;
		_animationFrame = 0;
		_resumeIdleAfterFramesetCompletesFlag = false;
		break;

	case 16:
		_animationState = 7;
		_animationFrame = 0;
		_resumeIdleAfterFramesetCompletesFlag = false;
		break;

	case 26:
		_animationState = 9;
		_animationFrame = 0;
		break;

	case 72:
		if (_animationState != 8) {
			_animationState = 8;
			_animationFrame = 0;
		}
		break;
	}
	return true;
}

void AIScriptLeon::QueryAnimationState(int *animationState, int *animationFrame, int *animationStateNext, int *animationNext) {
	*animationState     = _animationState;
	*animationFrame     = _animationFrame;
	*animationStateNext = _animationStateNext;
	*animationNext      = _animationNext;
}

void AIScriptLeon::SetAnimationState(int animationState, int animationFrame, int animationStateNext, int animationNext) {
	_animationState     = animationState;
	_animationFrame     = animationFrame;
	_animationStateNext = animationStateNext;
	_animationNext      = animationNext;
}

bool AIScriptLeon::ReachedMovementTrackWaypoint(int waypointId) {
	if (waypointId == 353) {
		Actor_Set_Goal_Number(kActorLeon, kGoalLeonGone);
	}
	return true;
}

void AIScriptLeon::FledCombat() {}

float AIScriptLeon::distanceTo(int actorId, float x, float y, float z) {
	float actorX, actorY, actorZ;
	Actor_Query_XYZ(actorId, &actorX, &actorY, &actorZ);
	return sqrt(static_cast<float>((z - actorZ) * (z - actorZ) + (y - actorY) * (y - actorY) + (x - actorX) * (x - actorX)));
}

} // End of namespace BladeRunner
