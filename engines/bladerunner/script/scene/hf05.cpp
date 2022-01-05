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

enum kHF05Loops {
	kHF05LoopMainLoopNoSpinner = 0,
	kHF05LoopMainLoopSpinner   = 2,
	kHF05LoopArmAnimation      = 4,
	kHF05LoopMainLoopHole      = 5
};

void SceneScriptHF05::InitializeScene() {
	if (Game_Flag_Query(kFlagHF06toHF05)) {
		Setup_Scene_Information(257.0f, 40.63f, 402.0f, 1000);
	} else if (Game_Flag_Query(kFlagHF07toHF05)) {
		Setup_Scene_Information(330.0f, 40.63f, -107.0f, 603);
	} else {
		Setup_Scene_Information(483.0f, 40.63f, -189.0f, 600);
	}

	Scene_Exit_Add_2D_Exit(0, 443, 270, 515, 350, 0);
	if (Global_Variable_Query(kVariableChapter) > 3) {
		Scene_Exit_Add_2D_Exit(1, 367, 298, 399, 349, 2);
	}
	Scene_Exit_Add_2D_Exit(2, 589,   0, 639, 479, 1);

	Ambient_Sounds_Add_Looping_Sound(kSfxRAINAWN1, 40, 1, 1);

	if (Game_Flag_Query(kFlagHF05Hole)) {
		Scene_Loop_Set_Default(kHF05LoopMainLoopHole);
		addAmbientSounds();
	} else if (Game_Flag_Query(kFlagHF06SteelInterruption)) {
		Scene_Loop_Set_Default(kHF05LoopMainLoopSpinner);
		addAmbientSounds();
	} else {
		Scene_Loop_Set_Default(kHF05LoopMainLoopNoSpinner);
	}
}

void SceneScriptHF05::SceneLoaded() {
	Obstacle_Object("MAINBASE", true);
	Unobstacle_Object("BTIRES02", true);
	Unobstacle_Object("LFTIRE02", true);
	if (Game_Flag_Query(kFlagHF05Hole)) {
		Unobstacle_Object("MONTE CARLO DRY", true);
	} else {
		Unobstacle_Object("OBSTACLE_HOLE", true);
	}
	Clickable_Object("TOP CON");
}

bool SceneScriptHF05::MouseClick(int x, int y) {
	return false;
}

bool SceneScriptHF05::ClickedOn3DObject(const char *objectName, bool a2) {
	if (Object_Query_Click("TOP CON", objectName)) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, 95.0f, 40.63f, 308.0f, 0, true, false, false)) {
			Actor_Face_Object(kActorMcCoy, "TOP CON", true);
			if (Actor_Query_In_Set(kActorCrazylegs, kSetHF05)
			 && Actor_Query_Goal_Number(kActorCrazylegs) != kGoalCrazyLegsShotAndHit
			 && Actor_Query_Goal_Number(kActorCrazylegs) != kGoalCrazyLegsLeavesShowroom
			) {
				Actor_Face_Actor(kActorCrazylegs, kActorMcCoy, true);
				Actor_Says(kActorCrazylegs, 480, 13);
				return true;
			}

			if (!Game_Flag_Query(kFlagHF01TalkToLovedOne)
			 ||  Game_Flag_Query(kFlagHF05Hole)
			) {
				Actor_Change_Animation_Mode(kActorMcCoy, 23);
				Sound_Play(kSfxELEBAD1, 100, 0, 0, 50);
				return true;
			}

			Player_Loses_Control();
			Actor_Set_Goal_Number(kActorOfficerLeary, kGoalOfficerLearyPoliceWait60SecondsToAttackHF05);
			Game_Flag_Set(kFlagHF05Hole);
			Game_Flag_Set(kFlagHF07Hole);
			Obstacle_Object("OBSTACLE_HOLE", true);
			Unobstacle_Object("MONTE CARLO DRY", true);

			if (getCompanionActor() != kActorMcCoy) {
				Loop_Actor_Walk_To_XYZ(getCompanionActor(), 181.54f, 40.63f, 388.09f, 0, false, true, false);
				Actor_Face_Actor(kActorMcCoy, getCompanionActor(), true);
				Actor_Face_Actor(getCompanionActor(), kActorMcCoy, true);
				Actor_Says(kActorMcCoy, 1785, kAnimationModeTalk);
				Actor_Says(kActorMcCoy, 1790, kAnimationModeTalk); //00-1790.AUD	But wait for my signal before you drop it in.
				// Added in some dialogue.
				if (_vm->_cutContent) {
				Delay (2000);
				Actor_Says(kActorMcCoy, 1795, kAnimationModeTalk); //00-1795.AUD	Hang on!
				}

			}

			Actor_Face_Heading(kActorMcCoy, 0, false);
			Actor_Change_Animation_Mode(kActorMcCoy, 23);
			Scene_Loop_Set_Default(kHF05LoopMainLoopHole);
			Scene_Loop_Start_Special(kSceneLoopModeOnce, kHF05LoopArmAnimation, true);


			if (getCompanionActor() == kActorMcCoy) {
				ADQ_Flush();
				ADQ_Add(kActorVoiceOver, 940, -1);
				Ambient_Sounds_Play_Sound(kSfxLABMISC2, 50, 99, 0, 0);
				Delay(1500);
				Loop_Actor_Walk_To_XYZ(kActorMcCoy, 181.54f, 40.63f, 388.09f, 0, false, true, false);
				Actor_Face_Heading(kActorMcCoy, 0, false);
				Actor_Change_Animation_Mode(kActorMcCoy, 23);
				Actor_Clue_Lose(kActorMcCoy, kClueBomb);
			} else {
				if (getCompanionActor() == kActorDektora) {
					Actor_Face_Heading(kActorDektora, 0, false);
					Ambient_Sounds_Play_Sound(kSfxLABMISC2, 50, 99, 0, 0);
					Delay(3000);
					Actor_Face_Heading(kActorDektora, 0, false);
					Actor_Change_Animation_Mode(kActorDektora, 23);
				} else {
					Actor_Face_Heading(kActorLucy, 0, false);
					Ambient_Sounds_Play_Sound(kSfxLABMISC2, 50, 99, 0, 0);
					Delay(3000);
					Actor_Face_Heading(kActorLucy, 0, false);
					Actor_Change_Animation_Mode(kActorLucy, 13);
				}
				Actor_Face_Actor(kActorMcCoy, getCompanionActor(), true);
				Actor_Says(kActorMcCoy, 1805, kAnimationModeTalk); //00-1805.AUD	Now!
				if (_vm->_cutContent) {
					// Added in some lines for Dektora and Lucy. The lines are said just after McCoy drops the car into the sewers.
					Delay (5000);
					if (getCompanionActor() == kActorDektora) {
						if (!Game_Flag_Query(kFlagDektoraIsReplicant)) {
						Actor_Says(kActorDektora, 180, kAnimationModeTalk); //03-0180.AUD	What are you waiting for?
						Actor_Says(kActorDektora, 190, kAnimationModeTalk); //03-0190.AUD	They’ll be coming in any second!
						}
					}
					if (getCompanionActor() == kActorLucy) {
						Actor_Says(kActorLucy, 460, kAnimationModeTalk); //06-0460.AUD	What are you waiting for?
						Actor_Says(kActorLucy, 470, kAnimationModeTalk); //06-0470.AUD	They’ll be coming any second!
					}
				}
			}
			Player_Gains_Control();
		}
		return true;
	}
	return false;
}

