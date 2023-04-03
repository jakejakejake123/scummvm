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

void SceneScriptKP05::InitializeScene() {
	if (Game_Flag_Query(kFlagKP06toKP05)) {
		Setup_Scene_Information( -868.0f, 0.0f, -68.0f, 520);
	} else if (Game_Flag_Query(kFlagKP04toKP05)) {
		Setup_Scene_Information(-1142.0f, 0.0f, 932.0f, 276);
	} else {
		Setup_Scene_Information( -802.0f, 0.0f, 972.0f, 800);
	}

	Scene_Exit_Add_2D_Exit(0, 589, 0, 639, 479, 1);
	Scene_Exit_Add_2D_Exit(1,   0, 0,  30, 479, 3);
	Scene_Exit_Add_2D_Exit(2,   0, 0, 257, 204, 0);

	Ambient_Sounds_Add_Looping_Sound(kSfxKPAMB1,   34, 1, 1);
	Ambient_Sounds_Add_Looping_Sound(kSfxSKINBED1, 27, 1, 1);
	Ambient_Sounds_Add_Looping_Sound(kSfxRUMLOOP1, 90, 1, 1);
	Ambient_Sounds_Add_Sound(kSfxSCARY1,  2, 100, 25,  33, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSCARY2,  2, 100, 25,  33, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSCARY3,  2, 100, 25,  33, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxTHNDER2, 5, 180, 50, 100, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxTHNDER3, 5, 180, 50, 100, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxTHNDER4, 5, 180, 50, 100, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSCARY4,  2, 100, 25,  33, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSCARY5,  2, 100, 25,  33, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSCARY6,  2, 100, 25,  33, -100, 100, -101, -101, 0, 0);
}

void SceneScriptKP05::SceneLoaded() {
	Unobstacle_Object("OBSTACLEBOX20", true);
	Clickable_Object("BRIDGE02");
	Unclickable_Object("BRIDGE02");

	if (!Actor_Clue_Query(kActorMcCoy, kCluePowerSource)
	 &&  Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)
	) {
		if (_vm->_cutContent) {
			if (Actor_Query_Intelligence(kActorSadik) == 70) {
				Item_Add_To_World(kItemPowerSource, kModelAnimationPowerSource, kSetKP05_KP06, -1095.0f, 0.0f, 770.0f, 256, 24, 24, false, true, false, true);
			}
		} else {
			Item_Add_To_World(kItemPowerSource, kModelAnimationPowerSource, kSetKP05_KP06, -1095.0f, 0.0f, 770.0f, 256, 24, 24, false, true, false, true);
		}
	}
}

bool SceneScriptKP05::MouseClick(int x, int y) {
	return false;
}

bool SceneScriptKP05::ClickedOn3DObject(const char *objectName, bool a2) {
	return false;
}

bool SceneScriptKP05::ClickedOnActor(int actorId) {
	return false;
}

bool SceneScriptKP05::ClickedOnItem(int itemId, bool a2) {
	if (itemId == kItemPowerSource) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -1058.0f, 0.0f, 852.0f, 0, true, false, false)) {
			Actor_Face_Item(kActorMcCoy, kItemPowerSource, true);
			if (_vm->_cutContent) {
				if (Actor_Query_Goal_Number(kActorSadik) == kGoalSadikKP06NeedsReactorCoreFromMcCoy) {
					Actor_Clue_Acquire(kActorMcCoy, kCluePowerSource, true, -1);
					Item_Remove_From_World(kItemPowerSource);
					Item_Pickup_Spin_Effect(kModelAnimationPowerSource, 58, 321);
					Actor_Says(kActorMcCoy, 8885, 13); //00-8885.AUD	A power source.
					Actor_Says(kActorMcCoy, 8495, 15); //00-8495.AUD	This might work.
				} else {
					Actor_Says(kActorMcCoy, 8885, 13); //00-8885.AUD	A power source.
					Actor_Says(kActorMcCoy, 8525, -1); // 00-8525.AUD	Hmph
				}
			} else {
				Actor_Clue_Acquire(kActorMcCoy, kCluePowerSource, true, -1);
				Item_Remove_From_World(kItemPowerSource);
				Item_Pickup_Spin_Effect(kModelAnimationPowerSource, 58, 321);
			}
		}
	}
	return false;
}

