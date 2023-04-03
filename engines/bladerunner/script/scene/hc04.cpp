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

void SceneScriptHC04::InitializeScene() {
	if (Game_Flag_Query(kFlagRC03toHC04)) {
		Setup_Scene_Information(-112.0f, 0.14f, -655.0f, 460);
		Game_Flag_Reset(kFlagRC03toHC04);
	} else {
		Setup_Scene_Information(-88.0f, 0.14f, -463.0f, 1013);
	}
	int loop = kMusicLoopRepeat;
	if (_vm->_cutContent && Random_Query(0, 2) == 1) {
		loop = kMusicLoopRepeatRandomStart;
	}
	Music_Play(kMusicOneTime, 14, -90, 1, -1, loop, 2);

	if (_vm->_cutContent) {
		if (!Game_Flag_Query(kFlagIsabellaArrested)
		&& Global_Variable_Query(kVariableChapter) < 4) { 
			Actor_Put_In_Set(kActorIsabella, kSetHC01_HC02_HC03_HC04);
			Actor_Set_At_XYZ(kActorIsabella, -210.0f, 0.0f, -445.0f, 250);
		} else {
			Actor_Put_In_Set(kActorIsabella, kSetRC01);
			Actor_Set_At_XYZ(kActorIsabella, -210.0f, 0.0f, -445.0f, 250);
		}
	} else {
		Actor_Put_In_Set(kActorIsabella, kSetHC01_HC02_HC03_HC04);
		Actor_Set_At_XYZ(kActorIsabella, -210.0f, 0.0f, -445.0f, 250);
	}

	Scene_Exit_Add_2D_Exit(0, 539,  51, 639, 309, 0);
	Scene_Exit_Add_2D_Exit(1,   0, 456, 639, 479, 2);

	Ambient_Sounds_Add_Looping_Sound(kSfxRAINAWN1, 50, 50, 0);
	Ambient_Sounds_Add_Looping_Sound(kSfxMAMASNG1, 16, 16, 0);
	Ambient_Sounds_Add_Looping_Sound(kSfxROTIS2,   40, 40, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0480R, 5, 70, 14, 16, -100,  100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0540R, 5, 70, 14, 16, -100,  100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0560R, 5, 70, 14, 16, -100,  100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0870R, 5, 70, 14, 16, -100,  100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0900R, 5, 70, 14, 16, -100,  100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0940R, 5, 70, 14, 16, -100,  100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_1070R, 5, 70, 14, 16, -100,  100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_1080R, 5, 70, 14, 16, -100,  100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_1160R, 5, 70, 14, 16, -100,  100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBARSFX1,  3, 60, 16, 16, -100, -100, -101, -101, 0, 0);
#if BLADERUNNER_ORIGINAL_BUGS
	Ambient_Sounds_Add_Sound(kSfxBARSFX1,  3, 60, 16, 16, -100, -100, -101, -101, 0, 0);
#endif // BLADERUNNER_ORIGINAL_BUGS
	Ambient_Sounds_Add_Sound(kSfxBARSFX3,  3, 60, 16, 16, -100, -100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBARSFX4,  3, 60, 16, 16, -100, -100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBARSFX5,  3, 60, 16, 16, -100, -100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBARSFX6,  3, 60, 16, 16, -100, -100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBARSFX7,  3, 60, 16, 16, -100, -100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxCLINK1,   3, 60, 16, 16, -100, -100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxCLINK2,   3, 60, 16, 16, -100, -100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxCLINK3,   3, 60, 16, 16, -100, -100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxCLINK4,   3, 60, 16, 16, -100, -100, -101, -101, 0, 0);

	if (Game_Flag_Query(kFlagHC02toHC04)) {
		Scene_Loop_Start_Special(kSceneLoopModeLoseControl, 0, false);
		Scene_Loop_Set_Default(1);
		Game_Flag_Reset(kFlagHC02toHC04);
	} else {
		Scene_Loop_Set_Default(1);
	}
}

void SceneScriptHC04::SceneLoaded() {
	Obstacle_Object("CAN FIRE", true);
	Unobstacle_Object("ASIANMALE01", true);
	Clickable_Object("CAN FIRE");
#if BLADERUNNER_ORIGINAL_BUGS
#else
	Unclickable_Object("CAN FIRE");
#endif // BLADERUNNER_ORIGINAL_BUGS
}

