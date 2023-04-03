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

void SceneScriptCT09::InitializeScene() {
	if (Game_Flag_Query(kFlagCT10toCT09)) {
		Setup_Scene_Information(160.0f,   349.0f, 587.0f, 490);
	} else if (Game_Flag_Query(kFlagCT08toCT09)) {
		Setup_Scene_Information(235.0f, 3348.52f, 599.0f, 800);
	} else {
		Setup_Scene_Information(107.0f,  348.52f, 927.0f, 200);
	}

	Scene_Exit_Add_2D_Exit(0, 321, 164, 345, 309, 1);
	Scene_Exit_Add_2D_Exit(1,   0,   0,  15, 479, 3);
	Scene_Exit_Add_2D_Exit(2, 198, 177, 263, 311, 0);

	Ambient_Sounds_Add_Looping_Sound(kSfxFLORBUZZ, 28, 0, 1);
	Ambient_Sounds_Add_Sound(kSfxTHNDER2, 6, 180, 33, 33, 0, 0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxTHNDER3, 5, 180, 33, 33, 0, 0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxTHNDER4, 5, 180, 33, 33, 0, 0, -101, -101, 0, 0);
}

void SceneScriptCT09::SceneLoaded() {
	Obstacle_Object("PHONE01", true);
	Unobstacle_Object("MAINBEAM01", true);
	Unobstacle_Object("MIDDLE WALL", true);
	Clickable_Object("BELL");
}

bool SceneScriptCT09::MouseClick(int x, int y) {
	return false;
}

bool SceneScriptCT09::ClickedOn3DObject(const char *objectName, bool a2) {
	if (Object_Query_Click("BELL", objectName)) {
		if (Actor_Query_Which_Set_In(kActorLeon) != kSetCT09) {
			if (_vm->_cutContent) {
				if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, 270.0f, 348.52f, 846.0f, 12, true, false, false)) {
					Actor_Face_Object(kActorMcCoy, "BELL", true);
					Actor_Change_Animation_Mode(kActorMcCoy, 23);
					Delay(800);
					Sound_Play(kSfxDESKBELL, 100, 0, 0, 50);					
					if (!Actor_Query_Goal_Number(kActorDeskClerk)) {
						Actor_Face_Actor(kActorDeskClerk, kActorMcCoy, true);
						Actor_Says(kActorDeskClerk, 160, kAnimationModeTalk);
						// Put a flag here so ringing the bell will change the clerks disposition towards you.
						Game_Flag_Set(kFlagBellRung);
					}
				}
			} else if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, 229.0f, 348.52f, 851.0f, 36, true, false, false)) {
				Actor_Face_Object(kActorMcCoy, "BELL", true);
				Sound_Play(kSfxDESKBELL, 100, 0, 0, 50);
				if (!Actor_Query_Goal_Number(kActorDeskClerk)) {
					Actor_Says(kActorDeskClerk, 160, kAnimationModeTalk);
				}
			}
		}
		return true;
	}
	return false;
}

