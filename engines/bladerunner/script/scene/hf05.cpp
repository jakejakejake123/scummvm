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
				if (_vm->_cutContent) {
					Actor_Change_Animation_Mode(kActorMcCoy, 23);
					Delay(800);
				}
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
			if (_vm->_cutContent) {
				if (!Game_Flag_Query(kFlagMcCoyIsInnocent)
				|| Player_Query_Agenda() == kPlayerAgendaSurly 
				|| Player_Query_Agenda() == kPlayerAgendaErratic) {
					Actor_Set_Goal_Number(kActorOfficerLeary, kGoalOfficerLearyPoliceWait60SecondsToAttackHF05);
				}
			} else {
				Actor_Set_Goal_Number(kActorOfficerLeary, kGoalOfficerLearyPoliceWait60SecondsToAttackHF05);
			}
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
					Delay (6000);
					if (getCompanionActor() == kActorDektora) {
						if (!Game_Flag_Query(kFlagDektoraIsReplicant)) {
							if (!Game_Flag_Query(kFlagMcCoyIsInnocent)
							|| Player_Query_Agenda() == kPlayerAgendaSurly 
							|| Player_Query_Agenda() == kPlayerAgendaErratic) {
								Actor_Face_Actor(kActorMcCoy, getCompanionActor(), true);
								Actor_Face_Actor(getCompanionActor(), kActorMcCoy, true);
								Actor_Says(kActorDektora, 180, kAnimationModeTalk); //03-0180.AUD	What are you waiting for?
								Actor_Says(kActorDektora, 190, kAnimationModeTalk); //03-0190.AUD	They’ll be coming in any second!
							}
						}
					} else if (getCompanionActor() == kActorLucy) {
						if (!Game_Flag_Query(kFlagMcCoyIsInnocent)
						|| Player_Query_Agenda() == kPlayerAgendaSurly 
						|| Player_Query_Agenda() == kPlayerAgendaErratic) {
							Actor_Face_Actor(kActorMcCoy, getCompanionActor(), true);
							Actor_Face_Actor(getCompanionActor(), kActorMcCoy, true);
							Actor_Says(kActorLucy, 460, kAnimationModeTalk); //06-0460.AUD	What are you waiting for?
							Actor_Says(kActorLucy, 470, kAnimationModeTalk); //06-0470.AUD	They’ll be coming any second!
						}
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
					if (_vm->_cutContent) {
						if (Actor_Query_Is_In_Current_Set(kActorDektora)) {
							if (!Game_Flag_Query(kFlagMcCoyIsInnocent)
							|| Player_Query_Agenda() == kPlayerAgendaSurly 
							|| Player_Query_Agenda() == kPlayerAgendaErratic) {
								Actor_Face_Actor(kActorMcCoy, kActorDektora, true);
								Actor_Says(kActorMcCoy, 1810, 16); //00-1810.AUD	Come on, they’ll be coming through the door any second!
							}
						} else if (Actor_Query_Is_In_Current_Set(kActorLucy)) {
							if (!Game_Flag_Query(kFlagMcCoyIsInnocent)
							|| Player_Query_Agenda() == kPlayerAgendaSurly 
							|| Player_Query_Agenda() == kPlayerAgendaErratic) {
								Actor_Face_Actor(kActorMcCoy, kActorLucy, true);
								Actor_Says(kActorMcCoy, 1810, 16); //00-1810.AUD	Come on, they’ll be coming through the door any second!
							}	
						}
					} else {
						Actor_Face_Actor(kActorMcCoy, affectionTowardsActor, true);
						Actor_Says(kActorMcCoy, 1810, 16); //00-1810.AUD	Come on, they’ll be coming through the door any second!
					}
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
		if (_vm->_cutContent) {
			if (Actor_Query_Is_In_Current_Set(kActorDektora)) {
				if (Game_Flag_Query(kFlagDektoraIsReplicant)
				|| !Game_Flag_Query(kFlagMcCoyIsInnocent)
				|| Game_Flag_Query(kFlagMcCoyRetiredHuman)
				|| Actor_Query_Friendliness_To_Other(kActorCrazylegs, kActorMcCoy) < 50) {
					Music_Play(kMusicBatl226M, 50, 0, 2, -1, kMusicLoopPlayOnce, 0);
				}
			} else if (Actor_Query_Is_In_Current_Set(kActorLucy)) {
				if (Game_Flag_Query(kFlagLucyIsReplicant)
				|| !Game_Flag_Query(kFlagMcCoyIsInnocent)
				|| Game_Flag_Query(kFlagMcCoyRetiredHuman)
				|| Actor_Query_Friendliness_To_Other(kActorCrazylegs, kActorMcCoy) < 50) {
					Music_Play(kMusicBatl226M, 50, 0, 2, -1, kMusicLoopPlayOnce, 0);
				}	
			} else {
				if (Game_Flag_Query(kFlagDektoraIsReplicant)
				|| !Game_Flag_Query(kFlagMcCoyIsInnocent)
				|| Game_Flag_Query(kFlagMcCoyRetiredHuman)
				|| Actor_Query_Friendliness_To_Other(kActorCrazylegs, kActorMcCoy) < 50) {
					Music_Play(kMusicBatl226M, 50, 0, 2, -1, kMusicLoopPlayOnce, 0);
				} else if (Game_Flag_Query(kFlagLucyIsReplicant)
				|| !Game_Flag_Query(kFlagMcCoyIsInnocent)
				|| Game_Flag_Query(kFlagMcCoyRetiredHuman)
				|| Actor_Query_Friendliness_To_Other(kActorCrazylegs, kActorMcCoy) < 50) {
					Music_Play(kMusicBatl226M, 50, 0, 2, -1, kMusicLoopPlayOnce, 0);
				}
			}
		} else {
			Music_Play(kMusicBatl226M, 50, 0, 2, -1, kMusicLoopPlayOnce, 0);
		}
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
				if (_vm->_cutContent) {
					if (Actor_Query_Is_In_Current_Set(kActorDektora) 
					&& !Game_Flag_Query(kFlagDektoraIsReplicant)
					&& Game_Flag_Query(kFlagMcCoyIsInnocent)
					&& !Game_Flag_Query(kFlagMcCoyRetiredHuman)
					&& Actor_Query_Friendliness_To_Other(kActorCrazylegs, kActorMcCoy) > 49) {
						Game_Flag_Set(kFlagHF05PoliceArrived);
						Game_Flag_Set(kFlagParkedSpinner);
						Delay(1000);
						Actor_Face_Heading(kActorMcCoy, 100, true);
						Delay(1000);
						Actor_Says(kActorMcCoy, 2005, kAnimationModeIdle); //00-2005.AUD	A Spinner?
						Delay(2000);
						Actor_Says(kActorMcCoy, 8525, 13); // 00-8525.AUD	Hmph.
						Async_Actor_Walk_To_XYZ(kActorMcCoy, 483.0f, 40.63f, -189.0f, 0, true);
						Actor_Says(kActorDektora, 90, -1); //03-0090.AUD	Ray!?
						Delay(2000);
						Async_Actor_Walk_To_XYZ(kActorDektora, 483.0f, 40.63f, -189.0f, 0, true);
						Game_Flag_Reset(kFlagHF05toHF01);
						Game_Flag_Set(kFlagHF01toHF05);
						Set_Enter(kSetHF01, kSceneHF01);
					} else if (Actor_Query_Is_In_Current_Set(kActorLucy) 
					&& !Game_Flag_Query(kFlagLucyIsReplicant)
					&& Game_Flag_Query(kFlagMcCoyIsInnocent)
					&& !Game_Flag_Query(kFlagMcCoyRetiredHuman)
					&& Actor_Query_Friendliness_To_Other(kActorCrazylegs, kActorMcCoy) > 49) {
						Game_Flag_Set(kFlagHF05PoliceArrived);
						Game_Flag_Set(kFlagParkedSpinner);
						Delay(1000);
						Actor_Face_Heading(kActorMcCoy, 100, true);
						Delay(1000);
						Actor_Says(kActorMcCoy, 2005, kAnimationModeIdle); //00-2005.AUD	A Spinner?
						Delay(2000);
						Actor_Says(kActorMcCoy, 8525, 13); // 00-8525.AUD	Hmph.
						Async_Actor_Walk_To_XYZ(kActorMcCoy, 483.0f, 40.63f, -189.0f, 0, true);
						Actor_Says(kActorLucy, 380, -1); //06-0380.AUD	Ray.
						Delay(1000);
						Async_Actor_Walk_To_XYZ(kActorDektora, 483.0f, 40.63f, -189.0f, 0, true);
						Game_Flag_Reset(kFlagHF05toHF01);
						Game_Flag_Set(kFlagHF01toHF05);
						Set_Enter(kSetHF01, kSceneHF01);
					} else {
						Game_Flag_Set(kFlagHF05PoliceArrived);
						Music_Play(kMusicBatl226M, 40, 0, 2, -1, kMusicLoopPlayOnce, 0);
						Actor_Says(kActorOfficerGrayford, 200, kAnimationModeTalk);
						if (Player_Query_Agenda() == kPlayerAgendaSurly 
						|| Player_Query_Agenda() == kPlayerAgendaErratic) {
							Actor_Face_Heading(kActorMcCoy, 100, true);
							Actor_Says(kActorMcCoy, 2250, 14); //00-2250.AUD	Come out and show yourself, you coward!
							if (!Game_Flag_Query(kFlagMcCoyIsInnocent)) {
								if (Random_Query(1, 2) == 1) {
									Actor_Says(kActorOfficerGrayford, 290, kAnimationModeTalk); //24-0290.AUD	There’s the son of a bitch! Kill it!
								} else {
									Actor_Says(kActorOfficerGrayford, 270, kAnimationModeTalk); //24-0270.AUD	There it is! Take it out!
								}
							}
							Player_Set_Combat_Mode(true);
							Delay(1000);
							Sound_Play(kSfxGUNH1A, 100, 0, 0, 50);
							Actor_Change_Animation_Mode(kActorMcCoy, 6);
							Delay(1000);
							Sound_Play(kSfxGUNH1A, 100, 0, 0, 50);
							Actor_Change_Animation_Mode(kActorMcCoy, 6);
							Delay(1000);
							Sound_Play(kSfxSMCAL3, 100, 0, 0, 50);
							Actor_Change_Animation_Mode(kActorMcCoy, 22);
							Delay(1000);
							Sound_Play(kSfxGUNH1A, 100, 0, 0, 50);
							Actor_Change_Animation_Mode(kActorMcCoy, 6);
							Delay(1000);
							Actor_Says(kActorOfficerGrayford, 250, kAnimationModeTalk); //24-0250.AUD	Ah, I’m hit!
							Player_Set_Combat_Mode(false);
							Delay(2000);
						}
						if (!Game_Flag_Query(kFlagMcCoyIsInnocent) 
						|| Player_Query_Agenda() == kPlayerAgendaSurly 
						|| Player_Query_Agenda() == kPlayerAgendaErratic) {
							Actor_Says(kActorOfficerGrayford, 210, kAnimationModeTalk);
							Delay(1000);
						}
						if (getCompanionActor() ==  kActorDektora) {
							talkWithDektora();
						} else if (getCompanionActor() == kActorLucy) {
							talkWithLucy();
						}
					}
				} else {
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

	if (_vm->_cutContent) {
		if (Game_Flag_Query(kFlagParkedSpinnerChecked)) {
			Actor_Set_At_XYZ(kActorMcCoy, 399.0f, 40.63f, -85.0f, 603);
			Loop_Actor_Walk_To_XYZ(kActorMcCoy, 302.89f, 40.92f, 273.85f, 0, false, true, false);
			if (Actor_Query_Is_In_Current_Set(kActorDektora)) {
				Loop_Actor_Walk_To_XYZ(kActorDektora, 278.18f, 40.94f, 250.58f, 0, false, true, false);
			} else if (Actor_Query_Is_In_Current_Set(kActorLucy)) {
				Loop_Actor_Walk_To_XYZ(kActorLucy, 278.18f, 40.94f, 250.58f, 0, false, true, false);
			}
			Game_Flag_Reset(kFlagHF02toHF01);
			Game_Flag_Set(kFlagHF01toHF05);
			Actor_Face_Object(kActorMcCoy, "MONTE CARLO DRY", true);
			if (Actor_Query_Is_In_Current_Set(kActorDektora)) {
				Actor_Face_Actor(kActorDektora, kActorMcCoy, true);
			} else if (Actor_Query_Is_In_Current_Set(kActorLucy)) {
				Actor_Face_Actor(kActorLucy, kActorMcCoy, true);
			}
			Delay(2000);
			Actor_Says(kActorMcCoy, 8525, 13); // 00-8525.AUD	Hmph.
			Delay(1000);
			Actor_Says(kActorMcCoy, 8495, 15); //00-8495.AUD	This might work.
			Delay(1000);
			Player_Gains_Control();
			Game_Flag_Reset(kFlagParkedSpinnerChecked);
			if (getCompanionActor() ==  kActorDektora) {
				Actor_Face_Actor(kActorMcCoy, kActorDektora, true);
				Actor_Face_Actor(kActorDektora, kActorMcCoy, true);
				Actor_Says(kActorDektora, 90, 13); //03-0090.AUD	Ray!?
				talkWithDektora();
			} else if (getCompanionActor() == kActorLucy) {
				Actor_Face_Actor(kActorMcCoy, kActorLucy, true);
				Actor_Face_Actor(kActorLucy, kActorMcCoy, true);
				Actor_Says(kActorLucy, 380, 13); //06-0380.AUD	Ray.
				talkWithLucy();
			}
		}
	}
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
	// Made it so when you enter Crazys store a second time if McCoy is surly or erratic he is mean towards Crazylegs. This annoys Crazylegs and he leaves the room.
	if (_vm->_cutContent) {
		if (Actor_Query_Friendliness_To_Other(kActorCrazylegs, kActorMcCoy) > 49
		&& !Game_Flag_Query(kFlagCrazylegsIsReplicant)) {
			Actor_Says(kActorCrazylegs, 370, kAnimationModeTalk); //09-0370.AUD	Hey, Ray, how you’re doing?
			if (Player_Query_Agenda() != kPlayerAgendaSurly
			&& (Player_Query_Agenda() != kPlayerAgendaErratic)) {	
				Actor_Says(kActorMcCoy, 1855, kAnimationModeTalk); //00-1855.AUD	Just fine, Crazy.
			} else {
				Delay(2000);
			}
			Actor_Says(kActorCrazylegs, 380, 12); //09-0380.AUD	You’ve been thinking about the Caddy, haven’t you?
			Actor_Says(kActorCrazylegs, 390, 14);
			Actor_Says(kActorCrazylegs, 400, 15);
			Actor_Says(kActorCrazylegs, 410, 16); //09-0410.AUD	Which is definitely what’s in the cards for a stud of your caliber.
			if (Player_Query_Agenda() != kPlayerAgendaSurly
			&& (Player_Query_Agenda() != kPlayerAgendaErratic)) {	
				Actor_Says(kActorMcCoy, 1860, kAnimationModeTalk); //00-1860.AUD	Throw in a babe and maybe you’ve got a deal.
				Actor_Says(kActorCrazylegs, 420, kAnimationModeTalk);
				Actor_Says(kActorMcCoy, 1865, kAnimationModeTalk); //00-1865.AUD	Nah, just kidding.
			} else {
				Actor_Says(kActorMcCoy, 4320, 14); //00-4320.AUD	Save the pitch for someone who gives a shit.
				Actor_Modify_Friendliness_To_Other(kActorCrazylegs, kActorMcCoy, -2);
				Delay(2000);
				Actor_Says(kActorCrazylegs, 870, 15); // 09-0870.AUD	Look, Ray. It ain’t a crime for me to make a living.
			}
		} else {
			Actor_Says(kActorCrazylegs, 380, 14); //09-0380.AUD	You’ve been thinking about the Caddy, haven’t you?
			if (Player_Query_Agenda() != kPlayerAgendaPolite) {
				Actor_Says(kActorMcCoy, 7815, kAnimationModeTalk); //00-7815.AUD	No.
			} else {
				Actor_Says(kActorMcCoy, 7980, 19); //00-7980.AUD	Yeah. Maybe.
			}
			Actor_Says(kActorCrazylegs, 980, 14); //09-0980.AUD	You want the Caddy or not?
			Actor_Says(kActorCrazylegs, 990, 16); //09-0990.AUD	I’m looking to make deals, you know?
			if (Player_Query_Agenda() == kPlayerAgendaSurly
			|| (Player_Query_Agenda() == kPlayerAgendaErratic)) {
				Actor_Says(kActorMcCoy, 4320, 14); //00-4320.AUD	Save the pitch for someone who gives a shit.
				Delay(2000);
				Actor_Says(kActorCrazylegs, 970, 16); //09-0970.AUD	Hey, I’d never turn away a customer but… you’re getting to be a pain in the ass.
				Actor_Says(kActorMcCoy, 8420, 18); //00-8420.AUD	Must be rough.
				Delay(1000);
				Actor_Says(kActorCrazylegs, 1000, 16); //09-1000.AUD	I got customers on the line, so I ain’t got time to chit chat.
				Actor_Modify_Friendliness_To_Other(kActorCrazylegs, kActorMcCoy, -2);
				Actor_Set_Goal_Number(kActorCrazylegs, kGoalCrazyLegsLeavesShowroom);
			} else {
				Actor_Says(kActorMcCoy, 1860, kAnimationModeTalk);
				Actor_Says(kActorCrazylegs, 420, kAnimationModeTalk);
				Actor_Says(kActorMcCoy, 1865, kAnimationModeTalk);
			}
		}
	} else {
		Actor_Says(kActorCrazylegs, 370, kAnimationModeTalk);
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
	&& !Actor_Clue_Query(kActorMcCoy, kClueCrazylegsInterview2)
	 && Global_Variable_Query(kVariableChapter) == 3
	) {
		// This dialogue point does not talk about Grigorian's Note
		// but rather a Note that CrazyLegs wrote on one of his flyers
		// kClueCrazysInvolvement is only acquired in _cutContent (Restored Content) mode
		// so no need to add that extra check in the if clause.
		DM_Add_To_List_Never_Repeat_Once_Selected(1180, 3, 2, 1); // ADVERTISEMENT
	}
#endif // BLADERUNNER_ORIGINAL_BUGS
	// Added in flag so this topic will activate after you talk to Crazy about the car registration. The reason for this is because I made the Crazylegs interview 1 
	// clue feature the dialogue of this topic since it not only includes that facts mentioned in car registration but also some extra facts that are also relevant such as mentioning 
	// Gordo being with Dektora and saying that they were after a police spinner.
	// Made it so McCoy can only ask about clues in regards to the car in act 3 since in act 4 he is too busy getting to the bottom of the conspiracy to have time to be investigating
	// the animal murder case.
	if (_vm->_cutContent) {
		if (Actor_Clue_Query(kActorMcCoy, kClueDektoraConfession)) {
			if (Global_Variable_Query(kVariableChapter) == 3) {
				DM_Add_To_List_Never_Repeat_Once_Selected(1190, 5, 7, 6); // WOMAN
			}
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
			if (Global_Variable_Query(kVariableChapter) == 3) {
				if (Actor_Clue_Query(kActorMcCoy, kClueChinaBar)
				|| Actor_Clue_Query(kActorMcCoy, kClueWomanInAnimoidRow)
				|| Actor_Clue_Query(kActorMcCoy, kClueOuterDressingRoom)
				|| Actor_Clue_Query(kActorMcCoy, kClueDektorasDressingRoom)) {	
					DM_Add_To_List_Never_Repeat_Once_Selected(1200, 5, 5, 6); // WOMAN'S PHOTO
				}
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
	if (_vm->_cutContent) {
		if (Actor_Clue_Query(kActorMcCoy, kClueLucy)
		|| Actor_Clue_Query(kActorMcCoy, kClueLucyWithDektora)) {
			if (Actor_Clue_Query(kActorMcCoy, kClueHysteriaToken)) {
				if (Actor_Query_Goal_Number(kActorLucy) != kGoalLucyGone
				&& Global_Variable_Query(kVariableChapter) == 3 
				&& Global_Variable_Query(kVariableAffectionTowards) != kAffectionTowardsLucy) {
					DM_Add_To_List_Never_Repeat_Once_Selected(1210, 4, 3, 5); // LUCY'S PHOTO
				}
			}
		}
	} else if (Actor_Clue_Query(kActorMcCoy, kClueLucy)
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
	// Made it so so the Grigorian option is only available if you have both the Grigorians resources and the Grigorians note clue.
	// Considering during this option McCoy mentions Grigorian having friends with resources and McCoy mentions the note referring to Crazylegs
	// in his conversation with Grigorian it makes sense for McCoy to have both clues for this option to be available.
	if (Global_Variable_Query(kVariableChapter) == 3 
	&& Actor_Clue_Query(kActorMcCoy, kClueGrigoriansNote)
	&& Actor_Clue_Query(kActorMcCoy, kClueGrigoriansResources) // Restored feature - Original: it is impossible to obtain this clue either
	&& !Actor_Clue_Query(kActorMcCoy, kClueCrazylegsInterview2)) {	
		if (Actor_Clue_Query(kActorMcCoy, kClueCarRegistration1) 
		|| Actor_Clue_Query(kActorMcCoy, kClueCarRegistration3)) {
			// The chapter check is done for both cases:
			//      either McCoy has kClueGrigoriansResources or kClueGrigoriansNote
			DM_Add_To_List_Never_Repeat_Once_Selected(1220, 1, 2, 3); // GRIGORIAN
		}
	}
#endif
	if (_vm->_cutContent) {
		if (Global_Variable_Query(kVariableChapter) == 3) {
			if (Actor_Clue_Query(kActorMcCoy, kClueCarRegistration1)
			|| Actor_Clue_Query(kActorMcCoy, kClueCarRegistration3)) {
				// Dektora bought the car or Blake Williams (which is an alias, that Clovis used)
				// Gordo is with Dektora when making the car purchase (as revealed by CrazyLegs in the "WOMAN" question).
				DM_Add_To_List_Never_Repeat_Once_Selected(1230, 6, 7, 8); // CAR REGISTRATION
			}
		}
	} else if (Actor_Clue_Query(kActorMcCoy, kClueCarRegistration1)
	 || Actor_Clue_Query(kActorMcCoy, kClueCarRegistration3)
	) {
		// Dektora bought the car or Blake Williams (which is an alias, that Clovis used)
		// Gordo is with Dektora when making the car purchase (as revealed by CrazyLegs in the "WOMAN" question).
		DM_Add_To_List_Never_Repeat_Once_Selected(1230, 4, 7, -1); // CAR REGISTRATION
	}

	if (!Dialogue_Menu_Query_List_Size()) {
		if (_vm->_cutContent) {
			if (Player_Query_Agenda() == kPlayerAgendaPolite) {
				Actor_Says(kActorMcCoy, 1730, kAnimationModeTalk); //00-1730.AUD	You’re a stand up guy, Crazy.
				Actor_Says(kActorCrazylegs, 80, 23); //09-0080.AUD	That I am.
			} else {
				Actor_Says(kActorMcCoy, 1880, 15);
				Actor_Says(kActorCrazylegs, 490, kAnimationModeTalk);
				Actor_Says(kActorMcCoy, 1885, kAnimationModeTalk);
				Actor_Says(kActorCrazylegs, 500, 16); //09-0500.AUD	You can take it anyway you want. Just don’t take it for a test-drive in the Fourth Sector.
			}
		} else {
			Actor_Says(kActorMcCoy, 1880, 15);
			Actor_Says(kActorCrazylegs, 490, kAnimationModeTalk);
			Actor_Says(kActorMcCoy, 1885, kAnimationModeTalk);
			Actor_Says(kActorCrazylegs, 500, 16); //09-0500.AUD	You can take it anyway you want. Just don’t take it for a test-drive in the Fourth Sector.
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
		Actor_Says(kActorCrazylegs, 510, kAnimationModeTalk);
		if (_vm->_cutContent) {
			Actor_Says(kActorCrazylegs, 520, kAnimationModeTalk);
		}
		Actor_Says(kActorMcCoy, 1920, 23);
		Actor_Says(kActorMcCoy, 1925, kAnimationModeTalk); //00-1925.AUD	This your handwriting, Crazy?
		Actor_Says(kActorCrazylegs, 530, 12);
		Actor_Says(kActorMcCoy, 1930, 18); //00-1930.AUD	I found this in the possession of a Replicant.
		Actor_Says(kActorCrazylegs, 540, 14);
		Actor_Says(kActorMcCoy, 1935, 14); //00-1935.AUD	A Replicant.
		Actor_Says(kActorCrazylegs, 550, 16);
		if (_vm->_cutContent) {
			if (!Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
				Actor_Says(kActorMcCoy, 1940, 15); //00-1940.AUD	You know it’s illegal to sell anything to a Replicant.
				Actor_Says(kActorMcCoy, 1945, 16); //00-1945.AUD	Or to help a Replicant in any way.
				// Made it so Crazylegs doesn't try to throw Dektora and Gordo under the bus if he is a replicant. When Crazylegs is a rep
				// he is even more protective of the replicants and would never sell them out by blaming them for the transaction. In this scenario
				// Crazylegs just stays silent when McCoy says it is illegal to do business with reps. 
				if (!Game_Flag_Query(kFlagCrazylegsIsReplicant)) {
					// CrazyLegs cuts his sentence short here. He is not interrupted.
					Actor_Says(kActorCrazylegs, 560, 15); //09-0560.AUD	I didn’t know! I mean it. I was just trying to make a sale--
					Actor_Says(kActorCrazylegs, 570, 16); //09-0570.AUD	Hey, they came to me first. I didn’t go to them.
					if (Player_Query_Agenda() == kPlayerAgendaSurly 
					|| Player_Query_Agenda() == kPlayerAgendaErratic) {
						Actor_Says(kActorMcCoy, 1950, 17); //00-1950.AUD	Unscrupulous businessman, eh?
						Actor_Modify_Friendliness_To_Other(kActorCrazylegs, kActorMcCoy, -2);
					}
				} else {
					Delay (2000);
					Actor_Says(kActorMcCoy, 1885, 18); //00-1885.AUD	I’ll take that as a yes.
				}
			} else {
				Actor_Says(kActorMcCoy, 4880, 13); //00-4880.AUD	Is that right?
			}
		} else {
			Actor_Says(kActorMcCoy, 1940, 15); //00-1940.AUD	You know it’s illegal to sell anything to a Replicant.
			Actor_Says(kActorMcCoy, 1945, 16); //00-1945.AUD	Or to help a Replicant in any way.
			Actor_Says(kActorCrazylegs, 560, 15); //09-0560.AUD	I didn’t know! I mean it. I was just trying to make a sale--
			Actor_Says(kActorCrazylegs, 570, 16); //09-0570.AUD	Hey, they came to me first. I didn’t go to them.
			Actor_Says(kActorMcCoy, 1950, 17); //00-1950.AUD	Unscrupulous businessman, eh?
		}
		if (_vm->_cutContent) {
			Actor_Clue_Acquire(kActorMcCoy, kClueCrazylegsInterview2, true, kActorCrazylegs);
		}
		dialogueWithCrazylegs2();
		break;

	case 1190: // WOMAN
		Actor_Says(kActorMcCoy, 1895, kAnimationModeIdle); //00-1895.AUD	I gotta know more about the woman, Crazy.
		// Made it so if Crazylegs is a replicant he will not tell you any further information about Dektora.
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagCrazylegsIsReplicant)
			|| Actor_Query_Friendliness_To_Other(kActorCrazylegs, kActorMcCoy) < 50) {
				Actor_Says(kActorCrazylegs, 1150, 14); //09-1150.AUD	Only thing I know is that the best deals you can make are right in this showroom.
				if (Player_Query_Agenda() == kPlayerAgendaSurly 
				|| Player_Query_Agenda() == kPlayerAgendaErratic) {
					Actor_Says(kActorMcCoy, 8519, 14);//00-8519.AUD	What do you say we dish each other the straight goods.
					if (Game_Flag_Query(kFlagCrazylegsIsReplicant)) {
						Actor_Says(kActorCrazylegs, 1160, 16); //09-1160.AUD	Take a ride, McCoy. I already told you everything.
						Actor_Says(kActorMcCoy, 5075, 18); //00-5075.AUD	Hey, pal.
						Actor_Modify_Friendliness_To_Other(kActorCrazylegs, kActorMcCoy, -2);
					} else {
						Delay(2000);
						Actor_Says(kActorCrazylegs, 620, kAnimationModeTalk); //09-0620.AUD	Like I said, she was tall and blonde. Real woo bait.
						Actor_Says(kActorCrazylegs, 630, 12); //09-0630.AUD	She was tooling around with a short guy in a bow tie.
						Actor_Says(kActorMcCoy, 2000, 13); //00-2000.AUD	And she wanted a car.
						Actor_Says(kActorCrazylegs, 640, 14); //09-0640.AUD	At first, she was looking for a very hard to find item.
						Actor_Says(kActorCrazylegs, 650, 15); //09-0650.AUD	Something that doesn’t show up on the lot too often.
						Actor_Says(kActorCrazylegs, 660, 16); //09-0660.AUD	A… police-issue vehicle.
						Actor_Says(kActorMcCoy, 2005, kAnimationModeIdle); //00-2005.AUD	A Spinner?
						Actor_Says(kActorMcCoy, 2010, kAnimationModeTalk); //00-2010.AUD	But you didn’t have one.
						Actor_Says(kActorCrazylegs, 670, kAnimationModeTalk); //09-0670.AUD	Well, not one that would actually fly.
						Actor_Says(kActorCrazylegs, 680, 12); //09-0680.AUD	I told them to check back in a couple of days.
						Actor_Says(kActorCrazylegs, 690, 14); //09-0690.AUD	So, then they got looking at that Sedan.
						if (Player_Query_Agenda() != kPlayerAgendaPolite) {
							Actor_Says(kActorMcCoy, 2015, 14); //00-2015.AUD	You know how many years mandatory you’d get for selling a police Spinner?
							Actor_Says(kActorCrazylegs, 700, 15); //09-0700.AUD	I was gonna report them, if they showed up again.
							if (Player_Query_Agenda() != kPlayerAgendaSurly 
							|| Player_Query_Agenda() == kPlayerAgendaErratic) {
								Actor_Says(kActorMcCoy, 2020, 18); //00-2020.AUD	Sure you were.
								Actor_Modify_Friendliness_To_Other(kActorCrazylegs, kActorMcCoy, -2);
							}
						} else {
							Actor_Says(kActorMcCoy, 5065, 18); //00-5065.AUD	Is that right?
							Actor_Says(kActorCrazylegs, 720, 15); //09-0720.AUD	Uh-huh.
						}
						// Made it so the crazylegs interview 1 clue is for this dialogue instead. The reason is it contains a lot more information than the car registration topic.
						// I mean not only does Crazy describe Dektora in this topic, but he also mentions Gordo and how they asked for a police spinner. Pretty relevant information.
						Actor_Clue_Acquire(kActorMcCoy, kClueCrazylegsInterview1, true, kActorCrazylegs);
						// Inserted a flag to make the womans photo option available.
						Game_Flag_Set(kFlagCrazylegsTalkWoman);
					} 
				}
			} else {
				Actor_Says(kActorCrazylegs, 620, kAnimationModeTalk); //09-0620.AUD	Like I said, she was tall and blonde. Real woo bait.
				Actor_Says(kActorCrazylegs, 630, 12); //09-0630.AUD	She was tooling around with a short guy in a bow tie.
				Actor_Says(kActorMcCoy, 2000, 13); //00-2000.AUD	And she wanted a car.
				Actor_Says(kActorCrazylegs, 640, 14); //09-0640.AUD	At first, she was looking for a very hard to find item.
				Actor_Says(kActorCrazylegs, 650, 15); //09-0650.AUD	Something that doesn’t show up on the lot too often.
				Actor_Says(kActorCrazylegs, 660, 16); //09-0660.AUD	A… police-issue vehicle.
				Actor_Says(kActorMcCoy, 2005, kAnimationModeIdle); //00-2005.AUD	A Spinner?
				Actor_Says(kActorMcCoy, 2010, kAnimationModeTalk); //00-2010.AUD	But you didn’t have one.
				Actor_Says(kActorCrazylegs, 670, kAnimationModeTalk); //09-0670.AUD	Well, not one that would actually fly.
				Actor_Says(kActorCrazylegs, 680, 12); //09-0680.AUD	I told them to check back in a couple of days.
				Actor_Says(kActorCrazylegs, 690, 14); //09-0690.AUD	So, then they got looking at that Sedan.
				if (Player_Query_Agenda() != kPlayerAgendaPolite) {
					Actor_Says(kActorMcCoy, 2015, 14); //00-2015.AUD	You know how many years mandatory you’d get for selling a police Spinner?
					Actor_Says(kActorCrazylegs, 700, 15); //09-0700.AUD	I was gonna report them, if they showed up again.
					if (Player_Query_Agenda() != kPlayerAgendaSurly 
					|| Player_Query_Agenda() == kPlayerAgendaErratic) {
						Actor_Says(kActorMcCoy, 2020, 18); //00-2020.AUD	Sure you were.
						Actor_Modify_Friendliness_To_Other(kActorCrazylegs, kActorMcCoy, -2);
					}
				} else {
					Actor_Says(kActorMcCoy, 5065, 18); //00-5065.AUD	Is that right?
					Actor_Says(kActorCrazylegs, 720, 15); //09-0720.AUD	Uh-huh.
				}
				// Made it so the crazylegs interview 1 clue is for this dialogue instead. The reason is it contains a lot more information than the car registration topic.
				// I mean not only does Crazy describe Dektora in this topic, but he also mentions Gordo and how they asked for a police spinner. Pretty relevant information.
				Actor_Clue_Acquire(kActorMcCoy, kClueCrazylegsInterview1, true, kActorCrazylegs);
				// Inserted a flag to make the womans photo option available.
				Game_Flag_Set(kFlagCrazylegsTalkWoman);
			} 
		} else {
			Actor_Says(kActorCrazylegs, 620, kAnimationModeTalk); //09-0620.AUD	Like I said, she was tall and blonde. Real woo bait.
			Actor_Says(kActorCrazylegs, 630, 12); //09-0630.AUD	She was tooling around with a short guy in a bow tie.
			Actor_Says(kActorMcCoy, 2000, 13); //00-2000.AUD	And she wanted a car.
			Actor_Says(kActorCrazylegs, 640, 14);
			Actor_Says(kActorCrazylegs, 650, 15);
			Actor_Says(kActorCrazylegs, 660, 16);
			Actor_Says(kActorMcCoy, 2005, kAnimationModeIdle);
			Actor_Says(kActorMcCoy, 2010, kAnimationModeTalk);
			Actor_Says(kActorCrazylegs, 670, kAnimationModeTalk);
			Actor_Says(kActorCrazylegs, 680, 12);
			Actor_Says(kActorCrazylegs, 690, 14); //09-0690.AUD	So, then they got looking at that Sedan.
			Actor_Says(kActorMcCoy, 2015, 14); //00-2015.AUD	You know how many years mandatory you’d get for selling a police Spinner?
			Actor_Says(kActorCrazylegs, 700, 15); //09-0700.AUD	I was gonna report them, if they showed up again.
			Actor_Says(kActorMcCoy, 2020, 18); //00-2020.AUD	Sure you were.
		}
		break;

	case 1200: // WOMAN'S PHOTO
		Actor_Says(kActorMcCoy, 1900, 23);
		Actor_Says(kActorCrazylegs, 710, 16);
		Actor_Says(kActorMcCoy, 2025, kAnimationModeIdle);
		Actor_Says(kActorCrazylegs, 720, kAnimationModeTalk);
		Actor_Says(kActorCrazylegs, 730, 12);
		Game_Flag_Set(kFlagDektoraIdentified);
		break;

	case 1210: // LUCY'S PHOTO
		// Added in some dialogue.
		if (_vm->_cutContent) {
			Actor_Says(kActorMcCoy, 5600, 13); //00-5600.AUD	Let me ask you something.
			Actor_Says(kActorCrazylegs, 1140, 14); //09-1140.AUD	You can bet I’ve heard something you might be interested in.
		}
		Actor_Says(kActorMcCoy, 1905, 23); //00-1905.AUD	How about this girl. She look familiar?
		Actor_Says(kActorCrazylegs, 740, 14); //09-0740.AUD	You kidding? She ain’t old enough to drive.
		Actor_Says(kActorMcCoy, 2030, 13); //00-2030.AUD	You’ve never seen her?
		// Made it so Crazylegs doesn't tell McCoy where to find Lucy if he is a replicant.
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagCrazylegsIsReplicant)
			|| Actor_Query_Friendliness_To_Other(kActorCrazylegs, kActorMcCoy) < 50) {
				Actor_Says(kActorCrazylegs, 1150, 14); //09-1150.AUD	Only thing I know is that the best deals you can make are right in this showroom.
				Actor_Says(kActorMcCoy, 8565, 13); //00-8565.AUD	Really?
				Actor_Says(kActorCrazylegs, 1180, 15); //09-1180.AUD	What do you expect? I sell cars for a living.
			} else {	
				Actor_Says(kActorCrazylegs, 750, 15); //09-0750.AUD	She looks kinda familiar.
				if (Player_Query_Agenda() == kPlayerAgendaSurly 
				|| Player_Query_Agenda() == kPlayerAgendaErratic) {
					Actor_Says(kActorMcCoy, 2035, 18);
				} else {
					Delay(1000);
				}
				Actor_Says(kActorCrazylegs, 760, 16); //09-0760.AUD	Maybe you should try that arcade next door. 
				Actor_Says(kActorCrazylegs, 770, kAnimationModeTalk); //09-0770.AUD	She looks like the kind of girl you see there all the time.		
				Actor_Says(kActorMcCoy, 2040, kAnimationModeIdle); //00-2040.AUD	I’ll do that.
			}
		} else {
			Actor_Says(kActorCrazylegs, 750, 15); //09-0750.AUD	She looks kinda familiar.
			Actor_Says(kActorMcCoy, 2035, 18); //00-2035.AUD	Think real hard.
			Actor_Says(kActorCrazylegs, 760, 16); //09-0760.AUD	Maybe you should try that arcade next door. 
			Actor_Says(kActorCrazylegs, 770, kAnimationModeTalk); //09-0770.AUD	She looks like the kind of girl you see there all the time.
			Actor_Says(kActorMcCoy, 2040, kAnimationModeIdle);
		}
		break;

	case 1220: // GRIGORIAN
		// This dialogue does not mention Grigorian's note explicitly
		// but it does mention Grigorian talking about friends with resources.
		// So it needs that clue as a prerequisite
		// for that specific part of the dialogue (McCoy's cues only)
		Actor_Says(kActorMcCoy, 1910, kAnimationModeTalk); //00-1910.AUD	You know a man named Spencer Grigorian?
		if (Game_Flag_Query(kFlagCrazylegsIsReplicant)
		|| Actor_Query_Friendliness_To_Other(kActorCrazylegs, kActorMcCoy) < 50) {
			Actor_Says(kActorCrazylegs, 780, 12); //09-0780.AUD	No, I never heard of him.
			Actor_Says(kActorMcCoy, 2045, 17); //00-2045.AUD	Spencer Grigorian. The Citizens Against Replicant Slavery. CARS!
		}
		Actor_Says(kActorCrazylegs, 790, 14); //09-0790.AUD	Gotta be a thousand dealers in the city and you’re picking on me.
		Actor_Says(kActorMcCoy, 2050, kAnimationModeTalk); //00-2050.AUD	I know you know about CARS.
		if (_vm->_cutContent) {
			Actor_Says(kActorMcCoy, 1890, 23); //00-1890.AUD	You recognize this?
		} else {
			Actor_Change_Animation_Mode(kActorMcCoy, 23);
			Delay(2000);
			Item_Pickup_Spin_Effect_From_Actor(kModelAnimationGrigoriansNote, kActorMcCoy, 0, 0);
			Actor_Says(kActorMcCoy, 1890, 13); //00-1890.AUD	You recognize this?
		}
		Actor_Says(kActorMcCoy, 4385, 15); //00-4385.AUD	"Help these lost souls." Isn't that what it said?
		Delay(1000);
#if BLADERUNNER_ORIGINAL_BUGS
		Actor_Says(kActorMcCoy, 2050, kAnimationModeTalk);
		Actor_Says(kActorCrazylegs, 790, 14);
#else	
		Actor_Says(kActorMcCoy, 2055, 19); //00-2055.AUD	Grigorian was talking about friends with resources.
		Actor_Says(kActorMcCoy, 2060, 14); //00-2060.AUD	People who could set them up with vehicles.
#endif
		Actor_Says(kActorCrazylegs, 800, 15); //09-0800.AUD	Give me a break, will ya? I’m just trying to make an honest buck.
		if (Player_Query_Agenda() == kPlayerAgendaSurly  
		|| Player_Query_Agenda() == kPlayerAgendaErratic) {
			Actor_Says(kActorMcCoy, 2065, 18); //00-2065.AUD	If you’re honest, Crazy, I’m a doughnut.
			Actor_Modify_Friendliness_To_Other(kActorCrazylegs, kActorMcCoy, -2);
		}
		if (!Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
			Actor_Says(kActorMcCoy, 2070, 14); //00-2070.AUD	And any transactions with Replicants are illegal on Terra.
			if (!Game_Flag_Query(kFlagCrazylegsIsReplicant)) {
				Actor_Says(kActorCrazylegs, 810, 16); //09-0810.AUD	I know, I know!
			} else {
				Delay(2000);
				Actor_Says(kActorCrazylegs, 1030, 16); //09-1030.AUD	I don’t care whether they’re Reps or humans as long as the chinyen is real.
			}
		}
		if (_vm->_cutContent) {
			Game_Flag_Set(kFlagCrazylegsTalkGrigorian);
			Actor_Clue_Acquire(kActorMcCoy, kClueCrazylegsInterview2, true, kActorCrazylegs);
		}
		dialogueWithCrazylegs2();
		break;

	case 1230: // CAR REGISTRATION
		Actor_Says(kActorMcCoy, 1915, 12);
		if (Actor_Clue_Query(kActorMcCoy, kClueCarRegistration1)) {
			if (_vm->_cutContent) {
				if (!Game_Flag_Query(kFlagCrazylegsIsReplicant)
				&& Actor_Query_Friendliness_To_Other(kActorCrazylegs, kActorMcCoy) > 49) {
					Actor_Says(kActorCrazylegs, 840, 14); //09-0840.AUD	Hey, look. A sexy blonde wants to pay top dollar for the ugliest car in the place…
					Actor_Says(kActorCrazylegs, 850, 15);
					Actor_Says(kActorMcCoy, 2080, kAnimationModeTalk);
					Actor_Says(kActorCrazylegs, 860, 16);
					Actor_Says(kActorCrazylegs, 870, kAnimationModeTalk);
					Actor_Clue_Acquire(kActorMcCoy, kClueDektoraConfession, true, kActorCrazylegs);
				} else {
					Actor_Says(kActorCrazylegs, 820, kAnimationModeTalk);
					Actor_Says(kActorMcCoy, 2075, 13); //00-2075.AUD	I’ve seen the registration. I know a woman bought it from you.
					// Made it so Crazylegs is more resilient to answering McCoys question about the car registration if he is a replicant, but Crazylegs eventually relents
					// when McCoy puts pressure on him.
					Actor_Says(kActorCrazylegs, 1120, 15); //09-1120.AUD	I don’t know what you’re talking about.
					if (Player_Query_Agenda() != kPlayerAgendaSurly 
					&& Player_Query_Agenda() != kPlayerAgendaErratic) {
						Actor_Says(kActorMcCoy, 3910, 19); //00-3910.AUD	You’re lying. 
						Actor_Says(kActorCrazylegs, 1170, 16); //09-1170.AUD	I might lie about a sticker price but not about this.
					} else {
						Actor_Says(kActorMcCoy, 8519, 14);//00-8519.AUD	What do you say we dish each other the straight goods.
						Delay (2000);
						Actor_Says(kActorCrazylegs, 830, 12); //09-0830.AUD	Oh-- Ooh, that Sedan.
						Actor_Says(kActorCrazylegs, 840, 14);
						Actor_Says(kActorCrazylegs, 850, 15);
						Actor_Says(kActorMcCoy, 2080, kAnimationModeTalk);
						Actor_Says(kActorCrazylegs, 860, 16);
						Actor_Says(kActorCrazylegs, 870, kAnimationModeTalk);
						Actor_Clue_Acquire(kActorMcCoy, kClueDektoraConfession, true, kActorCrazylegs);
					}
				} 
			} else {
				Actor_Says(kActorCrazylegs, 830, 12); //09-0830.AUD	Oh-- Ooh, that Sedan.
				Actor_Says(kActorCrazylegs, 840, 14);
				Actor_Says(kActorCrazylegs, 850, 15);
				Actor_Says(kActorMcCoy, 2080, kAnimationModeTalk);
				Actor_Says(kActorCrazylegs, 860, 16);
				Actor_Says(kActorCrazylegs, 870, kAnimationModeTalk);
#if BLADERUNNER_ORIGINAL_BUGS
#else
				// This clue was never acquired, even though it is checked in KIA
				// (so that it appears as a recording in KIA if acquired)
				// It also enables the "WOMAN" conversation option with CrazyLegs.
				if (!_vm->_cutContent) {
					Actor_Clue_Acquire(kActorMcCoy, kClueCrazylegsInterview1, true, kActorCrazylegs);
				}
			}
#endif // BLADERUNNER_ORIGINAL_BUGS
		} else if (Actor_Clue_Query(kActorMcCoy, kClueCarRegistration3)) {
			if (_vm->_cutContent) {
				if (Game_Flag_Query(kFlagCrazylegsIsReplicant)
				|| Actor_Query_Friendliness_To_Other(kActorCrazylegs, kActorMcCoy) < 50) {
					Actor_Says(kActorCrazylegs, 880, 12); //09-0880.AUD	Family type cars ain’t my specialty.
					Actor_Says(kActorCrazylegs, 890, 14); //09-0890.AUD	I can hook you up though, if that’s really what you want.
					Actor_Says(kActorMcCoy, 2085, kAnimationModeTalk); //00-2085.AUD	You sold this to a Blake Williams. I’ve seen the registration.
					Actor_Says(kActorCrazylegs, 550, 15); //09-0550.AUD	That’s impossible.
					Actor_Says(kActorMcCoy, 3910, 13);//00-3910.AUD	You’re lying.
					Actor_Says(kActorCrazylegs, 1170, 16); //09-1170.AUD	I might lie about a sticker price but not about this.
					if (Player_Query_Agenda() != kPlayerAgendaSurly 
					&& Player_Query_Agenda() != kPlayerAgendaErratic) {
						Actor_Says(kActorMcCoy, 4515, 13); //00-4515.AUD	What do you know?
						Actor_Says(kActorCrazylegs, 1150, 14); //09-1150.AUD	Only thing I know is that the best deals you can make are right in this showroom.
					} else {
						Actor_Says(kActorMcCoy, 8519, 14);//00-8519.AUD	What do you say we dish each other the straight goods.
						Delay (2000);
						Actor_Says(kActorCrazylegs, 830, 12); //09-0830.AUD	Oh-- Ooh, that Sedan.
						Actor_Says(kActorMcCoy, 2090, 19); //00-2090.AUD	Blake Williams is a fake name.
						Actor_Says(kActorCrazylegs, 910, 16); //09-0910.AUD	You just never know about some people.
						Actor_Says(kActorMcCoy, 2095, 14); //00-2095.AUD	Did you forget to run a credit check?
						Actor_Says(kActorCrazylegs, 920, kAnimationModeTalk); //09-0920.AUD	He paid cash.
						Actor_Says(kActorMcCoy, 2100, 15); //00-2100.AUD	And people come in here and buy cars with cash every day!
						Actor_Says(kActorCrazylegs, 930, 12); //09-0930.AUD	In this neighborhood every hour is more like it.
						Actor_Says(kActorCrazylegs, 940, 14); //09-0940.AUD	But then again I do have the best selection in town.
						Actor_Says(kActorMcCoy, 2105, kAnimationModeTalk); //00-2105.AUD	What did this guy look like?
						Actor_Says(kActorCrazylegs, 950, 15); //09-0950.AUD	Nothing special. Beard, dark hair. Had these eyes, kinda…
						// Made it so the part of the conversation where Crazy and McCoy talk about Clovis and his piercing eyes only plays if McCoy has a close up photo of Clovis or Morajis description.
						if (Actor_Clue_Query(kActorMcCoy, kClueMorajiInterview)
						|| Actor_Clue_Query(kActorMcCoy, kClueAnimalMurderSuspect)
						|| Actor_Clue_Query(kActorMcCoy, kClueClovisAtMoonbus)
						|| Actor_Clue_Query(kActorMcCoy, kClueDektorasDressingRoom)) {	
							Actor_Says(kActorMcCoy, 2110, kAnimationModeIdle); //00-2110.AUD	Piercing?	
						} else {
							Actor_Says(kActorMcCoy, 2750, kAnimationModeTalk); //00-2750.AUD	Okay, I get the picture.
						}
						Actor_Says(kActorCrazylegs, 960, 16); //09-0960.AUD	Yeah. Pretty scary. But, heck, I never turn away a customer.
						// Made it so you receive the Crazylegs interview 2 clue if Clovis bought the car. 
						Actor_Clue_Acquire(kActorMcCoy, kClueCrazylegsInterview1, true, kActorCrazylegs);
					}
				} else {
					Actor_Says(kActorMcCoy, 2085, kAnimationModeTalk); //00-2085.AUD	You sold this to a Blake Williams. I’ve seen the registration.
					Actor_Says(kActorCrazylegs, 720, 15); //09-0720.AUD	Uh-huh.
					Actor_Says(kActorMcCoy, 2090, 19); //00-2090.AUD	Blake Williams is a fake name.
					Actor_Says(kActorCrazylegs, 910, 16); //09-0910.AUD	You just never know about some people.
					if (Player_Query_Agenda() != kPlayerAgendaPolite) {
						Actor_Says(kActorMcCoy, 2095, 14); //00-2095.AUD	Did you forget to run a credit check?
						Actor_Says(kActorCrazylegs, 920, kAnimationModeTalk); //09-0920.AUD	He paid cash.
						Actor_Says(kActorMcCoy, 2100, 15); //00-2100.AUD	And people come in here and buy cars with cash every day!
						Actor_Says(kActorCrazylegs, 930, 12); //09-0930.AUD	In this neighborhood every hour is more like it.
						Actor_Says(kActorCrazylegs, 940, 14); //09-0940.AUD	But then again I do have the best selection in town.
					}
					Actor_Says(kActorMcCoy, 2105, kAnimationModeTalk); //00-2105.AUD	What did this guy look like?
					Actor_Says(kActorCrazylegs, 950, 15); //09-0950.AUD	Nothing special. Beard, dark hair. Had these eyes, kinda…
					// Made it so the part of the conversation where Crazy and McCoy talk about Clovis and his piercing eyes only plays if McCoy has a close up photo of Clovis or Morajis description.
					if (Actor_Clue_Query(kActorMcCoy, kClueMorajiInterview)
					|| Actor_Clue_Query(kActorMcCoy, kClueAnimalMurderSuspect)
					|| Actor_Clue_Query(kActorMcCoy, kClueClovisAtMoonbus)
					|| Actor_Clue_Query(kActorMcCoy, kClueDektorasDressingRoom)) {	
						Actor_Says(kActorMcCoy, 2110, kAnimationModeIdle); //00-2110.AUD	Piercing?	
					} else {
						Actor_Says(kActorMcCoy, 2750, kAnimationModeTalk); //00-2750.AUD	Okay, I get the picture.
					}
					Actor_Says(kActorCrazylegs, 960, 16); //09-0960.AUD	Yeah. Pretty scary. But, heck, I never turn away a customer.
					// Made it so you receive the Crazylegs interview 2 clue if Clovis bought the car. 
					Actor_Clue_Acquire(kActorMcCoy, kClueCrazylegsInterview1, true, kActorCrazylegs);
				}
			} else {
				Actor_Says(kActorMcCoy, 2085, kAnimationModeTalk); //00-2085.AUD	You sold this to a Blake Williams. I’ve seen the registration.
				Actor_Says(kActorCrazylegs, 830, 12); //09-0830.AUD	Oh-- Ooh, that Sedan.
				Actor_Says(kActorMcCoy, 2090, 19); //00-2090.AUD	Blake Williams is a fake name.
				Actor_Says(kActorCrazylegs, 910, 16);
				Actor_Says(kActorMcCoy, 2095, 14);
				Actor_Says(kActorCrazylegs, 920, kAnimationModeTalk);
				Actor_Says(kActorMcCoy, 2100, 15);
				Actor_Says(kActorCrazylegs, 930, 12);
				Actor_Says(kActorCrazylegs, 940, 14);
				Actor_Says(kActorMcCoy, 2105, kAnimationModeTalk); //00-2105.AUD	What did this guy look like?
				Actor_Says(kActorCrazylegs, 950, 15); //09-0950.AUD	Nothing special. Beard, dark hair. Had these eyes, kinda…
				Actor_Says(kActorMcCoy, 2110, kAnimationModeIdle); //00-2110.AUD	Piercing?
				Actor_Says(kActorCrazylegs, 960, 16); //09-0960.AUD	Yeah. Pretty scary. But, heck, I never turn away a customer.
			}
		}
		break;
	}
}

