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

AIScriptGeneralDoll::AIScriptGeneralDoll(BladeRunnerEngine *vm) : AIScriptBase(vm) {
	_resumeIdleAfterFramesetCompletesFlag = false;
}

void AIScriptGeneralDoll::Initialize() {
	_animationFrame = 0;
	_animationState = 0;
	_animationStateNext = 0;
	_animationNext = 0;

	_resumeIdleAfterFramesetCompletesFlag = false;

	Actor_Put_In_Set(kActorGeneralDoll, kSetFreeSlotG);
	Actor_Set_At_Waypoint(kActorGeneralDoll, 39, 0);

	Actor_Set_Goal_Number(kActorGeneralDoll, 100);
}

bool AIScriptGeneralDoll::Update() {
	if (Global_Variable_Query(kVariableChapter) == 2
	 && Actor_Query_Goal_Number(kActorGeneralDoll) <= 101
	 && Player_Query_Current_Scene() == kSceneBB05
	) {
		Actor_Set_Goal_Number(kActorGeneralDoll, 101);
		return true;
	}

	if (Global_Variable_Query(kVariableChapter) == 3
	 && Actor_Query_Goal_Number(kActorGeneralDoll) < 200
	) {
		return true;
	}
	// Made it so the general doll is now targetable.
	if (_vm->_cutContent) {
		if (!Game_Flag_Query(kFlagGeneralDollShot)) {
			Actor_Set_Targetable(kActorGeneralDoll, true);
		} else {
			Actor_Set_Targetable(kActorGeneralDoll, false);	
		}
	} else {
		Actor_Set_Targetable(kActorGeneralDoll, false);	
	}
	return true;
}

void AIScriptGeneralDoll::TimerExpired(int timer) {
	if (timer == kActorTimerAIScriptCustomTask2) {
		Actor_Change_Animation_Mode(kActorMcCoy, kAnimationModeDie);
		Actor_Change_Animation_Mode(kActorGeneralDoll, kAnimationModeDie);
		AI_Countdown_Timer_Reset(kActorGeneralDoll, kActorTimerAIScriptCustomTask2);
		return; //true;
	}
	return; //false;
}

void AIScriptGeneralDoll::CompletedMovementTrack() {
	switch (Actor_Query_Goal_Number(kActorGeneralDoll)) {
	case 101:
		if (Player_Query_Current_Scene() == kSceneBB05) {
			switch (Random_Query(0, 5)) {
			case 0:
				Ambient_Sounds_Play_Speech_Sound(kActorGeneralDoll, 0, 80, 0, 0, 0);
				break;

			case 1:
				Ambient_Sounds_Play_Speech_Sound(kActorGeneralDoll, 10, 80, 0, 0, 0);
				break;

			case 2:
				Ambient_Sounds_Play_Speech_Sound(kActorGeneralDoll, 20, 80, 0, 0, 0);
				break;

			case 3:
				Ambient_Sounds_Play_Speech_Sound(kActorGeneralDoll, 30, 80, 0, 0, 0);
				break;

			case 4:
				Ambient_Sounds_Play_Speech_Sound(kActorGeneralDoll, 40, 80, 0, 0, 0);
				break;

			case 5:
				Ambient_Sounds_Play_Speech_Sound(kActorGeneralDoll, 50, 80, 0, 0, 0);
				break;
			}
			Actor_Set_Goal_Number(kActorGeneralDoll, 102);
		} else {
			Actor_Set_Goal_Number(kActorGeneralDoll, 103);
		}
		return; //true;

	case 102:
		Actor_Set_Goal_Number(kActorGeneralDoll, 103);
		return; //true;

	case 103:
		Actor_Set_Goal_Number(kActorGeneralDoll, 101);
		return; //true;

	case 200:
		Actor_Set_Goal_Number(kActorGeneralDoll, 201);
		return; //true;

	case 201:
		Actor_Set_Goal_Number(kActorGeneralDoll, 200);
		return; //true;
	}

	return; //false
}