bool SceneScriptKP05::ClickedOnExit(int exitId) {
	if (exitId == 0) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -802.0f, 0.0f, 972.0f, 0, true, false, false)) {
			Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
			Ambient_Sounds_Remove_All_Looping_Sounds(1u);
			Game_Flag_Set(kFlagKP05toKP03);
			Set_Enter(kSetKP03, kSceneKP03);
		}
		return true;
	}

	if (exitId == 1) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -1142.0f, 0.0f, 932.0f, 0, true, false, false)) {
			Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
			Ambient_Sounds_Remove_All_Looping_Sounds(1u);
			Game_Flag_Set(kFlagKP05toKP04);
			Set_Enter(kSetKP04, kSceneKP04);
		}
		return true;
	}

	if (exitId == 2) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -868.0f, 0.0f, -68.0f, 0, true, false, false)) {
			Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
			Ambient_Sounds_Remove_All_Looping_Sounds(1u);
			Game_Flag_Set(kFlagKP05toKP06);
			Async_Actor_Walk_To_XYZ(kActorMcCoy, -868.0f, 0.0f, -216.0f, 0, false);
			Set_Enter(kSetKP05_KP06, kSceneKP06);
		}
		return true;
	}
	return false;
}

bool SceneScriptKP05::ClickedOn2DRegion(int region) {
	return false;
}

void SceneScriptKP05::SceneFrameAdvanced(int frame) {
}

void SceneScriptKP05::ActorChangedGoal(int actorId, int newGoal, int oldGoal, bool currentSet) {
	if (_vm->_cutContent) {
		if (actorId == kActorSteele
		&& oldGoal != kGoalSteeleGone
		&& newGoal == kGoalSteeleGone
		) {
			Loop_Actor_Walk_To_Actor(kActorMcCoy, kActorSteele, 24, false, false);
			Actor_Face_Actor(kActorMcCoy, kActorSteele, true);
			Actor_Says(kActorSteele, 250, -1); //01-0250.AUD	(cough) Nice shot there, Slim.
			Actor_Says(kActorMcCoy, 2120, -1); //00-2120.AUD	You couldn’t leave well enough alone.
			Actor_Says(kActorSteele, 410, -1); //01-0410.AUD	My job… had my orders.
			Actor_Says(kActorMcCoy, 2170, -1); //00-2170.AUD	And my animal? Guzza tell you to get rid of her? Or did you do that on your own?
			Actor_Says(kActorSteele, 420, -1); //01-0420.AUD	Eat shit, Slim.
			Scene_Exits_Enable();
		}
	}
}

