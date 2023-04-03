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

enum kNR05Loops {
	kNR05LoopPanFromNR08 = 0,
	kNR05LoopMainLoop    = 1,
	kNR05LoopTableSwivel = 3
};


void SceneScriptNR05::InitializeScene() {
	if (Game_Flag_Query(kFlagNR08toNR05)) {
		Scene_Loop_Start_Special(kSceneLoopModeLoseControl, kNR05LoopPanFromNR08, false);
		Scene_Loop_Set_Default(kNR05LoopMainLoop);
#if BLADERUNNER_ORIGINAL_BUGS
		Setup_Scene_Information(-777.56f,  0.0f, -166.86f,   0);
#else
		Setup_Scene_Information(-752.09f, 0.0f, -193.58f, 258);
#endif // BLADERUNNER_ORIGINAL_BUGS
	} else if (Game_Flag_Query(kFlagNR03toNR05)) {
		Setup_Scene_Information( -456.0f,  0.0f,  -611.0f,   0);
	} else {
		Setup_Scene_Information( -527.0f, 1.57f,  -406.0f, 649);
	}

	Scene_Exit_Add_2D_Exit(0, 459, 147, 639, 290, 1);
	if (Game_Flag_Query(kFlagNR08Available)) {
		Scene_Exit_Add_2D_Exit(1, 0, 0, 30, 479, 3);
	}

	Ambient_Sounds_Add_Looping_Sound(kSfxBARAMB1, 50, 38, 0);
	Ambient_Sounds_Add_Sound(kSfxBARSFX1,  3, 60, 20, 20,  -30,  30, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBARSFX3,  3, 60, 20, 20,  -30,  30, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBARSFX4,  3, 60, 20, 20,  -30,  30, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBARSFX5,  3, 60, 20, 20,  -30,  30, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBARSFX6,  3, 60, 20, 20,  -30,  30, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBARSFX7,  3, 60, 20, 20,  -30,  30, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxCLINK1,   3, 60, 25, 25, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxCLINK2,   3, 60, 25, 25, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxCLINK3,   3, 60, 25, 25, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxCLINK4,   3, 60, 25, 25, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxFEMORG1,  5, 70, 11, 11, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxFEMORG2,  5, 70, 11, 11, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxFEMORG3,  5, 70, 11, 11, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxFEMORG4,  5, 70, 11, 11, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0480R, 5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0540R, 5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0560R, 5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0870R, 5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0900R, 5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0940R, 5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_1070R, 5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_1080R, 5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_1160R, 5, 70, 12, 12, -100, 100, -101, -101, 0, 0);

	if (Game_Flag_Query(kFlagNR08toNR05)) {
		Scene_Loop_Start_Special(kSceneLoopModeLoseControl, kNR05LoopPanFromNR08, false);
		Scene_Loop_Set_Default(kNR05LoopMainLoop);
	} else if (Game_Flag_Query(kFlagNR03toNR05)) {
		Scene_Loop_Start_Special(kSceneLoopModeLoseControl, kNR05LoopTableSwivel, false);
		Scene_Loop_Set_Default(kNR05LoopMainLoop);
		Game_Flag_Reset(kFlagNR03toNR05);
	} else {
		Scene_Loop_Set_Default(kNR05LoopMainLoop);
	}
}

void SceneScriptNR05::SceneLoaded() {
	Obstacle_Object("NM1-1+", true);
#if BLADERUNNER_ORIGINAL_BUGS
#else
	Obstacle_Object("CUSTLFTBLOCK", true);
#endif // BLADERUNNER_ORIGINAL_BUGS
	Clickable_Object("NM1-1+");
	Unclickable_Object("NM1-1+");
}

bool SceneScriptNR05::MouseClick(int x, int y) {
	return false;
}

bool SceneScriptNR05::ClickedOn3DObject(const char *objectName, bool a2) {
	return false;
}

bool SceneScriptNR05::ClickedOnActor(int actorId) {
	if (actorId == kActorEarlyQBartender) {
		if (_vm->_cutContent) {
			if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -656.61f, 0.41f, -399.82f, 0, true, false, false)) {
				talkToBartender();
			}
		} else {
			if (!Loop_Actor_Walk_To_Actor(kActorMcCoy, kActorEarlyQBartender, 120, true, false)) {
				talkToBartender();
			}
		}
		return true;
	}

	if (actorId == kActorEarlyQ) {
		Actor_Set_Goal_Number(kActorEarlyQ, kGoalEarlyQNR05TalkingToMcCoy);
		if (!Loop_Actor_Walk_To_Actor(kActorMcCoy, kActorEarlyQ, 36, true, false)) {
			talkToEarlyQ();
		}
		Actor_Set_Goal_Number(kActorEarlyQ, kGoalEarlyQNR05WillLeave);
		return true;
	}

	return false;
}

bool SceneScriptNR05::ClickedOnItem(int itemId, bool a2) {
	return false;
}

