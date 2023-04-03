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
	}

	Scene_Exit_Add_2D_Exit(0,   0,   0,  30, 479, 3);
	Scene_Exit_Add_2D_Exit(1, 589,   0, 639, 479, 1);
	Scene_Exit_Add_2D_Exit(2, 377, 374, 533, 479, 2);
	// Made it so Dektora (Pris) and Sebastian appears in the set after you go to the roof.
	// Dektora will be placed at the back of the room and her face will be obscured by a ceiling ornament so the player won't
	// know it's her and will assume it's Pris.
	// Made it so Sebastian has to be conscious and not know that McCoy is a blade runner so he will appear and talk to McCoy about the doll.
	if (_vm->_cutContent) {
		if (Game_Flag_Query(kFlagBB08Visited) 
		&& !Game_Flag_Query(kFlagSebastianKnockedOut) 
		&& !Actor_Clue_Query(kActorSebastian, kClueMcCoyIsABladeRunner)
		&& !Game_Flag_Query(kFlagNewDoll)
		&& Global_Variable_Query(kVariableChapter) == 3) {
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
		if (actorId == kActorDektora 
		&& !Game_Flag_Query(kFlagNewDoll)
		&& !Actor_Clue_Query(kActorSebastian, kClueMcCoyIsABladeRunner)
		&& !Game_Flag_Query(kFlagSebastianKnockedOut)
		&& !Loop_Actor_Walk_To_XYZ(kActorMcCoy, -45.93, 0.28, -13.71, 0, true, false, false)) {
			Actor_Face_Actor(kActorMcCoy, kActorDektora, true);
			Actor_Face_Actor(kActorSebastian, kActorDektora, true);
			if (Player_Query_Agenda() == kPlayerAgendaPolite) {
				Actor_Says(kActorMcCoy, 7230, 13); //00-7230.AUD	That's a real pretty design. I don't remember seeing it before.
			} else {
				Actor_Says(kActorMcCoy, 8695, 13); //00-8695.AUD	That's an unusual design.
			}
			Loop_Actor_Walk_To_XYZ(kActorSebastian, -29.04, 0.31, -63.71, 0, true, false, false);
			Actor_Face_Actor(kActorSebastian, kActorDektora, true);
			Actor_Says(kActorSebastian, 620, 16); //56-0620.AUD	She is new.
			Actor_Face_Actor(kActorMcCoy, kActorSebastian, true);
			Actor_Says(kActorMcCoy, 7235, 18); //00-7235.AUD	You make her, too?
			Actor_Face_Actor(kActorSebastian, kActorMcCoy, true);
			if (Actor_Query_Friendliness_To_Other(kActorSebastian, kActorMcCoy) < 50) {
				Actor_Says(kActorSebastian, 70, kAnimationModeTalk); //56-0070.AUD	Yes?
				Delay(1000);
			} else {
				Actor_Says(kActorSebastian, 630, 13); //56-0630.AUD	I-- I found her. On the street.
				Actor_Says(kActorSebastian, 640, 13); //56-0640.AUD	But she's mine now.
				if (Player_Query_Agenda() != kPlayerAgendaSurly 
				&& Player_Query_Agenda() != kPlayerAgendaErratic) {
					Actor_Says(kActorMcCoy, 7240, 18); //00-7240.AUD	Easy boy, I'm not gonna take her away from ya.
				} else {
					Delay(1000);
				}
			}
			Actor_Face_Actor(kActorMcCoy, kActorDektora, true);
			if (Player_Query_Agenda() == kPlayerAgendaPolite) {
				Actor_Says(kActorMcCoy, 7245, 15); //00-7245.AUD	The detail! She's a real beauty, ain't she?
			} else {
				Actor_Says(kActorMcCoy, 8700, 18); //00-8700.AUD	Never seen anything like that before.
			}
			if (Actor_Query_Friendliness_To_Other(kActorSebastian, kActorMcCoy) < 50) {
				Actor_Says(kActorSebastian, 650, 14); //56-0650.AUD	I haven't named her yet.
			}
			Delay(1000);
			Actor_Says(kActorMcCoy, 7250, 13); //00-7250.AUD	She almost looks real.
			Actor_Says(kActorSebastian, 660, 14); //56-0660.AUD	She isn't. Believe you me.
			Delay(1000);
			Actor_Says(kActorMcCoy, 7255, 15); //00-7255.AUD	You know, I can't place her for sure but she looks familiar.
			Actor_Face_Actor(kActorSebastian, kActorMcCoy, true);
			Actor_Says(kActorSebastian, 670, 14); //56-0670.AUD	Familiar to what?
			Actor_Set_Targetable(kActorGeneralDoll, false);
			if (Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)
			|| Player_Query_Agenda() == kPlayerAgendaPolite) { 
				Delay(1000);
				Actor_Face_Actor(kActorMcCoy, kActorSebastian, true);
				Actor_Says(kActorMcCoy, 1535, 16); //00-1535.AUD	Ah, never mind.
				Delay(1000);
				Actor_Says(kActorMcCoy, 2860, 14); //00-2860.AUD	You take care of yourself.
				Player_Loses_Control();
				Loop_Actor_Walk_To_XYZ(kActorMcCoy, 54.0f, 0.0f, 200.0f, 0, false, false, true); 
				Player_Gains_Control();
				Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
				Ambient_Sounds_Remove_All_Looping_Sounds(1u);
				Game_Flag_Set(kFlagBB12toBB05);
				Set_Enter(kSetBB05, kSceneBB05);
				Game_Flag_Set(kFlagNewDoll);
			} else {
				Actor_Says(kActorMcCoy, 7260, 16); //00-7260.AUD	Didn't I see an incept tape at the--
				Actor_Change_Animation_Mode(kActorMcCoy, 4);
				Actor_Says(kActorSebastian, 680, 14); //56-0680.AUD	Hey, you don't need to do that.
				Actor_Says(kActorMcCoy, 2775, -1); //00-2775.AUD	Hey, I'd just as soon not do this job.
				Actor_Says(kActorSebastian, 560, 20); //56-0560.AUD	You-- You're a Blade Runner, aren't you?
				Actor_Says(kActorMcCoy, 7200, -1); //00-7200.AUD	Bingo.
				Actor_Change_Animation_Mode(kActorMcCoy, 5);
				Loop_Actor_Walk_To_XYZ(kActorSebastian,  6.18, 0.29, -33.29, 0, false, false, true); 
				Actor_Face_Actor(kActorSebastian, kActorMcCoy, true);
				Actor_Says(kActorSebastian, 700, 13); //56-0700.AUD	Please! You don't have to pull your gun in here.
				Actor_Says(kActorMcCoy, 465, -1); //00-0465.AUD	Take your business elsewhere.
				Delay(1500);
				Actor_Says(kActorSebastian, 610, 14); //56-0610.AUD	I think you should leave now, Mr. McCoy.
				Delay(1500);
				Sound_Play(kSfxSHOTCOK1, 100, 0, 100, 50);
				Actor_Change_Animation_Mode(kActorSebastian, 20);
				Delay(1500);
				Music_Play(kMusicCrysDie1, 25, 0, 1, -1, kMusicLoopPlayOnce, 0);
				Delay(1500);
				Actor_Says(kActorSebastian, 710, 15); //56-0710.AUD	Stop! Please! Why are you doing all these terrible things?
				Delay(3000);
				Actor_Says(kActorMcCoy, 170, -1); //00-0170.AUD	Damn.
				Actor_Change_Animation_Mode(kActorMcCoy, 4);
				Delay(2000);
				Actor_Face_Actor(kActorMcCoy, kActorSebastian, true);
				Delay(1000);
				Actor_Says(kActorMcCoy, 1970, 4); //00-1970.AUD	You should start thinking about the company you keep.
				Delay(1000);
				Actor_Says(kActorSebastian, 110, 16); //56-0110.AUD	Well, if you insist... 
				Actor_Clue_Acquire(kActorSebastian, kClueMcCoyIsABladeRunner, true, kActorMcCoy);
				Delay(1000);
				Player_Loses_Control();
				Loop_Actor_Walk_To_XYZ(kActorMcCoy, 54.0f, 0.0f, 200.0f, 0, false, false, true);
				Player_Gains_Control();
				Actor_Set_Targetable(kActorGeneralDoll, false);
				Music_Stop(1u);
				Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
				Ambient_Sounds_Remove_All_Looping_Sounds(1u);
				Music_Play(kMusicBRBlues, 52, 0, 2, -1, kMusicLoopPlayOnce, 1);
				Game_Flag_Set(kFlagBB12toBB05);
				Set_Enter(kSetBB05, kSceneBB05);
				Game_Flag_Set(kFlagNewDoll);
			}
		}
		if (actorId == kActorSebastian) {
			if (!Game_Flag_Query(kFlagSebastianKnockedOut)) {
				Loop_Actor_Walk_To_Actor(kActorMcCoy, kActorSebastian, 24, true, false);
				Actor_Face_Actor(kActorSebastian, kActorMcCoy, true);
				Actor_Face_Actor(kActorMcCoy, kActorSebastian, true);
				if (!Game_Flag_Query(kFlagNewDoll)) {
					Actor_Says(kActorMcCoy, 7115, 13);
					Actor_Says(kActorSebastian, 280, 14);
				} else {
					Actor_Says(kActorMcCoy, 7110, 15);
					Actor_Says(kActorSebastian, 270, 16);
				}
			}
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
	if (_vm->_cutContent) {
		Player_Set_Combat_Mode(false);
	}
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
