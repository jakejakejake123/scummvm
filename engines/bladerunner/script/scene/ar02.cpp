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

void SceneScriptAR02::InitializeScene() {
	if (_vm->_cutContent) {
		Music_Play(kMusicArabLoop, 22, 0, 2, -1, kMusicLoopRepeatRandomStart, 2);
	} else {
		Music_Play(kMusicArabLoop, 22, 0, 2, -1, kMusicLoopRepeat, 2);
	}
	if (Game_Flag_Query(kFlagRC03toAR02)) {
		Setup_Scene_Information(-560.0f, 0.0f, -799.0f, 333);
	} else {
		Setup_Scene_Information(-182.0f, 0.0f, -551.0f, 973);
	}
	Scene_Exit_Add_2D_Exit(0,  0, 439, 212, 479, 2);
	Scene_Exit_Add_2D_Exit(1, 81, 202, 215, 406, 3);
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
	Ambient_Sounds_Add_Sound(kSfxHCANM8,   3,  30, 16,  16, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxHCANM2,   3,  30, 16,  16, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxHCANM3,   3,  30, 16,  16, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxHCANM4,   3,  30, 16,  16, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxHCANM5,   3,  30, 16,  16, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxHCANM6,   3,  30, 16,  16, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxHCANM7,   3,  30, 16,  16, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxHCANM1,   3,  30, 16,  16, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Speech_Sound(kActorBlimpGuy,  0, 10u, 260u, 17, 24, -100, 100, -101, -101, 1, 1);
	Ambient_Sounds_Add_Speech_Sound(kActorBlimpGuy, 20, 10u, 260u, 17, 24, -100, 100, -101, -101, 1, 1);
	Ambient_Sounds_Add_Speech_Sound(kActorBlimpGuy, 40, 10u, 260u, 17, 24, -100, 100, -101, -101, 1, 1);
	Ambient_Sounds_Add_Speech_Sound(kActorBlimpGuy, 50, 10u, 260u, 17, 24, -100, 100, -101, -101, 1, 1);
	Ambient_Sounds_Add_Sound(kSfxSPIN2B,  10, 180, 16,  25,    0,   0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSPIN3A,  10, 180, 16,  25,    0,   0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxTHNDER2, 10, 180, 50, 100,    0,   0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxTHNDER3, 10, 180, 50, 100,    0,   0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxTHNDER4, 10, 180, 50, 100,    0,   0, -101, -101, 0, 0);
	if (Game_Flag_Query(kFlagSpinnerAtAR01)
	    && Game_Flag_Query(kFlagAR01toAR02)) {
		Scene_Loop_Start_Special(kSceneLoopModeLoseControl, 1, false);
		Scene_Loop_Set_Default(2);
		Game_Flag_Reset(kFlagAR01toAR02);
	} else if (!Game_Flag_Query(kFlagSpinnerAtAR01)
	           &&  Game_Flag_Query(kFlagAR01toAR02)) {
		Scene_Loop_Start_Special(kSceneLoopModeLoseControl, 0, false);
		Scene_Loop_Set_Default(2);
		Game_Flag_Reset(kFlagAR01toAR02);
	} else {
		Scene_Loop_Set_Default(2);
	}
}

void SceneScriptAR02::SceneLoaded() {
	Obstacle_Object("DF_BOOTH", true);
#if BLADERUNNER_ORIGINAL_BUGS
	if (!Game_Flag_Query(kFlagAR02DektoraBoughtScorpions)) {
		Item_Add_To_World(kItemScorpions, kModelAnimationCageOfScorpions, kSetAR01_AR02, -442.84f, 36.77f, -1144.51f, 360, 36, 36, false, true, false, true);
	}
	if ( Global_Variable_Query(kVariableChapter) == 4
	 && !Game_Flag_Query(kFlagAR02DektoraBoughtScorpions)
	) {
		Game_Flag_Set(kFlagNotUsed0);
		Item_Remove_From_World(kItemScorpions);
	}
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

	} else if (_vm->_cutContent) {
		if (Global_Variable_Query(kVariableChapter) > 3
	    || Game_Flag_Query(kFlagAR02DektoraBoughtScorpions)) {
			Game_Flag_Reset(kFlagScorpionsInAR02);
			Item_Remove_From_World(kItemScorpions);
		}
	} else if (Global_Variable_Query(kVariableChapter) >= 4
	           && !Game_Flag_Query(kFlagAR02DektoraBoughtScorpions)
	           && Game_Flag_Query(kFlagScorpionsInAR02)
	) {
		Game_Flag_Reset(kFlagScorpionsInAR02);
		Item_Remove_From_World(kItemScorpions);
	}
#endif // BLADERUNNER_ORIGINAL_BUGS
}

bool SceneScriptAR02::MouseClick(int x, int y) {
	return Region_Check(250, 215, 325, 260);
}

bool SceneScriptAR02::ClickedOn3DObject(const char *objectName, bool a2) {
	return false;
}

