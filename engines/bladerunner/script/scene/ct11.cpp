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

enum kCT11Loops {
	kCT11LoopMainLoop  = 0,
	kCT11LoopMainNoCar = 2
};

void SceneScriptCT11::InitializeScene() {
	if (Game_Flag_Query(kFlagCT12toCT11)) {
		Setup_Scene_Information(-378.0f, 9.68f, -55.0f, 440);
	} else if (Game_Flag_Query(kFlagDR01toCT11)) {
		Setup_Scene_Information( 315.0f,  0.0f, 628.0f,   0);
	} else {
		Setup_Scene_Information( 152.0f, 9.68f,  -8.0f,   0);
	}

	Scene_Exit_Add_2D_Exit(0, 257, 240, 364, 330, 1);
	Scene_Exit_Add_2D_Exit(1,  97,   0, 155, 324, 0);
	Scene_Exit_Add_2D_Exit(2,   0,   0,  20, 479, 3);

	Ambient_Sounds_Add_Looping_Sound(kSfxCTRAIN1, 50, 0, 1);
	Ambient_Sounds_Add_Sound(kSfxSPIN2A, 5, 80, 16,  25, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSPIN1A, 5, 80, 16,  25, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxTHNDR1, 5, 80, 50, 100, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxTHNDR2, 5, 80, 50, 100, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxTHNDR3, 5, 80, 50, 100, -100, 100, -101, -101, 0, 0);

	if (Global_Variable_Query(kVariableChapter) > 3) {
		Scene_Loop_Set_Default(kCT11LoopMainNoCar);
	} else {
		Scene_Loop_Set_Default(kCT11LoopMainLoop);
	}
}