bool SceneScriptHF05::ClickedOnActor(int actorId) {
	if (actorId == kActorCrazylegs) {
		// Note: dialogueWithCrazylegs1() makes sense only for Acts 3 and 4.
		//      by Act 5, McCoy is done interrogating, and it would also be weird
		//      if he is asking questions about Lucy or Dektora, with them standing next to him.
		// TODO Recheck: Is McCoy allowed to click on CrazyLegs in Act5 while Dektora or Lucy are there too?
#if BLADERUNNER_ORIGINAL_BUGS
		if (!Loop_Actor_Walk_To_Actor(kActorMcCoy, kActorCrazylegs, 60, true, false)) {
			Actor_Face_Actor(kActorMcCoy, kActorCrazylegs, true);
			Actor_Face_Actor(kActorCrazylegs, kActorMcCoy, true);
			dialogueWithCrazylegs1();
		}
#else
		// Don't (re)start a dialogue with CrayLegs if he is leaving or insulted by McCoy drawing his gun
		if (Actor_Query_Goal_Number(kActorCrazylegs) != kGoalCrazyLegsLeavesShowroom
		    && Actor_Query_Goal_Number(kActorCrazylegs) != kGoalCrazyLegsMcCoyDrewHisGun) {
			if (!Loop_Actor_Walk_To_Actor(kActorMcCoy, kActorCrazylegs, 60, true, false)) {
				Actor_Face_Actor(kActorMcCoy, kActorCrazylegs, true);
				Actor_Face_Actor(kActorCrazylegs, kActorMcCoy, true);
				dialogueWithCrazylegs1();
			}
		} else {
			Actor_Face_Actor(kActorMcCoy, kActorCrazylegs, true);
			Actor_Says(kActorMcCoy, 5560, 15); // Hey
		}
#endif // BLADERUNNER_ORIGINAL_BUGS
	}
	return false;
}

bool SceneScriptHF05::ClickedOnItem(int itemId, bool a2) {
	return false;
}

bool SceneScriptHF05::ClickedOnExit(int exitId) {
	if (exitId == 0) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, 483.0f, 40.63f, -189.0f, 0, true, false, false)) {
			if (!Game_Flag_Query(kFlagHF05PoliceAttacked)) {
				Game_Flag_Set(kFlagHF05toHF01);
				Set_Enter(kSetHF01, kSceneHF01);
			}
		}
		return true;
	}

	if (exitId == 1) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, 330.0f, 40.63f, -85.0f, 0, true, false, false)) {
			if (!Game_Flag_Query(kFlagHF05PoliceAttacked)) {
				int affectionTowardsActor = getAffectionTowardsActor();
				if (Game_Flag_Query(kFlagHF05PoliceArrived)
				 && Game_Flag_Query(kFlagHF07Hole)
				 && affectionTowardsActor != -1
				) {
					Actor_Face_Actor(kActorMcCoy, affectionTowardsActor, true);
					Actor_Says(kActorMcCoy, 1810, 16);
				}
				Game_Flag_Set(kFlagHF05toHF07);
				Set_Enter(kSetHF07, kSceneHF07);
			}
		}
		return true;
	}

	if (exitId == 2) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, 277.0f, 40.63f, 410.0f, 0, true, false, false)) {
			if (!Game_Flag_Query(kFlagHF05PoliceAttacked)) {
				Game_Flag_Set(kFlagHF05toHF06);
				Set_Enter(kSetHF06, kSceneHF06);
			}
		}
		return true;
	}
	return false;
}

bool SceneScriptHF05::ClickedOn2DRegion(int region) {
	return false;
}

void SceneScriptHF05::SceneFrameAdvanced(int frame) {
	switch (frame) {
	case 126:
		Sound_Play(kSfxMAGMOVE1, 90, -20,  70, 50);
		break;

	case 152:
		Sound_Play(kSfxDORSLID2, 90,   0,   0, 50);
		break;

	case 156:
		Sound_Play(kSfxLOWERN1,  47, 100, 100, 50);
		break;

	case 161:
		Sound_Play(kSfxDORSLID1, 90,   0,   0, 50);
		break;

	case 176:
		Sound_Play(kSfxMAGCHNK1, 32, 100, 100, 50);
		break;

	case 178:
		Sound_Play(kSfxRAISEY1,  47, 100, 100, 50);
		break;

	case 179:
		Sound_Play(kSfxCAREXPL1, 90,   0,   0, 50);
		Music_Play(kMusicBatl226M, 50, 0, 2, -1, kMusicLoopPlayOnce, 0);
		break;

	case 186:
		Sound_Play(kSfxCARCREK1, 32, 100, 100, 50);
		break;

	case 209:
		Sound_Play(kSfxMAGMOVE2, 90, 100, -20, 50);
		break;

	case 243:
		Sound_Play(kSfxLOWERY1,  40, -20, -20, 50);
		break;

	case 261:
		Sound_Play(kSfxCARLAND1, 47, -20, -20, 50);
		break;

	case 268:
		Sound_Play(kSfxMAGDROP1, 58, -20, -20, 50);
		break;

	case 269:
		Sound_Play(kSfxRAISEN1,  43, -20, -20, 50);
		break;
	}
	//return true;
}

void SceneScriptHF05::ActorChangedGoal(int actorId, int newGoal, int oldGoal, bool currentSet) {
	if (actorId == kActorOfficerLeary
	 && newGoal == kGoalOfficerLearyPoliceAboutToAttackHF05
	) {
		Game_Flag_Set(kFlagHF05PoliceAttacked);
		policeAttack();
	}
	//return false;
}