bool SceneScriptAR02::ClickedOnActor(int actorId) {
	if (actorId == kActorInsectDealer) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -386.96f, 0.0f, -1078.45f, 12, true, false, false)) {
			Actor_Face_Actor(kActorMcCoy, kActorInsectDealer, true);
			Actor_Face_Actor(kActorInsectDealer, kActorMcCoy, true);
			if (Global_Variable_Query(kVariableChapter) == 2) {
				if (Actor_Query_Friendliness_To_Other(kActorInsectDealer, kActorMcCoy) < 50) {
					Actor_Says(kActorMcCoy, 8940, 13); //00-8940.AUD	What are you staring at?
				} else if (Game_Flag_Query(kFlagAR02InsectDealerInterviewed)
				&& !Game_Flag_Query(kFlagAR02InsectDealerTalk)) {
					Game_Flag_Set(kFlagAR02InsectDealerTalk);
					Player_Loses_Control();
					ADQ_Flush();
					ADQ_Add(kActorInsectDealer, 210, 14);
					Loop_Actor_Walk_To_XYZ(kActorMcCoy, -350.66f, 0.0f, -1117.19f, 0, false, false, false);
					Actor_Face_Actor(kActorMcCoy, kActorInsectDealer, true);
					if (_vm->_cutContent) {
						Actor_Says(kActorInsectDealer, 220, 14); // Doesn't she deserve a gift?
					}
					Actor_Says(kActorMcCoy, 110, 18); //00-0110.AUD	All my girl cares about is food and love.
					Actor_Says(kActorInsectDealer, 230, 14);
					Actor_Says(kActorMcCoy, 115, 18); //
					Actor_Says(kActorInsectDealer, 240, 14);
					Item_Pickup_Spin_Effect(kModelAnimationMaggieBracelet, 288, 257);
					Actor_Says(kActorInsectDealer, 250, 14);
					Player_Gains_Control();
					if (_vm->_cutContent) {
						if (Player_Query_Agenda() == kPlayerAgendaSurly 
						|| Player_Query_Agenda() == kPlayerAgendaErratic) {
							Actor_Says(kActorMcCoy, 8575, 19); // More useless junk.
							Actor_Modify_Friendliness_To_Other(kActorInsectDealer, kActorMcCoy, -2);
						} else {
							dialogueWithInsectDealerBuyBracelet();
						}
					} else {
						dialogueWithInsectDealerBuyBracelet();
					}
				} else if (Game_Flag_Query(kFlagAR02InsectDealerTalk)) {
					Actor_Says(kActorMcCoy, 75, 18);
					Actor_Says(kActorInsectDealer, 60, 12);
					Actor_Says(kActorInsectDealer, 70, 14);
					if (_vm->_cutContent) {
						// Made it so if Dektora purchased the scorpions at this point McCoy will ask about them if he saw them before.
						if (Game_Flag_Query(kFlagAR02ScorpionsChecked) 
						&& Game_Flag_Query(kFlagAR02DektoraBoughtScorpions) 
						&& !Actor_Clue_Query(kActorMcCoy, kCluePurchasedScorpions)) {
							Actor_Says(kActorMcCoy, 220, 14);
							Actor_Says(kActorInsectDealer, 320, 12);
							Actor_Says(kActorMcCoy, 225, 13);
							Actor_Says(kActorInsectDealer, 330, 14);
							Actor_Says(kActorMcCoy, 230, 19);
							Actor_Says(kActorInsectDealer, 340, 13);
							Actor_Says(kActorInsectDealer, 350, 12);
							if (Player_Query_Agenda() != kPlayerAgendaSurly 
							&& Player_Query_Agenda() != kPlayerAgendaErratic) {
								Actor_Says(kActorMcCoy, 235, 16); //00-0235.AUD	Gotcha.
							} else {
								Actor_Says(kActorMcCoy, 215, 13); // Thanks for your help
							}
							Actor_Clue_Acquire(kActorMcCoy, kCluePurchasedScorpions, false, kActorInsectDealer);	
						}
					}
				} else {
					dialogueWithInsectDealer1();
				}
			} else if (Global_Variable_Query(kVariableChapter) > 2) {
				if (Actor_Query_Friendliness_To_Other(kActorInsectDealer, kActorMcCoy) > 49) {	
					if (Actor_Clue_Query(kActorMcCoy, kCluePeruvianLadyInterview)
					&& !Actor_Clue_Query(kActorMcCoy, kClueDragonflyCollection)) {
						Actor_Says(kActorMcCoy, 205, 16);
						if (_vm->_cutContent) {
							Actor_Says(kActorInsectDealer, 390, 13);// 16-0390.AUD	Sí. Rumors are flying these days. Let me tell you what I have heard.
							Actor_Says(kActorMcCoy, 4940, 13); //00-4940.AUD	Okay, let's have it.
						}
						Actor_Says(kActorInsectDealer, 290, 12);
						Actor_Says(kActorInsectDealer, 300, 13);
						Actor_Says(kActorMcCoy, 210, 15); //00-0210.AUD	You know the name of the nightclub owner?
						Actor_Says(kActorInsectDealer, 310, 12);
						if (_vm->_cutContent) {
							if (Player_Query_Agenda() != kPlayerAgendaSurly 
							&& Player_Query_Agenda() != kPlayerAgendaErratic) {
								Actor_Says(kActorMcCoy, 1315, 12); //00-1315.AUD	Thanks for your time.
							} else {
								Actor_Says(kActorMcCoy, 215, 13); // Thanks for your help
							}
							if (Game_Flag_Query(kFlagAR02ScorpionsChecked) 
							&& Game_Flag_Query(kFlagAR02DektoraBoughtScorpions) 
							&& !Actor_Clue_Query(kActorMcCoy, kCluePurchasedScorpions)) {
								Actor_Says(kActorMcCoy, 220, 14);
								Actor_Says(kActorInsectDealer, 320, 12);
								Actor_Says(kActorMcCoy, 225, 13);
								Actor_Says(kActorInsectDealer, 330, 14);
								Actor_Says(kActorMcCoy, 230, 19);
								Actor_Says(kActorInsectDealer, 340, 13);
								Actor_Says(kActorInsectDealer, 350, 12);
								if (Player_Query_Agenda() != kPlayerAgendaSurly 
								&& Player_Query_Agenda() != kPlayerAgendaErratic) {
									Actor_Says(kActorMcCoy, 235, 16); //00-0235.AUD	Gotcha.
								} else {
									Actor_Says(kActorMcCoy, 215, 13); // Thanks for your help
								}
								Actor_Clue_Acquire(kActorMcCoy, kCluePurchasedScorpions, false, kActorInsectDealer);
							}
						} else if (Game_Flag_Query(kFlagAR02DektoraBoughtScorpions)) {
							Actor_Says(kActorMcCoy, 220, 14);
							Actor_Says(kActorInsectDealer, 320, 12);
							Actor_Says(kActorMcCoy, 225, 13);
							Actor_Says(kActorInsectDealer, 330, 14);
							Actor_Says(kActorMcCoy, 230, 19);
							Actor_Says(kActorInsectDealer, 340, 13);
							Actor_Says(kActorInsectDealer, 350, 12);
							Actor_Says(kActorMcCoy, 235, 16);
							Actor_Clue_Acquire(kActorMcCoy, kCluePurchasedScorpions, false, kActorInsectDealer);
						}
						Actor_Clue_Acquire(kActorMcCoy, kClueDragonflyCollection, false, kActorInsectDealer);
					} else if (_vm->_cutContent) {
						if (Actor_Query_Friendliness_To_Other(kActorInsectDealer, kActorMcCoy) > 49) {	
							if (Actor_Clue_Query(kActorMcCoy, kClueDragonflyCollection)) {
								if (!Game_Flag_Query(kFlagSlugTalk)) {
									Actor_Says(kActorMcCoy, 240, 17); // How's business?
									Actor_Says(kActorInsectDealer, 360, 13);
									Actor_Says(kActorInsectDealer, 370, 14);
									if (!Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
										Actor_Says(kActorMcCoy, 245, 13); //00-0245.AUD	Yeah, I can't imagine a better stocking-stuffer.
									}
									Delay (1000);
									Actor_Says(kActorMcCoy, 8610, 17); // What's the word, friend?																	
									Actor_Says(kActorInsectDealer, 400, 13); // I hear very little.
									Actor_Says(kActorInsectDealer, 460, 14);
									Actor_Says(kActorInsectDealer, 470, 13); // This slug, perhaps.
									Game_Flag_Set(kFlagSlugTalk);
									Item_Pickup_Spin_Effect_From_Actor(kModelAnimationSlug, kActorInsectDealer, 0, -40);
									if (!Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
										Actor_Voice_Over(1860, kActorVoiceOver); //99-1860.AUD	No self-respecting human would own one of those frauds.
									} else {
										dialogueWithInsectDealerBuySlug();
									}
								} else {
									if (Game_Flag_Query(kFlagAR02ScorpionsChecked) 
									&& Game_Flag_Query(kFlagAR02DektoraBoughtScorpions) 
									&& !Actor_Clue_Query(kActorMcCoy, kCluePurchasedScorpions)) {
										Actor_Says(kActorMcCoy, 220, 14);
										Actor_Says(kActorInsectDealer, 320, 12);
										Actor_Says(kActorMcCoy, 225, 13);
										Actor_Says(kActorInsectDealer, 330, 14);
										Actor_Says(kActorMcCoy, 230, 19);
										Actor_Says(kActorInsectDealer, 340, 13);
										Actor_Says(kActorInsectDealer, 350, 12);
										if (Player_Query_Agenda() != kPlayerAgendaSurly 
										&& Player_Query_Agenda() != kPlayerAgendaErratic) {
											Actor_Says(kActorMcCoy, 235, 16); //00-0235.AUD	Gotcha.
										} else {
											Actor_Says(kActorMcCoy, 215, 13); // Thanks for your help
										}
										Actor_Clue_Acquire(kActorMcCoy, kCluePurchasedScorpions, false, kActorInsectDealer);
									} else {
										Actor_Says(kActorMcCoy, 1315, 12); //00-1315.AUD	Thanks for your time.
									}
								}
							}
						}
					} else {
						// original behavior
						Actor_Says(kActorMcCoy, 240, 17); // How's business?
						Actor_Says(kActorInsectDealer, 360, 13);
						Actor_Says(kActorInsectDealer, 370, 14);
						Actor_Says(kActorMcCoy, 245, 13);
					}
				}
			}
			return true;
		}
	}

	if (actorId == kActorHasan
	// Made it so the intro convesation with Hasan always plays regardless of act. Also McCoy will now introduce himself as a cop immediately as to avoid inconsistencies with Hasan knowing that McCoy is a cop.
	&& Global_Variable_Query(kVariableChapter) >= 2
	) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -240.79f, 0.0f, -1328.89f, 12, true, false, false)) {
			Actor_Face_Actor(kActorMcCoy, kActorHasan, true);
			Actor_Face_Actor(kActorHasan, kActorMcCoy, true);
			if (!Game_Flag_Query(kFlagAR02HassanTalk)) {
				Actor_Says(kActorHasan, 0, 14);
				Actor_Says(kActorMcCoy, 140, 18);
				if (_vm->_cutContent) {
					Actor_Says(kActorMcCoy, 505, 23); //00-0505.AUD	McCoy, LPD.
					Actor_Says(kActorHasan, 30, 11);//20-0030.AUD	Oh, you're a policeman.	
					Actor_Says(kActorMcCoy, 7200, 13); //00-7200.AUD	Bingo.
					Actor_Says(kActorMcCoy, 660, 14); //00-0660.AUD	You seen any suspicious types around here lately?
					Actor_Says(kActorHasan, 250, 12); //20-0250.AUD	I'm afraid not, noble one. But you shall surely be the first to know, if I do hear something.
					if (Player_Query_Agenda() == kPlayerAgendaSurly 
					|| Player_Query_Agenda() == kPlayerAgendaErratic) {
						Actor_Says(kActorMcCoy, 3910, 16); //00-3910.AUD	You’re lying.
						Actor_Says(kActorHasan, 270, 11); //20-0270.AUD	You sully my good name with such accusations. I speak only the truth, I swear!
						Actor_Says(kActorMcCoy, 940, 13);
						// Quote 80 is *boop* in ENG and DEU versions
						// In FRA, ITA versions it is identical to the second half of quote 70, and thus redundant
						// In ESP version it is the missing second half of quote 70, and is required!
						if (_vm->_cutContent
							&& _vm->_language == Common::ES_ESP
						) {
							Actor_Says_With_Pause(kActorHasan, 70, 0.0f, 12);
							Actor_Says(kActorHasan, 80, kAnimationModeTalk);
						} else {
							Actor_Says(kActorHasan, 70, 12);//20-0070.AUD	Certainly the LPD must have better things to do than to question a humble merchant over and over again about the same things.
						}
						Actor_Says(kActorHasan, 90, 12);//20-0090.AUD	Why aren't you out arresting criminals like that disreputable Bob fellow.
						// Made it so McCoy only questions who Bob is and is directed to Bobs shop only if McCoy hasn't Met Bob.
						if (!Game_Flag_Query(kFlagRC04Entered)) {
							Actor_Says(kActorMcCoy, 180, 15); //00-0180.AUD	Bob?
						}
						Actor_Says(kActorHasan, 100, 14); //20-0100.AUD	He owns the armament shop up the street. He is insane, noble one. Insane.
						Actor_Says(kActorHasan, 110, 12);
						// Quote 130 is *boop* in ENG and DEU versions
						// In FRA, ITA versions it is identical to the second half of quote 120, and thus redundant
						// In ESP version it is the missing second half of quote 120, and is required!
						if (_vm->_cutContent
							&& _vm->_language == Common::ES_ESP
						) {
							Actor_Says_With_Pause(kActorHasan, 120, 0.0f, 13);
							Actor_Says(kActorHasan, 130, kAnimationModeTalk);
						} else {
							Actor_Says(kActorHasan, 120, 13);
						}
						Actor_Modify_Friendliness_To_Other(kActorHasan, kActorMcCoy, -2);
						Actor_Clue_Acquire(kActorMcCoy, kClueHasanInterview, false, kActorHasan);
						Actor_Modify_Friendliness_To_Other(kActorHasan, kActorMcCoy, -2);
					} else {
						Actor_Says(kActorMcCoy, 8525, 13);
					}			
				}
				Game_Flag_Set(kFlagAR02HassanTalk);
				return true;
			}
			dialogueWithHassan();
		}
	}

	if (_vm->_cutContent) {
		if (actorId == kActorHasan
		    && Global_Variable_Query(kVariableChapter) > 2) {

			if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -240.79f, 0.0f, -1328.89f, 12, true, false, false)) {
				Actor_Face_Actor(kActorMcCoy, kActorHasan, true);
				Actor_Face_Actor(kActorHasan, kActorMcCoy, true);

				if ((Actor_Clue_Query(kActorMcCoy, kClueStrangeScale1)
				|| Actor_Clue_Query(kActorMcCoy, kClueStrangeScale2))
				&& !Game_Flag_Query(kFlagWrongInvestigation)
				) {
					dialogueWithHassan();
				} else if (!Actor_Clue_Query(kActorMcCoy, kClueHasanInterview)
				) {
					dialogueWithHassan();
				} else if (!Game_Flag_Query(kFlagHasanTalkFinished)) {
					if (Actor_Query_Friendliness_To_Other(kActorHasan, kActorMcCoy) > 50) {
						Actor_Says(kActorMcCoy, 155, 13); // How's business?
						Actor_Says(kActorHasan, 10, 13); //20-0010.AUD	Well enough, noble one, to keep a humble merchant in bread and water.
						Actor_Says(kActorHasan, 20, 14); //20-0020.AUD	So few people realize what a bargain these lovely serpents are.
						Delay (1000);
						Actor_Says(kActorMcCoy, 6980, 13); // What's the word
						Actor_Says(kActorHasan, 290, 13);
						Actor_Says(kActorHasan, 300, 14);
						Actor_Says(kActorHasan, 310, 13);
						Game_Flag_Set(kFlagHasanTalkFinished);
						Item_Pickup_Spin_Effect_From_Actor(kModelAnimationGarterSnake, kActorHasan, 0, -40);
						if (!Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
							Actor_Voice_Over(1860, kActorVoiceOver); //99-1860.AUD	No self-respecting human would own one of those frauds.
							Actor_Modify_Friendliness_To_Other(kActorHasan, kActorMcCoy, -2);
						} else {
							dialogueWithHassanBuySnake();
						}
					} else {
						Actor_Says(kActorMcCoy, 8915, 14); // You got a minute, pal?
						Actor_Says(kActorHasan, 260, 14); // My time is quite valuable, noble one
						Game_Flag_Set(kFlagHasanTalkFinished);
					}
				} else { 
					if (Actor_Query_Friendliness_To_Other(kActorHasan, kActorMcCoy) > 50) {
						Actor_Says(kActorMcCoy, 1315, 13);		
					} else {
						Actor_Says(kActorMcCoy, 8595, 13); //00-8595.AUD	Hmm. He's damn unfriendly.				
					}
				}
			}
		}
	}
	return false;
}