void SceneScriptCT11::SceneLoaded() {
	Obstacle_Object("TRASH CAN", true);
	Unobstacle_Object("BOX NORTHWEST 1", true);
	Unobstacle_Object("BOX SOUTH 1", true);
	if (Global_Variable_Query(kVariableChapter) < 4) {
		if (_vm->_cutContent) {
			if (!Game_Flag_Query(kFlagCT11DogWrapperTaken)) {
				if (!Game_Flag_Query(kFlagGordoIsReplicant)) {
					Item_Add_To_World(kItemDogWrapper, kModelAnimationLichenDogWrapper, kSetCT11, 640.21f, 30.0f, 470.0f, 512, 12, 12, false, true, false, true);
					Scene_2D_Region_Add(0, 505, 316, 513, 321);
					Game_Flag_Set(kFlagCT11DogWrapperAvailable);
				}
			}
		} else {
			if (!Game_Flag_Query(kFlagCT11DogWrapperTaken)) {
				Item_Add_To_World(kItemDogWrapper, kModelAnimationLichenDogWrapper, kSetCT11, 640.21f, 30.0f, 470.0f, 512, 12, 12, false, true, false, true);
				Scene_2D_Region_Add(0, 505, 316, 513, 321);
				Game_Flag_Set(kFlagCT11DogWrapperAvailable);
			}
		}
		if (_vm->_cutContent) {
			if (!Actor_Clue_Query(kActorMcCoy, kClueLicensePlate)) {
				if (!Game_Flag_Query(kFlagGordoIsReplicant)) {
					Item_Add_To_World(kItemChopstickWrapper, kModelAnimationLicensePlate, kSetCT11, 617.45f, 0.81f, 654.48f, 512, 12, 12, false, true, false, true);
					Scene_2D_Region_Add(5, 380, 370, 470, 377);
				}
			}
		}
		// Made it so Grigorians note will appear in the car under any circumstance other than Gordo being a replicant and Dektora being human. If that is the case the reps never would have gone to Crazylegs and
		// Grigorians note to Crazylegs wouldn't be in the car.
		if (_vm->_cutContent) {
		    if (!Actor_Clue_Query(kActorMcCoy, kClueGrigoriansNote)) {
				if (Game_Flag_Query(kFlagDektoraIsReplicant)
				&& !Game_Flag_Query(kFlagGordoIsReplicant)) {
					Item_Add_To_World(kItemNote, kModelAnimationGrigoriansNote, kSetCT11, 641.21f, 26.0f, 472.0f, 304, 12, 12, false, true, false, true);
					Scene_2D_Region_Add(2, 505, 321, 519, 332);
				} else if (!Game_Flag_Query(kFlagDektoraIsReplicant)
				&& !Game_Flag_Query(kFlagGordoIsReplicant)) {
					Item_Add_To_World(kItemNote, kModelAnimationGrigoriansNote, kSetCT11, 641.21f, 26.0f, 472.0f, 304, 12, 12, false, true, false, true);
					Scene_2D_Region_Add(2, 505, 321, 519, 332);
				}
			}
		}

		if (!Actor_Clue_Query(kActorMcCoy, kClueCar)) {
#if BLADERUNNER_ORIGINAL_BUGS
			Scene_2D_Region_Add(1, 412, 258, 552, 358);
#else
			// expand region 1 a bit and add two more
			// as auxilliary in order to better cover the car area
			Scene_2D_Region_Add(1, 365, 258, 460, 358);
			Scene_2D_Region_Add(3, 267, 330, 460, 377);
			Scene_2D_Region_Add(4, 365, 358, 460, 377);
#endif // BLADERUNNER_ORIGINAL_BUGS
		}
	} else {
		if (Game_Flag_Query(kFlagCT11DogWrapperAvailable)) {
			Item_Remove_From_World(kItemDogWrapper);
			Game_Flag_Reset(kFlagCT11DogWrapperAvailable);
			Game_Flag_Set(kFlagCT11DogWrapperTaken);
		}
		// Check if Grigorian's note is still in the world after Act 3
		// and remove it (in cut content)
		if (_vm->_cutContent
		    && Game_Flag_Query(kFlagCT11GrigorianNotePlaced)
		    && !Actor_Clue_Query(kActorMcCoy, kClueGrigoriansNote)) {
			Item_Remove_From_World(kItemNote);
			Game_Flag_Reset(kFlagCT11GrigorianNotePlaced);
		}

		Unobstacle_Object("BRIDGE SUPPORT", true);
		Unobstacle_Object("BODY", true);
		Unobstacle_Object("HEADLIGHTS", true);
		Unobstacle_Object("LICENSE PLATE-FRONT", true);
		Unobstacle_Object("LICENSE PLATE-REAR", true);
		Unobstacle_Object("BRAKE DISC RF", true);
		Unobstacle_Object("TIRE RF", true);
		Unobstacle_Object("RIM RF", true);
		Unobstacle_Object("DOOR RIGHT", true);
		Unobstacle_Object("BUMPER REAR", true);
#if BLADERUNNER_ORIGINAL_BUGS
#else
		// this street sign blocks police officers from moving to waypoint 386 after they reach waypoint 242
		Unobstacle_Object("STREET SIGN", true);
#endif // BLADERUNNER_ORIGINAL_BUGS
	}
	Unclickable_Object("TRASH CAN");
}

bool SceneScriptCT11::MouseClick(int x, int y) {
	return false;
}

bool SceneScriptCT11::ClickedOn3DObject(const char *objectName, bool a2) {
	return false;
}

bool SceneScriptCT11::ClickedOnActor(int actorId) {
	return false;
}

