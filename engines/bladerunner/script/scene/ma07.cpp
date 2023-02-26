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

void SceneScriptMA07::InitializeScene() {
	if (Game_Flag_Query(kFlagUG19toMA07)) {
		Setup_Scene_Information(  6.75f, -172.43f, 356.0f, 997);
		Game_Flag_Reset(kFlagUG19toMA07);
		Game_Flag_Set(kFlagUG19Available);
	} else if (Game_Flag_Query(kFlagPS14toMA07)) {
		Setup_Scene_Information(-312.0f,  -162.8f, 180.0f,   0);
	} else {
		Setup_Scene_Information( 104.0f, -162.16f,  56.0f, 519);
	}

	Ambient_Sounds_Add_Looping_Sound(kSfxRAIN10, 100, 1, 1);
	Ambient_Sounds_Add_Sound(kSfxCOLONY,  100, 300, 16,  25, 0, 0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSPIN2B,   60, 180, 16,  25, 0, 0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSPIN3A,   60, 180, 16,  25, 0, 0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxTHNDER2,  60, 180, 50, 100, 0, 0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxTHNDER3,  50, 180, 50, 100, 0, 0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxTHNDER4,  50, 180, 50, 100, 0, 0, -101, -101, 0, 0);

	if (Global_Variable_Query(kVariableChapter) > 1) {
		Scene_Exit_Add_2D_Exit(1, 0, 200, 50, 479, 3);
	}
	if (Game_Flag_Query(kFlagUG19Available)) {
		Scene_Exit_Add_2D_Exit(2, 176, 386, 230, 426, 2);
	}
	Scene_Exit_Add_2D_Exit(0, 270, 216, 382, 306, 0);
}

void SceneScriptMA07::SceneLoaded() {
	Obstacle_Object("BARRICADE", true);
	if (_vm->_cutContent) {
		if (Actor_Query_Goal_Number(kActorRachael) == kGoalRachaelShouldBeOutsideMcCoysAct3) {
			Actor_Set_Goal_Number(kActorRachael, kGoalRachaelIsOutsideMcCoysBuildingAct3);
		}
	}
}

bool SceneScriptMA07::MouseClick(int x, int y) {
	return false;
}

bool SceneScriptMA07::ClickedOn3DObject(const char *objectName, bool a2) {
	return false;
}

bool SceneScriptMA07::ClickedOnActor(int actorId) {
	return false;
}

bool SceneScriptMA07::ClickedOnItem(int itemId, bool a2) {
	return false;
}

bool SceneScriptMA07::ClickedOnExit(int exitId) {
	if (exitId == 0) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, 104.0f, -162.0f, 56.0f, 12, true, false, false)) {
			if (Global_Variable_Query(kVariableChapter) == 4
			 && Game_Flag_Query(kFlagUG18GuzzaScene)
			) {
				Actor_Set_Goal_Number(kActorMcCoy, kGoalMcCoyStartChapter5);
			} else {
				Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
				Ambient_Sounds_Remove_All_Looping_Sounds(1u);
				Game_Flag_Set(kFlagMA07toMA06);
				Set_Enter(kSetMA06, kSceneMA06);
			}
		}
		return true;
	}

	if (exitId == 1) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -400.0f, -162.8f, 185.08f, 0, true, false, false)) {
			Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
			Ambient_Sounds_Remove_All_Looping_Sounds(1u);
			Game_Flag_Set(kFlagMA07toPS14);
			Game_Flag_Reset(kFlagMcCoyInMcCoyApartment);
			Game_Flag_Set(kFlagMcCoyInPoliceStation);
			Set_Enter(kSetPS14, kScenePS14);
		}
		return true;
	}

	if (exitId == 2) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, 8.0f, -172.43f, 356.0f, 0, true, false, false)) {
			Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
			Ambient_Sounds_Remove_All_Looping_Sounds(1u);
			Game_Flag_Set(kFlagMA07toUG19);
			Set_Enter(kSetUG19, kSceneUG19);
			if (_vm->_cutContent) {
				Sound_Play(kSfxMANHOLE1,  40, 0, 0, 50);
			}
		}
		return true;
	}
	return false;
}

bool SceneScriptMA07::ClickedOn2DRegion(int region) {
	return false;
}

void SceneScriptMA07::SceneFrameAdvanced(int frame) {
}

void SceneScriptMA07::ActorChangedGoal(int actorId, int newGoal, int oldGoal, bool currentSet) {
	if (actorId == kActorGaff
	 && newGoal == kGoalGaffMA07Left
	) {
		Scene_Exits_Enable();
	}
}

