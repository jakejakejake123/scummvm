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

void SceneScriptTB02::InitializeScene() {
	if (Game_Flag_Query(kFlagTB03toTB02)) {
		Setup_Scene_Information(-152.0f, 0.0f, 1774.0f, 999);
	} else if (Game_Flag_Query(kFlagTB05toTB02)) {
		Setup_Scene_Information(-32.0f, 0.0f, 1578.0f, 639);
	} else if (Game_Flag_Query(kFlagTB07toTB02)) {
		Setup_Scene_Information(-32.0f, 0.0f, 1578.0f, 639);
	} else {
		Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
		Ambient_Sounds_Remove_All_Looping_Sounds(1u);
		Outtake_Play(kOuttakeTyrellBuildingFly, false, -1); // TB_FLY_#.VQA Note: this is the only fly-through scene that is localized!
		Setup_Scene_Information(-304.0f, -81.46f, 1434.0f, 250);
	}
	if (Global_Variable_Query(kVariableChapter) > 3) {
		Scene_Exit_Add_2D_Exit(0, 0, 455, 639, 479, 2);
	}

	Ambient_Sounds_Add_Looping_Sound(kSfxFOUNTAIN, 20, 0, 1);
	Ambient_Sounds_Add_Sound(kSfxBELLY1, 2, 15, 16, 20, 0, 0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBELLY2, 2, 15, 16, 20, 0, 0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBELLY3, 2, 20, 16, 20, 0, 0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBELLY4, 2, 15, 16, 20, 0, 0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBELLY5, 2, 15, 16, 20, 0, 0, -101, -101, 0, 0);
	if (Global_Variable_Query(kVariableChapter) <= 3) {
		Ambient_Sounds_Add_Looping_Sound(kSfxPSAMB6, 35, 0, 1);
		Ambient_Sounds_Add_Sound(kSfx67_0470R, 5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
		Ambient_Sounds_Add_Sound(kSfx67_0480R, 5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
		Ambient_Sounds_Add_Sound(kSfx67_0500R, 5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
		Ambient_Sounds_Add_Sound(kSfx67_0540R, 5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
		Ambient_Sounds_Add_Sound(kSfx67_0560R, 5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
		Ambient_Sounds_Add_Sound(kSfx67_0870R, 5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
		Ambient_Sounds_Add_Sound(kSfx67_0900R, 5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
		Ambient_Sounds_Add_Sound(kSfx67_0940R, 5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
		Ambient_Sounds_Add_Sound(kSfx67_0960R, 5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
		Ambient_Sounds_Add_Sound(kSfx67_1070R, 5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
		Ambient_Sounds_Add_Sound(kSfx67_1080R, 5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
		Ambient_Sounds_Add_Sound(kSfx67_1100R, 5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
		Ambient_Sounds_Add_Sound(kSfx67_1140R, 5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
		Ambient_Sounds_Add_Sound(kSfx67_1160R, 5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
	}
	if (_vm->_cutContent) {
		if (Global_Variable_Query(kVariableChapter) == 4 
		&& !Actor_Clue_Query(kActorMcCoy, kClueDNATyrell)) {
			ADQ_Add(kActorTransient, 400, -1); //12-0400.AUD	Zzz…
		}
	}

	if (Game_Flag_Query(kFlagSpinnerAtTB02)
	 && Global_Variable_Query(kVariableChapter) < 4
	) {
		Scene_Exit_Add_2D_Exit(2, 67, 0, 233, 362, 3);
	}

	if (Game_Flag_Query(kFlagTB03toTB02)) {
		Scene_Loop_Start_Special(kSceneLoopModeLoseControl, 0, false);
		Scene_Loop_Set_Default(1);
	} else {
		Scene_Loop_Set_Default(1);
	}

	Actor_Put_In_Set(kActorTyrellGuard, kSetTB02_TB03);
	Actor_Set_At_XYZ(kActorTyrellGuard, -38.53f, 2.93f, 1475.97f, 673);
	if (Global_Variable_Query(kVariableChapter) == 4) {
		if (Actor_Query_Goal_Number(kActorTyrellGuard) < kGoalTyrellGuardSleeping) {
			Actor_Set_Goal_Number(kActorTyrellGuard, kGoalTyrellGuardSleeping);
		}
		Scene_Exit_Add_2D_Exit(1, 430, 235, 487, 396, 0);
	}
}

void SceneScriptTB02::SceneLoaded() {
	Obstacle_Object("SPHERE02", true);
	Unobstacle_Object("BOX36", true);
}

bool SceneScriptTB02::MouseClick(int x, int y) {
	return Region_Check(600, 300, 639, 479);
}

bool SceneScriptTB02::ClickedOn3DObject(const char *objectName, bool a2) {
	return false;
}

bool SceneScriptTB02::ClickedOnActor(int actorId) {
	if (actorId == kActorTyrellGuard) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -76.35f, 0.15f, 1564.2f, 0, true, false, false)) {
			Actor_Face_Actor(kActorMcCoy, kActorTyrellGuard, true);
			int chapter = Global_Variable_Query(kVariableChapter);
			if (chapter == 2) {
				if ( Game_Flag_Query(kFlagTB02ElevatorToTB05)
				 && !Game_Flag_Query(kFlagTB05Entered)
				) {
					// Added in some more dialogue for the Tyrell guard. Depending on McCoys agenda he will continue to pester the guard which results in friendliness loss. 
					Actor_Says(kActorMcCoy, 5150, 18); //00-5150.AUD	One more thing.
					Actor_Says(kActorTyrellGuard, 60, 12); //17-0060.AUD	I've told you everything I know, detective.
					if (_vm->_cutContent) {
						if (Player_Query_Agenda() != kPlayerAgendaPolite) {
							Actor_Says(kActorMcCoy, 3910, 14); //00-3910.AUD	You’re lying.
							Actor_Says(kActorTyrellGuard, 410, 12);	//17-0410.AUD	What I said is the truth, sir.
						} else {
							Actor_Says(kActorMcCoy, 4880, 18); //00-4880.AUD	Is that right?
						}
					}
					if (_vm->_cutContent) {
						if (Actor_Query_Friendliness_To_Other(kActorTyrellGuard, kActorMcCoy) < 50) {
							Actor_Says(kActorTyrellGuard, 70, 13); //17-0070.AUD	I gotta work! These monitors don't watch themselves.
							if (Player_Query_Agenda() == kPlayerAgendaSurly 
							|| Player_Query_Agenda() == kPlayerAgendaErratic) {
								Actor_Says(kActorMcCoy, 5155, 13); //00-5155.AUD	Yeah. It's a tough gig.
								Actor_Modify_Friendliness_To_Other(kActorTyrellGuard, kActorMcCoy, -2);
							}
						}
					} else {
						Actor_Says(kActorTyrellGuard, 70, 13); //17-0070.AUD	I gotta work! These monitors don't watch themselves.
						Actor_Says(kActorMcCoy, 5155, 13); //00-5155.AUD	Yeah. It's a tough gig.	
					}		
					if (!_vm->_cutContent) {
						Actor_Modify_Friendliness_To_Other(kActorTyrellGuard, kActorMcCoy, -1);
					}	
					Actor_Face_Heading(kActorTyrellGuard, 788, false);
					return true;
				}
				if (!_vm->_cutContent) {
					if (!Game_Flag_Query(kFlagTB02ElevatorToTB05)
					&& !Game_Flag_Query(kFlagTB05Entered)
					) {
						Game_Flag_Set(kFlagTB02ElevatorToTB05);
						Actor_Says(kActorMcCoy, 5160, 18);
						Actor_Says(kActorTyrellGuard, 80, 14);
						Scene_Exit_Add_2D_Exit(1, 430, 235, 487, 396, 0);
						return true;
					}
				}
				if (Game_Flag_Query(kFlagTB05Entered)) {
					dialogueWithTyrellGuard();
				} else {
					Actor_Face_Actor(kActorTyrellGuard, kActorMcCoy, true);
					Actor_Says(kActorMcCoy, 5150, 18); //00-5150.AUD	One more thing.
					Actor_Says(kActorTyrellGuard, 60, 12); //17-0060.AUD	I've told you everything I know, detective.
					if (Player_Query_Agenda() != kPlayerAgendaPolite) {
						Actor_Says(kActorMcCoy, 3910, 14); //00-3910.AUD	You’re lying.
						Actor_Says(kActorTyrellGuard, 410, 12);	//17-0410.AUD	What I said is the truth, sir.
					} else {
						Actor_Says(kActorMcCoy, 4880, 18); //00-4880.AUD	Is that right?
					}
					if (_vm->_cutContent) {
						if (Actor_Query_Friendliness_To_Other(kActorTyrellGuard, kActorMcCoy) < 50) {
							Actor_Says(kActorTyrellGuard, 70, 13); //17-0070.AUD	I gotta work! These monitors don't watch themselves.
							if (Player_Query_Agenda() == kPlayerAgendaSurly 
							|| Player_Query_Agenda() == kPlayerAgendaErratic) {
								Actor_Says(kActorMcCoy, 5155, 13); //00-5155.AUD	Yeah. It's a tough gig.
								Actor_Modify_Friendliness_To_Other(kActorTyrellGuard, kActorMcCoy, -2);
							}
						}
					} else {
						Actor_Says(kActorTyrellGuard, 70, 13); //17-0070.AUD	I gotta work! These monitors don't watch themselves.
						Actor_Says(kActorMcCoy, 5155, 13); //00-5155.AUD	Yeah. It's a tough gig.	
					}		
					if (!_vm->_cutContent) {
						Actor_Modify_Friendliness_To_Other(kActorTyrellGuard, kActorMcCoy, -1);
					}
					Actor_Face_Heading(kActorTyrellGuard, 788, false);
				}
				return true;
			}

			if (chapter == 3) {
				if (_vm->_cutContent) {
					if (Player_Query_Agenda() != kPlayerAgendaPolite) {
						Actor_Says(kActorMcCoy, 5235, 18);
						Actor_Says(kActorTyrellGuard, 280, 13);
					} else {
						Actor_Says(kActorMcCoy, 3210, kAnimationModeTalk); //00-3210.AUD	Hey, man.
					}
				} else {
					Actor_Says(kActorMcCoy, 5235, 18);
					Actor_Says(kActorTyrellGuard, 280, 13);
				}
				// Depending on your friendliness rating with the guard he will either tell you to leave or he will leave you alone. 
				if (_vm->_cutContent) {
					if (Actor_Query_Friendliness_To_Other(kActorTyrellGuard, kActorMcCoy) < 50) {
						Actor_Says(kActorTyrellGuard, 290, 12); //17-0290.AUD	I'm gonna have to ask you to leave, sir.
						Actor_Says(kActorMcCoy, 5240, 18); //00-5240.AUD	You're gonna throw me out?
						Actor_Says(kActorTyrellGuard, 300, 12); // 17-0300.AUD	If need be.
					} else {
						Actor_Says(kActorMcCoy, 8514, 18); //00-8514.AUD	Got anything new to tell me?
						Actor_Says(kActorTyrellGuard, 420, 12); //17-0420.AUD	Ah-- Oh, yeah, that's right. What I've said before, that's old information.
						Actor_Says(kActorMcCoy, 4940, 13); //00-4940.AUD	Okay, let's have it.
						Actor_Says(kActorTyrellGuard, 400, 12); //17-0400.AUD	I'm a little busy for this, sir.
						Actor_Says(kActorMcCoy, 2750, kAnimationModeTalk); //00-2750.AUD	Okay, I get the picture.
					}
					if (Player_Query_Agenda() == kPlayerAgendaPolite) {
						if (Actor_Clue_Query(kActorMcCoy, kClueTyrellSecurity)
						&& Actor_Clue_Query(kActorMcCoy, kClueTyrellSecurityPhoto)) {
							Delay(1000);
							Actor_Says(kActorMcCoy, 5150, 18); //00-5150.AUD	One more thing.
							Actor_Change_Animation_Mode(kActorMcCoy, 23);
							Actor_Change_Animation_Mode(kActorTyrellGuard, 23);
							Delay(800);
							Item_Pickup_Spin_Effect_From_Actor(kModelAnimationVideoDisc, kActorTyrellGuard, 0, 0);		
							Delay(800);
							Actor_Clue_Lose(kActorMcCoy, kClueTyrellSecurity);
							Actor_Clue_Acquire(kActorTyrellGuard, kClueTyrellSecurity, true, -1);
							Actor_Says(kActorMcCoy, 8170, 13); //00-8170.AUD	There you go.	
						}
					}
				} else {
					Actor_Says(kActorTyrellGuard, 290, 12); //17-0290.AUD	I'm gonna have to ask you to leave, sir.
					Actor_Says(kActorMcCoy, 5240, 18); //00-5240.AUD	You're gonna throw me out?
					Actor_Says(kActorTyrellGuard, 300, 12); // 17-0300.AUD	If need be.	
				}
				return false;
			}

			if (chapter == 4) {
				if (Actor_Query_Goal_Number(kActorTyrellGuard) == kGoalTyrellGuardSleeping) {
					Actor_Set_Goal_Number(kActorTyrellGuard, kGoalTyrellGuardWakeUpAndArrestMcCoy);
				}
			}
		}
	}
	return false;
}

bool SceneScriptTB02::ClickedOnItem(int itemId, bool a2) {
	return false;
}

bool SceneScriptTB02::ClickedOnExit(int exitId) {
	if (exitId == 0) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -152.0f, 0.0f, 1774.0f, 0, true, false, false)) {
			Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
			Ambient_Sounds_Remove_All_Looping_Sounds(1u);
			Game_Flag_Reset(kFlagTB02ElevatorToTB05);
			Set_Enter(kSetTB02_TB03, kSceneTB03);
			Async_Actor_Walk_To_XYZ(kActorMcCoy, -152.0f, 0.0f, 1890.0f, 0, false);
		}
		return true;
	}

	if (exitId == 1) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -32.0f, 0.0f, 1578.0f, 0, true, false, false)) {
				if (Global_Variable_Query(kVariableChapter) < 4) {
				// Restored the buzzer for the elevator along with its correlating dialogue. When McCoy first tries to access the elevator it is locked and he asks the guard
				// to buzz him in again to which the guard complies. Later on when the guard is asleep the elevator door is again locked and McCoy presses the buzzer to unlock it.
				if (_vm->_cutContent) {
					if (!Game_Flag_Query(kFlagTB05Entered)) {
						Actor_Says(kActorMcCoy, 8522, 13); //00-8522.AUD	Locked.
						Actor_Face_Actor(kActorMcCoy, kActorTyrellGuard, true);
						Actor_Says(kActorMcCoy, 5160, 15); //00-5160.AUD	Buzz me in again. I haven't made it up to Grav Test Lab yet.
						Actor_Says(kActorTyrellGuard, 80, 13); //17-0080.AUD	All right.
					}
				}	
				Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
				Ambient_Sounds_Remove_All_Looping_Sounds(1u);
				Game_Flag_Set(kFlagTB05Entered);
				Game_Flag_Set(kFlagTB02toTB05);
				Set_Enter(kSetTB05, kSceneTB05);
			} else if (Global_Variable_Query(kVariableChapter) == 4) {
				// Made it so in act 4 when breaking into the Tyrell building when McCoy approaches the elevator it is locked and he presses the buzzer to get in.
				if (_vm->_cutContent) { 
					if (Game_Flag_Query(kFlagElevatorLocked)) { 
						Actor_Says(kActorMcCoy, 8522, 13); //00-8522.AUD	Locked.
					} else {
						Actor_Says(kActorMcCoy, 8522, 13); //00-8522.AUD	Locked.
						Actor_Face_Actor(kActorMcCoy, kActorTyrellGuard, true);
						Delay (1000);
						Actor_Says(kActorMcCoy, 8525, 0); //00-8525.AUD	Hmph.
						Player_Loses_Control();
						Loop_Actor_Walk_To_XYZ(kActorMcCoy, -63.80f, 0.36f, 1518.58f, 0, true, false, false);
						Actor_Face_Heading(kActorMcCoy, 788, false);
						Delay (1000);
						Sound_Play(kSfxLABBUZZ1, 90, 0, 0, 50);
						Delay (1000);
						Actor_Face_Actor(kActorMcCoy, kActorTyrellGuard, true);
						Delay (2000);
						Actor_Face_Heading(kActorMcCoy, 788, false);
						Delay (1000);
						Sound_Play(kSfxLABBUZZ1, 90, 0, 0, 50);
						Delay (1000);
						Actor_Face_Actor(kActorMcCoy, kActorTyrellGuard, true);
						Delay (2000);
						Actor_Face_Heading(kActorMcCoy, 788, false);
						Delay (500);
						Sound_Play(kSfxLABBUZZ1, 90, 0, 0, 50);
						Delay (500);
						Sound_Play(kSfxLABBUZZ1, 90, 0, 0, 50);
						Delay (500);
						Sound_Play(kSfxLABBUZZ1, 90, 0, 0, 50);
						Delay (500);
						Actor_Face_Actor(kActorMcCoy, kActorTyrellGuard, true);
						Delay (1500);
						Actor_Face_Heading(kActorMcCoy, 788, false);
						Sound_Play(kSfxLABBUZZ1, 90, 0, 0, 50);
						Delay (500);
						Actor_Face_Actor(kActorMcCoy, kActorTyrellGuard, true);
						Delay (2000);
						Actor_Says(kActorMcCoy, 8527, 13);
						Loop_Actor_Walk_To_XYZ(kActorMcCoy, -32.0f, 0.0f, 1578.0f, 0, true, false, false);
						Player_Gains_Control();
						Game_Flag_Set(kFlagElevatorLocked);
						Set_Enter(kSetTB07, kSceneTB07);
					}
				} else {
					Set_Enter(kSetTB07, kSceneTB07);
				}
			}
		}
		return true;
	}

	if (exitId == 2) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -192.0f, 0.0f, 1430.0f, 0, true, false, false)) {
			Actor_Face_Heading(kActorMcCoy, 800, false);
			Loop_Actor_Travel_Stairs(kActorMcCoy, 9, false, kAnimationModeIdle);
			if (Actor_Query_Goal_Number(kActorTyrellGuard) == kGoalTyrellGuardSleeping) {
				Actor_Set_Goal_Number(kActorTyrellGuard, kGoalTyrellGuardWakeUpAndArrestMcCoy);
			} else {
				Game_Flag_Reset(kFlagMcCoyInChinaTown);
				Game_Flag_Reset(kFlagMcCoyInRunciters);
				Game_Flag_Reset(kFlagMcCoyInMcCoyApartment);
				Game_Flag_Reset(kFlagMcCoyInPoliceStation);
				Game_Flag_Reset(kFlagMcCoyInBradburyBuilding);
				Game_Flag_Reset(kFlagMcCoyInHysteriaHall);
				Game_Flag_Reset(kFlagMcCoyInTyrellBuilding);
				// Removed code that triggers the original buzzer scenario since the whole scene has now been revamped.
				if (!_vm->_cutContent) {
					Game_Flag_Reset(kFlagTB02ElevatorToTB05);
				}
				switch (Spinner_Interface_Choose_Dest(-1, false)) {
				case kSpinnerDestinationPoliceStation:
					Game_Flag_Set(kFlagMcCoyInPoliceStation);
					Game_Flag_Reset(kFlagSpinnerAtTB02);
					Game_Flag_Set(kFlagSpinnerAtPS01);
					Set_Enter(kSetPS01, kScenePS01);
					break;
				case kSpinnerDestinationMcCoysApartment:
					Game_Flag_Set(kFlagMcCoyInMcCoyApartment);
					Game_Flag_Reset(kFlagSpinnerAtTB02);
					Game_Flag_Set(kFlagSpinnerAtMA01);
					Set_Enter(kSetMA01, kSceneMA01);
					break;
				case kSpinnerDestinationRuncitersAnimals:
					Game_Flag_Set(kFlagMcCoyInRunciters);
					Game_Flag_Reset(kFlagSpinnerAtTB02);
					Game_Flag_Set(kFlagSpinnerAtRC01);
					Set_Enter(kSetRC01, kSceneRC01);
					break;
				case kSpinnerDestinationChinatown:
					Game_Flag_Set(kFlagMcCoyInChinaTown);
					Game_Flag_Reset(kFlagSpinnerAtTB02);
					Game_Flag_Set(kFlagSpinnerAtCT01);
					Set_Enter(kSetCT01_CT12, kSceneCT01);
					break;
				case kSpinnerDestinationAnimoidRow:
					Game_Flag_Set(kFlagMcCoyInAnimoidRow);
					Game_Flag_Reset(kFlagSpinnerAtTB02);
					Game_Flag_Set(kFlagSpinnerAtAR01);
					Set_Enter(kSetAR01_AR02, kSceneAR01);
					break;
				case kSpinnerDestinationDNARow:
					Game_Flag_Set(kFlagMcCoyInDNARow);
					Game_Flag_Reset(kFlagSpinnerAtTB02);
					Game_Flag_Set(kFlagSpinnerAtDR01);
					Set_Enter(kSetDR01_DR02_DR04, kSceneDR01);
					break;
				case kSpinnerDestinationBradburyBuilding:
					Game_Flag_Set(kFlagMcCoyInBradburyBuilding);
					Game_Flag_Reset(kFlagSpinnerAtTB02);
					Game_Flag_Set(kFlagSpinnerAtBB01);
					Set_Enter(kSetBB01, kSceneBB01);
					break;
				case kSpinnerDestinationNightclubRow:
					Game_Flag_Set(kFlagMcCoyInNightclubRow);
					Game_Flag_Reset(kFlagSpinnerAtTB02);
					Game_Flag_Set(kFlagSpinnerAtNR01);
					Set_Enter(kSetNR01, kSceneNR01);
					break;
				case kSpinnerDestinationHysteriaHall:
					Game_Flag_Set(kFlagMcCoyInHysteriaHall);
					Game_Flag_Reset(kFlagSpinnerAtTB02);
					Game_Flag_Set(kFlagSpinnerAtHF01);
					Set_Enter(kSetHF01, kSceneHF01);
					break;
				default:
					Game_Flag_Set(kFlagMcCoyInTyrellBuilding);
					break;
				}
			}
		}
		return true;
	}
	return false;
}

bool SceneScriptTB02::ClickedOn2DRegion(int region) {
	return false;
}

void SceneScriptTB02::SceneFrameAdvanced(int frame) {
}

void SceneScriptTB02::ActorChangedGoal(int actorId, int newGoal, int oldGoal, bool currentSet) {
}

void SceneScriptTB02::PlayerWalkedIn() {
	if (_vm->_cutContent) {
		Music_Stop(1u);
	}
	if (Game_Flag_Query(kFlagTB07TyrellMeeting)) {
		Game_Flag_Reset(kFlagTB07TyrellMeeting);
		if (Global_Variable_Query(kVariableChapter) == 2
		 || Global_Variable_Query(kVariableChapter) == 3
		) {
			Set_Enter(kSetTB07, kSceneTB07);
			return; // true;
		}
	}
	if (Game_Flag_Query(kFlagTB03toTB02)) {
		Async_Actor_Walk_To_XYZ(kActorMcCoy, -152.0f, 0.0f, 1702.0f, 0, false);
		Game_Flag_Reset(kFlagTB03toTB02);
	} else if (Game_Flag_Query(kFlagTB05toTB02)) {
		Game_Flag_Reset(kFlagTB05toTB02);
	} else if (Game_Flag_Query(kFlagTB07toTB02)) {
		Game_Flag_Reset(kFlagTB07toTB02);
		if (Actor_Query_Goal_Number(kActorTyrellGuard) == kGoalTyrellGuardSleeping) {
			Actor_Set_Goal_Number(kActorTyrellGuard, kGoalTyrellGuardWakeUp);
		}
		Music_Play(kMusicBatl226M, 50, 0, 2, -1, kMusicLoopPlayOnce, 0);
	} else {
		Loop_Actor_Travel_Stairs(kActorMcCoy, 9, true, kAnimationModeIdle);
		Loop_Actor_Walk_To_XYZ(kActorMcCoy, -140.0f, 0.79f, 1470.0f, 0, false, false, false);
	}
	int chapter = Global_Variable_Query(kVariableChapter);
	if (chapter > 4) {
		//return false;
		return;
	}
	if (chapter == 2) {
		if (!Game_Flag_Query(kFlagTB02GuardTalk1)) {
			Player_Loses_Control();
			if (_vm->_cutContent) {	
				Actor_Face_Actor(kActorMcCoy, kActorTyrellGuard, true);
				Actor_Face_Actor(kActorTyrellGuard, kActorMcCoy, true);
			}
			if (_vm->_cutContent) {	
				Actor_Says(kActorMcCoy, 5125, 23);
			} else {
				Actor_Says(kActorMcCoy, 5125, 18);
			}
			Actor_Says(kActorTyrellGuard, 0, 14);
			if (_vm->_cutContent) {	
				Actor_Change_Animation_Mode(kActorTyrellGuard, 50);
				Delay (800);
				Sound_Play(kSfxLABBUZZ1, 90, 0, 0, 50);
				Delay (1000);
				Actor_Says(kActorMcCoy, 5130, 13);
				Actor_Says(kActorTyrellGuard, 10, 15); //17-0010.AUD	Grav Test on the East Wing. 66th floor.
				Actor_Says(kActorMcCoy, 4130, kAnimationModeTalk); //00-4130.AUD	Anything else?
				Actor_Says(kActorTyrellGuard, 390, 15); //17-0390.AUD	I've told you everything I know, sir.
				if (Player_Query_Agenda() != kPlayerAgendaSurly
				&& Player_Query_Agenda() != kPlayerAgendaErratic) {
					Actor_Says(kActorMcCoy, 4180, kAnimationModeTalk); //00-4180.AUD	You sure?
					Delay(1000);
					Actor_Says(kActorTyrellGuard, 380, 10); //17-0380.AUD	Oh, yeah, there-- There is one more thing.
				} else {
					Actor_Says(kActorMcCoy, 6995, 18); //00-6995.AUD	That's not what I heard. You wanna set the record straight?
					Actor_Says(kActorTyrellGuard, 380, 10); //17-0380.AUD	Oh, yeah, there-- There is one more thing.
					Actor_Says(kActorMcCoy, 8445, 14); //00-8445.AUD	Cough it up!
					Delay(1000);
					Actor_Says(kActorMcCoy, 1805, 14); //00-1805.AUD	Now!
					Delay(500);
					Actor_Modify_Friendliness_To_Other(kActorTyrellGuard, kActorMcCoy, -2);
				}
			} else {
				Actor_Says(kActorMcCoy, 5130, 13);
				Actor_Says(kActorTyrellGuard, 10, 15); //17-0010.AUD	Grav Test on the East Wing. 66th floor.
			}
			if (_vm->_cutContent) {	
				Item_Pickup_Spin_Effect_From_Actor(kModelAnimationVideoDisc, kActorMcCoy, 0, 0);
				Actor_Says(kActorTyrellGuard, 20, 23); //17-0020.AUD	Ah-- here's the footage from the security cameras. You get a pretty good look at the man's face.
				Actor_Change_Animation_Mode(kActorMcCoy, 23);
			} else {
				Item_Pickup_Spin_Effect(kModelAnimationVideoDisc, 351, 315);
				Actor_Says(kActorTyrellGuard, 20, 23); //17-0020.AUD	Ah-- here's the footage from the security cameras. You get a pretty good look at the man's face.
			}
			Actor_Says(kActorMcCoy, 5140, 17);
			if (_vm->_cutContent) {	
				if (Actor_Query_Friendliness_To_Other(kActorTyrellGuard, kActorMcCoy) > 49) {
					Actor_Says(kActorTyrellGuard, 30, 14);
					Actor_Says(kActorTyrellGuard, 40, 13);
					Actor_Clue_Acquire(kActorMcCoy, kClueTyrellGuardInterview, true, kActorTyrellGuard);
				} else {
					Actor_Says(kActorTyrellGuard, 400, 13); //17-0400.AUD	I'm a little busy for this, sir.
				}
			} else {
				Actor_Says(kActorTyrellGuard, 30, 14);
				Actor_Says(kActorTyrellGuard, 40, 13);
				Actor_Clue_Acquire(kActorMcCoy, kClueTyrellGuardInterview, true, kActorTyrellGuard);
			}
			Loop_Actor_Walk_To_XYZ(kActorMcCoy, -140.0f, 0.0f, 1586.0f, 12, false, false, false);
			Loop_Actor_Walk_To_XYZ(kActorMcCoy, -112.0f, 0.0f, 1586.0f, 12, false, false, false);
			Actor_Face_Actor(kActorMcCoy, kActorTyrellGuard, true);
			Actor_Face_Actor(kActorTyrellGuard, kActorMcCoy, true);
			Actor_Says(kActorMcCoy, 5145, 13);
			if (_vm->_cutContent) {	
				if (Actor_Query_Friendliness_To_Other(kActorTyrellGuard, kActorMcCoy) > 49) {
					Actor_Says(kActorTyrellGuard, 50, 15);
				}
			} else {
				Actor_Says(kActorTyrellGuard, 50, 15);
			}
			Actor_Face_Heading(kActorTyrellGuard, 788, false);
			// Made it so the source of the Tyrell security disc is the Tyrell guard.
			if (_vm->_cutContent) {
				Actor_Clue_Acquire(kActorMcCoy, kClueTyrellSecurity, true, kActorTyrellGuard);
			} else {
				Actor_Clue_Acquire(kActorMcCoy, kClueTyrellSecurity, true, -1);	
			}
			Game_Flag_Set(kFlagTB02GuardTalk1);
			Game_Flag_Set(kFlagTB02ElevatorToTB05);
			Player_Gains_Control();
			Loop_Actor_Walk_To_XYZ(kActorMcCoy, -138.17f, 0.15f, 1578.32f, 0, true, false, false);
		}

		if (Game_Flag_Query(kFlagTB02ElevatorToTB05)) {
			Scene_Exit_Add_2D_Exit(1, 430, 235, 487, 396, 0);
		}

		if ( Game_Flag_Query(kFlagTB05Entered)
		 && !Game_Flag_Query(kFlagTB02ElevatorToTB05)
		) {
			Actor_Says(kActorTyrellGuard, 90, 18);
			Game_Flag_Set(kFlagTB02ElevatorToTB05);
			Scene_Exit_Add_2D_Exit(1, 430, 235, 487, 396, 0);
		}

		if ( Game_Flag_Query(kFlagTB05Entered)
		 && !Game_Flag_Query(kFlagTB02SteeleTalk)
		) {
			Loop_Actor_Walk_To_Actor(kActorSteele, kActorMcCoy, 36, true, false);
			if (_vm->_cutContent) {
				Actor_Face_Actor(kActorMcCoy, kActorSteele, true);
				Actor_Face_Actor(kActorSteele, kActorMcCoy, true);
			}
			// Made it so Crystal is a 'little' nicer to you if you have high friendliness with her. The friendliness increase will be a result of you retiring Zuben
			// which will be added into his script page.
			if (_vm->_cutContent) {
				if (Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) > 51) {
					Actor_Says(kActorSteele, 2030, 14); //	01-2030.AUD	Been keeping yourself busy?
					Actor_Says(kActorMcCoy, 5245, 13); //00-5245.AUD	Guzza didn't say anything about me working with a partner.
					Actor_Says(kActorSteele, 2740, 12); //01-2740.AUD	That’s a big maybe.
					Delay(500);	
				} else {
					Actor_Says(kActorSteele, 2220, 14); //01-2220.AUD	Lagging behind again?
					Actor_Says(kActorMcCoy, 5245, 13); ////00-5245.AUD	Guzza didn't say anything about me working with a partner.
					Actor_Says(kActorSteele, 2230, 12); //01-2230.AUD	(laughs) Oh, in a pig's ass, Slim. No, I'm following up on my own.
					Actor_Says(kActorSteele, 2240, 13); //01-2240.AUD	Could be it's linked to this Tyrell debacle.
					Actor_Says(kActorMcCoy, 5250, 15); //00-5250.AUD	How's yours connected to mine?
					if (Actor_Query_Intelligence(kActorSteele) == 90) {
						Actor_Says(kActorSteele, 2300, 12); //01-2300.AUD	I'm still putting the pieces together. It's all stored in ESPER's mainframe.
					} else if (Actor_Query_Intelligence(kActorSteele) == 70) {
						Actor_Says(kActorSteele, 2250, 12); //01-2250.AUD	I'm still fitting the pieces together.
					}
				}
			} else {								
				Actor_Says(kActorSteele, 2220, 14); //01-2220.AUD	Lagging behind again?
				Actor_Says(kActorMcCoy, 5245, 13); ////00-5245.AUD	Guzza didn't say anything about me working with a partner.
				Actor_Says(kActorSteele, 2230, 12); //01-2230.AUD	(laughs) Oh, in a pig's ass, Slim. No, I'm following up on my own.
				Actor_Says(kActorSteele, 2240, 13); //01-2240.AUD	Could be it's linked to this Tyrell debacle.
			}
			if (_vm->_cutContent) {								
				if (Game_Flag_Query(kFlagSadikIsReplicant)) {
					Actor_Says(kActorSteele, 2260, 13); //01-2260.AUD	You know the moonbus massacre that went down last month?
					Actor_Says(kActorMcCoy, 5265, 12); //00-5265.AUD	Gaff mentioned something about it.
					if (Actor_Query_Intelligence(kActorSteele) == 90) {
						Actor_Says(kActorSteele, 2270, 16);
						Actor_Says(kActorSteele, 2280, 13); //01-2280.AUD	And one of them is a demolitions expert. Similar MO to your vic upstairs.
						Actor_Says(kActorMcCoy, 5270, 16);
						if (Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) > 51) {
							Actor_Says(kActorSteele, 2290, 14); //01-2290.AUD	I'll call you, if I find out anything more about your case.
							Actor_Says(kActorMcCoy, 5280, 13); //00-5280.AUD	Do that.
						}
						Actor_Clue_Acquire(kActorMcCoy, kClueCrystalsCase, true, kActorSteele);
					} else if (Actor_Query_Intelligence(kActorSteele) == 70) {
						Actor_Says(kActorSteele, 2320, 12); //01-2320.AUD	Could be our cases are overlapping. I might keep you posted.
					}
				} else {
					Actor_Says(kActorSteele, 2310, 15); //01-2310.AUD	You hear about the moonbus massacre?
					Actor_Says(kActorMcCoy, 5275, 14); //00-5275.AUD	Gaff mentioned it.
					Actor_Says(kActorSteele, 2320, 12); //01-2320.AUD	Could be our cases are overlapping. I might keep you posted.
				}
				Game_Flag_Set(kFlagTB02SteeleTalk);
				if (!Game_Flag_Query(kFlagTB06PhotographTalk1)) {
					Delay(500);
					Actor_Says(kActorMcCoy, 5255, 11); //00-5255.AUD	You take a look at this crime scene?
					Actor_Says(kActorSteele, 2330, 13);
					if (!Game_Flag_Query(kFlagTB05toTB06)) {
						Actor_Says(kActorMcCoy, 4880, 13); //00-4880.AUD	Is that right?
						Actor_Says(kActorSteele, 2340, 14); //01-2340.AUD	Make sure you skip a meal before you go up.
					} else {
						Actor_Says(kActorMcCoy, 5705, 18); //00-5705.AUD	Uh-huh.
					}
					Delay(500);
					if (Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) > 51) {
						Actor_Says(kActorMcCoy, 5260, 13); //00-5260.AUD	Happy trails, Steele.
						Actor_Says(kActorSteele, 2350, 13);
					}
				}
			} else {
				dialogueWithSteele();
			}
			if (_vm->_cutContent) {
				Player_Loses_Control();
				Delay(7000);
				Loop_Actor_Walk_To_XYZ(kActorMcCoy, -76.35f, 0.15f, 1564.2f, 0, true, false, false); 
				Actor_Face_Actor(kActorMcCoy, kActorTyrellGuard, true);
				Actor_Says(kActorMcCoy, 5165, 11);
				Actor_Says(kActorTyrellGuard, 100, 13);
				Actor_Says(kActorTyrellGuard, 110, 12);
				if (Player_Query_Agenda() == kPlayerAgendaPolite) {
					Actor_Says(kActorMcCoy, 5185, 15);
				} else {
					Actor_Says(kActorMcCoy, 8190, -1);	// 00-8190.AUD	Why?
				}
				if (Actor_Query_Friendliness_To_Other(kActorTyrellGuard, kActorMcCoy) > 49) {
					Actor_Says(kActorTyrellGuard, 120, 12);
					Actor_Says(kActorTyrellGuard, 130, 14);
					Actor_Says(kActorMcCoy, 5190, 16);
					Actor_Says(kActorTyrellGuard, 140, 13); //17-0140.AUD	Grav Test Chief Engineer.
					Actor_Says(kActorMcCoy, 8320, 13); //	00-8320.AUD	Really?
					Actor_Says(kActorTyrellGuard, 430, 13);	//17-0430.AUD	Here's what I heard just a little while ago.
					Actor_Says(kActorTyrellGuard, 150, 14); //17-0150.AUD	The lab runs tests to see how a Replicant would perform in different planetary gravitational fields. That kind of thing.
					Actor_Says(kActorTyrellGuard, 170, 12);
					Player_Gains_Control();
					Actor_Clue_Acquire(kActorMcCoy, kClueVictimInformation, true, kActorTyrellGuard);
				} else {
					Actor_Says(kActorTyrellGuard, 400, 13); //17-0400.AUD	I'm a little busy for this, sir.
					Player_Gains_Control();
				}
			}
		}
		//return false;
		return;
	}

	if ( chapter == 3
	 && !Game_Flag_Query(kFlagTB02GuardTalk2)
	) {
		Loop_Actor_Walk_To_XYZ(kActorMcCoy, -131.28f, 0.79f, 1448.25f, 12, true, false, false);
		Actor_Says(kActorTyrellGuard, 260, 15);
		Actor_Says(kActorMcCoy, 5225, 16);
		if (_vm->_cutContent) {
			if (Actor_Query_Friendliness_To_Other(kActorTyrellGuard, kActorMcCoy) < 50) {
				Actor_Says(kActorTyrellGuard, 270, 14); //17-0270.AUD	So why you're here?
				Actor_Says(kActorMcCoy, 5230, 15); //00-5230.AUD	Just looking around.
			}
		} else {
			Actor_Says(kActorTyrellGuard, 270, 14); //17-0270.AUD	So why you're here?
		}
		Game_Flag_Set(kFlagTB02GuardTalk2);
		if (!_vm->_cutContent) {
			Actor_Modify_Friendliness_To_Other(kActorTyrellGuard, kActorMcCoy, -1);
		}
	}
	//return false;
}

