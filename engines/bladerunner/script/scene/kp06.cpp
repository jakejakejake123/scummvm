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
			Actor_Says(kActorMcCoy, 8610, 15);
			Actor_Says(kActorSadik, 290, kAnimationModeTalk);
		} else if (Actor_Clue_Query(kActorMcCoy, kCluePowerSource)) {
			Actor_Says(kActorSadik, 280, kAnimationModeTalk); //08-0280.AUD	You for real I’m thinking.
			// Removed some lines that didn't belong here.
			Actor_Says(kActorSadik, 290, kAnimationModeTalk); //08-0290.AUD	Go in. You see Clovis. He not got too much time left.
			Actor_Clue_Acquire(kActorSadik, kCluePowerSource, true, kActorMcCoy);
		} else {
			Actor_Says(kActorMcCoy, 2320, kAnimationModeTalk);
			Actor_Says(kActorMcCoy, 2325, kAnimationModeTalk);
			Actor_Says(kActorSadik, 300, kAnimationModeTalk);
			Actor_Says(kActorSadik, 310, kAnimationModeTalk);
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
			Actor_Says(kActorSadik, 280, kAnimationModeTalk);
			Actor_Says(kActorSadik, 290, kAnimationModeTalk);
			Actor_Clue_Acquire(kActorSadik, kCluePowerSource, true, kActorMcCoy);
			Loop_Actor_Walk_To_XYZ(kActorMcCoy, -731.0f, 8.26f, -657.0f, 0, false, true, false);
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
			if (Actor_Query_Goal_Number(kActorSteele) !=  kGoalSteeleGone) {
				if (Game_Flag_Query(kFlagMcCoyAttackedReplicants)) {
					Actor_Put_In_Set(kActorSteele, kSetKP05_KP06);
					Actor_Set_At_XYZ(kActorSteele, -782.15f, 8.26f, -263.64f, 52);
					// If Maggie is alive she will be in the scene.
					if	(Actor_Query_Goal_Number(kActorMaggie) < kGoalMaggieDead) {
						Actor_Put_In_Set(kActorMaggie, kSetKP05_KP06);
						Actor_Set_At_XYZ(kActorMaggie, -802.21, 3.74, -640.55, 659);
						Actor_Face_Actor(kActorMaggie, kActorMcCoy, true);
					}
					Actor_Face_Actor(kActorSteele, kActorMcCoy, true);
					Actor_Says(kActorSteele, 2560, 12); //01-2560.AUD	I gotta admit. I had my doubts about you.
					Actor_Face_Actor(kActorMcCoy, kActorSteele, true);
					Actor_Says(kActorMcCoy, 6210, 14); //00-6210.AUD	What are you saying, Steele? You still wanna put me on the Machine?
					Actor_Says(kActorSteele, 2570, 13); //01-2570.AUD	Take it easy, will ya?
					Actor_Says(kActorMcCoy, 6215, 14); //00-6215.AUD	I plan to. I’m going home.
					Actor_Says(kActorSteele, 2580, 15); //01-2580.AUD	I gotta say, McCoy. You had me fooled. I thought for sure you were a Rep.
					Actor_Says(kActorSteele, 2590, 12); //01-2590.AUD	Don’t get me wrong. I mean, you’re one crazy dude. But I like that.
					// Made it so Crystal or Gaff only mentions McCoy getting a promotion and having a lot of bonuses if he retires enough reps to earn 1500 chinyen.
					if (Actor_Query_Friendliness_To_Other(kActorGaff, kActorMcCoy) > 60) {
						Actor_Says(kActorSteele, 2550, 12); //01-2550.AUD	I think you got a promotion coming. Not to mention all those retirement bonuses.
						Actor_Says(kActorMcCoy, 6205, 14); //00-6205.AUD	As long as I get something like… twenty hours of sleep in the process.
					}
					Async_Actor_Walk_To_Waypoint(kActorMcCoy, 551, 0, false);
					Async_Actor_Walk_To_Waypoint(kActorMaggie, 551, 0, false);
					Delay(1000);
					Actor_Says(kActorMcCoy, 6220, -1); //00-6220.AUD	I’m going home, Steele. I’m finished.
					Delay(3000);
					Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
					Ambient_Sounds_Remove_All_Looping_Sounds(1u);
					Outtake_Play(kOuttakeEnd6, false, -1);
					Game_Over();
				} else if (Actor_Query_Goal_Number(kActorSteele) == kGoalSteeleWaitingForEnd) {
					Actor_Face_Actor(kActorSteele, kActorMcCoy, true);
					Actor_Says(kActorSteele, 2530, 13);
					Actor_Face_Actor(kActorMcCoy, kActorSteele, true);
					Actor_Says(kActorMcCoy, 6200, 11);
					Actor_Says(kActorSteele, 2540, 15);
					Delay(1000);
					if (Actor_Query_Friendliness_To_Other(kActorGaff, kActorMcCoy) > 60) {
						Actor_Says(kActorSteele, 2550, 12); //01-2550.AUD	I think you got a promotion coming. Not to mention all those retirement bonuses.
						Actor_Says(kActorMcCoy, 6205, 14); //00-6205.AUD	As long as I get something like… twenty hours of sleep in the process.
					} 
					Async_Actor_Walk_To_Waypoint(kActorMcCoy, 551, 0, false);
					Delay(1000);
					Actor_Says(kActorMcCoy, 6220, -1);
					Delay(3000);
					Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
					Ambient_Sounds_Remove_All_Looping_Sounds(1u);
					Outtake_Play(kOuttakeEnd6, false, -1);
					Game_Over();
				}
			} else { // Ending - talk with Gaff and leaving alone
				Actor_Set_Goal_Number(kActorGaff, kGoalGaffGone);
				Actor_Face_Actor(kActorGaff, kActorMcCoy, true);
				// If Maggie is alive she will be in the set.
				if (_vm->_cutContent) {
					if	(Actor_Query_Goal_Number(kActorMaggie) < kGoalMaggieDead) {
						Actor_Put_In_Set(kActorMaggie, kSetKP05_KP06);
						Actor_Set_At_XYZ(kActorMaggie, -802.21, 3.74, -640.55, 659);
						Actor_Face_Actor(kActorMaggie, kActorMcCoy, true);
					}
				}
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
				if (Actor_Query_Friendliness_To_Other(kActorGaff, kActorMcCoy) > 60) {
					Actor_Says(kActorGaff, 270, 13); //53-0270.AUD	Uh-uh,  you're a real Blade Runner now. Full retirement bonuses and everything.
				}
				Actor_Says(kActorGaff, 280, 15); 
				Actor_Says(kActorMcCoy, 6265, 14); //00-6265.AUD	How come I don’t feel good about it?
				// If Maggie is alive Gaffs lines about getting a new animal will not play and instead McCoy will say the city is a cess pool instead.
				if (Actor_Query_Goal_Number(kActorMaggie) < kGoalMaggieDead 
				// Made it so Gaff only mentions McCoy buying another dog if he has at least 1500 chinyen.
				|| Global_Variable_Query(kVariableChinyen) < 1200) {
					Actor_Says(kActorGaff, 290, 14); //53-0290.AUD	Who knows?
					Delay(2000);									
					Actor_Says(kActorMcCoy, 8625, 14); //00-8625.AUD	This city is a cesspool.
					Async_Actor_Walk_To_Waypoint(kActorMcCoy, 551, 0, false);
					Async_Actor_Walk_To_Waypoint(kActorMaggie, 551, 0, false);
					Async_Actor_Walk_To_Waypoint(kActorGaff, 551, 0, false);
					Actor_Says(kActorGaff, 310, -1); //53-0310.AUD	Whatever you want to believe, McCoy.
				} else if (Actor_Query_Goal_Number(kActorMaggie) > kGoalMaggieDead 
				&& Global_Variable_Query(kVariableChinyen) >= 1200) { 
					Actor_Says(kActorGaff, 290, 14);
					Actor_Says(kActorGaff, 300, 15);
					Actor_Says(kActorMcCoy, 6270, 11);
					Async_Actor_Walk_To_Waypoint(kActorMcCoy, 550, 0, false);
					Async_Actor_Walk_To_Waypoint(kActorGaff, 551, 0, false);
					Actor_Says(kActorGaff, 310, -1);
				}
				Delay(3000);
				Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
				Ambient_Sounds_Remove_All_Looping_Sounds(1u);
				Outtake_Play(kOuttakeEnd7, false, -1);
				Game_Over();
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
			// If Maggie is alive she will be in the set.
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