void SceneScriptMA07::PlayerWalkedIn() {
	if (Game_Flag_Query(kFlagPS14toMA07)) {
		Loop_Actor_Walk_To_XYZ(kActorMcCoy, -268.0f, -162.8f, 188.0f, 0, false, false, false);
		Game_Flag_Reset(kFlagPS14toMA07);
	}

	if (Actor_Query_Goal_Number(kActorRachael) == kGoalRachaelIsOutsideMcCoysBuildingAct3) {
		Actor_Set_Goal_Number(kActorRachael, kGoalRachaelIsOutWalksToPoliceHQAct3);
	} else if (_vm->_cutContent && Actor_Query_Goal_Number(kActorRachael) == kGoalRachaelIsOutsideMcCoysBuildingAct4) {
		Actor_Set_Goal_Number(kActorRachael, kGoalRachaelIsOutWalksToPoliceHQAct4);
	}

	if (_vm->_cutContent) {
		if (Game_Flag_Query(kFlagRachaelWalks)) {
			Actor_Put_In_Set(kActorRachael, kSetMA07);
			Actor_Set_At_XYZ(kActorRachael, -8.09f, -162.8f, 135.33f, 544);
			AI_Movement_Track_Flush(kActorRachael);
			AI_Movement_Track_Append(kActorRachael, 468, 0); // kSetMA07
			AI_Movement_Track_Append(kActorRachael, 39, 0);  // kSetFreeSlotG
			AI_Movement_Track_Repeat(kActorRachael);
			if (Global_Variable_Query(kVariableChapter) == 3) {
				if (!Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
					Player_Set_Combat_Mode(true);
					Actor_Set_Targetable(kActorRachael, true);
				} else if (Player_Query_Agenda() == kPlayerAgendaSurly 
				|| Player_Query_Agenda() == kPlayerAgendaErratic) {	
					Player_Set_Combat_Mode(true);
					Actor_Set_Targetable(kActorRachael, true);
				} else {
					Actor_Set_Targetable(kActorRachael, false);
				}
			} else {
				Actor_Set_Targetable(kActorRachael, false);
			}
		}
	}

	if (Game_Flag_Query(kFlagMA06toMA07)) {
		Game_Flag_Reset(kFlagMA06toMA07);
	}

	if (!Game_Flag_Query(kFlagMA07GaffTalk)
	 &&  Game_Flag_Query(kFlagUG18GuzzaScene)
	 &&  Global_Variable_Query(kVariableChapter) == 4
	) {
		Scene_Exits_Disable();
#if BLADERUNNER_ORIGINAL_BUGS
#else
		// don't have McCoy with his gun drawn out when talking to Gaff here
		Player_Set_Combat_Mode(false);
#endif // BLADERUNNER_ORIGINAL_BUGS
		Actor_Set_Goal_Number(kActorGaff, kGoalGaffMA07Wait);
	}

	if (Game_Flag_Query(kFlagMcCoyFreedOfAccusations)) {
		// Made it so McCoy receives 400 chinyen if he retired replicant Luther and Lance and he is found to be innocent.
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagLutherLanceIsReplicant)
			&& Actor_Query_Goal_Number(kActorLuther) > kGoalLutherGone) {
				if (Query_Difficulty_Level() != kGameDifficultyEasy) {
					Global_Variable_Increment (kVariableChinyen, 400);			
				}
			}
			if (Game_Flag_Query(kFlagMcCoyShotRunciter)) {
				if (Query_Difficulty_Level() != kGameDifficultyEasy) {
					Global_Variable_Increment (kVariableChinyen, 200);			
				}
			}
		}
		Actor_Voice_Over(1360, kActorVoiceOver); //99-1360.AUD	They didn’t even put me on the Machine.
		Actor_Voice_Over(1370, kActorVoiceOver); //99-1370.AUD	The evidence Guzza coughed up was all I’d needed to convince them I wasn’t a Rep.
		if (_vm->_cutContent) {
			Game_Flag_Set(kFlagMcCoyIsInnocent);
			if (Actor_Clue_Query(kActorMcCoy, kClueBriefcase)) {
				Actor_Clue_Lose(kActorMcCoy, kClueBriefcase);
			}
		}
		// Made it so McCoys comments are different here depending on whether or not he saved Guzza.
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagGuzzaSaved)) {
				if (!Game_Flag_Query(kFlagGuzzaArrested)) {
					Actor_Voice_Over(4410, kActorVoiceOver); //99-4410.AUD	Guzza must have a little something going on the side.
				}
				Delay(1000);
				Player_Gains_Control();
				Game_Flag_Reset(kFlagMcCoyFreedOfAccusations);
				Game_Flag_Set(kFlagMA06ToMA02);
				Set_Enter(kSetMA02_MA04, kSceneMA02);
			} else {		
				Actor_Voice_Over(1380, kActorVoiceOver); //99-1380.AUD	Bryant chewed me out for letting the Reps kill him…
				if (Player_Query_Agenda() == kPlayerAgendaSurly 
				|| Player_Query_Agenda() == kPlayerAgendaErratic) {
					Actor_Voice_Over(1390, kActorVoiceOver);
					Actor_Voice_Over(1400, kActorVoiceOver);
				} else {
					Actor_Voice_Over(3470, kActorVoiceOver); //99-3470.AUD	But I wasn’t gonna eat crow that easily.
				}
				Delay(1000);
				Player_Gains_Control();
				Actor_Clue_Lose(kActorMcCoy, kClueFolder);
				Game_Flag_Reset(kFlagMcCoyFreedOfAccusations);
				Game_Flag_Set(kFlagMA06ToMA02);
				Set_Enter(kSetMA02_MA04, kSceneMA02);
			}
		} else {
			Actor_Voice_Over(1380, kActorVoiceOver); //99-1380.AUD	Bryant chewed me out for letting the Reps kill him…
			Actor_Voice_Over(1390, kActorVoiceOver);
			Actor_Voice_Over(1400, kActorVoiceOver);
			Delay(1000);
			Game_Flag_Reset(kFlagMcCoyFreedOfAccusations);
			Game_Flag_Set(kFlagMA06ToMA02);
			Set_Enter(kSetMA02_MA04, kSceneMA02);
		}
	}
	if (_vm->_cutContent) {
		if (!Game_Flag_Query(kFlagCrystalTalkAct4)
		&& !Game_Flag_Query(kFlagMcCoyRetiredHuman)
		&& !Game_Flag_Query(kFlagUG18GuzzaScene)
		// Made it so whether of not you have affection towards Dektora or Lucy this will determine whether or not you will meet Crystal here.
		&& Global_Variable_Query(kVariableAffectionTowards) != kAffectionTowardsDektora
		&& Global_Variable_Query(kVariableAffectionTowards) != kAffectionTowardsLucy
		&&	Global_Variable_Query(kVariableChapter) == 4) {
			Actor_Put_In_Set(kActorSteele, kSetMA07);
			Actor_Set_At_XYZ(kActorSteele, 27.19, -162.21, 184.93, 0);
			Actor_Face_Actor(kActorSteele, kActorMcCoy, true);
			Actor_Face_Actor(kActorMcCoy, kActorSteele, true);
			Music_Play(kMusicBRBlues, 52, 0, 2, -1, kMusicLoopPlayOnce, 1);
			if (Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) < 60) {
				Actor_Says(kActorSteele, 2710, 12); //01-2710.AUD	You must be in better shape that I thought.
				Actor_Says(kActorSteele, 2720, 13); //01-2720.AUD	You’re still alive.	
				Actor_Says(kActorMcCoy, 5705, 13); //00-5705.AUD	Uh-huh.
			} else {
				Actor_Says(kActorSteele, 2360, 13); //01-2360.AUD	Slumming tonight, Slim?
				Actor_Says(kActorMcCoy, 2945, 14); //00-2945.AUD	You could say that.
			}
			if (Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) > 59) {
				Actor_Says(kActorSteele, 2690, 14); //01-2690.AUD	Hey, Slim. I dug up some new dirt. What do you say we have a pow-wow.
				if (Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
					Actor_Says(kActorMcCoy, 6305, 16); //00-6305.AUD	I don’t got the time or the inclination, Steele. 
					Actor_Says(kActorSteele, 3300, 13); //01-3300.AUD	One day you’ll be begging me for time, I guarantee.
					Player_Loses_Control();
					Loop_Actor_Walk_To_Actor(kActorMcCoy, kActorSteele, 24, true, false);
					Player_Gains_Control();
					Actor_Says(kActorMcCoy, 7835, 14); //00-7835.AUD	Is that so?
					Actor_Says(kActorSteele, 3280, 13); //01-3280.AUD	You better remember all the favors I’ve done for you.
					Actor_Modify_Friendliness_To_Other(kActorSteele, kActorMcCoy, -5);
					Delay(1000);
				} else {
					Actor_Says(kActorMcCoy, 6300, 15); //00-6300.AUD	You show me yours, I’ll show you mine.
					Actor_Says(kActorSteele, 3290, 12); //01-3290.AUD	Let’s hook ‘em up.
					Player_Loses_Control();
					Loop_Actor_Walk_To_Actor(kActorMcCoy, kActorSteele, 24, true, false);
					Player_Gains_Control();
					Actor_Face_Actor(kActorMcCoy, kActorSteele, true);
					Actor_Face_Actor(kActorSteele, kActorMcCoy, true);
					Actor_Change_Animation_Mode(kActorMcCoy, 23);
					Actor_Change_Animation_Mode(kActorSteele, 23);
					Delay(800);
					Ambient_Sounds_Play_Sound(kSfxDATALOAD, 50, 0, 0, 99);
					Delay(2000);
					Ambient_Sounds_Play_Sound(kSfxBEEPNEAT, 80, 0, 0, 99);
					Delay(1000);
					Actor_Says(kActorMcCoy, 8170, 13); //00-8170.AUD	There you go.
					Delay(1000);
					Actor_Clue_Acquire(kActorMcCoy, kClueBakersBadge, true, kActorSteele);
					if (Game_Flag_Query(kFlagDektoraIsReplicant))  {
						Actor_Clue_Acquire(kActorMcCoy, kClueSightingDektora, true, kActorSteele);
					}
					if (Game_Flag_Query(kFlagGordoIsReplicant))  {
						Actor_Clue_Acquire(kActorMcCoy, kClueWarRecordsGordoFrizz, true, kActorSteele); 
						Actor_Clue_Acquire(kActorMcCoy, kClueSightingGordo, true, kActorSteele);
					}
					if (!Game_Flag_Query(kFlagCrazylegsIsReplicant)) {
						if (Random_Query(1, 3) == 1) {
							if (!Game_Flag_Query(kFlagCrazylegsDead)) {
								if (Actor_Clue_Query(kActorMcCoy, kClueCrazylegsInterview1)
								|| Actor_Clue_Query(kActorMcCoy, kClueCrazylegsInterview2)) {
									Actor_Clue_Acquire(kActorMcCoy, kClueVKCrazylegsHuman,  true, kActorSteele);
									Actor_Clue_Acquire(kActorMcCoy, kClueCrystalTestedCrazylegs, true, kActorSteele);
								} else if (Actor_Clue_Query(kActorMcCoy, kClueCrazysInvolvement)) {
									Actor_Clue_Acquire(kActorMcCoy, kClueVKCrazylegsHuman,  true, kActorSteele);
									Actor_Clue_Acquire(kActorMcCoy, kClueCrystalTestedCrazylegs, true, kActorSteele);	
									Actor_Clue_Acquire(kActorMcCoy, kClueCrystalArrestedCrazylegs,  true, kActorSteele);
									Game_Flag_Set(kFlagCrazylegsArrested);
									Actor_Put_In_Set(kActorCrazylegs, kSetPS09);
									Actor_Set_At_XYZ(kActorCrazylegs, -315.15f, 0.0f, 241.06f, 512);
									Actor_Set_Goal_Number(kActorCrazylegs, kGoalCrazyLegsIsArrested);
								}
							}
						}
					} else {
						if (Random_Query(1, 3) == 1) {
							if (Actor_Clue_Query(kActorMcCoy, kClueCrazysInvolvement) 
							|| Actor_Clue_Query(kActorMcCoy, kClueCrazylegsInterview1)
							|| Actor_Clue_Query(kActorMcCoy, kClueCrazylegsInterview2)) {
								if (!Game_Flag_Query(kFlagCrazylegsDead)) {
									Actor_Clue_Acquire(kActorMcCoy, kClueVKCrazylegsReplicant, true, kActorSteele);
									Actor_Clue_Acquire(kActorMcCoy, kClueCrystalRetiredCrazylegs, true, kActorSteele);
									Actor_Set_Goal_Number(kActorCrazylegs, kGoalCrazyLegsLeavesShowroom);
									Game_Flag_Set(kFlagCrazylegsDead);
								}
							}
						}
					}
					// Added in code so if Steele receives the Runciter is replicant Vk result and Runciter is a replicant and alive she retires him
					// and receives the Crystal retired Runciter clue. Also did the same for Bob.
					if (Actor_Clue_Query(kActorMcCoy, kClueVKRunciterReplicant)
					|| Actor_Clue_Query(kActorMcCoy, kClueLabCorpses)
					|| Actor_Clue_Query(kActorMcCoy, kClueLucyInterview)
					|| Actor_Clue_Query(kActorMcCoy, kClueZubensMotive)) {
						if (Random_Query(1, 3) == 1) {
							if (Actor_Query_Goal_Number(kActorRunciter) < kGoalRunciterDead) {
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
					if (Actor_Clue_Query(kActorMcCoy, kClueVKBobGorskyReplicant)
					|| Actor_Clue_Query(kActorMcCoy, kClueHasanInterview)) {
						if (Random_Query(1, 3) == 1) {
							if (Actor_Query_Goal_Number(kActorBulletBob) < kGoalBulletBobGone) {
								if (Game_Flag_Query(kFlagBulletBobIsReplicant)) {
									Actor_Clue_Acquire(kActorMcCoy, kClueCrystalRetiredBob, true, kActorSteele);
									Actor_Clue_Acquire(kActorMcCoy, kClueVKBobGorskyReplicant, true, kActorSteele);
									Actor_Set_Goal_Number(kActorBulletBob, kGoalBulletBobGone);
								}
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
					// Made it so if Zuben escapes Crystal will track him down and retire him if she has enough clues. This will give you the Crystal retired Zuben clue. If she doesn't have enough clues
					// she just finds Zuben by chance and doesn't have time to come up with a plan of attack so escapes into the sewers. This will give you the Zuben sighting clue.
					if (Game_Flag_Query(kFlagZubenIsReplicant) 
					&& !Game_Flag_Query(kFlagZubenRetired)) {
						Actor_Clue_Acquire(kActorMcCoy, kClueMcCoyLetZubenEscape, true, kActorGaff);
						Actor_Clue_Acquire(kActorMcCoy, kClueSightingZuben, true, kActorSteele);
						if (Random_Query(1, 3) == 1) {
							Actor_Set_Goal_Number(kActorZuben, kGoalZubenGone);
							Actor_Clue_Acquire(kActorMcCoy, kClueCrystalRetiredZuben, true, kActorSteele);
						}
					}
					if (!Game_Flag_Query(kFlagIzoIsReplicant) 
					&& Game_Flag_Query(kFlagIzoArrested)) {
						Actor_Clue_Acquire(kActorMcCoy, kClueVKIzoHuman, true, kActorSteele);
					}
					// Added in these clues in regards to replicant Early Q.
					if (Actor_Clue_Query(kActorMcCoy, kClueEarlyQAndLucy)
					|| Actor_Clue_Query(kActorMcCoy, kClueEarlyInterviewB1)
					|| Actor_Clue_Query(kActorMcCoy, kClueEarlyInterviewB2)
					|| Actor_Clue_Query(kActorMcCoy, kClueDektorasDressingRoom)) {
						if (Random_Query(1, 3) == 1) {
							if (Game_Flag_Query(kFlagEarlyQIsReplicant)) {
								if (!Game_Flag_Query(kFlagEarlyQDead)
								&& !Game_Flag_Query(kFlagNR04EarlyQStungByScorpions)) {							
									Actor_Clue_Acquire(kActorMcCoy, kClueVKEarlyQReplicant, true, kActorSteele);
									Game_Flag_Set(kFlagEarlyQDead);
								}
							} else {
								Actor_Clue_Acquire(kActorMcCoy, kClueVKEarlyQHuman, true, kActorSteele);
								Game_Flag_Set(kFlagEarlyQArrested);
								Actor_Put_In_Set(kActorEarlyQ, kSetPS09);
								Actor_Set_At_XYZ(kActorEarlyQ, -425.88f, 0.15f, -220.74f, 512);
							}
						}
					}
					if (Actor_Clue_Query(kActorMcCoy, kClueVKGrigorianReplicant)) {
						if (Random_Query(1, 3) == 1) {
							Game_Flag_Set(kFlagGrigorianDead);
							Actor_Set_At_XYZ(kActorGrigorian, -728.0f, -354.0f, 1090.0f, 150);
						}
					}
					if (Actor_Clue_Query(kActorMcCoy, kClueSpecialIngredient)) {
						if (Random_Query(1, 3) == 1) {
							Game_Flag_Set(kFlagIsabellaArrested);
							Actor_Put_In_Set(kActorIsabella, kSetPS09);
							Actor_Set_At_XYZ(kActorIsabella, -450.0f, 0.2f, -200.0f, 518);
						}
					}
					if (Actor_Clue_Query(kActorMcCoy, kClueBobRobbed)) {
						if (Random_Query(1, 3) == 1) {
							Game_Flag_Set(kFlagHasanArrested);
							Actor_Put_In_Set(kActorHasan, kSetPS09);
							Actor_Set_At_XYZ(kActorHasan, -300.0f, 0.33f, -330.0f, 512);
						}
					}
					if (Actor_Clue_Query(kActorMcCoy, kClueMcCoyLetZubenEscape)
					|| Actor_Clue_Query(kActorMcCoy, kClueMcCoyRetiredZuben)) {
						if (Random_Query(1, 3) == 1) {
							Game_Flag_Set(kFlagHowieLeeArrested); 
							AI_Movement_Track_Flush(kActorHowieLee);
							Actor_Put_In_Set(kActorHowieLee, kSetPS09);
							Actor_Set_At_XYZ(kActorHowieLee, -399.0f, 0.2f, -255.0f, 200);
						}
					}
					if (!Game_Flag_Query(kFlagZubenIsReplicant) 
					&& !Game_Flag_Query(kFlagZubenArrested)) {
						if (Random_Query(1, 3) == 1) {
							Game_Flag_Set(kFlagZubenArrested);
							Actor_Put_In_Set(kActorZuben, kSetPS09);
							Actor_Set_At_XYZ(kActorZuben, -399.5f, 0.2f, -255.0f, 512);
						}
					}
				}
			}
			Actor_Says(kActorSteele, 2760, 13); //01-2760.AUD	What’s the latest?
			Actor_Says(kActorMcCoy, 6345, 15); //00-6345.AUD	I think you already know the answer to that question
			if (Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) > 59) {
				Actor_Says(kActorSteele, 2770, 14); //01-2770.AUD	I want to hear it from you.
				Actor_Says(kActorMcCoy, 6350, 16); //00-6350.AUD	What’s the point? You are not gonna believe a word I say.
			}
			Actor_Says(kActorSteele, 2780, 13); //01-2780.AUD	Do yourself a favor, Slim. Turn yourself in. Guzza will give you a fair shake.
			if (Actor_Clue_Query(kActorMcCoy, kClueGuzzaFramedMcCoy)) {
				if (Player_Query_Agenda() == kPlayerAgendaSurly 
				|| Player_Query_Agenda() == kPlayerAgendaErratic) {
					Actor_Says(kActorMcCoy, 6355, 14); //00-6355.AUD	Like hell!
				} else {
					Actor_Says(kActorMcCoy, 2485, 19); //00-2485.AUD	I’ve a hard time believing that.
				}
			} else {
				Actor_Says(kActorMcCoy, 5065, 18); //00-5065.AUD	Is that right?
			}
			// Made it so if McCoy has retired 4 replicants Steele is nicer to him.
			if (Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) > 59) {
				Actor_Says(kActorSteele, 2790, 12); //01-2790.AUD	I guarantee it. I’ll put you on the Machine myself.
				Actor_Says(kActorMcCoy, 6360, 13); //00-6360.AUD	Hey, you’re always crowing about the “magic”. What does it tell you now
				Actor_Says(kActorSteele, 1390, 13); //01-1390.AUD	I ain’t sure yet. I like to be sure.
			}
			Actor_Says(kActorMcCoy, 6330, 15); //00-6330.AUD	You find out anything about our friend Guzza?
			Actor_Says(kActorSteele, 2730, 15); //01-2730.AUD	Zilcho for now. Looks like the fat man took a jump off the face of the earth. 
			if (Actor_Clue_Query(kActorMcCoy, kClueGuzzaFramedMcCoy)) {
				Actor_Says(kActorMcCoy, 6335, 13); //00-6335.AUD	Maybe he just doesn’t want to be found.
				Actor_Says(kActorSteele, 2740, 14); //01-2740.AUD	That’s a big maybe.
				Actor_Says(kActorMcCoy, 6340, 15); //00-6340.AUD	A likely maybe, don’t you think?
				if (Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) < 60) {
					Actor_Says(kActorSteele, 2800, 15); //01-2800.AUD	You don’t want to know what I think.
					Delay(2000);
					Actor_Says(kActorSteele, 2810, 15); //01-2810.AUD	Beat it, Slim. Take it on the heel. Before I regret this.
				} else {
					Actor_Says(kActorSteele, 2750, 13); //01-2750.AUD	I think maybe you’re a lot smarter than you look, Slim.
					if (Player_Query_Agenda() != kPlayerAgendaSurly 
					&& Player_Query_Agenda() != kPlayerAgendaErratic) {
						Actor_Says(kActorMcCoy, 1345, 13); //00-1345.AUD	Thanks.
					}
					Delay(1000);
				}
			} else {
				Actor_Says(kActorMcCoy, 6325, 16); //00-6325.AUD	How’s that?
				Actor_Says(kActorSteele, 2250, 16); //01-2250.AUD	I'm still fitting the pieces together.
				Delay(1000);
			}
			Actor_Says(kActorMcCoy, 3255, 18); //00-3255.AUD	Maybe I’ll see you again.
			Actor_Says(kActorSteele, 970, 13); //01-0970.AUD	We’ll be meeting again, Slim. You can bank on it.
			if (Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) > 59) {
				Actor_Says(kActorMcCoy, 5260, 15); //00-5260.AUD	Happy trails, Steele.
				Actor_Says(kActorSteele, 2350, 14); //01-2350.AUD	Ditto.
			}
			Loop_Actor_Walk_To_XYZ(kActorSteele, -270.65, -162.25, 276.32, 0, true, false, false);
			Player_Gains_Control();
			Game_Flag_Set(kFlagCrystalTalkAct4);
		}
	}
	// Made it so if you saved Guzza you will meet him here instead of Gaff and the conversation will play out differently depending on whether McCoy retired a human
	// and has the briefcase of evidence.
	if (_vm->_cutContent) {
		if (Global_Variable_Query(kVariableChapter) == 4) {
			if (Game_Flag_Query(kFlagGuzzaSaved)) {
				Actor_Put_In_Set(kActorGuzza, kSetMA07);
				Actor_Set_At_XYZ(kActorGuzza, 184.49, -162.24, 215.34, 0);
				Actor_Face_Actor(kActorGuzza, kActorMcCoy, true);
				Actor_Face_Actor(kActorMcCoy, kActorGuzza, true);
				Actor_Says(kActorGuzza, 9005, 14); //04-9005.AUD	Hey.
				Actor_Says(kActorGuzza, 420, 13); //04-0420.AUD	Keeping out of trouble, kid?
				Actor_Face_Actor(kActorMcCoy, kActorGuzza, true);
				Actor_Says(kActorMcCoy, 9045, 15); //00-9045.AUD	Not these days.
				Music_Play(kMusicBRBlues, 52, 0, 2, -1, kMusicLoopPlayOnce, 1);
				Player_Loses_Control();
				Loop_Actor_Walk_To_Actor(kActorMcCoy, kActorGuzza, 24, true, false);
				Actor_Face_Actor(kActorMcCoy, kActorGuzza, true);
				Actor_Face_Actor(kActorGuzza, kActorMcCoy, true);
				Actor_Says(kActorMcCoy, 6610, 14); //00-6610.AUD	Been messing with peoples’ lives lately?
				Delay(2000);
				Actor_Says(kActorMcCoy, 8395, 18); //00-8395.AUD	You don't have anything to say?
				Delay(1000);
				Actor_Says(kActorGuzza, 1530, 15); //04-1530.AUD	I must have made a mistake or something. Truly, an honest mistake.
				if (Player_Query_Agenda() == kPlayerAgendaSurly 
				|| Player_Query_Agenda() == kPlayerAgendaErratic) {
					Actor_Says(kActorMcCoy, 2140, 14); //00-2140.AUD	Bullshit.
				} else {
					Actor_Says(kActorMcCoy, 3910, 15); //00-3910.AUD	You’re lying.
				}
				Delay(1000);
				Actor_Says(kActorMcCoy, 2130, 15); //00-2130.AUD	You’re the coldest person I’ve ever seen when it comes to killing.
				Delay(1000);
				Actor_Says(kActorMcCoy, 6645, 18); //00-6645.AUD	You were raking in the chinyen selling LPD wares to scumbags and Reps.
				Actor_Says(kActorGuzza, 540, 14); //04-0540.AUD	Trust me. Ain't nobody getting rich unless they're sneaking some on the side.
				Actor_Says(kActorMcCoy, 8345, 18); //00-8345.AUD	I wouldn't know.
				Delay(1000);
				Actor_Says(kActorGuzza, 260, 16);//04-0260.AUD	Once you start carving up that juicy bacon kid, the taste never goes away.
				Actor_Says(kActorGuzza, 270, 15);//04-0270.AUD	The great things in life...? Believe me you'll just be wanting more and more.
				if (!Game_Flag_Query(kFlagMcCoyRetiredHuman)
				&& Actor_Clue_Query(kActorMcCoy, kClueBriefcase)) {
					Actor_Says(kActorMcCoy, 6630, 15); //00-6630.AUD	I’m through listening, Guzza. Now it’s your turn.
					Player_Set_Combat_Mode(true);
					Actor_Change_Animation_Mode(kActorMcCoy, 5);
					Delay(1000);
					Actor_Says(kActorGuzza, 410, 15); //04-0410.AUD	Jesus.
					Actor_Says(kActorMcCoy, 3095, -1); //00-3095.AUD	Now we’re gonna take a little ride downtown.	
					Actor_Says(kActorGuzza, 600, 16);	// 04-0600.AUD	You what? Damn it, wha-- what are you telling me? I don't need this. Not today.
					Actor_Says(kActorMcCoy, 4205, -1); //00-4205.AUD	I'll bet. But this is only the beginning.
					Delay(1000);
					if (Player_Query_Agenda() == kPlayerAgendaSurly 
					|| Player_Query_Agenda() == kPlayerAgendaErratic) {
						Actor_Says(kActorMcCoy, 5150, -1); //00-5150.AUD	One more thing.
						Delay(500);
						Actor_Says(kActorMcCoy, 6180, -1); //00-6180.AUD	Your breath smells like you wiped your ass with your teeth..
						Delay(1000);
					}
					Actor_Says(kActorGuzza, 120, 17); // 04-0120.AUD	I don't want to ever see your sorry ass again.
					Actor_Says(kActorMcCoy, 4070, -1); //00-4070.AUD	You got it.
					Loop_Actor_Walk_To_XYZ(kActorGuzza, 127.63, -162.26, 252.58, 0, true, false, false);
					Async_Actor_Walk_To_Waypoint(kActorMcCoy, 100, 0, false);
					Async_Actor_Walk_To_Waypoint(kActorGuzza, 101, 0, false);
					Delay(4000);
					Music_Stop(1u);
					Actor_Force_Stop_Walking(kActorMcCoy);
					Actor_Put_In_Set(kActorGuzza, kSetPS09);
					Player_Gains_Control();
					Player_Set_Combat_Mode(false);
					Game_Flag_Set(kFlagMcCoyFreedOfAccusations);
					Game_Flag_Set(kFlagMcCoyIsInnocent);
					Game_Flag_Set(kFlagGuzzaArrested);
					Actor_Clue_Lose(kActorMcCoy, kClueFolder);
					Actor_Modify_Friendliness_To_Other(kActorSteele, kActorMcCoy, 2);
					Actor_Set_Goal_Number(kActorMcCoy, kGoalMcCoyStartChapter5);
				} else {
					Actor_Says(kActorMcCoy, 8519, 14); // 00-8519.AUD	What do you say we dish each other the straight goods.
					Delay(500);
					Actor_Says(kActorMcCoy, 6675, 18); //00-6675.AUD	I want my life back.
					Delay(1000);
					Actor_Says(kActorGuzza, 620, 17); //04-0620.AUD	I'm gonna have to call in some favors.
					Actor_Says(kActorMcCoy, 8320, 18); //00-8320.AUD	Really?
					Delay(500);
					Actor_Says(kActorGuzza, 450, 15); //04-0450.AUD	Yeah, I'll give it a try, kid. And I'll have to pull some strings, so don't go in there half-assed.
					Actor_Says(kActorMcCoy, 8502, 14); //00-8502.AUD	I hope it's enough.
					Actor_Says(kActorGuzza, 230, 14); //04-0230.AUD	Hey, don't worry. The boys upstairs want to keep our best and brightest happy.
					Delay(1000);
					Actor_Change_Animation_Mode(kActorMcCoy, 23);
					Actor_Change_Animation_Mode(kActorGuzza, 23);
					Delay(800);
					Item_Pickup_Spin_Effect_From_Actor(kModelAnimationFolder, kActorGuzza, 0, 0);
					Actor_Clue_Lose(kActorMcCoy, kClueFolder);
					Actor_Clue_Acquire(kActorGuzza, kClueFolder, true, -1);
					Delay(800);
					if (Player_Query_Agenda() == kPlayerAgendaPolite) {
						Actor_Start_Speech_Sample(kActorMcCoy, 4055); // 00-4055.AUD	Thanks, Lieutenant.
					} else {
						Actor_Start_Speech_Sample(kActorMcCoy, 8170); //00-8170.AUD	There you go.
					}
					Loop_Actor_Walk_To_XYZ(kActorMcCoy, 110.71, -162.25, 261.82, 0, true, false, false);
					Actor_Face_Actor(kActorGuzza, kActorMcCoy, true);
					Actor_Says(kActorGuzza, 740, 16); //04-0740.AUD	Look, McCoy. I know how it is on the street.
					Actor_Says(kActorGuzza, 750, 17); //04-0750.AUD	It's easy for a Blade Runner to step over the line.
					Actor_Face_Actor(kActorMcCoy, kActorGuzza, true);
					Delay(1000);
					Actor_Says(kActorMcCoy, 7980, 19); //00-7980.AUD	Yeah. Maybe.	
					Async_Actor_Walk_To_Waypoint(kActorMcCoy, 100, 0, false);
					Async_Actor_Walk_To_Waypoint(kActorGuzza, 101, 0, false);
					Delay(4000);
					Music_Stop(1u);
					Actor_Force_Stop_Walking(kActorMcCoy);
					Actor_Put_In_Set(kActorGuzza, kSetPS04);
					Player_Gains_Control();
					Game_Flag_Set(kFlagMcCoyFreedOfAccusations);
					Game_Flag_Set(kFlagMcCoyIsInnocent);
					if (Actor_Query_Friendliness_To_Other(kActorGuzza, kActorMcCoy) > 50) {
						Game_Flag_Reset(kFlagMcCoyRetiredHuman);
					}
					Actor_Set_Goal_Number(kActorMcCoy, kGoalMcCoyStartChapter5);
				}	
			}
		}
	}	
}	

