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

enum kAR01Loops {
	kAR01LoopFromAR02WithSpinner = 0,
	kAR01LoopInshot              = 1,
	kAR01LoopMainLoop            = 2,
	kAR01LoopDoorAnim            = 4,
	kAR01LoopOutshot             = 5,
	kAR01LoopFromAR02NoSpinner   = 6,
	kAR01LoopMainLoopNoSpinner   = 7
};

enum kAR01Exits {
	kAR01ExitHC01    = 0,
	kAR01ExitAR02    = 1,
	kAR01ExitSpinner = 2
};

void SceneScriptAR01::InitializeScene() {
	if (_vm->_cutContent) {
		Music_Play(kMusicArabLoop, 25, 0, 2, -1, kMusicLoopRepeatRandomStart, 2);
	} else {
		Music_Play(kMusicArabLoop, 25, 0, 2, -1, kMusicLoopRepeat, 2);
	}

	if (Game_Flag_Query(kFlagHC01toAR01)) {
		Setup_Scene_Information(-477.0f, 0.0f, -149.0f, 333);
	} else if (Game_Flag_Query(kFlagAR02toAR01)) {
		Setup_Scene_Information(-182.0f, 0.0f, -551.0f, 518);
	} else {
		Setup_Scene_Information(-152.0f, 0.0f, 332.0f, 545);
	}
	Scene_Exit_Add_2D_Exit(kAR01ExitHC01, 134, 165, 177, 290, 3);
	Scene_Exit_Add_2D_Exit(kAR01ExitAR02, 319,   0, 639, 207, 0);
	if (Game_Flag_Query(kFlagSpinnerAtAR01)) {
		Scene_Exit_Add_2D_Exit(kAR01ExitSpinner, 0, 404, 99, 479, 2);
	}
	Ambient_Sounds_Add_Looping_Sound(kSfxCTRAIN1, 50,   1, 1);
	Ambient_Sounds_Add_Looping_Sound(kSfxRCAMBR1, 60, 100, 1);
	Ambient_Sounds_Add_Looping_Sound(kSfxHCLOOP1, 50,   1, 1);
	Ambient_Sounds_Add_Sound(kSfx67_0480R, 5,  70, 12,  12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0540R, 5,  70, 12,  12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0560R, 5,  70, 12,  12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0870R, 5,  70, 12,  12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0900R, 5,  70, 12,  12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0940R, 5,  70, 12,  12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_1070R, 5,  70, 12,  12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_1080R, 5,  70, 12,  12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_1160R, 5,  70, 12,  12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxHCANM8,   3,  30, 11,  11,   50, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxHCANM2,   3,  30, 11,  11,   50, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxHCANM3,   3,  30, 11,  11,   50, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxHCANM4,   3,  30, 11,  11,   50, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxHCANM5,   3,  30, 11,  11,   50, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxHCANM6,   3,  30, 11,  11,   50, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxHCANM7,   3,  30, 11,  11,   50, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxHCANM1,   3,  30, 11,  11,   50, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Speech_Sound(kActorBlimpGuy,  0, 10u, 260u, 17, 24, -100, 100, -101, -101, 1, 1);
	Ambient_Sounds_Add_Speech_Sound(kActorBlimpGuy, 20, 10u, 260u, 17, 24, -100, 100, -101, -101, 1, 1);
	Ambient_Sounds_Add_Speech_Sound(kActorBlimpGuy, 40, 10u, 260u, 17, 24, -100, 100, -101, -101, 1, 1);
	Ambient_Sounds_Add_Speech_Sound(kActorBlimpGuy, 50, 10u, 260u, 17, 24, -100, 100, -101, -101, 1, 1);
	Ambient_Sounds_Add_Sound(kSfxSPIN2B,  10, 180, 16,  25,    0,   0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSPIN3A,  10, 180, 16,  25,    0,   0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxTHNDER2, 10, 180, 50, 100,    0,   0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxTHNDER3, 10, 180, 50, 100,    0,   0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxTHNDER4, 10, 180, 50, 100,    0,   0, -101, -101, 0, 0);
	if ( Game_Flag_Query(kFlagSpinnerAtAR01)
	 && !Game_Flag_Query(kFlagAR02toAR01)
	 && !Game_Flag_Query(kFlagHC01toAR01)
	) {
		Actor_Set_Invisible(kActorMcCoy, true);
		Game_Flag_Set(kFlagArrivedFromSpinner2);
		Scene_Loop_Start_Special(kSceneLoopModeLoseControl, kAR01LoopInshot, false);
		Scene_Loop_Set_Default(kAR01LoopMainLoop);
	} else if (Game_Flag_Query(kFlagSpinnerAtAR01)
	        && Game_Flag_Query(kFlagAR02toAR01)
	) {
		Scene_Loop_Start_Special(kSceneLoopModeLoseControl, kAR01LoopFromAR02WithSpinner, false);
		Scene_Loop_Set_Default(kAR01LoopMainLoop);
		Game_Flag_Reset(kFlagAR02toAR01);
	} else if (!Game_Flag_Query(kFlagSpinnerAtAR01)
	        &&  Game_Flag_Query(kFlagAR02toAR01)
	) {
		Scene_Loop_Start_Special(kSceneLoopModeLoseControl, kAR01LoopFromAR02NoSpinner, false);
		Scene_Loop_Set_Default(kAR01LoopMainLoopNoSpinner);
		Game_Flag_Reset(kFlagAR02toAR01);
	} else if (Game_Flag_Query(kFlagSpinnerAtAR01)
	        && Game_Flag_Query(kFlagHC01toAR01)
	) {
		Scene_Loop_Set_Default(kAR01LoopMainLoop);
	} else if (!Game_Flag_Query(kFlagSpinnerAtAR01)
	        &&  Game_Flag_Query(kFlagHC01toAR01)
	) {
		Scene_Loop_Set_Default(kAR01LoopMainLoopNoSpinner);
	} else { // bug? branch content is equal to previous branch
		Scene_Loop_Set_Default(kAR01LoopMainLoopNoSpinner);
	}
}

void SceneScriptAR01::SceneLoaded() {
	Obstacle_Object("DF_BOOTH", true);
	Unobstacle_Object("SPINNER BODY", true);

#if BLADERUNNER_ORIGINAL_BUGS
#else
	if (Global_Variable_Query(kVariableChapter) < 4
	    && !Game_Flag_Query(kFlagAR02DektoraBoughtScorpions)
	    && !Game_Flag_Query(kFlagScorpionsInAR02)
	) {
		// the kFlagScorpionsInAR02 flag helps keep track of the item in AR
		// and make it not blink in and out of existence
		// in the transition from AR01 to AR02
		Game_Flag_Set(kFlagScorpionsInAR02);
		Item_Add_To_World(kItemScorpions, kModelAnimationCageOfScorpions, kSetAR01_AR02, -442.84f, 36.77f, -1144.51f, 360, 36, 36, false, true, false, true);
	} else if (Global_Variable_Query(kVariableChapter) >= 4
	           && !Game_Flag_Query(kFlagAR02DektoraBoughtScorpions)
	           && Game_Flag_Query(kFlagScorpionsInAR02)
	) {
		Game_Flag_Reset(kFlagScorpionsInAR02);
		Item_Remove_From_World(kItemScorpions);
	}
#endif // BLADERUNNER_ORIGINAL_BUGS
}

bool SceneScriptAR01::MouseClick(int x, int y) {
	return false;
}

bool SceneScriptAR01::ClickedOn3DObject(const char *objectName, bool a2) {
	return false;
}

bool SceneScriptAR01::ClickedOnActor(int actorId) {
	if (actorId == kActorInsectDealer
	 || actorId == kActorHasan
	) {
		Actor_Face_Actor(kActorMcCoy, actorId, true);
		Actor_Says(kActorMcCoy, 8910, 14);
		return true;
	}

	if (actorId == kActorFishDealer) {
		Actor_Set_Goal_Number(kActorFishDealer, 2);
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -120.73f, 0.0f, 219.17f, 12, true, false, false)) {
			Actor_Face_Actor(kActorMcCoy, kActorFishDealer, true);
			Actor_Face_Actor(kActorFishDealer, kActorMcCoy, true);
			if (_vm->_cutContent) { 
				if (!Actor_Clue_Query(kActorMcCoy, kClueFishLadyInterview)
				&& !Game_Flag_Query(kFlagWrongInvestigation)
				&& !Game_Flag_Query(kFlagFishLadyTalkScale)
				&& Global_Variable_Query(kVariableChapter) < 4
				&& (Actor_Clue_Query(kActorMcCoy, kClueStrangeScale1)
				|| Actor_Clue_Query(kActorMcCoy, kClueStrangeScale2))) {	
					Actor_Says(kActorMcCoy, 40, 23);
					if (Actor_Query_Friendliness_To_Other(kActorFishDealer, kActorMcCoy) > 49) {		
						Actor_Says(kActorFishDealer, 120, 14);
						Actor_Says(kActorMcCoy, 45, 17); //00-0045.AUD	What other one?	
						// The fish lady will say this extra line if she told you about the Peruvian woman before.
						if  (Game_Flag_Query(kFlagAR01FishDealerTalkInsects)) {
							Actor_Says(kActorFishDealer, 210, 14); //29-0210.AUD	What I said before. That yesterdays news. Here real fact of it.
						}
						Actor_Says(kActorFishDealer, 130, 14); //29-0130.AUD	Other police show me scale from same snake.
						Actor_Says(kActorFishDealer, 140, 14);
						if (!Game_Flag_Query(kFlagAR01FishDealerMcCoyIsPolice)) {
							Actor_Says(kActorMcCoy, 50, 13);
							Actor_Says(kActorFishDealer, 150, 14);
						}
						Actor_Clue_Acquire(kActorMcCoy, kClueFishLadyInterview, true, kActorFishDealer);
						Game_Flag_Set(kFlagFishLadyTalkScale);
						Actor_Set_Goal_Number(kActorFishDealer, 1);
					} else {
						Actor_Says(kActorFishDealer, 180, 14); //29-0180.AUD	I can't stand all day gabbing away. My fish require attention.
						Game_Flag_Set(kFlagFishLadyTalkScale);
						Actor_Set_Goal_Number(kActorFishDealer, 1);
					}
				} else if (!Game_Flag_Query(kFlagAR01FishDealerTalk) 
				&& !Game_Flag_Query(kFlagAR02InsectDealerInterviewed)
				&& Global_Variable_Query(kVariableChapter) < 4) {		
					Actor_Says(kActorMcCoy, 0, 18);
					Actor_Says(kActorFishDealer, 0, 14);
					Actor_Says(kActorFishDealer, 10, 14); //29-0010.AUD	They're no good companion. But fish, fish are good.
					Actor_Says(kActorFishDealer, 20, 14); //29-0020.AUD	I have every kind of fish for you.
					Actor_Says(kActorFishDealer, 30, 14); //29-0030.AUD	Blowfish, Dorado, miniature Sailfish. Very friendly.
					if (Player_Query_Agenda() == kPlayerAgendaPolite) {
						Actor_Says(kActorMcCoy, 5, 17); //00-0005.AUD	No thanks. I got a dog at home.
						Actor_Says(kActorFishDealer, 40, 14); //29-0040.AUD	Fish just as good as dog.
						Actor_Says(kActorMcCoy, 10, 13); //00-0010.AUD	No, my dog is real.
						Actor_Says(kActorFishDealer, 50, 14); //29-0050.AUD	Real?! Oh, you must make lots of money.
						Delay(1000);
						Actor_Says(kActorFishDealer, 230, 14); // 29-0230.AUD	You buy fish? Highest quality.
						Delay(1000);
					} else {
						Actor_Says(kActorMcCoy, 7815, 13); //00-7815.AUD	No.
						Delay(1000);
						Actor_Says(kActorFishDealer, 230, 14); // 29-0230.AUD	You buy fish? Highest quality.
						Delay(1000);
					}
					// If McCoy is surly or erratic their friendliness will lower and this will effect the coversation later on.
					// It will also result in the fish lady not helping when trying to find the insect dealer and whne you ask her about the strange scale.
					if (Player_Query_Agenda() == kPlayerAgendaSurly 
					|| Player_Query_Agenda() == kPlayerAgendaErratic) {
						Actor_Says(kActorMcCoy, 6985, 16); //00-6985.AUD	Got the straight scoop for me or what?
						Delay(1000);
						Actor_Modify_Friendliness_To_Other(kActorFishDealer, kActorMcCoy, -2);
						Actor_Says(kActorFishDealer, 180, 14); //29-0180.AUD	I can't stand all day gabbing away. My fish require attention.
						Game_Flag_Set(kFlagAR01FishDealerTalk);
						Actor_Set_Goal_Number(kActorFishDealer, 1);
					} else {
						Actor_Says(kActorMcCoy, 15, 17); //00-0015.AUD	Let's get back to insects. Official LPD business.
						Game_Flag_Set(kFlagAR01FishDealerMcCoyIsPolice);
						Actor_Says(kActorFishDealer, 200, 14); //29-0200.AUD	Oh, all right. Where my head today?
						Actor_Says(kActorMcCoy, 7985, 17); //00-7985.AUD	It's okay.
						Actor_Says(kActorFishDealer, 60, 14); //29-0060.AUD	Ah! Down that end of Animal Row. You see big green sign?
						Actor_Says(kActorFishDealer, 70, 14);
						Game_Flag_Set(kFlagAR01FishDealerTalk);
						Game_Flag_Set(kFlagAR01FishDealerTalkInsects);					
						if (Actor_Query_Friendliness_To_Other(kActorInsectDealer, kActorMcCoy) < 50) {
							Actor_Says(kActorMcCoy, 8640, 14); // 00-8640.AUD	That's useless.
							Actor_Says(kActorFishDealer, 190, 14); // Ah! You think you get better info somewhere else? You welcome to try.
							Actor_Set_Goal_Number(kActorFishDealer, 1);
						} else {
							if (Player_Query_Agenda() == kPlayerAgendaPolite) {
								Actor_Says(kActorFishDealer, 80, 14);
								Actor_Says(kActorFishDealer, 90, 14);
								Actor_Says(kActorMcCoy, 25, 13);
								Actor_Modify_Friendliness_To_Other(kActorFishDealer, kActorMcCoy, 2);
							}
						}
						Actor_Says(kActorMcCoy, 5150, 14); //00-5150.AUD	One more thing.
						Actor_Says(kActorMcCoy, 30, 17);	//00-0030.AUD	Anything unusual happening down here?
						Actor_Says(kActorFishDealer, 230, 14); // 29-0230.AUD	You buy fish? Highest quality.
						Delay(2000);
						Loop_Actor_Walk_To_XYZ(kActorMcCoy, -221.49f, 0.62f, 86.42f, 48, false, false, true);
						Actor_Face_Actor(kActorFishDealer, kActorMcCoy, true);
						Actor_Says(kActorFishDealer, 230, 14); // 29-0230.AUD	You buy fish? Highest quality.
						Loop_Actor_Walk_To_XYZ(kActorMcCoy, -182.0, 0.0, -551.0, 0, true, false, false);
						Game_Flag_Set(kFlagAR01toAR02);
						Async_Actor_Walk_To_XYZ(kActorMcCoy, -222.0, 0.0, -690.0, 0, false);
						Set_Enter(kSetAR01_AR02, kSceneAR02);
					}
				} else if (!Game_Flag_Query(kFlagFishLadyTalkFinsished)) {	
					if (!Game_Flag_Query(kFlagFishDealerBuyFishTalk)) {
						if (Global_Variable_Query(kVariableChapter) < 3) {
							Actor_Says(kActorMcCoy, 8514, 11); // Got anything new to tell me?
							if (Actor_Query_Friendliness_To_Other(kActorFishDealer, kActorMcCoy) > 49) {
								Actor_Says(kActorFishDealer, 170, 14); // Afraid not. But been busy today. Maybe you ask me later.
								Actor_Set_Goal_Number(kActorFishDealer, 1);
							} else {
								Actor_Says(kActorFishDealer, 220, 14); //29-0220.AUD	I haven't heard much. Row been very quiet.
								Actor_Set_Goal_Number(kActorFishDealer, 1);
							}
						} else {
							Actor_Says(kActorFishDealer, 230, 14);
							Game_Flag_Set(kFlagFishDealerBuyFishTalk);
							if (!Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
								Actor_Says(kActorMcCoy, 35, 13);
								Actor_Voice_Over(1860, kActorVoiceOver); //99-1860.AUD	No self-respecting human would own one of those frauds.
								Actor_Modify_Friendliness_To_Other(kActorFishDealer, kActorMcCoy, -2);
								Actor_Set_Goal_Number(kActorFishDealer, 1);
							} else {
								dialogueWithFishDealerBuyGoldfish();
							}
						}
					} else {
						if (Actor_Clue_Query(kActorMcCoy, kClueGoldfish)) {
							Actor_Says(kActorMcCoy, 155, 17); //00-0155.AUD	How's business?
							Actor_Says(kActorFishDealer, 100, 14); //29-0100.AUD	Ah, business slow today. But tonight my people bring over baby barracudas.
							Actor_Says(kActorFishDealer, 110, 14); //29-0110.AUD	They're very cute. You should buy.
							Actor_Says(kActorMcCoy, 1845, 16); //00-1845.AUD	I’ll have to think about it.
							Game_Flag_Set(kFlagFishLadyTalkFinsished);
						} else {
							Actor_Says(kActorFishDealer, 230, 14); // 29-0230.AUD	You buy fish? Highest quality.
							Delay(2000);
							Game_Flag_Set(kFlagFishLadyTalkFinsished);
						}
					}
				} else {					
					// This dialogue will only happen if you have low frieneliness with the fish lady.
					Actor_Says(kActorMcCoy, 8514, 11); // Got anything new to tell me?
					if (Actor_Query_Friendliness_To_Other(kActorFishDealer, kActorMcCoy) > 49) {
						Actor_Says(kActorFishDealer, 170, 14); // Afraid not. But been busy today. Maybe you ask me later.
						Actor_Set_Goal_Number(kActorFishDealer, 1);
					} else {
						Actor_Says(kActorFishDealer, 220, 14); //29-0220.AUD	I haven't heard much. Row been very quiet.
						Actor_Set_Goal_Number(kActorFishDealer, 1);
					}
				}
			} else if (!Game_Flag_Query(kFlagAR01FishDealerTalk)) {
				Actor_Says(kActorMcCoy, 0, 18);
				Actor_Says(kActorFishDealer, 0, 14);
				Actor_Says(kActorFishDealer, 10, 14);
				Actor_Says(kActorFishDealer, 20, 14);
				Actor_Says(kActorFishDealer, 30, 14);
				Actor_Says(kActorMcCoy, 5, 17);
				Actor_Says(kActorFishDealer, 40, 14);
				Actor_Says(kActorMcCoy, 10, 13);
				Actor_Says(kActorFishDealer, 50, 14);
				Actor_Says(kActorMcCoy, 15, 17);
				Actor_Says(kActorFishDealer, 60, 14);
				Actor_Says(kActorFishDealer, 70, 14);
				Actor_Says(kActorFishDealer, 80, 14);
				Actor_Says(kActorFishDealer, 90, 14);
				Actor_Says(kActorMcCoy, 25, 13);
				Game_Flag_Set(kFlagAR01FishDealerTalk);
				Actor_Set_Goal_Number(kActorFishDealer, 1);
			} else {
				if (Actor_Clue_Query(kActorMcCoy, kClueStrangeScale1)
				    && !Actor_Clue_Query(kActorMcCoy, kClueFishLadyInterview)
				    && (!_vm->_cutContent || !Game_Flag_Query(kFlagWrongInvestigation))
				) {
					Actor_Says(kActorMcCoy, 40, 11);
					Actor_Says(kActorFishDealer, 120, 14);
					Actor_Says(kActorMcCoy, 45, 17); //00-0045.AUD	What other one?
					Actor_Says(kActorFishDealer, 130, 14); //29-0130.AUD	Other police show me scale from same snake.
					Actor_Says(kActorFishDealer, 140, 14);
					Actor_Says(kActorMcCoy, 50, 13);
					Actor_Says(kActorFishDealer, 150, 14);
#if BLADERUNNER_ORIGINAL_BUGS
					Actor_Clue_Acquire(kActorMcCoy, kClueFishLadyInterview, true, kActorMcCoy); // A bug? Shouldn't the last argument be -1 or kActorFishDealer here?
#else
					Actor_Clue_Acquire(kActorMcCoy, kClueFishLadyInterview, true, kActorFishDealer);
#endif // BLADERUNNER_ORIGINAL_BUGS
					
					} else {
						// original behavior
						if (Random_Query(1, 2) == 1) {
							Actor_Says(kActorMcCoy, 30, 17);
							Actor_Says(kActorFishDealer, 100, 14);
							Actor_Says(kActorFishDealer, 110, 14);
							Actor_Says(kActorMcCoy, 35, 13);
						} else {
							Actor_Says(kActorMcCoy, 30, 17);
							Actor_Says(kActorFishDealer, 220, 14);
						}
					}
				}
				Actor_Set_Goal_Number(kActorFishDealer, 1);
			}
			return true;
		}
		return false;
	}