void SceneScriptHF05::PlayerWalkedIn() {
	// Made it so McCoy has his gun holstered when he enters Crazys store.
	if (_vm->_cutContent) {
		Player_Set_Combat_Mode(false);
	}
	if (Game_Flag_Query(kFlagHF01TalkToLovedOne)) {
		int affectionTowardsActor = getAffectionTowardsActor();
		if (Game_Flag_Query(kFlagHF01TalkToLovedOne)
		 && affectionTowardsActor != -1
		) {
			Actor_Put_In_Set(affectionTowardsActor, kSetHF05);
			Actor_Force_Stop_Walking(affectionTowardsActor);
			if (Game_Flag_Query(kFlagHF01toHF05)) {
				Actor_Set_At_XYZ(affectionTowardsActor, 506.81f, 40.63f, -140.92f, 0);
				Async_Actor_Walk_To_Waypoint(affectionTowardsActor, 437, 36, false);
			} else if (Game_Flag_Query(kFlagHF06toHF05)) {
				Actor_Set_At_XYZ(affectionTowardsActor, 288.0f, 40.63f, 410.0f, 909);
			} else if (Game_Flag_Query(kFlagHF07toHF05)) {
				Actor_Set_At_XYZ(affectionTowardsActor, 298.0f, 40.63f, -107.0f, 512);
			} else {
				Actor_Set_At_XYZ(affectionTowardsActor, 284.0f, 40.63f, 286.0f, 0);
			}
		}

		if (Game_Flag_Query(kFlagHF05PoliceAttacked)) {
			policeAttack();
		} else if (Actor_Clue_Query(kActorMcCoy, kClueSpinnerKeys)
		        || Game_Flag_Query(kFlagHF06SteelInterruption)
		) {
			if ( Game_Flag_Query(kFlagHF06SteelInterruption)
			 && !Game_Flag_Query(kFlagHF05PoliceArrived)
			) {
				Game_Flag_Set(kFlagHF05PoliceArrived);
				Music_Play(kMusicBatl226M, 40, 0, 2, -1, kMusicLoopPlayOnce, 0);
				Actor_Says(kActorOfficerGrayford, 200, kAnimationModeTalk);
				Actor_Says(kActorOfficerGrayford, 210, kAnimationModeTalk);
				Actor_Set_Goal_Number(kActorOfficerLeary, kGoalOfficerLearyPoliceWait120SecondsToAttackHF05);
				if (getCompanionActor() ==  kActorDektora) {
					talkWithDektora();
				} else if (getCompanionActor() == kActorLucy) {
					talkWithLucy();
				}
			}
		} else {
			talkWithCrazylegs3(affectionTowardsActor);
		}
	} else if (Game_Flag_Query(kFlagHF01toHF05)) {
		Loop_Actor_Walk_To_XYZ(kActorMcCoy, 399.0f, 40.63f, -85.0f, 0, false, false, false);
	} else if (Game_Flag_Query(kFlagHF07toHF05)) {
		Actor_Set_At_XYZ(kActorMcCoy, 346.0f, 4.63f, -151.0f, 603);
		Loop_Actor_Travel_Stairs(kActorMcCoy, 4, true, kAnimationModeIdle);
	}

	if (Actor_Query_In_Set(kActorCrazylegs, kSetHF05)) {
		if (!Game_Flag_Query(kFlagHF05CrazyLegsTalk1)) {
			talkWithCrazyLegs1();
			Game_Flag_Set(kFlagHF05CrazyLegsTalk1);
		} else if (!Game_Flag_Query(kFlagHF05CrazyLegsTalk2)
		        &&  Global_Variable_Query(kVariableChapter) == 3
		) {
			talkWithCrazyLegs2();
			Game_Flag_Set(kFlagHF05CrazyLegsTalk2);
		}
	}

	Game_Flag_Reset(kFlagHF01toHF05);
	Game_Flag_Reset(kFlagHF06toHF05);
	Game_Flag_Reset(kFlagHF07toHF05);

	//return false;
}

void SceneScriptHF05::PlayerWalkedOut() {
	if (Actor_Query_Goal_Number(kActorCrazylegs) == kGoalCrazyLegsMcCoyDrewHisGun) {
		Actor_Set_Goal_Number(kActorCrazylegs, kGoalCrazyLegsLeavesShowroom);
	}
	Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
	Ambient_Sounds_Remove_All_Looping_Sounds(1u);
}

void SceneScriptHF05::DialogueQueueFlushed(int a1) {
}

void SceneScriptHF05::talkWithCrazyLegs2() {
	Loop_Actor_Walk_To_Actor(kActorCrazylegs, kActorMcCoy, 72, false, false);
	Actor_Face_Actor(kActorCrazylegs, kActorMcCoy, true);
	Actor_Face_Actor(kActorMcCoy, kActorCrazylegs, true);
	Actor_Says(kActorCrazylegs, 370, kAnimationModeTalk);
	// Made it so when you enter Crazys store a second time if McCoy is surly or erratic he is mean towards Crazylegs. This annoys Crazylegs and he leaves the room.
	if (_vm->_cutContent) {
		if (Player_Query_Agenda() == kPlayerAgendaSurly
		|| (Player_Query_Agenda() == kPlayerAgendaErratic)) {	
			Actor_Says(kActorCrazylegs, 380, 14); //09-0380.AUD	You’ve been thinking about the Caddy, haven’t you?
			Actor_Says(kActorMcCoy, 7815, kAnimationModeTalk); //00-7815.AUD	No.
			Actor_Says(kActorCrazylegs, 990, 16); //09-0990.AUD	I’m looking to make deals, you know?
			Actor_Says(kActorCrazylegs, 980, 14); //09-0980.AUD	You want the Caddy or not?
			Actor_Says(kActorMcCoy, 1875, kAnimationModeTalk); //00-1875.AUD	I wouldn’t drag that bucket of bolts if you paid me.
			Actor_Says(kActorCrazylegs, 970, 16); //09-0970.AUD	Hey, I’d never turn away a customer but… you’re getting to be a pain in the ass.
			Actor_Says(kActorMcCoy, 2660, kAnimationModeTalk); //00-2660.AUD	That breaks my heart.
			Actor_Says(kActorCrazylegs, 1000, 16); //09-1000.AUD	I got customers on the line, so I ain’t got time to chit chat.
			Actor_Set_Goal_Number(kActorCrazylegs, kGoalCrazyLegsLeavesShowroom);
		} else {
			Actor_Says(kActorMcCoy, 1855, kAnimationModeTalk);
			Actor_Says(kActorCrazylegs, 380, 12);
			Actor_Says(kActorCrazylegs, 390, 14);
			Actor_Says(kActorCrazylegs, 400, 15);
			Actor_Says(kActorCrazylegs, 410, 16);
			Actor_Says(kActorMcCoy, 1860, kAnimationModeTalk);
			Actor_Says(kActorCrazylegs, 420, kAnimationModeTalk);
			Actor_Says(kActorMcCoy, 1865, kAnimationModeTalk);
		}
	} else {
		Actor_Says(kActorMcCoy, 1855, kAnimationModeTalk);
		Actor_Says(kActorCrazylegs, 380, 12);
		Actor_Says(kActorCrazylegs, 390, 14);
		Actor_Says(kActorCrazylegs, 400, 15);
		Actor_Says(kActorCrazylegs, 410, 16);
		Actor_Says(kActorMcCoy, 1860, kAnimationModeTalk);
		Actor_Says(kActorCrazylegs, 420, kAnimationModeTalk);
		Actor_Says(kActorMcCoy, 1865, kAnimationModeTalk);
	}
}

