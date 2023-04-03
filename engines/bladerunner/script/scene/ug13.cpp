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

void SceneScriptUG13::InitializeScene() {
	if (Game_Flag_Query(kFlagUG18toUG13)) {
		Setup_Scene_Information(-477.0f, 141.9f, -870.0f, 378);
	} else if (Game_Flag_Query(kFlagUG15toUG13)) {
		Setup_Scene_Information(  39.0f, 52.94f, -528.0f, 600);
	} else {
		// arrived from elevator (going down)
		Setup_Scene_Information( -22.0f, 54.63f, -883.0f, 578);
#if BLADERUNNER_ORIGINAL_BUGS
		Actor_Set_Invisible(kActorMcCoy, false);
#else
		// McCoy should not be visible starting this scene when he goes down with the elevator
		Actor_Set_Invisible(kActorMcCoy, true);
#endif // BLADERUNNER_ORIGINAL_BUGS
	}

	if (!Game_Flag_Query(kFlagUG08ElevatorUp)) {
		Scene_Exit_Add_2D_Exit(0, 394, 205, 464, 281, 0);
	}
	Scene_Exit_Add_2D_Exit(1, 560, 90, 639, 368, 1);
	Scene_Exit_Add_2D_Exit(2, 108, 85, 175, 210, 3);

	Ambient_Sounds_Add_Looping_Sound(kSfxSTMLOOP7, 15, 0, 1);
	Ambient_Sounds_Add_Looping_Sound(kSfxUGBED1,   40, 0, 1);
	Ambient_Sounds_Add_Looping_Sound(kSfxUGBED2,   40, 0, 1);
	Ambient_Sounds_Add_Sound(kSfxYELL1M2,  2, 120, 11, 12, -100, 100, -100, 100, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxYELL1M3,  2, 120, 11, 12, -100, 100, -100, 100, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxGRUNT1M1, 2, 120, 11, 12, -100, 100, -100, 100, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxGRUNT2M2, 2, 120, 11, 12, -100, 100, -100, 100, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxGRUNT2M3, 2, 120, 11, 12, -100, 100, -100, 100, 0, 0);

	if ( Global_Variable_Query(kVariableChapter) == 4
	 && !Game_Flag_Query(kFlagCT04HomelessKilledByMcCoy)
	) {
		Actor_Set_Goal_Number(kActorTransient, 390);
	}

	if (Actor_Query_Goal_Number(kActorTransient) == 599
	|| Game_Flag_Query(kFlagTransientDead)) {
		Actor_Change_Animation_Mode(kActorTransient, 89);
	}

	if (Game_Flag_Query(kFlagUG08toUG13)) {
		Scene_Loop_Start_Special(kSceneLoopModeLoseControl, 0, false);
		Scene_Loop_Set_Default(1);
	} else if (Game_Flag_Query(kFlagUG08ElevatorUp)) {
		Scene_Loop_Set_Default(4);
	} else {
		Scene_Loop_Set_Default(1);
	}
}

void SceneScriptUG13::SceneLoaded() {
	Obstacle_Object("BASKET", true);
	Obstacle_Object("BOLLARD", true);
	Unobstacle_Object("STAIR", true);
	Unobstacle_Object("BOX FOR ARCHWAY 02", true);
	Unobstacle_Object("STAIR_RAIL", true);
	Unobstacle_Object("DISC_LEFT", true);
#if BLADERUNNER_ORIGINAL_BUGS
#else
	if (Game_Flag_Query(kFlagUG08ElevatorUp)) {
		Obstacle_Object("ELEVBLOCK", true);
	} else {
		Unobstacle_Object("ELEVBLOCK", true);
	}
#endif // BLADERUNNER_ORIGINAL_BUGS
	Clickable_Object("BASKET");
	Clickable_Object("BOLLARD");
	Unclickable_Object("BASKET");
	// Adjusted the conditions for the original requisition form to appear. The homeless man being dead really did not make any 
	// sense as a condition for it to appear. However the player must still have found one of the other forms since the dialogue of McCoy comparing the 
	// the form to the other forms won't make sense.
	if (_vm->_cutContent) {
		if (Game_Flag_Query(kFlagCT04HomelessKilledByMcCoy)
		&& !Actor_Clue_Query(kActorMcCoy, kClueOriginalRequisitionForm)) {
			Game_Flag_Set(kFlagUG13OriginalRequisitionFormPlaced);
			Item_Add_To_World(kItemWeaponsOrderForm, kModelAnimationOriginalRequisitionForm, kSetUG13, -209.01f, 70.76f, -351.79f, 0, 16, 12, false, true, false, true);
		}
	} else if (Global_Variable_Query(kVariableChapter) >= 3
	    && !Actor_Clue_Query(kActorMcCoy, kClueOriginalRequisitionForm)
	    && Game_Flag_Query(kFlagCT04HomelessKilledByMcCoy)
	    && (Actor_Clue_Query(kActorMcCoy, kClueShippingForm)
	        || Actor_Clue_Query(kActorMcCoy, kClueWeaponsOrderForm))
#if BLADERUNNER_ORIGINAL_BUGS
#else
	    && !Game_Flag_Query(kFlagUG13OriginalRequisitionFormPlaced)
#endif // BLADERUNNER_ORIGINAL_BUGS
	) {
		Game_Flag_Set(kFlagUG13OriginalRequisitionFormPlaced);
		Item_Add_To_World(kItemWeaponsOrderForm, kModelAnimationOriginalRequisitionForm, kSetUG13, -209.01f, 70.76f, -351.79f, 0, 16, 12, false, true, false, true);
	}
}

bool SceneScriptUG13::MouseClick(int x, int y) {
	return false;
}

bool SceneScriptUG13::ClickedOn3DObject(const char *objectName, bool a2) {
	if (Object_Query_Click("BOLLARD", objectName)) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, 7.0f, 44.0f, -695.0f, 0, true, false, false)) {
			Actor_Face_Object(kActorMcCoy, "BOLLARD", true);
			if (Game_Flag_Query(kFlagUG08ElevatorUp)) {
				Scene_Loop_Set_Default(1);
#if BLADERUNNER_ORIGINAL_BUGS
#else
				// start elevator sound, but wait a bit before starting the special loop
				Ambient_Sounds_Play_Sound(kSfxCARGELE2, 90, 0, 0, 100);
				Delay(1500);
#endif // BLADERUNNER_ORIGINAL_BUGS
				Scene_Loop_Start_Special(kSceneLoopModeOnce, 0, false);
				Game_Flag_Reset(kFlagUG08ElevatorUp);
				Game_Flag_Set(kFlagUG13CallElevator);
#if BLADERUNNER_ORIGINAL_BUGS
#else
				Unobstacle_Object("ELEVBLOCK", true);
#endif // BLADERUNNER_ORIGINAL_BUGS
				return true;
			} else {
				Scene_Loop_Set_Default(4);
				Scene_Loop_Start_Special(kSceneLoopModeOnce, 3, false);
				Game_Flag_Set(kFlagUG08ElevatorUp);
				Scene_Exit_Remove(0);
#if BLADERUNNER_ORIGINAL_BUGS
#else
				Obstacle_Object("ELEVBLOCK", true);
#endif // BLADERUNNER_ORIGINAL_BUGS
				return true;
			}
		}
	}
	return false;
}

