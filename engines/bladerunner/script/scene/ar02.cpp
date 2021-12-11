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

void SceneScriptAR02::InitializeScene() {
	if (_vm->_cutContent) {
		Music_Play(kMusicArabLoop, 22, 0, 2, -1, kMusicLoopRepeatRandomStart, 2);
	} else {
		Music_Play(kMusicArabLoop, 22, 0, 2, -1, kMusicLoopRepeat, 2);
	}
	if (Game_Flag_Query(kFlagRC03toAR02)) {
		Setup_Scene_Information(-560.0f, 0.0f, -799.0f, 333);
	} else {
		Setup_Scene_Information(-182.0f, 0.0f, -551.0f, 973);
	}
	Scene_Exit_Add_2D_Exit(0,  0, 439, 212, 479, 2);
	Scene_Exit_Add_2D_Exit(1, 81, 202, 215, 406, 3);
	Ambient_Sounds_Add_Looping_Sound(kSfxCTRAIN1, 50,   1, 1);
	Ambient_Sounds_Add_Looping_Sound(kSfxRCAMBR1, 60, 100, 1);
	Ambient_Sounds_Add_Looping_Sound(kSfxHCLOOP1, 50,   1, 1);
	Ambient_Sounds_Add_Sound(kSfx67_0480R, 5,  70, 12,  12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0540R, 5,  70, 12,  12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0560R, 5,  70, 12,  12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0870R, 5,  70, 12,  12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0900R, 5,  70, 12,  12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0940R, 5,  70, 12,  12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_1070R, 5,  70, 12,  12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_1080R, 5,  70, 12,  12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_1160R, 5,  70, 12,  12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxHCANM8,   3,  30, 16,  16, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxHCANM2,   3,  30, 16,  16, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxHCANM3,   3,  30, 16,  16, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxHCANM4,   3,  30, 16,  16, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxHCANM5,   3,  30, 16,  16, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxHCANM6,   3,  30, 16,  16, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxHCANM7,   3,  30, 16,  16, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxHCANM1,   3,  30, 16,  16, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Speech_Sound(kActorBlimpGuy,  0, 10u, 260u, 17, 24, -100, 100, -101, -101, 1, 1);
	Ambient_Sounds_Add_Speech_Sound(kActorBlimpGuy, 20, 10u, 260u, 17, 24, -100, 100, -101, -101, 1, 1);
	Ambient_Sounds_Add_Speech_Sound(kActorBlimpGuy, 40, 10u, 260u, 17, 24, -100, 100, -101, -101, 1, 1);
	Ambient_Sounds_Add_Speech_Sound(kActorBlimpGuy, 50, 10u, 260u, 17, 24, -100, 100, -101, -101, 1, 1);
	Ambient_Sounds_Add_Sound(kSfxSPIN2B,  10, 180, 16,  25,    0,   0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSPIN3A,  10, 180, 16,  25,    0,   0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxTHNDER2, 10, 180, 50, 100,    0,   0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxTHNDER3, 10, 180, 50, 100,    0,   0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxTHNDER4, 10, 180, 50, 100,    0,   0, -101, -101, 0, 0);
	if (Game_Flag_Query(kFlagSpinnerAtAR01)
	    && Game_Flag_Query(kFlagAR01toAR02)) {
		Scene_Loop_Start_Special(kSceneLoopModeLoseControl, 1, false);
		Scene_Loop_Set_Default(2);
		Game_Flag_Reset(kFlagAR01toAR02);
	} else if (!Game_Flag_Query(kFlagSpinnerAtAR01)
	           &&  Game_Flag_Query(kFlagAR01toAR02)) {
		Scene_Loop_Start_Special(kSceneLoopModeLoseControl, 0, false);
		Scene_Loop_Set_Default(2);
		Game_Flag_Reset(kFlagAR01toAR02);
	} else {
		Scene_Loop_Set_Default(2);
	}
}

void SceneScriptAR02::SceneLoaded() {
	Obstacle_Object("DF_BOOTH", true);
#if BLADERUNNER_ORIGINAL_BUGS
	if (!Game_Flag_Query(kFlagAR02DektoraBoughtScorpions)) {
		Item_Add_To_World(kItemScorpions, kModelAnimationCageOfScorpions, kSetAR01_AR02, -442.84f, 36.77f, -1144.51f, 360, 36, 36, false, true, false, true);
	}
	if ( Global_Variable_Query(kVariableChapter) == 4
	 && !Game_Flag_Query(kFlagAR02DektoraBoughtScorpions)
	) {
		Game_Flag_Set(kFlagNotUsed0);
		Item_Remove_From_World(kItemScorpions);
	}
#else
	if (Global_Variable_Query(kVariableChapter) < 4
	    && !Game_Flag_Query(kFlagAR02DektoraBoughtScorpions)
	    && !Game_Flag_Query(kFlagScorpionsInAR02)
	) {
		// the kFlagScorpionsInAR02 flag helps keep track of the item in AR
		// and make it not blink in and out of existence
		// in the transition from AR01 to AR02
		Game_Flag_Set(kFlagScorpionsInAR02);
		Item_Add_To_World(kItemScorpions, kModelAnimationCageOfScorpions, kSetAR01_AR02, -442.84f, 36.77f, -1144.51f, 360, 36, 36, false, true, false, true);
	} else if (Global_Variable_Query(kVariableChapter) >= 4
	           && !Game_Flag_Query(kFlagAR02DektoraBoughtScorpions)
	           && Game_Flag_Query(kFlagScorpionsInAR02)
	) {
		Game_Flag_Reset(kFlagScorpionsInAR02);
		Item_Remove_From_World(kItemScorpions);
	}
#endif // BLADERUNNER_ORIGINAL_BUGS
}

bool SceneScriptAR02::MouseClick(int x, int y) {
	return Region_Check(250, 215, 325, 260);
}

bool SceneScriptAR02::ClickedOn3DObject(const char *objectName, bool a2) {
	return false;
}

bool SceneScriptAR02::ClickedOnActor(int actorId) {
	if (actorId == kActorInsectDealer) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -386.96f, 0.0f, -1078.45f, 12, true, false, false)) {
			Actor_Face_Actor(kActorMcCoy, kActorInsectDealer, true);
			Actor_Face_Actor(kActorInsectDealer, kActorMcCoy, true);
			if (Global_Variable_Query(kVariableChapter) == 2) {
				if (Game_Flag_Query(kFlagAR02InsectDealerInterviewed)
				    && !Game_Flag_Query(kFlagAR02InsectDealerTalk)
				) {
					Game_Flag_Set(kFlagAR02InsectDealerTalk);
					Player_Loses_Control();
					ADQ_Flush();
					ADQ_Add(kActorInsectDealer, 210, 14);
					Loop_Actor_Walk_To_XYZ(kActorMcCoy, -350.66f, 0.0f, -1117.19f, 0, false, false, false);
					Actor_Face_Actor(kActorMcCoy, kActorInsectDealer, true);
					if (_vm->_cutContent) {
						Actor_Says(kActorInsectDealer, 220, 14); // Doesn't she deserve a gift?
					}
					Actor_Says(kActorMcCoy, 110, 18);
					Actor_Says(kActorInsectDealer, 230, 14);
					Actor_Says(kActorMcCoy, 115, 18);
					Actor_Says(kActorInsectDealer, 240, 14);
					Item_Pickup_Spin_Effect(kModelAnimationMaggieBracelet, 288, 257);
					Actor_Says(kActorInsectDealer, 250, 14);
					Player_Gains_Control();
					dialogueWithInsectDealerBuyBracelet();
				} else if (Game_Flag_Query(kFlagAR02InsectDealerInterviewed)) {
					Actor_Says(kActorMcCoy, 75, 18);
					Actor_Says(kActorInsectDealer, 60, 12);
					Actor_Says(kActorInsectDealer, 70, 14);
				} else {
					dialogueWithInsectDealer1();
				}
			} else if (Global_Variable_Query(kVariableChapter) > 2) {
				if (Actor_Clue_Query(kActorMcCoy, kCluePeruvianLadyInterview)
				    && !Actor_Clue_Query(kActorMcCoy, kClueDragonflyCollection)
				) {
					Actor_Says(kActorMcCoy, 205, 16);
					Actor_Says(kActorInsectDealer, 290, 12);
					Actor_Says(kActorInsectDealer, 300, 13);
					Actor_Says(kActorMcCoy, 210, 15);
					Actor_Says(kActorInsectDealer, 310, 12);
					Actor_Says(kActorMcCoy, 215, 13); // Thanks for your help
					if (Game_Flag_Query(kFlagAR02DektoraBoughtScorpions)) {
						Actor_Says(kActorMcCoy, 220, 14);
						Actor_Says(kActorInsectDealer, 320, 12);
						Actor_Says(kActorMcCoy, 225, 13);
						Actor_Says(kActorInsectDealer, 330, 14);
						Actor_Says(kActorMcCoy, 230, 19);
						Actor_Says(kActorInsectDealer, 340, 13);
						Actor_Says(kActorInsectDealer, 350, 12);
						Actor_Says(kActorMcCoy, 235, 16);
						Actor_Clue_Acquire(kActorMcCoy, kCluePurchasedScorpions, false, kActorInsectDealer);
					}
					Actor_Clue_Acquire(kActorMcCoy, kClueDragonflyCollection, false, kActorInsectDealer);
				} else {
					// still from Act 3 and beyond
					if (_vm->_cutContent) {
						switch (Global_Variable_Query(kVariableInsectDealerBanterTalk)) {
						case 0:
							// how's business
							Global_Variable_Increment(kVariableInsectDealerBanterTalk, 1);
							Actor_Says(kActorMcCoy, 240, 17); // How's business?
							Actor_Says(kActorInsectDealer, 360, 13);
							Actor_Says(kActorInsectDealer, 370, 14);
							Actor_Says(kActorMcCoy, 245, 13);
							break;
						case 1:
							Global_Variable_Increment(kVariableInsectDealerBanterTalk, 1);
							Actor_Says(kActorMcCoy, 8920, 13); // I gotta ask you a question.
							Actor_Says(kActorInsectDealer, 410, 13); //	Ah, perhaps you should ask someone else.
							//Added in some more dialogue for McCoy and the Peruvian woman.
							Actor_Says(kActorMcCoy, 1620, 13);  //00-1620.AUD	I’m not gonna hurt you.
							Delay (1000);
							Actor_Says(kActorInsectDealer, 400, 13); // I hear very little.							
							if (Player_Query_Agenda() == kPlayerAgendaSurly
							|| Player_Query_Agenda() == kPlayerAgendaErratic) { 
								Actor_Says(kActorMcCoy, 8450, 14); // Does this badge mean anything to you?
								Actor_Says(kActorInsectDealer, 440, 14); // Please, this is all I know.
				 				Actor_Says(kActorMcCoy, 8519, 14);//00-8519.AUD	What do you say we dish each other the straight goods.
								Actor_Says(kActorInsectDealer, 430, 14); //16-0430.AUD	I did not mean to offend. I only thought to spare you from the truth of it.
								Actor_Says(kActorMcCoy, 8455, 14); //00-8455.AUD	Let me judge what's gonna make me upset.	 		
								Actor_Says(kActorInsectDealer, 380, 14); //16-0380.AUD	You promised no hurt!
								Actor_Says(kActorMcCoy, 440, 16); //00-0440.AUD	Forget it.
								Actor_Modify_Friendliness_To_Other(kActorInsectDealer, kActorMcCoy, -10);
							}
							break;
						case 2:
							// offer to buy slug
							Global_Variable_Increment(kVariableInsectDealerBanterTalk, 1);
							Actor_Says(kActorMcCoy, 8520, 13); // What do you know?
							Actor_Says(kActorInsectDealer, 450, 13);
							// Made it so the Peruvian woman only sells you the slug if you have high friendliness.
							if (Actor_Query_Friendliness_To_Other(kActorInsectDealer, kActorMcCoy) >= 50) {
								Actor_Says(kActorInsectDealer, 460, 14);
								Actor_Says(kActorInsectDealer, 470, 13); // This slug, perhaps.
								Item_Pickup_Spin_Effect_From_Actor(kModelAnimationSlug, kActorInsectDealer, 0, -40);
								dialogueWithInsectDealerBuySlug();
							}
							break;
						case 3:
							Global_Variable_Increment(kVariableInsectDealerBanterTalk, 1);
							// Made it so friendliness actually effects the conversation.
							if (Actor_Query_Friendliness_To_Other(kActorInsectDealer, kActorMcCoy) >= 50) {
								Actor_Says(kActorMcCoy, 8610, 17); // What's the word, friend?
							} else {
								Actor_Says(kActorMcCoy, 8615, 17); // Heard anything on the street?
							}
							Actor_Says(kActorInsectDealer, 400, 13); // I hear very little.
							break;
						default:
						if (Actor_Query_Friendliness_To_Other(kActorInsectDealer, kActorMcCoy) >= 50) {
							Actor_Says(kActorMcCoy, 215, 13);
						} else {
							Actor_Says(kActorMcCoy, 8940, 13); //00-8940.AUD	What are you staring at?
						}
							break;
						}
					} else {
						// original behavior
						Actor_Says(kActorMcCoy, 240, 17); // How's business?
						Actor_Says(kActorInsectDealer, 360, 13);
						Actor_Says(kActorInsectDealer, 370, 14);
						Actor_Says(kActorMcCoy, 245, 13);
					}
				}
			}
			return true;
		}
	}

	if (actorId == kActorHasan
	    && Global_Variable_Query(kVariableChapter) == 2
	) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -240.79f, 0.0f, -1328.89f, 12, true, false, false)) {
			Actor_Face_Actor(kActorMcCoy, kActorHasan, true);
			Actor_Face_Actor(kActorHasan, kActorMcCoy, true);
			if (!Game_Flag_Query(kFlagAR02HassanTalk)) {
				Actor_Says(kActorHasan, 0, 14);
				Actor_Says(kActorMcCoy, 140, 18);
				Game_Flag_Set(kFlagAR02HassanTalk);
				return true;
			}
			dialogueWithHassan();
		}
	}

	if (_vm->_cutContent) {
		if (actorId == kActorHasan
		    && Global_Variable_Query(kVariableChapter) > 2) {

			if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -240.79f, 0.0f, -1328.89f, 12, true, false, false)) {
				Actor_Face_Actor(kActorMcCoy, kActorHasan, true);
				Actor_Face_Actor(kActorHasan, kActorMcCoy, true);

				if (Actor_Clue_Query(kActorMcCoy, kClueStrangeScale1)
					&& !Game_Flag_Query(kFlagWrongInvestigation)
				) {
					dialogueWithHassan();
				} else {
					switch (Global_Variable_Query(kVariableHasanBanterTalk)) {
					case 0:
						Global_Variable_Increment(kVariableHasanBanterTalk, 1);
						Actor_Says(kActorMcCoy, 155, 13); // How's business?
						Actor_Says(kActorHasan, 10, 13);
						Actor_Says(kActorHasan, 20, 14);
						break;
					case 1:
						Global_Variable_Increment(kVariableHasanBanterTalk, 1);
						Actor_Says(kActorMcCoy, 6980, 13); // What's the word
						Actor_Says(kActorHasan, 290, 13);
						if (Actor_Query_Friendliness_To_Other(kActorHasan, kActorMcCoy) > 49) {
							Actor_Says(kActorHasan, 300, 14);
							Actor_Says(kActorHasan, 310, 13);
							Item_Pickup_Spin_Effect_From_Actor(kModelAnimationGarterSnake, kActorHasan, 0, -40);
							dialogueWithHassanBuySnake();
						}
						break;
					case 2:
						// offer to buy snake
						Global_Variable_Increment(kVariableHasanBanterTalk, 1);
						if (Player_Query_Agenda() == kPlayerAgendaSurly
						   || Actor_Query_Friendliness_To_Other(kActorHasan, kActorMcCoy) <= 49 ) {
							Actor_Says(kActorMcCoy, 8915, 14); // You got a minute, pal?
							Actor_Says(kActorHasan, 260, 14); // My time is quite valuable, noble one
							Actor_Modify_Friendliness_To_Other(kActorHasan, kActorMcCoy, -5);
						} else {
							Actor_Says(kActorMcCoy, 8615, 13); // Heard anything on the street?
							Actor_Says(kActorHasan, 250, 13); // I'm afraid not, noble one. But you shall surely be the first to know, if I do hear something.
						}
						break;
					default:
						if (Actor_Query_Friendliness_To_Other(kActorHasan, kActorMcCoy) <= 45 ) {
							// Added in a line.
							Actor_Says(kActorMcCoy, 8595, 13); //00-8595.AUD	Hmm. He's damn unfriendly.
						} else {
							Actor_Says(kActorMcCoy, 1315, 13);
						}
						break;
					}
				}
			}
		}
	}
	return false;
}

