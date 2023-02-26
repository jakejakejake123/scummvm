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

void SceneScriptTB05::InitializeScene() {
	if (Game_Flag_Query(kFlagTB06toTB05)) {
		Setup_Scene_Information(23.0f, 151.53f, -205.0f, 450);
		Game_Flag_Set(kFlagTB06Visited);
		Game_Flag_Reset(kFlagTB06toTB05);
	} else {
		Setup_Scene_Information(14.0f, 151.53f, -77.0f, 6);
	}
	Scene_Exit_Add_2D_Exit(0, 62, 193, 206, 419, 0);
	Scene_Exit_Add_2D_Exit(1,  0, 455, 639, 479, 2);
	if (_vm->_cutContent
	    && Game_Flag_Query(kFlagTB05MonitorIntro)
	    && !Game_Flag_Query(kFlagMcCoyCommentsOnTB05Monitors)) {
		// in order not to confuse the player (much) with a red herring region,
		// we enable this region *after* the player has accessed the correct pc / panel
		Scene_2D_Region_Add(0, 382, 255, 634, 325); // monitors and panels other than the "main monitor"
	}
	Ambient_Sounds_Add_Looping_Sound(kSfxTB5LOOP1, 100, 0, 1);
	Ambient_Sounds_Add_Looping_Sound(kSfxTB5LOOP2, 100, 0, 1);
	Ambient_Sounds_Add_Sound(kSfxHUMMER1,  5, 30, 25, 33, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxHUMMER2,  5, 30, 25, 33, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxHUMMER3,  5, 30, 25, 33, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxHUMMER4,  5, 30, 25, 33, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxLABMISC1, 2, 30, 20, 25,    0,   0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxLABMISC2, 2, 30, 20, 25,    0,   0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxLABMISC3, 2, 30, 20, 25,    0,   0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxLABMISC4, 2, 30, 20, 25,    0,   0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxLABMISC6, 2, 30, 20, 25,    0,   0, -101, -101, 0, 0);
	Scene_Loop_Set_Default(0);
}

void SceneScriptTB05::SceneLoaded() {
	Clickable_Object("MONITOR05");
	Unclickable_Object("SMUDGE_GLASS01");
	if (_vm->_cutContent) {
		if (!Actor_Clue_Query(kActorMcCoy, kClueDragonflyEarring)) {
			if (!Game_Flag_Query(kFlagSadikIsReplicant)) {
				Item_Add_To_World(kItemDragonflyEarring, kModelAnimationDragonflyEarring, kSetTB05, 76.16f, 147.36f, -235.15f, 0, 6, 6, false, true, false, true);
			}
		} 
	} else {
		if (!Actor_Clue_Query(kActorMcCoy, kClueDragonflyEarring)) {
			Item_Add_To_World(kItemDragonflyEarring, kModelAnimationDragonflyEarring, kSetTB05, 76.16f, 147.36f, -235.15f, 0, 6, 6, false, true, false, true);
		} 
	}
	if (!Actor_Clue_Query(kActorMcCoy, kClueTyrellSalesPamphletEntertainModel)
	 && !Actor_Clue_Query(kActorMcCoy, kClueTyrellSalesPamphletLolita)
	 && (Game_Flag_Query(kFlagGordoIsReplicant)
	  || Game_Flag_Query(kFlagLucyIsReplicant)
	 )
	) {
		if (_vm->_cutContent) {
			if (!Game_Flag_Query(kFlagSadikIsReplicant)) {
				Item_Add_To_World(kItemTyrellSalesPamphlet, kModelAnimationTyrellSalesPamphlet, kSetTB05, 129.01f, 147.12f, -162.98f, 0, 8, 8, false, true, false, true);
			}
		} else {
			Item_Add_To_World(kItemTyrellSalesPamphlet, kModelAnimationTyrellSalesPamphlet, kSetTB05, 129.01f, 147.12f, -162.98f, 0, 8, 8, false, true, false, true);
		}
	}
}

