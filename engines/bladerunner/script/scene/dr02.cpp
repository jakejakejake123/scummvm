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

void SceneScriptDR02::InitializeScene() {
	if (Game_Flag_Query(kFlagDR03toDR02)) {
		Setup_Scene_Information(-1162.0f,  7.18f,  -322.0f, 552);
	} else if (Game_Flag_Query(kFlagDR01toDR02)) {
		Setup_Scene_Information( -835.0f, -0.04f,  -118.0f, 193);
	} else if (Game_Flag_Query(kFlagBB01toDR02)) {
		Setup_Scene_Information(-1258.0f,  7.18f,  -314.0f, 400);
	} else {
		Setup_Scene_Information( 168.78f,  0.16f, -775.72f, 193);
	}

	Scene_Exit_Add_2D_Exit(0, 605,   0, 639, 479, 1);
	Scene_Exit_Add_2D_Exit(1, 222, 176, 279, 314, 0);
	if (Game_Flag_Query(kFlagBB01Available)) {
		Scene_Exit_Add_2D_Exit(2, 95, 0, 148, 292, 0);
	}
	if (_vm->_cutContent) {
		// improved navigation of this set of scenes
		Scene_Exit_Add_2D_Exit(3,  0,   0,  34, 479, 3);
		Scene_Exit_Add_2D_Exit(4, 34, 445, 605, 479, 2);
		// Code for inserting the shoeshine man into the set.
		Actor_Put_In_Set(kActorShoeshineMan, kSetDR01_DR02_DR04);
		Actor_Set_At_XYZ(kActorShoeshineMan, -1160.0f, -0.04f, -235.0f, 524);
	}

	Ambient_Sounds_Remove_All_Non_Looping_Sounds(false);
	Ambient_Sounds_Remove_All_Looping_Sounds(0u);
	// Replaced China town rain with DNA row rain.
	if (_vm->_cutContent) {
		Ambient_Sounds_Add_Looping_Sound(kSfxDRRAIN1, 50,  0, 1);
	} else {
		Ambient_Sounds_Add_Looping_Sound(kSfxCTRAIN1, 50,  0, 1);
	}
	Ambient_Sounds_Add_Looping_Sound(kSfxHUMMER3, 27, 85, 1);
	Ambient_Sounds_Add_Looping_Sound(kSfxBIGFAN2, 38, 85, 1);
	if (_vm->_cutContent) {
		Ambient_Sounds_Add_Looping_Sound(kSfxBIGFAN3, 38, 85, 1);
	}
	Ambient_Sounds_Add_Sound(kSfxTHNDR1, 2,  50, 33, 100, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxTHNDR2, 2,  50, 33, 100, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxTHNDR3, 2,  50, 33, 100, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSPIN2A, 5, 100, 16,  25, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSPIN1A, 5, 100, 16,  25, -100, 100, -101, -101, 0, 0);

	if (Game_Flag_Query(kFlagDR01toDR02)) {
		Scene_Loop_Start_Special(kSceneLoopModeLoseControl, 0, false);
		Scene_Loop_Set_Default(1);
	} else {
		Scene_Loop_Set_Default(1);
	}
}