bool SceneScriptNR05::ClickedOnExit(int exitId) {
	if (exitId == 0) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -444.0f, 0.0f, -451.0f, 0, true, false, false)) {
			Player_Loses_Control();
			Music_Stop(2u);
			Player_Set_Combat_Mode(false);
			Actor_Face_Heading(kActorMcCoy, 1021, false);
			Actor_Change_Animation_Mode(kActorMcCoy, kAnimationModeSit);
			Game_Flag_Set(kFlagNR05toNR03);
			Set_Enter(kSetNR03, kSceneNR03);
			Scene_Loop_Start_Special(kSceneLoopModeChangeSet, kNR05LoopTableSwivel, false);
		}
		return true;
	}

	if (exitId == 1) {
#if BLADERUNNER_ORIGINAL_BUGS
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -777.56f, 0.0f, -166.86f, 0, true, false, false)) {
			Game_Flag_Set(kFlagNR05toNR08);
			Set_Enter(kSetNR05_NR08, kSceneNR08);
		}
#else
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -752.09f, 0.0f, -193.58f, 0, true, false, false)) {
			Game_Flag_Set(kFlagNR05toNR08);
			Set_Enter(kSetNR05_NR08, kSceneNR08);
		}
#endif // BLADERUNNER_ORIGINAL_BUGS
		return true;
	}
	return false;
}

bool SceneScriptNR05::ClickedOn2DRegion(int region) {
	return false;
}

void SceneScriptNR05::SceneFrameAdvanced(int frame) {
	if (!Music_Is_Playing()) {
		playNextMusic();
	}

	if (frame == 78) {
		Sound_Play(kSfxDORSLID1, 83, 70, 70, 50);
	}

	if (frame == 86) {
		Sound_Play(kSfxMAGMOVE2, 62, 70, 70, 50);
	}

	rotateActorOnGround(kActorHysteriaPatron2);
	if (_vm->_cutContent) {
		rotateActorOnGround(kActorHysteriaPatron3);
	}
	rotateActorOnGround(kActorMcCoy);

	if (Actor_Query_Goal_Number(kActorEarlyQ) == kGoalEarlyQNR05UnlockNR08) {
		Actor_Set_Goal_Number(kActorEarlyQ, kGoalEarlyQNR05UnlockedNR08);
		if (Player_Query_Current_Scene() == kSceneNR05) {
			Scene_Exit_Add_2D_Exit(1, 0, 0, 30, 479, 3);
		}
	}

	if (frame > 77 && frame <= 134) {
		rotateActorOnTable(frame - 13);
		if ( frame == 134 && !Game_Flag_Query(kFlagNR05toNR03)) {
			Actor_Set_Goal_Number(kActorMcCoy, kGoalMcCoyNRxxSitAtTable);
		}
		//return true;
	}
	//return false;
}

void SceneScriptNR05::ActorChangedGoal(int actorId, int newGoal, int oldGoal, bool currentSet) {
}

void SceneScriptNR05::PlayerWalkedIn() {
	if (Game_Flag_Query(kFlagNR08toNR05)) {
		Music_Stop(2u);
		Loop_Actor_Walk_To_XYZ(kActorMcCoy, -697.56f, 0.0f, -174.86f, 0, true, false, false);
		Game_Flag_Reset(kFlagNR08toNR05);
	}
	//	return false;
}

void SceneScriptNR05::PlayerWalkedOut() {
	if (Game_Flag_Query(kFlagNR05toNR03)) {
		Music_Stop(2u);
	}
	Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
	Ambient_Sounds_Remove_All_Looping_Sounds(1u);
}

void SceneScriptNR05::DialogueQueueFlushed(int a1) {
}

void SceneScriptNR05::rotateActorOnTable(int frame) {
	float angle = cos((frame - 65) * (M_PI / 57.0f)) * M_PI_2;
	float invertedAngle = M_PI - angle;
	if (!Game_Flag_Query(kFlagNR05toNR03)) {
		angle = angle + M_PI;
		invertedAngle = invertedAngle + M_PI;
	}
	float c = cos(invertedAngle);
	float s = sin(invertedAngle);
	float x = 6.0f * s - 80.0f * c + -450.0f;
	float z = 80.0f * s + 6.0f * c + -531.0f;

	int facing = angle * (512.0f / M_PI);
	facing = facing + 765;
	if (facing < 0) {
		facing = facing + 1789;
	}
	if (facing > 1023) {
		facing -= 1024;
	}
	Actor_Set_At_XYZ(kActorMcCoy, x, 0.0f, z, facing);
}

