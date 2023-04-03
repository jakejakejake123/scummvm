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

void SceneScriptKP06::InitializeScene() {
	if (Game_Flag_Query(kFlagKP07toKP06) ) {
		Setup_Scene_Information(-755.0f, 8.26f, -665.0f, 640);
	} else {
		Setup_Scene_Information(-868.0f, 8.26f,   -8.0f,   0);
	}

	Scene_Exit_Add_2D_Exit(0, 270, 445, 639, 479, 2);
	Scene_Exit_Add_2D_Exit(1, 320, 158, 352, 220, 0);

	Ambient_Sounds_Add_Looping_Sound(kSfxKPAMB1,   34, 1, 1);
	Ambient_Sounds_Add_Looping_Sound(kSfxSKINBED1, 27, 1, 1);
	Ambient_Sounds_Add_Looping_Sound(kSfxRUMLOOP1, 90, 1, 1);
	Ambient_Sounds_Add_Sound(kSfxSCARY1,  2, 100, 25,  33, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSCARY2,  2, 100, 25,  33, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSCARY3,  2, 100, 25,  33, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxTHNDER2, 5, 180, 50, 100, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxTHNDER3, 5, 180, 50, 100, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxTHNDER4, 5, 180, 50, 100, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSCARY4,  2, 100, 25,  33, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSCARY5,  2, 100, 25,  33, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSCARY6,  2, 100, 25,  33, -100, 100, -101, -101, 0, 0);

	if (Game_Flag_Query(kFlagKP05toKP06) ) {
		Scene_Loop_Start_Special(kSceneLoopModeLoseControl, 0, false);
		Scene_Loop_Set_Default(1);
		Game_Flag_Reset(kFlagKP05toKP06);
	} else {
		Scene_Loop_Set_Default(1);
	}
}

void SceneScriptKP06::SceneLoaded() {
	Obstacle_Object("TRASH CAN WITH FIRE", true);
	Obstacle_Object("MOONBUS", true);
	Obstacle_Object("STAIR 1", true);
	Obstacle_Object("COCKPIT FRONT", true);
	Unobstacle_Object("OBSTACLEBOX28", true);
	Unobstacle_Object("OBSTACLEBOX32", true);
	Unclickable_Object("TRASH CAN WITH FIRE");
}

bool SceneScriptKP06::MouseClick(int x, int y) {
	return false;
}

bool SceneScriptKP06::ClickedOn3DObject(const char *objectName, bool a2) {
	return false;
}

