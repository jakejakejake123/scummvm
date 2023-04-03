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

enum kNR01Loops {
	kNR01LoopInshot            = 0,
	kNR01LoopMainLoop          = 1,
	kNR01LoopOutshot           = 3,
	kNR01LoopMainLoopNoSpinner = 4
};

void SceneScriptNR01::InitializeScene() {
	if (Game_Flag_Query(kFlagSpinnerMissing)) {
		Setup_Scene_Information(-153.86f, 23.88f, -570.21f, 402);
	} else if (Game_Flag_Query(kFlagNR01DektoraFall)) {
		Setup_Scene_Information( -416.0f, 31.93f,  -841.0f, 200);
		Actor_Set_Invisible(kActorMcCoy, true);
		Preload(kModelAnimationDektoraInFlamesEndFalling);
	} else if (Game_Flag_Query(kFlagNR03toNR01)) {
		Setup_Scene_Information( -416.0f, 31.93f,  -841.0f, 200);
	} else if (Game_Flag_Query(kFlagUG06toNR01)) {
		Setup_Scene_Information( -270.0f,  4.93f, -1096.0f, 500);
	} else if (Game_Flag_Query(kFlagNR02toNR01)) {
		Setup_Scene_Information(  312.0f, 31.66f,  -901.0f, 700);
	} else {
		// eg. when thrown out
		Setup_Scene_Information(   76.0f, 23.88f,  -109.0f, 966);
	}

	Scene_Exit_Add_2D_Exit(0, 31, 270, 97, 373, 3);
	if (Global_Variable_Query(kVariableChapter) > 3) {
		Scene_Exit_Add_2D_Exit(1, 201, 320, 276, 357, 2);
	}
	Scene_Exit_Add_2D_Exit(2, 583, 262, 639, 365, 1);
	if (Game_Flag_Query(kFlagSpinnerAtNR01)) {
		Scene_Exit_Add_2D_Exit(3, 320, 445, 639, 479, 2);
	}

	Ambient_Sounds_Add_Looping_Sound(kSfxCTRAIN1,  50,  0, 1);
	Ambient_Sounds_Add_Looping_Sound(kSfxMUSBLEED, 22, 55, 1);
	Ambient_Sounds_Add_Sound(kSfxSEXYAD2,  10, 10, 20, 20,  -70, -70, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0480R,  5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0540R,  5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0560R,  5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0870R,  5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0900R,  5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0940R,  5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_1070R,  5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_1080R,  5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_1160R,  5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSPIN2B,   10, 80, 16, 25,    0,   0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSPIN3A,   10, 80, 16, 25,    0,   0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxTHNDER2,  10, 80, 33, 33,    0,   0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxTHNDER3,  10, 80, 33, 33,    0,   0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxTHNDER4,  10, 80, 33, 33,    0,   0, -101, -101, 0, 0);

	if (Game_Flag_Query(kFlagSteeleKnowsBulletBobIsDead)
	 && Actor_Query_Goal_Number(kActorSteele) == kGoalSteeleNR01WaitForMcCoy
	) {
		Game_Flag_Reset(kFlagSpinnerAtNR01);
		Game_Flag_Reset(kFlagSpinnerAtHF01);
	}

	if ( Game_Flag_Query(kFlagSpinnerAtNR01)
	 && !Game_Flag_Query(kFlagArrivedFromSpinner1)
	) {
		if ((!Game_Flag_Query(kFlagNR01VisitedFirstTimeWithSpinner) && Global_Variable_Query(kVariableChapter) == 3)
		    || Random_Query(1, 3) == 1
		) {
			// enhancement: don't always play after first visit
			Scene_Loop_Start_Special(kSceneLoopModeLoseControl, kNR01LoopInshot, false);
		}
		Scene_Loop_Set_Default(kNR01LoopMainLoop);
		Game_Flag_Set(kFlagArrivedFromSpinner1);
	} else if (Game_Flag_Query(kFlagSpinnerAtNR01)
	        && Game_Flag_Query(kFlagArrivedFromSpinner1)
	) {
		Scene_Loop_Set_Default(kNR01LoopMainLoop);
	} else {
		Scene_Loop_Set_Default(kNR01LoopMainLoopNoSpinner);
	}
}

void SceneScriptNR01::SceneLoaded() {
	Obstacle_Object("LAMPBASE01", true);
	Unclickable_Object("LAMPBASE01");
}

bool SceneScriptNR01::MouseClick(int x, int y) {
	if (Actor_Query_Goal_Number(kActorMcCoy) == kGoalMcCoyNR01LayDrugged) {
		Global_Variable_Increment(kVariableNR01GetUpCounter, 4);
		return true;
	}
	return false;
}

bool SceneScriptNR01::ClickedOn3DObject(const char *objectName, bool a2) {
	return false;
}

bool SceneScriptNR01::ClickedOnActor(int actorId) {
	return false;
}

bool SceneScriptNR01::ClickedOnItem(int itemId, bool a2) {
	return false;
}

