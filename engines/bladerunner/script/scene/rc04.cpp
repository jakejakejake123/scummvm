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

void SceneScriptRC04::InitializeScene() {
	Setup_Scene_Information(45.0f, 0.15f, 68.0f, 1018);

	Scene_Exit_Add_2D_Exit(0, 225, 47, 359, 248, 0);
	// Added a 2D region to the left weapons cabinet so when the player clicks on it the dialogue about the bullet proof vest plays.
	if (_vm->_cutContent) {
		if (!Game_Flag_Query(kFlagMcCoyHasVest)) {
			Scene_2D_Region_Add(0, 1, 1, 150, 200); 
		}
	}
	if (!Game_Flag_Query(kFlagRC04McCoyShotBob)) {
		Actor_Put_In_Set(kActorBulletBob, kSetRC04);
		Actor_Set_At_XYZ(kActorBulletBob, -60.0f, -11.0f, 62.0f, 12);
	}
	if (_vm->_cutContent) {
		if (Game_Flag_Query(kFlagRC04McCoyShotBob)) {
			Actor_Change_Animation_Mode(kActorBulletBob, 88);
		} else if (!Game_Flag_Query(kFlagBulletBobIsReplicant)
		&& Game_Flag_Query(kFlagIzoIsReplicant)) { 
			Actor_Set_Targetable(kActorBulletBob, false);
			Actor_Face_Heading(kActorBulletBob, 281, false);	
			Actor_Change_Animation_Mode(kActorBulletBob, 88);
			Scene_2D_Region_Remove(0);
		}
	} else if (Game_Flag_Query(kFlagRC04McCoyShotBob)) {
		Actor_Change_Animation_Mode(kActorBulletBob, 88);
	}
	if (_vm->_cutContent) {
		if (Game_Flag_Query(kFlagBulletBobIsReplicant)
		&& Actor_Query_Goal_Number(kActorBulletBob) < kGoalBulletBobGone 
		&& Global_Variable_Query(kVariableChapter) == 4) {
			AI_Movement_Track_Flush(kActorOfficerLeary);
			Actor_Put_In_Set(kActorOfficerLeary, kSetRC04);
			Actor_Set_At_XYZ(kActorOfficerLeary, 21.82f, 0.25f, -91.65f, 760);
		}
	}

	Ambient_Sounds_Add_Looping_Sound(kSfxRAIN10, 100, 1, 1);
	Ambient_Sounds_Add_Sound(kSfxRCCARBY1, 5, 30, 10, 20, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxRCCARBY2, 5, 30, 10, 20, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxRCCARBY3, 5, 30, 10, 20, -100, 100, -101, -101, 0, 0);
}

void SceneScriptRC04::SceneLoaded() {
	Obstacle_Object("Door New 01", true);
	Obstacle_Object("GRNDNEON05", true);
	Obstacle_Object("GRNDNEON06", true);
	Obstacle_Object("GRNDNEON07", true);
	Unobstacle_Object("DisplayTrim", true);
	Unobstacle_Object("Display01", true);
	Actor_Set_Goal_Number(kActorGenwalkerA, kGoalGenwalkerABulletBobsTrackGun);
	if (_vm->_cutContent) {
		if (!Game_Flag_Query(kFlagBulletBobIsReplicant)
		&& Game_Flag_Query(kFlagIzoIsReplicant)) { 
			Item_Add_To_World(kItemChopstickWrapper, kModelAnimationAmmoType00, kSceneRC04, 2.82f, 0.25f, -89.61f, 625, 6, 6, false, true, false, true);
		}
	}
}

bool SceneScriptRC04::MouseClick(int x, int y) {
	return false;
}

bool SceneScriptRC04::ClickedOn3DObject(const char *objectName, bool a2) {
	return false;
}

