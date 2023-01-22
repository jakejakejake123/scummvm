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

enum kCT04Loops {
	kCT04LoopInshot   = 0,
	kCT04LoopMainLoop = 1
};

void SceneScriptCT04::InitializeScene() {
	if (Game_Flag_Query(kFlagCT03toCT04)) {
		Scene_Loop_Start_Special(kSceneLoopModeLoseControl, kCT04LoopInshot, false);
		Scene_Loop_Set_Default(kCT04LoopMainLoop);
		Setup_Scene_Information(-150.0f, -621.3f, 357.0f, 533);
	} else {
		Scene_Loop_Set_Default(kCT04LoopMainLoop);
		Setup_Scene_Information(-82.86f, -621.3f, 769.03f, 1020);
	}

	Scene_Exit_Add_2D_Exit(0, 590,  0, 639, 479, 1);
	Scene_Exit_Add_2D_Exit(1, 194, 84, 320, 274, 0);
	if (_vm->_cutContent) {
		Scene_Exit_Add_2D_Exit(2, 0, 440, 590, 479, 2);
	}

	Ambient_Sounds_Add_Looping_Sound(kSfxCTRAIN1,  50,    1, 1);
	Ambient_Sounds_Add_Looping_Sound(kSfxCTAMBR1,  15, -100, 1);
	Ambient_Sounds_Add_Looping_Sound(kSfxCTRUNOFF, 34,  100, 1);
	Ambient_Sounds_Add_Sound(kSfxSPIN2B,  10, 40, 33, 50,    0,   0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSPIN3A,  10, 40, 33, 50,    0,   0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Speech_Sound(kActorBlimpGuy,  0, 10u, 260u, 17, 24, -100, 100, -101, -101, 1, 1);
	Ambient_Sounds_Add_Speech_Sound(kActorBlimpGuy, 20, 10u, 260u, 17, 24, -100, 100, -101, -101, 1, 1);
	Ambient_Sounds_Add_Speech_Sound(kActorBlimpGuy, 40, 10u, 260u, 17, 24, -100, 100, -101, -101, 1, 1);
	Ambient_Sounds_Add_Speech_Sound(kActorBlimpGuy, 50, 10u, 260u, 17, 24, -100, 100, -101, -101, 1, 1);
	Ambient_Sounds_Add_Sound(kSfxTHNDER3, 10, 60, 33, 50, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxTHNDER4, 10, 60, 33, 50, -100, 100, -101, -101, 0, 0);
}

void SceneScriptCT04::SceneLoaded() {
	Obstacle_Object("DUMPSTER", true);
	Obstacle_Object("RIGHTWALL01", true);
	Obstacle_Object("BACK-BLDNG", true);
	Clickable_Object("DUMPSTER");
	Footstep_Sounds_Set(0, 1);
	if (Game_Flag_Query(kFlagCT03toCT04)) {
		Game_Flag_Reset(kFlagCT03toCT04);
	}
	if (Actor_Query_Goal_Number(kActorTransient) == kGoalTransientDefault) {
		Actor_Change_Animation_Mode(kActorTransient, 38);
	}
}

bool SceneScriptCT04::MouseClick(int x, int y) {
	return false;
}

bool SceneScriptCT04::ClickedOn3DObject(const char *objectName, bool a2) {
	if (objectName) { // this can be only "DUMPSTER"
		if (!Game_Flag_Query(kFlagCT04HomelessTalk)
		 && !Game_Flag_Query(kFlagCT04HomelessKilledByMcCoy)
		 &&  Actor_Query_Goal_Number(kActorTransient) == kGoalTransientDefault
		) {
			Game_Flag_Set(kFlagCT04HomelessTalk);
			Actor_Set_Goal_Number(kActorTransient, kGoalTransientCT04Leave);
		}

		if ( Game_Flag_Query(kFlagCT04HomelessKilledByMcCoy)
		 && !Game_Flag_Query(kFlagCT04HomelessBodyInDumpster)
		 && !Game_Flag_Query(kFlagCT04HomelessBodyFound)
		 && !Game_Flag_Query(kFlagCT04HomelessBodyThrownAway)
		 &&  Global_Variable_Query(kVariableChapter) == 1
		) {
			if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -147.41f, -621.3f, 724.57f, 0, true, false, false)) {
				Player_Loses_Control();
				Actor_Face_Heading(kActorMcCoy, 792, false);
				Actor_Put_In_Set(kActorTransient, kSetFreeSlotI);
				Actor_Set_At_XYZ(kActorTransient, 0, 0, 0, 0);
				Actor_Change_Animation_Mode(kActorMcCoy, 40);
				if (_vm->_cutContent) { 
					if (Player_Query_Agenda() != kPlayerAgendaSurly 
					&& Player_Query_Agenda() != kPlayerAgendaErratic) {
						Actor_Voice_Over(320, kActorVoiceOver);
						Actor_Voice_Over(330, kActorVoiceOver);
					}
				} else {
					Actor_Voice_Over(320, kActorVoiceOver);
					Actor_Voice_Over(330, kActorVoiceOver);
				}
				if (!_vm->_cutContent) { 
					Actor_Voice_Over(340, kActorVoiceOver);
				}
				Game_Flag_Set(kFlagCT04HomelessBodyInDumpster);
				if (_vm->_cutContent) {
					Actor_Set_Goal_Number(kActorZuben, kGoalZubenFled);
				}
			}
			return false;
		}

		if (Game_Flag_Query(kFlagCT04HomelessBodyInDumpster)) {
			if (Game_Flag_Query(kFlagCT04HomelessBodyThrownAway)) {
				Actor_Voice_Over(270, kActorVoiceOver); //99-0270.AUD	The trash had been collected.
				Actor_Voice_Over(280, kActorVoiceOver); //99-0280.AUD	It was gone for good. All of it.
				if (_vm->_cutContent) { 
					if (Player_Query_Agenda() == kPlayerAgendaSurly 
					|| Player_Query_Agenda() == kPlayerAgendaErratic) {
						Actor_Voice_Over(340, kActorVoiceOver); //99-0340.AUD	Besides specials vanished every day in this city. And no one ever missed them.
					}
				} 
			} else if (Game_Flag_Query(kFlagCT04HomelessBodyFound)) {
				Actor_Voice_Over(250, kActorVoiceOver); //99-0250.AUD	The body had vanished but the trash was still there.
				if (_vm->_cutContent) { 
					if (Player_Query_Agenda() != kPlayerAgendaSurly 
					&& Player_Query_Agenda() != kPlayerAgendaErratic) {
						Actor_Voice_Over(260, kActorVoiceOver); //99-0260.AUD	I'd screwed up and screwed up bad. But maybe there was still a way to make it right.
					}
				} else {
					Actor_Voice_Over(260, kActorVoiceOver); //99-0260.AUD	I'd screwed up and screwed up bad. But maybe there was still a way to make it right.
				}
			} else {
				Actor_Voice_Over(230, kActorVoiceOver); //99-0230.AUD	The body was still there.
				if (_vm->_cutContent) { 
					if (Player_Query_Agenda() == kPlayerAgendaSurly 
					|| Player_Query_Agenda() == kPlayerAgendaErratic) {
						Actor_Voice_Over(240, kActorVoiceOver); //99-0240.AUD	I didn't know when the trash got picked up in this neighborhood but I hoped it was soon.
					}
				} else {
					Actor_Voice_Over(240, kActorVoiceOver);	
				}
			}
			return true;
		}

		if (!Actor_Clue_Query(kActorMcCoy, kClueLicensePlate)) {
			if (!Loop_Actor_Walk_To_Waypoint(kActorMcCoy, 75, 0, true, false)) {
				Actor_Face_Heading(kActorMcCoy, 707, false);
				Actor_Change_Animation_Mode(kActorMcCoy, 38);
				if (_vm->_cutContent) { 
					if (Actor_Clue_Query(kActorMcCoy, kCluePartialLicenseNumber)) {
						if (!Actor_Clue_Query(kActorMcCoy, kClueLicensePlate)) {
							Actor_Clue_Acquire(kActorMcCoy, kClueLicensePlate, true, kActorZuben);
							Item_Pickup_Spin_Effect(kModelAnimationLicensePlate, 392, 225);
							Game_Flag_Set(kFlagCT04LicensePlaceFound); 
							//Restored the license plate match clue. When McCoy finds the license plate in the dumpster and he has the partial license plate photo clue
							//he runs a test on the KIA and it is a positive match. Also added in code to the esper script so the same happens if it is the other way around.
							Actor_Says(kActorMcCoy, 8760, -1);//00-8760.AUD	A license plate.
							Delay(2000);
							Actor_Says(kActorMcCoy, 8525, 9); //00-8525.AUD	Hmph.
							Actor_Says(kActorAnsweringMachine, 390, kAnimationModeTalk); // 39-0390.AUD	Begin test.
							Ambient_Sounds_Play_Sound(kSfxDATALOAD, 50, 0, 0, 99);
							Delay(2000);
							Ambient_Sounds_Play_Sound(kSfxBEEPNEAT, 80, 0, 0, 99);
							Actor_Says(kActorAnsweringMachine, 420, 19); //39-0420.AUD	Positive result.
							Actor_Says(kActorAnsweringMachine, 470, kAnimationModeTalk); //39-0470.AUD	End test.
							Actor_Says(kActorMcCoy, 7200, 13); //00-7200.AUD	Bingo.
							Actor_Clue_Acquire(kActorMcCoy, kClueLicensePlateMatch, true, -1); 
						}
			  		} else {
						Ambient_Sounds_Play_Sound(kSfxGARBAGE, 45, 30, 30, 0);
						Actor_Voice_Over(1810, kActorVoiceOver);
						Actor_Voice_Over(1820, kActorVoiceOver);
					}
				} else {
					Actor_Clue_Acquire(kActorMcCoy, kClueLicensePlate, true, -1);
					Item_Pickup_Spin_Effect(kModelAnimationLicensePlate, 392, 225);
					Game_Flag_Set(kFlagCT04LicensePlaceFound); 
				}
				return true;
			}
		}

		if (!Loop_Actor_Walk_To_Waypoint(kActorMcCoy, 75, 0, true, false)) {
			Actor_Face_Heading(kActorMcCoy, 707, false);
			Actor_Change_Animation_Mode(kActorMcCoy, 38);
			Ambient_Sounds_Play_Sound(kSfxGARBAGE, 45, 30, 30, 0);
			Actor_Voice_Over(1810, kActorVoiceOver);
			Actor_Voice_Over(1820, kActorVoiceOver);
			return true;
		}
	}
	return false;
}