bool SceneScriptCT09::ClickedOnActor(int actorId) {
	if (actorId == kActorDeskClerk) {
		if (Actor_Query_Goal_Number(kActorDeskClerk) == kGoalDeskClerkDefault
		 && Actor_Query_Which_Set_In(kActorLeon) != kSetCT09
		) {
			if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, 270.0f, 348.52f, 846.0f, 12, true, false, false)) {
				Player_Loses_Control();
				Actor_Face_Actor(kActorMcCoy, kActorDeskClerk, true);
				// Made it so the clerk faces McCoy when he talks to him.
				if (_vm->_cutContent) {
					Actor_Face_Actor(kActorDeskClerk, kActorMcCoy, true);
				}
				if (Global_Variable_Query(kVariableChapter) < 3) { // it is impossible to get here before chapter 3
					Actor_Says(kActorMcCoy, 650, kAnimationModeTalk);
					Actor_Says(kActorDeskClerk, 250, 12);
					Actor_Says(kActorMcCoy, 665, 18);
				} else if (!Game_Flag_Query(kFlagCT09DeskClerkTalk)) {
					Game_Flag_Set(kFlagCT09DeskClerkTalk);
					Actor_Says(kActorDeskClerk, 170, 13);
					Actor_Says(kActorMcCoy, 630, 12); //00-0630.AUD	What?
					Actor_Says(kActorDeskClerk, 180, 14);
					Actor_Says(kActorMcCoy, 635, kAnimationModeTalk); //00-0635.AUD	What were they doing here?
					Actor_Says(kActorDeskClerk, 190, 15); //27-0190.AUD	I don't ask a lot of questions when a badge is shoved in my face.
					if (_vm->_cutContent) {
						if (Actor_Query_Goal_Number(kActorZuben) < kGoalZubenGone) { 
							Actor_Says(kActorMcCoy, 640, 12); //00-0640.AUD	You have a big guy with a strange-looking mustache staying here?
							Actor_Says(kActorMcCoy, 645, kAnimationModeTalk); //00-0645.AUD	He worked at Howie Lee's around the corner.
							Actor_Says(kActorDeskClerk, 200, 13); //27-0200.AUD	I don't break a lot of bread with the class of people that pass through here.
						}
					} else {
						Actor_Says(kActorMcCoy, 640, 12); //00-0640.AUD	You have a big guy with a strange-looking mustache staying here?
						Actor_Says(kActorMcCoy, 645, kAnimationModeTalk); //00-0645.AUD	He worked at Howie Lee's around the corner.
						Actor_Says(kActorDeskClerk, 200, 13); //27-0200.AUD	I don't break a lot of bread with the class of people that pass through here.
					}
					if (_vm->_cutContent) {
						if (Game_Flag_Query(kFlagCT09LeonInterrupted)
						&& !Game_Flag_Query(kFlagBellRung)) {
							Actor_Says(kActorDeskClerk, 210, 14); //27-0210.AUD	But if you want to look around, check out some rooms, be my guest.
						}
					} else {
						Actor_Says(kActorDeskClerk, 210, 14); //27-0210.AUD	But if you want to look around, check out some rooms, be my guest.
					}
				}
				// Restored some dialogue for the desk clerk where McCoy asks him about the back room. If McCoy didn't help the desk clerk he will be more resistant to answering McCoys question.
				if (_vm->_cutContent) { 
					if (!Game_Flag_Query(kFlagCT09DeskClerkTalk2)) {
						Actor_Face_Heading(kActorMcCoy, 240, true);
						Delay(1000);
						Actor_Face_Actor(kActorMcCoy, kActorDeskClerk, true);
						Actor_Says(kActorMcCoy, 610, 15); //00-0610.AUD	What do you got back there?
						Actor_Says(kActorDeskClerk, 100, 13); //27-0100.AUD	Excuse me?
						Actor_Says(kActorMcCoy, 615, 18); //00-0615.AUD	The back room.
						if (Game_Flag_Query(kFlagCT09LeonInterrupted)
						&& !Game_Flag_Query(kFlagBellRung)) {
							Actor_Says(kActorDeskClerk, 120, 13); //27-0120.AUD	Used to store all the booty the tenants left behind in there.
							Actor_Says(kActorDeskClerk, 130, 14);  //27-0130.AUD	My boss sold everything to a Mongolian guy last month
							Actor_Says(kActorMcCoy, 625, 13); //00-0625.AUD	So, now there's nothing in there.
							Actor_Says(kActorDeskClerk, 140, 13); //27-0140.AUD	Rumor has it the boss wants to rent it out. What a dump.
							Actor_Says(kActorDeskClerk, 150, 15); //27-0150.AUD	Maybe if we paid you, someone would actually want to stay there. (laughs)
							Actor_Says(kActorMcCoy, 4130, 13); //00-4130.AUD	Anything else?
							Delay(500);
							Actor_Says(kActorMcCoy, 8990, 14); //00-8990.AUD	What have you got there?
							Actor_Change_Animation_Mode(kActorMcCoy, 23);
							Actor_Change_Animation_Mode(kActorDeskClerk, 23);
							Delay(800);
							Item_Pickup_Spin_Effect_From_Actor(kModelAnimationCheese, kActorMcCoy, 0, 0);
							Actor_Clue_Acquire(kActorMcCoy, kClueCheese, true, kActorDeskClerk);
							Delay(800);
							Actor_Says(kActorMcCoy, 8820, 14);	//00-8820.AUD	A piece of cheese.
							Actor_Voice_Over(480, kActorVoiceOver);
							Actor_Voice_Over(490, kActorVoiceOver);
							Actor_Voice_Over(500, kActorVoiceOver);
							Delay(500);
							Actor_Says(kActorMcCoy, 5850, 13); //00-5850.AUD	Where did you get this?
							Delay(500);
							Actor_Face_Heading(kActorMcCoy, 240, false);
							Actor_Face_Heading(kActorDeskClerk, 240, false);
							Actor_Says(kActorDeskClerk, 170, 13);
							Delay(1000);
							Actor_Says(kActorMcCoy, 615, -1); //00-0615.AUD	The back room.
							Delay(1000);
							Actor_Says(kActorMcCoy, 6975, -1); //00-6975.AUD	Interesting.
							Actor_Face_Actor(kActorDeskClerk, kActorMcCoy, true);
							Game_Flag_Set(kFlagCT09DeskClerkTalk2);
						} else {
							Actor_Says(kActorDeskClerk, 110, 15); //27-0110.AUD	Mister, you don't want to know. It'd take a Level Four suit just to put a key in the door. 
							if (Player_Query_Agenda() != kPlayerAgendaPolite) {
								Actor_Says(kActorMcCoy, 3910, 14); //00-3910.AUD	You’re lying. 
								Actor_Says(kActorDeskClerk, 280, 14); //27-0280.AUD	You seem to think I care.
								if (Player_Query_Agenda() == kPlayerAgendaSurly 
								|| Player_Query_Agenda() == kPlayerAgendaErratic) {
									Actor_Says(kActorMcCoy, 8519, 14);//00-8519.AUD	What do you say we dish each other the straight goods.
									Actor_Says(kActorDeskClerk, 300, 13); //27-0300.AUD	Okay, okay! 
									Actor_Says(kActorDeskClerk, 290, 15); //27-0290.AUD	So I lied. Cause you won't like what I heard, that's why—
									Actor_Says(kActorMcCoy, 6985, 16); //00-6985.AUD	Got the straight scoop for me or what?
									Actor_Says(kActorDeskClerk, 260, 14); //27-0260.AUD	If I tell you this, will you promise to go our separate ways?
									Actor_Says(kActorMcCoy, 1025, 13); //00-1025.AUD	Absolutely.
									Delay(1000);
									Actor_Says(kActorDeskClerk, 120, 13); //27-0120.AUD	Used to store all the booty the tenants left behind in there.
									Actor_Says(kActorDeskClerk, 130, 14);  //27-0130.AUD	My boss sold everything to a Mongolian guy last month
									Actor_Says(kActorMcCoy, 625, 13); //00-0625.AUD	So, now there's nothing in there.
									Actor_Says(kActorDeskClerk, 140, 13); //27-0140.AUD	Rumor has it the boss wants to rent it out. What a dump.
									Actor_Says(kActorDeskClerk, 150, 15); //27-0150.AUD	Maybe if we paid you, someone would actually want to stay there. (laughs)
									Actor_Says(kActorMcCoy, 4130, 13); //00-4130.AUD	Anything else?
									Delay(500);
									Actor_Says(kActorMcCoy, 8990, 14); //00-8990.AUD	What have you got there?
									Actor_Change_Animation_Mode(kActorMcCoy, 23);
									Actor_Change_Animation_Mode(kActorDeskClerk, 23);
									Delay(800);
									Item_Pickup_Spin_Effect_From_Actor(kModelAnimationCheese, kActorMcCoy, 0, 0);
									Actor_Clue_Acquire(kActorMcCoy, kClueCheese, true, kActorDeskClerk);
									Delay(800);
									Actor_Says(kActorMcCoy, 8820, 14);	//00-8820.AUD	A piece of cheese.
									Actor_Voice_Over(480, kActorVoiceOver);
									Actor_Voice_Over(490, kActorVoiceOver);
									Actor_Voice_Over(500, kActorVoiceOver);
									Delay(500);
									Actor_Says(kActorMcCoy, 5850, 13); //00-5850.AUD	Where did you get this?
									Delay(500);
									Actor_Face_Heading(kActorMcCoy, 240, false);
									Actor_Face_Heading(kActorDeskClerk, 240, false);
									Actor_Says(kActorDeskClerk, 170, 13);
									Delay(1000);
									Actor_Says(kActorMcCoy, 615, -1); //00-0615.AUD	The back room.
									Delay(1000);
									Actor_Says(kActorMcCoy, 6975, -1); //00-6975.AUD	Interesting.
									Actor_Face_Actor(kActorDeskClerk, kActorMcCoy, true);
									Game_Flag_Set(kFlagCT09DeskClerkTalk2);
								}
							}
						}
					// Made it so the desk clerk treats you differently depending on your actions. If you helped the clerk out with Leon he will be nice to you.
					// If you helped out the clerk but rang the bell he will be neutral towrds you. If you didn't help out the clerk he will be mean to you.
					} else {
						if (!Game_Flag_Query(kFlagBellRung) 
						&& Game_Flag_Query(kFlagCT09LeonInterrupted)) {
							Actor_Says(kActorMcCoy, 660, 14); //00-0660.AUD	You seen any suspicious types around here lately?
							Actor_Says(kActorDeskClerk, 230, 13); //27-0230.AUD	Hey, rest up them dogs right down in the lobby here.
							Actor_Says(kActorDeskClerk, 240, 15); //27-0240.AUD	I assure you. You'll see a lot of fine people strolling through
							if (Player_Query_Agenda() == kPlayerAgendaPolite) {
								Actor_Says(kActorMcCoy, 3140, 16); //00-3140.AUD	Thanks.
							}
							Player_Gains_Control();
						} else if (Game_Flag_Query(kFlagBellRung)
						&& Game_Flag_Query(kFlagCT09LeonInterrupted)) {
							Actor_Says(kActorMcCoy, 650, 18); //00-0650.AUD	You seen any suspicious types around here lately?
							Actor_Says(kActorDeskClerk, 220, 15); //27-0220.AUD	Howley, that's all I do see. You think this is a Club Med or something?	
							Actor_Says(kActorMcCoy, 655, 13); //00-0655.AUD	But no one you could put your finger on.
							Actor_Says(kActorDeskClerk, 270, 15); //27-0270.AUD	I mind my own business, pal. I don't see who goes in and I don't see who goes out.
						} else if (!Game_Flag_Query(kFlagBellRung)
						&& !Game_Flag_Query(kFlagCT09LeonInterrupted)) {
							Actor_Says(kActorMcCoy, 650, 18); //00-0650.AUD	You seen any suspicious types around here lately?
							Actor_Says(kActorDeskClerk, 220, 15); //27-0220.AUD	Howley, that's all I do see. You think this is a Club Med or something?	
							Actor_Says(kActorMcCoy, 655, 13); //00-0655.AUD	But no one you could put your finger on.
							Actor_Says(kActorDeskClerk, 270, 15); //27-0270.AUD	I mind my own business, pal. I don't see who goes in and I don't see who goes out.
						} else if (Game_Flag_Query(kFlagBellRung)
						&& !Game_Flag_Query(kFlagCT09LeonInterrupted)) {
							Actor_Says(kActorMcCoy, 660, 14); //00-0660.AUD	You seen any suspicious types around here lately?
							Actor_Says(kActorDeskClerk, 250, 13); //27-0250.AUD	You're pretty suspicious.
							if (Player_Query_Agenda() != kPlayerAgendaSurly 
							&& Player_Query_Agenda() != kPlayerAgendaErratic) {
								Actor_Says(kActorMcCoy, 2685, 13);
							} else {
								Actor_Says(kActorMcCoy, 665, 16); //00-0665.AUD	Real funny, pal.
							}
						}	
					}	
				} else {
					Actor_Says(kActorMcCoy, 650, 18);
					Actor_Says(kActorDeskClerk, 220, 15);
				}
				Player_Gains_Control();
			}
		}
		return true;
	}
	return false;
}