bool SceneScriptUG13::ClickedOnActor(int actorId) {
	if (actorId == kActorTransient
	 && Global_Variable_Query(kVariableChapter) == 4
	) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -248.0f, 44.0f, -390.0f, 12, true, false, false)) {
			Actor_Face_Actor(kActorMcCoy, kActorTransient, true);
			if (Actor_Query_Goal_Number(kActorTransient) != 6
			 && Actor_Query_Goal_Number(kActorTransient) != 599
			) {
				if (!Game_Flag_Query(kFlagUG13HomelessTalk1)) {
					Actor_Face_Actor(kActorMcCoy, kActorTransient, true);
					Game_Flag_Set(kFlagUG13HomelessTalk1);
					if (_vm->_cutContent) {
						// Made it so McCoy and the homeless man only recognise each other if they had a conversation behind Howie Lees when McCoy was chasing Zuben.
						// It would make no sense for them to recognise each other if McCoy just ran past the homeless guy without talking to him, especially when the homeless guy
						// had his face buried in the dumpster while searching through the trash.
						if (Game_Flag_Query(kFlagCT04HomelessTalk)) {
							Actor_Says(kActorMcCoy, 5560, 13); // hey
							Actor_Says_With_Pause(kActorMcCoy, 5565, 3.0f, 18); // haven't i seen...?
							if (Actor_Query_Friendliness_To_Other(kActorTransient, kActorMcCoy) < 51) {
								Actor_Says(kActorTransient, 70, 31); // Ah, always chasing.
							}
							Actor_Says(kActorTransient, 80, 32); // Got that big dumb lox...
							Actor_Says(kActorMcCoy, 5570, kAnimationModeTalk); // small world...
							if (Actor_Query_Friendliness_To_Other(kActorTransient, kActorMcCoy) < 51) {
								Actor_Says(kActorTransient, 90, 32); // Hm, guess so
							}
						} else {
							Actor_Says(kActorMcCoy, 5560, 13); // hey
							Actor_Says(kActorMcCoy, 8915, 11); //00-8915.AUD	You got a minute, pal?
							Actor_Says(kActorTransient, 130, 31); // You got something...?
							Actor_Says(kActorMcCoy, 7815, 15); //00-7815.AUD	No.
							if (Player_Query_Agenda() == kPlayerAgendaPolite) {
								Actor_Says(kActorMcCoy, 2305, 13); //00-2305.AUD	I’m sorry.
							}
						}
					} else {
						Actor_Face_Actor(kActorMcCoy, kActorTransient, true);
						Game_Flag_Set(kFlagUG13HomelessTalk1);
						Actor_Says(kActorMcCoy, 5560, 13); // hey
						Actor_Says_With_Pause(kActorMcCoy, 5565, 3.0f, 18); // haven't i seen...?
						Actor_Says(kActorTransient, 70, 31); // Ah, always chasing.
						Actor_Says(kActorTransient, 80, 32); // Got that big dumb lox...
						Actor_Says(kActorMcCoy, 5570, kAnimationModeTalk); // small world...
						Actor_Says(kActorTransient, 90, 32); // Hm, guess so
					}
				} else if (!Actor_Clue_Query(kActorMcCoy, kClueHomelessManInterview1) || !Actor_Clue_Query(kActorMcCoy, kClueHomelessManInterview2)) {
					dialogueWithHomeless1();
				} else {
					if (_vm->_cutContent) {
						Actor_Set_Goal_Number(kActorTransient, 391);
						if (Actor_Clue_Query(kActorMcCoy, kClueFlaskOfAbsinthe)
						&& !Actor_Clue_Query(kActorMcCoy, kClueBigManLimping)) {
							dialogueWithHomeless1();
						} else if (!Actor_Clue_Query(kActorMcCoy, kClueFlaskOfAbsinthe)
						&& !Actor_Clue_Query(kActorMcCoy, kClueBigManLimping)) {
							Actor_Face_Actor(kActorMcCoy, kActorTransient, true);
							Actor_Says(kActorTransient, 130, 53); //12-0130.AUD	You got something so's I can wet my whistle?
							Actor_Says(kActorMcCoy, 7815, 13); //00-7815.AUD	No.
							if (Player_Query_Agenda() == kPlayerAgendaPolite) {
								Actor_Says(kActorMcCoy, 2305, 18); //00-2305.AUD	I’m sorry.
							}
							Delay(1000);
							Actor_Says(kActorMcCoy, 5600, 14);               // Let me ask you
							Actor_Says(kActorTransient, 280, 32);  //12-0280.AUD	You got anything to drink? My throat’s awful dry.
							Actor_Says(kActorMcCoy, 5605, 18); // I'm talking to you...
							Delay(2000);
							Actor_Says(kActorTransient, 160, 31); //12-0160.AUD	Sure you don’t got that drink?
							Delay(1000);
							Actor_Says(kActorMcCoy, 8525, 13); // generic "hmph"
							Delay(1000);
							Game_Flag_Set(kFlagUG10GateOpen);
							Game_Flag_Set(kFlagRC03UnlockedToUG01);
							Game_Flag_Set(kFlagHC04toHC02);
							Set_Enter(kSetHC01_HC02_HC03_HC04, kSceneHC02);
						} else if (Game_Flag_Query(kFlagTransientDead)) {
							if (Player_Query_Agenda() == kPlayerAgendaSurly 
							|| Player_Query_Agenda() == kPlayerAgendaErratic) {
								Actor_Says(kActorMcCoy, 8665, 13); //00-8665.AUD	Disgusting.
							} else if (Player_Query_Agenda() == kPlayerAgendaPolite) {
								Delay(1000);
								Actor_Says(kActorMcCoy, 2305, 13); //00-2305.AUD	I’m sorry.
								Delay(1000);
							} else {
								Actor_Says(kActorMcCoy, 8630, 12);  // What a waste
							}
						} else {
							Actor_Says(kActorMcCoy, 5600, 14);               // Let me ask you
							Actor_Says(kActorTransient, 100, 53);            // sleeping, mumbling
							Actor_Says(kActorMcCoy, 5605, 18);               // I'm talking to you...
							Actor_Start_Speech_Sample(kActorTransient, 110); // sleeping, mumbling
							Actor_Set_Goal_Number(kActorTransient, 395);
						} 
					} else {
						Actor_Set_Goal_Number(kActorTransient, 391);
						if (Actor_Clue_Query(kActorMcCoy, kClueFlaskOfAbsinthe)) {
							dialogueWithHomeless1();
						} else {
							Actor_Face_Actor(kActorMcCoy, kActorTransient, true);
							Actor_Says(kActorMcCoy, 5600, 14);               // Let me ask you
							Actor_Says(kActorTransient, 100, 53);            // sleeping, mumbling
							Actor_Says(kActorMcCoy, 5605, 18);               // I'm talking to you...
							Actor_Start_Speech_Sample(kActorTransient, 110); // sleeping, mumbling
							Actor_Set_Goal_Number(kActorTransient, 395);
						}
					}
				}
			} else if (Random_Query(0, 1) == 1) {
				Actor_Says(kActorMcCoy, 8590, 16);
			} else {
				Actor_Says(kActorMcCoy, 8655, 15);
			}
		}
	}
	return false;
}