bool SceneScriptAR02::ClickedOnItem(int itemId, bool a2) {
	if (itemId == kItemScorpions) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -386.96f, 0.0f, -1078.45f, 12, true, false, false)) {
			Actor_Face_Actor(kActorMcCoy, kActorInsectDealer, true);
			if (_vm->_cutContent) {
				if (!Game_Flag_Query(kFlagAR02ScorpionsChecked)) {
					if (Actor_Query_Friendliness_To_Other(kActorInsectDealer, kActorMcCoy) < 50) {
						Actor_Says(kActorMcCoy, 65, 21);
						Actor_Says(kActorInsectDealer, 0, 14); // 16-0000.AUD	Careful, señor. They are poison.
						Actor_Says(kActorMcCoy, 70, 19); //00-0070.AUD	I ain't feeling so good.
						Actor_Says(kActorInsectDealer, 50, 14); //16-0050.AUD	If you're not dead already, you will live.
						Delay(1000);
						Actor_Voice_Over(4180, kActorVoiceOver); //99-4180.AUD	Scorpions.
						Actor_Says(kActorInsectDealer, 190, 14); //16-0190.AUD	Sí, good products. Scorpions my best work. Finest quality. Even poison.
						Actor_Says(kActorMcCoy, 105, 18); //00-0105.AUD	Isn't that illegal?
						Actor_Says(kActorInsectDealer, 200, 14); //16-0200.AUD	I have permit, señor. My customers demand authenticity.
						Actor_Says(kActorMcCoy, 3910, 14); //00-3910.AUD	You’re lying
						Actor_Says(kActorInsectDealer, 420, 14); //16-0420.AUD	Believe what you will, señor. But I speak the truth.
						Actor_Says(kActorMcCoy, 7835, 18); //00-7835.AUD	Is that so?
						if (Global_Variable_Query(kVariableChapter) < 4) {
							Actor_Says(kActorMcCoy, 1955, 14); //00-1955.AUD	We’re taking a little drive downtown.
							Game_Flag_Set(kFlagAR02StungByScorpion);
							Game_Flag_Set(kFlagInsectDealerArrested);
							Music_Stop(1u);
							Delay (1000);
							Item_Remove_From_World(kItemScorpions);
							Actor_Put_In_Set(kActorInsectDealer, kSetPS09);
							Actor_Set_At_XYZ(kActorInsectDealer, -300.0f, 0.33f, -280.0f, 512);
							Game_Flag_Reset(kFlagSpinnerAtAR01);
							Game_Flag_Set(kFlagSpinnerAtPS01);
							Game_Flag_Reset(kFlagMcCoyInAnimoidRow);
							Game_Flag_Set(kFlagMcCoyInPoliceStation);
							Outtake_Play(kOuttakeAway1, true, -1);
							Set_Enter(kSetPS09, kScenePS09);
						}
					} else {	
						Actor_Says(kActorInsectDealer, 0, 14); 
						Actor_Says(kActorMcCoy, 55, 18);
						Actor_Says(kActorInsectDealer, 10, 14);
						if (Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
							Actor_Says(kActorMcCoy, 60, 18); //00-0060.AUD	I don't think so. They are beautiful, though. I never seen one before.
							Actor_Says(kActorInsectDealer, 20, 14);
						} else {
							Actor_Says(kActorMcCoy, 8980, 16); //00-8980.AUD	No, thanks, I'm saving for a rainy day.
						}
						Game_Flag_Set(kFlagAR02ScorpionsChecked);
					}
				} else if ( Game_Flag_Query(kFlagAR02ScorpionsChecked)
				&& !Game_Flag_Query(kFlagAR02StungByScorpion)) {
					Actor_Says(kActorMcCoy, 65, 21);
					Actor_Says(kActorInsectDealer, 30, 14);
					Actor_Says(kActorInsectDealer, 40, 14);
					Actor_Says(kActorMcCoy, 70, 18);
					Actor_Says(kActorInsectDealer, 50, 14);
					Game_Flag_Set(kFlagAR02StungByScorpion);
				} else {
					Actor_Says(kActorMcCoy, 8527, 14);
				}
			} else if (!Game_Flag_Query(kFlagAR02ScorpionsChecked)) {
				Actor_Says(kActorInsectDealer, 0, 14);
				Actor_Says(kActorMcCoy, 55, 18);
				Actor_Says(kActorInsectDealer, 10, 14);
				Actor_Says(kActorMcCoy, 60, 18);
				Actor_Says(kActorInsectDealer, 20, 14);
				Game_Flag_Set(kFlagAR02ScorpionsChecked);
			} else if ( Game_Flag_Query(kFlagAR02ScorpionsChecked)
			        && !Game_Flag_Query(kFlagAR02StungByScorpion)
			) {
				Actor_Says(kActorMcCoy, 65, 21);
				Actor_Says(kActorInsectDealer, 30, 14);
				Actor_Says(kActorInsectDealer, 40, 14);
				Actor_Says(kActorMcCoy, 70, 18);
				Actor_Says(kActorInsectDealer, 50, 14);
				Game_Flag_Set(kFlagAR02StungByScorpion);
			} else {
				Actor_Says(kActorMcCoy, 8527, 14);
			}
			return true;
		}
	}
	return false;
}

