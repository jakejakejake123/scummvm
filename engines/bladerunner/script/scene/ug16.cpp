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

void SceneScriptUG16::InitializeScene() {
	if (Game_Flag_Query(kFlagDR06toUG16)) {
		Setup_Scene_Information(-270.76f, -34.88f, -504.02f, 404);
		Game_Flag_Reset(kFlagDR06toUG16);
	} else if (Game_Flag_Query(kFlagUG15toUG16a)) {
		Setup_Scene_Information(-322.0f,   -34.0f,  -404.0f, 345);
		Game_Flag_Reset(kFlagUG15toUG16a);
	} else {
		Setup_Scene_Information(-318.0f,   -34.0f,  -216.0f, 340);
	}

	Scene_Exit_Add_2D_Exit(0, 242, 169, 282, 262, 3);
	Scene_Exit_Add_2D_Exit(1, 375, 166, 407, 251, 3);
	Scene_Exit_Add_2D_Exit(2, 461, 148, 523, 248, 0);

	if (_vm->_cutContent) {
		if (Actor_Query_Goal_Number(kActorLuther) < kGoalLutherGone) {
			Ambient_Sounds_Add_Looping_Sound(kSfxELECLAB1, 33, 81, 0);
		}
	} else {
		Ambient_Sounds_Add_Looping_Sound(kSfxELECLAB1, 33, 81, 0);
	}
	Ambient_Sounds_Add_Looping_Sound(kSfxUGBED1,   40,  0, 1);
	Ambient_Sounds_Add_Looping_Sound(kSfxUGBED2,   40,  0, 1);

	if (Game_Flag_Query(kFlagUG16ComputerOff)) {
		Scene_Loop_Set_Default(5);
	} else {
		Scene_Loop_Set_Default(0);
	}
}

void SceneScriptUG16::SceneLoaded() {
	Obstacle_Object("BED", true);
	Obstacle_Object("QUADPATCH07", true);
	Obstacle_Object("QUADPATCH05", true);
	Obstacle_Object("SCREEN 01", true);
	Obstacle_Object("BOX49", true);
	Obstacle_Object("CYLINDER07", true);
	Unobstacle_Object("SEAT 1", true);
	Unobstacle_Object("SEAT 2", true);
	Unclickable_Object("BED");
	Unclickable_Object("QUADPATCH07");
	Clickable_Object("QUADPATCH05");
	Clickable_Object("SCREEN 01");
	Unclickable_Object("BOX49");
	Unclickable_Object("CYLINDER07");
	Unobstacle_Object("BOX67", true);
	Footstep_Sounds_Set(0, 3);
	Footstep_Sounds_Set(1, 2);
	Footstep_Sounds_Set(2, 3);
	Footstep_Sounds_Set(6, 3);
}

bool SceneScriptUG16::MouseClick(int x, int y) {
	return false;
}

bool SceneScriptUG16::ClickedOn3DObject(const char *objectName, bool a2) {
	if (Object_Query_Click("QUADPATCH05", objectName)) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, 194.0f, -35.0f, 160.8f, 0, true, false, false)) {
			Actor_Face_Heading(kActorMcCoy, 870, false);
			if (!Game_Flag_Query(kFlagUG16FolderFound)
			 &&  Game_Flag_Query(kFlagLutherLanceAreDead)
			) {
				Game_Flag_Set(kFlagUG16FolderFound);
				Delay(1000);
				// Altered the scene where McCoy finds the folder in Luther and Lances chest of drawers. He now describes the folder and also doesn't say 'what a
				// difference a day makes' and until realizes what he has found.
				if (_vm->_cutContent) {
					Actor_Change_Animation_Mode(kActorMcCoy, 38);
					Sound_Play(kSfxDRAWER1, 100, 0, 0, 50);
					Delay(4000);
					Item_Pickup_Spin_Effect(kModelAnimationFolder, 460, 287);
					Actor_Says(kActorMcCoy, 8870, 13); //00-8870.AUD	A folder with information about Guzza.
					Delay(1000);
					Actor_Voice_Over(3480, kActorVoiceOver);
				} else {
					Actor_Voice_Over(3480, kActorVoiceOver);
					Actor_Change_Animation_Mode(kActorMcCoy, 38);
					Sound_Play(kSfxDRAWER1, 100, 0, 0, 50);
					Delay(1000);
					Item_Pickup_Spin_Effect(kModelAnimationFolder, 460, 287);
				}
				Actor_Voice_Over(2740, kActorVoiceOver);
				Actor_Voice_Over(2750, kActorVoiceOver);
				Actor_Voice_Over(2760, kActorVoiceOver);
				Actor_Voice_Over(2770, kActorVoiceOver);
				// Added in an extra line.
				if (_vm->_cutContent) {
					if (!Actor_Clue_Query(kActorMcCoy, kClueGuzzaFramedMcCoy)) {
						Actor_Voice_Over(2820, kActorVoiceOver); //99-2820.AUD	Why did the Reps have this? Were they blackmailing Guzza? I knew I was getting close.
						Delay(1000);
					} else {
						Delay(1000);
						Actor_Voice_Over(3430, kActorVoiceOver); //99-3430.AUD	The info I’d gotten from Luther and Lance finally made some sense.
						Actor_Voice_Over(3440, kActorVoiceOver); //99-3440.AUD	The Reps must had found out about Guzza’s career's sidelines…
						Actor_Voice_Over(3450, kActorVoiceOver); //99-3450.AUD	and pressured him to set me up in order to get me off their backs.
						Actor_Voice_Over(3460, kActorVoiceOver); //99-3460.AUD	This nasty business he was only too willing to do.
						Actor_Voice_Over(3470, kActorVoiceOver); //99-3470.AUD	But I wasn’t gonna eat crow that easily.
						if (Player_Query_Agenda() == kPlayerAgendaSurly 
						|| Player_Query_Agenda() == kPlayerAgendaErratic) {
							Actor_Voice_Over(2780, kActorVoiceOver); //99-2780.AUD	When my stomach stopped churning, I realized I had everything I needed to force the bastard to play ball with me.
							Actor_Voice_Over(2800, kActorVoiceOver); //99-2800.AUD	I knew that he would listen to reason, if applied with serious pressure.
							Actor_Voice_Over(3500, kActorVoiceOver); //99-3500.AUD	All I had to do was place a call and make the worm squirm.	
						} else {
							Actor_Voice_Over(3490, kActorVoiceOver); //99-3490.AUD	It was time to have my own little fun with Guzza.
							Actor_Voice_Over(2810, kActorVoiceOver);	
						}
					}
				}
				if (_vm->_cutContent) {
					Actor_Clue_Acquire(kActorMcCoy, kClueFolder, true, kActorLuther);
				} else {
					Actor_Clue_Acquire(kActorMcCoy, kClueFolder, true, -1);
				}
			} else {
				Actor_Says(kActorMcCoy, 8523, 12);
				Actor_Says(kActorMcCoy, 8635, 12);
			}
			return true;
		}
	}

	if (Object_Query_Click("SCREEN 01", objectName)) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, 194.0f, -35.0f, 160.8f, 0, true, false, false)) {

			Actor_Face_Heading(kActorMcCoy, 870, false);

			if (_vm->_cutContent) {
				if (!Actor_Clue_Query(kActorMcCoy, kClueDNALutherLance)) {
					if (!Game_Flag_Query(kFlagLutherLanceIsReplicant)) {
						Actor_Face_Heading(kActorMcCoy, 1016, false);
						Delay(2000);
						Actor_Change_Animation_Mode(kActorMcCoy, 23);
						Delay(800);
						Item_Pickup_Spin_Effect(kModelAnimationDNADataDisc, 418, 305);
						Delay(800);
						Actor_Clue_Acquire(kActorMcCoy, kClueDNALutherLance, true, kActorLuther);
					} else {
						if (( Game_Flag_Query(kFlagLutherLanceAreDead)
						|| !Actor_Query_Is_In_Current_Set(kActorLuther))
						&& !Actor_Clue_Query(kActorMcCoy, kClueDNALutherLance)
						&& !Game_Flag_Query(kFlagUG16ComputerOff)) {
							Actor_Face_Heading(kActorMcCoy, 1016, false);
							Delay(2000);
							Actor_Says(kActorMcCoy, 5725, 14);
							Delay(1000);
							Actor_Change_Animation_Mode(kActorMcCoy, 23);
							Delay(800);
							Item_Pickup_Spin_Effect(kModelAnimationDNADataDisc, 418, 305);
							Delay(800);
							Actor_Clue_Acquire(kActorMcCoy, kClueDNALutherLance, true, kActorLuther);
						} else {
							Actor_Says(kActorMcCoy, 8522, 14); // Locked
						}
					}
				} else {
					Actor_Says(kActorMcCoy, 8525, 12);
					Actor_Says(kActorMcCoy, 8526, 12);
				}
			} else if (( Game_Flag_Query(kFlagLutherLanceAreDead)
			  || !Actor_Query_Is_In_Current_Set(kActorLuther)
			 )
			 && !Actor_Clue_Query(kActorMcCoy, kClueDNALutherLance)
			 && !Game_Flag_Query(kFlagUG16ComputerOff)
			) {
				Delay(2000);
				Actor_Face_Heading(kActorMcCoy, 1016, false);
				Delay(2000);
				Actor_Says(kActorMcCoy, 5725, 14);
				Delay(1000);
				Item_Pickup_Spin_Effect(kModelAnimationDNADataDisc, 418, 305);
				Actor_Clue_Acquire(kActorMcCoy, kClueDNALutherLance, true, -1);
				return true;
			}

			Actor_Says(kActorMcCoy, 8525, 12);
			Actor_Says(kActorMcCoy, 8526, 12);
		}
	}
	return false;
}

