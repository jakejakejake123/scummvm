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

	if ( Global_Variable_Query(kVariableChapter) == 2
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
		} else if (!Actor_Clue_Query(kActorMcCoy, kClueWeaponsOrderForm)) {
			Item_Remove_From_World(kItemWeaponsOrderForm);
			Item_Pickup_Spin_Effect(kModelAnimationOriginalRequisitionForm, 464, 362);
			Actor_Says(kActorMcCoy, 4485, kAnimationModeTalk);
			Actor_Clue_Acquire(kActorMcCoy, kClueWeaponsOrderForm, true, kActorMcCoy);
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
	// Code for the scene where Guzza gets angry at you for retiring Rachael.
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
		Actor_Set_Goal_Number(kActorMcCoy, kGoalMcCoyArrested);
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
	if (Global_Variable_Query(kVariableChapter) > 1) {
		// Made it so this flag which activates after you ask the Tyrell guard for a meeting with Tyrell is the trigger for requesting a meeing with Tyrell from Guzza
		// and not the attempted file access clue.
		if (_vm->_cutContent) {
			if	(Game_Flag_Query(kFlagTyrellGuardTalkMeeting)) {
				DM_Add_To_List_Never_Repeat_Once_Selected(110, 5, 7, 4); // REQUEST TYRELL MEETING
			}
		} else if (Actor_Clue_Query(kActorMcCoy, kClueAttemptedFileAccess)) {
			DM_Add_To_List_Never_Repeat_Once_Selected(110, 5, 7, 4); // REQUEST TYRELL MEETING
		}
		DM_Add_To_List_Never_Repeat_Once_Selected(120, 1, -1, -1); // MONEY
		if (Actor_Clue_Query(kActorMcCoy, kClueHoldensBadge)) {
			DM_Add_To_List_Never_Repeat_Once_Selected(150, 7, 6, 5); // HOLDEN'S BADGE
		}
	}
	if (Game_Flag_Query(kFlagCT04HomelessKilledByMcCoy)) {
		DM_Add_To_List_Never_Repeat_Once_Selected(140, 3, -1, -1); // CONFESS TO SHOOTING
	}
	DM_Add_To_List(130, 1, 1, 1); // REPORT IN
	Dialogue_Menu_Add_DONE_To_List(160); // DONE

	Dialogue_Menu_Appear(320, 240);
	int answer = Dialogue_Menu_Query_Input();
	Dialogue_Menu_Disappear();

	switch (answer) {
	case 110: // REQUEST TYRELL MEETING
		if (_vm->_cutContent) {
			Actor_Says(kActorGuzza, 420, 31);
		}
		Actor_Says(kActorMcCoy, 3990, 19);
		Actor_Says(kActorMcCoy, 3995, 17);
		if (_vm->_cutContent) {
			Actor_Says(kActorGuzza, 430, 33);
			Actor_Says(kActorMcCoy, 4025, 18);
			Actor_Says(kActorMcCoy, 4030, 12);
		}
		Actor_Says(kActorGuzza, 440, 31);
		Actor_Says(kActorMcCoy, 4035, 13);
		Actor_Says(kActorGuzza, 450, 34);
		Actor_Says(kActorGuzza, 460, 33);
		Actor_Says(kActorMcCoy, 4040, 17);
		Game_Flag_Set(kFlagTB07TyrellMeeting);
		break;

	case 120: // MONEY
		Actor_Says(kActorMcCoy, 4000, 18);
		if (_vm->_cutContent) {
			// Using cut content we have two cases:
			// 1. Guzza can accept the loan (as in ORIGINAL)
			// 2. Guzza can refuse the loan (CUT)
			// Basically, if McCoy hasn't retired Zuben or if he drunk away his money at the bar
			// then he'll have a small amount of chinyen and Guzza should accept the loan

			//JakeJakeJake123 - Altered code so Guzza gives you the loan if you retired Zuben and Guzza
			//likes you. Considering Guzza says if you retire a rep you get an advance when he refuses the loan, this make sense.
			//I mean if you let Zuben go and you get the Guzza is furious dialogue it would not make any 
			//sense for Guzza to give you the loan since he is upset with you.
		
			if (Actor_Query_Friendliness_To_Other(kActorGuzza, kActorMcCoy) >= 50) {
				Actor_Clue_Acquire(kActorMcCoy, kClueGuzzasCash, true, kActorGuzza);
				Actor_Says(kActorGuzza, 520, 33);
				Actor_Says(kActorMcCoy, 4055, 13);
				Actor_Says(kActorGuzza, 530, 31); //04-0530.AUD	This goddamn city doesn't know how to manage funds. They've been flush for years.
				//Added in some lines.
				Actor_Says(kActorMcCoy, 8265, 13); //00-8265.AUD	Really?
				Actor_Says(kActorGuzza, 1520, 33); //04-1520.AUD	Everything I say is as true as holy writ.
				//Fixed this line.
				Actor_Says(kActorMcCoy, 4060, 13);
				Actor_Says(kActorGuzza, 540, 31); //04-0540.AUD	Trust me. Ain't nobody getting rich unless they're sneaking some on the side.
				Actor_Says(kActorGuzza, 550, 32);
				Actor_Says(kActorMcCoy, 4065, 18);
				Actor_Says(kActorGuzza, 560, 34);
				if (Query_Difficulty_Level() != kGameDifficultyEasy) {
					Global_Variable_Increment(kVariableChinyen, 100);
				}
			} else {
				// McCoy has plenty cash already - Guzza denies the loan
				Actor_Says(kActorGuzza, 470, 33);	// Hey, I'd love to be your own personal ATM but the department's strapped right now.
				Actor_Says(kActorGuzza, 480, 31);
				Actor_Says(kActorGuzza, 490, 31);
				Actor_Says(kActorGuzza, 500, 32);
				Actor_Says(kActorMcCoy, 4045, 16);
				Actor_Says(kActorGuzza, 510, 31);	// Hey, you track down a Rep, you get an advance.
				Actor_Says(kActorMcCoy, 4050, 18);
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
		if (_vm->_cutContent 
			&& Game_Flag_Query(kFlagZubenSpared)
			&& !Game_Flag_Query(kFlagPS04GuzzaTalkIsFurious)) {
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
				// Lowered friendlines towards Guzza and McCoy so a conversation where Guzza tells you to go away will now play.
				Actor_Modify_Friendliness_To_Other(kActorGuzza, kActorMcCoy, -5);
				Game_Flag_Set(kFlagPS04GuzzaTalkIsFurious);
				// Made so Guzza will also not get angry with McCoy if he at least retired Izo or Runciter.
			} else if 
				((Game_Flag_Query(kFlagZubenRetired)
				|| Game_Flag_Query(kFlagMcCoyRetiredIzo)
				|| Game_Flag_Query(kFlagMcCoyRetiredRunciter))
				&& !Game_Flag_Query(kFlagPS04GuzzaTalkIsFurious)
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
					Actor_Modify_Friendliness_To_Other(kActorGuzza, kActorMcCoy, 5);
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
		// Made it so Guzza is nice to McCoy if he retired Zuben and Guzza didn't get angry at McCoy.
		} else if (_vm->_cutContent 
		    && !Game_Flag_Query(kFlagPS04GuzzaTalkIsFurious)
		    && Game_Flag_Query(kFlagPS04GuzzaTalkZubenRetired)
			&& Actor_Query_Friendliness_To_Other(kActorGuzza, kActorMcCoy) >= 50
		) {
			Actor_Says(kActorMcCoy, 3955, 13);
			Actor_Says(kActorGuzza, 280, 30);
			Actor_Says(kActorMcCoy, 3960, 18);
				if (Global_Variable_Query(kVariableChapter) == 1) { // only play this dialogue (about day off) on day one. It doesn't fit in the next days
				Actor_Says(kActorGuzza, 290, 32);	// Don't push it kid. You look like you're beat anyway.
				Actor_Says(kActorGuzza, 300, 31);	// Why don't you rest them dogs the rest of the day.
				Actor_Says(kActorMcCoy, 3965, 13);	// I still got plenty energy.
				Actor_Says(kActorGuzza, 310, 33);	// That's an order McCoy.
				Actor_Says(kActorGuzza, 320, 34);	// I'm ordering you to relax.
			}
			} else if (!_vm->_cutContent 
			 && Game_Flag_Query(kFlagZubenSpared)
		     && !Game_Flag_Query(kFlagPS04GuzzaTalkZubenEscaped)
		) {
			Actor_Says(kActorMcCoy, 3955, 13);
			Actor_Says(kActorGuzza, 280, 30);
			Actor_Says(kActorMcCoy, 3960, 18);
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
		} else if ((Actor_Clue_Query(kActorMcCoy, kClueChopstickWrapper)
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
			//Jake - Added in some banter dialogue for McCoy and Guzza. Also this conversation will now play since McCoys friendliness was lowered during
			//Guzza is furious conversation.
			if (_vm->_cutContent) {
				Actor_Says(kActorMcCoy, 8514, 18); //00-8514.AUD	Got anything new to tell me?
				Actor_Says(kActorGuzza, 1510, 30); //04-1510.AUD	You’re the one on the job, kid. My own case looks stacked up on a desk a yard high. 
				Actor_Says(kActorMcCoy, 2305, 16); //00-2305.AUD	I’m sorry.
				Actor_Says(kActorGuzza, 1500, 30); //04-1500.AUD	Anything comes up, kid, you’ll be the first to know.
				Actor_Says(kActorMcCoy, 5150, 16); //00-5150.AUD	One more thing.
			}
			Actor_Says(kActorGuzza, 130, 30); //04-0130.AUD	Don't got time for you now, McCoy. Hit me later.
			Actor_Face_Current_Camera(kActorGuzza, true);
			Actor_Says(kActorMcCoy, 3915, 13);
		}
		break;

	case 140: // CONFESS TO SHOOTING
		Actor_Says(kActorMcCoy, 4010, 12);
		Actor_Says(kActorGuzza, 600, 31);
		Actor_Says(kActorMcCoy, 4080, 18);
		Actor_Says(kActorGuzza, 610, 33);
		Actor_Face_Heading(kActorGuzza, 400, false);
		Actor_Says(kActorGuzza, 620, 32);
		if (_vm->_cutContent) {
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
		}
		Actor_Says(kActorGuzza, 700, 34);
		Actor_Says(kActorMcCoy, 4100, 13);
		Actor_Says(kActorGuzza, 710, 31);
		Actor_Says(kActorGuzza, 720, 34);
		Actor_Says(kActorMcCoy, 4105, 18);
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
		//Jake - added in a flag so at the end of act 3 when talking to Crystal she will also mention McCoy killing someone if
		//he killed the homeless guy and told Guzza about it. Guzza ends up using it against McCoy to get him out of the way.
		//Also if Guzza liked you he will now be angry with you and the next dialogues you receive is him being angry with McCoy.
		if (_vm->_cutContent) {
			Game_Flag_Set(kFlagGuzzaInformed);
			Actor_Modify_Friendliness_To_Other(kActorGuzza, kActorMcCoy, -6);
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
		Actor_Says(kActorGuzza, 690, 31);
		//Jake - Made it so your friendliness with Guzza increases when you show him the badge.
		//Made it so when you show Holdens badge to Guzza you give it to him. It would not make any sense to show it to him
		//and to also have the option to give it to Bob so it looks like he found it. Also added in the McCoy recovered Holdens badge clue.
		if (_vm->_cutContent) {
			Actor_Clue_Acquire(kActorMcCoy, kClueMcCoyRecoveredHoldensBadge, true, kActorGuzza);
			Actor_Clue_Lose(kActorMcCoy, kClueHoldensBadge);
			Actor_Clue_Acquire(kActorGuzza, kClueHoldensBadge, true, kActorMcCoy);
			Actor_Modify_Friendliness_To_Other(kActorGuzza, kActorMcCoy, 8);
		}
		break;

	case 160: // DONE
		// nothing here
		break;
	}
}

} // End of namespace BladeRunner
