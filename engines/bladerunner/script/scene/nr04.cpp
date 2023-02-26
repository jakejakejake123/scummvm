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

void SceneScriptNR04::InitializeScene() {
	Music_Adjust(30, 80, 2u);

	Setup_Scene_Information(53.0f, 0.0f, -110.0f, 569);

	Scene_Exit_Add_2D_Exit(0, 498, 126, 560, 238, 0);

	Scene_2D_Region_Add(0,  0, 259,  61, 479);
	Scene_2D_Region_Add(1, 62, 327,  92, 479);
	Scene_2D_Region_Add(2, 93, 343, 239, 479);

	Ambient_Sounds_Add_Looping_Sound(kSfxAPRTFAN1, 16, 0, 1);
	Ambient_Sounds_Add_Looping_Sound(kSfxRUMLOOP1, 16, 0, 1);
	Ambient_Sounds_Add_Sound(kSfxCLINK1,   3, 60, 9, 9, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxCLINK2,   3, 60, 9, 9, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxCLINK3,   3, 60, 9, 9, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxCLINK4,   3, 60, 9, 9, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0480R, 5, 70, 8, 8, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0540R, 5, 70, 8, 8, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0560R, 5, 70, 8, 8, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0870R, 5, 70, 8, 8, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0900R, 5, 70, 8, 8, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0940R, 5, 70, 8, 8, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_1070R, 5, 70, 8, 8, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_1080R, 5, 70, 8, 8, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_1160R, 5, 70, 8, 8, -100, 100, -101, -101, 0, 0);

	Scene_Loop_Set_Default(0);
}

void SceneScriptNR04::SceneLoaded() {
	Clickable_Object("B.TV01");
	Clickable_Object("B.TV02");
	Clickable_Object("B.TV03");
	Clickable_Object("B.TV05");
	Clickable_Object("DESK");
	if (!Game_Flag_Query(kFlagNR04DiscFound)) {
		Clickable_Object("TORUS01");
	}
	Clickable_Object("BOX12");
}

bool SceneScriptNR04::MouseClick(int x, int y) {
	if (Actor_Query_Animation_Mode(kActorMcCoy) == 85
	 || Actor_Query_Animation_Mode(kActorMcCoy) == 29
	) {
		return true;
	}

	if (Actor_Query_Animation_Mode(kActorMcCoy) == kAnimationModeSit) {
		Actor_Change_Animation_Mode(kActorMcCoy, 29);
		return true;
	}
	return false;
}

bool SceneScriptNR04::ClickedOn3DObject(const char *objectName, bool a2) {
	if (Object_Query_Click("B.TV01", objectName)
	 || Object_Query_Click("B.TV02", objectName)
	 || Object_Query_Click("B.TV03", objectName)
	 || Object_Query_Click("B.TV05", objectName)
	 || Object_Query_Click("DESK", objectName)
	) {
		if (!Loop_Actor_Walk_To_Waypoint(kActorMcCoy, 546, 0, true, false)) {
			if (Object_Query_Click("DESK", objectName)) {
				Actor_Face_Object(kActorMcCoy, "DESK", true);
				// Made it so if Early Q is a rep the receipt for the dragonfly jewelry will not be on the desk. Instead Early Q will have it on him and this will
				// be the evidence that he uses to bargain with McCoy in exchange for the disc.
				if (_vm->_cutContent) {
					if (Game_Flag_Query(kFlagEarlyQIsReplicant)) {
						Actor_Voice_Over(3700, kActorVoiceOver);
					} else { 
						if (!Game_Flag_Query(kFlagEarlyQTalkJewelry)) {
							Actor_Voice_Over(1600, kActorVoiceOver);
							Actor_Voice_Over(1610, kActorVoiceOver);
						} else {
							if (!Actor_Clue_Query(kActorMcCoy, kClueCollectionReceipt)) {
								Actor_Clue_Acquire(kActorMcCoy, kClueCollectionReceipt, false, kActorEarlyQ);
								Actor_Change_Animation_Mode(kActorMcCoy, 23);
								Delay(800);
								Item_Pickup_Spin_Effect(kModelAnimationCollectionReceipt, 247, 141);
								Delay(800);
								Actor_Says(kActorMcCoy, 8845, kAnimationModeTalk); //00-8845.AUD	A receipt.
								Actor_Voice_Over(1560, kActorVoiceOver);
								Actor_Voice_Over(1570, kActorVoiceOver);
								Actor_Voice_Over(1580, kActorVoiceOver);
								if (!Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
									Actor_Voice_Over(1590, kActorVoiceOver); //99-1590.AUD	for more money than I’d see, if I retired a dozen Reps.
								}
								Delay(1000);
								Actor_Change_Animation_Mode(kActorMcCoy, 23);
								Delay(800);
								Item_Pickup_Spin_Effect(kModelAnimationPhoto, 247, 141);
								Delay(800);
								Actor_Says(kActorMcCoy, 1600, 11); //00-1600.AUD	Lucy?
								Delay(1000);
								Actor_Says(kActorMcCoy, 8525, kAnimationModeTalk); //00-8525.AUD	Hmph.
								Actor_Clue_Acquire(kActorMcCoy, kClueDragonflyAnklet, false, kActorEarlyQ);
							} else {
								Actor_Says(kActorMcCoy, 8580, 13); //00-8580.AUD	Nothing else there.
							}
						}
					}
				} else if (!Actor_Clue_Query(kActorMcCoy, kCluePeruvianLadyInterview)) {
					Actor_Voice_Over(1600, kActorVoiceOver);
					Actor_Voice_Over(1610, kActorVoiceOver);
				} else if (!Actor_Clue_Query(kActorMcCoy, kClueCollectionReceipt)) {
					Actor_Clue_Acquire(kActorMcCoy, kClueCollectionReceipt, false, -1);
					Item_Pickup_Spin_Effect(kModelAnimationCollectionReceipt, 247, 141);
					Actor_Voice_Over(1560, kActorVoiceOver);
					Actor_Voice_Over(1570, kActorVoiceOver);
					Actor_Voice_Over(1580, kActorVoiceOver);
					Actor_Voice_Over(1590, kActorVoiceOver); //99-1590.AUD	for more money than I’d see, if I retired a dozen Reps.
				} else {
					Actor_Says(kActorMcCoy, 8580, kAnimationModeTalk);
				}
			} else {
				Actor_Face_Object(kActorMcCoy, "B.TV01", true);
				Actor_Voice_Over(1530, kActorVoiceOver);
				if (_vm->_cutContent) {
					if (!Game_Flag_Query(kFlagEarlyQIsReplicant)) {
						Actor_Voice_Over(1540, kActorVoiceOver);
						Actor_Voice_Over(1550, kActorVoiceOver);
						Game_Flag_Set(kFlagDiscoveredEarlyQsMonitors);
					} 
				} else {
					Actor_Voice_Over(1540, kActorVoiceOver);
					Actor_Voice_Over(1550, kActorVoiceOver);
				}
			}
		}
		return false;
	}

	if ( Object_Query_Click("TORUS01", objectName)
	 && !Loop_Actor_Walk_To_XYZ(kActorMcCoy, 18.56f, 0.0f, 38.86f, 0, true, false, false)
	 && !Game_Flag_Query(kFlagNR04DiscFound)
	) {
		Unclickable_Object("TORUS01");
		Scene_Exits_Disable();
		Player_Loses_Control();
		Game_Flag_Set(kFlagNR04DiscFound);
		Actor_Face_Object(kActorMcCoy, "TORUS01", true);
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagEarlyQIsReplicant)
			&& Game_Flag_Query(kFlagSadikIsReplicant)) {
				Actor_Change_Animation_Mode(kActorMcCoy, 23);
				Delay(800);
				Item_Pickup_Spin_Effect(kModelAnimationDNADataDisc, 358, 160);
				Delay(1500);
				Item_Pickup_Spin_Effect(kModelAnimationDNADataDisc, 358, 160);
				Delay(1500);
				Item_Pickup_Spin_Effect(kModelAnimationDNADataDisc, 358, 160);
				Delay(1500);
				Actor_Voice_Over(130, kActorVoiceOver); //99-0130.AUD	DNA research, incept dates.
				Actor_Voice_Over(140, kActorVoiceOver); //99-0140.AUD	A lot of jargon but I bet my spinner it was valuable to somebody.
				Actor_Clue_Acquire(kActorMcCoy, kClueDNAMarcus, true, kActorEarlyQ);
				Actor_Clue_Acquire(kActorMcCoy, kClueDNASebastian, true, kActorEarlyQ);
				Actor_Clue_Acquire(kActorMcCoy, kClueDNAMoraji, true, kActorEarlyQ);
				Delay(1000);
			}
			Actor_Change_Animation_Mode(kActorMcCoy, 23);
			Delay(800);
			Item_Pickup_Spin_Effect(kModelAnimationVideoDisc, 358, 160);
			Delay(800);
			Actor_Voice_Over(1620, kActorVoiceOver);
			Actor_Voice_Over(1630, kActorVoiceOver);
			Actor_Clue_Acquire(kActorMcCoy, kClueEarlyQsClub, false, kActorEarlyQ);
			Actor_Set_Goal_Number(kActorEarlyQ, kGoalEarlyQNR04Enter);
		} else {
			Item_Pickup_Spin_Effect(kModelAnimationVideoDisc, 358, 160);
			Actor_Voice_Over(1620, kActorVoiceOver);
			Actor_Voice_Over(1630, kActorVoiceOver);
			Actor_Clue_Acquire(kActorMcCoy, kClueEarlyQsClub, false, -1);
			Actor_Set_Goal_Number(kActorEarlyQ, kGoalEarlyQNR04Enter);
		}
		return false;
	}

	return false;
}