bool SceneScriptAR01::ClickedOnItem(int itemId, bool a2) {
	return false;
}

bool SceneScriptAR01::ClickedOnExit(int exitId) {
	if (exitId == kAR01ExitHC01) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -358.0, 0.0, -149.0, 0, true, false, false)) {
			Loop_Actor_Walk_To_XYZ(kActorMcCoy, -477.0, 0.0, -149.0, 0, false, false, false);
			Game_Flag_Set(kFlagAR01toHC01);
			Game_Flag_Set(kFlagHC01GuzzaPrepare);
			Game_Flag_Reset(kFlagMcCoyInAnimoidRow);
			Game_Flag_Set(kFlagMcCoyInHawkersCircle);
			Set_Enter(kSetHC01_HC02_HC03_HC04, kSceneHC01);
			Actor_Set_Goal_Number(kActorFishDealer, 3);
		}
		return true;
	}

	if (exitId == kAR01ExitAR02) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -182.0, 0.0, -551.0, 0, true, false, false)) {
			Game_Flag_Set(kFlagAR01toAR02);
			Async_Actor_Walk_To_XYZ(kActorMcCoy, -222.0, 0.0, -690.0, 0, false);
			Set_Enter(kSetAR01_AR02, kSceneAR02);
#if BLADERUNNER_ORIGINAL_BUGS
			// Causes the fish dealer to blink out of existence
			// during the transition to AR02
			Actor_Set_Goal_Number(kActorFishDealer, 3);
#endif // BLADERUNNER_ORIGINAL_BUGS
		}
		return true;
	}

	if (exitId == kAR01ExitSpinner) {
		if (Game_Flag_Query(kFlagDNARowAvailable)) {
			Spinner_Set_Selectable_Destination_Flag(kSpinnerDestinationDNARow, true);
		}
		int v1 = Loop_Actor_Walk_To_XYZ(kActorMcCoy, -164.0f, 0.0f, 332.0f, 0, true, false, false);
		Actor_Face_Heading(kActorMcCoy, 545, false);
		if (Actor_Query_Goal_Number(kActorIzo) >= kGoalIzoTakePhoto
		&& Actor_Query_Goal_Number(kActorIzo) <= kGoalIzoEscape
		) {
			if (_vm->_cutContent) {
				// Made it so Izo only kills McCoy if he is a replicant. If McCoy tries to leave animoid row when he is chasing Izo he will refuse.
				if (Game_Flag_Query(kFlagIzoIsReplicant)) {	
					Player_Loses_Control();
					Actor_Put_In_Set(kActorIzo, kSetAR01_AR02);
					Actor_Set_At_XYZ(kActorIzo, -448.0, 0.0, 130.0, 0);
					Loop_Actor_Walk_To_XYZ(kActorIzo, -323.0f, 0.64f, 101.74f, 48, false, true, false);
					Loop_Actor_Walk_To_Actor(kActorIzo, kActorMcCoy, 48, false, true);
					Actor_Face_Actor(kActorIzo, kActorMcCoy, true);
					Actor_Change_Animation_Mode(kActorIzo, kAnimationModeCombatAttack);
					Actor_Says(kActorMcCoy, 1800, 21);
					Actor_Change_Animation_Mode(kActorMcCoy, 39);
					Player_Gains_Control();
					Actor_Retired_Here(kActorMcCoy, 12, 48, 1, kActorIzo);
				} else {
					Actor_Says(kActorMcCoy, 3545, 15); //00-3545.AUD	Not yet.
				}
			} else {
				Player_Loses_Control();
				Actor_Put_In_Set(kActorIzo, kSetAR01_AR02);
				Actor_Set_At_XYZ(kActorIzo, -448.0, 0.0, 130.0, 0);
				Loop_Actor_Walk_To_XYZ(kActorIzo, -323.0f, 0.64f, 101.74f, 48, false, true, false);
				Loop_Actor_Walk_To_Actor(kActorIzo, kActorMcCoy, 48, false, true);
				Actor_Face_Actor(kActorIzo, kActorMcCoy, true);
				Actor_Change_Animation_Mode(kActorIzo, kAnimationModeCombatAttack);
				Actor_Says(kActorMcCoy, 1800, 21);
				Actor_Change_Animation_Mode(kActorMcCoy, 39);
				Player_Gains_Control();
				Actor_Retired_Here(kActorMcCoy, 12, 48, 1, kActorIzo);
			}
		} else if (!v1) {
			if ( Game_Flag_Query(kFlagDNARowAvailable)
			&& !Game_Flag_Query(kFlagDNARowAvailableTalk)
			) {
				if (_vm->_cutContent) {
					if (Actor_Clue_Query(kActorMcCoy, kClueWeaponsCache)
					&& (Actor_Clue_Query(kActorMcCoy, kClueDetonatorWire)
					|| Actor_Clue_Query(kActorMcCoy, kCluePoliceWeaponUsed)
					|| Actor_Clue_Query(kActorMcCoy, kCluePlasticExplosive))) {
						Actor_Voice_Over(3480, kActorVoiceOver); //99-3480.AUD	Yeah, what a difference a day makes.
						Delay(1000);
						Actor_Voice_Over(3510, kActorVoiceOver); //99-3510.AUD	The picture was still a little blurry.
					} else if (Game_Flag_Query(kFlagDragonflyEarringTaken)) {
						Actor_Voice_Over(3480, kActorVoiceOver); //99-3480.AUD	Yeah, what a difference a day makes.
						Delay(1000);
						Actor_Voice_Over(3510, kActorVoiceOver); //99-3510.AUD	The picture was still a little blurry.
					} else {
						Actor_Voice_Over(4310, kActorVoiceOver); // 99-4310.AUD	I was fresh out of leads.	
					}
				} else {
					Actor_Voice_Over(4310, kActorVoiceOver); // 99-4310.AUD	I was fresh out of leads.	
				}
				if (_vm->_cutContent) {
					if (!Actor_Clue_Query(kActorMcCoy, kClueWeaponsCache)
					&& !Actor_Clue_Query(kActorMcCoy, kClueBobShotInSelfDefense)
					&& !Game_Flag_Query(kFlagMcCoyShotIzo)
					&& !Game_Flag_Query(kFlagDragonflyEarringTaken)) {
						Actor_Voice_Over(4320, kActorVoiceOver); //99-4320.AUD	Poking around Hawker's Circle had been a waste of time.
					}
				} else {
					Actor_Voice_Over(4320, kActorVoiceOver); //99-4320.AUD	Poking around Hawker's Circle had been a waste of time.
				}
				if (_vm->_cutContent) {
					if (!Actor_Clue_Query(kActorMcCoy, kClueWeaponsCache)
					&& !Game_Flag_Query (kFlagDragonflyEarringTaken)) {
						Actor_Voice_Over(4330, kActorVoiceOver); //99-4330.AUD	I had nothing to connect this Izo character to the Eisenduller murder.
					} else if (Actor_Clue_Query(kActorMcCoy, kClueWeaponsCache)
					&& (!Actor_Clue_Query(kActorMcCoy, kClueDetonatorWire)
					&& !Actor_Clue_Query(kActorMcCoy, kCluePoliceWeaponUsed)
					&& !Actor_Clue_Query(kActorMcCoy, kCluePlasticExplosive))) {
						Actor_Voice_Over(4330, kActorVoiceOver); //99-4330.AUD	I had nothing to connect this Izo character to the Eisenduller murder.
					}
				} else {
					Actor_Voice_Over(4330, kActorVoiceOver);
				}
				Actor_Voice_Over(4340, kActorVoiceOver); //99-4340.AUD	But if the Replicants had done in one Tyrell scientist, maybe they'd go after another.
				Actor_Voice_Over(4350, kActorVoiceOver);
				if (_vm->_cutContent) {
					if (Player_Query_Agenda() == kPlayerAgendaPolite) {
						Delay(500);
						Actor_Says(kActorMcCoy, 170, 14); //00-0170.AUD	Damn.
						Delay(1000);
						Actor_Says(kActorMcCoy, 6875, 13); //00-6875.AUD	I gotta go.
					}
				}		
				if (_vm->_cutContent) {
					Game_Flag_Reset(kFlagIzoGotAway);
					Game_Flag_Reset(kFlagIzoOnTheRun);
					Game_Flag_Reset(kFlagIzoWarnedAboutCrystal);
				}
				Game_Flag_Set(kFlagDNARowAvailableTalk);
			}
			Game_Flag_Reset(kFlagMcCoyInChinaTown);
			Game_Flag_Reset(kFlagMcCoyInRunciters);
			Game_Flag_Reset(kFlagMcCoyInMcCoyApartment);
			Game_Flag_Reset(kFlagMcCoyInPoliceStation);
			Game_Flag_Reset(kFlagMcCoyInBradburyBuilding);
			Game_Flag_Reset(kFlagMcCoyInHysteriaHall);
			Game_Flag_Reset(kFlagMcCoyInAnimoidRow);

			int spinnerDest = Spinner_Interface_Choose_Dest(kAR01LoopDoorAnim, false);
			Actor_Face_Heading(kActorMcCoy, 545, false);

			switch (spinnerDest) {
			case kSpinnerDestinationPoliceStation:
				Game_Flag_Set(kFlagMcCoyInPoliceStation);
				Game_Flag_Reset(kFlagSpinnerAtAR01);
				Game_Flag_Set(kFlagSpinnerAtPS01);
				Set_Enter(kSetPS01, kScenePS01);
				Scene_Loop_Start_Special(kSceneLoopModeChangeSet, kAR01LoopOutshot, true);
				break;
			case kSpinnerDestinationMcCoysApartment:
				Game_Flag_Set(kFlagMcCoyInMcCoyApartment);
				Game_Flag_Reset(kFlagSpinnerAtAR01);
				Game_Flag_Set(kFlagSpinnerAtMA01);
				Set_Enter(kSetMA01, kSceneMA01);
				Scene_Loop_Start_Special(kSceneLoopModeChangeSet, kAR01LoopOutshot, true);
				break;
			case kSpinnerDestinationRuncitersAnimals:
				Game_Flag_Set(kFlagMcCoyInRunciters);
				Game_Flag_Reset(kFlagSpinnerAtAR01);
				Game_Flag_Set(kFlagSpinnerAtRC01);
				Set_Enter(kSetRC01, kSceneRC01);
				Scene_Loop_Start_Special(kSceneLoopModeChangeSet, kAR01LoopOutshot, true);
				break;
			case kSpinnerDestinationChinatown:
				Game_Flag_Set(kFlagMcCoyInChinaTown);
				Game_Flag_Reset(kFlagSpinnerAtAR01);
				Game_Flag_Set(kFlagSpinnerAtCT01);
				Set_Enter(kSetCT01_CT12, kSceneCT01);
				Scene_Loop_Start_Special(kSceneLoopModeChangeSet, kAR01LoopOutshot, true);
				break;
			case kSpinnerDestinationTyrellBuilding:
				Game_Flag_Set(kFlagMcCoyInTyrellBuilding);
				Game_Flag_Reset(kFlagSpinnerAtAR01);
				Game_Flag_Set(kFlagSpinnerAtTB02);
				Set_Enter(kSetTB02_TB03, kSceneTB02);
				Scene_Loop_Start_Special(kSceneLoopModeChangeSet, kAR01LoopOutshot, true);
				break;
			case kSpinnerDestinationDNARow:
				Game_Flag_Set(kFlagMcCoyInDNARow);
				Game_Flag_Reset(kFlagSpinnerAtAR01);
				Game_Flag_Set(kFlagSpinnerAtDR01);
				Set_Enter(kSetDR01_DR02_DR04, kSceneDR01);
				Scene_Loop_Start_Special(kSceneLoopModeChangeSet, kAR01LoopOutshot, true);
				break;
			case kSpinnerDestinationBradburyBuilding:
				Game_Flag_Set(kFlagMcCoyInBradburyBuilding);
				Game_Flag_Reset(kFlagSpinnerAtAR01);
				Game_Flag_Set(kFlagSpinnerAtBB01);
				Set_Enter(kSetBB01, kSceneBB01);
				Scene_Loop_Start_Special(kSceneLoopModeChangeSet, kAR01LoopOutshot, true);
				break;
			case kSpinnerDestinationNightclubRow:
				Game_Flag_Set(kFlagMcCoyInNightclubRow);
				Game_Flag_Reset(kFlagSpinnerAtAR01);
				Game_Flag_Set(kFlagSpinnerAtNR01);
				Set_Enter(kSetNR01, kSceneNR01);
				Scene_Loop_Start_Special(kSceneLoopModeChangeSet, kAR01LoopOutshot, true);
				break;
			case kSpinnerDestinationHysteriaHall:
				Game_Flag_Set(kFlagMcCoyInHysteriaHall);
				Game_Flag_Reset(kFlagSpinnerAtAR01);
				Game_Flag_Set(kFlagSpinnerAtHF01);
				Set_Enter(kSetHF01, kSceneHF01);
				Scene_Loop_Start_Special(kSceneLoopModeChangeSet, kAR01LoopOutshot, true);
				break;
			default:
				Game_Flag_Set(kFlagMcCoyInAnimoidRow);
				Actor_Set_Invisible(kActorMcCoy, false);
				break;
			}
		}
		return true;
	}
	return false;
}