void AIScriptGeneralDoll::ReceivedClue(int clueId, int fromActorId) {
	//return false;
}

void AIScriptGeneralDoll::ClickedByPlayer() {
	// Made it so if McCoy examines the doll and realizes he won't get any retirement money for it, the option to shoot the doll is no longer available.
	if (_vm->_cutContent) {
		if (!Game_Flag_Query(kFlagGeneralDollShot)) {
			Actor_Face_Actor(kActorMcCoy, kActorGeneralDoll, true);
			Actor_Voice_Over(30, kActorVoiceOver);
			if (Player_Query_Agenda() == kPlayerAgendaSurly 
			|| Player_Query_Agenda() == kPlayerAgendaErratic) {
				Actor_Voice_Over(40, kActorVoiceOver);
			}
			Actor_Set_Targetable(kActorGeneralDoll, false);
		}
	} else {
		Actor_Face_Actor(kActorMcCoy, kActorGeneralDoll, true);
		Actor_Voice_Over(30, kActorVoiceOver);
		Actor_Voice_Over(40, kActorVoiceOver);
	}
}

void AIScriptGeneralDoll::EnteredSet(int setId) {
	// return false;
}

void AIScriptGeneralDoll::OtherAgentEnteredThisSet(int otherActorId) {
	// return false;
}

void AIScriptGeneralDoll::OtherAgentExitedThisSet(int otherActorId) {
	// return false;
}

void AIScriptGeneralDoll::OtherAgentEnteredCombatMode(int otherActorId, int combatMode) {
	// return false;
}

void AIScriptGeneralDoll::ShotAtAndMissed() {
	// return false;
}