bool SceneScriptHC04::MouseClick(int x, int y) {
	return false;
}

bool SceneScriptHC04::ClickedOn3DObject(const char *objectName, bool a2) {
	return false;
}

bool SceneScriptHC04::ClickedOnActor(int actorId) {
	if (actorId == kActorIsabella) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -155.0f, 0.0f, -475.0f, 12, true, false, false)) {
			Actor_Face_Actor(kActorMcCoy, kActorIsabella, true);
			Actor_Face_Actor(kActorIsabella, kActorMcCoy, true);
			if (!Game_Flag_Query(kFlagHC04IsabellaTalk)) {
				Actor_Says(kActorIsabella, 0, kAnimationModeTalk);
				if (_vm->_cutContent) {
					if (Actor_Clue_Query(kActorMcCoy, kClueKingstonKitchenBox2)
	 				|| Actor_Clue_Query(kActorMcCoy, kClueKingstonKitchenBox1)
					|| Actor_Clue_Query(kActorMcCoy, kClueSpecialIngredient)) {
						if (Global_Variable_Query(kVariableChapter) < 4) {
							if (Player_Query_Agenda() != kPlayerAgendaPolite) {	
								Actor_Says(kActorMcCoy, 4560, 23); //00-4560.AUD	McCoy, LPD.
								Actor_Says(kActorMcCoy, 8920, 14); //00-8920.AUD	I gotta ask you a question.
							} else {
								Actor_Says(kActorMcCoy, 1280, 23); //00-1280.AUD	McCoy, LPD. Mind if I ask you a couple of questions?
							}
							if (Game_Flag_Query(kFlagSadikIsReplicant)) {
								Actor_Says(kActorIsabella, 20, kAnimationModeTalk);
							} else {
								Actor_Says(kActorIsabella, 150, kAnimationModeTalk); //59-0150.AUD	This is a clean place man. Mama Isabella law-abiding soul.
								Delay(2000);
								Actor_Says(kActorMcCoy, 5705, 13); //00-5705.AUD	Uh-huh.
							}
						}
					}
				} else {
					Actor_Says(kActorMcCoy, 1280, kAnimationModeTalk);
					Actor_Says(kActorIsabella, 20, kAnimationModeTalk);
				}
				Game_Flag_Set(kFlagHC04IsabellaTalk);
				return true;
			} else {
				dialogueWithIsabella();
				return true;
			}
		}
	}
	return false;
}

bool SceneScriptHC04::ClickedOnItem(int itemId, bool a2) {
	return false;
}

bool SceneScriptHC04::ClickedOnExit(int exitId) {
	if (exitId == 0) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -108.0f, 0.14f, -639.0f, 0, true, false, false)) {
			Music_Stop(2u);
			Game_Flag_Set(kFlagHC04toRC03);
			Game_Flag_Reset(kFlagMcCoyInHawkersCircle);
			Game_Flag_Set(kFlagMcCoyInRunciters);
			Set_Enter(kSetRC03, kSceneRC03);
		}
		return true;
	}

	if (exitId == 1) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -72.0f, 0.14f, -399.0f, 0, true, false, false)) {
			Game_Flag_Set(kFlagHC04toHC02);
			Set_Enter(kSetHC01_HC02_HC03_HC04, kSceneHC02);
		}
		return true;
	}
	return false;
}

bool SceneScriptHC04::ClickedOn2DRegion(int region) {
	return false;
}

void SceneScriptHC04::SceneFrameAdvanced(int frame) {
}

void SceneScriptHC04::ActorChangedGoal(int actorId, int newGoal, int oldGoal, bool currentSet) {
}

void SceneScriptHC04::PlayerWalkedIn() {
	if (_vm->_cutContent) {
		Game_Flag_Set(kFlagHC04Visited);
	}
}

void SceneScriptHC04::PlayerWalkedOut() {
	Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
	Ambient_Sounds_Remove_All_Looping_Sounds(1u);
}

void SceneScriptHC04::DialogueQueueFlushed(int a1) {
}

