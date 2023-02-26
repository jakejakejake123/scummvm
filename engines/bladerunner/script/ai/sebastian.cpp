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

AIScriptSebastian::AIScriptSebastian(BladeRunnerEngine *vm) : AIScriptBase(vm) {
	_resumeIdleAfterFramesetCompletesFlag = false;
}

void AIScriptSebastian::Initialize() {
	_animationFrame = 0;
	_animationState = 0;
	_animationStateNext = 0;
	_animationNext = 0;

	_resumeIdleAfterFramesetCompletesFlag = false;

	Actor_Set_Goal_Number(kActorSebastian, 0);
}

bool AIScriptSebastian::Update() {
	if (Actor_Query_Goal_Number(kActorSebastian) < 200
	 && Global_Variable_Query(kVariableChapter) == 3
	) {
		Actor_Set_Goal_Number(kActorSebastian, 200);
	}

	return false;
}

void AIScriptSebastian::TimerExpired(int timer) {
	//return false;
}

void AIScriptSebastian::CompletedMovementTrack() {
	//return false;
}

void AIScriptSebastian::ReceivedClue(int clueId, int fromActorId) {
	//return false;
}

void AIScriptSebastian::ClickedByPlayer() {
	if (Actor_Query_Goal_Number(kActorSebastian) == 205) {
		AI_Movement_Track_Pause(kActorSebastian);
		Actor_Face_Actor(kActorSebastian, kActorMcCoy, true);
		Actor_Face_Actor(kActorMcCoy, kActorSebastian, true);
		if (Actor_Clue_Query(kActorSebastian, kClueMcCoyIsABladeRunner)) {
			Actor_Says(kActorMcCoy, 6985, 16);
			Actor_Says(kActorSebastian, 610, 14);
		} else {
			dialogue();
		}

		AI_Movement_Track_Unpause(kActorSebastian);
		return; //true;
	}
	return; //false;
}

void AIScriptSebastian::EnteredSet(int setId) {
	// return false;
}

void AIScriptSebastian::OtherAgentEnteredThisSet(int otherActorId) {
	// return false;
}

void AIScriptSebastian::OtherAgentExitedThisSet(int otherActorId) {
	// return false;
}

void AIScriptSebastian::OtherAgentEnteredCombatMode(int otherActorId, int combatMode) {
	if (otherActorId == kActorMcCoy
	&& !Game_Flag_Query(kFlagSebastianKnockedOut)
	 && combatMode
	) {
		//Made it so McCoy is a little more aggressive towards Sebastian when he pulls out his gun if he is surly or erratic.
		if (_vm->_cutContent) {
			Actor_Face_Actor(kActorSebastian, kActorMcCoy, true);
			Actor_Face_Actor(kActorMcCoy, kActorSebastian, true);
			if (Actor_Query_Friendliness_To_Other(kActorSebastian, kActorMcCoy) > 49) {
				Actor_Says(kActorSebastian, 680, 12); //56-0680.AUD	Hey, you don't need to do that.
			} else {
				Actor_Says(kActorSebastian, 700, 15); //56-0700.AUD	Please! You don't have to pull your gun in here.
			}
			if (Player_Query_Agenda() == kPlayerAgendaSurly 
			|| Player_Query_Agenda() == kPlayerAgendaErratic) {
				Actor_Says_With_Pause(kActorMcCoy, 7265, 0.0f, -1); //00-7265.AUD	Think real hard JF. You got anything here that someone would want?
				Actor_Says(kActorSebastian, 690, 16);//56-0690.AUD	There's nothing in here. People don't even like to come inside my building.
			} else {
				Actor_Says_With_Pause(kActorMcCoy, 7270, 0.0f, -1); //00-7270.AUD	I got ambushed in here once before. It ain't gonna happen again.	
			}
			Actor_Modify_Friendliness_To_Other(kActorSebastian, kActorMcCoy, -2);
		} else {
			Global_Variable_Increment(kVariableGunPulledInFrontOfSebastian, 1);
			Actor_Modify_Friendliness_To_Other(kActorSebastian, kActorMcCoy, -5);
			AI_Movement_Track_Pause(kActorSebastian);
			Actor_Face_Actor(kActorSebastian, kActorMcCoy, true);

			if (Global_Variable_Query(kVariableGunPulledInFrontOfSebastian) == 1) {
				Actor_Says(kActorSebastian, 680, 12);
				Actor_Face_Actor(kActorMcCoy, kActorSebastian, true);
				Actor_Says_With_Pause(kActorMcCoy, 7265, 0.0f, kAnimationModeCombatIdle);
				Actor_Change_Animation_Mode(kActorMcCoy, kAnimationModeCombatIdle);
				Delay(500);
				Actor_Says(kActorSebastian, 690, 16);
			} else {
				Actor_Says(kActorSebastian, 700, 15);
				Actor_Says_With_Pause(kActorMcCoy, 7270, 0.0f, kAnimationModeCombatIdle);
				Actor_Change_Animation_Mode(kActorMcCoy, kAnimationModeCombatIdle);
			}
		}
		AI_Movement_Track_Unpause(kActorSebastian);

		return; //true;
	}
}