bool SceneScriptCT11::ClickedOnItem(int itemId, bool a2) {
	if (itemId == kItemChopstickWrapper) {
		if (!Loop_Actor_Walk_To_Item(kActorMcCoy, kItemChopstickWrapper, 36, true, false)) {
			Actor_Face_Item(kActorMcCoy, kItemChopstickWrapper, true);
			if (Actor_Clue_Query(kActorMcCoy, kCluePartialLicenseNumber)
			|| Actor_Clue_Query(kActorMcCoy, kClueCar)) {	
				Item_Pickup_Spin_Effect(kModelAnimationLicensePlate, 279, 388);
				Item_Remove_From_World(kItemChopstickWrapper);
				Actor_Says(kActorMcCoy, 8760, 13); //00-8760.AUD	A license plate.
				Actor_Clue_Acquire(kActorMcCoy, kClueLicensePlate, true, -1);
				if (Actor_Clue_Query(kActorMcCoy, kCluePartialLicenseNumber)) {
					Delay(500);
					Actor_Voice_Over(4190, kActorVoiceOver); //99-4190.AUD	Where have I seen that before?
					Delay(1000);
					Actor_Says(kActorMcCoy, 8525, 9); //00-8525.AUD	Hmph.
					Actor_Change_Animation_Mode(kActorMcCoy, 23);
					Delay(800);
					Actor_Says(kActorAnsweringMachine, 390, kAnimationModeTalk); // 39-0390.AUD	Begin test.
					Ambient_Sounds_Play_Sound(kSfxDATALOAD, 50, 0, 0, 99);
					Delay(2000);
					Ambient_Sounds_Play_Sound(kSfxBEEPNEAT, 80, 0, 0, 99);
					Actor_Says(kActorAnsweringMachine, 420, 19); //39-0420.AUD	Positive result.
					Actor_Says(kActorAnsweringMachine, 470, kAnimationModeTalk); //39-0470.AUD	End test.
					Actor_Says(kActorMcCoy, 7200, 13); //00-7200.AUD	Bingo.
					Actor_Clue_Acquire(kActorMcCoy, kClueLicensePlateMatch, true, -1); 
					if (Game_Flag_Query(kFlagKleinCarIdentityTalk)
					&& !Actor_Clue_Query(kActorMcCoy, kClueCar)
					&& !Actor_Clue_Query(kActorMcCoy, kClueCarRegistration1)
					&& !Actor_Clue_Query(kActorMcCoy, kClueCarRegistration2)
					&& !Actor_Clue_Query(kActorMcCoy, kClueCarRegistration3)) {
						Actor_Voice_Over(540, kActorVoiceOver); //99-0540.AUD	If I ran it through the Mainframe back at the station, I could ID the owner.
					}
				}
			} else {
				Actor_Says(kActorMcCoy, 8760, 13); //00-8760.AUD	A license plate.
				Actor_Says(kActorMcCoy, 8525, 9); //00-8525.AUD	Hmph.
			}
		}
	}
	return false;
}

bool SceneScriptCT11::ClickedOnExit(int exitId) {
	if (exitId == 0) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, 121.0f, 9.68f, -42.0f, 0, true, false, false)) {
			Set_Enter(kSetCT09, kSceneCT09);
		}
		return true;
	}

	if (exitId == 1) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -300.0f, 9.68f, 66.0f, 0, true, false, false)) {
			Loop_Actor_Walk_To_XYZ(kActorMcCoy, -400.0f, 9.68f, -70.0f, 0, true, false, false);
			Game_Flag_Set(kFlagCT11toCT12);
			Set_Enter(kSetCT01_CT12, kSceneCT12);
		}
		return true;
	}

	if (exitId == 2) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, 290.0f, 0.0f, 635.0f, 0, true, false, false)) {
			Game_Flag_Set(kFlagCT11toDR01);
			Game_Flag_Reset(kFlagMcCoyInChinaTown);
			Game_Flag_Set(kFlagMcCoyInDNARow);
			Set_Enter(kSetDR01_DR02_DR04, kSceneDR01);
		}
		return true;
	}
	return false;
}