bool SceneScriptAR02::ClickedOnItem(int itemId, bool a2) {
	if (itemId == kItemScorpions) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -386.96f, 0.0f, -1078.45f, 12, true, false, false)) {
			Actor_Face_Actor(kActorMcCoy, kActorInsectDealer, true);
			if (!Game_Flag_Query(kFlagAR02ScorpionsChecked)) {
				Actor_Says(kActorInsectDealer, 0, 14);
				Actor_Says(kActorMcCoy, 55, 18);
				Actor_Says(kActorInsectDealer, 10, 14);
				Actor_Says(kActorMcCoy, 60, 18);
				Actor_Says(kActorInsectDealer, 20, 14);
				Game_Flag_Set(kFlagAR02ScorpionsChecked);
			} else if ( Game_Flag_Query(kFlagAR02ScorpionsChecked)
			        && !Game_Flag_Query(kFlagAR02StungByScorpion)
			) {
				Actor_Says(kActorMcCoy, 65, 21);
				Actor_Says(kActorInsectDealer, 30, 14);
				Actor_Says(kActorInsectDealer, 40, 14);
				Actor_Says(kActorMcCoy, 70, 18);
				Actor_Says(kActorInsectDealer, 50, 14);
				Game_Flag_Set(kFlagAR02StungByScorpion);
			} else {
				Actor_Says(kActorMcCoy, 8527, 14);
			}
			return true;
		}
	}
	return false;
}