void AIScriptSebastian::ShotAtAndMissed() {
	// return false;
}

bool AIScriptSebastian::ShotAtAndHit() {
	return false;
}

void AIScriptSebastian::Retired(int byActorId) {
	// return false;
}

int AIScriptSebastian::GetFriendlinessModifierIfGetsClue(int otherActorId, int clueId) {
	return 0;
}

bool AIScriptSebastian::GoalChanged(int currentGoalNumber, int newGoalNumber) {
	if (newGoalNumber == 200) {
		Actor_Put_In_Set(kActorSebastian, kSetBB05);
		Actor_Set_At_XYZ(kActorSebastian, -13.08f, -60.31f, 100.88f, 470);
	}

	return false;
}

bool AIScriptSebastian::UpdateAnimation(int *animation, int *frame) {
	switch (_animationState) {
	case 0:
		*animation = kModelAnimationSebastianIdle;
		++_animationFrame;
		if (_animationFrame > Slice_Animation_Query_Number_Of_Frames(kModelAnimationSebastianIdle) - 1) {
			_animationFrame = 0;
		}
		break;

	case 1:
		*animation = kModelAnimationSebastianWalking;
		++_animationFrame;
		if (_animationFrame > Slice_Animation_Query_Number_Of_Frames(kModelAnimationSebastianWalking) - 1) {
			_animationFrame = 0;
		}
		break;

	case 2:
		*animation = kModelAnimationSebastianStepsBack;
		++_animationFrame;
		if (_animationFrame > Slice_Animation_Query_Number_Of_Frames(kModelAnimationSebastianStepsBack) - 1) {
			Actor_Change_Animation_Mode(kActorSebastian, kAnimationModeIdle);
			*animation = kModelAnimationSebastianIdle;
			_animationFrame = 0;
			_animationState = 0;
		}
		break;

	case 3:
		*animation = kModelAnimationSebastianTriesToRunHitsHeadAndFalls;
		if (_animationFrame < Slice_Animation_Query_Number_Of_Frames(kModelAnimationSebastianTriesToRunHitsHeadAndFalls) - 1) {
			++_animationFrame;
		}
		break;

	case 4:
		if (_animationFrame == 0 && _resumeIdleAfterFramesetCompletesFlag) {
			Actor_Change_Animation_Mode(kActorSebastian, kAnimationModeIdle);
			*animation = kModelAnimationSebastianIdle;
			_animationState = 0;
			_animationFrame = 0;
		} else {
			*animation = kModelAnimationSebastianCalmHeadNodLeftTalk;
			++_animationFrame;
			if (_animationFrame > Slice_Animation_Query_Number_Of_Frames(kModelAnimationSebastianCalmHeadNodLeftTalk) - 1) {
				_animationFrame = 0;
			}
		}
		break;

	case 5:
		*animation = kModelAnimationSebastianCalmHeadNodRightTalk;
		++_animationFrame;
		if (_animationFrame > Slice_Animation_Query_Number_Of_Frames(kModelAnimationSebastianCalmHeadNodRightTalk) - 1) {
			_animationFrame = 0;
			_animationState = 4;
			*animation = kModelAnimationSebastianCalmHeadNodLeftTalk;
		}
		break;

	case 6:
		*animation = kModelAnimationSebastianSuggestTalk;
		++_animationFrame;
		if (_animationFrame > Slice_Animation_Query_Number_Of_Frames(kModelAnimationSebastianSuggestTalk) - 1) {
			_animationFrame = 0;
			_animationState = 4;
			*animation = kModelAnimationSebastianCalmHeadNodLeftTalk;
		}
		break;

	case 7:
		*animation = kModelAnimationSebastianWonderingTalk;
		++_animationFrame;
		if (_animationFrame > Slice_Animation_Query_Number_Of_Frames(kModelAnimationSebastianWonderingTalk) - 1) {
			_animationFrame = 0;
			_animationState = 4;
			*animation = kModelAnimationSebastianCalmHeadNodLeftTalk;
		}
		break;

	case 8:
		*animation = kModelAnimationSebastianPointingToSelfTalk;
		++_animationFrame;
		if (_animationFrame > Slice_Animation_Query_Number_Of_Frames(kModelAnimationSebastianPointingToSelfTalk) - 1) {
			_animationFrame = 0;
			_animationState = 4;
			*animation = kModelAnimationSebastianCalmHeadNodLeftTalk;
		}
		break;

	case 9:
		*animation = kModelAnimationSebastianScratchEarTalk;
		++_animationFrame;
		if (_animationFrame > Slice_Animation_Query_Number_Of_Frames(kModelAnimationSebastianScratchEarTalk) - 1) {
			_animationFrame = 0;
			_animationState = 4;
			*animation = kModelAnimationSebastianCalmHeadNodLeftTalk;
		}
		break;

	case 10:
		*animation = kModelAnimationSebastianAnnoyedTalk;
		++_animationFrame;
		if (_animationFrame > Slice_Animation_Query_Number_Of_Frames(kModelAnimationSebastianAnnoyedTalk) - 1) {
			_animationFrame = 0;
			_animationState = 4;
			*animation = kModelAnimationSebastianCalmHeadNodLeftTalk;
		}
		break;

	case 11:
		*animation = kModelAnimationSebastianWaitTalk;
		++_animationFrame;
		if (_animationFrame > Slice_Animation_Query_Number_Of_Frames(kModelAnimationSebastianWaitTalk) - 1) {
			_animationFrame = 0;
			_animationState = 4;
			*animation = kModelAnimationSebastianCalmHeadNodLeftTalk;
		}
		break;

	default:
		break;
	}
	*frame = _animationFrame;

	return true;
}