bool SceneScriptUG16::ClickedOnActor(int actorId) {
	if (Actor_Query_Goal_Number(kActorLuther) < 490) { // Luther & Lance are alive
		dialogueWithLuther();
		return true;
	}
	return false;
}

bool SceneScriptUG16::ClickedOnItem(int itemId, bool a2) {
	return false;
}

bool SceneScriptUG16::ClickedOnExit(int exitId) {
	if (exitId == 0) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -322.0f, -34.0f, -216.0f, 0, true, false, false)) {
			if (_vm->_cutContent) {
				if (!Game_Flag_Query(kFlagUG15BridgeBroken)) {
					Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
					Ambient_Sounds_Remove_All_Looping_Sounds(1u);
					Game_Flag_Set(kFlagUG16toUG15b);
					Set_Enter(kSetUG15, kSceneUG15);
				} else {
					Actor_Says(kActorMcCoy, 7815, 13); //00-7815.AUD	No.
				}
			} else {
				Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
				Ambient_Sounds_Remove_All_Looping_Sounds(1u);
				Game_Flag_Set(kFlagUG16toUG15b);
				Set_Enter(kSetUG15, kSceneUG15);
			}
		}
		return true;
	}

	if (exitId == 1) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -322.0f, -34.0f, -404.0f, 0, true, false, false)) {
			if (_vm->_cutContent) {
				if (!Game_Flag_Query(kFlagUG15BridgeBroken)) {
					Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
					Ambient_Sounds_Remove_All_Looping_Sounds(1u);
					Game_Flag_Set(kFlagUG16toUG15a);
					Set_Enter(kSetUG15, kSceneUG15);
				} else {
					Actor_Says(kActorMcCoy, 7815, 13); //00-7815.AUD	No.
				}
			} else {
				Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
				Ambient_Sounds_Remove_All_Looping_Sounds(1u);
				Game_Flag_Set(kFlagUG16toUG15a);
				Set_Enter(kSetUG15, kSceneUG15);
			}
		}
		return true;
	}

	if (exitId == 2) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -316.78f, -34.88f, -533.27f, 0, true, false, false)) {
			Actor_Face_Heading(kActorMcCoy, 0, false);
			Loop_Actor_Travel_Stairs(kActorMcCoy, 13, true, kAnimationModeIdle);
			Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
			Ambient_Sounds_Remove_All_Looping_Sounds(1u);
			Set_Enter(kSetDR06, kSceneDR06);
		}
		return true;
	}
	return false;
}

bool SceneScriptUG16::ClickedOn2DRegion(int region) {
	return false;
}

void SceneScriptUG16::SceneFrameAdvanced(int frame) {
	if (frame == 132) {
		Ambient_Sounds_Remove_Looping_Sound(kSfxELECLAB1, 1u);
	}
}

void SceneScriptUG16::ActorChangedGoal(int actorId, int newGoal, int oldGoal, bool currentSet) {
}