void SceneScriptKP05::PlayerWalkedIn() {
	if (Game_Flag_Query(kFlagKP06toKP05)) {
		Game_Flag_Reset(kFlagKP06toKP05);
	} else if (Game_Flag_Query(kFlagKP04toKP05)) {
		// Made it so McCoy appears in the set instantly so when Steele confronts him in the Clovis ending she doesn't teleport into the set.
		if (_vm->_cutContent) {
			Actor_Set_At_XYZ(kActorMcCoy, -1110.0f, 0.0f, 932.0f, 0);
			Game_Flag_Reset(kFlagKP04toKP05);
		} else {
			Loop_Actor_Walk_To_XYZ(kActorMcCoy, -1110.0f, 0.0f, 932.0f, 0, false, false, false);
			Game_Flag_Reset(kFlagKP04toKP05);
		}
	} else if (_vm->_cutContent) {
		Actor_Set_At_XYZ(kActorMcCoy, -846.0f, 0.0f, 972.0f, 0);
	} else {
		Loop_Actor_Walk_To_XYZ(kActorMcCoy, -846.0f, 0.0f, 972.0f, 0, false, false, false);
		Game_Flag_Query(kFlagKP03toKP05); // bug in game?
	}

	if (Actor_Query_Goal_Number(kActorMaggie) == kGoalMaggieKP05Wait) {
		Actor_Set_Goal_Number(kActorMaggie, kGoalMaggieKP05McCoyEntered);
	}
	// Changed the conditions for which Steele will confront McCoy during the Clovis ending.
	if (_vm->_cutContent) {
		if (Actor_Query_Goal_Number(kActorSteele) < kGoalSteeleGone
		&& Actor_Query_Goal_Number(kActorMaggie) != kGoalMaggieKP05Wait) {
			if (!Game_Flag_Query(kFlagMcCoyIsInnocent)) {
				Actor_Put_In_Set(kActorSteele, kSetKP05_KP06);
				Actor_Set_At_XYZ(kActorSteele, -947.39f, 0.0f, 728.89f, 0);
				Actor_Change_Animation_Mode(kActorSteele, kAnimationModeCombatIdle);
				Scene_Exits_Disable();
				Actor_Face_Actor(kActorSteele, kActorMcCoy, true);
				Actor_Face_Actor(kActorMcCoy, kActorSteele, true);
				Actor_Says(kActorSteele, 530, 15); //01-0530.AUD	You almost got away with it, Slim.
				Actor_Says(kActorSteele, 540, 16); //01-0540.AUD	And I expected so much more from you.
				Player_Set_Combat_Mode(true);
				Actor_Says(kActorMcCoy, 2200, 3); //00-2200.AUD	Why did you have to kill her?
				if (!Game_Flag_Query(kFlagMcCoyIsInnocent)) {
					Actor_Says(kActorSteele, 550, 17); //01-0550.AUD	Who, the mutt? The artificial pet of a Replicant? What'd you think I’d do?
					Actor_Says(kActorMcCoy, 2205, 3); //00-2205.AUD	Show some mercy?
					Actor_Says(kActorSteele, 560, 15); //01-0560.AUD	Well, I guess that’s why you’re there and I’m here.
				} else {
					Actor_Says(kActorSteele, 330, 15); //01-0330.AUD	Nobody gives a damn.
				}
				Delay(1000);
				Actor_Says(kActorSteele, 570, 16); //01-0570.AUD	Now, why don’t you explain to me what you’re doing out here, Slim.
				Actor_Says(kActorSteele, 580, 13); //01-0580.AUD	Maybe you can ease my suspicious mind.
				if (Player_Query_Agenda() != kPlayerAgendaPolite) {
					Actor_Says(kActorMcCoy, 2210, 3); //00-2210.AUD	I’m just checking it out.
					Actor_Says(kActorSteele, 590, 13); //01-0590.AUD	Just doing a little sightseeing?
					Actor_Says(kActorMcCoy, 2215, 3); //00-2215.AUD	That’s right.
					if (!Game_Flag_Query(kFlagMcCoyIsInnocent)) {
						Actor_Says(kActorSteele, 600, 16); //01-0600.AUD	Right. And not fifty yards from your pal Clovis and the moonbus you hijacked.
					}
					Actor_Says(kActorSteele, 610, 15); //01-0610.AUD	You’re not convincing me too good, Slim.
				} else {
					Delay(2000);
					Actor_Says(kActorSteele, 610, 15); //01-0610.AUD	You’re not convincing me too good, Slim.
				}
				Actor_Says(kActorMcCoy, 2220, 3); //00-2220.AUD	You gonna shoot me down right here?
				if (!Game_Flag_Query(kFlagMcCoyIsInnocent)) {
					Actor_Says(kActorSteele, 630, 17); //01-0630.AUD	Maybe you wanna go on the Machine now? See if you can answer this question.
				} else {
					Actor_Says(kActorSteele, 620, 15); //01-0620.AUD	It’s as good a place as any.
				}
				// Added in some action music for your fight with Crystal.
				if (_vm->_cutContent) {
					if (Actor_Query_Goal_Number(kActorSadik) < kGoalSadikGone) {
						Actor_Set_Goal_Number(kActorSadik, 414);
					}
					Music_Play(kMusicMoraji, 71, 0, 0, -1, kMusicLoopPlayOnce, 2);
				}
				Non_Player_Actor_Combat_Mode_On(kActorSteele, kActorCombatStateIdle, true, kActorMcCoy, 9, kAnimationModeCombatIdle, kAnimationModeCombatWalk, kAnimationModeCombatRun, 0, -1, -1, 20, 240, false);
			} else if (Global_Variable_Query(kVariableAffectionTowards) == kAffectionTowardsDektora
			|| Global_Variable_Query(kVariableAffectionTowards) == kAffectionTowardsLucy) {
				if (Game_Flag_Query(kFlagDektoraIsReplicant)) {
					Actor_Put_In_Set(kActorSteele, kSetKP05_KP06);
					Actor_Set_At_XYZ(kActorSteele, -947.39f, 0.0f, 728.89f, 0);
					Actor_Change_Animation_Mode(kActorSteele, kAnimationModeCombatIdle);
					Scene_Exits_Disable();
					Actor_Face_Actor(kActorSteele, kActorMcCoy, true);
					Actor_Face_Actor(kActorMcCoy, kActorSteele, true);
					Actor_Says(kActorSteele, 530, 15); //01-0530.AUD	You almost got away with it, Slim.
					Actor_Says(kActorSteele, 540, 16); //01-0540.AUD	And I expected so much more from you.
					Player_Set_Combat_Mode(true);
					Actor_Says(kActorMcCoy, 2200, 3); //00-2200.AUD	Why did you have to kill her?
					if (!Game_Flag_Query(kFlagMcCoyIsInnocent)) {
						Actor_Says(kActorSteele, 550, 17); //01-0550.AUD	Who, the mutt? The artificial pet of a Replicant? What'd you think I’d do?
						Actor_Says(kActorMcCoy, 2205, 3); //00-2205.AUD	Show some mercy?
						Actor_Says(kActorSteele, 560, 15); //01-0560.AUD	Well, I guess that’s why you’re there and I’m here.
					} else {
						Actor_Says(kActorSteele, 330, 15); //01-0330.AUD	Nobody gives a damn.
					}
					Delay(1000);
					Actor_Says(kActorSteele, 570, 16); //01-0570.AUD	Now, why don’t you explain to me what you’re doing out here, Slim.
					Actor_Says(kActorSteele, 580, 13); //01-0580.AUD	Maybe you can ease my suspicious mind.
					if (Player_Query_Agenda() != kPlayerAgendaPolite) {
						Actor_Says(kActorMcCoy, 2210, 3); //00-2210.AUD	I’m just checking it out.
						Actor_Says(kActorSteele, 590, 13); //01-0590.AUD	Just doing a little sightseeing?
						Actor_Says(kActorMcCoy, 2215, 3); //00-2215.AUD	That’s right.
						if (!Game_Flag_Query(kFlagMcCoyIsInnocent)) {
							Actor_Says(kActorSteele, 600, 16); //01-0600.AUD	Right. And not fifty yards from your pal Clovis and the moonbus you hijacked.
						}
						Actor_Says(kActorSteele, 610, 15); //01-0610.AUD	You’re not convincing me too good, Slim.
					} else {
						Delay(2000);
						Actor_Says(kActorSteele, 610, 15); //01-0610.AUD	You’re not convincing me too good, Slim.
					}
					Actor_Says(kActorMcCoy, 2220, 3); //00-2220.AUD	You gonna shoot me down right here?
					if (!Game_Flag_Query(kFlagMcCoyIsInnocent)) {
						Actor_Says(kActorSteele, 630, 17); //01-0630.AUD	Maybe you wanna go on the Machine now? See if you can answer this question.
					} else {
						Actor_Says(kActorSteele, 620, 15); //01-0620.AUD	It’s as good a place as any.
					}
					// Added in some action music for your fight with Crystal.
					if (_vm->_cutContent) {
						if (Actor_Query_Goal_Number(kActorSadik) < kGoalSadikGone) {
							Actor_Set_Goal_Number(kActorSadik, 414);
						}
						Music_Play(kMusicMoraji, 71, 0, 0, -1, kMusicLoopPlayOnce, 2);
					}
					Non_Player_Actor_Combat_Mode_On(kActorSteele, kActorCombatStateIdle, true, kActorMcCoy, 9, kAnimationModeCombatIdle, kAnimationModeCombatWalk, kAnimationModeCombatRun, 0, -1, -1, 20, 240, false);
				} else if (Game_Flag_Query(kFlagLucyIsReplicant)) {
					Actor_Put_In_Set(kActorSteele, kSetKP05_KP06);
					Actor_Set_At_XYZ(kActorSteele, -947.39f, 0.0f, 728.89f, 0);
					Actor_Change_Animation_Mode(kActorSteele, kAnimationModeCombatIdle);
					Scene_Exits_Disable();
					Actor_Face_Actor(kActorSteele, kActorMcCoy, true);
					Actor_Face_Actor(kActorMcCoy, kActorSteele, true);
					Actor_Says(kActorSteele, 530, 15); //01-0530.AUD	You almost got away with it, Slim.
					Actor_Says(kActorSteele, 540, 16); //01-0540.AUD	And I expected so much more from you.
					Player_Set_Combat_Mode(true);
					Actor_Says(kActorMcCoy, 2200, 3); //00-2200.AUD	Why did you have to kill her?
					if (!Game_Flag_Query(kFlagMcCoyIsInnocent)) {
						Actor_Says(kActorSteele, 550, 17); //01-0550.AUD	Who, the mutt? The artificial pet of a Replicant? What'd you think I’d do?
						Actor_Says(kActorMcCoy, 2205, 3); //00-2205.AUD	Show some mercy?
						Actor_Says(kActorSteele, 560, 15); //01-0560.AUD	Well, I guess that’s why you’re there and I’m here.
					} else {
						Actor_Says(kActorSteele, 330, 15); //01-0330.AUD	Nobody gives a damn.
					}
					Delay(1000);
					Actor_Says(kActorSteele, 570, 16); //01-0570.AUD	Now, why don’t you explain to me what you’re doing out here, Slim.
					Actor_Says(kActorSteele, 580, 13); //01-0580.AUD	Maybe you can ease my suspicious mind.
					if (Player_Query_Agenda() != kPlayerAgendaPolite) {
						Actor_Says(kActorMcCoy, 2210, 3); //00-2210.AUD	I’m just checking it out.
						Actor_Says(kActorSteele, 590, 13); //01-0590.AUD	Just doing a little sightseeing?
						Actor_Says(kActorMcCoy, 2215, 3); //00-2215.AUD	That’s right.
						if (!Game_Flag_Query(kFlagMcCoyIsInnocent)) {
							Actor_Says(kActorSteele, 600, 16); //01-0600.AUD	Right. And not fifty yards from your pal Clovis and the moonbus you hijacked.
						}
						Actor_Says(kActorSteele, 610, 15); //01-0610.AUD	You’re not convincing me too good, Slim.
					} else {
						Delay(2000);
						Actor_Says(kActorSteele, 610, 15); //01-0610.AUD	You’re not convincing me too good, Slim.
					}
					Actor_Says(kActorMcCoy, 2220, 3); //00-2220.AUD	You gonna shoot me down right here?
					if (!Game_Flag_Query(kFlagMcCoyIsInnocent)) {
						Actor_Says(kActorSteele, 630, 17); //01-0630.AUD	Maybe you wanna go on the Machine now? See if you can answer this question.
					} else {
						Actor_Says(kActorSteele, 620, 15); //01-0620.AUD	It’s as good a place as any.
					}
					// Added in some action music for your fight with Crystal.
					if (_vm->_cutContent) {
						if (Actor_Query_Goal_Number(kActorSadik) < kGoalSadikGone) {
							Actor_Set_Goal_Number(kActorSadik, 414);
						}
						Music_Play(kMusicMoraji, 71, 0, 0, -1, kMusicLoopPlayOnce, 2);
					}
					Non_Player_Actor_Combat_Mode_On(kActorSteele, kActorCombatStateIdle, true, kActorMcCoy, 9, kAnimationModeCombatIdle, kAnimationModeCombatWalk, kAnimationModeCombatRun, 0, -1, -1, 20, 240, false);
				}
			}
		}
	} else if (Actor_Query_Goal_Number(kActorSteele) == 450) {
		Scene_Exits_Disable();
		Actor_Face_Actor(kActorSteele, kActorMcCoy, true);
		Actor_Says(kActorSteele, 530, 15);
		Actor_Says(kActorSteele, 540, 16);
		Actor_Face_Actor(kActorMcCoy, kActorSteele, true);
		Player_Set_Combat_Mode(true);
		Actor_Says(kActorMcCoy, 2200, 3);
		Actor_Says(kActorSteele, 550, 17);
		Actor_Says(kActorMcCoy, 2205, 3);
		Actor_Says(kActorSteele, 560, 15);
		Actor_Says(kActorSteele, 570, 16);
		Actor_Says(kActorSteele, 580, 13);
		Actor_Says(kActorMcCoy, 2210, 3);
		Actor_Says(kActorSteele, 590, 13);
		Actor_Says(kActorMcCoy, 2215, 3);
		Actor_Says(kActorSteele, 600, 16);
		Actor_Says(kActorSteele, 610, 15);
		Actor_Says(kActorMcCoy, 2220, 3);
		Actor_Says(kActorSteele, 620, 15);
		Actor_Says(kActorSteele, 630, 17);
		Non_Player_Actor_Combat_Mode_On(kActorSteele, kActorCombatStateIdle, true, kActorMcCoy, 9, kAnimationModeCombatIdle, kAnimationModeCombatWalk, kAnimationModeCombatRun, 0, -1, -1, 20, 240, false);
	}
}

void SceneScriptKP05::PlayerWalkedOut() {
}

void SceneScriptKP05::DialogueQueueFlushed(int a1) {
}

} // End of namespace BladeRunner