bool SceneScriptAR02::ClickedOnExit(int exitId) {
	if (exitId == 0) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -182.0f, 0.0f, -551.0f, 0, true, false, false)) {
			Game_Flag_Set(kFlagAR02toAR01);
			Async_Actor_Walk_To_XYZ(kActorMcCoy, -182.0f, 0.0f, -407.0f, 0, false);
			Set_Enter(kSetAR01_AR02, kSceneAR01);
		}
		return true;
	}

	if (exitId == 1) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -465.0f, 0.0f, -799.0f, 0, true, false, false)) {
			Loop_Actor_Walk_To_XYZ(kActorMcCoy, -560.0f, 0.0f, -799.0f, 0, false, false, false);
			Game_Flag_Set(kFlagAR02toRC03);
			Game_Flag_Reset(kFlagMcCoyInAnimoidRow);
			Game_Flag_Set(kFlagMcCoyInRunciters);
			Music_Stop(3u);
			Set_Enter(kSetRC03, kSceneRC03);
		}
		return true;
	}
	return false;
}

bool SceneScriptAR02::ClickedOn2DRegion(int region) {
	return false;
}

void SceneScriptAR02::SceneFrameAdvanced(int frame) {
}

void SceneScriptAR02::ActorChangedGoal(int actorId, int newGoal, int oldGoal, bool currentSet) {
}