bool SceneScriptKP06::ClickedOnActor(int actorId) {
	if ( actorId == kActorSadik
	 && !Game_Flag_Query(kFlagMcCoyAttackedReplicants)
	) {
		if (Actor_Clue_Query(kActorSadik, kCluePowerSource)) {
			Actor_Face_Actor(kActorMcCoy, kActorSadik, true);
			if (_vm->_cutContent) {
				if (Player_Query_Agenda() == kPlayerAgendaPolite) {
					Actor_Says(kActorMcCoy, 8610, 15);
				} else {
					Actor_Says(kActorMcCoy, 8514, 14); //00-8514.AUD	Got anything new to tell me?
				}
			} else {
				Actor_Says(kActorMcCoy, 8610, 15);
			}
			Actor_Says(kActorSadik, 290, kAnimationModeTalk);
		} else if (Actor_Clue_Query(kActorMcCoy, kCluePowerSource)) {
			if (_vm->_cutContent) {
				Loop_Actor_Walk_To_XYZ(kActorMcCoy, -847.79f, 0.98f, -667.24f, 0, false, true, false);
				Loop_Actor_Walk_To_Actor(kActorMcCoy, kActorSadik, 24, false, true);
				Actor_Face_Actor(kActorSadik, kActorMcCoy, true);
				Actor_Face_Actor(kActorMcCoy, kActorSadik, true);
				Actor_Change_Animation_Mode(kActorMcCoy, 23);
				Actor_Change_Animation_Mode(kActorSadik, 23);
				Delay(800);
				Item_Pickup_Spin_Effect_From_Actor(kModelAnimationPowerSource, kActorSadik, 0, 0);
				Game_Flag_Set(kFlagMcCoyIsHelpingReplicants);
				Actor_Set_Goal_Number(kActorClovis, kGoalClovisKP07Wait);
				Actor_Clue_Lose(kActorMcCoy, kCluePowerSource);
				Delay(800);
				Actor_Says(kActorMcCoy, 8170, 11); //00-8170.AUD	There you go.
			}
			if (!_vm->_cutContent) {
				Actor_Says(kActorSadik, 280, kAnimationModeTalk); //08-0280.AUD	You for real I’m thinking.
			}
			Actor_Says(kActorSadik, 290, kAnimationModeTalk); //08-0290.AUD	Go in. You see Clovis. He not got too much time left.
			Actor_Clue_Acquire(kActorSadik, kCluePowerSource, true, kActorMcCoy);
			if (_vm->_cutContent) {
				if (Player_Query_Agenda() != kPlayerAgendaSurly 
				&& Player_Query_Agenda() != kPlayerAgendaErratic) {
					if (Actor_Clue_Query(kActorMcCoy, kClueDragonflyEarring)
					|| Actor_Clue_Query(kActorMcCoy, kClueLabAnalysisGoldChain)) {
						Actor_Says(kActorMcCoy, 5150, 18); //00-5150.AUD	One more thing.
						Actor_Change_Animation_Mode(kActorMcCoy, 23);
						Actor_Change_Animation_Mode(kActorSadik, 23);
						Delay(800);
						if (Actor_Clue_Query(kActorMcCoy, kClueDragonflyEarring)) {
							Actor_Clue_Lose(kActorMcCoy, kClueDragonflyEarring);
							Actor_Clue_Acquire(kActorSadik, kClueDragonflyEarring, true, -1);
							Item_Pickup_Spin_Effect_From_Actor(kModelAnimationDragonflyEarring, kActorSadik, 0, 0);
							Delay(1500);
						} 
						if (Actor_Clue_Query(kActorMcCoy, kClueLabAnalysisGoldChain)) {
							Actor_Clue_Lose(kActorMcCoy, kClueLabAnalysisGoldChain);
							Actor_Clue_Acquire(kActorSadik, kClueLabAnalysisGoldChain, true, -1);
							Item_Pickup_Spin_Effect_From_Actor(kModelAnimationMaggieBracelet, kActorSadik, 0, 0);
							Delay(1500);
							if (Actor_Query_Friendliness_To_Other(kActorClovis, kActorMcCoy) > 50
							&& !Game_Flag_Query(kFlagMcCoyRetiredReplicant)) { 
								Actor_Says(kActorMcCoy, 115, -1); //00-0115.AUD	Maggie.
								Delay(1000);
								Actor_Says(kActorMcCoy, 700, kAnimationModeTalk); //00-0700.AUD	I'm starting to understand.
								Delay(2000);
								Actor_Says(kActorMcCoy, 2305, 13); //00-2305.AUD	I’m sorry.		
							}				
						}
					}
				}
				Delay(1000);
				Loop_Actor_Walk_To_XYZ(kActorMcCoy, -731.0f, 8.26f, -657.0f, 0, false, false, false);
				Player_Set_Combat_Mode(false);
				Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
				Ambient_Sounds_Remove_All_Looping_Sounds(1u);
				Game_Flag_Set(kFlagKP06toKP07);
				Set_Enter(kSetKP07, kSceneKP07);
			}
		} else {
			Actor_Says(kActorMcCoy, 2320, kAnimationModeTalk);
			Actor_Says(kActorMcCoy, 2325, kAnimationModeTalk);
			Actor_Says(kActorSadik, 300, kAnimationModeTalk);
			if (_vm->_cutContent) {
				if (Actor_Query_Friendliness_To_Other(kActorClovis, kActorMcCoy) > 50
				&& !Game_Flag_Query(kFlagMcCoyRetiredReplicant)) { 
					Actor_Says(kActorSadik, 310, kAnimationModeTalk);
				}
			} else {
				Actor_Says(kActorSadik, 310, kAnimationModeTalk);
			}
		}
	}
	return false;
}

