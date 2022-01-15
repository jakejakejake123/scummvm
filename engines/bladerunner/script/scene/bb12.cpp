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

void SceneScriptBB12::InitializeScene() {
	if (Game_Flag_Query(kFlagBB07toBB12)) {
		Setup_Scene_Information( 138.0f, 0.0f, 104.0f, 760);
	} else if (Game_Flag_Query(kFlagBB08toBB12)) {
		Setup_Scene_Information(-129.0f, 0.0f,  64.0f, 307);
	} else {
		Setup_Scene_Information(  54.0f, 0.0f, 200.0f,   0);
		Game_Flag_Reset(kFlagBB05toBB12);
	}

	Scene_Exit_Add_2D_Exit(0,   0,   0,  30, 479, 3);
	Scene_Exit_Add_2D_Exit(1, 589,   0, 639, 479, 1);
	Scene_Exit_Add_2D_Exit(2, 377, 374, 533, 479, 2);
	// Made it so Dektora (Pris) and Sebastian appears in the set after you go to the roof.
	// Dektora will be placed at the back of the room and her face will be obscured by a ceiling ornament so the player won't
	// know it's her and will assume it's Pris.
	if (_vm->_cutContent) {
		if  (Game_Flag_Query(kFlagBB11Visited) &&
			(Global_Variable_Query(kVariableChapter) == 3)) {
			Actor_Put_In_Set(kActorDektora, kSetBB12);
			Actor_Set_At_XYZ(kActorDektora, 39.97, 0.31, -56.65, 180);
			Actor_Put_In_Set(kActorSebastian, kSetBB12);
			Actor_Set_At_XYZ(kActorSebastian, 85.70, 0.17, 124.84, 0);
		}
	}

	Ambient_Sounds_Add_Looping_Sound(kSfxRAINAWN1, 28, 0, 1);
	Ambient_Sounds_Add_Sound(kSfxSCARY4,  2, 180, 14, 16, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSCARY5,  2, 180, 14, 16, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSCARY6,  2, 180, 14, 16, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSCARY7,  2, 180, 14, 16, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBBGRN1,  5,  50, 27, 27, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBBGRN2,  5,  50, 27, 27, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBBGRN3,  5,  50, 27, 27, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBBMOVE1, 5,  50, 27, 27, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBBMOVE2, 5,  50, 27, 27, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBBMOVE3, 5,  50, 27, 27, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxHAUNT1,  5,  50, 27, 27, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxHAUNT2,  5,  50, 27, 27, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxTHNDER2, 5, 180, 25, 25, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxTHNDER3, 5, 180, 25, 25, -100, 100, -101, -101, 0, 0);

	if (!Game_Flag_Query(kFlagBB12Entered)) {
		// Made it so the battle music plays when you walk in the room and see Sadiks shadow.
		if (_vm->_cutContent) {
			Music_Play(kMusicBatl226M, 50, 0, 2, -1, kMusicLoopPlayOnce, 0);
		}
		Overlay_Play("BB12OVER", 0, false, false, 0); // Sadik's shadow going left
		Game_Flag_Set(kFlagBB12Entered);
	}
}

void SceneScriptBB12::SceneLoaded() {
	Obstacle_Object("BALLS", true);
	Unclickable_Object("BALLS");
}

bool SceneScriptBB12::MouseClick(int x, int y) {
	return false;
}

bool SceneScriptBB12::ClickedOn3DObject(const char *objectName, bool a2) {
	return false;
}