bool SceneScriptAR02::ClickedOnExit(int exitId) {
	if (exitId == 0) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -182.0f, 0.0f, -551.0f, 0, true, false, false)) {
			Game_Flag_Set(kFlagAR02toAR01);
			Async_Actor_Walk_To_XYZ(kActorMcCoy, -182.0f, 0.0f, -407.0f, 0, false);
			Set_Enter(kSetAR01_AR02, kSceneAR01);
		}
		return true;
	}

	if (exitId == 1) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -465.0f, 0.0f, -799.0f, 0, true, false, false)) {
			Loop_Actor_Walk_To_XYZ(kActorMcCoy, -560.0f, 0.0f, -799.0f, 0, false, false, false);
			Game_Flag_Set(kFlagAR02toRC03);
			Game_Flag_Reset(kFlagMcCoyInAnimoidRow);
			Game_Flag_Set(kFlagMcCoyInRunciters);
			Music_Stop(3u);
			Set_Enter(kSetRC03, kSceneRC03);
		}
		return true;
	}
	return false;
}

bool SceneScriptAR02::ClickedOn2DRegion(int region) {
	return false;
}

void SceneScriptAR02::SceneFrameAdvanced(int frame) {
}

void SceneScriptAR02::ActorChangedGoal(int actorId, int newGoal, int oldGoal, bool currentSet) {
}

void SceneScriptAR02::PlayerWalkedIn() {
	// This is the scene that plays after McCoy tries to convince Crystal offscreen about Izo not being involved in weapons smuggling.
	if (Actor_Query_Goal_Number(kActorSteele) == kGoalSteeleRC03GoToAR02) {
		Actor_Change_Animation_Mode(kActorSteele, kAnimationModeIdle);
		Actor_Face_Actor(kActorMcCoy, kActorSteele, true);
		Actor_Face_Actor(kActorSteele, kActorMcCoy, true);			
		if (Actor_Query_Friendliness_To_Other(kActorSteele, kActorMcCoy) > 50) {
			Actor_Says(kActorSteele, 1780, 14); //01-1780.AUD	(sigh) Sorry I missed all the laughs.
			Actor_Says(kActorMcCoy, 3825, 15); //00-3825.AUD	Next time.
			Actor_Says(kActorMcCoy, 5260, 18); //00-5260.AUD	Happy trails, Steele.
			Actor_Says(kActorSteele, 2350, 16);  //01-2350.AUD	Ditto.
		} else {
			Actor_Says(kActorSteele, 1800, 16); //01-1800.AUD	You should have waited for me, Slim.
			Actor_Says(kActorMcCoy, 2305, 15); //00-2305.AUD	I’m sorry.
			Actor_Says(kActorSteele, 1990, 15); //01-1990.AUD	A little word of advice, Slim. Stay out of my way.
		}
		Loop_Actor_Walk_To_XYZ(kActorSteele, -700.99, 0.74, -916.12, 48, false, true, false);
		Actor_Set_Goal_Number(kActorSteele, kGoalSteeleLeaveRC03);
		Player_Gains_Control();
		Scene_Exits_Enable();
		return; // true;
	}

	if (Game_Flag_Query(kFlagRC03toAR02)) {
		Loop_Actor_Walk_To_XYZ(kActorMcCoy, -465.0f, 0.0f, -799.0f, 0, false, false, false);
		Game_Flag_Reset(kFlagRC03toAR02);
	}
	Game_Flag_Set(kFlagAR02Entered);
}