bool SceneScriptCT11::ClickedOn2DRegion(int region) {
	if (region == 0 && Game_Flag_Query(kFlagCT11DogWrapperAvailable)) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, 686.0f, 0.0f, 658.0f, 12, true, false, false)) {
			Actor_Face_Heading(kActorMcCoy, 47, false);
			// Made it so McCoy will only pick up the lichen dog wrapper from within the car if he has found enough clues to deem the car suspicious.
			if (_vm->_cutContent) {
				if (Actor_Clue_Query(kActorMcCoy, kClueCar)
				|| Actor_Clue_Query(kActorMcCoy, kClueLicensePlateMatch)
				|| Game_Flag_Query(kFlagCarFound)) {
					Item_Remove_From_World(kItemDogWrapper);		
					Actor_Clue_Acquire(kActorMcCoy, kClueLichenDogWrapper, false, kActorMurray);
					Item_Pickup_Spin_Effect(kModelAnimationLichenDogWrapper, 510, 319);
					Game_Flag_Reset(kFlagCT11DogWrapperAvailable);
					Game_Flag_Set(kFlagCT11DogWrapperTaken);
					Actor_Says(kActorMcCoy, 8865, 13); //00-8865.AUD	A lichen-dog wrapper.
					Actor_Voice_Over(550, kActorVoiceOver);
					Actor_Voice_Over(560, kActorVoiceOver);
					Actor_Voice_Over(570, kActorVoiceOver);
					Actor_Voice_Over(580, kActorVoiceOver);
		#if !BLADERUNNER_ORIGINAL_BUGS
					// in the original game the hotspot would not be removed
					// after picking up the lichendog Wrapper
					Scene_2D_Region_Remove(0);
		#endif // !BLADERUNNER_ORIGINAL_BUGS
				} else {
					Actor_Says(kActorMcCoy, 8865, 13); //00-8865.AUD	A lichen-dog wrapper.
					Actor_Says(kActorMcCoy, 8525, -1); // 00-8525.AUD	Hmph.
				}
			} else {
				Item_Remove_From_World(kItemDogWrapper);		
				Actor_Clue_Acquire(kActorMcCoy, kClueLichenDogWrapper, false, kActorMurray);
				Item_Pickup_Spin_Effect(kModelAnimationLichenDogWrapper, 510, 319);
				Game_Flag_Reset(kFlagCT11DogWrapperAvailable);
				Game_Flag_Set(kFlagCT11DogWrapperTaken);
				Actor_Says(kActorMcCoy, 8865, 13); //00-8865.AUD	A lichen-dog wrapper.
				Actor_Voice_Over(550, kActorVoiceOver);
				Actor_Voice_Over(560, kActorVoiceOver);
				Actor_Voice_Over(570, kActorVoiceOver);
				Actor_Voice_Over(580, kActorVoiceOver);
		#if !BLADERUNNER_ORIGINAL_BUGS
				// in the original game the hotspot would not be removed
				// after picking up the lichendog Wrapper
				Scene_2D_Region_Remove(0);
		#endif // !BLADERUNNER_ORIGINAL_BUGS
			}
		}
		return true;
	}

	if (_vm->_cutContent
	    && region == 2
	    && !Actor_Clue_Query(kActorMcCoy, kClueGrigoriansNote)
	) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, 686.0f, 0.0f, 658.0f, 12, true, false, false)) {
			Actor_Face_Heading(kActorMcCoy, 47, false);
			if (Actor_Clue_Query(kActorMcCoy, kClueCar)
			|| Actor_Clue_Query(kActorMcCoy, kClueLicensePlateMatch)
			|| Game_Flag_Query(kFlagCarFound)) {
				Item_Remove_From_World(kItemNote);
				Actor_Clue_Acquire(kActorMcCoy, kClueGrigoriansNote, false, -1);
				Item_Pickup_Spin_Effect(kModelAnimationGrigoriansNote, 512, 326);
				Actor_Says(kActorMcCoy, 8840, 13); //00-8840.AUD	A note.
				Scene_2D_Region_Remove(2);
			} else {
				Actor_Says(kActorMcCoy, 8525, -1); // 00-8525.AUD	Hmph.
			}
		}
		return true;
	}

	if (region == 1
#if !BLADERUNNER_ORIGINAL_BUGS
	    || region == 3
	    || region == 4
#endif // !BLADERUNNER_ORIGINAL_BUGS
	) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, 686.0f, 0.0f, 658.0f, 12, true, false, false)) {
			Actor_Face_Heading(kActorMcCoy, 47, false);
			if (_vm->_cutContent) {
				int cluesFound = 0;
				if (Actor_Clue_Query(kActorMcCoy, kClueCrowdInterviewB)) {
					++cluesFound;
				}
				if (Actor_Clue_Query(kActorMcCoy, kCluePaintTransfer)) {
					++cluesFound;
				}
				if (Actor_Clue_Query(kActorMcCoy, kClueDispatchHitAndRun)) {
					++cluesFound;
				}
				if (Actor_Clue_Query(kActorMcCoy, kClueLabPaintTransfer)) {
					++cluesFound;
				}
				if (Actor_Clue_Query(kActorMcCoy, kClueChromeDebris)) {
					++cluesFound;
				}
				if (Actor_Clue_Query(kActorMcCoy, kClueLicensePlateMatch)) {
					++cluesFound;
				}
				if (Actor_Clue_Query(kActorMcCoy, kClueLicensePlate)) {
					++cluesFound;
				}
				if (Actor_Clue_Query(kActorMcCoy, kClueCarColorAndMake)) {
					++cluesFound;
				}
				if (Actor_Clue_Query(kActorMcCoy, kCluePartialLicenseNumber)) {
					++cluesFound;
				}
				if (cluesFound > 4
				&& !Actor_Clue_Query(kActorMcCoy, kClueCar)
				) {
					Actor_Voice_Over(510, kActorVoiceOver);
					Actor_Clue_Acquire(kActorMcCoy, kClueCar, false, -1);
					Game_Flag_Set(kFlagCarFound);
					// Made it so McCoy only gets the car identity clue if he was told by Dino how to identify the car by using the vehicle identification number.
					if (Game_Flag_Query(kFlagKleinCarIdentityTalk)
					&& !Actor_Clue_Query(kActorMcCoy, kClueCarRegistration1)
					&& !Actor_Clue_Query(kActorMcCoy, kClueCarRegistration2)
					&& !Actor_Clue_Query(kActorMcCoy, kClueCarRegistration3)
					) {
						if (Game_Flag_Query(kFlagGordoIsReplicant)) {
							Actor_Voice_Over(520, kActorVoiceOver); //99-0520.AUD	The driver had been smart enough to pull the license plate.
						} else {
							Actor_Says(kActorMcCoy, 8524, -1); //00-8524.AUD	That's a washout.
							Delay(500);
						}
						Actor_Voice_Over(530, kActorVoiceOver);
						Actor_Voice_Over(540, kActorVoiceOver);
					}
					Scene_2D_Region_Remove(1);
#if !BLADERUNNER_ORIGINAL_BUGS
					Scene_2D_Region_Remove(3);
					Scene_2D_Region_Remove(4);
#endif // !BLADERUNNER_ORIGINAL_BUGS
				} else {
					Actor_Says(kActorMcCoy, 8524, 13); //00-8524.AUD	That's a washout.
					Actor_Says(kActorMcCoy, 8525, 12); //00-8525.AUD	Hmph.
				}
			} else {
				int cluesFound = 0;
				if (Actor_Clue_Query(kActorMcCoy, kClueCrowdInterviewB)) {
					++cluesFound;
				}
				if (Actor_Clue_Query(kActorMcCoy, kCluePaintTransfer)) {
					++cluesFound;
				}
				if (Actor_Clue_Query(kActorMcCoy, kClueLabPaintTransfer)) {
					++cluesFound;
				}
				if (Actor_Clue_Query(kActorMcCoy, kClueLicensePlate)) {
					cluesFound += 2;
				}
				if (Actor_Clue_Query(kActorMcCoy, kClueCarColorAndMake)) {
					cluesFound += 2;
				}
				if (Actor_Clue_Query(kActorMcCoy, kCluePartialLicenseNumber)) {
					cluesFound += 2;
				}
				if ( cluesFound > 2
				&& !Actor_Clue_Query(kActorMcCoy, kClueCar)
				) {
					Actor_Voice_Over(510, kActorVoiceOver);
					Actor_Voice_Over(520, kActorVoiceOver);
					Actor_Voice_Over(530, kActorVoiceOver);
					Actor_Voice_Over(540, kActorVoiceOver);
					Actor_Clue_Acquire(kActorMcCoy, kClueCar, false, -1);
					Scene_2D_Region_Remove(1);
				}
			}
#if !BLADERUNNER_ORIGINAL_BUGS
			Scene_2D_Region_Remove(3);
			Scene_2D_Region_Remove(4);
#endif // !BLADERUNNER_ORIGINAL_BUGS
		}
		return true;
	}
	return false;
}

