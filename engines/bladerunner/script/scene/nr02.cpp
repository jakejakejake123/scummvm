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

void SceneScriptNR02::InitializeScene() {
	playNextMusic();
	Setup_Scene_Information(-283.0f, -24.0f, 326.0f, 200);
	Game_Flag_Reset(kFlagNR01toNR02);

	Scene_Exit_Add_2D_Exit(0, 0, 105, 75, 291, 3);

	Ambient_Sounds_Add_Looping_Sound(kSfxBARAMB1, 50, 38, 0);
	Ambient_Sounds_Add_Sound(kSfxBARSFX1,  3, 60, 25, 25, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBARSFX3,  3, 60, 25, 25, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBARSFX4,  3, 60, 25, 25, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBARSFX5,  3, 60, 25, 25, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBARSFX6,  3, 60, 25, 25, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBARSFX7,  3, 60, 25, 25, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxCLINK1,   3, 60, 25, 25, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxCLINK2,   3, 60, 25, 25, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxCLINK3,   3, 60, 25, 25, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxCLINK4,   3, 60, 25, 25, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0480R, 5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0540R, 5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0560R, 5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0870R, 5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0900R, 5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0940R, 5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_1070R, 5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_1080R, 5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_1160R, 5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
}

void SceneScriptNR02::SceneLoaded() {
	Obstacle_Object("VID PHONE 01", true);
	Unobstacle_Object("VICTORIAN CHAIR", true);
	Unobstacle_Object("WALL CANDLES", true);
	Unobstacle_Object("STAIRS", true);
	Unobstacle_Object("BOX30", true);
	Unobstacle_Object("VID CAM COVER", true);
	Unobstacle_Object("VID CAM COVER01", true);
	Unobstacle_Object("VID OUTER GLASS", true);
	Unobstacle_Object("VID OUTER GLASS01", true);
	Unobstacle_Object("VID MAIN MONITOR", true);
	Unobstacle_Object("VID MAIN MONITOR01", true);
	Clickable_Object("VID PHONE 01");
	Clickable_Object("VID PHONE 02");
}

bool SceneScriptNR02::MouseClick(int x, int y) {
	return false;
}

bool SceneScriptNR02::ClickedOn3DObject(const char *objectName, bool a2) {
	if (Object_Query_Click("VID PHONE 01", objectName)
	 || Object_Query_Click("VID PHONE 02", objectName)
	) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -191.9f, -24.0f, 62.15f, 0, true, false, false)) {
			Actor_Face_Heading(kActorMcCoy, 13, false);
			if ( Actor_Clue_Query(kActorMcCoy, kClueFolder)
			 &&  Actor_Clue_Query(kActorMcCoy, kClueGuzzaFramedMcCoy)
			 && !Game_Flag_Query(kFlagCallWithGuzza)
			) {
				Actor_Set_Goal_Number(kActorMcCoy, kGoalMcCoyCallWithGuzza);
				Game_Flag_Set(kFlagCallWithGuzza);
			} else {
				Sound_Play(kSfxSPNBEEP9, 50, 0, 0, 50);
				Delay(1000);
				Sound_Play(kSfxVIDFONE1, 30, 0, 0, 50);
				Delay(1500);
				Sound_Play(kSfxVIDFONE1, 30, 0, 0, 50);
				Delay(1500);
				Sound_Play(kSfxVIDFONE1, 30, 0, 0, 50);
				Delay(1500);
				Sound_Play(kSfxSPNBEEP9, 50, 0, 0, 50);
				Delay(1000);
				Actor_Says(kActorMcCoy, 170, 14);
			}
		}
	}
	return false;
}

bool SceneScriptNR02::ClickedOnActor(int actorId) {
	if (actorId == kActorGordo
	 && Actor_Query_Goal_Number(kActorGordo) == kGoalGordoNR02WaitAtBar
	) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, 67.37f, -24.0f, 389.32f, 0, true, false, false)) {
			Actor_Set_Goal_Number(kActorGordo, kGoalGordoNR02TalkToMcCoy);
		}
	}
	return false;
}