bool SceneScriptNR01::ClickedOnExit(int exitId) {
	if (exitId == 0) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -380.0f, 31.93f, -841.0f, 0, true, false, false)) {
			if (Global_Variable_Query(kVariableChapter) > 3) {
				Actor_Says(kActorMcCoy, 8522, 12);
			} else {
				Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
				Ambient_Sounds_Remove_All_Looping_Sounds(1u);
				Game_Flag_Set(kFlagNR01toNR03);
				Set_Enter(kSetNR03, kSceneNR03);
			}
		}
		return true;
	}

	if (exitId == 1) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -281.0f, 31.93f, -1061.0f, 0, true, false, false)) {
			Actor_Face_Heading(kActorMcCoy, 45, false);
			Loop_Actor_Travel_Stairs(kActorMcCoy, 3, false, kAnimationModeIdle);
			Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
			Ambient_Sounds_Remove_All_Looping_Sounds(1u);
			Game_Flag_Set(kFlagNR01toUG06);
			Set_Enter(kSetUG06, kSceneUG06);
		}
		return true;
	}

	if (exitId == 2) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, 312.0f, 31.66f, -901.0f, 0, true, false, false)) {
			Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
			Ambient_Sounds_Remove_All_Looping_Sounds(1u);
			Game_Flag_Set(kFlagNR01toNR02);
			Set_Enter(kSetNR02, kSceneNR02);
		}
		return true;
	}

	if (exitId == 3) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, 108.0f, 23.88f, -93.0f, 0, true, false, false)) {
			Game_Flag_Reset(kFlagMcCoyInChinaTown);
			Game_Flag_Reset(kFlagMcCoyInRunciters);
			Game_Flag_Reset(kFlagMcCoyInMcCoyApartment);
			Game_Flag_Reset(kFlagMcCoyInPoliceStation);
			Game_Flag_Reset(kFlagMcCoyInBradburyBuilding);
			Game_Flag_Reset(kFlagMcCoyInHysteriaHall);
			Game_Flag_Reset(kFlagMcCoyInTyrellBuilding);
			Game_Flag_Reset(kFlagMcCoyInNightclubRow);
			switch (Spinner_Interface_Choose_Dest(-1, true)) {
			case kSpinnerDestinationPoliceStation:
				Game_Flag_Set(kFlagMcCoyInPoliceStation);
				Game_Flag_Reset(kFlagSpinnerAtNR01);
				Game_Flag_Reset(kFlagArrivedFromSpinner1);
				Game_Flag_Set(kFlagSpinnerAtPS01);
				Set_Enter(kSetPS01, kScenePS01);
				Scene_Loop_Start_Special(kSceneLoopModeChangeSet, kNR01LoopOutshot, true);
				break;
			case kSpinnerDestinationMcCoysApartment:
				Game_Flag_Set(kFlagMcCoyInMcCoyApartment);
				Game_Flag_Reset(kFlagSpinnerAtNR01);
				Game_Flag_Reset(kFlagArrivedFromSpinner1);
				Game_Flag_Set(kFlagSpinnerAtMA01);
				Set_Enter(kSetMA01, kSceneMA01);
				Scene_Loop_Start_Special(kSceneLoopModeChangeSet, kNR01LoopOutshot, true);
				break;
			case kSpinnerDestinationRuncitersAnimals:
				Game_Flag_Set(kFlagMcCoyInRunciters);
				Game_Flag_Reset(kFlagSpinnerAtNR01);
				Game_Flag_Reset(kFlagArrivedFromSpinner1);
				Game_Flag_Set(kFlagSpinnerAtRC01);
				Set_Enter(kSetRC01, kSceneRC01);
				Scene_Loop_Start_Special(kSceneLoopModeChangeSet, kNR01LoopOutshot, true);
				break;
			case kSpinnerDestinationChinatown:
				Game_Flag_Set(kFlagMcCoyInChinaTown);
				Game_Flag_Reset(kFlagSpinnerAtNR01);
				Game_Flag_Reset(kFlagArrivedFromSpinner1);
				Game_Flag_Set(kFlagSpinnerAtCT01);
				Set_Enter(kSetCT01_CT12, kSceneCT01);
				Scene_Loop_Start_Special(kSceneLoopModeChangeSet, kNR01LoopOutshot, true);
				break;
			case kSpinnerDestinationAnimoidRow:
				Game_Flag_Set(kFlagMcCoyInAnimoidRow);
				Game_Flag_Reset(kFlagSpinnerAtNR01);
				Game_Flag_Reset(kFlagArrivedFromSpinner1);
				Game_Flag_Set(kFlagSpinnerAtAR01);
				Set_Enter(kSetAR01_AR02, kSceneAR01);
				Scene_Loop_Start_Special(kSceneLoopModeChangeSet, kNR01LoopOutshot, true);
				break;
			case kSpinnerDestinationTyrellBuilding:
				Game_Flag_Set(kFlagMcCoyInTyrellBuilding);
				Game_Flag_Reset(kFlagSpinnerAtNR01);
				Game_Flag_Reset(kFlagArrivedFromSpinner1);
				Game_Flag_Set(kFlagSpinnerAtTB02);
				Set_Enter(kSetTB02_TB03, kSceneTB02);
				Scene_Loop_Start_Special(kSceneLoopModeChangeSet, kNR01LoopOutshot, true);
				break;
			case kSpinnerDestinationDNARow:
				Game_Flag_Set(kFlagMcCoyInDNARow);
				Game_Flag_Reset(kFlagSpinnerAtNR01);
				Game_Flag_Reset(kFlagArrivedFromSpinner1);
				Game_Flag_Set(kFlagSpinnerAtDR01);
				Set_Enter(kSetDR01_DR02_DR04, kSceneDR01);
				Scene_Loop_Start_Special(kSceneLoopModeChangeSet, kNR01LoopOutshot, true);
				break;
			case kSpinnerDestinationBradburyBuilding:
				Game_Flag_Set(kFlagMcCoyInBradburyBuilding);
				Game_Flag_Reset(kFlagSpinnerAtNR01);
				Game_Flag_Reset(kFlagArrivedFromSpinner1);
				Game_Flag_Set(kFlagSpinnerAtBB01);
				Set_Enter(kSetBB01, kSceneBB01);
				Scene_Loop_Start_Special(kSceneLoopModeChangeSet, kNR01LoopOutshot, true);
				break;
			case kSpinnerDestinationHysteriaHall:
				Game_Flag_Set(kFlagMcCoyInHysteriaHall);
				Game_Flag_Reset(kFlagSpinnerAtNR01);
				Game_Flag_Set(kFlagSpinnerAtHF01);
				Set_Enter(kSetHF01, kSceneHF01);
				Scene_Loop_Start_Special(kSceneLoopModeChangeSet, kNR01LoopOutshot, true);
				break;
			default:
				Player_Loses_Control();
				Game_Flag_Set(kFlagMcCoyInNightclubRow);
				Game_Flag_Set(kFlagArrivedFromSpinner1);
				Player_Gains_Control();
				break;
			}
		}
		return true;
	}
	return false;
}

bool SceneScriptNR01::ClickedOn2DRegion(int region) {
	if (region == 0
	 && Player_Query_Combat_Mode()
	) {
		Sound_Play(kSfxGUNH1A, 100, 0, 0, 50);
		Actor_Set_Goal_Number(kActorSteele, kGoalSteeleNR01McCoyShotGun);
		Scene_2D_Region_Remove(0);
	}

	if (region == 1
	 && Player_Query_Combat_Mode()
	) {
		Sound_Play(kSfxGUNH1A, 100, 0, 0, 50);
		Actor_Set_Goal_Number(kActorGordo, kGoalGordoNR01Die);
		Actor_Set_Goal_Number(kActorSteele, kGoalSteeleNR01McCoyShotGordo);
		Scene_2D_Region_Remove(1);
		return true;
	}
	return false;

}

void SceneScriptNR01::SceneFrameAdvanced(int frame) {
	if (frame == 61) {
		Sound_Play(kSfxCARDOWN3, 40, 0, 0, 50);
	}

	if (frame == 184) {
		Sound_Play(kSfxCARUP3, 40, 80, 80, 50);
	}
	//return 0;
}

void SceneScriptNR01::ActorChangedGoal(int actorId, int newGoal, int oldGoal, bool currentSet) {
}