void SceneScriptHF05::dialogueWithCrazylegs1() {
	Dialogue_Menu_Clear_List();
#if BLADERUNNER_ORIGINAL_BUGS
	if (Actor_Clue_Query(kActorMcCoy, kClueGrigoriansNote) // cut feature? there is no way how to obtain this clue
	 && Global_Variable_Query(kVariableChapter) == 3
	) {
		DM_Add_To_List_Never_Repeat_Once_Selected(1180, 3, 6, 7); // ADVERTISEMENT
	}
#else
	// Restored feature - Original: it is impossible to obtain this clue
	if (Actor_Clue_Query(kActorMcCoy, kClueCrazysInvolvement)
	 && Global_Variable_Query(kVariableChapter) == 3
	) {
		// This dialogue point does not talk about Grigorian's Note
		// but rather a Note that CrazyLegs wrote on one of his flyers
		// kClueCrazysInvolvement is only acquired in _cutContent (Restored Content) mode
		// so no need to add that extra check in the if clause.
		DM_Add_To_List_Never_Repeat_Once_Selected(1180, 3, 6, 7); // ADVERTISEMENT
	}
#endif // BLADERUNNER_ORIGINAL_BUGS
	// Added in flag so this topic will activate after you talk to Crazy about the car registration. The reason for this is because I made the Crazylegs interview 1 
	// clue feature the dialogue of this topic since it not only includes that facts mentioned in car registration but also some extra facts that are also relevant such as mentioning 
	// Gordo being with Dektora and saying that they were after a police spinner.
	if (_vm->_cutContent) {
		if (Game_Flag_Query(kFlagCrazylegsTalkCarRegistration)) {
			DM_Add_To_List_Never_Repeat_Once_Selected(1190, 2, 7, 4); // WOMAN
		}
	} else if (Actor_Clue_Query(kActorMcCoy, kClueCrazylegsInterview1)) {
		// kClueCrazylegsInterview1 is acquired (after bug fix)
		// only when Dektora has bought the car (kClueCarRegistration1)
		// and McCoy has asked Crazylegs for the CAR REGISTRATION topic already
		DM_Add_To_List_Never_Repeat_Once_Selected(1190, 2, 7, 4); // WOMAN
	}
#if BLADERUNNER_ORIGINAL_BUGS
	if (Actor_Clue_Query(kActorMcCoy, kClueDektorasDressingRoom)) {
		DM_Add_To_List_Never_Repeat_Once_Selected(1200, 5, 5, 3); // WOMAN'S PHOTO
	}
#else
// Made it so if you have any photo of Dektora you are able to show it to Crazylegs and not just the dressing room photo. Also this option will only be available
// if you seleced the woman option earlier since Crazylegs describes Dektora in that option and it would make no sense for him to do that if you showed him the photo.
	if (_vm->_cutContent) {
		if (Game_Flag_Query(kFlagCrazylegsTalkWoman)) {
			if (Actor_Clue_Query(kActorMcCoy, kClueChinaBar)
				|| Actor_Clue_Query(kActorMcCoy, kClueDektorasDressingRoom)
				|| Actor_Clue_Query(kActorMcCoy, kClueWomanInAnimoidRow)
				|| Actor_Clue_Query(kActorMcCoy, kClueLucyWithDektora)
				|| Actor_Clue_Query(kActorMcCoy, kClueOuterDressingRoom)
				) {
				DM_Add_To_List_Never_Repeat_Once_Selected(1200, 5, 5, 3); // WOMAN'S PHOTO
			}
		}
	} else if ((Actor_Clue_Query(kActorMcCoy, kClueDektorasDressingRoom)
	    && Actor_Clue_Query(kActorMcCoy, kClueCrazylegsInterview1))
	) {
		// kClueDektorasDressingRoom is acquired from EarlyQ at his office (nr04)
		// McCoy should only ask about this if CrazyLegs already told him at least about the sexy blonde (kClueCrazylegsInterview1)
		// TODO Maybe McCoy can show the kClueWomanInAnimoidRow
		//      - if he has the kClueChinaBar (where she is with Clovis) too?
		//      - or if he met Dektora already.
		DM_Add_To_List_Never_Repeat_Once_Selected(1200, 5, 5, 3); // WOMAN'S PHOTO
	}
#endif // BLADERUNNER_ORIGINAL_BUGS
	if (Actor_Clue_Query(kActorMcCoy, kClueLucy)
	 && Actor_Query_Goal_Number(kActorLucy) != kGoalLucyGone
	) {
		DM_Add_To_List_Never_Repeat_Once_Selected(1210, 4, 6, 2); // LUCY'S PHOTO
	}
#if BLADERUNNER_ORIGINAL_BUGS
	if (Actor_Clue_Query(kActorMcCoy, kClueGrigoriansResources) // it is impossible to obtain this clue
	 || (Actor_Clue_Query(kActorMcCoy, kClueGrigoriansNote) // it is impossible to obtain this clue either
	  && Global_Variable_Query(kVariableChapter) == 3
	 )
	) {
		DM_Add_To_List_Never_Repeat_Once_Selected(1220, -1, 2, 8); // GRIGORIAN
	}
#else
	if (Global_Variable_Query(kVariableChapter) == 3
	    && (Actor_Clue_Query(kActorMcCoy, kClueGrigoriansResources) // Restored feature - Original: it is impossible to obtain this clue
	        || Actor_Clue_Query(kActorMcCoy, kClueGrigoriansNote)) // Restored feature - Original: it is impossible to obtain this clue either
	) {
		// The chapter check is done for both cases:
		//      either McCoy has kClueGrigoriansResources or kClueGrigoriansNote
		DM_Add_To_List_Never_Repeat_Once_Selected(1220, -1, 2, 8); // GRIGORIAN
	}
#endif
	if (Actor_Clue_Query(kActorMcCoy, kClueCarRegistration1)
	 || Actor_Clue_Query(kActorMcCoy, kClueCarRegistration3)
	) {
		// Dektora bought the car or Blake Williams (which is an alias, that Clovis used)
		// Gordo is with Dektora when making the car purchase (as revealed by CrazyLegs in the "WOMAN" question).
		DM_Add_To_List_Never_Repeat_Once_Selected(1230, 4, 7, -1); // CAR REGISTRATION
	}

	if (!Dialogue_Menu_Query_List_Size()) {
		Actor_Says(kActorMcCoy, 1880, 15);
		Actor_Says(kActorCrazylegs, 490, kAnimationModeTalk);
		Actor_Says(kActorMcCoy, 1885, kAnimationModeTalk);
		Actor_Says(kActorCrazylegs, 500, 16); //09-0500.AUD	You can take it anyway you want. Just don’t take it for a test-drive in the Fourth Sector.
		// Added in some banter dialogue.
		if (_vm->_cutContent) {
			Actor_Says(kActorMcCoy, 8615, kAnimationModeTalk);	//00-8615.AUD	Heard anything on the street?
			Actor_Says(kActorCrazylegs, 1150, kAnimationModeTalk); //09-1150.AUD	Only thing I know is that the best deals you can make are right in this showroom.
	}
		return;
	}

	Dialogue_Menu_Add_DONE_To_List(1240); // DONE

	Dialogue_Menu_Appear(320, 240);
	int answer = Dialogue_Menu_Query_Input();
	Dialogue_Menu_Disappear();

	switch (answer) {
	case 1180: // ADVERTISEMENT
		Actor_Says(kActorMcCoy, 1890, 23);
		if (_vm->_cutContent) {
			// McCoy shows the sales pamphlet (from Dektora's Vanity drawer) to CrazyLegs
			Item_Pickup_Spin_Effect_From_Actor(kModelAnimationTyrellSalesPamphlet, kActorMcCoy, 0, 0);
		}
		Actor_Says(kActorCrazylegs, 510, kAnimationModeTalk);
		if (_vm->_cutContent) {
			Actor_Says(kActorCrazylegs, 520, kAnimationModeTalk);
		}
		Actor_Says(kActorMcCoy, 1920, 23);
		if (_vm->_cutContent) {
			// McCoy shows the note he found inside the sales pamphlet (from Dektora's Vanity drawer) to CrazyLegs
			Item_Pickup_Spin_Effect_From_Actor(kModelAnimationLetter, kActorMcCoy, 0, 0);
		}
		Actor_Says(kActorMcCoy, 1925, kAnimationModeTalk);
		Actor_Says(kActorCrazylegs, 530, 12);
		Actor_Says(kActorMcCoy, 1930, 18);
		Actor_Says(kActorCrazylegs, 540, 14);
		Actor_Says(kActorMcCoy, 1935, 14);
		Actor_Says(kActorCrazylegs, 550, 16);
		Actor_Says(kActorMcCoy, 1940, 15);
		Actor_Says(kActorMcCoy, 1945, -1);
		// CrazyLegs cuts his sentence short here. He is not interrupted.
		Actor_Says(kActorCrazylegs, 560, 15);
		Actor_Says(kActorCrazylegs, 570, 16); //09-0570.AUD	Hey, they came to me first. I didn’t go to them.
		// Added in some dialogue.
		if (_vm->_cutContent) {
			Actor_Says(kActorMcCoy, 3910, 16); //00-3910.AUD	You’re lying.
			Actor_Says(kActorCrazylegs, 1170, 14); //09-1170.AUD	I might lie about a sticker price but not about this.
		}
		Actor_Says(kActorMcCoy, 1950, 17); //00-1950.AUD	Unscrupulous businessman, eh?
		dialogueWithCrazylegs2();
		break;

	case 1190: // WOMAN
		Actor_Says(kActorMcCoy, 1895, kAnimationModeIdle);
		Actor_Says(kActorCrazylegs, 620, kAnimationModeTalk);
		Actor_Says(kActorCrazylegs, 630, 12);
		Actor_Says(kActorMcCoy, 2000, 13);
		Actor_Says(kActorCrazylegs, 640, 14);
		Actor_Says(kActorCrazylegs, 650, 15);
		Actor_Says(kActorCrazylegs, 660, 16);
		Actor_Says(kActorMcCoy, 2005, kAnimationModeIdle);
		Actor_Says(kActorMcCoy, 2010, kAnimationModeTalk);
		Actor_Says(kActorCrazylegs, 670, kAnimationModeTalk);
		Actor_Says(kActorCrazylegs, 680, 12);
		Actor_Says(kActorCrazylegs, 690, 14);
		Actor_Says(kActorMcCoy, 2015, 14);
		Actor_Says(kActorCrazylegs, 700, 15);
		Actor_Says(kActorMcCoy, 2020, 18);
		// Made it so the crazylegs interview 1 clue is for this dialogue instead. The reason is it contains a lot more information than the car registration topic.
		// I mean not only does Crazy describe Dektora in this topic, but he also mentions Gordo and how they asked for a police spinner. Pretty relevant information.
		if (_vm->_cutContent) {
			Actor_Clue_Acquire(kActorMcCoy, kClueCrazylegsInterview1, true, kActorCrazylegs);
		}
		// Inserted a flag to make the womans photo option available.
		Game_Flag_Set(kFlagCrazylegsTalkWoman);
		break;

	case 1200: // WOMAN'S PHOTO
		Actor_Says(kActorMcCoy, 1900, 23);
		Actor_Says(kActorCrazylegs, 710, 16);
		Actor_Says(kActorMcCoy, 2025, kAnimationModeIdle);
		Actor_Says(kActorCrazylegs, 720, kAnimationModeTalk);
		Actor_Says(kActorCrazylegs, 730, 12);
		break;

	case 1210: // LUCY'S PHOTO
		// Added in some dialogue.
		if (_vm->_cutContent) {
			Actor_Says(kActorMcCoy, 5600, 13); //00-5600.AUD	Let me ask you something.
			Actor_Says(kActorCrazylegs, 1140, 14); //09-1140.AUD	You can bet I’ve heard something you might be interested in.
		}
		Actor_Says(kActorMcCoy, 1905, 23); //00-1905.AUD	How about this girl. She look familiar?
		Actor_Says(kActorCrazylegs, 740, 14);
		Actor_Says(kActorMcCoy, 2030, 13);
		Actor_Says(kActorCrazylegs, 750, 15);
		Actor_Says(kActorMcCoy, 2035, 18);
		Actor_Says(kActorCrazylegs, 760, 16);
		Actor_Says(kActorCrazylegs, 770, kAnimationModeTalk); //09-0770.AUD	She looks like the kind of girl you see there all the time.
		if (_vm->_cutContent) {
			if (Player_Query_Agenda() == kPlayerAgendaSurly 
			|| Player_Query_Agenda() == kPlayerAgendaErratic) {
				Actor_Says(kActorMcCoy, 8640, 18); //00-8640.AUD	That's useless.
				Actor_Says(kActorCrazylegs, 1180, kAnimationModeTalk);	//	09-1180.AUD	What do you expect? I sell cars for a living.
			} else {
				Actor_Says(kActorMcCoy, 2040, kAnimationModeIdle);
			}	
		} else {				
			Actor_Says(kActorMcCoy, 2040, kAnimationModeIdle);
		}
		break;

	case 1220: // GRIGORIAN
		// This dialogue does not mention Grigorian's note explicitly
		// but it does mention Grigorian talking about friends with resources.
		// So it needs that clue as a prerequisite
		// for that specific part of the dialogue (McCoy's cues only)
		Actor_Says(kActorMcCoy, 1910, kAnimationModeTalk);
		Actor_Says(kActorCrazylegs, 780, 12);
		Actor_Says(kActorMcCoy, 2045, 17);
#if BLADERUNNER_ORIGINAL_BUGS
		Actor_Says(kActorMcCoy, 2050, kAnimationModeTalk);
		Actor_Says(kActorCrazylegs, 790, 14);
#else
		if (Actor_Clue_Query(kActorMcCoy, kClueGrigoriansResources)) {
			Actor_Says(kActorMcCoy, 2050, kAnimationModeTalk);
			Actor_Says(kActorCrazylegs, 790, 14);
		}
#endif
		Actor_Says(kActorMcCoy, 2055, 19);
		Actor_Says(kActorMcCoy, 2060, -1);
		Actor_Says(kActorCrazylegs, 800, 15);
		Actor_Says(kActorMcCoy, 2065, 18);
		Actor_Says(kActorMcCoy, 2070, 14);
		Actor_Says(kActorCrazylegs, 810, 16);
		dialogueWithCrazylegs2();
		break;

	case 1230: // CAR REGISTRATION
		Actor_Says(kActorMcCoy, 1915, 12);
		if (Actor_Clue_Query(kActorMcCoy, kClueCarRegistration1)) {
			Actor_Says(kActorCrazylegs, 820, kAnimationModeTalk);
			Actor_Says(kActorMcCoy, 2075, 13);
			Actor_Says(kActorCrazylegs, 830, 12);
			Actor_Says(kActorCrazylegs, 840, 14);
			Actor_Says(kActorCrazylegs, 850, 15);
			Actor_Says(kActorMcCoy, 2080, kAnimationModeTalk);
			Actor_Says(kActorCrazylegs, 860, 16);
			Actor_Says(kActorCrazylegs, 870, kAnimationModeTalk);
			// Added in a flag so the woman option will activate after talking to Crazy about the car registration.
			if (_vm->_cutContent) {
				Game_Flag_Set(kFlagCrazylegsTalkCarRegistration);
			}
#if BLADERUNNER_ORIGINAL_BUGS
#else
			// This clue was never acquired, even though it is checked in KIA
			// (so that it appears as a recording in KIA if acquired)
			// It also enables the "WOMAN" conversation option with CrazyLegs.
			if (!_vm->_cutContent) {
				Actor_Clue_Acquire(kActorMcCoy, kClueCrazylegsInterview1, true, kActorCrazylegs);
			}
#endif // BLADERUNNER_ORIGINAL_BUGS
		} else if (Actor_Clue_Query(kActorMcCoy, kClueCarRegistration3)) {
			Actor_Says(kActorCrazylegs, 880, 12);
			Actor_Says(kActorCrazylegs, 890, 14);
			Actor_Says(kActorMcCoy, 2085, kAnimationModeTalk);
			Actor_Says(kActorCrazylegs, 900, 15);
			Actor_Says(kActorMcCoy, 2090, 19);
			Actor_Says(kActorCrazylegs, 910, 16);
			Actor_Says(kActorMcCoy, 2095, 14);
			Actor_Says(kActorCrazylegs, 920, kAnimationModeTalk);
			Actor_Says(kActorMcCoy, 2100, 15);
			Actor_Says(kActorCrazylegs, 930, 12);
			Actor_Says(kActorCrazylegs, 940, 14);
			Actor_Says(kActorMcCoy, 2105, kAnimationModeTalk);
			Actor_Says(kActorCrazylegs, 950, 15);
			Actor_Says(kActorMcCoy, 2110, kAnimationModeIdle);
			Actor_Says(kActorCrazylegs, 960, 16); //09-0960.AUD	Yeah. Pretty scary. But, heck, I never turn away a customer.
			// Made it so you receive the Crazylegs interview 2 clue if Clovis bought the car. 
			if (_vm->_cutContent) {
				Actor_Clue_Acquire(kActorMcCoy, kClueCrazylegsInterview2, true, kActorCrazylegs);
			}
		}
		break;
	}
}