bool SceneScriptNR02::ClickedOnItem(int itemId, bool a2) {
	if (itemId == kItemGordosLighterReplicant
	 || itemId == kItemGordosLighterHuman
	) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, 109.38f, -24.0f, 420.5f, 0, true, false, false)) {
			Actor_Face_Heading(kActorMcCoy, 423, false);
			if (_vm->_cutContent) {
				if (Actor_Clue_Query(kActorMcCoy, kClueStolenCheese)  
				|| Actor_Clue_Query(kActorMcCoy, kClueGordoInterview3)) {
					if (itemId == kItemGordosLighterReplicant) {
						Actor_Change_Animation_Mode(kActorMcCoy, 23);
						Delay(800);
						Item_Remove_From_World(kItemGordosLighterReplicant);
						Item_Pickup_Spin_Effect(kModelAnimationGordosLighterReplicant, 214, 380);
						Delay(800);
						Actor_Clue_Acquire(kActorMcCoy, kClueGordosLighterReplicant, true, kActorGordo);
						Actor_Says(kActorMcCoy, 8850, 13); //00-8850.AUD	A lighter.
					} else if (itemId == kItemGordosLighterHuman) {
						Actor_Change_Animation_Mode(kActorMcCoy, 23);
						Delay(800);
						Item_Remove_From_World(kItemGordosLighterHuman);
						Item_Pickup_Spin_Effect(kModelAnimationGordosLighterHuman, 214, 380);
						Delay(800);
						Actor_Clue_Acquire(kActorMcCoy, kClueGordosLighterHuman, true, kActorGordo);
						Actor_Says(kActorMcCoy, 8850, 13); //00-8850.AUD	A lighter.
					}
				} else {
					Actor_Says(kActorMcCoy, 8525, 13); // 00-8525.AUD	Hmph.
				}
			} else {
				if (itemId == kItemGordosLighterReplicant) {					
					Item_Remove_From_World(kItemGordosLighterReplicant);
					Item_Pickup_Spin_Effect(kModelAnimationGordosLighterReplicant, 214, 380);
					Actor_Clue_Acquire(kActorMcCoy, kClueGordosLighterReplicant, true, -1);
				}
				if (itemId == kItemGordosLighterHuman) {
					Item_Remove_From_World(kItemGordosLighterHuman);
					Item_Pickup_Spin_Effect(kModelAnimationGordosLighterHuman, 214, 380);
					Actor_Clue_Acquire(kActorMcCoy, kClueGordosLighterHuman, true, -1);
				}
			}
		}
	}
	return false;
}

bool SceneScriptNR02::ClickedOnExit(int exitId) {
	if (exitId == 0) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -283.0f, -24.0f, 326.0f, 0, true, false, false)) {
			if (Actor_Query_Goal_Number(kActorGordo) < kGoalGordoNR01WaitAndAttack
			 || Actor_Query_Goal_Number(kActorGordo) > kGoalGordoNR01WaitAndTakeHostage
			) {
				Music_Stop(2u);
			}
			Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
			Ambient_Sounds_Remove_All_Looping_Sounds(1u);
			Game_Flag_Set(kFlagNR02toNR01);
			Set_Enter(kSetNR01, kSceneNR01);
		}
		return true;
	}
	return false;
}

bool SceneScriptNR02::ClickedOn2DRegion(int region) {
	return false;
}

void SceneScriptNR02::SceneFrameAdvanced(int frame) {
	// Gordo not running away
	if (!Music_Is_Playing()
	 && (Actor_Query_Goal_Number(kActorGordo) < kGoalGordoNR02TalkAboutMcCoy
	  || Actor_Query_Goal_Number(kActorGordo) > kGoalGordoNR02RunAway3
	 )
	) {
		playNextMusic();
	}
	//return false;
}

void SceneScriptNR02::ActorChangedGoal(int actorId, int newGoal, int oldGoal, bool currentSet) {
}