void SceneScriptAR02::PlayerWalkedIn() {
	if (Game_Flag_Query(kFlagRC03toAR02)) {
		Loop_Actor_Walk_To_XYZ(kActorMcCoy, -465.0f, 0.0f, -799.0f, 0, false, false, false);
		Game_Flag_Reset(kFlagRC03toAR02);
	}
	Game_Flag_Set(kFlagAR02Entered);
}

void SceneScriptAR02::PlayerWalkedOut() {
	Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
	Ambient_Sounds_Remove_All_Looping_Sounds(1u);
}

void SceneScriptAR02::DialogueQueueFlushed(int a1) {
}

void SceneScriptAR02::dialogueWithInsectDealer1() {
	Dialogue_Menu_Clear_List();
	if (Actor_Clue_Query(kActorMcCoy, kClueDragonflyEarring)
	    || Actor_Clue_Query(kActorMcCoy, kClueBombingSuspect)
	) {
		DM_Add_To_List_Never_Repeat_Once_Selected(490, 3, 5, 5); // EARRING
	}
	if (Actor_Clue_Query(kActorMcCoy, kClueDragonflyAnklet)
	    && !Actor_Clue_Query(kActorMcCoy, kClueDragonflyEarring)
	    && !Actor_Clue_Query(kActorMcCoy, kClueBombingSuspect)
	) {
		DM_Add_To_List_Never_Repeat_Once_Selected(500, 3, 5, 5); // ANKLET
	}
	DM_Add_To_List_Never_Repeat_Once_Selected(510, 8, 3, -1); // MERCHANDISE
	Dialogue_Menu_Add_DONE_To_List(520); // DONE

	Dialogue_Menu_Appear(320, 240);
	int answerValue = Dialogue_Menu_Query_Input();
	Dialogue_Menu_Disappear();

	switch (answerValue) {
	case 490: // EARRING
	case 500: // ANKLET
		if (answerValue == 490) { // EARRING
			Actor_Says(kActorMcCoy, 145, 15);
		} else { // ANKLET
		// Added in the appropriate line.
			if (_vm->_cutContent) {
				Actor_Says(kActorMcCoy, 8470, 15); //00-8470.AUD	You recognize the insect in this photo?
			} else {
				Actor_Says(kActorMcCoy, 150, 15); //00-0150.AUD	You know anything about insects?
			}
		}
		Actor_Says(kActorInsectDealer, 80, 14);
		Actor_Says(kActorMcCoy, 80, 16);
		Actor_Says(kActorInsectDealer, 90, 12);
		Actor_Says(kActorMcCoy, 85, 17);
		Actor_Says(kActorInsectDealer, 100, 14);
		Actor_Says(kActorInsectDealer, 110, 12);
		Actor_Says(kActorInsectDealer, 120, 12);
		Actor_Says(kActorMcCoy, 90, 13);
		Actor_Says(kActorInsectDealer, 130, 12);
		Actor_Says(kActorInsectDealer, 140, 14);
		Actor_Says(kActorMcCoy, 95, 15);
		Actor_Says(kActorInsectDealer, 150, 12);
		Actor_Says(kActorInsectDealer, 160, 13);
		Actor_Says(kActorInsectDealer, 170, 14);
		Actor_Says(kActorMcCoy, 100, 16);
		Actor_Says(kActorInsectDealer, 180, 13);
		Game_Flag_Set(kFlagAR02InsectDealerInterviewed);
		Actor_Clue_Acquire(kActorMcCoy, kCluePeruvianLadyInterview, true, kActorInsectDealer);
		break;

	case 510: // MERCHANDISE
		Actor_Says(kActorMcCoy, 8475, 12);
		Actor_Says(kActorInsectDealer, 190, 12);
		Actor_Says(kActorMcCoy, 105, 15);
		Actor_Says(kActorInsectDealer, 200, 14);
		break;

	case 520: // DONE
		Actor_Says(kActorMcCoy, 215, 16); // Thanks for your help.
		break;
	}
}

