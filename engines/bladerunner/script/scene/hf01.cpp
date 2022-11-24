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

enum kHF01Loops {
	kHF01LoopInshot            = 0,
	kHF01LoopMainLoopSpinner   = 1,
	kHF01LoopDoorAnim          = 3,
	kHF01LoopOutshot           = 4,
	kHF01LoopMainLoopNoSpinner = 5
};

void SceneScriptHF01::InitializeScene() {
	if (Game_Flag_Query(kFlagSpinnerMissing)) {
		Setup_Scene_Information(243.94f, 8.0f, -341.9f, 342);
	} else if (Game_Flag_Query(kFlagHF05toHF01)) {
		Setup_Scene_Information(-202.0f, 0.0f, -619.0f, 407);
	} else if (Game_Flag_Query(kFlagHF03toHF01)) {
		Setup_Scene_Information( 124.0f, 8.0f, -880.0f, 455);
	} else if (Game_Flag_Query(kFlagHF02toHF01)) {
		Setup_Scene_Information( 406.0f, 8.0f, -813.0f, 455);
	} else {
		Setup_Scene_Information( 100.0f, 0.0f, -260.0f,   0);
	}

	Scene_Exit_Add_2D_Exit(0, 81, 226, 169, 321, 0);
	if (!Game_Flag_Query(kFlagHF05PoliceArrived)) {
		Scene_Exit_Add_2D_Exit(1, 304, 239, 492, 339, 0);
		Scene_Exit_Add_2D_Exit(2, 560, 231, 639, 360, 0);
		if (Game_Flag_Query(kFlagSpinnerAtHF01)) {
			Scene_Exit_Add_2D_Exit(3, 0, 311, 66, 417, 2);
			if (_vm->_cutContent) {
				// improve hotspot for Spinner in HF01
				Scene_Exit_Add_2D_Exit(4,  66, 335, 140, 410, 2);
				Scene_Exit_Add_2D_Exit(5, 140, 350, 230, 390, 2);
			}
		}
	}

	Ambient_Sounds_Add_Looping_Sound(kSfxCTRAIN1, 50,   0, 1);
	Ambient_Sounds_Add_Looping_Sound(kSfxARCBED1, 25,   0, 1);
	Ambient_Sounds_Add_Looping_Sound(kSfxRCAMBR1, 60, 100, 1);
	Ambient_Sounds_Add_Sound(kSfx67_0480R,  5,  70, 12,  12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0540R,  5,  70, 12,  12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0560R,  5,  70, 12,  12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0870R,  5,  70, 12,  12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0900R,  5,  70, 12,  12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0940R,  5,  70, 12,  12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_1070R,  5,  70, 12,  12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_1080R,  5,  70, 12,  12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_1160R,  5,  70, 12,  12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSPIN2B,   10, 180, 16,  25,    0,   0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSPIN3A,   10, 180, 16,  25,    0,   0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxTHNDER2,  10, 180, 50, 100,    0,   0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxTHNDER3,  10, 180, 50, 100,    0,   0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxTHNDER4,  10, 180, 50, 100,    0,   0, -101, -101, 0, 0);

	if (Game_Flag_Query(kFlagSpinnerAtHF01)) {
		if (!Game_Flag_Query(kFlagHF02toHF01)
		 && !Game_Flag_Query(kFlagHF03toHF01)
		 && !Game_Flag_Query(kFlagHF05toHF01)
		) {
			Scene_Loop_Start_Special(kSceneLoopModeLoseControl, kHF01LoopInshot, false);
		}
		Scene_Loop_Set_Default(kHF01LoopMainLoopSpinner);
	} else if (Game_Flag_Query(kFlagHF05PoliceArrived)) {
		Scene_Loop_Set_Default(kHF01LoopMainLoopSpinner);
	} else {
		Scene_Loop_Set_Default(kHF01LoopMainLoopNoSpinner);
	}
}

void SceneScriptHF01::SceneLoaded() {
	Obstacle_Object("LOFT41", true);
	if (!Game_Flag_Query(kFlagSpinnerAtHF01)) {
		Unobstacle_Object("OBSTACLE BOX15", true);
	}
}

bool SceneScriptHF01::MouseClick(int x, int y) {
	return false;
}

bool SceneScriptHF01::ClickedOn3DObject(const char *objectName, bool a2) {
	return false;
}