void SceneScriptUG16::PlayerWalkedIn() {
	// Made it so McCoys gun is holstrered when entering the twins lab so the conversation with them isn't cut off.
	if (_vm->_cutContent) {
		Player_Set_Combat_Mode(false);

	}
	Game_Flag_Set(kFlagDR06UnlockedToUG16);

	if (!Game_Flag_Query(kFlagLutherLanceAreDead)) {
		Actor_Set_Goal_Number(kActorLuther, kGoalLutherStop);
	}

	if (!Game_Flag_Query(kFlagUG16LutherLanceTalk1)
	 &&  Actor_Query_Is_In_Current_Set(kActorLuther)
	) {
		Player_Loses_Control();
		Loop_Actor_Walk_To_XYZ(kActorMcCoy, 120.29f, -35.67f, 214.8f, 310, false, false, false);
		Actor_Face_Actor(kActorMcCoy, kActorLuther, true);
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagLutherLanceIsReplicant)) {
				Actor_Says(kActorLuther, 0, 6);
				Actor_Says(kActorLuther, 30, 13);
			}
		} else {
			Actor_Says(kActorLuther, 0, 6);
			Actor_Says(kActorLuther, 30, 13);
		}
		Actor_Change_Animation_Mode(kActorLuther, 17);
		if (_vm->_cutContent) {
			Actor_Says(kActorMcCoy, 755, 18);
		}
		Actor_Says(kActorLance, 0, 17); //13-0000.AUD	Hey, it’s about time you showed up.
		Actor_Says(kActorMcCoy, 5710, 14);
		// Altered the dialogue between McCoy and Luther and Lance so if they are human they don't act like sarcastic jerks to him and they also don't want Tyrell dead despite
		// their anger towards him. If they are Replicants they treat McCoy badly and want Clovis to kill Tyrell/
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagLutherLanceIsReplicant)) {
				Actor_Says(kActorLance, 10, 13); //13-0010.AUD	Detective Ray McCoy.
			} else {
				Actor_Says(kActorLuther, 40, 13); //10-0040.AUD	Detective Ray McCoy.
			}
		} else {
			Actor_Says(kActorLuther, 40, 13); //10-0040.AUD	Detective Ray McCoy.
		}
		// Made it so Luther and Lance only mention Morajis death if Moraji died.
		if (_vm->_cutContent) {
			if (!Game_Flag_Query(kFlagMorajiAlive)) { 
				Actor_Says(kActorLuther, 50, 15); //10-0050.AUD	You’re investigating Moraji’s death.
				Actor_Says(kActorLance, 20, 12); //13-0020.AUD	And Eisenduller’s.
				if (Game_Flag_Query(kFlagLutherLanceIsReplicant)) {
					Actor_Says(kActorLuther, 60, 23); //10-0060.AUD	Having any luck?
				}
			}
		} else {
			Actor_Says(kActorLuther, 50, 15);
			Actor_Says(kActorLance, 20, 12);
			Actor_Says(kActorLuther, 60, 23);
		}
		Actor_Says(kActorMcCoy, 5715, 14); //00-5715.AUD	You’re Luther and Lance?
		if (_vm->_cutContent) {
			if (!Game_Flag_Query(kFlagLutherLanceIsReplicant)) {
				Actor_Says(kActorLuther, 320, 16); //10-0320.AUD	No question.
			} else {
				Actor_Says(kActorLance, 30, 16); //13-0030.AUD	Hell of a smart cookie there.
				Actor_Says(kActorLuther, 70, 6); //10-0070.AUD	Take your guns and your violence elsewhere. We’ve got important work to do.
			}
		} else {
			Actor_Says(kActorLance, 30, 16); //13-0030.AUD	Hell of a smart cookie there.
			Actor_Says(kActorLuther, 70, 6); //10-0070.AUD	Take your guns and your violence elsewhere. We’ve got important work to do.
		}
		// Made it so you can not shoot Luther and Lance at first. Doesn't make sense for McCoy to shoot two random strangers in the back.
		// This will change when Luther and Lance reveal that they are reps.
		if (_vm->_cutContent) {
			Actor_Set_Targetable(kActorLuther, false);
		}
		Player_Gains_Control();
		Game_Flag_Set(kFlagUG16LutherLanceTalk1);
	}
}

void SceneScriptUG16::PlayerWalkedOut() {
	if (!Game_Flag_Query(kFlagLutherLanceAreDead)) {
		Actor_Set_Goal_Number(kActorLuther, kGoalLutherMoveAround);
		//return true;
	}
	//return false;
}

void SceneScriptUG16::DialogueQueueFlushed(int a1) {
}