void SceneScriptAR02::dialogueWithInsectDealerBuyBracelet() {
	Dialogue_Menu_Clear_List();

	if (_vm->_cutContent) {
		Dialogue_Menu_Clear_Never_Repeat_Was_Selected_Flag(530);
		Dialogue_Menu_Clear_Never_Repeat_Was_Selected_Flag(540);
	}

	if (Global_Variable_Query(kVariableChinyen) >= 15
	    || Query_Difficulty_Level() == kGameDifficultyEasy
	) {
		DM_Add_To_List_Never_Repeat_Once_Selected(530, 7, 5, 3); // BUY
	}
	DM_Add_To_List_Never_Repeat_Once_Selected(540, 3, 5, 7); // NO THANKS

	Dialogue_Menu_Appear(320, 240);
	int answerValue = Dialogue_Menu_Query_Input();
	Dialogue_Menu_Disappear();

	if (answerValue == 530) { // BUY
		Actor_Says(kActorMcCoy, 120, 12);
		if (Query_Difficulty_Level() != kGameDifficultyEasy) {
			Global_Variable_Decrement(kVariableChinyen, 15);
		}
		Actor_Clue_Acquire(kActorMcCoy, kClueMaggieBracelet, true, kActorInsectDealer);
		Actor_Modify_Friendliness_To_Other(kActorInsectDealer, kActorMcCoy, 5);
	} else if (answerValue == 540) { // NO THANKS
		Actor_Says(kActorMcCoy, 125, 13);
		Actor_Says(kActorInsectDealer, 260, kAnimationModeTalk);
		Actor_Says(kActorMcCoy, 130, 15);
		Actor_Says(kActorInsectDealer, 270, kAnimationModeTalk);
		Actor_Says(kActorInsectDealer, 280, kAnimationModeTalk);
		Actor_Says(kActorMcCoy, 135, 11);
		Actor_Modify_Friendliness_To_Other(kActorInsectDealer, kActorMcCoy, -5);
	}
}

