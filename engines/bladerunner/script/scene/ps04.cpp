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

enum kPS04Loops {
	kPS04LoopPanToPS04                 = 0, //   0 -  29
	kPS04LoopMainLoop                  = 1  //  30 -  90 (actually 31-90)
};

void SceneScriptPS04::InitializeScene() {
	AI_Movement_Track_Pause(kActorGuzza);
	if (Game_Flag_Query(kFlagPS03toPS04)) {
		Game_Flag_Reset(kFlagPS03toPS04);
	}
	Setup_Scene_Information(-668.0f, -354.0f, 974.0f, 475);
	if (Global_Variable_Query(kVariableChapter) == 1) {
		Actor_Put_In_Set(kActorGuzza, kSetPS04);
		Actor_Set_At_XYZ(kActorGuzza, -728.0f, -354.0f, 1090.0f, 150);
		Actor_Change_Animation_Mode(kActorGuzza, 53);
	}
	Scene_Exit_Add_2D_Exit(0, 347, 113, 469, 302, 0);
	Ambient_Sounds_Remove_All_Non_Looping_Sounds(false);
	Ambient_Sounds_Add_Looping_Sound(kSfxPSAMB6, 16, 1, 1);
	Ambient_Sounds_Add_Looping_Sound(kSfxRTONE3, 50, 1, 1);
	Ambient_Sounds_Add_Sound(kSfxSCANNER1, 9, 40, 20, 20, 0, 0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSCANNER2, 9, 40, 20, 20, 0, 0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSCANNER3, 9, 40, 20, 20, 0, 0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSCANNER4, 9, 40, 20, 20, 0, 0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSCANNER5, 9, 40, 20, 20, 0, 0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSCANNER6, 9, 40, 20, 20, 0, 0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSCANNER7, 9, 40, 20, 20, 0, 0, -101, -101, 0, 0);

	Scene_Loop_Start_Special(kSceneLoopModeLoseControl, kPS04LoopPanToPS04, false);
	Scene_Loop_Set_Default(kPS04LoopMainLoop);
}

void SceneScriptPS04::SceneLoaded() {
	Obstacle_Object("CHAIR07", true);
	Unobstacle_Object("GOOD B.WALL", true);
	Unobstacle_Object("B.DOOR", true);
	Unobstacle_Object("B.CHAIR01", true);
	Unclickable_Object("CHAIR07");
#if BLADERUNNER_ORIGINAL_BUGS
#else
	Unclickable_Object("FLOOR");
#endif // BLADERUNNER_ORIGINAL_BUGS

	if (_vm->_cutContent) {
		if ( Global_Variable_Query(kVariableChapter) > 1
		&& !Actor_Clue_Query(kActorMcCoy, kClueWeaponsOrderForm)
		&& !Game_Flag_Query(kFlagPS04WeaponsOrderForm)
		) {
			Item_Add_To_World(kItemWeaponsOrderForm, kModelAnimationWeaponsOrderForm, kSetPS04, -643.5f, -318.82f, 1148.87f, 525, 16, 12, false, true, false, true);
			Game_Flag_Set(kFlagPS04WeaponsOrderForm);
		}
	} else if ( Global_Variable_Query(kVariableChapter) == 2
	 && !Actor_Clue_Query(kActorMcCoy, kClueWeaponsOrderForm)
	 && !Game_Flag_Query(kFlagPS04WeaponsOrderForm)
	) {
		Item_Add_To_World(kItemWeaponsOrderForm, kModelAnimationOriginalRequisitionForm, kSetPS04, -643.5f, -318.82f, 1148.87f, 525, 16, 12, false, true, false, true);
		Game_Flag_Set(kFlagPS04WeaponsOrderForm);
	}

	if (Actor_Query_Is_In_Current_Set(kActorGuzza)) {
		Actor_Change_Animation_Mode(kActorGuzza, 53);
	}
}

bool SceneScriptPS04::MouseClick(int x, int y) {
	return false;
}

bool SceneScriptPS04::ClickedOn3DObject(const char *objectName, bool a2) {
	return false;
}

bool SceneScriptPS04::ClickedOnActor(int actorId) {
	if (actorId == kActorGuzza) {
		if (!Loop_Actor_Walk_To_Actor(kActorMcCoy, kActorGuzza, 36, true, false)) {
			Actor_Face_Actor(kActorMcCoy, kActorGuzza, true);
			Actor_Face_Actor(kActorGuzza, kActorMcCoy, true);
			dialogueWithGuzza();
			return true;
		}
	}
	return false;
}

bool SceneScriptPS04::ClickedOnItem(int itemId, bool a2) {
#if BLADERUNNER_ORIGINAL_BUGS
	if (itemId == kItemWeaponsOrderForm
	 && Actor_Query_Is_In_Current_Set(kActorGuzza)
	) {
		Actor_Says(kActorGuzza, 560, 30);
	} else if (!Actor_Clue_Query(kActorMcCoy, kClueWeaponsOrderForm)) {
		Item_Remove_From_World(kItemWeaponsOrderForm);
		Item_Pickup_Spin_Effect(kModelAnimationOriginalRequisitionForm, 464, 362);
		Actor_Says(kActorMcCoy, 4485, kAnimationModeTalk);
		Actor_Clue_Acquire(kActorMcCoy, kClueWeaponsOrderForm, true, kActorMcCoy);
	}
#else
	// bugfix: correct code, this is only for clicking on the kItemWeaponsOrderForm
	if (itemId == kItemWeaponsOrderForm) {
		if (Actor_Query_Is_In_Current_Set(kActorGuzza)) {
			Actor_Says(kActorGuzza, 560, 30);
			if (_vm->_cutContent) {
				Actor_Modify_Friendliness_To_Other(kActorGuzza, kActorMcCoy, -2);
			}
		} else if (!Actor_Clue_Query(kActorMcCoy, kClueWeaponsOrderForm)) {
			Item_Remove_From_World(kItemWeaponsOrderForm);
			if (_vm->_cutContent) {
				Actor_Change_Animation_Mode(kActorMcCoy, 23);
				Delay(800);
				Item_Pickup_Spin_Effect(kModelAnimationWeaponsOrderForm, 464, 362);
				Delay(800);
			} else {
				Item_Pickup_Spin_Effect(kModelAnimationOriginalRequisitionForm, 464, 362);
			}
			Actor_Says(kActorMcCoy, 4485, kAnimationModeTalk);
			if (_vm->_cutContent) {
				Actor_Clue_Acquire(kActorMcCoy, kClueWeaponsOrderForm, true, kActorGuzza);
			} else {
				Actor_Clue_Acquire(kActorMcCoy, kClueWeaponsOrderForm, true, kActorMcCoy);
			}
		}
	}
#endif // BLADERUNNER_ORIGINAL_BUGS
	return false;
}

