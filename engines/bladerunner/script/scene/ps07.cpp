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

void SceneScriptPS07::InitializeScene() {
	Setup_Scene_Information(609.07f, 0.22f, -598.67f, 768);
	Scene_Exit_Add_2D_Exit(0, 610, 0, 639, 479, 1);
	Ambient_Sounds_Remove_All_Non_Looping_Sounds(false);
	Ambient_Sounds_Add_Looping_Sound(kSfxLABAMB3, 80, 0, 1);
	Ambient_Sounds_Add_Sound(kSfxTUBES1,   5, 20,  5, 10,  -70,  70, -101, -101, 0, 0);
	if (_vm->_cutContent) {
		Ambient_Sounds_Add_Sound(kSfxTUBES2,   5, 20,  5, 10,  -70,  70, -101, -101, 0, 0);
		Ambient_Sounds_Add_Sound(kSfxTUBES3,   5, 20,  5, 10,  -70,  70, -101, -101, 0, 0);
	}
	Ambient_Sounds_Add_Sound(kSfxLABMISC1, 5, 30,  5, 10,  -70,  70, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxLABMISC2, 2, 20,  5, 10,  -70,  70, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxLABMISC3, 2, 10, 10, 20,  -70,  70, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxLABMISC4, 2, 10, 10, 20,  -70,  70, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxLABMISC5, 2, 10, 10, 20,  -70,  70, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxLABMISC6, 2, 10, 10, 20,  -70,  70, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxLABMISC7, 2, 30, 10, 15,  -70,  70, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxLABMISC8, 2, 20, 10, 15,  -70,  70, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxLABMISC9, 5, 20, 10, 15,  -70,  70, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxTUBES4,   5, 30,  5,  8, -100, 100, -101, -101, 0, 0);
}

void SceneScriptPS07::SceneLoaded() {
	Obstacle_Object("RICE BOX01", true); // garbage can
	Unobstacle_Object("RICE BOX01", true);
	if (_vm->_cutContent) {
		Unobstacle_Object("L.MOUSE", true);
		Clickable_Object("L.MOUSE");
	}
}

bool SceneScriptPS07::MouseClick(int x, int y) {
	return false;
}

bool SceneScriptPS07::ClickedOn3DObject(const char *objectName, bool a2) {
	if (Object_Query_Click("L.MOUSE", objectName)) { // this object is restored in the scene (buzzer button)
		Sound_Play(kSfxLABBUZZ1, 70, 0, 0, 50);
		if (Actor_Query_Goal_Number(kActorKlein) < kGoalKleinIsAnnoyedByMcCoyInit
		    && Actor_Query_Goal_Number(kActorKlein) > kGoalKleinDefault
		) {
			Actor_Face_Actor(kActorMcCoy, kActorKlein, true);
			Actor_Set_Goal_Number(kActorKlein, kGoalKleinGotoLabSpeaker);
			Actor_Modify_Friendliness_To_Other(kActorKlein, kActorMcCoy, -3);
		}
		return true;
	}
	return false;
}