void SceneScriptNR01::PlayerWalkedIn() {
	// Added in some dispatcher dialogue.
	if (_vm->_cutContent) {
		if (!Game_Flag_Query(kFlagNR01Visited)) {
			Game_Flag_Set(kFlagNR01Visited);
			ADQ_Add(kActorDispatcher, 410, kAnimationModeTalk); //38-0410.AUD	Any Sector 3 unit in position. We have a 4-15 in progress between an unknown vendor and customer.
			ADQ_Add(kActorDispatcher, 430, kAnimationModeTalk); //38-0430.AUD	The dispute is causing traffic problems in Nightclub Row.
			if (Actor_Query_Intelligence(kActorOfficerLeary) == 60) {
				ADQ_Add(kActorOfficerGrayford, 540, kAnimationModeTalk); //24-0540.AUD	LA, 38 Metro 3. Copied. Responding with an ETA momentarily.
				ADQ_Add(kActorDispatcher, 440, kAnimationModeTalk); //38-0440.AUD	38, Metro 3, LA. Copy.
				ADQ_Add(kActorDispatcher, 450, kAnimationModeTalk); //38-0450.AUD	Be advised. A second caller reports one of the parties is being a possible 51-50.
				ADQ_Add(kActorDispatcher, 460, kAnimationModeTalk); //38-0460.AUD	Use extreme caution on approach.
			}
			if (Actor_Query_Intelligence(kActorOfficerGrayford) == 50) {
				ADQ_Add(kActorOfficerLeary, 330, kAnimationModeTalk); //23-0330.AUD	LA, 38 Metro 3. Copied. Be advised I'll be 10-98 from the scene.
				ADQ_Add(kActorDispatcher, 470, kAnimationModeTalk); //38-0470.AUD	38 Metro 3. 10-4. LA copy. 10-97 in Code 4.	
			}
		}
	}

	if (Game_Flag_Query(kFlagSpinnerMissing)) {
		Actor_Set_Goal_Number(kActorSteele, kGoalSteeleTalkAboutMissingSpinner);
		Game_Flag_Reset(kFlagSpinnerMissing);
		//return true;
		return;
	}

	if (_vm->_cutContent) {
		if (Game_Flag_Query(kFlagHanoiFight)) {
			Delay(2200);
			Actor_Put_In_Set(kActorHanoi, kSetNR01);
			Actor_Set_At_XYZ(kActorHanoi, -327.96, 32.07, -691.79, 256);
			Actor_Face_Heading(kActorMcCoy, 512, false);
			Actor_Face_Heading(kActorMcCoy, 768, true);
			Delay(150);
			Actor_Change_Animation_Mode(kActorMcCoy, kAnimationModeIdle);
			Loop_Actor_Walk_To_Actor(kActorHanoi, kActorMcCoy, 36, false, false);
			Actor_Change_Animation_Mode(kActorHanoi, 4);
			Actor_Face_Actor(kActorHanoi, kActorMcCoy, true);
			Actor_Face_Actor(kActorMcCoy, kActorHanoi, true);
			Sound_Play(kSfxSHOTCOK1, 77, 0, 0, 20);
			Delay(1000);
			Music_Play(kMusicMoraji, 71, 0, 0, -1, kMusicLoopPlayOnce, 2);
			Actor_Change_Animation_Mode(kActorHanoi, 6);
			Ambient_Sounds_Play_Sound(kSfxSHOTGUN1, 97, 0, 0, 20);
			Loop_Actor_Walk_To_XYZ(kActorMcCoy, -173.89, 24.15, -321.90, 0, false, true, false);
			Actor_Face_Actor(kActorHanoi, kActorMcCoy, true);
			Actor_Face_Actor(kActorMcCoy, kActorHanoi, true);
			Sound_Play(kSfxGUNH1A, 100, 0, 0, 50);
			Actor_Change_Animation_Mode(kActorMcCoy, 6);
			Actor_Change_Animation_Mode(kActorHanoi, 21);
			Delay(1000);
			Actor_Change_Animation_Mode(kActorHanoi, 6);
			Ambient_Sounds_Play_Sound(kSfxSHOTGUN1, 97, 0, 0, 20);
			Loop_Actor_Walk_To_XYZ(kActorMcCoy, -155.81, 24.21, -422.68, 0, false, true, false);
			Actor_Face_Actor(kActorHanoi, kActorMcCoy, true);
			Actor_Face_Actor(kActorMcCoy, kActorHanoi, true);
			Sound_Play(kSfxGUNH1A, 100, 0, 0, 50);
			Actor_Change_Animation_Mode(kActorMcCoy, 6);
			Actor_Change_Animation_Mode(kActorHanoi, 21);
			Delay(1000);
			Actor_Change_Animation_Mode(kActorHanoi, 6);
			Ambient_Sounds_Play_Sound(kSfxSHOTGUN1, 97, 0, 0, 20);
			Actor_Change_Animation_Mode(kActorMcCoy, 22);
			Delay(1000);
			Loop_Actor_Walk_To_XYZ(kActorMcCoy, -145.06, 24.35, -629.20, 0, false, true, false);
			Actor_Face_Actor(kActorHanoi, kActorMcCoy, true);
			Actor_Face_Actor(kActorMcCoy, kActorHanoi, true);
			Sound_Play(kSfxGUNH1A, 100, 0, 0, 50);
			Actor_Change_Animation_Mode(kActorMcCoy, 6);
			Actor_Change_Animation_Mode(kActorHanoi, 21);
			Delay(1000);
			Actor_Change_Animation_Mode(kActorHanoi, 6);
			Ambient_Sounds_Play_Sound(kSfxSHOTGUN1, 97, 0, 0, 20);
			Actor_Change_Animation_Mode(kActorMcCoy, 85);
			Delay(1500);
			Loop_Actor_Walk_To_Actor(kActorHanoi, kActorMcCoy, 36, false, false);
			Actor_Change_Animation_Mode(kActorHanoi, 4);
			Sound_Play(kSfxSHOTCOK1, 77, 0, 0, 20);
			Actor_Change_Animation_Mode(kActorMcCoy, 29);
			Delay(1000);
			Sound_Play(kSfxGUNH1A, 100, 0, 0, 50);
			Actor_Change_Animation_Mode(kActorMcCoy, kAnimationModeCombatAim);
			Actor_Change_Animation_Mode(kActorMcCoy, kAnimationModeCombatAttack);
			Actor_Change_Animation_Mode(kActorHanoi, 21);
			Delay(600);
			Sound_Play(kSfxGUNH1A, 100, 0, 0, 50);
			Actor_Change_Animation_Mode(kActorMcCoy, kAnimationModeCombatAim);
			Actor_Change_Animation_Mode(kActorMcCoy, kAnimationModeCombatAttack);
			Actor_Change_Animation_Mode(kActorHanoi, 21);
			Delay(600);
			Sound_Play(kSfxGUNH1A, 100, 0, 0, 50);
			Actor_Change_Animation_Mode(kActorMcCoy, kAnimationModeCombatAim);
			Actor_Change_Animation_Mode(kActorMcCoy, kAnimationModeCombatAttack);
			Actor_Change_Animation_Mode(kActorHanoi, 21);
			Delay(600);
			Sound_Play(kSfxGUNH1A, 100, 0, 0, 50);
			Actor_Change_Animation_Mode(kActorMcCoy, 6);
			Actor_Change_Animation_Mode(kActorHanoi, 48);
			Delay(2000);
			Player_Set_Combat_Mode(false);
			Delay(1000);
			Actor_Says(kActorMcCoy, 1275, -1); //00-1275.AUD	A real pacifist that guy.
			Player_Gains_Control();
			Scene_Exits_Enable();
			Actor_Modify_Friendliness_To_Other(kActorSteele, kActorMcCoy, 2);
			Actor_Modify_Friendliness_To_Other(kActorClovis, kActorMcCoy, -2);
			Actor_Modify_Friendliness_To_Other(kActorGuzza, kActorMcCoy, 2);
			Actor_Modify_Friendliness_To_Other(kActorGaff, kActorMcCoy, 2);
			Game_Flag_Set(kFlagMcCoyRetiredReplicant);
			Game_Flag_Reset(kFlagMcCoyIsHelpingReplicants);
			Game_Flag_Reset(kFlagHanoiFight);
			Game_Flag_Reset(kFlagNR03McCoyThrownOut);
			Game_Flag_Set(kFlagHanoiDead);
			if (Query_Difficulty_Level() != kGameDifficultyEasy) {
				Global_Variable_Increment (kVariableChinyen, 200);
			}
			Player_Gains_Control();
			Scene_Exits_Enable();
		}
	}
			
	if (Actor_Query_Goal_Number(kActorSteele) == kGoalSteeleNR01ConfrontGordo) {
		Scene_Exits_Disable();
		ADQ_Flush();
		Actor_Set_Goal_Number(kActorSteele, kGoalSteeleNR01TalkToGordo);
		Scene_2D_Region_Add(0, 450, 316, 464, 333);
		Scene_2D_Region_Add(1, 233, 321, 240, 362);
		// Action music will play during the confrontation with Gordo.
		if (_vm->_cutContent) {
			Loop_Actor_Walk_To_XYZ(kActorMcCoy, 239.0f, 31.66f, -901.0f, 0, false, false, false);
			Music_Stop(1u);
			Music_Play(kMusicBatl226M, 50, 0, 2, -1, kMusicLoopPlayOnce, 0);
			if (Player_Query_Agenda() == kPlayerAgendaPolite) {
				Player_Loses_Control();
				Actor_Says(kActorGordo, 70, 81);
				Actor_Says(kActorSteele, 990, kAnimationModeTalk); //01-0990.AUD	You got nowhere to go, Gordo! You’re a Replicant.
				Actor_Says(kActorGordo, 80, 82); //02-0080.AUD	Everyone’s a critic.
				Actor_Says(kActorGordo, 90, 81); //02-0090.AUD	I’ve died on stage plenty of times. I’m used to it.
				if (Actor_Query_Intelligence(kActorSteele) == 90) {
					Actor_Says(kActorSteele, 1010, kAnimationModeTalk); //01-1010.AUD	Why don’t you let her go then?
					Actor_Says(kActorGordo, 100, 81); //02-0100.AUD	I didn’t say I was ready.
					Actor_Says(kActorSteele, 1020, kAnimationModeTalk); //01-1020.AUD	This is only gonna end one way, Gordo. You really wanna take an innocent with you?
					Actor_Says(kActorGordo, 110, 82); //02-0110.AUD	Nobody’s innocent down here, lady.
				} else if (Actor_Query_Intelligence(kActorSteele) == 70) {
					Actor_Says(kActorSteele, 1030, kAnimationModeTalk); //01-1030.AUD	I’d rather lose her than the dozen I’d lose if I let you go.
				}
				Actor_Says(kActorSteele, 1040, kAnimationModeTalk); //01-1040.AUD	You’re a killer, pal. And you’re not gonna change. That’s how Tyrell build you.
				Actor_Says(kActorGordo, 1400, 82); //02-1400.AUD	That old killer instinct? That was just a bonus. But, heck, you gotta have it, if you wanna work in this town.
				Actor_Says(kActorGordo, 120, 81); //02-0120.AUD	An entertainer. That’s all I ever was. That’s all I ever wanted to be.
				Actor_Says(kActorGordo, 130, 82); //02-0130.AUD	Curtain call time, baby.
				Actor_Says(kActorGordo, 140, 81); //02-0140.AUD	I’ve waited all my life for my big break. And now you’re gonna get yours.
				Actor_Says(kActorGordo, 150, 81); //02-0150.AUD	(singing) I did it my way!
				Actor_Says(kActorGordo, 160, 82); //02-0160.AUD	(singing) I did it my way!
				Actor_Face_Actor(kActorMcCoy, kActorSteele, true);
				Player_Set_Combat_Mode(true);
				Delay(1500);
				Sound_Play(kSfxGUNH1A, 100, 0, 0, 50);
				Actor_Change_Animation_Mode(kActorMcCoy, 6);	
				Delay(1000);
				Actor_Set_Goal_Number(kActorGordo, kGoalGordoNR01ReleaseHostage);
				Game_Flag_Reset(kFlagSteeleAimingAtGordo);
				Game_Flag_Set(kFlagGordoRanAway);
				Actor_Face_Actor(kActorSteele, kActorMcCoy, true);
				Actor_Says(kActorSteele, 1160, 15); //01-1160.AUD	Dah! What the hell?! Now we’ll never catch it.
				Player_Set_Combat_Mode(false);
				Actor_Says(kActorMcCoy, 3035, 14); //00-3035.AUD	You were gonna shoot!
				Actor_Says(kActorSteele, 1170, 16); //01-1170.AUD	Damn straight!
				Actor_Says(kActorMcCoy, 3040, 15); //00-3040.AUD	What about the hostage?
				if (Actor_Query_Intelligence(kActorSteele) == 70) {
					Actor_Says(kActorSteele, 1180, 16); //01-1180.AUD	A small price to pay to juice that skin-job.
				} else if (Actor_Query_Intelligence(kActorSteele) == 90) {
					Delay(1000);
				}
				Actor_Says(kActorMcCoy, 3045, 15); //00-3045.AUD	You think Bryant is gonna keep you on if you start wasting civilians in the middle of the street?
				Actor_Says(kActorMcCoy, 3055, 15); //00-3055.AUD	I just saved your job, Steele.
				if (Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) < 60) {
					Actor_Says(kActorSteele, 1190, 16); //01-1190.AUD	I can’t believe you took a shot at me!
					Actor_Says(kActorMcCoy, 3060, 15); //00-3060.AUD	At your gun. There’s a difference.
					Actor_Says(kActorSteele, 1200, 16); //01-1200.AUD	Yeah, about three inches!
				} else {
					Delay(2000);
				}
				Actor_Says(kActorSteele, 1210, 14); //01-1210.AUD	We’d better call this in. Maybe we can seal off the sewers and get a search team out here. Your vehicle close by?
				Actor_Clue_Acquire(kActorMcCoy, kClueMcCoyHelpedGordo, true, kActorSteele);
				Actor_Clue_Acquire(kActorGordo, kClueMcCoyHelpedGordo, true, -1);
				Game_Flag_Set(kFlagMcCoyIsHelpingReplicants);
				Game_Flag_Set(kFlagGordoEscaped);
				Actor_Modify_Friendliness_To_Other(kActorSteele, kActorMcCoy, -2);
				Actor_Modify_Friendliness_To_Other(kActorClovis, kActorMcCoy, 2);
				Actor_Modify_Friendliness_To_Other(kActorGuzza, kActorMcCoy, -2);
				Music_Stop(1u);
				Player_Gains_Control();
				Actor_Set_Goal_Number(kActorSteele, kGoalSteeleTalkAboutMissingSpinner);
			} else {
				ADQ_Add(kActorGordo, 70, 81);
				ADQ_Add(kActorSteele, 990, kAnimationModeTalk);
				ADQ_Add(kActorGordo, 80, 82);
				ADQ_Add(kActorGordo, 90, 81);
				if (Actor_Query_Intelligence(kActorSteele) == 90) {
					ADQ_Add(kActorSteele, 1010, kAnimationModeTalk);
					ADQ_Add(kActorGordo, 100, 81);
					ADQ_Add(kActorSteele, 1020, kAnimationModeTalk);
					ADQ_Add(kActorGordo, 110, 82);
				} else if (Actor_Query_Intelligence(kActorSteele) == 70) {
					ADQ_Add(kActorSteele, 1030, kAnimationModeTalk);
				}
				ADQ_Add(kActorSteele, 1040, kAnimationModeTalk);
				ADQ_Add(kActorGordo, 1400, 82); //02-1400.AUD	That old killer instinct? That was just a bonus. But, heck, you gotta have it, if you wanna work in this town.
				ADQ_Add(kActorGordo, 120, 81); //02-0120.AUD	An entertainer. That’s all I ever was. That’s all I ever wanted to be.
				ADQ_Add(kActorGordo, 130, 82); //02-0130.AUD	Curtain call time, baby.
				ADQ_Add(kActorGordo, 140, 81); //02-0140.AUD	I’ve waited all my life for my big break. And now you’re gonna get yours.
				ADQ_Add(kActorGordo, 150, 81); //02-0150.AUD	(singing) I did it my way!
				ADQ_Add(kActorGordo, 160, 82); //02-0160.AUD	(singing) I did it my way!
			}
		} else {
			ADQ_Add(kActorGordo, 70, 81);
			ADQ_Add(kActorSteele, 990, kAnimationModeTalk);
			ADQ_Add(kActorGordo, 80, 82);
			ADQ_Add(kActorGordo, 90, 81);
			ADQ_Add(kActorSteele, 1010, kAnimationModeTalk);
			ADQ_Add(kActorGordo, 100, 81);
			ADQ_Add(kActorSteele, 1020, kAnimationModeTalk);
			ADQ_Add(kActorGordo, 110, 82);
			ADQ_Add(kActorSteele, 1030, kAnimationModeTalk);
			ADQ_Add(kActorSteele, 1040, kAnimationModeTalk);
			ADQ_Add(kActorGordo, 120, 82);
		}
	}

	if (Game_Flag_Query(kFlagNR03McCoyThrownOut)) {
		if (Game_Flag_Query(kFlagNR08TouchedDektora)) {
			ADQ_Add(kActorHanoi, 150, kAnimationModeTalk);
			Game_Flag_Reset(kFlagNR08TouchedDektora);
		}
		Game_Flag_Reset(kFlagNR03McCoyThrownOut);
#if BLADERUNNER_ORIGINAL_BUGS
		// This is an extra call Player_Gains_Control() (McCoy should gain control by his AI script - goal kGoalMcCoyNR01GetUp)
		// or when he's drugged the goal kGoalMcCoyNR01LayDrugged ensures gaining control
		// It causes buggy behavior since it enables control, and by clicking fast the player can skip McCoy's AI script handling
		// of his goal change to kGoalMcCoyNR01ThrownOut, and he can stay invisible, and also spawn at the bottom right of the scene
		Player_Gains_Control();
#endif
		//return true;
		return;
	}

	if (Game_Flag_Query(kFlagNR01DektoraFall)) {
		Delay(3500);
		Set_Enter(kSetNR11, kSceneNR11);
		//return true;
		return;
	}

	if (Game_Flag_Query(kFlagNR03toNR01)) {
		Loop_Actor_Walk_To_XYZ(kActorMcCoy, -380.0f, 31.73f, -841.0f, 0, false, false, false);
		Game_Flag_Reset(kFlagNR03toNR01);
	} else if (Game_Flag_Query(kFlagUG06toNR01)) {
		Loop_Actor_Travel_Stairs(kActorMcCoy, 3, true, kAnimationModeIdle);
		Game_Flag_Reset(kFlagUG06toNR01);
		if (Actor_Query_Goal_Number(kActorSteele) == kGoalSteeleNR01WaitForMcCoy) {
			Actor_Face_Actor(kActorSteele, kActorMcCoy, true);
			// Changed a Steele line based on your friendliness with her.
			if (_vm->_cutContent) {
				// Steele will respond differently if McCoy retired a few reps.
				if (Actor_Clue_Query(kActorMcCoy, kClueMcCoyIncept)) { 
					if (Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) > 59) {
						Actor_Says(kActorSteele, 2640, 12); //01-2640.AUD	Killing time again, Slim?
					} else {
						Actor_Says(kActorSteele, 1440, 13);
					}
				} else {
					Actor_Says(kActorSteele, 2600, kAnimationModeTalk); //-	01-2600.AUD	Hey, Slim!
				}
			} else {
				Actor_Says(kActorSteele, 1440, 13);
			}
			Loop_Actor_Walk_To_Actor(kActorMcCoy, kActorSteele, 48, false, true);
			Actor_Says(kActorMcCoy, 3145, 13);
			if (Global_Variable_Query(kVariableHollowayArrest) != 3) {
				Actor_Says(kActorSteele, 1450, 12);
				Actor_Says(kActorSteele, 1460, 13);
			}
			Actor_Says(kActorMcCoy, 3150, 14);
			Actor_Says(kActorSteele, 1470, 12);
			Actor_Says(kActorSteele, 1480, 13);
			Actor_Says(kActorMcCoy, 3155, 15);
			Actor_Says(kActorSteele, 1500, 16);
			if (_vm->_cutContent) {
				if (Player_Query_Agenda() == kPlayerAgendaSurly 
				|| Player_Query_Agenda() == kPlayerAgendaErratic) {
					Actor_Says(kActorMcCoy, 3160, 12);
				} else {
					Actor_Says(kActorMcCoy, 4130, 13);	//00-4130.AUD	Anything else?
				}	
			} else {
				Actor_Says(kActorMcCoy, 3160, 12);
			}
			// Made it so Crystal also says that Guzza mentioned that McCoy retired a human if you told him about killing the homeless man.
			// Guzza lied and did not cover it up like he said he would and instead used it against McCoy to get him out of the way.
			if (Game_Flag_Query(kFlagSteeleKnowsBulletBobIsDead)
			&& !_vm->_cutContent) {
				Actor_Says(kActorSteele, 1330, 12); //01-1330.AUD	We got a problem, though. There’s an APB out for you.
				Actor_Says(kActorSteele, 1340, 12); //01-1340.AUD	You’ve been shooting civilians? Because that’s what Guzza's saying.
				Actor_Says(kActorSteele, 1350, 12); //01-1350.AUD	He wants to put you on the Machine.
				Actor_Says(kActorMcCoy, 3120, 15); //00-3120.AUD	You’re gonna retire me, Steele?
				Actor_Says(kActorSteele, 1360, 12); //01-1360.AUD	You’re not on my list yet. That means no retirement swag.
				Actor_Says(kActorSteele, 1370, 12); //01-1370.AUD	The uniforms know you’re down here. They already towed your Spinner.
				Actor_Says(kActorMcCoy, 3125, 15); //00-3125.AUD	I was wondering where it went.
				Actor_Says(kActorSteele, 1380, 12); //01-1380.AUD	Is it true, Slim? Did you kill somebody?
				Actor_Says(kActorMcCoy, 3130, 15); //00-3130.AUD	What do you think?
				Actor_Says(kActorSteele, 1390, 12); //01-1390.AUD	I ain’t sure yet. I like to be sure.
				Actor_Says(kActorSteele, 1400, 12); //01-1400.AUD	Something ain’t right. That setup underground? I didn’t see a V-K Machine down there.
				Actor_Says(kActorSteele, 1410, 12); //01-1410.AUD	Baker wasn’t gonna take you downtown and he wasn’t gonna test you.
				Actor_Says(kActorMcCoy, 3135, 15); //00-3135.AUD	No kidding.
				Actor_Says(kActorSteele, 1420, 12);
				Actor_Says(kActorMcCoy, 3140, 15); //00-3140.AUD	Thanks.
				Actor_Says(kActorSteele, 1430, 12); //01-1430.AUD	Don’t thank me yet. The next time you see me... (smacks lips twice) 
				Actor_Set_Goal_Number(kActorSteele, kGoalSteeleImmediatelyStartChapter4);
			} else {
				int v0 = Global_Variable_Query(kVariableHollowayArrest);
				if (v0 == 1) { // Dektora called the fake cops
					Actor_Says(kActorSteele, 1510, 15); //01-1510.AUD	That stripper you interviewed. She’s one of them.
					if (_vm->_cutContent) {
						if (Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) > 59
						&& Actor_Query_Intelligence(kActorSteele) == 90) {
							Actor_Says(kActorSteele, 1520, 14); //01-1520.AUD	Figure it out! She must have made the call to Baker and that other Bozo.
							Actor_Says(kActorMcCoy, 8320, 18); //00-8320.AUD	Really?
							Delay(1000);
							Actor_Says(kActorSteele, 1400, 12); //01-1400.AUD	Something ain’t right. That setup underground? I didn’t see a V-K Machine down there.
							Actor_Says(kActorSteele, 1410, 12); //01-1410.AUD	Baker wasn’t gonna take you downtown and he wasn’t gonna test you.
							Actor_Says(kActorMcCoy, 3135, 15); //00-3135.AUD	No kidding.
							Actor_Clue_Acquire(kActorMcCoy, kClueSuspectDektora, true, kActorSteele);
						}
						Delay(1000);
						Actor_Says(kActorSteele, 1570, 12); //01-1570.AUD	I bet she’s still there, Slim.
						Delay(500);
						if (Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) < 60) {
							Actor_Says(kActorSteele, 1580, 14); //01-1580.AUD	You coming or not?
							Actor_Says(kActorMcCoy, 3170, 13);
						} else {
							Actor_Says(kActorSteele, 1530, 13); //01-1530.AUD	Let’s attend to some business.
						}
					} else {
						Actor_Says(kActorSteele, 1520, 14); //01-1520.AUD	Figure it out! She must have made the call to Baker and that other Bozo.
						Actor_Says(kActorSteele, 1530, 13); //01-1530.AUD	Let’s attend to some business.
					}
					Actor_Set_Goal_Number(kActorSteele, kGoalSteeleNR01GoToNR08);
				} else if (v0 == 2) { // Gordo called the fake cops
					Actor_Says(kActorSteele, 1590, 15);
					Actor_Says(kActorMcCoy, 3195, 14); //00-3195.AUD	Gordo?
					if (_vm->_cutContent) {
						if (Actor_Query_Intelligence(kActorSteele) == 70) {
							Actor_Says(kActorSteele, 1600, 16); //01-1600.AUD	He’s one of them. You should have popped him right there on the stage.
							if (Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)
							|| Player_Query_Agenda() == kPlayerAgendaPolite) {
								Actor_Says(kActorMcCoy, 3200, 13); //00-3200.AUD	Yeah. That would have been good publicity for the Department.
								if (Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) < 60) {
									Actor_Says(kActorSteele, 1610, 17); //01-1610.AUD	That’s your problem, McCoy. You worry too much about what people think.
								}
							} else {
								Actor_Says(kActorMcCoy, 1025, 13); //00-1025.AUD	Absolutely.
							}
						} else if (Actor_Query_Intelligence(kActorSteele) == 90) {
							Actor_Says(kActorSteele, 1660, 17); //01-1660.AUD	You see it anywhere?
							Actor_Says(kActorMcCoy, 7815, 16); //00-7815.AUD	No.
							Actor_Says(kActorSteele, 1690, 15); //01-1690.AUD	I don’t want this one giving us the blow-off.
						}
					} else {
						Actor_Says(kActorMcCoy, 3200, 13); //00-3200.AUD	Yeah. That would have been good publicity for the Department.
						Actor_Says(kActorSteele, 1610, 17); //01-1610.AUD	That’s your problem, McCoy. You worry too much about what people think.
					}
					if (_vm->_cutContent) {
						if (Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) < 60) {
							Actor_Says(kActorSteele, 1620, 15); //01-1620.AUD	Now, excuse me while I go collect.
						} else {
						 	Actor_Says(kActorSteele, 1530, 14);  //01-1530.AUD	Let’s attend to some business.
							Delay(500);
							Actor_Says(kActorSteele, 1630, 14); //01-1630.AUD	You in or out?
							Actor_Says(kActorMcCoy, 3205, 12); //00-3205.AUD	In.
						}
					} else {
						Actor_Says(kActorSteele, 1620, 15); //01-1620.AUD	Now, excuse me while I go collect.
						Actor_Says(kActorSteele, 1630, 14); //01-1630.AUD	You in or out?
						Actor_Says(kActorMcCoy, 3205, 12); //00-3205.AUD	In.
					}
					Actor_Set_Goal_Number(kActorSteele, kGoalSteeleNR01GoToNR02);
				} else if (v0 == 3) { // Lucy called the fake cops
					Actor_Says(kActorSteele, 1540, 15); //01-1540.AUD	That girl, the one from the arcade. She’s one of them.
					Actor_Says(kActorMcCoy, 3175, 13); //00-3175.AUD	You sure? I didn’t get a chance to put her on the Machine.
					Actor_Says(kActorSteele, 1550, 13); //01-1550.AUD	I’ve been sure since I’ve heard about all those dead animals in Runciter’s shop.	
					if (_vm->_cutContent) {
						if (Actor_Query_Intelligence(kActorSteele) == 70) {
							Actor_Says(kActorSteele, 1560, 16); //01-1560.AUD	You should have whacked her when you had the chance.
							Actor_Says(kActorMcCoy, 3180, 15); //00-3180.AUD	Yeah, right in front of all the other children in the arcade. That would have been great publicity.
							Delay(1000);
						} else if (Actor_Query_Intelligence(kActorSteele) == 90) {
							Delay(1000);
						}
					} else {
						Actor_Says(kActorSteele, 1560, 16); //01-1560.AUD	You should have whacked her when you had the chance.
						Actor_Says(kActorMcCoy, 3180, 15); //00-3180.AUD	Yeah, right in front of all the other children in the arcade. That would have been great publicity.
					}
					Actor_Says(kActorSteele, 1570, 12); //01-1570.AUD	I bet she’s still there, Slim.
					if (_vm->_cutContent) {
						if (Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) < 60) {
							Actor_Says(kActorSteele, 1580, 14);  //01-1580.AUD	You coming or not?
							Actor_Says(kActorMcCoy, 3190, 12); //00-3190.AUD	Right behind you.
						} else {
							Actor_Says(kActorSteele, 1530, 13); //01-1530.AUD	Let’s attend to some business.
						}
					}
					Actor_Set_Goal_Number(kActorSteele, kGoalSteeleNR01GoToHF03);
				}
			}
		}
	} else if (Game_Flag_Query(kFlagNR02toNR01)) {
		Loop_Actor_Walk_To_XYZ(kActorMcCoy, 239.0f, 31.66f, -901.0f, 0, false, false, false);
		Game_Flag_Reset(kFlagNR02toNR01);
		if (Actor_Query_Goal_Number(kActorGordo) == kGoalGordoNR01WaitAndAttack) {
			Scene_Exits_Disable();
			// Adjusted code so during the confrontation with Gordo action music plays, McCoy pulls out his gun and yells freeze and Gordo
			// will immediately attack you instead of running away.
			if (_vm->_cutContent) {
				if (!Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
					if (Actor_Clue_Query(kActorMcCoy, kClueStolenCheese)  
					|| Actor_Clue_Query(kActorMcCoy, kClueGordoInterview3)
					|| Actor_Clue_Query(kActorMcCoy, kClueGordosLighterReplicant)
					|| Actor_Clue_Query(kActorMcCoy, kClueCrazylegsInterview1)
					|| Actor_Clue_Query(kActorMcCoy, kClueLichenDogWrapper)) {
						Music_Stop(1u);
						Music_Play(kMusicMoraji, 71, 0, 0, -1, kMusicLoopPlayOnce, 2);
						Player_Set_Combat_Mode(true);
						Actor_Face_Actor(kActorGordo, kActorMcCoy, true);
						Actor_Face_Actor(kActorMcCoy, kActorGordo, true);
						Actor_Says(kActorMcCoy, 8945, 14); //00-8945.AUD	Freeze!
						Actor_Change_Animation_Mode(kActorGordo, 4);
						Delay(1000);
						Actor_Set_Goal_Number(kActorGordo, kGoalGordoNR01Attack);
						Non_Player_Actor_Combat_Mode_On(kActorGordo, kActorCombatStateIdle, true, kActorMcCoy, 3, kAnimationModeCombatIdle, kAnimationModeCombatWalk, kAnimationModeCombatRun, 0, -1, -1, 20, 300, false);
					} else {
						Actor_Face_Actor(kActorGordo, kActorMcCoy, true);
						Actor_Face_Actor(kActorMcCoy, kActorGordo, true);
						Actor_Says(kActorMcCoy, 3970, 14); //00-3970.AUD	Hey.
						Loop_Actor_Walk_To_Actor(kActorGordo, kActorMcCoy, 60, false, true);
						Actor_Face_Actor(kActorGordo, kActorMcCoy, true);
						Actor_Face_Actor(kActorMcCoy, kActorGordo, true);
						Actor_Says(kActorMcCoy, 4270, 14); //00-4270.AUD	I got some more questions for you.
						Actor_Says(kActorGordo, 330, 15); //02-0330.AUD	Man, don’t you got anything better to do than hassle innocent people at their place of work?
						Actor_Says(kActorMcCoy, 7815, 13); //00-7815.AUD	No.
						Delay(1000);
						Actor_Says(kActorGordo, 40, 13);//02-0040.AUD	Unfortunately, my man, I got to book.
						Actor_Says(kActorMcCoy, 7915, 14);	//00-7915.AUD	We're not finished yet.
						Actor_Says(kActorGordo, 570, 14); //02-0570.AUD	Gotta go, daddy-o.
						Actor_Set_Targetable(kActorGordo, false);
						Game_Flag_Set(kFlagGordoRanAway);
						Game_Flag_Set(kFlagGordoEscaped);
						Scene_Exits_Enable();
						Actor_Set_Goal_Number(kActorGordo, kGoalGordoNR01RunAway);
					}
				} else {
					if (Actor_Clue_Query(kActorMcCoy, kClueStolenCheese)  
					|| Actor_Clue_Query(kActorMcCoy, kClueGordoInterview3)
					|| Actor_Clue_Query(kActorMcCoy, kClueGordosLighterReplicant)
					|| Actor_Clue_Query(kActorMcCoy, kClueCrazylegsInterview1)
					|| Actor_Clue_Query(kActorMcCoy, kClueLichenDogWrapper)) {
						Actor_Face_Actor(kActorGordo, kActorMcCoy, true);
						Actor_Face_Actor(kActorMcCoy, kActorGordo, true);
						Player_Set_Combat_Mode(false);
						Actor_Says(kActorMcCoy, 455, 14); //00-0455.AUD	Relax. Nobody's gonna get retired. Okay?
						Loop_Actor_Walk_To_Actor(kActorGordo, kActorMcCoy, 60, false, true);
						Actor_Face_Actor(kActorGordo, kActorMcCoy, true);
						Actor_Face_Actor(kActorMcCoy, kActorGordo, true);
						Actor_Says(kActorMcCoy, 3105, 15); //Instead, I’m gonna let you go. But here’s what you’re gonna do.
						Actor_Says(kActorMcCoy, 3110, 17); //00-3110.AUD	You’re gonna go tell your pal, Clovis, that I’m looking for him.
						Actor_Says(kActorGordo, 250, 13);
						Actor_Says(kActorGordo, 260, 18);
						Actor_Says(kActorMcCoy, 3115, 14);
						Actor_Says(kActorGordo, 270, 15); //02-0270.AUD	Very funny.
						Actor_Says(kActorMcCoy, 3255, 18); //00-3255.AUD	Maybe I’ll see you again.
						Actor_Says(kActorGordo, 10, 15); //02-0010.AUD	Catch you later.
						Actor_Modify_Friendliness_To_Other(kActorSteele, kActorMcCoy, -2);
						Actor_Modify_Friendliness_To_Other(kActorClovis, kActorMcCoy, 2);
						Actor_Modify_Friendliness_To_Other(kActorGuzza, kActorMcCoy, -2);
						Actor_Clue_Acquire(kActorGordo, kClueMcCoyHelpedGordo, true, -1);
						Actor_Set_Targetable(kActorGordo, false);
						Game_Flag_Set(kFlagGordoRanAway);
						Game_Flag_Set(kFlagGordoEscaped);
						Scene_Exits_Enable();
						Actor_Set_Goal_Number(kActorGordo, kGoalGordoNR01RunAway);
					} else {
						Actor_Face_Actor(kActorGordo, kActorMcCoy, true);
						Actor_Face_Actor(kActorMcCoy, kActorGordo, true);
						Actor_Says(kActorMcCoy, 3970, 14); //00-3970.AUD	Hey.
						Loop_Actor_Walk_To_Actor(kActorGordo, kActorMcCoy, 60, false, true);
						Actor_Face_Actor(kActorGordo, kActorMcCoy, true);
						Actor_Face_Actor(kActorMcCoy, kActorGordo, true);
						Actor_Says(kActorMcCoy, 4270, 14); //00-4270.AUD	I got some more questions for you.
						Actor_Says(kActorGordo, 330, 15); //02-0330.AUD	Man, don’t you got anything better to do than hassle innocent people at their place of work?
						Actor_Says(kActorMcCoy, 7815, 13); //00-7815.AUD	No.
						Delay(1000);
						Actor_Says(kActorGordo, 40, 13);//02-0040.AUD	Unfortunately, my man, I got to book.
						Actor_Says(kActorMcCoy, 7915, 14);	//00-7915.AUD	We're not finished yet.
						Actor_Says(kActorGordo, 570, 14); //02-0570.AUD	Gotta go, daddy-o.
						Actor_Set_Targetable(kActorGordo, false);
						Game_Flag_Set(kFlagGordoRanAway);
						Game_Flag_Set(kFlagGordoEscaped);
						Scene_Exits_Enable();
						Actor_Set_Goal_Number(kActorGordo, kGoalGordoNR01RunAway);
					}
				}
			} else {
				Actor_Set_Goal_Number(kActorGordo, kGoalGordoNR01Attack);
				Non_Player_Actor_Combat_Mode_On(kActorGordo, kActorCombatStateIdle, true, kActorMcCoy, 3, kAnimationModeCombatIdle, kAnimationModeCombatWalk, kAnimationModeCombatRun, 0, -1, -1, 20, 300, false);
			}
		}
	} else {
		if (!Game_Flag_Query(kFlagNR01VisitedFirstTimeWithSpinner) && Game_Flag_Query(kFlagArrivedFromSpinner1)) {
			Game_Flag_Set(kFlagNR01VisitedFirstTimeWithSpinner);
		}
		Loop_Actor_Walk_To_XYZ(kActorMcCoy, 48.0f, 23.88f, -189.0f, 0, false, false, false);
	}

	if (Game_Flag_Query(kFlagCrazylegsArrestedTalk)) {
		Game_Flag_Reset(kFlagCrazylegsArrestedTalk);
		Actor_Voice_Over(950, kActorVoiceOver);
		Actor_Voice_Over(960, kActorVoiceOver);
		Actor_Voice_Over(970, kActorVoiceOver);
		Actor_Voice_Over(980, kActorVoiceOver);
	}

	if (Actor_Query_Goal_Number(kActorGordo) == kGoalGordoNR01WaitAndGiveUp) {
		Scene_Exits_Disable();
		Actor_Set_Goal_Number(kActorGordo, kGoalGordoNR01GiveUp);
		if (!Player_Query_Combat_Mode()) {
			if (_vm->_cutContent) {
				if (Actor_Clue_Query(kActorMcCoy, kClueStolenCheese)  
				|| Actor_Clue_Query(kActorMcCoy, kClueGordoInterview3)
				|| Actor_Clue_Query(kActorMcCoy, kClueGordosLighterReplicant)
				|| Actor_Clue_Query(kActorMcCoy, kClueCrazylegsInterview1)
				|| Actor_Clue_Query(kActorMcCoy, kClueLichenDogWrapper)) {
					if (!Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)
					&& Player_Query_Agenda() != kPlayerAgendaPolite) {
						Player_Set_Combat_Mode(true);
					}
				} 
			} else {
				Player_Set_Combat_Mode(true);
			}
		}
	}
	//return false;
	return;
}

