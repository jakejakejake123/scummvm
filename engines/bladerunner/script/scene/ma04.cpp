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

enum kMA04Loops {
	kMA04LoopInshot   = 0,
	kMA04LoopMainLoop = 1,
	kMA04LoopSleep    = 3,
	kMA04LoopWakeup   = 4
};

enum kMA04Exits {
	kMA04ExitMA02     = 0,
	kMA04ExitMA05     = 1,
	kMA04ExitKitchen  = 2
};

enum kMA04Regions {
	kMA04RegionPhone = 0,
	kMA04RegionBed   = 1
};

void SceneScriptMA04::InitializeScene() {
	if (Game_Flag_Query(kFlagMA05toMA04)) {
		Setup_Scene_Information(-7199.0f, 953.97f, 1579.0f, 502);
		if (Global_Variable_Query(kVariableChapter) != 2 && Global_Variable_Query(kVariableChapter) != 3) {
			Scene_Loop_Start_Special(kSceneLoopModeLoseControl, kMA04LoopInshot, false);
		}
	} else if (Game_Flag_Query(kFlagMA02ToMA04)) {
		Setup_Scene_Information(-7099.0f, 954.0f, 1866.0f, 502);
	} else if (Game_Flag_Query(kFlagMA04McCoySleeping)) {
		Setup_Scene_Information(-7107.0f, 954.0f, 1742.0f, 502);
		Scene_Loop_Start_Special(kSceneLoopModeLoseControl, kMA04LoopWakeup, false);
	} else {
		Setup_Scene_Information(-7143.0f, 954.0f, 1868.0f, 733);
	}
	Scene_Exit_Add_2D_Exit(kMA04ExitMA02,    496,  0, 639, 354, 1);
	Scene_Exit_Add_2D_Exit(kMA04ExitMA05,     33, 63, 113, 258, 0);
	Scene_Exit_Add_2D_Exit(kMA04ExitKitchen, 248, 98, 314, 284, 1);
	Scene_2D_Region_Add(kMA04RegionPhone, 343,  97, 353, 190);
	Scene_2D_Region_Add(kMA04RegionBed,     0, 340, 116, 479);
	Ambient_Sounds_Add_Looping_Sound(kSfxAPRTFAN1, 30,   0, 1);
	Ambient_Sounds_Add_Looping_Sound(kSfxRAINAWN1, 30, -80, 1);
	Ambient_Sounds_Add_Looping_Sound(kSfxAPRTAMB5, 12,   0, 1);
	Ambient_Sounds_Add_Sound(kSfxSWEEP2,   5,  30, 11, 11, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSWEEP3,   5,  30, 12, 12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSWEEP4,   5,  30, 12, 12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxTHNDER2, 10,  60, 20, 20,    0,   0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxTHNDER3, 10,  60, 20, 20,    0,   0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSIREN2,  10,  60, 16, 16, -100,   0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSPIN2B,  60, 180, 16, 25,    0,   0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSPIN3A,  60, 180, 16, 25,    0,   0, -101, -101, 0, 0);
	if (isPhoneRinging()) {
		Ambient_Sounds_Add_Sound(kSfxVIDFONE1, 3, 3, 100, 100, 0, 0, 0, 0, 99, 0);
	}
	Scene_Loop_Set_Default(kMA04LoopMainLoop);
}

void SceneScriptMA04::SceneLoaded() {
	Obstacle_Object("BED-DOG DISH", true);
	Unobstacle_Object("BEDDog BONE", true);
	Unobstacle_Object("BED-BOOK1", true);
	Clickable_Object("BED-SHEETS");
	if (Game_Flag_Query(kFlagMA04WatchedTV)) {
		Unclickable_Object("BED-TV-1");
		Unclickable_Object("BED-TV-2");
	} else {
		Clickable_Object("BED-TV-1");
		Clickable_Object("BED-TV-2");
	}
}

bool SceneScriptMA04::MouseClick(int x, int y) {
	return false;
}

bool SceneScriptMA04::ClickedOn3DObject(const char *objectName, bool a2) {
	if (Object_Query_Click("BED-SHEETS", objectName)) {
		sleep();
		return false;
	}
	if (Object_Query_Click("BED-TV-1", objectName) || Object_Query_Click("BED-TV-2", objectName)) {
		if (!Loop_Actor_Walk_To_Scene_Object(kActorMcCoy, "BED-TV-2", 24, true, false)) {
			Game_Flag_Set(kFlagMA04WatchedTV);
			Unclickable_Object("BED-TV-1");
			Unclickable_Object("BED-TV-2");
			Sound_Play(kSfxSPNBEEP4, 100, 0, 0, 50);
			turnOnTV();
			return false;
		}
		return true;
	}
	return false;
}

bool SceneScriptMA04::ClickedOnActor(int actorId) {
	return false;
}

bool SceneScriptMA04::ClickedOnItem(int itemId, bool a2) {
	return false;
}

bool SceneScriptMA04::ClickedOnExit(int exitId) {
	if (exitId == kMA04ExitMA02) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -7099.0f, 954.0f, 1866.0f, 0, true, false, false)) {
			Game_Flag_Set(kFlagMA04ToMA02);
			Set_Enter(kSetMA02_MA04, kSceneMA02);
		}
		return true;
	}
	if (exitId == kMA04ExitMA05) {
		float x, y, z;
		Actor_Query_XYZ(kActorMcCoy, &x, &y, &z);
		if (z <= 1677.0f || !Loop_Actor_Walk_To_XYZ(kActorMcCoy, -7199.0f, 955.0f, 1675.0f, 0, true, false, false)) {
			if (isPhoneMessageWaiting() || isPhoneRinging()) {
				Overlay_Remove("MA04OVER");
			}
#if BLADERUNNER_ORIGINAL_BUGS
			Loop_Actor_Walk_To_XYZ(kActorMcCoy, -7199.0f, 955.0f, 1675.0f, 0, false, false, true);
#else
			Loop_Actor_Walk_To_XYZ(kActorMcCoy, -7199.0f, 955.0f, 1627.0f, 0, false, false, true);
#endif // BLADERUNNER_ORIGINAL_BUGS
			Game_Flag_Set(kFlagMA04toMA05);
			if (Global_Variable_Query(kVariableChapter) != 2 && Global_Variable_Query(kVariableChapter) != 3) {
				Async_Actor_Walk_To_XYZ(kActorMcCoy, -7199.0f, 956.17f, 1568.0f, 0, false);
			}
			Set_Enter(kSetMA05, kSceneMA05);
		}
		return true;
	}
	if (exitId == kMA04ExitKitchen) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -7115.0f, 954.0f, 1742.0f, 0, true, false, false)) {
			int sounds[] = {kSfxBARSFX1, kSfxTOILET1, kSfxDRAIN1X, kSfxWASH1, kSfxGARGLE1};
			Ambient_Sounds_Play_Sound(sounds[Random_Query(0, 4)], 50, 0, 0, 0);
			Delay(3000);
			Loop_Actor_Walk_To_XYZ(kActorMcCoy, -7139.0f, 954.0f, 1746.0f, 0, true, false, true);
		}
	}
	return false;
}