bool SceneScriptUG13::ClickedOnItem(int itemId, bool a2) {
	if (itemId == kItemWeaponsOrderForm) {
		if (!Loop_Actor_Walk_To_Item(kActorMcCoy, kItemWeaponsOrderForm, 36, true, false)) {
			Actor_Face_Item(kActorMcCoy, kItemWeaponsOrderForm, true);
			Actor_Clue_Acquire(kActorMcCoy, kClueOriginalRequisitionForm, true, -1);
			Item_Remove_From_World(kItemWeaponsOrderForm);
			Item_Pickup_Spin_Effect(kModelAnimationOriginalRequisitionForm, 426, 316);
			if (_vm->_cutContent) {
				Actor_Says(kActorMcCoy, 8805, 13); //00-8805.AUD	A requisition form.
				if (Actor_Clue_Query(kActorMcCoy, kClueRequisitionForm)) {
					Actor_Voice_Over(3950, kActorVoiceOver);
					Actor_Voice_Over(3960, kActorVoiceOver);
					Actor_Voice_Over(3970, kActorVoiceOver);
					Actor_Voice_Over(3980, kActorVoiceOver);
					Actor_Voice_Over(3990, kActorVoiceOver);
					Actor_Voice_Over(4000, kActorVoiceOver);
				}
			} else {
				Actor_Voice_Over(3950, kActorVoiceOver);
				Actor_Voice_Over(3960, kActorVoiceOver);
				Actor_Voice_Over(3970, kActorVoiceOver);
				Actor_Voice_Over(3980, kActorVoiceOver);
				Actor_Voice_Over(3990, kActorVoiceOver);
				Actor_Voice_Over(4000, kActorVoiceOver);
			}
			return true;
		}
	}
	return false;
}

bool SceneScriptUG13::ClickedOnExit(int exitId) {
	if (exitId == 0) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -32.0f, 54.63f, -883.0f, 0, true, false, false)) {
			Player_Loses_Control();
			Game_Flag_Set(kFlagUG13toUG08);
			Game_Flag_Set(kFlagUG08ElevatorUp);
			Set_Enter(kSetUG08, kSceneUG08);
			Scene_Loop_Start_Special(kSceneLoopModeChangeSet, 3, false);
		}
		return true;
	}

	if (exitId == 1) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, 39.0f, 52.94f, -528.0f, 0, true, false, false)) {
			if (_vm->_cutContent) {
				if (!Game_Flag_Query(kFlagUG15BridgeBroken)) {
					Game_Flag_Set(kFlagUG13toUG15);
					Set_Enter(kSetUG15, kSceneUG15);
				} else {
					Actor_Says(kActorMcCoy, 7815, 13); //00-7815.AUD	No.
				}
			} else {
				Game_Flag_Set(kFlagUG13toUG15);
				Set_Enter(kSetUG15, kSceneUG15);
			}
		}
		return true;
	}

	if (exitId == 2) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -267.0f, 44.0f, -795.0f, 0, true, false, false)) {
			Actor_Face_Heading(kActorMcCoy, 830, false);
			Footstep_Sound_Override_On(3);
			Loop_Actor_Travel_Stairs(kActorMcCoy, 11, true, kAnimationModeIdle);
			Footstep_Sound_Override_Off();
			// This path is unreachable in the original game
			// Restore this condition only for hard mode. Probably occurs before meeting with Guzza is set
			// Since this situation always now happens in cut content mode it will only play in hard mode for the original game.
			if (_vm->_cutContent && Game_Flag_Query(kFlagUG18GuzzaScene)) {
				Actor_Says(kActorMcCoy, 7815, 13); //00-7815.AUD	No.
				Actor_Face_Heading(kActorMcCoy, 325, false);
				Loop_Actor_Travel_Stairs(kActorMcCoy, 11, false, kAnimationModeIdle);
			} else if (!_vm->_cutContent && Query_Difficulty_Level() == kGameDifficultyHard) {
				if (!Game_Flag_Query(kFlagCallWithGuzza)) {
					// Passage to UG18 is locked
					// These lines of dialogue are not in the code of the original game
					if (Actor_Query_Goal_Number(kActorTransient) == 391
					    || Actor_Query_Goal_Number(kActorTransient) == 395
					    || Actor_Query_Goal_Number(kActorTransient) == 599
						|| Game_Flag_Query(kFlagGuzzaSaved)
					) {
						Actor_Says(kActorMcCoy, 8522, 14); // Locked
					} else {
						Actor_Says(kActorMcCoy, 5555, 14); // How do I get this thing open?
						Actor_Says(kActorTransient, 60, 31); // Nah, it only happens when they want it to open.
					}
					// turn back
					Actor_Face_Heading(kActorMcCoy, 325, false);
					Loop_Actor_Travel_Stairs(kActorMcCoy, 11, false, kAnimationModeIdle);
					return true;
				}
			} else {
				Loop_Actor_Walk_To_XYZ(kActorMcCoy, -477.0f, 141.9f, -870.0f, 0, false, false, false);
				Set_Enter(kSetUG18, kSceneUG18);
			}
		}
		return true;
	}

	return false;
}

bool SceneScriptUG13::ClickedOn2DRegion(int region) {
	return false;
}

void SceneScriptUG13::SceneFrameAdvanced(int frame) {
	if (frame == 94) {
		Ambient_Sounds_Play_Sound(kSfxCARGELE2, 90, 0, 0, 100);
	}

	if (Game_Flag_Query(kFlagUG13CallElevator)
	 && frame > 29
	 && frame < 91
	) {
		Scene_Exit_Add_2D_Exit(0, 394, 205, 464, 281, 0);
		Game_Flag_Reset(kFlagUG13CallElevator);
		//return true;
		return;
	}

	if (Game_Flag_Query(kFlagUG08toUG13)
	 && frame < 25
	) {
		Actor_Set_Invisible(kActorMcCoy, true);
	} else if (Game_Flag_Query(kFlagUG13toUG08)
	        && frame >= 94
	        && frame <= 120
	) {
		Actor_Set_Invisible(kActorMcCoy, true);
	} else {
		Actor_Set_Invisible(kActorMcCoy, false);
	}
	//return false;
	return;
}

void SceneScriptUG13::ActorChangedGoal(int actorId, int newGoal, int oldGoal, bool currentSet) {
}