void SceneScriptNR05::talkToBartender() {
	Actor_Face_Actor(kActorMcCoy, kActorEarlyQBartender, true);
	Actor_Face_Actor(kActorEarlyQBartender, kActorMcCoy, true);
	if (!Game_Flag_Query(kFlagNR05BartenderTalk1)) {
		Actor_Says(kActorEarlyQBartender, 0, 13);
		Actor_Says(kActorMcCoy, 3470, kAnimationModeTalk);
		Actor_Says(kActorEarlyQBartender, 10, 23);
		Game_Flag_Set(kFlagNR05BartenderTalk1);
		if (_vm->_cutContent) {
			if (Global_Variable_Query(kVariableChinyen) >= 5
			|| Query_Difficulty_Level() == kGameDifficultyEasy) {
				Actor_Change_Animation_Mode(kActorMcCoy, 23);
				Actor_Change_Animation_Mode(kActorEarlyQBartender, 23);
				Delay(1500);
				Actor_Change_Animation_Mode(kActorMcCoy, 75);
				Global_Variable_Increment(kVariableMcCoyDrinks, 1);
				if (Query_Difficulty_Level() != kGameDifficultyEasy) {
					Global_Variable_Decrement(kVariableChinyen, 5);
				}
			} else {
				Actor_Says(kActorMcCoy, 125, 13); //00-0125.AUD	I'm a little strapped for cash right now.
			}
		} else {
			Actor_Change_Animation_Mode(kActorMcCoy, 75);
			Global_Variable_Increment(kVariableMcCoyDrinks, 1);
		}
	} else if (!Game_Flag_Query(kFlagNR05BartenderTalk2)) {
		Actor_Says(kActorMcCoy, 3475, 17);
		Actor_Says(kActorEarlyQBartender, 20, 23);
		Game_Flag_Set(kFlagNR05BartenderTalk2);
		if (_vm->_cutContent) {
			if (Global_Variable_Query(kVariableChinyen) >= 5
			|| Query_Difficulty_Level() == kGameDifficultyEasy) {
				Actor_Change_Animation_Mode(kActorMcCoy, 23);
				Actor_Change_Animation_Mode(kActorEarlyQBartender, 23);
				Delay(1500);
				Actor_Change_Animation_Mode(kActorMcCoy, 75);
				Global_Variable_Increment(kVariableMcCoyDrinks, 1);
				if (Query_Difficulty_Level() != kGameDifficultyEasy) {
					Global_Variable_Decrement(kVariableChinyen, 5);
				}
			} else {
				Actor_Says(kActorMcCoy, 125, 13); //00-0125.AUD	I'm a little strapped for cash right now.
			}
		} else {
			Actor_Change_Animation_Mode(kActorMcCoy, 75);
			Global_Variable_Increment(kVariableMcCoyDrinks, 1);
		}
	} else {
		if (_vm->_cutContent) {
			if (!Actor_Clue_Query(kActorMcCoy, kClueFlaskOfAbsinthe)) {
				Actor_Says(kActorMcCoy, 3480, 19);
				Delay(1000);		
				Actor_Says(kActorMcCoy, 8990, 14); //00-8990.AUD	What have you got there?
				Delay(1000);
				Actor_Says(kActorMcCoy, 8880, 13); //00-8880.AUD	A flask of absinthe.
				Delay(1000);
				if (Global_Variable_Query(kVariableChinyen) >= 20
				|| Query_Difficulty_Level() == kGameDifficultyEasy) {
					Actor_Says(kActorMcCoy, 4940, 18); //00-4940.AUD	Okay, let's have it.
					Actor_Change_Animation_Mode(kActorEarlyQBartender, 23);
					Actor_Change_Animation_Mode(kActorMcCoy, 23);
					Delay(800);
					Item_Pickup_Spin_Effect_From_Actor(kModelAnimationFlaskOfAbsinthe, kActorMcCoy, 0, 0);
					Actor_Clue_Acquire(kActorMcCoy, kClueFlaskOfAbsinthe, true, kActorEarlyQBartender);
					if (Query_Difficulty_Level() != kGameDifficultyEasy) {
						Global_Variable_Decrement(kVariableChinyen, 20);
					}
					Delay(800);
				} else {
					Actor_Says(kActorMcCoy, 125, 13); //00-0125.AUD	I'm a little strapped for cash right now.
				}	
			} else {
				Actor_Says(kActorMcCoy, 3480, 19);
				Actor_Says(kActorEarlyQBartender, 30, 12);
				Actor_Says(kActorMcCoy, 3485, kAnimationModeTalk);
				Actor_Says(kActorEarlyQBartender, 40, 13);
				if (Global_Variable_Query(kVariableChinyen) >= 5
				|| Query_Difficulty_Level() == kGameDifficultyEasy) {
					if (Player_Query_Agenda() != kPlayerAgendaPolite) {
						Actor_Says(kActorMcCoy, 3490, kAnimationModeTalk); //00-3490.AUD	Here’s what I need.
						Actor_Says(kActorMcCoy, 3330, kAnimationModeTalk); //00-3330.AUD	Single orange. Straight up.
					}
					Actor_Change_Animation_Mode(kActorMcCoy, 23);
					Actor_Change_Animation_Mode(kActorEarlyQBartender, 23);
					Delay(1500);
					Actor_Change_Animation_Mode(kActorMcCoy, 75);
					Global_Variable_Increment(kVariableMcCoyDrinks, 1);
					if (Query_Difficulty_Level() != kGameDifficultyEasy) {
						Global_Variable_Decrement(kVariableChinyen, 5);
					}
				} else {
					Actor_Says(kActorMcCoy, 125, 13); //00-0125.AUD	I'm a little strapped for cash right now.
				}
			}
		} else {
			Actor_Says(kActorMcCoy, 3480, 19);
			Actor_Says(kActorEarlyQBartender, 30, 12);
			Actor_Says(kActorMcCoy, 3485, kAnimationModeTalk);
			Actor_Says(kActorEarlyQBartender, 40, 13);
			Actor_Change_Animation_Mode(kActorEarlyQBartender, 23);
			Actor_Change_Animation_Mode(kActorMcCoy, 75);
			Global_Variable_Increment(kVariableMcCoyDrinks, 1);
		}
	}
}