bool SceneScriptMA04::ClickedOn2DRegion(int region) {
	if (Player_Query_Combat_Mode()) {
		return false;
	}
	if (region == kMA04RegionBed) {
		sleep();
		return true;
	}
	if (region == kMA04RegionPhone) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -7176.0f, 954.0f, 1806.0f, 0, true, false, false)) {
			Actor_Face_Heading(kActorMcCoy, 256, false);
			if (isPhoneRinging()) {
				Actor_Says(kActorMcCoy, 2680, 0);
				Ambient_Sounds_Remove_Sound(kSfxVIDFONE1, true);
				Sound_Play(kSfxSPNBEEP9, 100, 0, 0, 50);
				Overlay_Remove("MA04OVER");
				Delay(500);
				// Altered the conditions for which McCoy receives the phone call from Crystal or Clovis.
				// In oeder to get Crystal on your side it will not be dependent on whether or not you help the reps since you need to be able to
				// help them and still get her to trust you so you can get the Crystal betrayal ending. In order to get Crystal on your side (including the true blade runner ending with Crystal) you have to
				// 1. Not retire a human.
				// 2. Do not warn Lucy, Dektora and Izo (restored) about Crystal by selecting the Crystal option.
				// 3. In act 4 when meeting Crystal outside McCoys apartment in act 4 (restored). Have 60 friendliness with Crystal by retiring 2 reps and being
				// nice to her by accepting her offer to exchange information. You can also get her to trust you by submitting the Guzza evidence to the police.  
				if (_vm->_cutContent) {
					if (Global_Variable_Query(kVariableAffectionTowards) != kAffectionTowardsDektora
					&& Global_Variable_Query(kVariableAffectionTowards) != kAffectionTowardsLucy) {
						if (Game_Flag_Query(kFlagMcCoyIsInnocent)) {
							if (!Game_Flag_Query(kFlagMcCoyRetiredHuman)) {	
								phoneCallWithSteele();
							} else {
								phoneCallWithClovis();
							}
						} else {
							phoneCallWithClovis();
						}
					} else if (Global_Variable_Query(kVariableAffectionTowards) == kAffectionTowardsDektora) {
						phoneCallWithDektora();
					} else if (Global_Variable_Query(kVariableAffectionTowards) == kAffectionTowardsLucy) {
						phoneCallWithLucy();
					}
					Music_Play(kMusicBRBlues, 52, 0, 3, -1, kMusicLoopPlayOnce, 0);
				} else if (Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
					if (Global_Variable_Query(kVariableAffectionTowards) == kAffectionTowardsDektora) {
						phoneCallWithDektora();
					} else if (Global_Variable_Query(kVariableAffectionTowards) == kAffectionTowardsLucy) {
						phoneCallWithLucy();
					} else {
						phoneCallWithClovis();
					}
				} else {
					phoneCallWithSteele();
				}
				Music_Play(kMusicBRBlues, 52, 0, 3, -1, kMusicLoopPlayOnce, 0);
				return false;
			}
			if (Actor_Clue_Query(kActorClovis, kClueMcCoyRetiredZuben) && !Game_Flag_Query(kFlagMA04PhoneMessageFromClovis)) {
				if (_vm->_cutContent) {
					Actor_Change_Animation_Mode(kActorMcCoy, 23);
					Delay(800);
					Sound_Play(kSfxSPNBEEP9, 100, 0, 0, 50);
					Overlay_Remove("MA04OVER");
					Delay(800);
				} else {
					Sound_Play(kSfxSPNBEEP9, 100, 0, 0, 50);
					Overlay_Remove("MA04OVER");
					Delay(500);
				}	
				Actor_Says(kActorClovis, 310, 3);
				Actor_Says(kActorClovis, 320, 3);
				if (_vm->_cutContent && Global_Variable_Query(kVariableChapter) < 3) {
					Actor_Voice_Over(1300, kActorVoiceOver); //99-1300.AUD	Crank calls were a dime a dozen in this city and I'd had my share.
					Actor_Voice_Over(1310, kActorVoiceOver); //99-1310.AUD	Still, this guy sounded more like an English teacher than the average scumbag.
					Actor_Voice_Over(1320, kActorVoiceOver); //99-1320.AUD	If I'd been more awake, the message might have spooked me.
				} else if (!Game_Flag_Query(kFlagDirectorsCut) && Global_Variable_Query(kVariableChapter) < 3) {
					Actor_Voice_Over(1300, kActorVoiceOver); //99-1300.AUD	Crank calls were a dime a dozen in this city and I'd had my share.
					Actor_Voice_Over(1310, kActorVoiceOver); //99-1310.AUD	Still, this guy sounded more like an English teacher than the average scumbag.
					Actor_Voice_Over(1320, kActorVoiceOver); //99-1320.AUD	If I'd been more awake, the message might have spooked me.
				}
				Actor_Says(kActorMcCoy, 2445, 13);
				Sound_Play(kSfxSPNBEEP9, 100, 0, 0, 50);
				Game_Flag_Set(kFlagMA04PhoneMessageFromClovis);
				return true;
			}
			if (Actor_Clue_Query(kActorLucy, kClueMcCoyLetZubenEscape) && !Game_Flag_Query(kFlagMA04PhoneMessageFromLucy)) {
				if (_vm->_cutContent) {
					Actor_Change_Animation_Mode(kActorMcCoy, 23);
					Delay(800);
					Sound_Play(kSfxSPNBEEP9, 100, 0, 0, 50);
					Overlay_Remove("MA04OVER");
					Delay(800);
				} else {
					Sound_Play(kSfxSPNBEEP9, 100, 0, 0, 50);
					Overlay_Remove("MA04OVER");
					Delay(500);
				}	
				Actor_Says(kActorLucy, 500, 3);
				Actor_Says(kActorLucy, 510, 3); //-	06-0510.AUD	I heard about what you did for my friend and I just wanted to say thanks.
				//Added in an extra line
				if (_vm->_cutContent) {
					Actor_Says(kActorLucy, 520, 3); //-	06-0520.AUD	Sorry I missed you. Goodbye.
					if (Global_Variable_Query(kVariableChapter) < 3) {
						Actor_Voice_Over(1330, kActorVoiceOver); //99-1330.AUD	The message could have come from any of a dozen people.
						if (Player_Query_Agenda() == kPlayerAgendaPolite) { 
							Actor_Voice_Over(1340, kActorVoiceOver); //99-1340.AUD	I'd done my share of favors when I was in uniform.
						}
						Actor_Voice_Over(1350, kActorVoiceOver); //99-1350.AUD	Something about the voice was familiar but I was too tired to place it for sure.
					} else {
						Delay(1000);
						Actor_Says(kActorMcCoy, 1600, 11); //00-1600.AUD	Lucy?
					}
				} else if (!Game_Flag_Query(kFlagDirectorsCut) && Global_Variable_Query(kVariableChapter) < 3) {
					Actor_Voice_Over(1330, kActorVoiceOver); //99-1330.AUD	The message could have come from any of a dozen people.
					Actor_Voice_Over(1340, kActorVoiceOver); //99-1340.AUD	I'd done my share of favors when I was in uniform.
					Actor_Voice_Over(1350, kActorVoiceOver); //99-1350.AUD	Something about the voice was familiar but I was too tired to place it for sure.
				}
				Actor_Says(kActorMcCoy, 2445, 13);
				Sound_Play(kSfxSPNBEEP9, 100, 0, 0, 50);
				Game_Flag_Set(kFlagMA04PhoneMessageFromLucy);
				return true;
			}
			Actor_Says(kActorMcCoy, 2670, 13);
			if (_vm->_cutContent) {
				Actor_Says(kActorMcCoy, 2675, 17);
			} else if (!Game_Flag_Query(kFlagDirectorsCut)) {
				Actor_Says(kActorMcCoy, 2675, 17);
			}
		}
		return true;
	}
	return false;
}

void SceneScriptMA04::SceneFrameAdvanced(int frame) {
	Set_Fade_Color(0, 0, 0);
	if (frame >= 91 && frame < 121) {
		Set_Fade_Density((frame - 91) / 30.0f);
	} else if (frame >= 121 && frame < 151) {
		Set_Fade_Density((151 - frame) / 30.0f);
	} else {
		Set_Fade_Density(0.0f);
	}
	if (frame == 121 && (Game_Flag_Query(kFlagZubenRetired) || Game_Flag_Query(kFlagZubenSpared)) && !Game_Flag_Query(kFlagPS04GuzzaTalkZubenRetired)) {
		Sound_Play(kSfxVIDFONE1, 50, 0, 0, 50);
	}
}

void SceneScriptMA04::ActorChangedGoal(int actorId, int newGoal, int oldGoal, bool currentSet) {
}