bool SceneScriptAR01::ClickedOn2DRegion(int region) {
	return false;
}

void SceneScriptAR01::SceneFrameAdvanced(int frame) {
	if (frame == 16) {
		Ambient_Sounds_Play_Sound(kSfxCARDOWN3,  40,   0,   0, 99);
	}
	if (frame == 78 || frame == 199) {
		Ambient_Sounds_Play_Sound(kSfxSPINOPN4, 100, -50, -50, 99);
	}
	if (frame == 122 || frame == 242) {
		Ambient_Sounds_Play_Sound(kSfxSPINCLS1, 100, -50, -50, 99);
	}
	if (frame == 256) {
		Ambient_Sounds_Play_Sound(kSfxCARUP3,    40, -50,  80, 99);
	}
	if ((frame == 75
	  || frame == 196
	 )
	 && Game_Flag_Query(kFlagArrivedFromSpinner2)
	) {
		Actor_Face_Heading(kActorMcCoy, 545, false);
		Actor_Change_Animation_Mode(kActorMcCoy, kAnimationModeSpinnerGetOut);
		Game_Flag_Reset(kFlagArrivedFromSpinner2);
	} else if ( frame == 196
	        && !Game_Flag_Query(kFlagArrivedFromSpinner2
	)) {
		Actor_Change_Animation_Mode(kActorMcCoy, kAnimationModeSpinnerGetIn);
	}
}