void SceneScriptNR02::PlayerWalkedIn() {
	if (Actor_Query_Goal_Number(kActorGordo) == kGoalGordoNR02WaitAtPodium) {
		Actor_Set_Goal_Number(kActorGordo, kGoalGordoNR02RunAway1);
	}

	if (Actor_Query_Goal_Number(kActorGordo) == kGoalGordoNR02WaitForMcCoy) {
		Actor_Set_Goal_Number(kActorGordo, kGoalGordoNR02NextAct);
	}

	if (Actor_Query_Goal_Number(kActorGordo) == kGoalGordoNR02TellJoke1) {
		Actor_Set_Goal_Number(kActorGordo, kGoalGordoNR02NextAct);
	}
	if (_vm->_cutContent) {
		if (Global_Variable_Query(kVariableAffectionTowards) == kAffectionTowardsDektora) {
			Actor_Set_At_XYZ(kActorMcCoy, -203.0f, -24.0f, 334.0f, 0);
		}
	} else {
		Loop_Actor_Walk_To_XYZ(kActorMcCoy, -203.0f, -24.0f, 334.0f, 0, false, false, false);
	}
	Loop_Actor_Walk_To_XYZ(kActorMcCoy, -203.0f, -24.0f, 334.0f, 0, false, false, false);
	//return false;
	// Code for an encounter you can have with Dektora at Taffys in act 4 if Dektora is alive and you have global affection towards her.
	if (_vm->_cutContent) {
		if (Global_Variable_Query(kVariableChapter) == 4) {
			if (Global_Variable_Query(kVariableAffectionTowards) == kAffectionTowardsDektora) {
				if (!Game_Flag_Query(kFlagDektoraTalkAct4)
				&& !Actor_Clue_Query(kActorDektora, kClueMcCoyRetiredZuben)
				&& !Actor_Clue_Query(kActorDektora, kClueMcCoyRetiredLucy)
				&& !Actor_Clue_Query(kActorDektora, kClueMcCoyRetiredGordo)
				&& Actor_Clue_Query(kActorMcCoy, kClueFolder)
				&& Actor_Clue_Query(kActorMcCoy, kClueGuzzaFramedMcCoy)) {
					Actor_Put_In_Set(kActorDektora, kSetNR02);
					Actor_Set_At_XYZ(kActorDektora, -141.56, -23.67, 356.49, 0);
					Actor_Face_Actor(kActorMcCoy, kActorDektora, true);
					Actor_Face_Actor(kActorDektora, kActorMcCoy, true);
					Delay(1000);
					if (Player_Query_Agenda() != kPlayerAgendaPolite) {
						Actor_Says(kActorMcCoy, 6425, 14); //00-6425.AUD	You shouldn’t be here!
						Actor_Says(kActorDektora, 1280, 12); //03-1280.AUD	I had to see you.
						Actor_Says(kActorMcCoy, 6430, 13); //00-6430.AUD	If they find you with me—
						Actor_Says(kActorDektora, 1290, 13); //03-1290.AUD	I know, I’m in danger too.
					} else {
						Actor_Says(kActorMcCoy, 7960, 13); //00-7960.AUD	Dektora?
						Delay(1000);
						Actor_Says(kActorMcCoy, 6185, 19); //00-6185.AUD	(sighs) You got any idea how glad I am to see ya?
						Actor_Says(kActorDektora, 1280, 12); //03-1280.AUD	I had to see you.	
					}
					Music_Stop(1u);
					Delay(1000);
					Music_Play(kMusicLoveSong, 35, 0, 3, -1, kMusicLoopPlayOnce, 1);
					if (Game_Flag_Query(kFlagDektoraIsReplicant)) {
						Actor_Says(kActorDektora, 1330, 11); //03-1330.AUD	The police know I’ve been helping Clovis. They probably think I’m a Replicant.
						if (!Actor_Clue_Query(kActorMcCoy, kClueVKDektoraReplicant)) {
							Actor_Says(kActorMcCoy, 6440, 13); //00-6440.AUD	But you’re not.
							Delay(2000);
							Actor_Says(kActorMcCoy, 6865, 14); //00-6865.AUD	You're a Replicant.
							Actor_Says(kActorDektora, 1480, -1); //03-1480.AUD	Yes.
						} else {
							Actor_Says(kActorMcCoy, 4180, 13); //00-4180.AUD	You sure?
						}
						Actor_Says(kActorDektora, 1300, 12); //03-1300.AUD	The police know what I am.
						Actor_Says(kActorMcCoy, 6435, 14); //00-6435.AUD	Legally, it can’t be proved unless they put you on the Machine
						if (Actor_Query_Intelligence(kActorDektora) == 90) {
							Actor_Says(kActorDektora, 1310, 13); //03-1310.AUD	Crystal Steele won’t bother with formalities.
							Actor_Says(kActorDektora, 1320, 14); //03-1320.AUD	And they’ve found my incept photo or my records, it won’t matter anyway
						} else if (Actor_Query_Intelligence(kActorDektora) == 70) {
							Delay(1000);
							Actor_Says(kActorDektora, 1980, 14); //03-1980.AUD	All right.
							Delay(1000);
						}
					} else {
						if (!Actor_Clue_Query(kActorMcCoy, kClueVKDektoraReplicant)) {
							Delay(1000);
							Actor_Says(kActorMcCoy, 6865, 14); //00-6865.AUD	You're a Replicant.					
							Actor_Says(kActorDektora, 1340, 14); //03-1340.AUD	Of course not. I didn’t come down on the moonbus with him.
							Actor_Says(kActorDektora, 1350, 12); //03-1350.AUD	And I remember growing up back East. My mother, my father.
							Actor_Says(kActorDektora, 1360, 13); //03-1360.AUD	I had a spotted pony. She would take carrots right out of my mouth!
							Actor_Says(kActorMcCoy, 6445, 11); //00-6445.AUD	Memories can be implanted.
							Actor_Says(kActorDektora, 1370, 12); //03-1370.AUD	Not mine. Mine are real!
							Actor_Says(kActorDektora, 1380, 13); //03-1380.AUD	God damn Tyrell!
						} else {
							Delay(1000);
							Actor_Says(kActorMcCoy, 2310, kAnimationModeTalk); //00-2310.AUD	I understand.
							Delay(1000);
						}
					}		
					Actor_Says(kActorMcCoy, 6535, 11); //00-6535.AUD	I need to see Clovis ASAP.
					Actor_Says(kActorDektora, 1410, 12); //03-1410.AUD	You must be patient. He’ll find you, when he’s ready
					Actor_Says(kActorDektora, 1130, 13); //03-1130.AUD	He is very jealous. You don’t understand
					if (Actor_Query_Friendliness_To_Other(kActorClovis, kActorMcCoy) < 51) {
						Actor_Says(kActorMcCoy, 6365, 13); //00-6365.AUD	Jealous, huh? On top of everything else?
					}
					Actor_Says(kActorDektora, 1140, 13); //03-1140.AUD	He is a very complicated man. He wants so much. Things he just can’t have.
					if (Actor_Query_Friendliness_To_Other(kActorClovis, kActorMcCoy) < 51) { 
						Actor_Says(kActorMcCoy, 6370, 12); //00-6370.AUD	Then he’s no different from anybody else.
						Actor_Says(kActorDektora, 1150, 15); //03-1150.AUD	God forbid you ever have to find out how different he is.
						Actor_Says(kActorDektora, 1160, 13); //03-1160.AUD	How dangerous he can be. And if he thinks that you and I… It can only bring trouble.
						if (!Game_Flag_Query(kFlagDektoraIsReplicant)) {
							Actor_Says(kActorMcCoy, 8510, 11); //00-8510.AUD	You got a real thing for machines, don't ya?
							Delay(2000);
						}
					}				
					Actor_Says(kActorDektora, 1170, 13); //03-1170.AUD	We’re both running then.
					Actor_Says(kActorMcCoy, 6375, 13); //00-6375.AUD	Are we?
					Actor_Says(kActorDektora, 1180, 14); //03-1180.AUD	From Clovis.
					Actor_Says(kActorMcCoy, 6380, 12); //00-6380.AUD	Clovis is pretty low priority right now. I’ve been framed and I got the rest of the LPD trying to find me.
					Actor_Says(kActorDektora, 1190, 13); //03-1190.AUD	Blade Runners?		
					Actor_Says(kActorMcCoy, 6390, 16); //00-6390.AUD	They think I’m a Replicant.
					if (Game_Flag_Query(kFlagDektoraIsReplicant)) {
						Actor_Says(kActorDektora, 1200, 13); //03-1200.AUD	Do they now?
						if (Player_Query_Agenda() != kPlayerAgendaPolite) { 
							Actor_Says(kActorMcCoy, 6395, 13); //00-6395.AUD	Glad I amuse you.
						}
					} else {
						Actor_Says(kActorDektora, 1210, 13); //03-1210.AUD	I’m sorry. It’s just…
					}
					Actor_Says(kActorDektora, 1220, 13); //03-1220.AUD	Their thinking it doesn’t make you one. It’s what you feel that’s important.
					if (!Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
						Actor_Says(kActorMcCoy, 6400, 11); //00-6400.AUD	I’m a human being.
					} else {
						Delay(1000);
					}
					Actor_Says(kActorDektora, 1230, 13); //03-1230.AUD	But do you ever have doubts?
					Actor_Says(kActorDektora, 1240, 16); //03-1240.AUD	Do you ever wonder if your memories actually belong to you?
					Delay(1500);
					Actor_Says(kActorMcCoy, 6405, 13); //00-6405.AUD	I dream about a place. More mine than anywhere else. Full of sun and light. And warmth.
					Actor_Says(kActorDektora, 1250, 13); //03-1250.AUD	I’ve seen that place. I’ve dreamed about it too.
					Delay(1000);
					Actor_Says(kActorMcCoy, 6410, 13); //00-6410.AUD	Maybe all Reps--
					if (!Game_Flag_Query(kFlagDektoraIsReplicant)) {
						Actor_Says(kActorDektora, 1260, 13); //03-1260.AUD	Don’t say it!
						Delay(2000);
					} else {
						Actor_Says(kActorDektora, 1270, 13); //03-1270.AUD	When you see yourself there, are you alone?
						Actor_Says(kActorMcCoy, 6415, 11); //00-6415.AUD	Sometimes.
						Delay(2000);
					}
					Actor_Says(kActorMcCoy, 6450, 13); //00-6450.AUD	It’s too dangerous for you around here. You gotta hide. Go underground.
					Actor_Says(kActorMcCoy, 6455, 11); //00-6455.AUD	In the meantime, I’ve gotta see Clovis.
					Actor_Says(kActorDektora, 1100, 13); //03-1100.AUD	Okay. Ray.
					Loop_Actor_Walk_To_XYZ(kActorDektora, -300.18, -23.44, 44.75, 48, true, false, false);
					Music_Stop(1u);
					Game_Flag_Set(kFlagDektoraTalkAct4);
					Loop_Actor_Walk_To_XYZ(kActorMcCoy, -191.9f, -24.0f, 62.15f, 0, true, false, false);
					Actor_Face_Heading(kActorMcCoy, 13, false);
					Actor_Set_Goal_Number(kActorMcCoy, kGoalMcCoyCallWithGuzza);
					Game_Flag_Set(kFlagCallWithGuzza);
				}
			}
		}
	}
}