void SceneScriptMA04::PlayerWalkedIn() {
	// Made it so when McCoy is drugged and appears in his apartment these unused lines play. McCoy then appears back in nightclub row since the player
	// can not use the spinner since it is in nightclub row. McCoy had to walk all the way back to nightclub row. 
	if (_vm->_cutContent) {
		if (Game_Flag_Query(kFlagNR01McCoyIsDrugged)) {
			Actor_Set_Goal_Number(kActorMcCoy, kGoalMcCoyNR01LayDrugged);
			Delay(2000);
			Actor_Says(kActorVoiceOver, 3560, kAnimationModeTalk); //99-3560.AUD	Ugh. This was all too familiar territory. Jackhammers were drilling through my brain and my stomach felt like it had been bathed in battery acid.	
			Actor_Says(kActorVoiceOver, 3580, kAnimationModeTalk); //99-3580.AUD	I couldn’t remember how I got home, but it was damn sure a miracle I’d made it at all.
			Actor_Says(kActorVoiceOver, 3590, kAnimationModeTalk); //99-3590.AUD	I don’t know if somebody had slipped me a mickey or what…	
			Actor_Says(kActorVoiceOver, 3600, kAnimationModeTalk); //99-3600.AUD	but whatever it was I was sure as hell paying the price.	 
			Actor_Says(kActorVoiceOver, 3610, kAnimationModeTalk); //99-3610.AUD	Something inside told me that if I made a hash out of things any more…	
			Actor_Says(kActorVoiceOver, 3620, kAnimationModeTalk); //99-3620.AUD	the next price I paid would probably be my life.
			Delay(2000);
			Game_Flag_Reset(kFlagNR01McCoyIsDrugged);
			Set_Enter(kSceneNR01, kSceneNR01);
			Scene_Exits_Enable();
			Player_Gains_Control();
		}
	}
	if (Game_Flag_Query(kFlagMA04McCoySleeping)) {
		Player_Gains_Control();
	}
	if (isPhoneMessageWaiting() || isPhoneRinging()) {
		Overlay_Play("MA04OVER", 0, true, false, 0);
	}
	if (Game_Flag_Query(kFlagMA04McCoySleeping)) {
		Loop_Actor_Walk_To_XYZ(kActorMcCoy, -7139.0f, 954.0f, 1746.0f, 0, true, false, false);
	} else if (Game_Flag_Query(kFlagMA02ToMA04)) {
		if (_vm->_cutContent) {
			Player_Loses_Control();
			Loop_Actor_Walk_To_XYZ(kActorMcCoy, -7200.37f, 954.09f, 1862.70f, 0, true, false, false);
			Player_Gains_Control();
		} else {
			Loop_Actor_Walk_To_XYZ(kActorMcCoy, -7143.0f, 954.0f, 1868.0f, 0, true, false, false);
		}
	}
	Game_Flag_Reset(kFlagMA02ToMA04);
	Game_Flag_Reset(kFlagMA05toMA04);
	Game_Flag_Reset(kFlagMA04McCoySleeping);
	if (Game_Flag_Query(kFlagChapter1Ended)) {
		if (Global_Variable_Query(kVariableChapter) == 2 && !Actor_Clue_Query(kActorMcCoy, kCluePhoneCallGuzza)) {
			Sound_Play(kSfxVIDFONE1, 100, 0, 0, 50);
			Loop_Actor_Walk_To_XYZ(kActorMcCoy, -7176.0f, 954.0f, 1806.0f, 0, false, false, false);
			Actor_Face_Heading(kActorMcCoy, 256, true);
			Actor_Says(kActorMcCoy, 2680, kAnimationModeIdle);
			Sound_Play(kSfxSPNBEEP9, 100, 0, 0, 50);
			Delay(500);
			if (_vm->_cutContent) {
				if (Actor_Query_Friendliness_To_Other(kActorGuzza, kActorMcCoy) < 51) {
					Actor_Says(kActorGuzza, 1390, 3); //04-1390.AUD	McCoy! Where the hell have you been? We’ve been looking all over for you.
					if (Player_Query_Agenda() == kPlayerAgendaPolite) {
						Actor_Says(kActorMcCoy, 2545, 13); //00-2545.AUD	Sorry, but I-- I was just… sleeping. What’s going on?
					} else {
						Actor_Says(kActorMcCoy, 2690, 17);
					}
				} else {
					Actor_Says(kActorGuzza, 0, 3);
					if (Player_Query_Agenda() != kPlayerAgendaSurly 
					&& Player_Query_Agenda() != kPlayerAgendaErratic) {
						Actor_Says(kActorMcCoy, 2685, 13);
					} else {
						Actor_Says(kActorMcCoy, 665, 16); //00-0665.AUD	Real funny, pal.
					}
					Actor_Says(kActorGuzza, 10, 3);
					Actor_Says(kActorMcCoy, 2690, 17);
				}
			} else {
				Actor_Says(kActorGuzza, 0, 3);
				Actor_Says(kActorMcCoy, 2685, 13);
				Actor_Says(kActorGuzza, 10, 3);
				Actor_Says(kActorMcCoy, 2690, 17);
			}
			Actor_Says(kActorGuzza, 30, 3);
			Actor_Says(kActorMcCoy, 2695, 12);
			Actor_Says(kActorGuzza, 40, 3);
			Actor_Says(kActorGuzza, 50, 3);
			Actor_Says(kActorMcCoy, 2700, 3);
			Actor_Says(kActorGuzza, 60, 3);
			Actor_Says(kActorGuzza, 70, 3);
			Sound_Play(kSfxSPNBEEP9, 100, 0, 0, 50);
			Actor_Clue_Acquire(kActorMcCoy, kCluePhoneCallGuzza, false, kActorGuzza);
			Spinner_Set_Selectable_Destination_Flag(kSpinnerDestinationTyrellBuilding, true);
			Game_Flag_Set(kFlagRC01PoliceDone);
			if (!Game_Flag_Query(kFlagRC01ChromeDebrisTaken)) {
				Game_Flag_Set(kFlagRC01ChromeDebrisTaken);
				Item_Remove_From_World(kItemChromeDebris);
			}
			Actor_Set_Goal_Number(kActorOfficerLeary, kGoalOfficerLearyEndOfAct1);
			Actor_Put_In_Set(kActorOfficerLeary, kSetFreeSlotC);
			Actor_Set_At_Waypoint(kActorOfficerLeary, 35, 0); // kSetFreeSlotC
			Autosave_Game(0);
		}
		//return false;
		return;
	}
	if ((Game_Flag_Query(kFlagZubenRetired) || Game_Flag_Query(kFlagZubenSpared)) && !Game_Flag_Query(kFlagChapter1Ending)) {
		if (_vm->_cutContent) {
			Sound_Play(kSfxSPNBEEP4, 100, 0, 0, 50);
			Overlay_Play("MA04OVR2", 0, true, false, 0);
			Actor_Face_Object(kActorMcCoy, "BED-TV-1", true);
			ADQ_Add(kActorNewscaster, 40, kAnimationModeTalk);
			ADQ_Add(kActorNewscaster, 50, kAnimationModeTalk);
			ADQ_Add(kActorNewscaster, 60, kAnimationModeTalk);
			ADQ_Add(kActorNewscaster, 70, kAnimationModeTalk);
			ADQ_Add(kActorNewscaster, 80, kAnimationModeTalk);
			Delay(20000);
			Overlay_Remove("MA04OVR2");
			ADQ_Add(kActorMcCoy, 8625, 14); //00-8625.AUD	This city is a cesspool.
			Music_Play(kMusicBRBlues, 52, 0, 2, -1, kMusicLoopPlayOnce, 0);
			Delay(3000);
			Player_Loses_Control();
		}
		if (!_vm->_cutContent) {
			Music_Play(kMusicBRBlues, 52, 0, 2, -1, kMusicLoopPlayOnce, 0);
			Player_Loses_Control();
		}
		Loop_Actor_Walk_To_XYZ(kActorMcCoy, -7199.0f, 955.0f, 1677.0f, 0, true, false, false);
		if (isPhoneMessageWaiting() || isPhoneRinging()) {
			Overlay_Remove("MA04OVER");	
		}
		Loop_Actor_Walk_To_XYZ(kActorMcCoy, -7199.0f, 955.0f, 1675.0f, 0, true, false, false);
		Game_Flag_Set(kFlagChapter1Ending);

		Async_Actor_Walk_To_XYZ(kActorMcCoy, -7204.0f, 956.17f, 1568.0f, 0, false);
		Set_Enter(kSetMA05, kSceneMA05);
	}
}

void SceneScriptMA04::PlayerWalkedOut() {
	Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
	Ambient_Sounds_Remove_All_Looping_Sounds(1u);
	if (Game_Flag_Query(kFlagChapter2Intro)) {
		Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
		Ambient_Sounds_Remove_All_Looping_Sounds(1u);
		Outtake_Play(kOuttakeMovieA, false, -1);
		Game_Flag_Reset(kFlagChapter2Intro);
	}
}

void SceneScriptMA04::DialogueQueueFlushed(int a1) {
	Overlay_Remove("MA04OVR2");
}

bool SceneScriptMA04::isPhoneRinging() {
	return Global_Variable_Query(kVariableChapter) == 5
	   && !Actor_Clue_Query(kActorMcCoy, kCluePhoneCallClovis)
	   && !Actor_Clue_Query(kActorMcCoy, kCluePhoneCallCrystal)
	   && !Actor_Clue_Query(kActorMcCoy, kCluePhoneCallDektora1)
	   && !Actor_Clue_Query(kActorMcCoy, kCluePhoneCallDektora2)
	   && !Actor_Clue_Query(kActorMcCoy, kCluePhoneCallLucy1)
	   && !Actor_Clue_Query(kActorMcCoy, kCluePhoneCallLucy2);
}

bool SceneScriptMA04::isPhoneMessageWaiting() {
	return (Actor_Clue_Query(kActorClovis, kClueMcCoyRetiredZuben) && !Game_Flag_Query(kFlagMA04PhoneMessageFromClovis))
	    || (Actor_Clue_Query(kActorLucy, kClueMcCoyLetZubenEscape) && !Game_Flag_Query(kFlagMA04PhoneMessageFromLucy));
}