bool SceneScriptKP06::ClickedOnItem(int itemId, bool a2) {
	return false;
}

bool SceneScriptKP06::ClickedOnExit(int exitId) {
	if (exitId == 0) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -868.0f, 8.26f, -68.0f, 0, true, false, false)) {
			Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
			Ambient_Sounds_Remove_All_Looping_Sounds(1u);
			Game_Flag_Set(kFlagKP06toKP05);
			Set_Enter(kSetKP05_KP06, kSceneKP05);
		}
		return true;
	}

	if (exitId == 1) {
		if (Actor_Clue_Query(kActorSadik, kCluePowerSource)
		 || Actor_Query_Goal_Number(kActorSadik) != kGoalSadikKP06NeedsReactorCoreFromMcCoy
		) {
			if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -731.0f, 8.26f, -657.0f, 0, true, false, false)) {
				if (Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
					if (!Game_Flag_Query(kFlagMcCoyAttackedReplicants)) {
						Player_Set_Combat_Mode(false);
					}
				} else if (Actor_Query_Goal_Number(kActorSteele) == kGoalSteeleKP06Leave) {
					Actor_Set_Goal_Number(kActorSteele, kGoalSteeleWaitingForEnd);
				} else {
					Actor_Set_Goal_Number(kActorGaff, kGoalGaffGone);
				}
				Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
				Ambient_Sounds_Remove_All_Looping_Sounds(1u);
				Game_Flag_Set(kFlagKP06toKP07);
				Set_Enter(kSetKP07, kSceneKP07);
			}
		} else if (Actor_Clue_Query(kActorMcCoy, kCluePowerSource)) {
			if (_vm->_cutContent) {
				Loop_Actor_Walk_To_XYZ(kActorMcCoy, -847.79f, 0.98f, -667.24f, 0, false, true, false);
				Loop_Actor_Walk_To_Actor(kActorMcCoy, kActorSadik, 24, false, true);
				Actor_Face_Actor(kActorSadik, kActorMcCoy, true);
				Actor_Face_Actor(kActorMcCoy, kActorSadik, true);
				Actor_Change_Animation_Mode(kActorMcCoy, 23);
				Actor_Change_Animation_Mode(kActorSadik, 23);
				Delay(800);
				Item_Pickup_Spin_Effect_From_Actor(kModelAnimationPowerSource, kActorSadik, 0, 0);
				Game_Flag_Set(kFlagMcCoyIsHelpingReplicants);
				Actor_Set_Goal_Number(kActorClovis, kGoalClovisKP07Wait);
				Actor_Clue_Lose(kActorMcCoy, kCluePowerSource);
				Delay(800);
				Actor_Says(kActorMcCoy, 8170, 11); //00-8170.AUD	There you go.
			}
			if (_vm->_cutContent) {
				if (Actor_Query_Friendliness_To_Other(kActorClovis, kActorMcCoy) > 50
				&& !Game_Flag_Query(kFlagMcCoyRetiredReplicant)) { 
					Actor_Says(kActorSadik, 280, kAnimationModeTalk); //08-0280.AUD	You for real I’m thinking.
				}
			} else {
				Actor_Says(kActorSadik, 280, kAnimationModeTalk); //08-0280.AUD	You for real I’m thinking.
			}
			Actor_Says(kActorSadik, 290, kAnimationModeTalk);
			Actor_Clue_Acquire(kActorSadik, kCluePowerSource, true, kActorMcCoy);
			if (_vm->_cutContent) {
				if (Player_Query_Agenda() != kPlayerAgendaSurly 
				&& Player_Query_Agenda() != kPlayerAgendaErratic) {
					if (Actor_Clue_Query(kActorMcCoy, kClueDragonflyEarring)
					|| Actor_Clue_Query(kActorMcCoy, kClueLabAnalysisGoldChain)) {
						Actor_Says(kActorMcCoy, 5150, 18); //00-5150.AUD	One more thing.
						Actor_Change_Animation_Mode(kActorMcCoy, 23);
						Actor_Change_Animation_Mode(kActorSadik, 23);
						Delay(800);
						if (Actor_Clue_Query(kActorMcCoy, kClueDragonflyEarring)) {
							Actor_Clue_Lose(kActorMcCoy, kClueDragonflyEarring);
							Actor_Clue_Acquire(kActorSadik, kClueDragonflyEarring, true, -1);
							Item_Pickup_Spin_Effect_From_Actor(kModelAnimationDragonflyEarring, kActorSadik, 0, 0);
							Delay(1500);
						}
						if (Actor_Clue_Query(kActorMcCoy, kClueLabAnalysisGoldChain)) {
							Actor_Clue_Lose(kActorMcCoy, kClueLabAnalysisGoldChain);
							Actor_Clue_Acquire(kActorSadik, kClueLabAnalysisGoldChain, true, -1);
							Item_Pickup_Spin_Effect_From_Actor(kModelAnimationMaggieBracelet, kActorSadik, 0, 0);
							Delay(1500);
							if (Actor_Query_Friendliness_To_Other(kActorClovis, kActorMcCoy) > 50
							&& !Game_Flag_Query(kFlagMcCoyRetiredReplicant)) { 
								Actor_Says(kActorMcCoy, 115, -1); //00-0115.AUD	Maggie.
								Delay(1000);
								Actor_Says(kActorMcCoy, 700, kAnimationModeTalk); //00-0700.AUD	I'm starting to understand.
								Delay(2000);
								Actor_Says(kActorMcCoy, 2305, 13); //00-2305.AUD	I’m sorry.
							}
						}				
					}
				}
				Delay(1000);
				Loop_Actor_Walk_To_XYZ(kActorMcCoy, -731.0f, 8.26f, -657.0f, 0, false, false, false);
			} else {
				Loop_Actor_Walk_To_XYZ(kActorMcCoy, -731.0f, 8.26f, -657.0f, 0, false, true, false);
			}
			Player_Set_Combat_Mode(false);
			Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
			Ambient_Sounds_Remove_All_Looping_Sounds(1u);
			Game_Flag_Set(kFlagKP06toKP07);
			Set_Enter(kSetKP07, kSceneKP07);
		} else {
			Actor_Set_Goal_Number(kActorSadik, 417);
		}
		return true;
	}
	return false;
}