bool SceneScriptTB05::MouseClick(int x, int y) {
	return false;
}

bool SceneScriptTB05::ClickedOn3DObject(const char *objectName, bool a2) {
	if (Object_Query_Click("MONITOR05", objectName)) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, 122.54f, 147.12f, -197.17f, 0, true, false, false)) {
			Actor_Face_Heading(kActorMcCoy, 38, false);
			if (!Actor_Clue_Query(kActorMcCoy, kClueDNAMarcus)
			 && !Game_Flag_Query(kFlagTB05MonitorIntro)) {
				Actor_Clue_Acquire(kActorMcCoy, kClueAttemptedFileAccess, true, -1);
				Actor_Voice_Over(2170, kActorVoiceOver);
				Actor_Voice_Over(2180, kActorVoiceOver);
				Actor_Voice_Over(2190, kActorVoiceOver);
				Actor_Voice_Over(2200, kActorVoiceOver);
				Game_Flag_Set(kFlagTB05MonitorIntro);
				// Made it McCoy only makes his distasteful comment about the 'wallpapered engineer' if he has seen Eisendullers body and if he is surly or erratic.
				if (_vm->_cutContent && Game_Flag_Query(kFlagTB05toTB06)) {
					// in order not to confuse the player (much) with a red herring region,
					// we enable this region *after* the player has accessed the correct pc / panel
					Scene_2D_Region_Add(0, 382, 255, 634, 325); // monitors and panels other than the "main monitor"
				}
				return true;
			}

			if ( Game_Flag_Query(kFlagTB05MonitorIntro)
			 && !Game_Flag_Query(kFlagTB05MonitorUnlockAttempt)
			 && !Actor_Clue_Query(kActorMcCoy, kClueDNAMarcus)
			) {
				if (Actor_Clue_Query(kActorMcCoy, kClueDogCollar1)
				 || Actor_Clue_Query(kActorMcCoy, kClueDogCollar2)
				) {
					if (_vm->_cutContent) {
						if (Game_Flag_Query(kFlagSadikIsReplicant)) {
							Actor_Change_Animation_Mode(kActorMcCoy, 23);
							Delay(2000);
							Sound_Play(kSfxELEBAD1, 100, 0, 0, 50);
							Delay(1000);
							Actor_Voice_Over(2270, kActorVoiceOver); //99-2270.AUD	I couldn't even begin to guess what Eisenduller's password was.
							Delay(1000);
							Actor_Says(kActorMcCoy, 8525, -1); // 00-8525.AUD	Hmph.
							Actor_Change_Animation_Mode(kActorMcCoy, 23);
							Delay(800);
							Actor_Voice_Over(4160, kActorVoiceOver); //99-4160.AUD	The dog collar has a name on it. "Rikki" maybe?
							Actor_Change_Animation_Mode(kActorMcCoy, 23);
							Delay(2000);
							Actor_Says(kActorMcCoy, 8522, 14); // Locked
							Actor_Voice_Over(2290, kActorVoiceOver); //99-2290.AUD	Tyrell security was even better than I'd heard.
							Game_Flag_Set(kFlagTB05MonitorUnlockAttempt);
							Game_Flag_Set(kFlagTB05MonitorDone);
						} else {
							Actor_Change_Animation_Mode(kActorMcCoy, 23);
							Delay(2000);
							Sound_Play(kSfxELEBAD1, 100, 0, 0, 50);
							Delay(1000);
							Actor_Voice_Over(2270, kActorVoiceOver); //99-2270.AUD	I couldn't even begin to guess what Eisenduller's password was.
							Delay(1000);
							Actor_Says(kActorMcCoy, 8525, 13); // 00-8525.AUD	Hmph.
							Actor_Change_Animation_Mode(kActorMcCoy, 23);
							Delay(800);
							Actor_Voice_Over(4160, kActorVoiceOver); //99-4160.AUD	The dog collar has a name on it. "Rikki" maybe?
							Actor_Change_Animation_Mode(kActorMcCoy, 23);
							Delay(2000);
							Ambient_Sounds_Play_Sound(kSfxBEEPNEAT, 80, 0, 0, 99);
							Delay(1000);
							Actor_Voice_Over(2230, kActorVoiceOver);
							Actor_Change_Animation_Mode(kActorMcCoy, 23);
							Delay(800);
							Item_Pickup_Spin_Effect(kModelAnimationDNADataDisc, 352, 333);
							Actor_Clue_Acquire(kActorMcCoy, kClueDNAMarcus, true, kActorMarcus);
							if (Player_Query_Agenda() != kPlayerAgendaSurly 
							&& Player_Query_Agenda() != kPlayerAgendaErratic) {
								Actor_Voice_Over(2240, kActorVoiceOver);
								Actor_Voice_Over(2250, kActorVoiceOver);
								Actor_Voice_Over(2260, kActorVoiceOver);
							} else {
								Actor_Voice_Over(130, kActorVoiceOver); //99-0130.AUD	DNA research, incept dates.
								Actor_Voice_Over(140, kActorVoiceOver); //99-0140.AUD	A lot of jargon but I bet my spinner it was valuable to somebody.
							}
							Game_Flag_Set(kFlagTB05MonitorUnlockAttempt);
							Game_Flag_Set(kFlagTB05MonitorDone);
						}
					} else {
						Actor_Clue_Acquire(kActorMcCoy, kClueDNAMarcus, true, -1);
						Actor_Voice_Over(2230, kActorVoiceOver); //99-2230.AUD	Eisenduller had used his dog's name as a password.
						Item_Pickup_Spin_Effect(kModelAnimationDNADataDisc, 352, 333);
						Actor_Voice_Over(2240, kActorVoiceOver);
						Actor_Voice_Over(2250, kActorVoiceOver);
						Actor_Voice_Over(2260, kActorVoiceOver);
						Game_Flag_Set(kFlagTB05MonitorUnlockAttempt);
						Game_Flag_Set(kFlagTB05MonitorDone);
					}
				} else {
					if (_vm->_cutContent) {
						Actor_Change_Animation_Mode(kActorMcCoy, 23);
						Delay(2000);
						Sound_Play(kSfxELEBAD1, 100, 0, 0, 50);
						Delay(1000);
					}
					Actor_Voice_Over(2270, kActorVoiceOver);
					Game_Flag_Set(kFlagTB05MonitorUnlockAttempt);
				}
				return true;
			}

			if ( Game_Flag_Query(kFlagTB05MonitorUnlockAttempt)
			 && !Game_Flag_Query(kFlagTB05MonitorDone)
			) {
				if (Actor_Clue_Query(kActorMcCoy, kClueDogCollar1)
				 || Actor_Clue_Query(kActorMcCoy, kClueDogCollar2)
				) {
					if (_vm->_cutContent) {
						if (Game_Flag_Query(kFlagSadikIsReplicant)) {
							Actor_Voice_Over(3700, kActorVoiceOver);
							Game_Flag_Set(kFlagTB05MonitorDone);
						} else {
							Actor_Says(kActorMcCoy, 8525, -1); // 00-8525.AUD	Hmph.
							Actor_Change_Animation_Mode(kActorMcCoy, 23);
							Delay(800);
							Actor_Voice_Over(4160, kActorVoiceOver); //99-4160.AUD	The dog collar has a name on it. "Rikki" maybe?
							Actor_Change_Animation_Mode(kActorMcCoy, 23);
							Delay(2000);
							Ambient_Sounds_Play_Sound(kSfxBEEPNEAT, 80, 0, 0, 99);
							Delay(1000);
							Actor_Voice_Over(2230, kActorVoiceOver);
							Actor_Change_Animation_Mode(kActorMcCoy, 23);
							Delay(800);
							Item_Pickup_Spin_Effect(kModelAnimationDNADataDisc, 352, 333);
							Actor_Clue_Acquire(kActorMcCoy, kClueDNAMarcus, true, kActorMarcus);
							if (Player_Query_Agenda() != kPlayerAgendaSurly 
							&& Player_Query_Agenda() != kPlayerAgendaErratic) {
								Actor_Voice_Over(2240, kActorVoiceOver);
								Actor_Voice_Over(2250, kActorVoiceOver);
								Actor_Voice_Over(2260, kActorVoiceOver);
							} else {
								Actor_Voice_Over(130, kActorVoiceOver); //99-0130.AUD	DNA research, incept dates.
								Actor_Voice_Over(140, kActorVoiceOver); //99-0140.AUD	A lot of jargon but I bet my spinner it was valuable to somebody.
							}
							Game_Flag_Set(kFlagTB05MonitorDone);
						}
					} else {
						Actor_Clue_Acquire(kActorMcCoy, kClueDNAMarcus, true, -1);
						Actor_Voice_Over(2230, kActorVoiceOver); //99-2230.AUD	Eisenduller had used his dog's name as a password.
						Item_Pickup_Spin_Effect(kModelAnimationDNADataDisc, 352, 333);
						Actor_Voice_Over(2240, kActorVoiceOver);
						Actor_Voice_Over(2250, kActorVoiceOver);
						Actor_Voice_Over(2260, kActorVoiceOver);
						Game_Flag_Set(kFlagTB05MonitorDone);
					}
				} else {
					if (_vm->_cutContent) {
						Actor_Change_Animation_Mode(kActorMcCoy, 23);
						Delay(2000);
						Sound_Play(kSfxELEBAD1, 100, 0, 0, 50);
						Delay(1000);
					}
					Actor_Voice_Over(2280, kActorVoiceOver);
					Actor_Voice_Over(2290, kActorVoiceOver);
					Game_Flag_Set(kFlagTB05MonitorDone);
				}
				return true;
			}

			if (Game_Flag_Query(kFlagTB05MonitorDone)) {
				Actor_Voice_Over(3700, kActorVoiceOver);
				return true;
			}
		}
	}
	return false;
}