void SceneScriptNR05::talkToEarlyQ() {
	if (Actor_Query_Goal_Number(kActorEarlyQ) == kGoalEarlyQNR05Wait) {
		Actor_Set_Goal_Number(kActorEarlyQ, kGoalEarlyQNR05WillLeave);
	}

	Actor_Face_Actor(kActorMcCoy, kActorEarlyQ, true);
	Actor_Face_Actor(kActorEarlyQ, kActorMcCoy, true);

	if (!Game_Flag_Query(kFlagNR05EarlyQTalk)) {
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagEarlyQIsReplicant)) {
				Actor_Says(kActorMcCoy, 8513, kAnimationModeTalk); //00-8513.AUD	Early, how's it hanging?
				Actor_Says(kActorEarlyQ, 360, kAnimationModeTalk);
				if (Game_Flag_Query(kFlagHanoiTalk)) {
					Actor_Says(kActorMcCoy, 3495, 11); //00-3495.AUD	Your man gave me a hard time out there.
					Actor_Says(kActorEarlyQ, 370, 15); //18-0370.AUD	I like Hanoi but I can’t deny his sphincter is a little tight.
				}
				Actor_Says(kActorMcCoy, 3500, 17); //00-3500.AUD	What’s on tap tonight?
				Actor_Says(kActorEarlyQ, 380, 13);
				Game_Flag_Set(kFlagNR05EarlyQTalk);
			} else {
				Actor_Says(kActorMcCoy, 3520, kAnimationModeTalk); //00-3520.AUD	Hey, Early.
				Actor_Says(kActorMcCoy, 8605, 14); //00-8605.AUD	You staying out of trouble, buddy?.
				Actor_Says(kActorEarlyQ, 750, 18); //18-0750.AUD	Look, General. No reason to get your panties in a bind. If I’d known you were gonna get so testy, I would have tossed you the straight dope to begin with.
				if (Player_Query_Agenda() == kPlayerAgendaSurly 
				|| Player_Query_Agenda() == kPlayerAgendaErratic) {
					Actor_Says(kActorMcCoy, 4940, 13); //00-4940.AUD	Okay, let's have it.
					Actor_Change_Animation_Mode(kActorMcCoy, 23);
					Actor_Change_Animation_Mode(kActorEarlyQ, 23);
					Delay(2000);
					Actor_Change_Animation_Mode(kActorMcCoy, 75);
					Delay(1000);
					Ambient_Sounds_Play_Sound(kSfxDRUGOUT, 50, 99, 0, 0);
					Delay(6000);
				} else {
					Actor_Says(kActorMcCoy, 3390, 14); //00-3390.AUD	Not interested.
					Actor_Says(kActorEarlyQ, 110, 18);
					Actor_Says(kActorMcCoy, 9045, 14); //00-9045.AUD	Not these days.
					Delay(1000);
				}
				Actor_Says(kActorMcCoy, 8615, 16); //00-8615.AUD	Heard anything on the street?
				Actor_Says(kActorEarlyQ, 700, kAnimationModeTalk); //18-0700.AUD	I heard some things, yeah. I’m the kind of guy people confide in, you know.
				if (Player_Query_Agenda() != kPlayerAgendaSurly 
				&& Player_Query_Agenda() != kPlayerAgendaErratic) {
					Actor_Says(kActorMcCoy, 4880, 13); //00-4880.AUD	Is that right?
				} else {
					Actor_Says(kActorMcCoy, 2485, 18); //00-2485.AUD	I’ve a hard time believing that.
				}
				Game_Flag_Set(kFlagNR05EarlyQTalk);
			}
		} else {
			Actor_Says(kActorMcCoy, 8513, kAnimationModeTalk);
			Actor_Says(kActorEarlyQ, 360, kAnimationModeTalk);
			Actor_Says(kActorMcCoy, 3495, 11); //00-3495.AUD	Your man gave me a hard time out there.
			Actor_Says(kActorEarlyQ, 370, 15); //18-0370.AUD	I like Hanoi but I can’t deny his sphincter is a little tight.
			Actor_Says(kActorMcCoy, 3500, 17);
			Actor_Says(kActorEarlyQ, 380, 13);
			Game_Flag_Set(kFlagNR05EarlyQTalk);
		}
		return;
	}

	Dialogue_Menu_Clear_List();
	if (Actor_Query_Friendliness_To_Other(kActorEarlyQ, kActorMcCoy) >= 48) {
		if (Actor_Clue_Query(kActorMcCoy, kClueDragonflyCollection)
		|| Actor_Clue_Query(kActorMcCoy, kClueCollectionReceipt)) {
			if (!Actor_Clue_Query(kActorMcCoy, kClueEarlyInterviewB1)) {
				if (_vm->_cutContent) {
					DM_Add_To_List_Never_Repeat_Once_Selected(890, 6, 7, 8); // JEWELRY
				} else {
					DM_Add_To_List_Never_Repeat_Once_Selected(890, -1, 4, 8); // JEWELRY
				}
			}
		}
		// Made it you can now ask Early Q about Lucy even if you don't have her photo.
		if (_vm->_cutContent) {
			if (Actor_Clue_Query(kActorMcCoy, kClueHysteriaToken)) {
				if (Actor_Query_Goal_Number(kActorLucy) != kGoalLucyGone
				&& Global_Variable_Query(kVariableAffectionTowards) != kAffectionTowardsLucy)  {
					DM_Add_To_List_Never_Repeat_Once_Selected(900, 5, 6, 5); // LUCY
				}
			}
		} else if (Actor_Clue_Query(kActorMcCoy, kClueLucy)
		&& Actor_Query_Goal_Number(kActorLucy) != kGoalLucyGone) {
			DM_Add_To_List_Never_Repeat_Once_Selected(900, 5, 6, 5); // LUCY
		}
		// Made it so the blonde woman option is now available if you have either the China bar photo or the woman in animoid row photo.
		// Also made it so this option is only available if you also talked to Early Q about the jewelry. This is because Early Q mentions giving the jewelry to 'Hecuba'
		// in this conversation which is a follow up of the previous conversation where he mentions giving the jewelry to one of his dancers.
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagDektoraIdentified)) {
				if (Actor_Clue_Query(kActorMcCoy, kClueChinaBar)
				|| Actor_Clue_Query(kActorMcCoy, kClueWomanInAnimoidRow)) {
					// TODO A bug? kClueDektorasDressingRoom is acquired from EarlyQ
					// at his office (nr04) while being threatened by McCoy.
					// At which point EarlyQ already tells McCoy who the people on the photograph are.
					// It makes no sense that McCoy will next find EarlyQ at the VIP area (this area, nr05)
					// and casually ask him about who the woman is in this photo.
					// (McCoy won't be able to even find EarlyQ there again).
					// Maybe it's another photo of Dektora needed here
					// --- Animoid Row? Why would McCoy suspect that woman?
					// --- Hawker's Bar? Can we find a Dektora pic in SHP resources?
					DM_Add_To_List_Never_Repeat_Once_Selected(910, 5, 5, 5); // BLOND WOMAN
				}
			}
		}
	}

	if (!Dialogue_Menu_Query_List_Size()) {
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagEarlyQIsReplicant)) {
				Actor_Says(kActorMcCoy, 3520, kAnimationModeTalk); //00-3520.AUD	Hey, Early.
			}
		} else {
			Actor_Says(kActorMcCoy, 3520, kAnimationModeTalk); //00-3520.AUD	Hey, Early.
		}
		// Added in some banter dialogue. 
		if (_vm->_cutContent) {
			Actor_Says(kActorMcCoy, 8514, kAnimationModeTalk); //00-8514.AUD	Got anything new to tell me?
			Actor_Says(kActorEarlyQ, 710, kAnimationModeTalk); //18-0710.AUD	The only thing I’ve heard lately is that ol’ moan of pleasure from an ultra-vixen, if you know what I mean.
			if (Player_Query_Agenda() != kPlayerAgendaPolite 
			|| !Game_Flag_Query(kFlagEarlyQIsReplicant)) {
				Actor_Says(kActorMcCoy, 3910, kAnimationModeTalk); //00-3910.AUD	You’re lying.
				Actor_Says(kActorEarlyQ, 740, kAnimationModeTalk); //18-0740.AUD	Hey, would this face lie to you?
				Delay(500);
				if (!Game_Flag_Query(kFlagEarlyQIsReplicant)) {
					Actor_Says(kActorMcCoy, 1025, 13); //00-1025.AUD	Absolutely.
					Delay(2000);
				}
			}
			Actor_Says(kActorMcCoy, 5150, kAnimationModeTalk); //00-5150.AUD	One more thing.
		}
		Actor_Says(kActorEarlyQ, 730, kAnimationModeTalk); //18-0730.AUD	I’m working right now, General. Ask me later.
		Actor_Face_Heading(kActorEarlyQ, 849, false);
		return;
	}

	Dialogue_Menu_Add_DONE_To_List(100); // DONE

	Dialogue_Menu_Appear(320, 240);
	int answer = Dialogue_Menu_Query_Input();
	Dialogue_Menu_Disappear();

	switch (answer) {
	case 890: // JEWELRY
		Actor_Says(kActorMcCoy, 3505, kAnimationModeTalk);
		// Made it so Early Q will be resistant to answering McCoys question about the jewelry if he is a replicant. In fact Early Q won't answer the question at all if he is a rep.
		// However if Early Q is human he will answer McCoys question about the jewelry, he won't even resist.
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagEarlyQIsReplicant)) {
				Actor_Says(kActorEarlyQ, 420, 12); //18-0420.AUD	Who’s asking?
				Actor_Says(kActorEarlyQ, 430, 13); //18-0430.AUD	You ain’t with Robbery-Homicide.
				Actor_Says(kActorMcCoy, 3530, 15); //00-3530.AUD	No, sir.
				Actor_Says(kActorEarlyQ, 730, kAnimationModeTalk); //18-0730.AUD	I’m working right now, General. Ask me later.
				if (Player_Query_Agenda() == kPlayerAgendaSurly
				|| (Player_Query_Agenda() == kPlayerAgendaErratic)) {
					Actor_Says(kActorMcCoy, 8519, 14);//00-8519.AUD	What do you say we dish each other the straight goods.
					Delay(2000);
					Actor_Says(kActorMcCoy, 8445, 14); //00-8445.AUD	Cough it up!
					Delay(1000);
					Actor_Says(kActorEarlyQ, 440, 15); //18-0440.AUD	Eh, those pieces ain’t hot. I got the papers to prove it. I picked them up at a legitimate auction. Cost me nearly a pound of flesh too.
					Actor_Says(kActorMcCoy, 3535, 13);
					Actor_Says(kActorEarlyQ, 460, 16); //18-0460.AUD	You kiddin’? I ain’t that stupid. No, no, no, no. I was letting one of my dancers use the stuff in her act. Kind of a tribute to the ancient swamp lands, you know what I mean?
					Actor_Says(kActorMcCoy, 3540, 15);
					Actor_Says(kActorEarlyQ, 490, 16); //18-0490.AUD	Hecuba. She’s going on in a few.
					Actor_Says(kActorEarlyQ, 500, 13); //18-0500.AUD	She’s one of my biggest earners too. She ain’t in any trouble now, is she?
					if (!Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)
					|| Player_Query_Agenda() != kPlayerAgendaPolite) {
						Actor_Says(kActorMcCoy, 3545, 15);
					} else {
						Actor_Says(kActorMcCoy, 7815, 15); //00-7815.AUD	No.
					}
					Actor_Says(kActorEarlyQ, 520, 12); //18-0520.AUD	(sighs) Good, good. Wouldn’t wanna slaughter the goose that lays them golden eggs.
					Actor_Clue_Acquire(kActorMcCoy, kClueEarlyInterviewA, true, kActorEarlyQ);
				}
			} else {
				Actor_Says(kActorEarlyQ, 440, 15); //18-0440.AUD	Eh, those pieces ain’t hot. I got the papers to prove it. I picked them up at a legitimate auction. Cost me nearly a pound of flesh too.
				Actor_Says(kActorMcCoy, 3535, 13);
				Actor_Says(kActorEarlyQ, 460, 16); //18-0460.AUD	You kiddin’? I ain’t that stupid. No, no, no, no. I was letting one of my dancers use the stuff in her act. Kind of a tribute to the ancient swamp lands, you know what I mean?
				Actor_Says(kActorMcCoy, 3540, 15);
				Actor_Says(kActorEarlyQ, 490, 16); //18-0490.AUD	Hecuba. She’s going on in a few.
				Actor_Says(kActorEarlyQ, 500, 13); //18-0500.AUD	She’s one of my biggest earners too. She ain’t in any trouble now, is she?
				if (!Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)
				|| Player_Query_Agenda() != kPlayerAgendaPolite) {
					Actor_Says(kActorMcCoy, 3545, 15);
				} else {
					Actor_Says(kActorMcCoy, 7815, 15); //00-7815.AUD	No.
				}
				Actor_Says(kActorEarlyQ, 520, 12); //18-0520.AUD	(sighs) Good, good. Wouldn’t wanna slaughter the goose that lays them golden eggs.
				Actor_Clue_Acquire(kActorMcCoy, kClueEarlyInterviewA, true, kActorEarlyQ);
			}
			Game_Flag_Set(kFlagEarlyQTalkJewelry);
			Actor_Face_Heading(kActorEarlyQ, 849, false);
		} else {
			Actor_Modify_Friendliness_To_Other(kActorEarlyQ, kActorMcCoy, -1);
			Actor_Says(kActorEarlyQ, 420, 12); //18-0420.AUD	Who’s asking?
			Actor_Says(kActorEarlyQ, 430, 13); //18-0430.AUD	You ain’t with Robbery-Homicide.
			Actor_Says(kActorMcCoy, 3530, 15); //00-3530.AUD	No, sir.
			Actor_Says(kActorEarlyQ, 440, 15); //18-0440.AUD	Eh, those pieces ain’t hot. I got the papers to prove it. I picked them up at a legitimate auction. Cost me nearly a pound of flesh too.
			Actor_Says(kActorMcCoy, 3535, 13);
			Actor_Says(kActorEarlyQ, 460, 16); //18-0460.AUD	You kiddin’? I ain’t that stupid. No, no, no, no. I was letting one of my dancers use the stuff in her act. Kind of a tribute to the ancient swamp lands, you know what I mean?
			Actor_Says(kActorMcCoy, 3540, 15);
			Actor_Says(kActorEarlyQ, 490, 16); //18-0490.AUD	Hecuba. She’s going on in a few.
			Actor_Says(kActorEarlyQ, 500, 13); //18-0500.AUD	She’s one of my biggest earners too. She ain’t in any trouble now, is she?
			Actor_Says(kActorMcCoy, 3545, 15);
			Actor_Says(kActorEarlyQ, 520, 12); //18-0520.AUD	(sighs) Good, good. Wouldn’t wanna slaughter the goose that lays them golden eggs.
			// Added in this flag so when McCoy shows Early Q the photo of Dektora after talking to Early about the jewelry Early mentions Dektora being the one that he gave the jewelry to.
			// Early slipped up by saying Hecuba was the one he gave the jewelry after looking at the photo of Dektora whereas if you did not ask him about the jewelry he does not
			// mention that therefore McCoy has no reason not press him into telling the truth and Early outright denies knowing the woman in the photo.
			//Added in a clue.
			Actor_Face_Heading(kActorEarlyQ, 849, false);
		}
		break;

	case 900: // LUCY
		if (_vm->_cutContent) {	
			Actor_Says(kActorMcCoy, 3510, 23); //00-3510.AUD	This girl one of yours?
		} else {
			Actor_Says(kActorMcCoy, 3510, 15); //00-3510.AUD	This girl one of yours?
		}
		if (!_vm->_cutContent) {
			Actor_Modify_Friendliness_To_Other(kActorEarlyQ, kActorMcCoy, -1);
		}
		Actor_Says_With_Pause(kActorEarlyQ, 530, 1.2f, kAnimationModeTalk); //18-0530.AUD	This ain’t no daycare center, General.
		// Made it so if Early Q is a rep he doesn't make those creepy comments about Lucy. If Early Q is a rep he actually cares about the reps and would never hurt Lucy
		// who is someone that the reps really care about.
		if (_vm->_cutContent) {
			if (!Game_Flag_Query(kFlagEarlyQIsReplicant)) {
				Actor_Says(kActorEarlyQ, 540, 15); //18-0540.AUD	Of course, she ain’t half bad looking. My pappy always used to say ‘if there’s grass on the field, it’s time to play ball’.			
				Actor_Says(kActorMcCoy, 8665, 13); //00-8665.AUD	Disgusting.	
				Delay(2000);
			}
		} else {
			Actor_Says(kActorEarlyQ, 540, 15); //18-0540.AUD	Of course, she ain’t half bad looking. My pappy always used to say ‘if there’s grass on the field, it’s time to play ball’.			
		}
		Actor_Says(kActorMcCoy, 3550, 13); //00-3550.AUD	So, she hasn’t been around here?
		Actor_Says(kActorEarlyQ, 560, 14); //18-0560.AUD	Nah, she ain’t one of mine.
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagEarlyQIsReplicant)) {
				Actor_Says(kActorEarlyQ, 570, 13); //18-0570.AUD	Talk to Taffy. He gets most of the peddy business around here.
				Actor_Says(kActorMcCoy, 3555, 12); //00-3555.AUD	It’s men like you that made this country great, Early.
				Game_Flag_Set(kFlagEarlyQTalkLucy);
			} else {
				Actor_Says(kActorMcCoy, 2485, 19); //00-2485.AUD	I’ve a hard time believing that.
				Delay(2000);
				Game_Flag_Set(kFlagEarlyQTalkLucy);
			}
		} else {
			Actor_Says(kActorEarlyQ, 570, 13); //18-0570.AUD	Talk to Taffy. He gets most of the peddy business around here.
			Actor_Says(kActorMcCoy, 3555, 12); //00-3555.AUD	It’s men like you that made this country great, Early.
		}
		Actor_Face_Heading(kActorEarlyQ, 849, false);
		break;

	case 910: // BLOND WOMAN
		if (_vm->_cutContent) {
			Actor_Says(kActorMcCoy, 3515, 23); //00-3515.AUD	You ever seen this woman before?
		} else {
			Actor_Says(kActorMcCoy, 3515, 14); //00-3515.AUD	You ever seen this woman before?
		}
		if (!_vm->_cutContent) {
			Actor_Modify_Friendliness_To_Other(kActorEarlyQ, kActorMcCoy, -1);
		}
		// Made it so Early Q will only says that he recognises Dektora if he is a human. If he is a rep he will be protecting the reps so he will deny recognising Dektora.
		if (!Game_Flag_Query(kFlagEarlyQIsReplicant)) { 
			// A BUG?
			// TODO why is Grigorian's Note needed here, for EarlyQ to reveal who Hecuba is?
			// TODO could CrazysInvolvement also do here?
			//      maybe another clue should be required in its place or some additional ones?
			// Early Q acknowledges he knows Dektora, and also reveals Hecuba is her stage name
			// (Early Q also mentions Hecuba in the JEWELRY question but does not connect her with Dektora)
			// This dialogue thread assumes:
			// - Early Q has told McCoy about JEWELRY (weak, not necessarily)
			// --- If McCoy has not discussed the JEWELRY topic with EarlyQ yet, 
			// --- then he should NOT be able to do this AFTER this conversation IF McCoy has the clue condition
			// --- for this specific bit of dialogue which reveals Hecuba's identity.
			// --- Otherwiase it would create inconsistency to what is known about Hecuba
			// - Dektora/Hecuba has *not* performed her act yet
			if (_vm->_cutContent) {
				if (Actor_Clue_Query(kActorMcCoy, kClueEarlyInterviewA)) {
					Actor_Says(kActorEarlyQ, 580, 12); //18-0580.AUD	Hey. That kinda looks like Hecuba. The one I lent the jewelry to?
					Actor_Says(kActorMcCoy, 3560, 13); 
					Actor_Says(kActorEarlyQ, 590, 16); //18-0590.AUD	That’s it.
				} else {
					Actor_Says(kActorEarlyQ, 560, 14); //18-0560.AUD	Nah, she ain’t one of mine.
				}
			} else {
				Actor_Says(kActorEarlyQ, 580, 12); //18-0580.AUD	Hey. That kinda looks like Hecuba. The one I lent the jewelry to?
				Actor_Says(kActorMcCoy, 3560, 13); 
				Actor_Says(kActorEarlyQ, 590, 16); //18-0590.AUD	That’s it.
			}
			if (_vm->_cutContent) {
				if (Player_Query_Agenda() == kPlayerAgendaSurly
				|| (Player_Query_Agenda() == kPlayerAgendaErratic)) {
					if (Actor_Clue_Query(kActorMcCoy, kClueEarlyInterviewA)) {
						Actor_Says(kActorMcCoy, 3565, 16); //00-3565.AUD	There hasn’t been an exotic dancer who used her real name since Jesus was a pup.
					} else {
						Actor_Says(kActorMcCoy, 6995, 16); //00-6995.AUD	That's not what I heard. You wanna set the record straight?
						Delay(2000);
						Actor_Says(kActorMcCoy, 6985, 16); //00-6985.AUD	Got the straight scoop for me or what?
						Delay(1000);
					}
					Actor_Says(kActorEarlyQ, 600, 13);
					Actor_Says(kActorMcCoy, 3570, 14); //00-3570.AUD	I’m gonna want to talk to her. When is she up?
					Actor_Says(kActorEarlyQ, 620, 15); //18-0620.AUD	Next, General. Have a couple of drinks, relax a little. But wait until her act is over. I don’t want to deprive a lady of her livelihood.
					Actor_Says(kActorMcCoy, 3575, 13); //00-3575.AUD	Oh, god forbid.
					// Added in the this Early interview clue where he mentions Hecuba is Dektora.
					Actor_Clue_Acquire(kActorMcCoy, kClueEarlyInterviewB1, true, kActorEarlyQ);
				} else {
					Actor_Says(kActorMcCoy, 4880, 16); //00-4880.AUD	Is that right?
					Actor_Says(kActorEarlyQ, 740, 15); // 18-0740.AUD	Hey, would this face lie to you?
					Actor_Says(kActorMcCoy, 5705, 18); //00-5705.AUD	Uh-huh.
					Delay(2000);
					Actor_Says(kActorMcCoy, 745, 14); //00-0745.AUD	I'm watching you, pal.
				}
			} else {
				Actor_Says(kActorMcCoy, 3565, 16); //00-3565.AUD	There hasn’t been an exotic dancer who used her real name since Jesus was a pup.
				Actor_Says(kActorEarlyQ, 600, 13);
				Actor_Says(kActorMcCoy, 3570, 14);
				Actor_Says(kActorEarlyQ, 620, 15);
				Actor_Says(kActorMcCoy, 3575, 13);
			}
		} else {
			// Early Q denies recongnizing Dektora
			Actor_Says(kActorEarlyQ, 640, 13); //18-0640.AUD	Gee, I don’t know. She looks kind of familiar but I got so many broads working here, they all get kinda jumbled in my brain.
			if (_vm->_cutContent) {
				if (Player_Query_Agenda() != kPlayerAgendaPolite) {
					Actor_Says(kActorMcCoy, 3580, 15);  //00-3580.AUD	Sure they do.
				}
			} else {
				Actor_Says(kActorMcCoy, 3580, 15);  //00-3580.AUD	Sure they do.
			}
			Actor_Says(kActorEarlyQ, 660, 12); //18-0660.AUD	Relax, have a drink, loosen up. You see her, you let me know.
			if (Player_Query_Agenda() == kPlayerAgendaSurly
			|| (Player_Query_Agenda() == kPlayerAgendaErratic)) {
				Actor_Says(kActorMcCoy, 8519, 14);//00-8519.AUD	What do you say we dish each other the straight goods.
				Actor_Says(kActorEarlyQ, 730, kAnimationModeTalk); //18-0730.AUD	I’m working right now, General. Ask me later.
			}
		}
		Actor_Face_Heading(kActorEarlyQ, 849, false);
		break;
	}
}