void SceneScriptMA04::phoneCallWithDektora() {
	int answer;
	// Made it so this flag is set whenever Dektora Lucy or Clovis gives you a phone call.
	// With the new requirements I've added it can be possible for the player to reach this part without having the flag set.
	// So I have set it here and also for Clovis and Lucys phone calls just to be safe.
	Actor_Says(kActorDektora, 220, 3);
	Actor_Says(kActorMcCoy, 2460, 0);  //00-2460.AUD	Yeah.
	Actor_Says(kActorDektora, 230, 3); //03-0230.AUD	Look, I think I got Clovis and Sadik to let you alone.
	Actor_Says(kActorDektora, 240, 3);
	if (_vm->_cutContent) {
		if (Actor_Clue_Query(kActorMcCoy, kClueCrystalsCigarette)) { 	
			Actor_Says(kActorMcCoy, 2465, 0);
			Actor_Says(kActorDektora, 250, 3); //03-0250.AUD	What’s the matter?
			Actor_Says_With_Pause(kActorMcCoy, 2470, 1.5f, 17);
			if (!Game_Flag_Query(kFlagDektoraIsReplicant)) {
				Actor_Says(kActorDektora, 260, 3);
				if (Player_Query_Agenda() != kPlayerAgendaPolite) {
					Actor_Says(kActorMcCoy, 2475, 15); //00-2475.AUD	Not it. Her! Maggie.
				} else {
					Actor_Says(kActorMcCoy, 2460, 15); //00-2460.AUD	Yeah.
				}
			} 
			if (Actor_Query_Friendliness_To_Other(kActorClovis, kActorMcCoy) > 50
			&& !Game_Flag_Query(kFlagMcCoyRetiredReplicant)) {
				Actor_Says(kActorDektora, 270, 3); //03-0270.AUD	Clovis didn’t do it. I’m sure of that.
				Actor_Says(kActorMcCoy, 2480, 0); //00-2480.AUD	No kidding.
			}
		} else {
			Actor_Says(kActorMcCoy, 4880, 13); //00-4880.AUD	Is that right?
		}
	} else {
		Actor_Says(kActorMcCoy, 2465, 0);
		Actor_Says(kActorDektora, 250, 3); //03-0250.AUD	What’s the matter?
		Actor_Says(kActorDektora, 260, 3);
		Actor_Says_With_Pause(kActorMcCoy, 2470, 1.5f, 17);
		Actor_Says(kActorMcCoy, 2475, 15); //00-2475.AUD	Not it. Her! Maggie.
		Actor_Says(kActorDektora, 270, 3); //03-0270.AUD	Clovis didn’t do it. I’m sure of that.
		Actor_Says(kActorMcCoy, 2480, 0); //00-2480.AUD	No kidding.
	}
	Actor_Says(kActorDektora, 280, 3); //03-0280.AUD	I also told him about us, Ray. He took it very well.
	Actor_Says(kActorDektora, 290, 3); //03-0290.AUD	He and I are finished for good this time.
	if (_vm->_cutContent) {
		if (Player_Query_Agenda() != kPlayerAgendaPolite) {
			Actor_Says(kActorMcCoy, 2485, 19); //00-2485.AUD	I’ve a hard time believing that.
		} else {
			Actor_Says(kActorMcCoy, 8320, 18); //00-8320.AUD	Really?
		}
	} else {
		Actor_Says(kActorMcCoy, 2485, 19); //00-2485.AUD	I’ve a hard time believing that.
	}
	Actor_Says(kActorDektora, 300, 3); //03-0300.AUD	He’s been very philosophical. He’s aware that his time is running out.
	Actor_Says(kActorDektora, 310, 3); //03-0310.AUD	That’s why he wants to help us.
	Actor_Says(kActorMcCoy, 2490, 0); //00-2490.AUD	No hard feelings, huh?
	if (_vm->_cutContent) {
		if (Actor_Query_Friendliness_To_Other(kActorClovis, kActorMcCoy) > 50
		&& !Game_Flag_Query(kFlagMcCoyRetiredReplicant)) {
			Actor_Says(kActorDektora, 330, 3); 
			Actor_Says(kActorMcCoy, 2495, 0); //00-2495.AUD	Okay.
		} else {
			Delay(2000);
			Actor_Says(kActorMcCoy, 2750, kAnimationModeTalk); //00-2750.AUD	Okay, I get the picture.
		}
	} 
	if (_vm->_cutContent) {
		if (Actor_Query_Intelligence(kActorDektora) == 90) {
			Actor_Says(kActorDektora, 340, 3); //03-0340.AUD	But there’s another way. Why don’t you and I just go away from here?
			Actor_Says(kActorDektora, 350, 3);
		}
	} else {
		Actor_Says(kActorDektora, 340, 3); //03-0340.AUD	But there’s another way. Why don’t you and I just go away from here?
		Actor_Says(kActorDektora, 350, 3);
	}
	if (_vm->_cutContent) {
		if (!Game_Flag_Query(kFlagCrazylegsArrested)
		&& Actor_Query_Goal_Number(kActorCrazylegs) != kGoalCrazyLegsLeavesShowroom
		&& Actor_Query_Intelligence(kActorDektora) == 90 
		&& !Actor_Clue_Query(kActorDektora, kClueMcCoyRetiredZuben)
		&& !Actor_Clue_Query(kActorDektora, kClueMcCoyRetiredLucy)
		&& !Actor_Clue_Query(kActorDektora, kClueMcCoyRetiredGordo)
		&& !Game_Flag_Query(kFlagGuzzaSaved)) {
			answer = 1160; // OK
		} else {
			Dialogue_Menu_Clear_List();
			DM_Add_To_List_Never_Repeat_Once_Selected(1160, 1, 2, 3); // OK
			DM_Add_To_List_Never_Repeat_Once_Selected(1170, 2, 1, 1); // CLOVIS
			Dialogue_Menu_Appear(320, 240);
			answer = Dialogue_Menu_Query_Input();
			Dialogue_Menu_Disappear();
		}
	} else {
		if (Game_Flag_Query(kFlagCrazylegsArrested)
		|| Actor_Query_Goal_Number(kActorCrazylegs) == kGoalCrazyLegsLeavesShowroom
		) {
			answer = 1170; // CLOVIS
		} else {
			Dialogue_Menu_Clear_List();
			DM_Add_To_List_Never_Repeat_Once_Selected(1160, 1, 1, 2); // OK
			DM_Add_To_List_Never_Repeat_Once_Selected(1170, 2, 1, 1); // CLOVIS
			Dialogue_Menu_Appear(320, 240);
			answer = Dialogue_Menu_Query_Input();
			Dialogue_Menu_Disappear();
		}
	}
	if (answer == 1160) { // OK
		Actor_Says(kActorMcCoy, 2500, 19); 
		Actor_Says(kActorDektora, 360, 3);
		Actor_Says(kActorMcCoy, 2510, 0); //00-2510.AUD	I know it.
		//Made it so the lines where Dektora mentions her and Gordo going to buy a car from Crazylegs only plays if Dektora is a replicant.
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagDektoraIsReplicant)) {
				Actor_Says(kActorDektora, 370, 3); //03-0370.AUD	Gordo and I went there before looking for a vehicle.
				Actor_Says(kActorDektora, 380, 3); //03-0380.AUD	The owner was nice to us. He’ll probably help us, if we pay him.
			}
		} else {
			Actor_Says(kActorDektora, 370, 3); 
			Actor_Says(kActorDektora, 380, 3);
		}
		Actor_Says(kActorMcCoy, 2515, 12); //00-2515.AUD	We’d need a Spinner to be able to get anywhere.
		Actor_Says(kActorDektora, 390, 3); //03-0390.AUD	He’s got a couple for sale.
		Actor_Says(kActorMcCoy, 2520, 13);  //00-2520.AUD	It’s real risky. And illegal.
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagDektoraIsReplicant)) {
				Actor_Says(kActorDektora, 400, 3); //Well, it’s better than sitting out there in the Kipple waiting to die.
				Actor_Says(kActorDektora, 410, 3); //03-0410.AUD	Watching everybody else die. If you won’t do it, I’ll go get the car myself.
				Actor_Says(kActorMcCoy, 2525, 15);  //00-2525.AUD	I didn’t say I wasn’t gonna do it.
			} else {
				Delay(500);
				Actor_Says(kActorMcCoy, 3170, 13); //00-3170.AUD	I’m there.
			}
		} else {
			Actor_Says(kActorDektora, 400, 3); //Well, it’s better than sitting out there in the Kipple waiting to die.
			Actor_Says(kActorDektora, 410, 3); //03-0410.AUD	Watching everybody else die. If you won’t do it, I’ll go get the car myself.
			Actor_Says(kActorMcCoy, 2525, 15);  //00-2525.AUD	I didn’t say I wasn’t gonna do it.
		}
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagDektoraIsReplicant)) {
				Actor_Says(kActorDektora, 490, 3); //03-0490.AUD	And if you can’t come, adieu my love.
			} else {
				Actor_Says(kActorDektora, 420, 3); //03-0420.AUD	Then meet me there. I’ll be there within the hour.
			}
		} else {
			Actor_Says(kActorDektora, 420, 3); //03-0420.AUD	Then meet me there. I’ll be there within the hour.
		}
		Sound_Play(kSfxSPNBEEP9, 100, 0, 0, 50);
		if (_vm->_cutContent) {
			Game_Flag_Set(kFlagCarEnding);
			Actor_Clue_Acquire(kActorMcCoy, kCluePhoneCallDektora1, true, kActorDektora);
			Actor_Set_Targetable(kActorDektora, false);
		} else {
			Actor_Clue_Acquire(kActorMcCoy, kCluePhoneCallDektora1, true, -1);
		}
	} else { 
		Actor_Says_With_Pause(kActorMcCoy, 2505, 0.5f, 19);
		Actor_Says(kActorDektora, 430, 3); //03-0430.AUD	He’s been struggling out in the Kipple. Trying to get the moonbus fixed.
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagDektoraIsReplicant)
			&& Actor_Query_Intelligence(kActorSadik) == 70) {
				Actor_Says(kActorDektora, 440, 3); //03-0440.AUD	If you could help repair it, maybe we can all leave together.
			}
		} else {
			Actor_Says(kActorDektora, 440, 3); //03-0440.AUD	If you could help repair it, maybe we can all leave together.
		}
		Actor_Says(kActorMcCoy, 2530, 0); //00-2530.AUD	How far out are they?
		Actor_Says(kActorDektora, 450, 3);
		Actor_Says(kActorMcCoy, 2535, 12); //00-2535.AUD	There’s bound to be tons of radioactive waste between here and there.
		Actor_Says(kActorDektora, 460, 3); //03-0460.AUD	There’s a tunnel in the sewers. That’s how Clovis and Sadik go back and forth.
		Actor_Says_With_Pause(kActorDektora, 470, 1.0f, 3);
		Actor_Says(kActorDektora, 480, 3); //03-0480.AUD	I need you, Ray. I can’t watch my friends die. Not alone.
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagDektoraIsReplicant)) {
				Actor_Says(kActorDektora, 490, 3); //03-0490.AUD	And if you can’t come, adieu my love.
			} else {
				Actor_Says(kActorMcCoy, 1825, 13);	//00-1825.AUD	Okay
				Actor_Says(kActorDektora, 420, 3); //03-0420.AUD	Then meet me there. I’ll be there within the hour.
			}
		} else {
			Actor_Says(kActorDektora, 490, 3); //03-0490.AUD	And if you can’t come, adieu my love.
		}
		Sound_Play(kSfxSPNBEEP9, 100, 0, 0, 50);
		if (_vm->_cutContent) {
			if (Player_Query_Agenda() != kPlayerAgendaPolite) {
				Actor_Says(kActorMcCoy, 2540, 15); //00-2540.AUD	Dektora, wait! Damn it.
			}
		} else {
			Actor_Says(kActorMcCoy, 2540, 15); //00-2540.AUD	Dektora, wait! Damn it.
		}
		if (_vm->_cutContent) {
			if (Actor_Query_Friendliness_To_Other(kActorClovis, kActorMcCoy) > 50
			&& !Game_Flag_Query(kFlagMcCoyRetiredReplicant)) {
				Game_Flag_Set(kFlagMcCoyIsHelpingReplicants);
				Actor_Set_Goal_Number(kActorClovis, kGoalClovisKP07Wait);
				Actor_Set_Goal_Number(kActorSadik, 414);
			} else {
				if (!Actor_Clue_Query(kActorMcCoy, kClueCrystalsCigarette)) {
					if (Actor_Query_Goal_Number(kActorSadik) < kGoalSadikGone
					&& Game_Flag_Query(kFlagSadikIsReplicant)) {
						Game_Flag_Reset(kFlagMcCoyIsHelpingReplicants);
						Actor_Set_Goal_Number(kActorSadik, 411);
					} else {
						Actor_Set_Goal_Number(kActorMaggie, kGoalMaggieKP05Wait);
						Actor_Put_In_Set(kActorClovis, kSetKP05_KP06);
						Actor_Set_At_XYZ(kActorClovis, -961.0f, 0.0f, -778.0f, 150);
						Game_Flag_Reset(kFlagMcCoyIsHelpingReplicants);
						if (Actor_Query_Goal_Number(kActorSadik) < kGoalSadikGone) {
							Actor_Put_In_Set(kActorSadik, kSetKP05_KP06);
							Actor_Set_At_XYZ(kActorSadik, -1134.0f, 0.0f, 73.45f, 398);
						}
					}
				} else {
					Game_Flag_Set(kFlagMcCoyIsHelpingReplicants);
					Actor_Set_Goal_Number(kActorClovis, kGoalClovisKP07Wait);
					Actor_Set_Goal_Number(kActorSadik, 414);
				}
			}
			Actor_Clue_Acquire(kActorMcCoy, kCluePhoneCallDektora2, true, kActorDektora);	
		} else {
			Actor_Clue_Acquire(kActorMcCoy, kCluePhoneCallDektora2, true, -1);
		}
	}
}