bool SceneScriptPS07::ClickedOnActor(int actorId) {
	if (actorId == kActorKlein) {
		if (_vm->_cutContent
		    && (Actor_Query_Goal_Number(kActorKlein) >= kGoalKleinIsAnnoyedByMcCoyInit
		        || (Actor_Query_Goal_Number(kActorKlein) < kGoalKleinIsAnnoyedByMcCoyInit
		            && Actor_Query_Friendliness_To_Other(kActorKlein, kActorMcCoy) < 41))
		) {
			// Annoyed Dino ignores McCoy
			return true;
		} else {
			Actor_Face_Actor(kActorMcCoy, kActorKlein, true);
			Actor_Set_Goal_Number(kActorKlein, kGoalKleinGotoLabSpeaker);
			if (!Game_Flag_Query(kFlagPS07KleinTalkClues)) {
				Actor_Says(kActorMcCoy, 4115, 13);
			}

			if (!Game_Flag_Query(kFlagPS07KleinTalkClues)
			    && ((_vm->_cutContent && (Actor_Clue_Query(kActorKlein, kClueShellCasings)
			                              || Actor_Clue_Query(kActorKlein, kClueOfficersStatement)
			                              || Actor_Clue_Query(kActorKlein, kCluePaintTransfer)
			                              || Actor_Clue_Query(kActorKlein, kClueChromeDebris)))
			        || (!_vm->_cutContent && (Game_Flag_Query(kFlagMcCoyHasShellCasings)
			                                  || Game_Flag_Query(kFlagMcCoyHasOfficersStatement)
			                                  || Game_Flag_Query(kFlagMcCoyHasPaintTransfer)
			                                  || Game_Flag_Query(kFlagMcCoyHasChromeDebris))))
			) {
				Actor_Face_Actor(kActorKlein, kActorMcCoy, true);
				if (_vm->_cutContent) {
					if (Actor_Query_Friendliness_To_Other(kActorKlein, kActorMcCoy) > 49) {
						Actor_Says(kActorKlein, 30, 12); //30-0030.AUD	I was wondering when you'd show your mug around here, McCoy.
					}
				} else {
					Actor_Says(kActorKlein, 30, 12); //30-0030.AUD	I was wondering when you'd show your mug around here, McCoy.
				}
				Game_Flag_Set(kFlagPS07KleinTalkClues);
			} else {
				if (Game_Flag_Query(kFlagPS07KleinTalkClues)) {
					Actor_Says(kActorMcCoy, 4130, 18);
				}
			}

			// Restored cut content version uses Clues system. Klein gets the clues if McCoy has uploaded to the mainframe
			// The original version takes a shortcut here and uses flags for this (McCoy does not have to upload the clues to the mainframe)
			if (((_vm->_cutContent && Actor_Clue_Query(kActorKlein, kClueShellCasings))
			      || (!_vm->_cutContent && Game_Flag_Query(kFlagMcCoyHasShellCasings)))
			    && !Game_Flag_Query(kFlagPS07KleinTalkShellCasings)
			) {
				Game_Flag_Set(kFlagPS07KleinTalkShellCasings);
				Actor_Clue_Acquire(kActorMcCoy, kClueLabShellCasings, false, kActorKlein);
				Actor_Says(kActorKlein, 50, 16);
				if (_vm->_cutContent) {
					if (!Actor_Clue_Query(kActorMcCoy, kClueBobInterview1)) {
						Actor_Says(kActorMcCoy, 4135, 13); //00-4135.AUD	How's that?
					}
				} else {
					Actor_Says(kActorMcCoy, 4135, 13);
				} 
				Actor_Says(kActorKlein, 60, 15); //30-0060.AUD	They're from an Ender rifle. It's standard-issue Off-World military hardware.
				if (_vm->_cutContent) {
					if (Actor_Query_Friendliness_To_Other(kActorKlein, kActorMcCoy) < 50) {
						Actor_Says(kActorKlein, 70, 12); //30-0070.AUD	Heavy caliber. That puppy can punch right through a tank.
					}
					if (!Actor_Clue_Query(kActorMcCoy, kClueBobInterview1)) {
						Actor_Says(kActorMcCoy, 4140, 13); //00-4140.AUD	What can I conclude from that?
					}
				} else {
					Actor_Says(kActorKlein, 70, 12); //30-0070.AUD	Heavy caliber. That puppy can punch right through a tank.
					Actor_Says(kActorMcCoy, 4140, 13);
				}
				Actor_Says(kActorKlein, 80, 14);
				Actor_Says(kActorKlein, 90, 14);
				Actor_Set_Goal_Number(kActorKlein, kGoalKleinMovingInLab01);
				return true;
			}
			// Made it so Klein only talks about the animal corpses if McCoy has already seen them and he can talk about the wounds.
			if (((_vm->_cutContent && Game_Flag_Query(kFlagRC02Entered))
			      || (!_vm->_cutContent && Game_Flag_Query(kFlagMcCoyHasOfficersStatement)))
			   		 && !Game_Flag_Query(kFlagPS07KleinTalkOfficersStatement)
			) {
				Game_Flag_Set(kFlagPS07KleinTalkOfficersStatement);
				Actor_Clue_Acquire(kActorMcCoy, kClueLabCorpses, false, kActorKlein);
				Actor_Says(kActorKlein, 100, 13);
				Actor_Says(kActorMcCoy, 4145, 13); //-	00-4145.AUD	Bone marrow?
				//Jake - Added in some extra lines for Klein.
				if (_vm->_cutContent) {
					Actor_Says(kActorKlein, 310, 13); //-	30-0310.AUD	I’m gonna tell it to you straight. But you ain’t gonna like it.
					if (Player_Query_Agenda() != kPlayerAgendaSurly 
					&& Player_Query_Agenda() != kPlayerAgendaErratic) {
						Actor_Says(kActorMcCoy, 620, 18); //-	00-0620.AUD	Try me.
					} else {
						Actor_Says(kActorMcCoy, 8455, 14); //00-8455.AUD	Let me judge what's gonna make me upset.
						Delay(2000);
						Actor_Says(kActorMcCoy, 6985, 16); //00-6985.AUD	Got the straight scoop for me or what?
						Actor_Modify_Friendliness_To_Other(kActorKlein, kActorMcCoy, -3);
						Delay(1000);
					}
				}
				Actor_Says(kActorKlein, 110, 12); //-	30-0110.AUD	About 50% were real. The rest were fakes.
				Actor_Says(kActorMcCoy, 4150, 15);
				if (_vm->_cutContent) {
					if (Actor_Query_Friendliness_To_Other(kActorKlein, kActorMcCoy) > 49) {
						Actor_Says(kActorKlein, 120, 14);
						Actor_Says(kActorMcCoy, 4155, 17);
						Actor_Says(kActorKlein, 130, 15);
					} else {
						Delay(1000);
					}
				} else {
					Actor_Says(kActorKlein, 120, 14);
					Actor_Says(kActorMcCoy, 4155, 17);
					Actor_Says(kActorKlein, 130, 15);
				}
				Actor_Says(kActorMcCoy, 4160, 13); //-	00-4160.AUD	What about the wounds?
				Actor_Says(kActorKlein, 140, 16); 
				// quote 150 is *boop* in ENG version
				// it is redundant in DEU and FRA versions (identical to second half of quote 140)
				// it is required in ESP and ITA versions. It is the missing second half of quote 140.
				if (_vm->_cutContent
				    && (_vm->_language == Common::ES_ESP
				        || _vm->_language == Common::IT_ITA)
				) {
					Actor_Says(kActorKlein, 150, kAnimationModeTalk); //30-0140.AUD	Most of them were shot point-blank but we're looking at some others… pteh, sloppy cuts with a knife. Like the perp was really pissed off at something.
				}
				// Made it so McCoy only makes the meat cleaver joke if he is not surly or erratic. Also made it so if McCoy is surly or erratic he is annoyed about Klein not mentioning the knife wounds before.
				if (_vm->_cutContent) {
					if (Player_Query_Agenda() == kPlayerAgendaSurly 
					|| Player_Query_Agenda() == kPlayerAgendaErratic) {
						Actor_Says(kActorMcCoy, 3725, 18); //00-3725.AUD	Is that right? Any reason you didn’t tell me that right off?
						Actor_Says(kActorKlein, 300, 17); //30-0300.AUD	I didn’t think you needed to hear about this.
						Actor_Modify_Friendliness_To_Other(kActorKlein, kActorMcCoy, -3);
						Actor_Set_Goal_Number(kActorKlein, kGoalKleinMovingInLab01); 
					} else {
						if (Actor_Clue_Query(kActorMcCoy, kClueSightingMcCoyRuncitersShop)) {
							Actor_Says(kActorMcCoy, 4165, 18);
							Actor_Says(kActorKlein, 160, 13);
						}
						if (!Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
							Actor_Says(kActorMcCoy, 4170, 19); // 00-4170.AUD	Nice bunch of Reps I'm tailing.
							Actor_Says(kActorMcCoy, 4175, 18); // 00-4175.AUD	Hope you're not pulling a meat cleaver out of my back next week.
							if (Actor_Query_Friendliness_To_Other(kActorKlein, kActorMcCoy) > 49) {
								Actor_Says(kActorKlein, 210, 12); //30-0210.AUD  	Ha, you're a real funny guy, McCoy.
								Actor_Modify_Friendliness_To_Other(kActorKlein, kActorMcCoy, 3);
							} else {
								Actor_Says(kActorKlein, 280, 13); //30-0280.AUD	Come back at me when you got something worthwhile, McCoy.
							}
						} else {
							Actor_Says(kActorMcCoy, 4880, 13); //00-4880.AUD	Is that right?
						}
						Actor_Set_Goal_Number(kActorKlein, kGoalKleinMovingInLab01);
					}	
				} else {
					Actor_Says(kActorMcCoy, 4165, 18);
					Actor_Says(kActorKlein, 160, 13);
					Actor_Says(kActorMcCoy, 4170, 19); // 00-4170.AUD	Nice bunch of Reps I'm tailing.
					Actor_Says(kActorMcCoy, 4175, 19); // 00-4175.AUD	Hope you're not pulling a meat cleaver out of my back next week.
					Actor_Modify_Friendliness_To_Other(kActorKlein, kActorMcCoy, 3);
					Actor_Set_Goal_Number(kActorKlein, kGoalKleinMovingInLab01);
			    }
					return true;
			}

			if (((_vm->_cutContent && Actor_Clue_Query(kActorKlein, kCluePaintTransfer))
			      || (!_vm->_cutContent && Game_Flag_Query(kFlagMcCoyHasPaintTransfer)))
			    && !Game_Flag_Query(kFlagPS07KleinTalkPaintTransfer)
			) {
				Game_Flag_Set(kFlagPS07KleinTalkPaintTransfer);
				Actor_Clue_Acquire(kActorMcCoy, kClueLabPaintTransfer, false, kActorKlein);
				Actor_Says(kActorKlein, 170, 14);
				Actor_Says(kActorMcCoy, 4180, 13); //00-4180.AUD	You sure?
				//Jake - Added in a couple of lines.
				if (_vm->_cutContent) {
					Actor_Says(kActorKlein, 290, 14); //30-0290.AUD	Would I lie to you?
					if (Player_Query_Agenda() == kPlayerAgendaSurly 
					|| Player_Query_Agenda() == kPlayerAgendaErratic) {
						Actor_Says(kActorMcCoy, 8295, 13); //00-8295.AUD	You tell me.
						Actor_Modify_Friendliness_To_Other(kActorKlein, kActorMcCoy, -3);
						Delay (1000);
					} else {
						Actor_Says(kActorMcCoy, 3530, 13); //00-3530.AUD	No, sir.
					}
				}
				Actor_Says(kActorKlein, 180, 12); //30-0180.AUD	The angle of impact was almost head-on.
#if BLADERUNNER_ORIGINAL_BUGS
				Actor_Says(kActorKlein, 190, 13);
#else
				// Dino's quote 190 is continued in quote 200, and needs 0.0f pause to sound better flowing
				Actor_Says_With_Pause(kActorKlein, 190, 0.0f, 13); //30-0190.AUD	And there ain't too many spinner drivers klutzy enough…
#endif // BLADERUNNER_ORIGINAL_BUGS
				// Made it so McCoy only makes that mean spirited joke towards Dinos wife if he is surly or erratic.
				// Also adjusted the friendliness loss towards Dino so doesn't walk off when McCoy insults his wife.
				// Seems a bit unfair to punish the player so harshly by having Dino  walk off because of a single comment.
				Actor_Says(kActorKlein, 200, 16); //30-0200.AUD	to smack a street-level hydrant in VTOL mode.
				if (_vm->_cutContent) {
					if (Player_Query_Agenda() == kPlayerAgendaSurly 
					|| Player_Query_Agenda() == kPlayerAgendaErratic) {
						Actor_Says(kActorMcCoy, 4185, 18); //00-4185.AUD	I heard your wife got her license back.
						Delay(1000);
						Actor_Says(kActorKlein, 280, 13); //30-0280.AUD	Come back at me when you got something worthwhile, McCoy.
						Actor_Modify_Friendliness_To_Other(kActorKlein, kActorMcCoy, -6);
						if (!Game_Flag_Query(kFlagKleinCarIdentityTalk)) {
							Actor_Says(kActorMcCoy, 5150, 18); //00-5150.AUD	One more thing.
							Actor_Says(kActorMcCoy, 4195, 13);
							Actor_Says(kActorKlein, 240, 16); 
							Game_Flag_Set(kFlagKleinCarIdentityTalk);
							Actor_Set_Goal_Number(kActorKlein, kGoalKleinMovingInLab01);
						} else {
							Actor_Says(kActorMcCoy, 8320, 13); //00-8320.AUD	Really?
							Delay(500);
							Actor_Says(kActorMcCoy, 8525, -1); // 00-8525.AUD	Hmph.
						}
						Actor_Set_Goal_Number(kActorKlein, kGoalKleinMovingInLab01);
				    } else {
						if (!Game_Flag_Query(kFlagKleinCarIdentityTalk)) {
							Actor_Says(kActorMcCoy, 5150, 18); //00-5150.AUD	One more thing.
							Actor_Says(kActorMcCoy, 4195, 13);
							Actor_Says(kActorKlein, 240, 16); 
							Game_Flag_Set(kFlagKleinCarIdentityTalk);
							Actor_Set_Goal_Number(kActorKlein, kGoalKleinMovingInLab01);
						} else {
							Actor_Says(kActorMcCoy, 8320, 13); //00-8320.AUD	Really?
							Delay(500);
							Actor_Says(kActorMcCoy, 8525, -1); // 00-8525.AUD	Hmph.
						}
					}
				} else {
					Actor_Says(kActorKlein, 200, 16);
					Actor_Says(kActorMcCoy, 4185, 18);
					Actor_Says(kActorKlein, 210, 12);	
					Actor_Modify_Friendliness_To_Other(kActorKlein, kActorMcCoy, -12);
					Actor_Set_Goal_Number(kActorKlein, kGoalKleinMovingInLab01);
				}
				return true;
			}

			if (((_vm->_cutContent && Actor_Clue_Query(kActorKlein, kClueChromeDebris))
			      || (!_vm->_cutContent && Game_Flag_Query(kFlagMcCoyHasChromeDebris)))
			    && !Game_Flag_Query(kFlagPS07KleinTalkChromeDebris)
			) {
				Game_Flag_Set(kFlagPS07KleinTalkChromeDebris);
				Actor_Says(kActorKlein, 220, 12);
				if (_vm->_cutContent) {
					if (Player_Query_Agenda() == kPlayerAgendaSurly 
					|| Player_Query_Agenda() == kPlayerAgendaErratic) {
						Actor_Says(kActorMcCoy, 8575, 14); //00-8575.AUD	More useless junk.
					} else {
						Actor_Says(kActorMcCoy, 4190, 13); //00-4190.AUD	Nice set of wheels.
					}
					if (Actor_Query_Friendliness_To_Other(kActorKlein, kActorMcCoy) > 49) {
						Actor_Says(kActorKlein, 230, 14);
					} else {
						Delay(1000);
					}
					Actor_Says(kActorMcCoy, 4195, 13); //00-4195.AUD	Any way to find the car's owner?
					Actor_Says(kActorKlein, 240, 16); 
					Game_Flag_Set(kFlagKleinCarIdentityTalk);
					Actor_Set_Goal_Number(kActorKlein, kGoalKleinMovingInLab01);
				} else {
					Actor_Says(kActorMcCoy, 4190, 13); //00-4190.AUD	Nice set of wheels.
					Actor_Says(kActorKlein, 230, 14);
				}
				// Car VIN
				// quote 250 is *boop* in ENG version
				// it is redundant in DEU and FRA versions (identical to second half of quote 240)
				// it is required in ESP and ITA versions. It is the missing second half of quote 240.
				if (_vm->_language == Common::ES_ESP
					|| _vm->_language == Common::IT_ITA
				) {
					Actor_Says(kActorKlein, 250, kAnimationModeTalk);
				}
			Actor_Set_Goal_Number(kActorKlein, kGoalKleinMovingInLab01);
			return true;
			}
			// Restored the lab analysis gold chain clue. In place of the gold chain will be the Maggie bracelet and you will only
			// receive it from Klein if you have seen the Tyrell security photo. This is because the chain belongs to Sadik and McCoy
			// says where have I seen that before upon receiving the clue. The clue is added to Sadiks suspect profile. I'll admit you can
			// still see the Maggie inscription on the 'gold chain' but Sadik did mention having a lover that was killed by a blade runner.
			// Could it be that her name was also Maggie? It certainly is a possibility and would be pretty if it were true.
			if (_vm->_cutContent 
			&& (Global_Variable_Query(kVariableChapter) == 2) 	
			&& !Actor_Clue_Query(kActorMcCoy, kClueLabAnalysisGoldChain)
			&& Actor_Clue_Query(kActorMcCoy, kClueTyrellSecurityPhoto)	
			&& (Actor_Query_Friendliness_To_Other(kActorKlein, kActorMcCoy) > 49)) {
				Actor_Says(kActorKlein, 260, 12); //30-0260.AUD Yeah, dig this. It's been doing the circuits throughout the station.
				Actor_Change_Animation_Mode(kActorMcCoy, 23);
				Actor_Change_Animation_Mode(kActorKlein, 23);
				Delay(800);
				Item_Pickup_Spin_Effect_From_Actor(kModelAnimationMaggieBracelet, kActorMcCoy, 0, 0);
				Delay(800);
				Actor_Says(kActorMcCoy, 4190, 13); //99-4190.AUD	Where have I seen that before?
				Actor_Clue_Acquire(kActorMcCoy, kClueLabAnalysisGoldChain, false, kActorKlein);
				Actor_Set_Goal_Number(kActorKlein, kGoalKleinMovingInLab01);
				return true;
			}				
			// Altered code so Dinos response to McCoy if he has nothing left to analyze is determined based on his friendliness with McCoy.
			if (_vm->_cutContent) {
				if (Actor_Query_Friendliness_To_Other(kActorKlein, kActorMcCoy) >= 50) {
					Actor_Says(kActorKlein, 40, 13); //30-0040.AUD	Not right now. If anything else turns up, you'll be the first to know.
				} else if 
					(Actor_Query_Friendliness_To_Other(kActorKlein, kActorMcCoy) == 47) {
					Actor_Says(kActorKlein, 270, 13); //30-0270.AUD	Nah, the place has been pretty quiet the last couple of days.
				} else if 
					(Actor_Query_Friendliness_To_Other(kActorKlein, kActorMcCoy) == 44) {
					Actor_Says(kActorKlein, 0, 13); //30-0000.AUD	Zip, man. Try me later.
				} else if 
					(Actor_Query_Friendliness_To_Other(kActorKlein, kActorMcCoy) == 41) {
					Actor_Says(kActorKlein, 280, 13); //30-0280.AUD	Come back at me when you got something worthwhile, McCoy.
				}
			} else {
				Actor_Says(kActorKlein, 0, 13);
			}
			Actor_Set_Goal_Number(kActorKlein, kGoalKleinMovingInLab01);
			return true;
		}
	}
	return false;

}