bool SceneScriptPS04::ClickedOnExit(int exitId) {
	if (exitId == 0) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -668.0f, -350.85f, 962.0f, 0, true, false, false)) {
			Game_Flag_Set(kFlagPS04toPS03);
			Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
			Ambient_Sounds_Remove_All_Looping_Sounds(1u);
			Set_Enter(kSetPS03, kScenePS03);
		}
		return true;
	}
	return false;
}

bool SceneScriptPS04::ClickedOn2DRegion(int region) {
	return false;
}

void SceneScriptPS04::SceneFrameAdvanced(int frame) {
}

void SceneScriptPS04::ActorChangedGoal(int actorId, int newGoal, int oldGoal, bool currentSet) {
}

void SceneScriptPS04::PlayerWalkedIn() {
	if (Actor_Query_Which_Set_In(kActorGuzza) == kSetPS04) {
		Actor_Face_Actor(kActorMcCoy, kActorGuzza, true);
	}
	if (_vm->_cutContent) {
		if (Game_Flag_Query(kFlagCT01TalkToHowieAfterZubenMissing)
		&& !Game_Flag_Query(kFlagZubenRetired)
		&& !Game_Flag_Query(kFlagPS04GuzzaTalkIsFurious)
		&& !Actor_Clue_Query(kActorMcCoy, kClueMcCoyKilledRunciter1)
		&& !Game_Flag_Query(kFlagMcCoyShotRachael)
		&& !Game_Flag_Query(kFlagMcCoyShotGrigorian)
		&& !Game_Flag_Query(kFlagRunciterArrested)
		&& !Game_Flag_Query(kFlagZubenArrested)
		&& !Game_Flag_Query(kFlagGrigorianDead)) {
			Actor_Put_In_Set(kActorGuzza, kSetPS04);
			Actor_Set_At_XYZ(kActorGuzza, -728.0f, -354.0f, 1090.0f, 150);
			Actor_Change_Animation_Mode(kActorGuzza, 53);
			Actor_Face_Actor(kActorGuzza, kActorMcCoy, true);
			Actor_Face_Actor(kActorMcCoy, kActorGuzza, true);
			Actor_Says(kActorMcCoy, 3970, 18);
			Actor_Says(kActorGuzza, 330, 30); //04-0330.AUD	What the hell you've been doing out there, McCoy? Rustling up toe jam?
			Actor_Says(kActorGuzza, 340, 32); //04-0340.AUD	I need results and fast.
			Actor_Says(kActorMcCoy, 3975, 13); //00-3975.AUD	I'm working on it.
			Actor_Says(kActorGuzza, 350, 31); //04-0350.AUD	That's not good enough. Bryant's been crawling up my ass all morning.
			Actor_Says(kActorMcCoy, 3910, 15); //00-3910.AUD	You’re lying.
			Actor_Says(kActorGuzza, 1520, 16); //04-1520.AUD	Everything I say is as true as holy writ.
			if (Player_Query_Agenda() == kPlayerAgendaPolite) {
				Actor_Says(kActorMcCoy, 4880, 13); //00-4880.AUD	Is that right?
			} else {
				Actor_Says(kActorMcCoy, 2485, 18); //00-2485.AUD	I’ve a hard time believing that.
			}
			Delay(1000);
			Actor_Says(kActorGuzza, 360, 34); //04-0360.AUD	If you can't cut it just tell me and I'll reassign the Gaffster or Steele.
			Actor_Says(kActorMcCoy, 3980, 13); //00-3980.AUD	I can handle it.
			Actor_Says(kActorGuzza, 370, 33); //04-0370.AUD	I don't know if you can, McCoy. I really got my doubts.
			Actor_Says(kActorGuzza, 380, 32); // 04-0380.AUD	You blow chunks on your first assignment, you can damn near shit-can your future here.
			if (Actor_Query_Friendliness_To_Other(kActorGuzza, kActorMcCoy) < 51) {	
				Actor_Says(kActorGuzza, 390, 31); //04-0390.AUD	Not to mention how it makes me look.
			}
			if (Player_Query_Agenda() == kPlayerAgendaSurly 
			|| Player_Query_Agenda() == kPlayerAgendaErratic) {
				Actor_Says(kActorMcCoy, 4320, 14); //00-4320.AUD	Save the pitch for someone who gives a shit.
				Actor_Says(kActorGuzza, 410, 31);
				Actor_Modify_Friendliness_To_Other(kActorGuzza, kActorMcCoy, -2);
				Game_Flag_Set(kFlagPS04GuzzaTalkIsFurious);
			} else {	
				Actor_Says(kActorMcCoy, 3985, 18); //00-3985.AUD	I hear ya.
				if (Actor_Query_Friendliness_To_Other(kActorGuzza, kActorMcCoy) < 51) {
					Actor_Says(kActorGuzza, 400, 34); //04-0400.AUD	Get the hell out of here! And show me the promoting you wasn't a fool move.
				}
				Actor_Says(kActorGuzza, 410, 31);
				Game_Flag_Set(kFlagPS04GuzzaTalkIsFurious);
			}
		}
	}
	// Code for the scene where Guzza gets angry at you for retiring Rachael.
	if (_vm->_cutContent) {
		if (Game_Flag_Query(kFlagMcCoyShotRachael)) {
			Actor_Put_In_Set(kActorGuzza, kSetPS04);
			Actor_Set_At_XYZ(kActorGuzza, -728.0f, -354.0f, 1090.0f, 150);
			Actor_Change_Animation_Mode(kActorGuzza, 53);
			Actor_Face_Actor(kActorGuzza, kActorMcCoy, true);
			Actor_Face_Actor(kActorMcCoy, kActorGuzza, true);
			Actor_Says(kActorGuzza, 80, 31); //04-0080.AUD	Tyrell's niece! Are you out of your cotton-picking mind?
			Actor_Says(kActorMcCoy, 2725, 14); //00-2725.AUD	Bring her in! We'll do a bone marrow test, you'll see.
			Actor_Says(kActorMcCoy, 2720, 15); //00-2720.AUD	She's a Rep. I'm telling you Nexus-6!
			Actor_Says(kActorGuzza, 90, 33); //04-0090.AUD	So what? She's private property.
			Actor_Says(kActorGuzza, 100, 32); //04-0100.AUD	Did you even stop to think about what her last name was, idiot?
			Actor_Says(kActorGuzza, 110, 31); //04-0110.AUD	I can't save you, McCoy. Bryant wants your walking papers and I can't blame him.
			Actor_Says(kActorGuzza, 120, 34); //04-0120.AUD	I don't want to ever see your sorry ass again.
			Delay(1000);
			Actor_Retired_Here(kActorMcCoy, 6, 6, 1, -1);
		}
	}
	if (_vm->_cutContent) {
		if (Game_Flag_Query(kFlagMcCoyShotGrigorian)) {
			Actor_Put_In_Set(kActorGuzza, kSetPS04);
			Actor_Set_At_XYZ(kActorGuzza, -728.0f, -354.0f, 1090.0f, 150);
			Actor_Change_Animation_Mode(kActorGuzza, 53);
			Actor_Face_Actor(kActorGuzza, kActorMcCoy, true);
			Actor_Face_Actor(kActorMcCoy, kActorGuzza, true);
			Actor_Says(kActorGuzza, 150, 31); //04-0150.AUD	You've really been surprising the troops around here, kid.
			Actor_Says(kActorGuzza, 160, 32); //04-0160.AUD	Gaff says you worked that retirement like a champ.
			Actor_Says(kActorMcCoy, 2215, 18); //00-2215.AUD	That’s right.
			Delay(1000);
			Actor_Says(kActorMcCoy, 8514, 13); //00-8514.AUD	Got anything new to tell me?
			Actor_Says(kActorGuzza, 290, 33); //04-0290.AUD	Don't push it, kid. You look like you're beat anyway.
			Actor_Says(kActorMcCoy, 690, 18); //00-0690.AUD	Gotcha.
			Scene_Exits_Enable();
			Game_Flag_Set(kFlagGrigorianDead);
			Game_Flag_Set(kFlagMcCoyRetiredReplicant);
			Game_Flag_Reset(kFlagMcCoyShotGrigorian);
			if (Query_Difficulty_Level() != kGameDifficultyEasy) {
				Global_Variable_Increment(kVariableChinyen, 200);
			}
			Actor_Set_At_XYZ(kActorGrigorian, -728.0f, -354.0f, 1090.0f, 150);
			Actor_Modify_Friendliness_To_Other(kActorClovis, kActorMcCoy, -2);
			Game_Flag_Reset(kFlagMcCoyIsHelpingReplicants);
			Actor_Modify_Friendliness_To_Other(kActorSteele, kActorMcCoy, 2);
			Actor_Modify_Friendliness_To_Other(kActorGuzza, kActorMcCoy, 2);
			Actor_Modify_Friendliness_To_Other(kActorGaff, kActorMcCoy, 2);
		}
	}
	//return false;
}