void SceneScriptMA04::phoneCallWithLucy() {
	Actor_Says(kActorLucy, 530, 3); 
	if (_vm->_cutContent) {
		if (Player_Query_Agenda() == kPlayerAgendaPolite) {
			Actor_Says(kActorMcCoy, 2545, 19); //00-2545.AUD	Sorry, but I-- I was just… sleeping. What’s going on?
		} else {
			Actor_Says(kActorMcCoy, 8320, 13); //00-8320.AUD	Really?
		}
	} else {
		Actor_Says(kActorMcCoy, 2545, 19); //00-2545.AUD	Sorry, but I-- I was just… sleeping. What’s going on?
	}
	Actor_Says(kActorLucy, 540, 3);  //06-0540.AUD	Father wants to meet you. He said he’s sorry about everything he did.
	Actor_Says(kActorLucy, 550, 3);
	Actor_Says(kActorMcCoy, 2550, 13); //00-2550.AUD	Where is he now?
	Actor_Says(kActorLucy, 560, 3);
	Actor_Says(kActorMcCoy, 2555, 19); //00-2555.AUD	Tell him to stay where he is, until I can find a way for all of us to escape.
	Actor_Says(kActorLucy, 570, 3);
	Actor_Says(kActorMcCoy, 2560, 17); //00-2560.AUD	Maybe we’ll do it after I talk to him.
	Actor_Says(kActorLucy, 580, 3); // You promise?
	if (_vm->_cutContent) {
		if (!Game_Flag_Query(kFlagCrazylegsArrested)
		&& Actor_Query_Goal_Number(kActorCrazylegs) != kGoalCrazyLegsLeavesShowroom
		&& Actor_Query_Intelligence(kActorLucy) == 70
		&& !Actor_Clue_Query(kActorLucy, kClueMcCoyRetiredZuben)
		&& !Actor_Clue_Query(kActorLucy, kClueMcCoyRetiredDektora)
		&& !Actor_Clue_Query(kActorLucy, kClueMcCoyRetiredGordo)
		&& !Game_Flag_Query(kFlagGuzzaSaved)) {
			Actor_Says(kActorLucy, 590, 3); //06-0590.AUD	We could buy a car. From that place next to the arcade.
			Actor_Says(kActorMcCoy, 2565, 12);
			Actor_Says(kActorLucy, 600, 3); //06-0600.AUD	One of those flying cars would though. 
			Actor_Says(kActorLucy, 610, 3);
			Actor_Says(kActorLucy, 620, 3);
			Actor_Says(kActorMcCoy, 6805, 13); //00-6805.AUD	I-- I promise you. But for now we gotta be careful. You should stay hidden for a while.
			Actor_Says_With_Pause(kActorLucy, 630, 0.0f, 3); //06-0630.AUD	I’ll meet you there, okay? At the place where he sells the cars.
			Actor_Says_With_Pause(kActorMcCoy, 2575, 0.0f, 15);
			Actor_Says(kActorLucy, 640, 3);
			Sound_Play(kSfxSPNBEEP9, 100, 0, 0, 50);
			Game_Flag_Set(kFlagCarEnding);
			Actor_Clue_Acquire(kActorMcCoy, kCluePhoneCallLucy1, true, kActorLucy);
			Actor_Set_Targetable(kActorLucy, false);
		} else {
			Actor_Says(kActorMcCoy, 6805, 13); //00-6805.AUD	I-- I promise you. But for now we gotta be careful. You should stay hidden for a while.
			Actor_Says(kActorLucy, 640, 3);
			Actor_Says_With_Pause(kActorMcCoy, 2570, 0.0f, 13); // Lucy, there's a good chance--
			Sound_Play(kSfxSPNBEEP9, 100, 0, 0, 50); // (Lucy hangs up)
			Actor_Says(kActorMcCoy, 2575, 15); // Wait, Lucy!
			if (Actor_Query_Friendliness_To_Other(kActorClovis, kActorMcCoy) > 50
			&& !Game_Flag_Query(kFlagMcCoyRetiredReplicant)) {
				Game_Flag_Set(kFlagMcCoyIsHelpingReplicants);
				Actor_Set_Goal_Number(kActorClovis, kGoalClovisKP07Wait);
				Actor_Set_Goal_Number(kActorSadik, 414);
			} else {
				if (!Actor_Clue_Query(kActorMcCoy, kClueCrystalsCigarette)) {
					if (Actor_Query_Goal_Number(kActorSadik) < kGoalSadikGone
					&& Game_Flag_Query(kFlagSadikIsReplicant)) {
						Game_Flag_Reset(kFlagMcCoyIsHelpingReplicants);
						Actor_Set_Goal_Number(kActorSadik, 411);
					} else {
						Actor_Set_Goal_Number(kActorMaggie, kGoalMaggieKP05Wait);
						Actor_Put_In_Set(kActorClovis, kSetKP05_KP06);
						Actor_Set_At_XYZ(kActorClovis, -961.0f, 0.0f, -778.0f, 150);
						Game_Flag_Reset(kFlagMcCoyIsHelpingReplicants);
						if (Actor_Query_Goal_Number(kActorSadik) < kGoalSadikGone) {
							Actor_Put_In_Set(kActorSadik, kSetKP05_KP06);
							Actor_Set_At_XYZ(kActorSadik, -1134.0f, 0.0f, 73.45f, 398);
						}
					}
				} else {
					Game_Flag_Set(kFlagMcCoyIsHelpingReplicants);
					Actor_Set_Goal_Number(kActorClovis, kGoalClovisKP07Wait);
					Actor_Set_Goal_Number(kActorSadik, 414);
				}
			}
			Actor_Clue_Acquire(kActorMcCoy, kCluePhoneCallLucy2, true, kActorLucy);
		} 
	} else if (Game_Flag_Query(kFlagCrazylegsArrested)
	|| Actor_Query_Goal_Number(kActorCrazylegs) == kGoalCrazyLegsLeavesShowroom
	) {
#if BLADERUNNER_ORIGINAL_BUGS
		Actor_Says(kActorLucy, 630, 3); // I'll meet you there, okay? At the place where he sells the cars.
		Actor_Says_With_Pause(kActorMcCoy, 2575, 0.0f, 15); // Wait, Lucy!
		if (!Game_Flag_Query(kFlagDirectorsCut)) {
			Actor_Says(kActorLucy, 640, 3);
		}
#else
		// When CrazyLegs is gone from his shop,
		// it does not make sense for Lucy to say "At the place where he sells the cars"
		Actor_Says_With_Pause(kActorMcCoy, 2570, 0.0f, 13); // Lucy, there's a good chance--
		if (!Game_Flag_Query(kFlagDirectorsCut)) {
			Actor_Says(kActorLucy, 640, 3);
		}
		Sound_Play(kSfxSPNBEEP9, 100, 0, 0, 50); // (Lucy hangs up)
		Actor_Says(kActorMcCoy, 2575, 15); // Wait, Lucy!
#endif // BLADERUNNER_ORIGINAL_BUGS
		Actor_Clue_Acquire(kActorMcCoy, kCluePhoneCallLucy2, true, -1);
	} else {
		Actor_Says(kActorLucy, 590, 3); //06-0590.AUD	We could buy a car. From that place next to the arcade.
		Actor_Says(kActorMcCoy, 2565, 12);
		Actor_Says(kActorLucy, 600, 3); //06-0600.AUD	One of those flying cars would though. 
		Actor_Says(kActorLucy, 610, 3);
		Actor_Says(kActorLucy, 620, 3);
#if BLADERUNNER_ORIGINAL_BUGS
		Actor_Says(kActorMcCoy, 2570, 13);
#else
		// McCoy is interrupted here, so use Actor_Says_With_Pause
		Actor_Says_With_Pause(kActorMcCoy, 2570, 0.0f, 13);
#endif // BLADERUNNER_ORIGINAL_BUGS
		Actor_Says_With_Pause(kActorLucy, 630, 0.0f, 3); //06-0630.AUD	I’ll meet you there, okay? At the place where he sells the cars.
		Actor_Says_With_Pause(kActorMcCoy, 2575, 0.0f, 15);
		if (!Game_Flag_Query(kFlagDirectorsCut)) {
			Actor_Says(kActorLucy, 640, 3);
		}
#if BLADERUNNER_ORIGINAL_BUGS
#else
		Sound_Play(kSfxSPNBEEP9, 100, 0, 0, 50);
#endif // BLADERUNNER_ORIGINAL_BUGS
		Actor_Clue_Acquire(kActorMcCoy, kCluePhoneCallLucy1, true, -1);
	}
#if BLADERUNNER_ORIGINAL_BUGS
	Sound_Play(kSfxSPNBEEP9, 100, 0, 0, 50);
#endif // BLADERUNNER_ORIGINAL_BUGS
}