void SceneScriptRC04::dialogueWithBulletBob() {
	Dialogue_Menu_Clear_List();
	if (_vm->_cutContent) {
		if (Actor_Clue_Query(kActorMcCoy, kClueShellCasings)
		&& Actor_Clue_Query(kActorMcCoy, kClueLabShellCasings)
		&& !Actor_Clue_Query(kActorMcCoy, kClueWeaponsCache)) {
		 DM_Add_To_List_Never_Repeat_Once_Selected(580, 7, 8, 9); // WEAPONS
		}
	} else if ( Actor_Clue_Query(kActorMcCoy, kClueLabShellCasings)
	 && !Actor_Clue_Query(kActorMcCoy, kClueRadiationGoggles)
	) {
		DM_Add_To_List_Never_Repeat_Once_Selected(580, -1, 4, 9); // WEAPONS
	}
	if (_vm->_cutContent) {
		if (Actor_Clue_Query(kActorMcCoy, kClueShellCasings)
		&& !Actor_Clue_Query(kActorMcCoy, kClueLabShellCasings)
		&& !Actor_Clue_Query(kActorMcCoy, kClueWeaponsCache)) {
			DM_Add_To_List_Never_Repeat_Once_Selected(590, 6, 7, 8); // SHELL CASINGS
		}
	} else if ( Actor_Clue_Query(kActorMcCoy, kClueShellCasings)
	 && !Actor_Clue_Query(kActorMcCoy, kClueLabShellCasings)
	 && !Actor_Clue_Query(kActorMcCoy, kClueRadiationGoggles)
	) {
		DM_Add_To_List_Never_Repeat_Once_Selected(590, 6, 5, 3); // SHELL CASINGS
	}
	if (_vm->_cutContent) {
		if (Actor_Clue_Query(kActorMcCoy, kClueHasanInterview)) {
			DM_Add_To_List_Never_Repeat_Once_Selected(600, 1, 2, 3); // HASAN
		}
	} else {
		DM_Add_To_List_Never_Repeat_Once_Selected(600, -1, 3, 7); // HASAN
	}
	if (!_vm->_cutContent) {
		DM_Add_To_List_Never_Repeat_Once_Selected(1310, -1, 2, 8); // VOIGT-KAMPFF
	} 
	if ( Actor_Clue_Query(kActorMcCoy, kClueRadiationGoggles)
	 && !Actor_Clue_Query(kActorMcCoy, kClueGogglesReplicantIssue)
	) {
		DM_Add_To_List_Never_Repeat_Once_Selected(610, 4, 5, 6); // GOGGLES
	}
	if (_vm->_cutContent) {
		if (!Game_Flag_Query(kFlagRC04BobTalkAmmo)) {
			DM_Add_To_List_Never_Repeat_Once_Selected(1280, 5, 4, 7); // AMMO
		}
	} else {
		if (!Game_Flag_Query(kFlagRC04BobTalkAmmo)) {
			DM_Add_To_List_Never_Repeat_Once_Selected(1280, 1, 2, 3); // AMMO
		}
	}
	if ( Actor_Clue_Query(kActorMcCoy, kClueHoldensBadge)
	) {
		// Made it so the Holdens badge option is only available if Bob is a human. If Bob is a replicant 
		// he won't be friends with Holden 
		if (_vm->_cutContent) {
			if (!Game_Flag_Query(kFlagBulletBobIsReplicant)) {
				DM_Add_To_List_Never_Repeat_Once_Selected(620, 2, 3, 4); // HOLDEN'S BADGE
			}
		} else {
			DM_Add_To_List_Never_Repeat_Once_Selected(620, 1, -1, -1); // HOLDEN'S BADGE
		}
	}
	Dialogue_Menu_Add_DONE_To_List(630); // DONE

	Dialogue_Menu_Appear(320, 240);
	int answer = Dialogue_Menu_Query_Input();
	Dialogue_Menu_Disappear();

	switch (answer) {
	case 580: // WEAPONS
		if (_vm->_cutContent) {
			Actor_Face_Actor(kActorBulletBob, kActorMcCoy, true);
			Actor_Face_Actor(kActorMcCoy, kActorBulletBob, true);
		}
		Actor_Says(kActorMcCoy, 4955, 30);
		Actor_Says(kActorBulletBob, 210, 37);
		if (_vm->_cutContent) {
			if (!Game_Flag_Query(kFlagBulletBobIsReplicant)) {
				if (Actor_Query_Friendliness_To_Other(kActorBulletBob, kActorMcCoy) > 49) {
					Actor_Says(kActorBulletBob, 220, 37); //14-0220.AUD	Wish I had one, though. The Ender was a real workhorse.
					Actor_Says(kActorBulletBob, 230, 37); //14-0230.AUD	Good stopping power, decent rate of fire.
					Actor_Says(kActorBulletBob, 240, 37);
					Actor_Says(kActorMcCoy, 4990, 16);
				}
			}
		} else {
			Actor_Says(kActorBulletBob, 220, 37); //14-0220.AUD	Wish I had one, though. The Ender was a real workhorse.
			Actor_Says(kActorBulletBob, 230, 37); //14-0230.AUD	Good stopping power, decent rate of fire.
			Actor_Says(kActorBulletBob, 240, 37);
			Actor_Says(kActorMcCoy, 4990, 16);
		}
		Actor_Says(kActorMcCoy, 4995, 11); //00-4995.AUD	Somebody shot up Runciter's shop with one.
		// Added in some dialogue for Bob and McCoy.
		if (_vm->_cutContent) {
			Actor_Says(kActorBulletBob, 1860, 33); //14-1860.AUD	Runciter? You mean that animal dealer down the street?
			Actor_Says(kActorMcCoy, 8535, 18); //00-8535.AUD	Yeah.
			Delay (2000);
		}
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagBulletBobIsReplicant)) {
				Actor_Says(kActorBulletBob, 270, 31); // 14-0270.AUD	Sucker had it coming. I'm sure of that.
				Actor_Says(kActorMcCoy, 5005, 16); 
				Actor_Says(kActorBulletBob, 280, 32);
				Actor_Says(kActorBulletBob, 290, 30);
				Actor_Says(kActorBulletBob, 300, 33);
				Actor_Says(kActorBulletBob, 310, 31); //14-0310.AUD	it's out of here. Got no place at Bullet Bob's.
			} else {
				Actor_Says(kActorBulletBob, 1700, 30); //14-1700.AUD	Damn. You know I'm getting to be an old man and I ain't gonna...
				Actor_Says(kActorMcCoy, 3730, 16); // 00-3730.AUD	Animal murder is pretty horrible.
				Actor_Says(kActorBulletBob, 1550, 31); //14-1550.AUD	I'd kick the crap out of that sicko.
				Actor_Says(kActorBulletBob, 1340, 37); //14-1340.AUD	You know what I mean?
			}
		} else {
			Actor_Says(kActorBulletBob, 270, 31); // 14-0270.AUD	Sucker had it coming. I'm sure of that.
			Actor_Says(kActorMcCoy, 5005, 16); 
			Actor_Says(kActorBulletBob, 280, 32);
			Actor_Says(kActorBulletBob, 290, 30);
			Actor_Says(kActorBulletBob, 300, 33);
			Actor_Says(kActorBulletBob, 310, 31); //14-0310.AUD	it's out of here. Got no place at Bullet Bob's.
		}
		Actor_Says(kActorMcCoy, 5010, 11);
		// Made it so Bobs opinion on Izo will be determined by Bobs replicant status. If Bob is a replicant he will always speak positively about Izo and
		// if Bob is a human he will always speak negatively about Izo.
		if (_vm->_cutContent) {
			if (!Game_Flag_Query(kFlagBulletBobIsReplicant)
			&& Actor_Query_Friendliness_To_Other(kActorBulletBob, kActorMcCoy) > 49) {
				Actor_Says(kActorBulletBob, 320, 30);
				Actor_Says(kActorBulletBob, 330, 33);
				Actor_Says(kActorBulletBob, 340, 37); //14-0340.AUD	But who knows what the real title is.
				Actor_Says(kActorMcCoy, 5015, 11);
				Actor_Says(kActorBulletBob, 350, 32); //14-0350.AUD	I've been around here a long time, Ray.
				Actor_Says(kActorBulletBob, 360, 33); //14-0360.AUD	It always pisses me off when some dilettante
				Actor_Says(kActorBulletBob, 370, 30); //14-0370.AUD	sets up shop and tries to horn in on my action.
				Actor_Says(kActorMcCoy, 5020, 16); //00-5020.AUD	How long has Izo been around?
				Actor_Says(kActorBulletBob, 390, 11); //14-0390.AUD	I went over to introduce myself when he first moved in and he practically ignored me!
				Actor_Says(kActorMcCoy, 7805, 13); //00-7805.AUD	Answer the question.
				Actor_Says(kActorBulletBob, 400, 37); //14-0400.AUD	Said he was too busy to talk. Don't think I didn't consider kicking his ass, too.
				Delay(1000);
				Actor_Says(kActorMcCoy, 5080, 11); //00-5080.AUD	Just answer the question.
				Delay(500);
				Actor_Says(kActorBulletBob, 380, 37); //14-0380.AUD	He's brand-new. He's a cold son of a bitch, too.
				Actor_Clue_Acquire(kActorMcCoy, kClueBobInterview1, true, kActorBulletBob);
				Delay(1000);
				if (Player_Query_Agenda() == kPlayerAgendaPolite) {
					Actor_Says(kActorMcCoy, 5040, 16); //00-5040.AUD	Sometimes you just got to be philosophical about these things.
				} else {
					Actor_Says(kActorMcCoy, 7835, 16); //00-7835.AUD	Is that so?
				}
				Actor_Says(kActorBulletBob, 630, 32); // 14-0630.AUD	He's got that cold Rep way about him. You know what I mean?
				if (Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
					Actor_Says(kActorMcCoy, 5055, 11); // 00-5055.AUD	Don't jump to conclusions.
				} else {
					Actor_Says(kActorMcCoy, 8320, 11); //00-8320.AUD	Really?
				}
				Actor_Says(kActorBulletBob, 440, 31); // 14-0440.AUD	I was out there, Ray. I did my time. Three and a half years worth.
				Actor_Says(kActorBulletBob, 450, 32); //14-0450.AUD	And I can tell you: Reps got no business being down here on Earth, okay?	
				// Made it so McCoy only says Earth doesn't deserve replicants if he is surly or erratic.
				if (!Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
					if (Player_Query_Agenda() == kPlayerAgendaSurly
					|| Player_Query_Agenda() == kPlayerAgendaErratic) { 
						Actor_Says(kActorMcCoy, 5030, 16); //00-5030.AUD	Yeah. Earth don't deserve them.
						Actor_Says(kActorBulletBob, 460, 37); //14-0460.AUD	Tell me about it. We got standards to uphold down here.
						Actor_Modify_Friendliness_To_Other(kActorBulletBob, kActorMcCoy, 2);
					} else {
						Actor_Says(kActorMcCoy, 7980, 19); //00-7980.AUD	Yeah. Maybe.
					}
				} else {
					Actor_Says(kActorMcCoy, 4880, 13); //00-4880.AUD	Is that right?
				}
			} else {
				Actor_Says(kActorBulletBob, 1820, 34); //14-1820.AUD	You want to make it as a Blade Runner, you ought to do your own investigations.
				if (Player_Query_Agenda() == kPlayerAgendaSurly 
				|| Player_Query_Agenda() == kPlayerAgendaErratic) {
					Actor_Says(kActorMcCoy, 8445, 14); //00-8445.AUD	Cough it up!
					Delay(1000);
					Actor_Says(kActorMcCoy, 1805, 14); //00-1805.AUD	Now!
					Actor_Says(kActorBulletBob, 1840, 34); //14-1840.AUD	Okay, okay, look.
					Actor_Says(kActorBulletBob, 1850, 35); //14-1850.AUD	I didn't want to get you riled up for no reason but here's the real skinny.
					Delay(1000);
					Actor_Says(kActorMcCoy, 4940, 13); //00-4940.AUD	Okay, let's have it.
					Delay(1000);
					Actor_Says(kActorBulletBob, 320, 30);
					Actor_Says(kActorBulletBob, 330, 33);
					Actor_Says(kActorBulletBob, 340, 37); //14-0340.AUD	But who knows what the real title is.
					Actor_Says(kActorMcCoy, 5015, 11);
					if (!Game_Flag_Query(kFlagBulletBobIsReplicant)) {
						Actor_Says(kActorBulletBob, 350, 32); //14-0350.AUD	I've been around here a long time, Ray.
						Actor_Says(kActorBulletBob, 360, 33); //14-0360.AUD	It always pisses me off when some dilettante
						Actor_Says(kActorBulletBob, 370, 30); //14-0370.AUD	sets up shop and tries to horn in on my action.
						Actor_Says(kActorMcCoy, 5020, 16); //00-5020.AUD	How long has Izo been around?
						Actor_Says(kActorBulletBob, 390, 11); //14-0390.AUD	I went over to introduce myself when he first moved in and he practically ignored me!
						Actor_Says(kActorMcCoy, 7805, 13); //00-7805.AUD	Answer the question.	
						Actor_Says(kActorBulletBob, 400, 37); //14-0400.AUD	Said he was too busy to talk. Don't think I didn't consider kicking his ass, too.
						Delay(1000);
						Actor_Says(kActorMcCoy, 5080, 11); //00-5080.AUD	Just answer the question.
						Delay(500);
						Actor_Says(kActorBulletBob, 380, 37); //14-0380.AUD	He's brand-new. He's a cold son of a bitch, too.
						Actor_Clue_Acquire(kActorMcCoy, kClueBobInterview1, true, kActorBulletBob);
						Delay(1000);
						if (Player_Query_Agenda() == kPlayerAgendaPolite) {
							Actor_Says(kActorMcCoy, 5040, 16); //00-5040.AUD	Sometimes you just got to be philosophical about these things.
						} else {
							Actor_Says(kActorMcCoy, 7835, 16); //00-7835.AUD	Is that so?
						}
						Actor_Says(kActorBulletBob, 630, 32); // 14-0630.AUD	He's got that cold Rep way about him. You know what I mean?
						if (Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
							Actor_Says(kActorMcCoy, 5055, 11); // 00-5055.AUD	Don't jump to conclusions.
						} else {
							Actor_Says(kActorMcCoy, 8320, 11); //00-8320.AUD	Really?
						}
						Actor_Says(kActorBulletBob, 440, 31); // 14-0440.AUD	I was out there, Ray. I did my time. Three and a half years worth.
						Actor_Says(kActorBulletBob, 450, 32); //14-0450.AUD	And I can tell you: Reps got no business being down here on Earth, okay?	
						// Made it so McCoy only says Earth doesn't deserve replicants if he is surly or erratic.
						if (!Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
							if (Player_Query_Agenda() == kPlayerAgendaSurly
							|| Player_Query_Agenda() == kPlayerAgendaErratic) { 
								Actor_Says(kActorMcCoy, 5030, 16); //00-5030.AUD	Yeah. Earth don't deserve them.
								Actor_Says(kActorBulletBob, 460, 37); //14-0460.AUD	Tell me about it. We got standards to uphold down here.
								Actor_Modify_Friendliness_To_Other(kActorBulletBob, kActorMcCoy, 2);
							} else {
								Actor_Says(kActorMcCoy, 7980, 19); //00-7980.AUD	Yeah. Maybe.
							}
						} else {
							Actor_Says(kActorMcCoy, 4880, 13); //00-4880.AUD	Is that right?
						}
					} else {
						Actor_Says(kActorBulletBob, 410, 11); //14-0410.AUD	Izo is okay. He's run the Green Pawn for a while.
						Actor_Says(kActorBulletBob, 420, 37); //14-0420.AUD	We're friendly competitors, I guess. But I don't appreciate his politics.
						Actor_Says(kActorMcCoy, 5025, 16); //00-5025.AUD	Yeah?
						Actor_Says(kActorBulletBob, 430, 30); //14-0430.AUD	Rumors that's all they are.
						Actor_Clue_Acquire(kActorMcCoy, kClueBobInterview1, true, kActorBulletBob);
					}
				} else {
					Actor_Says(kActorMcCoy, 5075, 18); //00-5075.AUD	Hey, pal.
				}
			}			
		} else {
			Actor_Says(kActorBulletBob, 320, 30);
			Actor_Says(kActorBulletBob, 330, 33);
			Actor_Says(kActorBulletBob, 340, 37);
			Actor_Says(kActorMcCoy, 5015, 11);
			if (Game_Flag_Query(kFlagIzoIsReplicant)) {
				Actor_Says(kActorBulletBob, 350, 32);
				Actor_Says(kActorBulletBob, 360, 33);
				Actor_Says(kActorBulletBob, 370, 30);
				Actor_Says(kActorMcCoy, 5020, 16);
				Actor_Says(kActorBulletBob, 380, 37);
				Actor_Says(kActorBulletBob, 390, 11);
				Actor_Says(kActorBulletBob, 400, 37);
#if BLADERUNNER_ORIGINAL_BUGS
				Actor_Clue_Acquire(kActorMcCoy, kClueBobInterview1, true, kActorMcCoy);  // A bug? Shouldn't the last argument be -1 or kActorBulletBob here?
#else
				Actor_Clue_Acquire(kActorMcCoy, kClueBobInterview1, true, kActorBulletBob);
#endif // BLADERUNNER_ORIGINAL_BUGS
			} else {
				Actor_Says(kActorBulletBob, 410, 11);
				Actor_Says(kActorBulletBob, 420, 37);
				Actor_Says(kActorMcCoy, 5025, 16);
				Actor_Says(kActorBulletBob, 430, 30);
				Actor_Says(kActorBulletBob, 440, 31);
				Actor_Says(kActorBulletBob, 450, 32);
				Actor_Says(kActorMcCoy, 5030, 16);
				Actor_Says(kActorBulletBob, 460, 37);
			}
#if BLADERUNNER_ORIGINAL_BUGS
			Actor_Clue_Acquire(kActorMcCoy, kClueBobInterview2, true, kActorMcCoy);  // A bug? Shouldn't the last argument be -1 or kActorBulletBob here?
#else
			Actor_Clue_Acquire(kActorMcCoy, kClueBobInterview2, true, kActorBulletBob);
#endif // BLADERUNNER_ORIGINAL_BUGS
		}
		return;

	case 590: // SHELL CASINGS
		if (_vm->_cutContent) {
			Actor_Face_Actor(kActorBulletBob, kActorMcCoy, true);
			Actor_Face_Actor(kActorMcCoy, kActorBulletBob, true);
		}
		if (_vm->_cutContent) {
			Actor_Says(kActorMcCoy, 4960, 23);
		} else {
			Actor_Says(kActorMcCoy, 4960, 13);
		}
		Actor_Says(kActorBulletBob, 250, 30);
		if (_vm->_cutContent) {
			if (!Game_Flag_Query(kFlagBulletBobIsReplicant)
			&& Actor_Query_Friendliness_To_Other(kActorBulletBob, kActorMcCoy) > 49) {
				Actor_Says(kActorBulletBob, 260, 33);
			} else {
				Delay(500);
			}
		} else {
			Actor_Says(kActorBulletBob, 260, 33);
		}
		Actor_Says(kActorMcCoy, 4995, 15); //00-4995.AUD	Somebody shot up Runciter's shop with one.
		// Added in some dialogue for Bob and McCoy.
		if (_vm->_cutContent) {
			Actor_Says(kActorBulletBob, 1860, 33); //14-1860.AUD	Runciter? You mean that animal dealer down the street?
			Actor_Says(kActorMcCoy, 8535, 18); ////00-8535.AUD	Yeah.
			Delay (2000);
		}
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagBulletBobIsReplicant)) {
				Actor_Says(kActorBulletBob, 270, 31); // 14-0270.AUD	Sucker had it coming. I'm sure of that.
				Actor_Says(kActorMcCoy, 5005, 16); 
				Actor_Says(kActorBulletBob, 280, 32);
				Actor_Says(kActorBulletBob, 290, 30);
				Actor_Says(kActorBulletBob, 300, 33);
				Actor_Says(kActorBulletBob, 310, 31); //14-0310.AUD	it's out of here. Got no place at Bullet Bob's.
			} else {
				Actor_Says(kActorBulletBob, 1700, 30); //14-1700.AUD	Damn. You know I'm getting to be an old man and I ain't gonna...
				Actor_Says(kActorMcCoy, 3730, 16); // 00-3730.AUD	Animal murder is pretty horrible.
				Actor_Says(kActorBulletBob, 1550, 31); //14-1550.AUD	I'd kick the crap out of that sicko.
				Actor_Says(kActorBulletBob, 1340, 37); //14-1340.AUD	You know what I mean?
			}
		} else {
			Actor_Says(kActorBulletBob, 270, 31); // 14-0270.AUD	Sucker had it coming. I'm sure of that.
			Actor_Says(kActorMcCoy, 5005, 16); 
			Actor_Says(kActorBulletBob, 280, 32);
			Actor_Says(kActorBulletBob, 290, 30);
			Actor_Says(kActorBulletBob, 300, 33);
			Actor_Says(kActorBulletBob, 310, 31); //14-0310.AUD	it's out of here. Got no place at Bullet Bob's.
		}
		Actor_Says(kActorMcCoy, 5010, 11); //00-5010.AUD	You know anyone who might sell Ender rifles?
		if (_vm->_cutContent) {
			if (!Game_Flag_Query(kFlagBulletBobIsReplicant)
			&& Actor_Query_Friendliness_To_Other(kActorBulletBob, kActorMcCoy) > 49) {
				Actor_Says(kActorBulletBob, 320, 30);
				Actor_Says(kActorBulletBob, 330, 33);
				Actor_Says(kActorBulletBob, 340, 37); //14-0340.AUD	But who knows what the real title is.
				Actor_Says(kActorMcCoy, 5015, 11);
				Actor_Says(kActorBulletBob, 350, 32); //14-0350.AUD	I've been around here a long time, Ray.
				Actor_Says(kActorBulletBob, 360, 33); //14-0360.AUD	It always pisses me off when some dilettante
				Actor_Says(kActorBulletBob, 370, 30); //14-0370.AUD	sets up shop and tries to horn in on my action.
				Actor_Says(kActorMcCoy, 5020, 16); //00-5020.AUD	How long has Izo been around?
				Actor_Says(kActorBulletBob, 390, 11); //14-0390.AUD	I went over to introduce myself when he first moved in and he practically ignored me!
				Actor_Says(kActorMcCoy, 7805, 13); //00-7805.AUD	Answer the question.	
				Actor_Says(kActorBulletBob, 400, 37); //14-0400.AUD	Said he was too busy to talk. Don't think I didn't consider kicking his ass, too.
				Delay(1000);
				Actor_Says(kActorMcCoy, 5080, 11); //00-5080.AUD	Just answer the question.
				Delay(500);
				Actor_Says(kActorBulletBob, 380, 37); //14-0380.AUD	He's brand-new. He's a cold son of a bitch, too.
				Actor_Clue_Acquire(kActorMcCoy, kClueBobInterview1, true, kActorBulletBob);
				Delay(1000);
				if (Player_Query_Agenda() == kPlayerAgendaPolite) {
					Actor_Says(kActorMcCoy, 5040, 16); //00-5040.AUD	Sometimes you just got to be philosophical about these things.
				} else {
					Actor_Says(kActorMcCoy, 7835, 16); //00-7835.AUD	Is that so?
				}
				Actor_Says(kActorBulletBob, 630, 32); // 14-0630.AUD	He's got that cold Rep way about him. You know what I mean?
				if (Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
					Actor_Says(kActorMcCoy, 5055, 11); // 00-5055.AUD	Don't jump to conclusions.
				} else {
					Actor_Says(kActorMcCoy, 8320, 11); //00-8320.AUD	Really?
				}
				Actor_Says(kActorBulletBob, 440, 31); // 14-0440.AUD	I was out there, Ray. I did my time. Three and a half years worth.
				Actor_Says(kActorBulletBob, 450, 32); //14-0450.AUD	And I can tell you: Reps got no business being down here on Earth, okay?
				// Made it so McCoy only says Earth doesn't deserve replicants if he is surly or erratic.
				if (!Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
					if (Player_Query_Agenda() == kPlayerAgendaSurly
					|| Player_Query_Agenda() == kPlayerAgendaErratic) { 
						Actor_Says(kActorMcCoy, 5030, 16); //00-5030.AUD	Yeah. Earth don't deserve them.
						Actor_Says(kActorBulletBob, 460, 37); //14-0460.AUD	Tell me about it. We got standards to uphold down here.
						Actor_Modify_Friendliness_To_Other(kActorBulletBob, kActorMcCoy, 2);
					} else {
						Actor_Says(kActorMcCoy, 7980, 19); //00-7980.AUD	Yeah. Maybe.						
					}
				} else {
					Actor_Says(kActorMcCoy, 4880, 13); //00-4880.AUD	Is that right?
				}
			} else {
				Actor_Says(kActorBulletBob, 1820, 34); //14-1820.AUD	You want to make it as a Blade Runner, you ought to do your own investigations.
				if (Player_Query_Agenda() == kPlayerAgendaSurly 
				|| Player_Query_Agenda() == kPlayerAgendaErratic) {
					Actor_Says(kActorMcCoy, 8445, 14); //00-8445.AUD	Cough it up!
					Delay(1000);
					Actor_Says(kActorMcCoy, 1805, 14); //00-1805.AUD	Now!
					Actor_Says(kActorBulletBob, 1840, 34); //14-1840.AUD	Okay, okay, look.
					Actor_Says(kActorBulletBob, 1850, 35); //14-1850.AUD	I didn't want to get you riled up for no reason but here's the real skinny.
					Delay(1000);
					Actor_Says(kActorMcCoy, 4940, 13); //00-4940.AUD	Okay, let's have it.
					Delay(1000);
					Actor_Says(kActorBulletBob, 320, 30);
					Actor_Says(kActorBulletBob, 330, 33);
					Actor_Says(kActorBulletBob, 340, 37); //14-0340.AUD	But who knows what the real title is.
					Actor_Says(kActorMcCoy, 5015, 11);
					if (!Game_Flag_Query(kFlagBulletBobIsReplicant)) {
						Actor_Says(kActorBulletBob, 350, 32); //14-0350.AUD	I've been around here a long time, Ray.
						Actor_Says(kActorBulletBob, 360, 33); //14-0360.AUD	It always pisses me off when some dilettante
						Actor_Says(kActorBulletBob, 370, 30); //14-0370.AUD	sets up shop and tries to horn in on my action.
						Actor_Says(kActorMcCoy, 5020, 16); //00-5020.AUD	How long has Izo been around?
						Actor_Says(kActorBulletBob, 390, 11); //14-0390.AUD	I went over to introduce myself when he first moved in and he practically ignored me!
						Actor_Says(kActorMcCoy, 7805, 13); //00-7805.AUD	Answer the question.	
						Actor_Says(kActorBulletBob, 400, 37); //14-0400.AUD	Said he was too busy to talk. Don't think I didn't consider kicking his ass, too.
						Delay(1000);
						Actor_Says(kActorMcCoy, 5080, 11); //00-5080.AUD	Just answer the question.
						Delay(500);
						Actor_Says(kActorBulletBob, 380, 37); //14-0380.AUD	He's brand-new. He's a cold son of a bitch, too.
						if (Player_Query_Agenda() == kPlayerAgendaPolite) {
							Actor_Says(kActorMcCoy, 5040, 16); //00-5040.AUD	Sometimes you just got to be philosophical about these things.
						} else {
							Actor_Says(kActorMcCoy, 7835, 16); //00-7835.AUD	Is that so?
						}
						Actor_Says(kActorBulletBob, 630, 32); // 14-0630.AUD	He's got that cold Rep way about him. You know what I mean?
						if (Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
							Actor_Says(kActorMcCoy, 5055, 11); // 00-5055.AUD	Don't jump to conclusions.
						} else {
							Actor_Says(kActorMcCoy, 8320, 11); //00-8320.AUD	Really?
						}
						Actor_Says(kActorBulletBob, 440, 31); // 14-0440.AUD	I was out there, Ray. I did my time. Three and a half years worth.
						Actor_Says(kActorBulletBob, 450, 32); //14-0450.AUD	And I can tell you: Reps got no business being down here on Earth, okay?	
						// Made it so McCoy only says Earth doesn't deserve replicants if he is surly or erratic.
						if (!Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
							if (Player_Query_Agenda() == kPlayerAgendaSurly
							|| Player_Query_Agenda() == kPlayerAgendaErratic) { 
								Actor_Says(kActorMcCoy, 5030, 16); //00-5030.AUD	Yeah. Earth don't deserve them.
								Actor_Says(kActorBulletBob, 460, 37); //14-0460.AUD	Tell me about it. We got standards to uphold down here.
								Actor_Modify_Friendliness_To_Other(kActorBulletBob, kActorMcCoy, 2);
							} else {
								Actor_Says(kActorMcCoy, 7980, 19); //00-7980.AUD	Yeah. Maybe.				
							}
						} else {
							Actor_Says(kActorMcCoy, 4880, 13); //00-4880.AUD	Is that right?
						}
					} else {
						Actor_Says(kActorBulletBob, 410, 11); //14-0410.AUD	Izo is okay. He's run the Green Pawn for a while.
						Actor_Says(kActorBulletBob, 420, 37); //14-0420.AUD	We're friendly competitors, I guess. But I don't appreciate his politics.
						Actor_Says(kActorMcCoy, 5025, 16); //00-5025.AUD	Yeah?
						Actor_Says(kActorBulletBob, 430, 30); //14-0430.AUD	Rumors that's all they are.
						Actor_Clue_Acquire(kActorMcCoy, kClueBobInterview1, true, kActorBulletBob);
					}
				}
			}			
		} else {
			Actor_Says(kActorBulletBob, 320, 30);
			Actor_Says(kActorBulletBob, 330, 33);
			Actor_Says(kActorBulletBob, 340, 37);
			Actor_Says(kActorMcCoy, 5015, 11);
			if (Game_Flag_Query(kFlagIzoIsReplicant)) {
				Actor_Says(kActorBulletBob, 350, 32);
				Actor_Says(kActorBulletBob, 360, 33);
				Actor_Says(kActorBulletBob, 370, 30);
				Actor_Says(kActorMcCoy, 5020, 16);
				Actor_Says(kActorBulletBob, 380, 37);
				Actor_Says(kActorBulletBob, 390, 11);
				Actor_Says(kActorBulletBob, 400, 37);
#if BLADERUNNER_ORIGINAL_BUGS
				Actor_Clue_Acquire(kActorMcCoy, kClueBobInterview1, true, kActorMcCoy);  // A bug? Shouldn't the last argument be -1 or kActorBulletBob here?
#else
				Actor_Clue_Acquire(kActorMcCoy, kClueBobInterview1, true, kActorBulletBob);
#endif // BLADERUNNER_ORIGINAL_BUGS
			} else {
				Actor_Says(kActorBulletBob, 410, 11);
				Actor_Says(kActorBulletBob, 420, 37);
				Actor_Says(kActorMcCoy, 5025, 16);
				Actor_Says(kActorBulletBob, 430, 30);
				Actor_Says(kActorBulletBob, 440, 31);
				Actor_Says(kActorBulletBob, 450, 32);
				Actor_Says(kActorMcCoy, 5030, 16);
				Actor_Says(kActorBulletBob, 460, 37);
			}
#if BLADERUNNER_ORIGINAL_BUGS
			Actor_Clue_Acquire(kActorMcCoy, kClueBobInterview2, true, kActorMcCoy);  // A bug? Shouldn't the last argument be -1 or kActorBulletBob here?
#else
			Actor_Clue_Acquire(kActorMcCoy, kClueBobInterview2, true, kActorBulletBob);
#endif // BLADERUNNER_ORIGINAL_BUGS
		}
		break;

	case 600: // HASAN
		if (_vm->_cutContent) {
			Actor_Face_Actor(kActorBulletBob, kActorMcCoy, true);
			Actor_Face_Actor(kActorMcCoy, kActorBulletBob, true);
		}
		Actor_Says(kActorMcCoy, 4965, 11);
		Actor_Says(kActorBulletBob, 470, 11);
		Actor_Says(kActorMcCoy, 5035, 15);
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagBulletBobIsReplicant)) {
				Actor_Says(kActorBulletBob, 480, 30); //14-0480.AUD	That's the one. I should have popped him when I had the chance.
			} 
		} else {
			Actor_Says(kActorBulletBob, 480, 30); //14-0480.AUD	That's the one. I should have popped him when I had the chance.
		}
		Actor_Says(kActorBulletBob, 490, 31); //14-0490.AUD	You want to know what really happened?
		if (_vm->_cutContent) {
			if (!Game_Flag_Query(kFlagBulletBobIsReplicant)) {
				Actor_Says(kActorBulletBob, 500, 32); //14-0500.AUD	I wanted to get my daughter a present for her birthday, right?
			}
		} else {
			Actor_Says(kActorBulletBob, 500, 32); //14-0500.AUD	I wanted to get my daughter a present for her birthday, right?
		}
		Actor_Says(kActorBulletBob, 510, 33); //14-0510.AUD	I bought an Iguana from that crook Hasan.
