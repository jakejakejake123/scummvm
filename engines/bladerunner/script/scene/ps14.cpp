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

void SceneScriptPS14::InitializeScene() {
	if (Game_Flag_Query(kFlagPS03toPS14)) {
		Setup_Scene_Information(-1119.61f, 508.14f, -1208.22f, 315);
		Game_Flag_Reset(kFlagPS03toPS14);
	} else {
		Setup_Scene_Information( -785.45f, 508.14f,  -1652.0f, 315);
	}

	Scene_Exit_Add_2D_Exit(0, 610,  0, 639, 479, 1);
	Scene_Exit_Add_2D_Exit(1,  46, 51, 125, 192, 0);

	Ambient_Sounds_Add_Looping_Sound(kSfxRAIN10, 100, 1, 1);
	Ambient_Sounds_Add_Sound(kSfxCOLONY,  100, 300, 16,  25, 0, 0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSPIN2B,   60, 180, 16,  25, 0, 0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSPIN3A,   60, 180, 16,  25, 0, 0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxTHNDER2,  60, 180, 50, 100, 0, 0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxTHNDER3,  50, 180, 50, 100, 0, 0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxTHNDER4,  50, 180, 50, 100, 0, 0, -101, -101, 0, 0);
}

void SceneScriptPS14::SceneLoaded() {
	Obstacle_Object("CABLES UPPER RIGHT", true);
	Unobstacle_Object("CYLINDER63", true);
	Clickable_Object("CABLES UPPER RIGHT");
	Unclickable_Object("CABLES UPPER RIGHT");
}

bool SceneScriptPS14::MouseClick(int x, int y) {
	return false;
}

bool SceneScriptPS14::ClickedOn3DObject(const char *objectName, bool a2) {
	return false;
}

bool SceneScriptPS14::ClickedOnActor(int actorId) {
	return false;
}

bool SceneScriptPS14::ClickedOnItem(int itemId, bool a2) {
	return false;
}

bool SceneScriptPS14::ClickedOnExit(int exitId) {
	if (exitId == 1) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -2101.0f, 508.14f, -1361.0f, 0, true, false, false)) {
			Actor_Face_Heading(kActorMcCoy, 819, false);
			Loop_Actor_Travel_Stairs(kActorMcCoy, 3, true, kAnimationModeIdle);

			if (Global_Variable_Query(kVariableChapter) == 4
			 && Game_Flag_Query(kFlagUG18GuzzaScene)
			) {
				if (Actor_Clue_Query(kActorMcCoy, kClueBriefcase)) {
					Game_Flag_Set(kFlagMcCoyFreedOfAccusations);
					Actor_Set_Goal_Number(kActorMcCoy, kGoalMcCoyStartChapter5);
				} else {
					Actor_Set_Goal_Number(kActorMcCoy, kGoalMcCoyArrested);
				}
			} else if (Global_Variable_Query(kVariableChapter) > 3) {
				Actor_Says(kActorMcCoy, 8522, 12);
				Actor_Face_Heading(kActorMcCoy, 307, false);
				Loop_Actor_Travel_Stairs(kActorMcCoy, 3, false, kAnimationModeIdle);
			} else {
				Game_Flag_Set(kFlagPS14toPS03);
				Set_Enter(kSetPS03, kScenePS03);
			}
		}
		return true;
	}

	if (exitId == 0) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -785.45f, 508.14f, -1652.0f, 0, true, false, false)) {
			Game_Flag_Set(kFlagPS14toMA07);
			Game_Flag_Reset(kFlagMcCoyInPoliceStation);
			Game_Flag_Set(kFlagMcCoyInMcCoyApartment);
			Set_Enter(kSetMA07, kSceneMA07);
		}
		return true;
	}
	return false;
}

bool SceneScriptPS14::ClickedOn2DRegion(int region) {
	return false;
}

void SceneScriptPS14::SceneFrameAdvanced(int frame) {
}

void SceneScriptPS14::ActorChangedGoal(int actorId, int newGoal, int oldGoal, bool currentSet) {
}