void SceneScriptAR02::PlayerWalkedOut() {
	Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
	Ambient_Sounds_Remove_All_Looping_Sounds(1u);
}

void SceneScriptAR02::DialogueQueueFlushed(int a1) {
}

void SceneScriptAR02::dialogueWithInsectDealer1() {
	Dialogue_Menu_Clear_List();
	if (_vm->_cutContent) {
		if (Global_Variable_Query(kVariableChapter) < 4) {
			if (Actor_Clue_Query(kActorMcCoy, kClueDragonflyEarring)
	   		|| Actor_Clue_Query(kActorMcCoy, kClueBombingSuspect)) {
				DM_Add_To_List_Never_Repeat_Once_Selected(490, 3, 5, 5); // EARRING
			}
		}
	} else if (Actor_Clue_Query(kActorMcCoy, kClueDragonflyEarring)
	    || Actor_Clue_Query(kActorMcCoy, kClueBombingSuspect)
	) {
		DM_Add_To_List_Never_Repeat_Once_Selected(490, 3, 5, 5); // EARRING
	}
	if (Actor_Clue_Query(kActorMcCoy, kClueDragonflyAnklet)
	    && !Actor_Clue_Query(kActorMcCoy, kClueDragonflyEarring)
	    && !Actor_Clue_Query(kActorMcCoy, kClueBombingSuspect)
	) {
		DM_Add_To_List_Never_Repeat_Once_Selected(500, 3, 5, 5); // ANKLET
	}
	if (!_vm->_cutContent) {
		DM_Add_To_List_Never_Repeat_Once_Selected(510, 8, 3, -1); // MERCHANDISE
	}
	Dialogue_Menu_Add_DONE_To_List(520); // DONE

	Dialogue_Menu_Appear(320, 240);
	int answerValue = Dialogue_Menu_Query_Input();
	Dialogue_Menu_Disappear();

	switch (answerValue) {
	case 490: // EARRING
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
				Actor_Says(kActorMcCoy, 8475, 12); //00-8475.AUD	Nice looking creatures you have around here.
				Actor_Says(kActorInsectDealer, 10, 12); // 16-0010.AUD	Sí. Finest quality. Perhaps you purchase one?
				Actor_Says(kActorMcCoy, 35, 15); //00-0035.AUD	I'll pass.
			}
			Actor_Says(kActorMcCoy, 335, 23);
			Delay (1000);
			Actor_Says(kActorInsectDealer, 410, 13); //	Ah, perhaps you should ask someone else.
			Actor_Says(kActorMcCoy, 1620, 13);  //00-1620.AUD	I’m not gonna hurt you.
			Actor_Says(kActorInsectDealer, 450, 13); // 16-0450.AUD	I know nothing except the value of simple insects.		
			if (Player_Query_Agenda() == kPlayerAgendaSurly
			|| Player_Query_Agenda() == kPlayerAgendaErratic) { 
				Actor_Says(kActorMcCoy, 8450, 23); // Does this badge mean anything to you?
				Actor_Says(kActorInsectDealer, 440, 14); // Please, this is all I know.
				Actor_Says(kActorMcCoy, 8519, 14);//00-8519.AUD	What do you say we dish each other the straight goods.
				Actor_Says(kActorInsectDealer, 430, 14); //16-0430.AUD	I did not mean to offend. I only thought to spare you from the truth of it.
				Actor_Says(kActorMcCoy, 8455, 14); //00-8455.AUD	Let me judge what's gonna make me upset.	 		
				Actor_Says(kActorInsectDealer, 380, 14); //16-0380.AUD	You promised no hurt!
				Actor_Says(kActorMcCoy, 745, 14); //00-0745.AUD	I'm watching you, pal.
				Actor_Modify_Friendliness_To_Other(kActorInsectDealer, kActorMcCoy, -2);
			} else {
				if (Actor_Clue_Query(kActorMcCoy, kClueDragonflyAnklet)
				||  Actor_Clue_Query(kActorMcCoy, kClueBombingSuspect)) {
					Actor_Says(kActorMcCoy, 7940, 13); //00-7940.AUD	Right.
					Delay (1000);
					Actor_Says(kActorMcCoy, 8470, 23); //00-8470.AUD	You recognize the insect in this photo?
				} else {
					Actor_Says(kActorMcCoy, 7940, 13); //00-7940.AUD	Right.
					Delay (1000);
					Actor_Says(kActorMcCoy, 8465, 23); //00-8465.AUD	What kind of insect is this?
				}
				Actor_Says(kActorInsectDealer, 80, 14);
				Actor_Says(kActorMcCoy, 80, 16);
				Actor_Says(kActorInsectDealer, 90, 12);
				Actor_Says(kActorMcCoy, 85, 17);
				Actor_Says(kActorInsectDealer, 100, 14);
				Actor_Says(kActorInsectDealer, 110, 12); //16-0110.AUD	Very rare, señor. Estate item and most likely part of large collection.
				if (_vm->_cutContent) {
					Actor_Says(kActorMcCoy, 8517, kAnimationModeTalk); //00-8517.AUD	But how do you know?
				}
				Actor_Says(kActorInsectDealer, 120, 12);
				Actor_Says(kActorMcCoy, 90, 13); //00-0090.AUD	More than I can afford.
				Actor_Says(kActorInsectDealer, 130, 12);
				Actor_Says(kActorInsectDealer, 140, 14);
				Actor_Says(kActorMcCoy, 95, 15); //00-0095.AUD	If this is from a collection I'm also looking for the other pieces.
				Actor_Says(kActorInsectDealer, 150, 12);
				Actor_Says(kActorInsectDealer, 160, 13); //16-0160.AUD	then you buy a piece, right? For special lady friend?
				Actor_Says(kActorInsectDealer, 170, 14); //16-0170.AUD	You come back later.
				if (_vm->_cutContent) {
					if (Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
						Actor_Says(kActorMcCoy, 100, 16); //00-0100.AUD	I'll do that.
						Actor_Says(kActorInsectDealer, 180, 13); //16-0180.AUD	Ah, you take care chasing the Dragon.
					} else {
						Actor_Says(kActorMcCoy, 7980, 19); //00-7980.AUD	Yeah. Maybe.
						Actor_Says(kActorInsectDealer, 170, 14); //16-0170.AUD	You come back later.
					}
				} else {
					Actor_Says(kActorInsectDealer, 170, 14); //16-0170.AUD	You come back later.
					Actor_Says(kActorMcCoy, 100, 16); //00-0100.AUD	I'll do that.
					Actor_Says(kActorInsectDealer, 180, 13); //16-0180.AUD	Ah, you take care chasing the Dragon.
				}
				Game_Flag_Set(kFlagAR02InsectDealerInterviewed);
				Actor_Clue_Acquire(kActorMcCoy, kCluePeruvianLadyInterview, true, kActorInsectDealer);
			}
		} else {
			Actor_Says(kActorMcCoy, 145, 15);
			Actor_Says(kActorInsectDealer, 80, 14);
			Actor_Says(kActorMcCoy, 80, 16);
			Actor_Says(kActorInsectDealer, 90, 12);
			Actor_Says(kActorMcCoy, 85, 17);
			Actor_Says(kActorInsectDealer, 100, 14);
			Actor_Says(kActorInsectDealer, 110, 12);
			Actor_Says(kActorInsectDealer, 120, 12);
			Actor_Says(kActorMcCoy, 90, 13);
			Actor_Says(kActorInsectDealer, 130, 12);
			Actor_Says(kActorInsectDealer, 140, 14);
			Actor_Says(kActorMcCoy, 95, 15);
			Actor_Says(kActorInsectDealer, 150, 12);
			Actor_Says(kActorInsectDealer, 160, 13);
			Actor_Says(kActorInsectDealer, 170, 14);
			Actor_Says(kActorMcCoy, 100, 16);
			Actor_Says(kActorInsectDealer, 180, 13);
			Game_Flag_Set(kFlagAR02InsectDealerInterviewed);
			Actor_Clue_Acquire(kActorMcCoy, kCluePeruvianLadyInterview, true, kActorInsectDealer);
		}
		break;

	case 510: // MERCHANDISE
		Actor_Says(kActorMcCoy, 8475, 12);
		Actor_Says(kActorInsectDealer, 190, 12);
		Actor_Says(kActorMcCoy, 105, 15);
		Actor_Says(kActorInsectDealer, 200, 14);
		break;

	case 520: // DONE
		if (_vm->_cutContent) {
			if (Actor_Query_Friendliness_To_Other(kActorHasan, kActorMcCoy) > 49) {
				Actor_Says(kActorMcCoy, 215, 16); // Thanks for your help.
			} else {
				Actor_Says(kActorMcCoy, 8940, 18); //00-8940.AUD	What are you staring at?
			}
		} else {
			Actor_Says(kActorMcCoy, 215, 16); // Thanks for your help.
		}
		break;
	}
}