bool AIScriptSebastian::ChangeAnimationMode(int mode) {
	switch (mode) {
	case kAnimationModeIdle:
		if (_animationState > 11) {
			_animationState = 0;
			_animationFrame = 0;
		} else {
			_resumeIdleAfterFramesetCompletesFlag = true;
		}
		break;

	case kAnimationModeWalk:
		_animationState = 1;
		_animationFrame = 0;
		break;

	case kAnimationModeTalk:
		_animationState = 4;
		_animationFrame = 0;
		_resumeIdleAfterFramesetCompletesFlag = false;
		break;

	case 12:
		_animationState = 5;
		_animationFrame = 0;
		_resumeIdleAfterFramesetCompletesFlag = false;
		break;

	case 13:
		_animationState = 6;
		_animationFrame = 0;
		_resumeIdleAfterFramesetCompletesFlag = false;
		break;

	case 14:
		_animationState = 7;
		_animationFrame = 0;
		_resumeIdleAfterFramesetCompletesFlag = false;
		break;

	case 15:
		_animationState = 8;
		_animationFrame = 0;
		_resumeIdleAfterFramesetCompletesFlag = false;
		break;

	case 16:
		_animationState = 9;
		_animationFrame = 0;
		_resumeIdleAfterFramesetCompletesFlag = false;
		break;

	case 17:
		_animationState = 10;
		_animationFrame = 0;
		_resumeIdleAfterFramesetCompletesFlag = false;
		break;

	case 18:
		_animationState = 11;
		_animationFrame = 0;
		_resumeIdleAfterFramesetCompletesFlag = false;
		break;

	case 20:
		_animationState = 2;
		_animationFrame = 0;
		break;

	case kAnimationModeDie:
		_animationState = 3;
		_animationFrame = 0;
		break;
	}

	return true;
}