bool SceneScriptKP06::ClickedOn2DRegion(int region) {
	return false;
}

void SceneScriptKP06::SceneFrameAdvanced(int frame) {
}

void SceneScriptKP06::ActorChangedGoal(int actorId, int newGoal, int oldGoal, bool currentSet) {
}

void SceneScriptKP06::PlayerWalkedIn() {
	if (!Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)
	 &&  Game_Flag_Query(kFlagKP07toKP06)
	) {
		Game_Flag_Reset(kFlagKP07toKP06);

		// Ending - leave with Steele
		// Restored the Replicant betrayal ending where Crystal is alive. If you didn't retire a human and didn't warn Lucy Dektora or Izo, and you didn't turn in the Guzza evidence
		// or got Crystal to trust you by not retiring enough reps you will not confront her in the kipple and she will appear here instead.
		// Fixed the code here. I accidentally made it so the Crystal ending where you betray the reps is the only ending the plays in retored content mode. This has been fixed and now all the different endings will play.
		if (_vm->_cutContent) {
			if (Actor_Query_Is_In_Current_Set(kActorSadik)) {
				Actor_Put_In_Set(kActorSadik, kSetKP01);
				Actor_Set_At_XYZ(kActorSadik, -389.43f, 2.06f, -200.77f, 512);
			}
			Music_Stop(1u);
			Music_Play(kMusicBRBlues, 52, 0, 2, -1, kMusicLoopPlayOnce, 0);
			if (Actor_Query_Goal_Number(kActorSteele) < kGoalSteeleGone) {
				Actor_Put_In_Set(kActorSteele, kSetKP05_KP06);
				Actor_Set_At_XYZ(kActorSteele, -782.15f, 8.26f, -263.64f, 52);
				Actor_Face_Actor(kActorSteele, kActorMcCoy, true);
				Actor_Face_Actor(kActorMcCoy, kActorSteele, true);
				if	(Actor_Query_Goal_Number(kActorMaggie) < kGoalMaggieDead) {
					Actor_Put_In_Set(kActorMaggie, kSetKP05_KP06);
					Actor_Set_At_XYZ(kActorMaggie, -802.21, 3.74, -640.55, 659);	
					Actor_Face_Actor(kActorMaggie, kActorSteele, true);
				}	
				if (!Game_Flag_Query(kFlagMcCoyAttackedReplicants)) {
					Actor_Says(kActorSteele, 2530, 13);
					Actor_Says(kActorMcCoy, 6200, 11); //00-6200.AUD	Do it. You just might be doing me a favor.
					Actor_Says(kActorSteele, 2540, 15);
					if (Game_Flag_Query(kFlagMcCoyRetiredClovis)) {
						Actor_Says(kActorMcCoy, 5705, 18); //00-5705.AUD	Uh-huh.
					} else {
						Delay(2000);
					}
				} else {
					Actor_Says(kActorSteele, 2560, 12); //01-2560.AUD	I gotta admit. I had my doubts about you.
					if (Player_Query_Agenda() != kPlayerAgendaPolite) {
						Actor_Says(kActorMcCoy, 6210, 14); //00-6210.AUD	What are you saying, Steele? You still wanna put me on the Machine?
						Actor_Says(kActorSteele, 2570, 13); //01-2570.AUD	Take it easy, will ya?
						Actor_Says(kActorMcCoy, 6215, 14); //00-6215.AUD	I plan to. I’m going home.
					} else {
						Actor_Says(kActorMcCoy, 5065, 18); //00-5065.AUD	Is that right?
					}
					Actor_Says(kActorSteele, 2580, 15); //01-2580.AUD	I gotta say, McCoy. You had me fooled. I thought for sure you were a Rep.
					Actor_Says(kActorSteele, 2590, 12); //01-2590.AUD	Don’t get me wrong. I mean, you’re one crazy dude. But I like that.
					Delay(1000);
				}
				if (Game_Flag_Query(kFlagMcCoyRetiredHuman)) {
					Actor_Says(kActorSteele, 1330, 12); //01-1330.AUD	We got a problem, though. There’s an APB out for you.
					if (Game_Flag_Query(kFlagGuzzaSaved)
					&& !Game_Flag_Query(kFlagGuzzaArrested)
					&& Actor_Query_Friendliness_To_Other(kActorGuzza, kActorMcCoy) < 51) {
						Actor_Says(kActorSteele, 1340, 12); //01-1340.AUD	You’ve been shooting civilians? Because that’s what Guzza's saying.
						Actor_Says(kActorSteele, 1350, 12); //01-1350.AUD	He wants to put you on the Machine.
						Delay(1000);
						Actor_Says(kActorMcCoy, 3120, 15); //00-3120.AUD	You’re gonna retire me, Steele?
						Actor_Says(kActorSteele, 640, 12); //01-0640.AUD	No chance.
						Delay(1000);
					}
					Actor_Says(kActorSteele, 1380, 12); //01-1380.AUD	Is it true, Slim? Did you kill somebody?
					if (Player_Query_Agenda() != kPlayerAgendaSurly 
					&& Player_Query_Agenda() != kPlayerAgendaErratic) {
						Delay(1000);
						Actor_Says(kActorMcCoy, 7980, 19); //00-7980.AUD	Yeah. Maybe.
						Delay(1000);
					} else {
						Actor_Says(kActorMcCoy, 3130, 15); //00-3130.AUD	What do you think?
						Actor_Says(kActorSteele, 1390, 12); //01-1390.AUD	I ain’t sure yet. I like to be sure.
						Delay(1000);
					}
					Actor_Change_Animation_Mode(kActorSteele, 4);
					Delay(1500);
					Actor_Says(kActorSteele, 2210, -1); //01-2210.AUD	I guess I gotta take you in. They'll probably have to run a couple of tests, too.
					Delay(3000);
					if (Actor_Query_Goal_Number(kActorClovis) < kGoalClovisGone) {
						Outtake_Play(kOuttakeEnd2, false, -1);
					}
					Game_Over();
				} else {		
					// Made it so Crystal or Gaff only mentions McCoy getting a promotion and having a lot of bonuses if he retires enough reps to earn 1500 chinyen.
					if (Actor_Query_Friendliness_To_Other(kActorGaff, kActorMcCoy) > 60) {
						Actor_Says(kActorSteele, 2550, 12); //01-2550.AUD	I think you got a promotion coming. Not to mention all those retirement bonuses.
						Actor_Says(kActorMcCoy, 6205, 14); //00-6205.AUD	As long as I get something like… twenty hours of sleep in the process.
					}
					Async_Actor_Walk_To_Waypoint(kActorMcCoy, 551, 0, false);
					if	(Actor_Query_Goal_Number(kActorMaggie) < kGoalMaggieDead) {
						Async_Actor_Walk_To_Waypoint(kActorMaggie, 551, 0, false);
					}
					Delay(1000);
					Actor_Says(kActorMcCoy, 6220, -1); //00-6220.AUD	I’m going home, Steele. I’m finished.
					Delay(3000);
					Music_Stop(1u);
					Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
					Ambient_Sounds_Remove_All_Looping_Sounds(1u);
					if (Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) > 60) {
						Outtake_Play(kOuttakeEnd6, false, -1);
					}
					Game_Over();	
				}
			} else { // Ending - talk with Gaff and leaving alone
				AI_Movement_Track_Flush(kActorGaff);
				Actor_Put_In_Set(kActorGaff, kSetKP05_KP06);
				Actor_Set_At_XYZ(kActorGaff, -782.15f, 8.26f, -263.64f, 52);
				Actor_Face_Actor(kActorGaff, kActorMcCoy, true);
				Actor_Face_Actor(kActorMcCoy, kActorGaff, true);
				// If Maggie is alive she will be in the set.
				if (_vm->_cutContent) {
					if	(Actor_Query_Goal_Number(kActorMaggie) < kGoalMaggieDead) {
						Actor_Put_In_Set(kActorMaggie, kSetKP05_KP06);
						Actor_Set_At_XYZ(kActorMaggie, -802.21, 3.74, -640.55, 659);
						Actor_Face_Actor(kActorMaggie, kActorGaff, true);
					}
				}
				if (Game_Flag_Query(kFlagMcCoyRetiredHuman)) {
					Actor_Says(kActorGaff, 110, 12);
					Actor_Says(kActorMcCoy, 5705, 18); //00-5705.AUD	Uh-huh.
					Delay(2000);
					Actor_Says(kActorGaff, 190, 14); //53-0190.AUD	It's like I said before. You retire a human, your career is over.
					Actor_Says(kActorGaff, 200, 15); //53-0200.AUD	Your life too, maybe.
					Delay(1000);
					Actor_Says(kActorMcCoy, 3005, 13); //00-3005.AUD	What are you gonna do? Take me in?
					Delay(2000);
					Actor_Says(kActorMcCoy, 170, 19); //00-0170.AUD	Damn.
					Delay(3000);
					if (Actor_Query_Goal_Number(kActorClovis) < kGoalClovisGone) {
						Outtake_Play(kOuttakeEnd2, false, -1);
					}
					Game_Over();
				} else {
					Actor_Says(kActorGaff, 220, 13);
					if (Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) > 59) {
						Actor_Says(kActorMcCoy, 6245, 11); //00-6245.AUD	I could have used you about ten minutes ago.
						Actor_Says(kActorGaff, 230, 14);
					} else {
						Actor_Says(kActorMcCoy, 5705, 18); //00-5705.AUD	Uh-huh.
						Delay(1000);
					}
					if (Game_Flag_Query(kFlagMcCoyAttackedReplicants)) {
						Actor_Says(kActorMcCoy, 6250, 15); //00-6250.AUD	I thought it was all over, when Steele showed up.
						Actor_Says(kActorGaff, 240, 13);
						Delay(1000);
						Actor_Says(kActorMcCoy, 6255, 17); 
						Actor_Says(kActorGaff, 250, 14);
						Delay(1000);
					}
					if (Actor_Query_Friendliness_To_Other(kActorGaff, kActorMcCoy) > 60) {
						Actor_Says(kActorGaff, 260, 12); //53-0260.AUD	Chief Bryant wants to talk to you. He says you're really ready now.
						Actor_Says(kActorMcCoy, 6260, 15); //00-6260.AUD	It never ends, does it?
						Actor_Says(kActorGaff, 270, 13); //53-0270.AUD	Uh-uh,  you're a real Blade Runner now. Full retirement bonuses and everything.
					}
					Actor_Says(kActorGaff, 280, 15); //53-0280.AUD	You've done a man's job, sir.
					if (Player_Query_Agenda() != kPlayerAgendaSurly 
					&& Player_Query_Agenda() != kPlayerAgendaErratic) {
						Actor_Says(kActorMcCoy, 6265, 18); //00-6265.AUD	How come I don’t feel good about it?
						Actor_Says(kActorGaff, 290, 14); //53-0290.AUD	Who knows?
					} else {
						Actor_Says(kActorMcCoy, 2215, 14); //00-2215.AUD	That’s right.
					}
					// If Maggie is alive Gaffs lines about getting a new animal will not play and instead McCoy will say the city is a cess pool instead.
					if (Actor_Query_Goal_Number(kActorMaggie) < kGoalMaggieDead) {
						Delay(1000);
						Actor_Says(kActorGaff, 100, 14); //53-0100.AUD	Go home and get some rest. I'm sure you need it.
						Delay(1500);				
						Actor_Says(kActorMcCoy, 8625, 14); //00-8625.AUD	This city is a cesspool.
						Async_Actor_Walk_To_Waypoint(kActorMcCoy, 551, 0, false);
						if	(Actor_Query_Goal_Number(kActorMaggie) < kGoalMaggieDead) {
							Async_Actor_Walk_To_Waypoint(kActorMaggie, 551, 0, false);
						}
						Async_Actor_Walk_To_Waypoint(kActorGaff, 551, 0, false);
						Actor_Says(kActorGaff, 310, -1); //53-0310.AUD	Whatever you want to believe, McCoy.
					} else { 
						if (Actor_Query_Friendliness_To_Other(kActorGaff, kActorMcCoy) > 60) {
							Actor_Says(kActorGaff, 300, 15); //53-0300.AUD	Buy yourself another animal maybe. A real one, not a Tyrell fake.
							Actor_Says(kActorMcCoy, 6270, 11);
							Async_Actor_Walk_To_Waypoint(kActorMcCoy, 550, 0, false);
							Async_Actor_Walk_To_Waypoint(kActorGaff, 551, 0, false);
							Actor_Says(kActorGaff, 310, -1);
						} else {
							Delay(1000);
							Actor_Says(kActorGaff, 100, 14); //53-0100.AUD	Go home and get some rest. I'm sure you need it.
							Delay(1500);				
							Actor_Says(kActorMcCoy, 8625, 14); //00-8625.AUD	This city is a cesspool.
							Async_Actor_Walk_To_Waypoint(kActorMcCoy, 551, 0, false);
							Async_Actor_Walk_To_Waypoint(kActorGaff, 551, 0, false);
							Actor_Says(kActorGaff, 310, -1);
						}
					}
					Delay(3000);
					if	(Actor_Query_Goal_Number(kActorMaggie) > kGoalMaggieDead) {
						Outtake_Play(kOuttakeEnd7, false, -1);
					}
					Game_Over();
				}
			}
		} else if (Actor_Query_Goal_Number(kActorSteele) == kGoalSteeleWaitingForEnd) {
			Actor_Face_Actor(kActorSteele, kActorMcCoy, true);
			Actor_Says(kActorSteele, 2530, 13);
			Actor_Face_Actor(kActorMcCoy, kActorSteele, true);
			Actor_Says(kActorMcCoy, 6200, 11);
			Actor_Says(kActorSteele, 2540, 15);
			Actor_Says(kActorSteele, 2550, 12);
			Actor_Says(kActorMcCoy, 6205, 14);
			if (Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) < 50) {
				Actor_Says(kActorSteele, 2560, 12);
				Actor_Says(kActorMcCoy, 6210, 14);
				Actor_Says(kActorSteele, 2570, 13);
				Actor_Says(kActorMcCoy, 6215, 14);
				Actor_Says(kActorSteele, 2580, 15);
				Actor_Says(kActorSteele, 2590, 12);
			}
			Async_Actor_Walk_To_Waypoint(kActorMcCoy, 551, 0, false);
			Delay(1000);
			Actor_Says(kActorMcCoy, 6220, -1);
			Delay(3000);
			Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
			Ambient_Sounds_Remove_All_Looping_Sounds(1u);
			Outtake_Play(kOuttakeEnd6, false, -1);
			Game_Over();
		} else { // Ending - talk with Gaff and leaving alone
			Actor_Set_Goal_Number(kActorGaff, kGoalGaffGone);
			Actor_Face_Actor(kActorGaff, kActorMcCoy, true);
			Actor_Says(kActorGaff, 220, 13);
			Actor_Face_Actor(kActorMcCoy, kActorGaff, true);
			Actor_Says(kActorMcCoy, 6245, 11);
			Actor_Says(kActorGaff, 230, 14);
			if (Game_Flag_Query(kFlagMcCoyAttackedReplicants)) {
				Actor_Says(kActorMcCoy, 6250, 15);
				Actor_Says(kActorGaff, 240, 13);
				Delay(1000);
				Actor_Says(kActorMcCoy, 6255, 17);
				Actor_Says(kActorGaff, 250, 14);
				Delay(1000);
			}
			Actor_Says(kActorGaff, 260, 12);
			Actor_Says(kActorMcCoy, 6260, 15);
			Actor_Says(kActorGaff, 270, 13);
			Actor_Says(kActorGaff, 280, 15); 
			Actor_Says(kActorMcCoy, 6265, 14); //00-6265.AUD	How come I don’t feel good about it?
			Actor_Says(kActorGaff, 290, 14);
			Actor_Says(kActorGaff, 300, 15);
			Actor_Says(kActorMcCoy, 6270, 11);
			Async_Actor_Walk_To_Waypoint(kActorMcCoy, 550, 0, false);
			Async_Actor_Walk_To_Waypoint(kActorGaff, 551, 0, false);
			Actor_Says(kActorGaff, 310, -1);
			Delay(3000);
			Outtake_Play(kOuttakeEnd7, false, -1);
#if BLADERUNNER_ORIGINAL_BUGS
#else
			// match behavior of other ending outtakes
			// but do it after the cutscene,
			// since this particular cutscene has no sound
			Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
			Ambient_Sounds_Remove_All_Looping_Sounds(1u);
#endif // BLADERUNNER_ORIGINAL_BUGS
			Game_Over();
		}
		return; // true;
	}

	if (Actor_Query_Goal_Number(kActorSadik) == 414) {
		Loop_Actor_Walk_To_XYZ(kActorMcCoy, -809.0f, 8.26f, -619.0f, 0, false, false, false);
		Actor_Face_Actor(kActorMcCoy, kActorSadik, true);
		Actor_Set_Goal_Number(kActorSadik, 415);
	}

	if (Actor_Query_Goal_Number(kActorSteele) == kGoalSteeleKP05Leave) {
		Actor_Set_Goal_Number(kActorSteele, kGoalSteeleKP06Enter);
	}
}

void SceneScriptKP06::PlayerWalkedOut() {
	if (Game_Flag_Query(kFlagKP06toKP07)
	 && Actor_Query_Goal_Number(kActorSteele) == kGoalSteeleKP06Leave
	) {
		Actor_Set_Goal_Number(kActorSteele, kGoalSteeleWaitingForEnd);
	}
}

void SceneScriptKP06::DialogueQueueFlushed(int a1) {
}

} // End of namespace BladeRunner