void SceneScriptAR02::dialogueWithInsectDealerBuyBracelet() {
	Dialogue_Menu_Clear_List();

	if (_vm->_cutContent) {
		Dialogue_Menu_Clear_Never_Repeat_Was_Selected_Flag(530);
		Dialogue_Menu_Clear_Never_Repeat_Was_Selected_Flag(540);
	}

	if (Global_Variable_Query(kVariableChinyen) >= 15
	|| Query_Difficulty_Level() == kGameDifficultyEasy) {
		if (Player_Query_Agenda() != kPlayerAgendaSurly 
		&& Player_Query_Agenda() != kPlayerAgendaErratic) {
			DM_Add_To_List_Never_Repeat_Once_Selected(530, 7, 5, 3); // BUY
		} else {
			DM_Add_To_List_Never_Repeat_Once_Selected(540, 3, 5, 7); // NO THANKS
		}
	} else {
		DM_Add_To_List_Never_Repeat_Once_Selected(540, 3, 5, 7); // NO THANKS
	}

	Dialogue_Menu_Appear(320, 240);
	int answerValue = Dialogue_Menu_Query_Input();
	Dialogue_Menu_Disappear();

	if (answerValue == 530) { // BUY
		Actor_Says(kActorMcCoy, 120, 12);
		if (Query_Difficulty_Level() != kGameDifficultyEasy) {
			Global_Variable_Decrement(kVariableChinyen, 15);
		}
		Actor_Clue_Acquire(kActorMcCoy, kClueMaggieBracelet, true, kActorInsectDealer);
		if (!_vm->_cutContent) {
			Actor_Modify_Friendliness_To_Other(kActorInsectDealer, kActorMcCoy, 5);
		} else {
			Actor_Modify_Friendliness_To_Other(kActorInsectDealer, kActorMcCoy, 2);
		}
	} else if (answerValue == 540) { // NO THANKS
		Actor_Says(kActorMcCoy, 125, 13);
		Actor_Says(kActorInsectDealer, 260, kAnimationModeTalk);
		Actor_Says(kActorMcCoy, 130, 15);
		Actor_Says(kActorInsectDealer, 270, kAnimationModeTalk);
		Actor_Says(kActorInsectDealer, 280, kAnimationModeTalk);
		if (_vm->_cutContent) {
			if (Player_Query_Agenda() != kPlayerAgendaSurly 
			&& Player_Query_Agenda() != kPlayerAgendaErratic) {
				Actor_Says(kActorMcCoy, 135, 11);
			}
		} else {
			Actor_Says(kActorMcCoy, 135, 11);
		}
		if (!_vm->_cutContent) {
			Actor_Modify_Friendliness_To_Other(kActorInsectDealer, kActorMcCoy, -5);
		}
	}
}

/**
* This is only for cut content (purchasing the Electric Slug)
*/
void SceneScriptAR02::dialogueWithInsectDealerBuySlug() {
	Dialogue_Menu_Clear_List();

	Dialogue_Menu_Clear_Never_Repeat_Was_Selected_Flag(530);
	Dialogue_Menu_Clear_Never_Repeat_Was_Selected_Flag(540);

	if (Global_Variable_Query(kVariableChinyen) >= 125
	|| Query_Difficulty_Level() == kGameDifficultyEasy) {
		if (Player_Query_Agenda() != kPlayerAgendaSurly 
		&& Player_Query_Agenda() != kPlayerAgendaErratic) {
			DM_Add_To_List_Never_Repeat_Once_Selected(530, 7, 5, 3); // BUY
		} else {
			DM_Add_To_List_Never_Repeat_Once_Selected(540, 3, 5, 7); // NO THANKS
		}
	} else {
		DM_Add_To_List_Never_Repeat_Once_Selected(540, 3, 5, 7); // NO THANKS
	}

	Dialogue_Menu_Appear(320, 240);
	int answerValue = Dialogue_Menu_Query_Input();
	Dialogue_Menu_Disappear();

	if (answerValue == 530) { // BUY
		Actor_Says(kActorMcCoy, 7000, 23);
		if (Query_Difficulty_Level() != kGameDifficultyEasy) {
			Global_Variable_Decrement(kVariableChinyen, 125);
		}
		Actor_Clue_Acquire(kActorMcCoy, kClueSlug, true, kActorInsectDealer);
		Actor_Modify_Friendliness_To_Other(kActorInsectDealer, kActorMcCoy, 2);
	} else if (answerValue == 540) { // NO THANKS
		Actor_Says(kActorMcCoy, 7005, 13);
	}
}