void SceneScriptHF05::dialogueWithCrazylegs2() { // Restored feature - Original: it is impossible to obtain this clue
	Dialogue_Menu_Clear_List();
	DM_Add_To_List_Never_Repeat_Once_Selected(1250, -1, -1, 10); // ARREST
	DM_Add_To_List_Never_Repeat_Once_Selected(1260, 10,  5, -1); // WARNING

	Dialogue_Menu_Appear(320, 240);
	int answer = Dialogue_Menu_Query_Input();
	Dialogue_Menu_Disappear();

	if (answer == 1250) { // ARREST
		Actor_Says(kActorMcCoy, 1955, 17);
		Actor_Says(kActorMcCoy, 1960, 23);
		Item_Pickup_Spin_Effect(kModelAnimationSpinnerKeys, 315, 327);
		Delay(2000);
		Actor_Says(kActorMcCoy, 1980, 23);
		Actor_Says(kActorMcCoy, 1985, kAnimationModeTalk);
		Actor_Says(kActorCrazylegs, 580, kAnimationModeTalk);
		Actor_Says(kActorCrazylegs, 590, 15);
		Actor_Says(kActorMcCoy, 1990, 17);
		Actor_Says(kActorCrazylegs, 600, 16);
		Actor_Says(kActorMcCoy, 1995, kAnimationModeTalk);
		// Made it so you receive the Crazylegs grovels clue.
		if (_vm->_cutContent) {
			Actor_Clue_Acquire(kActorMcCoy, kClueCrazylegGrovels, true, kActorCrazylegs);
		}
		Game_Flag_Set(kFlagCrazylegsArrested);
		Actor_Put_In_Set(kActorCrazylegs, kSetPS09);
		// This XYZ is awry (won't show Crazylegs inside a cell or at all in the PS09 scene)
		// but it is eventually overridden by the PS09 script, which puts Crazylegs at the right spot
		Actor_Set_At_XYZ(kActorCrazylegs, -315.15f, 0.0f, 241.06f, 583);
		Actor_Set_Goal_Number(kActorCrazylegs, kGoalCrazyLegsIsArrested);
		Game_Flag_Set(kFlagCrazylegsArrestedTalk);
		if (Game_Flag_Query(kFlagSpinnerAtNR01)) {
			Set_Enter(kSetNR01, kSceneNR01);
		} else {
			Game_Flag_Set(kFlagHF05toHF01);
			Set_Enter(kSetHF01, kSceneHF01);
		}
	} else if (answer == 1260) { // WARNING
		Actor_Says(kActorMcCoy, 1965, 12);
		Actor_Says(kActorMcCoy, 1970, kAnimationModeTalk);
		Actor_Says(kActorMcCoy, 1975, kAnimationModeTalk);
		Actor_Says(kActorCrazylegs, 610, 16);
	}
}