void SceneScriptNR02::PlayerWalkedOut() {
	Music_Stop(2u);

	// Gordo on the podium
	if (Actor_Query_Goal_Number(kActorGordo) < kGoalGordoNR02TalkAboutMcCoy
	 && Actor_Query_Goal_Number(kActorGordo) >= kGoalGordoNR02NextAct
	) {
		Actor_Set_Goal_Number(kActorGordo, kGoalGordoNR02WaitForMcCoy);
	}
}

void SceneScriptNR02::DialogueQueueFlushed(int a1) {
	if (Player_Query_Current_Scene() == kSceneNR02
	 && Actor_Query_Goal_Number(kActorGordo) == kGoalGordoNR02TellJoke1
	) {
		Sound_Play(kSfxRIMSHOT1, 50, 0, 0, 50);
		Sound_Play(kSfxAUDLAFF3, 50, 0, 0, 50);
	}

	if (Player_Query_Current_Scene() == kSceneNR02
	 && Actor_Query_Goal_Number(kActorGordo) == kGoalGordoNR02TellJoke2
	) {
		Sound_Play(kSfxRIMSHOT2, 50, 0, 0, 50);
		Sound_Play(kSfxAUDLAFF5, 50, 0, 0, 50);
	}

	if (Player_Query_Current_Scene() == kSceneNR02
	 && Actor_Query_Goal_Number(kActorGordo) == kGoalGordoNR02TellJoke3
	) {
		Sound_Play(kSfxRIMSHOT5, 50, 0, 0, 50);
		Sound_Play(kSfxAUDLAFF6, 50, 0, 0, 50);
	}

	// Gordo on the podium
	if (Player_Query_Current_Scene() == kSceneNR02
	 && Actor_Query_Goal_Number(kActorGordo) > kGoalGordoNR02NextAct
	 && Actor_Query_Goal_Number(kActorGordo) < kGoalGordoNR02TalkAboutMcCoy
	) {
		Actor_Set_Goal_Number(kActorGordo, kGoalGordoNR02NextAct);
		return; // true;
	}

	// Gordo on the podium, but McCoy is outside
	if (Actor_Query_Goal_Number(kActorGordo) > kGoalGordoNR02NextAct
	 && Actor_Query_Goal_Number(kActorGordo) < kGoalGordoNR02TalkAboutMcCoy
	) {
		Actor_Set_Goal_Number(kActorGordo, kGoalGordoNR02WaitForMcCoy);
		return; // true;
	}
	//return false;
}

void SceneScriptNR02::playNextMusic() {
	int track = Global_Variable_Query(kVariableTaffyLewisMusic);
	int loop = kMusicLoopPlayOnce;
	if (_vm->_cutContent && Random_Query(0, 2) == 1) {
		loop = kMusicLoopPlayOnceRandomStart;
	}
	if (track == 0) {
		Music_Play(kMusicTaffy2, 41, 0, 2, -1, loop, 0);
	} else if (track == 1) {
		Music_Play(kMusicTaffy3, 41, 0, 2, -1, loop, 0);
	} else if (track == 2) {
		Music_Play(kMusicTaffy4, 41, 0, 2, -1, loop, 0);
	}
	++track;
	if (track > 2) {
		track = 0;
	}
	Global_Variable_Set(kVariableTaffyLewisMusic, track);
}

} // End of namespace BladeRunner