void SceneScriptHF05::dialogueWithCrazylegs2() { // Restored feature - Original: it is impossible to obtain this clue
	Dialogue_Menu_Clear_List();
	DM_Add_To_List(1250, -1, 6, 10); // ARREST
	DM_Add_To_List_Never_Repeat_Once_Selected(1260, 10,  5, -1); // WARNING

	Dialogue_Menu_Appear(320, 240);
	int answer = Dialogue_Menu_Query_Input();
	Dialogue_Menu_Disappear();

	if (answer == 1250) { // ARREST
		Actor_Says(kActorMcCoy, 1955, 17); //00-1955.AUD	We’re taking a little drive downtown.
		// Made it so if Crazylegs is a replicant and McCoy arrests him McCoy remembers an incet tape that he saw at the police station and it was of Crazylegs.
		// McCoy then calls out Crazylegs for being a replicant which he denies but McCoy persists. Crazylegs then tries to flee and the player has to shoot him 
		// quickly before he escaps offscreen. Of course the player can spare him by putting the gun away. 
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagCrazylegsIsReplicant))  {
				Delay (1000);
				Actor_Says(kActorMcCoy, 525, 13); //00-0525.AUD	I've seen you before...
				Actor_Says(kActorCrazylegs, 540, 12); //09-0540.AUD	Huh, what--?
				Actor_Says(kActorMcCoy, 7260, 13); //00-7260.AUD	Didn't I see an incept tape at the—
				Actor_Says(kActorCrazylegs, 1120, 14); //09-1120.AUD	I don’t know what you’re talking about.
				Delay (1000);
				Actor_Says(kActorMcCoy, 6865, 14); //00-6865.AUD	You're a Replicant.
				Actor_Says(kActorCrazylegs, 550, 13); //09-0550.AUD	That’s impossible.
				Delay (1000);
				if (!Game_Flag_Query(kFlagMcCoyIsHelpingReplicants))  {				
					Actor_Says(kActorMcCoy, 2755, 15); //00-2755.AUD	You all right? You look a little pale.
					Delay (2000);
					Actor_Says(kActorCrazylegs, 1000, 12); //09-1000.AUD	I got customers on the line, so I ain’t got time to chit chat.
					Actor_Set_Goal_Number(kActorCrazylegs, kGoalCrazyLegsLeavesShowroom);
					Actor_Says(kActorMcCoy, 8955, 16); //00-8955.AUD	Stop!
					Actor_Set_Targetable(kActorCrazylegs, true);
					Player_Set_Combat_Mode(true);
					Player_Gains_Control();
				} else {
					Delay(1000);
					Actor_Says(kActorMcCoy, 3690, 14); //00-3690.AUD	Look. I wanna warn you. There’s a woman looking for you and your friends.
					Delay(1000);
					Actor_Says(kActorMcCoy, 6720, 18); //00-6720.AUD	Watch your back.
					Actor_Says(kActorCrazylegs, 610, 14); //09-0610.AUD	I gotta get my priorities straight. You’re right.
					Actor_Says(kActorMcCoy, 2860, 14);                  // YouTakeCareOfYourself
					Actor_Set_Friendliness_To_Other(kActorCrazylegs, kActorMcCoy, 60);
				}
			} else {
				Actor_Says(kActorCrazylegs, 580, kAnimationModeTalk);
				Actor_Says(kActorCrazylegs, 590, 15); //09-0590.AUD	You like that Bishy Caddy, right? I’ll give it to you at the absolute lowest price.
				Actor_Says(kActorMcCoy, 1990, 17);
				Actor_Says(kActorCrazylegs, 600, 16); //09-0600.AUD	Not a bribe. Just a gift. You know, out of friendship.
				if (Player_Query_Agenda() == kPlayerAgendaSurly 
				|| Player_Query_Agenda() == kPlayerAgendaErratic) {
					Actor_Says(kActorMcCoy, 7000, 13); //00-7000.AUD	Yeah, okay. I'll take it.
					Actor_Says(kActorCrazylegs, 540, 12); //09-0540.AUD	Huh, what--?
					Actor_Says(kActorMcCoy, 120, 12); //00-0120.AUD	It's kind of ugly but you talked me into it.
					Delay(1000);
					Actor_Says(kActorCrazylegs, 330, 12); //09-0330.AUD	And, honestly… No, frankly, I gotta tell you it’s got your name written all over it: Ray McCovey.
					Actor_Says(kActorMcCoy, 1840, kAnimationModeTalk); //00-1840.AUD	McCoy.
					Actor_Change_Animation_Mode(kActorMcCoy, 23);
					Actor_Change_Animation_Mode(kActorCrazylegs, 23);
					Delay(800);
					Item_Pickup_Spin_Effect_From_Actor(kModelAnimationSpinnerKeys, kActorMcCoy, 0, 0);
					Actor_Modify_Friendliness_To_Other(kActorClovis, kActorMcCoy, 1);
					Actor_Modify_Friendliness_To_Other(kActorSteele, kActorMcCoy, -1);
					Actor_Modify_Friendliness_To_Other(kActorGuzza, kActorMcCoy, -1);
					Actor_Set_Friendliness_To_Other(kActorCrazylegs, kActorMcCoy, 60);
					Delay(1000);
				} else {
					Actor_Says(kActorMcCoy, 1995, kAnimationModeTalk); //00-1995.AUD	We ain’t friends, Crazy.
					Delay(1000);
					Actor_Says(kActorMcCoy, 1960, 23); //00-1960.AUD	Give me your wheelchair’s ignition key and put your hands on top of your head.
					Actor_Change_Animation_Mode(kActorMcCoy, 23);
					Actor_Change_Animation_Mode(kActorCrazylegs, 23);
					Delay(800);
					Item_Pickup_Spin_Effect_From_Actor(kModelAnimationSpinnerKeys, kActorMcCoy, 0, 0);
					Delay(1000);
					Actor_Says(kActorMcCoy, 1980, 23); //00-1980.AUD	Give me your phone.
					Actor_Change_Animation_Mode(kActorMcCoy, 23);
					Actor_Change_Animation_Mode(kActorCrazylegs, 23);
					Delay(2000);
					if (Player_Query_Agenda() != kPlayerAgendaSurly 
					|| Player_Query_Agenda() != kPlayerAgendaErratic) {
						Actor_Says(kActorMcCoy, 1985, kAnimationModeTalk); //00-1985.AUD	I’ll try to clear it so you aren’t stuck in a cell with fifty mutant speed loaders
					}
					Delay(1000);
					// Made it so you receive the Crazylegs grovels clue.
					Actor_Clue_Acquire(kActorMcCoy, kClueCrazylegGrovels, true, kActorCrazylegs);
					Actor_Modify_Friendliness_To_Other(kActorClovis, kActorMcCoy, -1);
					Actor_Modify_Friendliness_To_Other(kActorSteele, kActorMcCoy, 1);
					Actor_Modify_Friendliness_To_Other(kActorGuzza, kActorMcCoy, 1);
					Actor_Modify_Friendliness_To_Other(kActorCrazylegs, kActorMcCoy, -2);
					Game_Flag_Set(kFlagCrazylegsArrested);
					Game_Flag_Reset(kFlagMcCoyIsHelpingReplicants);
					Actor_Put_In_Set(kActorCrazylegs, kSetPS09);
					// This XYZ is awry (won't show Crazylegs inside a cell or at all in the PS09 scene)
					// but it is eventually overridden by the PS09 script, which puts Crazylegs at the right spot
					Actor_Set_At_XYZ(kActorCrazylegs, -315.15f, 0.0f, 241.06f, 512);
					Actor_Set_Goal_Number(kActorCrazylegs, kGoalCrazyLegsIsArrested);
					Game_Flag_Set(kFlagCrazylegsArrestedTalk);
					if (Game_Flag_Query(kFlagSpinnerAtNR01)) {
						Set_Enter(kSetNR01, kSceneNR01);
					} else {
						Game_Flag_Set(kFlagHF05toHF01);
						Set_Enter(kSetHF01, kSceneHF01);
					}
				}	
			}
		} else {
			Actor_Says(kActorMcCoy, 1955, 17);
			Actor_Says(kActorMcCoy, 1960, 23);
			if (_vm->_cutContent) {
				// This extra check is required to fix a problematic saved game where
				// the clue kClueGrigoriansResources was acquired in Vanilla Mode,
				// due to a bug that affected ScummVM 2.5.0, 2.5.1 and 2.6.0.
				// This bug only occurs if the game's data files contain
				// separate CDFRAMESx.DAT files instead of a single HDFRAMES.DAT file.
				// In Vanilla Mode the currently loaded CDFRAMES files
				// is missing an animation (Bug #13727).
				// In Restored Content mode we load all animation files
				// so the bug, expectedly, does not manifest there.
				// The animation for the keys item is the culprit.
				Item_Pickup_Spin_Effect(kModelAnimationSpinnerKeys, 315, 327);
			}
			Delay(2000);
			Actor_Says(kActorMcCoy, 1980, 23);
			Actor_Says(kActorMcCoy, 1985, kAnimationModeTalk);
			Actor_Says(kActorCrazylegs, 580, kAnimationModeTalk);
			Actor_Says(kActorCrazylegs, 590, 15);
			Actor_Says(kActorMcCoy, 1990, 17);
			Actor_Says(kActorCrazylegs, 600, 16);
			Actor_Says(kActorMcCoy, 1995, kAnimationModeTalk);
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
		}
	} else if (answer == 1260) { // WARNING
		Actor_Says(kActorMcCoy, 1965, 12);
		Actor_Says(kActorMcCoy, 1970, kAnimationModeTalk);
		Actor_Says(kActorMcCoy, 1975, kAnimationModeTalk);
		Actor_Says(kActorCrazylegs, 610, 16);
		if (_vm->_cutContent) {
			Actor_Modify_Friendliness_To_Other(kActorCrazylegs, kActorMcCoy, 10);
			Actor_Modify_Friendliness_To_Other(kActorClovis, kActorMcCoy, 1);
			Actor_Modify_Friendliness_To_Other(kActorSteele, kActorMcCoy, -1);
			Actor_Modify_Friendliness_To_Other(kActorGuzza, kActorMcCoy, -1);
			Actor_Set_Friendliness_To_Other(kActorCrazylegs, kActorMcCoy, 60);
		}
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
	if (_vm->_cutContent) {
		if (!Game_Flag_Query(kFlagMcCoyIsInnocent)
		|| Player_Query_Agenda() == kPlayerAgendaSurly 
		|| Player_Query_Agenda() == kPlayerAgendaErratic) {
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
	} else {
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
}			

void SceneScriptHF05::talkWithDektora() {
	Actor_Face_Actor(kActorMcCoy, kActorDektora, true);
	Actor_Face_Actor(kActorDektora, kActorMcCoy, true);
	// Added in some lines for Dektora. I noticed that when she says some of her lines she is over emotional where as for other lines she is
	// totally calm and almost emotionless. Playing these lines back to back is really jarring since she switches from totally calm to downright hysterical.
	// So what I will do is for the lines where Dektora is overly emotional she is human and when she is calm she is a replicant.
	if (_vm->_cutContent) {
		if (Game_Flag_Query(kFlagDektoraIsReplicant)
		|| !Game_Flag_Query(kFlagMcCoyIsInnocent)
		|| Game_Flag_Query(kFlagMcCoyRetiredHuman)
		|| Actor_Query_Friendliness_To_Other(kActorCrazylegs, kActorMcCoy) < 50) {
			if (!Game_Flag_Query(kFlagMcCoyIsInnocent)
			|| Player_Query_Agenda() == kPlayerAgendaSurly 
			|| Player_Query_Agenda() == kPlayerAgendaErratic) {
				if (!Game_Flag_Query(kFlagDektoraIsReplicant)) {
					Actor_Says(kActorDektora, 120, 12); //03-0120.AUD	I won’t let them shoot us down like that.
				} else {
					Actor_Says(kActorDektora, 2660, 12); //03-2660.AUD	I’ll be right back.
				}
			} else {
				Actor_Says(kActorDektora, 90, -1); //03-0090.AUD	Ray!?
			}
			Delay(1000);
			Actor_Says(kActorMcCoy, 8990, kAnimationModeTalk);
			Actor_Says(kActorDektora, 2670, 13); //03-2670.AUD	One of Sadik’s bombs.
#if BLADERUNNER_ORIGINAL_BUGS
	Actor_Says(kActorDektora, 2680, 17);
#else
	// Dektora is interrupted here
	
	Actor_Says_With_Pause(kActorDektora, 2680, 0.0f, 17); //03-2680.AUD	I stole it. If they want a fight--
#endif // BLADERUNNER_ORIGINAL_BUGS
			if (Player_Query_Agenda() == kPlayerAgendaSurly 
			|| Player_Query_Agenda() == kPlayerAgendaErratic) {
				Actor_Says(kActorMcCoy, 4180, 13); //00-4180.AUD	You sure?
			} else {
				Actor_Says(kActorMcCoy, 8995, 14); //00-8995.AUD	No.
			}
			if (!Game_Flag_Query(kFlagDektoraIsReplicant)) {
				Actor_Says(kActorDektora, 140, 12); //03-0140.AUD	I’m not afraid to use it on them, Ray.
			} else {
				Actor_Says(kActorDektora, 2690, 15); //03-2690.AUD	They’re little people with small minds.
			}
			if (Game_Flag_Query(kFlagDektoraIsReplicant)) {
				if (!Game_Flag_Query(kFlagNR04EarlyQStungByScorpions)) {
					Actor_Says(kActorDektora, 1420, 15); //03-1420.AUD	This will be the first time I’ve killed a human without being ordered to do it by another human.
					Actor_Says(kActorDektora, 1430, 12); //03-1430.AUD	It’s strangely liberating.
				}
			}
			if (Player_Query_Agenda() != kPlayerAgendaSurly 
			&& Player_Query_Agenda() != kPlayerAgendaErratic) {
				Actor_Says_With_Pause(kActorMcCoy, 9000, 1.0f, 16); //00-9000.AUD	No!
				if (!Game_Flag_Query(kFlagDektoraIsReplicant)) {
					Actor_Says(kActorDektora, 150, 12); //03-0150.AUD	We have no other choice.
					Actor_Says_With_Pause(kActorMcCoy, 9005, 1.0f, 19); //00-9005.AUD	We'll find another way.
				} else {
					Delay(2000);
				}
			}
		} else {
			Delay(1000);
			Actor_Says(kActorMcCoy, 8990, kAnimationModeTalk); //00-8990.AUD	What have you got there?
			Actor_Says(kActorDektora, 2670, 13); //03-2670.AUD	One of Sadik’s bombs.
			Delay(2000);
		}
	} else {
		Actor_Says(kActorDektora, 2660, 12);
		Actor_Says(kActorMcCoy, 8990, kAnimationModeTalk);
		Actor_Says(kActorDektora, 2670, 13);
#if BLADERUNNER_ORIGINAL_BUGS
	Actor_Says(kActorDektora, 2680, 17);
#else
	// Dektora is interrupted here
	Actor_Says_With_Pause(kActorDektora, 2680, 0.0f, 17);
#endif // BLADERUNNER_ORIGINAL_BUGS
		Actor_Says(kActorMcCoy, 8995, 14);
		Actor_Says(kActorDektora, 2690, 15);
		Actor_Says_With_Pause(kActorMcCoy, 9000, 1.0f, 16);
		Actor_Says_With_Pause(kActorMcCoy, 9005, 1.0f, 19);
	}
	Actor_Says(kActorMcCoy, 1765, 17); //00-1765.AUD	Wait a minute. We’re right on top of the old subway system!
	if (_vm->_cutContent) {
		if (Game_Flag_Query(kFlagDektoraIsReplicant)
		|| !Game_Flag_Query(kFlagMcCoyIsInnocent)
		|| Game_Flag_Query(kFlagMcCoyRetiredHuman)
		|| Actor_Query_Friendliness_To_Other(kActorCrazylegs, kActorMcCoy) < 50) {
			if (!Game_Flag_Query(kFlagDektoraIsReplicant)) {
				Actor_Says(kActorDektora, 160, 12); //03-0160.AUD	But they’ll follow us.
				Actor_Says(kActorMcCoy, 1770, 15); //00-1770.AUD	Not if we can get a ground car down there.
			}
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
			Actor_Says(kActorDektora, 1920, kAnimationModeTalk); // 03-1920.AUD	I.… no, that's ridiculous.
		}
	} else {
		Actor_Says(kActorDektora, 170, kAnimationModeTalk); //03-0170.AUD	What if it’s collapsed?
	}
	Actor_Says_With_Pause(kActorMcCoy, 1780, 1.0f, 18); //00-1780.AUD	It’s worth a shot.
}

void SceneScriptHF05::talkWithLucy() {
	Actor_Face_Actor(kActorMcCoy, kActorLucy, true);
	Actor_Face_Actor(kActorLucy, kActorMcCoy, true);
	if (_vm->_cutContent) {
		if (!Game_Flag_Query(kFlagMcCoyIsInnocent)
		|| Player_Query_Agenda() == kPlayerAgendaSurly 
		|| Player_Query_Agenda() == kPlayerAgendaErratic) {
			if (Game_Flag_Query(kFlagLucyIsReplicant)) {
				Actor_Says(kActorLucy, 400, 16);
			} else {
				Actor_Says(kActorLucy, 380, 13); //06-0380.AUD	Ray.
			}
		} else {
			Actor_Says(kActorLucy, 380, 13); //06-0380.AUD	Ray.
		}
	} else {
		Actor_Says(kActorLucy, 400, 16);
	}
	if (_vm->_cutContent) {
		Actor_Says(kActorMcCoy, 8990, kAnimationModeTalk); //00-8990.AUD	What have you got there?
		Actor_Change_Animation_Mode(kActorLucy, 13);
		Delay(2000);
	}
	Actor_Says(kActorMcCoy, 1750, 14);
	Actor_Says(kActorLucy, 410, 12); //06-0410.AUD	I stole it from Sadik.
	if (_vm->_cutContent) {
		if (!Game_Flag_Query(kFlagMcCoyIsInnocent)
		|| Player_Query_Agenda() == kPlayerAgendaSurly 
		|| Player_Query_Agenda() == kPlayerAgendaErratic) {
			if (Game_Flag_Query(kFlagLucyIsReplicant)) {
				Actor_Says(kActorLucy, 420, 14); //06-0420.AUD	We can die together! The only thing we’ll feel is the love we have for each other.
				if (Player_Query_Agenda() == kPlayerAgendaSurly 
				&& Player_Query_Agenda() == kPlayerAgendaErratic) {
					Actor_Says(kActorMcCoy, 1755, 16); //00-1755.AUD	I refuse to go out that way!
					Actor_Says(kActorLucy, 430, 18); //06-0430.AUD	We have no other choice!
					Actor_Says_With_Pause(kActorMcCoy, 1760, 1.0f, 15); //00-1760.AUD	We’ve got to!
					Delay(1000);
				} else {
					Actor_Says(kActorMcCoy, 8995, 14); //00-8995.AUD	No.
					Actor_Says(kActorLucy, 430, 18); //06-0430.AUD	We have no other choice!
					Actor_Says_With_Pause(kActorMcCoy, 9000, 1.0f, 16); //00-9000.AUD	No!
					Actor_Says_With_Pause(kActorMcCoy, 9005, 1.0f, 19); //00-9005.AUD	We'll find another way.
				}
			} else {
				Delay(1000);
			}
		} else {
			Delay(1000);
		}
	} else {
		Actor_Says(kActorLucy, 420, 14); //06-0420.AUD	We can die together! The only thing we’ll feel is the love we have for each other.
		Actor_Says(kActorMcCoy, 1755, 16); //00-1755.AUD	I refuse to go out that way!
		Actor_Says(kActorLucy, 430, 18); //06-0430.AUD	We have no other choice!
		Actor_Says_With_Pause(kActorMcCoy, 1760, 1.0f, 15); //00-1760.AUD	We’ve got to!
	}
	Actor_Says(kActorMcCoy, 1765, 17); //00-1765.AUD	Wait a minute. We’re right on top of the old subway system!
	if (_vm->_cutContent) {
		if (Game_Flag_Query(kFlagLucyIsReplicant)
		|| !Game_Flag_Query(kFlagMcCoyIsInnocent)
		|| Game_Flag_Query(kFlagMcCoyRetiredHuman)
		|| Actor_Query_Friendliness_To_Other(kActorCrazylegs, kActorMcCoy) < 50) {
			Actor_Says(kActorLucy, 440, kAnimationModeTalk);
			Actor_Says(kActorMcCoy, 1770, 15); //00-1770.AUD	Not if we can get a ground car down there.
		}
	} else {
		Actor_Says(kActorLucy, 440, kAnimationModeTalk);
		Actor_Says(kActorMcCoy, 1770, 15); //00-1770.AUD	Not if we can get a ground car down there.
	}
	Actor_Says(kActorMcCoy, 1775, kAnimationModeTalk); //00-1775.AUD	Hell, we can drive right through that tunnel and disappear.
	Actor_Says(kActorLucy, 450, 17);
	Actor_Says_With_Pause(kActorMcCoy, 1780, 1.0f, 18); //00-1780.AUD	It’s worth a shot.
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
		if (_vm->_cutContent) {
			if (Actor_Query_Friendliness_To_Other(kActorCrazylegs, kActorMcCoy) > 49) {
				Actor_Says(kActorCrazylegs, 0, kAnimationModeTalk); //09-0000.AUD	How’s it going, Ray?
			} else {
				Actor_Says(kActorCrazylegs, 380, 12); //09-0380.AUD	You’ve been thinking about the Caddy, haven’t you?
			}
		} else {
			Actor_Says(kActorCrazylegs, 0, kAnimationModeTalk); //09-0000.AUD	How’s it going, Ray?
		}
		// Made it so Crazylegs only says this line if you talked to him about Dektora.
		if (_vm->_cutContent) {
			if (Actor_Query_Is_In_Current_Set(kActorDektora)) {
				if (Actor_Clue_Query(kActorMcCoy, kClueCrazylegsInterview1)
				&& !Game_Flag_Query(kFlagCrazylegsIsReplicant)) {
					Actor_Says(kActorCrazylegs, 10, 12); //09-0010.AUD	Wait a minute, I thought you was going to arrest her.
					if (Player_Query_Agenda() == kPlayerAgendaSurly 
					|| Player_Query_Agenda() == kPlayerAgendaErratic) {
						Actor_Says(kActorMcCoy, 1715, 19); //00-1715.AUD	You don’t get paid the big bucks to think, Crazy.
						Actor_Modify_Friendliness_To_Other(kActorCrazylegs, kActorMcCoy, -2);
					}
				}
			}
		} else {
			Actor_Says(kActorCrazylegs, 10, 12); //09-0010.AUD	Wait a minute, I thought you was going to arrest her.
			Actor_Says(kActorMcCoy, 1715, 19); //00-1715.AUD	You don’t get paid the big bucks to think, Crazy.
		}
		Actor_Says(kActorMcCoy, 1720, -1); //00-1720.AUD	Any of your Spinners up and running?
		Actor_Says(kActorCrazylegs, 20, 14); //09-0020.AUD	Uh… Sure, got one up on the roof.
		Actor_Says(kActorCrazylegs, 30, 15); //09-0030.AUD	A real beaut. Ain’t a cheap ride, though, I’ll tell you right now.
		Actor_Says(kActorMcCoy, 1725, kAnimationModeTalk); //00-1725.AUD	I gotta take it for a test drive.
		if (_vm->_cutContent) {
			if (Actor_Query_Friendliness_To_Other(kActorCrazylegs, kActorMcCoy) > 49) {
				if (Actor_Query_Friendliness_To_Other(kActorCrazylegs, kActorMcCoy) == 60) {
					Actor_Says(kActorCrazylegs, 40, 16); //09-0040.AUD	Ray, I-- I always liked you…
					Actor_Says(kActorCrazylegs, 50, kAnimationModeTalk); //09-0050.AUD	True, I hardly know you. You seem like a stand up guy.
				} else {
					Delay(1000);
					Actor_Says(kActorCrazylegs, 60, 12); //09-0060.AUD	Eventually, when this fiasco is all over and done with I--
					Actor_Says(kActorCrazylegs, 70, 13); //09-0070.AUD	I know you’ll get me on the com, right?
				}
				if (Player_Query_Agenda() != kPlayerAgendaSurly 
				&& Player_Query_Agenda() != kPlayerAgendaErratic) {
					Actor_Says(kActorMcCoy, 1730, kAnimationModeTalk); //00-1730.AUD	You’re a stand up guy, Crazy.
				} else {
					Actor_Says(kActorMcCoy, 5705, 18); //00-5705.AUD	Uh-huh.
				}
				Loop_Actor_Walk_To_Actor(kActorCrazylegs, kActorMcCoy, 28, false, false);
				Actor_Change_Animation_Mode(kActorMcCoy, 23);
				Actor_Change_Animation_Mode(kActorCrazylegs, 23);
				Delay(2000);
				Item_Pickup_Spin_Effect_From_Actor(kModelAnimationSpinnerKeys, kActorMcCoy, 0, 0);
				if (Player_Query_Agenda() != kPlayerAgendaSurly 
				&& Player_Query_Agenda() != kPlayerAgendaErratic) {
					Actor_Start_Speech_Sample(kActorCrazylegs, 80); //09-0080.AUD	That I am.
				}
				Actor_Clue_Acquire(kActorMcCoy, kClueSpinnerKeys, true, kActorCrazylegs);
				Delay(1000);
			} else {
				Delay(1000);
				Actor_Says(kActorCrazylegs, 1160, 13); //09-1160.AUD	Take a ride, McCoy. I already told you everything.
				if (Player_Query_Agenda() == kPlayerAgendaSurly 
				|| Player_Query_Agenda() == kPlayerAgendaErratic) {
					Actor_Change_Animation_Mode(kActorMcCoy, 5);
					Actor_Start_Speech_Sample(kActorMcCoy, 460); //00-0460.AUD	Hold it right there!
					Delay(1000);
					if (Actor_Query_Is_In_Current_Set(kActorDektora)) {
						if (!Game_Flag_Query(kFlagDektoraIsReplicant)) {
							Actor_Says(kActorDektora, 90, kAnimationModeTalk); //03-0090.AUD	Ray!?
						}
					} else if (Actor_Query_Is_In_Current_Set(kActorLucy)) {
						Actor_Says(kActorLucy, 380, kAnimationModeTalk); //06-0380.AUD	Ray.
					}
					if (!Game_Flag_Query(kFlagCrazylegsIsReplicant)) {
						Actor_Says(kActorCrazylegs, 430, 3); //09-0430.AUD	If this is a hold up, Ray, I don’t have any cash in the house.
					} else {
						Actor_Says(kActorCrazylegs, 480, 13); //09-0480.AUD	Hey, keep your paws off that, Ray!
					}
					Actor_Says(kActorMcCoy, 8519, -1);//00-8519.AUD	What do you say we dish each other the straight goods.
					Delay(2000);
					Actor_Says(kActorMcCoy, 8445, -1); //00-8445.AUD	Cough it up!
					Delay(1500);
					Actor_Says(kActorMcCoy, 1805, -1); //00-1805.AUD	Now!
					Delay(1000); 
					Player_Loses_Control();
					Loop_Actor_Walk_To_Actor(kActorCrazylegs, kActorMcCoy, 28, false, false);
					Player_Gains_Control();
					Actor_Change_Animation_Mode(kActorMcCoy, 23);
					Actor_Change_Animation_Mode(kActorCrazylegs, 23);
					Delay(800);
					Item_Pickup_Spin_Effect_From_Actor(kModelAnimationSpinnerKeys, kActorMcCoy, 0, 0);
					Delay(1000);
					Actor_Clue_Acquire(kActorMcCoy, kClueSpinnerKeys, true, kActorCrazylegs);
					Delay(1000);
				} else {
					Actor_Says(kActorMcCoy, 8519, 13);//00-8519.AUD	What do you say we dish each other the straight goods.
					Delay(2000);
					Actor_Says(kActorMcCoy, 8445, 14); //00-8445.AUD	Cough it up!
					Delay(1000);
					Loop_Actor_Walk_To_Actor(kActorCrazylegs, kActorMcCoy, 28, false, false);
					Player_Gains_Control();
					Actor_Change_Animation_Mode(kActorMcCoy, 23);
					Actor_Change_Animation_Mode(kActorCrazylegs, 23);
					Delay(800);
					Item_Pickup_Spin_Effect_From_Actor(kModelAnimationSpinnerKeys, kActorMcCoy, 0, 0);
					Delay(1000);
					Actor_Clue_Acquire(kActorMcCoy, kClueSpinnerKeys, true, kActorCrazylegs);
				}
			}
		} else {
			Actor_Says(kActorCrazylegs, 40, 16); //09-0040.AUD	Ray, I-- I always liked you…
			Actor_Says(kActorCrazylegs, 50, kAnimationModeTalk); //09-0050.AUD	True, I hardly know you. You seem like a stand up guy.
			Actor_Says(kActorCrazylegs, 60, 12); //09-0060.AUD	Eventually, when this fiasco is all over and done with I--
			Actor_Says(kActorCrazylegs, 70, 13); //09-0070.AUD	I know you’ll get me on the com, right?
			Actor_Says(kActorMcCoy, 1730, kAnimationModeTalk); //00-1730.AUD	You’re a stand up guy, Crazy.
			Loop_Actor_Walk_To_Actor(kActorCrazylegs, kActorMcCoy, 28, false, false);
			Item_Pickup_Spin_Effect(kModelAnimationSpinnerKeys, 315, 327);
			Actor_Says(kActorCrazylegs, 80, 23); //09-0080.AUD	That I am.
			Actor_Clue_Acquire(kActorMcCoy, kClueSpinnerKeys, true, kActorCrazylegs);
		}
		// Made it so Crystal only shows up if either your companion is a replicant or you haven't proven your innocence or both.
		// If neither of these conditions are fulfilled Crystal won't show up at all. After all if neither you and companion are replicants or at least suspected
		// of being replicants then Crystal has no reason to come after you.
		// First set of code is for when Dektora is with you.
		// Your companion is a replicant and McCoys innocence hasn't been proven Steele shows up.
		if (_vm->_cutContent) {
			if (getCompanionActor() == kActorDektora) {
				if (Game_Flag_Query(kFlagDektoraIsReplicant)
				|| !Game_Flag_Query(kFlagMcCoyIsInnocent)) {
					if (Actor_Query_Friendliness_To_Other(kActorCrazylegs, kActorMcCoy) > 49) {
						Actor_Says(kActorCrazylegs, 90, 15); //09-0090.AUD	You want me to tell your friend where you’re going?
						Actor_Says(kActorMcCoy, 1735, 17); //00-1735.AUD	Friend?
						Actor_Says(kActorCrazylegs, 100, 16); //09-0100.AUD	You know. The doll with the cigarette.
						Actor_Says(kActorCrazylegs, 110, kAnimationModeTalk); //09-0110.AUD	She told me you were in trouble and she wanted to help. What should I tell her?
						Actor_Face_Actor(affectionTowardsActor, kActorMcCoy, true);
						Actor_Says(kActorDektora, 90, kAnimationModeTalk);
						Actor_Says(kActorMcCoy, 1740, 14);    // You tell her we're headed South.
						Actor_Says(kActorCrazylegs, 120, 12); // Ten Four.
						Actor_Set_Goal_Number(kActorCrazylegs, kGoalCrazyLegsLeavesShowroom);
					} else {
						if (Player_Query_Agenda() == kPlayerAgendaSurly 
						|| Player_Query_Agenda() == kPlayerAgendaErratic) {
							Actor_Says(kActorCrazylegs, 460, 3); //09-0460.AUD	Unfortunately, I got a stigma about weapons.
							Actor_Says(kActorCrazylegs, 470, 3);
							Actor_Set_Goal_Number(kActorCrazylegs, kGoalCrazyLegsLeavesShowroom);
						} else {
							Actor_Says(kActorCrazylegs, 1000, 16); //09-1000.AUD	I got customers on the line, so I ain’t got time to chit chat.
							Actor_Set_Goal_Number(kActorCrazylegs, kGoalCrazyLegsLeavesShowroom);
						}
					}
					// Dektora is only afraid is he is a human.
					Actor_Face_Actor(affectionTowardsActor, kActorMcCoy, true);
					Actor_Face_Actor(kActorMcCoy, affectionTowardsActor, true);
					if (!Game_Flag_Query(kFlagDektoraIsReplicant)) {
						Actor_Says(kActorDektora, 100, kAnimationModeTalk); //03-0100.AUD	I’m afraid, Ray.
					}
					Actor_Says(kActorMcCoy, 1745, kAnimationModeTalk);
					Actor_Says(kActorDektora, 200, 12); //03-0200.AUD	I love you, Ray. Remember that.
					Actor_Change_Animation_Mode(kActorMcCoy, 23);
					Delay(2000);
					Actor_Says(kActorDektora, 110, 12); //03-0110.AUD	Please, we don’t have time for this. Let’s just take the Spinner and go!
					Async_Actor_Walk_To_XYZ(affectionTowardsActor, 309.0f, 40.63f, 402.0f, 0, false);
					Loop_Actor_Walk_To_XYZ(kActorMcCoy, 277.0f, 40.63f, 410.0f, 0, false, false, false);
					Set_Enter(kSetHF06, kSceneHF06);
					// If McCoy is found to be innocent and his companion is human, Steele doesn't show up and this happens instead.
				} else {
					if (Actor_Query_Friendliness_To_Other(kActorCrazylegs, kActorMcCoy) < 50) {
						if (Player_Query_Agenda() == kPlayerAgendaSurly 
						|| Player_Query_Agenda() == kPlayerAgendaErratic) {
							Actor_Says(kActorCrazylegs, 460, 3); //09-0460.AUD	Unfortunately, I got a stigma about weapons.
							Actor_Says(kActorCrazylegs, 470, 3);
							Actor_Set_Goal_Number(kActorCrazylegs, kGoalCrazyLegsLeavesShowroom);
						} else {
							Actor_Says(kActorCrazylegs, 1000, 16); //09-1000.AUD	I got customers on the line, so I ain’t got time to chit chat.
							Actor_Set_Goal_Number(kActorCrazylegs, kGoalCrazyLegsLeavesShowroom);
						}
					}
					Actor_Set_Goal_Number(kActorCrazylegs, kGoalCrazyLegsLeavesShowroom);
					Actor_Face_Actor(kActorMcCoy, affectionTowardsActor, true);
					Actor_Face_Actor(affectionTowardsActor, kActorMcCoy, true);
					Actor_Says(kActorMcCoy, 2115, kAnimationModeTalk); //00-2115.AUD	Let’s go. There’s nothing here for us anymore.
					Async_Actor_Walk_To_XYZ(affectionTowardsActor, 309.0f, 40.63f, 402.0f, 0, false);
					Loop_Actor_Walk_To_XYZ(kActorMcCoy, 277.0f, 40.63f, 410.0f, 0, false, false, false);
					Set_Enter(kSetHF06, kSceneHF06);
				}
				// This is the code for when Lucy is with you.
			} else if (getCompanionActor() == kActorLucy) { 
				if (Game_Flag_Query(kFlagLucyIsReplicant)
				|| !Game_Flag_Query(kFlagMcCoyIsInnocent)) {
					if (Actor_Query_Friendliness_To_Other(kActorCrazylegs, kActorMcCoy) > 49) {
						Actor_Says(kActorCrazylegs, 90, 15); //09-0090.AUD	You want me to tell your friend where you’re going?
						Actor_Says(kActorMcCoy, 1735, 17); //00-1735.AUD	Friend?
						Actor_Says(kActorCrazylegs, 100, 16); //09-0100.AUD	You know. The doll with the cigarette.
						Actor_Says(kActorCrazylegs, 110, kAnimationModeTalk); //09-0110.AUD	She told me you were in trouble and she wanted to help. What should I tell her?
						Actor_Face_Actor(affectionTowardsActor, kActorMcCoy, true);
						Actor_Says(kActorDektora, 90, kAnimationModeTalk);
						Actor_Says(kActorMcCoy, 1740, 14);    // You tell her we're headed South.
						Actor_Says(kActorCrazylegs, 120, 12); // Ten Four.
						Actor_Set_Goal_Number(kActorCrazylegs, kGoalCrazyLegsLeavesShowroom);
					} else {
						if (Player_Query_Agenda() == kPlayerAgendaSurly 
						|| Player_Query_Agenda() == kPlayerAgendaErratic) {
							Actor_Says(kActorCrazylegs, 460, 3); //09-0460.AUD	Unfortunately, I got a stigma about weapons.
							Actor_Says(kActorCrazylegs, 470, 3);
							Actor_Set_Goal_Number(kActorCrazylegs, kGoalCrazyLegsLeavesShowroom);
						} else {
							Actor_Says(kActorCrazylegs, 1000, 16); //09-1000.AUD	I got customers on the line, so I ain’t got time to chit chat.
							Actor_Set_Goal_Number(kActorCrazylegs, kGoalCrazyLegsLeavesShowroom);
						}
					}
					Actor_Face_Actor(kActorMcCoy, affectionTowardsActor, true);
					Actor_Face_Actor(affectionTowardsActor, kActorMcCoy, true);
					Actor_Says(kActorLucy, 390, kAnimationModeTalk);
					Actor_Says(kActorMcCoy, 1745, kAnimationModeTalk);
					Actor_Says(kActorLucy, 480, kAnimationModeTalk); //06-0480.AUD	I love you, Ray. Remember that.
					Async_Actor_Walk_To_XYZ(affectionTowardsActor, 309.0f, 40.63f, 402.0f, 0, false);
					Loop_Actor_Walk_To_XYZ(kActorMcCoy, 277.0f, 40.63f, 410.0f, 0, false, false, false);
					Set_Enter(kSetHF06, kSceneHF06);
				} else {
					if (Player_Query_Agenda() == kPlayerAgendaSurly 
					|| Player_Query_Agenda() == kPlayerAgendaErratic) {
						Actor_Says(kActorCrazylegs, 460, 3); //09-0460.AUD	Unfortunately, I got a stigma about weapons.
						Actor_Says(kActorCrazylegs, 470, 3);
						Actor_Set_Goal_Number(kActorCrazylegs, kGoalCrazyLegsLeavesShowroom);
					} else {
						Actor_Says(kActorCrazylegs, 1000, 16); //09-1000.AUD	I got customers on the line, so I ain’t got time to chit chat.
						Actor_Set_Goal_Number(kActorCrazylegs, kGoalCrazyLegsLeavesShowroom);
					}
					Actor_Set_Goal_Number(kActorCrazylegs, kGoalCrazyLegsLeavesShowroom);
					Actor_Face_Actor(kActorMcCoy, affectionTowardsActor, true);
					Actor_Face_Actor(affectionTowardsActor, kActorMcCoy, true);
					Actor_Says(kActorMcCoy, 2115, kAnimationModeTalk); //00-2115.AUD	Let’s go. There’s nothing here for us anymore.
					Async_Actor_Walk_To_XYZ(affectionTowardsActor, 309.0f, 40.63f, 402.0f, 0, false);
					Loop_Actor_Walk_To_XYZ(kActorMcCoy, 277.0f, 40.63f, 410.0f, 0, false, false, false);
					Set_Enter(kSetHF06, kSceneHF06);
				}
			}
				// This section is the default code that plays in the vanilla game.
		} else {
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
				Actor_Says(kActorDektora, 100, kAnimationModeTalk); //03-0100.AUD	I’m afraid, Ray.
			} else {
				Actor_Says(kActorLucy, 390, kAnimationModeTalk);
			}
			Actor_Face_Actor(kActorMcCoy, affectionTowardsActor, true);
			Actor_Says(kActorMcCoy, 1745, kAnimationModeTalk);
			Async_Actor_Walk_To_XYZ(affectionTowardsActor, 309.0f, 40.63f, 402.0f, 0, false);
			Loop_Actor_Walk_To_XYZ(kActorMcCoy, 277.0f, 40.63f, 410.0f, 0, false, false, false);
			Set_Enter(kSetHF06, kSceneHF06);
		}
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
	if (_vm->_cutContent) {
		Actor_Face_Object(kActorMcCoy, "MONTE CARLO DRY", true);
		Delay(2000);
		Actor_Says(kActorMcCoy, 8695, 13); //00-8695.AUD	That's an unusual design.
		Delay(1000);
	}
	Actor_Says(kActorCrazylegs, 170, kAnimationModeTalk); //09-0170.AUD	Admiring that Bishy Caddy, ain’t ya?
	Actor_Says(kActorCrazylegs, 180, 12); //09-0180.AUD	I don’t blame you. It’s a classic ride in a deluxe sport package.
	Actor_Says(kActorCrazylegs, 190, 14); //09-0190.AUD	It will push 125 without so much as a shake.
	Actor_Says(kActorCrazylegs, 200, 15);
	Actor_Says(kActorMcCoy, 1815, 12); //00-1815.AUD	That’s always the problem.
	Actor_Says(kActorCrazylegs, 210, 16); //09-0210.AUD	Crazylegs Larry Hirsch. Pleased to meet ya.
	if (_vm->_cutContent) {
		Actor_Says(kActorMcCoy, 4870, 23);
		if (Game_Flag_Query(kFlagCrazylegsIsReplicant)) {
			Delay(1000);
			Actor_Says(kActorMcCoy, 8920, 14); //00-8920.AUD	I gotta ask you a question.
			Actor_Says(kActorCrazylegs, 1000, 12); //09-1000.AUD	I got customers on the line, so I ain’t got time to chit chat.
			Actor_Says(kActorMcCoy, 400, 14); //00-0400.AUD	It won't take too long.
			Delay(2000);
			Actor_Says(kActorMcCoy, 8930, 14);
			Actor_Says(kActorCrazylegs, 1120, 15); //09-1120.AUD	I don’t know what you’re talking about.
			Delay(1000);
			Actor_Says(kActorMcCoy, 1535, 19); //00-1535.AUD	Ah, never mind.
		} else {
			Actor_Says(kActorCrazylegs, 220, kAnimationModeTalk);
			Actor_Says(kActorCrazylegs, 230, 12);
			Actor_Says(kActorCrazylegs, 240, 14);
			Actor_Says(kActorMcCoy, 1825, kAnimationModeIdle); //00-1825.AUD	Okay.
			Actor_Says(kActorCrazylegs, 250, 15);
			Actor_Face_Object(kActorCrazylegs, "MONTE CARLO DRY", true);
			Actor_Says(kActorCrazylegs, 260, 16);
			Actor_Face_Object(kActorMcCoy, "MONTE CARLO DRY", true);
			Actor_Says(kActorMcCoy, 1830, kAnimationModeIdle); //00-1830.AUD	Looks like a piece of work.
			Actor_Face_Actor(kActorCrazylegs, kActorMcCoy, true);
			Actor_Face_Actor(kActorMcCoy, kActorCrazylegs, true);
			Actor_Says(kActorCrazylegs, 270, kAnimationModeTalk); //09-0270.AUD	Forget those Fibro Plast Filipino heaps everyone is driving around.
			Actor_Says(kActorCrazylegs, 280, 12); //09-0280.AUD	This is real. Just feast your eyes on this.
			Async_Actor_Walk_To_XYZ(kActorCrazylegs, 276.0f, 40.63f, 182.0f, 12, false);
			Loop_Actor_Walk_To_XYZ(kActorMcCoy, 335.0f, 40.63f, 131.0f, 12, false, false, false);
			Actor_Face_Object(kActorCrazylegs, "MONTE CARLO DRY", true);
			Actor_Face_Object(kActorMcCoy, "MONTE CARLO DRY", true);
			Actor_Says(kActorCrazylegs, 290, 14); //09-0290.AUD	Ya see it? Ya see it, that’s actual chrome, the real stuff.
			Actor_Says(kActorCrazylegs, 300, 15); //09-0300.AUD	They saved a couple of hundred sheets of Tijuana Chrome from before the war.
			Actor_Says(kActorCrazylegs, 310, 16); //09-0310.AUD	It’s completely legal and everything. Beautiful ain’t it?
			if (Player_Query_Agenda() == kPlayerAgendaSurly 
			|| Player_Query_Agenda() == kPlayerAgendaErratic) {
				Actor_Face_Actor(kActorCrazylegs, kActorMcCoy, true);
				Actor_Face_Actor(kActorMcCoy, kActorCrazylegs, true);
				Actor_Says(kActorMcCoy, 1875, kAnimationModeTalk); //00-1875.AUD	I wouldn’t drag that bucket of bolts if you paid me.
				Actor_Modify_Friendliness_To_Other(kActorCrazylegs, kActorMcCoy, -2);
				Delay(2000);
				Actor_Says(kActorMcCoy, 8920, 14); //00-8920.AUD	I gotta ask you a question.
				Actor_Says(kActorCrazylegs, 1000, 12); //09-1000.AUD	I got customers on the line, so I ain’t got time to chit chat.
				Actor_Says(kActorMcCoy, 7860, 14); //00-7860.AUD	Stay right where you are.
				Delay(1000);
				Actor_Says(kActorMcCoy, 4680, 11); // 00-4680.AUD	We're gonna have a little chat.
			} else if (Player_Query_Agenda() == kPlayerAgendaPolite) {
				Actor_Says(kActorMcCoy, 4190, 13); //00-4190.AUD	Nice set of wheels.
				Actor_Modify_Friendliness_To_Other(kActorCrazylegs, kActorMcCoy, 2);
				Actor_Face_Actor(kActorCrazylegs, kActorMcCoy, true);
				Actor_Face_Actor(kActorMcCoy, kActorCrazylegs, true);
				Actor_Says(kActorCrazylegs, 320, kAnimationModeTalk); //09-0320.AUD	And you probably won’t ever see it again unless you steal this puppy.
				Actor_Says(kActorCrazylegs, 330, 12); //09-0330.AUD	And, honestly… No, frankly, I gotta tell you it’s got your name written all over it: Ray McCovey.
				Actor_Says(kActorMcCoy, 1840, kAnimationModeTalk); //00-1840.AUD	McCoy.
				Actor_Says(kActorCrazylegs, 340, 14); //09-0340.AUD	Uh, give or take a couple of letters.
				Actor_Says(kActorMcCoy, 1845, 16); //00-1845.AUD	I’ll have to think about it.
				Actor_Says(kActorCrazylegs, 350, 15);
				Actor_Says(kActorCrazylegs, 360, 16);
			} else {
				Actor_Says(kActorMcCoy, 1835, 12); //00-1835.AUD	I don’t think I’ve ever seen it before.
				Actor_Face_Actor(kActorCrazylegs, kActorMcCoy, true);
				Actor_Says(kActorCrazylegs, 320, kAnimationModeTalk); //09-0320.AUD	And you probably won’t ever see it again unless you steal this puppy.
				Actor_Face_Actor(kActorMcCoy, kActorCrazylegs, true);
				Actor_Says(kActorCrazylegs, 330, 12); //09-0330.AUD	And, honestly… No, frankly, I gotta tell you it’s got your name written all over it: Ray McCovey.
				Actor_Says(kActorMcCoy, 1840, kAnimationModeTalk); //00-1840.AUD	McCoy.
				Actor_Says(kActorCrazylegs, 340, 14); //09-0340.AUD	Uh, give or take a couple of letters.
				Delay(1000);
				Actor_Says(kActorMcCoy, 4945, 16); //00-4945.AUD	I think I'll pass.
			}
		}
	} else {
		Actor_Says(kActorMcCoy, 1820, -1); //00-1820.AUD	Ray McCoy.
		Actor_Says(kActorCrazylegs, 220, kAnimationModeTalk);
		Actor_Says(kActorCrazylegs, 230, 12);
		Actor_Says(kActorCrazylegs, 240, 14);
		Actor_Says(kActorMcCoy, 1825, kAnimationModeIdle); //00-1825.AUD	Okay.
		Actor_Says(kActorCrazylegs, 250, 15);
		Actor_Face_Object(kActorCrazylegs, "MONTE CARLO DRY", true);
		Actor_Says(kActorCrazylegs, 260, 16);
		Actor_Face_Object(kActorMcCoy, "MONTE CARLO DRY", true);
		Actor_Says(kActorMcCoy, 1830, kAnimationModeIdle); //00-1830.AUD	Looks like a piece of work.
		Actor_Face_Actor(kActorCrazylegs, kActorMcCoy, true);
		Actor_Face_Actor(kActorMcCoy, kActorCrazylegs, true);
		Actor_Says(kActorCrazylegs, 270, kAnimationModeTalk); //09-0270.AUD	Forget those Fibro Plast Filipino heaps everyone is driving around.
		Actor_Says(kActorCrazylegs, 280, 12);
		Async_Actor_Walk_To_XYZ(kActorCrazylegs, 276.0f, 40.63f, 182.0f, 12, false);
		Loop_Actor_Walk_To_XYZ(kActorMcCoy, 335.0f, 40.63f, 131.0f, 12, false, false, false);
		Actor_Face_Object(kActorCrazylegs, "MONTE CARLO DRY", true);
		Actor_Face_Object(kActorMcCoy, "MONTE CARLO DRY", true);
		Actor_Says(kActorCrazylegs, 290, 14);
		Actor_Says(kActorCrazylegs, 300, 15);
		Actor_Says(kActorCrazylegs, 310, 16); //09-0310.AUD	It’s completely legal and everything. Beautiful ain’t it?
		Actor_Says(kActorMcCoy, 1835, 12);
		Actor_Face_Actor(kActorCrazylegs, kActorMcCoy, true);
		Actor_Says(kActorCrazylegs, 320, kAnimationModeTalk);
		Actor_Face_Actor(kActorMcCoy, kActorCrazylegs, true);
		Actor_Says(kActorCrazylegs, 330, 12);
		Actor_Says(kActorMcCoy, 1840, kAnimationModeTalk); //00-1840.AUD	McCoy.
		Actor_Says(kActorCrazylegs, 340, 14);
		Actor_Says(kActorMcCoy, 1845, kAnimationModeTalk); //00-1845.AUD	I’ll have to think about it.
		Actor_Says(kActorCrazylegs, 350, 15);
		Actor_Says(kActorCrazylegs, 360, 16);
	}
	Player_Gains_Control();
}

void SceneScriptHF05::addAmbientSounds() {
	if (_vm->_cutContent) {
		if (Game_Flag_Query(kFlagDektoraIsReplicant)
		|| !Game_Flag_Query(kFlagMcCoyIsInnocent)
		|| Game_Flag_Query(kFlagMcCoyRetiredHuman)
		|| Actor_Query_Friendliness_To_Other(kActorCrazylegs, kActorMcCoy) < 50) {
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
		} else if (Game_Flag_Query(kFlagLucyIsReplicant)
		|| !Game_Flag_Query(kFlagMcCoyIsInnocent)
		|| Game_Flag_Query(kFlagMcCoyRetiredHuman)
		|| Actor_Query_Friendliness_To_Other(kActorCrazylegs, kActorMcCoy) < 50) {
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
	} else {
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