void SceneScriptMA04::phoneCallWithSteele() {
	Actor_Says(kActorSteele, 680, 3);
	if (_vm->_cutContent) {
		if (Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) < 58) {
			Actor_Says(kActorMcCoy, 2630, 17); //00-2630.AUD	My dog is still missing.
			Actor_Says(kActorSteele, 690, 3);
			Actor_Says(kActorMcCoy, 2635, 18);
		} else {
			Actor_Says(kActorMcCoy, 8514, 14); //00-8514.AUD	Got anything new to tell me?
		}
	} else {
		Actor_Says(kActorMcCoy, 2630, 17); //00-2630.AUD	My dog is still missing.
		Actor_Says(kActorSteele, 690, 3);
		Actor_Says(kActorMcCoy, 2635, 18);
	}
	Actor_Says(kActorSteele, 700, 3); //01-0700.AUD	I got a line on where the skin-jobs are holing up.
	Actor_Says(kActorMcCoy, 2640, 14); //00-2640.AUD	Not the Yukon?
	Actor_Says(kActorSteele, 710, 3); //01-0710.AUD	Yesterdays news. Remember Gaff was talking about that moonbus massacre?
	Actor_Says(kActorSteele, 720, 3); //01-0720.AUD	I found out where they crash-landed it. And five will get you ten they’ll be licking their wounds there.
	if (_vm->_cutContent) {
		if (!Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
			Actor_Says(kActorMcCoy, 2645, 13); //00-2645.AUD	Excellent. Where do we go?
			if (Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) < 60) {
				Actor_Says(kActorSteele, 740, 3); //01-0740.AUD	We? How about moi? Here’s a hint, Slim.
			}
		}
	} else {
		Actor_Says(kActorMcCoy, 2645, 13); //00-2645.AUD	Excellent. Where do we go?
		Actor_Says(kActorSteele, 740, 3); //01-0740.AUD	We? How about moi? Here’s a hint, Slim.
	}
	Actor_Says(kActorSteele, 750, 3); //01-0750.AUD	It’s way the shit out there in the Kipple. Way, way out.
	Actor_Says(kActorMcCoy, 2650, 12); //
	Actor_Says(kActorSteele, 760, 3); //01-0760.AUD	They’ve been accessing through an old sewer tunnel.
	// Restored some of the dialogue for the phone conversation with Crystal.
	if (_vm->_cutContent) {
		Actor_Says(kActorSteele, 770, 3); //01-0770.AUD	That son of a bitch, Clovis, was climbing in and out of a manhole right next to the police station and nobody ever noticed.
		if (Game_Flag_Query(kFlagGuzzaArrested)
		|| !Game_Flag_Query(kFlagGuzzaSaved)) {	
			Actor_Says(kActorMcCoy, 2655, 16); //00-2655.AUD	Figures. With incompetents like Guzza at the helm.	
			// Made it so Crystal only says Guzza is going to be fed to the barracudas if McCoy saved Guzza and arrested him.
			if (Game_Flag_Query(kFlagGuzzaArrested)) {
				Actor_Says(kActorSteele, 790, 3); //01-0790.AUD	I think we can forget about Guzza. That guy’s gonna be fed to the barracudas.
				if (Player_Query_Agenda() == kPlayerAgendaSurly 
				|| Player_Query_Agenda() == kPlayerAgendaErratic) {
					Actor_Says(kActorMcCoy, 2660, 18); //00-2660.AUD	That breaks my heart.
					Actor_Says(kActorSteele, 800, 3); //01-0800.AUD	I knew it would.
				}
			}
		}
	} 
	Actor_Says(kActorMcCoy, 2665, 13); //00-2665.AUD	We’re gonna air out the Reps together or what?
	if (_vm->_cutContent) {
		if (Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) > 59) {
			Actor_Says(kActorSteele, 810, 3); //01-0810.AUD	Mm. I’m liking your style more and more.
			Actor_Says(kActorMcCoy, 1885, 13); //00-1885.AUD	I’ll take that as a yes.
			Delay(1000);
			Actor_Says(kActorMcCoy, 3170, 13); //00-3170.AUD	I’m there.
		} else {
			Actor_Says(kActorSteele, 820, 3); //01-0820.AUD	But first come, first serve. I share my bonuses with nobody. See you on the other side, Slim.
		}
	} else {
		Actor_Says(kActorSteele, 810, 3); //01-0810.AUD	Mm. I’m liking your style more and more.
		Actor_Says(kActorSteele, 820, 3); //01-0820.AUD	But first come, first serve. I share my bonuses with nobody. See you on the other side, Slim.
	}
	Sound_Play(kSfxSPNBEEP9, 100, 0, 0, 50);
	if (_vm->_cutContent) {
		if (Actor_Query_Friendliness_To_Other(kActorClovis, kActorMcCoy) > 50
		&& !Game_Flag_Query(kFlagMcCoyRetiredReplicant)) {
			Game_Flag_Set(kFlagMcCoyIsHelpingReplicants);
			Actor_Set_Goal_Number(kActorClovis, kGoalClovisKP07Wait);
			Actor_Set_Goal_Number(kActorSadik, 414);
		} else {
			if (!Actor_Clue_Query(kActorMcCoy, kClueCrystalsCigarette)) {
				if (Actor_Query_Goal_Number(kActorSadik) < kGoalSadikGone
				&& Game_Flag_Query(kFlagSadikIsReplicant)) {
					Game_Flag_Reset(kFlagMcCoyIsHelpingReplicants);
					Actor_Set_Goal_Number(kActorSadik, 411);
				} else {
					Actor_Set_Goal_Number(kActorMaggie, kGoalMaggieKP05Wait);
					Actor_Put_In_Set(kActorClovis, kSetKP05_KP06);
					Actor_Set_At_XYZ(kActorClovis, -961.0f, 0.0f, -778.0f, 150);
					Game_Flag_Reset(kFlagMcCoyIsHelpingReplicants);
					if (Actor_Query_Goal_Number(kActorSadik) < kGoalSadikGone) {
						Actor_Put_In_Set(kActorSadik, kSetKP05_KP06);
						Actor_Set_At_XYZ(kActorSadik, -1134.0f, 0.0f, 73.45f, 398);
					}
				}
			} else {
				Game_Flag_Set(kFlagMcCoyIsHelpingReplicants);
				Actor_Set_Goal_Number(kActorClovis, kGoalClovisKP07Wait);
				Actor_Set_Goal_Number(kActorSadik, 414);
			}
		}
		Actor_Clue_Acquire(kActorMcCoy, kCluePhoneCallCrystal, true, kActorSteele);
	} else {
		Actor_Clue_Acquire(kActorMcCoy, kCluePhoneCallCrystal, true, -1);
	}
}