void SceneScriptAR01::ActorChangedGoal(int actorId, int newGoal, int oldGoal, bool currentSet) {
}

void SceneScriptAR01::PlayerWalkedIn() {
	if (!Game_Flag_Query(kFlagAR01Entered)) {
	// Moved game set flag to after the following dispatcher dialogue so it can play.
	}
	if (Game_Flag_Query(kFlagHC01toAR01)) {
		Loop_Actor_Walk_To_XYZ(kActorMcCoy, -358.0f, 0.0f, -149.0f, 0, true, false, false);
		Game_Flag_Reset(kFlagHC01toAR01);
	}
	// Added in some dialogue with the fish lady so McCoy will now learn Hasans name. Also added in some dispatcher dialogue.
	if (_vm->_cutContent) {
		if (!Game_Flag_Query(kFlagAR01Entered)) {
			Player_Loses_Control();
			Loop_Actor_Walk_To_XYZ(kActorMcCoy, -152.40f, 0.55f, 208.19f, 48, false, false, true);
			Actor_Face_Actor(kActorMcCoy, kActorFishDealer, true);
			Actor_Face_Actor(kActorFishDealer, kActorMcCoy, true);
			Player_Gains_Control();
			Actor_Says(kActorMcCoy, 8910, 14); //00-8910.AUD	Hey you.
			Actor_Says(kActorFishDealer, 230, -1); // 29-0230.AUD	You buy fish? Highest quality.
			if (Player_Query_Agenda() == kPlayerAgendaPolite) {
				Actor_Says(kActorMcCoy, 140, 18); //00-0140.AUD	Not today, thanks.
			} else {
				Actor_Says(kActorMcCoy, 35, 13); //00-0035.AUD	I'll pass.
			}
			Actor_Says(kActorMcCoy, 475, 13);  //00-0475.AUD	There are things I want to know.
			Actor_Says(kActorFishDealer, 230, -1); // 29-0230.AUD	You buy fish? Highest quality.
			Delay (1000);
			Actor_Says(kActorMcCoy, 7815, 16); //00-7815.AUD	No.
			Delay (500);
			Actor_Says(kActorMcCoy, 660, 14); //00-0660.AUD	You seen any suspicious types around here lately?
			Delay (2000);
			Actor_Says(kActorMcCoy, 1885, kAnimationModeTalk); //00-1885.AUD	I’ll take that as a yes.
			Delay (500);
			Actor_Says(kActorMcCoy, 875, 17); //00-0875.AUD	Where do I find him?
			Delay (1000);
			Actor_Face_Actor(kActorMcCoy, kActorHasan, true);
			Actor_Face_Actor(kActorFishDealer, kActorHasan, true);
			Actor_Says(kActorFishDealer, 140, -1);//29-0140.AUD	I sent him to Abdul Hasan.
			Actor_Says(kActorFishDealer, 70, -1);// 29-0070.AUD	You try there.
			Actor_Face_Actor(kActorMcCoy, kActorFishDealer, true);
			Actor_Face_Actor(kActorFishDealer, kActorMcCoy, true);
			Actor_Says(kActorMcCoy, 100, 18);//00-0100.AUD	I'll do that.
			Delay (1000);
			Actor_Says(kActorMcCoy, 5150, 14); //00-5150.AUD	One more thing.
			Actor_Says(kActorMcCoy, 8615, 16); //00-8615.AUD	Heard anything on the street?
			Actor_Says(kActorFishDealer, 160, -1); //29-0160.AUD	I heard something, yeah. I tell it to you, if you like.
			Actor_Says(kActorMcCoy, 2635, 18); //00-2635.AUD	I’m all ears.
			Actor_Says(kActorFishDealer, 230, -1); // 29-0230.AUD	You buy fish? Highest quality.
			Actor_Says(kActorMcCoy, 940, 13); //00-0940.AUD	I need to ask you--
			Actor_Says(kActorFishDealer, 230, -1); // 29-0230.AUD	You buy fish? Highest quality.
			Delay (2000);							
			Actor_Says(kActorMcCoy, 1535, 19); //00-1535.AUD	Ah, never mind.
			Delay (1000);
			Actor_Says(kActorFishDealer, 230, -1); // 29-0230.AUD	You buy fish? Highest quality.
			Delay (3000);	
			Game_Flag_Set(kFlagAR01Entered);
			if (Actor_Query_Intelligence(kActorOfficerLeary) == 40) { 
				ADQ_Add(kActorOfficerLeary, 300, kAnimationModeTalk); //23-0300.AUD	LA, 38 Metro 3. Subject check.
				ADQ_Add(kActorDispatcher, 480, kAnimationModeTalk); //38-0480.AUD	Sector 3 unit was under check. Go ahead.
				ADQ_Add(kActorOfficerLeary, 290, kAnimationModeTalk);  // 23-0290.AUD	Subject check on a Willard Mack. M-A-C-K. White male, six foot, 180 pounds, brown and brown with a DOB of 10-30-1995.
				ADQ_Add(kActorDispatcher, 490, kAnimationModeTalk); //38-0490.AUD	38 Metro 3 LA. 10-4. Stand by.
				ADQ_Add_Pause(1000);
				ADQ_Add(kActorDispatcher, 500, kAnimationModeTalk); //38-0500.AUD	38 Metro 3 LA. No hits locally around CIC on subject Willard Mack. M-A-C-K.
				ADQ_Add(kActorOfficerLeary, 450, kAnimationModeTalk);  // 23-0450.AUD	LA, 13 Metro 1. Copied. No wants.
				ADQ_Add(kActorDispatcher, 510, kAnimationModeTalk); //38-0510.AUD	10-4. LA Copy. 10-98.
			}
		}
	}
	if (Actor_Query_Goal_Number(kActorPhotographer) < 199) {
		Actor_Set_Goal_Number(kActorPhotographer, 199);
	}
}