void SceneScriptCT11::SceneFrameAdvanced(int frame) {
}

void SceneScriptCT11::ActorChangedGoal(int actorId, int newGoal, int oldGoal, bool currentSet) {
}

void SceneScriptCT11::PlayerWalkedIn() {
	if (Game_Flag_Query(kFlagCT12toCT11)) {
		Loop_Actor_Walk_To_XYZ(kActorMcCoy, -358.0f, 9.68f, 32.0f, 0, false, false, false);
		Game_Flag_Reset(kFlagCT12toCT11);
	} else if (Game_Flag_Query(kFlagDR01toCT11)) {
		Loop_Actor_Walk_To_XYZ(kActorMcCoy, 329.0f, 0.0f, 617.0f, 0, false, false, false);
		Game_Flag_Reset(kFlagDR01toCT11);
	} else {
		Player_Loses_Control();
		Actor_Set_Immunity_To_Obstacles(kActorMcCoy, true);
		Loop_Actor_Walk_To_XYZ(kActorMcCoy, 125.0f, 9.68f, 74.0f, 0, false, false, false);
		Actor_Set_Immunity_To_Obstacles(kActorMcCoy, false);
		Player_Gains_Control();
	}
	if (_vm->_cutContent) {
		if (!Game_Flag_Query(kFlagCT11Visited)) {
			Game_Flag_Set (kFlagCT11Visited);
			Actor_Set_Goal_Number(kActorDeskClerk, kGoalDeskClerkRecovered);
			ADQ_Add(kActorDispatcher, 220, kAnimationModeTalk); //38-0220.AUD	Attention all Sector 3 units.
			ADQ_Add(kActorDispatcher, 230, kAnimationModeTalk); //38-0230.AUD	Be advised. 2-11 in progress. Kitty Hawk Savings and Loan. Corner of Peach and Lincoln.
			ADQ_Add(kActorOfficerGrayford, 490, kAnimationModeTalk); // 24-0490.AUD	LA, 34 Metro 3. Copied. ETA two minutes. Be advised 34 is a two men Unit.
			ADQ_Add(kActorDispatcher, 240, kAnimationModeTalk); //38-0240.AUD	Units responding identify..
			ADQ_Add(kActorOfficerGrayford, 500, kAnimationModeTalk); //24-0500.AUD	LA, Two men Unit 32 Metro 3 is responding to provide backup. ETA three minutes.
			ADQ_Add(kActorDispatcher, 250, kAnimationModeTalk); //38-0250.AUD	LA Copy. Units 34 and 32 en route. 2-11 in progress at Peach and Lincoln.
			ADQ_Add(kActorDispatcher, 260, kAnimationModeTalk); //38-0260.AUD	All Sector 3 units. Hold your traffic until we confirm a Code 4.
			ADQ_Add_Pause(1000);
			ADQ_Add(kActorOfficerGrayford, 510, kAnimationModeTalk); //24-0510.AUD	LA, Units 34 and 32 are 10-97
			ADQ_Add(kActorDispatcher, 270, kAnimationModeTalk); //38-0270.AUD	LA Copy. 34 and 32 at 10-97 at the scene. All Third Sector Units stand by.
			ADQ_Add_Pause(1000);
			ADQ_Add(kActorOfficerGrayford, 410 , kAnimationModeTalk); // 24-0410.AUD	LA, This is 32 Metro 3. Code 4. Two suspects in custody.
			ADQ_Add(kActorDispatcher, 280, kAnimationModeTalk);	//38-0280.AUD	32 Metro 3. 10-4. LA Copy. Code 4. Two in custody.
			ADQ_Add(kActorDispatcher, 290, kAnimationModeTalk); //38-0290.AUD	Attention all Third Sector units. We have a Code 4 at the Kitty Hawk Savings and Loan. LA clear. Resume normal traffic.
		}	
	}
}

void SceneScriptCT11::PlayerWalkedOut() {
	Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
	Ambient_Sounds_Remove_All_Looping_Sounds(1u);
}

void SceneScriptCT11::DialogueQueueFlushed(int a1) {
}

} // End of namespace BladeRunner