bool SceneScriptNR04::ClickedOnActor(int actorId) {
	if (actorId == kActorEarlyQ
	 && Game_Flag_Query(kFlagNR04EarlyQStungByScorpions)
	) {
		Actor_Voice_Over(1640, kActorVoiceOver);
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagDiscoveredEarlyQsMonitors)) {
				Actor_Voice_Over(1650, kActorVoiceOver); //99-1650.AUD	And he’d taken his dirty little secrets with him.
			}
		} else {
			Actor_Voice_Over(1650, kActorVoiceOver); //99-1650.AUD	And he’d taken his dirty little secrets with him.
		}
		// Made it so McCoy only says Early Q deserved to die if he is surly or erratic.
		if (_vm->_cutContent) {
			if (Player_Query_Agenda() != kPlayerAgendaPolite) {
				Actor_Voice_Over(1660, kActorVoiceOver); //99-1660.AUD	Someone had set him up, but my guess was that the bastard deserved it.
			} else {
				Actor_Voice_Over(1670, kActorVoiceOver); //99-1670.AUD	Still it was a hell of a way to go.
			}
		} else {
			Actor_Voice_Over(1660, kActorVoiceOver); //99-1660.AUD	Someone had set him up, but my guess was that the bastard deserved it.
			Actor_Voice_Over(1670, kActorVoiceOver); //99-1670.AUD	Still it was a hell of a way to go.
		}
		Actor_Voice_Over(1680, kActorVoiceOver);
		// Added in some code so you can loot Early Qs body after he dies and receive the Dektoras dressing room photo.
		if (_vm->_cutContent) {
			 if (!Game_Flag_Query(kFlagEarlyQIsReplicant)) {
				if (!Actor_Clue_Query(kActorMcCoy, kClueDektorasDressingRoom)) {
					Delay(1000);
					Actor_Clue_Acquire(kActorMcCoy, kClueDektorasDressingRoom, true, kActorEarlyQ);
					Item_Pickup_Spin_Effect_From_Actor(kModelAnimationPhoto, kActorEarlyQ, 0, 0);
					Actor_Voice_Over(4100, kActorVoiceOver); //99-4100.AUD	They look familiar.
				}
			}
		}
		return true;
	}
	return false;
}

bool SceneScriptNR04::ClickedOnItem(int itemId, bool a2) {
	return false;
}

bool SceneScriptNR04::ClickedOnExit(int exitId) {
	if (exitId == 0) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, 45.0f, 0.0f, -106.0f, 0, true, false, false)) {
			Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
			Ambient_Sounds_Remove_All_Looping_Sounds(1u);
			Game_Flag_Set(kFlagNR04toNR03);
			Set_Enter(kSetNR03, kSceneNR03);
		}
		return true;
	}
	return false;
}