void SceneScriptAR01::PlayerWalkedOut() {
	Actor_Set_Invisible(kActorMcCoy, false);
	Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
	Ambient_Sounds_Remove_All_Looping_Sounds(1u);
	if (!Game_Flag_Query(kFlagMcCoyInHawkersCircle)) {
		Music_Stop(2u);
	}
	if (!Game_Flag_Query(kFlagAR01toHC01)
	 && !Game_Flag_Query(kFlagAR01toAR02)
	) {
#if BLADERUNNER_ORIGINAL_BUGS
		Outtake_Play(kOuttakeTowards3, true, -1);
#else
		if (!Game_Flag_Query(kFlagMcCoyInTyrellBuilding)) {
			// don't play an extra outtake when going to Tyrell Building
			Outtake_Play(kOuttakeTowards3, true, -1); // Act 1, 2, 3
		}
#endif // BLADERUNNER_ORIGINAL_BUGS
	}
}

void SceneScriptAR01::DialogueQueueFlushed(int a1) {
}

/**
* This is only for cut content (purchasing the Goldfish)
*/
void SceneScriptAR01::dialogueWithFishDealerBuyGoldfish() {
	Dialogue_Menu_Clear_List();

	Dialogue_Menu_Clear_Never_Repeat_Was_Selected_Flag(530);
	Dialogue_Menu_Clear_Never_Repeat_Was_Selected_Flag(540);

	if (_vm->_cutContent) {
		if (Global_Variable_Query(kVariableChinyen) >= 105
		|| Query_Difficulty_Level() == kGameDifficultyEasy
		) {
			if (Player_Query_Agenda() == kPlayerAgendaPolite) {
				DM_Add_To_List_Never_Repeat_Once_Selected(530, 7, 3, 2); // BUY
			} else {
				DM_Add_To_List_Never_Repeat_Once_Selected(540, 1, 5, 7); // NO THANKS
			}
		} else {
			DM_Add_To_List_Never_Repeat_Once_Selected(540, 1, 5, 7); // NO THANKS
		}
	} else {
		if (Global_Variable_Query(kVariableChinyen) >= 105
		|| Query_Difficulty_Level() == kGameDifficultyEasy
		) {
			DM_Add_To_List_Never_Repeat_Once_Selected(530, 7, 5, 3); // BUY
		}
		DM_Add_To_List_Never_Repeat_Once_Selected(540, 3, 5, 7); // NO THANKS
	}

	Dialogue_Menu_Appear(320, 240);
	int answerValue = Dialogue_Menu_Query_Input();
	Dialogue_Menu_Disappear();

	if (answerValue == 530) { // BUY
	// Added in a flag so certain dialogue will trigger.
		Actor_Says(kActorMcCoy, 7000, 23);
		if (_vm->_cutContent) {
			Actor_Change_Animation_Mode(kActorMcCoy, 23);
			Actor_Change_Animation_Mode(kActorFishDealer, 23);
			Delay(800);
			Item_Pickup_Spin_Effect_From_Actor(kModelAnimationGoldfish, kActorMcCoy, 0, 0);
			Delay(800);
		}
		Game_Flag_Set(kFlagBoughtFish);
		if (Query_Difficulty_Level() != kGameDifficultyEasy) {
			Global_Variable_Decrement(kVariableChinyen, 105);
		}
		Actor_Clue_Acquire(kActorMcCoy, kClueGoldfish, true, kActorFishDealer);
		if (!_vm->_cutContent) {
			Actor_Modify_Friendliness_To_Other(kActorFishDealer, kActorMcCoy, 5);
		}
	} else if (answerValue == 540) { // NO THANKS
		Actor_Says(kActorMcCoy, 7005, 13);
		if (!_vm->_cutContent) {
			Actor_Modify_Friendliness_To_Other(kActorFishDealer, kActorMcCoy, -5);
		}
	}
}

} // End of namespace BladeRunner