void SceneScriptAR02::dialogueWithHassan() {
	Dialogue_Menu_Clear_List();
	if (_vm->_cutContent) {
		if (Global_Variable_Query(kVariableChapter) < 4) {
			if (Actor_Clue_Query(kActorMcCoy, kClueStrangeScale1)
			|| Actor_Clue_Query(kActorMcCoy, kClueStrangeScale2)) {
				DM_Add_To_List_Never_Repeat_Once_Selected(550, 8, 5, 2); // SCALE
			}
		}
	} else if (Actor_Clue_Query(kActorMcCoy, kClueStrangeScale1)) {
		DM_Add_To_List_Never_Repeat_Once_Selected(550, 8, 5, 2); // SCALE
	}
	if (_vm->_cutContent) {
		if (Global_Variable_Query(kVariableChapter) < 4) {
			if (Actor_Clue_Query(kActorMcCoy, kClueBobRobbed)) {
				if (Player_Query_Agenda() == kPlayerAgendaSurly 	
				|| Player_Query_Agenda() == kPlayerAgendaErratic 
				|| Player_Query_Agenda() == kPlayerAgendaUserChoice) {
					DM_Add_To_List_Never_Repeat_Once_Selected(1250, -1, -1, 10); // ARREST
				}
			}
		}
	}
	if (!_vm->_cutContent) {
		if (Global_Variable_Query(kVariableChapter) < 4) {
			if (!Actor_Clue_Query(kActorMcCoy, kCluePeruvianLadyInterview)) {
				DM_Add_To_List_Never_Repeat_Once_Selected(560, 6, 5, 7); // EARRING
			}
		}
	} else {
		if (!Actor_Clue_Query(kActorMcCoy, kCluePeruvianLadyInterview)) {
			DM_Add_To_List_Never_Repeat_Once_Selected(560, 6, 5, 7); // EARRING
		}
	}
	Dialogue_Menu_Add_DONE_To_List(570); // DONE

	Dialogue_Menu_Appear(320, 240);
	int answerValue = Dialogue_Menu_Query_Input();
	Dialogue_Menu_Disappear();

	switch (answerValue) {
	case 550: // SCALE
		Actor_Says(kActorMcCoy, 145, 23); // This your work?
		// Made it so the conversation with Hasan will play out differently depending on your friendliness with him.
		// Firstly if you have low friendliness towards Hasan he lies to you and says he knows nothing.
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagAR02HassanTalk)) {
				if (Actor_Query_Friendliness_To_Other(kActorHasan, kActorMcCoy) > 50) {
					Actor_Says(kActorHasan, 40, 12); //20-0040.AUD	I told the last detective I sold the snake to Taffy Lewis.
					Actor_Says(kActorMcCoy, 165, 13); //00-0165.AUD	The last detective?
					Delay(1000);
					Actor_Says(kActorMcCoy, 4130, kAnimationModeTalk); //00-4130.AUD	Anything else?
					Actor_Says(kActorHasan, 240, 14); //20-0240.AUD	In truth this humble merchant has discovered a fact surely to be of interest to you.
					Actor_Says(kActorHasan, 50, 13); //20-0050.AUD	His name was Deckard.
					Actor_Says(kActorMcCoy, 170, 19); //00-0170.AUD	Damn.
					Actor_Says(kActorHasan, 60, 11); //20-0060.AUD	What's the problem, noble one?
					Actor_Says(kActorMcCoy, 175, 16); //00-0175.AUD	I think I've been following up on someone else's case.
				} else {
					Actor_Says(kActorHasan, 250, 14);  //20-0250.AUD	I'm afraid not, noble one. But you shall surely be the first to know, if I do hear something.
					Actor_Says(kActorMcCoy, 3910, 16); //00-3910.AUD	You’re lying.
					Actor_Says(kActorHasan, 270, 11); //20-0270.AUD	You sully my good name with such accusations. I speak only the truth, I swear!
					if (Player_Query_Agenda() == kPlayerAgendaSurly 	
					|| Player_Query_Agenda() == kPlayerAgendaErratic) {
						Actor_Says(kActorMcCoy, 8519, 14);//00-8519.AUD	What do you say we dish each other the straight goods.
						Delay (1000);
						Actor_Says(kActorHasan, 280, 13); //20-0280.AUD	Oh, yes, now I remember. I misspoke before, that is all. Here's the truth of it.
						Actor_Says(kActorMcCoy, 2635, 18); //00-2635.AUD	I’m all ears.
						Actor_Says(kActorHasan, 40, 12); //20-0040.AUD	I told the last detective I sold the snake to Taffy Lewis.
						Actor_Says(kActorMcCoy, 165, 13); //00-0165.AUD	The last detective?
						Delay(1000);
						Actor_Says(kActorMcCoy, 4130, kAnimationModeTalk); //00-4130.AUD	Anything else?
						Actor_Says(kActorHasan, 50, 13); //20-0050.AUD	His name was Deckard.
						Actor_Says(kActorMcCoy, 170, 19); //00-0170.AUD	Damn.
						Actor_Says(kActorMcCoy, 175, 16); //00-0175.AUD	I think I've been following up on someone else's case.
						Actor_Modify_Friendliness_To_Other(kActorHasan, kActorMcCoy, -2);			
					}
				}
			}
		}
		Game_Flag_Set(kFlagWrongInvestigation);
		break;

	case 560: // EARRING
		if (_vm->_cutContent) {
			Actor_Says(kActorMcCoy, 4270, 18); //00-4270.AUD	I got some more questions for you.
			Actor_Says(kActorMcCoy, 150, 11); //00-0150.AUD	You know anything about insects?
			if (Actor_Query_Friendliness_To_Other(kActorHasan, kActorMcCoy) < 50) {
				Actor_Says(kActorHasan, 250, 11); //20-0250.AUD	I'm afraid not, noble one. But you shall surely be the first to know, if I do hear something.
			} else {				
				Actor_Says(kActorHasan, 140, 14); 
				Actor_Says(kActorMcCoy, 185, 13);
				Actor_Says(kActorHasan, 150, 12);
				Actor_Says(kActorHasan, 160, 13);
				Actor_Says(kActorMcCoy, 190, 16);
				Actor_Says(kActorHasan, 170, 12);
				Actor_Says(kActorMcCoy, 195, 15);
				Actor_Says(kActorHasan, 180, 12);
				Actor_Says(kActorHasan, 190, 13);
				Actor_Says(kActorHasan, 200, 11);
				Actor_Says(kActorMcCoy, 200, 13);
				Actor_Says(kActorHasan, 210, 11); // Perhaps you should ask the Peruvian woman next door.
				Actor_Says(kActorHasan, 220, 14); // She's an expert on such things
				Actor_Says(kActorHasan, 230, 13); // and will cut a wonderful deal to friends.
				if (Actor_Query_Friendliness_To_Other(kActorInsectDealer, kActorMcCoy) < 50) {
					Actor_Says(kActorMcCoy, 8640, 14); // 00-8640.AUD	That's useless.
					Actor_Says(kActorHasan, 60, 11); //20-0060.AUD	What's the problem, noble one?
					Actor_Says(kActorMcCoy, 1535, 15); //00-1535.AUD	Ah, never mind.
				} else {
					Actor_Says(kActorMcCoy, 5150, 18); //00-5150.AUD	One more thing.
					Actor_Says(kActorMcCoy, 8615, 16);	//00-8615.AUD	Heard anything on the street?
					Actor_Says(kActorHasan, 290, 12);	//20-0290.AUD	I have heard nothing of late, noble one.
				}
			}
		} else {
			Actor_Says(kActorMcCoy, 150, 11);
			Actor_Says(kActorHasan, 140, 11);
			Actor_Says(kActorMcCoy, 185, 11);
			Actor_Says(kActorHasan, 150, 11);
			Actor_Says(kActorHasan, 160, 11);
			Actor_Says(kActorMcCoy, 190, 11);
			Actor_Says(kActorHasan, 170, 11);
			Actor_Says(kActorMcCoy, 195, 11);
			Actor_Says(kActorHasan, 180, 11);
			Actor_Says(kActorHasan, 190, 11);
			Actor_Says(kActorHasan, 200, 11);
			Actor_Says(kActorMcCoy, 200, 11);
			Actor_Says(kActorHasan, 210, 11); // Perhaps you should ask the Peruvian woman next door.
			Actor_Says(kActorHasan, 220, 11); // She's an expert on such things
			Actor_Says(kActorHasan, 230, 11); // and will cut a wonderful deal to friends.
		}
		break;
	// This is the code for the arrest option for Hasan.
	case 1250:
		Actor_Says(kActorMcCoy, 7930, 14); //00-7930.AUD	Stay right where you are.
		Actor_Says(kActorHasan, 60, 11); //20-0060.AUD	What's the problem, noble one?
		Actor_Says(kActorMcCoy, 1955, 14); //00-1955.AUD	We’re taking a little drive downtown.
		Game_Flag_Set(kFlagHasanArrested);
		Music_Stop(1u);
		Delay(1000);
		Actor_Put_In_Set(kActorHasan, kSetPS09);
		Actor_Set_At_XYZ(kActorHasan, -300.0f, 0.33f, -330.0f, 512);
		Game_Flag_Reset(kFlagSpinnerAtAR01);
		Game_Flag_Set(kFlagSpinnerAtPS01);
		Game_Flag_Reset(kFlagMcCoyInAnimoidRow);
		Game_Flag_Set(kFlagMcCoyInPoliceStation);
		Outtake_Play(kOuttakeAway1, true, -1);
		Set_Enter(kSetPS09, kScenePS09);
		break;

	case 570: // DONE
		// This time around Hasan will only get angry with McCoy and tell him about Bob if they have low friendliness with each other.
		if (_vm->_cutContent) {
			if (!Actor_Clue_Query(kActorMcCoy, kClueHasanInterview)) {
				Actor_Says(kActorMcCoy, 940, 13);
				// Quote 80 is *boop* in ENG and DEU versions
				// In FRA, ITA versions it is identical to the second half of quote 70, and thus redundant
				// In ESP version it is the missing second half of quote 70, and is required!
				if (_vm->_cutContent
					&& _vm->_language == Common::ES_ESP
				) {
					Actor_Says_With_Pause(kActorHasan, 70, 0.0f, 12);
					Actor_Says(kActorHasan, 80, kAnimationModeTalk);
				} else {
					Actor_Says(kActorHasan, 70, 12);//20-0070.AUD	Certainly the LPD must have better things to do than to question a humble merchant over and over again about the same things.
				}
				Actor_Says(kActorHasan, 90, 12);//20-0090.AUD	Why aren't you out arresting criminals like that disreputable Bob fellow.
				// Made it so McCoy only questions who Bob is and is directed to Bobs shop only if McCoy hasn't Met Bob.
				if (!Game_Flag_Query(kFlagRC04Entered)) {
					Actor_Says(kActorMcCoy, 180, 15); //00-0180.AUD	Bob?
				}
				Actor_Says(kActorHasan, 100, 14); //20-0100.AUD	He owns the armament shop up the street. He is insane, noble one. Insane.
				Actor_Says(kActorHasan, 110, 12);
				// Quote 130 is *boop* in ENG and DEU versions
				// In FRA, ITA versions it is identical to the second half of quote 120, and thus redundant
				// In ESP version it is the missing second half of quote 120, and is required!
				if (_vm->_cutContent
					&& _vm->_language == Common::ES_ESP
				) {
					Actor_Says_With_Pause(kActorHasan, 120, 0.0f, 13);
					Actor_Says(kActorHasan, 130, kAnimationModeTalk);
				} else {
					Actor_Says(kActorHasan, 120, 13);
				}
				Actor_Modify_Friendliness_To_Other(kActorHasan, kActorMcCoy, -2);
				Actor_Clue_Acquire(kActorMcCoy, kClueHasanInterview, false, kActorHasan);
			} else {					
				if (Actor_Query_Friendliness_To_Other(kActorHasan, kActorMcCoy) > 49) {
					Actor_Says(kActorMcCoy, 1315, 11); // Thanks for your time
				} else {
					Actor_Says(kActorMcCoy, 8595, 13); //00-8595.AUD	Hmm. He's damn unfriendly.
				}
			}
		} else {
			if (!Actor_Clue_Query(kActorMcCoy, kClueHasanInterview)) {
				Actor_Says(kActorMcCoy, 940, 13);
				Actor_Says(kActorHasan, 70, 12);//20-0070.AUD	Certainly the LPD must have better things to do than to question a humble merchant over and over again about the same things.
				Actor_Says(kActorHasan, 90, 12);//20-0090.AUD	Why aren't you out arresting criminals like that disreputable Bob fellow.
				Actor_Says(kActorMcCoy, 180, 15); //00-0180.AUD	Bob?
				Actor_Says(kActorHasan, 100, 14); //20-0100.AUD	He owns the armament shop up the street. He is insane, noble one. Insane.
				Actor_Says(kActorHasan, 110, 12);
				Actor_Says(kActorHasan, 120, 13);
				Actor_Clue_Acquire(kActorMcCoy, kClueHasanInterview, false, kActorHasan);
				Actor_Modify_Friendliness_To_Other(kActorHasan, kActorMcCoy, -1);
			} else {
				Actor_Says(kActorMcCoy, 1315, 11); // Thanks for your time
			}
		}
		break;
	}
}