/**
* This is only for cut content (purchasing the Electric Slug)
*/
void SceneScriptAR02::dialogueWithInsectDealerBuySlug() {
	Dialogue_Menu_Clear_List();

	Dialogue_Menu_Clear_Never_Repeat_Was_Selected_Flag(530);
	Dialogue_Menu_Clear_Never_Repeat_Was_Selected_Flag(540);

	if (Global_Variable_Query(kVariableChinyen) >= 125
	    || Query_Difficulty_Level() == kGameDifficultyEasy
	) {
		DM_Add_To_List_Never_Repeat_Once_Selected(530, 7, 5, 3); // BUY
	}
	DM_Add_To_List_Never_Repeat_Once_Selected(540, 3, 5, 7); // NO THANKS

	Dialogue_Menu_Appear(320, 240);
	int answerValue = Dialogue_Menu_Query_Input();
	Dialogue_Menu_Disappear();

	if (answerValue == 530) { // BUY
		Actor_Says(kActorMcCoy, 7000, 12);
		if (Query_Difficulty_Level() != kGameDifficultyEasy) {
			Global_Variable_Decrement(kVariableChinyen, 125);
		}
		Actor_Clue_Acquire(kActorMcCoy, kClueSlug, true, kActorInsectDealer);
		Actor_Modify_Friendliness_To_Other(kActorInsectDealer, kActorMcCoy, 5);
	} else if (answerValue == 540) { // NO THANKS
		Actor_Says(kActorMcCoy, 7005, 13);
		Actor_Modify_Friendliness_To_Other(kActorInsectDealer, kActorMcCoy, -5);
	}
}

