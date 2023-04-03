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

#include "bladerunner/script/scene_script.h"

namespace BladeRunner {

void SceneScriptNR07::InitializeScene() {
	Setup_Scene_Information(-110.0f, -73.5f, -193.0f, 554);

	Scene_Exit_Add_2D_Exit(0, 429, 137, 506, 251, 0);

	Ambient_Sounds_Add_Looping_Sound(kSfxDRAMB5, 25, 0, 1);
}

void SceneScriptNR07::SceneLoaded() {
	Obstacle_Object("VANITY", true);
	Clickable_Object("VASE");	
	// Added code so the dragonfly belt appears on Dektoras desk. It never made sense to me that you just receive the belt after asking Dektora about it.
	// I mean she doesn't give it to you and why would she, you are a complete stranger after all. So now it will appear on her desk and if you try to take it
	// while she's there she will say not to touch it and while she's away you can pick it up.
	if (_vm->_cutContent) {
		if (!Actor_Clue_Query(kActorMcCoy, kClueDragonflyBelt)) {
			if (Actor_Query_Is_In_Current_Set(kActorDektora)) {
				Item_Add_To_World(kItemDragonflyBelt, kModelAnimationDragonflyBelt, kSetNR07,  -103.12, -38.08, 41.14,  0, 12, 12, false, true, false, true);
			}
		}
	}
	if (_vm->_cutContent) {
		if (!Game_Flag_Query(kFlagDragonflyEarringTaken)) {
			if (Actor_Query_Is_In_Current_Set(kActorDektora)) {
				Item_Add_To_World(kItemDragonflyEarring, kModelAnimationDragonflyEarring, kSetNR07, -113.01, -38.24, 0.50, 0, 6, 6, false, true, false, true);
			}
		}
	}
	if (_vm->_cutContent
	    && Global_Variable_Query(kVariableChapter) < 4) {
		// The car is only bought by Reps from CrazyLegs
		// if Dektora is a Replicant (so she will have the note from CrazyLegs)
		// or if Dektora  is human and Gordo is also human (in which case, there'll be no note in the drawer) 
		// We add the region in any case - on Restored Content mode
		// to indicate there might be something of interest there,
		// albeit not all playthroughs will have the note in there.
		Scene_2D_Region_Add(0, 501, 381, 522, 466);
	}
	if (_vm->_cutContent) {
		if (Game_Flag_Query(kFlagEarlyQIsReplicant)) {
			if (!Actor_Query_Is_In_Current_Set(kActorDektora)) {
				Item_Remove_From_World(kItemDragonflyBelt);
				Item_Remove_From_World(kItemDragonflyEarring);
			}
		}
	}
}

bool SceneScriptNR07::MouseClick(int x, int y) {
	return false;
}

bool SceneScriptNR07::ClickedOn3DObject(const char *objectName, bool a2) {
	Actor_Set_Goal_Number(kActorHanoi, kGoalHanoiDefault);

	if (Object_Query_Click("VASE", objectName)) {
		clickedOnVase();
	}

	Actor_Set_Goal_Number(kActorHanoi, kGoalHanoiResetTimer);
	return false;
}

bool SceneScriptNR07::ClickedOnActor(int actorId) {
	if (actorId == kActorDektora) {
		if (Actor_Query_Goal_Number(kActorHolloway) >= kGoalHollowayGoToNR07) { // Holloway is not yet comming
			return true;
		}

		Actor_Set_Goal_Number(kActorHanoi, kGoalHanoiResetTimer);
		Actor_Face_Actor(kActorMcCoy, kActorDektora, true);
		Dialogue_Menu_Clear_List();
		if (Game_Flag_Query(kFlagNR07McCoyIsCop)) {
			if (_vm->_cutContent) {
				if (Actor_Clue_Query(kActorMcCoy, kClueEarlyQInterview)
				|| Actor_Clue_Query(kActorMcCoy, kClueCarWasStolen)
				|| Actor_Clue_Query(kActorMcCoy, kClueDektoraConfession)) {
					if (Player_Query_Agenda() == kPlayerAgendaPolite) { 
						DM_Add_To_List_Never_Repeat_Once_Selected(1110, 3, 2, -1); // CRYSTAL	
					} else {
						DM_Add_To_List_Never_Repeat_Once_Selected(1100, -1, 3, 4); // VOIGT-KAMPFF
					}
				}
			} else {
				DM_Add_To_List_Never_Repeat_Once_Selected(1100, -1, 3, 8); // VOIGT-KAMPFF
				DM_Add_To_List_Never_Repeat_Once_Selected(1110, 8, 2, -1); // CRYSTAL	
			}
			if (_vm->_cutContent) {
				if (Actor_Clue_Query(kActorMcCoy, kClueEarlyInterviewB2)) {
					DM_Add_To_List_Never_Repeat_Once_Selected(1120, 4, 5, 6); // MOONBUS
				}
			}
			if (!_vm->_cutContent) {
				if (Actor_Clue_Query(kActorMcCoy, kClueCarRegistration1)) {
					DM_Add_To_List_Never_Repeat_Once_Selected(1130, 4, 5, 7); // BLACK SEDAN
				}
			}
			if (Actor_Clue_Query(kActorMcCoy, kCluePowerSource)) {
				DM_Add_To_List_Never_Repeat_Once_Selected(1140, 5, 6, 7); // SCORPIONS
			}
		} else {
			if (_vm->_cutContent) {
				DM_Add_To_List_Never_Repeat_Once_Selected(1090, 7, 6, 8); // EARLY-Q
			} else {
				DM_Add_To_List_Never_Repeat_Once_Selected(1090, 7, 5, 4); // EARLY-Q
			}
			DM_Add_To_List_Never_Repeat_Once_Selected(1080, 3, 5, 7); // BELT
		}
		Dialogue_Menu_Add_DONE_To_List(1150); // DONE

		Dialogue_Menu_Appear(320, 240);
		int answer = Dialogue_Menu_Query_Input();
		Dialogue_Menu_Disappear();

		switch (answer) {
		case 1080: // BELT
			talkAboutBelt1();
			break;

		case 1090: // EARLY-Q
			if (_vm->_cutContent) {
				Actor_Face_Actor(kActorDektora, kActorMcCoy, true);
				Actor_Face_Actor(kActorMcCoy, kActorDektora, true);
			}
			Actor_Says(kActorMcCoy, 3650, 13);
#if BLADERUNNER_ORIGINAL_BUGS
			Actor_Says(kActorDektora, 630, 30);
#else
			// Dektora is interrupted here
			if (_vm->_cutContent) {
				if (!Game_Flag_Query(kFlagEarlyQIsReplicant)) {
					Actor_Says_With_Pause(kActorDektora, 630, 0.0f, 30); //03-0630.AUD	He’s always treated me very well. I--
					Actor_Says(kActorMcCoy, 3655, 16);
					if (Game_Flag_Query(kFlagDektoraIsReplicant)) {
						Actor_Says(kActorDektora, 640, 31);
					} else {
						Actor_Says(kActorDektora, 2060, 30); //03-2060.AUD	No.
					}
				} else {
					Actor_Says(kActorDektora, 1440, 31); //03-1440.AUD	I don't see why you need to know that.
				}
			} else {
				Actor_Says_With_Pause(kActorDektora, 630, 0.0f, 30);
#endif // BLADERUNNER_ORIGINAL_BUGS
				Actor_Says(kActorMcCoy, 3655, 16);
				Actor_Says(kActorDektora, 640, 31);
			}
			break;

		case 1100: // VOIGT-KAMPFF
			talkAboutVoightKampff();
			break;

		case 1110: // CRYSTAL
			talkAboutSteele();
			break;

		case 1120: // MOONBUS
			talkAboutMoonbus();
			break;

		case 1130: // BLACK SEDAN
			talkAboutBlackSedan();
			break;

		case 1140: // SCORPIONS
			talkAboutScorpions();
			break;

		default:
			break;
		}

		Actor_Set_Goal_Number(kActorHanoi, kGoalHanoiDefault);
	}
	return false;
}

bool SceneScriptNR07::ClickedOnItem(int itemId, bool a2) {
	if (_vm->_cutContent) {
		if (itemId == kItemDragonflyBelt) {
			if (Actor_Query_Is_In_Current_Set(kActorDektora)) {
				if (!Game_Flag_Query(kFlagNR07McCoyIsCop)) {
					Actor_Face_Item(kActorMcCoy, kItemDragonflyBelt, true);
					Actor_Face_Actor(kActorDektora, kActorMcCoy, true);
					Actor_Says(kActorMcCoy, 3625, 19);
					if (Actor_Query_Friendliness_To_Other(kActorDektora, kActorMcCoy) < 50 
					|| Game_Flag_Query(kFlagDektoraIsReplicant)
					|| Actor_Query_Intelligence(kActorDektora) == 90) {
						Actor_Says(kActorDektora, 1480, 30); //03-1480.AUD	Yes
						Delay(1000);
					} else {
						Actor_Says(kActorDektora, 570, 30);
						Actor_Says_With_Pause(kActorDektora, 580, 1.0f, 31);
						Actor_Says(kActorMcCoy, 3630, 13);
						Actor_Says_With_Pause(kActorDektora, 590, 1.0f, 30);
						Actor_Says(kActorDektora, 600, 30);
						Actor_Says_With_Pause(kActorMcCoy, 3635, 1.5f, 18); // Insects, hm.
						Actor_Clue_Acquire(kActorMcCoy, kClueDektoraInterview2, true, kActorDektora);
					}
					Actor_Face_Actor(kActorMcCoy, kActorDektora, true);
					Actor_Says(kActorMcCoy, 3640, 14);  // Tell you the truth, I'm from the LPD. (...)
					Actor_Modify_Friendliness_To_Other(kActorDektora, kActorMcCoy, -2);
					Game_Flag_Set(kFlagNR07McCoyIsCop);
					if (!Game_Flag_Query(kFlagEarlyQIsReplicant)) {
						Actor_Says_With_Pause(kActorDektora, 610, 0.0f, 31); //03-0610.AUD	Is this about Early Q? Because I could tell you--
					} else {
						Delay(1000);
						Actor_Says(kActorDektora, 1980, kAnimationModeSit); //03-1980.AUD	All right.
						Delay(1000);
					}
					if (!Actor_Clue_Query(kActorMcCoy, kClueDragonflyCollection)) {
						Actor_Says(kActorMcCoy, 3645, 12);
						if (Actor_Query_Friendliness_To_Other(kActorDektora, kActorMcCoy) < 50 
						|| Game_Flag_Query(kFlagDektoraIsReplicant)
						|| Actor_Query_Intelligence(kActorDektora) == 90) {
							Actor_Says(kActorDektora, 620, 30); //03-0620.AUD	I’m sure I don’t know what you mean.
							if (Player_Query_Agenda() == kPlayerAgendaSurly 
							|| Player_Query_Agenda() == kPlayerAgendaErratic) {
								Actor_Says(kActorMcCoy, 2485, 19); //00-2485.AUD	I’ve a hard time believing that.
								Actor_Modify_Friendliness_To_Other(kActorDektora, kActorMcCoy, -2);
								Delay(1000);
							} else {
								Actor_Says(kActorMcCoy, 8225, 14); //00-8225.AUD	Just relax.
								Actor_Modify_Friendliness_To_Other(kActorDektora, kActorMcCoy, 2);
								Delay(1000);
							}
						} else {
							Actor_Says(kActorDektora, 1480, 30); //03-1480.AUD	Yes
						}
					}
					Actor_Says(kActorMcCoy, 7395, 14); //00-7395.AUD	What's your name?
					Actor_Says(kActorDektora, 1470, 30); //03-1470.AUD	Dektora.
					Delay(1000);
					if (Actor_Clue_Query(kActorMcCoy, kClueCarRegistration1)) {
						Actor_Says(kActorMcCoy, 3615, 16);
						if (Actor_Query_Friendliness_To_Other(kActorDektora, kActorMcCoy) < 50 
						|| Game_Flag_Query(kFlagDektoraIsReplicant)
						|| Actor_Query_Intelligence(kActorDektora) == 90) {
							Actor_Says(kActorDektora, 2060, 30); //03-2060.AUD	No.
							if (Player_Query_Agenda() == kPlayerAgendaSurly 
							|| Player_Query_Agenda() == kPlayerAgendaErratic) {
								Actor_Says(kActorMcCoy, 6995, 18); //00-6995.AUD	That's not what I heard. You wanna set the record straight?
								Delay(1000); 
								Actor_Modify_Friendliness_To_Other(kActorDektora, kActorMcCoy, -2);
								Actor_Says(kActorDektora, 1980, 30); //03-1980.AUD	All right.
								Actor_Says(kActorDektora, 1480, 30); //03-1480.AUD	Yes
								Delay(500);
								Actor_Says(kActorDektora, 770, 30);
								Actor_Says(kActorMcCoy, 3720, 15);
								Actor_Says_With_Pause(kActorDektora, 780, 2.0f, 30);
								Actor_Says(kActorDektora, 790, 31);
								Actor_Clue_Acquire(kActorMcCoy, kClueCarWasStolen, true, kActorDektora);
								Actor_Says(kActorMcCoy, 3725, 18); //00-3725.AUD	Is that right? Any reason you didn’t tell me that right off?
								Actor_Says(kActorDektora, 800, 30);
								Actor_Says_With_Pause(kActorMcCoy, 3730, 2.0f, 13); //00-3730.AUD	Animal murder is pretty horrible.
								Actor_Says(kActorDektora, 1480, 30); //03-1480.AUD	Yes
							}
						} else {
							Actor_Says(kActorDektora, 770, 30);
							Actor_Says(kActorMcCoy, 3720, 15);
							Actor_Says_With_Pause(kActorDektora, 780, 2.0f, 30);
							Actor_Says(kActorDektora, 790, 31);
							Actor_Clue_Acquire(kActorMcCoy, kClueCarWasStolen, true, kActorDektora);
							if (Player_Query_Agenda() == kPlayerAgendaSurly 
							|| Player_Query_Agenda() == kPlayerAgendaErratic) {
								Actor_Says(kActorMcCoy, 3725, 18); //00-3725.AUD	Is that right? Any reason you didn’t tell me that right off?
								Actor_Says(kActorDektora, 800, 30);
								Actor_Modify_Friendliness_To_Other(kActorDektora, kActorMcCoy, -2);
							} 
							Actor_Says_With_Pause(kActorMcCoy, 3730, 2.0f, 13); //00-3730.AUD	Animal murder is pretty horrible.
							if (Actor_Query_Friendliness_To_Other(kActorDektora, kActorMcCoy) < 50) {
								Actor_Says(kActorDektora, 1480, 30); //03-1480.AUD	Yes
							} else {
								Actor_Says_With_Pause(kActorDektora, 810, 1.0f, kAnimationModeSit);
								Actor_Says(kActorDektora, 820, 30);	 //03-0820.AUD	Any murder is horrible. And unfortunate.
								Actor_Says(kActorMcCoy, 3735, 14); //00-3735.AUD	Some are worse than others.
								Actor_Says(kActorDektora, 830, 31);
								Actor_Says(kActorMcCoy, 3740, 19);
							}
						}
					}
					if (Actor_Clue_Query(kActorMcCoy, kCluePurchasedScorpions)) { 
						if (Actor_Clue_Query(kActorMcCoy, kClueScorpionbox)
						|| Game_Flag_Query(kFlagScorpionsDiscovered)) {
							Delay(1000);
							Actor_Face_Actor(kActorDektora, kActorMcCoy, true);
							Actor_Face_Actor(kActorMcCoy, kActorDektora, true);
							Actor_Says(kActorMcCoy, 3620, 19); //00-3620.AUD	You like scorpions, huh?
							Actor_Says(kActorDektora, 840, 30); //03-0840.AUD	Scorpions?
							Actor_Says(kActorMcCoy, 3745, 9); //00-3745.AUD	Insects. Fakes. From Animoid Row. You buy a box of them?
							if (Actor_Query_Friendliness_To_Other(kActorDektora, kActorMcCoy) < 50 
							|| Game_Flag_Query(kFlagDektoraIsReplicant)
							|| Actor_Query_Intelligence(kActorDektora) == 90) {
								Actor_Says(kActorDektora, 2360, 30); //03-2360.AUD	Of course not.
								if (Player_Query_Agenda() == kPlayerAgendaSurly 
								|| Player_Query_Agenda() == kPlayerAgendaErratic) {
									Actor_Says(kActorMcCoy, 8519, 14);//00-8519.AUD	What do you say we dish each other the straight goods.
									Actor_Modify_Friendliness_To_Other(kActorDektora, kActorMcCoy, -2);
									Delay(1000);
									Actor_Says_With_Pause(kActorDektora, 850, 1.0f, 30); // I didn't know what they were called
									Actor_Says(kActorDektora, 860, 31); //03-0860.AUD	Insects make excellent pets. And they were so beautiful I just had to have the whole set.
									Actor_Says(kActorMcCoy, 3750, 11); //00-3750.AUD	Did you know they were poisonous?
									Actor_Says(kActorDektora, 880, 30);
									Actor_Says(kActorMcCoy, 3755, 16); //00-3755.AUD	And that doesn’t scare you?
									Actor_Says(kActorDektora, 890, 31);
									Actor_Says(kActorDektora, 900, 30); // Who would need to add insects to the list?
									Actor_Clue_Acquire(kActorMcCoy, kClueDektoraInterview4, true, kActorDektora);
								}
							} else {
								Actor_Says_With_Pause(kActorDektora, 850, 1.0f, 30); // I didn't know what they were called
								Actor_Says(kActorDektora, 860, 31); //03-0860.AUD	Insects make excellent pets. And they were so beautiful I just had to have the whole set.
								Actor_Clue_Acquire(kActorMcCoy, kClueDektoraInterview4, true, kActorDektora);
								Actor_Says(kActorMcCoy, 3750, 11); //00-3750.AUD	Did you know they were poisonous?
								Actor_Says(kActorDektora, 880, 30);
								Actor_Says(kActorMcCoy, 3755, 16); //00-3755.AUD	And that doesn’t scare you?
								Actor_Says(kActorDektora, 890, 31);
								Actor_Says(kActorDektora, 900, 30); // Who would need to add insects to the list?
							}
						}
					} else if (Actor_Clue_Query(kActorMcCoy, kClueScorpions)
					&& Actor_Clue_Query(kActorMcCoy, kClueWomanInAnimoidRow)) {
						Delay(1000);
						Actor_Face_Actor(kActorDektora, kActorMcCoy, true);
						Actor_Face_Actor(kActorMcCoy, kActorDektora, true);
						Actor_Says(kActorMcCoy, 3620, 19); //00-3620.AUD	You like scorpions, huh?
						Actor_Says(kActorDektora, 840, 30); //03-0840.AUD	Scorpions?
						Actor_Says(kActorMcCoy, 3745, 9); //00-3745.AUD	Insects. Fakes. From Animoid Row. You buy a box of them?
						if (Actor_Query_Friendliness_To_Other(kActorDektora, kActorMcCoy) < 50 
						|| Game_Flag_Query(kFlagDektoraIsReplicant)
						|| Actor_Query_Intelligence(kActorDektora) == 90) {
							Actor_Says(kActorDektora, 2060, 30); //03-2060.AUD	No.
							if (Player_Query_Agenda() == kPlayerAgendaSurly 
							|| Player_Query_Agenda() == kPlayerAgendaErratic) {
								Actor_Says(kActorMcCoy, 6995, 18); //00-6995.AUD	That's not what I heard. You wanna set the record straight?
								Actor_Modify_Friendliness_To_Other(kActorDektora, kActorMcCoy, -2);
								Delay(1000);
								Actor_Says_With_Pause(kActorDektora, 850, 1.0f, 30); // I didn't know what they were called
								Actor_Says(kActorDektora, 860, 31); //03-0860.AUD	Insects make excellent pets. And they were so beautiful I just had to have the whole set.
								Actor_Says(kActorMcCoy, 3750, 11); //00-3750.AUD	Did you know they were poisonous?
								Actor_Says(kActorDektora, 880, 30);
								Actor_Says(kActorMcCoy, 3755, 16); //00-3755.AUD	And that doesn’t scare you?
								Actor_Says(kActorDektora, 890, 31);
								Actor_Says(kActorDektora, 900, 30); // Who would need to add insects to the list?
								Actor_Clue_Acquire(kActorMcCoy, kClueDektoraInterview4, true, kActorDektora);
							}
						} else {
							Actor_Says_With_Pause(kActorDektora, 850, 1.0f, 30); // I didn't know what they were called
							Actor_Says(kActorDektora, 860, 31); //03-0860.AUD	Insects make excellent pets. And they were so beautiful I just had to have the whole set.
							Actor_Clue_Acquire(kActorMcCoy, kClueDektoraInterview4, true, kActorDektora);
							Actor_Says(kActorMcCoy, 3750, 11); //00-3750.AUD	Did you know they were poisonous?
							Actor_Says(kActorDektora, 880, 30);
							Actor_Says(kActorMcCoy, 3755, 16); //00-3755.AUD	And that doesn’t scare you?
							Actor_Says(kActorDektora, 890, 31);
							Actor_Says(kActorDektora, 900, 30); // Who would need to add insects to the list?
						}
					}
				} else {
					Loop_Actor_Walk_To_Item(kActorMcCoy, kItemDragonflyBelt, 12, true, false);
					Actor_Face_Item(kActorMcCoy, kItemDragonflyBelt, true);
					Actor_Change_Animation_Mode(kActorMcCoy, 23);
					Delay(800);
					Actor_Face_Object(kActorDektora, "VANITY", true);
					Actor_Says(kActorDektora, 560, 31); // Please don't touch that. It's private.
					Actor_Says(kActorMcCoy, 8525, 19);  // Hmph.
				}
			} else {
				Loop_Actor_Walk_To_Item(kActorMcCoy, kItemDragonflyBelt, 12, true, false);
				Actor_Face_Item(kActorMcCoy, kItemDragonflyBelt, true);
				Actor_Change_Animation_Mode(kActorMcCoy, 23);
				Delay(800);
				Actor_Clue_Acquire(kActorMcCoy, kClueDragonflyBelt, true, kActorDektora);
				Item_Pickup_Spin_Effect(kModelAnimationDragonflyBelt, 542, 350);
				Item_Remove_From_World(kItemDragonflyBelt);
				Delay(800);
				Actor_Says(kActorMcCoy, 8825, 13);
			}	
		}
		if (itemId == kItemDragonflyEarring) {
			if (Actor_Query_Is_In_Current_Set(kActorDektora)) {
				Loop_Actor_Walk_To_Item(kActorMcCoy, kItemDragonflyEarring, 12, true, false);
				Actor_Face_Item(kActorMcCoy, kItemDragonflyEarring, true);
				Actor_Change_Animation_Mode(kActorMcCoy, 23);
				Delay(800);
				Actor_Face_Object(kActorDektora, "VANITY", true);
				if (!Game_Flag_Query(kFlagNR07McCoyIsCop)) {
					Actor_Says(kActorMcCoy, 3610, 19);  // Sorry (McCoy fake fan voice)
				} else {
					Actor_Says(kActorMcCoy, 8525, 19);  // Hmph.
				}
			} else {
				Loop_Actor_Walk_To_Item(kActorMcCoy, kItemDragonflyEarring, 12, true, false);
				Actor_Face_Item(kActorMcCoy, kItemDragonflyEarring, true);
				Actor_Change_Animation_Mode(kActorMcCoy, 23);
				Delay(800);
				Item_Remove_From_World(kItemDragonflyEarring);
				Item_Pickup_Spin_Effect(kModelAnimationDragonflyEarring, 330, 239);
				Delay(800);		
				Actor_Says(kActorMcCoy, 8765, 13); //00-8765.AUD	An earring.
				if (!Actor_Clue_Query(kActorMcCoy, kClueDragonflyEarring)) {
					Actor_Clue_Acquire(kActorMcCoy, kClueDragonflyEarring, true, kActorDektora);
				}
				Game_Flag_Set(kFlagDragonflyEarringTaken);
			}
		}
	}
	return true;
}

bool SceneScriptNR07::ClickedOnExit(int exitId) {
	if (exitId == 0) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -102.0f, -73.5f, -233.0f, 0, true, false, false)) {
			Actor_Set_Goal_Number(kActorHanoi, kGoalHanoiResetTimer);
			Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
			Ambient_Sounds_Remove_All_Looping_Sounds(1u);
			Game_Flag_Set(kFlagNR07toNR06);
			Set_Enter(kSetNR06, kSceneNR06);
		}
		return true;
	}
	return false;
}

