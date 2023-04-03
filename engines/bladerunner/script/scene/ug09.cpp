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

void SceneScriptUG09::InitializeScene() {
	if (Game_Flag_Query(kFlagCT12ToUG09)) {
		Setup_Scene_Information(-67.0f, 156.94f, -425.0f,  500);
		Game_Flag_Reset(kFlagCT12ToUG09);
	} else {
		Setup_Scene_Information(-53.0f, 156.94f,  174.0f, 1000);
	}

	Scene_Exit_Add_2D_Exit(0, 204, 159, 392, 360, 0);
	Scene_Exit_Add_2D_Exit(1,   0, 455, 639, 479, 2);

	Ambient_Sounds_Add_Looping_Sound(kSfxCTRUNOFF, 71, 0, 1);
	Ambient_Sounds_Add_Looping_Sound(kSfxBOILPOT2, 45, 0, 1);
	Ambient_Sounds_Add_Looping_Sound(kSfxUGBED1,   76, 0, 1);
	Ambient_Sounds_Add_Sound(kSfxBBDRIP1,  2,  20, 25, 33, -100, 100, -100,  100, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBBDRIP2,  2,  20, 25, 33, -100, 100, -100,  100, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBBDRIP4,  2,  20, 25, 33, -100, 100, -100,  100, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxYELL1M2,  2, 120, 11, 12, -100, 100, -100,  100, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxYELL1M3,  2, 120, 11, 12, -100, 100, -100,  100, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxGRUNT1M1, 2, 120, 11, 12, -100, 100, -100,  100, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxGRUNT2M2, 2, 120, 11, 12, -100, 100, -100,  100, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxGRUNT2M3, 2, 120, 11, 12, -100, 100, -100,  100, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBBDRIP5,  2,  20, 25, 33, -100, 100, -100,  100, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBBGRN1,   5,  50, 47, 57, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBBGRN2,   5,  50, 47, 57, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBBGRN3,   5,  50, 47, 57, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSTEAM1,   5,  50, 47, 57, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSTEAM3,   5,  50, 17, 37, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSTEAM6A,  5,  50, 17, 37, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBBMOVE2,  5,  50, 27, 37, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBBMOVE3,  5,  50, 27, 37, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxZUBWLK3,  5,  50, 27, 37, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxZUBWLK4,  5,  50, 27, 37, -100, 100, -101, -101, 0, 0);
}

void SceneScriptUG09::SceneLoaded() {
	Obstacle_Object("FACADE_CANOPY", true);
	Obstacle_Object("VW PROP SLAB", true);
	Obstacle_Object("WALL_LEFT FRONT", true);
	Unobstacle_Object("PATH_FRAGMENT 1", true);
	Unobstacle_Object("BOXS FOR ARCHWAY 02", true);
	Unobstacle_Object("BOXS FOR ARCHWAY 04", true);
	Unobstacle_Object("BOXS FOR ARCHWAY 05", true);
	Unobstacle_Object("BOX45", true);
	Unobstacle_Object("BOX44", true);
	Unobstacle_Object("BOX43", true);
	Unobstacle_Object("BOX42", true);
	Unobstacle_Object("BOX41", true);
	Unobstacle_Object("BOX40", true);
	Unobstacle_Object("BOX39", true);
	Unobstacle_Object("BOX38", true);
	Unobstacle_Object("BOX37", true);
	Unobstacle_Object("BOX36", true);
	Unobstacle_Object("BOX35", true);
	Unobstacle_Object("BOX34", true);
	Unobstacle_Object("BOX32", true);
	Clickable_Object("FACADE_CANOPY");
#if BLADERUNNER_ORIGINAL_BUGS
#else
	Unclickable_Object("FACADE_CANOPY");
#endif // BLADERUNNER_ORIGINAL_BUGS
}

bool SceneScriptUG09::MouseClick(int x, int y) {
	return false;
}

bool SceneScriptUG09::ClickedOn3DObject(const char *objectName, bool a2) {
	return false;
}

bool SceneScriptUG09::ClickedOnActor(int actorId) {
	return false;
}

bool SceneScriptUG09::ClickedOnItem(int itemId, bool a2) {
	return false;
}

bool SceneScriptUG09::ClickedOnExit(int exitId) {
	if (exitId == 0) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -67.0f, 156.94f, -425.0f, 0, true, false, false)) {
			Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
			Ambient_Sounds_Remove_All_Looping_Sounds(1u);
			Game_Flag_Set(kFlagUG09toCT12);
			Set_Enter(kSetCT01_CT12, kSceneCT12);
		}
		return true;
	}

	if (exitId == 1) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -53.0f, 156.94f, 206.0f, 0, true, false, false)) {
			Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
			Ambient_Sounds_Remove_All_Looping_Sounds(1u);
			Game_Flag_Set(kFlagUG09ToUG07);
			Set_Enter(kSetUG07, kSceneUG07);
		}
		return true;
	}
	return false;
}