void SceneScriptMA07::PlayerWalkedOut() {
	if (_vm->_cutContent) {	
		if (Actor_Query_Goal_Number(kActorRachael) == kGoalRachaelIsOutsideMcCoysBuildingAct3
			|| Actor_Query_Goal_Number(kActorRachael) == kGoalRachaelIsOutWalksToPoliceHQAct3
			|| Actor_Query_Goal_Number(kActorRachael) == kGoalRachaelIsOutFleeingToPoliceHQAct3
		) {
			Actor_Set_Goal_Number(kActorRachael, kGoalRachaelAtEndOfAct3IfNotMetWithMcCoy);
		} else if (Actor_Query_Goal_Number(kActorRachael) == kGoalRachaelIsOutResumesWalkToPoliceHQAct3) {
			Actor_Set_Goal_Number(kActorRachael, kGoalRachaelAtEndOfAct3IfMetWithMcCoy);
		} else if (Actor_Query_Goal_Number(kActorRachael) == kGoalRachaelIsOutsideMcCoysBuildingAct4
			|| Actor_Query_Goal_Number(kActorRachael) == kGoalRachaelIsOutWalksToPoliceHQAct4
		) {
			Actor_Set_Goal_Number(kActorRachael, kGoalRachaelAtEndOfAct4);
		}
		Game_Flag_Reset(kFlagRachaelWalks);
		Music_Stop(1u);		
	}
}

void SceneScriptMA07::DialogueQueueFlushed(int a1) {
}

} // End of namespace BladeRunner