#if BLADERUNNER_ORIGINAL_BUGS
		Actor_Says(kActorBulletBob, 520, 34);
#else
		//  Quote 530 is the second half of the 520 sentence and flow of speech works better without the default delay
		Actor_Says_With_Pause(kActorBulletBob, 520, 0.0f, 34); 
#endif // BLADERUNNER_ORIGINAL_BUGS
		Actor_Says(kActorBulletBob, 530, 35);
		Actor_Says(kActorBulletBob, 540, 36); //14-0540.AUD	Son of a bitch wouldn't give me a refund. So I threatened to burn down his shop.
		if (_vm->_cutContent) {
			Actor_Clue_Acquire(kActorMcCoy, kClueBobRobbed, true, kActorBulletBob);
			Game_Flag_Set(kFlagMcCoyTalkedToBulletBobAboutHasan);
			Actor_Says(kActorMcCoy, 7835, 18); //00-7835.AUD	Is that so?
			if (Game_Flag_Query(kFlagBulletBobIsReplicant)) {
				Actor_Says(kActorBulletBob, 1310, 30); //14-1310.AUD	I meant to kill him so that was kind of embarrassing.
				Actor_Says(kActorMcCoy, 8320, 14); //00-8320.AUD	Really?
			}
			Actor_Says(kActorBulletBob, 1050, 30); //14-1050.AUD	The son of a bitch who robs me is dead.
			if (Game_Flag_Query(kFlagBulletBobIsReplicant)) {
				Actor_Says(kActorBulletBob, 1060, 18);//14-1060.AUD	Ka-blam. No fooling around.
			}
			Delay(2000);
			Actor_Says(kActorMcCoy, 4130, 18); //00-4130.AUD	Anything else?
			Actor_Says(kActorBulletBob, 1350, 35); //14-1350.AUD	I'd beat the crap out of him.
			if (Player_Query_Agenda() == kPlayerAgendaPolite) {
				Delay(2000);
				Actor_Says(kActorMcCoy, 5040, 16);
				if (!Game_Flag_Query(kFlagBulletBobIsReplicant)) {
					Actor_Says(kActorBulletBob, 550, 11); //14-0550.AUD	That's exactly what my wife says.
				}
			}
			Delay(1000);
			Actor_Says(kActorMcCoy, 4980, 11);
			if (Game_Flag_Query(kFlagBulletBobIsReplicant)
			|| Actor_Query_Friendliness_To_Other(kActorBulletBob, kActorMcCoy) < 50) {
				Actor_Says(kActorBulletBob, 770, 36); //14-0770.AUD	You mean the Voigt-Kampff?
				Actor_Says(kActorBulletBob, 780, 36); //14-0780.AUD	You come into my shop and you want to V-K me?
				if (Player_Query_Agenda() == kPlayerAgendaSurly
				|| Player_Query_Agenda() == kPlayerAgendaErratic) {
					Actor_Says(kActorMcCoy, 7930, 14); //00-7930.AUD	Stay right where you are.
				} else {
					Actor_Says_With_Pause(kActorMcCoy, 5090, 0.0f, 16); //00-5090.AUD	Relax, I just wa--
				}
				Actor_Says(kActorBulletBob, 790, 36); //14-0790.AUD	It's funny. You thinking I'm a Rep.
				Actor_Says(kActorBulletBob, 800, 35); // 14-0800.AUD	Set up the test. We'll see what's what around here.
			} else {
				Actor_Says(kActorBulletBob, 740, 37); //14-0740.AUD	Test? You mean the Voigt-Kampff?
				Actor_Says_With_Pause(kActorMcCoy, 5085, 0.0f, 16); //00-5085.AUD	Yeah, I don't think you're a Rep, but I want to--
				Actor_Says(kActorBulletBob, 750, 37); //14-0750.AUD	Hey, hey, hey. You don't have to explain. I always wanted to see the machine in action.
				Actor_Says(kActorBulletBob, 760, 37); //14-0760.AUD	Go on, set it up.
			}
			Voight_Kampff_Activate(kActorBulletBob, 50);	
			Actor_Says(kActorBulletBob, 810, 30); //14-0810.AUD	So that's it?
			Actor_Says(kActorMcCoy, 5025, 13); //00-5025.AUD	Yeah?
			Actor_Says(kActorBulletBob, 820, 31); //14-0820.AUD	Since you didn't shoot me, I must have registered okay.
			if (!Game_Flag_Query(kFlagBulletBobIsReplicant)
			&& Actor_Clue_Query(kActorMcCoy, kClueVKBobGorskyHuman)) {
				Actor_Says(kActorMcCoy, 5100, 11); //00-5100.AUD	Yeah, it was touch-and-go there for a while.
				if (Actor_Query_Friendliness_To_Other(kActorBulletBob, kActorMcCoy) > 49) {
					Actor_Says(kActorBulletBob, 830, 31); //14-0830.AUD	Well, you know, I think about skin-jobs all the time.
					Actor_Says(kActorBulletBob, 840, 35); //14-0840.AUD	Try to get into their heads. Maybe that's what the deal is.
				}
			}
			if (!Game_Flag_Query(kFlagBulletBobIsReplicant)
			&& Actor_Clue_Query(kActorMcCoy, kClueVKBobGorskyHuman)) {
				if (!Game_Flag_Query(kFlagIzoGotAway)
				&& !Game_Flag_Query(kFlagIzoOnTheRun)) {
					if (Player_Query_Agenda() != kPlayerAgendaSurly
					&& Player_Query_Agenda() != kPlayerAgendaErratic) {
						Actor_Says(kActorMcCoy, 3095, 15); //00-3095.AUD	Now we’re gonna take a little ride downtown.
						if (Game_Flag_Query(kFlagKIAPrivacyAddon)
						|| Game_Flag_Query(kFlagMcCoyHasVest)) {
							Actor_Says(kActorBulletBob, 1830, 33); //14-1830.AUD	I'm hurt, McCoy. Deeply hurt. After all I've done for you.
						} else {
							Actor_Says(kActorBulletBob, 1680, 34); //14-1680.AUD	Is that right?
							Actor_Says(kActorMcCoy, 2215, 18); //00-2215.AUD	That’s right.			
						}
						Delay (1000);
						Game_Flag_Set(kFlagBulletBobArrested);
						Actor_Modify_Friendliness_To_Other(kActorHasan, kActorMcCoy, 10);
						Actor_Put_In_Set(kActorBulletBob, kSetPS09);
						Actor_Set_At_XYZ(kActorBulletBob, -476.0f, 0.2f, -300.0f, 200);
						Game_Flag_Reset(kFlagSpinnerAtAR01);
						Game_Flag_Reset(kFlagSpinnerAtRC01);
						Game_Flag_Set(kFlagSpinnerAtPS01);
						Scene_Exits_Enable();
						Game_Flag_Reset(kFlagMcCoyInAnimoidRow);
						Game_Flag_Set(kFlagMcCoyInPoliceStation);
						Outtake_Play(kOuttakeAway1, true, -1);
						Set_Enter(kSetPS09, kScenePS09);
						Actor_Set_Targetable(kActorBulletBob, false);
					}
				}
			}	
		} else {
			Actor_Says(kActorMcCoy, 5040, 16);
			Actor_Says(kActorBulletBob, 550, 11); //14-0550.AUD	That's exactly what my wife says.
		}
		if (!_vm->_cutContent) {
			Actor_Modify_Friendliness_To_Other(kActorBulletBob, kActorMcCoy, -6);
		}
		Game_Flag_Set(kFlagMcCoyTalkedToBulletBobAboutHasan);
		break;

	case 610: // GOGGLES
		if (_vm->_cutContent) {
			Actor_Face_Actor(kActorBulletBob, kActorMcCoy, true);
			Actor_Face_Actor(kActorMcCoy, kActorBulletBob, true);
		}
		if (_vm->_cutContent) {
			Actor_Says(kActorMcCoy, 4970, 23);
		} else {
			Actor_Says(kActorMcCoy, 4970, 16);
		}
		if (Actor_Query_Friendliness_To_Other(kActorBulletBob, kActorMcCoy) < 50) {
			// Made it so Bob doesn't make certain comments if he is a replicant. Also it is now impossible for Bob to like you enough
			// to tell you about the goggles if he is a replicant, and why would he since he already doesn't like you for being a blade runner.
			if (_vm->_cutContent) {
				Actor_Says(kActorBulletBob, 700, 11); //14-0700.AUD	Looks like goggles.
				Actor_Says(kActorMcCoy, 5070, 11); //00-5070.AUD	Would a Replicant need something like this?
				if (!Game_Flag_Query(kFlagBulletBobIsReplicant)) {	
					Actor_Says(kActorBulletBob, 710, 11); //14-0710.AUD	You're asking me about what a skin-job would need?
				} else {
					Actor_Says(kActorBulletBob, 720, 30); //14-0720.AUD	Ask one of your friends.
				}
			} else {
				Actor_Says(kActorBulletBob, 700, 11); //14-0700.AUD	Looks like goggles.
				Actor_Says(kActorMcCoy, 5070, 11); //00-5070.AUD	Would a Replicant need something like this?
				Actor_Says(kActorBulletBob, 710, 11); //14-0710.AUD	You're asking me about what a skin-job would need?
			}	
			if (_vm->_cutContent) {
				if (Player_Query_Agenda() == kPlayerAgendaPolite) {
					Actor_Says(kActorMcCoy, 7380, 13); // M: Just answer the question please.
				} else if (Player_Query_Agenda() == kPlayerAgendaSurly
				|| Player_Query_Agenda() == kPlayerAgendaErratic) {
					Actor_Says(kActorMcCoy, 5080, 11); //00-5080.AUD	Just answer the question.
				} else {
					Actor_Says(kActorMcCoy, 7805, 13); //00-7805.AUD	Answer the question.
				}
			} else {
				Actor_Says(kActorMcCoy, 5080, 11); //00-5080.AUD	Just answer the question.
			}
			if (_vm->_cutContent) {
				if (!Game_Flag_Query(kFlagBulletBobIsReplicant)) {
					Actor_Says(kActorBulletBob, 730, 37); //14-0730.AUD	I hear they give out retirement bonuses to civilians that bag Reps.
				}
			} else { 
				Actor_Says(kActorBulletBob, 730, 37); //14-0730.AUD	I hear they give out retirement bonuses to civilians that bag Reps.
			}
			if (_vm->_cutContent) {
				Delay(2000);
				Actor_Says(kActorMcCoy, 440, 16); //00-0440.AUD	Forget it.
			}
#if BLADERUNNER_ORIGINAL_BUGS
			// Last argument should be -1 or kActorBulletBob here
			// However, this clue is acquired for asking about Izo, when Izo is Replicant
			// (see also the KIA entry for it, which references the audio recording from that discussion)
			// It should not be acquired here.
			Actor_Clue_Acquire(kActorMcCoy, kClueBobInterview1, true, kActorMcCoy);
#endif // BLADERUNNER_ORIGINAL_BUGS
		} else {
			if (_vm->_cutContent) {
				if (!Game_Flag_Query(kFlagBulletBobIsReplicant)) {
					Actor_Says(kActorBulletBob, 560, 37);
					Actor_Says(kActorMcCoy, 5070, 13);
					Actor_Says(kActorBulletBob, 570, 36);
					Actor_Says(kActorBulletBob, 580, 37); // //14-0580.AUD	The humans weren't allowed to get that close to the flash point. 
					Actor_Says(kActorMcCoy, 8190, 0);	// 00-8190.AUD	Why?
					Actor_Says(kActorBulletBob, 1800, 36); //14-1800.AUD	You're gonna love this, McCoy. I couldn't believe it when I heard.
					Actor_Says(kActorBulletBob, 590, 31); //14-0590.AUD	U.N. Command figured it out, because the Rep skin held up...
					Actor_Says(kActorBulletBob, 600, 32); //14-0600.AUD	but their eyes melted inside two kilometers from Ground Zero.
					Actor_Clue_Acquire(kActorMcCoy, kClueGogglesReplicantIssue, true, kActorBulletBob);
					Actor_Says(kActorBulletBob, 610, 30);
					Actor_Says(kActorMcCoy, 5050, 16); //00-5050.AUD	Izo.
					Actor_Says(kActorBulletBob, 620, 35);
					Actor_Says(kActorBulletBob, 630, 35);
					if (Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
						Actor_Says(kActorMcCoy, 5055, 11); // 00-5055.AUD	Don't jump to conclusions.
					}
					Actor_Says(kActorBulletBob, 640, 36);
					Actor_Says(kActorBulletBob, 650, 35);
					Actor_Says(kActorBulletBob, 660, 30); //14-0660.AUD	Davy is up there. So is Gaff. Want to see?
					if (Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
						Actor_Says(kActorMcCoy, 5060, 13); //00-5060.AUD	Some other time.
					} else {
						Actor_Says(kActorMcCoy, 2160, 14); //00-2160.AUD	Hell, yeah.
						Actor_Change_Animation_Mode(kActorMcCoy, 23);
						Actor_Change_Animation_Mode(kActorBulletBob, 23);
						Delay(2000);
						Actor_Says(kActorMcCoy, 6975, kAnimationModeTalk); //00-6975.AUD	Interesting.
						Actor_Change_Animation_Mode(kActorMcCoy, 23);
						Actor_Change_Animation_Mode(kActorBulletBob, 23);
						Delay(2000);
					}
				} else {
					Actor_Says(kActorBulletBob, 720, 30); //14-0720.AUD	Ask one of your friends.
					if (Player_Query_Agenda() == kPlayerAgendaPolite) {
						Actor_Says(kActorMcCoy, 7380, 13); // M: Just answer the question please.
					} else if (Player_Query_Agenda() == kPlayerAgendaSurly
					|| Player_Query_Agenda() == kPlayerAgendaErratic) {
						Actor_Says(kActorMcCoy, 5080, 11); //00-5080.AUD	Just answer the question.
					} else {
						Actor_Says(kActorMcCoy, 7805, 13); //00-7805.AUD	Answer the question.
					}
					Delay(2000);
					Actor_Says(kActorMcCoy, 440, 16); //00-0440.AUD	Forget it.
				}
			} else {
				Actor_Says(kActorBulletBob, 560, 37);
				Actor_Says(kActorMcCoy, 5070, 13);
				Actor_Says(kActorBulletBob, 570, 36);
				Actor_Says(kActorBulletBob, 580, 37); // //14-0580.AUD	The humans weren't allowed to get that close to the flash point. 
				Actor_Says(kActorBulletBob, 590, 31); //14-0590.AUD	U.N. Command figured it out, because the Rep skin held up...
				Actor_Says(kActorBulletBob, 600, 32); //14-0600.AUD	but their eyes melted inside two kilometers from Ground Zero.
				Actor_Says(kActorBulletBob, 610, 30);
				Actor_Says(kActorMcCoy, 5050, 16); //00-5050.AUD	Izo.
				Actor_Says(kActorBulletBob, 620, 35);
				Actor_Says(kActorBulletBob, 630, 35);
				Actor_Says(kActorMcCoy, 5055, 11); // 00-5055.AUD	Don't jump to conclusions.
				Actor_Says(kActorBulletBob, 640, 36);
				Actor_Says(kActorBulletBob, 650, 35);
				Actor_Says(kActorBulletBob, 660, 30);
				Actor_Says(kActorMcCoy, 5060, 13); //00-5060.AUD	Some other time.
#if BLADERUNNER_ORIGINAL_BUGS
			Actor_Clue_Acquire(kActorMcCoy, kClueGogglesReplicantIssue, true, kActorMcCoy);  // A bug? Shouldn't the last argument be -1 or kActorBulletBob here?
#else
			Actor_Clue_Acquire(kActorMcCoy, kClueGogglesReplicantIssue, true, kActorBulletBob);
#endif // BLADERUNNER_ORIGINAL_BUGS						
			}
		}
		break;

	case 620: // HOLDEN'S BADGE
		if (_vm->_cutContent) {
			Actor_Face_Actor(kActorBulletBob, kActorMcCoy, true);
			Actor_Face_Actor(kActorMcCoy, kActorBulletBob, true);
		}
		Actor_Says(kActorMcCoy, 4985, 11);
		Actor_Says(kActorBulletBob, 850, 35);
		Actor_Says(kActorMcCoy, 5105, 13);
		Actor_Says(kActorMcCoy, 5110, 11); //00-5110.AUD	You turn it in, the department would owe you a favor.
		Actor_Says(kActorBulletBob, 860, 30); //14-0860.AUD	And what's in it for you?
		if (_vm->_cutContent) {
			if (Player_Query_Agenda() == kPlayerAgendaSurly
			|| Player_Query_Agenda() == kPlayerAgendaErratic) {
				Actor_Says(kActorMcCoy, 5115, 16); //00-5115.AUD	You're a smart guy, Bob. You'll think of something.
				Actor_Says(kActorBulletBob, 870, 31); //14-0870.AUD	I could throw a few chinyen your way…
				Actor_Says(kActorMcCoy, 5120, 15); //00-5120.AUD	That'll work.
			} else {
				Actor_Says(kActorMcCoy, 8526, 16); //00-8526.AUD	Nothing.
				Actor_Says(kActorBulletBob, 1680, 34); //14-1680.AUD	Is that right?
				Actor_Says(kActorMcCoy, 2215, 18); //00-2215.AUD	That’s right.
			}
		} else {
			Actor_Says(kActorMcCoy, 5115, 16); //00-5115.AUD	You're a smart guy, Bob. You'll think of something.
			Actor_Says(kActorBulletBob, 870, 31); //14-0870.AUD	I could throw a few chinyen your way…
			Actor_Says(kActorMcCoy, 5120, 15); //00-5120.AUD	That'll work.
		}
		if (_vm->_cutContent) {
			Actor_Change_Animation_Mode(kActorMcCoy, 23);
			Actor_Change_Animation_Mode(kActorBulletBob, 23);
			Delay(2000);
			Item_Pickup_Spin_Effect_From_Actor(kModelAnimationBadge, kActorBulletBob, 0, 0);
			Actor_Says(kActorMcCoy, 8170, 15); //00-8170.AUD	There you go.
		}
		Actor_Says(kActorBulletBob, 880, 34);
		Actor_Clue_Acquire(kActorBulletBob, kClueHoldensBadge, true, kActorMcCoy);
		// Made it so you actually lose Holdens badge when you give it to Bob.
		Actor_Clue_Lose(kActorMcCoy, kClueHoldensBadge);
		Actor_Modify_Friendliness_To_Other(kActorBulletBob, kActorMcCoy, 8);
		if (_vm->_cutContent) {
			if (Player_Query_Agenda() == kPlayerAgendaSurly
			|| Player_Query_Agenda() == kPlayerAgendaErratic) {
				if (Query_Difficulty_Level() != kGameDifficultyEasy) {
					Global_Variable_Increment(kVariableChinyen, 60);
				}
			} 
		} else {
			if (Query_Difficulty_Level() != kGameDifficultyEasy) {
				Global_Variable_Increment(kVariableChinyen, 60);
			}
		}
		break;

	case 630: // DONE
	//Restored some banter dialogue for Bob. Also made it so he treats you differently based on your friendliness rating.
	if (_vm->_cutContent) {
		Actor_Face_Actor(kActorMcCoy, kActorBulletBob, true);
		Actor_Face_Actor(kActorBulletBob, kActorMcCoy, true);
		Actor_Says(kActorMcCoy, 30, 12); //00-0030.AUD	Anything unusual happening down here?
		// Made it so Bullet Bobs banter dialogue is negative if he is a replicant. If it is act 4 Bob will discover that you are a replicant and if he is
		// one he will be nice to you.
		if (!Game_Flag_Query(kFlagBulletBobIsReplicant)
		&& Actor_Query_Friendliness_To_Other(kActorBulletBob, kActorMcCoy) > 49) {
			Actor_Says(kActorBulletBob, 200, 34); //14-0200.AUD	Nah, it's been quite around here, Ray.
			Actor_Says(kActorMcCoy, 8320, 18); //00-8320.AUD	Really?
			Actor_Says(kActorBulletBob, 1810, 34); //14-1810.AUD	Sorry, man. You know if I heard something you guys would be the first call I'd make.
			if (Player_Query_Agenda() == kPlayerAgendaPolite) {
				Actor_Says(kActorMcCoy, 1315, 12); //00-1315.AUD	Thanks for your time.
			} else {
				Actor_Says(kActorMcCoy, 4595, 14);
			}
		} else {
			Actor_Says(kActorBulletBob, 1820, 34); //14-1820.AUD	You want to make it as a Blade Runner, you ought to do your own investigations.
			Actor_Says(kActorMcCoy, 5075, 18); //00-5075.AUD	Hey, pal.
		}
	} else {
		Actor_Says(kActorMcCoy, 1315, 12); //00-1315.AUD	Thanks for your time.
	}
	break;

	case 1280: // AMMO
	// Added in some extra dialogue for McCoy and Bob.
	if (_vm->_cutContent) {
		Actor_Face_Actor(kActorBulletBob, kActorMcCoy, true);
		Actor_Face_Actor(kActorMcCoy, kActorBulletBob, true);
		if (Game_Flag_Query(kFlagBulletBobIsReplicant)) {
			Actor_Says(kActorMcCoy, 9040, 16); //00-9040.AUD	You got any decent ammo for my piece?
			Actor_Says(kActorBulletBob, 210, 37); //14-0210.AUD	No, I ain't seen anything like that in years.
			if (Player_Query_Agenda() != kPlayerAgendaSurly
			&& Player_Query_Agenda() != kPlayerAgendaErratic) {
				Actor_Says(kActorMcCoy, 8320, 18); //00-8320.AUD	Really?
				Actor_Says(kActorBulletBob, 720, 33); //14-0720.AUD	Ask one of your friends.
			} else {
				Actor_Says(kActorMcCoy, 2485, 19); //00-2485.AUD	I’ve a hard time believing that.
			}
		} else {
			if (Actor_Query_Friendliness_To_Other(kActorBulletBob, kActorMcCoy) > 49) {
				Actor_Says(kActorMcCoy, 4975, 15); //00-4975.AUD	I'm looking for some ammunition.
				Actor_Says(kActorBulletBob, 670, 33); //14-0670.AUD	Nothing but the best. My special blend.
				Actor_Says(kActorBulletBob, 680, 30); //14-0680.AUD	Three times the stopping power of that police-issue crap you're packing.
				Actor_Says(kActorMcCoy, 8320, 18); //00-8320.AUD	Really?
				Actor_Says(kActorBulletBob, 690, 36); //14-0690.AUD	You betcha. Twenty chinyen a clip. You ain't gonna find a better price in this city.
				Game_Flag_Set(kFlagRC04BobTalkAmmo);
				if (Global_Variable_Query(kVariableChinyen) >= 40
				|| Query_Difficulty_Level() == kGameDifficultyEasy
				) {
					Actor_Says(kActorMcCoy, 4940, 23); //00-4940.AUD	Okay, let's have it.
					if (Query_Difficulty_Level() != kGameDifficultyEasy) {
						Global_Variable_Decrement(kVariableChinyen, 40);
					}
					Actor_Change_Animation_Mode(kActorMcCoy, 23);
					Actor_Change_Animation_Mode(kActorBulletBob, 23);
					Delay(800);
					Item_Pickup_Spin_Effect_From_Actor(kModelAnimationAmmoType01, kActorMcCoy, 0, 0);
					Give_McCoy_Ammo(1, 24);
					Delay(800);
				} else {
					Actor_Says(kActorMcCoy, 125, 13); ////00-0125.AUD	I'm a little strapped for cash right now.
				}
			} else {
				Actor_Says(kActorMcCoy, 9040, 16); //00-9040.AUD	You got any decent ammo for my piece?
				Actor_Says(kActorBulletBob, 2080, 30); //14-2080.AUD	You mean the good stuff.
				Actor_Says(kActorBulletBob, 2090, 37); //14-2090.AUD	'Cause I know them police-issue spitballs just don't cut it.
				Actor_Says(kActorMcCoy, 9045, 14); //00-9045.AUD	Not these days.
				Actor_Says(kActorBulletBob, 2100, 32); //14-2100.AUD	Yeah, I know how it is.
				Actor_Says(kActorBulletBob, 2110, 37); //14-2110.AUD	If you want to drop a skin-job, you need a little extra oomph!
				Actor_Says(kActorBulletBob, 2120, 37); //14-2120.AUD	I got a few clips around here somewhere, if you got the chinyen for it.
				Game_Flag_Set(kFlagRC04BobTalkAmmo);
				if (Global_Variable_Query(kVariableChinyen) >= 40
				|| Query_Difficulty_Level() == kGameDifficultyEasy) {
					Actor_Says(kActorMcCoy, 4940, 23); //00-4940.AUD	Okay, let's have it.
					if (Query_Difficulty_Level() != kGameDifficultyEasy) {
						Global_Variable_Decrement(kVariableChinyen, 40);
					}
					Actor_Change_Animation_Mode(kActorMcCoy, 23);
					Actor_Change_Animation_Mode(kActorBulletBob, 23);
					Delay(800);
					Item_Pickup_Spin_Effect_From_Actor(kModelAnimationAmmoType01, kActorMcCoy, 0, 0);
					Give_McCoy_Ammo(1, 24);
					Delay(800);
				} else {
					Actor_Says(kActorMcCoy, 125, 13); //00-0125.AUD	I'm a little strapped for cash right now.
				}
			}
		}
	} else if (!Game_Flag_Query(kFlagRC04BobTalkAmmo)) {
		Actor_Says(kActorMcCoy, 9040, 16); //00-9040.AUD	You got any decent ammo for my piece?
		Actor_Says(kActorBulletBob, 2080, 30);
		Actor_Says(kActorBulletBob, 2090, 37);
		Actor_Says(kActorMcCoy, 9045, 14);
		Actor_Says(kActorBulletBob, 2100, 32);
		Actor_Says(kActorBulletBob, 2110, 37);
		Game_Flag_Set(kFlagRC04BobTalkAmmo);
		Actor_Says(kActorBulletBob, 2120, 31);
		if (Global_Variable_Query(kVariableChinyen) > 40
		 || Query_Difficulty_Level() == kGameDifficultyEasy
		) {
			Actor_Says(kActorMcCoy, 4940, 13);
			if (Query_Difficulty_Level() != kGameDifficultyEasy) {
				Global_Variable_Decrement(kVariableChinyen, 40);
			}
			Item_Pickup_Spin_Effect(kModelAnimationAmmoType01, 405, 192);
			Give_McCoy_Ammo(1, 24);
		} else {
			Actor_Says(kActorMcCoy, 125, 13);
			Actor_Modify_Friendliness_To_Other(kActorBulletBob, kActorMcCoy, -2);
		}
	}
	break;

	case 1310: // VOIGT-KAMPFF
		Actor_Says(kActorMcCoy, 4980, 11);
		if (Actor_Query_Friendliness_To_Other(kActorBulletBob, kActorMcCoy) > 49) {
			Actor_Says(kActorBulletBob, 740, 37); //14-0740.AUD	Test? You mean the Voigt-Kampff?
#if BLADERUNNER_ORIGINAL_BUGS
			Actor_Says(kActorMcCoy, 5085, 16);
#else
			// McCoy is interrupted here
			Actor_Says_With_Pause(kActorMcCoy, 5085, 0.0f, 16); //00-5085.AUD	Yeah, I don't think you're a Rep, but I want to--
#endif // BLADERUNNER_ORIGINAL_BUGS
			Actor_Says(kActorBulletBob, 750, 37);
			Actor_Says(kActorBulletBob, 760, 37);
			Voight_Kampff_Activate(kActorBulletBob, 50);
			Actor_Modify_Friendliness_To_Other(kActorBulletBob, kActorMcCoy, 3);
			Actor_Says(kActorBulletBob, 810, 37);
			Actor_Says(kActorMcCoy, 5025, 13);
			Actor_Says(kActorBulletBob, 820, 32);
			Actor_Says(kActorMcCoy, 5100, 11);
			Actor_Says(kActorBulletBob, 830, 31);
			Actor_Says(kActorBulletBob, 840, 35);
		} else {
			Actor_Says(kActorBulletBob, 770, 36);
			Actor_Says(kActorBulletBob, 780, 36);
#if BLADERUNNER_ORIGINAL_BUGS
			Actor_Says(kActorMcCoy, 5090, 16);
#else
			// McCoy is interrupted here
			Actor_Says_With_Pause(kActorMcCoy, 5090, 0.0f, 16);
#endif // BLADERUNNER_ORIGINAL_BUGS
			Actor_Says(kActorBulletBob, 790, 36);
			Actor_Says(kActorBulletBob, 800, 35);
			Voight_Kampff_Activate(kActorBulletBob, 50);
			Actor_Says(kActorBulletBob, 810, 30);
			Actor_Says(kActorMcCoy, 5025, 13);
			Actor_Says(kActorBulletBob, 820, 31);
			Actor_Says(kActorMcCoy, 5100, 15);
			Actor_Says(kActorBulletBob, 830, 34);
			Actor_Says(kActorBulletBob, 840, 34);
		}
		break;
	}
}