void AIScriptSebastian::QueryAnimationState(int *animationState, int *animationFrame, int *animationStateNext, int *animationNext) {
	*animationState     = _animationState;
	*animationFrame     = _animationFrame;
	*animationStateNext = _animationStateNext;
	*animationNext      = _animationNext;
}

void AIScriptSebastian::SetAnimationState(int animationState, int animationFrame, int animationStateNext, int animationNext) {
	_animationState     = animationState;
	_animationFrame     = animationFrame;
	_animationStateNext = animationStateNext;
	_animationNext      = animationNext;
}

bool AIScriptSebastian::ReachedMovementTrackWaypoint(int waypointId) {
	return true;
}

void AIScriptSebastian::FledCombat() {
	// return false;
}

void AIScriptSebastian::dialogue() {
	Dialogue_Menu_Clear_List();

	if (_vm->_cutContent) {
		DM_Add_To_List_Never_Repeat_Once_Selected(930, 5, 5, 5); // MORAJI AND CHEW
		DM_Add_To_List_Never_Repeat_Once_Selected(940, 4, 5, 6); // EISENDULLER
		DM_Add_To_List_Never_Repeat_Once_Selected(950, 5, 5, 5); // TYRELL
	} else {
		if (Actor_Query_Friendliness_To_Other(kActorSebastian, kActorMcCoy) >= 45) {
			DM_Add_To_List_Never_Repeat_Once_Selected(930, 5, 5, 5); // MORAJI AND CHEW
			DM_Add_To_List_Never_Repeat_Once_Selected(940, -1, 5, 6); // EISENDULLER
			DM_Add_To_List_Never_Repeat_Once_Selected(950, 5, 5, 5); // TYRELL
		}
	}

	if (Actor_Clue_Query(kActorMcCoy, kClueAnsweringMachineMessage)) {
		if (_vm->_cutContent) {
			DM_Add_To_List_Never_Repeat_Once_Selected(960, 3, 1, 4); // TWINS
		} else {
			DM_Add_To_List_Never_Repeat_Once_Selected(960, 3, -1, 5); // TWINS
		}
	}

	if (Actor_Clue_Query(kActorMcCoy, kClueAnsweringMachineMessage)
	 && Actor_Clue_Query(kActorMcCoy, kClueEnvelope)
	) {
		if (_vm->_cutContent) {
			DM_Add_To_List_Never_Repeat_Once_Selected(970, 2, 3, 4); // RUNCITER
		} else {
			DM_Add_To_List_Never_Repeat_Once_Selected(970, -1, 4, -1); // RUNCITER
		}
	}
	if (_vm->_cutContent) {
		DM_Add_To_List_Never_Repeat_Once_Selected(980, 6, 5, 7); // ROBBERS
		DM_Add_To_List_Never_Repeat_Once_Selected(990, 1, 2, 3); // NEXUS-6
	} else {
		DM_Add_To_List_Never_Repeat_Once_Selected(980, -1, -1, 7); // ROBBERS
		DM_Add_To_List_Never_Repeat_Once_Selected(990, 7, 3, -1); // NEXUS-6
	}

	if (Dialogue_Menu_Query_List_Size()) {
		// This condition clause for non-empty dialogue menu options before adding the DONE option
		// only occurs in Sebastian's AI script.
		// Probably because, selecting "DONE" here, McCoy has nothing to say
		// so there's no point to add it as a "auto-selected" last option
		// if no other options exist in the list
		Dialogue_Menu_Add_DONE_To_List(1000); // DONE
		Dialogue_Menu_Appear(320, 240);
		int answer = Dialogue_Menu_Query_Input();
		Dialogue_Menu_Disappear();

		switch (answer) {
		case 930: // MORAJI AND CHEW
			Actor_Says(kActorMcCoy, 7075, 13);
			Actor_Says(kActorSebastian, 290, 12);
			// Made it so Sebastian will be a bit more forthcoming with McCoy with what he knows if they have high friendlinss with each other.
			if (_vm->_cutContent) {
				if (Actor_Query_Friendliness_To_Other(kActorSebastian, kActorMcCoy) > 49) {
					Actor_Says(kActorSebastian, 300, 13); //56-0300.AUD	I don't go in for the parties and stuff, and I never go down to the Row.
				}
			} else {
				Actor_Says(kActorSebastian, 300, 13); //56-0300.AUD	I don't go in for the parties and stuff, and I never go down to the Row.
			}
			break;

		case 940: // EISENDULLER
			Actor_Says(kActorMcCoy, 7080, 15);
			Actor_Says(kActorSebastian, 310, 13); //56-0310.AUD	We're in different fields.
			if (_vm->_cutContent) {
				if (Actor_Query_Friendliness_To_Other(kActorSebastian, kActorMcCoy) > 49) {
					Actor_Says(kActorSebastian, 320, 16); //56-0320.AUD	I'm in basic bio-genetic design and he works on the practical application of Off-World physics.
					Actor_Says(kActorSebastian, 340, 12); //56-0340.AUD	He seems to be a very nice man.
					Actor_Says(kActorMcCoy, 7120, 14);
					Actor_Says(kActorSebastian, 350, kAnimationModeTalk);
				} else {
					Delay(1000);
				}
			} else {
				Actor_Says(kActorSebastian, 320, 16); //56-0320.AUD	I'm in basic bio-genetic design and he works on the practical application of Off-World physics.
				Actor_Says(kActorSebastian, 340, 12); //56-0340.AUD	He seems to be a very nice man.
				Actor_Says(kActorMcCoy, 7120, 14);
				Actor_Says(kActorSebastian, 350, kAnimationModeTalk);
			}
			Actor_Says(kActorMcCoy, 7125, 13); //00-7125.AUD	He was murdered. Probably by a Replicant.
			Actor_Says(kActorSebastian, 360, 17);
			Actor_Says_With_Pause(kActorMcCoy, 7130, 1.0f, kAnimationModeTalk);
			if (_vm->_cutContent) {
				if (Player_Query_Agenda() != kPlayerAgendaSurly 
				&& Player_Query_Agenda() != kPlayerAgendaErratic) {	
					Actor_Says(kActorMcCoy, 7135, 18); //00-7135.AUD	And who do you think they'll start looking for next?
				} 
			} else {
				Actor_Says(kActorMcCoy, 7135, 18); //00-7135.AUD	And who do you think they'll start looking for next?
			}
			break;

		case 950: // TYRELL
			Actor_Says(kActorMcCoy, 7085, 15);
			Actor_Says_With_Pause(kActorSebastian, 370, 0.30f, 13);
			Actor_Says_With_Pause(kActorSebastian, 380, 0.70f, 17);
			if (_vm->_cutContent) {
				if (Actor_Query_Friendliness_To_Other(kActorSebastian, kActorMcCoy) > 49) {
					Actor_Says(kActorSebastian, 390, 14); //56-0390.AUD	Dr. Tyrell and I play chess every week. I've only beaten him once.
					if (Game_Flag_Query(kFlagChessTableChecked)) {
						Actor_Says(kActorMcCoy, 7140, kAnimationModeTalk); //00-7140.AUD	You're in the middle of a game right now?
						Actor_Says(kActorSebastian, 400, 12);
						Actor_Says(kActorMcCoy, 7145, 16); //00-7145.AUD	I don't have the patience for chess.
						Actor_Says(kActorSebastian, 410, 13);
						Actor_Says(kActorMcCoy, 7150, 17);
						Actor_Says(kActorSebastian, 420, 13);
						Actor_Says(kActorSebastian, 430, 14);
						Actor_Clue_Acquire(kActorMcCoy, kClueChessTable, true, kActorSebastian);
					}
				}
			} else {
				Actor_Says(kActorSebastian, 390, 14); //56-0390.AUD	Dr. Tyrell and I play chess every week. I've only beaten him once.
				if (Actor_Clue_Query(kActorMcCoy, kClueChessTable)) {
					Actor_Says(kActorMcCoy, 7140, kAnimationModeTalk);
					Actor_Says(kActorSebastian, 400, 12);
					Actor_Says(kActorMcCoy, 7145, 16);
					Actor_Says(kActorSebastian, 410, 13);
					Actor_Says(kActorMcCoy, 7150, 17);
					Actor_Says(kActorSebastian, 420, 13);
					Actor_Says(kActorSebastian, 430, 14);
				}
			}
			break;

		case 960: // TWINS
			Actor_Says(kActorMcCoy, 7090, 17);
			Actor_Says(kActorSebastian, 440, 14); //56-0440.AUD	You mean Luther and Lance? They were Dr. Tyrell's favorites until he let them go,	 
			Actor_Says(kActorSebastian, 450, 13); //56-0450.AUD	Nobody really knows why either.	
			Actor_Says(kActorMcCoy, 7155, 13); //00-7155.AUD	You think they'd hold a grudge against Tyrell?
			// What Sebastian says about the twins now changes based on their replicant status.
			if (_vm->_cutContent) {
				if (Game_Flag_Query(kFlagLutherLanceIsReplicant)) {
					Actor_Says(kActorSebastian, 460, 17); //56-0460.AUD	Maybe. But they're decent fellows Mr. McCoy.
				} else {
					Actor_Says(kActorSebastian, 470, 12); //56-0470.AUD	I don't think they'd ever do a mean thing to anybody.
				}
			} else {
				Actor_Says(kActorSebastian, 460, 17); //56-0460.AUD	Maybe. But they're decent fellows Mr. McCoy.
				Actor_Says(kActorSebastian, 470, 12); //56-0470.AUD	I don't think they'd ever do a mean thing to anybody.
			}
			if (_vm->_cutContent) {
				if (Actor_Query_Friendliness_To_Other(kActorSebastian, kActorMcCoy) > 49) {
					Actor_Says(kActorSebastian, 480, 13); //56-0480.AUD	They're real smart, too. Almost as smart as Dr. Tyrell.
					Actor_Says(kActorMcCoy, 7160, 18); //00-7160.AUD	Maybe they're too smart to keep around. Too much competition for the old man.
					Actor_Says(kActorSebastian, 490, 14); //56-0490.AUD	Oh, they could never take Dr. Tyrell's place.
				} 
			} else {
				Actor_Says(kActorSebastian, 480, 13); //56-0480.AUD	They're real smart, too. Almost as smart as Dr. Tyrell.
				Actor_Says(kActorMcCoy, 7160, 18); //00-7160.AUD	Maybe they're too smart to keep around. Too much competition for the old man.
				Actor_Says(kActorSebastian, 490, 14); //56-0490.AUD	Oh, they could never take Dr. Tyrell's place.
			}
			if (_vm->_cutContent) {
				if (!Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
					Actor_Says(kActorMcCoy, 7165, 14); //00-7165.AUD	How about this. Do you think they're the type who might help out renegade Replicants?
					setMcCoyIsABladeRunner();
				}
			} else {
				Actor_Says(kActorMcCoy, 7165, 14);
				setMcCoyIsABladeRunner();
			}
			break;

		case 970: // RUNCITER
			Actor_Says(kActorMcCoy, 7095, 13);
			if (_vm->_cutContent) {
				if (Actor_Query_Friendliness_To_Other(kActorSebastian, kActorMcCoy) > 49) {
					Actor_Says(kActorSebastian, 520, 14);
					Actor_Says(kActorMcCoy, 7180, 12);
					Actor_Says(kActorSebastian, 530, 13);
					Actor_Clue_Acquire(kActorMcCoy, kClueRunciterConfession2, true, kActorSebastian);
					if (!Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
						Actor_Says(kActorMcCoy, 7185, 12); // 00-7185.AUD	So, Tyrell would really be pissed, if he knew Luther and Lance were helping renegade Replicants.
						setMcCoyIsABladeRunner();
					}	
				} else {
					Actor_Says(kActorSebastian, 500, 13); //56-0500.AUD	Deal? I don't think I understand.
					if (Game_Flag_Query(kFlagLutherLanceIsReplicant)) {
						Actor_Says(kActorMcCoy, 7170, 17); //00-7170.AUD	Runciter was paying the twins for something. I saw the cash hidden inside a statue.
						Actor_Says(kActorSebastian, 510, 12);
					}
					if (Player_Query_Agenda() == kPlayerAgendaSurly 
					|| Player_Query_Agenda() == kPlayerAgendaErratic) {	
						Actor_Says(kActorMcCoy, 7175, 18); //00-7175.AUD	Come on, Sebastian, I heard you on the machine. You guys are buddies, right?
						Actor_Says(kActorSebastian, 520, 14);
						Actor_Says(kActorMcCoy, 7180, 12);
						Actor_Says(kActorSebastian, 530, 13);
						Actor_Clue_Acquire(kActorMcCoy, kClueRunciterConfession2, true, kActorSebastian);
						if (!Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
							Actor_Says(kActorMcCoy, 7185, 12); // 00-7185.AUD	So, Tyrell would really be pissed, if he knew Luther and Lance were helping renegade Replicants.
							setMcCoyIsABladeRunner();
						}
					}
				}
			} else {
				Actor_Says(kActorSebastian, 510, 12);
				Actor_Says(kActorMcCoy, 7175, 18);
				Actor_Says(kActorSebastian, 520, 14);
				Actor_Says(kActorMcCoy, 7180, 12);
				Actor_Says(kActorSebastian, 530, 13);
				Actor_Says(kActorMcCoy, 7185, 12);
				setMcCoyIsABladeRunner();
			}
			break;

		case 980: // ROBBERS
			if (_vm->_cutContent) {
				Actor_Says(kActorMcCoy, 7110, 15); //00-7110.AUD	Maybe you can clear something up for me...
				Actor_Says(kActorMcCoy, 7100, 12); //00-7100.AUD	You're sure you don't have much valuable stuff around here?
				Actor_Says(kActorSebastian, 540, 16); //56-0540.AUD	Anything worthwhile I probably would have sold a long time ago. All this is personal stuff. Wouldn't mean a whole lot to anyone but me.
				if (Player_Query_Agenda() == kPlayerAgendaSurly 
				|| Player_Query_Agenda() == kPlayerAgendaErratic) {
					Delay(1000);
					Actor_Says(kActorMcCoy, 7115, 13); //00-7115.AUD	You're sure there isn't anything missing?
					if (Actor_Query_Friendliness_To_Other(kActorSebastian, kActorMcCoy) > 49) {
						Actor_Says(kActorSebastian, 280, 14); //56-0280.AUD	Yes. I mean… No, sir. All my things are here.
					} else {
						Actor_Says(kActorSebastian, 270, 16); //56-0270.AUD	You saw for yourself nothing's here. I wish you'd leave me alone.
						Actor_Modify_Friendliness_To_Other(kActorSebastian, kActorMcCoy, -2);
					}
				} else {
					Actor_Says(kActorMcCoy, 7195, 18); //00-7195.AUD	Maybe they were looking for you.
					Actor_Says(kActorSebastian, 720, 12);
				}
			} else {
				Actor_Says(kActorMcCoy, 7100, 12);
				Actor_Says(kActorSebastian, 540, 16);
				Actor_Says(kActorMcCoy, 7195, 18);
				Actor_Says(kActorSebastian, 720, 12);
			}
			break;

		case 990: // NEXUS-6
			Actor_Says(kActorMcCoy, 7105, 18);
			setMcCoyIsABladeRunner();
			break;

		default:
			break;
		}
	} else if (!_vm->_cutContent) {
		if (Actor_Query_Friendliness_To_Other(kActorSebastian, kActorMcCoy) >= 45) {
			Actor_Says(kActorMcCoy, 7115, 13);
			Actor_Says(kActorSebastian, 280, 14);
		} else {
			Actor_Says(kActorMcCoy, 7110, 15);
			Actor_Says(kActorSebastian, 270, 16);
		}
	}
}

