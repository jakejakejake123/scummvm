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

AIScriptIsabella::AIScriptIsabella(BladeRunnerEngine *vm) : AIScriptBase(vm) {
	_var1 = 0;
	_varNumOfTimesToHoldCurrentFrame = 0;
	// _varChooseIdleAnimation can have valid values: 0,
	_varChooseIdleAnimation = 0;
	_var4 = 1;
}

void AIScriptIsabella::Initialize() {
	_animationFrame = 0;
	_animationState = 0;
	_animationStateNext = 0;
	_animationNext = 0;

	_var1 = 0;
	_varNumOfTimesToHoldCurrentFrame = 0;
	_varChooseIdleAnimation = 0;
	_var4 = 1;
}

bool AIScriptIsabella::Update() {
	return false;
}

void AIScriptIsabella::TimerExpired(int timer) {
	//return false;
}

void AIScriptIsabella::CompletedMovementTrack() {
	//return false;
}

void AIScriptIsabella::ReceivedClue(int clueId, int fromActorId) {
	//return false;
}

void AIScriptIsabella::ClickedByPlayer() {
	if (_vm->_cutContent) {
		if (Actor_Query_In_Set(kActorIsabella, kSetPS09)) {
			if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -473.0f, 0.2f, -133.0f, 12, false, false, false)) {
				Actor_Face_Actor(kActorMcCoy, kActorIsabella, true);
				Actor_Face_Actor(kActorIsabella, kActorMcCoy, true);
				Actor_Says(kActorMcCoy, 8605, 18);//00-8605.AUD	You staying out of trouble, buddy?
				Actor_Says(kActorIsabella, 170, kAnimationModeTalk); //59-0170.AUD	Why you pick on Mama Isabella? I never do you no harm.
				if (Actor_Clue_Query(kActorMcCoy, kClueSpecialIngredient)
				&& !Actor_Clue_Query(kActorMcCoy, kClueStolenCheese)
				&& !Game_Flag_Query(kFlagIsabellaCheeseTalk)) {
					Game_Flag_Set(kFlagIsabellaCheeseTalk);
					Actor_Says(kActorMcCoy, 1305, 14); //00-1305.AUD	Mia and Murray tell me you're using cheese in your stew. Real cheese.
					Actor_Says(kActorIsabella, 160, kAnimationModeTalk); //59-0160.AUD	Them old buzzards. What they know?
					if (Actor_Query_Is_In_Current_Set(kActorMurray)) {
						Actor_Face_Actor(kActorMcCoy, kActorMurray, true);
						Actor_Face_Actor(kActorIsabella, kActorMurray, true);
						Actor_Face_Actor(kActorMurray, kActorIsabella, true);
						Actor_Face_Actor(kActorMia, kActorIsabella, true);
						Actor_Says(kActorMia, 140, kAnimationModeTalk); //22-0140.AUD	That stew she makes, it always did taste a little gamey.
						Actor_Says(kActorMurray, 220, kAnimationModeTalk); //31-0220.AUD	She's always bragging about her special ingredient.
						Actor_Says(kActorMurray, 230, kAnimationModeTalk); //31-0230.AUD	And she charges an arm and leg for it, too.
						Actor_Says(kActorMurray, 320, kAnimationModeTalk); //31-0320.AUD	Ah... when I was young we respected our elders.
						Delay(1000);
						Actor_Face_Actor(kActorIsabella, kActorMcCoy, true);
						Actor_Face_Actor(kActorMcCoy, kActorIsabella, true);
					}
					Actor_Says(kActorIsabella, 140, kAnimationModeTalk); //59-0140.AUD	Don't know nothing about cheese. That stuff illegal. It bad news.
					Actor_Says(kActorMcCoy, 1365, 13); //00-1365.AUD	I'm not looking to bust the dealer. I just want to know who bought it.
					Delay(2000);
					if (Actor_Query_Is_In_Current_Set(kActorMurray)) {
						Actor_Face_Actor(kActorMcCoy, kActorMurray, true);
						Actor_Face_Actor(kActorIsabella, kActorMurray, true);
						Actor_Face_Actor(kActorMurray, kActorIsabella, true);
						Actor_Says(kActorMurray, 260, kAnimationModeTalk); //31-0260.AUD	Spit it out, woman! McCoy doesn't have all day!
						Actor_Face_Actor(kActorIsabella, kActorMcCoy, true);
						Actor_Face_Actor(kActorMcCoy, kActorIsabella, true);
						Delay (2000);
					}		
					Actor_Says(kActorMcCoy, 8590, 13);  // Not the talkative type
					if (Player_Query_Agenda() == kPlayerAgendaSurly 
					|| Player_Query_Agenda() == kPlayerAgendaErratic) {
						Actor_Says(kActorMcCoy, 4360, 16); //00-4360.AUD	Tell it straight or I'm gonna make sure you get the same as he gets. Full conspiracy, payable for 25.
						Delay(1000);
						Actor_Says(kActorIsabella, 180, kAnimationModeTalk); //59-0180.AUD	My sister. She got connections.
						Actor_Says(kActorMcCoy, 1380, kAnimationModeTalk);
						Actor_Says(kActorIsabella, 190, kAnimationModeTalk); //59-0190.AUD	She back in Jamaica, mon. Far away from here. She send me cheese once maybe twice a month.
						if (Game_Flag_Query(kFlagSadikIsReplicant)) {
							Delay(2000);
							Actor_Says(kActorIsabella, 210, kAnimationModeTalk); //59-0210.AUD	You know, funny thing you asking about the cheese. Last week this ugly little man, he ran by. Grab whole box of empty takeout cartons right off the counter.
							Actor_Says(kActorIsabella, 240, kAnimationModeTalk);
							Actor_Says(kActorMcCoy, 1385, kAnimationModeTalk);
							Actor_Says(kActorIsabella, 260, kAnimationModeTalk);
							Actor_Says(kActorMcCoy, 1390, kAnimationModeTalk);
							if (Actor_Query_Is_In_Current_Set(kActorGordo)) {
								Actor_Face_Actor(kActorIsabella, kActorGordo, true);
								Delay(1500);
								Actor_Face_Actor(kActorGordo, kActorIsabella, true);
								Delay(1500);
							}
							Actor_Says(kActorIsabella, 300, kAnimationModeTalk); //59-0300.AUD	Short, real short. Bad clothes, colors way too bright. Funny bow tie.
							Actor_Clue_Acquire(kActorMcCoy, kClueStolenCheese, false, kActorIsabella);
							if (Actor_Query_Is_In_Current_Set(kActorGordo)) {
								Actor_Face_Actor(kActorMcCoy, kActorGordo, true);
								Delay(1500);
								Actor_Face_Actor(kActorGordo, kActorMcCoy, true);
								Delay(1500);
								Actor_Face_Actor(kActorIsabella, kActorMcCoy, true);
								if (!Actor_Clue_Query(kActorMcCoy, kClueGordoConfession)) {
									if (Actor_Clue_Query(kActorMcCoy, kClueCheese)) {
										Actor_Face_Actor(kActorIsabella, kActorMcCoy, true);
										Actor_Says(kActorMcCoy, 6540, 23); //00-6540.AUD	Did you steal this cheese from Kingston Kitchen?	
										if (Actor_Query_Intelligence(kActorGordo) == 80) {
											Actor_Face_Actor(kActorIsabella, kActorGordo, true);
											Actor_Says(kActorGordo, 1280, 13); //02-1280.AUD	Hey, baby. I may steal a line or two. But I’d never steal some cheese. I don’t do dairy.
											Actor_Face_Actor(kActorIsabella, kActorMcCoy, true);
											if (Player_Query_Agenda() == kPlayerAgendaSurly 
											|| Player_Query_Agenda() == kPlayerAgendaErratic) {
												Actor_Says(kActorMcCoy, 6590, 15); //00-6590.AUD	The owner described you to a tee. Even down to that rotten bow tie you always wear. 
											} else {
												Actor_Says(kActorMcCoy, 6995, 18); //00-6995.AUD	That's not what I heard. You wanna set the record straight?
											}
										}
									} else {
										Actor_Face_Actor(kActorMcCoy, kActorIsabella, true);
										Actor_Says(kActorMcCoy, 3250, kAnimationModeTalk);
										Actor_Face_Actor(kActorIsabella, kActorGordo, true);
										Actor_Says(kActorGordo, 530, 18);
										Actor_Face_Actor(kActorMcCoy, kActorIsabella, true);
										Actor_Says(kActorMcCoy, 3300, 15);
										if (Actor_Query_Intelligence(kActorGordo) == 60) {
											Actor_Face_Actor(kActorIsabella, kActorGordo, true);
											Actor_Says(kActorGordo, 540, 13);
											Actor_Face_Actor(kActorMcCoy, kActorIsabella, true);
											Actor_Says(kActorMcCoy, 3305, kAnimationModeTalk);
											Actor_Face_Actor(kActorIsabella, kActorGordo, true);
											Actor_Says(kActorGordo, 550, 16); //02-0550.AUD	For crying out loud. Can’t a guy make a living in this fakakta place without being hassled?
											Actor_Face_Actor(kActorMcCoy, kActorIsabella, true);
											Actor_Says(kActorMcCoy, 7815, 13); //00-7815.AUD	No.
											Actor_Clue_Acquire(kActorMcCoy, kClueGordoConfession, true, kActorGordo);
											Delay(1000);	
										}
									}
								} else {
									Actor_Face_Actor(kActorMcCoy, kActorIsabella, true);
									Actor_Says(kActorMcCoy, 3250, kAnimationModeTalk);
									Delay(1000);
								}
								Actor_Face_Actor(kActorIsabella, kActorGordo, true);
								Actor_Says(kActorMcCoy, 6600, 13); //00-6600.AUD	Why the big deal over food?
								Actor_Says(kActorGordo, 1310, 14); //02-1310.AUD	It was just some cheese, McCoy. And some takeout cartons.
								Actor_Face_Actor(kActorIsabella, kActorMcCoy, true);
								if (Actor_Clue_Query(kActorMcCoy, kClueKingstonKitchenBox1)
								|| Actor_Clue_Query(kActorMcCoy, kClueKingstonKitchenBox2)) {
									Actor_Says(kActorMcCoy, 6595, 15); //00-6595.AUD	And you gave the takeout cartons to Sadik. 
								}
								Actor_Face_Actor(kActorIsabella, kActorMcCoy, true);
								Actor_Says(kActorMcCoy, 6555, 15); //00-6555.AUD	Let’s hear the rest of it.
								Actor_Face_Actor(kActorIsabella, kActorGordo, true);
								Actor_Says(kActorGordo, 1030, 11); //02-1030.AUD	Sorry, Charlie.
								Delay (2000);
								Actor_Face_Actor(kActorMcCoy, kActorIsabella, true);
								Actor_Face_Actor(kActorIsabella, kActorMcCoy, true);
								Actor_Says(kActorMcCoy, 1970, 13); //00-1970.AUD	You should start thinking about the company you keep.
								Actor_Says(kActorIsabella, 330, kAnimationModeTalk); //59-0330.AUD	You bet, mon. That cheese’s been nothing but trouble for Mama Isabella.
							}
						}
					}
				}
			}
		}
	//return false;
	}
}