bool SceneScriptTB05::ClickedOnActor(int actorId) {
	return false;
}

bool SceneScriptTB05::ClickedOnItem(int itemId, bool a2) {
	if (itemId == kItemDragonflyEarring) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, 54.0f, 147.12f, -209.0f, 0, true, false, false)) {
			Actor_Face_Heading(kActorMcCoy, 126, false);
			Item_Remove_From_World(kItemDragonflyEarring);
			Item_Pickup_Spin_Effect(kModelAnimationDragonflyEarring, 295, 408);
			if (_vm->_cutContent) {				
				Actor_Says(kActorMcCoy, 8765, -1); //00-8765.AUD	An earring.
				if (!Actor_Clue_Query(kActorMcCoy, kCluePeruvianLadyInterview)) {
					Delay(1000);
					Actor_Says(kActorMcCoy, 4050, 13);
				}
			} else { 			
				Actor_Voice_Over(2140, kActorVoiceOver);
				Actor_Voice_Over(2150, kActorVoiceOver);
				Actor_Voice_Over(2160, kActorVoiceOver);
			}
			Actor_Clue_Acquire(kActorMcCoy, kClueDragonflyEarring, true, -1);
			return true;
		}
	}

	if (itemId == kItemTyrellSalesPamphlet) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, 107.89f, 147.12f, -156.26f, 0, true, false, false)) {
			Actor_Face_Heading(kActorMcCoy, 126, false);
			Item_Remove_From_World(kItemTyrellSalesPamphlet);
			Item_Pickup_Spin_Effect(kModelAnimationTyrellSalesPamphlet, 449, 431);
			if (_vm->_cutContent) {
				Actor_Says(kActorMcCoy, 8780, 13); //00-8780.AUD	A sales pamphlet.
			}
			Actor_Voice_Over(4280, kActorVoiceOver);
			if (Game_Flag_Query(kFlagGordoIsReplicant)) {
				Actor_Voice_Over(4290, kActorVoiceOver);
				Actor_Clue_Acquire(kActorMcCoy, kClueTyrellSalesPamphletEntertainModel, true, -1);
			} else {
				Actor_Voice_Over(4300, kActorVoiceOver);
				Actor_Clue_Acquire(kActorMcCoy, kClueTyrellSalesPamphletLolita, true, -1);
			}
		}
	}
	return false;
}