void SceneScriptPS14::PlayerWalkedIn() {
	if (_vm->_cutContent) {
		Game_Flag_Reset(kFlagRachaelWalks);
		Music_Stop(1u);
	}
	if (Game_Flag_Query(kFlagMA07toPS14)) {
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagUG18GuzzaScene)) {
				Actor_Set_At_XYZ(kActorMcCoy, -801.45f, 508.14f, -1596.68f, 0);
				Actor_Face_Heading(kActorMcCoy, 511, false);
			} else {
				Loop_Actor_Walk_To_XYZ(kActorMcCoy, -801.45f, 508.14f, -1596.68f, 0, false, false, false);
			}
		} else {
			Loop_Actor_Walk_To_XYZ(kActorMcCoy, -801.45f, 508.14f, -1596.68f, 0, false, false, false);
		}
		Game_Flag_Reset(kFlagMA07toPS14);
	}
	// Restored the scene for when you encounter Leary and Grayford and you have the Guzza evidence and they take you in and act 5 begins.
	// Set the scene just outside the police station because that made more sense than some random location in China town. Leary and Grayford will
	// be placed in fornt of the police station after your meeting with Guzza and if you don't have the evidence they will arrst you and it will be 
	// a game over.
	if (_vm->_cutContent) {
		if (Game_Flag_Query(kFlagUG18GuzzaScene)
		&& !Game_Flag_Query(kFlagOfficerLearyKilledByBob)
		&& (Global_Variable_Query(kVariableChapter) == 4)) {  
			Actor_Put_In_Set(kActorOfficerGrayford, kSetPS14);
			Actor_Set_At_XYZ(kActorOfficerGrayford, -879.97, 507.86, -1132.41, 0);
			Actor_Put_In_Set(kActorOfficerLeary, kSetPS14);
			Actor_Set_At_XYZ(kActorOfficerLeary, -871.09, 507.83, -1034.80, 0);
			Actor_Face_Actor(kActorOfficerLeary, kActorOfficerGrayford, true); 
			Actor_Face_Actor(kActorOfficerGrayford, kActorOfficerLeary, true);
			Actor_Says(kActorOfficerLeary, 280, kAnimationModeTalk); //23-0280.AUD	Sounds like another nutcase overdosed on too many lichen-dogs.	 
			Actor_Says(kActorOfficerGrayford, 460, kAnimationModeTalk); //24-0460.AUD	Either that or another street punk that sucked one too many sugar cubes.;
			Actor_Face_Actor(kActorMcCoy, kActorOfficerGrayford, true);
			Actor_Face_Actor(kActorOfficerGrayford, kActorMcCoy, true);
			Actor_Face_Actor(kActorOfficerLeary, kActorMcCoy, true);
			Actor_Says(kActorMcCoy, 3970, 15); //00-3970.AUD	Hey.
			Music_Play(kMusicBatl226M, 50, 0, 2, -1, kMusicLoopPlayOnce, 0);
			Actor_Change_Animation_Mode(kActorOfficerLeary, kAnimationModeCombatIdle);
			Actor_Says(kActorOfficerGrayford, 300, kAnimationModeTalk); //24-0300.AUD	Over there!
			Actor_Says(kActorOfficerGrayford, 0, kAnimationModeTalk); //24-0000.AUD	It’s that Rep McCoy! Take it down!
			Actor_Says(kActorOfficerGrayford, 10, kAnimationModeTalk); //24-0010.AUD	Get Guzza on the horn ASAP. We got him cornered.
			if (Actor_Query_Intelligence(kActorOfficerGrayford) == 30) {	
				Actor_Says(kActorOfficerGrayford, 260, kAnimationModeTalk); //24-0260.AUD	We’re gonna nail your ass, McCoy!
			}
			// If McCoy doesn't have the evidence or retired a human he is arrested and it is game over.
			if (!Actor_Clue_Query(kActorMcCoy, kClueBriefcase)) {
				Actor_Change_Animation_Mode(kActorOfficerGrayford, kAnimationModeCombatAttack);
				if (Actor_Query_Friendliness_To_Other(kActorOfficerLeary, kActorMcCoy) < 50) {
					Actor_Change_Animation_Mode(kActorOfficerLeary, kAnimationModeCombatAttack);
				}
				Sound_Play(kSfxSMCAL3, 100, 0, 0, 50);
				Actor_Change_Animation_Mode(kActorMcCoy, kAnimationModeDie);
				Actor_Retired_Here(kActorMcCoy, 12, 12, true, -1);
			} else {
				Actor_Says(kActorMcCoy, 710, 23); //00-0710.AUD	Hold it! I'm not a Replicant, I got proof!	
				if (Actor_Query_Intelligence(kActorOfficerGrayford) == 30) {	 
					Actor_Says(kActorOfficerGrayford, 20, kAnimationModeTalk); //24-0020.AUD	Don’t bullshit, McCoy!
				}
				Actor_Says(kActorMcCoy, 715, 23); //00-0715.AUD	It's all in there!
				if (Actor_Query_Intelligence(kActorOfficerGrayford) == 50) {	 
					Actor_Says(kActorOfficerGrayford, 30, kAnimationModeTalk); //24-0030.AUD	Let’s get the bomb squad out here!
				}
				//The Crystal will vouch for me line will only play if you are on good terms with Crystal meaning not having Lucy and Dektoras global affection goals activated.	 
				if (Global_Variable_Query(kVariableAffectionTowards) != kAffectionTowardsDektora 	 
				&& Global_Variable_Query(kVariableAffectionTowards) != kAffectionTowardsLucy
				&& Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) > 59
				&& !Game_Flag_Query(kFlagMcCoyRetiredHuman)) {
					Actor_Says(kActorMcCoy, 720, kAnimationModeTalk); //00-0720.AUD	Talk to Crystal Steele, she'll vouch for me.
				}
				if (Actor_Query_Intelligence(kActorOfficerGrayford) == 50) {	
					Actor_Says(kActorOfficerGrayford, 40, kAnimationModeTalk); //24-0040.AUD	Drop your gun, put your hands in the air and then we’ll talk.
					Actor_Change_Animation_Mode(kActorMcCoy, 4);
					Delay(400);
					Actor_Change_Animation_Mode(kActorMcCoy, 0);
				}
				Actor_Says(kActorOfficerGrayford, 50, kAnimationModeTalk); //24-0050.AUD	Okay. Come on out!
				Player_Loses_Control();
				Loop_Actor_Walk_To_Actor(kActorMcCoy, kActorOfficerGrayford, 48, true, false);
				Player_Gains_Control();
				if (Actor_Query_Intelligence(kActorOfficerGrayford) == 30) {	
					Actor_Says(kActorOfficerGrayford, 60, kAnimationModeTalk); //24-0060.AUD	If you don’t follow my exact instructions, we’re gonna shred you into a thousand pieces.
					Actor_Says(kActorMcCoy, 725, 13); //00-0725.AUD	Relax! I hear ya.
				}
				Actor_Says(kActorOfficerGrayford, 70, kAnimationModeTalk); //24-0070.AUD	All right, assume the position. On the ground!
				if (Actor_Query_Intelligence(kActorOfficerGrayford) == 30) {	
					Actor_Says(kActorOfficerGrayford, 80, kAnimationModeTalk); //24-0080.AUD	I swear to God, McCoy…
					Actor_Says(kActorOfficerGrayford, 90, kAnimationModeTalk); //24-0090.AUD	if you are lying, if you’ve killed any humans in the process…
					Actor_Says(kActorOfficerGrayford, 100, kAnimationModeTalk); //24-0100.AUD	you gonna wish we disposed you right here and now.
				}
				Actor_Says(kActorOfficerGrayford, 110, kAnimationModeTalk); //24-0110.AUD	Take him in!
				Music_Stop(1u);
				Actor_Set_At_XYZ(kActorOfficerGrayford, 180.04, 11.73, -5.42, 0);
				Game_Flag_Set(kFlagMcCoyFreedOfAccusations);
				// Added in flag for the endgame.
				Game_Flag_Set(kFlagMcCoyIsInnocent);
				Actor_Set_Goal_Number(kActorMcCoy, kGoalMcCoyStartChapter5);
			}
		} else if (Global_Variable_Query(kVariableChapter) == 5) { 
			Actor_Put_In_Set(kActorOfficerGrayford, kScenePS13);
			Actor_Set_At_XYZ(kActorOfficerGrayford, -879.97, 507.86, -1132.41, 0);
		}
	}
	//return false;
}

void SceneScriptPS14::PlayerWalkedOut() {
}

void SceneScriptPS14::DialogueQueueFlushed(int a1) {
}

} // End of namespace BladeRunner
