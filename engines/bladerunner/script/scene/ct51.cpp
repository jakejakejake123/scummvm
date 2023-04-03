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

void SceneScriptCT51::InitializeScene() {
	Setup_Scene_Information(0.0f, 0.0f, -102.0f, 470);

	Scene_Exit_Add_2D_Exit(1, 0, 0, 30, 479, 3);

	Ambient_Sounds_Add_Looping_Sound(kSfxRAIN10, 100, 1, 1);
	Ambient_Sounds_Add_Sound(kSfxSPIN2B,  60, 180, 16,  25, 0, 0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSPIN3A,  60, 180, 16,  25, 0, 0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxTHNDER2, 60, 180, 50, 100, 0, 0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxTHNDER3, 50, 180, 50, 100, 0, 0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxTHNDER4, 50, 180, 50, 100, 0, 0, -101, -101, 0, 0);

	Scene_Loop_Start_Special(kSceneLoopModeLoseControl, 0, false);
	Scene_Loop_Set_Default(1);
}

void SceneScriptCT51::SceneLoaded() {
	Unobstacle_Object("BLANKET03", true);
	Clickable_Object("BED02");
	if (!Actor_Clue_Query(kActorMcCoy, kClueRagDoll)) {
#if BLADERUNNER_ORIGINAL_BUGS
		Item_Add_To_World(kItemRagDoll, kModelAnimationRagDoll, kSetCT08_CT51_UG12, 44.0f, 0.0f, -95.0f, 540, 24, 24, false, true, false, true);
#else
		// fix click-box overlap with clickable bed
		if (_vm->_cutContent) {
			if (Actor_Query_Intelligence(kActorIzo) == 85) {
				Item_Add_To_World(kItemRagDoll, kModelAnimationRagDoll, kSetCT08_CT51_UG12, 44.0f, 3.0f, -100.0f, 540, 24, 24, false, true, false, true);
			}
		}
#endif
	}
	if (_vm->_cutContent) {
		if (!Actor_Clue_Query(kActorMcCoy, kClueMoonbus1)) {
			if (Actor_Query_Intelligence(kActorIzo) == 85
			&& Game_Flag_Query(kFlagIzoFled)) {
				Item_Add_To_World(kItemMoonbusPhoto, kModelAnimationPhoto, kSetCT08_CT51_UG12, 44.0f, 0.0f, -22.0f, 0, 12, 12, false, true, false, true);
			}
		}
	} else {
		if (!Actor_Clue_Query(kActorMcCoy, kClueMoonbus1)) {
			Item_Add_To_World(kItemMoonbusPhoto, kModelAnimationPhoto, kSetCT08_CT51_UG12, 44.0f, 0.0f, -22.0f, 0, 12, 12, false, true, false, true);
		}
	}
}

bool SceneScriptCT51::MouseClick(int x, int y) {
	return true;
}