bool SceneScriptCT09::ClickedOnItem(int itemId, bool a2) {
	return false;
}

bool SceneScriptCT09::ClickedOnExit(int exitId) {
	if (exitId == 0) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, 206.0f, 348.52f, 599.0f, 0, true, false, false)) {
			Loop_Actor_Walk_To_XYZ(kActorMcCoy, 235.0f, 348.52f, 599.0f, 0, false, false, false);
			Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
			Ambient_Sounds_Remove_All_Looping_Sounds(1u);
			Set_Enter(kSetCT08_CT51_UG12, kSceneCT08);
		}
		return true;
	}

	if (exitId == 1) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, 107.0f, 348.52f, 927.0f, 0, true, false, false)) {
			Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
			Ambient_Sounds_Remove_All_Looping_Sounds(1u);
			Set_Enter(kSetCT11, kSceneCT11);
		}
		return true;
	}

	if (exitId == 2) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, 159.0f, 349.0f, 570.0f, 0, true, false, false)) {
			Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
			Ambient_Sounds_Remove_All_Looping_Sounds(1u);
			Set_Enter(kSetCT10, kSceneCT10);
		}
		return true;
	}
	return false;
}

bool SceneScriptCT09::ClickedOn2DRegion(int region) {
	return false;
}

void SceneScriptCT09::SceneFrameAdvanced(int frame) {
	if (frame == 6
	 || frame == 12
	 || frame == 19
	 || frame == 25
	 || frame == 46
	 || frame == 59
	) {
		Sound_Play(kSfxNEON7, Random_Query(47, 47), 70, 70, 50);
	}
}