/**
* This is only for cut content (purchasing the Garter Snake)
*/
void SceneScriptAR02::dialogueWithHassanBuySnake() {
	Dialogue_Menu_Clear_List();

	Dialogue_Menu_Clear_Never_Repeat_Was_Selected_Flag(530);
	Dialogue_Menu_Clear_Never_Repeat_Was_Selected_Flag(540);

	if (Global_Variable_Query(kVariableChinyen) >= 175
	    || Query_Difficulty_Level() == kGameDifficultyEasy) {
		if (Player_Query_Agenda() != kPlayerAgendaSurly 
		&& Player_Query_Agenda() != kPlayerAgendaErratic) {
			DM_Add_To_List_Never_Repeat_Once_Selected(530, 7, 5, 3); // BUY
		} else {
			DM_Add_To_List_Never_Repeat_Once_Selected(540, 3, 5, 7); // NO THANKS
		}
	} else {
		DM_Add_To_List_Never_Repeat_Once_Selected(540, 3, 5, 7); // NO THANKS
	}

	Dialogue_Menu_Appear(320, 240);
	int answerValue = Dialogue_Menu_Query_Input();
	Dialogue_Menu_Disappear();

	if (answerValue == 530) { // BUY
		Actor_Says(kActorMcCoy, 7000, 23);
		if (Query_Difficulty_Level() != kGameDifficultyEasy) {
			Global_Variable_Decrement(kVariableChinyen, 175);
		}
		Actor_Clue_Acquire(kActorMcCoy, kClueGarterSnake, true, kActorHasan);
		if (!_vm->_cutContent) {
			Actor_Modify_Friendliness_To_Other(kActorHasan, kActorMcCoy, 5);
		}
	} else if (answerValue == 540) { // NO THANKS
		Actor_Says(kActorMcCoy, 7005, 13);
		if (!_vm->_cutContent) {
			Actor_Modify_Friendliness_To_Other(kActorHasan, kActorMcCoy, -5);
		}
	}
}

} // End of namespace BladeRunner