int SceneScriptHF05::getAffectionTowardsActor() {
	if (Global_Variable_Query(kVariableAffectionTowards) == kAffectionTowardsDektora
	 && Actor_Query_Goal_Number(kActorDektora) != kGoalDektoraGone
	) {
		return kActorDektora;
	}
	if (Global_Variable_Query(kVariableAffectionTowards) == kAffectionTowardsLucy
	 && Actor_Query_Goal_Number(kActorLucy) != kGoalLucyGone
	) {
		return kActorLucy;
	}
	return -1;
}

void SceneScriptHF05::policeAttack() {
	Actor_Force_Stop_Walking(kActorMcCoy);
	Actor_Put_In_Set(kActorOfficerLeary, kSetHF05);
	Actor_Set_At_XYZ(kActorOfficerLeary, 430.4f, 40.63f, -258.18f, 300);
	Actor_Put_In_Set(kActorOfficerGrayford, kSetHF05);
	Actor_Set_At_XYZ(kActorOfficerGrayford, 526.4f, 37.18f, -138.18f, 300);
	ADQ_Flush();
	ADQ_Add(kActorOfficerGrayford, 260, -1);
	Player_Loses_Control();
	Non_Player_Actor_Combat_Mode_On(kActorOfficerLeary, kActorCombatStateUncover, true, kActorMcCoy, 4, kAnimationModeCombatIdle, kAnimationModeCombatWalk, kAnimationModeCombatRun, 0, 0, 100, 100, 1200, true);
	Non_Player_Actor_Combat_Mode_On(kActorOfficerGrayford, kActorCombatStateUncover, true, kActorMcCoy, 4, kAnimationModeCombatIdle, kAnimationModeCombatWalk, kAnimationModeCombatRun, 0, 0, 100, 100, 300, true);
}