bool AIScriptGeneralDoll::ShotAtAndHit() {
	AI_Movement_Track_Flush(kActorGeneralDoll);
	Global_Variable_Increment(kVariableGeneralDollShot, 1);
	if (!Game_Flag_Query(kFlagGeneralDollShot)
	 &&  Global_Variable_Query(kVariableGeneralDollShot) == 1
	) {
		Sound_Play(kSfxSERVOD1, 100, 0, 0, 50);
		Game_Flag_Set(kFlagGeneralDollShot);
		Actor_Set_Goal_Number(kActorGeneralDoll, 104);
		ChangeAnimationMode(kAnimationModeDie);
		Actor_Set_Targetable(kActorGeneralDoll, false);
	}
	// Made it so when you shoot the general doll and Sebastian is in the room he reacts to this and so does McCoy.
	// If you shoot the general doll in front of Sebastian the McCoy is a blade runner clue will be added to Sebastians database and Sebastian will tell you to leave.
	if (_vm->_cutContent) {
		if (Game_Flag_Query(kFlagGeneralDollShot)) {
			if (Actor_Query_Is_In_Current_Set(kActorSebastian)) {		
				Actor_Face_Actor(kActorMcCoy, kActorGeneralDoll, true);
				Actor_Face_Actor(kActorSebastian, kActorMcCoy, true);
				Actor_Modify_Friendliness_To_Other(kActorSebastian, kActorMcCoy, -10);
				Actor_Says(kActorSebastian, 710, 21); //56-0710.AUD	Stop! Please! Why are you doing all these terrible things?
				Actor_Face_Actor(kActorMcCoy, kActorSebastian, true);
				if (Player_Query_Agenda() == kPlayerAgendaSurly 
				|| Player_Query_Agenda() == kPlayerAgendaErratic) {
					Actor_Says(kActorMcCoy, 7275, -1); //  00-7275.AUD	Sometimes I just can't help myself.
				} else {
					Actor_Says(kActorMcCoy, 8519, -1);//00-8519.AUD	What do you say we dish each other the straight goods.
				}
				// Added in an animation where Sebastian tries to run away from McCoy but accidentally hits his head on the vase knocking himself out.
				Actor_Face_Heading(kActorSebastian, 310, true);
				Actor_Change_Animation_Mode(kActorSebastian, 48);
				Delay (500);
				Sound_Play(kSfxBIGPOT4, 50, 0, 0, 50);
				if (Player_Query_Agenda() == kPlayerAgendaSurly 
				|| Player_Query_Agenda() == kPlayerAgendaErratic) {
					Delay(2000);
					Player_Loses_Control();
					Loop_Actor_Walk_To_Actor(kActorMcCoy, kActorSebastian, 24, true, false);
					Player_Gains_Control();
					Delay(1000);
					Actor_Face_Actor(kActorMcCoy, kActorSebastian, true);
					Actor_Says(kActorMcCoy, 8600, 18); //00-8600.AUD	You keeping busy, pal?
				} else {
					Delay(2000);
				}
				Actor_Set_Targetable(kActorGeneralDoll, false);
				Game_Flag_Set(kFlagSebastianKnockedOut);
				Player_Gains_Control();
			} else {	
				Delay (2000);
				Player_Loses_Control();
				Loop_Actor_Walk_To_Actor(kActorMcCoy, kActorGeneralDoll, 24, true, false);
				Player_Gains_Control();
				Actor_Face_Actor(kActorMcCoy, kActorGeneralDoll, true);
				Actor_Voice_Over(60, kActorVoiceOver); //99-0060.AUD	Plastic and wires. Not human and not a Replicant.
				if (Player_Query_Agenda() == kPlayerAgendaSurly 
				|| Player_Query_Agenda() == kPlayerAgendaErratic) {
					Actor_Voice_Over(70, kActorVoiceOver); //99-0070.AUD	And I wasted another bullet.
				} else {
					Actor_Says(kActorMcCoy, 8508, -1); //00-8508.AUD	No retirement swag.
				}
				Delay(500);
				Actor_Set_Targetable(kActorGeneralDoll, false);
			}
			if (Actor_Query_In_Set(kActorMcCoy, kSetBB05)) {
				Actor_Set_Targetable(kActorGeneralDoll, false);
				Sound_Play(kSfxBANGDOOR, 50, 0, 0, 50);
				Actor_Face_Heading(kActorMcCoy, 300, false);
				Delay (2000);
				Actor_Says(kActorMcCoy, 8525, -1); //00-8525.AUD	Hmph.
				Player_Loses_Control();
				Loop_Actor_Walk_To_XYZ(kActorMcCoy, 271.0f, -60.31f, 203.0f, 0, true, false, false);
				Player_Gains_Control();
				Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
				Ambient_Sounds_Remove_All_Looping_Sounds(1u);
				Actor_Put_In_Set(kActorGeneralDoll, kSetBB10);
				Actor_Set_At_XYZ(kActorGeneralDoll, 500.77f, 4.4f, -600.67f, 126);
				Game_Flag_Set(kFlagBB05toBB07);
				Set_Enter(kSetBB07, kSceneBB07);
			}
		}
	}

	return false;
}

void AIScriptGeneralDoll::Retired(int byActorId) {
	// return false;
}

int AIScriptGeneralDoll::GetFriendlinessModifierIfGetsClue(int otherActorId, int clueId) {
	return 0;
}