void SceneScriptHC04::dialogueWithIsabella() {
	Dialogue_Menu_Clear_List();
	if (Actor_Clue_Query(kActorMcCoy, kClueKingstonKitchenBox2)
	 || Actor_Clue_Query(kActorMcCoy, kClueKingstonKitchenBox1)
	) {
		// Made it so the deliverymen option will display if you have the bombing suspect photo.
		// It makes no sense for the option to be labelled Sadik photo because in act 2 McCoy hasn't 
		// learned Sadiks name. Instead McCoy will now first ask about the delivery men and when he has no luck with that
		// he shows Isabella the photo.
		// Made it if McCoy hreatens Isabella with jail time none of the other options are available.
		// Also made it so if you have the stolen cheese clue the deliverymen and Eisenduller options disappear since McCoy now knows that it was
		// Gordo who stole that takeout boxes and not Sadik who was delivring them.
		if (_vm->_cutContent) {
			if (Global_Variable_Query(kVariableChapter) < 4) {
				if (Actor_Clue_Query(kActorMcCoy, kClueBombingSuspect)
				&& !Actor_Clue_Query(kActorMcCoy, kClueStolenCheese)) {
					DM_Add_To_List_Never_Repeat_Once_Selected(350, 4, 5, 6); // DELIVERYMEN
				}
			}
		} else if (Actor_Clue_Query(kActorMcCoy, kClueBombingSuspect)) {
			DM_Add_To_List_Never_Repeat_Once_Selected(340, 5, 6, 5); // SADIK PHOTO
		} else if (Actor_Clue_Query(kActorMcCoy, kClueTyrellSecurityPhoto)) {
			DM_Add_To_List_Never_Repeat_Once_Selected(350, 5, 6, 5); // DELIVERYMEN
		}
		if (_vm->_cutContent) {
			if (Global_Variable_Query(kVariableChapter) < 4) {
				if  (!Actor_Clue_Query(kActorMcCoy, kClueStolenCheese)) {
					DM_Add_To_List_Never_Repeat_Once_Selected(360, 5, 6, 7); // MARCUS EISENDULLER
				}
			}		
		} else {
			DM_Add_To_List_Never_Repeat_Once_Selected(360, 6, 4, 3); // MARCUS EISENDULLER
		}
	}
	if (_vm->_cutContent) {
		if (Global_Variable_Query(kVariableChapter) < 4) {
			if ( Actor_Clue_Query(kActorMcCoy, kClueCheese)
			&& !Actor_Clue_Query(kActorMcCoy, kClueSpecialIngredient)) {
				DM_Add_To_List_Never_Repeat_Once_Selected(370, 3, 4, 5); // CHEESE
			}
		}
	} else if ( Actor_Clue_Query(kActorMcCoy, kClueCheese)
	 && !Actor_Clue_Query(kActorMcCoy, kClueSpecialIngredient)
	) {
		DM_Add_To_List_Never_Repeat_Once_Selected(370, 3, 4, 7); // CHEESE
	}
	if (_vm->_cutContent) {
		if (Global_Variable_Query(kVariableChapter) < 4) {
			if (Actor_Clue_Query(kActorMcCoy, kClueSpecialIngredient)) {
				DM_Add_To_List_Never_Repeat_Once_Selected(380, 2, 3, 4); // MIA AND MURRAY INFO
			}
		}
	} else if (Actor_Clue_Query(kActorMcCoy, kClueSpecialIngredient)) {
		DM_Add_To_List_Never_Repeat_Once_Selected(380, -1, 5, 8); // MIA AND MURRAY INFO
	}
	// Made it so McCoy doesn't have the option to buy the stew if he found out about the special ingredient.
	// It would make no sense for McCoy to ask what's in the stew and then buy some of it knowing it contains illegal ingredients.
	if (_vm->_cutContent) {
		if (Global_Variable_Query(kVariableChapter) < 4) {
			if (!Actor_Clue_Query(kActorMcCoy, kClueSpecialIngredient)) {
				DM_Add_To_List_Never_Repeat_Once_Selected(390, 7, 8, 9); // BUY STEW
			}
		}
	} else {
		DM_Add_To_List_Never_Repeat_Once_Selected(390, 7, 5, -1); // BUY STEW	
	}
	Dialogue_Menu_Add_DONE_To_List(400); // DONE

	Dialogue_Menu_Appear(320, 240);
	int answer = Dialogue_Menu_Query_Input();
	Dialogue_Menu_Disappear();

	switch (answer) {
	case 340: // SADIK PHOTO
		Actor_Says(kActorMcCoy, 1285, kAnimationModeTalk);
		Actor_Says(kActorIsabella, 50, kAnimationModeTalk);
		Actor_Says(kActorMcCoy, 1330, kAnimationModeTalk);
		Actor_Says(kActorIsabella, 60, kAnimationModeTalk);
		break;

	case 350: // DELIVERYMEN
		// Altered deliverymen dialogue to also contain the dialogue for the Sadiks photo option.
		if (_vm->_cutContent) {
			if (Actor_Query_Friendliness_To_Other(kActorIsabella, kActorMcCoy) < 50) {
				Actor_Says(kActorMcCoy, 1290, kAnimationModeTalk); //00-1290.AUD	How many delivery men you got working here?
				Delay(2000);
				Actor_Says(kActorMcCoy, 6985, 14); //00-6985.AUD	Got the straight scoop for me or what?
				Delay(1000);
			} else {
				Actor_Says(kActorMcCoy, 1290, kAnimationModeTalk); //00-1290.AUD	How many delivery men you got working here?
			}
			Actor_Says(kActorIsabella, 70, kAnimationModeTalk); //59-0070.AUD	Two. Sometimes three on the busy night.
			Actor_Says(kActorIsabella, 80, kAnimationModeTalk); //59-0080.AUD	Usual two riders. They Chinese. Third guy part timer. He Moroccan I think.
			Actor_Says(kActorMcCoy, 1340, kAnimationModeTalk); //00-1340.AUD	A big guy with dreadlocks?
			Actor_Says(kActorIsabella, 90, kAnimationModeTalk); //59-0090.AUD	Oh no. Shaved head. Real short.
			Actor_Says(kActorMcCoy, 1335, kAnimationModeTalk); //00-1335.AUD	Any Rastafarians?
			Delay(500);
			Actor_Says(kActorMcCoy, 1285, 23); //00-1285.AUD	This guy work for you?
			if (Game_Flag_Query(kFlagSadikIsReplicant)) {
				Actor_Says(kActorIsabella, 50, kAnimationModeTalk);  //59-0050.AUD	No, but I wish he do. He be one fine-looking man.
				Actor_Says(kActorMcCoy, 1330, kAnimationModeTalk); //00-1330.AUD	You sure? Never seen him before?
				Actor_Says(kActorIsabella, 60, kAnimationModeTalk); //59-0060.AUD	I'd remember him for sure.
			} else {
				Delay (2000);
				Actor_Says(kActorMcCoy, 1885, kAnimationModeTalk); //00-1885.AUD	I’ll take that as a yes.
				Delay (500);
				Actor_Says(kActorMcCoy, 875, 17); //00-0875.AUD	Where do I find him?
				Delay (2000);
				Actor_Says(kActorMcCoy, 8395, 18); //00-8395.AUD	You don't have anything to say?
				Delay(1000);
				if (Player_Query_Agenda() != kPlayerAgendaSurly
				&& (Player_Query_Agenda() != kPlayerAgendaErratic)) {
					Actor_Says(kActorMcCoy, 745, 14); //00-0745.AUD	I'm watching you, pal.
				} else {
					Actor_Says(kActorMcCoy, 4360, 16); //00-4360.AUD	Tell it straight or I'm gonna make sure you get the same as he gets. Full conspiracy, payable for 25.
					Delay(2000);	
					Actor_Says(kActorMcCoy, 1955, 14); //00-1955.AUD	We’re taking a little drive downtown.
					Game_Flag_Set(kFlagIsabellaArrested);
					Music_Stop(1u);
					Delay (1000);
					Actor_Put_In_Set(kActorIsabella, kSetPS09);
					Actor_Set_At_XYZ(kActorIsabella, -450.0f, 0.2f, -195.0f, 518);
					Game_Flag_Reset(kFlagSpinnerAtAR01);
					Game_Flag_Set(kFlagSpinnerAtPS01);
					Scene_Exits_Enable();
					Game_Flag_Reset(kFlagMcCoyInHawkersCircle);
					Game_Flag_Set(kFlagMcCoyInPoliceStation);
					Outtake_Play(kOuttakeAway1, true, -1);
					Set_Enter(kSetPS09, kScenePS09);
				}
			}
		} else {
			Actor_Says(kActorMcCoy, 1290, kAnimationModeTalk);
			Actor_Says(kActorIsabella, 70, kAnimationModeTalk);
			Actor_Says(kActorMcCoy, 1335, kAnimationModeTalk);
			Actor_Says(kActorIsabella, 80, kAnimationModeTalk);
			Actor_Says(kActorMcCoy, 1340, kAnimationModeTalk);
			Actor_Says(kActorIsabella, 90, kAnimationModeTalk);
			Actor_Says(kActorMcCoy, 1345, kAnimationModeTalk);
		}
		break;

	case 360: // MARCUS EISENDULLER
		if (_vm->_cutContent) {
			Actor_Says(kActorMcCoy, 1295, kAnimationModeTalk);
			if (Actor_Query_Friendliness_To_Other(kActorIsabella, kActorMcCoy) > 49) {
				Actor_Says(kActorIsabella, 100, kAnimationModeTalk);
				Actor_Says(kActorMcCoy, 1350, kAnimationModeTalk);
				if (Game_Flag_Query(kFlagSadikIsReplicant)) {
					Actor_Says(kActorIsabella, 110, kAnimationModeTalk); //59-0110.AUD	No sir. No deliveries to him no more. Not since last month. He be way behind on his bill.
					Actor_Says(kActorMcCoy, 1355, kAnimationModeTalk);
					Actor_Says(kActorIsabella, 130, kAnimationModeTalk);
					if (Player_Query_Agenda() == kPlayerAgendaPolite) {
						Actor_Says(kActorMcCoy, 1360, kAnimationModeTalk); //00-1360.AUD	You may have a little trouble collecting. He's dead.
						Delay(2000);
						Actor_Says(kActorMcCoy, 2305, 13); //00-2305.AUD	I’m sorry.
						Actor_Modify_Friendliness_To_Other(kActorIsabella, kActorMcCoy, 2);
					} else {
						Actor_Says(kActorMcCoy, 4880, 13); //00-4880.AUD	Is that right?
					}
				} else {
					Delay(2000);
					Actor_Says(kActorMcCoy, 1885, kAnimationModeTalk); //00-1885.AUD	I’ll take that as a yes.
					Delay(2000);
					Actor_Says(kActorMcCoy, 2755, 18);                  // AreYouAlrightALittlePale
					Delay(1000);
					Actor_Says(kActorMcCoy, 8525, kAnimationModeTalk); // generic "hmph"
				}
			} else {
				Delay(2000);
				Actor_Says(kActorMcCoy, 7995, kAnimationModeTalk); //00-7995.AUD	No?
				Delay(2000);
				Actor_Says(kActorMcCoy, 8590, 13);  // Not the talkative type
			}
		} else {
			Actor_Says(kActorMcCoy, 1295, kAnimationModeTalk);
			Actor_Says(kActorIsabella, 100, kAnimationModeTalk);
			Actor_Says(kActorMcCoy, 1350, kAnimationModeTalk);
			Actor_Says(kActorIsabella, 110, kAnimationModeTalk);
			Actor_Says(kActorMcCoy, 1355, kAnimationModeTalk);
			Actor_Says(kActorIsabella, 130, kAnimationModeTalk);
			Actor_Says(kActorMcCoy, 1360, kAnimationModeTalk);
		}
		break;

	case 370: // CHEESE
		Actor_Says(kActorMcCoy, 1300, kAnimationModeTalk);
		Actor_Says(kActorIsabella, 140, kAnimationModeTalk);
		if (_vm->_cutContent) {
			if (Player_Query_Agenda() == kPlayerAgendaPolite) {
				Actor_Says(kActorMcCoy, 1365, kAnimationModeTalk);
			} else if (Player_Query_Agenda() == kPlayerAgendaSurly
			|| (Player_Query_Agenda() == kPlayerAgendaErratic)) {
				Actor_Says(kActorMcCoy, 8519, 14);//00-8519.AUD	What do you say we dish each other the straight goods.
				Actor_Modify_Friendliness_To_Other(kActorIsabella, kActorMcCoy, -2);
			} else {
				Actor_Says(kActorMcCoy, 3910, 16); //00-3910.AUD	You’re lying.
			}
			Actor_Says(kActorIsabella, 150, kAnimationModeTalk);
		} else {
			Actor_Says(kActorMcCoy, 1365, kAnimationModeTalk);
			Actor_Says(kActorIsabella, 150, kAnimationModeTalk);
		}
		break;

	case 380: // MIA AND MURRAY INFO
		Actor_Says(kActorMcCoy, 1305, kAnimationModeTalk);
		if (!_vm->_cutContent) {
			Actor_Modify_Friendliness_To_Other(kActorIsabella, kActorMcCoy, -2);
		}
		Actor_Says(kActorIsabella, 160, kAnimationModeTalk);
		if (_vm->_cutContent) {
			if (Player_Query_Agenda() != kPlayerAgendaPolite) {
				Actor_Says(kActorMcCoy, 1370, kAnimationModeTalk);
				Actor_Says(kActorIsabella, 170, kAnimationModeTalk); //59-0170.AUD	Why you pick on Mama Isabella? I never do you no harm.
				Actor_Modify_Friendliness_To_Other(kActorIsabella, kActorMcCoy, -2);
			}
		} else {
			Actor_Says(kActorMcCoy, 1370, kAnimationModeTalk);
			Actor_Says(kActorIsabella, 170, kAnimationModeTalk); //59-0170.AUD	Why you pick on Mama Isabella? I never do you no harm.
		}
		// Added in some dialogue and made the conversation play out differently based on whether McCoy is surly or erratic.
		// If McCoy is mean Mama Isabella denies all involvement but if McCoy is nice to her she reluctantly tells him the truth.
		if (_vm->_cutContent) {
			Delay (1000);
			if (Player_Query_Agenda() == kPlayerAgendaSurly 
			|| Player_Query_Agenda() == kPlayerAgendaErratic) {
				Actor_Says(kActorMcCoy, 8519, 14); //00-8519.AUD	What do you say we dish each other the straight goods.
				Actor_Says(kActorIsabella, 150, kAnimationModeTalk); //59-0150.AUD	This is a clean place man. Mama Isabella law-abiding soul.
				Actor_Says(kActorMcCoy, 7835, 18); //00-7835.AUD	Is that so?
				Delay (1000);
				Actor_Says(kActorMcCoy, 1955, 14); //00-1955.AUD	We’re taking a little drive downtown.
				Game_Flag_Set(kFlagIsabellaArrested);
				Music_Stop(1u);
				Delay (1000);
				Actor_Put_In_Set(kActorIsabella, kSetPS09);
				Actor_Set_At_XYZ(kActorIsabella, -450.0f, 0.2f, -195.0f, 518);
				Game_Flag_Reset(kFlagSpinnerAtAR01);
				Game_Flag_Set(kFlagSpinnerAtPS01);
				Scene_Exits_Enable();
				Game_Flag_Reset(kFlagMcCoyInHawkersCircle);
				Game_Flag_Set(kFlagMcCoyInPoliceStation);
				Outtake_Play(kOuttakeAway1, true, -1);
				Set_Enter(kSetPS09, kScenePS09);
			} else {
				Actor_Says(kActorMcCoy, 1375, kAnimationModeTalk); //00-1375.AUD	Where did you get it?
				Delay(1000);
				Actor_Says(kActorIsabella, 180, kAnimationModeTalk); //59-0180.AUD	My sister. She got connections.
				Actor_Says(kActorMcCoy, 1380, kAnimationModeTalk);
				Actor_Says(kActorIsabella, 190, kAnimationModeTalk); //59-0190.AUD	She back in Jamaica, mon. Far away from here. She send me cheese once maybe twice a month.
				if (Game_Flag_Query(kFlagSadikIsReplicant)) {
					Actor_Says(kActorIsabella, 210, kAnimationModeTalk); //59-0210.AUD	You know, funny thing you asking about the cheese. Last week this ugly little man, he ran by. Grab whole box of empty takeout cartons right off the counter.
					Actor_Says(kActorIsabella, 240, kAnimationModeTalk);
					Actor_Says(kActorMcCoy, 1385, kAnimationModeTalk);
					Actor_Says(kActorIsabella, 260, kAnimationModeTalk);
					Actor_Says(kActorMcCoy, 1390, kAnimationModeTalk);
					Actor_Says(kActorIsabella, 300, kAnimationModeTalk);
					Actor_Says(kActorIsabella, 310, kAnimationModeTalk);
					Actor_Says(kActorIsabella, 320, kAnimationModeTalk);  //59-0320.AUD	I'm thinking you not really care about the cheese.
					Actor_Clue_Acquire(kActorMcCoy, kClueStolenCheese, false, kActorIsabella);
				} else {
					Actor_Says(kActorIsabella, 320, kAnimationModeTalk); //59-0320.AUD	I'm thinking you not really care about the cheese.
				}
				if (Player_Query_Agenda() == kPlayerAgendaPolite) {
					Actor_Says(kActorMcCoy, 1395, kAnimationModeTalk); //00-1395.AUD	You're right. But I still think you ought to get yourself a different secret ingredient.
					Actor_Says(kActorIsabella, 330, kAnimationModeTalk); //59-0330.AUD	You bet, mon. That cheese’s been nothing but trouble for Mama Isabella.
					Actor_Says(kActorMcCoy, 5150, 18); //00-5150.AUD	One more thing.	
					Actor_Change_Animation_Mode(kActorMcCoy, 23);
					Actor_Change_Animation_Mode(kActorIsabella, 23);
					Delay(800);
					Actor_Clue_Lose(kActorMcCoy, kClueCheese);
					Actor_Clue_Acquire(kActorIsabella, kClueCheese, true, -1);
					Item_Pickup_Spin_Effect_From_Actor(kModelAnimationCheese, kActorIsabella, 0, 0);
					Delay(1500);
					if (Actor_Clue_Query(kActorMcCoy, kClueKingstonKitchenBox1)) {
						Actor_Clue_Lose(kActorMcCoy, kClueKingstonKitchenBox1);
						Actor_Clue_Acquire(kActorIsabella, kClueKingstonKitchenBox1, true, -1);
						Item_Pickup_Spin_Effect_From_Actor(kModelAnimationKingstonKitchenBox, kActorIsabella, 0, 0);
						Delay(1500);
					}
					Actor_Says(kActorMcCoy, 8170, 13); //00-8170.AUD	There you go.
					Delay(1000);
					Actor_Says(kActorMcCoy, 2860, 14); //00-2860.AUD	You take care of yourself.
					Actor_Modify_Friendliness_To_Other(kActorIsabella, kActorMcCoy, 2);			
				} else {
					Actor_Says(kActorMcCoy, 7815, 13); //00-7815.AUD	No.
				}		
			}
		} else {
			Actor_Says(kActorMcCoy, 1375, kAnimationModeTalk); //00-1375.AUD	Where did you get it?
			Actor_Says(kActorIsabella, 180, kAnimationModeTalk); //59-0180.AUD	My sister. She got connections.
			Actor_Says(kActorMcCoy, 1380, kAnimationModeTalk);
			Actor_Says(kActorIsabella, 190, kAnimationModeTalk);
			Actor_Says(kActorIsabella, 210, kAnimationModeTalk);
			Actor_Says(kActorIsabella, 240, kAnimationModeTalk);
			Actor_Says(kActorMcCoy, 1385, kAnimationModeTalk);
			Actor_Says(kActorIsabella, 260, kAnimationModeTalk);
			Actor_Says(kActorMcCoy, 1390, kAnimationModeTalk);
			Actor_Says(kActorIsabella, 300, kAnimationModeTalk);
			Actor_Says(kActorIsabella, 310, kAnimationModeTalk);
			Actor_Says(kActorIsabella, 320, kAnimationModeTalk); //59-0320.AUD	I'm thinking you not really care about the cheese.
			Actor_Says(kActorMcCoy, 1395, kAnimationModeTalk); //00-1395.AUD	You're right. But I still think you ought to get yourself a different secret ingredient.
			Actor_Says(kActorIsabella, 330, kAnimationModeTalk); //59-0330.AUD	You bet, mon. That cheese’s been nothing but trouble for Mama Isabella.
			Actor_Clue_Acquire(kActorMcCoy, kClueStolenCheese, false, kActorIsabella);
		}
		break;

	case 390: // BUY STEW
		if (_vm->_cutContent) {
			Loop_Actor_Walk_To_XYZ(kActorMcCoy, -154.54, 0.31, -441.12, 0, true, false, false);
			Actor_Face_Actor(kActorMcCoy, kActorIsabella, true);
			Actor_Face_Actor(kActorIsabella, kActorMcCoy, true);
			if (Player_Query_Agenda() == kPlayerAgendaPolite) {
				Actor_Says(kActorMcCoy, 1310, kAnimationModeTalk);
			} else {
				Actor_Says(kActorMcCoy, 8990, 12); //00-8990.AUD	What have you got there?
			}
		} else {
			Actor_Says(kActorMcCoy, 1310, kAnimationModeTalk);
			Actor_Modify_Friendliness_To_Other(kActorIsabella, kActorMcCoy, 2);
		}
		// Added in some dialogue. Made it so you actually lose 30 chinyen when you buy the stew. Made it so you
		// receive a kingston kitchen box when you buy the stew.
		Actor_Says(kActorIsabella, 340, kAnimationModeTalk); //59-0340.AUD	Fix you right up. Only 30 chinyen. It put a spring in your step, mon. The ladies they be loving you.
		if (_vm->_cutContent) {
			if (Player_Query_Agenda() != kPlayerAgendaPolite) {
				Delay(1000);
				Actor_Says(kActorMcCoy, 8650, 14); //00-8650.AUD	What smells in there?
				Actor_Says(kActorIsabella, 30, kAnimationModeTalk); //59-0030.AUD	All in special recipe. (laughs) But if I be telling you what's in it, you might be thinking twice about eating it.
				Delay(2000);
				Actor_Says(kActorMcCoy, 1325, 13); //00-1325.AUD	Uh... I'm not that hungry anyway.
				if (Player_Query_Agenda() == kPlayerAgendaSurly 
				|| Player_Query_Agenda() == kPlayerAgendaErratic) {
					Delay(1000);
					Actor_Says(kActorMcCoy, 5685, 15); //00-5685.AUD	Triple-A you ain’t.
					Actor_Modify_Friendliness_To_Other(kActorIsabella, kActorMcCoy, -2);
					Actor_Says(kActorIsabella, 170, kAnimationModeTalk); //59-0170.AUD	Why you pick on Mama Isabella? I never do you no harm.		
				}
			} else {
				Actor_Says(kActorMcCoy, 1320, kAnimationModeTalk); // 00-1320.AUD	Smells good. What is it?
				Actor_Says(kActorIsabella, 30, kAnimationModeTalk); //59-0030.AUD	All in special recipe. (laughs) But if I be telling you what's in it, you might be thinking twice about eating it.
				if (Global_Variable_Query(kVariableChinyen) >= 30
				|| Query_Difficulty_Level() == kGameDifficultyEasy) {
					Actor_Says(kActorMcCoy, 4940, 23); //00-4940.AUD	Okay, let's have it.
					if (Query_Difficulty_Level() != kGameDifficultyEasy) {
						Global_Variable_Decrement(kVariableChinyen, 30);
					}
					Actor_Change_Animation_Mode(kActorMcCoy, 23);
					Actor_Change_Animation_Mode(kActorIsabella, 23);
					Delay(800);
					Item_Pickup_Spin_Effect_From_Actor(kModelAnimationKingstonKitchenBox, kActorMcCoy, 0, 0);
					Delay(800);
					Actor_Modify_Friendliness_To_Other(kActorIsabella, kActorMcCoy, 2);
					Actor_Says(kActorMcCoy, 1345, 13); //00-1345.AUD	Thanks.		
				} else {
					Actor_Says(kActorMcCoy, 1325, 13); //00-1325.AUD/Uh... I'm not that hungry anyway.
				}
			}
		}

		break;

	case 400: // DONE
	// Made it so McCoy responds differently to Isabella based on his friendliness status.
	if (_vm->_cutContent) {
		if (Actor_Clue_Query(kActorMcCoy, kClueStolenCheese)) {
			Actor_Says(kActorMcCoy, 8605, kAnimationModeTalk);//00-8605.AUD	You staying out of trouble, buddy?
		} else if (Player_Query_Agenda() == kPlayerAgendaPolite) {
			Actor_Says(kActorMcCoy, 1315, kAnimationModeTalk); //00-1315.AUD	Thanks for your time.
		} else {
			Actor_Says(kActorMcCoy, 4595, 14); //00-4595.AUD	Stick around. I may not be finished with you.
		}
	} else {
		Actor_Says(kActorMcCoy, 1315, kAnimationModeTalk);
	}
	break;

	default: // never used?
		Actor_Says(kActorMcCoy, 1320, kAnimationModeTalk);
		Actor_Says(kActorIsabella, 30, kAnimationModeTalk);
		Actor_Says(kActorMcCoy, 1325, kAnimationModeTalk);
		Actor_Says(kActorMcCoy, 1345, kAnimationModeTalk);
		break;
	}
}

} // End of namespace BladeRunner