void SceneScriptCT04::dialogueWithHomeless() {
	Dialogue_Menu_Clear_List();
	// Made it so McCoy only gives the homeless man money if he is not surly or erratic and he has enough money.
	if (_vm->_cutContent) { 
		if (Player_Query_Agenda() == kPlayerAgendaPolite) {
			if (Global_Variable_Query(kVariableChinyen) >= 10
			|| Query_Difficulty_Level() == kGameDifficultyEasy) {
				DM_Add_To_List_Never_Repeat_Once_Selected(410, 8, 4, -1); // YES
			} else {
				DM_Add_To_List_Never_Repeat_Once_Selected(420, -1, 6, 8); // NO
			}
		} else {
			DM_Add_To_List_Never_Repeat_Once_Selected(420, -1, 6, 8); // NO
		}
	} else {
		if (Global_Variable_Query(kVariableChinyen) > 10
		|| Query_Difficulty_Level() == kGameDifficultyEasy) {
			DM_Add_To_List_Never_Repeat_Once_Selected(410, 8, 4, -1); // YES
		} else {
			DM_Add_To_List_Never_Repeat_Once_Selected(420, 2, 6, 8); // NO
		}
	}
	Dialogue_Menu_Appear(320, 240);
	int answer = Dialogue_Menu_Query_Input();
	Dialogue_Menu_Disappear();

	switch (answer) {
	case 410: // YES
		if (_vm->_cutContent) {
			Actor_Change_Animation_Mode(kActorMcCoy, 23);
			Delay(2000);
			Actor_Says(kActorMcCoy, 8170, 13); //00-8170.AUD	There you go.
		}
		Actor_Says(kActorTransient, 10, 13); // Thanks. The big man. He kind of limping.
		if (_vm->_cutContent) {
			Actor_Says(kActorTransient, 20, 14); // That way.
			Delay(1000);
		} else {
			Actor_Says(kActorTransient, 20, 13); // That way.
		}
		//Restored the big man limping clue.
		if (_vm->_cutContent) {
			Actor_Clue_Acquire(kActorMcCoy, kClueBigManLimping, true, kActorTransient);
		}
		Actor_Modify_Friendliness_To_Other(kActorTransient, kActorMcCoy, 5);
		if (Query_Difficulty_Level() != kGameDifficultyEasy) {
			Global_Variable_Decrement(kVariableChinyen, 10);
		}
		break;

	case 420: // NO
		Actor_Says(kActorMcCoy, 430, 3);
		if (_vm->_cutContent) {
			Actor_Says(kActorTransient, 30, 13); // Hey, that'd work.
			Actor_Says(kActorMcCoy, 440, 16); //00-0440.AUD	Forget it.
		} else {
			Actor_Says(kActorTransient, 30, 14); // Hey, that'd work.
		}
		Actor_Modify_Friendliness_To_Other(kActorTransient, kActorMcCoy, -5);
		break;
	}
}