void AIScriptIsabella::EnteredSet(int setId) {
	// return false;
}

void AIScriptIsabella::OtherAgentEnteredThisSet(int otherActorId) {
	// return false;
}

void AIScriptIsabella::OtherAgentExitedThisSet(int otherActorId) {
	// return false;
}

void AIScriptIsabella::OtherAgentEnteredCombatMode(int otherActorId, int combatMode) {
	// return false;
}

void AIScriptIsabella::ShotAtAndMissed() {
	// return false;
}

bool AIScriptIsabella::ShotAtAndHit() {
	return false;
}

void AIScriptIsabella::Retired(int byActorId) {
	// return false;
}

int AIScriptIsabella::GetFriendlinessModifierIfGetsClue(int otherActorId, int clueId) {
	return 0;
}

bool AIScriptIsabella::GoalChanged(int currentGoalNumber, int newGoalNumber) {
	return false;
}

bool AIScriptIsabella::UpdateAnimation(int *animation, int *frame) {
	bool flag;

	switch (_animationState) {
	case 0:
		if (_varChooseIdleAnimation == 1) {
			*animation = kModelIsabellaPutsSpicesInSoup;
			++_animationFrame;
			if (_animationFrame > Slice_Animation_Query_Number_Of_Frames(kModelIsabellaPutsSpicesInSoup) - 1) {
				_animationFrame = 0;
			}
			if (_animationFrame < 0) {
				_animationFrame = Slice_Animation_Query_Number_Of_Frames(kModelIsabellaPutsSpicesInSoup) - 1;
			}
			if (_animationFrame == 0) {
				_varChooseIdleAnimation = 0;
				_var4 = 2 * Random_Query(0, 1) - 1;
			}
		} else if (_varChooseIdleAnimation == 0) {
			*animation = kModelIsabellaIdle;
			if (_varNumOfTimesToHoldCurrentFrame > 0) {
				--_varNumOfTimesToHoldCurrentFrame;
				if (_varNumOfTimesToHoldCurrentFrame == 0) {
					_var4 = 2 * Random_Query(0, 1) - 1;
				}
			} else {
				_animationFrame += _var4;
				if (_animationFrame > Slice_Animation_Query_Number_Of_Frames(kModelIsabellaIdle) - 1) {
					_animationFrame = 0;
				}
				if (_animationFrame < 0) {
					_animationFrame = Slice_Animation_Query_Number_Of_Frames(kModelIsabellaIdle) - 1;
				}
				if (_animationFrame == 1) {
					if (!Random_Query(0, 1)) {
						_varNumOfTimesToHoldCurrentFrame = Random_Query(4, 8);
					}
				}
				if (_animationFrame == 11) {
					if (!Random_Query(0, 1)) {
						_varNumOfTimesToHoldCurrentFrame = Random_Query(4, 8);
					}
				}
				if (_animationFrame == 16) {
					if (!Random_Query(0, 1)) {
						_varNumOfTimesToHoldCurrentFrame = Random_Query(4, 8);
					}
				}
				if (_animationFrame == 0) {
					if (!Random_Query(0, 2)) {
						_varChooseIdleAnimation = 1;
					}
				}
			}
		}
		break;

	case 1:
		*animation = kModelIsabellaGestureGiveOrTake;
		++_animationFrame;
		if (_animationFrame > Slice_Animation_Query_Number_Of_Frames(kModelIsabellaGestureGiveOrTake) - 1) {
			flag = true;
			_animationFrame = 0;
		} else {
			if (_animationFrame < 0) {
				_animationFrame = Slice_Animation_Query_Number_Of_Frames(kModelIsabellaGestureGiveOrTake) - 1;
				flag = true;
			} else {
				flag = false;
			}
		}
		if (flag) {
			*animation = kModelIsabellaIdle;
			_animationState = 0;
		}
		break;

	case 2:
		*animation = kModelIsabellaCalmTalk;
		if (_animationFrame < 2 && _var1) {
			_animationFrame = 0;
			_animationState = 0;
		} else {
			++_animationFrame;
			if (_animationFrame > Slice_Animation_Query_Number_Of_Frames(kModelIsabellaCalmTalk) - 1) {
				_animationFrame = 0;
			} else {
				if (_animationFrame < 0) {
					_animationFrame = Slice_Animation_Query_Number_Of_Frames(kModelIsabellaCalmTalk) - 1;
				}
			}
			if (_animationFrame == 0) {
				_animationState = Random_Query(2, 3);
			}
		}
		break;

	case 3:
		*animation = kModelIsabellaSuggestTalk;
		if (_animationFrame < 2 && _var1) {
			_animationFrame = 0;
			_animationState = 0;
		} else {
			++_animationFrame;
			if (_animationFrame > Slice_Animation_Query_Number_Of_Frames(kModelIsabellaSuggestTalk) - 1) {
				_animationFrame = 0;
			} else {
				if (_animationFrame < 0) {
					_animationFrame = Slice_Animation_Query_Number_Of_Frames(kModelIsabellaSuggestTalk) - 1;
				}
			}
			if (_animationFrame == 0) {
				*animation = kModelIsabellaCalmTalk;
				_animationState = 2;
			}
		}
		break;

	case 4:
		*animation = kModelIsabellaProtestTalk;
		++_animationFrame;
		if (_animationFrame > Slice_Animation_Query_Number_Of_Frames(kModelIsabellaProtestTalk) - 1) {
			flag = true;
			_animationFrame = 0;
		} else {
			if (_animationFrame < 0) {
				_animationFrame = Slice_Animation_Query_Number_Of_Frames(kModelIsabellaProtestTalk) - 1;
				flag = true;
			} else {
				flag = false;
			}
		}
		if (flag) {
			*animation = kModelIsabellaCalmTalk;
			_animationState = 2;
		}
		break;

	case 5:
		*animation = kModelIsabellaMoreCalmTalk;
		++_animationFrame;
		if (_animationFrame > Slice_Animation_Query_Number_Of_Frames(kModelIsabellaMoreCalmTalk) - 1) {
			flag = true;
			_animationFrame = 0;
		} else {
			if (_animationFrame < 0) {
				_animationFrame = Slice_Animation_Query_Number_Of_Frames(kModelIsabellaMoreCalmTalk) - 1;
				flag = true;
			} else {
				flag = false;
			}
		}
		if (flag) {
			*animation = kModelIsabellaCalmTalk;
			_animationState = 2;
		}
		break;

	case 6:
		*animation = kModelIsabellaLaughTalk;
		++_animationFrame;
		if (_animationFrame > Slice_Animation_Query_Number_Of_Frames(kModelIsabellaLaughTalk) - 1) {
			flag = true;
			_animationFrame = 0;
		} else {
			if (_animationFrame < 0) {
				_animationFrame = Slice_Animation_Query_Number_Of_Frames(kModelIsabellaLaughTalk) - 1;
				flag = true;
			} else {
				flag = false;
			}
		}
		if (flag) {
			*animation = kModelIsabellaCalmTalk;
			_animationState = 2;
		}
		break;

	case 7:
		*animation = kModelIsabellaLaughTalk;
		++_animationFrame;
		if (_animationFrame > Slice_Animation_Query_Number_Of_Frames(kModelIsabellaLaughTalk) - 1) {
			flag = true;
			_animationFrame = 0;
		} else {
			if (_animationFrame < 0) {
				_animationFrame = Slice_Animation_Query_Number_Of_Frames(kModelIsabellaLaughTalk) - 1;
				flag = true;
			} else {
				flag = false;
			}
		}
		if (flag) {
			*animation = kModelIsabellaCalmTalk;
			_animationState = 2;
		}
		break;

	case 8:
		*animation = kModelIsabellaMoreCalmTalk;
		++_animationFrame;
		if (_animationFrame > Slice_Animation_Query_Number_Of_Frames(kModelIsabellaMoreCalmTalk) - 1) {
			flag = true;
			_animationFrame = 0;
		} else {
			if (_animationFrame < 0) {
				_animationFrame = Slice_Animation_Query_Number_Of_Frames(kModelIsabellaMoreCalmTalk) - 1;
				flag = true;
			} else {
				flag = false;
			}
		}
		if (flag) {
			*animation = kModelIsabellaCalmTalk;
			_animationState = 2;
		}
		break;

	case 9:
		if (_varChooseIdleAnimation == 0) {
			*animation = kModelIsabellaIdle;
		}
		if (_varChooseIdleAnimation == 1) {
			*animation = kModelIsabellaPutsSpicesInSoup;
		}
		if (_animationFrame < Slice_Animation_Query_Number_Of_Frames(*animation)) {
			_animationFrame += 2;
			if (_animationFrame >= Slice_Animation_Query_Number_Of_Frames(*animation)) {
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
		break;

	default:
		break;
	}

	int frames = Slice_Animation_Query_Number_Of_Frames(*animation);

	if (frames != -1)
		_animationFrame %= frames;
	else
		_animationFrame = 0;

	*frame = _animationFrame;

	return true;
}

bool AIScriptIsabella::ChangeAnimationMode(int mode) {
	switch (mode) {
	case 0:
		if (_animationState > 8) {
			_animationState = 0;
			_animationFrame = 0;
		} else {
			_var1 = 1;
		}
		break;

	case 3:
		// fall through
	case 9:
		if (_animationState < 2 || _animationState > 8) {
			_animationState = 9;
			_animationStateNext = 2;
			_animationNext = kModelIsabellaCalmTalk;
			_var1 = 0;
		}
		break;

	case 10:
		// fall through
	case 12:
		if (_animationState < 2 || _animationState > 8) {
			_animationState = 9;
			_animationStateNext = 3;
			_animationNext = kModelIsabellaSuggestTalk;
			_var1 = 0;
		}
		break;

	case 11:
		// fall through
	case 14:
		if (_animationState < 2 || _animationState > 8) {
			_animationState = 9;
			_animationStateNext = 5;
			_animationNext = kModelIsabellaMoreCalmTalk;
			_var1 = 0;
		}
		break;

	case 13:
		if (_animationState < 2 || _animationState > 8) {
			_animationState = 9;
			_animationStateNext = 4;
			_animationNext = kModelIsabellaProtestTalk;
			_var1 = 0;
		}
		break;

	case 15:
		if (_animationState < 2 || _animationState > 8) {
			_animationState = 9;
			_animationStateNext = 6;
			_animationNext = kModelIsabellaLaughTalk;
			_var1 = 0;
		}
		break;

	case 16:
		if (_animationState < 2 || _animationState > 8) {
			_animationState = 9;
			_animationStateNext = 7;
			_animationNext = kModelIsabellaLaughTalk;
			_var1 = 0;
		}
		break;

	case 17:
		if (_animationState < 2 || _animationState > 8) {
			_animationState = 9;
			_animationStateNext = 8;
			_animationNext = kModelIsabellaMoreCalmTalk;
			_var1 = 0;
		}
		break;

	default:
		break;
	}

	return true;
}

void AIScriptIsabella::QueryAnimationState(int *animationState, int *animationFrame, int *animationStateNext, int *animationNext) {
	*animationState     = _animationState;
	*animationFrame     = _animationFrame;
	*animationStateNext = _animationStateNext;
	*animationNext      = _animationNext;
}

void AIScriptIsabella::SetAnimationState(int animationState, int animationFrame, int animationStateNext, int animationNext) {
	_animationState     = animationState;
	_animationFrame     = animationFrame;
	_animationStateNext = animationStateNext;
	_animationNext      = animationNext;
}

bool AIScriptIsabella::ReachedMovementTrackWaypoint(int waypointId) {
	return true;
}

void AIScriptIsabella::FledCombat() {
	// return false;
}

} // End of namespace BladeRunner