void AIScriptSebastian::setMcCoyIsABladeRunner() {
	Actor_Clue_Acquire(kActorSebastian, kClueMcCoyIsABladeRunner, true, kActorMcCoy);
	Actor_Modify_Friendliness_To_Other(kActorSebastian, kActorMcCoy, -5);
	// Restored an animation where Sebastian takes a step back when he realizes that McCoy is a blade runner.
	if (_vm->_cutContent) {
		Actor_Says(kActorSebastian, 560, 20);
	} else {
		Actor_Says(kActorSebastian, 560, 15);
	}
	if (_vm->_cutContent) {
		if (!Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
			Actor_Says(kActorMcCoy, 7200, 14); //00-7200.AUD	Bingo.
			Actor_Says(kActorSebastian, 570, 16);
		}
	} else {
		Actor_Says(kActorMcCoy, 7200, 14);
		Actor_Says(kActorSebastian, 570, 16);
	}
	Actor_Says(kActorMcCoy, 7205, 17); //00-7205.AUD	The guys who broke in might be Replicants.
	Actor_Says(kActorSebastian, 580, 13);
	if (_vm->_cutContent) {
		if (Player_Query_Agenda() == kPlayerAgendaSurly 
		|| Player_Query_Agenda() == kPlayerAgendaErratic) {
			Actor_Says(kActorMcCoy, 7975, 18); //00-7975.AUD	You tell me.
			Delay(2000);
		} else {
			Actor_Says_With_Pause(kActorMcCoy, 7210, 1.0f, 16); //00-7210.AUD	You worked on the Nexus-6 series, didn't you?
			Actor_Says(kActorSebastian, 590, 12);
			Actor_Says(kActorMcCoy, 7215, 19); //00-7215.AUD	Would you say that the Sixes are smarter than the old Fours and Fives?
			Actor_Says(kActorSebastian, 600, 14);
			Actor_Says(kActorMcCoy, 7220, 13); //00-7220.AUD	So, maybe they want to learn more about themselves.
			Actor_Says_With_Pause(kActorMcCoy, 7225, 0.80f, 14); //00-7225.AUD	Maybe they want to pick your brain about their brains.
		}
	} else {
		Actor_Says_With_Pause(kActorMcCoy, 7210, 1.0f, 16); //00-7210.AUD	You worked on the Nexus-6 series, didn't you?
		Actor_Says(kActorSebastian, 590, 12);
		Actor_Says(kActorMcCoy, 7215, 19); //00-7215.AUD	Would you say that the Sixes are smarter than the old Fours and Fives?
		Actor_Says(kActorSebastian, 600, 14);
		Actor_Says(kActorMcCoy, 7220, 13); //00-7220.AUD	So, maybe they want to learn more about themselves.
		Actor_Says_With_Pause(kActorMcCoy, 7225, 0.80f, 14); //00-7225.AUD	Maybe they want to pick your brain about their brains.
	}
	Actor_Says(kActorSebastian, 610, 15);
	if (_vm->_cutContent) {
		Delay(1000);
		Actor_Says(kActorMcCoy, 5145, 13);
		Player_Loses_Control();
		Loop_Actor_Walk_To_XYZ(kActorMcCoy, -212.0f, -60.31f, 131.0f, 0, true, false, false);
		Player_Gains_Control();
		Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
		Ambient_Sounds_Remove_All_Looping_Sounds(1u);
		Game_Flag_Set(kFlagBB05toBB03);
		Set_Enter(kSetBB03, kSceneBB03);
	}
}

} // End of namespace BladeRunner