bool SceneScriptCT04::ClickedOnActor(int actorId) {
	if (actorId == kActorTransient) {
		if (Game_Flag_Query(kFlagCT04HomelessKilledByMcCoy)) {
			if (!Loop_Actor_Walk_To_Actor(kActorMcCoy, kActorTransient, 36, true, false)) {
				Actor_Voice_Over(290, kActorVoiceOver); //99-0290.AUD	He was just an old bum. Not Howie's cook and certainly not a Replicant.
				Actor_Voice_Over(300, kActorVoiceOver); //99-0300.AUD	I'd screwed up. Plain and simple.
				if (_vm->_cutContent) { 
					if (Player_Query_Agenda() != kPlayerAgendaPolite) {
						Actor_Voice_Over(310, kActorVoiceOver);
					}
				} else {
					Actor_Voice_Over(310, kActorVoiceOver);
				}
			}
		} else {
			Actor_Set_Targetable(kActorTransient, false);
			if (!Loop_Actor_Walk_To_Actor(kActorMcCoy, kActorTransient, 36, true, false)) {
				Actor_Face_Actor(kActorMcCoy, kActorTransient, true);
				if (!Game_Flag_Query(kFlagCT04HomelessTalk)) {
					if (Game_Flag_Query(kFlagZubenRetired)) {
						Actor_Says(kActorMcCoy, 435, kAnimationModeTalk);
						Actor_Set_Goal_Number(kActorTransient, kGoalTransientCT04Leave);
					} else {
						Music_Stop(3u);
						Actor_Says(kActorMcCoy, 425, kAnimationModeTalk);
						// Added in code so the homeless guy faces McCoy when he talks to him.
						// I mean how would McCoy give him money if his back is turned to him.
						if (_vm->_cutContent) {
							Actor_Face_Actor(kActorTransient, kActorMcCoy, true);
						}
						Actor_Says(kActorTransient, 0, 13); // Hey, maybe spare some chinyen?
						dialogueWithHomeless();
						Actor_Set_Goal_Number(kActorTransient, kGoalTransientCT04Leave);
					}
					Game_Flag_Set(kFlagCT04HomelessTalk);
				} else {
					Actor_Face_Actor(kActorMcCoy, kActorTransient, true);
					Actor_Says(kActorMcCoy, 435, kAnimationModeTalk);
				}
			}
		}
		return true;
	}
	return false;
}