bool SceneScriptNR07::ClickedOn2DRegion(int region) {
	if (_vm->_cutContent
	    && region == 0) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -134.5f, -73.35f, 43.98f, 4, true, false, false)) {
			Player_Loses_Control();
			Actor_Face_Object(kActorMcCoy, "VANITY", true);
			if (Actor_Query_Is_In_Current_Set(kActorDektora)) {
				Actor_Change_Animation_Mode(kActorMcCoy, 23);
				Delay(800);
				Actor_Face_Object(kActorDektora, "VANITY", true);
				Actor_Says(kActorDektora, 560, 31); // Please don't touch that. It's private.
				if (!Game_Flag_Query(kFlagNR07McCoyIsCop)) {
					Actor_Says(kActorMcCoy, 3610, 19);  // Sorry (McCoy fake fan voice)
				} else {
					if (Player_Query_Agenda() == kPlayerAgendaSurly 
					|| Player_Query_Agenda() == kPlayerAgendaErratic) {
						Actor_Says(kActorMcCoy, 4475, 17); //00-4475.AUD	Yeah. I forgot you were keeping your lacy underthings in there.
						Actor_Modify_Friendliness_To_Other(kActorDektora, kActorMcCoy, -2);
					} else {
						Actor_Says(kActorMcCoy, 8525, 19);  // Hmph.
					}			
				}
			} else {
				if (Game_Flag_Query(kFlagDektoraIsReplicant)
				&& Game_Flag_Query(kFlagZubenIsReplicant)
				&& Actor_Query_Intelligence(kActorDektora) == 70) {
					if (Actor_Clue_Query(kActorMcCoy, kClueCrazysInvolvement)) {
						Actor_Says(kActorMcCoy, 8580, 12); // Nothing else there
					} else {
						Actor_Change_Animation_Mode(kActorMcCoy, 23);
						Sound_Play(kSfxDRAWER1, 90, 85, 85, 50);
						Delay(700);
						Actor_Clue_Acquire(kActorMcCoy, kClueCrazysInvolvement, false, -1);
						// McCoy picks up a sales brochure (it's CrazyLeg's -- but the model is the same as the Tyrell's Pamphlet)
						Item_Pickup_Spin_Effect(kModelAnimationTyrellSalesPamphlet, 508, 401);
						// McCoy finds something inside the brochure - CrazyLeg's note to the Replicants
						// Logic is similar to HC03 (finding photos inside Izo's camera)
						Actor_Voice_Over(3690, kActorVoiceOver); // Hmm
						Delay(1200);
						Item_Pickup_Spin_Effect(kModelAnimationLetter, 508, 401);
						Actor_Says(kActorMcCoy, 6975, 12); // Interesting
						// We don't remove the region after picking the clue
						// McCoy will just point out that there's nothing more there to find.
						// (Saves us from using up a flag and having to write extra code)
						Actor_Change_Animation_Mode(kActorMcCoy, 23);
						Delay(2000);
						Item_Pickup_Spin_Effect(kModelAnimationPhoto, 508, 401);
						Actor_Says(kActorMcCoy, 7960, 13); //00-7960.AUD	Dektora?
						Delay(1500);
						Actor_Says(kActorMcCoy, 6975, 12); // Interesting
					}
				} else {
					Actor_Change_Animation_Mode(kActorMcCoy, 23);
					Sound_Play(kSfxDRAWER1, 90, 85, 85, 50);
					Delay(1500);
					Actor_Voice_Over(3700, kActorVoiceOver); // Nothing
				}
			}
			Player_Gains_Control();
		}
		return true;
	}
	return false;
}

