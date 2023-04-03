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

void SceneScriptUG19::InitializeScene() {
	if (Game_Flag_Query(kFlagMA07toUG19)) {
		Setup_Scene_Information(67.03f, 105.0f, -74.97f, 256);
	} else {
		Setup_Scene_Information(181.0f, 11.52f,  -18.0f, 777);
	}

	Scene_Exit_Add_2D_Exit(0, 351,   0, 491, 347, 0);
	Scene_Exit_Add_2D_Exit(1, 548, 124, 639, 369, 1);

	Ambient_Sounds_Add_Looping_Sound(kSfxBOILPOT2, 45, 0, 1);
	Ambient_Sounds_Add_Looping_Sound(kSfxUGBED1,   76, 0, 1);
	Ambient_Sounds_Add_Sound(kSfxBBDRIP1,  2,  20, 25, 33, -100, 100, -100,  100, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBBDRIP2,  2,  20, 25, 33, -100, 100, -100,  100, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBBDRIP3,  2,  20, 25, 33, -100, 100, -100,  100, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBBDRIP4,  2,  20, 25, 33, -100, 100, -100,  100, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBBDRIP5,  2,  20, 25, 33, -100, 100, -100,  100, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxYELL1M2,  2, 120, 11, 12, -100, 100, -100,  100, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxGRUNT1M1, 2, 120, 11, 12, -100, 100, -100,  100, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxGRUNT1M3, 2, 120, 11, 12, -100, 100, -100,  100, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxGRUNT2M2, 2, 120, 11, 12, -100, 100, -100,  100, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBBGRN1,   5,  50, 47, 57, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBBGRN2,   5,  50, 47, 57, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBBGRN3,   5,  50, 47, 57, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSTEAM1,   5,  50, 47, 57, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSTEAM3,   5,  50, 17, 37, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSTEAM6A,  5,  50, 17, 37, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBBMOVE1,  5,  50, 27, 37, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBBMOVE2,  5,  50, 27, 37, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBBMOVE3,  5,  50, 27, 37, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxZUBWLK1,  5,  50, 27, 37, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxZUBWLK2,  5,  50, 27, 37, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxZUBWLK3,  5,  50, 27, 37, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxZUBWLK4,  5,  50, 27, 37, -100, 100, -101, -101, 0, 0);
}

void SceneScriptUG19::SceneLoaded() {
	Obstacle_Object("LADDER", true);
	Unclickable_Object("LADDER");
	Footstep_Sounds_Set(1, 0);
	Footstep_Sounds_Set(0, 3);
}

bool SceneScriptUG19::MouseClick(int x, int y) {
	return false;
}

bool SceneScriptUG19::ClickedOn3DObject(const char *objectName, bool a2) {
	return false;
}

bool SceneScriptUG19::ClickedOnActor(int actorId) {
	return false;
}

bool SceneScriptUG19::ClickedOnItem(int itemId, bool a2) {
	return false;
}

bool SceneScriptUG19::ClickedOnExit(int exitId) {
	if (exitId == 0) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, 67.03f, 7.29f, -74.97f, 0, true, false, false)) {
			Actor_Face_Heading(kActorMcCoy, 256, false);
			Footstep_Sound_Override_On(3);
			Loop_Actor_Travel_Ladder(kActorMcCoy, 8, true, kAnimationModeIdle);
			Footstep_Sound_Override_Off();
			Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
			Ambient_Sounds_Remove_All_Looping_Sounds(1u);
			Game_Flag_Set(kFlagUG19toMA07);
			Set_Enter(kSetMA07, kSceneMA07);
			if (_vm->_cutContent) {
				Sound_Play(kSfxMANHOLE1,  40, 0, 0, 50);
			}
		}
		return true;
	}

	if (exitId == 1) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, 181.0f, 11.52f, -18.0f, 0, true, false, false)) {
			Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
			Ambient_Sounds_Remove_All_Looping_Sounds(1u);
			Game_Flag_Set(kFlagUG19toUG14);
			Set_Enter(kSetUG14, kSceneUG14);
		}
		return true;
	}
	return false;
}