void SceneScriptDR02::SceneLoaded() {
	Obstacle_Object("TRASH CAN WITH FIRE", true);
	Obstacle_Object("V2PYLON02", true);
	Obstacle_Object("V2PYLON04", true);
	Obstacle_Object("U2 CHEWDOOR", true);
	Obstacle_Object("MMTRASHCAN", true);
	Obstacle_Object("PARKMETR02", true);
	Obstacle_Object("TRANSFORMER 01", true);
	Obstacle_Object("TRANSFORMER 02", true);
	Obstacle_Object("PARKMETR01", true);
	Obstacle_Object("Z2ENTRYDR", true);
	Obstacle_Object("Z2DR2", true);
	// there are two objects named "TRASH CAN WITH FIRE" in the scene (but not visible)
	// and none of them have to be set clickable
	Clickable_Object("TRASH CAN WITH FIRE");
	Clickable_Object("U2 CHEWDOOR");
	Clickable_Object("MMTRASHCAN");
	Clickable_Object("U2 EYE");
	Clickable_Object("U2 E");
	Clickable_Object("MMNEWSP01");
	Clickable_Object("MMNEWSP02");
	Clickable_Object("MMNEWSP04");
	Clickable_Object("MMNEWSP05");
	Clickable_Object("MMNEWSP07");
	Clickable_Object("PARKMETR02");
	Clickable_Object("TRANSFORMER 01");
	Clickable_Object("TRANSFORMER 02");
	Clickable_Object("V2CANPIPE02");
	// there are two objects named "TRASH CAN WITH FIRE" in the scene (but not visible)
	// and none of them have to be set clickable
	// and also resetting them here would only reset one of them - and one remains as clickable
	Unclickable_Object("TRASH CAN WITH FIRE");
	Unclickable_Object("U2 CHEWDOOR");
	Unclickable_Object("MMTRASHCAN");
	if (_vm->_cutContent) {
		if (Game_Flag_Query(kFlagMcCoyCommentsOnEyeOfEyeworks)) {
			Unclickable_Object("U2 EYE");
		}
	} else {
		Unclickable_Object("U2 EYE");
	}
	Unclickable_Object("U2 E");
	Unclickable_Object("MMNEWSP01");
	Unclickable_Object("MMNEWSP02");
	Unclickable_Object("MMNEWSP04");
	Unclickable_Object("MMNEWSP05");
	Unclickable_Object("MMNEWSP07");
	Unclickable_Object("PARKMETR02");
	Unclickable_Object("TRANSFORMER 01");
	Unclickable_Object("TRANSFORMER 02");
	Unclickable_Object("V2CANPIPE02");
}

bool SceneScriptDR02::MouseClick(int x, int y) {
	return false;
}

bool SceneScriptDR02::ClickedOn3DObject(const char *objectName, bool a2) {
	if (_vm->_cutContent) {
		if (!Game_Flag_Query(kFlagMcCoyCommentsOnEyeOfEyeworks)
		    && (Object_Query_Click("U2 EYE", objectName))
		) {
			Game_Flag_Set(kFlagMcCoyCommentsOnEyeOfEyeworks);
			Unclickable_Object("U2 EYE");
			Actor_Voice_Over(660, kActorVoiceOver);
			return true;
		}
	}
	return false;
}