void SceneScriptNR07::SceneFrameAdvanced(int frame) {
}

void SceneScriptNR07::ActorChangedGoal(int actorId, int newGoal, int oldGoal, bool currentSet) {
}

void SceneScriptNR07::PlayerWalkedIn() {
	// Altered
	if (_vm->_cutContent) {
		Loop_Actor_Walk_To_XYZ(kActorMcCoy, -112.0f, -73.0f, -89.0f, 0, false, false, false);
	} else {
		Loop_Actor_Walk_To_XYZ(kActorMcCoy, -110.0f, -73.5f, -169.0f, 0, false, false, false);
	}

	if (Actor_Query_In_Set(kActorDektora, kSetNR07)) {
		if (!Game_Flag_Query(kFlagNR07Entered)) {
			Game_Flag_Set(kFlagNR07Entered);

			if (!_vm->_cutContent) {
				if (!Actor_Clue_Query(kActorDektora, kClueMcCoyIsABladeRunner)) {
					Actor_Modify_Friendliness_To_Other(kActorDektora, kActorMcCoy, 5);
				} else if (Actor_Clue_Query(kActorMcCoy, kClueMcCoyWarnedIzo)
				|| Actor_Clue_Query(kActorMcCoy, kClueMcCoyHelpedIzoIzoIsAReplicant)
				) {
					Actor_Modify_Friendliness_To_Other(kActorDektora, kActorMcCoy, 10);
				}
			}
			if (_vm->_cutContent) {
				Actor_Face_Actor(kActorDektora, kActorMcCoy, true);
				Actor_Face_Actor(kActorMcCoy, kActorDektora, true);
				Music_Play(kMusicTaffy3, 41, 0, 2, -1, kMusicLoopPlayOnce, 0);
			}
			Actor_Says(kActorDektora, 500, 30);
			if (_vm->_cutContent) {
				if (Player_Query_Agenda() != kPlayerAgendaPolite) {
					Actor_Says(kActorMcCoy, 3585, 14); //00-3585.AUD	I just wanted to say: Wow, you were awe inspiring.
					Actor_Says(kActorDektora, 510, 30);
					Actor_Start_Speech_Sample(kActorMcCoy, 3590);
					Delay(1000);
					Actor_Says(kActorDektora, 520, kAnimationModeSit);
				} else {
					Actor_Face_Item(kActorMcCoy, kItemDragonflyBelt, true);
					Delay(1000);
					Actor_Says(kActorMcCoy, 4920, 15); //00-4920.AUD	You got some nice pieces here.
					Actor_Modify_Friendliness_To_Other(kActorDektora, kActorMcCoy, 2);
					Actor_Face_Actor(kActorMcCoy, kActorDektora, true);
					Actor_Says(kActorDektora, 510, 30); //03-0510.AUD	Well, thank you very much, mister…?
					Actor_Says(kActorMcCoy, 1820, 13); //00-1820.AUD	Ray McCoy.
					Delay(1000);
					Actor_Says(kActorDektora, 520, kAnimationModeSit); //03-0520.AUD	Is there something I can do for you, Mr. McCoy?
					Actor_Says(kActorMcCoy, 3640, 14);  // Tell you the truth, I'm from the LPD. (...)
					if (!Game_Flag_Query(kFlagEarlyQIsReplicant)) {
						Actor_Says_With_Pause(kActorDektora, 610, 0.0f, 31); //03-0610.AUD	Is this about Early Q? Because I could tell you--
					} else {
						Delay(1000);
						Actor_Says(kActorDektora, 1980, kAnimationModeSit); //03-1980.AUD	All right.
						Delay(1000);
					}
					if (!Actor_Clue_Query(kActorMcCoy, kClueDragonflyCollection)) {	
						Actor_Says(kActorMcCoy, 3645, 12);
						if (Actor_Query_Friendliness_To_Other(kActorDektora, kActorMcCoy) < 50 
						|| Game_Flag_Query(kFlagDektoraIsReplicant)
						|| Actor_Query_Intelligence(kActorDektora) == 90) {
							Actor_Says(kActorDektora, 620, 30); //03-0620.AUD	I’m sure I don’t know what you mean.
							if (Player_Query_Agenda() == kPlayerAgendaSurly 
							|| Player_Query_Agenda() == kPlayerAgendaErratic) {
								Actor_Says(kActorMcCoy, 2485, 19); //00-2485.AUD	I’ve a hard time believing that.
								Actor_Modify_Friendliness_To_Other(kActorDektora, kActorMcCoy, -2);
								Delay(1000);
							} else {
								Actor_Says(kActorMcCoy, 8225, 14); //00-8225.AUD	Just relax.
								Actor_Modify_Friendliness_To_Other(kActorDektora, kActorMcCoy, 2);
								Delay(1000);
							}
						} else {
							Actor_Says(kActorDektora, 1480, 30); //03-1480.AUD	Yes
							Delay(1000);
						}
					}
					Actor_Says(kActorMcCoy, 7395, 14); //00-7395.AUD	What's your name?
					Actor_Says(kActorDektora, 1470, 30); //03-1470.AUD	Dektora.
					Game_Flag_Set(kFlagNR07McCoyIsCop);
					Delay(1000);
					if (Actor_Clue_Query(kActorMcCoy, kClueCarRegistration1)) {
						Actor_Says(kActorMcCoy, 3615, 16);
						if (Actor_Query_Friendliness_To_Other(kActorDektora, kActorMcCoy) < 50 
						|| Game_Flag_Query(kFlagDektoraIsReplicant)
						|| Actor_Query_Intelligence(kActorDektora) == 90) {
							Actor_Says(kActorDektora, 2060, 30); //03-2060.AUD	No.
							if (Player_Query_Agenda() == kPlayerAgendaSurly 
							|| Player_Query_Agenda() == kPlayerAgendaErratic) {
								Actor_Says(kActorMcCoy, 6995, 18); //00-6995.AUD	That's not what I heard. You wanna set the record straight?
								Delay(1000); 
								Actor_Modify_Friendliness_To_Other(kActorDektora, kActorMcCoy, -2);
								Actor_Says(kActorDektora, 1980, 30); //03-1980.AUD	All right.
								Actor_Says(kActorDektora, 1480, 30); //03-1480.AUD	Yes
								Delay(500);
								Actor_Says(kActorDektora, 770, 30);
								Actor_Says(kActorMcCoy, 3720, 15);
								Actor_Says_With_Pause(kActorDektora, 780, 2.0f, 30);
								Actor_Says(kActorDektora, 790, 31);
								Actor_Clue_Acquire(kActorMcCoy, kClueCarWasStolen, true, kActorDektora);
								Actor_Says(kActorMcCoy, 3725, 18); //00-3725.AUD	Is that right? Any reason you didn’t tell me that right off?
								Actor_Says(kActorDektora, 800, 30);
								Actor_Says_With_Pause(kActorMcCoy, 3730, 2.0f, 13); //00-3730.AUD	Animal murder is pretty horrible.
								Actor_Says(kActorDektora, 1480, 30); //03-1480.AUD	Yes
							}
						} else {
							Actor_Says(kActorDektora, 770, 30);
							Actor_Says(kActorMcCoy, 3720, 15);
							Actor_Says_With_Pause(kActorDektora, 780, 2.0f, 30);
							Actor_Says(kActorDektora, 790, 31);
							Actor_Clue_Acquire(kActorMcCoy, kClueCarWasStolen, true, kActorDektora);
							if (Player_Query_Agenda() == kPlayerAgendaSurly 
							|| Player_Query_Agenda() == kPlayerAgendaErratic) {
								Actor_Says(kActorMcCoy, 3725, 18); //00-3725.AUD	Is that right? Any reason you didn’t tell me that right off?
								Actor_Says(kActorDektora, 800, 30);
								Actor_Modify_Friendliness_To_Other(kActorDektora, kActorMcCoy, -2);
							}
							Actor_Says_With_Pause(kActorMcCoy, 3730, 2.0f, 13); //00-3730.AUD	Animal murder is pretty horrible.
							if (Actor_Query_Friendliness_To_Other(kActorDektora, kActorMcCoy) < 50) {
								Actor_Says(kActorDektora, 1480, 30); //03-1480.AUD	Yes
							} else {
								Actor_Says_With_Pause(kActorDektora, 810, 1.0f, kAnimationModeSit);
								Actor_Says(kActorDektora, 820, 30);	 //03-0820.AUD	Any murder is horrible. And unfortunate.
								Actor_Says(kActorMcCoy, 3735, 14); //00-3735.AUD	Some are worse than others.
								Actor_Says(kActorDektora, 830, 31);
								Actor_Says(kActorMcCoy, 3740, 19);
							}
						}
					}
					if (Actor_Clue_Query(kActorMcCoy, kCluePurchasedScorpions)) { 
						if (Actor_Clue_Query(kActorMcCoy, kClueScorpionbox)
						|| Game_Flag_Query(kFlagScorpionsDiscovered)) {
							Actor_Face_Actor(kActorDektora, kActorMcCoy, true);
							Actor_Face_Actor(kActorMcCoy, kActorDektora, true);
							Delay(1000);
							Actor_Says(kActorMcCoy, 3620, 19); //00-3620.AUD	You like scorpions, huh?
							Actor_Says(kActorDektora, 840, 30); //03-0840.AUD	Scorpions?
							Actor_Says(kActorMcCoy, 3745, 9); //00-3745.AUD	Insects. Fakes. From Animoid Row. You buy a box of them?
							if (Actor_Query_Friendliness_To_Other(kActorDektora, kActorMcCoy) < 50 
							|| Game_Flag_Query(kFlagDektoraIsReplicant)
							|| Actor_Query_Intelligence(kActorDektora) == 90) {
								Actor_Says(kActorDektora, 2360, 30); //03-2360.AUD	Of course not.
								if (Player_Query_Agenda() == kPlayerAgendaSurly 
								|| Player_Query_Agenda() == kPlayerAgendaErratic) {
									Actor_Says(kActorMcCoy, 8519, 14);//00-8519.AUD	What do you say we dish each other the straight goods.
									Actor_Modify_Friendliness_To_Other(kActorDektora, kActorMcCoy, -2);
									Delay(1000);
									Actor_Says_With_Pause(kActorDektora, 850, 1.0f, 30); // I didn't know what they were called
									Actor_Says(kActorDektora, 860, 31); //03-0860.AUD	Insects make excellent pets. And they were so beautiful I just had to have the whole set.
									Actor_Says(kActorMcCoy, 3750, 11); //00-3750.AUD	Did you know they were poisonous?
									Actor_Says(kActorDektora, 880, 30);
									Actor_Says(kActorMcCoy, 3755, 16); //00-3755.AUD	And that doesn’t scare you?
									Actor_Says(kActorDektora, 890, 31);
									Actor_Says(kActorDektora, 900, 30); // Who would need to add insects to the list?
									Actor_Clue_Acquire(kActorMcCoy, kClueDektoraInterview4, true, kActorDektora);
								}
							} else {
								Actor_Says_With_Pause(kActorDektora, 850, 1.0f, 30); // I didn't know what they were called
								Actor_Says(kActorDektora, 860, 31); //03-0860.AUD	Insects make excellent pets. And they were so beautiful I just had to have the whole set.	
								Actor_Says(kActorMcCoy, 3750, 11); //00-3750.AUD	Did you know they were poisonous?
								Actor_Says(kActorDektora, 880, 30);
								Actor_Says(kActorMcCoy, 3755, 16); //00-3755.AUD	And that doesn’t scare you?
								Actor_Says(kActorDektora, 890, 31);
								Actor_Says(kActorDektora, 900, 30); // Who would need to add insects to the list?
								Actor_Clue_Acquire(kActorMcCoy, kClueDektoraInterview4, true, kActorDektora);
							}
						}
					} else if (Actor_Clue_Query(kActorMcCoy, kClueScorpions)
					&& Actor_Clue_Query(kActorMcCoy, kClueWomanInAnimoidRow)) {
						Actor_Face_Actor(kActorDektora, kActorMcCoy, true);
						Actor_Face_Actor(kActorMcCoy, kActorDektora, true);
						Actor_Says(kActorMcCoy, 3620, 19); //00-3620.AUD	You like scorpions, huh?
						Actor_Says(kActorDektora, 840, 30); //03-0840.AUD	Scorpions?
						Actor_Says(kActorMcCoy, 3745, 9); //00-3745.AUD	Insects. Fakes. From Animoid Row. You buy a box of them?
						if (Actor_Query_Friendliness_To_Other(kActorDektora, kActorMcCoy) < 50 
						|| Game_Flag_Query(kFlagDektoraIsReplicant)
						|| Actor_Query_Intelligence(kActorDektora) == 90) {
							Actor_Says(kActorDektora, 2060, 30); //03-2060.AUD	No.
							if (Player_Query_Agenda() == kPlayerAgendaSurly 
							|| Player_Query_Agenda() == kPlayerAgendaErratic) {
								Actor_Says(kActorMcCoy, 6995, 18); //00-6995.AUD	That's not what I heard. You wanna set the record straight?
								Actor_Modify_Friendliness_To_Other(kActorDektora, kActorMcCoy, -2);
								Delay(2000);
								Actor_Says_With_Pause(kActorDektora, 850, 1.0f, 30); // I didn't know what they were called
								Actor_Says(kActorDektora, 860, 31); //03-0860.AUD	Insects make excellent pets. And they were so beautiful I just had to have the whole set.
								Actor_Says(kActorMcCoy, 3750, 11); //00-3750.AUD	Did you know they were poisonous?
								Actor_Says(kActorDektora, 880, 30);
								Actor_Says(kActorMcCoy, 3755, 16); //00-3755.AUD	And that doesn’t scare you?
								Actor_Says(kActorDektora, 890, 31);
								Actor_Says(kActorDektora, 900, 30); // Who would need to add insects to the list?
								Actor_Clue_Acquire(kActorMcCoy, kClueDektoraInterview4, true, kActorDektora);
							}
						} else {
							Actor_Says_With_Pause(kActorDektora, 850, 1.0f, 30); // I didn't know what they were called
							Actor_Says(kActorDektora, 860, 31); //03-0860.AUD	Insects make excellent pets. And they were so beautiful I just had to have the whole set.
							Actor_Clue_Acquire(kActorMcCoy, kClueDektoraInterview4, true, kActorDektora);
							Actor_Says(kActorMcCoy, 3750, 11); //00-3750.AUD	Did you know they were poisonous?
							Actor_Says(kActorDektora, 880, 30);
							Actor_Says(kActorMcCoy, 3755, 16); //00-3755.AUD	And that doesn’t scare you?
							Actor_Says(kActorDektora, 890, 31);
							Actor_Says(kActorDektora, 900, 30); // Who would need to add insects to the list?
							Actor_Clue_Acquire(kActorMcCoy, kClueDektoraInterview4, true, kActorDektora);
						}
					}
				}
			}
		} else {
			if (!_vm->_cutContent) {
				Actor_Modify_Friendliness_To_Other(kActorDektora, kActorMcCoy, -2);
			}
			if (_vm->_cutContent) {
				Actor_Face_Actor(kActorDektora, kActorMcCoy, true);
				Actor_Face_Actor(kActorMcCoy, kActorDektora, true);
			}
			if (_vm->_cutContent) {
				if (Actor_Query_Friendliness_To_Other(kActorDektora, kActorMcCoy) < 50 
				|| Game_Flag_Query(kFlagDektoraIsReplicant)) {
					if (Game_Flag_Query(kFlagHanoiIsReplicant)) {
						Actor_Says(kActorDektora, 530, 31);
						Actor_Modify_Friendliness_To_Other(kActorDektora, kActorMcCoy, -2);
					}
				}
			} else {
				Actor_Says(kActorDektora, 530, 31);
			}
			if (!_vm->_cutContent) {
				Actor_Face_Object(kActorDektora, "VANITY", true);
			}
		}
		Actor_Set_Goal_Number(kActorHanoi, kGoalHanoiDefault);
	}
	//return false;
}