bool SceneScriptNR04::ClickedOn2DRegion(int region) {
	if ((region == 0
	  || region == 1
	  || region == 2
	 )
	 &&  Actor_Query_Which_Set_In(kActorEarlyQ) != kSetNR04
	 &&  Actor_Query_Animation_Mode(kActorMcCoy) != kAnimationModeSit
	) {
		if (!Loop_Actor_Walk_To_Waypoint(kActorMcCoy, 445, 0, true, false)) {
			Actor_Face_Heading(kActorMcCoy, 49, false);
			Actor_Change_Animation_Mode(kActorMcCoy, 85);
			Delay(2500);

			if (!Game_Flag_Query(kFlagNR04EarlyQStungByScorpions)
			&&  Game_Flag_Query(kFlagAR02DektoraBoughtScorpions)
			) {
				if (_vm->_cutContent) {
					if (!Game_Flag_Query(kFlagEarlyQIsReplicant)
					&& Game_Flag_Query(kFlagDektoraIsReplicant)) {
						Player_Loses_Control();
						Actor_Voice_Over(4180, kActorVoiceOver);
						Actor_Change_Animation_Mode(kActorMcCoy, kAnimationModeDie);
						Ambient_Sounds_Play_Sound(kSfxMALEHURT, 90, 99, 0, 0);
						Delay(350);
						Actor_Set_At_XYZ(kActorMcCoy, 109.0f, 0.0f, 374.0f, 0);
						Actor_Retired_Here(kActorMcCoy, 12, 12, true, -1);
					}
				} else {
					Player_Loses_Control();
					Actor_Voice_Over(4180, kActorVoiceOver);
					Actor_Change_Animation_Mode(kActorMcCoy, kAnimationModeDie);
					Ambient_Sounds_Play_Sound(kSfxMALEHURT, 90, 99, 0, 0);
					Delay(350);
					Actor_Set_At_XYZ(kActorMcCoy, 109.0f, 0.0f, 374.0f, 0);
					Actor_Retired_Here(kActorMcCoy, 12, 12, true, -1);
				} 
			}
			return true;
		}
	}
	return false;
}

void SceneScriptNR04::SceneFrameAdvanced(int frame) {
	if ( frame == 1
	 && !Music_Is_Playing()
	) {
		playNextMusic();
	}

	if (frame > 60
	 && frame < 120
	) {
		druggedEffect(frame);
	} else if (frame == 120) {
		Set_Fade_Color(1.0f, 1.0f, 1.0f);
		Set_Fade_Density(0.0f);
	}
	//return false;
}