bool SceneScriptHF01::ClickedOnActor(int actorId) {
	int affectionTowardsActor;
	if (Global_Variable_Query(kVariableAffectionTowards) == kAffectionTowardsDektora) {
		affectionTowardsActor = kActorDektora;
	} else if (Global_Variable_Query(kVariableAffectionTowards) == kAffectionTowardsLucy) {
		affectionTowardsActor = kActorLucy;
	} else {
		affectionTowardsActor = -1;
	}

	if (actorId == kActorMia
	 || actorId == kActorMurray
	) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, 504.04f, 8.0f, -242.17f, 12, true, false, false)) {
			ADQ_Flush();
			Actor_Face_Actor(kActorMcCoy, kActorMurray, true);
			if (!Game_Flag_Query(kFlagHF01MurrayMiaTalk)) {
				Actor_Says(kActorMcCoy, 1455, 15); //00-1455.AUD	You guys still battling it out?
				// Made it so Mia, Murray and McCoy face the appropriate character when they talk to them. Any other actor face actor code on this page is for that purpose.
				if (_vm->_cutContent) {
					Actor_Face_Actor(kActorMurray, kActorMcCoy, true);
					Actor_Face_Actor(kActorMia, kActorMcCoy, true);
				}
				Actor_Says(kActorMurray, 40, 13); // 31-0040.AUD	That's what keeps our marriage alive and kicking, Ray. What can we do you for?
				Actor_Says(kActorMcCoy, 1460, 13); //00-1460.AUD	The works.
				if (_vm->_cutContent) {
					Actor_Face_Actor(kActorMurray, kActorMia, true);
				}
				Actor_Says(kActorMurray, 50, 12); //31-0050.AUD	Coming right up.
				if (_vm->_cutContent) {
					Delay(1000);
					Actor_Face_Actor(kActorMurray, kActorMcCoy, true);
					Actor_Change_Animation_Mode(kActorMcCoy, 23);
					Delay(2000);
				}
				Item_Pickup_Spin_Effect(kModelAnimationLichenDogWrapper, 396, 359);
				if (!_vm->_cutContent) {
					Actor_Face_Actor(kActorMia, kActorMcCoy, true);
					Actor_Says(kActorMia, 60, kAnimationModeTalk); //22-0060.AUD	We got a two for one special today, Ray. How about it?
					if (Player_Query_Agenda() != kPlayerAgendaPolite) {
						Actor_Voice_Over(910, kActorVoiceOver);  //99-0910.AUD	The thought of eating another one of those green-dogs made my stomach roll.
						Actor_Says(kActorMcCoy, 1475, 18); //00-1475.AUD	No thanks. But I got a question for you guys.
					} else {
						Actor_Says(kActorMcCoy, 4940, 13); //00-4940.AUD	Okay, let's have it.
						Actor_Change_Animation_Mode(kActorMcCoy, 23);
						Delay(2000);
						Item_Pickup_Spin_Effect(kModelAnimationLichenDogWrapper, 396, 359);
						Actor_Says(kActorMcCoy, 3935, 14); // 00-3935.AUD	Thanks.
					}
				}
				Actor_Says(kActorMurray, 60, 12); //31-0060.AUD	You know anything about politics, Ray? Famous quotes, things like that?
				if (_vm->_cutContent) {
					if (Player_Query_Agenda() != kPlayerAgendaPolite) {
						Actor_Says(kActorMcCoy, 1465, 15);
					} else {
						Actor_Says(kActorMcCoy, 1025, 13); //00-1025.AUD	Absolutely.
					}
				} else {
					Actor_Says(kActorMcCoy, 1465, 15);
				}
				Actor_Face_Actor(kActorMurray, kActorMcCoy, true);
				Actor_Says(kActorMurray, 70, 13);
				if (_vm->_cutContent) {
					if (Player_Query_Agenda() != kPlayerAgendaPolite) {
						Actor_Says(kActorMcCoy, 1470, 14);
					} else {
						Actor_Says(kActorMcCoy, 7980, 19); //00-7980.AUD	Yeah. Maybe.
					}
				} else {
					Actor_Says(kActorMcCoy, 1470, 14);
				}
				Actor_Says(kActorMia, 30, kAnimationModeTalk);
				if (_vm->_cutContent) {
					Actor_Face_Actor(kActorMurray, kActorMia, true);
					Actor_Face_Actor(kActorMia, kActorMurray, true);
				}
				Actor_Says(kActorMurray, 80, 15);
				// Restored some dialogue for Mia and Murray
				if (_vm->_cutContent) {
					Actor_Says(kActorMurray, 90, 15); //31-0090.AUD	Maybe we should consult the Bard. What do you say?
					Actor_Says(kActorMia, 40, kAnimationModeTalk); //22-0040.AUD	I'd say it's a waste of money. Heh, not to mention the fact that the Bard only does poetry.
					Actor_Says(kActorMurray, 100, 15); //31-0100.AUD	Ah, right. I forgot.
					Actor_Says(kActorMia, 50, kAnimationModeTalk); //22-0050.AUD	(snickers) You're forgetting a lot in your old age.
					Actor_Says(kActorMurray, 110, 14); //31-0110.AUD	Right behind you, lady.
				} else {
					Actor_Says(kActorMia, 50, kAnimationModeTalk);
					Actor_Says(kActorMurray, 110, 14);
				}
				Game_Flag_Set(kFlagHF01MurrayMiaTalk);
			} else {
				dialogueWithMiaAndMurray();
			}
			return true;
		}
		return false;
	}

	if (affectionTowardsActor != -1
	 && actorId == affectionTowardsActor
	) {
		if (!Loop_Actor_Walk_To_Actor(kActorMcCoy, actorId, 28, true, false)) {
			if (Actor_Query_Goal_Number(affectionTowardsActor) == 599) {
				Actor_Says(kActorMcCoy, 8630, 13);
				return true;
			}
			if (_vm->_cutContent) {
				if (Global_Variable_Query(kVariableChapter) == 5
				&& (Actor_Clue_Query(kActorMcCoy, kCluePhoneCallDektora1)
				|| Actor_Clue_Query(kActorMcCoy, kCluePhoneCallLucy1)
				)
				&& !Game_Flag_Query(kFlagCrazylegsArrested)
				&&  Actor_Query_Goal_Number(kActorCrazylegs) != kGoalCrazyLegsLeavesShowroom
				&& !Game_Flag_Query(kFlagHF01TalkToLovedOne)
				) {
					Game_Flag_Set(kFlagHF01TalkToLovedOne);
					Actor_Face_Actor(kActorMcCoy, affectionTowardsActor, true);
					Actor_Face_Actor(affectionTowardsActor, kActorMcCoy, true);
					if (affectionTowardsActor == kActorDektora) {
						talkWithDektora();
					} else if (affectionTowardsActor == kActorLucy) {
						talkWithLucy();
					}
					Async_Actor_Walk_To_XYZ(affectionTowardsActor, -175.0f, 8.0f, -617.0f, 0, false);
					Loop_Actor_Walk_To_XYZ(kActorMcCoy, -137.0f, 8.0f, -577.0f, 0, false, false, true);
					Game_Flag_Set(kFlagHF01toHF05);
					Set_Enter(kSetHF05, kSceneHF05);
				}
			} else {
				if (Global_Variable_Query(kVariableChapter) == 5
				&& (Actor_Clue_Query(kActorMcCoy, kCluePhoneCallDektora1)
				|| Actor_Clue_Query(kActorMcCoy, kCluePhoneCallLucy1)
				)
				&& !Game_Flag_Query(kFlagCrazylegsArrested)
				&&  Actor_Query_Goal_Number(kActorCrazylegs) != kGoalCrazyLegsLeavesShowroom
				&&  Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)
				&& !Game_Flag_Query(kFlagHF01TalkToLovedOne)
				) {
					Game_Flag_Set(kFlagHF01TalkToLovedOne);
					Actor_Face_Actor(kActorMcCoy, affectionTowardsActor, true);
					Actor_Face_Actor(affectionTowardsActor, kActorMcCoy, true);
					if (affectionTowardsActor == kActorDektora) {
						talkWithDektora();
					} else if (affectionTowardsActor == kActorLucy) {
						talkWithLucy();
					}
					Async_Actor_Walk_To_XYZ(affectionTowardsActor, -175.0f, 8.0f, -617.0f, 0, false);
					Loop_Actor_Walk_To_XYZ(kActorMcCoy, -137.0f, 8.0f, -577.0f, 0, false, false, true);
					Game_Flag_Set(kFlagHF01toHF05);
					Set_Enter(kSetHF05, kSceneHF05);
				}
			}
		}
	}
	return false;
}

bool SceneScriptHF01::ClickedOnItem(int itemId, bool a2) {
	return false;
}

bool SceneScriptHF01::ClickedOnExit(int exitId) {
	if (exitId == 0) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -202.0f, 8.0f, -619.0f, 0, true, false, false)) {
			Game_Flag_Set(kFlagHF01toHF05);
			Set_Enter(kSetHF05, kSceneHF05);
		}
		return true;
	}

	if (exitId == 1) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, 124.0f, 8.0f, -724.0f, 0, true, false, false)) {
			Loop_Actor_Walk_To_XYZ(kActorMcCoy, 124.0f, 8.0f, -880.0f, 0, false, false, false);
			Game_Flag_Set(kFlagHF01toHF03);
			Set_Enter(kSetHF03, kSceneHF03);
		}
		return true;
	}

	if (exitId == 2) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, 406.0f, 8.0f, -717.0f, 0, true, false, false)) {
			Loop_Actor_Walk_To_XYZ(kActorMcCoy, 406.0f, 8.0f, -813.0f, 0, false, false, false);
			Game_Flag_Set(kFlagHF01toHF02);
			Set_Enter(kSetHF02, kSceneHF02);
		}
		return true;
	}

	if (exitId == 3
	    || (_vm->_cutContent && (exitId == 4 || exitId == 5))) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, 100.0f, 0.0f, -260.0f, 0, true, false, false)) {
			Game_Flag_Reset(kFlagMcCoyInChinaTown);
			Game_Flag_Reset(kFlagMcCoyInRunciters);
			Game_Flag_Reset(kFlagMcCoyInMcCoyApartment);
			Game_Flag_Reset(kFlagMcCoyInPoliceStation);
			Game_Flag_Reset(kFlagMcCoyInBradburyBuilding);
			Game_Flag_Reset(kFlagMcCoyInHysteriaHall);
			int spinnerDest = Spinner_Interface_Choose_Dest(kHF01LoopDoorAnim, false);
			switch (spinnerDest) {
			case kSpinnerDestinationPoliceStation:
				Game_Flag_Set(kFlagMcCoyInPoliceStation);
				Game_Flag_Reset(kFlagSpinnerAtHF01);
				Game_Flag_Set(kFlagSpinnerAtPS01);
				Set_Enter(kSetPS01, kScenePS01);
				Scene_Loop_Start_Special(kSceneLoopModeChangeSet, kHF01LoopOutshot, true);
				break;
			case kSpinnerDestinationMcCoysApartment:
				Game_Flag_Set(kFlagMcCoyInMcCoyApartment);
				Game_Flag_Reset(kFlagSpinnerAtHF01);
				Game_Flag_Set(kFlagSpinnerAtMA01);
				Set_Enter(kSetMA01, kSceneMA01);
				Scene_Loop_Start_Special(kSceneLoopModeChangeSet, kHF01LoopOutshot, true);
				break;
			case kSpinnerDestinationRuncitersAnimals:
				Game_Flag_Set(kFlagMcCoyInRunciters);
				Game_Flag_Reset(kFlagSpinnerAtHF01);
				Game_Flag_Set(kFlagSpinnerAtRC01);
				Set_Enter(kSetRC01, kSceneRC01);
				Scene_Loop_Start_Special(kSceneLoopModeChangeSet, kHF01LoopOutshot, true);
				break;
			case kSpinnerDestinationChinatown:
				Game_Flag_Set(kFlagMcCoyInChinaTown);
				Game_Flag_Reset(kFlagSpinnerAtHF01);
				Game_Flag_Set(kFlagSpinnerAtCT01);
				Set_Enter(kSetCT01_CT12, kSceneCT01);
				Scene_Loop_Start_Special(kSceneLoopModeChangeSet, kHF01LoopOutshot, true);
				break;
			case kSpinnerDestinationTyrellBuilding:
				Game_Flag_Set(kFlagMcCoyInTyrellBuilding);
				Game_Flag_Reset(kFlagSpinnerAtHF01);
				Game_Flag_Set(kFlagSpinnerAtTB02);
				Set_Enter(kSetTB02_TB03, kSceneTB02);
				Scene_Loop_Start_Special(kSceneLoopModeChangeSet, kHF01LoopOutshot, true);
				break;
			case kSpinnerDestinationAnimoidRow:
				Game_Flag_Set(kFlagMcCoyInAnimoidRow);
				Game_Flag_Reset(kFlagSpinnerAtHF01);
				Game_Flag_Set(kFlagSpinnerAtAR01);
				Set_Enter(kSetAR01_AR02, kSceneAR01);
				Scene_Loop_Start_Special(kSceneLoopModeChangeSet, kHF01LoopOutshot, true);
				break;
			case kSpinnerDestinationDNARow:
				Game_Flag_Set(kFlagMcCoyInDNARow);
				Game_Flag_Reset(kFlagSpinnerAtHF01);
				Game_Flag_Set(kFlagSpinnerAtDR01);
				Set_Enter(kSetDR01_DR02_DR04, kSceneDR01);
				Scene_Loop_Start_Special(kSceneLoopModeChangeSet, kHF01LoopOutshot, true);
				break;
			case kSpinnerDestinationBradburyBuilding:
				Game_Flag_Set(kFlagMcCoyInBradburyBuilding);
				Game_Flag_Reset(kFlagSpinnerAtHF01);
				Game_Flag_Set(kFlagSpinnerAtBB01);
				Set_Enter(kSetBB01, kSceneBB01);
				Scene_Loop_Start_Special(kSceneLoopModeChangeSet, kHF01LoopOutshot, true);
				break;
			case kSpinnerDestinationNightclubRow:
				Game_Flag_Set(kFlagMcCoyInNightclubRow);
				Game_Flag_Reset(kFlagSpinnerAtHF01);
				Game_Flag_Set(kFlagSpinnerAtNR01);
				Set_Enter(kSetNR01, kSceneNR01);
				Scene_Loop_Start_Special(kSceneLoopModeChangeSet, kHF01LoopOutshot, true);
				break;
			default:
				Game_Flag_Set(kFlagMcCoyInHysteriaHall);
				Loop_Actor_Walk_To_XYZ(kActorMcCoy, 100.0f, 0.0f, -300.0f, 0, true, false, false);				
				break;
			}
		}
		return true;
	}
	return false;
}

