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

enum kRC02Exits {
	kRC02ExitRC01 = 0,
	kRC02ExitRC51 = 1
};

void SceneScriptRC02::InitializeScene() {
	if (Game_Flag_Query(kFlagRC01toRC02)) {
		Setup_Scene_Information(-103.0f, -1238.89f, 108603.04f, 1007);
	} else {
		Setup_Scene_Information(-20.2f, -1238.89f, 108100.73f, 539);
	}
	Scene_Exit_Add_2D_Exit(kRC02ExitRC01, 0, 460, 639, 479, 2);
	if (Game_Flag_Query(kFlagRC51Available)) {
		Scene_Exit_Add_2D_Exit(kRC02ExitRC51, 265, 58, 346, 154, 0);
	}
	if (_vm->_cutContent
	    && Global_Variable_Query(kVariableChapter) == 1
	    && !Game_Flag_Query(kFlagRC02McCoyCommentsOnVideoScreens)) {
		Scene_2D_Region_Add(0, 187, 104, 235, 150);// broken screen
	}
	Ambient_Sounds_Remove_All_Non_Looping_Sounds(false);
	Ambient_Sounds_Add_Looping_Sound(kSfxBRBED5,   50,   1, 1);
	Ambient_Sounds_Add_Looping_Sound(kSfxWINDLOP8, 75,   1, 1);
	Ambient_Sounds_Add_Looping_Sound(kSfxCTRUNOFF, 30, 100, 1);
	Ambient_Sounds_Add_Sound(kSfxSWEEP3,   5, 20, 10, 10, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSWEEP4,   5, 20, 10, 10, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxPETDEAD1, 5, 40,  6,  6, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxPETDEAD3, 5, 40,  6,  6, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxPETDEAD4, 5, 40,  6,  6, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxPETDEAD5, 5, 40,  6,  6, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Speech_Sound(kActorOfficerLeary,    250, 10u, 60u, 5, 5, 100, 100, -101, -101, 1, 1);
	Ambient_Sounds_Add_Speech_Sound(kActorOfficerLeary,    330, 10u, 60u, 5, 5, 100, 100, -101, -101, 1, 1);
	Ambient_Sounds_Add_Speech_Sound(kActorOfficerGrayford, 380, 10u, 60u, 5, 5, 100, 100, -101, -101, 1, 1);
	Ambient_Sounds_Add_Speech_Sound(kActorOfficerGrayford, 510, 10u, 60u, 5, 5, 100, 100, -101, -101, 1, 1);
	Ambient_Sounds_Add_Speech_Sound(kActorDispatcher,       80, 10u, 60u, 5, 5, 100, 100, -101, -101, 1, 1);
	Ambient_Sounds_Add_Speech_Sound(kActorDispatcher,      160, 10u, 60u, 5, 5, 100, 100, -101, -101, 1, 1);
	Ambient_Sounds_Add_Sound(kSfxSIREN2,  20, 80, 10, 20,  100, 100, -101, -101, 0, 0);
}

void SceneScriptRC02::SceneLoaded() {
	Obstacle_Object("TABLETOP", true);
	Obstacle_Object("DRAPE01", true);
	Obstacle_Object("DRAPE03", true);
	Obstacle_Object("DRAPE04", true);
	Obstacle_Object("DRAPE05", true);
	Obstacle_Object("DRAPE06", true);
	Obstacle_Object("DRAPE07", true);
	Obstacle_Object("OUTR_DESK", true);
	Obstacle_Object("CAGE_BASE", true);
	Obstacle_Object("POLE_ROP01", true);
	Unobstacle_Object("LEGS", true);
	Unobstacle_Object("SLATS01", true);
	Unobstacle_Object("DRAPE07", true);
	if (_vm->_cutContent) {
		// improvement: broaden path for Runciter to his desk
		Unobstacle_Object("GRD ROPE04", true);
	}
	Clickable_Object("SCRTY CA03");
	Unclickable_Object("GRL_DSKLEG");
	Unclickable_Object("CURTAIN");
	if (_vm->_cutContent) {
		if (Global_Variable_Query(kVariableChapter) == 1
		    && !Game_Flag_Query(kFlagMcCoyCommentsOnMurderedAnimals)
		    && !Actor_Clue_Query(kActorMcCoy, kClueLabCorpses)
		) {
			Clickable_Object("DRAPE01");
			Clickable_Object("DRAPE02");
			Clickable_Object("DRAPE03");
			Clickable_Object("DRAPE04");
			Clickable_Object("DRAPE05");
			Clickable_Object("DRAPE06");
			Clickable_Object("DRAPE07");
		} else {
			Unclickable_Object("DRAPE01");
			Unclickable_Object("DRAPE02");
			Unclickable_Object("DRAPE03");
			Unclickable_Object("DRAPE04");
			Unclickable_Object("DRAPE05");
			Unclickable_Object("DRAPE06");
			Unclickable_Object("DRAPE07");
		}
		// If Crystal retired Runciter she leaves a cigarette on the floor.
		if (_vm->_cutContent &&
			(Game_Flag_Query(kFlagCrystalRetiredRunciter))) { 
			Item_Add_To_World(kItemCigarette, kModelAnimationCrystalsCigarette, kSetRC02_RC51, -88.19, -1238.74, 108483.28, 0, 12, 12, false, true, false, true);
		}
	} else {
		// original code
		Unclickable_Object("DRAPE01");
		Unclickable_Object("DRAPE02");
		Unclickable_Object("DRAPE03");
		Unclickable_Object("DRAPE05");
		Unclickable_Object("DRAPE06");
		Unclickable_Object("DRAPE07");
	}

	if (Actor_Clue_Query(kActorMcCoy, kClueRuncitersVideo) || Global_Variable_Query(kVariableChapter) > 1) {
		Unclickable_Object("SCRTY CA03");
	}
	if (!Game_Flag_Query(kFlagRC02ShellCasingsTaken)) {
		Item_Add_To_World(kItemShellCasingA, kModelAnimationShellCasings, kSetRC02_RC51, -52.88f, -1238.89f, 108467.74f, 256, 6, 6, false, true, false, true);
		Item_Add_To_World(kItemShellCasingB, kModelAnimationShellCasings, kSetRC02_RC51, -37.16f, -1238.89f, 108456.59f, 512, 6, 6, false, true, false, true);
		Item_Add_To_World(kItemShellCasingC, kModelAnimationShellCasings, kSetRC02_RC51, -62.86f, -1238.89f, 108437.52f, 625, 6, 6, false, true, false, true);
	}
}

bool SceneScriptRC02::MouseClick(int x, int y) {
	return false;
}

bool SceneScriptRC02::ClickedOn3DObject(const char *objectName, bool a2) {
	if ( Object_Query_Click("SCRTY CA03", objectName)
	 && !Actor_Clue_Query(kActorMcCoy, kClueRuncitersVideo)
	) {
		if (Actor_Clue_Query(kActorMcCoy, kClueRunciterInterviewA)
		 && Actor_Query_Is_In_Current_Set(kActorRunciter)
		) {
			AI_Movement_Track_Pause(kActorRunciter);
			Actor_Face_Actor(kActorMcCoy, kActorRunciter, true);
			Actor_Says(kActorMcCoy, 4545, 14);
			Actor_Face_Actor(kActorRunciter, kActorMcCoy, true);
			Actor_Says(kActorRunciter, 0, 14);
			Actor_Says(kActorRunciter, 10, 16);
			Actor_Says(kActorMcCoy, 4550, 13);
			Actor_Says(kActorRunciter, 20, 13);
			Loop_Actor_Walk_To_Waypoint(kActorRunciter, 89, 0, false, false);
			Actor_Face_Actor(kActorMcCoy, kActorRunciter, true);
			Loop_Actor_Walk_To_Waypoint(kActorRunciter, 102, 0, false, false);
			Actor_Face_Actor(kActorMcCoy, kActorRunciter, true);
			Actor_Face_Heading(kActorRunciter, 539, false);
			Delay(2000);
			Loop_Actor_Walk_To_Waypoint(kActorRunciter, 89, 0, false, false);
			Loop_Actor_Walk_To_Actor(kActorRunciter, kActorMcCoy, 24, 0, false);
			Item_Pickup_Spin_Effect(kModelAnimationVideoDisc, 357, 228);
			Actor_Face_Actor(kActorMcCoy, kActorRunciter, true);
			Actor_Face_Actor(kActorRunciter, kActorMcCoy, true);
			Actor_Says(kActorRunciter, 30, 23);
			Actor_Says(kActorMcCoy, 4555, 18);
			Actor_Clue_Acquire(kActorMcCoy, kClueRuncitersVideo, true, kActorRunciter);
			Unclickable_Object("SCRTY CA03");
			AI_Movement_Track_Unpause(kActorRunciter);
			return true;
		} else {
			Actor_Face_Object(kActorMcCoy, "SCRTY CA03", true);
			Actor_Voice_Over(2000, kActorVoiceOver);
			return true;
		}
	}

	if (_vm->_cutContent
	    && Global_Variable_Query(kVariableChapter) == 1
	    && !Game_Flag_Query(kFlagMcCoyCommentsOnMurderedAnimals)
	    && !Actor_Clue_Query(kActorMcCoy, kClueLabCorpses)
	    && (Object_Query_Click("DRAPE01", objectName)
	        || Object_Query_Click("DRAPE02", objectName)
	        || Object_Query_Click("DRAPE03", objectName)
	        || Object_Query_Click("DRAPE04", objectName)
	        || Object_Query_Click("DRAPE05", objectName)
	        || Object_Query_Click("DRAPE06", objectName)
	        || Object_Query_Click("DRAPE07", objectName))
	) {
		if (Player_Query_Agenda() == kPlayerAgendaSurly
		    || (Player_Query_Agenda() == kPlayerAgendaErratic && Random_Query(0, 1) == 1)
		) {
			Actor_Voice_Over(1940, kActorVoiceOver);
			// Note: Quote 1950 is *boop* in ENG version
			//       However it is voiced in FRA, DEU, ESP and ITA versions
			//       In ESP and FRA this quote roughly translates to:
			//       "Seeing them slaughtered was worse than any of my nightmares."
			//       In DEU and ITA it seems to be the second (missing) half of the previous quote (1940)
			//       and it is required for those.
			if (_vm->_language == Common::FR_FRA
			    || _vm->_language == Common::DE_DEU
			    || _vm->_language == Common::ES_ESP
			    || _vm->_language == Common::IT_ITA
			) {
				Actor_Voice_Over(1950, kActorVoiceOver);
			}
		} else {
			Actor_Voice_Over(9010, kActorMcCoy);
			Actor_Voice_Over(9015, kActorMcCoy);
			Actor_Voice_Over(9020, kActorMcCoy);
		}
		Game_Flag_Set(kFlagMcCoyCommentsOnMurderedAnimals);
		Unclickable_Object("DRAPE01");
		Unclickable_Object("DRAPE02");
		Unclickable_Object("DRAPE03");
		Unclickable_Object("DRAPE04");
		Unclickable_Object("DRAPE05");
		Unclickable_Object("DRAPE06");
		Unclickable_Object("DRAPE07");
		return true;
	}
	return false;
}

void SceneScriptRC02::dialogueWithRunciter() {
	Dialogue_Menu_Clear_List();
	// Made it so no new topics will be available once you discover that Runciter is a replicant.
	// It would make no sense for McCoy to discover that Runciter is a replicant, spare him and continue
	// the conversation like nothing has happened.
	if (_vm->_cutContent) {
		if (!Game_Flag_Query(kFlagRunciterDiscovered)) {
			DM_Add_To_List_Never_Repeat_Once_Selected( 0, 5, 6, 2);     // MOTIVES
		}
	} else {
		DM_Add_To_List_Never_Repeat_Once_Selected( 0, 5, 6, 2);     // MOTIVES
	}
	if (_vm->_cutContent) {
		if (!Game_Flag_Query(kFlagRunciterDiscovered)) {
			DM_Add_To_List_Never_Repeat_Once_Selected(10, 5, 4, 8);     // LUCY
		}
	} else {
		DM_Add_To_List_Never_Repeat_Once_Selected(10, 5, 4, 8);     // LUCY
	}
	if (_vm->_cutContent) {
		if (!Game_Flag_Query(kFlagRunciterDiscovered)) {
			if (Actor_Clue_Query(kActorMcCoy, kClueRunciterInterviewB1)
			|| Actor_Clue_Query(kActorMcCoy, kClueRunciterInterviewB2)) {
				DM_Add_To_List_Never_Repeat_Once_Selected(20, 6, 4, 5); // REFERENCE
			}
		}
	} else if (Actor_Clue_Query(kActorMcCoy, kClueRunciterInterviewB1)
		|| Actor_Clue_Query(kActorMcCoy, kClueRunciterInterviewB2)) {
			DM_Add_To_List_Never_Repeat_Once_Selected(20, 6, 4, 5); // REFERENCE
	}
	if (_vm->_cutContent
	    && (!Game_Flag_Query(kFlagRC02RunciterVKChosen)
	    && (!Actor_Clue_Query(kActorMcCoy, kClueVKRunciterHuman)
		&& !Actor_Clue_Query(kActorMcCoy, kClueVKRunciterReplicant)))) {
			Dialogue_Menu_Clear_Never_Repeat_Was_Selected_Flag(200);
			// Made it so you can only VK Runciter after he gives you the video disc. This is to avoid a dead end
			// since the video disc contains evidence necessary to proceed further into the game.
			if (Actor_Clue_Query(kActorMcCoy, kClueRuncitersVideo)) {
				DM_Add_To_List_Never_Repeat_Once_Selected(200, -1, 3, 6); // VOIGT-KAMPFF
			}
		}
	Dialogue_Menu_Add_DONE_To_List(30); // DONE

	Dialogue_Menu_Appear(320, 240);
	int answer = Dialogue_Menu_Query_Input();
	Dialogue_Menu_Disappear();

	switch (answer) {
	case 0: // MOTIVES
		// Jake - Moved the I can tell your crushed line to later in the conversation and McCoy only says it if he is not surly or erratic.
		Actor_Says(kActorMcCoy, 4580, 13);
		Actor_Face_Actor(kActorRunciter, kActorMcCoy, true);
		Actor_Says(kActorRunciter, 110, 18);
		Actor_Says(kActorRunciter, 120, 17);
		Actor_Says(kActorRunciter, 130, 19);
		Actor_Says(kActorMcCoy, 4605, 13);	
		// Jake - Added in some extra dialogue for Runciter. Originally these lines were only played one at a time as banter dialogue
		// but I think they work better as a conversation. Basically after Runciter says how barbaric the reps were he then says they should have just killed him
		// McCoys asks why and Runciter tells him how he lost everything. McCoy can be kind or cruel towards Runciter based on his agenda. Also set the flag
		// Runciter talk motives to be triggered when you ask him about the suspects motives. This will ensure that when McCoy exits the store he will only talk
		// about the suspects motive if he learned from Runciter that nothing was stolen. Also McCoys friendliness towards Runciter now changes based on whether 
		// he is surly or erratic.	
		// If Runciter is a replicant when McCoy asks him if replicants could have committed the crime, Runciter just says how would I know and the conversation 
		// cuts off there.
		if (Game_Flag_Query(kFlagRunciterIsReplicant)) {
			Actor_Says(kActorRunciter, 1420, 19); //15-1420.AUD	How would I know?
			Game_Flag_Set(kFlagRunciterTalkMotives);
		} else {
			Actor_Says(kActorRunciter, 140, 16); // 15-0140.AUD	Who else would be capable of such barbaric acts?
		if (_vm->_cutContent) {
			Actor_Says(kActorRunciter, 310, 18);  // 15-0310.AUD	They should have just killed me!
			Actor_Says(kActorMcCoy, 8190, 0);	// 00-8190.AUD	Why?
			Actor_Says(kActorRunciter, 300, 16); // 15-0300.AUD	Do you have any idea how much this is going to cost me? I'm ruined!		
			Actor_Says(kActorRunciter, 90, 17); // 15-0090.AUD	That snow tiger alone was worth more than most people will ever see in a lifetime. 
			Actor_Says(kActorRunciter, 540, 19); // 15-0540.AUD	I sacrificed everything to get that tiger. And now she's dead.
			Actor_Clue_Acquire(kActorMcCoy, kClueRunciterConfession1, true, kActorRunciter);
			Game_Flag_Set(kFlagRunciterTalkMotives);
			if (Player_Query_Agenda() == kPlayerAgendaSurly 
					|| Player_Query_Agenda() == kPlayerAgendaErratic) {
				Actor_Says(kActorRunciter, 530, 17); //15-0530.AUD	My precious one. She was my baby.   
				Actor_Says(kActorMcCoy, 2660, 18); // 00-2660.AUD	That breaks my heart. (Sarcastically.)
				Actor_Modify_Friendliness_To_Other(kActorRunciter, kActorMcCoy, -5);
			} else {
				Actor_Says(kActorMcCoy, 4575, kAnimationModeTalk); //	00-4575.AUD	I can tell you're crushed.
				Actor_Says(kActorRunciter, 530, 17); //15-0530.AUD	My precious one. She was my baby.
				Actor_Says(kActorMcCoy, 2305, 13); //00-2305.AUD	I’m sorry.
				Actor_Modify_Friendliness_To_Other(kActorRunciter, kActorMcCoy, 5);
			}	
		}
		}
		Game_Flag_Set(kFlagRC02RunciterTalk1);		
		break;

	case 10: // LUCY
	// In the cutscene at the beginning of act 3 McCoy talks to Lucy. He recognises her and mentions that he saw her things at Runciters. However it is possible that the player never went to the back area of Runciters where her things are
	// or received any clues that described Lucys appearance so this scene will not make sense to some players. I have corrected this by making sure when the player first clicks on Runciter which they must do to advance the game
	// McCoy automatically asks Runciter about Lucys appearance and where her desks is which he then he automatically walks over to. The Lucy topic will also play out a little differently because of this with Runciter not showing you Lucys 
	// desks and certain parts of the conversation not playing out because they have been said already.
	if (_vm->_cutContent) {
		Actor_Says(kActorMcCoy, 4760, 13);//00-4760.AUD	About the girl.
		Actor_Face_Actor(kActorRunciter, kActorMcCoy, true);
		Actor_Says(kActorRunciter, 590, 14); //15-0590.AUD	What? Who?
		Actor_Says(kActorMcCoy, 4775, 14);//00-4775.AUD	Lucy.
		Actor_Says(kActorMcCoy, 8514, 15);//00-8514.AUD	Got anything new to tell me?
	} else {
		Actor_Says(kActorMcCoy, 4585, 13);
	}
		Actor_Face_Actor(kActorRunciter, kActorMcCoy, true);
		if (Game_Flag_Query(kFlagLucyIsReplicant)) {
			Actor_Says(kActorRunciter, 250, 13);
			if (!_vm->_cutContent) {
				Actor_Says(kActorRunciter, 270, 13); //15-0270.AUD	She's about fourteen years old with pink hair. A very attractive young thing.
			}
			Actor_Clue_Acquire(kActorMcCoy, kClueRunciterInterviewB1, true, kActorRunciter);
		} else {
			Actor_Says(kActorRunciter, 260, 14);
			if (!_vm->_cutContent) {
				Actor_Says(kActorRunciter, 270, 13); //15-0270.AUD	She's about fourteen years old with pink hair. A very attractive young thing.
			}
			if (!_vm->_cutContent) {
				Actor_Clue_Acquire(kActorMcCoy, kClueRunciterInterviewB2, true, kActorRunciter);
			}
		}
		Actor_Says(kActorMcCoy, 4645, 13);
		Actor_Says(kActorRunciter, 280, 13);
		Actor_Says(kActorRunciter, 290, 13);
		Actor_Says(kActorMcCoy, 4650, 18);
		Actor_Says(kActorRunciter, 320, 13);
		if (_vm->_cutContent) {
			Actor_Says(kActorMcCoy, 4655, 15);
			Actor_Says(kActorRunciter, 330, 13); // 15-0330.AUD	I'm the only one who handles my animals, detective.

			// Made it so Runciter only says the unskilled labor line where he says Lucy was practically made for it only if Lucy is a
			// replicant. That line is just too on the nose for it not to be a hint to Lucys true nature.
			if (_vm->_cutContent &&	Game_Flag_Query(kFlagLucyIsReplicant)) {
				Actor_Says(kActorMcCoy, 4660, 13); // 00-4660.AUD	So what did she do?
				Actor_Says(kActorRunciter, 340, 14); // 15-0340.AUD	Unskilled labor, mostly. She was perfect for that. As if she were made for it.
			}
		}
		if (!_vm->_cutContent) {
			Actor_Says(kActorMcCoy, 4665, 13);
			Actor_Face_Object(kActorRunciter, "CURTAIN", true);
			Actor_Says(kActorRunciter, 350, 13);
			Actor_Face_Actor(kActorRunciter, kActorMcCoy, true);
			Scene_Exit_Add_2D_Exit(kRC02ExitRC51, 265, 58, 346, 154, 0);
			Game_Flag_Set(kFlagRC51Available);
		}
		break;

	case 20: // REFERENCE
		Actor_Says(kActorMcCoy, 4590, 19);
		Actor_Face_Actor(kActorRunciter, kActorMcCoy, true);
		// Made it so Runciter only gives McCoy the letter if McCoy wasn't a jerk towards him. If McCoy treated him badly Runciter has had enough
		// and tells McCoy to get lost.
		if (_vm->_cutContent) {
			if (Actor_Query_Friendliness_To_Other(kActorRunciter, kActorMcCoy) <= 46) {
				Actor_Says(kActorRunciter, 720, 13); //15-0720.AUD	I have nothing more to say to you, detective.
			} else if (Actor_Query_Friendliness_To_Other(kActorRunciter, kActorMcCoy) > 46) {
				Actor_Says(kActorRunciter, 360, 13);
				Loop_Actor_Walk_To_Waypoint(kActorRunciter, 89, 0, false, false);
				Loop_Actor_Walk_To_Waypoint(kActorRunciter, 102, 0, false, false);
				Actor_Face_Actor(kActorMcCoy, kActorRunciter, true);
				Actor_Face_Heading(kActorRunciter, 539, false);
				Delay(2000);
				Loop_Actor_Walk_To_Waypoint(kActorRunciter, 89, 0, false, false);
				Actor_Face_Actor(kActorMcCoy, kActorRunciter, true);
				Loop_Actor_Walk_To_Actor(kActorRunciter, kActorMcCoy, 24, false, false);
				Actor_Face_Actor(kActorRunciter, kActorMcCoy, true);
				Actor_Face_Actor(kActorMcCoy, kActorRunciter, true);
				Item_Pickup_Spin_Effect(kModelAnimationReferenceLetter, 357, 228);
				Actor_Says(kActorRunciter, 1700, 13);
				Actor_Clue_Acquire(kActorMcCoy, kClueReferenceLetter, true, kActorRunciter);
				// If McCoy doesn't have the shell casings yet and Runciter likes him Runciter will show McCoy where the shell casings are and give them to him.
				Actor_Says(kActorMcCoy, 3935, 14);	// 00-3935.AUD	Thanks.
				Actor_Says(kActorMcCoy, 4130, 13); //00-4130.AUD	Anything else?
				if (Actor_Clue_Query(kActorMcCoy, kClueShellCasings)) {
					Actor_Says(kActorRunciter, 960, 13); //15-0960.AUD	No.
				} else {
					Actor_Says(kActorRunciter, 1600, 13); //15-1600.AUD	There is one thing, yes. I don't know if it's important but here it is.
					Player_Loses_Control();
					Loop_Actor_Walk_To_XYZ(kActorRunciter, -45.61, -1238.70, 108445.07, 0, true, false, false);
					Actor_Face_Actor(kActorRunciter, kActorMcCoy, true);
					Loop_Actor_Walk_To_Actor(kActorMcCoy, kActorRunciter, 24, true, false);
					Actor_Face_Actor(kActorMcCoy, kActorRunciter, true);
					Actor_Clue_Acquire(kActorMcCoy, kClueShellCasings, true, kActorRunciter);
					Game_Flag_Set(kFlagRC02ShellCasingsTaken);
					Item_Remove_From_World(kItemShellCasingA);
					Item_Remove_From_World(kItemShellCasingB);
					Item_Remove_From_World(kItemShellCasingC);
					Item_Pickup_Spin_Effect(kModelAnimationShellCasings, 395, 352);
					Actor_Says(kActorRunciter, 1700, 13); //15-1700.AUD	Here you are.
					Actor_Says(kActorMcCoy, 8730, 13); //00-8730.AUD	Shell casings.
					Actor_Voice_Over(1960, kActorVoiceOver); //99-1960.AUD	Big caliber. Possibly Off-World combat weaponry. Ballistics might give me a fix on it.
					Player_Gains_Control();
				}				
			}
		} else {
			Actor_Says(kActorRunciter, 360, 13);
			Loop_Actor_Walk_To_Waypoint(kActorRunciter, 89, 0, false, false);
			Loop_Actor_Walk_To_Waypoint(kActorRunciter, 102, 0, false, false);
			Actor_Face_Actor(kActorMcCoy, kActorRunciter, true);
			Actor_Face_Heading(kActorRunciter, 539, false);
			Delay(2000);
			Loop_Actor_Walk_To_Waypoint(kActorRunciter, 89, 0, false, false);
			Actor_Face_Actor(kActorMcCoy, kActorRunciter, true);
			Loop_Actor_Walk_To_Actor(kActorRunciter, kActorMcCoy, 24, false, false);
			Actor_Face_Actor(kActorRunciter, kActorMcCoy, true);
			Actor_Face_Actor(kActorMcCoy, kActorRunciter, true);
			Item_Pickup_Spin_Effect(kModelAnimationReferenceLetter, 357, 228);
			Actor_Says(kActorRunciter, 1700, 13);
			Actor_Clue_Acquire(kActorMcCoy, kClueReferenceLetter, true, kActorRunciter);
		}
		break;

	case 200:
		if (_vm->_cutContent) { // scene 16 79
			Game_Flag_Set(kFlagRC02RunciterVKChosen);
			Actor_Face_Actor(kActorMcCoy, kActorRunciter, true);
			Actor_Says(kActorMcCoy, 395, 14);
			Actor_Face_Actor(kActorRunciter, kActorMcCoy, true);
			// Changed code so Runciter is more resistant to being VKed if he is a replicant or has low friendliness with McCoy
			if (!Game_Flag_Query(kFlagRunciterIsReplicant)
			|| Actor_Query_Friendliness_To_Other(kActorRunciter, kActorMcCoy) < 46) {
				Actor_Says(kActorRunciter, 1680, 13); //15-1680.AUD	No. I have a lot of cleaning up to do.
				Actor_Says(kActorMcCoy, 400, 14); //00-0400.AUD	It won't take too long.
				Actor_Modify_Friendliness_To_Other(kActorRunciter, kActorMcCoy, -5);
			} else {
				Actor_Says(kActorMcCoy, 400, 14); //00-0400.AUD	It won't take too long.
				Actor_Modify_Friendliness_To_Other(kActorRunciter, kActorMcCoy, -3);
				Voight_Kampff_Activate(kActorRunciter, 20);
			}
			// The dialogue that plays when the VK test confirms that Runciter is a replicant. McCoy pulls out his gun and
			// the exits are disabled. The player must choose whether or not to shoot Runciter or spare him.
			if (Game_Flag_Query(kFlagRunciterIsReplicant)) {
				Actor_Face_Actor(kActorMcCoy, kActorRunciter, true);
				Actor_Face_Actor(kActorRunciter, kActorMcCoy, true);
				// Sadly I couldn't get the VK test to work properly so it confirms Runciter as a replicant if he is one, so
				// I turned it into a simple cutscene instead. This is something that you could change since you understand the code 
				// better than I do.
				Actor_Says(kActorAnsweringMachine, 390, kAnimationModeTalk); // 39-0390.AUD	Begin test.
				Ambient_Sounds_Play_Sound(kSfxDATALOAD, 50, 0, 0, 99);
				Delay(2000);
				Ambient_Sounds_Play_Sound(kSfxBEEPNEAT, 80, 0, 0, 99);
				Actor_Says(kActorAnsweringMachine, 420, 19); //39-0420.AUD	Positive result.
				Actor_Says(kActorAnsweringMachine, 430, 19); //39-0430.AUD	Subject is Replicant.
				Actor_Says(kActorAnsweringMachine, 460, 19); //39-0460.AUD	Test terminated.
				Actor_Says(kActorMcCoy, 6865, 14); //00-6865.AUD	You're a Replicant.
				Actor_Says(kActorRunciter, 490, 13); //15-0490.AUD	No. You heard it wrong.
				Actor_Says(kActorRunciter, 1070, 13); //15-1070.AUD	I'm not a Replicant for heaven's sakes.
				Actor_Says(kActorMcCoy, 1610, 13); //00-1610.AUD	Yes. You are.
				Actor_Says(kActorRunciter, 600, 13); //15-0600.AUD	That's ridiculous. I--.
				Actor_Says(kActorRunciter, 720, 13); //15-0720.AUD	I have nothing more to say to you, detective.
				Player_Set_Combat_Mode(true);
				Actor_Set_Targetable(kActorRunciter, true);
				Actor_Says(kActorRunciter, 420, 12); //15-0420.AUD	What? Why?
				Game_Flag_Set(kFlagRunciterDiscovered);
				Game_Flag_Set(kFlagRunciterConfronted);
				// Added code so Runciters goal where he walks around changes to him standing still. This is to prevent him still walking around
				// after you shoot him dead.
				Actor_Set_Goal_Number(kActorRunciter, kGoalRunciterStill);
				Player_Gains_Control();
				Scene_Exits_Disable();
			} else if (!Actor_Clue_Query(kActorMcCoy, kClueVKRunciterReplicant)) {
				Actor_Says(kActorMcCoy, 6880, 14); //00-6880.AUD	The test says you're human.
			}
		}
		break;

	case 30: // DONE
		// Added in some banter dialogue for Runciter. It is also different based on your friendliness with Runcter.
		if (_vm->_cutContent && Actor_Query_Goal_Number(kActorRunciter) != kGoalRunciterDead) {
			Actor_Says(kActorMcCoy, 4600, 14); // A couple questions.
			Actor_Face_Actor(kActorRunciter, kActorMcCoy, true);
			if (Actor_Query_Friendliness_To_Other(kActorRunciter, kActorMcCoy) < 46) {
				Actor_Says(kActorRunciter, 100, 13); //15-0100.AUD	I'm all talked out. Shouldn't you be tracking down the girl?
			} else {
				Actor_Says(kActorRunciter, 730, 13); //15-0730.AUD	Please. Just leave me alone.
			}
		} else if (Actor_Query_Goal_Number(kActorRunciter) != kGoalRunciterDead) {
			Actor_Says(kActorMcCoy, 4595, 14);
		}
		break;
	}
}

bool SceneScriptRC02::ClickedOnActor(int actorId) {
	if (actorId == kActorRunciter) {
		if (Global_Variable_Query(kVariableChapter) == 1
			&& Actor_Query_Goal_Number(kActorRunciter) == kGoalRunciterDead) {
			Actor_Face_Actor(kActorMcCoy, kActorRunciter, true);
			Actor_Says(kActorMcCoy, 8630, 12);  // What a waste
		} else if (Global_Variable_Query(kVariableChapter) == 4) {
			Actor_Face_Actor(kActorMcCoy, kActorRunciter, true);
			if (Actor_Query_Goal_Number(kActorRunciter) == kGoalRunciterDead) {
				if (_vm->_cutContent) {
					switch (Random_Query(1, 3)) {
					case 1:
						Actor_Says(kActorMcCoy, 8715, 17);
						break;
					case 2:
						Actor_Says(kActorMcCoy, 8720, 17);
						break;
					case 3:
						Actor_Says(kActorMcCoy, 8725, 17);
						break;
					}
				} else {
					if (Random_Query(1, 2) == 1) {
						Actor_Says(kActorMcCoy, 8715, 17);
					} else {
						Actor_Says(kActorMcCoy, 8720, 17);
					}
				}
				return true;
			}

			if (!Game_Flag_Query(kFlagRC02RunciterTalkWithGun)
			 && !Game_Flag_Query(kFlagRC02RunciterTalk2)
			) {
				// Added in a flag for when Runciter talks about Luther and Lance. Originally in act 4 McCoy always said to Runciter he wanted
				// to talk about his friends again even if he did not talk about them before so this flag will fix that. Also made it so McCoy only says
				// aggresively says we're going to have a little chat if he has the Zubens motive clue.
				if (_vm->_cutContent) {
					if (Actor_Clue_Query(kActorMcCoy, kClueRunciterConfession2) && Actor_Clue_Query(kActorMcCoy, kClueEnvelope)) {
						Actor_Says(kActorMcCoy, 4690, 11); // 00-4690.AUD	I wanted to ask you about the Tyrell subcontractors again.
						Actor_Says(kActorMcCoy, 4695, 13); // 00-4695.AUD	The ones down on DNA Row.
					} else if (Actor_Clue_Query(kActorMcCoy, kClueZubensMotive))	{
						Actor_Says(kActorMcCoy, 4680, 11); // 00-4680.AUD	We're gonna have a little chat.
					} else {
						Actor_Says(kActorMcCoy, 4685, 11);	// 00-4685.AUD	You're sure there's nothing else you wanna tell me?	
					}
				} else {
					Actor_Says(kActorMcCoy, 4690, 11);
					Actor_Says(kActorMcCoy, 4695, 13);
				}
				Actor_Face_Actor(kActorRunciter, kActorMcCoy, true);
				if (_vm->_cutContent) {
					if (Actor_Clue_Query(kActorMcCoy, kClueRunciterConfession2)) {
						Actor_Says(kActorRunciter, 1670, 14); // 15-1670.AUD	Haven't we been already through this? Why would I have any dealings with those people?
					} else {
						Actor_Says(kActorRunciter, 1610, 11); // 15-1610.AUD	Detective, if I knew something you can be sure I'd tell you.	 		
					}		
    			} else {
					Actor_Says(kActorRunciter, 1610, 14);
				}
				if (Actor_Clue_Query(kActorMcCoy, kClueEnvelope)) {
					Actor_Says(kActorMcCoy, 4700, 12);
					Actor_Says(kActorMcCoy, 4705, 13);
					Actor_Says(kActorRunciter, 1620, 12);
					Actor_Says(kActorMcCoy, 4710, 15);
					Actor_Says(kActorMcCoy, 4715, 11);
					Delay(2000);
					Actor_Says(kActorMcCoy, 4720, 16);
					Actor_Says(kActorMcCoy, 4725, 17);
					Actor_Says(kActorRunciter, 430, 16);
					// Added in some dialogue where if you click on Runciter and McCoy knows what he did to Lucy he brings it up.
					if (_vm->_cutContent) {
						if (Actor_Clue_Query(kActorMcCoy, kClueZubensMotive)) {
							Actor_Says(kActorMcCoy, 4760, 13); // 00-4760.AUD	About the girl.
							Actor_Says(kActorRunciter, 590, 14); // 15-0590.AUD	What? Who?
							Actor_Says(kActorMcCoy, 4765, 15); // 00-4765.AUD	Lucy. I know what you did.
							Actor_Says(kActorRunciter, 1690, 12); // 15-1690.AUD	Get out of my shop.
						}					
					}
					Actor_Face_Heading(kActorRunciter, 1007, false);
				}
				Game_Flag_Set(kFlagRC02RunciterTalk2);
				return true;
			}

			// Made it so after McCoy has pulled his gun on Runciter and the player puts it away and click on Runciter McCoy will now say listen up more aggresively.
			if (_vm->_cutContent) {
				Actor_Face_Actor(kActorMcCoy, kActorRunciter, true);
				if (Game_Flag_Query(kFlagRC02RunciterTalk2)) {
					Actor_Says(kActorMcCoy, 4805, 11); //00-4805.AUD	Listen up.
				} else {
					Actor_Says(kActorMcCoy, 4810, 11); //00-4810.AUD	Listen up!
				}
			} else {
				Actor_Says(kActorMcCoy, 4805, 11); //00-4805.AUD	Listen up.
			}
			Actor_Face_Actor(kActorRunciter, kActorMcCoy, true);
			if (Game_Flag_Query(kFlagRC02RunciterTalk2)) {
				Actor_Says(kActorRunciter, 720, 15);
			} else {
				Actor_Says(kActorRunciter, 730, 14);
			}
			Actor_Face_Heading(kActorRunciter, 1007, false);
			return true;
		}

		AI_Movement_Track_Pause(kActorRunciter);
		Loop_Actor_Walk_To_Actor(kActorMcCoy, kActorRunciter, 48, true, false);
		Actor_Face_Actor(kActorMcCoy, kActorRunciter, true);

		if (!Game_Flag_Query(kFlagRC02RunciterInterview)) {
			Actor_Says(kActorMcCoy, 4560, 13);
			Actor_Face_Actor(kActorRunciter, kActorMcCoy, true);
			Actor_Says(kActorRunciter, 40, 16);
			Actor_Says(kActorRunciter, 50, 15);
			Actor_Says(kActorMcCoy, 4565, 13);
			Actor_Says(kActorRunciter, 60, 14);
			Actor_Says(kActorMcCoy, 4570, 18);
			Actor_Says(kActorRunciter, 70, 13); //15-0070.AUD	Big and scary and absolutely malevolent.
			// The altered part of the conversation that I mentioned above when you first click on Runciter.
			if (_vm->_cutContent) {
				Actor_Says(kActorMcCoy, 4585, 13); //00-4585.AUD	Tell me about this Lucy.
				Actor_Says(kActorRunciter, 270, 13); //15-0270.AUD	She's about fourteen years old with pink hair. A very attractive young thing.
				Actor_Says(kActorMcCoy, 4665, 13); //00-4665.AUD	She got a desk or some place where she worked?
				Actor_Face_Object(kActorRunciter, "CURTAIN", true);
				Actor_Says(kActorRunciter, 350, 13); //15-0350.AUD	She used to eat over there.
				Actor_Face_Actor(kActorRunciter, kActorMcCoy, true);
				Scene_Exit_Add_2D_Exit(kRC02ExitRC51, 265, 58, 346, 154, 0);
				Game_Flag_Set(kFlagRC51Available);
				Game_Flag_Set(kFlagRC02RunciterInterview);
				Actor_Clue_Acquire(kActorMcCoy, kClueRunciterInterviewA, true, kActorRunciter);
				AI_Movement_Track_Unpause(kActorRunciter);
				Player_Loses_Control();
				Loop_Actor_Walk_To_XYZ(kActorMcCoy, -20.2f, -1238.73f, 108152.73f, 0, true, false, false);
				Async_Actor_Walk_To_XYZ(kActorMcCoy, -8.87f, -1238.89f, 108076.27f, 0, false);
				Set_Enter(kSetRC02_RC51, kSceneRC51);
				Player_Gains_Control();
			}
			return true;
		}

		if (Game_Flag_Query(kFlagRC02RunciterTalk1)) {
			if (Player_Query_Agenda() == kPlayerAgendaPolite) {
				Game_Flag_Reset(kFlagNotUsed0);
				dialogueWithRunciter();
				AI_Movement_Track_Unpause(kActorRunciter);
				return true;
			}
			// Jake - Removed the line where McCoy says a couple of question if he is surly or erratic. He doesn't say it in an aggressive tone and McCoy is actually
			// quite calm so it didn't make any sense to have it here.
			Actor_Says(kActorMcCoy, 4610, 19);
			Actor_Face_Actor(kActorRunciter, kActorMcCoy, true);
			// Made it so the dialogue where Runciter mentions being friends with Governor Kolvig doesn't play if Runciter is a replicant.
			// It would make no sense for a replicant to be friends with such a high ranking official, especially one that doesn't like replicants.
			if (_vm->_cutContent && Game_Flag_Query(kFlagRunciterIsReplicant)) {
				Actor_Says(kActorRunciter, 9000, 15); //15-9000.AUD	No!
				Actor_Says(kActorMcCoy, 4615, 13); //00-4615.AUD	Just wondering.
				Actor_Says(kActorRunciter, 180, 13); //15-0180.AUD	Do I look like I need to carry artificial product?
			} else {
				Actor_Says(kActorRunciter, 150, 15);
				Actor_Says(kActorMcCoy, 4615, 13);
				Actor_Says(kActorRunciter, 160, 14);
				Actor_Says(kActorRunciter, 170, 15);
				Actor_Says(kActorRunciter, 180, 13);
				if (_vm->_cutContent) {
					Actor_Clue_Acquire(kActorMcCoy, kClueRunciterInterviewB2, true, kActorRunciter);
				}
			}
			if (_vm->_cutContent) {
				// Made it so McCoy talks about Runciters friends regardless of his agenda. McCoy doesn't really come of as a jerk here so
				// it wouldn't make sense for these lines to play based on whether or not he is surly or erratic.
				Actor_Says(kActorMcCoy, 4620, 19);
				Actor_Says(kActorRunciter, 190, 14);
				Actor_Says(kActorMcCoy, 4625, 13); // 00-4625.AUD	Do you know anybody who works at Tyrell Corporation? 
				// Made it so Runciter will tell you immediately about his friends if you have high friendliness with him. If not he will deny it and will only tell McCoy
				// if he is surly or erratic.
				if (Actor_Query_Friendliness_To_Other(kActorRunciter, kActorMcCoy) < 49) {
					Actor_Says(kActorRunciter, 9000, 14); //15-9000.AUD	No! 
					Delay (1000);
					Actor_Says(kActorMcCoy, 4685, 15); //00-4685.AUD	You're sure there's nothing else you wanna tell me?
					Actor_Says(kActorRunciter, 1630, 17); //15-1630.AUD	What? Do you really think I'd lie to you? Preposterous,
					if (Player_Query_Agenda() == kPlayerAgendaSurly 
							|| Player_Query_Agenda() == kPlayerAgendaErratic) {
						Actor_Says(kActorMcCoy, 8519, 14);//00-8519.AUD	What do you say we dish each other the straight goods.
						Actor_Modify_Friendliness_To_Other(kActorRunciter, kActorMcCoy, -3);
						Actor_Says(kActorRunciter, 1640, 14); //15-1640.AUD	Ah...well, yes. I suppose that isn't the whole truth but...
						Actor_Says(kActorRunciter, 1650, 16); //15-1650.AUD	All right, all right. Here's the real truth.
						Actor_Says(kActorRunciter, 210, 13);
						Actor_Says(kActorMcCoy, 4630, 18);
						Actor_Says(kActorRunciter, 220, 14);
						Actor_Says(kActorRunciter, 230, 13);
						Actor_Says(kActorMcCoy, 4635, 19); // 00-4635.AUD	I assume you're talking about some of those fruitcakes on DNA Row.
						Actor_Says(kActorRunciter, 240, 16); // 15-0240.AUD	That's a horrible thing to say about people, detective.
						Actor_Says(kActorMcCoy, 4640, 17); // 00-4640.AUD	Sorry.
						Actor_Clue_Acquire(kActorMcCoy, kClueRunciterConfession2, true, kActorRunciter);
					}
				} else if (Actor_Query_Friendliness_To_Other(kActorRunciter, kActorMcCoy) > 49) {
					Actor_Says(kActorRunciter, 210, 13);
					Actor_Says(kActorMcCoy, 4630, 18);
					Actor_Says(kActorRunciter, 220, 14);
					Actor_Says(kActorRunciter, 230, 13);
					Actor_Clue_Acquire(kActorMcCoy, kClueRunciterConfession2, true, kActorRunciter);
				// These last few lines where McCoy calls the DNA row subcons freaks and sarcastically says sorry will only play if he is surly or erratic. It also results in
				// a friendliness loss.
				if (Player_Query_Agenda() == kPlayerAgendaSurly 
						|| Player_Query_Agenda() == kPlayerAgendaErratic) {
					Actor_Says(kActorMcCoy, 4635, 19); // 00-4635.AUD	I assume you're talking about some of those fruitcakes on DNA Row.
					Actor_Says(kActorRunciter, 240, 16); // 15-0240.AUD	That's a horrible thing to say about people, detective.
					Actor_Says(kActorMcCoy, 4640, 17); // 00-4640.AUD	Sorry.
					Actor_Modify_Friendliness_To_Other(kActorRunciter, kActorMcCoy, -3);
				} 
			}
				// Original behaviour without cut content.
			} else if (Player_Query_Agenda() == kPlayerAgendaSurly) {
				Actor_Says(kActorMcCoy, 4620, 19);
				Actor_Says(kActorRunciter, 190, 14);
				Actor_Says(kActorMcCoy, 4625, 13);
				Actor_Says(kActorRunciter, 210, 13);
				Actor_Says(kActorMcCoy, 4630, 18);
				Actor_Says(kActorRunciter, 220, 14);
				Actor_Says(kActorRunciter, 230, 13);
				Actor_Says(kActorMcCoy, 4635, 19);
				Actor_Says(kActorRunciter, 240, 16);
				Actor_Says(kActorMcCoy, 4640, 17);
			}
			Game_Flag_Reset(kFlagRC02RunciterTalk1);
			AI_Movement_Track_Unpause(kActorRunciter);
			return true;
		}
		dialogueWithRunciter();
		AI_Movement_Track_Unpause(kActorRunciter);
		return true;
	}
	return false;
}

bool SceneScriptRC02::ClickedOnItem(int itemId, bool a2) {
	if (_vm->_cutContent) {
		if (itemId == kItemCigarette) { 
			if (!Loop_Actor_Walk_To_Item(kActorMcCoy, kItemCigarette, 12, true, false)) {
				Actor_Face_Item(kActorMcCoy, kItemCigarette, true);
				Actor_Voice_Over(1770, kActorVoiceOver); //99-1770.AUD	Lucky Strikes. Crystal's brand.
				return true;
			}
		}
	}
	if (itemId == kItemShellCasingA
	 || itemId == kItemShellCasingB
	 || itemId == kItemShellCasingC
	) {
		if (!Loop_Actor_Walk_To_Item(kActorMcCoy, kItemShellCasingA, 24, true, false)) {
			Actor_Face_Item(kActorMcCoy, kItemShellCasingA, true);
			Actor_Clue_Acquire(kActorMcCoy, kClueShellCasings, true, -1);
			Game_Flag_Set(kFlagRC02ShellCasingsTaken);
			Item_Remove_From_World(kItemShellCasingA);
			Item_Remove_From_World(kItemShellCasingB);
			Item_Remove_From_World(kItemShellCasingC);
			Item_Pickup_Spin_Effect(kModelAnimationShellCasings, 395, 352);
			if (_vm->_cutContent) {
				Actor_Says(kActorMcCoy, 8730, 13); //00-8730.AUD	Shell casings.
			}
			Actor_Voice_Over(1960, kActorVoiceOver);
		}
		return true;
	}
	return false;
}

bool SceneScriptRC02::ClickedOnExit(int exitId) {
	if (exitId == kRC02ExitRC01) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -71.51f, -1238.89f, 108587.15f, 0, true, false, false)) {
			Game_Flag_Set(kFlagRC02toRC01);
			Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
			Ambient_Sounds_Remove_Looping_Sound(kSfxBRBED5,   1u);
			Ambient_Sounds_Remove_Looping_Sound(kSfxWINDLOP8, 1u);
			Ambient_Sounds_Adjust_Looping_Sound(kSfxRCRAIN1, 100, -101, 1u);
			Actor_Set_Goal_Number(kActorRunciter, kGoalRunciterDefault);
			Set_Enter(kSetRC01, kSceneRC01);
		}
		return true;
	}

	if (exitId == kRC02ExitRC51) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -20.2f, -1238.73f, 108152.73f, 0, true, false, false)) {
			Async_Actor_Walk_To_XYZ(kActorMcCoy, -8.87f, -1238.89f, 108076.27f, 0, false);
			Set_Enter(kSetRC02_RC51, kSceneRC51);
		}
		return true;
	}
	return false;
}