bool AIScriptGeneralDoll::GoalChanged(int currentGoalNumber, int newGoalNumber) {
	switch (newGoalNumber) {
	case 100:
		AI_Movement_Track_Flush(kActorGeneralDoll);
		AI_Movement_Track_Append(kActorGeneralDoll, 39, 0);
		AI_Movement_Track_Repeat(kActorGeneralDoll);
		break;

	case 101:
		AI_Movement_Track_Flush(kActorGeneralDoll);
		AI_Movement_Track_Append(kActorGeneralDoll, 196, 0);
		AI_Movement_Track_Repeat(kActorGeneralDoll);
		break;

	case 102:
		AI_Movement_Track_Flush(kActorGeneralDoll);
		AI_Movement_Track_Append(kActorGeneralDoll, 197, 0);
		AI_Movement_Track_Repeat(kActorGeneralDoll);
		break;

	case 103:
		AI_Movement_Track_Flush(kActorGeneralDoll);
		if (Random_Query(1, 2) == 1) {
			AI_Movement_Track_Append(kActorGeneralDoll, 198, 0);
			AI_Movement_Track_Append(kActorGeneralDoll, 329, 0);
			AI_Movement_Track_Append(kActorGeneralDoll, 328, 0);
			AI_Movement_Track_Append(kActorGeneralDoll, 330, 0);
			AI_Movement_Track_Append(kActorGeneralDoll, 331, 0);
			AI_Movement_Track_Append(kActorGeneralDoll, 335, 0);
			AI_Movement_Track_Append(kActorGeneralDoll, 139, 0);
			AI_Movement_Track_Append(kActorGeneralDoll, 138, 0);
			AI_Movement_Track_Append(kActorGeneralDoll, 137, 0);
			AI_Movement_Track_Append(kActorGeneralDoll, 136, 0);
			AI_Movement_Track_Append(kActorGeneralDoll, 135, 0);
			AI_Movement_Track_Append(kActorGeneralDoll, 134, 0);
			AI_Movement_Track_Append(kActorGeneralDoll, 326, 0);
			AI_Movement_Track_Append(kActorGeneralDoll, 327, 0);
		} else {
			AI_Movement_Track_Append(kActorGeneralDoll, 136, 0);
			AI_Movement_Track_Append(kActorGeneralDoll, 137, 0);
			AI_Movement_Track_Append(kActorGeneralDoll, 138, 0);
			AI_Movement_Track_Append(kActorGeneralDoll, 139, 0);
			AI_Movement_Track_Append(kActorGeneralDoll, 335, 0);
			AI_Movement_Track_Append(kActorGeneralDoll, 331, 0);
			AI_Movement_Track_Append(kActorGeneralDoll, 327, 0);
			AI_Movement_Track_Append(kActorGeneralDoll, 326, 0);
		}
		AI_Movement_Track_Repeat(kActorGeneralDoll);
		break;

	case 104:
		AI_Movement_Track_Flush(kActorGeneralDoll);
		break;

	case 106:
		AI_Movement_Track_Flush(kActorGeneralDoll);
		AI_Movement_Track_Append(kActorGeneralDoll, 196, 0);
		AI_Movement_Track_Append(kActorGeneralDoll, 197, 0);
		AI_Movement_Track_Repeat(kActorGeneralDoll);
		break;

	case 200:
		AI_Movement_Track_Flush(kActorGeneralDoll);
		Actor_Put_In_Set(kActorGeneralDoll, kSetBB05);
		Actor_Set_At_Waypoint(kActorGeneralDoll, 134, 0);
		Actor_Set_Goal_Number(kActorGeneralDoll, 201);
		break;

	case 201:
		AI_Movement_Track_Flush(kActorGeneralDoll);
		if (Random_Query(1, 2) == 1) {
			AI_Movement_Track_Append(kActorGeneralDoll, 198, 0);
			AI_Movement_Track_Append(kActorGeneralDoll, 329, 0);
			AI_Movement_Track_Append(kActorGeneralDoll, 328, 0);
			AI_Movement_Track_Append(kActorGeneralDoll, 330, 0);
			AI_Movement_Track_Append(kActorGeneralDoll, 331, 0);
			AI_Movement_Track_Append(kActorGeneralDoll, 335, 0);
			AI_Movement_Track_Append(kActorGeneralDoll, 139, 0);
			AI_Movement_Track_Append(kActorGeneralDoll, 138, 0);
			AI_Movement_Track_Append(kActorGeneralDoll, 137, 0);
			AI_Movement_Track_Append(kActorGeneralDoll, 136, 0);
			AI_Movement_Track_Append(kActorGeneralDoll, 135, 0);
			AI_Movement_Track_Append(kActorGeneralDoll, 134, 0);
			AI_Movement_Track_Append(kActorGeneralDoll, 326, 0);
			AI_Movement_Track_Append(kActorGeneralDoll, 327, 0);
		} else {
			AI_Movement_Track_Append(kActorGeneralDoll, 136, 0);
			AI_Movement_Track_Append(kActorGeneralDoll, 137, 0);
			AI_Movement_Track_Append(kActorGeneralDoll, 138, 0);
			AI_Movement_Track_Append(kActorGeneralDoll, 139, 0);
			AI_Movement_Track_Append(kActorGeneralDoll, 335, 0);
			AI_Movement_Track_Append(kActorGeneralDoll, 331, 0);
			AI_Movement_Track_Append(kActorGeneralDoll, 327, 0);
			AI_Movement_Track_Append(kActorGeneralDoll, 326, 0);
		}
		AI_Movement_Track_Repeat(kActorGeneralDoll);
		break;

	case 299:
		AI_Movement_Track_Flush(kActorGeneralDoll);
		break;

	default:
		return false;
	}

	return true;
}