void SceneScriptNR07::PlayerWalkedOut() {

}

void SceneScriptNR07::DialogueQueueFlushed(int a1) {
}

void SceneScriptNR07::dektoraRunAway() {
	Actor_Set_Goal_Number(kActorHanoi, kGoalHanoiResetTimer);
	Player_Loses_Control();
	Actor_Set_At_XYZ(kActorDektora, -136.0f, -73.0f, -18.0f, 300);
	Actor_Change_Animation_Mode(kActorDektora, 71);
	Actor_Change_Animation_Mode(kActorMcCoy, 21);
	Loop_Actor_Walk_To_XYZ(kActorDektora, -102.0f, -73.5f, -233.0f, 0, false, true, false);

	if (Game_Flag_Query(kFlagDektoraIsReplicant)) {
		Actor_Set_Goal_Number(kActorDektora, kGoalDektoraNR08ReadyToRun);
	} else {
		Actor_Set_Goal_Number(kActorDektora, kGoalDektoraNR07RanAway);
		Game_Flag_Set(kFlagDektoraRanAway);
		Actor_Put_In_Set(kActorDektora, kSetFreeSlotA);
		Actor_Set_At_Waypoint(kActorDektora, 33, 0);
	}
	Player_Gains_Control();
}

void SceneScriptNR07::callHolloway() {
	Scene_Exits_Disable();
	Actor_Set_Goal_Number(kActorHanoi, kGoalHanoiResetTimer);
	if (_vm->_cutContent) {
		Actor_Face_Actor(kActorDektora, kActorMcCoy, true);
		Actor_Face_Actor(kActorMcCoy, kActorDektora, true);
	}
	Actor_Says_With_Pause(kActorDektora, 930, 1.0f, 30);
	if (_vm->_cutContent) {
		if (!Actor_Clue_Query(kActorDektora, kClueMcCoyHelpedDektora)) {
			Actor_Says_With_Pause(kActorDektora, 910, 1.0f, 30);
		}
	} else {
		Actor_Says_With_Pause(kActorDektora, 910, 1.0f, 30);
	}
	Actor_Face_Object(kActorDektora, "VANITY", true);
	Actor_Says(kActorDektora, 940, 31); //03-0940.AUD	Give me the police!
	if (_vm->_cutContent) {
		if (Game_Flag_Query(kFlagDektoraIsReplicant)
		&& Actor_Clue_Query(kActorMcCoy, kClueVKDektoraReplicant)) {
			Actor_Says(kActorMcCoy, 1870, 14); //00-1870.AUD	I’m a cop.
		} else {
			Actor_Says(kActorMcCoy, 3770, 19); //00-3770.AUD	(sigh) You’re doing the right thing.
		}
	} else {
		Actor_Says(kActorMcCoy, 3770, 19);
	}
	Async_Actor_Walk_To_XYZ(kActorMcCoy, -193.0f, -73.5f, -13.0f, 0, false);
	Actor_Says(kActorDektora, 950, 31);
	if (_vm->_cutContent) {
		if (Game_Flag_Query(kFlagDektoraIsReplicant)
		&& Actor_Clue_Query(kActorMcCoy, kClueVKDektoraReplicant)) {
			Actor_Face_Actor(kActorMcCoy, kActorDektora, true);
			Actor_Says(kActorMcCoy, 7930, 14); //00-7930.AUD	Stay right where you are.
		} 
	}
	Actor_Face_Actor(kActorDektora, kActorMcCoy, true);
	Actor_Face_Actor(kActorMcCoy, kActorDektora, true);
	if (_vm->_cutContent) {
		if (!Actor_Clue_Query(kActorDektora, kClueMcCoyHelpedDektora)) {
			Actor_Change_Animation_Mode(kActorDektora, kAnimationModeCombatIdle);
			Actor_Says(kActorMcCoy, 3760, 19);
		}
	} else {
		Actor_Change_Animation_Mode(kActorDektora, kAnimationModeCombatIdle);
		Actor_Says(kActorMcCoy, 3760, 19);
	}
	Actor_Says(kActorDektora, 960, kAnimationModeSit); //03-0960.AUD	Now we wait.
	if (_vm->_cutContent) {
		if (Actor_Clue_Query(kActorDektora, kClueMcCoyHelpedDektora)) {
			Delay(3000);
		} else {
			Actor_Says(kActorMcCoy, 3765, kAnimationModeTalk); // Let me show you my ID.
			Actor_Says(kActorDektora, 920, kAnimationModeSit); //03-0920.AUD	If your hand moves, I’ll shoot.
			Actor_Says_With_Pause(kActorMcCoy, 3780, 0.0f, kAnimationModeIdle); //00-3780.AUD	Okay, uh--
			Actor_Says(kActorDektora, 970, kAnimationModeSit);
			Actor_Voice_Over(1710, kActorVoiceOver);
			Actor_Voice_Over(1720, kActorVoiceOver); //99-1720.AUD	Any other mark, I’d had been a dead man.
			if (!Actor_Clue_Query(kActorMcCoy, kClueVKDektoraReplicant)) {
				Actor_Voice_Over(1730, kActorVoiceOver); //99-1730.AUD	But if she was a Replicant, she must not have known it if she was willing to call the police.
			}
		}
	} else {
		Actor_Says(kActorDektora, 920, kAnimationModeSit);
#if BLADERUNNER_ORIGINAL_BUGS
			Actor_Says(kActorMcCoy, 3780, kAnimationModeIdle);
#else
			// McCoy is interrupted here
			Actor_Says_With_Pause(kActorMcCoy, 3780, 0.0f, kAnimationModeIdle); //00-3780.AUD	Okay, uh--
#endif // BLADERUNNER_ORIGINAL_BUGS
		Actor_Voice_Over(1710, kActorVoiceOver);
		Actor_Voice_Over(1720, kActorVoiceOver); //99-1720.AUD	Any other mark, I’d had been a dead man.
		Actor_Voice_Over(1730, kActorVoiceOver); //99-1730.AUD	But if she was a Replicant, she must not have known it if she was willing to call the police.
	}
	Actor_Set_Goal_Number(kActorHolloway, kGoalHollowayGoToNR07);
}