bool SceneScriptRC04::ClickedOnActor(int actorId) {
	if (Player_Query_Combat_Mode()) {
		return false;
	}

	if (actorId == kActorBulletBob) {
		// Made it so you can talk to Bob in act 3.
		if ( Global_Variable_Query(kVariableChapter) >= 2
		 && !Game_Flag_Query(kFlagRC04McCoyShotBob)
		) {
			Loop_Actor_Walk_To_Waypoint(kActorMcCoy, 104, 0, false, false);
			Actor_Face_Actor(kActorMcCoy, kActorBulletBob, true);
			if (_vm->_cutContent) {
				Actor_Face_Actor(kActorBulletBob, kActorMcCoy, true);
			}
			// Made it so if Bob is a replicant he is always mean towards McCoy and knows who he is and if Bob is a human he is nicer to McCoy and doesn't know who he is.
			// It never made any sense that Bob seems to know who you are based on your friendliness with him so this change somewhat rectifies that.
			if (_vm->_cutContent) {
				if (Game_Flag_Query(kFlagRC04Entered) 
				&& !Game_Flag_Query(kFlagRC04BobTalk2)) {
					if (Game_Flag_Query(kFlagBulletBobIsReplicant)) {
						Actor_Says(kActorBulletBob, 40, 30); //14-0040.AUD	I heard of you.
						Actor_Says(kActorMcCoy, 4880, 13); //00-4880.AUD	Is that right?
						Actor_Says(kActorBulletBob, 50, 35); //14-0050.AUD	You ain't done much.
						Actor_Says(kActorMcCoy, 4875, 16); //00-4875.AUD	I just got assigned.
						Actor_Says(kActorBulletBob, 60, 36); //14-0060.AUD	Guys like you get hurt real easy.
						if (Player_Query_Agenda() != kPlayerAgendaSurly
						&& Player_Query_Agenda() != kPlayerAgendaErratic) {
							Actor_Says(kActorMcCoy, 4890, 13); //00-4890.AUD	Meaning what exactly?
							Actor_Says(kActorBulletBob, 70, 33); //14-0070.AUD	It ain't like you're a real Blade Runner. Not like Steele or Gaff.
							if (!Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
								Actor_Says(kActorMcCoy, 4895, 16); //00-4895.AUD	They get hurt sometimes too. It's a dangerous business.
							} else {
								Actor_Says(kActorMcCoy, 5705, 13); //00-5705.AUD	Uh-huh.
							}
						} else {
							Actor_Says(kActorMcCoy, 8440, 18); //00-8440.AUD	Oh, yeah. I'm shaking now.
						}
						if (Actor_Clue_Query(kActorMcCoy, kClueHasanInterview)) {
							Actor_Clue_Acquire(kActorMcCoy, kClueSightingBulletBob, true, kActorBulletBob);
						}
						Actor_Modify_Friendliness_To_Other(kActorBulletBob, kActorMcCoy, -2);
						Game_Flag_Set(kFlagRC04BobTalk2);
					} else {
						Actor_Says(kActorBulletBob, 30, 30); //14-0030.AUD	How come I never heard of you?
						Actor_Says(kActorMcCoy, 4875, 13); //00-4875.AUD	I just got assigned.
						Actor_Says(kActorBulletBob, 80, 31); //14-0080.AUD	Yeah, I'm kind of buddies with Davy Holden. How's he doing?
						Actor_Says(kActorMcCoy, 4900, 15); //00-4900.AUD	Word is he's gonna be okay.
						Actor_Says(kActorBulletBob, 90, 33); //14-0090.AUD	That skin-job must have been pretty damn quick getting by Davy like that.
						Actor_Says(kActorBulletBob, 100, 34); //14-0100.AUD	He's the best in the business.
						if (!Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
							Actor_Says(kActorMcCoy, 4905, 15); //00-4905.AUD	He'll be back on the job soon.
						}
						Actor_Face_Heading(kActorMcCoy, 240, true);
						Actor_Face_Heading(kActorBulletBob, 240, true);
						Delay(1000);
						if (Player_Query_Agenda() == kPlayerAgendaPolite) {
							Actor_Says(kActorMcCoy, 4920, 15); //00-4920.AUD	You got some nice pieces here.
						} else {
							Actor_Says(kActorMcCoy, 8695, 15); //00-8695.AUD	That's an unusual design.
						}	
						Actor_Says(kActorBulletBob, 110, 33); //14-0110.AUD	Take your time, Ray. Enjoy the goods. I got the best in the city right here.
						Actor_Says(kActorBulletBob, 130, 34); //14-0130.AUD	Anything you want and you don't see, just ask.
						if (Player_Query_Agenda() == kPlayerAgendaPolite) {
							Actor_Face_Actor(kActorMcCoy, kActorBulletBob, true);
							Actor_Face_Actor(kActorBulletBob, kActorMcCoy, true);
							Actor_Says(kActorMcCoy, 4910, 15); //00-4910.AUD	Thanks.
							Actor_Modify_Friendliness_To_Other(kActorBulletBob, kActorMcCoy, 2);
						} else if (Player_Query_Agenda() == kPlayerAgendaSurly
						|| Player_Query_Agenda() == kPlayerAgendaErratic) {
							Actor_Says(kActorMcCoy, 8575, 14); // More useless junk.
							Actor_Face_Actor(kActorBulletBob, kActorMcCoy, true);
							Actor_Says(kActorBulletBob, 1680, 34); //14-1680.AUD	Is that right?
							Actor_Face_Actor(kActorMcCoy, kActorBulletBob, true);
							Actor_Says(kActorMcCoy, 5705, 18); //00-5705.AUD	Uh-huh.
							Actor_Modify_Friendliness_To_Other(kActorBulletBob, kActorMcCoy, -2);
							Delay(1000);
						} else {
							Actor_Face_Actor(kActorMcCoy, kActorBulletBob, true);
							Actor_Face_Actor(kActorBulletBob, kActorMcCoy, true);
							Actor_Says(kActorMcCoy, 5705, 18); //00-5705.AUD	Uh-huh.
						}
						Actor_Face_Actor(kActorMcCoy, kActorBulletBob, true);
						Actor_Face_Actor(kActorBulletBob, kActorMcCoy, true);
						if (Actor_Clue_Query(kActorMcCoy, kClueHasanInterview)) {
							Actor_Clue_Acquire(kActorMcCoy, kClueSightingBulletBob, true, kActorBulletBob);
						}
						Game_Flag_Set(kFlagRC04BobTalk2);
						Actor_Says(kActorBulletBob, 1870, 30); //14-1870.AUD	Hey, check out the man's database.
						Actor_Says(kActorBulletBob, 1880, 30);
						Actor_Says(kActorMcCoy, 8960, 13);
						Actor_Says(kActorBulletBob, 1890, 36);
						Actor_Says(kActorBulletBob, 1900, 35);
						Actor_Says(kActorMcCoy, 8965, 16);
						if (Actor_Query_Friendliness_To_Other(kActorBulletBob, kActorMcCoy) > 49) {
							Actor_Says(kActorBulletBob, 1920, 36); //14-1920.AUD	Hey, Ray, relax! I'm your pal, ain't I?
							Actor_Says(kActorBulletBob, 1930, 33); //14-1930.AUD	You don't have to step soft around me.
							Actor_Says(kActorMcCoy, 4950, 16); //00-4950.AUD	Frankly I don't see you as the comforting type.
							Delay(500);
							Actor_Says(kActorBulletBob, 1400, 34); //14-1400.AUD	Hmm yeah, sure.
							Delay(1000);
						}
						Actor_Says(kActorBulletBob, 1940, 36); //14-1940.AUD	The department's been infiltrated, right?
						Actor_Says(kActorBulletBob, 1950, 30); //14-1950.AUD	That's the only way Davy could have been taken out like he was.
						Actor_Says(kActorMcCoy, 8970, 13); //00-8970.AUD	Holden is good. No question.
						Actor_Says(kActorBulletBob, 1960, 33); //14-1960.AUD	When you hook into the mainframe you always give them everything.
						Actor_Says(kActorBulletBob, 1970, 30);
						Actor_Says(kActorBulletBob, 1980, 36);
						Actor_Clue_Acquire(kActorMcCoy, kClueBobInterview2, true, kActorBulletBob);
						Delay(1000);
						Actor_Says(kActorMcCoy, 3940, 13); //00-3940.AUD	How much? 
						Actor_Says(kActorBulletBob, 1990, 33); //14-1990.AUD	100 chinyen.
						Actor_Says(kActorBulletBob, 2000, 30); //14-2000.AUD	You'd spend that much on a day's worth of mouldy soya.
						Delay(1000);
						Actor_Says(kActorBulletBob, 2010, 35);
						if (Player_Query_Agenda() == kPlayerAgendaPolite) {
							Actor_Says(kActorMcCoy, 3390, 14); //00-3390.AUD	Not interested.
							if (Actor_Query_Friendliness_To_Other(kActorBulletBob, kActorMcCoy) > 49) {
								Actor_Says(kActorBulletBob, 2040, 30);
								Actor_Says(kActorMcCoy, 8985, 15);
								Actor_Says(kActorBulletBob, 2050, 33);
							}
						} else {
							if (Global_Variable_Query(kVariableChinyen) >= 100
							|| Query_Difficulty_Level() == kGameDifficultyEasy
							) {
								Actor_Says(kActorMcCoy, 8975, 16); //00-8975.AUD	Sounds like a plan. Set it up.
								Actor_Says(kActorBulletBob, 2020, 30); //14-2020.AUD	Hand it over.
								if (Query_Difficulty_Level() != kGameDifficultyEasy) {
									Global_Variable_Decrement(kVariableChinyen, 100);
								}
								Actor_Change_Animation_Mode(kActorMcCoy, 23);
								Actor_Change_Animation_Mode(kActorBulletBob, 23);
								Delay(3000);
								Actor_Change_Animation_Mode(kActorMcCoy, 23);
								Actor_Change_Animation_Mode(kActorBulletBob, 23);
								Delay(800);
								Item_Pickup_Spin_Effect_From_Actor(kModelAnimationDNADataDisc, kActorMcCoy, 0, 0);
								if (Actor_Query_Friendliness_To_Other(kActorBulletBob, kActorMcCoy) > 49) { 
									Actor_Says(kActorBulletBob, 2030, 30); //14-2030.AUD	There you go better than new.
								}
								Game_Flag_Set(kFlagKIAPrivacyAddon);
							} else {
								Actor_Says(kActorMcCoy, 8980, 16);
								if (Actor_Query_Friendliness_To_Other(kActorBulletBob, kActorMcCoy) > 49) {
									Actor_Says(kActorBulletBob, 2040, 30);
									Actor_Says(kActorMcCoy, 8985, 15);
									Actor_Says(kActorBulletBob, 2050, 33);
								}
							}
						}
					}	
				} else if (Actor_Clue_Query(kActorMcCoy, kClueLabShellCasings)
				||  Actor_Clue_Query(kActorMcCoy, kClueShellCasings)
				||  Actor_Clue_Query(kActorMcCoy, kClueRadiationGoggles)
				||  Actor_Clue_Query(kActorMcCoy, kClueHoldensBadge)
				||  Actor_Clue_Query(kActorMcCoy, kClueHasanInterview)
				|| !Game_Flag_Query(kFlagRC04BobTalkAmmo)) {	
					dialogueWithBulletBob();
				} else {
					Actor_Face_Actor(kActorBulletBob, kActorMcCoy, true);
					Actor_Says(kActorMcCoy, 30, 12); //00-0030.AUD	Anything unusual happening down here?
					// Made it so Bullet Bobs banter dialogue is negative if he is a replicant. If it is act 4 Bob will discover that you are a replicant and if he is
					// one he will be nice to you.
					if (!Game_Flag_Query(kFlagBulletBobIsReplicant)
					&& Actor_Query_Friendliness_To_Other(kActorBulletBob, kActorMcCoy) > 49) {
						Actor_Says(kActorBulletBob, 200, 34); //14-0200.AUD	Nah, it's been quite around here, Ray.
						Actor_Says(kActorMcCoy, 8320, 18); //00-8320.AUD	Really?
						Actor_Says(kActorBulletBob, 1810, 34); //14-1810.AUD	Sorry, man. You know if I heard something you guys would be the first call I'd make.
						if (Player_Query_Agenda() == kPlayerAgendaPolite) {
							Actor_Says(kActorMcCoy, 1315, 12); //00-1315.AUD	Thanks for your time.
						} else {
							Actor_Says(kActorMcCoy, 4595, 14);
						}
					} else {
						Actor_Says(kActorBulletBob, 1820, 34); //14-1820.AUD	You want to make it as a Blade Runner, you ought to do your own investigations.
						Actor_Says(kActorMcCoy, 5075, 18); //00-5075.AUD	Hey, pal.
					}
				}
			} else if ( Game_Flag_Query(kFlagRC04Entered)
			 && !Game_Flag_Query(kFlagRC04BobTalk2)
			 &&  Actor_Query_Friendliness_To_Other(kActorBulletBob, kActorMcCoy) > 45) {
				Actor_Says(kActorBulletBob, 30, 30);
				Actor_Says(kActorMcCoy, 4875, 13);
				Actor_Says(kActorBulletBob, 80, 31);
				Actor_Says(kActorMcCoy, 4900, 15);
				Actor_Says(kActorBulletBob, 90, 33);
				Actor_Says(kActorBulletBob, 100, 34);
				Actor_Says(kActorMcCoy, 4905, 15);
				Game_Flag_Set(kFlagRC04BobTalk2);
			} else if ( Game_Flag_Query(kFlagRC04Entered)
					&& !Game_Flag_Query(kFlagRC04BobTalk1)
					&& Actor_Query_Friendliness_To_Other(kActorBulletBob, kActorMcCoy) < 45
					&& (!_vm->_cutContent)
			) {
				Actor_Says(kActorBulletBob, 40, 30);
				Actor_Says(kActorMcCoy, 4880, 13);
				Actor_Says(kActorBulletBob, 50, 35);
				Actor_Says(kActorMcCoy, 4875, 16);
				Actor_Says(kActorBulletBob, 60, 36);
				Actor_Says(kActorMcCoy, 4890, 13);
				Actor_Says(kActorBulletBob, 70, 33);
				Actor_Says(kActorMcCoy, 4895, 16);
				Actor_Modify_Friendliness_To_Other(kActorBulletBob, kActorMcCoy, -5);
				Game_Flag_Set(kFlagRC04BobTalk1);
		
			} else if ( Actor_Query_Friendliness_To_Other(kActorBulletBob, kActorMcCoy) > 51
				&& !Game_Flag_Query(kFlagRC04BobTalk3)
			) {
				Actor_Says(kActorBulletBob, 1870, 30);
				Actor_Says(kActorBulletBob, 1880, 30);
				Actor_Says(kActorMcCoy, 8960, 13);
				Actor_Says(kActorBulletBob, 1890, 36);
				Actor_Says(kActorBulletBob, 1900, 35);
				Actor_Says(kActorMcCoy, 8965, 16);
				Actor_Says(kActorBulletBob, 1920, 36); //14-1920.AUD	Hey, Ray, relax! I'm your pal, ain't I?
				Actor_Says(kActorBulletBob, 1930, 33); //14-1930.AUD	You don't have to step soft around me.
				Actor_Says(kActorBulletBob, 1940, 36); //14-1940.AUD	The department's been infiltrated, right?
				Actor_Says(kActorBulletBob, 1950, 30); //14-1950.AUD	That's the only way Davy could have been taken out like he was.
				Actor_Says(kActorMcCoy, 8970, 13); //00-8970.AUD	Holden is good. No question.
				Actor_Says(kActorBulletBob, 1960, 33); //14-1960.AUD	When you hook into the mainframe you always give them everything.
				Actor_Says(kActorBulletBob, 1970, 30);
				Actor_Says(kActorBulletBob, 1980, 36);
				Delay(1000);
				Actor_Says(kActorBulletBob, 2010, 35);
			    if (Global_Variable_Query(kVariableChinyen) >= 50
				|| Query_Difficulty_Level() == kGameDifficultyEasy) {
					Actor_Says(kActorMcCoy, 8975, 16); //00-8975.AUD	Sounds like a plan. Set it up.
					if (Query_Difficulty_Level() != kGameDifficultyEasy) {
						Global_Variable_Decrement(kVariableChinyen, 50);
					}
					Delay(3000);
					Item_Pickup_Spin_Effect(kModelAnimationDNADataDisc, 405, 192);
					Actor_Says(kActorBulletBob, 2030, 30);
					Game_Flag_Set(kFlagKIAPrivacyAddon);
				} else {
					Actor_Says(kActorMcCoy, 8980, 16);
					Actor_Says(kActorBulletBob, 2040, 30);
					Actor_Says(kActorMcCoy, 8985, 15);
					Actor_Says(kActorBulletBob, 2050, 33);
				}
				Game_Flag_Set(kFlagRC04BobTalk3);

			 } else if ( Actor_Clue_Query(kActorMcCoy, kClueLabShellCasings)
			        ||  Actor_Clue_Query(kActorMcCoy, kClueShellCasings)
			        ||  Actor_Clue_Query(kActorMcCoy, kClueRadiationGoggles)
			        ||  Actor_Clue_Query(kActorMcCoy, kClueHoldensBadge)
			        ||  Actor_Clue_Query(kActorMcCoy, kClueHasanInterview)
			        || !Game_Flag_Query(kFlagRC04BobTalkAmmo)
			) {
				dialogueWithBulletBob();
			} else {
				Actor_Says(kActorBulletBob, 1820, 30);
			}
			return true;
		}

		if (Game_Flag_Query(kFlagRC04McCoyShotBob)) {
			Actor_Face_Actor(kActorMcCoy, kActorBulletBob, true);
			// Made it so Bob being a replicant changes McCoys response when you click on a dead Bob.
			if (Actor_Clue_Query(kActorMcCoy, kClueVKBobGorskyReplicant)
			|| Game_Flag_Query(kFlagBulletBobIsReplicant)) {
				Actor_Says(kActorMcCoy, 8590, -1); //00-8590.AUD	Not the talkative type.
			} else {
				Actor_Voice_Over(2100, kActorVoiceOver);
				Actor_Voice_Over(2110, kActorVoiceOver);
			}
			return true;
		}
	}
	return false;
}