bool SceneScriptCT51::ClickedOn3DObject(const char *objectName, bool a2) {
	if (Object_Query_Click("BED02", objectName)) {
		if (_vm->_cutContent) {
			if (!Actor_Clue_Query(kActorMcCoy, kClueHysteriaToken)) {
				Item_Pickup_Spin_Effect(kModelAnimationHysteriaToken, 203, 200);
				Actor_Clue_Acquire(kActorMcCoy, kClueHysteriaToken, true, kActorLucy);
				Actor_Says(kActorMcCoy, 8810, 14);	//00-8810.AUD	An arcade token.
				Actor_Voice_Over(420, kActorVoiceOver);
			} else if (!Actor_Clue_Query(kActorMcCoy, kClueLicensePlate)
			&& Game_Flag_Query(kFlagGordoIsReplicant)
			&& Actor_Query_Intelligence(kActorGordo) == 80) {
				Item_Pickup_Spin_Effect(kModelAnimationLicensePlate, 397, 274);
				Actor_Says(kActorMcCoy, 8760, 13); //00-8760.AUD	A license plate.
				Actor_Clue_Acquire(kActorMcCoy, kClueLicensePlate, true, -1);
				if (Actor_Clue_Query(kActorMcCoy, kCluePartialLicenseNumber)) {
					Delay(500);
					Actor_Voice_Over(4190, kActorVoiceOver); //99-4190.AUD	Where have I seen that before?
					Delay(1000);
					Actor_Says(kActorMcCoy, 8525, 9); //00-8525.AUD	Hmph.
					Actor_Change_Animation_Mode(kActorMcCoy, 23);
					Delay(800);
					Actor_Says(kActorAnsweringMachine, 390, kAnimationModeTalk); // 39-0390.AUD	Begin test.
					Ambient_Sounds_Play_Sound(kSfxDATALOAD, 50, 0, 0, 99);
					Delay(2000);
					Ambient_Sounds_Play_Sound(kSfxBEEPNEAT, 80, 0, 0, 99);
					Actor_Says(kActorAnsweringMachine, 420, 19); //39-0420.AUD	Positive result.
					Actor_Says(kActorAnsweringMachine, 470, kAnimationModeTalk); //39-0470.AUD	End test.
					Actor_Says(kActorMcCoy, 7200, 13); //00-7200.AUD	Bingo.
					Actor_Clue_Acquire(kActorMcCoy, kClueLicensePlateMatch, true, -1); 
					if (Game_Flag_Query(kFlagKleinCarIdentityTalk)
					&& !Actor_Clue_Query(kActorMcCoy, kClueCar)
					&& !Actor_Clue_Query(kActorMcCoy, kClueCarRegistration1)
					&& !Actor_Clue_Query(kActorMcCoy, kClueCarRegistration2)
					&& !Actor_Clue_Query(kActorMcCoy, kClueCarRegistration3)) {
						Actor_Voice_Over(540, kActorVoiceOver); //99-0540.AUD	If I ran it through the Mainframe back at the station, I could ID the owner.
					}
				}
			} else {
				Actor_Says(kActorMcCoy, 8580, 12);
			}
		} else {
			if (!Actor_Clue_Query(kActorMcCoy, kClueHysteriaToken)) {
				Item_Pickup_Spin_Effect(kModelAnimationHysteriaToken, 203, 200);
				Actor_Clue_Acquire(kActorMcCoy, kClueHysteriaToken, true, -1);
				Actor_Says(kActorMcCoy, 8810, 14);	//00-8810.AUD	An arcade token.
				Actor_Voice_Over(420, kActorVoiceOver);
			} else {
				Actor_Says(kActorMcCoy, 8580, 12);
			}
		}
	}
	return false;
}

bool SceneScriptCT51::ClickedOnActor(int actorId) {
	return false;
}

bool SceneScriptCT51::ClickedOnItem(int itemId, bool a2) {
	if (itemId == kItemRagDoll) {
		if (_vm->_cutContent) {
			Actor_Clue_Acquire(kActorMcCoy, kClueRagDoll, true, kActorLucy);
		} else {
			Actor_Clue_Acquire(kActorMcCoy, kClueRagDoll, true, -1);
		}
		Item_Pickup_Spin_Effect(kModelAnimationRagDoll, 260, 200);
		Ambient_Sounds_Play_Sound(kSfxBABYCRY2, 40, 99, 0, 0);
		Item_Remove_From_World(kItemRagDoll);
		if (_vm->_cutContent) {
			Actor_Says(kActorMcCoy, 8815, kAnimationModeTalk); //00-8815.AUD	A creepy looking doll.
		}
		return true;
	}

	if (itemId == kItemMoonbusPhoto) {
		if (_vm->_cutContent) {
			Actor_Clue_Acquire(kActorMcCoy, kClueMoonbus1, true, kActorIzo);
		} else {
			Actor_Clue_Acquire(kActorMcCoy, kClueMoonbus1, true, -1);
		}
		Item_Pickup_Spin_Effect(kModelAnimationPhoto, 490, 307);
		Item_Remove_From_World(kItemMoonbusPhoto);
		Actor_Says(kActorMcCoy, 8527, kAnimationModeTalk);
		return true;
	}
	return false;
}

bool SceneScriptCT51::ClickedOnExit(int exitId) {
	if (exitId == 1) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, 0.0f, 0.0f, -102.0f, 0, true, false, false)) {
			Loop_Actor_Walk_To_XYZ(kActorMcCoy, -11.0f, 0.0f, -156.0f, 0, false, false, false);
			Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
			Ambient_Sounds_Remove_All_Looping_Sounds(1u);
			Game_Flag_Set(kFlagCT51toCT08);
			Set_Enter(kSetCT08_CT51_UG12, kSceneCT08);
		}
		return true;
	}
	return false;

}

bool SceneScriptCT51::ClickedOn2DRegion(int region) {
	return false;
}

void SceneScriptCT51::SceneFrameAdvanced(int frame) {
}

void SceneScriptCT51::ActorChangedGoal(int actorId, int newGoal, int oldGoal, bool currentSet) {
}

void SceneScriptCT51::PlayerWalkedIn() {
}

void SceneScriptCT51::PlayerWalkedOut() {
	if (!Actor_Clue_Query(kActorMcCoy, kClueRagDoll)) {
		Item_Remove_From_World(kItemRagDoll);
	}
}

void SceneScriptCT51::DialogueQueueFlushed(int a1) {
}

} // End of namespace BladeRunner