void SceneScriptNR01::PlayerWalkedOut() {
	Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
	Ambient_Sounds_Remove_All_Looping_Sounds(1u);
	if (!Game_Flag_Query(kFlagNR01toUG06)
	 && !Game_Flag_Query(kFlagNR01toNR02)
	 && !Game_Flag_Query(kFlagNR01toNR03)
	 && !Game_Flag_Query(kFlagNR01DektoraFall)
	 && !Game_Flag_Query(kFlagChapter4Starting)
	) {
#if BLADERUNNER_ORIGINAL_BUGS
		Outtake_Play(kOuttakeAway1,   true, -1);
		Outtake_Play(kOuttakeInside2, true, -1);
#else
		if (!Game_Flag_Query(kFlagMcCoyInTyrellBuilding)) {
			// don't play an extra outtake when going to Tyrell Building
			// also switch order so inside2 outtake is not last
			Outtake_Play(kOuttakeInside2, true, -1);
			Outtake_Play(kOuttakeAway1,   true, -1);
		}
#endif // BLADERUNNER_ORIGINAL_BUGS
	}
	Game_Flag_Reset(kFlagChapter4Starting);
}

void SceneScriptNR01::DialogueQueueFlushed(int a1) {
	if (_vm->_cutContent) {
		if (!Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
			if (Actor_Query_Goal_Number(kActorSteele) == kGoalSteeleNR01TalkToGordo
			&& Actor_Query_Goal_Number(kActorGordo) != kGoalGordoNR01Die
			&& Actor_Query_Goal_Number(kActorGordo) != kGoalGordoNR01HostageShot
			&& Actor_Query_Goal_Number(kActorGordo) != kGoalGordoNR01HostageDie
			) {
				Actor_Set_Goal_Number(kActorSteele, kGoalSteeleNR01ShootGordo);
			}
		}
	} else {
		if (Actor_Query_Goal_Number(kActorSteele) == kGoalSteeleNR01TalkToGordo
		&& Actor_Query_Goal_Number(kActorGordo) != kGoalGordoNR01Die
		&& Actor_Query_Goal_Number(kActorGordo) != kGoalGordoNR01HostageShot
		&& Actor_Query_Goal_Number(kActorGordo) != kGoalGordoNR01HostageDie
		) {
			Actor_Set_Goal_Number(kActorSteele, kGoalSteeleNR01ShootGordo);
		}
	}
}

} // End of namespace BladeRunner