void SceneScriptUG13::PlayerWalkedIn() {
	if (Game_Flag_Query(kFlagUG18toUG13)) {
#if BLADERUNNER_ORIGINAL_BUGS
		Loop_Actor_Walk_To_XYZ(kActorMcCoy, -389.0f, 143.0f, -844.0f, 0, false, false, false);
#else
		Actor_Set_At_XYZ(kActorMcCoy, -389.0f, 143.0f, -844.0f, 325);
#endif // BLADERUNNER_ORIGINAL_BUGS
		Actor_Face_Heading(kActorMcCoy, 325, false);
		Footstep_Sound_Override_On(3);
		Loop_Actor_Travel_Stairs(kActorMcCoy, 11, false, kAnimationModeIdle);
		Footstep_Sound_Override_Off();
		Game_Flag_Reset(kFlagUG18toUG13);
		Player_Gains_Control();
		// This is code for a scene  where McCoy returns to the transient after chasing down Guzza. McCoy checks on the the transient but he died from his wound. 
		// McCoy then searches the transients body and finds the original shipping form clue. 
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagGuzzaKilledTransient)) {	
				Player_Loses_Control();
				Loop_Actor_Walk_To_XYZ(kActorMcCoy, -248.0f, 44.0f, -390.0f, 12, true, false, false);
				Actor_Face_Actor(kActorMcCoy, kActorTransient, true);
				Delay(1000);
				Actor_Says(kActorMcCoy, 3970, 14); //00-3970.AUD	Hey.
				Music_Play(kMusicBRBlues, 52, 0, 2, -1, kMusicLoopPlayOnce, 1);
				Delay(2000);
				if (Player_Query_Agenda() == kPlayerAgendaPolite) {
					Actor_Says(kActorMcCoy, 2390, kAnimationModeIdle); //00-2390.AUD	Oh, God. No.
					Delay(1000);
				}
				Loop_Actor_Walk_To_Actor(kActorMcCoy, kActorTransient, 24, true, false);
				Player_Gains_Control();
				Actor_Face_Actor(kActorMcCoy, kActorTransient, true);
				Delay(2000);
				if (Player_Query_Agenda() == kPlayerAgendaPolite) {
					Actor_Says(kActorMcCoy, 2305, 13); //00-2305.AUD	I’m sorry.
				} else {
					Actor_Says(kActorMcCoy, 170, -1); //00-0170.AUD	Damn.
				}
				Actor_Change_Animation_Mode(kActorMcCoy, 23);
				Delay(3000);
				Item_Pickup_Spin_Effect_From_Actor(kModelAnimationOriginalRequisitionForm, kActorTransient, 0, 0);
				Actor_Says(kActorMcCoy, 8805, 13); //00-8805.AUD	A requisition form.
				Actor_Voice_Over(3950, kActorVoiceOver);
				Actor_Voice_Over(3960, kActorVoiceOver);
				Actor_Voice_Over(3970, kActorVoiceOver);
				Actor_Voice_Over(3980, kActorVoiceOver);
				Actor_Voice_Over(3990, kActorVoiceOver);
				Actor_Voice_Over(4000, kActorVoiceOver);
				Actor_Clue_Acquire(kActorMcCoy, kClueOriginalRequisitionForm, true, kActorTransient);
				Actor_Set_Targetable(kActorTransient, false);
				Game_Flag_Reset(kFlagGuzzaKilledTransient);
				Player_Gains_Control();
			}
		}
	} else if (Game_Flag_Query(kFlagUG15toUG13)) {
		Loop_Actor_Walk_To_XYZ(kActorMcCoy, -12.0f, 44.0f, -528.0f, 0, false, false, false);
		Game_Flag_Reset(kFlagUG15toUG13);
	} else {
		// arrived from elevator (going down)
		Loop_Actor_Walk_To_XYZ(kActorMcCoy, -60.0f, 55.24f, -816.0f, 0, false, false, false);
		Game_Flag_Reset(kFlagUG08toUG13);
		Player_Gains_Control();
	}

	if ( Actor_Query_Goal_Number(kActorTransient) >= 390
	 && !Game_Flag_Query(kFlagCT04HomelessKilledByMcCoy)
	) {
		if (!Game_Flag_Query(kFlagUG13Entered)) {
			if (!_vm->_cutContent) {
				Game_Flag_Set(kFlagUG13Entered);
			}
			Actor_Says(kActorTransient, 50, kAnimationModeTalk); // Hey, another one? ...
			// Made it so McCoy can't shoot the homeless guy. It doesn't make sense for McCoy to shoot a defenceless man that helped him.
			if (_vm->_cutContent) {
				Actor_Set_Targetable(kActorTransient, false);
			}
		} else {
			if (Random_Query(1, 3) == 1) {
				Actor_Set_Goal_Number(kActorTransient, 395);
			}
		}	
		// It never made any sense to me when McCoy calls Guzza and tells him to meet him in the sewers in the room with the round platform even though 
		// McCoy has never been there before. To fix his I have added a scene where when McCoy first enters the homeless mans place he hears a noise and goes 
		// towards the gate which is locked. In order to open the gate McCoy shoots the lock and walks into the room with the round platform and there is nothing 
		// there. Since this scene will always happen McCoys phone call with Guzza where he organises a meeting will always makes sense since McCoy will always 
		// see the room by default.	
		if (_vm->_cutContent && !Game_Flag_Query(kFlagUG13Entered)) {
			Sound_Play(kSfxBANGDOOR, 50, 0, 0, 50);
			Actor_Face_Heading(kActorMcCoy, 830, false);
			Delay (2000);
			Actor_Says(kActorMcCoy, 8525, 13); //00-8525.AUD	Hmph.
			Player_Loses_Control();
			Loop_Actor_Walk_To_XYZ(kActorMcCoy, -267.0f, 44.0f, -795.0f, 0, true, false, false);
			Footstep_Sound_Override_On(3);
			Loop_Actor_Travel_Stairs(kActorMcCoy, 11, true, kAnimationModeIdle);
			Footstep_Sound_Override_Off();
			if (Actor_Query_Goal_Number(kActorTransient) == 391
			|| Actor_Query_Goal_Number(kActorTransient) == 395
			|| Actor_Query_Goal_Number(kActorTransient) == 599) {
				Actor_Says(kActorMcCoy, 8522, 14); // Locked
				Delay(1000);
				Actor_Says(kActorMcCoy, 8525, 13); //00-8525.AUD	Hmph.
				Player_Set_Combat_Mode(true);
				Game_Flag_Set(kFlagUG13Entered);
			} else {
				Actor_Says(kActorMcCoy, 8522, 14); // Locked
				Actor_Face_Actor(kActorMcCoy, kActorTransient, true);
				Actor_Says(kActorMcCoy, 5555, 14); // How do I get this thing open?
				Actor_Says(kActorTransient, 60, 31); // Nah, it only happens when they want it to open.
				Actor_Face_Heading(kActorMcCoy, 830, false);
				Actor_Says(kActorMcCoy, 8525, 13); //00-8525.AUD	Hmph.
				Player_Set_Combat_Mode(true);
				Game_Flag_Set(kFlagUG13Entered);
			}				
			Set_Enter(kSetUG18, kSceneUG18);
		}
	}
	//return false;
}

void SceneScriptUG13::PlayerWalkedOut() {
	Actor_Set_Invisible(kActorMcCoy, false);
	Ambient_Sounds_Remove_All_Looping_Sounds(1u);
	if (Game_Flag_Query(kFlagUG13toUG08)) {
		Ambient_Sounds_Remove_Sound(kSfxYELL1M2,  false);
		Ambient_Sounds_Remove_Sound(kSfxYELL1M3,  false);
		Ambient_Sounds_Remove_Sound(kSfxGRUNT1M1, false);
		Ambient_Sounds_Remove_Sound(kSfxGRUNT2M2, false);
		Ambient_Sounds_Remove_Sound(kSfxGRUNT2M3, false);
	} else {
		Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
	}
}

void SceneScriptUG13::DialogueQueueFlushed(int a1) {
}