void SceneScriptNR05::rotateActorOnGround(int actorId) {
	int animationMode = Actor_Query_Animation_Mode(actorId);
	if (animationMode == kAnimationModeWalk
	 || animationMode == kAnimationModeRun
	 || animationMode == kAnimationModeCombatWalk
	 || animationMode == kAnimationModeCombatRun
	) {
		return;
	}

	float x, y, z;
	Actor_Query_XYZ(actorId, &x, &y, &z);
	x -= -542.0f;
	z -= -195.0f;
	if (x * x + z * z < 92.0f * 92.0f) {
		float s = sin(M_PI / 128.0f);
		float c = cos(M_PI / 128.0f);
		float newX = x * c - z * s + -542.0f;
		float newZ = x * s + z * c + -195.0f;
		int newFacing = (Actor_Query_Facing_1024(actorId) + 4) % 1024;
		Actor_Set_At_XYZ(actorId, newX, y, newZ, newFacing);
	}
}

void SceneScriptNR05::playNextMusic() {
	if (Music_Is_Playing()) {
		Music_Adjust(51, 0, 2u);
	} else {
		int track = Global_Variable_Query(kVariableEarlyQBackMusic);
		int loop = kMusicLoopPlayOnce;
		if (_vm->_cutContent && Random_Query(0, 2) == 1) {
			loop = kMusicLoopPlayOnceRandomStart;
		}
		if (track == 0) {
			Music_Play(kMusicDkoDnce1, 61, -80, 2, -1, loop, 0);
		} else if (track == 1) {
			Music_Play(kMusicStrip1, 41, -80, 2, -1, loop, 0);
		} else if (track == 2) {
			Music_Play(kMusicArkDnce1, 41, -80, 2, -1, loop, 0);
		}
		++track;
		if (track > 2) {
			track = 0;
		}
		Global_Variable_Set(kVariableEarlyQBackMusic, track);
	}
}

} // End of namespace BladeRunner