void SceneScriptNR07::clickedOnVase() {
	Loop_Actor_Walk_To_XYZ(kActorMcCoy, -109.0f, -73.0f, -89.0f, 0, false, false, false);
	Actor_Face_Object(kActorMcCoy, "VASE", true);
	if (Actor_Query_Is_In_Current_Set(kActorDektora)) {
		if (!Actor_Clue_Query(kActorMcCoy, kClueDektoraInterview3)) {
			// Made it so you now receive the Dektora interview 3 clue after you talk to Dektora about the flowers.
			// Originally you could click on the vase after McCoy reveals that he is a cop and still receive the clue despite 
			// him not having the conversation with Dektora.
			if (!_vm->_cutContent) {
				Actor_Clue_Acquire(kActorMcCoy, kClueDektoraInterview3, true, -1);
				int friendliness = Actor_Query_Friendliness_To_Other(kActorDektora, kActorMcCoy);
				if (friendliness > 50) {
					Actor_Modify_Friendliness_To_Other(kActorDektora, kActorMcCoy, 2);
				} else {
					Actor_Modify_Friendliness_To_Other(kActorDektora, kActorMcCoy, -2);
				}
			}
#if BLADERUNNER_ORIGINAL_BUGS
			Actor_Says(kActorMcCoy, 3600, 19);  // The flowers are beautiful. (McCoy fake fan voice)
			Actor_Says(kActorDektora, 550, 30); // And a extremely rare (...)
			Actor_Says(kActorMcCoy, 3605, 19);  // That's a pretty card. (McCoy fake fan voice)
			Actor_Says(kActorDektora, 560, 31); // Please don't touch that. It's private.
			Actor_Says(kActorMcCoy, 3610, 19);  // Sorry (McCoy fake fan voice)
#else
			if (!Game_Flag_Query(kFlagNR07McCoyIsCop)) {
				if (_vm->_cutContent) {
					Actor_Face_Actor(kActorDektora, kActorMcCoy, true);
				}
				Actor_Says(kActorMcCoy, 3600, 19);  // The flowers are beautiful. (McCoy fake fan voice)
				if (_vm->_cutContent) {					
					if (Actor_Query_Friendliness_To_Other(kActorDektora, kActorMcCoy) < 50 
					|| Game_Flag_Query(kFlagDektoraIsReplicant)
					|| Actor_Query_Intelligence(kActorDektora) == 90) {
						Actor_Says(kActorDektora, 1480, 30); //03-1480.AUD	Yes.
					} else {
						Actor_Says(kActorDektora, 550, 30); // And a extremely rare (...)
						Actor_Says(kActorMcCoy, 3605, 19);  // That's a pretty card. (McCoy fake fan voice)
						Actor_Says(kActorDektora, 1480, 30); //03-1480.AUD	Yes.
						// The clue will now be obtained here.
						Actor_Clue_Acquire(kActorMcCoy, kClueDektoraInterview3, true, kActorDektora);
					}
				} else {
					Actor_Says(kActorDektora, 550, 30); // And a extremely rare (...)
					Actor_Says(kActorMcCoy, 3605, 19);  // That's a pretty card. (McCoy fake fan voice)
					Actor_Says(kActorDektora, 560, 31); // Please don't touch that. It's private.
					Actor_Says(kActorMcCoy, 3610, 19);  // Sorry (McCoy fake fan voice)
				}
			} else {
				if (_vm->_cutContent) {
					Actor_Change_Animation_Mode(kActorMcCoy, 23);
					Delay(800);
					Actor_Says(kActorDektora, 560, 31); // Please don't touch that. It's private.
				} else {
					Actor_Says(kActorDektora, 560, 31); // Please don't touch that. It's private.
				}
				if (_vm->_cutContent) {
					if (!Game_Flag_Query(kFlagNR07McCoyIsCop)) {
						Actor_Says(kActorMcCoy, 3610, 19);  // Sorry (McCoy fake fan voice)
					} else {
						Actor_Says(kActorMcCoy, 8525, 19);  // Hmph.
					}
				} else {
					Actor_Says(kActorMcCoy, 8525, 19);  // Hmph.
				}
				if (!_vm->_cutContent) {
					Actor_Modify_Friendliness_To_Other(kActorDektora, kActorMcCoy, -2);
				}
			}
#endif // BLADERUNNER_ORIGINAL_BUGS
		} else {
			Actor_Says(kActorDektora, 560, 31); // Please don't touch that. It's private.
			if (_vm->_cutContent) {
				if (!Game_Flag_Query(kFlagNR07McCoyIsCop)) {
					Actor_Says(kActorMcCoy, 3610, 19);  // Sorry (McCoy fake fan voice)
				} else {
					Actor_Says(kActorMcCoy, 8525, 19);  // Hmph.
				}
			}
		}
	} else if (!Actor_Clue_Query(kActorMcCoy, kClueDektorasCard)) {
		if (_vm->_cutContent) {
			Actor_Clue_Acquire(kActorMcCoy, kClueDektorasCard, true, kActorDektora);
		} else {
			Actor_Clue_Acquire(kActorMcCoy, kClueDektorasCard, true, -1);
		}
		Loop_Actor_Walk_To_Scene_Object(kActorMcCoy, "VASE", 100, true, false);
		if (_vm->_cutContent) {
			if (!Game_Flag_Query(kFlagDektoraIsReplicant)) {
				Actor_Change_Animation_Mode(kActorMcCoy, 23);
				Delay(800);
				Item_Pickup_Spin_Effect(kModelAnimationDektorasCard, 526, 268);
				Delay(800);
				Actor_Says(kActorMcCoy, 8835, 13);	//00-8835.AUD	A card.
				Actor_Voice_Over(1690, kActorVoiceOver);
				if (Player_Query_Agenda() == kPlayerAgendaSurly 
				|| Player_Query_Agenda() == kPlayerAgendaErratic) {
					Actor_Voice_Over(1700, kActorVoiceOver); //99-1700.AUD	Poetry. I was running into a lot of that crap lately.
				} else {
					Actor_Says(kActorMcCoy, 2340, kAnimationModeTalk); // 00-2340.AUD	I never did like poetry.
				}
			} else {
				Actor_Voice_Over(3700, kActorVoiceOver);
			}
		} else {
			Item_Pickup_Spin_Effect(kModelAnimationDektorasCard, 526, 268);
			Actor_Voice_Over(1690, kActorVoiceOver);
			Actor_Voice_Over(1700, kActorVoiceOver); //99-1700.AUD	Poetry. I was running into a lot of that crap lately.
		}
	} else {
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagDektoraIsReplicant)) {
				Actor_Voice_Over(3700, kActorVoiceOver);
			} else {
				Actor_Says(kActorMcCoy, 8585, 14);
			}
		} else {
			Actor_Says(kActorMcCoy, 8585, 14);
		}
	}
}