void SceneScriptUG13::talkAboutGuzza() {
	Actor_Clue_Acquire(kActorMcCoy, kClueHomelessManInterview2, false, kActorTransient);
	if (!_vm->_cutContent) {
		Actor_Modify_Friendliness_To_Other(kActorTransient, kActorMcCoy, -10);
	}
	Actor_Says(kActorTransient, 220, 30); // Bunch of times. Last time weren't that long ago.
	Actor_Says(kActorMcCoy, 5640, 19);    // What was he doing?
	if (_vm->_cutContent) {
		if (!Game_Flag_Query(kFlagGuzzaIsStupid)) {
			Actor_Says(kActorTransient, 230, 33); // Collecting guns like always.
			Player_Set_Combat_Mode(true);
			Actor_Says(kActorMcCoy, 5645, 16);    // Handguns? A blaster like mine?
			Player_Set_Combat_Mode(false);
			Actor_Says(kActorTransient, 240, 30); // Handguns, rifles. A whole armful. Took them through that gate.
			if (!Actor_Clue_Query(kActorMcCoy, kClueBigManLimping)) {
				Actor_Says(kActorTransient, 250, 33); // Dumped them it a sewer. They're gone now. You sure you ain't got nothing to drink?
			}
			Actor_Says(kActorMcCoy, 5650, 14);    // Can you describe him?
			Actor_Says(kActorTransient, 260, 32); // Eh, rough guy. Barks out orders a lot. Everybody listens when he's around. A natural.
		} else {
			Delay(2000);
			Actor_Says(kActorMcCoy, 3970, 14); //00-3970.AUD	Hey.
			Delay(1000);
			Actor_Says(kActorMcCoy, 5660, 13); // Stay with me for a minute, pal.
		}
		if (Actor_Clue_Query(kActorMcCoy, kClueBigManLimping)
		&& !Actor_Clue_Query(kActorMcCoy, kClueFolder)) {
			Player_Gains_Control();
			Loop_Actor_Walk_To_Actor(kActorMcCoy, kActorTransient, 36, false, true);
			Player_Loses_Control();
			Actor_Face_Actor(kActorMcCoy, kActorTransient, true);
			dialogueWithHomeless2();
		}
	} else {
		Actor_Says(kActorTransient, 230, 33); // Collecting guns like always.
		Actor_Says(kActorMcCoy, 5645, 16);    // Handguns? A blaster like mine?
		Actor_Says(kActorTransient, 240, 30); // Handguns, rifles. A whole armful. Took them through that gate.
		Actor_Says(kActorTransient, 250, 33); // Dumped them it a sewer. They're gone now. You sure you ain't got nothing to drink?
		Actor_Says(kActorMcCoy, 5650, 14);    // Can you describe him?
		Actor_Says(kActorTransient, 260, 32); // Eh, rough guy. Barks out orders a lot. Everybody listens when he's around. A natural.
	}	
}

void SceneScriptUG13::dialogueWithHomeless1() {
	Dialogue_Menu_Clear_List();
	DM_Add_To_List_Never_Repeat_Once_Selected(1320, 6, 3, 1); // OTHERS
	if (_vm->_cutContent) {
		if (Actor_Clue_Query(kActorMcCoy, kClueHomelessManInterview1)
		&& !Actor_Clue_Query(kActorMcCoy, kClueFolder)) {
			DM_Add_To_List_Never_Repeat_Once_Selected(1330, 5, 8, 5); // FAT MAN
		}
	} else if (Actor_Clue_Query(kActorMcCoy, kClueHomelessManInterview1)) {
		DM_Add_To_List_Never_Repeat_Once_Selected(1330, 5, 8, 5); // FAT MAN
	}
	if (_vm->_cutContent) {
		DM_Add_To_List_Never_Repeat_Once_Selected(1340, 8, 9, 6); // SEWERS
	} else {
		DM_Add_To_List_Never_Repeat_Once_Selected(1340, 2, 4, 6); // SEWERS
	}
	if (_vm->_cutContent) {
		if (Actor_Clue_Query(kActorMcCoy, kClueFlaskOfAbsinthe)
		&& Actor_Clue_Query(kActorMcCoy, kClueHomelessManInterview2)
		&& !Actor_Clue_Query(kActorMcCoy, kClueBigManLimping)
		&& !Actor_Clue_Query(kActorMcCoy, kClueFolder)) {
			DM_Add_To_List_Never_Repeat_Once_Selected(1350, 1, 2, 3); // GIVE FLASK
		}
	} else {
		if (Actor_Clue_Query(kActorMcCoy, kClueFlaskOfAbsinthe)) {
			DM_Add_To_List_Never_Repeat_Once_Selected(1350, 1, 3, 7); // GIVE FLASK
		}
	}
	Dialogue_Menu_Add_DONE_To_List(1360); // DONE

	Dialogue_Menu_Appear(320, 240);
	int answer = Dialogue_Menu_Query_Input();
	Dialogue_Menu_Disappear();

	switch (answer) {
	case 1320: // OTHERS
		Actor_Face_Actor(kActorMcCoy, kActorTransient, true);
		Actor_Clue_Acquire(kActorMcCoy, kClueHomelessManInterview1, false, kActorTransient);
		if (!_vm->_cutContent) {
			Actor_Modify_Friendliness_To_Other(kActorTransient, kActorMcCoy, -5);
		}
		Actor_Says(kActorMcCoy, 5575, 16); // You said another one...
		if (_vm->_cutContent) {
			Actor_Says(kActorMcCoy, 5580, 14); // A lot of people...?
		}
		Actor_Says(kActorTransient, 120, 31); // None of that are people...
		if (_vm->_cutContent) {
			// Added in a line.
			Actor_Says(kActorMcCoy, 1670, 16); //00-1670.AUD	Artificial?
			Actor_Says(kActorTransient, 380, 32); // Skin-jobs, okay?
		}
		Actor_Says(kActorMcCoy, 5610, 15); // How do you know...?
		Actor_Says(kActorTransient, 140, 32); // Are you kidding?
		if (_vm->_cutContent) {
			Actor_Says(kActorTransient, 150, 31); // Something funny about their eyes.
			if (Player_Query_Agenda() != kPlayerAgendaSurly 
			&& Player_Query_Agenda() != kPlayerAgendaErratic) {
				Actor_Says(kActorMcCoy, 4570, 18); //00-4570.AUD	Obviously. What did they look like?
			} else {
				Actor_Says(kActorMcCoy, 5615, 14); // Describe them...
			}
		} else {
			Actor_Says(kActorMcCoy, 5615, 18); // Describe them...
		}
		if (_vm->_cutContent) {
			if (!Actor_Clue_Query(kActorMcCoy, kClueBigManLimping)) {
				Actor_Says(kActorTransient, 160, 33); // Sure you don't got that drink?
				Actor_Says(kActorMcCoy, 5620, 9); // Maybe later
			} 
		} else {
			Actor_Says(kActorTransient, 160, 33); // Sure you don't got that drink?
			Actor_Says(kActorMcCoy, 5620, 9); // Maybe later
		}
		Actor_Says(kActorTransient, 170, 30); //Well, there's the Japanese guy with the coat and the glasses.
		Actor_Says(kActorMcCoy, 5625, 12); // Skinny...?
		Actor_Says(kActorTransient, 180, 32); // Yeah! And the guy with the muscles and the funny hair.
		Actor_Says(kActorMcCoy, 5630, 18); // Dreadlocks?
		Actor_Says(kActorTransient, 190, 32); // Right! Seen them twice. And a two headed guy and a fat man.
		// Made it so if McCoy never interacted with the homeless man in act 1 he doesn't mention chasing Zuben since the homeless man wouldn't know. McCoy now simply asks if he knows him.
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagCT04HomelessTalk)) {
				Actor_Says(kActorMcCoy, 5635, 15); //00-5635.AUD	Fat man? The one I was chasing from the sushi bar.
			} else {
				Actor_Says(kActorMcCoy, 3230, 15); //00-3230.AUD	You know the chef at Howie’s?
			}
		} else {
			Actor_Says(kActorMcCoy, 5635, 15); //00-5635.AUD	Fat man? The one I was chasing from the sushi bar.
		} 
		Actor_Says(kActorTransient, 200, 31); // Nah, the other fat man. You know him.
		if (_vm->_cutContent) {
			Actor_Says(kActorTransient, 210, 31); // Saw him wail...
		}
		break;

	case 1330: // FAT MAN
		Actor_Says(kActorMcCoy, 5585, 16); // How many times have you seen the fat man down here?
		talkAboutGuzza();
		break;

	case 1340: // SEWERS
		if (!_vm->_cutContent) {
			Actor_Modify_Friendliness_To_Other(kActorTransient, kActorMcCoy, -10);
		}
		Actor_Says(kActorMcCoy, 5590, 15); // This is where...?
		Actor_Says(kActorTransient, 270, 31); // You could call it that.
		Actor_Says(kActorMcCoy, 5655, 16); // You know your way...?
		if (_vm->_cutContent) {
			if (!Actor_Clue_Query(kActorMcCoy, kClueBigManLimping)) {
				Actor_Says(kActorTransient, 280, 32); // You got anything to drink? My throat's awful dry.
			} else {
				Delay(2000);
				Actor_Says(kActorMcCoy, 5660, 13); // Stay with me for a minute, pal.
			}
		} else {
			Actor_Says(kActorTransient, 280, 32); // You got anything to drink? My throat's awful dry.
		}
		break;

	case 1350: // GIVE FLASK
	// Made it so McCoy walks around to the front of the couch so he can give transient the flask.
		if (_vm->_cutContent) {
			Player_Loses_Control();
			Loop_Actor_Walk_To_Actor(kActorMcCoy, kActorTransient, 36, false, true);
			Actor_Face_Actor(kActorMcCoy, kActorTransient, true);
			Player_Gains_Control();
		}
		Actor_Clue_Acquire(kActorTransient, kClueFlaskOfAbsinthe, false, kActorMcCoy);
		if (_vm->_cutContent) {
			Actor_Says_With_Pause(kActorMcCoy, 5595, 1.0f, 13); // You still thirsty, pal?
		} else {
			Actor_Says_With_Pause(kActorMcCoy, 5595, 1.0f, 23); // You still thirsty, pal?
		}
		if (_vm->_cutContent) {
			Actor_Change_Animation_Mode(kActorMcCoy, 23);
			Delay(800);
			Item_Pickup_Spin_Effect_From_Actor(kModelAnimationFlaskOfAbsinthe, kActorTransient, 0, 0);
			Actor_Says(kActorTransient, 290, 32); // Mucho obligado, senor.
		} else {
			Item_Pickup_Spin_Effect(kModelAnimationFlaskOfAbsinthe, 193, 325);
			Actor_Says(kActorTransient, 290, 33); // Mucho obligado, senor.
		}
		if (!_vm->_cutContent) {
			Actor_Says(kActorMcCoy, 5660, 13); // Stay with me for a minute, pal.
		}
		Actor_Clue_Lose(kActorMcCoy, kClueFlaskOfAbsinthe);
		dialogueWithHomeless2();
		break;

	case 1360: // DONE
		return;

	default:
		Actor_Face_Actor(kActorMcCoy, kActorTransient, true);
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagTransientDead)) {
				if (Player_Query_Agenda() == kPlayerAgendaSurly 
				|| Player_Query_Agenda() == kPlayerAgendaErratic) {
					Actor_Says(kActorMcCoy, 8665, 13); //00-8665.AUD	Disgusting.
				} else if (Player_Query_Agenda() == kPlayerAgendaPolite) {
					Delay(1000);
					Actor_Says(kActorMcCoy, 2305, 13); //00-2305.AUD	I’m sorry.
					Delay(1000);
				} else {
					Actor_Says(kActorMcCoy, 8630, 12);  // What a waste
				}
			} else {
				Actor_Says(kActorMcCoy, 5600, 14);               // Let me ask you
				Actor_Says(kActorTransient, 100, 53);            // sleeping, mumbling
				Actor_Says(kActorMcCoy, 5605, 18);               // I'm talking to you...
				Actor_Start_Speech_Sample(kActorTransient, 110); // sleeping, mumbling
				Actor_Set_Goal_Number(kActorTransient, 395);
			}
		} else {
			Actor_Says(kActorMcCoy, 5600, 14);               // Let me ask you
			Actor_Says(kActorTransient, 100, 53);            // sleeping, mumbling
			Actor_Says(kActorMcCoy, 5605, 18);               // I'm talking to you...
			Actor_Start_Speech_Sample(kActorTransient, 110); // sleeping, mumbling
			Actor_Set_Goal_Number(kActorTransient, 395);
		}
		break;
	}
}