bool SceneScriptRC04::ClickedOnItem(int itemId, bool a2) {
	return false;
}

bool SceneScriptRC04::ClickedOnExit(int exitId) {
	if (exitId == 0) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, 45.0f, 0.15f, 68.0f, 0, true, false, false)) {
			if (_vm->_cutContent) {
				if (Actor_Clue_Query(kActorMcCoy, kClueVKBobGorskyReplicant)
				&& Game_Flag_Query(kFlagBulletBobIsReplicant)
				&& !Game_Flag_Query(kFlagBulletBobWarned)
				&& Actor_Query_Goal_Number(kActorBulletBob) < kGoalBulletBobGone) {
					Actor_Face_Actor(kActorMcCoy, kActorBulletBob, true);
					Actor_Face_Actor(kActorBulletBob, kActorMcCoy, true);
					Actor_Says(kActorMcCoy, 3690, 18); //00-3690.AUD	Look. I wanna warn you. There’s a woman looking for you and your friends.
					Actor_Says(kActorBulletBob, 1680, 34); //14-1680.AUD	Is that right?
					Actor_Says(kActorMcCoy, 3700, 13); // If I found you, so will she.
					Delay(500);
					Actor_Says(kActorMcCoy, 6450, 18); //00-6450.AUD	It’s too dangerous for you around here. You gotta hide. Go underground.
					Delay(1000);
					Actor_Says(kActorBulletBob, 880, 34); //14-0880.AUD	They really ought to pay you guys better.
					if (Player_Query_Agenda() == kPlayerAgendaPolite) {
						Actor_Says(kActorMcCoy, 2860, 13); // YouTakeCareOfYourself
					}
					Actor_Modify_Friendliness_To_Other(kActorSteele, kActorMcCoy, -2);
					Actor_Modify_Friendliness_To_Other(kActorGuzza, kActorMcCoy, -2);
					Actor_Modify_Friendliness_To_Other(kActorClovis, kActorMcCoy, 2);	
					Actor_Set_Targetable(kActorBulletBob, false);
					Game_Flag_Set(kFlagBulletBobWarned);
					Game_Flag_Set(kFlagMcCoyIsHelpingReplicants);
				}
			}
			Game_Flag_Set(kFlagRC04toRC03);
			Set_Enter(kSetRC03, kSceneRC03);
		}
		return true;
	}
	return false;
}