bool SceneScriptTB05::ClickedOnExit(int exitId) {
	if (exitId == 0) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, 23.0f, 151.53f, -205.0f, 12, true, false, false)) {
			// Added in some dialogue for when McCoy first enters the grav lab. The smell of charred flesh and burnt walls is still quite pungent.
			if (_vm->_cutContent) {
				Actor_Face_Heading(kActorMcCoy, 10, false);
				if (!Game_Flag_Query(kFlagTB05toTB06)) {
					Actor_Says(kActorMcCoy, 8650, kAnimationModeTalk); //00-8650.AUD	What smells in there?
					Actor_Says(kActorMcCoy, 8660, kAnimationModeTalk);  //00-8660.AUD	I think something's burning.
				}
			}
			Game_Flag_Set(kFlagTB05toTB06);
			Set_Enter(kSetTB06, kSceneTB06);
			//Reset this flag so the buzzer doesn't go off when you exit the grav lab.
			if (_vm->_cutContent) {
				Game_Flag_Reset(kFlagTB02toTB05);
			}
			Scene_Loop_Start_Special(kSceneLoopModeChangeSet, 2, true);
		}
		return true;
	}
	if (exitId == 1) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, 14.0f, 147.12f, 123.0f, 0, true, false, false)) {
			Game_Flag_Set(kFlagTB05toTB02);
			Set_Enter(kSetTB02_TB03, kSceneTB02);
		}
		return true;
	}
	return false;
}