bool SceneScriptPS07::ClickedOnItem(int itemId, bool a2) {
	return false;
}

bool SceneScriptPS07::ClickedOnExit(int exitId) {
	if (exitId == 0) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, 609.07f, 0.22f, -598.67f, 0, false, false, false)) {
			Set_Enter(kSetPS02, kScenePS02);
		}
		return true;
	}
	return false;
}

bool SceneScriptPS07::ClickedOn2DRegion(int region) {
	return false;
}

void SceneScriptPS07::SceneFrameAdvanced(int frame) {
}

void SceneScriptPS07::ActorChangedGoal(int actorId, int newGoal, int oldGoal, bool currentSet) {
}

void SceneScriptPS07::PlayerWalkedIn() {
	Loop_Actor_Walk_To_XYZ(kActorMcCoy, 561.07f, 0.34f, -606.67f, 6, false, false, false);
	Game_Flag_Reset(kFlagPS02toPS07);
	//return false;
}

void SceneScriptPS07::PlayerWalkedOut() {
	if (!Game_Flag_Query(kFlagPS07KleinInsulted)
	    && ((_vm->_cutContent && Global_Variable_Query(kVariableChapter) < 4)
	        || (!_vm->_cutContent && Global_Variable_Query(kVariableChapter) == 1))
	){
		Actor_Set_Goal_Number(kActorKlein, kGoalKleinDefault);
	}
}

void SceneScriptPS07::DialogueQueueFlushed(int a1) {
}

} // End of namespace BladeRunner