bool SceneScriptUG09::ClickedOn2DRegion(int region) {
	return false;
}

void SceneScriptUG09::SceneFrameAdvanced(int frame) {
	//return false;
}

void SceneScriptUG09::ActorChangedGoal(int actorId, int newGoal, int oldGoal, bool currentSet) {
}

void SceneScriptUG09::PlayerWalkedIn() {
	if (Global_Variable_Query(kVariableChapter) == 4
	 && Game_Flag_Query(kFlagUG07Empty)
	) {
		Game_Flag_Set(kFlagMutantsPaused);
	}
	// Restored scene when you talk to Izo in the sewers in act 4.
	if (!Game_Flag_Query(kFlagIzoTalkAct4)
	&& Game_Flag_Query(kFlagIzoFled)
	&& !Game_Flag_Query(kFlagIzoArrested)
	&& !Game_Flag_Query(kFlagMcCoyShotIzo)
	&& !Actor_Clue_Query(kActorMcCoy, kClueCrystalRetiredIzo)) {
		Actor_Put_In_Set(kActorIzo, kSetUG09);
		Actor_Set_At_XYZ(kActorIzo, -81.17, 157.41, 71.37, 0);
		Actor_Face_Actor(kActorMcCoy, kActorIzo, true);
		Actor_Says(kActorMcCoy, 3970, 14); //00-3970.AUD	Hey.
		Actor_Face_Actor(kActorIzo, kActorMcCoy, true);
		// If you didn't help Izo with Crystal by convinvcing her that he isn't smuggling weapons and warning him in act 3 outside his shop this happens.
		if (Actor_Clue_Query(kActorMcCoy, kClueWeaponsCache)
		&& !Game_Flag_Query(kFlagIzoWarned)) {
			Actor_Says(kActorMcCoy, 6710, 16); //00-6710.AUD	How’s business these days, Izo?
			if (!Game_Flag_Query(kFlagGuzzaIsStupid)) {
				Actor_Says(kActorIzo, 850, 12); //07-0850.AUD	Non existent. You and Steele made sure of that. Scavengers took the rest.
				Actor_Says(kActorMcCoy, 6740, 16); //00-6740.AUD	What exactly did the scavengers take?
				Actor_Says(kActorIzo, 970, 17); //07-0970.AUD	Some of the police-issue weapons and electronics. They took them down into the sewers.
				Actor_Says(kActorMcCoy, 7835, 16); //00-7835.AUD	Is that so?
				Actor_Clue_Acquire(kActorMcCoy, kCluePoliceIssueWeapons, true, kActorIzo);
			} else {
				Delay(2000);
				Actor_Says(kActorMcCoy, 8395, 18); //00-8395.AUD	You don't have anything to say?
			}
		} else {
			Actor_Says(kActorMcCoy, 6745, 18); //00-6745.AUD	Izo, we gotta talk.
		}
		Delay(1000);
		//Made it so Izo only shares what he knows with McCoy in regards to who framed him if McCoy helped Izo in covering up his weapon smuggling operation.
		if (!Actor_Clue_Query(kActorMcCoy, kClueGuzzaFramedMcCoy)) {
			Actor_Says(kActorMcCoy, 6735, 15); //00-6735.AUD	Who is trying to nail me, Izo?
			Actor_Says(kActorIzo, 920, 13); //07-0920.AUD	I probably have a good idea.
			if (Player_Query_Agenda() == kPlayerAgendaSurly 
			|| Player_Query_Agenda() == kPlayerAgendaErratic) {
				Actor_Says(kActorMcCoy, 8445, 14); //00-8445.AUD	Cough it up!
			} else {
				Actor_Says(kActorMcCoy, 6760, 18); //00-6760.AUD	Feel like sharing?
			}
			if (!Game_Flag_Query(kFlagIzoWarned)) {
				if (!Game_Flag_Query(kFlagIzoIsReplicant)) {		
					Actor_Says(kActorIzo, 930, 14); //07-0930.AUD	My life wouldn’t be worth one chinyen, if I did.
					Actor_Says(kActorMcCoy, 6765, 13); //00-6765.AUD	You’re talking about Clovis. 
					Actor_Says(kActorIzo, 940, 17); //07-0940.AUD	One man? Nobody can act alone.
					Actor_Says(kActorMcCoy, 6770, 18); //00-6770.AUD	You mean conspiracy?
				} else {
					Delay(2000);
					Actor_Says(kActorMcCoy, 8590, 18); //00-8590.AUD	Not the talkative type
					Delay(1000);
				}
			} else {
				Actor_Says(kActorIzo, 950, 16); //07-0950.AUD	Think, McCoy. Which human has the most power over one’s activities on a daily basis?
				Actor_Says(kActorMcCoy, 6775, 15); //00-6775.AUD	I don’t know. Why don’t you tell me?
				Actor_Says(kActorIzo, 960, 15); //07-0960.AUD	I’m sorry to say you and I are on the same boat. Beholden to the same person.
				if (Player_Query_Agenda() != kPlayerAgendaPolite) {
					Actor_Says(kActorMcCoy, 3910, 16); //00-3910.AUD	You’re lying.
				} else {
					Actor_Says(kActorMcCoy, 6780, 18); //00-6780.AUD	Don’t jump to any conclusions.
				}
			}
		}
		if (Actor_Query_Friendliness_To_Other(kActorClovis, kActorMcCoy) < 51
		|| Game_Flag_Query(kFlagMcCoyRetiredReplicant)) {
			if (Game_Flag_Query(kFlagIzoWarned)) {
				Actor_Says(kActorIzo, 750, 13); //07-0750.AUD	Clovis is looking for you, McCoy.
				Actor_Says(kActorMcCoy, 6755, 13); //00-6755.AUD	He wants to talk to me?!
				Actor_Says(kActorIzo, 910, 12); //07-0910.AUD	He would have made that clear.
				Actor_Clue_Acquire(kActorMcCoy, kClueIzosWarning, true, kActorIzo);
				if (Actor_Clue_Query(kActorClovis, kClueMcCoyRetiredZuben)) {
					Actor_Says(kActorIzo, 760, 14); //07-0760.AUD	He knows all about you. Knows what happened with Zuben.
				}
				if (!Actor_Clue_Query(kActorMcCoy, kCluePlasticExplosive)
				&& !Actor_Clue_Query(kActorMcCoy, kClueDetonatorWire)) {
					Actor_Says(kActorMcCoy, 5500, 18); //00-5500.AUD	Is Clovis the Tyrell bomber?
					Actor_Says(kActorIzo, 770, 12); //07-0770.AUD	You really are groping in the dark.
					Actor_Says(kActorIzo, 780, 17); //07-0780.AUD	No. The bomb belonged to Sadik. It was his signature.
				}
			}
		}
		Delay(1000);
		Actor_Says(kActorMcCoy, 5505, 13); //00-5505.AUD	I need to talk to Clovis.
		if (Player_Query_Agenda() != kPlayerAgendaSurly 
		&& Player_Query_Agenda() != kPlayerAgendaErratic) {	
			Actor_Says(kActorMcCoy, 6730, 15); //00-6730.AUD	I’ll do you a good turn, if you hook me up with Clovis.
			if (!Game_Flag_Query(kFlagIzoIsReplicant)) {
				Actor_Says(kActorIzo, 880, 14); //07-0880.AUD	Good turns are meaningless to me, if I go against Clovis’ wishes.
				Actor_Says(kActorMcCoy, 6750, 18); //00-6750.AUD	You’re afraid of him?
				Actor_Says(kActorIzo, 890, 13); //07-0890.AUD	People must prove themselves to me before I make any judgments
				Actor_Says(kActorIzo, 900, 15); //07-0900.AUD	Clovis has done that. A thousand times over. He’s not to be taken lightly.
			}
		}	
		if (Game_Flag_Query(kFlagIzoWarned)) {
			Actor_Says(kActorIzo, 790, 16); //07-0790.AUD	I’ll tell him you helped me. That’s as much as I can do.
		} else {
			if (!Game_Flag_Query(kFlagIzoIsReplicant)) {
				Actor_Says(kActorIzo, 870, 17); //07-0870.AUD	I’ve been warned not to waste any more words with you.
			} else {
				Actor_Says(kActorIzo, 550, 15);
			}
		}
		Delay(1000);
		if (Player_Query_Agenda() != kPlayerAgendaPolite) {
			Actor_Says(kActorMcCoy, 5470, 15); //00-5470.AUD	Get lost, Izo. Take off.
		}
		Loop_Actor_Walk_To_XYZ(kActorIzo, -109.20, 152.67, -676.67, 48, false, true, false);
		Actor_Put_In_Set(kActorIzo, kSetCT11);
		Game_Flag_Set(kFlagIzoTalkAct4);
	}
}

void SceneScriptUG09::PlayerWalkedOut() {
	if (Global_Variable_Query(kVariableChapter) == 4) {
		Game_Flag_Reset(kFlagMutantsPaused);
	}

	if (Game_Flag_Query(kFlagUG09toCT12)) {
		Game_Flag_Set(kFlagMcCoyInChinaTown);
		Game_Flag_Reset(kFlagMcCoyInUnderground);
	}
}

void SceneScriptUG09::DialogueQueueFlushed(int a1) {
}

} // End of namespace BladeRunner