void SceneScriptNR07::talkAboutBelt1() {
	if (_vm->_cutContent) {
		Actor_Face_Actor(kActorDektora, kActorMcCoy, true);
		Actor_Face_Actor(kActorMcCoy, kActorDektora, true);
	}
	if (_vm->_cutContent) {
		Actor_Clue_Acquire(kActorMcCoy, kClueDektoraInterview2, true, kActorDektora);
	} else {
		Actor_Clue_Acquire(kActorMcCoy, kClueDektoraInterview2, true, -1);
	}
	Actor_Says(kActorMcCoy, 3625, 19);
	if (_vm->_cutContent) {
		if (Actor_Query_Friendliness_To_Other(kActorDektora, kActorMcCoy) < 50 
		|| Game_Flag_Query(kFlagDektoraIsReplicant)
		|| Actor_Query_Intelligence(kActorDektora) == 90) {
			Actor_Says(kActorDektora, 1480, 30); //03-1480.AUD	Yes
			Delay(2000);
		} else {
			Actor_Says(kActorDektora, 570, 30);
			Actor_Says_With_Pause(kActorDektora, 580, 1.0f, 31);
			Actor_Says(kActorMcCoy, 3630, 13);
			Actor_Says_With_Pause(kActorDektora, 590, 1.0f, 30);
			Actor_Says(kActorDektora, 600, 30);
			Actor_Says_With_Pause(kActorMcCoy, 3635, 1.5f, 18); // Insects, hm.
		}
	} else {
		Actor_Says(kActorDektora, 570, 30);
		Actor_Says_With_Pause(kActorDektora, 580, 1.0f, 31);
		Actor_Says(kActorMcCoy, 3630, 13);
		Actor_Says_With_Pause(kActorDektora, 590, 1.0f, 30);
		Actor_Says(kActorDektora, 600, 30);
	}
	if (_vm->_cutContent) {
		Actor_Says(kActorMcCoy, 3640, 14);  // Tell you the truth, I'm from the LPD. (...)
	} else {
		Actor_Start_Speech_Sample(kActorMcCoy, 3640);  // Tell you the truth, I'm from the LPD. (...)
	}
	if (!_vm->_cutContent) {
		Loop_Actor_Walk_To_XYZ(kActorMcCoy, -109.0f, -73.0f, -89.0f, 0, false, false, false);
		Actor_Face_Actor(kActorMcCoy, kActorDektora, true);
		Actor_Face_Actor(kActorDektora, kActorMcCoy, true);
	}
	if (_vm->_cutContent) {
		Actor_Modify_Friendliness_To_Other(kActorDektora, kActorMcCoy, -2);
	}
	Game_Flag_Set(kFlagNR07McCoyIsCop);
	// Made it so you don't receive the dragonflybelt after talking to Dektora about it.
	if (!_vm->_cutContent) {
		Actor_Clue_Acquire(kActorMcCoy, kClueDragonflyBelt, true, kActorDektora);

		int friendliness = Actor_Query_Friendliness_To_Other(kActorDektora, kActorMcCoy);
		if (!Game_Flag_Query(kFlagDektoraIsReplicant)
		&&  friendliness < 40
		) {
			dektoraRunAway();
			return;
		}

		if (friendliness < 36) {
			callHolloway();
			return;
		}
	}

	talkAboutBelt2();
}

void SceneScriptNR07::talkAboutBelt2() {
	if (Actor_Clue_Query(kActorDektora, kClueMcCoysDescription)
	 && Actor_Clue_Query(kActorDektora, kClueMcCoyIsABladeRunner)
	) {
		if (!_vm->_cutContent) {
			Actor_Modify_Friendliness_To_Other(kActorDektora, kActorMcCoy, -1);
		}
	}

#if BLADERUNNER_ORIGINAL_BUGS
	Actor_Says(kActorDektora, 610, 31);
#else
	// Dektora is interrupted here
	if (_vm->_cutContent) {
		if (!Game_Flag_Query(kFlagEarlyQIsReplicant)) {
			Actor_Says_With_Pause(kActorDektora, 610, 0.0f, 31); //03-0610.AUD	Is this about Early Q? Because I could tell you--
		} else {
			Delay(1000);
			Actor_Says(kActorDektora, 1980, kAnimationModeSit); //03-1980.AUD	All right.
			Delay(1000);
		}
	} else {
		Actor_Says_With_Pause(kActorDektora, 610, 0.0f, 31); //03-0610.AUD	Is this about Early Q? Because I could tell you--
	}
#endif // BLADERUNNER_ORIGINAL_BUGS
	if (_vm->_cutContent) {
		if (!Actor_Clue_Query(kActorMcCoy, kClueDragonflyCollection)) {
			Actor_Says(kActorMcCoy, 3645, 12);
			if (Actor_Query_Friendliness_To_Other(kActorDektora, kActorMcCoy) < 50 
			|| Game_Flag_Query(kFlagDektoraIsReplicant)
			|| Actor_Query_Intelligence(kActorDektora) == 90) {
				Actor_Says(kActorDektora, 620, 30); //03-0620.AUD	I’m sure I don’t know what you mean.
				if (Player_Query_Agenda() == kPlayerAgendaSurly 
				|| Player_Query_Agenda() == kPlayerAgendaErratic) {
					Actor_Says(kActorMcCoy, 2485, 19); //00-2485.AUD	I’ve a hard time believing that.
					Actor_Modify_Friendliness_To_Other(kActorDektora, kActorMcCoy, -2);
					Delay(1000);
				} else {
					Actor_Says(kActorMcCoy, 8225, 14); //00-8225.AUD	Just relax.
					Delay(1000);
					Actor_Modify_Friendliness_To_Other(kActorDektora, kActorMcCoy, 2);
				}
			} else {
				Actor_Says(kActorDektora, 1480, 30); //03-1480.AUD	Yes
			}
		}
		Actor_Says(kActorMcCoy, 7395, 14); //00-7395.AUD	What's your name?
		Actor_Says(kActorDektora, 1470, 30); //03-1470.AUD	Dektora.
		if (Actor_Clue_Query(kActorMcCoy, kClueCarRegistration1)) {
			Actor_Says(kActorMcCoy, 3615, 16);
			if (Actor_Query_Friendliness_To_Other(kActorDektora, kActorMcCoy) < 50 
			|| Game_Flag_Query(kFlagDektoraIsReplicant)
			|| Actor_Query_Intelligence(kActorDektora) == 90) {
				Actor_Says(kActorDektora, 2060, 30); //03-2060.AUD	No.
				if (Player_Query_Agenda() == kPlayerAgendaSurly 
				|| Player_Query_Agenda() == kPlayerAgendaErratic) {
					Actor_Says(kActorMcCoy, 6995, 18); //00-6995.AUD	That's not what I heard. You wanna set the record straight?
					Delay(1000); 
					Actor_Modify_Friendliness_To_Other(kActorDektora, kActorMcCoy, -2);
					Actor_Says(kActorDektora, 1980, 30); //03-1980.AUD	All right.
					Actor_Says(kActorDektora, 1480, 30); //03-1480.AUD	Yes
					Delay(500);
					Actor_Says(kActorDektora, 770, 30);
					Actor_Says(kActorMcCoy, 3720, 15);
					Actor_Says_With_Pause(kActorDektora, 780, 2.0f, 30);
					Actor_Says(kActorDektora, 790, 31);
					Actor_Clue_Acquire(kActorMcCoy, kClueCarWasStolen, true, kActorDektora);
					Actor_Says(kActorMcCoy, 3725, 18); //00-3725.AUD	Is that right? Any reason you didn’t tell me that right off?
					Actor_Says(kActorDektora, 800, 30);
					Actor_Says_With_Pause(kActorMcCoy, 3730, 2.0f, 13); //00-3730.AUD	Animal murder is pretty horrible.
					Actor_Says(kActorDektora, 1480, 30); //03-1480.AUD	Yes
				}
			} else {
				Actor_Says(kActorDektora, 770, 30);
				Actor_Says(kActorMcCoy, 3720, 15);
				Actor_Says_With_Pause(kActorDektora, 780, 2.0f, 30);
				Actor_Says(kActorDektora, 790, 31);
				Actor_Clue_Acquire(kActorMcCoy, kClueCarWasStolen, true, kActorDektora);
				if (Player_Query_Agenda() == kPlayerAgendaSurly 
				|| Player_Query_Agenda() == kPlayerAgendaErratic) {
					Actor_Says(kActorMcCoy, 3725, 18); //00-3725.AUD	Is that right? Any reason you didn’t tell me that right off?
					Actor_Says(kActorDektora, 800, 30);
					Actor_Modify_Friendliness_To_Other(kActorDektora, kActorMcCoy, -2);
				}
				Actor_Says_With_Pause(kActorMcCoy, 3730, 2.0f, 13); //00-3730.AUD	Animal murder is pretty horrible.
				if (Actor_Query_Friendliness_To_Other(kActorDektora, kActorMcCoy) < 50) {
					Actor_Says(kActorDektora, 1480, 30); //03-1480.AUD	Yes
				} else {
					Actor_Says_With_Pause(kActorDektora, 810, 1.0f, kAnimationModeSit);
					Actor_Says(kActorDektora, 820, 30);	 //03-0820.AUD	Any murder is horrible. And unfortunate.
					Actor_Says(kActorMcCoy, 3735, 14); //00-3735.AUD	Some are worse than others.
					Actor_Says(kActorDektora, 830, 31);
					Actor_Says(kActorMcCoy, 3740, 19);
				}
			}
		}
		if (Actor_Clue_Query(kActorMcCoy, kCluePurchasedScorpions)) { 
			if (Actor_Clue_Query(kActorMcCoy, kClueScorpionbox)
			|| Game_Flag_Query(kFlagScorpionsDiscovered)) {
				Actor_Face_Actor(kActorDektora, kActorMcCoy, true);
				Actor_Face_Actor(kActorMcCoy, kActorDektora, true);
				Delay(1000);
				Actor_Says(kActorMcCoy, 3620, 19); //00-3620.AUD	You like scorpions, huh?
				Actor_Says(kActorDektora, 840, 30); //03-0840.AUD	Scorpions?
				Actor_Says(kActorMcCoy, 3745, 9); //00-3745.AUD	Insects. Fakes. From Animoid Row. You buy a box of them?
				if (Actor_Query_Friendliness_To_Other(kActorDektora, kActorMcCoy) < 50 
				|| Game_Flag_Query(kFlagDektoraIsReplicant)
				|| Actor_Query_Intelligence(kActorDektora) == 90) {
					Actor_Says(kActorDektora, 2360, 30); //03-2360.AUD	Of course not.
					if (Player_Query_Agenda() == kPlayerAgendaSurly 
					|| Player_Query_Agenda() == kPlayerAgendaErratic) {
						Actor_Says(kActorMcCoy, 8519, 14);//00-8519.AUD	What do you say we dish each other the straight goods.
						Actor_Modify_Friendliness_To_Other(kActorDektora, kActorMcCoy, -2);
						Delay(1000);
						Actor_Says_With_Pause(kActorDektora, 850, 1.0f, 30); // I didn't know what they were called
						Actor_Says(kActorDektora, 860, 31); //03-0860.AUD	Insects make excellent pets. And they were so beautiful I just had to have the whole set.
						Actor_Says(kActorMcCoy, 3750, 11); //00-3750.AUD	Did you know they were poisonous?
						Actor_Says(kActorDektora, 880, 30);
						Actor_Says(kActorMcCoy, 3755, 16); //00-3755.AUD	And that doesn’t scare you?
						Actor_Says(kActorDektora, 890, 31);
						Actor_Says(kActorDektora, 900, 30); // Who would need to add insects to the list?
						Actor_Clue_Acquire(kActorMcCoy, kClueDektoraInterview4, true, kActorDektora);
					}
				} else {
					Actor_Says_With_Pause(kActorDektora, 850, 1.0f, 30); // I didn't know what they were called
					Actor_Says(kActorDektora, 860, 31); //03-0860.AUD	Insects make excellent pets. And they were so beautiful I just had to have the whole set.		
					Actor_Says(kActorMcCoy, 3750, 11); //00-3750.AUD	Did you know they were poisonous?
					Actor_Says(kActorDektora, 880, 30);
					Actor_Says(kActorMcCoy, 3755, 16); //00-3755.AUD	And that doesn’t scare you?
					Actor_Says(kActorDektora, 890, 31);
					Actor_Says(kActorDektora, 900, 30); // Who would need to add insects to the list?
					Actor_Clue_Acquire(kActorMcCoy, kClueDektoraInterview4, true, kActorDektora);
				}
			}
	 	} else if (Actor_Clue_Query(kActorMcCoy, kClueScorpions)
		&& Actor_Clue_Query(kActorMcCoy, kClueWomanInAnimoidRow)) {
			Actor_Face_Actor(kActorDektora, kActorMcCoy, true);
			Actor_Face_Actor(kActorMcCoy, kActorDektora, true);
			Actor_Says(kActorMcCoy, 3620, 19); //00-3620.AUD	You like scorpions, huh?
			Actor_Says(kActorDektora, 840, 30); //03-0840.AUD	Scorpions?
			Actor_Says(kActorMcCoy, 3745, 9); //00-3745.AUD	Insects. Fakes. From Animoid Row. You buy a box of them?
			if (Actor_Query_Friendliness_To_Other(kActorDektora, kActorMcCoy) < 50 
			|| Game_Flag_Query(kFlagDektoraIsReplicant)
			|| Actor_Query_Intelligence(kActorDektora) == 90) {
				Actor_Says(kActorDektora, 2060, 30); //03-2060.AUD	No.
				if (Player_Query_Agenda() == kPlayerAgendaSurly 
				|| Player_Query_Agenda() == kPlayerAgendaErratic) {
					Actor_Says(kActorMcCoy, 6995, 18); //00-6995.AUD	That's not what I heard. You wanna set the record straight?
					Actor_Modify_Friendliness_To_Other(kActorDektora, kActorMcCoy, -2);
					Delay(2000);
					Actor_Says_With_Pause(kActorDektora, 850, 1.0f, 30); // I didn't know what they were called
					Actor_Says(kActorDektora, 860, 31); //03-0860.AUD	Insects make excellent pets. And they were so beautiful I just had to have the whole set.
					Actor_Says(kActorMcCoy, 3750, 11); //00-3750.AUD	Did you know they were poisonous?
					Actor_Says(kActorDektora, 880, 30);
					Actor_Says(kActorMcCoy, 3755, 16); //00-3755.AUD	And that doesn’t scare you?
					Actor_Says(kActorDektora, 890, 31);
					Actor_Says(kActorDektora, 900, 30); // Who would need to add insects to the list?
					Actor_Clue_Acquire(kActorMcCoy, kClueDektoraInterview4, true, kActorDektora);
				}
			} else {
				Actor_Says_With_Pause(kActorDektora, 850, 1.0f, 30); // I didn't know what they were called
				Actor_Says(kActorDektora, 860, 31); //03-0860.AUD	Insects make excellent pets. And they were so beautiful I just had to have the whole set.
				Actor_Says(kActorMcCoy, 3750, 11); //00-3750.AUD	Did you know they were poisonous?
				Actor_Says(kActorDektora, 880, 30);
				Actor_Says(kActorMcCoy, 3755, 16); //00-3755.AUD	And that doesn’t scare you?
				Actor_Says(kActorDektora, 890, 31);
				Actor_Says(kActorDektora, 900, 30); // Who would need to add insects to the list?
				Actor_Clue_Acquire(kActorMcCoy, kClueDektoraInterview4, true, kActorDektora);
			}
		}
	} else {
		Actor_Says(kActorMcCoy, 3645, 12);
		Actor_Says(kActorDektora, 620, 30); //03-0620.AUD	I’m sure I don’t know what you mean.
	}
	if (!_vm->_cutContent) {
		int friendliness = Actor_Query_Friendliness_To_Other(kActorDektora, kActorMcCoy);
		if (!Game_Flag_Query(kFlagDektoraIsReplicant)
		&&  friendliness < 40
		) {
			dektoraRunAway();
			return;
		}

		if (friendliness < 36) {
			callHolloway();
			return;
		}
		Actor_Face_Object(kActorDektora, "VANITY", true);
	}
}