void SceneScriptMA04::phoneCallWithClovis() {
	Actor_Says(kActorClovis, 330, 3); //05-0330.AUD	I see you survived.
	//Altered code so McCoy only gets angry at Clovis for trying to kill him if Clovis actually tried to kill McCoy in the sewers. If that didn't happen we skip straight to the part
	//Where Clovis apologises to McCoy for the situation with Guzza.
	// Altered code so Clovis and McCoy will be angry with each other if McCoy retired Dektora Lucy or Zuben or he didn't kill Guzza.
	// If he didn't do any of that Clovis is nicer to him.
	if (_vm->_cutContent) {
		if (Actor_Query_Friendliness_To_Other(kActorClovis, kActorMcCoy) < 51
		|| Game_Flag_Query(kFlagMcCoyRetiredReplicant)) {
			Actor_Says(kActorMcCoy, 2580, 14); //00-2580.AUD	No thanks to you.
			Actor_Says(kActorClovis, 340, 3); //05-0340.AUD	Don’t you think you’d already be dead, if that’s what I so desired?
			Actor_Says(kActorMcCoy, 2585, 19); //00-2585.AUD	Talking like a god, Clovis. Isn’t that a little over the top? Even for you?
			Actor_Says(kActorClovis, 350, 3); //05-0350.AUD	Prometheus was chained to a rock and vultures pecked at his liver.
			Actor_Says(kActorClovis, 360, 3); //05-0360.AUD	I haven’t quite had to suffer such ordeals literally speaking of course.
			if (Player_Query_Agenda() == kPlayerAgendaSurly 
			|| Player_Query_Agenda() == kPlayerAgendaErratic) {
				Actor_Says(kActorMcCoy, 2590, 18); //00-2590.AUD	Well, there’s still time.
			} else {
				Delay(2000);
			}
			Actor_Says_With_Pause(kActorClovis, 420, 1.5f, 3); //05-0420.AUD	Is something the matter, brother?
		} else {
			Actor_Says(kActorMcCoy, 8305, 18); //00-8305.AUD	I think so.
			Actor_Says(kActorClovis, 370, 3); //05-0370.AUD	(laughs) I’m calling to apologize, brother. I should have never recruited Guzza against you. I just had to make sure that you weren’t going to betray us.
			Actor_Says(kActorMcCoy, 2595, 15); //00-2595.AUD	Guzza probably thought that he recruited you.
			Actor_Says(kActorClovis, 390, 3); //05-0390.AUD	To be honest we had a sort of eh… business relationship
			Actor_Says(kActorClovis, 400, 3); //05-0400.AUD	where our different interests converge.
			Actor_Says(kActorClovis, 410, 3); //05-0410.AUD	But he was never to be trusted. Unlike you.
			if (Player_Query_Agenda() != kPlayerAgendaSurly 
			&& Player_Query_Agenda() != kPlayerAgendaErratic) {
				Actor_Says(kActorMcCoy, 2600, 15); //00-2600.AUD	I appreciate that.
			} else {
				Delay(2000);
			}
			Actor_Says_With_Pause(kActorClovis, 420, 1.5f, 3); //05-0420.AUD	Is something the matter, brother?
		}
	} else {
		Actor_Says(kActorMcCoy, 2580, 14); 
		Actor_Says(kActorClovis, 340, 3);
		Actor_Says(kActorMcCoy, 2585, 19);
		Actor_Says(kActorClovis, 350, 3);
		Actor_Says(kActorClovis, 360, 3);
		Actor_Says(kActorMcCoy, 2590, 18);
		Actor_Says(kActorClovis, 370, 3); //05-0370.AUD	(laughs) I’m calling to apologize, brother. I should have never recruited Guzza against you. I just had to make sure that you weren’t going to betray us.
		Actor_Says(kActorMcCoy, 2595, 15); //00-2595.AUD	Guzza probably thought that he recruited you.
		Actor_Says(kActorClovis, 390, 3); 
		Actor_Says(kActorClovis, 400, 3); 
		Actor_Says(kActorClovis, 410, 3); //05-0410.AUD	But he was never to be trusted. Unlike you.
		Actor_Says(kActorMcCoy, 2600, 15); //00-2600.AUD	I appreciate that.
		Actor_Says_With_Pause(kActorClovis, 420, 1.5f, 3); //05-0420.AUD	Is something the matter, brother?
	}
	if (_vm->_cutContent) {
		if (Actor_Clue_Query(kActorMcCoy, kClueCrystalsCigarette)) { 
			Actor_Says(kActorMcCoy, 2605, 17); //00-2605.AUD	My dog’s been murdered.
			Actor_Says(kActorClovis, 430, 3); //05-0430.AUD	And does that not wet your thirst for vengeance?
			Actor_Says(kActorClovis, 440, 3); //05-0440.AUD	Come back home to us. We’ll demand justice and receive it!
		}
	} else {
		Actor_Says(kActorMcCoy, 2605, 17); //00-2605.AUD	My dog’s been murdered.
		Actor_Says(kActorClovis, 430, 3); //05-0430.AUD	And does that not wet your thirst for vengeance?
		Actor_Says(kActorClovis, 440, 3); //05-0440.AUD	Come back home to us. We’ll demand justice and receive it!
	}
	Actor_Says(kActorMcCoy, 2610, 3); //00-2610.AUD	How do I know who I really am?
	Actor_Says(kActorClovis, 450, 3); //05-0450.AUD	Guzza must have programmed you as an experiment.
	Actor_Says(kActorClovis, 460, 3); //05-0460.AUD	To see if you could really act as one of them.
	Actor_Says(kActorClovis, 470, 3); //05-0470.AUD	He wiped out all your memories of our time together.
	Actor_Says(kActorClovis, 480, 3); //05-0480.AUD	As soldiers during the Phobos wars.
	Actor_Says(kActorClovis, 490, 3); //05-0490.AUD	The battle of the Gemini. Firefights on the top of the Olympus Mountains!
	Actor_Says(kActorMcCoy, 2615, 17); //00-2615.AUD	I don’t remember.
	//Restored some dialogue for the phone call.
	if (_vm->_cutContent) {
		Actor_Says(kActorClovis, 1230, 3); //05-1230.AUD	That’s what I remember.
		Actor_Says(kActorMcCoy, 8565, 13); //00-8565.AUD	Really?
	}
	Actor_Says(kActorClovis, 500, 3); //05-0500.AUD	But if you dig real deep and feel, you’ll know what’s real.
	if (_vm->_cutContent) {
		Actor_Says(kActorMcCoy, 2620, 15); //00-2620.AUD	Okay. What do we do next?
		Actor_Says(kActorClovis, 510, 3); //05-0510.AUD	In the sewers near the police station is a tunnel that leads out to the Kipple.
		Actor_Says(kActorClovis, 520, 3); //05-0520.AUD	Do you know it?
		Actor_Says(kActorMcCoy, 2625, 14); //00-2625.AUD	I can find it.
		if (Actor_Query_Friendliness_To_Other(kActorClovis, kActorMcCoy) > 50
		&& !Game_Flag_Query(kFlagMcCoyRetiredReplicant)) {
			Actor_Says(kActorClovis, 530, 3); //05-0530.AUD	It’s a passage to freedom, McCoy. To your destiny.
			Actor_Says(kActorClovis, 540, 3); //05-0540.AUD	An underground railroad to carry you from bondage. We’ll be waiting.
		}	
		Actor_Clue_Acquire(kActorMcCoy, kCluePhoneCallClovis, true, kActorClovis);
		if (Actor_Query_Friendliness_To_Other(kActorClovis, kActorMcCoy) > 50
		&& !Game_Flag_Query(kFlagMcCoyRetiredReplicant)) {
			Game_Flag_Set(kFlagMcCoyIsHelpingReplicants);
			Actor_Set_Goal_Number(kActorClovis, kGoalClovisKP07Wait);
			Actor_Set_Goal_Number(kActorSadik, 414);
		} else {
			if (!Actor_Clue_Query(kActorMcCoy, kClueCrystalsCigarette)) {
				if (Actor_Query_Goal_Number(kActorSadik) < kGoalSadikGone
				&& Game_Flag_Query(kFlagSadikIsReplicant)) {
					Game_Flag_Reset(kFlagMcCoyIsHelpingReplicants);
					Actor_Set_Goal_Number(kActorSadik, 411);
				} else {
					Actor_Set_Goal_Number(kActorMaggie, kGoalMaggieKP05Wait);
					Actor_Put_In_Set(kActorClovis, kSetKP05_KP06);
					Actor_Set_At_XYZ(kActorClovis, -961.0f, 0.0f, -778.0f, 150);
					Game_Flag_Reset(kFlagMcCoyIsHelpingReplicants);
					if (Actor_Query_Goal_Number(kActorSadik) < kGoalSadikGone) {
						Actor_Put_In_Set(kActorSadik, kSetKP05_KP06);
						Actor_Set_At_XYZ(kActorSadik, -1134.0f, 0.0f, 73.45f, 398);
					}
				}
			} else {
				Game_Flag_Set(kFlagMcCoyIsHelpingReplicants);
				Actor_Set_Goal_Number(kActorClovis, kGoalClovisKP07Wait);
				Actor_Set_Goal_Number(kActorSadik, 414);
			}
		}
	} else {
		Actor_Says(kActorClovis, 530, 3); //05-0530.AUD	It’s a passage to freedom, McCoy. To your destiny.
		Actor_Says(kActorClovis, 540, 3); //05-0540.AUD	An underground railroad to carry you from bondage. We’ll be waiting.
	}	
	Sound_Play(kSfxSPNBEEP9, 100, 0, 0, 50);
}
void SceneScriptMA04::turnOnTV() {
	Overlay_Play("MA04OVR2", 0, true, false, 0);
	switch (Global_Variable_Query(kVariableNextTvNews)) {
	case 0:
		ADQ_Add(kActorNewscaster, 0, kAnimationModeTalk);
		ADQ_Add(kActorNewscaster, 10, kAnimationModeTalk);
		ADQ_Add(kActorNewscaster, 20, kAnimationModeTalk);
		ADQ_Add(kActorNewscaster, 30, kAnimationModeTalk);
		ADQ_Add(kActorTyrell, 430, kAnimationModeTalk);
		ADQ_Add(kActorTyrell, 440, kAnimationModeTalk);
		ADQ_Add(kActorTyrell, 450, kAnimationModeTalk);
		ADQ_Add(kActorTyrell, 460, kAnimationModeTalk);
		break;
	case 1:
		ADQ_Add(kActorNewscaster, 40, kAnimationModeTalk);
		ADQ_Add(kActorNewscaster, 50, kAnimationModeTalk);
		ADQ_Add(kActorNewscaster, 60, kAnimationModeTalk);
		ADQ_Add(kActorNewscaster, 70, kAnimationModeTalk);
		ADQ_Add(kActorNewscaster, 80, kAnimationModeTalk);
		break;
	case 2:
		if (_vm->_cutContent) {
			Game_Flag_Set(kFlagZhoraNewsReport);
		}
		if (Actor_Query_Friendliness_To_Other(kActorClovis, kActorMcCoy) <= Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy)) {
			ADQ_Add(kActorNewscaster, 90, kAnimationModeTalk);
			ADQ_Add(kActorNewscaster, 100, kAnimationModeTalk);
			ADQ_Add(kActorNewscaster, 110, kAnimationModeTalk);
			ADQ_Add(kActorGuzza, 1540, kAnimationModeTalk);
			ADQ_Add(kActorGuzza, 1550, kAnimationModeTalk);
			ADQ_Add(kActorGuzza, 1560, kAnimationModeTalk);
		} else {
			ADQ_Add(kActorNewscaster, 120, kAnimationModeTalk);
			ADQ_Add(kActorNewscaster, 130, kAnimationModeTalk);
			ADQ_Add(kActorNewscaster, 140, kAnimationModeTalk);
			ADQ_Add(kActorNewscaster, 150, kAnimationModeTalk);
			ADQ_Add(kActorGuzza, 1570, kAnimationModeTalk);
			ADQ_Add(kActorGuzza, 1580, kAnimationModeTalk);
			ADQ_Add(kActorGuzza, 1590, kAnimationModeTalk);
		}
		break;
	case 3:
		ADQ_Add(kActorNewscaster, 170, kAnimationModeTalk);
		ADQ_Add(kActorNewscaster, 180, kAnimationModeTalk);
		ADQ_Add(kActorNewscaster, 190, kAnimationModeTalk);
		ADQ_Add(kActorNewscaster, 200, kAnimationModeTalk);
		ADQ_Add(kActorNewscaster, 210, kAnimationModeTalk);
		ADQ_Add(kActorNewscaster, 220, kAnimationModeTalk);
		ADQ_Add(kActorGovernorKolvig, 80, kAnimationModeTalk);
		ADQ_Add(kActorGovernorKolvig, 90, kAnimationModeTalk);
		ADQ_Add(kActorGovernorKolvig, 100, kAnimationModeTalk);
		ADQ_Add(kActorGovernorKolvig, 110, kAnimationModeTalk);
		ADQ_Add(kActorGovernorKolvig, 120, kAnimationModeTalk);
		ADQ_Add(kActorGovernorKolvig, 130, kAnimationModeTalk);
		break;
	case 4:
		ADQ_Add(kActorNewscaster, 230, kAnimationModeTalk);
		ADQ_Add(kActorNewscaster, 240, kAnimationModeTalk);
		break;
	}
}