void SceneScriptNR04::ActorChangedGoal(int actorId, int newGoal, int oldGoal, bool currentSet) {
	if (actorId == kActorEarlyQ) {
		switch (newGoal) {
		case kGoalEarlyQNR04Talk1:
			Actor_Face_Actor(kActorEarlyQ, kActorMcCoy, true);
			Actor_Face_Actor(kActorMcCoy, kActorEarlyQ, true);
			Actor_Says(kActorEarlyQ, 30, kAnimationModeTalk); 
			Actor_Says(kActorMcCoy, 3375, kAnimationModeTalk); //00-3375.AUD	What’s on the disc, Early?
			Actor_Says_With_Pause(kActorEarlyQ, 50, 1.5f, kAnimationModeTalk); //18-0050.AUD	Hey, hey, I don’t hassle you about your private life.
			Actor_Says(kActorEarlyQ, 60, kAnimationModeTalk); //18-0060.AUD	Put it down, McCoy.
			// Made it so McCoy only mentions Early Q spying on the women if he has seen the security monitors.
			if (_vm->_cutContent) {
				if (!Game_Flag_Query(kFlagEarlyQIsReplicant)) {
					if (Game_Flag_Query(kFlagDiscoveredEarlyQsMonitors)) {
						Actor_Says_With_Pause(kActorMcCoy, 3380, 1.0f, kAnimationModeTalk); //00-3380.AUD	Must be something pretty juicy. Your girls know about the cameras?
					} else {
						Actor_Says(kActorMcCoy, 5855, kAnimationModeTalk); //00-5855.AUD	Not a chance.
					}
				} else { 
					Actor_Says(kActorMcCoy, 5855, kAnimationModeTalk); //00-5855.AUD	Not a chance.
				}
			} else {
				Actor_Says_With_Pause(kActorMcCoy, 3380, 1.0f, kAnimationModeTalk); //00-3380.AUD	Must be something pretty juicy. Your girls know about the cameras?
			}
			Actor_Says(kActorEarlyQ, 70, kAnimationModeTalk);//18-0070.AUD	I got ya. You want a trade. The disc for… what?
			if (_vm->_cutContent) {
				if (Player_Query_Agenda() != kPlayerAgendaPolite) {
					Actor_Says(kActorMcCoy, 3415, kAnimationModeTalk); //00-3415.AUD	Let’s hear what you got.
				} else {
					Actor_Says(kActorMcCoy, 8370, kAnimationModeTalk); //00-8370.AUD	It's okay. I got what I need. 
				}
			} else {
				Actor_Says(kActorMcCoy, 3415, kAnimationModeTalk); //00-3415.AUD	Let’s hear what you got.
			}		
			Actor_Says(kActorEarlyQ, 80, kAnimationModeTalk); //
			Player_Gains_Control();
			Actor_Set_Goal_Number(kActorEarlyQ, kGoalEarlyQNR04GoToBar);
			if (_vm->_cutContent) {
				if (Player_Query_Agenda() == kPlayerAgendaSurly 
				|| Player_Query_Agenda() == kPlayerAgendaErratic) {
					Delay(1000);
					Player_Set_Combat_Mode(true);
				}
			}
			//return true;
			break;

		case kGoalEarlyQNR04PourDrink:
			Actor_Face_Actor(kActorMcCoy, kActorEarlyQ, true);
			Actor_Says(kActorEarlyQ, 90, 73);
			if (_vm->_cutContent) {
				if (Player_Query_Agenda() == kPlayerAgendaPolite) {
					Actor_Says(kActorMcCoy, 3390, 14); //00-3390.AUD	Not interested.
				} else {
					Actor_Says(kActorMcCoy, 2485, 13); //00-2485.AUD	I’ve a hard time believing that.
				}
			} else {
				Actor_Says(kActorMcCoy, 3390, 3); //00-3390.AUD	Not interested.
			}
			if (_vm->_cutContent) {
				Actor_Says(kActorEarlyQ, 140, 16); //18-0140.AUD	You want Dektora? Is that it? The girl with the Rep friends?
				Actor_Clue_Acquire(kActorMcCoy, kClueEarlyQInterview, true, kActorEarlyQ);
				Delay(1000);
				if (Game_Flag_Query(kFlagEarlyQIsReplicant)) {
					Player_Loses_Control();
					Loop_Actor_Walk_To_XYZ(kActorMcCoy, 18.56f, 0.0f, 38.86f, 0, true, false, false);
					Actor_Face_Actor(kActorMcCoy, kActorEarlyQ, true);
					Delay(1000);
					Actor_Says(kActorEarlyQ, 190, 74); //18-0190.AUD	You’re cold, General.
					Delay(2000);
					if (!Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
						Actor_Says(kActorMcCoy, 6865, 14); //00-6865.AUD	You're a Replicant.
						Music_Stop(1u);
						Delay(1000);
						Actor_Change_Animation_Mode(kActorEarlyQ, 4);
						Delay(1000);
						Actor_Face_Actor(kActorEarlyQ, kActorMcCoy, true);
						Actor_Change_Animation_Mode(kActorEarlyQ, kAnimationModeCombatAttack);
						Actor_Change_Animation_Mode(kActorMcCoy, 21);
						Music_Play(kMusicMoraji, 71, 0, 0, -1, kMusicLoopPlayOnce, 2);
						Delay(1000);
						Loop_Actor_Walk_To_XYZ(kActorMcCoy, 7.84, 0.26, 172.93, 0, false, true, false);
						Actor_Face_Actor(kActorEarlyQ, kActorMcCoy, true);
						Actor_Face_Actor(kActorMcCoy, kActorEarlyQ, true);
						Sound_Play(kSfxGUNH1A, 100, 0, 0, 50);
						Actor_Change_Animation_Mode(kActorMcCoy, 6);
						Actor_Change_Animation_Mode(kActorEarlyQ, 21);
						Delay(1000);
						Loop_Actor_Walk_To_XYZ(kActorMcCoy, -17.91, 0.24, 247.39, 0, true, true, false);
						Actor_Face_Actor(kActorEarlyQ, kActorMcCoy, true);
						Actor_Face_Actor(kActorMcCoy, kActorEarlyQ, true);
						Sound_Play(kSfxGUNH1A, 100, 0, 0, 50);
						Actor_Change_Animation_Mode(kActorMcCoy, 6);
						Actor_Change_Animation_Mode(kActorEarlyQ, 21);
						Delay(1000);
						Loop_Actor_Walk_To_XYZ(kActorMcCoy, -30.30, 0.22, 299.78, 0, false, true, false);
						Actor_Face_Actor(kActorEarlyQ, kActorMcCoy, true);
						Actor_Change_Animation_Mode(kActorEarlyQ, kAnimationModeCombatAttack);
						Actor_Change_Animation_Mode(kActorMcCoy, 22);
						Delay(1000);
						Actor_Face_Actor(kActorMcCoy, kActorEarlyQ, true);
						Sound_Play(kSfxGUNH1A, 100, 0, 0, 50);
						Actor_Change_Animation_Mode(kActorMcCoy, 6);
						Actor_Change_Animation_Mode(kActorEarlyQ, 21);
						Delay(1000);
						Loop_Actor_Walk_To_XYZ(kActorMcCoy, 31.22f, 0.0f, 267.51f, 0, true, false, false);
						Actor_Face_Actor(kActorEarlyQ, kActorMcCoy, true);
						Actor_Change_Animation_Mode(kActorEarlyQ, kAnimationModeCombatAttack);
						Actor_Change_Animation_Mode(kActorMcCoy, 22);
						Delay(1000);
						Actor_Face_Actor(kActorEarlyQ, kActorMcCoy, true);
						Actor_Change_Animation_Mode(kActorEarlyQ, 7);
						Delay(1000);
						Actor_Face_Actor(kActorEarlyQ, kActorMcCoy, true);
						Actor_Face_Actor(kActorMcCoy, kActorEarlyQ, true);
						Sound_Play(kSfxGUNH1A, 100, 0, 0, 50);
						Actor_Change_Animation_Mode(kActorMcCoy, 6);
						if (Player_Query_Agenda() == kPlayerAgendaSurly 
						|| (Player_Query_Agenda() == kPlayerAgendaErratic)) {
							Actor_Start_Speech_Sample(kActorMcCoy, 490); //00-0490.AUD	Suck on this, skin-job!
						}
						AI_Movement_Track_Flush(kActorEarlyQ);
						Actor_Change_Animation_Mode(kActorEarlyQ, kAnimationModeDie);
						Actor_Retired_Here(kActorEarlyQ, 6, 6, true, kActorMcCoy);
						Actor_Face_Heading(kActorEarlyQ, 760, false);
						Actor_Set_At_XYZ(kActorEarlyQ, 122.09f, 0.14f, 370.11f, 760);
						Delay(2000);
						Game_Flag_Set(kFlagEarlyQDead);
						Game_Flag_Reset(kFlagMcCoyIsHelpingReplicants);
						Actor_Modify_Friendliness_To_Other(kActorSteele, kActorMcCoy, 2);
						Actor_Modify_Friendliness_To_Other(kActorClovis, kActorMcCoy, -2);
						Actor_Modify_Friendliness_To_Other(kActorGuzza, kActorMcCoy, 2);
						Actor_Modify_Friendliness_To_Other(kActorGaff, kActorMcCoy, 2);
						Actor_Set_Targetable(kActorEarlyQ, false);
						if (Query_Difficulty_Level() != kGameDifficultyEasy) {
							Global_Variable_Increment (kVariableChinyen, 200);
						}
						if (Game_Flag_Query(kFlagHanoiIsReplicant)) {
							Actor_Set_Goal_Number(kActorHanoi, kGoalHanoiNR04Enter);
						} else {
							Player_Gains_Control();
						}
					} else {
						if (Player_Query_Agenda() == kPlayerAgendaPolite) {
							Actor_Says(kActorMcCoy, 8512, 15); // 00-8512.AUD	The disc? I'm keeping it for now.
							Delay(1000);
							Actor_Face_Actor(kActorEarlyQ, kActorMcCoy, true);
							Actor_Face_Actor(kActorMcCoy, kActorEarlyQ, true);
							Actor_Says(kActorEarlyQ, 340, 12); //18-0340.AUD	No more free drinks for you, buddy boy.
							Actor_Says(kActorMcCoy, 3465, 12); //00-3465.AUD	I didn’t get free drinks before.
							Actor_Says(kActorEarlyQ, 350, 16);
							Actor_Set_Goal_Number(kActorEarlyQ, kGoalEarlyQNR04Leave);
							Delay(8000);
							Player_Loses_Control();
							Loop_Actor_Walk_To_XYZ(kActorMcCoy, 45.0f, 0.0f, -106.0f, 0, true, false, false);
							Player_Gains_Control();
							Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
							Ambient_Sounds_Remove_All_Looping_Sounds(1u);
							Game_Flag_Set(kFlagNR04toNR03);
							Set_Enter(kSetNR03, kSceneNR03);
							Scene_Exits_Enable();
							Player_Gains_Control();
						} else {
							Actor_Says(kActorMcCoy, 3385, 3); //00-3385.AUD	I want information.
							Actor_Says(kActorEarlyQ, 120, 74);
							Actor_Face_Actor(kActorEarlyQ, kActorMcCoy, true);
							Actor_Set_Goal_Number(kActorEarlyQ, kGoalEarlyQNR04GoToMcCoy);
						}
					}
				} else {
					if (Player_Query_Agenda() == kPlayerAgendaPolite) {
						Actor_Says(kActorMcCoy, 8512, 15); 
						Delay(1000);
						Actor_Face_Actor(kActorEarlyQ, kActorMcCoy, true);
						Actor_Face_Actor(kActorMcCoy, kActorEarlyQ, true);
						Actor_Says(kActorEarlyQ, 340, 12); //18-0340.AUD	No more free drinks for you, buddy boy.
						Actor_Says(kActorMcCoy, 3465, 12); //00-3465.AUD	I didn’t get free drinks before.
						Actor_Says(kActorEarlyQ, 350, 16);
						Actor_Set_Goal_Number(kActorEarlyQ, kGoalEarlyQNR04Leave);
						Delay(8000);
						Player_Loses_Control();
						Loop_Actor_Walk_To_XYZ(kActorMcCoy, 45.0f, 0.0f, -106.0f, 0, true, false, false);
						Player_Gains_Control();
						Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
						Ambient_Sounds_Remove_All_Looping_Sounds(1u);
						Game_Flag_Set(kFlagNR04toNR03);
						Set_Enter(kSetNR03, kSceneNR03);
						Scene_Exits_Enable();
						Player_Gains_Control();
					} else {
						Actor_Says(kActorMcCoy, 3385, 3); //00-3385.AUD	I want information.
						Actor_Says(kActorEarlyQ, 120, 74);
						Actor_Set_Goal_Number(kActorEarlyQ, kGoalEarlyQNR04GoToMcCoy);
					}
				}
			} else {
				Actor_Face_Actor(kActorEarlyQ, kActorMcCoy, true);
				Actor_Says(kActorEarlyQ, 110, 74);
				Actor_Says(kActorMcCoy, 3385, 3);
				Actor_Says(kActorEarlyQ, 120, 74);
				Actor_Face_Actor(kActorEarlyQ, kActorMcCoy, true);
				Actor_Set_Goal_Number(kActorEarlyQ, kGoalEarlyQNR04GoToMcCoy);
			}
			//return true;
			break;

		case kGoalEarlyQNR04SitDown:
			Loop_Actor_Walk_To_Waypoint(kActorEarlyQ, 445, 0, true, false);
			Actor_Face_Heading(kActorEarlyQ, 49, false);
			Actor_Change_Animation_Mode(kActorEarlyQ, 85);
			Actor_Face_Actor(kActorMcCoy, kActorEarlyQ, true);
			Actor_Set_Goal_Number(kActorEarlyQ, kGoalEarlyQNR04ScorpionsCheck);
			// The quotes corresponding to this clue are from kGoalEarlyQNR04McCoyPulledGun (previous goal of EarlyQ)
			// That goal leads to this one (if McCoy does not shoot Early Q that is)
			// TODO maybe move acquiring the clue to the kGoalEarlyQNR04McCoyPulledGun?
			//return true;
			break;

		case kGoalEarlyQNR04Talk2:
			Actor_Face_Actor(kActorMcCoy, kActorEarlyQ, true);
			Delay(3000);
			Actor_Says(kActorEarlyQ, 170, 30);
			Actor_Says(kActorMcCoy, 3415, kAnimationModeTalk); //00-3415.AUD	Let’s hear what you got.
			Actor_Says(kActorEarlyQ, 180, 30);
			Actor_Says_With_Pause(kActorMcCoy, 3420, 1.5f, kAnimationModeTalk);
			if (_vm->_cutContent) {
				Scene_Exits_Disable();
				if (Game_Flag_Query(kFlagEarlyQIsReplicant)) {
					Actor_Says(kActorEarlyQ, 190, 30); //18-0190.AUD	You’re cold, General.
					// After Early Q says you're cold general, McCoy realizes that Early Q is a replicant.
					Delay (2000);
					Actor_Says(kActorMcCoy, 6865, -1); //00-6865.AUD	You're a Replicant.
					Delay (2000);
					Actor_Says(kActorEarlyQ, 90, 30);
				}
				if (Player_Query_Agenda() == kPlayerAgendaPolite) {
					Delay(1000);
					Actor_Set_Goal_Number(kActorEarlyQ, kGoalEarlyQNR04Talk3);
				} else {
					Actor_Set_Goal_Number(kActorEarlyQ, kGoalEarlyQNR04WaitForPulledGun);
				}
			} else {
				Actor_Says(kActorEarlyQ, 190, 30); //18-0190.AUD	You’re cold, General.
				Actor_Set_Goal_Number(kActorEarlyQ, kGoalEarlyQNR04WaitForPulledGun);
			}
			//return true;
			break;

		case kGoalEarlyQNR04Talk3:
		// If McCoy puts his gun away and spares Early Q this will result in Early Q giving McCoy the receipt for the dragonfly jewelry.
			if (_vm->_cutContent) {
				if (Game_Flag_Query(kFlagEarlyQIsReplicant)) {
					Player_Set_Combat_Mode(false);
					Actor_Says(kActorMcCoy, 455, -1); //00-0455.AUD	Relax. Nobody's gonna get retired. Okay?
					Delay (1000);
					Actor_Says(kActorEarlyQ, 120, 30); //18-0120.AUD	You can have whatever you little heart desires, General.
					Delay (1000);
					Actor_Says(kActorMcCoy, 3385, 13); //00-3385.AUD	I want information.
					Actor_Says(kActorEarlyQ, 700, 30); //18-0700.AUD	I heard some things, yeah. I’m the kind of guy people confide in, you know.
					Actor_Says(kActorMcCoy, 150, 13); //00-0150.AUD	You know anything about insects?
					// Fixed the conversation so it flows better.
					Actor_Says(kActorMcCoy, 1110, 14); //00-1110.AUD	We're talking exceptionally fine jewelry in the shape of a dragonfly.
					Delay (1000);
					Actor_Says(kActorMcCoy, 8990, 18); //00-8990.AUD	What have you got there?
					Delay (1000);
					Player_Loses_Control();
					Loop_Actor_Walk_To_Actor(kActorMcCoy, kActorEarlyQ, 24, true, false);
					Player_Gains_Control();
					Actor_Change_Animation_Mode(kActorMcCoy, 23);
					Delay (800);
					Actor_Clue_Acquire(kActorMcCoy, kClueCollectionReceipt, false, kActorEarlyQ);
					Item_Pickup_Spin_Effect_From_Actor(kModelAnimationCollectionReceipt, kActorMcCoy, 0, 0);
					Delay (800);
					Actor_Says(kActorMcCoy, 8845, 18); //00-8845.AUD	A receipt.
					Actor_Voice_Over(1570, kActorVoiceOver); //99-1570.AUD	There were three pieces. A belt, earrings and an anklet.
					Actor_Voice_Over(1580, kActorVoiceOver); //99-1580.AUD	Early had bought them last month at an auction…
					if (!Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
						Actor_Voice_Over(1590, kActorVoiceOver); //99-1590.AUD	for more money than I’d see, if I retired a dozen Reps.
					}
					Delay (1000);
					Actor_Says(kActorMcCoy, 4130, 18); //00-4130.AUD	Anything else?
					Actor_Says(kActorEarlyQ, 280, 30); //18-0280.AUD	No, General. I ain’t the nosy type.
					Actor_Modify_Friendliness_To_Other(kActorClovis, kActorMcCoy, 2);
					Actor_Modify_Friendliness_To_Other(kActorSteele, kActorMcCoy, -2);
					Actor_Modify_Friendliness_To_Other(kActorGuzza, kActorMcCoy, -2);
					Game_Flag_Set(kFlagMcCoyIsHelpingReplicants);
					Scene_Exits_Enable();
					if (Player_Query_Agenda() == kPlayerAgendaSurly 
					|| Player_Query_Agenda() == kPlayerAgendaErratic) {
						Actor_Says(kActorMcCoy, 3445, kAnimationModeTalk);
					}
					Actor_Set_Goal_Number(kActorEarlyQ, kGoalEarlyQNR04AskForDisk);
				} else { 
					Actor_Start_Speech_Sample(kActorMcCoy, 3); //00-4940.AUD	Okay, let's have it.
					Player_Loses_Control();
					Loop_Actor_Walk_To_Actor(kActorMcCoy, kActorEarlyQ, 24, true, false);
					Player_Gains_Control();
					Actor_Change_Animation_Mode(kActorMcCoy, 23);
					Delay (800);
					Actor_Clue_Acquire(kActorMcCoy, kClueDektorasDressingRoom, false, kActorEarlyQ);
					Item_Pickup_Spin_Effect_From_Actor(kModelAnimationPhoto, kActorMcCoy, 0, 0);
					Delay (800);
					if (Game_Flag_Query(kFlagDiscoveredEarlyQsMonitors)) {
						Actor_Start_Speech_Sample(kActorEarlyQ, 200); //18-0200.AUD	But I know you’re gonna be thankful I put those cameras in.
					}
					Delay(1000);
					Actor_Says(kActorEarlyQ, 210, 30); //18-0210.AUD	Hey, check out Dektora’s bearded boy-toy.
					if (Actor_Clue_Query(kActorMcCoy, kClueAnimalMurderSuspect)
					|| Actor_Clue_Query(kActorMcCoy, kClueMorajiInterview)
					|| Actor_Clue_Query(kActorMcCoy, kClueClovisAtMoonbus)
					|| Actor_Clue_Query(kActorMcCoy, kClueIzosFriend)) {
						Actor_Says_With_Pause(kActorMcCoy, 3425, 1.5f, 13); //00-3425.AUD	I’ve seen them before.
					} else {
						Actor_Says(kActorMcCoy, 5065, 18); //00-5065.AUD	Is that right?
					}
					Actor_Says(kActorEarlyQ, 220, 30); //18-0220.AUD	Eh, he’s here all the time. You can be sure he ain’t coming around for the witty conversation.
					Actor_Says(kActorMcCoy, 3430, 14); //00-3430.AUD	What makes you think he’s a Replicant?
					Actor_Says(kActorEarlyQ, 240, 30);
					Actor_Says(kActorMcCoy, 3435, 18); 
					Actor_Says(kActorEarlyQ, 250, 30);
					Actor_Says(kActorMcCoy, 3440, 13);
					Actor_Says(kActorEarlyQ, 280, 30);
					if (Player_Query_Agenda() == kPlayerAgendaSurly 
					|| Player_Query_Agenda() == kPlayerAgendaErratic) {
						Actor_Says(kActorMcCoy, 3445, 18); //00-3445.AUD	Yeah. You’re a model citizen.
					}
					// Added in a clue.
					Actor_Clue_Acquire(kActorMcCoy, kClueEarlyInterviewB2, true, kActorEarlyQ);
					Scene_Exits_Enable();
					Actor_Set_Goal_Number(kActorEarlyQ, kGoalEarlyQNR04AskForDisk);
				}
			} else { 
				Actor_Clue_Acquire(kActorMcCoy, kClueDektorasDressingRoom, false, kActorEarlyQ);
				Item_Pickup_Spin_Effect(kModelAnimationPhoto, 200, 160);
				Actor_Says(kActorEarlyQ, 200, 30);
				Actor_Says(kActorEarlyQ, 210, 30);
				Actor_Says(kActorEarlyQ, 220, 30);
				Actor_Says_With_Pause(kActorMcCoy, 3425, 1.5f, 23);
				Actor_Says(kActorMcCoy, 3430, kAnimationModeTalk);
				Actor_Says(kActorEarlyQ, 240, 30);
				Actor_Says(kActorMcCoy, 3435, kAnimationModeTalk);
				Actor_Says(kActorEarlyQ, 250, 30);
				Actor_Says(kActorMcCoy, 3440, kAnimationModeTalk);
				Actor_Says(kActorEarlyQ, 280, 30);
				Actor_Says(kActorMcCoy, 3445, kAnimationModeTalk);
				Actor_Set_Goal_Number(kActorEarlyQ, kGoalEarlyQNR04AskForDisk);
			}
			//return true;
			break;

		case kGoalEarlyQNR04AskForDisk:
			Actor_Change_Animation_Mode(kActorEarlyQ, 29);
			Delay(2500);
			if (_vm->_cutContent) {
				Actor_Face_Actor(kActorEarlyQ, kActorMcCoy, true);
			}
			Actor_Says(kActorEarlyQ, 290, kAnimationModeTalk);
			dialogueWithEarlyQ();
			//return true;
			break;
		}
	}
	//return false;
}