bool SceneScriptBB12::ClickedOnActor(int actorId) {
	// Code for when you click on Dektora (Pris).
	if (_vm->_cutContent) {
		if (actorId == kActorDektora && !Game_Flag_Query(kFlagNewDoll)) {
			Actor_Face_Actor(kActorMcCoy, kActorDektora, true);
			Actor_Face_Actor(kActorSebastian, kActorDektora, true);
			Actor_Says(kActorMcCoy, 7230, 13); //00-7230.AUD	That's a real pretty design. I don't remember seeing it before.
			Actor_Says(kActorSebastian, 620, 16); //56-0620.AUD	She is new.
			Actor_Says(kActorMcCoy, 7235, 18); //00-7235.AUD	You make her, too?
			Actor_Says(kActorSebastian, 630, 13); //56-0630.AUD	I-- I found her. On the street.
			Actor_Says(kActorSebastian, 640, 13); //56-0640.AUD	But she's mine now.
			Actor_Says(kActorMcCoy, 7240, 18); //00-7240.AUD	Easy boy, I'm not gonna take her away from ya.
			Actor_Says(kActorMcCoy, 7245, 15); //00-7245.AUD	The detail! She's a real beauty, ain't she?
			Actor_Says(kActorSebastian, 650, 14); //56-0650.AUD	I haven't named her yet.
			Actor_Says(kActorMcCoy, 7250, 13); //00-7250.AUD	She almost looks real.
			Actor_Says(kActorSebastian, 660, 14); //56-0660.AUD	She isn't. Believe you me.
			Actor_Says(kActorMcCoy, 7255, 15); //00-7255.AUD	You know, I can't place her for sure but she looks familiar.
			Actor_Says(kActorSebastian, 670, 14); //56-0670.AUD	Familiar to what?
			Delay(1000);
			Actor_Says(kActorMcCoy, 1535, 16); //00-1535.AUD	Ah, never mind.
			Game_Flag_Set(kFlagNewDoll);
		}
	}
	return true;
}

bool SceneScriptBB12::ClickedOnItem(int itemId, bool a2) {
	return false;
}

bool SceneScriptBB12::ClickedOnExit(int exitId) {
	if (exitId == 0) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -129.0f, 0.0f, 64.0f, 0, true, false, false)) {
			Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
			Ambient_Sounds_Remove_All_Looping_Sounds(1u);
			Game_Flag_Set(kFlagBB12toBB08);
			Set_Enter(kSetBB08, kSceneBB08);
			// The trailing laughter of the toy monkey can be heard as you leave the room.
			if (_vm->_cutContent) {
				Sound_Play(kSfxMONKEY2,  40, 0, 0, 50);
			}
		}
		return true;
	}

	if (exitId == 1) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, 138.0f, 0.0f, 104.0f, 0, true, false, false)) {
			Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
			Ambient_Sounds_Remove_All_Looping_Sounds(1u);
			Game_Flag_Set(kFlagBB12toBB07);
			Set_Enter(kSetBB07, kSceneBB07);
			if (_vm->_cutContent) {
				Sound_Play(kSfxMONKEY2,  40, 0, 0, 50);	
			}
		}
		return true;
	}

	if (exitId == 2) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, 54.0f, 0.0f, 200.0f, 0, true, false, false)) {
			Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
			Ambient_Sounds_Remove_All_Looping_Sounds(1u);
			Game_Flag_Set(kFlagBB12toBB05);
			Set_Enter(kSetBB05, kSceneBB05);
			if (_vm->_cutContent) {
				Sound_Play(kSfxMONKEY2,  40, 0, 0, 50);
			}
		}
		return true;
	}
	return false;
}

bool SceneScriptBB12::ClickedOn2DRegion(int region) {
	return false;
}

void SceneScriptBB12::SceneFrameAdvanced(int frame) {
	if (frame == 10
	 || frame == 22
	 || frame == 33
	 || frame == 41
	) {
		Sound_Play(kSfxMONKCYM1, 17, -30, -30, 50);
	}

	if (frame == 3) {
		Sound_Play(kSfxMONKEY1,  16, -30, -30, 50);
	}
}

void SceneScriptBB12::ActorChangedGoal(int actorId, int newGoal, int oldGoal, bool currentSet) {
}

void SceneScriptBB12::PlayerWalkedIn() {
	if (Game_Flag_Query(kFlagBB07toBB12)) {
		Loop_Actor_Walk_To_XYZ(kActorMcCoy, 114.0f, 0.0f, 104.0f, 0, false, false, false);
		Game_Flag_Reset(kFlagBB07toBB12);
	} else if (Game_Flag_Query(kFlagBB08toBB12)) {
		Loop_Actor_Walk_To_XYZ(kActorMcCoy, -101.0f, 0.0f, 64.0f, 0, false, false, false);
		Game_Flag_Reset(kFlagBB08toBB12);
	}
}

void SceneScriptBB12::PlayerWalkedOut() {
}

void SceneScriptBB12::DialogueQueueFlushed(int a1) {
}

} // End of namespace BladeRunner