bool SceneScriptRC04::ClickedOn2DRegion(int region) {
	// Added in the option to buy the bulletproof vest. The price of the vest will be based on whether or not Bob likes you.
	if (_vm->_cutContent) {
		if (!Game_Flag_Query(kFlagMcCoyHasVest)) {
			Actor_Face_Heading(kActorMcCoy, 240, true);
			Actor_Face_Heading(kActorBulletBob, 240, true);
			Actor_Says(kActorMcCoy, 4925, 11); //00-4925.AUD	That a bulletproof vest?
			Actor_Says(kActorBulletBob, 150, 35); //14-0150.AUD	It'd stop a slug dead cold. You wouldn't even feel it.
			Actor_Face_Actor(kActorMcCoy, kActorBulletBob, true);
			Actor_Face_Actor(kActorBulletBob, kActorMcCoy, true);
			Actor_Says(kActorMcCoy, 4930, 13); //00-4930.AUD	How much?
			if (Game_Flag_Query(kFlagBulletBobIsReplicant)) {
				Actor_Says(kActorBulletBob, 2100, 31); //14-2100.AUD	Yeah, I know how it is.
				Actor_Says(kActorBulletBob, 60, 32); //14-0060.AUD	Guys like you get hurt real easy.
				Actor_Says(kActorBulletBob, 70, 35); //14-0070.AUD	It ain't like you're a real Blade Runner. Not like Steele or Gaff.
				Actor_Says(kActorMcCoy, 8445, 14); //00-8445.AUD	Cough it up!
				Delay(2000);
				Actor_Says(kActorMcCoy, 440, 16); //00-0440.AUD	Forget it.
				Actor_Modify_Friendliness_To_Other(kActorRunciter, kActorMcCoy, -2);
			} else {
				if (Actor_Query_Friendliness_To_Other(kActorBulletBob, kActorMcCoy) > 49) {
					Actor_Says(kActorBulletBob, 160, 33); //14-0160.AUD	200 chinyen.				
					if (Global_Variable_Query(kVariableChinyen) >= 200
					|| Query_Difficulty_Level() == kGameDifficultyEasy
					) {
						Actor_Says(kActorMcCoy, 7000, 13); //00-7000.AUD	Yeah, okay. I'll take it.
						Loop_Actor_Walk_To_Waypoint(kActorMcCoy, 104, 0, false, false);
						Actor_Face_Actor(kActorMcCoy, kActorBulletBob, true);
						Actor_Face_Actor(kActorBulletBob, kActorMcCoy, true);
						Actor_Change_Animation_Mode(kActorMcCoy, 23);
						Actor_Change_Animation_Mode(kActorBulletBob, 23);
						Delay(2000);
						Loop_Actor_Walk_To_XYZ(kActorMcCoy, 77.30, 0.27, -77.67, 0, false, false, true);
						Actor_Change_Animation_Mode(kActorMcCoy, 23);
						Delay(2000);
						Actor_Set_Health(kActorMcCoy, 90, 90);
						Game_Flag_Set(kFlagMcCoyHasVest);
						Scene_2D_Region_Remove(0);
						if (Query_Difficulty_Level() != kGameDifficultyEasy) {
							Global_Variable_Decrement(kVariableChinyen, 200);
						}
					} else {
						Actor_Says(kActorMcCoy, 4945, 16); //00-4945.AUD	I think I'll pass.
						Actor_Says(kActorBulletBob, 190, 30); //14-0190.AUD	You better not come crying to me when you catch a bullet.		
					}
				} else {
					Actor_Says(kActorBulletBob, 170, 33); //14-0170.AUD	300 chinyen.
					if (Global_Variable_Query(kVariableChinyen) >= 300
					|| Query_Difficulty_Level() == kGameDifficultyEasy
					) {
						Actor_Says(kActorMcCoy, 7000, 13); //00-7000.AUD	Yeah, okay. I'll take it.
						Loop_Actor_Walk_To_Waypoint(kActorMcCoy, 104, 0, false, false);
						Actor_Change_Animation_Mode(kActorMcCoy, 23);
						Actor_Change_Animation_Mode(kActorBulletBob, 23);
						Delay(2000);
						Loop_Actor_Walk_To_XYZ(kActorMcCoy, 77.30, 0.27, -77.67, 0, false, false, true);
						Actor_Change_Animation_Mode(kActorMcCoy, 23);
						Delay(2000);
						Actor_Set_Health(kActorMcCoy, 90, 90);
						Game_Flag_Set(kFlagMcCoyHasVest);
						Scene_2D_Region_Remove(0);
						if (Query_Difficulty_Level() != kGameDifficultyEasy) {
							Global_Variable_Decrement(kVariableChinyen, 300);
						}
					} else {
						Actor_Says(kActorMcCoy, 4935, 13); //00-4935.AUD	That's a little steep.
						Actor_Says(kActorBulletBob, 180, 35); //14-0180.AUD	Retire a few skin-jobs and maybe you'll get a discount.
					}
				}
			}
		}	
			return true;
	}
	return false;
}