void SceneScriptNR07::talkAboutVoightKampff() {
	if (_vm->_cutContent) {
		Actor_Clue_Acquire(kActorMcCoy, kClueDektoraInterview1, true, kActorDektora);
	} else {
		Actor_Clue_Acquire(kActorMcCoy, kClueDektoraInterview1, true, -1);
	}
	if (_vm->_cutContent) {
		Loop_Actor_Walk_To_XYZ(kActorMcCoy, -109.0f, -73.0f, -89.0f, 0, false, false, false);
		Actor_Face_Actor(kActorDektora, kActorMcCoy, true);
		Actor_Face_Actor(kActorMcCoy, kActorDektora, true);
	}
	Actor_Start_Speech_Sample(kActorMcCoy, 3660);
	Loop_Actor_Walk_To_XYZ(kActorMcCoy, -109.0f, -73.0f, -89.0f, 0, false, false, false);
	Actor_Face_Actor(kActorMcCoy, kActorDektora, true);
	Actor_Says(kActorDektora, 650, 30); //03-0650.AUD	Do you think I’m a Replicant? Is that what this is about?
	// Made it so if Early Q is a replicant Dektora will not go against him since he is now helping out the replicants.
	if (_vm->_cutContent) {
		if (!Game_Flag_Query(kFlagEarlyQIsReplicant)) {
			Actor_Says(kActorDektora, 660, 31); //03-0660.AUD	If it’s Early Q, I’ll help you any way you want.
			Actor_Says(kActorMcCoy, 3665, 18);
		}
	} else {
		Actor_Says(kActorDektora, 660, 31); //03-0660.AUD	If it’s Early Q, I’ll help you any way you want.
		Actor_Says(kActorMcCoy, 3665, 18);
	}
	if (_vm->_cutContent) {
		if (Actor_Query_Goal_Number(kActorLucy) < kGoalLucyGone) {
			if (Actor_Query_Intelligence(kActorDektora) == 90) {
				Actor_Face_Actor(kActorDektora, kActorMcCoy, true);
				Actor_Says(kActorDektora, 670, 31); //03-0670.AUD	This is insane. I have a family, a daughter for heaven’s sake.	
			}
		}
	} else {
		Actor_Face_Actor(kActorDektora, kActorMcCoy, true);
		Actor_Says(kActorDektora, 670, 31); //03-0670.AUD	This is insane. I have a family, a daughter for heaven’s sake.
	}
	// If Early Q is a rep Dektora won't say how she will testify against him which leads to her questioning if McCoy is a replicant. 
	// Instead McCoy will just say the test won't take too long and the rest of the dialogue will be skipped.
	if (_vm->_cutContent) {
		if (Game_Flag_Query(kFlagEarlyQIsReplicant)) {
			Delay(1000);
			Actor_Says(kActorMcCoy, 8325, 13); //00-8325.AUD	It's just a test.
			Actor_Says(kActorMcCoy, 400, 14); //00-0400.AUD	It won't take too long.
		} else {
			Actor_Says(kActorDektora, 680, 30); //03-0680.AUD	Look, I’m willing to testify against Early Q.
			if (Actor_Query_Intelligence(kActorDektora) == 90) {				
				Actor_Says(kActorDektora, 690, 31); //03-0690.AUD	A Replicant wouldn’t do that, would it?
				if (!Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
					Actor_Says(kActorMcCoy, 3670, 17);
					Actor_Says(kActorDektora, 700, 30); //03-0700.AUD	Then, you must be a Replicant.
					Actor_Says(kActorMcCoy, 3675, 19); 
					Actor_Says(kActorDektora, 710, 30); //03-0710.AUD	How do you know you’re not a Replicant? Did you ever take that test yourself?
					Actor_Says(kActorMcCoy, 3680, 19); 
					Actor_Says(kActorDektora, 720, 30); //03-0720.AUD	Don’t Replicants go around with false memories?
					Actor_Says(kActorDektora, 730, 30); //03-0730.AUD	Maybe somewhere along the line you killed a human, took his place and your superiors don’t even know about it.
					Actor_Says(kActorMcCoy, 3685, 13); //00-3685.AUD	Interesting idea. But I’m still gonna give you the test.
				} else {
					Delay(1000);
					Actor_Says(kActorMcCoy, 8325, 13); //00-8325.AUD	It's just a test.
					Actor_Says(kActorMcCoy, 400, 14); //00-0400.AUD	It won't take too long.
				}
			} else {
				Delay(1000);
				Actor_Says(kActorMcCoy, 8325, 13); //00-8325.AUD	It's just a test.
				Actor_Says(kActorMcCoy, 400, 14); //00-0400.AUD	It won't take too long.
			}
		}
		Game_Flag_Reset(kFlagMcCoyIsHelpingReplicants);
		Actor_Modify_Friendliness_To_Other(kActorDektora, kActorMcCoy, -2);
		Voight_Kampff_Activate(kActorDektora, 40);
	} else {
		Actor_Says(kActorDektora, 680, 30); //03-0680.AUD	Look, I’m willing to testify against Early Q.
		Actor_Says(kActorDektora, 690, 31); //03-0690.AUD	A Replicant wouldn’t do that, would it?
		Actor_Says(kActorMcCoy, 3670, 17); 
		Actor_Says(kActorDektora, 700, 30); //03-0700.AUD	Then, you must be a Replicant.
		Actor_Says(kActorMcCoy, 3675, 19); 
		Actor_Says(kActorDektora, 710, 30); 
		Actor_Says(kActorMcCoy, 3680, 19); 
		Actor_Says(kActorDektora, 720, 30); 
		Actor_Says(kActorDektora, 730, 30); 
		Actor_Says(kActorMcCoy, 3685, 13); 
		Voight_Kampff_Activate(kActorDektora, 40);
	}

	if (Game_Flag_Query(kFlagDektoraIsReplicant)) {
		callHolloway();
	} else {
		// Made it so if Dektora is human and Hanoi is a replicant Hanoi will enter the room and attack McCoy.
		// The scene will be slightly different depending on if you warned Dektora about Crystal or VKed with her being more sympathetic if you warned her
		// or not caring at all if you VKed her. 
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagHanoiIsReplicant)
			&& !Game_Flag_Query(kFlagHanoiDead)) {
				Player_Loses_Control();
				Actor_Put_In_Set(kActorHanoi, kSetNR07);
				Actor_Set_At_XYZ(kActorHanoi, -102.0f, -73.5f, -233.0f, 0);
				Actor_Face_Actor(kActorHanoi, kActorDektora, true);
				Actor_Face_Actor(kActorDektora, kActorHanoi, true);
				Async_Actor_Walk_To_Waypoint(kActorMcCoy, 338, 0, false);
				Actor_Says(kActorHanoi, 130, 3);
				Actor_Face_Actor(kActorMcCoy, kActorHanoi, true);
				Actor_Says(kActorDektora, 540, 30);	
				Actor_Says(kActorHanoi, 140, kAnimationModeTalk);
				AI_Movement_Track_Flush(kActorHanoi);
				AI_Movement_Track_Append(kActorHanoi, 337, 0);
				AI_Movement_Track_Repeat(kActorHanoi); 
				Delay (6000);
				Actor_Face_Actor(kActorHanoi, kActorMcCoy, true);
				Actor_Face_Actor(kActorMcCoy, kActorHanoi, true);
				Actor_Change_Animation_Mode(kActorHanoi, 23);
				Actor_Set_Invisible(kActorMcCoy, true);
				Actor_Face_Actor(kActorDektora, kActorHanoi, true);
				Actor_Says(kActorMcCoy, 3595, kAnimationModeTalk);
				dektoraRunAway();
				Actor_Set_Goal_Number(kActorDektora, kGoalDektoraNR08ReadyToRun);
				Actor_Says(kActorMcCoy, 3785, kAnimationModeTalk); //00-3785.AUD	Let go, you lug. I gotta-- (grunts)
				Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
				Ambient_Sounds_Remove_All_Looping_Sounds(1u);
				Actor_Set_Goal_Number(kActorHanoi, kGoalHanoiThrowOutMcCoy);
			} else {
				dektoraRunAway();
				Actor_Set_Goal_Number(kActorDektora, kGoalDektoraNR08ReadyToRun);
			}
		} else {
			dektoraRunAway();
		}
	}
}