void SceneScriptHF05::talkWithDektora() {
	Actor_Face_Actor(kActorMcCoy, kActorDektora, true);
	Actor_Face_Actor(kActorDektora, kActorMcCoy, true);
	// Added in some lines for Dektora. I noticed that when she says some of her lines she is over emotional where as for other lines she is
	// totally calm and almost emotionless. Playing these lines back to back is really jarring since she switches from totally calm to downright hysterical.
	// So what I will do is for the lines where Dektora is overly emotional she is human and when she is calm she is a replicant.
	if (_vm->_cutContent) {
		if (!Game_Flag_Query(kFlagDektoraIsReplicant)) {
			Actor_Says(kActorDektora, 120, 12); //03-0120.AUD	I won’t let them shoot us down like that.
		} else {
			Actor_Says(kActorDektora, 2660, 12); //03-2660.AUD	I’ll be right back.
		}
	} else {
	Actor_Says(kActorDektora, 2660, 12);
	}
	Actor_Says(kActorMcCoy, 8990, kAnimationModeTalk);
	Actor_Says(kActorDektora, 2670, 13); //03-2670.AUD	One of Sadik’s bombs.
#if BLADERUNNER_ORIGINAL_BUGS
	Actor_Says(kActorDektora, 2680, 17);
#else
	// Dektora is interrupted here
	
	Actor_Says_With_Pause(kActorDektora, 2680, 0.0f, 17); //03-2680.AUD	I stole it. If they want a fight--
#endif // BLADERUNNER_ORIGINAL_BUGS
	Actor_Says(kActorMcCoy, 8995, 14); //00-8995.AUD	No.
	
	if (_vm->_cutContent) {
		if (!Game_Flag_Query(kFlagDektoraIsReplicant)) {
			Actor_Says(kActorDektora, 140, 12); //03-0140.AUD	I’m not afraid to use it on them, Ray.
		} else {
			Actor_Says(kActorDektora, 2690, 15); //03-2690.AUD	They’re little people with small minds.
		}
	} else {
		Actor_Says(kActorDektora, 2690, 15); //03-2690.AUD	They’re little people with small minds.
	}
	if (_vm->_cutContent) {
		if (Game_Flag_Query(kFlagDektoraIsReplicant)) {
	 		Actor_Says(kActorDektora, 1420, 15); //03-1420.AUD	This will be the first time I’ve killed a human without being ordered to do it by another human.
			Actor_Says(kActorDektora, 1430, 12); //03-1430.AUD	It’s strangely liberating.
		} 
	}	
	Actor_Says_With_Pause(kActorMcCoy, 9000, 1.0f, 16); //00-9000.AUD	No!
	if (_vm->_cutContent) {
		if (!Game_Flag_Query(kFlagDektoraIsReplicant)) {
			Actor_Says(kActorDektora, 150, 12); //03-0150.AUD	We have no other choice.
		}
	}
	Actor_Says_With_Pause(kActorMcCoy, 9005, 1.0f, 19); //00-9005.AUD	We'll find another way.
	Actor_Says(kActorMcCoy, 1765, 17); //00-1765.AUD	Wait a minute. We’re right on top of the old subway system!
	if (_vm->_cutContent) {
		if (!Game_Flag_Query(kFlagDektoraIsReplicant)) {
			Actor_Says(kActorDektora, 160, 12); //03-0160.AUD	But they’ll follow us.
			Actor_Says(kActorMcCoy, 1770, 15); //00-1770.AUD	Not if we can get a ground car down there.
		}
	} else {
		Actor_Says(kActorDektora, 160, 12); //03-0160.AUD	But they’ll follow us.
		Actor_Says(kActorMcCoy, 1770, 15); //00-1770.AUD	Not if we can get a ground car down there.		
	}
	Actor_Says(kActorMcCoy, 1775, kAnimationModeTalk); //00-1775.AUD	Hell, we can drive right through that tunnel and disappear.
	if (_vm->_cutContent) {
		if (!Game_Flag_Query(kFlagDektoraIsReplicant)) {
			Actor_Says(kActorDektora, 170, kAnimationModeTalk); //03-0170.AUD	What if it’s collapsed?
		} else {
			// If Dektora is a replicant she remains silent since she is sceptical of the plan.
			Delay (2000);
		}
	} else {
		Actor_Says(kActorDektora, 170, kAnimationModeTalk); //03-0170.AUD	What if it’s collapsed?
	}
	Actor_Says_With_Pause(kActorMcCoy, 1780, 1.0f, 18); //00-1780.AUD	It’s worth a shot.
	// Added in a line for McCoy
	if (_vm->_cutContent) {
		Actor_Says(kActorMcCoy, 1810, 15); //00-1810.AUD	Come on, they’ll be coming through the door any second!
	}
}

void SceneScriptHF05::talkWithLucy() {
	Actor_Face_Actor(kActorMcCoy, kActorLucy, true);
	Actor_Face_Actor(kActorLucy, kActorMcCoy, true);
	Actor_Says(kActorLucy, 400, 16);
	Actor_Says(kActorMcCoy, 1750, 14);
	Actor_Says(kActorLucy, 410, 12);
	Actor_Says(kActorLucy, 420, 14);
	Actor_Says(kActorMcCoy, 1755, 16);
	Actor_Says(kActorLucy, 430, 18);
	Actor_Says_With_Pause(kActorMcCoy, 1760, 1.0f, 15);
	Actor_Says(kActorMcCoy, 1765, 17);
	Actor_Says(kActorLucy, 440, kAnimationModeTalk);
	Actor_Says(kActorMcCoy, 1770, 15);
	Actor_Says(kActorMcCoy, 1775, kAnimationModeTalk);
	Actor_Says(kActorLucy, 450, 17);
	Actor_Says_With_Pause(kActorMcCoy, 1780, 1.0f, 18); //00-1780.AUD	It’s worth a shot.
	// Added in a line.
	if (_vm->_cutContent) {
		Actor_Says(kActorMcCoy, 1810, 15); //00-1810.AUD	Come on, they’ll be coming through the door any second!
	}
}

void SceneScriptHF05::talkWithCrazylegs3(int affectionTowardsActor) {
	if (affectionTowardsActor != -1
	 && Actor_Query_In_Set(kActorCrazylegs, kSetHF05)
	) {
		Async_Actor_Walk_To_Waypoint(affectionTowardsActor, 437, 36, false);
		Loop_Actor_Walk_To_Waypoint(kActorMcCoy, 437, 0, false, false);
		Actor_Face_Actor(kActorCrazylegs, kActorMcCoy, true);
		Actor_Face_Actor(kActorMcCoy, kActorCrazylegs, true);
		Actor_Face_Actor(affectionTowardsActor, kActorCrazylegs, true);
		Actor_Says(kActorCrazylegs, 0, kAnimationModeTalk);
		Actor_Says(kActorCrazylegs, 10, 12);
		Actor_Says(kActorMcCoy, 1715, 19);
		Actor_Says(kActorMcCoy, 1720, -1);
		Actor_Says(kActorCrazylegs, 20, 14);
		Actor_Says(kActorCrazylegs, 30, 15);
		Actor_Says(kActorMcCoy, 1725, kAnimationModeTalk);
		Actor_Says(kActorCrazylegs, 40, 16);
		Actor_Says(kActorCrazylegs, 50, kAnimationModeTalk);
		// CrazyLegs cuts his sentence short here. He is not interrupted.
		Actor_Says(kActorCrazylegs, 60, 12);
		Actor_Says(kActorCrazylegs, 70, 13);
		Actor_Says(kActorMcCoy, 1730, kAnimationModeTalk);
		Loop_Actor_Walk_To_Actor(kActorCrazylegs, kActorMcCoy, 28, false, false);
		Item_Pickup_Spin_Effect(kModelAnimationSpinnerKeys, 315, 327);
		Actor_Says(kActorCrazylegs, 80, 23);
		Actor_Clue_Acquire(kActorMcCoy, kClueSpinnerKeys, true, kActorCrazylegs);
		Actor_Says(kActorCrazylegs, 90, 15);
		Actor_Says(kActorMcCoy, 1735, 17);
		Actor_Says(kActorCrazylegs, 100, 16);
		Actor_Says(kActorCrazylegs, 110, kAnimationModeTalk);
		Actor_Face_Actor(affectionTowardsActor, kActorMcCoy, true);
		if (affectionTowardsActor == kActorDektora) {
			Actor_Says(kActorDektora, 90, kAnimationModeTalk);
		} else {
			Actor_Says(kActorLucy, 380, kAnimationModeTalk);
		}
		Actor_Says(kActorMcCoy, 1740, 14);    // You tell her we're headed South.
		Actor_Says(kActorCrazylegs, 120, 12); // Ten Four.
		Actor_Set_Goal_Number(kActorCrazylegs, kGoalCrazyLegsLeavesShowroom);
		if (affectionTowardsActor == kActorDektora) {
			Actor_Says(kActorDektora, 100, kAnimationModeTalk);
		} else {
			Actor_Says(kActorLucy, 390, kAnimationModeTalk);
		}
		Actor_Face_Actor(kActorMcCoy, affectionTowardsActor, true);
		Actor_Says(kActorMcCoy, 1745, kAnimationModeTalk);
		Async_Actor_Walk_To_XYZ(affectionTowardsActor, 309.0f, 40.63f, 402.0f, 0, false);
		Loop_Actor_Walk_To_XYZ(kActorMcCoy, 277.0f, 40.63f, 410.0f, 0, false, false, false);
		Game_Flag_Set(kFlagHF05toHF06);
		Set_Enter(kSetHF06, kSceneHF06);
	}
}