bool SceneScriptDR02::ClickedOnActor(int actorId) {
	// This is the code for when you click on the shoeshine man. Depending on McCoys agenda he will will either be nice to the shoeshine man and give him some money
	// or he will simply tell the shoeshine man to get lost. If McCoy helps the shoeshine man he will give McCoy several clues throughout the game when McCoy interacts with him.   
	if (actorId == kActorShoeshineMan) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -1098.15f, -0.04f, -201.53f, 0, true, false, false)) {
			if (!Game_Flag_Query(kFlagShoeshineManTalk)) {
				Actor_Face_Actor(kActorMcCoy, kActorShoeshineMan, true);
				Actor_Face_Actor(kActorShoeshineMan, kActorMcCoy, true);
				Game_Flag_Set(kFlagShoeshineManTalk);
				Actor_Says(kActorMcCoy, 4870, 23);
				Delay(1000);
				Actor_Says(kActorMcCoy, 8615, 16); //00-8615.AUD	Heard anything on the street?
				Delay(2000);
				Actor_Says(kActorMcCoy, 4515, 13); //00-4515.AUD	What do you know?
				Delay(3000);
				Actor_Says(kActorMcCoy, 8590, 18);//00-8590.AUD	Not the talkative type.
				Delay(2000);
				if (Player_Query_Agenda() == kPlayerAgendaPolite) {
					if (Global_Variable_Query(kVariableChinyen) >= 10
					|| Query_Difficulty_Level() == kGameDifficultyEasy) {
						Global_Variable_Decrement(kVariableChinyen, 10);
						Actor_Says(kActorMcCoy, 340, 13); //00-0340.AUD	You're a pretty smart looking cat.
						Actor_Says(kActorMcCoy, 345, 16); //00-0345.AUD	Wanna make some money?
						Delay(2000);
						Actor_Change_Animation_Mode(kActorMcCoy, 23);
						Delay(2000);
						Actor_Says(kActorMcCoy, 8170, 13); //00-8170.AUD	There you go.
						Delay(3000);
						Actor_Says(kActorMcCoy, 8395, 13); //00-8395.AUD	You don't have anything to say?
						Delay(3000);
						Actor_Says(kActorMcCoy, 2860, 14); //00-2860.AUD	You take care of yourself.
						Delay(2000);
						Actor_Face_Heading(kActorShoeshineMan, 524, false);
						Game_Flag_Set(kFlagMcCoyHelpedShoeshineMan);
					} else {
						Actor_Says(kActorMcCoy, 745, 14); //00-0745.AUD	I'm watching you, pal.
						Delay(2000);
						Actor_Face_Heading(kActorShoeshineMan, 524, false);
					}
				} else { 
					Actor_Says_With_Pause(kActorMcCoy, 735, 1.0f, 14);//00-0735.AUD	Beat it.
					Player_Loses_Control();
					Loop_Actor_Walk_To_XYZ(kActorMcCoy, -921.11f, 0.44f, -155.89f, 0, true, false, false);
					Player_Gains_Control();
					if (Player_Query_Agenda() == kPlayerAgendaSurly 
					|| Player_Query_Agenda() == kPlayerAgendaErratic) { 
						Delay(1000);
						Actor_Face_Actor(kActorMcCoy, kActorShoeshineMan, true);
						Actor_Face_Actor(kActorShoeshineMan, kActorMcCoy, true);
						Delay(2000);
						Actor_Says(kActorMcCoy, 740, 15); //00-0740.AUD	I thought I told you to take a hike.
						Delay(2000);
					}
					Actor_Face_Heading(kActorShoeshineMan, 524, false);	
				}
			} else {
				if (Game_Flag_Query(kFlagMcCoyHelpedShoeshineMan)) {
					Actor_Face_Actor(kActorMcCoy, kActorShoeshineMan, true);
					Actor_Face_Actor(kActorShoeshineMan, kActorMcCoy, true);
					Actor_Says(kActorMcCoy, 3210, kAnimationModeTalk); //00-3210.AUD	Hey, man.
					Delay(1000);
					if (!Actor_Clue_Query(kActorMcCoy, kClueOriginalShippingForm)) {
						Actor_Says(kActorMcCoy, 8990, 17);//00-8990.AUD	What have you got there?
						Actor_Change_Animation_Mode(kActorMcCoy, 23);
						Delay(800);
						Item_Pickup_Spin_Effect_From_Actor(kModelAnimationOriginalShippingForm, kActorMcCoy, 0, 0);
						Delay(800);
						Actor_Clue_Acquire(kActorMcCoy, kClueOriginalShippingForm, true, kActorShoeshineMan);
						Actor_Says(kActorMcCoy, 8805, 13); //00-8805.AUD	A requisition form.
						Delay(1000);
						if (Player_Query_Agenda() == kPlayerAgendaPolite) {
							Actor_Says(kActorMcCoy, 3935, kAnimationModeTalk); //00-3935.AUD	Thanks.
						}
						Actor_Face_Heading(kActorShoeshineMan, 524, false);
					} else if (Game_Flag_Query(kFlagDektoraIsReplicant) 
					&& Global_Variable_Query(kVariableChapter) > 3 
					&& !Actor_Clue_Query(kActorMcCoy, kClueDektoraIncept)) {
						Actor_Says(kActorMcCoy, 8990, 17);//00-8990.AUD	What have you got there?
						Actor_Change_Animation_Mode(kActorMcCoy, 23);
						Delay(800);
						Item_Pickup_Spin_Effect_From_Actor(kModelAnimationPhoto, kActorMcCoy, 0, 0);
						Delay(800);
						Actor_Clue_Acquire(kActorMcCoy, kClueDektoraIncept, true, kActorShoeshineMan);
						Actor_Voice_Over(4090, kActorVoiceOver); //99-4090.AUD	She looks familiar.
						Delay(1000);
						if (Player_Query_Agenda() == kPlayerAgendaPolite) {
							Actor_Says(kActorMcCoy, 3935, kAnimationModeTalk); //00-3935.AUD	Thanks.
						}
						Actor_Face_Heading(kActorShoeshineMan, 524, false);
					} else if (Game_Flag_Query(kFlagGordoIsReplicant) 
					&& Global_Variable_Query(kVariableChapter) > 3 
					&& !Actor_Clue_Query(kActorMcCoy, kClueGordoIncept)) {
						Actor_Says(kActorMcCoy, 8990, 17);//00-8990.AUD	What have you got there?
						Actor_Change_Animation_Mode(kActorMcCoy, 23);
						Delay(800);
						Item_Pickup_Spin_Effect_From_Actor(kModelAnimationPhoto, kActorMcCoy, 0, 0);
						Delay(800);
						Actor_Clue_Acquire(kActorMcCoy, kClueGordoIncept, true, kActorShoeshineMan);
						Actor_Voice_Over(4080, kActorVoiceOver);
						Delay(1000);
						if (Player_Query_Agenda() == kPlayerAgendaPolite) {
							Actor_Says(kActorMcCoy, 3935, kAnimationModeTalk); //00-3935.AUD	Thanks.
						}
						Actor_Face_Heading(kActorShoeshineMan, 524, false);	
					} else if (Game_Flag_Query(kFlagIzoIsReplicant) 
					&& Global_Variable_Query(kVariableChapter) > 2 
					&& !Actor_Clue_Query(kActorMcCoy, kClueIzoIncept)) {
						Actor_Says(kActorMcCoy, 8990, 17);//00-8990.AUD	What have you got there?
						Actor_Change_Animation_Mode(kActorMcCoy, 23);
						Delay(800);
						Item_Pickup_Spin_Effect_From_Actor(kModelAnimationPhoto, kActorMcCoy, 0, 0);
						Delay(800);
						Actor_Clue_Acquire(kActorMcCoy, kClueIzoIncept, true, kActorShoeshineMan);
						Actor_Voice_Over(4080, kActorVoiceOver);
						Delay(1000);
						if (Player_Query_Agenda() == kPlayerAgendaPolite) {
							Actor_Says(kActorMcCoy, 3935, kAnimationModeTalk); //00-3935.AUD	Thanks.
						}
						Actor_Face_Heading(kActorShoeshineMan, 524, false);
					} else if (Game_Flag_Query(kFlagLucyIsReplicant) 
					&& Global_Variable_Query(kVariableChapter) > 1 
					&& !Actor_Clue_Query(kActorMcCoy, kClueLucyIncept)) {
						Actor_Says(kActorMcCoy, 8990, 17);//00-8990.AUD	What have you got there?
						Actor_Change_Animation_Mode(kActorMcCoy, 23);
						Delay(800);
						Item_Pickup_Spin_Effect_From_Actor(kModelAnimationPhoto, kActorMcCoy, 0, 0);
						Delay(800);
						Actor_Clue_Acquire(kActorMcCoy, kClueLucyIncept, true, kActorShoeshineMan);
						Actor_Voice_Over(4090, kActorVoiceOver); //99-4090.AUD	She looks familiar.
						Delay(1000);
						if (Player_Query_Agenda() == kPlayerAgendaPolite) {
							Actor_Says(kActorMcCoy, 3935, kAnimationModeTalk); //00-3935.AUD	Thanks.
						}
						Actor_Face_Heading(kActorShoeshineMan, 524, false);
					} else if (Game_Flag_Query(kFlagZubenIsReplicant) 
					&& Global_Variable_Query(kVariableChapter) > 1 
					&& !Actor_Clue_Query(kActorMcCoy, kClueZubenIncept)) {
						Actor_Says(kActorMcCoy, 8990, 17);//00-8990.AUD	What have you got there?
						Actor_Change_Animation_Mode(kActorMcCoy, 23);
						Delay(800);
						Item_Pickup_Spin_Effect_From_Actor(kModelAnimationPhoto, kActorMcCoy, 0, 0);
						Delay(800);
						Actor_Clue_Acquire(kActorMcCoy, kClueZubenIncept, true, kActorShoeshineMan);
						Actor_Voice_Over(4080, kActorVoiceOver);
						Delay(1000);
						if (Player_Query_Agenda() == kPlayerAgendaPolite) {
							Actor_Says(kActorMcCoy, 3935, kAnimationModeTalk); //00-3935.AUD	Thanks.
						}
						Actor_Face_Heading(kActorShoeshineMan, 524, false);
					} else if (Game_Flag_Query(kFlagSadikIsReplicant) 
					&& Global_Variable_Query(kVariableChapter) > 2 
					&& !Actor_Clue_Query(kActorMcCoy, kClueSadikIncept)) {
						Actor_Says(kActorMcCoy, 8990, 17);//00-8990.AUD	What have you got there?
						Actor_Change_Animation_Mode(kActorMcCoy, 23);
						Delay(800);
						Item_Pickup_Spin_Effect_From_Actor(kModelAnimationPhoto, kActorMcCoy, 0, 0);
						Delay(800);
						Actor_Clue_Acquire(kActorMcCoy, kClueSadikIncept, true, kActorShoeshineMan);
						Actor_Voice_Over(4080, kActorVoiceOver);
						Delay(1000);
						if (Player_Query_Agenda() == kPlayerAgendaPolite) {
							Actor_Says(kActorMcCoy, 3935, kAnimationModeTalk); //00-3935.AUD	Thanks.
						}
						Actor_Face_Heading(kActorShoeshineMan, 524, false);
					} else if (!Actor_Clue_Query(kActorMcCoy, kClueMcCoyIncept)
					&& Global_Variable_Query(kVariableChapter) > 3) {
						Actor_Says(kActorMcCoy, 8990, 17);//00-8990.AUD	What have you got there?
						Actor_Change_Animation_Mode(kActorMcCoy, 23);
						Delay(800);
						Item_Pickup_Spin_Effect_From_Actor(kModelAnimationPhoto, kActorMcCoy, 0, 0);
						Delay(800);
						Actor_Clue_Acquire(kActorMcCoy, kClueMcCoyIncept, true, kActorShoeshineMan);
						Actor_Voice_Over(4240, kActorVoiceOver); //99-4240.AUD	That can't be me.
						Actor_Says(kActorMcCoy, 5850, 14); //00-5850.AUD	Where did you get this?
						Delay(2000);
						Actor_Says(kActorMcCoy, 2750, kAnimationModeTalk); //00-2750.AUD	Okay, I get the picture.
						Actor_Face_Heading(kActorShoeshineMan, 524, false);
					} 
				} else {
					Actor_Face_Actor(kActorMcCoy, kActorShoeshineMan, true);
					Actor_Face_Actor(kActorShoeshineMan, kActorMcCoy, true);
					Actor_Says(kActorMcCoy, 745, 14); //00-0745.AUD	I'm watching you, pal.
					Delay(2000);
					Actor_Face_Heading(kActorShoeshineMan, 524, false);
				}
			}
		}
	}
	return false;
}