bool SceneScriptUG19::ClickedOn2DRegion(int region) {
	return false;
}

void SceneScriptUG19::SceneFrameAdvanced(int frame) {
}

void SceneScriptUG19::ActorChangedGoal(int actorId, int newGoal, int oldGoal, bool currentSet) {
}

void SceneScriptUG19::PlayerWalkedIn() {
	if (Game_Flag_Query(kFlagUG14toUG19)) {
		Game_Flag_Reset(kFlagUG14toUG19);
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagGordoEscaped)
			&& Global_Variable_Query(kVariableChapter) == 4
			&& !Game_Flag_Query(kFlagGordoTalkAct4)
			&& Actor_Query_Goal_Number(kActorGordo) != kGoalGordoNR01Arrested
			&& Actor_Query_Goal_Number(kActorGordo) < kGoalGordoGone) {
				if (Actor_Clue_Query(kActorMcCoy, kClueStolenCheese)  
				|| Actor_Clue_Query(kActorMcCoy, kClueGordoInterview3)
				|| Actor_Clue_Query(kActorMcCoy, kClueGordosLighterReplicant)
				|| Actor_Clue_Query(kActorMcCoy, kClueCrazylegsInterview1)
				|| Actor_Clue_Query(kActorMcCoy, kClueLichenDogWrapper)) {
					Actor_Set_At_XYZ(kActorMcCoy, 129.0f, 11.52f, -18.0f, 0);
				}
			} else {
				Loop_Actor_Walk_To_XYZ(kActorMcCoy, 129.0f, 11.52f, -18.0f, 0, false, false, false);
			}
			Game_Flag_Reset(kFlagRachaelWalks);
		} else {
			Loop_Actor_Walk_To_XYZ(kActorMcCoy, 129.0f, 11.52f, -18.0f, 0, false, false, false);
		}
	} else {
		Game_Flag_Reset(kFlagMA07toUG19);
		Footstep_Sound_Override_On(3);
		Loop_Actor_Travel_Ladder(kActorMcCoy, 8, false, kAnimationModeIdle);
		Footstep_Sound_Override_Off();
	}
	// Code for an encounter that you can have with Gordo in act 4 if he was neither arrested or killed.
	if (Global_Variable_Query(kVariableChapter) == 4) {
		if (Game_Flag_Query(kFlagGordoEscaped)
		&& !Game_Flag_Query(kFlagGordoTalkAct4)
		&& Actor_Query_Goal_Number(kActorGordo) != kGoalGordoNR01Arrested
		&& Actor_Query_Goal_Number(kActorGordo) < kGoalGordoGone) {
			if (Actor_Clue_Query(kActorMcCoy, kClueStolenCheese)  
			|| Actor_Clue_Query(kActorMcCoy, kClueGordoInterview3)
			|| Actor_Clue_Query(kActorMcCoy, kClueGordosLighterReplicant)
			|| Actor_Clue_Query(kActorMcCoy, kClueCrazylegsInterview1)
			|| Actor_Clue_Query(kActorMcCoy, kClueLichenDogWrapper)) {
				Actor_Put_In_Set(kActorGordo, kSetUG19);
				Actor_Set_At_XYZ(kActorGordo, 45.75, 7.22, -23.31, 0);
				Actor_Face_Actor(kActorMcCoy, kActorGordo, true);
				Actor_Face_Actor(kActorGordo, kActorMcCoy, true);
				if (Actor_Clue_Query(kActorGordo, kClueMcCoyHelpedGordo)) {
					Actor_Says(kActorMcCoy, 6515, 15); //00-6515.AUD	Gordo. I was wondering when you’d show your face again. –	
					Actor_Says(kActorGordo, 1100, 11); //02-1100.AUD	Still swinging, baby. And I probably got you to thank. 
					Actor_Says(kActorMcCoy, 6525, 15); //00-6525.AUD	That’s right. Now you can do something for me. 
					Actor_Says(kActorGordo, 1110, 12); //02-1110.AUD	I’m everywhere the spotlight is, baby. You tend to yours and I’ll take care of mine.
				} else {
					Actor_Says(kActorMcCoy, 6550, 14); //00-6550.AUD	You’re still hanging around?
					if (Actor_Query_Friendliness_To_Other(kActorGordo, kActorMcCoy) < 51) {
						Actor_Says(kActorGordo, 1090, 15); //02-1090.AUD	Wasn’t too damn cool the way it went down back there.
						Actor_Says(kActorMcCoy, 6520, 14); //00-6520.AUD	You’re alive, aren’t ya?
					}
					Actor_Says(kActorGordo, 1320, 16); //02-1320.AUD	Pretty astute, my man.
				} 
				Delay(1000);
				// Made it so McCoy only asks if Gordo stole the cheese if he has the stolen chesse clue and Gordo didn't confess to stealing the cheese in act 3.
				// It would make no sense for McCoy to ask if Gordo stole the cheese if he already confessed.
				if (Actor_Clue_Query(kActorMcCoy, kClueStolenCheese)) {
					if (!Actor_Clue_Query(kActorMcCoy, kClueGordoConfession)) {
						if (Actor_Clue_Query(kActorMcCoy, kClueCheese)) {
							Actor_Says(kActorMcCoy, 6540, 23); //00-6540.AUD	Did you steal this cheese from Kingston Kitchen?	
							if (Actor_Query_Intelligence(kActorGordo) == 80) {
								Actor_Says(kActorGordo, 1280, 13); //02-1280.AUD	Hey, baby. I may steal a line or two. But I’d never steal some cheese. I don’t do dairy.
								if (Player_Query_Agenda() == kPlayerAgendaSurly 
								|| Player_Query_Agenda() == kPlayerAgendaErratic) {
									Actor_Says(kActorMcCoy, 6590, 15); //00-6590.AUD	The owner described you to a tee. Even down to that rotten bow tie you always wear. 
								} else {
									Actor_Says(kActorMcCoy, 6995, 18); //00-6995.AUD	That's not what I heard. You wanna set the record straight?
								}
							}
						} else {
							Actor_Says(kActorMcCoy, 3250, kAnimationModeTalk);
							Actor_Says(kActorGordo, 530, 18);
							Actor_Says(kActorMcCoy, 3300, 15);
							if (Actor_Query_Intelligence(kActorGordo) == 60) {
								Actor_Says(kActorGordo, 540, 13);
								Actor_Says(kActorMcCoy, 3305, kAnimationModeTalk);
								Actor_Says(kActorGordo, 550, 16); //02-0550.AUD	For crying out loud. Can’t a guy make a living in this fakakta place without being hassled?
								Actor_Says(kActorMcCoy, 7815, 13); //00-7815.AUD	No.
								Actor_Clue_Acquire(kActorMcCoy, kClueGordoConfession, true, kActorGordo);
								Delay(1000);	
							}
						}
					} else {
						Actor_Says(kActorMcCoy, 3250, kAnimationModeTalk);
						Delay(1000);
					}
					Actor_Clue_Acquire(kActorMcCoy, kClueGordoInterview2, true, kActorGordo);	
					Actor_Says(kActorMcCoy, 6600, 13); //00-6600.AUD	Why the big deal over food?
					Actor_Says(kActorGordo, 1310, 14); //02-1310.AUD	It was just some cheese, McCoy. And some takeout cartons.
					if (Actor_Clue_Query(kActorMcCoy, kClueKingstonKitchenBox1)
					|| Actor_Clue_Query(kActorMcCoy, kClueKingstonKitchenBox2)) {
						Actor_Says(kActorMcCoy, 6595, 15); //00-6595.AUD	And you gave the takeout cartons to Sadik. 
					}
					Actor_Says(kActorMcCoy, 6555, 15); //00-6555.AUD	Let’s hear the rest of it.
					if (Actor_Clue_Query(kActorGordo, kClueMcCoyHelpedGordo)) {
						if (Game_Flag_Query(kFlagLucyIsReplicant)) {
							Music_Play(kMusicCrysDie1, 25, 0, 1, -1, kMusicLoopPlayOnce, 0);
							Delay(1000);
							Actor_Says(kActorGordo, 1330, 16); //02-1330.AUD	Anything good is damn hard to come by. Poor Lucy wasn’t doing so hot.
							Actor_Says(kActorGordo, 1340, 12); //02-1340.AUD	She couldn’t keep anything down.
							Delay(1000);
							Actor_Says(kActorGordo, 1350, 11); //02-1350.AUD	So, I thought… maybe something different to eat would help.
							Delay(2000);
							Actor_Says(kActorMcCoy, 170, 19); //00-0170.AUD	Damn.
							Delay(1000);
							Actor_Says(kActorGordo, 1380, 16); //02-1380.AUD	It’s the way of all flesh, baby. Just the issue of when that’s got us concerned.
							Delay(2000);
							Actor_Says(kActorMcCoy, 2305, 13); //00-2305.AUD	I’m sorry.
							Delay(2000);
						} else {
							Actor_Says(kActorGordo, 1360, 11); //02-1360.AUD	Clovis… well, he’s been getting sick. He can’t keep anything down.
							Actor_Says(kActorGordo, 1370, 13); //02-1370.AUD	I thought… maybe something a little different to eat.
							if (Actor_Query_Friendliness_To_Other(kActorClovis, kActorMcCoy) > 50) {
								Actor_Says(kActorGordo, 6605, 15); //00-6605.AUD	He’s dying, isn’t he?
								Actor_Says(kActorGordo, 1380, 16); //02-1380.AUD	It’s the way of all flesh, baby. Just the issue of when that’s got us concerned.
							}
						}
					} else {
						Actor_Says(kActorGordo, 1030, 11); //02-1030.AUD	Sorry, Charlie.
					}
				}
				Delay(1000);
				if (!Actor_Clue_Query(kActorMcCoy, kClueGuzzaFramedMcCoy)) {
					Actor_Says(kActorMcCoy, 6530, 15); //00-6530.AUD	Somebody set me up, Gordo. Who’s behind it? Clovis? 	
					Actor_Says(kActorGordo, 1120, 12); //02-1120.AUD	Clovis ain’t no zipper-head He’s capable of pulling a string or two.
					Actor_Says(kActorGordo, 1130, 11); //02-1130.AUD	But no way he’s a one-man show.
					Actor_Says(kActorMcCoy, 6990, 15); //00-6990.AUD	Enlighten me.	
					if (Actor_Clue_Query(kActorGordo, kClueMcCoyHelpedGordo)) {
						Actor_Says(kActorGordo, 1160, 13); //02-1160.AUD	Shoot. All you gotta do is look to your own.
						Actor_Says(kActorMcCoy, 6565, 15); //00-6565.AUD	Someone inside the Blade Runner unit?
						if (Actor_Query_Friendliness_To_Other(kActorGordo, kActorMcCoy) < 51) {
							Actor_Says(kActorGordo, 1170, 14); //02-1170.AUD	Smart. Real genius level you are
						} else {
							Delay(1000);
							Actor_Says(kActorMcCoy, 6975, 13);
						}
						Actor_Clue_Acquire(kActorMcCoy, kClueGordoBlabs, true, kActorGordo);
					} else {
						Actor_Says(kActorGordo, 1180, 14); //02-1180.AUD	Hey, baby. Nine times out of ten I give the audience what they want.
						Actor_Says(kActorGordo, 1190, 16); //02-1190.AUD	But this time, well, I can’t risk spoiling this beautiful mug.
						Actor_Says(kActorGordo, 1200, 15); //02-1200.AUD	Clovis would be serving up free cosmetic surgery.
						if (Player_Query_Agenda() == kPlayerAgendaSurly 
						|| Player_Query_Agenda() == kPlayerAgendaErratic) {
							Actor_Says(kActorMcCoy, 6560, 15); //00-6560.AUD	Big loss. The fifties went out in the nineties. Now I want you to throw me a name.
							if (Actor_Query_Friendliness_To_Other(kActorGordo, kActorMcCoy) < 51) {
								Actor_Says(kActorGordo, 1290, 11); //02-1290.AUD	Nice words coming from a fashion plate like you.
								Actor_Says(kActorGordo, 1300, 13); //02-1300.AUD	When did you last press that shirt? 1492?
								Actor_Says(kActorMcCoy, 665, 15); //00-0665.AUD	Real funny, pal.
							} else {
								Actor_Says(kActorGordo, 1030, 11); //02-1030.AUD	Sorry, Charlie.
							}
						}
					}
				}
				Delay(1000);
				Actor_Says(kActorMcCoy, 6535, 15); //00-6535.AUD	I need to see Clovis ASAP.
				if (Actor_Clue_Query(kActorGordo, kClueMcCoyHelpedGordo)) {
					if (Game_Flag_Query(kFlagGordoIsReplicant)) {
						Actor_Says(kActorGordo, 1210, 15); //02-1210.AUD	Sure. But he wants to pick the venue. And he doesn’t like to be hurried into anything.
					} else {
						Actor_Says(kActorGordo, 1140, 14); //02-1140.AUD	You know what Clovis would do, if he found out I was even talking to you? 
						Actor_Says(kActorGordo, 1150, 13); //02-1150.AUD	Eleven to one I’d never rumba again!
						Actor_Says(kActorMcCoy, 6570, 15); //00-6570.AUD	You know he wants to meet with me.
					}		
				}	
				Actor_Says(kActorGordo, 1220, 12); //02-1220.AUD	Hell, I don’t know why you’re so gung-ho to see the man anyway.
				Actor_Says(kActorMcCoy, 6575, 15); //00-6575.AUD	I need some answers, that’s why. I’m running out of time.
				if (Game_Flag_Query(kFlagGordoIsReplicant)) {
					Actor_Says(kActorGordo, 1230, 13); //02-1230.AUD	Join the club. 
					if (!Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
						Actor_Says(kActorMcCoy, 6580, 15); //00-6580.AUD	I ain’t a member of your club.	
					} else {
						Actor_Says(kActorMcCoy, 6985, 16); //00-6985.AUD	Got the straight scoop for me or what?
					}
				} 
				if (Actor_Query_Intelligence(kActorGordo) == 80) {
					Actor_Says(kActorGordo, 1240, 12); //02-1240.AUD	Easy, boss. I’m just saying… that we’re all like a bunch of kids’ tops.
					Actor_Says(kActorGordo, 1250, 13); //02-1250.AUD	Been wound up with a string and sent off spinning in all directions.
					Actor_Says(kActorGordo, 1260, 15); //02-1260.AUD	Never know when you’re gonna be flying off the table, ya dig?
					Actor_Says(kActorGordo, 1270, 11); //02-1270.AUD	And when the spinning is gonna stop.
					if (Player_Query_Agenda() == kPlayerAgendaSurly 
					|| Player_Query_Agenda() == kPlayerAgendaErratic) {
						Actor_Says(kActorMcCoy, 6585, 15); //00-6585.AUD	That’s real profound, Gordo.
					} else {
						Actor_Says(kActorMcCoy, 4880, 13); //00-4880.AUD	Is that right?
					}
				}
				Delay(1000);
				Actor_Says(kActorGordo, 620, 16); //02-0620.AUD		Look I’d love to stay and jawbone but the show must go on, you dig?
				// Removed code that makes Gordo invisible. Also added in code so McCoy moves out of the way when Gordo leaves so Gordo doesn't phase through McCoy.
				Player_Loses_Control();
				Loop_Actor_Walk_To_XYZ(kActorMcCoy, 115.51, 11.73, -40.11, 0, true, false, false);
				Actor_Face_Actor(kActorMcCoy, kActorGordo, true);
				Loop_Actor_Walk_To_XYZ(kActorGordo, 180.04, 11.73, -5.42, 0, true, false, false);
				Player_Gains_Control();
				Game_Flag_Set(kFlagGordoTalkAct4);
			}
		}
	}
}											

void SceneScriptUG19::PlayerWalkedOut() {
}

void SceneScriptUG19::DialogueQueueFlushed(int a1) {
}

} // End of namespace BladeRunner