void SceneScriptPS04::PlayerWalkedOut() {
	AI_Movement_Track_Unpause(kActorGuzza);
}

void SceneScriptPS04::DialogueQueueFlushed(int a1) {
}

void SceneScriptPS04::dialogueWithGuzza() {
	Dialogue_Menu_Clear_List();

	if (_vm->_cutContent) {
		if (Game_Flag_Query(kFlagTyrellGuardTalkMeeting)) { 
			DM_Add_To_List_Never_Repeat_Once_Selected(110, 5, 7, 4); // REQUEST TYRELL MEETING
		}
	} else if (Actor_Clue_Query(kActorMcCoy, kClueAttemptedFileAccess)) {
		DM_Add_To_List_Never_Repeat_Once_Selected(110, 5, 7, 4); // REQUEST TYRELL MEETING
	}
	if (_vm->_cutContent) {
		if (Game_Flag_Query(kFlagCT01TalkToHowieAfterZubenMissing)) { 
			DM_Add_To_List_Never_Repeat_Once_Selected(120, 4, 3, 2); // MONEY
		}
	} else {
		DM_Add_To_List_Never_Repeat_Once_Selected(120, 1, -1, -1); // MONEY
	}
	if (Actor_Clue_Query(kActorMcCoy, kClueHoldensBadge)) {
		DM_Add_To_List_Never_Repeat_Once_Selected(150, 7, 6, 5); // HOLDEN'S BADGE
	}
	if (_vm->_cutContent) {
		if (Game_Flag_Query(kFlagCT04HomelessKilledByMcCoy)) {
			DM_Add_To_List_Never_Repeat_Once_Selected(140, 3, 2, 1); // CONFESS TO SHOOTING
		}
	} else {
		DM_Add_To_List_Never_Repeat_Once_Selected(140, 3, -1, -1); // CONFESS TO SHOOTING
	}
	DM_Add_To_List(130, 1, 1, 1); // REPORT IN
	Dialogue_Menu_Add_DONE_To_List(160); // DONE

	Dialogue_Menu_Appear(320, 240);
	int answer = Dialogue_Menu_Query_Input();
	Dialogue_Menu_Disappear();

	switch (answer) {
	case 110: // REQUEST TYRELL MEETING
		Actor_Says(kActorGuzza, 420, 31);
		Actor_Says(kActorMcCoy, 3990, 19);
		Actor_Says(kActorMcCoy, 3995, 17); 
		if (_vm->_cutContent) {
			if (Actor_Query_Friendliness_To_Other(kActorGuzza, kActorMcCoy) < 51) {
				Actor_Says(kActorGuzza, 430, 33);
				Actor_Says(kActorMcCoy, 4025, 18); //00-4025.AUD	One of his employees got his brains splattered inside the pyramid.
				Actor_Says(kActorMcCoy, 4030, 12); //00-4030.AUD	I thought maybe Tyrell could fill in some blanks.
				Actor_Says(kActorGuzza, 440, 31);
				Actor_Says(kActorMcCoy, 4035, 13); //00-4035.AUD	You and I both know it's a one-man show over there.
			}
		} else {
			Actor_Says(kActorGuzza, 430, 33);
			Actor_Says(kActorMcCoy, 4025, 18);
			Actor_Says(kActorMcCoy, 4030, 12);
			Actor_Says(kActorGuzza, 440, 31);
			Actor_Says(kActorMcCoy, 4035, 13);
		}
		Actor_Says(kActorGuzza, 450, 34); //04-0450.AUD	Yeah, I'll give it a try, kid. And I'll have to pull some strings, so don't go in there half-assed.
		Actor_Says(kActorGuzza, 460, 33); //04-0460.AUD	Make sure you got some legit questions for the resident genius.
		if (_vm->_cutContent) {
			if (Player_Query_Agenda() == kPlayerAgendaPolite) {
				Actor_Says(kActorMcCoy, 4040, 17); //00-4040.AUD	Appreciate it, Lieutenant.
			} else {
				Actor_Says(kActorMcCoy, 690, kAnimationModeTalk); //00-0690.AUD	Gotcha.
			}
		} else {
			Actor_Says(kActorMcCoy, 4040, 17); //00-4040.AUD	Appreciate it, Lieutenant.
		}
		Game_Flag_Set(kFlagTB07TyrellMeeting);
		Game_Flag_Reset(kFlagTyrellGuardTalkMeeting);
		break;

	case 120: // MONEY
		Actor_Says(kActorMcCoy, 4000, 18);
		if (_vm->_cutContent) {
			if (Actor_Query_Friendliness_To_Other(kActorGuzza, kActorMcCoy) > 50) {
				Actor_Clue_Acquire(kActorMcCoy, kClueGuzzasCash, true, kActorGuzza);
				Actor_Says(kActorGuzza, 1490, 33); //04-1490.AUD	This has got your name written all over it.
				Actor_Change_Animation_Mode(kActorMcCoy, 23);
				Delay(2000);
				if (Player_Query_Agenda() == kPlayerAgendaPolite) {
					Actor_Says(kActorMcCoy, 4055, 13); //00-4055.AUD	Thanks, Lieutenant.
				}
				Actor_Says(kActorGuzza, 520, 33); //04-0520.AUD	Look, this ain't on the department tab, okay? This is a personal loan.
				Actor_Says(kActorGuzza, 530, 31); //04-0530.AUD	This goddamn city doesn't know how to manage funds. They've been flush for years.
				Actor_Says(kActorMcCoy, 4060, 13);
				Actor_Says(kActorGuzza, 540, 31); //04-0540.AUD	Trust me. Ain't nobody getting rich unless they're sneaking some on the side.
				Actor_Says(kActorGuzza, 550, 32); //04-0550.AUD	Hell, I can barely pay for the fuel for my car.
				if (Player_Query_Agenda() == kPlayerAgendaSurly 
				|| Player_Query_Agenda() == kPlayerAgendaErratic) {
					Actor_Says(kActorMcCoy, 4065, 18); //00-4065.AUD	Ever hear of public transportation?
					Actor_Says(kActorGuzza, 560, 34);
					Actor_Modify_Friendliness_To_Other(kActorGuzza, kActorMcCoy, -2);
				} else if (Player_Query_Agenda() == kPlayerAgendaPolite) {
					Actor_Says(kActorMcCoy, 2305, 14); //00-2305.AUD	I’m sorry.
					Actor_Modify_Friendliness_To_Other(kActorGuzza, kActorMcCoy, 2);
				} else {
					Actor_Says(kActorMcCoy, 4880, 13); //00-4880.AUD	Is that right?
				}
				if (Query_Difficulty_Level() != kGameDifficultyEasy) {
					Global_Variable_Increment(kVariableChinyen, 100);
				}
			} else {
				Actor_Says(kActorGuzza, 470, 33);	// Hey, I'd love to be your own personal ATM but the department's strapped right now.
				Actor_Says(kActorGuzza, 480, 31);
				if (!Actor_Clue_Query(kActorMcCoy, kClueMcCoyRecoveredHoldensBadge)) {
					Actor_Says(kActorGuzza, 490, 31); //04-0490.AUD	And one of the old-timers is freelancing a contract job.
				}
				Actor_Says(kActorGuzza, 500, 32);
				if (Player_Query_Agenda() == kPlayerAgendaPolite) {
					Actor_Says(kActorMcCoy, 4045, 16); //00-4045.AUD	Okay, okay. Sorry I asked!
				} else {
					Actor_Says(kActorMcCoy, 4880, 13); //00-4880.AUD	Is that right?
				}
				Actor_Says(kActorGuzza, 510, 31);	// Hey, you track down a Rep, you get an advance.
				if (Player_Query_Agenda() != kPlayerAgendaPolite) {
					Actor_Says(kActorMcCoy, 4050, 18); //00-4050.AUD	Gee, wish I'd thought of that.
				}
			}
		} else {
			Actor_Clue_Acquire(kActorMcCoy, kClueGuzzasCash, true, kActorGuzza);
			Actor_Says(kActorGuzza, 520, 33);
			Actor_Says(kActorMcCoy, 4055, 13);
			Actor_Says(kActorGuzza, 530, 31);
			Actor_Says(kActorMcCoy, 4060, 13);
			Actor_Says(kActorGuzza, 540, 31);
			Actor_Says(kActorGuzza, 550, 32);
			Actor_Says(kActorMcCoy, 4065, 18);
			Actor_Says(kActorGuzza, 560, 34);
			if (Query_Difficulty_Level() != kGameDifficultyEasy) {
				Global_Variable_Increment(kVariableChinyen, 100);
			}
		}
		break;

	case 130: // REPORT IN
	//Altered code so Guzza gets angry at McCoy just based on the fact that he let Zuben escape. This fact alone should make Guzza
	//angry and not all the other factors that was included in the code originally.
		if (_vm->_cutContent) {
			if (!Game_Flag_Query(kFlagPS04GuzzaTalkIsFurious)
			&& !Game_Flag_Query(kFlagPS04GuzzaTalkZubenRetired)
			&& Game_Flag_Query(kFlagCT01TalkToHowieAfterZubenMissing)
			&& !Game_Flag_Query(kFlagGuzzaInformed)
			&& (Game_Flag_Query(kFlagZubenRetired)
			|| Actor_Clue_Query(kActorMcCoy, kClueMcCoyKilledRunciter1))) {	
				Actor_Says(kActorMcCoy, 3920, 13); //00-3920.AUD	Bryant go on permanent leave and you get full use of the office, Lieutenant?
				Actor_Says(kActorGuzza, 140, 30); //04-0140.AUD	You'd be amazed at how accommodating a man can be after his hemorrhoids get lanced.
				Actor_Face_Current_Camera(kActorGuzza, true);
				Actor_Says(kActorGuzza, 150, 31); //04-0150.AUD	You've really been surprising the troops around here, kid.
				Actor_Says(kActorGuzza, 160, 32); //04-0160.AUD	Gaff says you worked that retirement like a champ.
				if (!Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
					Actor_Says(kActorMcCoy, 3925, 18); //00-3925.AUD	Just doing the job.
					Actor_Face_Actor(kActorGuzza, kActorMcCoy, true);
					if (!Actor_Clue_Query(kActorMcCoy, kClueMcCoyKilledRunciter1)) {
						Actor_Says(kActorGuzza, 170, 33); //04-0170.AUD	Yeah, well don't get too cocky. Those Sixes can be damn unpredictable.
						Loop_Actor_Walk_To_XYZ(kActorMcCoy, -716.0f, -354.85f, 1042.0f, 0, false, false, true);
						Actor_Face_Actor(kActorMcCoy, kActorGuzza, true);
						Actor_Says(kActorMcCoy, 3930, 13); // 00-3930.AUD	That I know. 
					} else {
						Loop_Actor_Walk_To_XYZ(kActorMcCoy, -716.0f, -354.85f, 1042.0f, 0, false, false, true);
						Actor_Face_Actor(kActorMcCoy, kActorGuzza, true);
					}
				} else {
					Loop_Actor_Walk_To_XYZ(kActorMcCoy, -716.0f, -354.85f, 1042.0f, 0, false, false, true);
					Actor_Face_Actor(kActorGuzza, kActorMcCoy, true);
					Actor_Says(kActorMcCoy, 4880, 13); //00-4880.AUD	Is that right?
				}
				Game_Flag_Set(kFlagPS04GuzzaTalkZubenRetired);
				Actor_Face_Actor(kActorGuzza, kActorMcCoy, true);
				if (Global_Variable_Query(kVariableChapter) == 1) { // only play this dialogue (about day off) on day one. It doesn't fit in the next days
					Actor_Says(kActorGuzza, 180, 34);	// But I'm proud of you McCoy. Why don't you take the rest of the day off?
					if (Player_Query_Agenda() == kPlayerAgendaSurly 
					|| Player_Query_Agenda() == kPlayerAgendaErratic) {
						Actor_Says(kActorMcCoy, 8200, 14); //00-8200.AUD	When I'm done, maybe.
					} else {
						Actor_Says(kActorMcCoy, 3935, 13);	// Thanks.
					}
					Actor_Says(kActorGuzza, 190, 30); //04-0190.AUD	Payments is wiring the advance to your account as we speak.
					Actor_Says(kActorMcCoy, 3940, 16); //00-3940.AUD	How much? 
					Actor_Says(kActorGuzza, 200, 31); //04-0200.AUD	Couple hundred chinyen. Enough to buy a sandwich or two.
					Actor_Says(kActorGuzza, 210, 33); //04-0210.AUD	We got to hold back the rest until the lab does the autopsy.
					Actor_Says(kActorGuzza, 220, 34); //04-0220.AUD	Paperwork, you know. Shouldn't take more than a couple of days.
					Actor_Says(kActorMcCoy, 3945, 17); //00-3945.AUD	So the check's in the mail.
					if (Actor_Query_Friendliness_To_Other(kActorGuzza, kActorMcCoy) > 50) {
						Actor_Says(kActorGuzza, 230, 32); //04-0230.AUD	Hey, don't worry. The boys upstairs want to keep our best and brightest happy.
					}
					Actor_Says(kActorGuzza, 240, 31); //04-0240.AUD	Any idea what you want to spend it on?
					Actor_Says(kActorMcCoy, 3950, 13); //00-3950.AUD	I was thinking maybe a companion for my animal at home.
					Actor_Says(kActorGuzza, 250, 34); //04-0250.AUD	Forget that. Buy yourself something. Something nice.
					Actor_Says(kActorGuzza, 260, 33); //04-0260.AUD	Once you start carving up that juicy bacon, kid, the taste never goes away.
					Actor_Says(kActorGuzza, 270, 32); //04-0270.AUD	The great things in life…? Believe me you'll just be wanting more and more.
					if (!Game_Flag_Query(kFlagZubenBountyPaid)) { // get retirement money only if haven't been auto-paid at end of Day 1 (sleep trigger)
						if (Query_Difficulty_Level() != kGameDifficultyEasy) {
							Global_Variable_Increment(kVariableChinyen, 200);
						}
						Game_Flag_Set(kFlagZubenBountyPaid); // not a proper bug, but was missing from original code, so the flag would remain in non-consistent state in this case
					}
					if (!Game_Flag_Query(kFlagRunciterBountyPaid)) { // get retirement money only if haven't been auto-paid at end of Day 1 (sleep trigger)
						if (Query_Difficulty_Level() != kGameDifficultyEasy) {
							Global_Variable_Increment(kVariableChinyen, 200);
						}
						Game_Flag_Set(kFlagRunciterBountyPaid); 
					}
				}
			// Made it so Guzza is nice to McCoy if he retired Zuben and Guzza didn't get angry at McCoy. 
			} else if (Game_Flag_Query(kFlagPS04GuzzaTalkZubenRetired)
			&& !Game_Flag_Query(kFlagPS04GuzzaTalkDumpToMainframe)) {
				Actor_Says(kActorMcCoy, 3955, 13); //00-3955.AUD	Bryant on permanent vacation or what, Lieutenant?
				Actor_Says(kActorGuzza, 280, 30); //04-0280.AUD	He sends his regards from the hemorrhoid hospital (soft chuckle). What's the good news?
				Actor_Says(kActorMcCoy, 3960, 18); //00-3960.AUD	Fresh out but I'm following up some leads.
				Game_Flag_Set(kFlagPS04GuzzaTalkDumpToMainframe);
				if (Global_Variable_Query(kVariableChapter) == 1) { // only play this dialogue (about day off) on day one. It doesn't fit in the next days
					if (Actor_Query_Friendliness_To_Other(kActorGuzza, kActorMcCoy) > 50) {
						Actor_Says(kActorGuzza, 290, 32);	// Don't push it kid. You look like you're beat anyway.
						Actor_Says(kActorGuzza, 300, 31);	// Why don't you rest them dogs the rest of the day.
						Actor_Says(kActorMcCoy, 3965, 13);	// I still got plenty energy.
						Actor_Says(kActorGuzza, 310, 33);	// That's an order McCoy.
						Actor_Says(kActorGuzza, 320, 34);	// I'm ordering you to relax.
						if (Player_Query_Agenda() == kPlayerAgendaSurly 
						|| Player_Query_Agenda() == kPlayerAgendaErratic) {
							Actor_Says(kActorMcCoy, 8200, 13); //00-8200.AUD	When I'm done, maybe.
						}
					}
				}
			} else if (!Game_Flag_Query(kFlagPS04GuzzaTalkDumpToMainframe)) {
				Actor_Says(kActorMcCoy, 3920, 13); //00-3920.AUD	Bryant go on permanent leave and you get full use of the office, Lieutenant?
				Actor_Says(kActorGuzza, 570, 32); //04-0570.AUD	You know the procedure. Dump it all in the mainframe upstairs and I'll read it later.
				if (Player_Query_Agenda() != kPlayerAgendaSurly 
				|| Player_Query_Agenda() != kPlayerAgendaErratic) {
					Actor_Says(kActorMcCoy, 4070, 13); //00-4070.AUD	You got it.
				}
				Game_Flag_Set(kFlagPS04GuzzaTalkDumpToMainframe);
			} else if (Game_Flag_Query(kFlagPS04GuzzaTalkDumpToMainframe)
			&& Actor_Query_Friendliness_To_Other(kActorGuzza, kActorMcCoy) > 50) {
				Actor_Says(kActorMcCoy, 8514, 18); //00-8514.AUD	Got anything new to tell me?
				Actor_Says(kActorGuzza, 1510, 30); //04-1510.AUD	You’re the one on the job, kid. My own case looks stacked up on a desk a yard high. 
				if (Player_Query_Agenda() == kPlayerAgendaPolite) {
					Actor_Says(kActorMcCoy, 2305, 16); //00-2305.AUD	I’m sorry.
				}
				Actor_Says(kActorGuzza, 1500, 30); //04-1500.AUD	Anything comes up, kid, you’ll be the first to know.
			} else if (Game_Flag_Query(kFlagPS04GuzzaTalkDumpToMainframe)
			&& Actor_Query_Friendliness_To_Other(kActorGuzza, kActorMcCoy) < 51) {
				if (Player_Query_Agenda() == kPlayerAgendaPolite) {
					Actor_Says(kActorMcCoy, 4020, 13); //00-4020.AUD	Sorry to bother you, Lieutenant. I was just checking in.
					Actor_Says(kActorGuzza, 580, 34);
					if (!Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
						Actor_Says(kActorMcCoy, 4075, 16); //00-4075.AUD	Yeah, suicidal targets would make my job a lot easier.
						Actor_Says(kActorGuzza, 590, 33);	
					}
				}
				Actor_Says(kActorMcCoy, 5150, 16); //00-5150.AUD	One more thing.
				Actor_Says(kActorGuzza, 130, 30); //04-0130.AUD	Don't got time for you now, McCoy. Hit me later.
				Actor_Face_Current_Camera(kActorGuzza, true);
				if (Player_Query_Agenda() != kPlayerAgendaSurly
				&& (Player_Query_Agenda() != kPlayerAgendaErratic)) {
					Actor_Says(kActorMcCoy, 3915, 13);
				} else {
					Actor_Says(kActorMcCoy, 5075, 13); //00-5075.AUD	Hey, pal.
				}
			}
		} else if (Game_Flag_Query(kFlagZubenRetired)
		    && !Game_Flag_Query(kFlagPS04GuzzaTalkZubenRetired)
		) {
			Actor_Says(kActorMcCoy, 3920, 13);
			Actor_Says(kActorGuzza, 140, 30);
			Actor_Face_Current_Camera(kActorGuzza, true);
			Actor_Says(kActorGuzza, 150, 31);
			Actor_Says(kActorGuzza, 160, 32);
			Actor_Says(kActorMcCoy, 3925, 18);
			Actor_Face_Actor(kActorGuzza, kActorMcCoy, true);
			Actor_Says(kActorGuzza, 170, 33);
			Loop_Actor_Walk_To_XYZ(kActorMcCoy, -716.0f, -354.85f, 1042.0f, 0, false, false, false);
			Actor_Face_Actor(kActorMcCoy, kActorGuzza, true);
			Actor_Says(kActorMcCoy, 3930, 13);
			Actor_Face_Actor(kActorGuzza, kActorMcCoy, true);
#if BLADERUNNER_ORIGINAL_BUGS
			Actor_Says(kActorGuzza, 180, 34);	// But I'm proud of you McCoy. Why don't you take the rest of the day off?
			Actor_Says(kActorMcCoy, 3935, 13);	// Thanks.
#else
			if (Global_Variable_Query(kVariableChapter) == 1) { // only play this dialogue (about day off) on day one. It doesn't fit in the next days
				Actor_Says(kActorGuzza, 180, 34);	// But I'm proud of you McCoy. Why don't you take the rest of the day off?
				Actor_Says(kActorMcCoy, 3935, 13);	// Thanks.
			}
#endif // BLADERUNNER_ORIGINAL_BUGS
			Actor_Says(kActorGuzza, 190, 30);
			Actor_Says(kActorMcCoy, 3940, 16);
			Actor_Says(kActorGuzza, 200, 31);
			Actor_Says(kActorGuzza, 210, 33);
			Actor_Says(kActorGuzza, 220, 34);
			Actor_Says(kActorMcCoy, 3945, 17);
			Actor_Says(kActorGuzza, 230, 32);
			Actor_Says(kActorGuzza, 240, 31);
			Actor_Says(kActorMcCoy, 3950, 13);
			Actor_Says(kActorGuzza, 250, 34);
			Actor_Says(kActorGuzza, 260, 33);
			Actor_Says(kActorGuzza, 270, 32);
			Game_Flag_Set(kFlagPS04GuzzaTalkZubenRetired);
#if BLADERUNNER_ORIGINAL_BUGS
			if (Query_Difficulty_Level() != kGameDifficultyEasy) {
				Global_Variable_Increment(kVariableChinyen, 200);
			}
			Game_Flag_Set(kFlagZubenBountyPaid);
#else
			if (!Game_Flag_Query(kFlagZubenBountyPaid)) { // get retirement money only if haven't been auto-paid at end of Day 1 (sleep trigger)
				if (Query_Difficulty_Level() != kGameDifficultyEasy) {
					Global_Variable_Increment(kVariableChinyen, 200);
				}
				Game_Flag_Set(kFlagZubenBountyPaid); // not a proper bug, but was missing from original code, so the flag would remain in non-consistent state in this case
			}
#endif // BLADERUNNER_ORIGINAL_BUGS
		} else if (Game_Flag_Query(kFlagZubenSpared)
		&& !Game_Flag_Query(kFlagPS04GuzzaTalkZubenEscaped)) {
			Actor_Says(kActorMcCoy, 3955, 13); //00-3955.AUD	Bryant on permanent vacation or what, Lieutenant?
			Actor_Says(kActorGuzza, 280, 30);
			Actor_Says(kActorMcCoy, 3960, 18); //00-3960.AUD	Fresh out but I'm following up some leads.
#if BLADERUNNER_ORIGINAL_BUGS
			Actor_Says(kActorGuzza, 290, 32);	// Don't push it kid. You look like you're beat anyway.
			Actor_Says(kActorGuzza, 300, 31);	// Why don't you rest them dogs the rest of the day.
			Actor_Says(kActorMcCoy, 3965, 13);	// I still got plenty energy.
			Actor_Says(kActorGuzza, 310, 33);	// That's an order McCoy.
			Actor_Says(kActorGuzza, 320, 34);	// I'm ordering you to relax.
#else
			if (Global_Variable_Query(kVariableChapter) == 1) { // only play this dialogue (about day off) on day one. It doesn't fit in the next days
				Actor_Says(kActorGuzza, 290, 32);	// Don't push it kid. You look like you're beat anyway.
				Actor_Says(kActorGuzza, 300, 31);	// Why don't you rest them dogs the rest of the day.
				Actor_Says(kActorMcCoy, 3965, 13);	// I still got plenty energy.
				Actor_Says(kActorGuzza, 310, 33);	// That's an order McCoy.
				Actor_Says(kActorGuzza, 320, 34);	// I'm ordering you to relax.
			}
#endif // BLADERUNNER_ORIGINAL_BUGS
			Game_Flag_Set(kFlagPS04GuzzaTalkZubenEscaped);
		} else if (( Actor_Clue_Query(kActorMcCoy, kClueChopstickWrapper)
		            || Actor_Clue_Query(kActorMcCoy, kClueSushiMenu))
		           &&  Actor_Clue_Query(kActorMcCoy, kClueRunciterInterviewA)
		           &&  Actor_Query_Friendliness_To_Other(kActorGuzza, kActorMcCoy) < 50
		           && !Game_Flag_Query(kFlagPS04GuzzaTalkIsFurious)
		) {
			Actor_Says(kActorMcCoy, 3970, 18);
			Actor_Says(kActorGuzza, 330, 30);
			Actor_Says(kActorGuzza, 340, 32);
			Actor_Says(kActorMcCoy, 3975, 13);
			Actor_Says(kActorGuzza, 350, 31);
			Actor_Says(kActorGuzza, 360, 34);
			Actor_Says(kActorMcCoy, 3980, 13);
			Actor_Says(kActorGuzza, 370, 33);
			Actor_Says(kActorGuzza, 380, 32);
			Actor_Says(kActorGuzza, 390, 31);
			Actor_Says(kActorMcCoy, 3985, 18);
			Actor_Says(kActorGuzza, 400, 34);
			Actor_Says(kActorGuzza, 410, 31);
			Game_Flag_Set(kFlagPS04GuzzaTalkIsFurious);
		} else if ((Actor_Clue_Query(kActorMcCoy, kClueChopstickWrapper)
		            || Actor_Clue_Query(kActorMcCoy, kClueSushiMenu))
		           &&  Actor_Clue_Query(kActorMcCoy, kClueRunciterInterviewA)
		           && !Game_Flag_Query(kFlagPS04GuzzaTalkDumpToMainframe)
		) {
			// McCoy metions Bryant's "vacation",
			// Guzza says about the procedure via Mainframe
			Actor_Says(kActorMcCoy, 3920, 13);
			Actor_Says(kActorGuzza, 570, 32);
			Actor_Says(kActorMcCoy, 4070, 13);
			Game_Flag_Set(kFlagPS04GuzzaTalkDumpToMainframe);
		} else if (Actor_Query_Friendliness_To_Other(kActorGuzza, kActorMcCoy) >= 50) {
			// Main check-in talk
			Actor_Says(kActorMcCoy, 4020, 13);
			Actor_Says(kActorGuzza, 580, 34);
			Actor_Says(kActorMcCoy, 4075, 16);
			Actor_Says(kActorGuzza, 590, 33);
		} else {
			Actor_Says(kActorMcCoy, 4020, 18);
			Actor_Says(kActorGuzza, 130, 30);
			Actor_Face_Current_Camera(kActorGuzza, true);
			Actor_Says(kActorMcCoy, 3915, 13);
		}
		break;

	case 140: // CONFESS TO SHOOTING
		if (_vm->_cutContent) {
			Actor_Says(kActorMcCoy, 4010, 12); //00-4010.AUD	Lieutenant, I-- I shot a guy. Down in Chinatown.
			Actor_Says(kActorGuzza, 600, 31);
			if (Player_Query_Agenda() != kPlayerAgendaSurly 
			&& Player_Query_Agenda() != kPlayerAgendaErratic) {
				if (!Game_Flag_Query(kFlagCT04HomelessBodyFound)) {
					Actor_Says(kActorMcCoy, 4080, 18); //00-4080.AUD	Hey, I'm trying to do the right thing here. I could have left the guy to rot.
				} else {
					Actor_Says(kActorMcCoy, 2305, 16); //00-2305.AUD	I’m sorry.
				}
			} else {
				Actor_Says(kActorMcCoy, 8085, 14); //00-8085.AUD	Me either.
			}
			Actor_Says(kActorGuzza, 610, 33);
			Actor_Face_Heading(kActorGuzza, 400, false);
			Actor_Says(kActorGuzza, 620, 32);
			// add a fade-out here while Guzza calls-in for favors
			Scene_Loop_Start_Special(kSceneLoopModeOnce, kPS04LoopPanToPS04, true);
			Scene_Loop_Set_Default(kPS04LoopMainLoop);
			Delay(1000);
			Actor_Face_Actor(kActorGuzza, kActorMcCoy, true);
			Delay(1000);
			// if McCoy confesses before the body is dumped, then the body should be found (even if in dumpster)
			if (!Game_Flag_Query(kFlagCT04HomelessBodyThrownAway)) {
				Game_Flag_Set(kFlagCT04HomelessBodyFound);
				// return false;
			}
			Actor_Says(kActorGuzza, 700, 34); //04-0700.AUD	So they're calling it a justified shooting.
			if (Player_Query_Agenda() == kPlayerAgendaSurly 
			|| Player_Query_Agenda() == kPlayerAgendaErratic) {
				Actor_Says(kActorMcCoy, 4100, 13); //00-4100.AUD	I kind of thought they might.
			} else {
				Actor_Says(kActorMcCoy, 8265, 18); //00-8265.AUD	Really?
			}
			if (Actor_Query_Friendliness_To_Other(kActorGuzza, kActorMcCoy) < 51) {
				Actor_Says(kActorGuzza, 710, 31); //04-0710.AUD	That doesn't mean your ass is out of the fire with me, McCoy.
			}
			Actor_Says(kActorGuzza, 720, 34); //04-0720.AUD	You may have put one over on internal affairs but you and I both know the real skinny.
			if (Player_Query_Agenda() == kPlayerAgendaPolite) {
				Actor_Says(kActorMcCoy, 2305, 13); //00-2305.AUD	I’m sorry.
			} else {
				Actor_Says(kActorMcCoy, 4105, 18); //00-4105.AUD	Is that right?
			}
	#if BLADERUNNER_ORIGINAL_BUGS
			Loop_Actor_Walk_To_XYZ(kActorMcCoy, -668.0f, -350.85f, 962.0f, 0, false, false, false);
	#else
			// enforce stop running (if was running) - McCoy running in Guzza's office in this scene looks bad
			Loop_Actor_Walk_To_XYZ(kActorMcCoy, -668.0f, -350.85f, 962.0f, 0, false, false, true);
	#endif // BLADERUNNER_ORIGINAL_BUGS
			Actor_Says(kActorGuzza, 730, 32); //04-0730.AUD	You can't just go around waxing civilians.
			Actor_Face_Actor(kActorMcCoy, kActorGuzza, true);
			Loop_Actor_Walk_To_XYZ(kActorMcCoy, -716.0f, -354.85f, 1042.0f, 0, false, false, false);
			Actor_Face_Actor(kActorGuzza, kActorMcCoy, true);
			if (Actor_Query_Friendliness_To_Other(kActorGuzza, kActorMcCoy) > 50) {
				Actor_Says(kActorGuzza, 740, 31); //04-0740.AUD	Look, McCoy. I know how it is on the street.
				Actor_Says(kActorGuzza, 750, 32); //04-0750.AUD	It's easy for a Blade Runner to step over the line.
			}
			Actor_Says(kActorGuzza, 760, 33); //04-0760.AUD	You do this job right, you got a long career ahead of you. But you screw up again...
			Actor_Face_Actor(kActorMcCoy, kActorGuzza, true);
			Actor_Says(kActorMcCoy, 4110, 13); //00-4110.AUD	I can handle it.
			if (Actor_Query_Friendliness_To_Other(kActorGuzza, kActorMcCoy) < 51) {
				Actor_Says(kActorGuzza, 770, 32); //04-0770.AUD	You'd better.
				Actor_Says(kActorGuzza, 780, 31); 
			}
			//Jake - added in a flag so at the end of act 3 when talking to Crystal she will also mention McCoy killing someone if
			//he killed the homeless guy and told Guzza about it. Guzza ends up using it against McCoy to get him out of the way.
			//Also if Guzza liked you he will now be angry with you and the next dialogues you receive is him being angry with McCoy.
			Game_Flag_Set(kFlagGuzzaInformed);
			Actor_Modify_Friendliness_To_Other(kActorGuzza, kActorMcCoy, -2);
		} else {
			Actor_Says(kActorMcCoy, 4010, 12);
			Actor_Says(kActorGuzza, 600, 31);
			Actor_Says(kActorMcCoy, 4080, 18); //00-4080.AUD	Hey, I'm trying to do the right thing here. I could have left the guy to rot.
			Actor_Says(kActorGuzza, 610, 33);
			Actor_Face_Heading(kActorGuzza, 400, false);
			Actor_Says(kActorGuzza, 620, 32);
			Actor_Says(kActorGuzza, 700, 34);
			Actor_Says(kActorMcCoy, 4100, 13); //00-4100.AUD	I kind of thought they might.
			Actor_Says(kActorGuzza, 710, 31); //04-0710.AUD	That doesn't mean your ass is out of the fire with me, McCoy.
			Actor_Says(kActorGuzza, 720, 34); //04-0720.AUD	You may have put one over on internal affairs but you and I both know the real skinny.
			Actor_Says(kActorMcCoy, 4105, 18); //00-4105.AUD	Is that right?
	#if BLADERUNNER_ORIGINAL_BUGS
			Loop_Actor_Walk_To_XYZ(kActorMcCoy, -668.0f, -350.85f, 962.0f, 0, false, false, false);
	#else
			// enforce stop running (if was running) - McCoy running in Guzza's office in this scene looks bad
			Loop_Actor_Walk_To_XYZ(kActorMcCoy, -668.0f, -350.85f, 962.0f, 0, false, false, true);
	#endif // BLADERUNNER_ORIGINAL_BUGS
			Actor_Says(kActorGuzza, 730, 32);
			Actor_Face_Actor(kActorMcCoy, kActorGuzza, true);
			Loop_Actor_Walk_To_XYZ(kActorMcCoy, -716.0f, -354.85f, 1042.0f, 0, false, false, false);
			Actor_Face_Actor(kActorGuzza, kActorMcCoy, true);
			Actor_Says(kActorGuzza, 740, 31);
			Actor_Says(kActorGuzza, 750, 32);
			Actor_Says(kActorGuzza, 760, 33);
			Actor_Face_Actor(kActorMcCoy, kActorGuzza, true);
			Actor_Says(kActorMcCoy, 4110, 13);
			Actor_Says(kActorGuzza, 770, 32);
			Actor_Says(kActorGuzza, 780, 31); 
		}
		break;

	case 150: // HOLDEN'S BADGE
		Actor_Says(kActorMcCoy, 4015, 16);
		Actor_Says(kActorGuzza, 630, 34);
		Actor_Says(kActorMcCoy, 4085, 19);
		Actor_Says(kActorMcCoy, 4090, 18);
		Actor_Says(kActorGuzza, 640, 31);
		Actor_Says(kActorGuzza, 650, 32);
		Actor_Says(kActorGuzza, 670, 34);
		Actor_Says(kActorMcCoy, 4095, 17); 
		Actor_Says(kActorGuzza, 680, 32);
		if (_vm->_cutContent) {
			Loop_Actor_Walk_To_XYZ(kActorMcCoy, -716.0f, -354.85f, 1042.0f, 0, false, false, true);
			Actor_Face_Actor(kActorMcCoy, kActorGuzza, true);
			Actor_Change_Animation_Mode(kActorMcCoy, 23);
			Delay(800);
			Item_Pickup_Spin_Effect_From_Actor(kModelAnimationBadge, kActorGuzza, 0, 0);
			Delay(800);
			Actor_Says(kActorMcCoy, 8170, 13); //00-8170.AUD	There you go.
		}
		Actor_Says(kActorGuzza, 690, 31);
		if (_vm->_cutContent) {	
			Actor_Clue_Acquire(kActorMcCoy, kClueMcCoyRecoveredHoldensBadge, true, kActorGuzza);
			Actor_Clue_Lose(kActorMcCoy, kClueHoldensBadge);
			Actor_Clue_Acquire(kActorGuzza, kClueHoldensBadge, true, -1);
			Actor_Modify_Friendliness_To_Other(kActorGuzza, kActorMcCoy, 2);
		} 
		break;

	case 160: // DONE
		// nothing here
		break;
	}
}

} // End of namespace BladeRunner