bool SceneScriptDR02::ClickedOnItem(int itemId, bool a2) {
	return false;
}

bool SceneScriptDR02::ClickedOnExit(int exitId) {
	if (exitId == 0) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -835.0f, -0.04f, -118.0f, 0, true, false, false)) {
			Async_Actor_Walk_To_XYZ(kActorMcCoy, -727.0f, -0.04f, -118.0f, 0, false);
			Game_Flag_Set(kFlagDR02toDR01);
			Set_Enter(kSetDR01_DR02_DR04, kSceneDR01);
		}
		Ambient_Sounds_Adjust_Looping_Sound(kSfxHUMMER3, 12, -101, 1u);
		Ambient_Sounds_Adjust_Looping_Sound(kSfxBIGFAN2, 14, -101, 1u);
		return true;
	}

	if (_vm->_cutContent
	    && (exitId == 3 || exitId == 4)) {
	    if ((exitId == 3 && !Loop_Actor_Walk_To_XYZ(kActorMcCoy, -1162.45f, 0.78f, -167.45f, 0, true, false, false))
		    || (exitId == 4 && !Loop_Actor_Walk_To_XYZ(kActorMcCoy, -975.17f, 0.42f, -120.04f, 0, true, false, false))
		) {
			if (exitId == 3) {
				Async_Actor_Walk_To_XYZ(kActorMcCoy, -1176.40f, 0.58f, -86.02f, 0, false);
			} else {
				Async_Actor_Walk_To_XYZ(kActorMcCoy, -845.00f, 0.37f, -31.60f, 0, false);
			}
			Game_Flag_Set(kFlagDR02toDR01);
			Set_Enter(kSetDR01_DR02_DR04, kSceneDR01);
		}
		Ambient_Sounds_Adjust_Looping_Sound(kSfxHUMMER3, 12, -101, 1u);
		Ambient_Sounds_Adjust_Looping_Sound(kSfxBIGFAN2, 14, -101, 1u);
		return true;
	}


	if (exitId == 1) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -1162.0f, 7.18f, -322.0f, 0, true, false, false)) {
			// Made it so you can enter Chews place in act 3 and the scene with him giving you the data plays. Once it plays McCoy exits the place and the door is now locked.
			if (_vm->_cutContent) {	
				if (Game_Flag_Query(kFlagChewTalkGiveData)
				|| (Global_Variable_Query(kVariableChapter) > 3)) {
					Actor_Says(kActorMcCoy, 7815, 13); //00-7815.AUD	No.
				} else {
					Game_Flag_Set(kFlagDR02toDR03);
					Set_Enter(kSetDR03, kSceneDR03);
				}
			} else {
				if (Global_Variable_Query(kVariableChapter) > 2) {
					Actor_Says(kActorMcCoy, 8522, 15);
				} else {
					Game_Flag_Set(kFlagDR02toDR03);
					Set_Enter(kSetDR03, kSceneDR03);
				}
			}
		}
		return true;
	}

	if (exitId == 2) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -1258.0f, 7.18f, -314.0f, 0, true, false, false)) {
			Game_Flag_Set(kFlagDR02toBB01);
			Game_Flag_Reset(kFlagMcCoyInDNARow);
			Game_Flag_Set(kFlagMcCoyInBradburyBuilding);
			Set_Enter(kSetBB01, kSceneBB01);
		}
		return true;
	}
	return false;
}

bool SceneScriptDR02::ClickedOn2DRegion(int region) {
	return false;
}

void SceneScriptDR02::SceneFrameAdvanced(int frame) {
	if (frame == 1) {
		Sound_Play(kSfxSTEAM1, 10, 85, 85, 50);
	}
}

void SceneScriptDR02::ActorChangedGoal(int actorId, int newGoal, int oldGoal, bool currentSet) {
}

void SceneScriptDR02::PlayerWalkedIn() {
	if (Game_Flag_Query(kFlagDR03toDR02)) {
		Game_Flag_Reset(kFlagDR03toDR02);
	}
	if (Game_Flag_Query(kFlagDR01toDR02)) {
		Game_Flag_Reset(kFlagDR01toDR02);
	}
	if (Game_Flag_Query(kFlagBB01toDR02)) {
		Game_Flag_Reset(kFlagBB01toDR02);
	}
}

void SceneScriptDR02::PlayerWalkedOut() {
}

void SceneScriptDR02::DialogueQueueFlushed(int a1) {
}

} // End of namespace BladeRunner