bool SceneScriptHF01::ClickedOn2DRegion(int region) {
	return false;
}

void SceneScriptHF01::SceneFrameAdvanced(int frame) {
	if (frame == 10) {
		Sound_Play(kSfxCARDOWN3, 40, 0, 0, 50);
	}

	if (frame == 72
	 || frame == 193
	) {
		Sound_Play(kSfxSPINOPN4, 100, -50, -50, 50);
	}

	if (frame == 88
	 || frame == 214
	) {
		Sound_Play(kSfxSPINCLS1, 100, -50, -50, 50);
	}

	if (frame == 242) {
		Sound_Play(kSfxCARUP3,    40, -50, 80, 50);
	}

	if (Actor_Query_Goal_Number(kActorMurray) == 1) {
		Actor_Set_Goal_Number(kActorMurray, 0);
	}
}

void SceneScriptHF01::ActorChangedGoal(int actorId, int newGoal, int oldGoal, bool currentSet) {
}

void SceneScriptHF01::PlayerWalkedIn() {
	// Reworked the encounter with Zuben in act 4. Made it so it is an actually that plays if Zuben in alive and you go to Hysteria hall in act 4.
	// This encounter with Zuben in the original game was way too cryptic in the origianl game. Not only does Zuben have to be alive and you have to go to Hysteria 
	// hall there is a high chance that he won't appear at all. Heck even though I knew what to do he almost never showed up so this change feels neccessary 
	// especially for a scene where McCoy learns some very important information.
	if (_vm->_cutContent) {
		Music_Stop(1u);
	}
	if (_vm->_cutContent) {
		if (!Game_Flag_Query(kFlagZubenTalkAct4)
		&& (Actor_Query_Goal_Number(kActorZuben) < kGoalZubenGone) 
		&& (Global_Variable_Query(kVariableChapter) == 4)) {
			Actor_Put_In_Set(kActorZuben, kSetHF01);
			Actor_Set_At_XYZ(kActorZuben, 500.07f, -0.01f, -205.43f, 0);
			Actor_Face_Current_Camera(kActorZuben, true);
			Actor_Face_Actor(kActorMcCoy, kActorZuben, true);
			Delay(1000);
			Actor_Says(kActorMcCoy, 3970, 14); //00-3970.AUD	Hey.
			Player_Loses_Control();
			Loop_Actor_Walk_To_Actor(kActorMcCoy, kActorZuben, 24, false, true);
			Actor_Face_Actor(kActorZuben, kActorMcCoy, true);
			Actor_Says(kActorMcCoy, 8910, 11); //00-8910.AUD	Hey you.
			Actor_Says(kActorZuben, 140, 14); //19-0140.AUD	Stay away!
			Actor_Says(kActorMcCoy, 7280, 11); //00-7280.AUD	You remember me?
			Actor_Says(kActorZuben, 150, 15); //19-0150.AUD	You chased Zuben.
			if (Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
				Actor_Says(kActorMcCoy, 7285, 12); //00-7285.AUD	But I didn't kill you, did I?
			} else {
				Actor_Says(kActorMcCoy, 2790, 18); //00-2790.AUD	Uh-huh.
			}
			Actor_Says(kActorZuben, 160, 13); //19-0160.AUD	You following me?
			Actor_Says(kActorMcCoy, 7305, 15); //00-7305.AUD	No, it's just a coincidence.
			Delay(1000);
			if (Actor_Query_Goal_Number(kActorLucy) < kGoalLucyGone) {
				Actor_Says(kActorMcCoy, 7295, 11); //00-7295.AUD	The girl. I need to know where's the girl.
				Actor_Says(kActorZuben, 200, 12); //19-0200.AUD	Girl?
				Actor_Says(kActorMcCoy, 7315, 16); //00-7315.AUD	Lucy.
				Actor_Says(kActorZuben, 210, 12); //19-0210.AUD	She daughter. She with Clovis.
				Delay(1000);
				Actor_Says(kActorZuben, 220, 14); //19-0220.AUD	You not hurt her.
				if (Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
					Actor_Says(kActorMcCoy, 7940, 13);	//00-7940.AUD	Right.
					Delay(1000);
				}
				Actor_Says(kActorMcCoy, 7320, 17); //00-7320.AUD	Is she a Replicant?
				if (Game_Flag_Query(kFlagLucyIsReplicant)) {
					Actor_Says(kActorZuben, 230, 14); //19-0230.AUD	Daughter sick. Only four years to live. Four years. Daughter Zuben whole family.
					if (Actor_Clue_Query(kActorMcCoy, kClueLucyIncept)
					|| Actor_Clue_Query(kActorMcCoy, kClueVKLucyReplicant)) {
						Actor_Says(kActorMcCoy, 7325, 17); //00-7325.AUD	I know.
					}
					Actor_Says(kActorZuben, 240, 15); //19-0240.AUD	But Clovis he fix.
					if (Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
						Actor_Says(kActorMcCoy, 7330, 16); //00-7330.AUD	Let's hope so.
					}
					Actor_Clue_Acquire(kActorMcCoy, kClueZubenTalksAboutLucy1, false, kActorZuben);
				} else {
					Actor_Says(kActorZuben, 250, 14); //19-0250.AUD	Daughter not like me.
					if (!Actor_Clue_Query(kActorMcCoy, kClueVKLucyHuman)) {
						Actor_Says(kActorMcCoy, 7335, 14); //00-7335.AUD	She's not a Replicant?
					}
					Actor_Says(kActorZuben, 260, 15); //19-0260.AUD	She good girl. She stay with Clovis.
					Actor_Says(kActorMcCoy, 7340, 16); //00-7340.AUD	I know.
					Actor_Says(kActorZuben, 340, 15); //19-0340.AUD	You promise no hurt.
					if (Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {	
						Actor_Says(kActorMcCoy, 7345, 12); //00-7345.AUD	Right, no hurt. No hurt anymore.
					} else {
						Delay(2000);
					}
					Actor_Clue_Acquire(kActorMcCoy, kClueZubenTalksAboutLucy2, false, kActorZuben);
				}
			}
			Delay(1000);
			if (!Actor_Clue_Query(kActorMcCoy, kClueLucyInterview)) {
				Actor_Says(kActorMcCoy, 7300, 13); //00-7300.AUD	Did you kill the animals?
			} else {
				Actor_Says(kActorMcCoy, 7355, 14); //00-7355.AUD	All those animals died.
			}
			Actor_Says(kActorZuben, 270, 15); //19-0270.AUD	Because he bad.
			Actor_Says(kActorMcCoy, 7350, 14);	//00-7350.AUD	Runciter?
			Actor_Says(kActorZuben, 280, 12); //19-0280.AUD	He not pay. Bad to Lucy. Bad to everybody. Make people starve.
			Actor_Says(kActorZuben, 290, 15); //19-0290.AUD	He made Lucy do bad things. Lucy hurt. Clovis more angry.
			Actor_Says(kActorZuben, 300, 14); //19-0300.AUD	Girl was forced to do bad things Off-World. Clovis thought Terra better.
			Actor_Says(kActorZuben, 310, 13); //19-0310.AUD	But Terra's no better for young girls. Runciter bad to Lucy.
			Delay(2000);
			if (Actor_Query_Goal_Number(kActorLucy) != kGoalLucyGone) {
				if (Player_Query_Agenda() == kPlayerAgendaSurly 
				|| Player_Query_Agenda() == kPlayerAgendaErratic) {
					Actor_Says(kActorMcCoy, 7365, 12);	//00-7365.AUD	You should have killed him.
				} else {
					Actor_Says(kActorMcCoy, 7360, 11); //00-7360.AUD	Did he do things to Lucy?
				}
			}
			Actor_Says(kActorZuben, 320, 12); //19-0320.AUD	Clovis say Runciter love animals. Runciter still alive so he hurt now. Know what pain is.
			Actor_Says(kActorZuben, 330, 12); //19-0330.AUD	Kill him, he not hurt. Just dead.
			Actor_Clue_Acquire(kActorMcCoy, kClueZubensMotive, false, kActorZuben);
			Actor_Says(kActorMcCoy, 7290, 12); //00-7290.AUD	Listen it's very important I talked to Clovis.
			Actor_Says(kActorZuben, 180, 15); //19-0180.AUD	No way. You enemy of Clovis.
			if (Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
				Actor_Says(kActorMcCoy, 7310, 16); //00-7310.AUD	No, I'm trying to help him and you.
				Actor_Says(kActorZuben, 190, 15); //19-0190.AUD	We do good without you. Do good without anybody.
				Actor_Says(kActorMcCoy, 5065, 18); //00-5065.AUD	Is that right?
			}
			Actor_Says(kActorZuben, 170, 14); //19-0170.AUD	Now I go.
			Loop_Actor_Walk_To_XYZ(kActorZuben,  200.17, 0.29, -190.72 , 0, true, false, false);
			Player_Gains_Control();
			Game_Flag_Set(kFlagZubenTalkAct4);
		}
	}
	if (!_vm->_cutContent) {
		if (Game_Flag_Query(kFlagHF05PoliceArrived)) {
			ADQ_Flush();
			ADQ_Add(kActorOfficerGrayford, 280, kAnimationModeTalk);
			Actor_Put_In_Set(kActorOfficerLeary, kSetHF01);
			Actor_Set_At_XYZ(kActorOfficerLeary, 8.2f, 8.0f, -346.67f, 1021);
			Actor_Put_In_Set(kActorOfficerGrayford, kSetHF01);
			Actor_Set_At_XYZ(kActorOfficerGrayford, 51.21f, 8.0f, -540.78f, 796);
			Non_Player_Actor_Combat_Mode_On(kActorOfficerLeary, kActorCombatStateUncover, true, kActorMcCoy, 4, kAnimationModeCombatIdle, kAnimationModeCombatWalk, kAnimationModeCombatRun, 0, 0, 0, 100, 300, false);
			Non_Player_Actor_Combat_Mode_On(kActorOfficerGrayford, kActorCombatStateUncover, true, kActorMcCoy, 4, kAnimationModeCombatIdle, kAnimationModeCombatWalk, kAnimationModeCombatRun, 0, 0, 0, 100, 300, false);	
		}
	}

	if (!Game_Flag_Query(kFlagCrazylegsArrested)
	 &&  Actor_Query_Goal_Number(kActorCrazylegs) != kGoalCrazyLegsLeavesShowroom
	) {
		if (Actor_Clue_Query(kActorMcCoy, kCluePhoneCallLucy1)
		 && Global_Variable_Query(kVariableAffectionTowards) == kAffectionTowardsLucy
		 && Actor_Query_Goal_Number(kActorLucy) != kGoalLucyGone
		) {
			Actor_Put_In_Set(kActorLucy, kSetHF01);
			Actor_Set_At_XYZ(kActorLucy, -5.0f, 8.0f, -622.0f, 419);
			Actor_Set_Targetable(kActorLucy, true);
		} else if (Actor_Clue_Query(kActorMcCoy, kCluePhoneCallDektora1)
		        && Global_Variable_Query(kVariableAffectionTowards) == kAffectionTowardsDektora
		        && Actor_Query_Goal_Number(kActorDektora) != kGoalDektoraGone
		) {
			Actor_Put_In_Set(kActorDektora, kSetHF01);
			Actor_Set_At_XYZ(kActorDektora, -5.0f, 8.0f, -622.0f, 419);
			Actor_Set_Targetable(kActorDektora, true);
		}
	}

	if (Game_Flag_Query(kFlagSpinnerMissing)) {
		Actor_Set_Goal_Number(kActorSteele, kGoalSteeleTalkAboutMissingSpinner);
		Game_Flag_Reset(kFlagSpinnerMissing);
		//return true;
		return;
	}
	// After McCoy shoots Crazylegs and appears outside he will say a couple of things and receive 200 chinyen.
	if (_vm->_cutContent) {
		if (Game_Flag_Query(kFlagCrazylegsShot)) {
			Game_Flag_Reset(kFlagCrazylegsArrestedTalk);
			if (Game_Flag_Query(kFlagCrazylegsIsReplicant)) {
				if (Player_Query_Agenda() != kPlayerAgendaSurly 
				&& Player_Query_Agenda() != kPlayerAgendaErratic) {
					Actor_Voice_Over(1410, kActorVoiceOver); //99-1410.AUD	I’d retired another Replicant so more money was headed my way but I didn’t feel so good about it.
					Actor_Voice_Over(1670, kActorVoiceOver); //99-1670.AUD	Still it was a hell of a way to go.
				} else {
					Actor_Voice_Over(920, kActorVoiceOver); //99-0920.AUD	Easy money.
				}
				Actor_Modify_Friendliness_To_Other(kActorSteele, kActorMcCoy, 2);
				Actor_Modify_Friendliness_To_Other(kActorClovis, kActorMcCoy, -2);
				Actor_Modify_Friendliness_To_Other(kActorGuzza, kActorMcCoy, 2);
				Actor_Modify_Friendliness_To_Other(kActorGaff, kActorMcCoy, 2);
				Actor_Set_Goal_Number(kActorCrazylegs, kGoalCrazyLegsLeavesShowroom);
				Game_Flag_Reset(kFlagMcCoyIsHelpingReplicants);
				Game_Flag_Reset(kFlagCrazylegsShot);
				if (Query_Difficulty_Level() != kGameDifficultyEasy) {
					Global_Variable_Increment (kVariableChinyen, 200);
				}		
			} else {
				if (Player_Query_Agenda() != kPlayerAgendaSurly 
				&& Player_Query_Agenda() != kPlayerAgendaErratic) {
					Actor_Voice_Over(2410, kActorVoiceOver); //99-2410.AUD	He went down too easy. Just one shot.
					Actor_Voice_Over(2420, kActorVoiceOver);
					Delay(1000);
					Outtake_Play(kOuttakeAway1, true, -1);
					Actor_Set_Goal_Number(kActorMcCoy, kGoalMcCoyArrested);
				} else {
					Actor_Voice_Over(2410, kActorVoiceOver); //99-2410.AUD	He went down too easy. Just one shot.
					Delay(1000);
					Actor_Voice_Over(2100, kActorVoiceOver); //99-2100.AUD	I'd crossed the line.
					Actor_Voice_Over(2120, kActorVoiceOver); //99-2120.AUD	I didn't have a lot of time and my options were pretty lousy.
					Actor_Voice_Over(2130, kActorVoiceOver);
					Actor_Set_Goal_Number(kActorCrazylegs, kGoalCrazyLegsLeavesShowroom);
					Game_Flag_Reset(kFlagCrazylegsShot);
					Game_Flag_Set(kFlagMcCoyRetiredHuman);
					Actor_Modify_Friendliness_To_Other(kActorClovis, kActorMcCoy, 2);
					Actor_Modify_Friendliness_To_Other(kActorSteele, kActorMcCoy, -2);
					Actor_Modify_Friendliness_To_Other(kActorGuzza, kActorMcCoy, -2);
				}
			}
		}
	}

	if (Game_Flag_Query(kFlagHF03toHF01)) {
		Loop_Actor_Walk_To_XYZ(kActorMcCoy, 124.0f, 8.0f, -724.0f, 0, true, false, false);
	} else if (Game_Flag_Query(kFlagHF02toHF01)) {
		Loop_Actor_Walk_To_XYZ(kActorMcCoy, 406.0f, 8.0f, -717.0f, 0, true, false, false);
	} else if (!Game_Flag_Query(kFlagHF05toHF01)) {
		Loop_Actor_Walk_To_XYZ(kActorMcCoy, 100.0f, 0.0f, -300.0f, 0, true, false, false);
	}

	if (Game_Flag_Query(kFlagCrazylegsArrestedTalk)) {
		Game_Flag_Reset(kFlagCrazylegsArrestedTalk);
		Actor_Voice_Over(950, kActorVoiceOver);
		Actor_Voice_Over(960, kActorVoiceOver);
		Actor_Voice_Over(970, kActorVoiceOver);
		Actor_Voice_Over(980, kActorVoiceOver);
	} else if (!Game_Flag_Query(kFlagHF01MurrayMiaIntro)
	        &&  Global_Variable_Query(kVariableChapter) < 4
	) {
		if (_vm->_cutContent) {
			Actor_Face_Actor(kActorMcCoy, kActorMurray, true);
			Actor_Says(kActorMurray, 0, 14);
			Actor_Says(kActorMurray, 10, kAnimationModeTalk);
			Actor_Says(kActorMia, 0, kAnimationModeTalk);
			Actor_Face_Actor(kActorMurray, kActorMia, true);
			Actor_Says(kActorMurray, 20, 13);
			Actor_Face_Actor(kActorMia, kActorMurray, true);
			Actor_Says(kActorMia, 10, kAnimationModeTalk);
			Actor_Says(kActorMurray, 30, kAnimationModeTalk);
			Actor_Says(kActorMia, 20, kAnimationModeTalk);
			Actor_Face_Heading(kActorMurray, 271, false);
			Actor_Face_Heading(kActorMia, 511, false);
			Game_Flag_Set(kFlagHF01MurrayMiaIntro);
			Delay(1000);
			Actor_Says(kActorMcCoy, 8525, 13); // 00-8525.AUD	Hmph.
			Delay(1000);
			Player_Loses_Control();
			Loop_Actor_Walk_To_XYZ(kActorMcCoy, -202.0f, 8.0f, -619.0f, 0, true, false, false);
			Player_Gains_Control();
			Game_Flag_Set(kFlagHF01MurrayMiaIntro);
			Game_Flag_Set(kFlagHF01toHF05);
			Set_Enter(kSetHF05, kSceneHF05);
		} else {
			ADQ_Flush();
			ADQ_Add(kActorMurray, 0, 14);
			ADQ_Add(kActorMurray, 10, kAnimationModeTalk);
			ADQ_Add(kActorMia, 0, kAnimationModeTalk);
			Actor_Face_Actor(kActorMurray, kActorMia, true);
			ADQ_Add(kActorMurray, 20, 13);
			ADQ_Add(kActorMia, 10, kAnimationModeTalk);
			ADQ_Add(kActorMurray, 30, kAnimationModeTalk);
			ADQ_Add(kActorMia, 20, kAnimationModeTalk);
			Actor_Face_Heading(kActorMurray, 271, false);
			Game_Flag_Set(kFlagHF01MurrayMiaIntro);	
		}
	}

	

	Game_Flag_Reset(kFlagHF03toHF01);
	Game_Flag_Reset(kFlagHF02toHF01);
	Game_Flag_Reset(kFlagHF05toHF01);
	//return false;
}

void SceneScriptHF01::PlayerWalkedOut() {
	Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
	Ambient_Sounds_Remove_All_Looping_Sounds(1u);

	if (!Game_Flag_Query(kFlagHF01toHF05)
	 && !Game_Flag_Query(kFlagHF01toHF02)
	 && !Game_Flag_Query(kFlagHF01toHF03)
	 && !Game_Flag_Query(kFlagChapter4Starting)
	) {
#if BLADERUNNER_ORIGINAL_BUGS
		Outtake_Play(kOuttakeInside2,  true, -1);
		Outtake_Play(kOuttakeTowards3, true, -1);
#else
		if (!Game_Flag_Query(kFlagMcCoyInTyrellBuilding)) {
			// don't play an extra outtake when going to Tyrell Building
			Outtake_Play(kOuttakeInside2,  true, -1);
			Outtake_Play(kOuttakeTowards3, true, -1);
		}
#endif // BLADERUNNER_ORIGINAL_BUGS
	}
	Game_Flag_Reset(kFlagChapter4Starting);

	if (Actor_Query_Goal_Number(kActorLucy) == 450) {
		Actor_Put_In_Set(kActorLucy, kSetFreeSlotG);
		Actor_Set_At_Waypoint(kActorLucy, 39, 0);
		Actor_Set_Goal_Number(kActorLucy, kGoalLucyGone);
	}

	if (Actor_Query_Goal_Number(kActorDektora) == 450) {
		Actor_Put_In_Set(kActorDektora, kSetFreeSlotG);
		Actor_Set_At_Waypoint(kActorDektora, 39, 0);
		Actor_Set_Goal_Number(kActorDektora, kGoalDektoraGone);
	}
}

void SceneScriptHF01::DialogueQueueFlushed(int a1) {
}

void SceneScriptHF01::dialogueWithMiaAndMurray() {
	// Made it so no further option will be available if McCoy threatened Mia and Murray when asking about the cheese.
	Dialogue_Menu_Clear_List();
	if (_vm->_cutContent) {
		if (Actor_Query_Friendliness_To_Other(kActorMurray, kActorMcCoy) > 49) {
			if (Actor_Clue_Query(kActorMcCoy, kClueLucy)
			|| Actor_Clue_Query(kActorMcCoy, kClueLucyWithDektora)) {
				if (Actor_Query_Goal_Number(kActorLucy) != kGoalLucyGone) {
					DM_Add_To_List_Never_Repeat_Once_Selected(440, 8, 6, 3); // LUCY PHOTO
				}
			}
		}
	} else if (Actor_Clue_Query(kActorMcCoy, kClueLucy)) {
		DM_Add_To_List_Never_Repeat_Once_Selected(440, 8, 6, 3); // LUCY PHOTO
	}
	if (_vm->_cutContent) {
		if (Actor_Query_Friendliness_To_Other(kActorMurray, kActorMcCoy) > 49) {
			if (!Actor_Clue_Query(kActorMcCoy, kClueLucy)
			&& !Actor_Clue_Query(kActorMcCoy, kClueLucyWithDektora)
			&& Actor_Query_Goal_Number(kActorLucy) != kGoalLucyGone) {
				 DM_Add_To_List_Never_Repeat_Once_Selected(450, 7, 6, 3); // LUCY
			}
		}
	} else if (!Actor_Clue_Query(kActorMcCoy, kClueLucy)
		 &&  Actor_Clue_Query(kActorMcCoy, kClueRunciterInterviewA)) {
			DM_Add_To_List_Never_Repeat_Once_Selected(450, 7, 6, 3); // LUCY
		 }
	if (Actor_Clue_Query(kActorMcCoy, kClueCheese)) {
		DM_Add_To_List_Never_Repeat_Once_Selected(460, 3, 5, 6); // CHEESE
	}
	// Restored the black sedan option.
	if (_vm->_cutContent) {
		if (Actor_Query_Friendliness_To_Other(kActorMurray, kActorMcCoy) > 49) {
			if (Actor_Clue_Query(kActorMcCoy, kClueCarRegistration1)
			|| Actor_Clue_Query(kActorMcCoy, kClueCarRegistration3)) {
				DM_Add_To_List_Never_Repeat_Once_Selected(1130, 1, 3, 8); // BLACK SEDAN
			}
		}
	}
	if (_vm->_cutContent) {
		if (Actor_Query_Friendliness_To_Other(kActorMurray, kActorMcCoy) > 49) {
			if (Actor_Clue_Query(kActorMcCoy, kClueLichenDogWrapper)) {
				DM_Add_To_List_Never_Repeat_Once_Selected(470, -1, 3, 8); // LICHEN DOG WRAPPER
			}
		}
	} else {
		DM_Add_To_List_Never_Repeat_Once_Selected(470, -1, 3, 8); // LICHEN DOG WRAPPER
	}
	Dialogue_Menu_Add_DONE_To_List(480); // DONE

	Dialogue_Menu_Appear(320, 240);
	int answer = Dialogue_Menu_Query_Input();
	Dialogue_Menu_Disappear();

	switch (answer) {
	case 440: // LUCY PHOTO
		if (_vm->_cutContent) {
			Actor_Face_Actor(kActorMurray, kActorMcCoy, true);
			Actor_Face_Actor(kActorMia, kActorMcCoy, true);
		}
		Actor_Says(kActorMcCoy, 1480, 15);
		Actor_Says(kActorMia, 70, kAnimationModeTalk);
		if (_vm->_cutContent) {
			Actor_Face_Actor(kActorMurray, kActorMia, true);
			Actor_Face_Actor(kActorMia, kActorMurray, true);
		}
		Actor_Says(kActorMurray, 120, kAnimationModeTalk);
		if (_vm->_cutContent) {
			Actor_Face_Actor(kActorMurray, kActorMcCoy, true);
			Actor_Face_Actor(kActorMia, kActorMcCoy, true);
		}
		Actor_Says(kActorMcCoy, 1505, 14);
		Actor_Says(kActorMia, 80, kAnimationModeTalk);
		if (_vm->_cutContent) {
			Actor_Face_Actor(kActorMurray, kActorMia, true);
			Actor_Face_Actor(kActorMia, kActorMurray, true);
		}
		Actor_Says(kActorMurray, 130, kAnimationModeTalk);
		Actor_Says(kActorMia, 90, kAnimationModeTalk);
		if (_vm->_cutContent) {
			Actor_Face_Actor(kActorMurray, kActorMcCoy, true);
			Actor_Face_Actor(kActorMia, kActorMcCoy, true);
		}
		Actor_Says(kActorMcCoy, 1510, 12);
		if (_vm->_cutContent) {
			Actor_Face_Actor(kActorMurray, kActorMia, true);
			Actor_Face_Heading(kActorMia, 511, false);
		}
		break;

	case 450: // LUCY
		if (_vm->_cutContent) {
			Actor_Face_Actor(kActorMurray, kActorMcCoy, true);
			Actor_Face_Actor(kActorMia, kActorMcCoy, true);
		}
		Actor_Says(kActorMcCoy, 1485, 16); //00-1485.AUD	You seen a girl around here? About fourteen with pink hair... Maybe in the arcade?
		Actor_Says(kActorMia, 100, kAnimationModeTalk);
		if (_vm->_cutContent) {
			Actor_Face_Actor(kActorMurray, kActorMia, true);
			Actor_Face_Actor(kActorMia, kActorMurray, true);
		}
		Actor_Says(kActorMurray, 140, 12);
		Actor_Says(kActorMia, 110, kAnimationModeTalk);
		if (_vm->_cutContent) {
			Actor_Face_Actor(kActorMurray, kActorMcCoy, true);
			Actor_Face_Actor(kActorMia, kActorMcCoy, true);
		}
		Actor_Says(kActorMia, 120, kAnimationModeTalk);
		Actor_Says(kActorMurray, 150, 14);
		if (_vm->_cutContent) {
			Actor_Face_Actor(kActorMurray, kActorMia, true);
			Actor_Face_Heading(kActorMia, 511, false);
		}
		break;

	case 460: // CHEESE
		if (_vm->_cutContent) {
			Actor_Face_Actor(kActorMurray, kActorMcCoy, true);
			Actor_Face_Actor(kActorMia, kActorMcCoy, true);
			// Restored some Mia and Murray dialogue. Reworked the conversation so McCoy in a round about way accuses Mia and Murray of dealing illegal substances.
			// This annoys Mia and Murray and they ignore McCoy for a little bit until they eventually talk to him again.
		}
		Actor_Says(kActorMcCoy, 1490, 23); //00-1490.AUD	You know where I could score some cheese, like this stuff?
		Actor_Says(kActorMurray, 160, 15); //31-0160.AUD	Oy, don't flash that around here!
		if (_vm->_cutContent) {
			Actor_Says(kActorMcCoy, 1870, 14); //00-1870.AUD	I’m a cop.
			Actor_Says(kActorMurray, 170, 13); //31-0170.AUD	Besides, the kids today...
			Actor_Says(kActorMurray, 180, 12); //31-0180.AUD	just as soon twist a knife in your back side as to ask for chinyen for the tram home.
			Actor_Says(kActorMurray, 190, 14); //31-0190.AUD	You show that cheese around here, you become a marked man.
			Actor_Says(kActorMcCoy, 1365, 15); //00-1365.AUD	I'm not looking to bust the dealer. I just want to know who bought it.
			Actor_Says(kActorMurray, 310, 13); //31-0310.AUD	McCoy, we've been friends for years. How dare you accuse us?
			Actor_Says(kActorMcCoy, 1515, 23); //00-1515.AUD	Who sells it?
			Actor_Says(kActorMurray, 320, 14); //31-0320.AUD	Ah... when I was young we respected our elders.
		} else {
			Actor_Says(kActorMia, 130, 13);  //22-0130.AUD	He's the police, sweetie.
			Actor_Says(kActorMurray, 170, 13); //31-0170.AUD	Besides, the kids today...
			Actor_Says(kActorMurray, 180, 12); //31-0180.AUD	just as soon twist a knife in your back side as to ask for chinyen for the tram home.
			Actor_Says(kActorMurray, 190, 14); //31-0190.AUD	You show that cheese around here, you become a marked man.
		}
		if (_vm->_cutContent) {
			// Made it so if McCoy is surly or erratic he threatens Mia and Murray with jail time if they don't tell him about the cheese and they comply. If McCoy is nice
			// he apolgises for upsetting them and they tell McCoy what he wants to know. 
			if (Player_Query_Agenda() == kPlayerAgendaSurly 
			|| Player_Query_Agenda() == kPlayerAgendaErratic) {
				Actor_Says(kActorMcCoy, 6985, 16); //00-6985.AUD	Got the straight scoop for me or what?
				Actor_Says(kActorMurray, 200, kAnimationModeTalk); //31-0200.AUD	Now, we aren't asking for any trouble, Ray. 
				Actor_Face_Actor(kActorMia, kActorMurray, true);
				Actor_Says(kActorMia, 130, 12); //22-0130.AUD	He's the police, sweetie.	
				Delay (1000);
				Actor_Face_Actor(kActorMcCoy, kActorMia, true);
				Actor_Says(kActorMcCoy, 8519, 14);//00-8519.AUD	What do you say we dish each other the straight goods.
				Actor_Modify_Friendliness_To_Other(kActorMurray, kActorMcCoy, -2);
				Delay (1000);
				Actor_Face_Actor(kActorMurray, kActorMia, true);
				Actor_Face_Heading(kActorMia, 511, false);
			} else {
				Actor_Says(kActorMcCoy, 1520, 15); //00-1520.AUD	I'm not working Bunco. I just want some information
				Delay(1000);
				Actor_Says(kActorMia, 180, 12); //22-0180.AUD	Well, we did hear something, Ray. I hope this won't get anybody into trouble.
				Actor_Says(kActorMcCoy, 1845, 19); //00-1845.AUD	I’ll have to think about it.
				Actor_Says(kActorMia, 250, 12); //22-0250.AUD	All right, then. Ray, here's the truth.
				Delay (1000);
				Actor_Says(kActorMurray, 210, 13);
				Actor_Says(kActorMurray, 220, 13);
				Actor_Says(kActorMia, 140, 12);
				Actor_Says(kActorMurray, 230, 13);
				Actor_Face_Actor(kActorMurray, kActorMia, true);
				Actor_Face_Heading(kActorMia, 511, false);
				Actor_Clue_Acquire(kActorMcCoy, kClueSpecialIngredient, false, kActorMurray);
			}
		} else {
			Actor_Says(kActorMcCoy, 1515, 15); //00-1515.AUD	Who sells it?
			Actor_Says(kActorMurray, 200, kAnimationModeTalk); //31-0200.AUD	Now, we aren't asking for any trouble, Ray. 
			Actor_Says(kActorMia, 130, 13);	//22-0130.AUD	He's the police, sweetie.
			Actor_Says(kActorMcCoy, 1520, 15); //00-1520.AUD	I'm not working Bunco. I just want some information
			Actor_Says(kActorMurray, 210, 13);
			Actor_Says(kActorMurray, 220, 13);
			Actor_Says(kActorMia, 140, 12);
			Actor_Says(kActorMurray, 230, 13);
			Actor_Clue_Acquire(kActorMcCoy, kClueSpecialIngredient, false, kActorMurray);
		}
		break;

	// Restored dialogur for the black sedan option.
	case 1130: // BLACK SEDAN
		Actor_Face_Actor(kActorMia, kActorMcCoy, true);
		Actor_Face_Actor(kActorMurray, kActorMcCoy, true);
		Actor_Says(kActorMcCoy, 1525, 13); //00-1525.AUD	You ever see a black ground car around here?
		Actor_Says(kActorMia, 150, kAnimationModeTalk); //22-0150.AUD	Oh, sure.
		Actor_Says(kActorMcCoy, 1530, 15); //00-1530.AUD	When?
		Delay(3000);
		Actor_Says(kActorMurray, 260, kAnimationModeTalk); //31-0260.AUD	Spit it out, woman! McCoy doesn't have all day!
		Actor_Says(kActorMia, 190, kAnimationModeTalk); //22-0190.AUD	I was just about to, when you interrupted.
		if (Player_Query_Agenda() == kPlayerAgendaPolite) {
			Actor_Says(kActorMcCoy, 7380, 13); // M: Just answer the question please.
		} else {
			Actor_Says(kActorMcCoy, 7805, 13); //00-7805.AUD	Answer the question.
		}
		Actor_Says(kActorMia, 160, kAnimationModeTalk); //22-0160.AUD	Well, let's see, er, we saw three this afternoon.
		Actor_Says(kActorMurray, 250, kAnimationModeTalk); //31-0250.AUD	At least six this morning.
		Actor_Says(kActorMia, 170, kAnimationModeTalk); //22-0170.AUD	Oh, and yesterday was even busier.
		Delay (2000);
		Actor_Says(kActorMcCoy, 1535, 16); //00-1535.AUD	Ah, never mind.
		Actor_Face_Actor(kActorMurray, kActorMia, true);
		Actor_Face_Heading(kActorMia, 511, false);
		break;


	case 470: // LICHEN DOG WRAPPER
		if (_vm->_cutContent) {
			Actor_Face_Actor(kActorMurray, kActorMcCoy, true);
			Actor_Face_Actor(kActorMia, kActorMcCoy, true);
		}
		Actor_Says(kActorMcCoy, 1495, 14);
		Actor_Face_Actor(kActorMurray, kActorMcCoy, true);
		Actor_Says(kActorMurray, 240, 13);
		Actor_Face_Actor(kActorMurray, kActorMia, true);
		if (_vm->_cutContent) {
			Actor_Face_Heading(kActorMia, 511, false);
		}
		break;

	case 480: // DONE
		if (_vm->_cutContent) {
			if (Actor_Query_Friendliness_To_Other(kActorMurray, kActorMcCoy) > 49) {
				if (!Game_Flag_Query(kFlagMiaAndMurrayFinishedTalk)) {
					Actor_Face_Actor(kActorMurray, kActorMcCoy, true);
					Actor_Face_Actor(kActorMia, kActorMcCoy, true);
					Actor_Says(kActorMcCoy, 6980, 16); //00-6980.AUD	What's the word on the street.
					Actor_Says(kActorMurray, 270, 13); //31-0270.AUD	We haven't heard anything lately. It's like the city's dead or something. 
					Actor_Face_Actor(kActorMia, kActorMurray, true);
					Actor_Says(kActorMia, 200, 12); //22-0200.AUD	You mean the city's asleep.
					Actor_Face_Actor(kActorMurray, kActorMia, true);
					Actor_Says(kActorMurray, 280, 13); //31-0280.AUD	No! I mean exactly what I said.
					Actor_Face_Actor(kActorMurray, kActorMia, true);
					Actor_Face_Heading(kActorMia, 511, false);
					Game_Flag_Set(kFlagMiaAndMurrayFinishedTalk);
				} else {
					if (Player_Query_Agenda() == kPlayerAgendaPolite) { 
						Actor_Says(kActorMcCoy, 1500, 16); //00-1500.AUD	Be good you two.
					} else {
						Actor_Says(kActorMcCoy, 5145, 13); //00-5145.AUD	I may have more questions for you later on.
					}
				}
			} else {
				if (!Game_Flag_Query(kFlagMiaMurrayAnnoyedTalk)) { 
					Actor_Face_Actor(kActorMurray, kActorMia, true);
					Actor_Face_Heading(kActorMia, 511, false);
					Actor_Says(kActorMcCoy, 3970, 14); //00-3970.AUD	Hey.
					Delay(1000);
					Actor_Says(kActorMcCoy, 815, 14); //00-0815.AUD	Listen to me!
					Actor_Face_Actor(kActorMia, kActorMurray, true);
					Actor_Says(kActorMia, 210, 12); //22-0210.AUD	Hmph! Is that rude boy talking to us?
					Actor_Face_Actor(kActorMurray, kActorMia, true);
					Actor_Says(kActorMurray, 290, 10); //31-0290.AUD	I think he is.
					Actor_Says(kActorMia, 220, 12); //22-0220.AUD	And after how he's been behaving. Well, surely he can't expect us to help him.
					Actor_Says(kActorMurray, 300, 11); //31-0300.AUD	For once we're in agreement. 
					Actor_Face_Actor(kActorMia, kActorMcCoy, true);
					Actor_Says(kActorMia, 230, 12); //22-0230.AUD	Hmph! No more free ‘dogs for you, young man.				
					Delay(2000);
					Actor_Face_Actor(kActorMurray, kActorMia, true);
					Actor_Face_Heading(kActorMia, 511, false);
					Game_Flag_Set(kFlagMiaMurrayAnnoyedTalk);
				} else {
					Actor_Face_Actor(kActorMurray, kActorMcCoy, true);
					Actor_Face_Actor(kActorMia, kActorMcCoy, true);
					Actor_Says(kActorMcCoy, 8520, 14); //00-8520.AUD	What do you know?
					Actor_Says(kActorMurray, 270, 13); //31-0270.AUD	We haven't heard anything lately. It's like the city's dead or something. 
					if (Player_Query_Agenda() == kPlayerAgendaSurly 
					|| Player_Query_Agenda() == kPlayerAgendaErratic) {
						Actor_Says(kActorMcCoy, 3910, 16); //00-3910.AUD	You’re lying.
						Delay(1000);
						Actor_Face_Actor(kActorMia, kActorMurray, true);
						Actor_Says(kActorMia, 240, 12); //22-0240.AUD	Oh, dear! He caught us in a fib, Murray.
						Delay(1000);
						Actor_Face_Actor(kActorMia, kActorMcCoy, true);
						Actor_Says(kActorMcCoy, 4360, 16); //00-4360.AUD	Tell it straight or I'm gonna make sure you get the same as he gets. Full conspiracy, payable for 25.
						Delay(2000);
						Actor_Says(kActorMcCoy, 3095, 18); //00-3095.AUD	Now we’re gonna take a little ride downtown.	
						Delay(1000);
						Game_Flag_Set(kFlagMiaAndMurrayArrested);
						Actor_Put_In_Set(kActorMurray, kSetPS09);
						Actor_Set_At_XYZ(kActorMurray, -455.0f, 0.2f, -210.0f, 518);
						Actor_Put_In_Set(kActorMia, kSetPS09);
						Actor_Set_At_XYZ(kActorMia, -460.0f, 0.2f, -239.0f, 518);
						Game_Flag_Reset(kFlagSpinnerAtHF01);
						Game_Flag_Set(kFlagSpinnerAtPS01);
						Scene_Exits_Enable();
						Game_Flag_Reset(kFlagMcCoyInHysteriaHall);
						Game_Flag_Set(kFlagMcCoyInPoliceStation);
					}
				}
			}
		} else {
			Actor_Says(kActorMcCoy, 1500, 16);
		}
		break;
	}
}

void SceneScriptHF01::talkWithDektora() {
	Actor_Says(kActorDektora, 0, kAnimationModeTalk);
	if (_vm->_cutContent) {
		Actor_Says(kActorDektora, 0, kAnimationModeTalk);
		if (Player_Query_Agenda() == kPlayerAgendaPolite) {
			Actor_Says(kActorMcCoy, 1400, kAnimationModeTalk); //00-1400.AUD	I promised you, didn't I?
			Actor_Says(kActorDektora, 10, kAnimationModeTalk); //03-0010.AUD	You’re one of the few people I’ve known who actually keep their promises.
		}
	} else {
		Actor_Says(kActorMcCoy, 1400, kAnimationModeTalk); //00-1400.AUD	I promised you, didn't I?
		Actor_Says(kActorDektora, 10, kAnimationModeTalk); //03-0010.AUD	You’re one of the few people I’ve known who actually keep their promises.
	}
	Actor_Says(kActorMcCoy, 1405, kAnimationModeTalk); //00-1405.AUD	Where's Clovis?
	Actor_Says(kActorDektora, 20, kAnimationModeTalk); //03-0020.AUD	He’s not coming with us.
	Actor_Says(kActorMcCoy, 1410, kAnimationModeTalk); //00-1410.AUD	You're gonna miss him?
	Actor_Says(kActorDektora, 30, kAnimationModeTalk); //03-0030.AUD	I’ve practically forgotten him already.
	if (_vm->_cutContent) {
		if (Actor_Query_Friendliness_To_Other(kActorClovis, kActorMcCoy) > 50) {
			Actor_Says(kActorMcCoy, 1415, kAnimationModeTalk); //00-1415.AUD	Some ways I wish I'd gotten to know him better.
			Actor_Says(kActorDektora, 40, kAnimationModeTalk); //03-0040.AUD	Then you know him better than you think.
			Actor_Says(kActorDektora, 50, kAnimationModeTalk); //03-0050.AUD	There’s a strange bond that exists between the two of you.
			Actor_Says(kActorDektora, 60, kAnimationModeTalk); //03-0060.AUD	I felt it from the start.
			Actor_Says(kActorDektora, 70, kAnimationModeTalk); //03-0070.AUD	That’s one of the reasons I was so drawn to you.
		} 
	} else {
		Actor_Says(kActorMcCoy, 1415, kAnimationModeTalk); //00-1415.AUD	Some ways I wish I'd gotten to know him better.
		Actor_Says(kActorDektora, 40, kAnimationModeTalk); //03-0040.AUD	Then you know him better than you think.
		Actor_Says(kActorDektora, 50, kAnimationModeTalk); //03-0050.AUD	There’s a strange bond that exists between the two of you.
		Actor_Says(kActorDektora, 60, kAnimationModeTalk); //03-0060.AUD	I felt it from the start.
		Actor_Says(kActorDektora, 70, kAnimationModeTalk); //03-0070.AUD	That’s one of the reasons I was so drawn to you.
	}
	Actor_Says(kActorMcCoy, 1420, kAnimationModeTalk); //00-1420.AUD	Are you ready?
	Actor_Says(kActorDektora, 80, kAnimationModeTalk); //03-0080.AUD	Like I’m beginning a whole new life.
}

void SceneScriptHF01::talkWithLucy() {
	Actor_Says(kActorLucy, 0, kAnimationModeTalk); //06-0000.AUD	I knew you’d come.
	if (_vm->_cutContent) {
		if (Player_Query_Agenda() == kPlayerAgendaPolite) {
			Actor_Says(kActorMcCoy, 1425, kAnimationModeTalk); //00-1425.AUD	I promised you, didn't I?
		}
	} else {
		Actor_Says(kActorMcCoy, 1425, kAnimationModeTalk); //00-1425.AUD	I promised you, didn't I?
	}
	Actor_Says(kActorLucy, 10, kAnimationModeTalk); //06-0010.AUD	Father wanted me to stay with him.
	if (_vm->_cutContent) {
		if (Actor_Query_Friendliness_To_Other(kActorClovis, kActorMcCoy) > 50) {
			Actor_Says(kActorLucy, 20, kAnimationModeTalk); //06-0020.AUD	But when I told him I was going with you, he gave us his blessing.
			Actor_Says(kActorMcCoy, 1430, kAnimationModeTalk); //00-1430.AUD	He is an extraordinary guy.
			Actor_Says(kActorLucy, 30, kAnimationModeTalk); //06-0030.AUD	I know.
		}
	} else {
		Actor_Says(kActorLucy, 20, kAnimationModeTalk); //06-0020.AUD	But when I told him I was going with you, he gave us his blessing.
		Actor_Says(kActorMcCoy, 1430, kAnimationModeTalk); //00-1430.AUD	He is an extraordinary guy.
		Actor_Says(kActorLucy, 30, kAnimationModeTalk); //06-0030.AUD	I know.
	}
	Actor_Says(kActorMcCoy, 1435, kAnimationModeTalk); //00-1435.AUD	You're gonna miss him?
	Actor_Says(kActorLucy, 40, kAnimationModeTalk); //06-0040.AUD	Of course, but now that I have you
	Actor_Says(kActorLucy, 50, kAnimationModeTalk); //06-0050.AUD	everything will be all right, won’t it?
	if (_vm->_cutContent) {
		if (Player_Query_Agenda() == kPlayerAgendaSurly 
		|| Player_Query_Agenda() == kPlayerAgendaErratic) {
			Actor_Says(kActorMcCoy, 1440, kAnimationModeTalk); //00-1440.AUD	Sure it will.
		} else {
			Actor_Says(kActorMcCoy, 7330, 16); //00-7330.AUD	Let's hope so.
		}
	} else {
		Actor_Says(kActorMcCoy, 1440, kAnimationModeTalk); //00-1440.AUD	Sure it will.
	}
	Actor_Says(kActorLucy, 60, kAnimationModeTalk); //06-0060.AUD	Promise me that we’re going to find that special place!
	Actor_Says(kActorLucy, 70, kAnimationModeTalk); //06-0070.AUD	The one with the trees and the flowers and the beautiful clear lake.
	if (_vm->_cutContent) {
		if (Player_Query_Agenda() == kPlayerAgendaSurly 
		|| Player_Query_Agenda() == kPlayerAgendaErratic) {
			Actor_Says(kActorMcCoy, 1445, kAnimationModeTalk); //00-1445.AUD	It exists somewhere.
			Actor_Says(kActorLucy, 80, kAnimationModeTalk); //06-0080.AUD	It’s so much more than a dream, isn’t it?
			Actor_Says(kActorLucy, 3030, kAnimationModeTalk);
		} else {
			Actor_Says(kActorMcCoy, 7980, 19); //00-7980.AUD	Yeah. Maybe.
			Actor_Says(kActorLucy, 2240, kAnimationModeTalk); // 06-2240.AUD	What?
			Delay(2000);
			Actor_Says(kActorLucy, 2210, kAnimationModeTalk); //06-2210.AUD	I should've known.
			Delay(1000);
			Actor_Says(kActorLucy, 1200, kAnimationModeTalk); //06-1200.AUD	It’s not fair!
			Actor_Says(kActorMcCoy, 6870, 14); //00-6870.AUD	No. But you had to know.
			Delay(1500);
			Actor_Says(kActorMcCoy, 8075, kAnimationModeTalk); //00-8075.AUD	 Let's move on.
			Actor_Says(kActorLucy, 1130, kAnimationModeTalk); //06-1130.AUD	Uh-huh.
		}
	} else {
		Actor_Says(kActorMcCoy, 1445, kAnimationModeTalk); //00-1445.AUD	It exists somewhere.
		Actor_Says(kActorLucy, 80, kAnimationModeTalk); //06-0080.AUD	It’s so much more than a dream, isn’t it?
		Actor_Says(kActorLucy, 3030, kAnimationModeTalk);
	}
}

} // End of namespace BladeRunner
