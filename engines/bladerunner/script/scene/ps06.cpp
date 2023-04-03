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

void SceneScriptPS06::InitializeScene() {
	Setup_Scene_Information(11257.26f, 707.3f, -4778.31f, 120);

	Scene_Exit_Add_2D_Exit(0, 610, 0, 639, 479, 1);

	Ambient_Sounds_Remove_All_Non_Looping_Sounds(false);
	Ambient_Sounds_Add_Looping_Sound(kSfxESPLOOP3, 50, 1, 1);
}

void SceneScriptPS06::SceneLoaded() {
	Obstacle_Object("E.SCREEN02", true);
	Clickable_Object("E.SCREEN02");
	Clickable_Object("E.MONITOR1");
	Clickable_Object("E.SCREEN03");
	Clickable_Object("E.MONITOR3");
}

bool SceneScriptPS06::MouseClick(int x, int y) {
	return false;
}

bool SceneScriptPS06::ClickedOn3DObject(const char *objectName, bool a2) {
	if (Object_Query_Click("E.MONITOR1", objectName)) {
		if (_vm->_cutContent) {
			Actor_Face_Object(kActorMcCoy, "E.MONITOR1", true);
			Actor_Change_Animation_Mode(kActorMcCoy, 23);
			Delay(800);
		}
		ESPER_Flag_To_Activate();
		return true;
	}
	if (Object_Query_Click("E.SCREEN03", objectName)
	 || Object_Query_Click("E.MONITOR3", objectName)
	) {
		if (_vm->_cutContent) {
			Actor_Face_Object(kActorMcCoy, "E.MONITOR3", true);
			Actor_Change_Animation_Mode(kActorMcCoy, 23);
			Delay(800);
		}
		Actor_Says(kActorAnsweringMachine, 330, kAnimationModeTalk); // uploading clues
		if (_vm->_cutContent) {
			if (Global_Variable_Query(kVariableChapter) > 1) {
				Actor_Clue_Acquire(kActorMcCoy, kClueCrimeSceneNotes,  true, kActorSteele);
				Actor_Clue_Acquire(kActorMcCoy, kClueGrigorianInterviewA, true, kActorSteele);
				if (Game_Flag_Query(kFlagIzoIsReplicant)) {
					Actor_Clue_Acquire(kActorMcCoy, kClueGrigorianInterviewB1,  true, kActorSteele);
				} else {
					Actor_Clue_Acquire(kActorMcCoy, kClueGrigorianInterviewB2,  true, kActorSteele);
				}
			}
			if (!Game_Flag_Query(kFlagCrazylegsDead)
			&& Actor_Query_Intelligence(kActorSteele) == 90) {
				if (!Game_Flag_Query(kFlagCrazylegsIsReplicant)) {			
					if (Actor_Clue_Query(kActorMcCoy, kClueCrazysInvolvement)
					|| Actor_Clue_Query(kActorMcCoy, kClueCrazylegsInterview1)
					|| Actor_Clue_Query(kActorMcCoy, kClueCrazylegsInterview2)
					|| Actor_Clue_Query(kActorMcCoy, kClueDektoraConfession)) {
						Actor_Clue_Acquire(kActorMcCoy, kClueVKCrazylegsHuman,  true, kActorSteele);
						Actor_Clue_Acquire(kActorMcCoy, kClueCrystalTestedCrazylegs, true, kActorSteele);
						Actor_Clue_Acquire(kActorMcCoy, kClueCrystalArrestedCrazylegs, true, kActorSteele);
						Game_Flag_Set(kFlagCrazylegsArrested);
						Actor_Put_In_Set(kActorCrazylegs, kSetPS09);
						Actor_Set_At_XYZ(kActorCrazylegs, -315.15f, 0.0f, 241.06f, 512);
						Actor_Set_Goal_Number(kActorCrazylegs, kGoalCrazyLegsIsArrested);
					}
				} else {
					if (Actor_Clue_Query(kActorMcCoy, kClueCrazysInvolvement)
					|| Actor_Clue_Query(kActorMcCoy, kClueCrazylegsInterview1)
					|| Actor_Clue_Query(kActorMcCoy, kClueCrazylegsInterview2)	
					|| Actor_Clue_Query(kActorMcCoy, kClueDektoraConfession)) {
						Actor_Clue_Acquire(kActorMcCoy, kClueVKCrazylegsReplicant, true, kActorSteele);
						Actor_Clue_Acquire(kActorMcCoy, kClueCrystalRetiredCrazylegs, true, kActorSteele);
						Actor_Set_Goal_Number(kActorCrazylegs, kGoalCrazyLegsLeavesShowroom);
						Game_Flag_Set(kFlagCrazylegsDead);
					}
				}
			}
			// Added in code so if Steele receives the Runciter is replicant Vk result and Runciter is a replicant and alive she retires him
			// and receives the Crystal retired Runciter clue. Also did the same for Bob.
			if (Actor_Clue_Query(kActorMcCoy, kClueVKRunciterReplicant)
			|| Actor_Clue_Query(kActorMcCoy, kClueLabCorpses)
			|| Actor_Clue_Query(kActorMcCoy, kClueLucyInterview)
			|| Actor_Clue_Query(kActorMcCoy, kClueZubensMotive)) {
				if (Actor_Clue_Query(kActorMcCoy, kClueRuncitersVideo)) {
					if (Actor_Query_Goal_Number(kActorRunciter) < kGoalRunciterDead) {
						if (Actor_Query_Intelligence(kActorSteele) == 90) {	
							if (Game_Flag_Query(kFlagRunciterIsReplicant)) {
								Actor_Clue_Acquire(kActorMcCoy, kClueCrystalRetiredRunciter1, true, kActorSteele);
								Actor_Clue_Acquire(kActorMcCoy, kClueCrystalRetiredRunciter2, true, kActorSteele);
								Actor_Clue_Acquire(kActorMcCoy, kClueVKRunciterReplicant, true, kActorSteele);
								Actor_Set_Goal_Number(kActorRunciter, kGoalRunciterDead);
							} else {
								Actor_Clue_Acquire(kActorMcCoy, kClueCrystalTestedRunciter, true, kActorSteele);
								Actor_Clue_Acquire(kActorMcCoy, kClueVKRunciterHuman, true, kActorSteele);
								if (Actor_Clue_Query(kActorMcCoy, kClueLabCorpses)
								|| Actor_Clue_Query(kActorMcCoy, kClueLucyInterview)
								|| Actor_Clue_Query(kActorMcCoy, kClueZubensMotive)) {	
									Game_Flag_Set(kFlagRunciterArrested);
									Actor_Put_In_Set(kActorRunciter, kSetPS09);
									Actor_Set_At_XYZ(kActorRunciter, -389.43f, 2.06f, -200.77f, 512);
								}
							}
						}
					}
				}
			}
			if (Actor_Clue_Query(kActorMcCoy, kClueVKBobGorskyReplicant)
			|| Actor_Clue_Query(kActorMcCoy, kClueHasanInterview)) {
				if (Actor_Query_Goal_Number(kActorBulletBob) < kGoalBulletBobGone) {
					if (Actor_Query_Intelligence(kActorSteele) == 90) {
						if (Game_Flag_Query(kFlagBulletBobIsReplicant)) {
							Actor_Clue_Acquire(kActorMcCoy, kClueCrystalRetiredBob, true, kActorSteele);
							Actor_Clue_Acquire(kActorMcCoy, kClueVKBobGorskyReplicant, true, kActorSteele);
							Actor_Set_Goal_Number(kActorBulletBob, kGoalBulletBobGone);
						} else {
							Actor_Clue_Acquire(kActorMcCoy, kClueCrystalTestedBulletBob, true, kActorSteele);
							Actor_Clue_Acquire(kActorMcCoy, kClueVKBobGorskyHuman, true, kActorSteele);
							if (Actor_Clue_Query(kActorMcCoy, kClueHasanInterview)) {
								Game_Flag_Set(kFlagBulletBobArrested);
								Actor_Put_In_Set(kActorBulletBob, kSetPS09);
								Actor_Set_At_XYZ(kActorBulletBob, -476.0f, 0.2f, -300.0f, 200);
							}
						}
					}
				}
			}	
			// Made it so if Zuben escapes Crystal will track him down and retire him if she has enough clues. This will give you the Crystal retired Zuben clue. If she doesn't have enough clues
			// she just finds Zuben by chance and doesn't have time to come up with a plan of attack so escapes into the sewers. This will give you the Zuben sighting clue.
			if (Game_Flag_Query(kFlagZubenIsReplicant) 
			&& !Game_Flag_Query(kFlagZubenRetired)) {
				Actor_Clue_Acquire(kActorMcCoy, kClueMcCoyLetZubenEscape, true, kActorGaff);
				if (Actor_Query_Intelligence(kActorSteele) == 70) {
					Actor_Clue_Acquire(kActorMcCoy, kClueSightingZuben, true, kActorSteele);
				} else if (Actor_Query_Intelligence(kActorSteele) == 90) {
					Actor_Set_Goal_Number(kActorZuben, kGoalZubenGone);
					Actor_Clue_Acquire(kActorMcCoy, kClueCrystalRetiredZuben, true, kActorSteele);
					Actor_Clue_Acquire(kActorMcCoy, kClueZubenSquadPhoto, true, kActorSteele);
				}
			}
			if (Game_Flag_Query(kFlagGordoIsReplicant)) { 
				if (Game_Flag_Query(kFlagGordoRanAway)
				|| Actor_Query_Goal_Number(kActorGordo) > kGoalGordoGone) {
					if (Actor_Query_Intelligence(kActorSteele) == 90) {
						Actor_Clue_Acquire(kActorMcCoy, kClueGordoIncept, true, kActorSteele);
						Actor_Clue_Acquire(kActorMcCoy, kClueWarRecordsGordoFrizz, true, kActorSteele);
					}	
					Actor_Clue_Acquire(kActorMcCoy, kClueSightingGordo, true, kActorSteele);
				}
			}
			if (!Game_Flag_Query(kFlagIzoIsReplicant) 
			&& Game_Flag_Query(kFlagIzoArrested)) {
				if (Actor_Query_Intelligence(kActorSteele) == 90) {
					Actor_Clue_Acquire(kActorMcCoy, kClueVKIzoHuman, true, kActorSteele);
				}
			}
			// Added in these clues in regards to replicant Early Q.
			if (Actor_Clue_Query(kActorMcCoy, kClueEarlyQInterview)
			|| Actor_Clue_Query(kActorMcCoy, kClueEarlyInterviewB2)
			|| Actor_Clue_Query(kActorMcCoy, kClueEarlyQAndLucy)
			|| Actor_Clue_Query(kActorMcCoy, kClueDektorasDressingRoom)) {
				if (!Game_Flag_Query(kFlagEarlyQDead)
				&& !Game_Flag_Query(kFlagNR04EarlyQStungByScorpions)) {
					if (Actor_Query_Intelligence(kActorSteele) == 90) {	
						if (Game_Flag_Query(kFlagEarlyQIsReplicant)) {
							Actor_Clue_Acquire(kActorMcCoy, kClueVKEarlyQReplicant, true, kActorSteele);
							Game_Flag_Set(kFlagEarlyQDead);					
						} else {
							if (Actor_Query_Intelligence(kActorSteele) == 90) {
								Actor_Clue_Acquire(kActorMcCoy, kClueVKEarlyQHuman, true, kActorSteele);
								Actor_Put_In_Set(kActorEarlyQ, kSetPS09);
								Actor_Set_At_XYZ(kActorEarlyQ, -425.88f, 0.15f, -220.74f, 512);
							}
						}
					}
				}
			}
			if (Actor_Clue_Query(kActorMcCoy, kClueVKGrigorianReplicant)) {
				if (Actor_Query_Intelligence(kActorSteele) == 90) {
					Game_Flag_Set(kFlagGrigorianDead);
					Actor_Set_At_XYZ(kActorGrigorian, -728.0f, -354.0f, 1090.0f, 150);
				}
			}
			if (Actor_Clue_Query(kActorMcCoy, kClueSpecialIngredient)) {
				if (Actor_Query_Intelligence(kActorSteele) == 90) {
					Game_Flag_Set(kFlagIsabellaArrested);
					Actor_Put_In_Set(kActorIsabella, kSetPS09);
					Actor_Set_At_XYZ(kActorIsabella, -450.0f, 0.2f, -200.0f, 518);
				}
			}
			if (Actor_Clue_Query(kActorMcCoy, kClueBobRobbed)) {
				if (Actor_Query_Intelligence(kActorSteele) == 90) {
					Game_Flag_Set(kFlagHasanArrested);
					Actor_Put_In_Set(kActorHasan, kSetPS09);
					Actor_Set_At_XYZ(kActorHasan, -300.0f, 0.33f, -330.0f, 512);
				}
			}
			if (Game_Flag_Query(kFlagCT01TalkToHowieAfterZubenMissing)
			&& Game_Flag_Query(kFlagZubenIsReplicant)) {
				if (Actor_Query_Intelligence(kActorSteele) == 90) {
					Game_Flag_Set(kFlagHowieLeeArrested); 
					AI_Movement_Track_Flush(kActorHowieLee);
					Actor_Put_In_Set(kActorHowieLee, kSetPS09);
					Actor_Set_At_XYZ(kActorHowieLee, -399.0f, 0.2f, -255.0f, 200);
				}
			}
			if (!Game_Flag_Query(kFlagZubenIsReplicant) 
			&& !Game_Flag_Query(kFlagZubenArrested)
			&& Game_Flag_Query(kFlagCT01TalkToHowieAfterZubenMissing)) {
				if (Actor_Query_Intelligence(kActorSteele) == 90) {
					Game_Flag_Set(kFlagZubenArrested);
					Actor_Put_In_Set(kActorZuben, kSetPS09);
					Actor_Set_At_XYZ(kActorZuben, -399.5f, 0.2f, -255.0f, 512);
				}
			}
			if (Global_Variable_Query(kVariableChapter) == 3
			&& Actor_Query_Intelligence(kActorSteele) == 90) {
				Actor_Clue_Acquire(kActorMcCoy, kClueStrangeScale1, true, kActorSteele);
				Actor_Clue_Acquire(kActorMcCoy, kClueInceptShotsLeon, true, kActorSteele);
			}
		}
		if (!Game_Flag_Query(kFlagDragonflyEarringTaken)) { 
			if (Actor_Query_Goal_Number(kActorIzo) > 500
			|| Game_Flag_Query(kFlagMcCoyShotIzo)) {
				if (Game_Flag_Query(kFlagIzoIsReplicant)
				&& Actor_Query_Intelligence(kActorIzo == 85)
				&& Actor_Query_Intelligence(kActorSteele) == 90) {
					Actor_Clue_Acquire(kActorIzo, kClueIzoIncept, true, kActorSteele);
					Actor_Clue_Acquire(kActorIzo, kClueRadiationGoggles, true, kActorSteele);
				}
				if (!Actor_Clue_Query(kActorMcCoy, kClueDragonflyEarring)) {
					Actor_Clue_Acquire(kActorMcCoy, kClueDragonflyEarring, true, kActorSteele);
				}
			}
			Game_Flag_Set(kFlagDragonflyEarringTaken);
		}
		if (Actor_Clue_Query(kActorMcCoy, kClueCar)
		 && !Actor_Clue_Query(kActorMcCoy, kClueCarRegistration1)
		 && !Actor_Clue_Query(kActorMcCoy, kClueCarRegistration2)
		 && !Actor_Clue_Query(kActorMcCoy, kClueCarRegistration3)
		 && !_vm->_cutContent
		) {
			Delay(2000);
			Actor_Voice_Over(3780, kActorVoiceOver);
			Actor_Voice_Over(3790, kActorVoiceOver); //99-3790.AUD	The car from Chinatown was the same vehicle that had smacked the hydrant at Runciter's.
			if (Game_Flag_Query(kFlagDektoraIsReplicant)) {
				Actor_Voice_Over(3800, kActorVoiceOver);
				Actor_Voice_Over(3810, kActorVoiceOver);
				Actor_Voice_Over(3820, kActorVoiceOver);
				Actor_Voice_Over(3830, kActorVoiceOver);
				Actor_Clue_Acquire(kActorMcCoy, kClueCarRegistration1, true, -1);
			} else if (Game_Flag_Query(kFlagGordoIsReplicant)) {
				Actor_Voice_Over(3840, kActorVoiceOver);
				Actor_Voice_Over(3850, kActorVoiceOver);
				Actor_Voice_Over(3860, kActorVoiceOver);
				Actor_Voice_Over(3870, kActorVoiceOver);
				Actor_Clue_Acquire(kActorMcCoy, kClueCarRegistration2, true, -1);
			} else {
				Actor_Voice_Over(3880, kActorVoiceOver);
				Actor_Voice_Over(3890, kActorVoiceOver);
				Actor_Voice_Over(3900, kActorVoiceOver);
				Actor_Voice_Over(3910, kActorVoiceOver);
				Actor_Clue_Acquire(kActorMcCoy, kClueCarRegistration3, true, -1);
			}
			Actor_Clues_Transfer_New_To_Mainframe(kActorMcCoy);
			Actor_Clues_Transfer_New_From_Mainframe(kActorMcCoy);
			Actor_Clues_Transfer_New_From_Mainframe(kActorKlein);
			// Made it so Crystal receives the clues that McCoy uploads to the mainframe. This is so the unused Crystal clues can now be received by McCoy.
			// Also did it for the other members of the police department because why would they not receive the clues from the mainframe.
			Actor_Clues_Transfer_New_From_Mainframe(kActorSteele);
			Actor_Clues_Transfer_New_From_Mainframe(kActorGuzza);
			Actor_Clues_Transfer_New_From_Mainframe(kActorSergeantWalls);
			Actor_Clues_Transfer_New_From_Mainframe(kActorGaff);
			Actor_Clues_Transfer_New_From_Mainframe(kActorOfficerLeary);
			Actor_Clues_Transfer_New_From_Mainframe(kActorOfficerGrayford);
			Actor_Clues_Transfer_New_From_Mainframe(kActorDispatcher);
			// also play "new clues added" cue, since McCoy gets the registrations clues
			Actor_Says(kActorAnsweringMachine, 360, kAnimationModeTalk);
			return true;
		} else if (Game_Flag_Query(kFlagKleinCarIdentityTalk)
		 && !Actor_Clue_Query(kActorMcCoy, kClueCarRegistration1)
		 && !Actor_Clue_Query(kActorMcCoy, kClueCarRegistration2)
		 && !Actor_Clue_Query(kActorMcCoy, kClueCarRegistration3)
		 && _vm->_cutContent
		 && (Actor_Clue_Query(kActorMcCoy, kClueLicensePlateMatch)
		 || Actor_Clue_Query(kActorMcCoy, kClueCar))) {
			Delay(2000);
			Actor_Voice_Over(3780, kActorVoiceOver);
			Delay(500);
			// Made it so McCoy only says this line if he found the black paint on the hydrant at Runciters.
			if (Actor_Clue_Query(kActorMcCoy, kCluePaintTransfer)) {
				Actor_Voice_Over(3790, kActorVoiceOver); //99-3790.AUD	The car from Chinatown was the same vehicle that had smacked the hydrant at Runciter's. 
			} else {
				Delay(500);
				Actor_Says(kActorMcCoy, 690, -1); //00-0690.AUD	Gotcha.
				Delay(500);
			}
			if (!Game_Flag_Query(kFlagZubenIsReplicant)) {
				Actor_Voice_Over(3840, kActorVoiceOver);
				Actor_Voice_Over(3850, kActorVoiceOver);
				Actor_Voice_Over(3860, kActorVoiceOver);
				Actor_Voice_Over(3870, kActorVoiceOver);
				Actor_Clue_Acquire(kActorMcCoy, kClueCarRegistration2, true, -1);
			} else if (Game_Flag_Query(kFlagDektoraIsReplicant)) {
				Actor_Voice_Over(3800, kActorVoiceOver);
				Actor_Voice_Over(3810, kActorVoiceOver);
				Actor_Voice_Over(3820, kActorVoiceOver);
				Actor_Voice_Over(3830, kActorVoiceOver);
				Actor_Clue_Acquire(kActorMcCoy, kClueCarRegistration1, true, -1);
			} else {
				Actor_Voice_Over(3880, kActorVoiceOver);
				Actor_Voice_Over(3890, kActorVoiceOver);
				Actor_Voice_Over(3900, kActorVoiceOver);
				Actor_Voice_Over(3910, kActorVoiceOver);
				Actor_Clue_Acquire(kActorMcCoy, kClueCarRegistration3, true, -1);
			}
			Actor_Clues_Transfer_New_To_Mainframe(kActorMcCoy);
			Actor_Clues_Transfer_New_From_Mainframe(kActorMcCoy);
			Actor_Clues_Transfer_New_From_Mainframe(kActorKlein);
			// Made it so Crystal receives the clues that McCoy uploads to the mainframe. This is so the unused Crystal clues can now be received by McCoy.
			// Also did it for the other members of the police department because why would they not receive the clues from the mainframe.
			Actor_Clues_Transfer_New_From_Mainframe(kActorSteele);
			Actor_Clues_Transfer_New_From_Mainframe(kActorGuzza);
			Actor_Clues_Transfer_New_From_Mainframe(kActorSergeantWalls);
			Actor_Clues_Transfer_New_From_Mainframe(kActorGaff);
			Actor_Clues_Transfer_New_From_Mainframe(kActorOfficerLeary);
			Actor_Clues_Transfer_New_From_Mainframe(kActorOfficerGrayford);
			Actor_Clues_Transfer_New_From_Mainframe(kActorDispatcher);
			// also play "new clues added" cue, since McCoy gets the registrations clues
			Actor_Says(kActorAnsweringMachine, 360, kAnimationModeTalk);
			return true;
		 } else {
			bool uploadedClues = Actor_Clues_Transfer_New_To_Mainframe(kActorMcCoy);
			if (uploadedClues) {
				if (_vm->_cutContent) {
					Actor_Clues_Transfer_New_From_Mainframe(kActorKlein);
					Actor_Clues_Transfer_New_From_Mainframe(kActorSteele);
					Actor_Clues_Transfer_New_From_Mainframe(kActorGuzza);
					Actor_Clues_Transfer_New_From_Mainframe(kActorSergeantWalls);
					Actor_Clues_Transfer_New_From_Mainframe(kActorGaff);
					Actor_Clues_Transfer_New_From_Mainframe(kActorOfficerLeary);
					Actor_Clues_Transfer_New_From_Mainframe(kActorOfficerGrayford);
					Actor_Clues_Transfer_New_From_Mainframe(kActorDispatcher);
				}
				Ambient_Sounds_Play_Sound(kSfxDATALOAD, 50, 0, 0, 99);
				if (_vm->_cutContent) {
					Delay(800); // shorten delay in Restored Content mode
				} else {
					Delay(2000);
				}
			}
			Actor_Says(kActorAnsweringMachine, 340,  kAnimationModeTalk);         // downloading clues
			bool downloadedClues = Actor_Clues_Transfer_New_From_Mainframe(kActorMcCoy);
			if (downloadedClues) {
				Ambient_Sounds_Play_Sound(kSfxDATALOAD, 50, 0, 0, 99);
				if (_vm->_cutContent) {
					Delay(800); // shorten delay in Restored Content mode
				} else {
					Delay(2000);
				}
			}
			Ambient_Sounds_Play_Sound(kSfxBEEPNEAT, 80, 0, 0, 99);
			Actor_Says(kActorAnsweringMachine, 350, kAnimationModeTalk);          // db transfer complete
			if (_vm->_cutContent) {
				if (downloadedClues) {
					Actor_Says(kActorAnsweringMachine, 360, kAnimationModeTalk);  // new clues added
				} else if (!uploadedClues && !downloadedClues) {
					// Play the "No clues transfered" if overall no clues were exchanged
					Actor_Says(kActorAnsweringMachine, 370,  kAnimationModeTalk); // no clues transfered
				}
			}
			return true;
		}
	}
	return false;
}

bool SceneScriptPS06::ClickedOnActor(int actorId) {
	return false;
}

bool SceneScriptPS06::ClickedOnItem(int itemId, bool a2) {
	return false;
}

bool SceneScriptPS06::ClickedOnExit(int exitId) {
	if (exitId == 0) {
		Game_Flag_Set(kFlagPS06toPS05);
		Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
		Ambient_Sounds_Remove_All_Looping_Sounds(1u);
		Set_Enter(kSetPS05, kScenePS05);
		return true;
	}
	return false;
}

bool SceneScriptPS06::ClickedOn2DRegion(int region) {
	return false;
}

void SceneScriptPS06::SceneFrameAdvanced(int frame) {
}

void SceneScriptPS06::ActorChangedGoal(int actorId, int newGoal, int oldGoal, bool currentSet) {
}

void SceneScriptPS06::PlayerWalkedIn() {
	if (Game_Flag_Query(kFlagPS05toPS06)) {
		Game_Flag_Reset(kFlagPS05toPS06);
	}
}

void SceneScriptPS06::PlayerWalkedOut() {
}

void SceneScriptPS06::DialogueQueueFlushed(int a1) {
}

} // End of namespace BladeRunner