void SceneScriptUG16::dialogueWithLuther() {
	Dialogue_Menu_Clear_List();
	if (_vm->_cutContent) {
		DM_Add_To_List_Never_Repeat_Once_Selected(1400, 6, 4, 5); // REPLICANTS
	} else {
		DM_Add_To_List_Never_Repeat_Once_Selected(1400, 5, 6, 2); // REPLICANTS
	}
	// Made it so the lifespan option is only available when you ask the twins about their work and they mention that they are
	// trying to extend the replicant lifespan.
	// Made it so this option is only available if you had the interview with Tyrell. When you pick this option McCoy mentions that Tyrell said the 4 year lifespan for reps can not be extended, 
	// which he would only know if he talked to Tyrell about it.
	if (_vm->_cutContent) {
		DM_Add_To_List_Never_Repeat_Once_Selected(1410, 6, 4, 5); // WORK
	} else {
		DM_Add_To_List_Never_Repeat_Once_Selected(1410, 5, 4, 8); // WORK
	}
	if (_vm->_cutContent) {
		if (Game_Flag_Query(kFlagLutherLanceTalkWork)) {
			if (Actor_Clue_Query(kActorMcCoy, kClueTyrellInterview)) {
				DM_Add_To_List_Never_Repeat_Once_Selected(1420, 6, 4, 5); // LIFESPAN
			}
		}
	}
	if (Game_Flag_Query(kFlagUG16LutherLanceTalkReplicants)
	 || Game_Flag_Query(kFlagUG16LutherLanceTalkHumans)
	) {
		if (!_vm->_cutContent) {
			DM_Add_To_List_Never_Repeat_Once_Selected(1420, 6, 4, 5); // LIFESPAN
		}
		DM_Add_To_List_Never_Repeat_Once_Selected(1430, 6, 4, 5); // CLOVIS
		if (!_vm->_cutContent) {
			DM_Add_To_List_Never_Repeat_Once_Selected(1440, 6, 4, 5); // VOIGT-KAMPFF
		}
	}
	if (_vm->_cutContent) {
		if (Actor_Clue_Query(kActorMcCoy, kClueGuzzaFramedMcCoy)
		&& !Actor_Clue_Query(kActorMcCoy, kClueFolder)
		) {
			DM_Add_To_List_Never_Repeat_Once_Selected(1450, 6, 4, 5); // GUZZA
		}
	} else if ( Global_Variable_Query(kVariableCorruptedGuzzaEvidence) > 1
	 && !Actor_Clue_Query(kActorMcCoy, kClueFolder)
	 ) {
		DM_Add_To_List_Never_Repeat_Once_Selected(1450, 6, 4, 5); // GUZZA
	}
	if (Actor_Clue_Query(kActorMcCoy, kClueEnvelope)) {
		DM_Add_To_List_Never_Repeat_Once_Selected(1460, 6, 4, 5); // RUNCITER
	}
	if ( Actor_Clue_Query(kActorMcCoy, kClueDNATyrell)
	 && !Actor_Clue_Query(kActorMcCoy, kClueFolder)
	 &&  Game_Flag_Query(kFlagUG15LanceLuthorTrade)
	) {
		DM_Add_To_List_Never_Repeat_Once_Selected(1470, 6, 4, 5); // TRADE
	}
	Dialogue_Menu_Add_DONE_To_List(1480); // DONE

	Dialogue_Menu_Appear(320, 240);
	int answer = Dialogue_Menu_Query_Input();
	Dialogue_Menu_Disappear();

	switch (answer) {
	case 1400: // REPLICANTS
		// If Moraji is alive McCoy won't mention that the reps killed him.
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagMorajiAlive)) { 
				Actor_Says(kActorMcCoy, 785, 13);//00-0785.AUD	There could be a group of Nexus-6s tracking down genetic designers.
				// Made it so McCoy will not mention the reps killing Eisenduller and Moraji if Moraji survived the explosion.
				// Also McCoy will only warn Luther and Lance if he is not surly or erratic.
			} else {
				Actor_Says(kActorMcCoy, 5730, 13); //00-5730.AUD	The Reps that killed Marcus and Moraji. They’ll be looking for you.
			}
		} else {
			Actor_Says(kActorMcCoy, 5730, 13); //00-5730.AUD	The Reps that killed Marcus and Moraji. They’ll be looking for you.
		}
		Actor_Face_Actor(kActorMcCoy, kActorLuther, true);
		Actor_Says(kActorLuther, 100, 18);
		if (_vm->_cutContent) {
			if (!Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
				Actor_Says(kActorMcCoy, 5775, 13); //00-5775.AUD	So why are you still walking around?
			} else {
				Actor_Says(kActorMcCoy, 5695, 14); // How's that?
			}
		} else {
			Actor_Says(kActorMcCoy, 5775, 13); //00-5775.AUD	So why are you still walking around?
		}
		Actor_Says(kActorLance, 70, 17); //13-0070.AUD	Cause we’re all part of the same suit of cards, you know what I mean?
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagLutherLanceIsReplicant)) {		
				Actor_Says(kActorLuther, 110, 16); //10-0110.AUD	Eldon makes mistakes just like any other… human. The difference is…
				Actor_Says(kActorLance, 80, 6); //13-0080.AUD	The difference is the old bastard doesn’t like to admit it. No, he-- he covers them up, pretends they’re human, gives them a job at his stinking corporation. And when they actually produce original work he boots them out on the street.
			} 
		} else {
			Actor_Says(kActorLuther, 110, 16); //10-0110.AUD	Eldon makes mistakes just like any other… human. The difference is…
			Actor_Says(kActorLance, 80, 6); //13-0080.AUD	The difference is the old bastard doesn’t like to admit it. No, he-- he covers them up, pretends they’re human, gives them a job at his stinking corporation. And when they actually produce original work he boots them out on the street.
		}
		Actor_Says(kActorMcCoy, 5780, 13); //00-5780.AUD	You’re saying you are Replicants?
		Actor_Says(kActorLuther, 120, 16);
		Actor_Says(kActorLance, 120, 13); //13-0120.AUD	Clovis helped us see the light.
		if (_vm->_cutContent) {
			if (Player_Query_Agenda() == kPlayerAgendaSurly 
			|| Player_Query_Agenda() == kPlayerAgendaErratic) {
				Actor_Says(kActorMcCoy, 5785, 14); //00-5785.AUD	But that’s ridiculous. Tyrell wouldn’t design something like you. He wants perfection.
				Actor_Says(kActorLuther, 130, 6); //10-0130.AUD	I told you we were a mistake.
				Actor_Modify_Friendliness_To_Other(kActorLuther, kActorMcCoy, -2);
			}
		} else {
			Actor_Says(kActorMcCoy, 5785, 13); //00-5785.AUD	But that’s ridiculous. Tyrell wouldn’t design something like you. He wants perfection.
			Actor_Says(kActorLuther, 130, 6); //10-0130.AUD	I told you we were a mistake.
		}
		Actor_Says(kActorMcCoy, 5825, 13); //00-5825.AUD	Keep talking.
		if (!_vm->_cutContent) {
			Actor_Modify_Friendliness_To_Other(kActorLuther, kActorMcCoy, -5);
		}
		if (Game_Flag_Query(kFlagLutherLanceIsReplicant)) {
			Actor_Says(kActorLuther, 140, 13);
			Actor_Says(kActorLuther, 150, 14);
			Actor_Says(kActorLuther, 160, 13);
			Actor_Says(kActorLance, 140, 16);
			if (_vm->_cutContent) {
				if (!Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
					Actor_Says(kActorMcCoy, 5790, 18); //00-5790.AUD	Maybe one of you just forgot.
					Actor_Says(kActorLuther, 170, 14);
					Delay(1000);
					Actor_Face_Actor(kActorMcCoy, kActorLuther, true);
					Actor_Says(kActorMcCoy, 5750, 13);
					if (Actor_Query_Friendliness_To_Other(kActorLuther, kActorMcCoy) < 50
					|| Game_Flag_Query(kFlagLutherLanceIsReplicant)) { 		
						Actor_Says(kActorLance, 280, 6); //13-0280.AUD	(scoffs) Do you believe this clown? He wants to Voigt Kampff us.
						Actor_Says(kActorLuther, 300, 14); //10-0300.AUD	Sorry, McCoy. Shoot us or leave us alone.
						Actor_Says(kActorLuther, 310, 15); //10-0310.AUD	Let’s get back to work.
						Actor_Modify_Friendliness_To_Other(kActorLuther, kActorMcCoy, -2);
					} else {
						Actor_Says(kActorLuther, 90, 15); //10-0090.AUD	Can’t talk now.
						Actor_Says(kActorLance, 60, 6); //13-0060.AUD	Major crunch time.
						Actor_Says(kActorLuther, 310, 15); //10-0310.AUD	Let’s get back to work.
					}
				} else {
					Delay(1000);
					Actor_Says(kActorMcCoy, 3690, 14); //00-3690.AUD	Look. I wanna warn you. There’s a woman looking for you and your friends.
					Delay(1000);
					Actor_Says(kActorMcCoy, 6720, 18); //00-6720.AUD	Watch your back.
					Actor_Modify_Friendliness_To_Other(kActorLuther, kActorMcCoy, 2);
				}		
			} else {
				Actor_Says(kActorMcCoy, 5790, 13); 
				Actor_Says(kActorLuther, 170, 14);
			}
			Game_Flag_Set(kFlagUG16LutherLanceTalkReplicants);
			if (!_vm->_cutContent) {
				Actor_Modify_Friendliness_To_Other(kActorLuther, kActorMcCoy, 5);
			}
			// Gave McCoy the ability to shoot the twins once they say they are replicants.
			if (_vm->_cutContent) {
				Actor_Set_Targetable(kActorLuther, true);
			}
		} else {
			Actor_Says(kActorLuther, 180, 14); //10-0180.AUD	Clovis showed us our incept photos.
			if (_vm->_cutContent) {
				Actor_Says(kActorMcCoy, 5795, 13); //00-5795.AUD	So what?
				Actor_Says(kActorLance, 150, 17); //13-0150.AUD	That’s a pretty damn good argument, you gotta admit.
				if (!Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
					Actor_Says(kActorMcCoy, 5800, 14); //00-5800.AUD	Photos can be doctored. It’s not proof.
					Delay(2000);
					Actor_Says(kActorLance, 290, 17); //13-0290.AUD	He’s sharp this one.
					Actor_Modify_Friendliness_To_Other(kActorLuther, kActorMcCoy, 2);
					Game_Flag_Set(kFlagTwinsConvinced);
					Delay(1000);
					Actor_Face_Actor(kActorMcCoy, kActorLuther, true);
					Actor_Says(kActorMcCoy, 5750, 13);
					if (Actor_Query_Friendliness_To_Other(kActorLuther, kActorMcCoy) < 50
					|| Game_Flag_Query(kFlagLutherLanceIsReplicant)) { 		
						Actor_Says(kActorLance, 280, 6); //13-0280.AUD	(scoffs) Do you believe this clown? He wants to Voigt Kampff us.
						Actor_Says(kActorLuther, 300, 14); //10-0300.AUD	Sorry, McCoy. Shoot us or leave us alone.
						Actor_Says(kActorLuther, 310, 15); //10-0310.AUD	Let’s get back to work.
						Actor_Modify_Friendliness_To_Other(kActorLuther, kActorMcCoy, -2);
					} else {
						Actor_Says(kActorLuther, 90, 15); //10-0090.AUD	Can’t talk now.
						Actor_Says(kActorLance, 60, 6); //13-0060.AUD	Major crunch time.
						Actor_Says(kActorLuther, 310, 15); //10-0310.AUD	Let’s get back to work.
					}
				} else {
					Delay(1000);
					Actor_Says(kActorMcCoy, 5705, 18); //00-5705.AUD	Uh-huh.
					Delay(1000);
					Actor_Says(kActorMcCoy, 3690, 14); //00-3690.AUD	Look. I wanna warn you. There’s a woman looking for you and your friends.
					Delay(1000);
					Actor_Says(kActorMcCoy, 6720, 18); //00-6720.AUD	Watch your back.
					Actor_Modify_Friendliness_To_Other(kActorLuther, kActorMcCoy, 2);
				}
			} else { 
				Actor_Says(kActorMcCoy, 5795, 13); //00-5795.AUD	So what?
				Actor_Says(kActorLance, 150, 17); //13-0150.AUD	That’s a pretty damn good argument, you gotta admit.
				Actor_Says(kActorMcCoy, 5800, 14); //00-5800.AUD	Photos can be doctored. It’s not proof.
				Actor_Says(kActorLuther, 190, 15);
			}
			Game_Flag_Set(kFlagUG16LutherLanceTalkHumans);
			if (!_vm->_cutContent) {
				Actor_Modify_Friendliness_To_Other(kActorLuther, kActorMcCoy, -10);
			}
			if (_vm->_cutContent) {
				Actor_Set_Targetable(kActorLuther, true);
			}
		}
		break;

	case 1410: // WORK
		Actor_Says(kActorMcCoy, 5735, 13); //00-5735.AUD	What are you doing down here?
		Actor_Face_Actor(kActorMcCoy, kActorLuther, true);
		Actor_Says(kActorLance, 160, 17); //13-0160.AUD	Eldon shafted us. So, now we’re returning the favor.
		// Added in a line and a flag which triggers the lifespan option to appear.
		if (_vm->_cutContent) {
			Actor_Says(kActorLance, 170, 17); //13-0170.AUD	We’re gonna figure out a way to beat that four year lifespan if it kills us.
		}
		if (_vm->_cutContent) {
			if (!Game_Flag_Query(kFlagTwinsConvinced)) {
				Actor_Says(kActorLuther, 200, 14); //10-0200.AUD	We promised Clovis we’d be finished with this by the time he got back, so if you don’t mind…
			}
		} else {
			Actor_Says(kActorLuther, 200, 14); //10-0200.AUD	We promised Clovis we’d be finished with this by the time he got back, so if you don’t mind…
		}
		if (_vm->_cutContent) {
			Game_Flag_Set(kFlagLutherLanceTalkWork);
		}
		break;

	case 1420: // LIFESPAN
		Actor_Says(kActorMcCoy, 5740, 13); //00-5740.AUD	Tyrell says the four year lifespan can’t be extended.
		Actor_Face_Actor(kActorMcCoy, kActorLuther, true);
		Actor_Says(kActorLance, 180, 15);
		Actor_Says(kActorLuther, 220, 13);
		Actor_Says(kActorLance, 190, 17); //13-0190.AUD	We got the research right here that will prove it.
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
				Actor_Says(kActorMcCoy, 5805, 14); //00-5805.AUD	Is it complete? Could you extend the life of a Replicant right now?
				Actor_Says(kActorLuther, 230, 14); //10-0230.AUD	Well, no. The four year limit is an integral part of every element of the Replicant.
			}
		} else {
			Actor_Says(kActorMcCoy, 5805, 13); //00-5805.AUD	Is it complete? Could you extend the life of a Replicant right now?
			Actor_Says(kActorLuther, 230, 14); //10-0230.AUD	Well, no. The four year limit is an integral part of every element of the Replicant.
		}	
		if (_vm->_cutContent) {
			Actor_Says(kActorMcCoy, 5825, 18); //00-5825.AUD	Keep talking.
			if (Actor_Query_Friendliness_To_Other(kActorLuther, kActorMcCoy) < 50 
			|| Game_Flag_Query(kFlagLutherLanceIsReplicant)) {
				Actor_Says(kActorLuther, 90, 15); //10-0090.AUD	Can’t talk now.
				Actor_Says(kActorLance, 50, 6); //13-0050.AUD	We gotta get this done.
			} else {
				Actor_Says(kActorLuther, 240, 13); //10-0240.AUD	Tyrell’s dictate was that every body part would fail. And only the designer’s of each would know exactly how it worked.
				Actor_Says(kActorLuther, 250, 13); //10-0250.AUD	And only the designers of each would know exactly how it worked.
				if (Actor_Query_Intelligence(kActorClovis) == 100) { 
					Actor_Says(kActorLance, 200, 17); //13-0200.AUD	Clovis has already unlocked the secret of the skin. That was Moraji.
				} 
				Actor_Says(kActorLuther, 260, 13); //10-0260.AUD	Sebastian and Chew, they know about the central nervous system and the eyes.
				Actor_Says(kActorLuther, 270, 15);
				Actor_Says(kActorLance, 210, 14); //13-0210.AUD	And Tyrell, he’s got the basic DNA pattern information but he won’t just give it up.
				Actor_Says(kActorMcCoy, 5810, 13);
				if (Actor_Query_Intelligence(kActorClovis) == 100) { 
					Actor_Says(kActorLance, 220, 14);
					Actor_Says(kActorLance, 230, 17);
				} else if (Actor_Query_Intelligence(kActorClovis) == 80) {
					Actor_Says(kActorLance, 290, 17); //13-0290.AUD	He’s sharp this one.
				}
				Actor_Clue_Acquire(kActorMcCoy, kClueLutherLanceInterview, true, kActorLuther);
			}
		} else {
			Actor_Says(kActorLuther, 240, 13); //10-0240.AUD	Tyrell’s dictate was that every body part would fail. And only the designer’s of each would know exactly how it worked.
			Actor_Says(kActorLuther, 250, 13); //10-0250.AUD	And only the designers of each would know exactly how it worked.
			Actor_Says(kActorLance, 200, 17);
			Actor_Says(kActorLuther, 260, 13);
			Actor_Says(kActorLuther, 270, 15);
			Actor_Says(kActorLance, 210, 14);
			Actor_Says(kActorMcCoy, 5810, 13);
			Actor_Says(kActorLance, 220, 14);
			Actor_Says(kActorLance, 230, 17);
			Actor_Clue_Acquire(kActorMcCoy, kClueLutherLanceInterview, true, kActorLuther);
		}
		break;

	case 1430: // CLOVIS
		Actor_Says(kActorMcCoy, 5745, 13); //00-5745.AUD	Where’s Clovis now?
		Actor_Face_Actor(kActorMcCoy, kActorLuther, true);
		// Added in some lines and a clue.
		if (_vm->_cutContent) {
			if (!Game_Flag_Query(kFlagLutherLanceIsReplicant)) {
				Actor_Says(kActorLuther, 340, 15); //10-0340.AUD	Clovis has gone to see Eldon.
			} else {
				Actor_Says(kActorLance, 240, 15); //13-0240.AUD	Gone to have a little heart to heart with Eldon.
			}
		} else {
			Actor_Says(kActorLance, 240, 15); //13-0240.AUD	Gone to have a little heart to heart with Eldon.
		}
		if (_vm->_cutContent) {
			Actor_Says(kActorLuther, 280, 15); //10-0280.AUD	We showed him how to get in through the basement.
			Actor_Clue_Acquire(kActorMcCoy, kClueSightingClovis, true, kActorLuther);
		}
		if (_vm->_cutContent) {
			if (Player_Query_Agenda() != kPlayerAgendaSurly 
			&& Player_Query_Agenda() != kPlayerAgendaErratic) {
				Actor_Says(kActorMcCoy, 5815, 14); //00-5815.AUD	He’ll kill Tyrell, if he gets to him.
				// Made it so if the twins are replicants the have no remorse in regards to Clovis trying to kill Tyrell. If they are human Clovis' lied about his intentions and the twins believe
				// that Clovis won't kill Tyrell.
				if (Game_Flag_Query(kFlagLutherLanceIsReplicant)) {
					Actor_Says(kActorLance, 250, 16);
					Actor_Says(kActorLuther, 290, 15);
					Actor_Says(kActorLance, 260, 15);
				} else {
					Actor_Says(kActorLuther, 190, 15);	//10-0190.AUD	Clovis said you’d say that.
				}
			}
		} else {
			Actor_Says(kActorLance, 250, 16);
			Actor_Says(kActorLuther, 290, 15);
			Actor_Says(kActorLance, 260, 15);
		}
		break;

	case 1440: // VOIGT-KAMPFF
		Actor_Says(kActorMcCoy, 5750, 13);
		Actor_Face_Actor(kActorMcCoy, kActorLuther, true);
		Actor_Says(kActorLance, 280, 6); //13-0280.AUD	(scoffs) Do you believe this clown? He wants to Voigt Kampff us.
		Actor_Says(kActorLuther, 300, 14); //10-0300.AUD	Sorry, McCoy. Shoot us or leave us alone.
		Actor_Says(kActorLuther, 310, 15); //10-0310.AUD	Let’s get back to work.
		Actor_Modify_Friendliness_To_Other(kActorLuther, kActorMcCoy, -5);
		break;

	case 1450: // GUZZA
		Actor_Says(kActorMcCoy, 5755, 13); //00-5755.AUD	Clovis set me up, didn’t he? And he used my boss to do it.
		Actor_Face_Actor(kActorMcCoy, kActorLuther, true);
		if (_vm->_cutContent) {
			if (Actor_Query_Friendliness_To_Other(kActorLuther, kActorMcCoy) < 50
			|| Game_Flag_Query(kFlagLutherLanceIsReplicant)) { 
				Actor_Says(kActorLance, 30, 16); //13-0030.AUD	Hell of a smart cookie there.
			} else {
				Actor_Says(kActorLance, 290, 17); //13-0290.AUD	He’s sharp this one.
				Actor_Says(kActorLuther, 320, 16); //10-0320.AUD	No question.
			}
		} else {
			Actor_Says(kActorLance, 290, 17); //13-0290.AUD	He’s sharp this one.
			Actor_Says(kActorLuther, 320, 16); //10-0320.AUD	No question.
		}
		Actor_Says(kActorMcCoy, 5820, 13); //00-5820.AUD	Tell me what you know.
		Actor_Says(kActorLance, 300, 17);
		Actor_Says(kActorLuther, 330, 14);
		Actor_Says(kActorMcCoy, 5825, 13);
		Actor_Says(kActorLuther, 340, 13); //10-0340.AUD	Clovis has gone to see Eldon.
		Actor_Says(kActorLance, 310, 13); //13-0310.AUD	But he might not make it.
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagLutherLanceIsReplicant)
			|| Game_Flag_Query(kFlagTwinsConvinced)) {
				Actor_Says(kActorLuther, 350, 13); //10-0350.AUD	Still the work will go on with or without Clovis.
			}
		} else {
			Actor_Says(kActorLuther, 350, 13); //10-0350.AUD	Still the work will go on with or without Clovis.
		}
		Actor_Says(kActorLuther, 360, 15); //10-0360.AUD	Get us Tyrell’s files. The rest of the DNA data. And we will help you.
		if (_vm->_cutContent) {
			if (Player_Query_Agenda() == kPlayerAgendaSurly 
			|| Player_Query_Agenda() == kPlayerAgendaErratic) {
				Actor_Says(kActorMcCoy, 690, 18); //00-0690.AUD	Gotcha.
			} else {
				Actor_Says(kActorMcCoy, 5830, 14); 
				Actor_Says(kActorLance, 320, 16);
				Actor_Says(kActorLance, 330, 15);
			}
		} else {
			Actor_Says(kActorMcCoy, 5830, 13); //00-5830.AUD	You want me to break into the Tyrell Building for you? You’re nuts.
			Actor_Says(kActorLance, 320, 16);
			Actor_Says(kActorLance, 330, 15);
		}
		Game_Flag_Set(kFlagUG15LanceLuthorTrade);
		break;

	case 1460: // RUNCITER
		Actor_Says(kActorMcCoy, 5760, 13);
		Actor_Face_Actor(kActorMcCoy, kActorLuther, true);
		if (_vm->_cutContent) {
			if (!Game_Flag_Query(kFlagLutherLanceIsReplicant)) {
				Actor_Says(kActorLuther, 370, 15);
			}
		} else {
			Actor_Says(kActorLuther, 370, 15);
		}
		Actor_Says(kActorLance, 340, 14); //13-0340.AUD	We just wanted to make some extra cash on the side.
		// Added in some lines.
		if (_vm->_cutContent) {
			Actor_Says(kActorLance, 350, 14); //13-0350.AUD	So, I sold Runciter some of Tyrell’s state of the art animals.
			Actor_Says(kActorLance, 360, 14); //13-0360.AUD	He was going to pawn them off as real.
		}
		if (_vm->_cutContent) {
			if (Player_Query_Agenda() != kPlayerAgendaSurly 
			&& Player_Query_Agenda() != kPlayerAgendaErratic) {
				Actor_Says(kActorMcCoy, 5835, 18); //00-5835.AUD	That probably had something to do with you guys getting fired.
				if (Game_Flag_Query(kFlagLutherLanceIsReplicant)) {
					Actor_Says(kActorLance, 370, 6); //13-0370.AUD	Since Eldon is such a pain in the ass control freak…
					Actor_Says(kActorLuther, 380, 15); //10-0380.AUD	I’m sure he wasn’t too pleased.
				} else {
					Delay(2000);
				}
			}
		} else {
			Actor_Says(kActorMcCoy, 5835, 13); //00-5835.AUD	That probably had something to do with you guys getting fired.
			Actor_Says(kActorLuther, 380, 15); //10-0380.AUD	I’m sure he wasn’t too pleased.
			Actor_Says(kActorLance, 370, 6); //13-0370.AUD	Since Eldon is such a pain in the ass control freak…
		}
		Actor_Says(kActorMcCoy, 5840, 13);
		Actor_Says(kActorLance, 380, 13); //13-0380.AUD	It was all just a coincidence.
		if (_vm->_cutContent) {
			Actor_Says(kActorLance, 390, 6); //13-0390.AUD	We just happened to be doing business with the same scumbag.
			Actor_Clue_Acquire(kActorMcCoy, kClueRunciterConfession1, true, kActorLance);
		}
		break;

	case 1470: // TRADE
		if (_vm->_cutContent) {
			Player_Loses_Control();
			Loop_Actor_Walk_To_Actor(kActorMcCoy, kActorLuther, 24, true, false);
			Player_Gains_Control();
		}
		Actor_Says(kActorMcCoy, 5765, 13);
		if (_vm->_cutContent) {
			Actor_Change_Animation_Mode(kActorMcCoy, 23);
			Delay(800);
			Item_Pickup_Spin_Effect_From_Actor(kModelAnimationDNADataDisc, kActorLuther, 0, 0);
			Delay(800);
			Actor_Clue_Acquire(kActorLuther, kClueDNATyrell, true, -1);
		}
		Actor_Face_Actor(kActorMcCoy, kActorLuther, true);
		if (_vm->_cutContent) {
			if (Actor_Query_Friendliness_To_Other(kActorLuther, kActorMcCoy) < 50
			|| Game_Flag_Query(kFlagLutherLanceIsReplicant))  {
				Actor_Says(kActorLance, 400, 15); //13-0400.AUD	Check it out, bro. The little man with the big gun did good.
			} else {
				Actor_Says(kActorLance, 290, 17); //13-0290.AUD	He’s sharp this one.
			}
		} else {
			Actor_Says(kActorLance, 400, 15); //13-0400.AUD	Check it out, bro. The little man with the big gun did good.
		}
		if (_vm->_cutContent) {
			if (Player_Query_Agenda() == kPlayerAgendaSurly 
			|| Player_Query_Agenda() == kPlayerAgendaErratic) {
				Actor_Says(kActorMcCoy, 5845, 13); //00-5845.AUD	A bargain’s a bargain. You said you’d give me Guzza.
			} else {
				Actor_Says(kActorMcCoy, 6985, 16); //00-6985.AUD	Got the straight scoop for me or what?
			}
		} else {
			Actor_Says(kActorMcCoy, 5845, 13); //00-5845.AUD	A bargain’s a bargain. You said you’d give me Guzza.
		}
		Actor_Says(kActorLuther, 390, 23); //10-0390.AUD	It’s all right here.
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagLutherLanceIsReplicant)) {
				Actor_Says(kActorLance, 410, 14); //13-0410.AUD	Your boss is a real piece of work, let me tell you. Almost as good as Tyrell.
			}
		} else {
			Actor_Says(kActorLance, 410, 14); //13-0410.AUD	Your boss is a real piece of work, let me tell you. Almost as good as Tyrell.
		}
		Actor_Says(kActorLance, 420, 17); 
		if (_vm->_cutContent) {
			Actor_Change_Animation_Mode(kActorMcCoy, 23);
			Delay(800);
			Item_Pickup_Spin_Effect_From_Actor(kModelAnimationFolder, kActorMcCoy, 0, 0);
			Delay(800);
			Actor_Voice_Over(2740, kActorVoiceOver);
		}