void SceneScriptTB02::PlayerWalkedOut() {
	Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
	Ambient_Sounds_Remove_All_Looping_Sounds(1u);
#if BLADERUNNER_ORIGINAL_BUGS
#else
	if (Global_Variable_Query(kVariableChapter) < 4
	    && !Game_Flag_Query(kFlagMcCoyInTyrellBuilding)
	) {
		// Acts 2, 3 - use a spinner fly-through transition
		Outtake_Play(kOuttakeTowards3, true, -1); // available in Acts 1, 2, 3
	}
#endif // BLADERUNNER_ORIGINAL_BUGS
}

void SceneScriptTB02::DialogueQueueFlushed(int a1) {
}

void SceneScriptTB02::dialogueWithTyrellGuard() {
	Dialogue_Menu_Clear_List();
	if (!_vm->_cutContent) {
		DM_Add_To_List_Never_Repeat_Once_Selected(700, 4, 5, 6); // VICTIM
	}

	if (_vm->_cutContent) {
		if (Actor_Clue_Query(kActorMcCoy, kClueDragonflyEarring)
		&& !Actor_Clue_Query(kActorMcCoy, kClueBombingSuspect)) {
			DM_Add_To_List_Never_Repeat_Once_Selected(710, 5, 5, 4); // EARRING
		}
	} else if (Actor_Clue_Query(kActorMcCoy, kClueDragonflyEarring)) {
		DM_Add_To_List_Never_Repeat_Once_Selected(710, 5, 5, 4); // EARRING
	}

	if (_vm->_cutContent) {
		if (Actor_Clue_Query(kActorMcCoy, kClueAttemptedFileAccess)) {
			DM_Add_To_List_Never_Repeat_Once_Selected(720, 1, 2, 3); // TYRELL
		}
	} else if (Actor_Clue_Query(kActorMcCoy, kClueVictimInformation)
	 || Actor_Clue_Query(kActorMcCoy, kClueAttemptedFileAccess)
	) {
		DM_Add_To_List_Never_Repeat_Once_Selected(720, 3, 5, 5); // TYRELL
	}

	if (Actor_Clue_Query(kActorMcCoy, kClueAttemptedFileAccess)) {
		DM_Add_To_List_Never_Repeat_Once_Selected(730, 3, 4, 8); // SECURITY
	}

	Dialogue_Menu_Add_DONE_To_List(100); // DONE

	Dialogue_Menu_Appear(320, 240);
	int answer = Dialogue_Menu_Query_Input();
	Dialogue_Menu_Disappear();

	switch (answer) {
	case 100: // DONE
		if (_vm->_cutContent) {
			Actor_Says(kActorMcCoy, 5145, 13);
			if (Actor_Query_Friendliness_To_Other(kActorTyrellGuard, kActorMcCoy) > 49) {
				Actor_Says(kActorTyrellGuard, 50, 15);
			}
			if (Player_Query_Agenda() == kPlayerAgendaPolite) {
				if (Actor_Clue_Query(kActorMcCoy, kClueTyrellSecurity)
				&& Actor_Clue_Query(kActorMcCoy, kClueTyrellSecurityPhoto)) {
					Delay(1000);
					Actor_Says(kActorMcCoy, 5150, 18); //00-5150.AUD	One more thing.
					Actor_Change_Animation_Mode(kActorMcCoy, 23);
					Actor_Change_Animation_Mode(kActorTyrellGuard, 23);
					Delay(800);
					Item_Pickup_Spin_Effect_From_Actor(kModelAnimationVideoDisc, kActorTyrellGuard, 0, 0);		
					Delay(800);
					Actor_Clue_Lose(kActorMcCoy, kClueTyrellSecurity);
					Actor_Clue_Acquire(kActorTyrellGuard, kClueTyrellSecurity, true, -1);
					Actor_Says(kActorMcCoy, 8170, 13); //00-8170.AUD	There you go.	
				}
			}
		} else {
			Actor_Says(kActorMcCoy, 5145, 13);
			Actor_Says(kActorTyrellGuard, 50, 15);
		}
		break;

	case 700: // VICTIM
		Actor_Says(kActorMcCoy, 5165, 11);
		Actor_Says(kActorTyrellGuard, 100, 13);
		Actor_Says(kActorTyrellGuard, 110, 12);
		Actor_Says(kActorMcCoy, 5185, 15);
		Actor_Says(kActorTyrellGuard, 120, 12);
		Actor_Says(kActorTyrellGuard, 130, 14);
		Actor_Says(kActorMcCoy, 5190, 16);
		Actor_Says(kActorTyrellGuard, 140, 13); //17-0140.AUD	Grav Test Chief Engineer.
		Actor_Says(kActorTyrellGuard, 150, 14); //17-0150.AUD	The lab runs tests to see how a Replicant would perform in different planetary gravitational fields. That kind of thing.
		Actor_Says(kActorTyrellGuard, 170, 12);
		Actor_Clue_Acquire(kActorMcCoy, kClueVictimInformation, true, kActorTyrellGuard);
		break;

	case 710: // EARRING
		if (_vm->_cutContent) {
			Actor_Says(kActorMcCoy, 5170, 23);
		} else {
			Actor_Says(kActorMcCoy, 5170, 12);
		}
		if (_vm->_cutContent) {
			if (Actor_Query_Friendliness_To_Other(kActorTyrellGuard, kActorMcCoy) < 50) {
				Actor_Says(kActorTyrellGuard, 400, 12); //17-0400.AUD	I'm a little busy for this, sir.
			} else {
				Actor_Says(kActorTyrellGuard, 180, 12);
				Actor_Says(kActorTyrellGuard, 190, 14);
				// Made it so McCoy also makes the Eisenduller mumu comment if he just saw the Tyrell security photo.
				// Also made it so McCoy and the guard won't pleasantly joke about Eisendullers mumu if they have low friendliness. 
				if (Game_Flag_Query(kFlagTB06Visited) 
				|| Actor_Clue_Query(kActorMcCoy, kClueTyrellSecurityPhoto)) {
					Actor_Says(kActorMcCoy, 5195, 13); //00-5195.AUD	How did Eisenduller's muumuu fit in?
					Actor_Says(kActorTyrellGuard, 200, 13); //17-0200.AUD	Heh. Hey, you know company rules only apply to the lesser mortals.
				}
			}
			Actor_Says(kActorTyrellGuard, 440, 13); //17-0440.AUD	You wanna leave it for pickup?
			if (Player_Query_Agenda() == kPlayerAgendaPolite
			&& !Actor_Clue_Query(kActorMcCoy, kClueBombingSuspect)) {
				Actor_Says(kActorMcCoy, 8000, 16); //00-8000.AUD	Yes.
				Actor_Change_Animation_Mode(kActorTyrellGuard, 23);
				Actor_Change_Animation_Mode(kActorMcCoy, 23);
				Delay(800);
				Item_Pickup_Spin_Effect_From_Actor(kModelAnimationDragonflyEarring, kActorTyrellGuard, 0, 0);
				Delay(800);
				Actor_Clue_Lose(kActorMcCoy, kClueDragonflyEarring);
			} else {
				Actor_Says(kActorMcCoy, 7815, 16); //00-7815.AUD	No.
			}
		} else {
			Actor_Says(kActorTyrellGuard, 180, 12);
			Actor_Says(kActorTyrellGuard, 190, 14);
			if (Game_Flag_Query(kFlagTB06Visited)) {
				Actor_Says(kActorMcCoy, 5195, 13); //00-5195.AUD	How did Eisenduller's muumuu fit in?
				Actor_Says(kActorTyrellGuard, 200, 13); //17-0200.AUD	Heh. Hey, you know company rules only apply to the lesser mortals.
			}
		}
		break;

	case 720: // TYRELL
		Actor_Says(kActorMcCoy, 5175, 12);
		Actor_Says(kActorTyrellGuard, 210, 14);
		Actor_Says(kActorMcCoy, 5200, 13); //00-5200.AUD	Okay. How do I make him wanna to see me?
		// Made it so if McCoy and the guard have low friendliness he will not elaborate on how to arrange a meeting with Tyrell.
		if (_vm->_cutContent) {
			if (Actor_Query_Friendliness_To_Other(kActorTyrellGuard, kActorMcCoy) < 50) {
				Actor_Says(kActorTyrellGuard, 400, 12); //17-0400.AUD	I'm a little busy for this, sir.
				Game_Flag_Set(kFlagTyrellGuardTalkMeeting);
			} else {
				Actor_Says(kActorTyrellGuard, 220, 13); //17-0220.AUD	Well, you could call his personal assistant.
				Actor_Says(kActorMcCoy, 5205, 15);
				Actor_Says(kActorTyrellGuard, 230, 12);
				if (Player_Query_Agenda() != kPlayerAgendaPolite) {
					Actor_Says(kActorMcCoy, 3910, 14); //00-3910.AUD	You’re lying.
					Actor_Says(kActorTyrellGuard, 410, 12);	//17-0410.AUD	What I said is the truth, sir.
					if (Player_Query_Agenda() == kPlayerAgendaSurly
					|| Player_Query_Agenda() == kPlayerAgendaErratic) {
						Actor_Says(kActorMcCoy, 8519, 15); //00-8519.AUD	What do you say we dish each other the straight goods.
						Actor_Says(kActorTyrellGuard, 400, 12); //17-0400.AUD	I'm a little busy for this, sir.
						Actor_Modify_Friendliness_To_Other(kActorTyrellGuard, kActorMcCoy, -2);
					}
				} else {
					Actor_Says(kActorMcCoy, 5210, 12);
				}
				// Added a flag here so instead of the clue attempted file access being the trigger that allows you to ask Guzza for a meeting with Tyrell
				// instead it will be this flag that activates after the guard denies you a meeting.
				Game_Flag_Set(kFlagTyrellGuardTalkMeeting);
			}
			ADQ_Add(kActorDispatcher, 60, kAnimationModeTalk); //38-0060.AUD	BR-61661, report to division Headquarters. Code 3, repeat, code 3.
		} else {		
			Actor_Says(kActorTyrellGuard, 220, 13);
			Actor_Says(kActorMcCoy, 5205, 15);
			Actor_Says(kActorTyrellGuard, 230, 12);
			Actor_Says(kActorMcCoy, 5210, 12);
		// Added a flag here so instead of the clue attempted file access being the trigger that allows you to ask Guzza for a meeting with Tyrell
		// instead it will be this flag that activates after the guard denies you a meeting.
		}
		break;

	case 730: // SECURITY
		Actor_Says(kActorMcCoy, 5180, 16);
		if (_vm->_cutContent) {
			if (Actor_Query_Friendliness_To_Other(kActorTyrellGuard, kActorMcCoy) < 50) {
				Actor_Says(kActorTyrellGuard, 390, 13); //17-0390.AUD	I've told you everything I know, sir.
			} else {
				Actor_Says(kActorTyrellGuard, 240, 12);
				Actor_Says(kActorMcCoy, 5215, 18);
				Actor_Says(kActorTyrellGuard, 250, 13);
				if (Player_Query_Agenda() == kPlayerAgendaPolite) {
					Actor_Says(kActorMcCoy, 5220, 16);
				} else {
					Actor_Says(kActorMcCoy, 5705, 18); //00-5705.AUD	Uh-huh.
				}
			}
		} else {
			Actor_Says(kActorTyrellGuard, 240, 12);
			Actor_Says(kActorMcCoy, 5215, 18);
			Actor_Says(kActorTyrellGuard, 250, 13);
			Actor_Says(kActorMcCoy, 5220, 16);
		}
		break;
	}
}