void SceneScriptAR02::dialogueWithHassan() {
	Dialogue_Menu_Clear_List();
	if (Actor_Clue_Query(kActorMcCoy, kClueStrangeScale1)) {
		DM_Add_To_List_Never_Repeat_Once_Selected(550, 8, 5, 2); // SCALE
	}
	if (Actor_Clue_Query(kActorMcCoy, kClueDragonflyEarring)) {
		DM_Add_To_List_Never_Repeat_Once_Selected(560, 6, 5, 7); // EARRING
	}
	Dialogue_Menu_Add_DONE_To_List(570); // DONE

	Dialogue_Menu_Appear(320, 240);
	int answerValue = Dialogue_Menu_Query_Input();
	Dialogue_Menu_Disappear();

	switch (answerValue) {
	case 550: // SCALE
		Actor_Says(kActorMcCoy, 145, 11); // This your work?
		// It never made any sense that Hasan is surprised that McCoy is a policeman even though he reffered to him as being part of the LPD earlier on.
		// I have rectified this by having Hasan say this only if you have not received the Hasan interview clue where he says this. 
		if (_vm->_cutContent) {
			if (!Actor_Clue_Query(kActorMcCoy, kClueHasanInterview)) {
				Actor_Says(kActorHasan, 30, 11); //20-0030.AUD	Oh, you're a policeman.
				Actor_Modify_Friendliness_To_Other(kActorHasan, kActorMcCoy, -1);
				Actor_Says(kActorMcCoy, 160, 11); //00-0160.AUD	That's right, McCoy, LPD.
			}
		} else {
			Actor_Says(kActorHasan, 30, 11); //20-0030.AUD	Oh, you're a policeman.
			Actor_Says(kActorMcCoy, 160, 11); //00-0160.AUD	That's right, McCoy, LPD.
		}
		// Made it so the conversation with Hasan will play out differently depending on your friendliness with him.
		// Firstly if you have low friendliness towards Hasan he lies to you and says he knows nothing.
		if (_vm->_cutContent) {
			if (Actor_Query_Friendliness_To_Other(kActorHasan, kActorMcCoy) < 50) {
				Actor_Says(kActorHasan, 250, 11);  //20-0250.AUD	I'm afraid not, noble one. But you shall surely be the first to know, if I do hear something.
				Actor_Says(kActorMcCoy, 3910, 16); //00-3910.AUD	You’re lying.
				Actor_Says(kActorHasan, 270, 11); //20-0270.AUD	You sully my good name with such accusations. I speak only the truth, I swear!
					if (Player_Query_Agenda() == kPlayerAgendaSurly 
							|| Player_Query_Agenda() == kPlayerAgendaErratic) {
						Actor_Says(kActorMcCoy, 8519, 14);//00-8519.AUD	What do you say we dish each other the straight goods.
						Actor_Modify_Friendliness_To_Other(kActorHasan, kActorMcCoy, -2);
					} else { 
						Actor_Says(kActorMcCoy, 6985, 11);	//-	00-6985.AUD	Got the straight scoop for me or what?
					}
				Delay (500);
				Actor_Says(kActorHasan, 280, 11); //20-0280.AUD	Oh, yes, now I remember. I misspoke before, that is all. Here's the truth of it.
				Actor_Says(kActorMcCoy, 2635, 18); //00-2635.AUD	I’m all ears.
			}
		}
		Actor_Says(kActorHasan, 40, 11); //20-0040.AUD	I told the last detective I sold the snake to Taffy Lewis.
		Actor_Says(kActorMcCoy, 165, 11); //00-0165.AUD	The last detective?
		// If you have high friendliness with Hasan he tells you the detectives name was Deckard.
		if (_vm->_cutContent) {
			Delay (500);
			if (Actor_Query_Friendliness_To_Other(kActorHasan, kActorMcCoy) >= 50) {
				Actor_Says(kActorMcCoy, 4130, kAnimationModeTalk); //00-4130.AUD	Anything else?
				Actor_Says(kActorHasan, 240, 11); //20-0240.AUD	In truth this humble merchant has discovered a fact surely to be of interest to you.
				Actor_Says(kActorHasan, 50, 11); //20-0050.AUD	His name was Deckard.
				Actor_Says(kActorMcCoy, 170, 11); //00-0170.AUD	Damn.
				Actor_Says(kActorHasan, 60, 11); //20-0060.AUD	What's the problem, noble one?
				Actor_Says(kActorMcCoy, 175, 16); //00-0175.AUD	I think I've been following up on someone else's case.
			} else {
				// However if you have low friendlines with Hasan he won't mention Deckards name.
				Actor_Says(kActorMcCoy, 4130, kAnimationModeTalk); //00-4130.AUD	Anything else?
				Actor_Says(kActorHasan, 70, 11); //20-0070.AUD	Certainly the LPD must have better things to do than to question a humble merchant over and over again about the same things.
				Actor_Says(kActorMcCoy, 6985, 11);	//-	00-6985.AUD	Got the straight scoop for me or what?
				Actor_Says(kActorHasan, 260, 11); //20-0260.AUD	My time is quite valuable, noble one. And I'm afraid I can spend no more with you.
				Actor_Says(kActorMcCoy, 440, 16); //00-0440.AUD	Forget it.
				Actor_Modify_Friendliness_To_Other(kActorHasan, kActorMcCoy, -2);
				}		
			} else {
				Actor_Says(kActorHasan, 50, 11); //20-0050.AUD	His name was Deckard.
				Actor_Says(kActorMcCoy, 170, 11); //00-0170.AUD	Damn.
				Actor_Says(kActorHasan, 60, 11); //20-0060.AUD	What's the problem, noble one?
				Actor_Says(kActorMcCoy, 175, 16); //00-0175.AUD	I think I've been following up on someone else's case.
			}
		if (_vm->_cutContent) {
			Game_Flag_Set(kFlagWrongInvestigation);
		}
		Game_Flag_Set(kFlagNotUsed370);
		break;

	case 560: // EARRING
		Actor_Says(kActorMcCoy, 150, 11);
		Actor_Says(kActorHasan, 140, 11);
		Actor_Says(kActorMcCoy, 185, 11);
		Actor_Says(kActorHasan, 150, 11);
		Actor_Says(kActorHasan, 160, 11);
		Actor_Says(kActorMcCoy, 190, 11);
		Actor_Says(kActorHasan, 170, 11);
		Actor_Says(kActorMcCoy, 195, 11);
		Actor_Says(kActorHasan, 180, 11);
		Actor_Says(kActorHasan, 190, 11);
		Actor_Says(kActorHasan, 200, 11);
		// Made it so McCoy only asks Hasan where to find more information on the earring and is directed to the Peruvian woman only
		// if he has not talked to her yet.
		if (_vm->_cutContent) {
			if (!Actor_Clue_Query(kActorMcCoy, kCluePeruvianLadyInterview)) {
				Actor_Says(kActorMcCoy, 200, 11);
				Actor_Says(kActorHasan, 210, 11); // Perhaps you should ask the Peruvian woman next door.
				Actor_Says(kActorHasan, 220, 11); // She's an expert on such things
				Actor_Says(kActorHasan, 230, 11); // and will cut a wonderful deal to friends.
			}
		} else {
			Actor_Says(kActorMcCoy, 200, 11);
			Actor_Says(kActorHasan, 210, 11); // Perhaps you should ask the Peruvian woman next door.
			Actor_Says(kActorHasan, 220, 11); // She's an expert on such things
			Actor_Says(kActorHasan, 230, 11); // and will cut a wonderful deal to friends.
		}
		Game_Flag_Set(kFlagNotUsed370);
		break;

	case 570: // DONE
		if (!Actor_Clue_Query(kActorMcCoy, kClueHasanInterview)) {
			// It never made any sense that Hasan seemed to know McCoy was a policemen but seemed to be surprised by this when you show him the scale later on.
			// I fixed this by having Hasan be a little resistant to McCoy which leads McCoy to reveal that he is a police officer. This only happens if McCoy has not shown 
			// Hasan the scale and he already found out.
			if (_vm->_cutContent &&
			 !Game_Flag_Query(kFlagWrongInvestigation)) {
				Actor_Says(kActorMcCoy, 8615, 13); // Heard anything on the street?
				Actor_Says(kActorHasan, 290, 11);  //20-0290.AUD	I have heard nothing of late, noble one.
				Actor_Says(kActorMcCoy, 505, 23); //00-0505.AUD	McCoy, LPD.
				Actor_Says(kActorHasan, 30, 11);//20-0030.AUD	Oh, you're a policeman.	
				Actor_Modify_Friendliness_To_Other(kActorHasan, kActorMcCoy, -1);
				Actor_Says(kActorMcCoy, 7200, 14); //00-7200.AUD	Bingo.
				Delay (500);
			 }
			Actor_Says(kActorMcCoy, 940, 13);
			// Quote 80 is *boop* in ENG and DEU versions
			// In FRA, ITA versions it is identical to the second half of quote 70, and thus redundant
			// In ESP version it is the missing second half of quote 70, and is required!
			if (_vm->_cutContent
			    && _vm->_language == Common::ES_ESP
			) {
				Actor_Says_With_Pause(kActorHasan, 70, 0.0f, 12);
				Actor_Says(kActorHasan, 80, kAnimationModeTalk);
			} else {
				Actor_Says(kActorHasan, 70, 12);
			}
			Actor_Says(kActorHasan, 90, 12);
			// Made it so McCoy only questions who Bob is and is directed to Bobs shop only if McCoy hasn't Met Bob.
			if (_vm->_cutContent) {
				if (!Game_Flag_Query(kFlagRC04Entered)) {
					Actor_Says(kActorMcCoy, 180, 15); //00-0180.AUD	Bob?
					Actor_Says(kActorHasan, 100, 14); //20-0100.AUD	He owns the armament shop up the street. He is insane, noble one. Insane.
				}
				} else {
					Actor_Says(kActorMcCoy, 180, 15); //00-0180.AUD	Bob?
					Actor_Says(kActorHasan, 100, 14); //20-0100.AUD	He owns the armament shop up the street. He is insane, noble one. Insane.
				}

			Actor_Says(kActorHasan, 110, 12);
			// Quote 130 is *boop* in ENG and DEU versions
			// In FRA, ITA versions it is identical to the second half of quote 120, and thus redundant
			// In ESP version it is the missing second half of quote 120, and is required!
			if (_vm->_cutContent
			    && _vm->_language == Common::ES_ESP
			) {
				Actor_Says_With_Pause(kActorHasan, 120, 0.0f, 13);
				Actor_Says(kActorHasan, 130, kAnimationModeTalk);
			} else {
				Actor_Says(kActorHasan, 120, 13);
			}
			Actor_Modify_Friendliness_To_Other(kActorHasan, kActorMcCoy, -1);
			Actor_Clue_Acquire(kActorMcCoy, kClueHasanInterview, false, kActorHasan);
		} else {
			Actor_Says(kActorMcCoy, 1315, 11); // Thanks for your time
		}
		break;
	}
}