#if BLADERUNNER_ORIGINAL_BUGS
		// This quote is repeated (also used in RUNCITER question
		// "That probably had something to do with you guys getting fired."
		// It makes little sense to be here.
		Actor_Says(kActorMcCoy, 5835, 13);
#endif // BLADERUNNER_ORIGINAL_BUGS
		if (!_vm->_cutContent) {
			Delay(1000);
			Item_Pickup_Spin_Effect(kModelAnimationFolder, 239, 454);
			Actor_Voice_Over(2740, kActorVoiceOver);
		}	
		Actor_Voice_Over(2750, kActorVoiceOver);
		Actor_Voice_Over(2760, kActorVoiceOver);
		Actor_Voice_Over(2770, kActorVoiceOver);
		if (_vm->_cutContent) {
			Delay(1000);
			Actor_Voice_Over(3430, kActorVoiceOver); //99-3430.AUD	The info I’d gotten from Luther and Lance finally made some sense.
			Actor_Voice_Over(3440, kActorVoiceOver); //99-3440.AUD	The Reps must had found out about Guzza’s career's sidelines…
			Actor_Voice_Over(3450, kActorVoiceOver); //99-3450.AUD	and pressured him to set me up in order to get me off their backs.
			Actor_Voice_Over(3460, kActorVoiceOver); //99-3460.AUD	This nasty business he was only too willing to do.
			Actor_Voice_Over(3470, kActorVoiceOver); //99-3470.AUD	But I wasn’t gonna eat crow that easily.
			if (Player_Query_Agenda() == kPlayerAgendaSurly 
			|| Player_Query_Agenda() == kPlayerAgendaErratic) {
				Actor_Voice_Over(2780, kActorVoiceOver); //99-2780.AUD	When my stomach stopped churning, I realized I had everything I needed to force the bastard to play ball with me.
				Actor_Voice_Over(2800, kActorVoiceOver); //99-2800.AUD	I knew that he would listen to reason, if applied with serious pressure.
				Actor_Voice_Over(3500, kActorVoiceOver); //99-3500.AUD	All I had to do was place a call and make the worm squirm.	
			} else {
				Actor_Voice_Over(3490, kActorVoiceOver); //99-3490.AUD	It was time to have my own little fun with Guzza.
				Actor_Voice_Over(2810, kActorVoiceOver);	
			}
			Delay(1000);
		}
		Actor_Says(kActorMcCoy, 5850, 13); 
		Actor_Says(kActorLuther, 400, 15); //10-0400.AUD	From Clovis. He told us to hold it for him.
		if (_vm->_cutContent) {
			if (!Game_Flag_Query(kFlagTwinsConvinced)
			|| Game_Flag_Query(kFlagLutherLanceIsReplicant)) {
				Actor_Says(kActorLance, 430, 6); //13-0430.AUD	Come to think of it I’m not sure you’re supposed to see it. You wanna give it back now?
				if (Player_Query_Agenda() == kPlayerAgendaSurly 
				|| Player_Query_Agenda() == kPlayerAgendaErratic) {
					Actor_Says(kActorMcCoy, 5855, 13);
				} else {
					Actor_Says(kActorMcCoy, 855, 13); //00-0855.AUD	What?
				}
				Actor_Says(kActorLuther, 410, 14); //10-0410.AUD	Let him have it. Clovis said he was finished with the policemen anyway.
			} else {
				Actor_Says(kActorMcCoy, 4880, 13); //00-4880.AUD	Is that right?
				Actor_Says(kActorLuther, 310, 14); //10-0310.AUD	Let’s get back to work.
			}
		} else {
			Actor_Says(kActorLance, 430, 6); //13-0430.AUD	Come to think of it I’m not sure you’re supposed to see it. You wanna give it back now?
			Actor_Says(kActorMcCoy, 5855, 13);
			Actor_Says(kActorLuther, 410, 14); //10-0410.AUD	Let him have it. Clovis said he was finished with the policemen anyway.
		}
		Game_Flag_Set(kFlagUG16FolderFound);
		Actor_Clue_Acquire(kActorMcCoy, kClueFolder, true, kActorLuther);
		break;

	case 1480: // DONE
		// Added in some banter dialogue.
		if (_vm->_cutContent) {
			Actor_Face_Actor(kActorMcCoy, kActorLuther, true);
			Actor_Says(kActorMcCoy, 5770, 15); //00-5770.AUD	Listen, fellas.
			if (Actor_Query_Friendliness_To_Other(kActorLuther, kActorMcCoy) < 50
			|| Game_Flag_Query(kFlagLutherLanceIsReplicant)) {
				Actor_Says(kActorLuther, 70, 6); //10-0070.AUD	Take your guns and your violence elsewhere. We’ve got important work to do.
			} else {
				Actor_Says(kActorLuther, 90, 15); //10-0090.AUD	Can’t talk now.
				Actor_Says(kActorLance, 50, 6); //13-0050.AUD	We gotta get this done.
				Actor_Says(kActorLance, 60, 6); //13-0060.AUD	Major crunch time.
			}
			if (Player_Query_Agenda() == kPlayerAgendaSurly 
			|| Player_Query_Agenda() == kPlayerAgendaErratic) {
				Actor_Says(kActorMcCoy, 8720, 17); //00-8720.AUD	Freak.
			} else if (Player_Query_Agenda() == kPlayerAgendaPolite) { 
				Actor_Says(kActorMcCoy, 805, 3); //00-0805.AUD	Sorry to bother you.
			} else {
				Actor_Says(kActorMcCoy, 4595, 14);
			}
		} else {
			Actor_Says(kActorMcCoy, 4595, 14);
		}
		break;
	}
}

} // End of namespace BladeRunner