bool AIScriptGeneralDoll::UpdateAnimation(int *animation, int *frame) {
	switch (_animationState) {
	case 0:
		*animation = kModelGeneralDollIdle;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelGeneralDollIdle)) {
			_animationFrame = 0;
		}
		break;

	case 1:
		*animation = kModelGeneralDollHaltSalute;
		if (_animationFrame == 0 && _resumeIdleAfterFramesetCompletesFlag) {
			*animation = kModelGeneralDollIdle;
			_animationFrame = 0;
			_animationState = 0;
		} else {
			++_animationFrame;
			if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelGeneralDollHaltSalute)) {
				_animationFrame = 0;
			}
		}
		break;

	case 2:
		*animation = kModelGeneralDollWalking;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelGeneralDollWalking)) {
			_animationFrame = 0;
		}
		break;

	case 3:
		*animation = kModelGeneralDollGotHit;
		++_animationFrame;
		if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(kModelGeneralDollGotHit)) {
			*animation = kModelGeneralDollIdle;
			_animationFrame = 0;
			_animationState = 0;
		}
		break;

	case 4:
		*animation = kModelGeneralDollShotDead;
		if (_animationFrame < Slice_Animation_Query_Number_Of_Frames(kModelGeneralDollShotDead) - 1) {
			++_animationFrame;
		}
		break;

	default:
		break;
	}
	*frame = _animationFrame;

	return true;
}

bool AIScriptGeneralDoll::ChangeAnimationMode(int mode) {
	switch (mode) {
	case 0:
		if (_animationState == 1) {
			_resumeIdleAfterFramesetCompletesFlag = true;
		} else {
			_animationState = 0;
			_animationFrame = 0;
		}
		break;

	case 1:
		_animationState = 2;
		_animationFrame = 0;
		break;

	case 3:
		_animationState = 1;
		_animationFrame = 0;
		_resumeIdleAfterFramesetCompletesFlag = false;
		break;

	case 43:
		_animationState = 3;
		_animationFrame = 0;
		break;

	case kAnimationModeDie:
		_animationState = 4;
		_animationFrame = 0;
		break;
	}

	return true;
}

void AIScriptGeneralDoll::QueryAnimationState(int *animationState, int *animationFrame, int *animationStateNext, int *animationNext) {
	*animationState     = _animationState;
	*animationFrame     = _animationFrame;
	*animationStateNext = _animationStateNext;
	*animationNext      = _animationNext;
}

void AIScriptGeneralDoll::SetAnimationState(int animationState, int animationFrame, int animationStateNext, int animationNext) {
	_animationState     = animationState;
	_animationFrame     = animationFrame;
	_animationStateNext = animationStateNext;
	_animationNext      = animationNext;
}

bool AIScriptGeneralDoll::ReachedMovementTrackWaypoint(int waypointId) {
	return true;
}

void AIScriptGeneralDoll::FledCombat() {
	// return false;
}

} // End of namespace BladeRunner