/**
* This is only for cut content (purchasing the Garter Snake)
*/
void SceneScriptAR02::dialogueWithHassanBuySnake() {
	Dialogue_Menu_Clear_List();

	Dialogue_Menu_Clear_Never_Repeat_Was_Selected_Flag(530);
	Dialogue_Menu_Clear_Never_Repeat_Was_Selected_Flag(540);

	if (Global_Variable_Query(kVariableChinyen) >= 175
	    || Query_Difficulty_Level() == kGameDifficultyEasy
	) {
		DM_Add_To_List_Never_Repeat_Once_Selected(530, 7, 5, 3); // BUY
	}
	DM_Add_To_List_Never_Repeat_Once_Selected(540, 3, 5, 7); // NO THANKS

	Dialogue_Menu_Appear(320, 240);
	int answerValue = Dialogue_Menu_Query_Input();
	Dialogue_Menu_Disappear();

	if (answerValue == 530) { // BUY
		Actor_Says(kActorMcCoy, 7000, 12);
		if (Query_Difficulty_Level() != kGameDifficultyEasy) {
			Global_Variable_Decrement(kVariableChinyen, 175);
		}
		Actor_Clue_Acquire(kActorMcCoy, kClueGarterSnake, true, kActorHasan);
		Actor_Modify_Friendliness_To_Other(kActorHasan, kActorMcCoy, 5);
	} else if (answerValue == 540) { // NO THANKS
		Actor_Says(kActorMcCoy, 7005, 13);
		Actor_Modify_Friendliness_To_Other(kActorHasan, kActorMcCoy, -5);
	}
}

} // End of namespace BladeRunner