bool SceneScriptTB05::ClickedOn2DRegion(int region) {
	if (_vm->_cutContent) {
		if (!Game_Flag_Query(kFlagMcCoyCommentsOnTB05Monitors) && region == 0) {
			Game_Flag_Set(kFlagMcCoyCommentsOnTB05Monitors);
			Actor_Force_Stop_Walking(kActorMcCoy);
			Actor_Face_Heading(kActorMcCoy, 64, false);
			Actor_Voice_Over(2210, kActorVoiceOver);
			if (Player_Query_Agenda() == kPlayerAgendaSurly
			|| Player_Query_Agenda() == kPlayerAgendaErratic) {
				Actor_Voice_Over(2220, kActorVoiceOver);
			}
			Scene_2D_Region_Remove(0);
			return true;
		}
	}
	return false;
}

void SceneScriptTB05::SceneFrameAdvanced(int frame) {
	if (frame == 61) {
		Sound_Play(kSfxLABMISC5, Random_Query(52, 52), 0, 0, 50);
	}
	if (frame == 63) {
		Sound_Play(kSfxTBDOOR1,  Random_Query(55, 55), 0, 0, 50);
	}
	//return true;
}

void SceneScriptTB05::ActorChangedGoal(int actorId, int newGoal, int oldGoal, bool currentSet) {
}

void SceneScriptTB05::PlayerWalkedIn() {
	//Altered code so the buzzer sound plays when you enter the set.
	if (_vm->_cutContent) {
		if (Game_Flag_Query(kFlagTB02toTB05)) {
			Sound_Play(kSfxLABBUZZ1, 90, 0, 0, 50);
		}
	}
}

void SceneScriptTB05::PlayerWalkedOut() {
	Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
	Ambient_Sounds_Remove_All_Looping_Sounds(1u);
}

void SceneScriptTB05::DialogueQueueFlushed(int a1) {
}

} // End of namespace BladeRunner