void SceneScriptNR04::PlayerWalkedIn() {
#if BLADERUNNER_ORIGINAL_BUGS
#else
	Game_Flag_Reset(kFlagNR03toNR04);
#endif // BLADERUNNER_ORIGINAL_BUGS
if (_vm->_cutContent) {
	if (Actor_Clue_Query(kActorMcCoy, kClueEarlyQAndLucy)
	&& !Game_Flag_Query(kFlagNR04EarlyQStungByScorpions)
	&& !Game_Flag_Query(kFlagEarlyQDead)
	&& !Game_Flag_Query(kFlagEarlyQArrested)) {
		Actor_Set_At_XYZ(kActorMcCoy,  53.0f, 0.0f, -26.0f, 0);
	} else {
		Loop_Actor_Walk_To_XYZ(kActorMcCoy, 53.0f, 0.0f, -26.0f, 0, false, false, false);
	}
} else {
	Loop_Actor_Walk_To_XYZ(kActorMcCoy, 53.0f, 0.0f, -26.0f, 0, false, false, false);
}
	if (_vm->_cutContent) {
		if (Game_Flag_Query(kFlagAR02DektoraBoughtScorpions)) {
			if (!Game_Flag_Query(kFlagEarlyQIsReplicant)) {
				Overlay_Play("nr04over", 0, true, false, 0);
				Delay(4000);
				Overlay_Remove("nr04over");
			}
		}
	} else {
		if (Game_Flag_Query(kFlagAR02DektoraBoughtScorpions)) {
			Overlay_Play("nr04over", 0, true, false, 0);
			Delay(4000);
			Overlay_Remove("nr04over");
		}
	}
	//return false;
	// Added in an option to arrest Early Q for what he did to Lucy or if she is a replicant being a rep sympathizier. After you receive the Early Q and Lucy clue you
	// walk into Early Qs office and this scene plays.
	if (_vm->_cutContent) {
		if (Actor_Clue_Query(kActorMcCoy, kClueEarlyQAndLucy)
		&& !Game_Flag_Query(kFlagNR04EarlyQStungByScorpions)
		&& !Game_Flag_Query(kFlagEarlyQDead)
		&& !Game_Flag_Query(kFlagEarlyQArrested)) {
			Actor_Put_In_Set(kActorEarlyQ, kSetNR04);
			Actor_Set_At_XYZ(kActorEarlyQ,  48.79, 0.32, 34.30, 126);
			Actor_Face_Actor(kActorMcCoy, kActorEarlyQ, true);
			Actor_Face_Actor(kActorEarlyQ, kActorMcCoy, true);
			Actor_Says(kActorEarlyQ, 30, 13); //18-0030.AUD	How’re you doing, General? You got a warrant to show me or you’re just breaking and entering?
			Actor_Voice_Over(4260, kActorVoiceOver); //99-4260.AUD	Early, you sick bastard.
			Actor_Says(kActorEarlyQ, 750, 18); //18-0750.AUD	Look, General. No reason to get your panties in a bind. If I’d known you were gonna get so testy, I would have tossed you the straight dope to begin with.
			Actor_Says(kActorMcCoy, 8519, 13); //00-8519.AUD	What do you say we dish each other the straight goods.
			Actor_Says(kActorEarlyQ, 700, 15); //18-0700.AUD	I heard some things, yeah. I’m the kind of guy people confide in, you know.
			Actor_Says(kActorMcCoy, 4760, 12); // 00-4760.AUD	About the girl.
			Actor_Says(kActorMcCoy, 4765, 15); // 00-4765.AUD	Lucy. I know what you did.
			// Removed a line for the sake of the clue that I added in.
			Delay (2000);
			Actor_Says(kActorMcCoy, 840, 14); //00-0840.AUD	Did you hear me?
			Delay (2000);
			Actor_Says(kActorEarlyQ, 540, 19); //18-0540.AUD	Of course, she ain’t half bad looking. My pappy always used to say ‘if there’s grass on the field, it’s time to play ball’.
			Actor_Says(kActorMcCoy, 4800, 14); //00-4800.AUD	You son of a bitch she couldn't object.
			Actor_Says(kActorEarlyQ, 50, 16); //18-0050.AUD	Hey, hey, I don’t hassle you about your private life.
			Actor_Says(kActorMcCoy, 2255, 15); //00-2255.AUD	She was innocent, you bastard!
			Actor_Says(kActorEarlyQ, 530, 18); //18-0530.AUD	This ain’t no daycare center, General.
			Actor_Clue_Acquire(kActorMcCoy, kClueEarlyAttemptedToSeduceLucy, true, kActorEarlyQ);
			Delay (1000);
			Actor_Says(kActorMcCoy, 3405, 13); //00-3405.AUD	Sit down.
			Actor_Says(kActorMcCoy, 4680, 15); // 00-4680.AUD	We're gonna have a little chat.
			Actor_Says(kActorEarlyQ, 410, 12); //18-0410.AUD	Sorry, General. I’ve got a major crisis backstage. One of my girls ran full steam into a pencil and we’re fresh out of tampons.
			Loop_Actor_Walk_To_XYZ(kActorEarlyQ, 45.02, 0.33, 5.52, 0, false, false, false);
			Actor_Face_Actor(kActorMcCoy, kActorEarlyQ, true);
			Actor_Face_Actor(kActorEarlyQ, kActorMcCoy, true);
			Actor_Says(kActorMcCoy, 460, 14); //00-0460.AUD	Hold it right there!
			// If Lucy is a rep McCoy arrests Early for being a rep sympathizier. If not he arrests him for what he did to her.
			if (Game_Flag_Query(kFlagLucyIsReplicant)) {
				Actor_Says(kActorMcCoy, 3090, 15); //00-3090.AUD	You may not be a Rep but you’re a damn Rep sympathizer for sure.
			}
			Actor_Says(kActorMcCoy, 3095, 14); //00-3095.AUD	Now we’re gonna take a little ride downtown.
			Actor_Modify_Friendliness_To_Other(kActorClovis, kActorMcCoy, 1);
			Actor_Modify_Friendliness_To_Other(kActorSteele, kActorMcCoy, 1);
			Actor_Modify_Friendliness_To_Other(kActorGuzza, kActorMcCoy, 1);
			Delay (1000);
			Music_Stop(1u);
			Game_Flag_Set(kFlagEarlyQArrested);
			Actor_Put_In_Set(kActorEarlyQ, kSetPS09);
			Actor_Set_At_XYZ(kActorEarlyQ, -400.43f, 2.06f, -200.77f, 512);
			Game_Flag_Reset(kFlagSpinnerAtNR01);
			Game_Flag_Reset(kFlagSpinnerAtHF01);
			Game_Flag_Set(kFlagSpinnerAtPS01);
			Scene_Exits_Enable();
			Game_Flag_Reset(kFlagMcCoyInNightclubRow);
			Game_Flag_Set(kFlagMcCoyInPoliceStation);
			Outtake_Play(kOuttakeAway1, true, -1);
			Set_Enter(kSetPS09, kScenePS09);
		}
	}
}