void SceneScriptNR07::talkAboutSteele() {
	Loop_Actor_Walk_To_XYZ(kActorMcCoy, -109.0f, -73.0f, -89.0f, 0, false, false, false);
	if (_vm->_cutContent) {
		Actor_Face_Actor(kActorDektora, kActorMcCoy, true);
		Actor_Face_Actor(kActorMcCoy, kActorDektora, true);
	}
	Actor_Says(kActorMcCoy, 3690, 14);
	Actor_Start_Speech_Sample(kActorDektora, 750);
	Actor_Face_Actor(kActorMcCoy, kActorDektora, true);
	Actor_Face_Actor(kActorDektora, kActorMcCoy, true);
	Actor_Says(kActorMcCoy, 3695, 15);
	if (_vm->_cutContent) {
		Actor_Says(kActorMcCoy, 3700, kAnimationModeTalk); // If I found you, so will she.
		Game_Flag_Set(kFlagMcCoyIsHelpingReplicants);
		Actor_Modify_Friendliness_To_Other(kActorDektora, kActorMcCoy, 2);
		if (Actor_Query_Friendliness_To_Other(kActorDektora, kActorMcCoy) > 49
		&& !Actor_Clue_Query(kActorDektora, kClueMcCoyRetiredZuben)
		&& !Actor_Clue_Query(kActorDektora, kClueMcCoyRetiredLucy)
		&& !Actor_Clue_Query(kActorDektora, kClueMcCoyRetiredGordo)) {
			Actor_Clue_Acquire(kActorDektora, kClueMcCoyHelpedDektora, true, kActorDektora);
			if (Global_Variable_Query(kVariableAffectionTowards) == kAffectionTowardsNone) {
				Global_Variable_Set(kVariableAffectionTowards, kAffectionTowardsDektora);
			}
		}
	}
	if (Game_Flag_Query(kFlagDektoraIsReplicant)) {
		callHolloway();
	} else {
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagHanoiIsReplicant)
			&& !Game_Flag_Query(kFlagHanoiDead)) {
				Player_Loses_Control();
				Actor_Put_In_Set(kActorHanoi, kSetNR07);
				Actor_Set_At_XYZ(kActorHanoi, -102.0f, -73.5f, -233.0f, 0);
				Actor_Face_Actor(kActorHanoi, kActorDektora, true);
				Actor_Face_Actor(kActorDektora, kActorHanoi, true);
				Async_Actor_Walk_To_Waypoint(kActorMcCoy, 338, 0, false);
				Actor_Says(kActorHanoi, 130, 3);
				Actor_Face_Actor(kActorMcCoy, kActorHanoi, true);
				Actor_Says(kActorDektora, 2360, 30);	//03-2360.AUD	Of course not.
				Actor_Says(kActorHanoi, 140, kAnimationModeTalk);
				AI_Movement_Track_Flush(kActorHanoi);
				AI_Movement_Track_Append(kActorHanoi, 337, 0);
				AI_Movement_Track_Repeat(kActorHanoi); 
				Delay (6000);
				Actor_Face_Actor(kActorHanoi, kActorMcCoy, true);
				Actor_Face_Actor(kActorMcCoy, kActorHanoi, true);
				Actor_Change_Animation_Mode(kActorHanoi, 23);
				Actor_Set_Invisible(kActorMcCoy, true);
				Actor_Face_Actor(kActorDektora, kActorHanoi, true);
				Actor_Says(kActorMcCoy, 3595, kAnimationModeTalk);
				Actor_Says(kActorDektora, 2610, 30);//03-2610.AUD	I… I've got to get out of here.
				dektoraRunAway();
				Actor_Set_Goal_Number(kActorDektora, kGoalDektoraNR08ReadyToRun);
				Actor_Says(kActorMcCoy, 3785, kAnimationModeTalk); //00-3785.AUD	Let go, you lug. I gotta-- (grunts)
				Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
				Ambient_Sounds_Remove_All_Looping_Sounds(1u);
				Actor_Set_Goal_Number(kActorHanoi, kGoalHanoiThrowOutMcCoy);
			} else {
				dektoraRunAway();
				Actor_Set_Goal_Number(kActorDektora, kGoalDektoraNR08ReadyToRun);
			}
		} else {
			dektoraRunAway();
		}
	}
}

void SceneScriptNR07::talkAboutMoonbus() {
	if (_vm->_cutContent) {
		Loop_Actor_Walk_To_XYZ(kActorMcCoy, -109.0f, -73.0f, -89.0f, 0, false, false, false);
		Actor_Face_Actor(kActorDektora, kActorMcCoy, true);
		Actor_Face_Actor(kActorMcCoy, kActorDektora, true);
	}
	Actor_Says(kActorMcCoy, 3705, 19);
	Actor_Says(kActorDektora, 760, kAnimationModeSit); // Excuse me?
	// Fixed the code here so now Dektora will run away or call Holloway after the conversation is finished and not in the middle of it. 
	Actor_Says(kActorMcCoy, 3710, kAnimationModeTalk); // Somebody told me about this moonbus that got hijacked.
	Actor_Says(kActorMcCoy, 3715, 15); // You know, the one where all those humans got killed?
	if (Game_Flag_Query(kFlagDektoraIsReplicant)) {
		if (_vm->_cutContent) {
			Actor_Modify_Friendliness_To_Other(kActorDektora, kActorMcCoy, -2);
		} else {
			Actor_Modify_Friendliness_To_Other(kActorDektora, kActorMcCoy, -5);
		}
#if BLADERUNNER_ORIGINAL_BUGS
		Actor_Says(kActorMcCoy, 3710, 18);
#else
#endif // BLADERUNNER_ORIGINAL_BUGS
		callHolloway();
		// Added in an extra scenario where McCoy arrests Dektora if he has enough evidence against her. McCoy will arrest her after selecting the moonbus option if he has enough evidence.
		// If Early Q is murdered and you have the purchased scorpions clue McCoy arrests Dektora fot the murder of Early Q. If you have the EarlyInterviewB2 clue where Early tells you about Dektora
		// and other trying to help get the reps offworld McCoy arrests her for being a rep sympathizer.
	} else {
		// Removed code for arresting Dektora for the murder of Early Q since she only kills Early Q if she is a replicant, therefore she can't be arrested.
		// Also expanded the scene of mcCoy arresting Dektora.
		Actor_Says(kActorDektora, 620, 30);	//03-0620.AUD	I’m sure I don’t know what you mean.
		Delay (2000);
		Actor_Says(kActorMcCoy, 3090, 14); //00-3090.AUD	You may not be a Rep but you’re a damn Rep sympathizer for sure.
		Actor_Says(kActorMcCoy, 3095, 18); //00-3095.AUD	Now we’re gonna take a little ride downtown.
		dektoraRunAway();
		Actor_Face_Heading(kActorMcCoy, 0, false);
		Actor_Change_Animation_Mode(kActorMcCoy, 5); // McCoy points his gun at Dektora.
		Actor_Says(kActorMcCoy, 8950, -1); //00-8950.AUD	Hold it right there!
		// Dektora comes back into the room.
		Actor_Put_In_Set(kActorDektora, kSetNR07);
		Actor_Set_At_XYZ(kActorDektora, -102.0f, -73.5f, -233.0f, 0);
		Loop_Actor_Walk_To_Actor(kActorDektora, kActorMcCoy, 108, true, true);
		Actor_Face_Actor(kActorMcCoy, kActorDektora, true);
		Actor_Face_Actor(kActorDektora, kActorMcCoy, true);
		Delay (1000);
		Actor_Says(kActorMcCoy, 1955, -1); //00-1955.AUD	We’re taking a little drive downtown.
		Actor_Modify_Friendliness_To_Other(kActorSteele, kActorMcCoy, 1);
		Actor_Modify_Friendliness_To_Other(kActorClovis, kActorMcCoy, -2);
		Actor_Modify_Friendliness_To_Other(kActorGuzza, kActorMcCoy, 1);
		Music_Stop(3u);
		Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
		Ambient_Sounds_Remove_All_Looping_Sounds(1u);
		Delay (1000);
		Game_Flag_Set(kFlagDektoraArrested);
		Game_Flag_Reset(kFlagMcCoyIsHelpingReplicants);
		Actor_Put_In_Set(kActorDektora, kSetPS09);
		Actor_Set_At_XYZ(kActorDektora, -280.0f, 0.33f, -270.0f, 583);
		Game_Flag_Reset(kFlagSpinnerAtNR01);
		Game_Flag_Reset(kFlagSpinnerAtHF01);
		Game_Flag_Set(kFlagSpinnerAtPS01);
		Scene_Exits_Enable();
		Game_Flag_Reset(kFlagMcCoyInNightclubRow);
		Game_Flag_Set(kFlagMcCoyInPoliceStation);
		Outtake_Play(kOuttakeAway1, true, -1);
		Set_Enter(kSetPS09, kScenePS09);
	}
}

void SceneScriptNR07::talkAboutBlackSedan() {
	Actor_Modify_Friendliness_To_Other(kActorDektora, kActorMcCoy, -3);
	Actor_Says(kActorMcCoy, 3615, 16);
	Actor_Says(kActorDektora, 770, 30);
	Actor_Says(kActorMcCoy, 3720, 15);
	Actor_Says_With_Pause(kActorDektora, 780, 2.0f, 30);
	Actor_Says(kActorDektora, 790, 31);
	Actor_Says(kActorMcCoy, 3725, 18); //00-3725.AUD	Is that right? Any reason you didn’t tell me that right off?
	Actor_Says(kActorDektora, 800, 30);
	Actor_Says_With_Pause(kActorMcCoy, 3730, 2.0f, 13); //00-3730.AUD	Animal murder is pretty horrible.
	Actor_Says_With_Pause(kActorDektora, 810, 1.0f, kAnimationModeSit);
	Actor_Says(kActorDektora, 820, 30);	 //03-0820.AUD	Any murder is horrible. And unfortunate.
	Actor_Says(kActorMcCoy, 3735, 14); //00-3735.AUD	Some are worse than others.
	Actor_Says(kActorDektora, 830, 31);
	Actor_Says(kActorMcCoy, 3740, 19);
}

void SceneScriptNR07::talkAboutScorpions() {
	Actor_Says(kActorMcCoy, 3620, 19); //00-3620.AUD	You like scorpions, huh?
	Actor_Says(kActorDektora, 840, 30); //03-0840.AUD	Scorpions?
	Actor_Says(kActorMcCoy, 3745, 9); //00-3745.AUD	Insects. Fakes. From Animoid Row. You buy a box of them?
#if BLADERUNNER_ORIGINAL_BUGS
	Actor_Says_With_Pause(kActorDektora, 850, 1.0f, 30);
	Actor_Says(kActorDektora, 860, 30);
	Actor_Says(kActorDektora, 870, kAnimationModeSit);
#else
	Actor_Says_With_Pause(kActorDektora, 850, 1.0f, 30); // I didn't know what they were called
	Actor_Says(kActorDektora, 860, 31); //03-0860.AUD	Insects make excellent pets. And they were so beautiful I just had to have the whole set.
	Actor_Clue_Acquire(kActorMcCoy, kClueDektoraInterview4, true, kActorDektora);
#endif // BLADERUNNER_ORIGINAL_BUGS
	Actor_Says(kActorMcCoy, 3750, 11); //00-3750.AUD	Did you know they were poisonous?
	Actor_Says(kActorDektora, 880, 30);
	Actor_Says(kActorMcCoy, 3755, 16); //00-3755.AUD	And that doesn’t scare you?
	Actor_Says(kActorDektora, 890, 31);
	// Repurposed the Dektora interview 4 clue to be about the scorpions. The original Dektora interview 4 clue dialogue will now be under the clue
	// Dektora confession where she admits to McCoy about being involved with Clovis and even calling him and Lucy her family.
	Actor_Says(kActorDektora, 900, 30); // Who would need to add insects to the list?
}

} // End of namespace BladeRunner