void SceneScriptMA04::sleep() {
	if (!Loop_Actor_Walk_To_Scene_Object(kActorMcCoy, "BED-SHEETS", 12, true, false)) {
		Actor_Says(kActorMcCoy, 8530, 12);
		Music_Stop(4u);
		if (isPhoneMessageWaiting() || isPhoneRinging()) {
			Overlay_Remove("MA04OVER");
		}
		Player_Loses_Control();
		Game_Flag_Set(kFlagMA04McCoySleeping);
		if ((Game_Flag_Query(kFlagZubenRetired) || Game_Flag_Query(kFlagZubenSpared)) && Global_Variable_Query(kVariableChapter) == 1) {
			if (Actor_Query_Goal_Number(kActorZuben) == kGoalZubenGone) {
				Actor_Put_In_Set(kActorZuben, kSetFreeSlotA);
				Actor_Set_At_Waypoint(kActorZuben, 33, 0);
			}
			Game_Flag_Set(kFlagChapter2Intro);
			Global_Variable_Set(kVariableChapter, 2);
			Chapter_Enter(2, kSetMA02_MA04, kSceneMA04);
#if BLADERUNNER_ORIGINAL_BUGS
			if (Query_Difficulty_Level() != kGameDifficultyEasy) {
				if (!Game_Flag_Query(kFlagZubenBountyPaid)) {
					Global_Variable_Increment(kVariableChinyen, 200);
				}
			}
#else // ensure valid kFlagZubenBountyPaid flag state
			// NOTE If not for the "Report In" to Guzza, it would be simpler to have McCoy get the money as soon as he retires Zuben
			//		so that would be in a single place in the code
			if (!Game_Flag_Query(kFlagZubenBountyPaid) && Game_Flag_Query(kFlagZubenRetired)) { // get retirement money at end of day 1 only if Zuben was retired.
				if (Query_Difficulty_Level() != kGameDifficultyEasy) {
					Global_Variable_Increment(kVariableChinyen, 200);
				}
				Game_Flag_Set(kFlagZubenBountyPaid); // not a proper bug, but was missing from original code, so the flag would remain in non-consistent state in this case
			}
			if (!Game_Flag_Query(kFlagRunciterBountyPaid) && Actor_Clue_Query(kActorMcCoy, kClueMcCoyKilledRunciter1)) { // get retirement money at end of day 1 only if Zuben was retired.
				if (Query_Difficulty_Level() != kGameDifficultyEasy) {
					Global_Variable_Increment(kVariableChinyen, 200);
				}
				Game_Flag_Set(kFlagRunciterBountyPaid); // not a proper bug, but was missing from original code, so the flag would remain in non-consistent state in this case
			}
#endif // BLADERUNNER_ORIGINAL_BUGS
		} else {
			Set_Enter(kSetMA02_MA04, kSceneMA04);
		}
		Scene_Loop_Start_Special(kSceneLoopModeChangeSet, kMA04LoopSleep, false);
	}
}

} // End of namespace BladeRunner