void SceneScriptNR04::PlayerWalkedOut() {
#if BLADERUNNER_ORIGINAL_BUGS
#else
	if (Game_Flag_Query(kFlagNR03McCoyThrownOut)) {
		Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
		Ambient_Sounds_Remove_All_Looping_Sounds(1u);
		Music_Stop(1u);
	}
#endif // BLADERUNNER_ORIGINAL_BUGS
}

void SceneScriptNR04::DialogueQueueFlushed(int a1) {
}

void SceneScriptNR04::dialogueWithEarlyQ() {
	Dialogue_Menu_Clear_List();
	if (_vm->_cutContent) {
		DM_Add_To_List(1530, 10, 5, 3); // GIVE DISC
		DM_Add_To_List(1540, 3, 6, 10); // KEEP IT		
	} else {
		DM_Add_To_List(1530, 10, 5, 3); // GIVE DISC
		DM_Add_To_List(1540, 3, 5, 10); // KEEP IT
	}
	Dialogue_Menu_Appear(320, 240);
	int answer = Dialogue_Menu_Query_Input();
	Dialogue_Menu_Disappear();

	if (answer == 1530) { // GIVE DISC
		Loop_Actor_Walk_To_Actor(kActorEarlyQ, kActorMcCoy, 36, false, false);
		Actor_Change_Animation_Mode(kActorMcCoy, 23);
		Actor_Change_Animation_Mode(kActorEarlyQ, 23);
		if (_vm->_cutContent) {
			Delay(800);
			Item_Pickup_Spin_Effect_From_Actor(kModelAnimationVideoDisc, kActorEarlyQ, 0, 0);
			Delay(800);
			if (Game_Flag_Query(kFlagEarlyQIsReplicant)
			&& Game_Flag_Query(kFlagSadikIsReplicant)
			&& Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
				Delay(1500);
				Item_Pickup_Spin_Effect_From_Actor(kModelAnimationDNADataDisc, kActorEarlyQ, 0, 0);
				Delay(1500);
				Item_Pickup_Spin_Effect_From_Actor(kModelAnimationDNADataDisc, kActorEarlyQ, 0, 0);
				Delay(1500);
				Item_Pickup_Spin_Effect_From_Actor(kModelAnimationDNADataDisc, kActorEarlyQ, 0, 0);
				Delay(1500);
				if (Actor_Clue_Query(kActorMcCoy, kClueDNAChew)) {
					Item_Pickup_Spin_Effect_From_Actor(kModelAnimationDNADataDisc, kActorEarlyQ, 0, 0);
					Delay(1500);
					Actor_Clue_Lose(kActorMcCoy, kClueDNAChew);
				}
				Actor_Clue_Lose(kActorMcCoy, kClueDNAMarcus);
				Actor_Clue_Lose(kActorMcCoy, kClueDNASebastian);
				Actor_Clue_Lose(kActorMcCoy, kClueDNAMoraji);			
			}
		} else {
			Delay(1500);
		}
		Actor_Says(kActorEarlyQ, 300, kAnimationModeTalk);
		Actor_Change_Animation_Mode(kActorMcCoy, kAnimationModeIdle);
		Actor_Change_Animation_Mode(kActorEarlyQ, kAnimationModeIdle);
		Actor_Says(kActorEarlyQ, 310, kAnimationModeTalk); 
		if (_vm->_cutContent) {
			Actor_Says(kActorMcCoy, 3450, kAnimationModeTalk);
			Delay(1000);	
			Actor_Says(kActorMcCoy, 5150, 18); //00-5150.AUD	One more thing.
			Actor_Says(kActorEarlyQ, 410, 12); //18-0410.AUD	Sorry, General. I’ve got a major crisis backstage. One of my girls ran full steam into a pencil and we’re fresh out of tampons.
			ADQ_Add(kActorMcCoy, 3525, kAnimationModeTalk); //00-3525.AUD	Ouch.
		} else {
			ADQ_Add(kActorMcCoy, 3450, kAnimationModeTalk);	
		}
		Actor_Set_Targetable(kActorEarlyQ, false);
		Actor_Set_Goal_Number(kActorEarlyQ, kGoalEarlyQNR04Leave);
		Actor_Clue_Lose(kActorMcCoy, kClueEarlyQsClub);
		Scene_Exits_Enable();
	} else if (answer == 1540) { // KEEP IT
		Actor_Says(kActorMcCoy, 8512, 15); 
		Actor_Says(kActorEarlyQ, 320, 12); 
		if (_vm->_cutContent) {
			if (Player_Query_Agenda() != kPlayerAgendaSurly 
			&& Player_Query_Agenda() != kPlayerAgendaErratic) {
				Actor_Says(kActorMcCoy, 3455, 13); //00-3455.AUD	You’ll get it back, if you behave.
				Actor_Says(kActorEarlyQ, 330, 15); //18-0330.AUD	Ah, so it’s blackmail.
				Actor_Says(kActorMcCoy, 3460, 12); //00-3460.AUD	Insurance.
			} else {
				Actor_Says(kActorMcCoy, 8080, 14); //00-8080.AUD	It doesn't matter.
				Delay(1000);
			}
		} else {
			Actor_Says(kActorMcCoy, 3455, 13); //00-3455.AUD	You’ll get it back, if you behave.
			Actor_Says(kActorEarlyQ, 330, 15); //18-0330.AUD	Ah, so it’s blackmail.
			Actor_Says(kActorMcCoy, 3460, 12); //00-3460.AUD	Insurance.
		}
		Actor_Says(kActorEarlyQ, 340, 12); //18-0340.AUD	No more free drinks for you, buddy boy.
		Actor_Says(kActorMcCoy, 3465, 12); //00-3465.AUD	I didn’t get free drinks before.
		Actor_Says(kActorEarlyQ, 350, 16); 
		Actor_Set_Targetable(kActorEarlyQ, false);
		Actor_Set_Goal_Number(kActorEarlyQ, kGoalEarlyQNR04Leave);
		Scene_Exits_Enable();
	}
}