void SceneScriptCT09::ActorChangedGoal(int actorId, int newGoal, int oldGoal, bool currentSet) {
}

void SceneScriptCT09::PlayerWalkedIn() {
	bool leonScene = false;

	if ( Global_Variable_Query(kVariableChapter) == 3
	 && !Game_Flag_Query(kFlagCT09Entered)
	) {
		Game_Flag_Set(kFlagCT09Entered);
		Actor_Set_Goal_Number(kActorLeon, kGoalLeonHoldingDeskClerk);
		leonScene = true;
		// Jake - Removed the code which disables the scene exits so when Leon approaches McCoy and the player has been given control
		// they have a chance to escape. 
	}

	if (Game_Flag_Query(kFlagCT10toCT09)) {
		Game_Flag_Reset(kFlagCT10toCT09);
	} else if (Game_Flag_Query(kFlagCT08toCT09)) {
		if (leonScene) {
			if (_vm->_cutContent) {
				if (Player_Query_Agenda() == kPlayerAgendaPolite) {
					Actor_Set_At_XYZ(kActorMcCoy, 206.0f, 348.52f, 599.0f, 0);
					Actor_Face_Actor(kActorMcCoy, kActorLeon, true);
					Delay(3000);
					Player_Set_Combat_Mode(true);
				} else {
					Async_Actor_Walk_To_XYZ(kActorMcCoy, 206.0f, 348.52f, 599.0f, 0, false);
				}
			} else {
				Async_Actor_Walk_To_XYZ(kActorMcCoy, 206.0f, 348.52f, 599.0f, 0, false);
			}
		} else {
			Loop_Actor_Walk_To_XYZ(kActorMcCoy, 206.0f, 348.52f, 599.0f, 0, false, false, false);
		}
		Game_Flag_Reset(kFlagCT08toCT09);
	} else {
		if (leonScene) {
			Async_Actor_Walk_To_XYZ(kActorMcCoy, 124.0f, 348.52f, 886.0f, 0, false);
		} else {
			Loop_Actor_Walk_To_XYZ(kActorMcCoy, 124.0f, 348.52f, 886.0f, 0, false, false, false);
		}
	}

	if (Actor_Query_Goal_Number(kActorDeskClerk) == kGoalDeskClerkRecovered) {
		if (_vm->_cutContent) {
			Actor_Face_Actor(kActorMcCoy, kActorDeskClerk, true);
			Delay(1000);
			Actor_Says(kActorMcCoy, 755, 18);
			Actor_Face_Actor(kActorDeskClerk, kActorMcCoy, true);
		}
		if (Game_Flag_Query(kFlagCT09LeonInterrupted)) {
			Actor_Says(kActorDeskClerk, 70, 13);
			Actor_Face_Actor(kActorMcCoy, kActorDeskClerk, true);
			Actor_Says(kActorMcCoy, 600, 17); //00-0600.AUD	He looked familiar.
			Actor_Says(kActorDeskClerk, 80, 14);
			if (_vm->_cutContent) {
				if (Player_Query_Agenda() == kPlayerAgendaPolite) {
					Actor_Says(kActorMcCoy, 605, 13); //00-0605.AUD	“To Protect and to Serve.”
				} else {
					Delay(1000);
				}
			} else {
				Actor_Says(kActorMcCoy, 605, 13); //00-0605.AUD	“To Protect and to Serve.”
			}
			Actor_Says(kActorDeskClerk, 90, 15);
		} else {
			// Quote 30 is *boop* in ENG and DEU versions
			// In FRA version it is muted
			// In ESP and ITA versions it is the missing second half of quote 20, and is required!
			if (_vm->_cutContent
			    && (_vm->_language == Common::ES_ESP
			        || _vm->_language == Common::IT_ITA)
			) {
				Actor_Says_With_Pause(kActorDeskClerk, 20, 0.0f, 12);
				Actor_Says(kActorDeskClerk, 30, kAnimationModeTalk);
			} else {
				if (_vm->_cutContent) {
					Actor_Face_Actor(kActorDeskClerk, kActorMcCoy, true);
				}
				Actor_Says(kActorDeskClerk, 20, 12);
			}
			if (_vm->_cutContent) {
				Actor_Face_Actor(kActorMcCoy, kActorDeskClerk, true);
				if (Player_Query_Agenda() == kPlayerAgendaSurly 
				|| Player_Query_Agenda() == kPlayerAgendaErratic) {
					Actor_Says(kActorMcCoy, 585, 18);
					Actor_Says(kActorDeskClerk, 40, 15);
					Actor_Says(kActorMcCoy, 590, 16);
					Actor_Says(kActorDeskClerk, 50, 14);
					Actor_Says(kActorMcCoy, 595, 14);
					Actor_Says(kActorDeskClerk, 60, 13);
					Actor_Modify_Friendliness_To_Other(kActorDeskClerk, kActorMcCoy, -1);
				} else if (Player_Query_Agenda() == kPlayerAgendaPolite) { 
					Delay(1000);
					Actor_Says(kActorMcCoy, 2305, 13); //00-2305.AUD	I’m sorry.
				} else {
					Actor_Says(kActorMcCoy, 4880, 13); //00-4880.AUD	Is that right?
					Actor_Says(kActorDeskClerk, 60, 13);
				}
			} else {
				Actor_Face_Actor(kActorMcCoy, kActorDeskClerk, true);
				Actor_Says(kActorMcCoy, 585, 18);
				Actor_Says(kActorDeskClerk, 40, 15);
				Actor_Says(kActorMcCoy, 590, 16);
				Actor_Says(kActorDeskClerk, 50, 14);
				Actor_Says(kActorMcCoy, 595, 14);
				Actor_Says(kActorDeskClerk, 60, 13);
				Actor_Modify_Friendliness_To_Other(kActorDeskClerk, kActorMcCoy, -1);
			}
		}
		Actor_Set_Goal_Number(kActorDeskClerk, kGoalDeskClerkDefault);
	}
}

void SceneScriptCT09::PlayerWalkedOut() {
}

void SceneScriptCT09::DialogueQueueFlushed(int a1) {
	Actor_Force_Stop_Walking(kActorMcCoy);

	if ( Actor_Query_Goal_Number(kActorLeon) == kGoalLeonHoldingDeskClerk
	 && !Game_Flag_Query(kFlagCT09LeonInterrupted)
	) {
		Player_Loses_Control();
		Actor_Set_Goal_Number(kActorLeon, kGoalLeonReleaseDeskClerk);
		//return true;
	}

	//return false;
}

} // End of namespace BladeRunner