bool SceneScriptRC02::ClickedOn2DRegion(int region) {

	if (_vm->_cutContent
	    && Global_Variable_Query(kVariableChapter) == 1
	    && !Game_Flag_Query(kFlagRC02McCoyCommentsOnVideoScreens)
	    && region == 0
	) {
		Game_Flag_Set(kFlagRC02McCoyCommentsOnVideoScreens);
		Scene_2D_Region_Remove(0);
		Actor_Voice_Over(9025, kActorMcCoy);
		Actor_Voice_Over(9030, kActorMcCoy);
		Actor_Voice_Over(9035, kActorMcCoy);
		return true;
	}
	return false;
}

void SceneScriptRC02::SceneFrameAdvanced(int frame) {
}

void SceneScriptRC02::ActorChangedGoal(int actorId, int newGoal, int oldGoal, bool currentSet) {
}

void SceneScriptRC02::PlayerWalkedIn() {
	Player_Set_Combat_Mode(false);
	if (Game_Flag_Query(kFlagRC01toRC02)) {
		Player_Loses_Control();
		Loop_Actor_Walk_To_XYZ(kActorMcCoy, -72.2f, -1238.89f, 108496.73f, 0, false, false, false);
		Player_Gains_Control();
		Game_Flag_Reset(kFlagRC01toRC02);
		if (!Game_Flag_Query(kFlagRC02Entered)) {
			Actor_Voice_Over(1970, kActorVoiceOver);
			Actor_Voice_Over(1980, kActorVoiceOver);
			Actor_Voice_Over(1990, kActorVoiceOver);
			Actor_Clue_Acquire(kActorMcCoy, kClueLimpingFootprints, true, -1);
			Actor_Clue_Acquire(kActorMcCoy, kClueGracefulFootprints, true, -1);
			Game_Flag_Set(kFlagRC02Entered);
		}
		if (Actor_Query_Which_Set_In(kActorRunciter) == kSetRC02_RC51
		 && Actor_Query_Goal_Number(kActorRunciter) < kGoalRunciterRC02Wait
		) {
			Actor_Set_Goal_Number(kActorRunciter, kGoalRunciterRC02WalkAround);
		}
		if ( Actor_Query_Goal_Number(kActorRunciter) == kGoalRunciterRC02Wait
		 && !Game_Flag_Query(kFlagRC02EnteredChapter4)
		) {
			Actor_Face_Actor(kActorRunciter, kActorMcCoy, true);
			Actor_Says(kActorRunciter, 370, 12);
			Actor_Says(kActorRunciter, 380, 14);
			Actor_Face_Actor(kActorMcCoy, kActorRunciter, true);
			Actor_Says(kActorMcCoy, 4670, 15);
			Actor_Says(kActorRunciter, 390, 13);
			Actor_Says(kActorMcCoy, 4675, 14);
			Actor_Face_Heading(kActorRunciter, 1007, false);
			Actor_Says(kActorRunciter, 400, 13);
			Actor_Says(kActorRunciter, 410, 12);
			Game_Flag_Set(kFlagRC02EnteredChapter4);
		}
	} else {
		Player_Loses_Control();
		Loop_Actor_Walk_To_XYZ(kActorMcCoy, -20.2f, -1238.89f, 108152.73f, 0, false, false, false);
		Player_Gains_Control();
	}
}

void SceneScriptRC02::PlayerWalkedOut() {
}

void SceneScriptRC02::DialogueQueueFlushed(int a1) {
}

} // End of namespace BladeRunner