void SceneScriptHF05::talkWithCrazyLegs1() {
	Player_Loses_Control();
	if (Global_Variable_Query(kVariableChapter) == 3) {
		ADQ_Flush();
		ADQ_Add(kActorCrazylegs, 130, 18);
		ADQ_Add(kActorCrazylegs, 140, 18);
		// CrazyLegs cuts his sentence short here. He is not interrupted.
		ADQ_Add(kActorCrazylegs, 150, 18);
		ADQ_Add(kActorCrazylegs, 160, 17);
	}
	Loop_Actor_Walk_To_XYZ(kActorMcCoy, 307.0f, 40.63f, 184.0f, 0, false, false, false);
	Loop_Actor_Walk_To_Actor(kActorCrazylegs, kActorMcCoy, 72, false, false);
	Ambient_Sounds_Play_Sound(kSfxLABMISC4, 99, 99, 0, 0);
	Actor_Face_Actor(kActorCrazylegs, kActorMcCoy, true);
	Actor_Face_Actor(kActorMcCoy, kActorCrazylegs, true);
#if BLADERUNNER_ORIGINAL_BUGS
#else
	// There is a chance here that Crazylegs will "interrupt himself"
	// and thus sometimes skip the last sentence of the above queued dialogue in chapter 3.
	// So we explicitly wait for the queue to be emptied before proceeding to his next line
	ADQ_Wait_For_All_Queued_Dialogue();
#endif // BLADERUNNER_ORIGINAL_BUGS
	Actor_Says(kActorCrazylegs, 170, kAnimationModeTalk);
	Actor_Says(kActorCrazylegs, 180, 12);
	Actor_Says(kActorCrazylegs, 190, 14);
	Actor_Says(kActorCrazylegs, 200, 15);
	Actor_Says(kActorMcCoy, 1815, 12);
	Actor_Says(kActorCrazylegs, 210, 16);
	Actor_Says(kActorMcCoy, 1820, -1);
	Actor_Says(kActorCrazylegs, 220, kAnimationModeTalk);
	Actor_Says(kActorCrazylegs, 230, 12);
	Actor_Says(kActorCrazylegs, 240, 14);
	Actor_Says(kActorMcCoy, 1825, kAnimationModeIdle);
	Actor_Says(kActorCrazylegs, 250, 15);
	Actor_Face_Object(kActorCrazylegs, "MONTE CARLO DRY", true);
	Actor_Says(kActorCrazylegs, 260, 16);
	Actor_Face_Object(kActorMcCoy, "MONTE CARLO DRY", true);
	Actor_Says(kActorMcCoy, 1830, kAnimationModeIdle);
	Actor_Face_Actor(kActorCrazylegs, kActorMcCoy, true);
	Actor_Face_Actor(kActorMcCoy, kActorCrazylegs, true);
	Actor_Says(kActorCrazylegs, 270, kAnimationModeTalk);
	Actor_Says(kActorCrazylegs, 280, 12);
	Async_Actor_Walk_To_XYZ(kActorCrazylegs, 276.0f, 40.63f, 182.0f, 12, false);
	Loop_Actor_Walk_To_XYZ(kActorMcCoy, 335.0f, 40.63f, 131.0f, 12, false, false, false);
	Actor_Face_Object(kActorCrazylegs, "MONTE CARLO DRY", true);
	Actor_Face_Object(kActorMcCoy, "MONTE CARLO DRY", true);
	Actor_Says(kActorCrazylegs, 290, 14);
	Actor_Says(kActorCrazylegs, 300, 15);
	Actor_Says(kActorCrazylegs, 310, 16);
	Actor_Says(kActorMcCoy, 1835, 12);
	Actor_Face_Actor(kActorCrazylegs, kActorMcCoy, true);
	Actor_Says(kActorCrazylegs, 320, kAnimationModeTalk);
	Actor_Face_Actor(kActorMcCoy, kActorCrazylegs, true);
	Actor_Says(kActorCrazylegs, 330, 12);
	Actor_Says(kActorMcCoy, 1840, kAnimationModeTalk);
	Actor_Says(kActorCrazylegs, 340, 14);
	Actor_Says(kActorMcCoy, 1845, kAnimationModeTalk);
	Actor_Says(kActorCrazylegs, 350, 15);
	Actor_Says(kActorCrazylegs, 360, 16);
	Actor_Says(kActorMcCoy, 1850, kAnimationModeTalk);
	Player_Gains_Control();
}

void SceneScriptHF05::addAmbientSounds() {
	Ambient_Sounds_Add_Sound(kSfxSIREN2, 20, 80, 20, 100, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Speech_Sound(kActorOfficerLeary,    250, 5u, 70u, 7, 10, -50, 50, -101, -101, 1, 1);
	Ambient_Sounds_Add_Speech_Sound(kActorOfficerLeary,    330, 5u, 70u, 7, 10, -50, 50, -101, -101, 1, 1);
	Ambient_Sounds_Add_Speech_Sound(kActorOfficerLeary,    340, 5u, 90u, 7, 10, -50, 50, -101, -101, 1, 1);
	Ambient_Sounds_Add_Speech_Sound(kActorOfficerLeary,    360, 5u, 70u, 7, 10, -50, 50, -101, -101, 1, 1);
	Ambient_Sounds_Add_Speech_Sound(kActorOfficerGrayford, 380, 5u, 70u, 7, 10, -50, 50, -101, -101, 1, 1);
	Ambient_Sounds_Add_Speech_Sound(kActorOfficerGrayford, 510, 5u, 70u, 7, 10, -50, 50, -101, -101, 1, 1);
	Ambient_Sounds_Add_Speech_Sound(kActorDispatcher,       80, 5u, 70u, 7, 10, -50, 50, -101, -101, 1, 1);
	Ambient_Sounds_Add_Speech_Sound(kActorDispatcher,      160, 5u, 70u, 7, 10, -50, 50, -101, -101, 1, 1);
	Ambient_Sounds_Add_Speech_Sound(kActorDispatcher,      280, 5u, 70u, 7, 10, -50, 50, -101, -101, 1, 1);
}

int SceneScriptHF05::getCompanionActor() {
	if (Actor_Query_In_Set(kActorDektora, kSetHF05)
	 && Actor_Query_Goal_Number(kActorDektora) != kGoalDektoraGone
	) {
		return kActorDektora;
	}

	if (Actor_Query_In_Set(kActorLucy, kSetHF05)
	 && Actor_Query_Goal_Number(kActorLucy) != kGoalLucyGone
	) {
		return kActorLucy;
	}

	return kActorMcCoy;
}

} // End of namespace BladeRunner