void SceneScriptRC04::SceneFrameAdvanced(int frame) {
}

void SceneScriptRC04::ActorChangedGoal(int actorId, int newGoal, int oldGoal, bool currentSet) {
}

void SceneScriptRC04::PlayerWalkedIn() {
	// Made it so McCoy has his gun holstered when he enters the shop.
	if (_vm->_cutContent) {
		Player_Set_Combat_Mode(false);
		if ( Global_Variable_Query(kVariableChapter) <= 3) {
			Loop_Actor_Walk_To_Waypoint(kActorMcCoy, 103, 0, false, false);
		} else {
			Actor_Set_At_XYZ(kActorMcCoy,  33.55, 0.32, 9.41, 0);
		}
	} else {
		Loop_Actor_Walk_To_Waypoint(kActorMcCoy, 103, 0, false, false);
	}
	if ( Global_Variable_Query(kVariableChapter) >= 2
	 && !Game_Flag_Query(kFlagRC04Entered)
	 && !Player_Query_Combat_Mode()
	) {
		if (_vm->_cutContent
		&& !Game_Flag_Query(kFlagBulletBobIsReplicant)
		&& Game_Flag_Query(kFlagIzoIsReplicant)) { 
			Actor_Face_Actor(kActorMcCoy, kActorBulletBob, true);
			Delay(1000);
			Actor_Says(kActorMcCoy, 755, 18);
			Delay(2000);
			Actor_Says(kActorMcCoy, 3970, 14);
			Delay(2000);
			Player_Loses_Control();
			Loop_Actor_Walk_To_Waypoint(kActorMcCoy, 104, 0, false, false);
			Player_Gains_Control();
			Actor_Face_Actor(kActorMcCoy, kActorBulletBob, true);
			Actor_Change_Animation_Mode(kActorMcCoy, 23);						
			Delay(2000);
			Actor_Says(kActorMcCoy, 5290, kAnimationModeTalk);
			Music_Play(kMusicBRBlues, 52, 0, 2, -1, kMusicLoopPlayOnce, 1);
			Delay(1000);
			Actor_Says(kActorMcCoy, 7125, -1); //00-7125.AUD	He was murdered. Probably by a Replicant.
			Actor_Clue_Acquire(kActorMcCoy, kClueBobShotInColdBlood, true, -1);
			CDB_Set_Crime(kClueBobShotInColdBlood, kCrimeBobMurder);
			Delay(1000);
			Actor_Change_Animation_Mode(kActorMcCoy, 23);						
			Delay(800);
			Item_Pickup_Spin_Effect_From_Actor(kModelAnimationAmmoType00, kActorBulletBob, 0, 0);
			Delay(800);
			Actor_Face_Heading(kActorMcCoy, 240, true);
			Actor_Voice_Over(4190, kActorVoiceOver); //99-4190.AUD	Where have I seen that before?	
			Delay(2000);
			Player_Loses_Control();
			Loop_Actor_Walk_To_XYZ(kActorMcCoy, 45.0f, 0.15f, 68.0f, 0, true, false, false);
			Player_Gains_Control();
			if (Player_Query_Agenda() == kPlayerAgendaPolite) {
				Actor_Face_Actor(kActorMcCoy, kActorBulletBob, true);
				Delay(2000);
				Actor_Says(kActorMcCoy, 2305, 13); //00-2305.AUD	I’m sorry.
				Delay(2000);
			}
			Actor_Voice_Over(2420, kActorVoiceOver); //99-2420.AUD	I got the cold cut boys down here and they performed a bone-marrow on him.
			Actor_Set_Goal_Number(kActorBulletBob, kGoalBulletBobDead);
			Delay(1000);
			Music_Stop(1u);
			Game_Flag_Set(kFlagRC04toRC03);
			Set_Enter(kSetRC03, kSceneRC03);	
		} else {
			// Made it so Bob actually faces you when he talks to you. I mean how is he supposed to know that McCoy has a 45 blaster under his coat unless he is looking at him? 
			if (_vm->_cutContent) {
				Actor_Face_Actor(kActorBulletBob, kActorMcCoy, true);
				Actor_Face_Actor(kActorMcCoy, kActorBulletBob, true);
			}
			Actor_Says(kActorBulletBob, 0, 31);
			Loop_Actor_Walk_To_Waypoint(kActorMcCoy, 104, 0, false, false);
			// Made it so Bob continually faces you.
			if (_vm->_cutContent) {
				Actor_Face_Actor(kActorBulletBob, kActorMcCoy, true);
			}
			Actor_Face_Actor(kActorMcCoy, kActorBulletBob, true);
			if (_vm->_cutContent) {
				if (Player_Query_Agenda() == kPlayerAgendaPolite) {
					Actor_Says(kActorMcCoy, 4865, 13);
					Actor_Says(kActorBulletBob, 10, 32);
				} 
			} else {
				Actor_Says(kActorMcCoy, 4865, 13);
				Actor_Says(kActorBulletBob, 10, 32);
			}
			if (_vm->_cutContent) {
				Actor_Says(kActorMcCoy, 4870, 23);
			} else {
				Actor_Says(kActorMcCoy, 4870, 16);
			}
			Actor_Says(kActorBulletBob, 20, 31);
			if (_vm->_cutContent) {
				if (!Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
					Actor_Says(kActorMcCoy, 1625, 15); //00-1625.AUD	Yes.
					Delay(500);
				} else {
					Delay(1000);
				}
				Actor_Says(kActorMcCoy, 7395, 14); //00-7395.AUD	What's your name?
				Actor_Says(kActorBulletBob, 930, 31); //14-0930.AUD	Bob Gorsky.
			}
			Game_Flag_Set(kFlagRC04Entered);
		}
		return; //true;
	}

	if ( Global_Variable_Query(kVariableChapter) == 4
	 && !Game_Flag_Query(kFlagRC04McCoyShotBob)
	) {
		// Code for the scene between McCoy and Leary at Bullet Bobs shop. After Leary is shot by Bobs tracking gun McCoy shoots it several time and disables it.
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagBulletBobIsReplicant)) {
				if (!Game_Flag_Query(kFlagOfficerLearyKilledByBob)
				&& Actor_Query_Goal_Number(kActorBulletBob) < kGoalBulletBobGone
				) {
					Actor_Set_Goal_Number(kActorOfficerLeary, kGoalOfficerLearyAtBulletBobs);
					Actor_Set_At_XYZ(kActorBulletBob, -85.71f, -41.29f, 65.11f, 240);
					AI_Movement_Track_Flush(kActorOfficerLeary);
					Actor_Put_In_Set(kActorOfficerLeary, kSetRC04);
					Actor_Set_At_XYZ(kActorOfficerLeary, 69.31, 0.25, -109.61, 12);
					Actor_Face_Actor(kActorMcCoy, kActorOfficerLeary, true);
					if (Actor_Query_Friendliness_To_Other(kActorOfficerLeary, kActorMcCoy) < 50) {
						Actor_Change_Animation_Mode(kActorOfficerLeary, kAnimationModeCombatIdle);
					}
					Music_Play(kMusicBatl226M, 50, 0, 2, -1, kMusicLoopPlayOnce, 0);
					Actor_Face_Actor(kActorOfficerLeary, kActorMcCoy, true);
					Delay(1000);
					Actor_Says(kActorMcCoy, 170, 15); //00-0170.AUD	Damn.
					Delay(1000);
					Actor_Says(kActorMcCoy, 3005, 13); //00-3005.AUD	What are you gonna do? Take me in?
					if (Actor_Query_Friendliness_To_Other(kActorOfficerLeary, kActorMcCoy) < 50) {
						Sound_Play(kSfxSHOTCOK1, 100, 0, 100, 50);
						Delay(500);
						Actor_Says(kActorMcCoy, 2380, 14); //00-2380.AUD	Wait a minute!
					}
					Delay(500);
					Sound_Play(kSfxGUNAIM1, 100, 0, 0, 50);
					Delay(1000);
					Actor_Says(kActorMcCoy, 2980, 19); //00-2980.AUD	What the hell is that?
					Sound_Play(kSfxGUNAIM1, 100, 0, 0, 50);
					Actor_Face_Actor(kActorMcCoy, kActorGenwalkerA, true);
					Delay(1500);	
					Actor_Face_Actor(kActorMcCoy, kActorOfficerLeary, true);									
					Actor_Says(kActorMcCoy, 2180, 14);	// 00-2180.AUD	Look out!
					Actor_Says(kActorOfficerLeary, 20, 4); //23-0020.AUD	Find something? 
					Delay(500);
					Actor_Face_Actor(kActorMcCoy, kActorGenwalkerA, true);
					Actor_Says(kActorMcCoy, 2185, 14);	//00-2185.AUD	There’s a trigger there. See it? And what’s that blinking? 
					Actor_Face_Actor(kActorMcCoy, kActorOfficerLeary, true);
					Actor_Face_Actor(kActorOfficerLeary, kActorMcCoy, true);
					Delay(1000);
					if (Actor_Query_Friendliness_To_Other(kActorOfficerLeary, kActorMcCoy) < 50) {
						Actor_Says(kActorOfficerLeary, 170, 4); //23-0170.AUD	You ain't talking to some flunky, McCoy.	
						Loop_Actor_Walk_To_XYZ(kActorOfficerLeary, 21.82, 0.25, -91.65, 0, true, false, false);
						Actor_Face_Actor(kActorMcCoy, kActorOfficerLeary, true);
						Actor_Face_Actor(kActorOfficerLeary, kActorMcCoy, true);
						Music_Stop(3u);
						Actor_Says(kActorMcCoy, 1800, 15); //00-1800.AUD	No, wait!
						Sound_Play(kSfxBARSFX2, 100, 0, 0, 50);
						Delay(1500);
						Sound_Play(kSfxLGCAL3, 100, 0, 0, 50);
						Music_Play(kMusicMoraji, 71, 0, 0, -1, kMusicLoopPlayOnce, 2);
						Actor_Change_Animation_Mode(kActorOfficerLeary, 48);
						Actor_Change_Animation_Mode(kActorMcCoy, 21);
						Delay(1200);
						Player_Set_Combat_Mode(true);
						Actor_Change_Animation_Mode(kActorMcCoy, 6);
						Sound_Play(kSfxGUNH1A, 100, 0, 0, 50);
						Player_Loses_Control();
						Delay(1000);
						Loop_Actor_Walk_To_Actor(kActorMcCoy, kActorOfficerLeary, 36, false, true);
						Actor_Face_Actor(kActorMcCoy, kActorGenwalkerA, true);
						Actor_Change_Animation_Mode(kActorMcCoy, 6);
						Sound_Play(kSfxGUNH1A, 100, 0, 0, 50);
						Delay(1000);
						Sound_Play(kSfxBARSFX2, 100, 0, 0, 50);
						Loop_Actor_Walk_To_XYZ(kActorMcCoy, 76.40, 0.26, -97.51, 0, true, false, false);
						Actor_Face_Actor(kActorMcCoy, kActorGenwalkerA, true);
						Actor_Change_Animation_Mode(kActorMcCoy, 6);
						Sound_Play(kSfxGUNH1A, 100, 0, 0, 50);
						Sound_Play(kSfxSERVOD1, 100, 0, 0, 50);
						Game_Flag_Set(kFlagOfficerLearyBobMeeting);
						Game_Flag_Set(kFlagOfficerLearyKilledByBob);
						Delay(2000);
						Music_Stop(3u);
						Player_Set_Combat_Mode(false);
						Actor_Face_Actor(kActorMcCoy, kActorOfficerLeary, true);
						Delay(1000);
						Music_Play(kMusicBRBlues, 52, 0, 2, -1, kMusicLoopPlayOnce, 1);
						Actor_Says(kActorMcCoy, 2235, 11); //00-2235.AUD	How could they?
						Loop_Actor_Walk_To_XYZ(kActorMcCoy, 27.12, 0.29, -47.35, 0, false, false, true);
						if (Player_Query_Agenda() == kPlayerAgendaPolite) {
							Actor_Face_Actor(kActorMcCoy, kActorOfficerLeary, true);
							Delay(1000);
							Actor_Says(kActorMcCoy, 2390, 14); //00-2390.AUD	Oh, God. No.
							Delay(2000);
							Actor_Says(kActorMcCoy, 2305, 19); //00-2305.AUD	I’m sorry.
							Delay(1000);
						} else {
							Actor_Face_Actor(kActorMcCoy, kActorOfficerLeary, true);
							Delay(1000);
							Actor_Says(kActorMcCoy, 170, -1); //00-0170.AUD	Damn.
						}
						Player_Gains_Control();
						Scene_2D_Region_Remove(0);
					} else { 
						if (Actor_Query_Intelligence(kActorOfficerLeary) == 60) {
							Actor_Face_Actor(kActorMcCoy, kActorGenwalkerA, true);
							Actor_Face_Actor(kActorOfficerLeary, kActorGenwalkerA, true);
							Delay(1000);
							Actor_Change_Animation_Mode(kActorOfficerLeary, kAnimationModeCombatIdle);
							Player_Set_Combat_Mode(true);
							Delay(1500);
							Actor_Says(kActorMcCoy, 1805, -1); //00-1805.AUD	Now!
							Actor_Change_Animation_Mode(kActorOfficerLeary, kAnimationModeCombatAttack);
							Actor_Change_Animation_Mode(kActorMcCoy, 6);
							Sound_Play(kSfxGUNH1A, 100, 0, 0, 50);
							Sound_Play(kSfxSERVOD1, 100, 0, 0, 50);
							Music_Stop(3u);
							Delay(2000);
							Player_Set_Combat_Mode(false);
							Delay(1500);
							Actor_Says(kActorMcCoy, 690, 14); //00-0690.AUD	Gotcha.
							Actor_Face_Actor(kActorMcCoy, kActorOfficerLeary, true);
							Actor_Face_Actor(kActorOfficerLeary, kActorMcCoy, true);
							Delay(2000);
							Actor_Says(kActorMcCoy, 2860, 13); // YouTakeCareOfYourself
							Delay(1000);
							Player_Loses_Control();
							Loop_Actor_Walk_To_XYZ(kActorMcCoy, 45.0f, 0.15f, 68.0f, 0, true, false, false);
							Player_Gains_Control();
							Game_Flag_Set(kFlagOfficerLearyBobMeeting);
							Game_Flag_Set(kFlagRC04toRC03);
							Set_Enter(kSetRC03, kSceneRC03);	
						} else if (Actor_Query_Intelligence(kActorOfficerLeary) == 40) {
							Actor_Says(kActorOfficerLeary, 10, 0); //23-0010.AUD	I'm on it.
							Loop_Actor_Walk_To_XYZ(kActorOfficerLeary, 21.82, 0.25, -91.65, 0, true, false, false);
							Actor_Face_Actor(kActorMcCoy, kActorOfficerLeary, true);
							Actor_Face_Actor(kActorOfficerLeary, kActorMcCoy, true);
							Music_Stop(3u);
							Actor_Says(kActorMcCoy, 1800, 15); //00-1800.AUD	No, wait!
							Sound_Play(kSfxBARSFX2, 100, 0, 0, 50);
							Delay(1500);
							Sound_Play(kSfxLGCAL3, 100, 0, 0, 50);
							Music_Play(kMusicMoraji, 71, 0, 0, -1, kMusicLoopPlayOnce, 2);
							Actor_Change_Animation_Mode(kActorOfficerLeary, 48);
							Actor_Change_Animation_Mode(kActorMcCoy, 21);
							Delay(1200);
							Player_Set_Combat_Mode(true);
							Actor_Change_Animation_Mode(kActorMcCoy, 6);
							Sound_Play(kSfxGUNH1A, 100, 0, 0, 50);
							Player_Loses_Control();
							Delay(1000);
							Loop_Actor_Walk_To_Actor(kActorMcCoy, kActorOfficerLeary, 36, false, true);
							Actor_Face_Actor(kActorMcCoy, kActorGenwalkerA, true);
							Actor_Change_Animation_Mode(kActorMcCoy, 6);
							Sound_Play(kSfxGUNH1A, 100, 0, 0, 50);
							Delay(1000);
							Sound_Play(kSfxBARSFX2, 100, 0, 0, 50);
							Loop_Actor_Walk_To_XYZ(kActorMcCoy, 76.40, 0.26, -97.51, 0, true, false, false);
							Actor_Face_Actor(kActorMcCoy, kActorGenwalkerA, true);
							Actor_Change_Animation_Mode(kActorMcCoy, 6);
							Sound_Play(kSfxGUNH1A, 100, 0, 0, 50);
							Sound_Play(kSfxSERVOD1, 100, 0, 0, 50);
							Game_Flag_Set(kFlagOfficerLearyBobMeeting);
							Game_Flag_Set(kFlagOfficerLearyKilledByBob);
							Delay(2000);
							Music_Stop(3u);
							Player_Set_Combat_Mode(false);
							Actor_Face_Actor(kActorMcCoy, kActorOfficerLeary, true);
							Delay(1000);
							Music_Play(kMusicBRBlues, 52, 0, 2, -1, kMusicLoopPlayOnce, 1);
							Actor_Says(kActorMcCoy, 2235, 11); //00-2235.AUD	How could they?
							Loop_Actor_Walk_To_XYZ(kActorMcCoy, 27.12, 0.29, -47.35, 0, false, false, true);
							if (Player_Query_Agenda() == kPlayerAgendaPolite) {
								Actor_Face_Actor(kActorMcCoy, kActorOfficerLeary, true);
								Delay(1000);
								Actor_Says(kActorMcCoy, 2390, 14); //00-2390.AUD	Oh, God. No.
								Delay(2000);
								Actor_Says(kActorMcCoy, 2305, 19); //00-2305.AUD	I’m sorry.
								Delay(1000);
							} else {
								Actor_Face_Actor(kActorMcCoy, kActorOfficerLeary, true);
								Delay(1000);
								Actor_Says(kActorMcCoy, 170, -1); //00-0170.AUD	Damn.
							}
							Player_Gains_Control();
							Scene_2D_Region_Remove(0);
						}
					}
				}
			} else {
				Actor_Says(kActorDispatcher, 40, 3);
				Actor_Face_Actor(kActorMcCoy, kActorBulletBob, true);
				Actor_Says(kActorBulletBob, 890, 37);
				Actor_Change_Animation_Mode(kActorBulletBob, 4);
				Delay(1500);
				Actor_Face_Actor(kActorBulletBob, kActorMcCoy, true);
				Sound_Play(kSfxSHOTCOK1, 75, 0, 0, 50);
				Delay(1000);
				Player_Loses_Control();
				Loop_Actor_Walk_To_XYZ(kActorMcCoy, 45.0f, 0.15f, 68.0f, 0, true, true, true);
				Player_Gains_Control();
				Game_Flag_Set(kFlagBobAttackedMcCoy);
				Game_Flag_Set(kFlagRC04toRC03);
				Set_Enter(kSetRC03, kSceneRC03);
			}
		} else {
			Actor_Says(kActorDispatcher, 40, 3);
			Actor_Says(kActorBulletBob, 890, 37);
			Actor_Set_Goal_Number(kActorBulletBob, kGoalBulletBobShootMcCoy);
		}
	}

	Game_Flag_Set(kFlagRC04Entered);

	//return false;
}

void SceneScriptRC04::PlayerWalkedOut() {
	Game_Flag_Reset(kFlagRC04McCoyWarned);
}

void SceneScriptRC04::DialogueQueueFlushed(int a1) {
}

} // End of namespace BladeRunner