bool SceneScriptCT04::ClickedOnItem(int itemId, bool a2) {
	return false;
}

bool SceneScriptCT04::ClickedOnExit(int exitId) {
	if (exitId == 1) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -82.86f, -621.3f, 769.03f, 0, true, false, false)) {
			Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
			Ambient_Sounds_Remove_All_Looping_Sounds(1u);
			if (Actor_Query_Goal_Number(kActorTransient) == kGoalTransientDefault) {
				Actor_Set_Goal_Number(kActorTransient, kGoalTransientCT04Leave);
			}
			Game_Flag_Set(kFlagCT04toCT05);
			Set_Enter(kSetCT05, kSceneCT05);
		}
		return true;
	}
	if (exitId == 0) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -187.0f, -621.3f, 437.0f, 0, true, false, false)) {
			Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
			Ambient_Sounds_Remove_All_Looping_Sounds(1u);
			Game_Flag_Set(kFlagCT04toCT03);
			Set_Enter(kSetCT03_CT04, kSceneCT03);
		}
		return true;
	}
	if (_vm->_cutContent) {
		if (exitId == 2) {
			if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -106.94f, -619.08f, 429.20f, 0, true, false, false)) {
				Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
				Ambient_Sounds_Remove_All_Looping_Sounds(1u);
				Game_Flag_Set(kFlagCT04toCT03);
				Set_Enter(kSetCT03_CT04, kSceneCT03);
			}
			return true;
		}
	}
	return false;
}

bool SceneScriptCT04::ClickedOn2DRegion(int region) {
	return false;
}

void SceneScriptCT04::SceneFrameAdvanced(int frame) {
	if (Game_Flag_Query(kFlagCT04BodyDumped)) {
		Game_Flag_Reset(kFlagCT04BodyDumped);
		Sound_Play(kSfxGARBAGE4, 100, 80, 80, 50);
	}
}

void SceneScriptCT04::ActorChangedGoal(int actorId, int newGoal, int oldGoal, bool currentSet) {
}

void SceneScriptCT04::PlayerWalkedIn() {
}

void SceneScriptCT04::PlayerWalkedOut() {
}

void SceneScriptCT04::DialogueQueueFlushed(int a1) {
}

} // End of namespace BladeRunner