void SceneScriptNR04::druggedEffect(int frame) {
	float colorMap[] = {
		1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 0.0f,
		0.8f, 0.4f, 0.0f,
		0.7f, 0.7f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		0.5f, 0.0f, 0.8f};

	float v3 = (frame - 60) * 0.1f;
	float v4 = (frame % 10) * 0.1f;
	float coef = 1.0f;
	if (frame > 100) {
		coef = 1.0f - (frame - 100) / 20.0f;
	}
	int index = 3 * v3;
	int nextIndex = 3 * v3 + 3;
	float r = ((colorMap[nextIndex + 0] - colorMap[index + 0]) * v4 + colorMap[index + 0]) * coef;
	float g = ((colorMap[nextIndex + 1] - colorMap[index + 1]) * v4 + colorMap[index + 1]) * coef;
	float b = ((colorMap[nextIndex + 2] - colorMap[index + 2]) * v4 + colorMap[index + 2]) * coef;
	Set_Fade_Color(r, g, b);
	if (frame >= 90) {
		Set_Fade_Density(0.75f);
	} else {
		Set_Fade_Density((frame - 60) / 45.0f);
	}
}

void SceneScriptNR04::playNextMusic() {
	int track = Global_Variable_Query(kVariableEarlyQFrontMusic);
	int loop = kMusicLoopPlayOnce;
	if (_vm->_cutContent && Random_Query(0, 2) == 1) {
		loop = kMusicLoopPlayOnceRandomStart;
	}
	if (track == 0) {
		Music_Play(kMusicGothic2, 11, 80, 2, -1, loop, 0);
	} else if (track == 1) {
		Music_Play(kMusicGothic1, 11, 80, 2, -1, loop, 0);
	} else if (track == 2) {
		Music_Play(kMusicGothic3, 11, 80, 2, -1, loop, 0);
	}
	++track;
	if (track > 2) {
		track = 0;
	}
	Global_Variable_Set(kVariableEarlyQFrontMusic, track);
}

} // End of namespace BladeRunner