void SceneScriptUG13::dialogueWithHomeless2() {
	// This occurs after the homeless guy gets the flask of absinthe
	// Note: McCoy can only ask one item from the dialogue menu
	Actor_Set_Friendliness_To_Other(kActorTransient, kActorMcCoy, 40);
	Dialogue_Menu_Clear_List();
	if (_vm->_cutContent) {
		DM_Add_To_List_Never_Repeat_Once_Selected(1370, 6, 1, 1); // DIRECTIONS
		if (!Actor_Clue_Query(kActorMcCoy, kClueFolder)) {
			DM_Add_To_List_Never_Repeat_Once_Selected(1380, 9, 8, 7); // FAT MAN
		}
	} else {
		DM_Add_To_List_Never_Repeat_Once_Selected(1370, 1, 1, 8); // DIRECTIONS
		DM_Add_To_List_Never_Repeat_Once_Selected(1380, 1, 8, 1); // FAT MAN
	}
	if (_vm->_cutContent) {
		if (!Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
			DM_Add_To_List_Never_Repeat_Once_Selected(1390, 1, 2, 6); // REPLICANTS
		}
	} else {
		DM_Add_To_List_Never_Repeat_Once_Selected(1390, 8, 1, 1); // REPLICANTS
	}
	Dialogue_Menu_Appear(320, 240);
	int answer = Dialogue_Menu_Query_Input();
	Dialogue_Menu_Disappear();

	switch (answer) {
	// After McCoy gives the transient the flask and selects one of the three options Guzza will shoot the transient before he can reveal the trutch and McCoy chases after Guzza.
	// This outcome can be avoided if you have high friendliness with Guzza by either retiring Zuben and talking to Guzza about it or giving Guzza holdens badge. 
	case 1370: // DIRECTIONS
		if (_vm->_cutContent) {
			if (Actor_Query_Friendliness_To_Other(kActorGuzza, kActorMcCoy) < 51) {
				Actor_Says(kActorMcCoy, 5665, 16); // This place is a maze
				Actor_Says(kActorTransient, 300, 32); // This is the sewers, man.
				Player_Loses_Control();
				Music_Play(kMusicMoraji, 71, 0, 0, -1, kMusicLoopPlayOnce, 2);
				Sound_Play(kSfxLGCAL3, 100, 0, 0, 50);
				Actor_Set_Goal_Number(kActorTransient, kGoalGuzzaShootsTransient);
				Delay(500);
				Player_Set_Combat_Mode(true);
				Delay(1000);
				Sound_Play(kSfxLGCAL3, 100, 0, 0, 50);
				Actor_Change_Animation_Mode(kActorMcCoy, 21);
				Delay(1000);
				Actor_Change_Animation_Mode(kActorMcCoy, 6);
				Sound_Play(kSfxGUNH1A, 100, 0, 0, 50);
				Delay(1000);
				Loop_Actor_Walk_To_Actor(kActorMcCoy, kActorTransient, 36, false, true);
				Loop_Actor_Walk_To_XYZ(kActorMcCoy, -267.0f, 44.0f, -795.0f, 0, true, false, false);
				Actor_Face_Heading(kActorMcCoy, 830, false);
				Footstep_Sound_Override_On(3);
				Loop_Actor_Travel_Stairs(kActorMcCoy, 11, true, kAnimationModeIdle);
				Footstep_Sound_Override_Off();
				Loop_Actor_Walk_To_XYZ(kActorMcCoy, -477.0f, 141.9f, -870.0f, 0, false, false, false);
				Actor_Set_Goal_Number(kActorTransient, 599);
				Game_Flag_Set(kFlagGuzzaKilledTransient);
				Game_Flag_Set(kFlagTransientDead);
				Set_Enter(kSetUG18, kSceneUG18);
			} else {
				Actor_Says(kActorMcCoy, 5665, 16); // This place is a maze
				Actor_Says(kActorTransient, 300, 32); // This is the sewers, man.
				Actor_Says(kActorMcCoy, 5680, 19); // So what? I just follow my nose?
				Actor_Says(kActorTransient, 310, 33); // Noses get a little overworked down here.
				Actor_Says(kActorTransient, 330, 30); // You can get to it all from down here.
				Actor_Says(kActorMcCoy, 4130, 18); //00-4130.AUD	Anything else?
				Delay(1000);
				Actor_Says(kActorMcCoy, 8990, 13); //00-8990.AUD	What have you got there?
				Actor_Change_Animation_Mode(kActorMcCoy, 23);
				Delay(800);
				Actor_Clue_Acquire(kActorMcCoy, kClueOriginalRequisitionForm, true, kActorTransient);
				Item_Remove_From_World(kItemWeaponsOrderForm);
				Item_Pickup_Spin_Effect_From_Actor(kModelAnimationOriginalRequisitionForm, kActorMcCoy, 0, 0);
				Delay(800);
				Actor_Says(kActorMcCoy, 8805, 19); //00-8805.AUD	A requisition form.
				Actor_Voice_Over(3950, kActorVoiceOver);
				Actor_Voice_Over(3960, kActorVoiceOver);
				Actor_Voice_Over(3970, kActorVoiceOver);
				Actor_Voice_Over(3980, kActorVoiceOver);
				Actor_Voice_Over(3990, kActorVoiceOver);
				Actor_Voice_Over(4000, kActorVoiceOver);
				Delay(1000);
				Player_Gains_Control();
				Actor_Says(kActorMcCoy, 5600, 14);               // Let me ask you
				Actor_Says(kActorTransient, 100, 30); // sleeping, mumbling
				Actor_Says(kActorMcCoy, 5605, 18);               // I'm talking to you...
				Actor_Start_Speech_Sample(kActorTransient, 110); // sleeping, mumbling
				Actor_Set_Goal_Number(kActorTransient, 395);
				if (Player_Query_Agenda() == kPlayerAgendaSurly 
				|| Player_Query_Agenda() == kPlayerAgendaErratic) {
					Actor_Voice_Over(3760, kActorVoiceOver); //99-3760.AUD	Sloth was practically a new religion around here.
					Actor_Says(kActorMcCoy, 5685, 18); // Triple-A...
					Actor_Says(kActorTransient, 420, 30); //12-0420.AUD	Don’t care what you think.
				}
			}
		} else {
			Actor_Says(kActorMcCoy, 5665, 16); // This place is a maze
			Actor_Says(kActorTransient, 300, 32); // This is the sewers, man.
			Actor_Says(kActorMcCoy, 5680, 19); // So what? I just follow my nose?
			Actor_Says(kActorTransient, 310, 33); // Noses get a little overworked down here.
			Actor_Says(kActorTransient, 330, 30); // You can get to it all from down here.
			Actor_Start_Speech_Sample(kActorTransient, 110); // sleeping, mumbling
			Actor_Set_Goal_Number(kActorTransient, 395);
			Actor_Says(kActorMcCoy, 5685, 18); // Triple-A...
			Actor_Says(kActorTransient, 420, 30); //12-0420.AUD	Don’t care what you think.
		}
		break;

	case 1380: // FAT MAN
		if (_vm->_cutContent) {
			Actor_Says(kActorMcCoy, 5670, 9); // About that fat man you saw.
			// Added in some lines.
			Actor_Says(kActorTransient, 390, 31); //12-0390.AUD	Don’t know why you’d wanna know this but, yeah, I heard something
			if (Actor_Query_Friendliness_To_Other(kActorGuzza, kActorMcCoy) < 51) {
				Player_Loses_Control();
				Music_Play(kMusicMoraji, 71, 0, 0, -1, kMusicLoopPlayOnce, 2);
				Sound_Play(kSfxLGCAL3, 100, 0, 0, 50);
				Actor_Set_Goal_Number(kActorTransient, kGoalGuzzaShootsTransient);
				Delay(500);
				Player_Set_Combat_Mode(true);
				Delay(1000);
				Sound_Play(kSfxLGCAL3, 100, 0, 0, 50);
				Actor_Change_Animation_Mode(kActorMcCoy, 21);
				Delay(1000);
				Actor_Change_Animation_Mode(kActorMcCoy, 6);
				Sound_Play(kSfxGUNH1A, 100, 0, 0, 50);
				Delay(1000);
				Loop_Actor_Walk_To_Actor(kActorMcCoy, kActorTransient, 36, false, true);
				Loop_Actor_Walk_To_XYZ(kActorMcCoy, -267.0f, 44.0f, -795.0f, 0, true, false, false);
				Actor_Face_Heading(kActorMcCoy, 830, false);
				Footstep_Sound_Override_On(3);
				Loop_Actor_Travel_Stairs(kActorMcCoy, 11, true, kAnimationModeIdle);
				Footstep_Sound_Override_Off();
				Loop_Actor_Walk_To_XYZ(kActorMcCoy, -477.0f, 141.9f, -870.0f, 0, false, false, false);
				Actor_Set_Goal_Number(kActorTransient, 599);
				Game_Flag_Set(kFlagGuzzaKilledTransient);
				Game_Flag_Set(kFlagTransientDead);
				Set_Enter(kSetUG18, kSceneUG18);
			} else {
				Actor_Says(kActorMcCoy, 2635, 18); //00-2635.AUD	I’m all ears.
				Actor_Says(kActorTransient, 340, 31); // You're "kid".
				Actor_Says(kActorMcCoy, 5690, 19); // Huh?
				Actor_Says(kActorTransient, 350, 32); // No, you're his kid. That's what it is.
				Actor_Says(kActorMcCoy, 5695, 14); // How's that?
				if (Player_Query_Agenda() != kPlayerAgendaPolite) {
					Delay (1000);
					Actor_Says(kActorMcCoy, 3910, 9); //00-3910.AUD	You’re lying.
					Actor_Says(kActorTransient, 430, 31); //12-0430.AUD	Half truth is all, eh, half truth. Here’s the real deal. Plain truth, okay?
					Actor_Says(kActorMcCoy, 4940, 9); //00-4940.AUD	Okay, let's have it.
				}
				Actor_Says(kActorTransient, 360, 33); // Hell, I seen you guys together. Three weeks ago.
				Actor_Voice_Over(2710, kActorVoiceOver);
				Actor_Voice_Over(2730, kActorVoiceOver);
				Actor_Voice_Over(4410, kActorVoiceOver); //99-4410.AUD	Guzza must have a little something going on the side.
				Actor_Clue_Acquire(kActorMcCoy, kClueHomelessManKid, false, kActorTransient);
				Actor_Says(kActorMcCoy, 4130, 18); //00-4130.AUD	Anything else?
				Delay(1000);
				Actor_Says(kActorMcCoy, 8990, 13); //00-8990.AUD	What have you got there?
				Actor_Change_Animation_Mode(kActorMcCoy, 23);
				Delay(800);
				Actor_Clue_Acquire(kActorMcCoy, kClueOriginalRequisitionForm, true, kActorTransient);
				Item_Remove_From_World(kItemWeaponsOrderForm);
				Item_Pickup_Spin_Effect_From_Actor(kModelAnimationOriginalRequisitionForm, kActorMcCoy, 0, 0);
				Delay(800);
				Actor_Says(kActorMcCoy, 8805, 19); //00-8805.AUD	A requisition form.
				Actor_Voice_Over(3950, kActorVoiceOver);
				Actor_Voice_Over(3960, kActorVoiceOver);
				Actor_Voice_Over(3970, kActorVoiceOver);
				Actor_Voice_Over(3980, kActorVoiceOver);
				Actor_Voice_Over(3990, kActorVoiceOver);
				Actor_Voice_Over(4000, kActorVoiceOver);
				Delay(1000);
				Player_Gains_Control();
				Actor_Says(kActorMcCoy, 5600, 14);               // Let me ask you
				Actor_Says(kActorTransient, 100, 30); // sleeping, mumbling
				Actor_Says(kActorMcCoy, 5605, 18);               // I'm talking to you...
				Actor_Start_Speech_Sample(kActorTransient, 110); // sleeping, mumbling
				Actor_Set_Goal_Number(kActorTransient, 395);
				if (Player_Query_Agenda() == kPlayerAgendaSurly 
				|| Player_Query_Agenda() == kPlayerAgendaErratic) {
					Actor_Voice_Over(3760, kActorVoiceOver); //99-3760.AUD	Sloth was practically a new religion around here.
					Actor_Says(kActorMcCoy, 5685, 18); // Triple-A...
					Actor_Says(kActorTransient, 420, 30); //12-0420.AUD	Don’t care what you think.
				}
			}
		} else if (Actor_Clue_Query(kActorMcCoy, kClueHomelessManInterview2)) {
			Actor_Says(kActorMcCoy, 5670, 9); // About that fat man you saw.
			Actor_Says(kActorTransient, 340, 31); // You're "kid".
			Actor_Says(kActorMcCoy, 5690, 19); // Huh?
			Actor_Says(kActorTransient, 350, 32); // No, you're his kid. That's what it is.
			Actor_Says(kActorMcCoy, 5695, 14); // How's that?
			Actor_Says(kActorTransient, 360, 33); // Hell, I seen you guys together. Three weeks ago.
			Actor_Voice_Over(2710, kActorVoiceOver);
			Actor_Voice_Over(2730, kActorVoiceOver);
			Actor_Clue_Acquire(kActorMcCoy, kClueHomelessManKid, false, kActorTransient);
		} else {
			// McCoy could also have asked about "Fat Man" before he gives the flask of absinthe
			// to the homeless man. But if he didn't then he'll only get the same conversation
			// that he would have got without giving him the flask.
#if BLADERUNNER_ORIGINAL_BUGS
#else
			// Re-use this line here, so the question is not so abrupt
			Actor_Says(kActorMcCoy, 5670, 9); // About that fat man you saw.
#endif // BLADERUNNER_ORIGINAL_BUGS
			Actor_Says(kActorMcCoy, 5700, 15); // He been down here a lot?
			talkAboutGuzza();
		}
		break;

	case 1390: // REPLICANTS
		if (_vm->_cutContent) {
			if (Actor_Query_Friendliness_To_Other(kActorGuzza, kActorMcCoy) < 51) {
				Actor_Says(kActorMcCoy, 5675, 9); // You say this place is crawling with Reps...
				Actor_Says(kActorTransient, 370, 32); // They ain't too bad. You don't mess with them, they don't mess with you.
				Player_Loses_Control();
				Music_Play(kMusicMoraji, 71, 0, 0, -1, kMusicLoopPlayOnce, 2);
				Sound_Play(kSfxLGCAL3, 100, 0, 0, 50);
				Actor_Set_Goal_Number(kActorTransient, kGoalGuzzaShootsTransient);
				Delay(500);
				Player_Set_Combat_Mode(true);
				Delay(1000);
				Sound_Play(kSfxLGCAL3, 100, 0, 0, 50);
				Actor_Change_Animation_Mode(kActorMcCoy, 21);
				Delay(1000);
				Actor_Change_Animation_Mode(kActorMcCoy, 6);
				Sound_Play(kSfxGUNH1A, 100, 0, 0, 50);
				Delay(1000);
				Loop_Actor_Walk_To_Actor(kActorMcCoy, kActorTransient, 36, false, true);
				Loop_Actor_Walk_To_XYZ(kActorMcCoy, -267.0f, 44.0f, -795.0f, 0, true, false, false);
				Actor_Face_Heading(kActorMcCoy, 830, false);
				Footstep_Sound_Override_On(3);
				Loop_Actor_Travel_Stairs(kActorMcCoy, 11, true, kAnimationModeIdle);
				Footstep_Sound_Override_Off();
				Loop_Actor_Walk_To_XYZ(kActorMcCoy, -477.0f, 141.9f, -870.0f, 0, false, false, false);
				Actor_Set_Goal_Number(kActorTransient, 599);
				Game_Flag_Set(kFlagGuzzaKilledTransient);
				Game_Flag_Set(kFlagTransientDead);
				Set_Enter(kSetUG18, kSceneUG18);
			} else {
				Actor_Says(kActorMcCoy, 5675, 9); // You say this place is crawling with Reps...
				Actor_Says(kActorTransient, 370, 32); // They ain't too bad. You don't mess with them, they don't mess with you.
				Actor_Says(kActorMcCoy, 5705, 10); // Uh-huh.
				Actor_Says(kActorMcCoy, 4130, 18); //00-4130.AUD	Anything else?
				Delay(1000);
				Actor_Says(kActorMcCoy, 8990, 13); //00-8990.AUD	What have you got there?
				Actor_Change_Animation_Mode(kActorMcCoy, 23);
				Delay(800);
				Actor_Clue_Acquire(kActorMcCoy, kClueOriginalRequisitionForm, true, kActorTransient);
				Item_Remove_From_World(kItemWeaponsOrderForm);
				Item_Pickup_Spin_Effect_From_Actor(kModelAnimationOriginalRequisitionForm, kActorMcCoy, 0, 0);
				Delay(800);
				Actor_Says(kActorMcCoy, 8805, 19); //00-8805.AUD	A requisition form.
				Actor_Voice_Over(3950, kActorVoiceOver);
				Actor_Voice_Over(3960, kActorVoiceOver);
				Actor_Voice_Over(3970, kActorVoiceOver);
				Actor_Voice_Over(3980, kActorVoiceOver);
				Actor_Voice_Over(3990, kActorVoiceOver);
				Actor_Voice_Over(4000, kActorVoiceOver);
				Delay(1000);
				Player_Gains_Control();
				Actor_Says(kActorMcCoy, 5600, 14);               // Let me ask you
				Actor_Says(kActorTransient, 100, 30); // sleeping, mumbling
				Actor_Says(kActorMcCoy, 5605, 18);               // I'm talking to you...
				Actor_Start_Speech_Sample(kActorTransient, 110); // sleeping, mumbling
				Actor_Set_Goal_Number(kActorTransient, 395);
				if (Player_Query_Agenda() == kPlayerAgendaSurly 
				|| Player_Query_Agenda() == kPlayerAgendaErratic) {
					Actor_Voice_Over(3760, kActorVoiceOver); //99-3760.AUD	Sloth was practically a new religion around here.
					Actor_Says(kActorMcCoy, 5685, 18); // Triple-A...
					Actor_Says(kActorTransient, 420, 30); //12-0420.AUD	Don’t care what you think.
				}
			}
		} else {
			Actor_Says(kActorMcCoy, 5675, 9); // You say this place is crawling with Reps...
			Actor_Says(kActorTransient, 370, 32); // They ain't too bad. You don't mess with them, they don't mess with you.
			Actor_Says(kActorMcCoy, 5705, 10); // Uh-huh.
		}
		break;
	}
}

} // End of namespace BladeRunner