void SceneScriptTB02::dialogueWithSteele() {
	Dialogue_Menu_Clear_List();
	DM_Add_To_List_Never_Repeat_Once_Selected(740, 4, 5, 6); // HER CASE
	DM_Add_To_List_Never_Repeat_Once_Selected(750, 3, 5, 5); // MURDER
	Dialogue_Menu_Add_DONE_To_List(100); // DONE

	Dialogue_Menu_Appear(320, 240);
	int answer = Dialogue_Menu_Query_Input();
	Dialogue_Menu_Disappear();

	switch (answer) {
	case 100: // DONE
		Actor_Says(kActorSteele, 2350, 13);
		if (!_vm->_cutContent) {
			Actor_Modify_Friendliness_To_Other(kActorSteele, kActorMcCoy, -5);
		}
		Game_Flag_Set(kFlagTB02SteeleTalk);
		break;

	case 740: // HER CASE
		Actor_Says(kActorMcCoy, 5250, 15);
		if (Game_Flag_Query(kFlagSadikIsReplicant)) {
			Actor_Says(kActorSteele, 2250, 12);
			Actor_Says(kActorSteele, 2260, 13);
			Actor_Says(kActorMcCoy, 5265, 12);
			Actor_Says(kActorSteele, 2270, 16);
			Actor_Says(kActorSteele, 2280, 13);
			Actor_Says(kActorMcCoy, 5270, 16);
			Actor_Says(kActorSteele, 2290, 14);
			Actor_Clue_Acquire(kActorMcCoy, kClueCrystalsCase, true, kActorSteele);
			Actor_Modify_Friendliness_To_Other(kActorSteele, kActorMcCoy, 1);
			Game_Flag_Set(kFlagTB02SteeleTalk);
		} else {
			Actor_Says(kActorSteele, 2300, 12);
			Actor_Says(kActorSteele, 2310, 15);
			Actor_Says(kActorMcCoy, 5275, 14);
			Actor_Says(kActorSteele, 2320, 12);
			Actor_Says(kActorMcCoy, 5280, 13);
			Actor_Modify_Friendliness_To_Other(kActorSteele, kActorMcCoy, 1);
			Game_Flag_Set(kFlagTB02SteeleTalk);
		}
		break;

	case 750: // MURDER
		Actor_Says(kActorMcCoy, 5255, 11);
		Actor_Says(kActorSteele, 2330, 13);
		Actor_Says(kActorSteele, 2340, 14);
		Game_Flag_Set(kFlagTB02SteeleTalk);
		break;
	}
}

} // End of namespace BladeRunner
