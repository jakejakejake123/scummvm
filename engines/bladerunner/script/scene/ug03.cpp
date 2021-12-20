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

void SceneScriptUG03::InitializeScene() {
	if (Game_Flag_Query(kFlagUG04toUG03)) {
		Setup_Scene_Information(  -51.0f, 0.03f,  255.0f, 780);
		Game_Flag_Reset(kFlagUG04toUG03);
	} else if (Game_Flag_Query(kFlagUG10toUG03)) {
		Setup_Scene_Information( -139.0f, 0.03f,  -13.0f, 540);
		Game_Flag_Reset(kFlagUG10toUG03);
	} else {
		Setup_Scene_Information(-121.88f, 0.03f, 213.35f, 540);
	}
	Scene_Exit_Add_2D_Exit(0,  46, 137, 131, 296, 0);
	Scene_Exit_Add_2D_Exit(1, 559, 141, 639, 380, 1);

	// Made it so Holloway appears in the set but offscreen for the scene where he tells McCoy about his incept photo. This is because Holloway is supposed to be lying down and doesn't have a lying down pose or animation 
	// so to circumvent this he will appear offscreen.
	if (_vm->_cutContent) {
		if (Global_Variable_Query(kVariableChapter) == 3) {
			Actor_Put_In_Set(kActorHolloway, kSetUG03);
			Actor_Set_At_XYZ(kActorHolloway, 4.22f, -1.37f, -925.0f, 750);
		}
	}

	Ambient_Sounds_Add_Looping_Sound(kSfxSTMLOOP7, 15, 0, 1);
	Ambient_Sounds_Add_Looping_Sound(kSfxUGBED1,   40, 0, 1);
	Ambient_Sounds_Add_Looping_Sound(kSfxUGBED2,   40, 0, 1);
	Ambient_Sounds_Add_Sound(kSfxYELL1M3,  2, 120, 10, 11,    0, 100,    0,  100, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxGRUNT2M1, 2, 120, 10, 11,    0, 100,    0,  100, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxGRUNT1M3, 2, 120, 10, 11,    0, 100,    0,  100, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxGRUNT1M2, 2, 120, 10, 11,    0, 100,    0,  100, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxPIPER1,   2, 190, 12, 16, -100, 100, -100,  100, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSQUEAK1,  2, 190, 12, 16, -100, 100, -100,  100, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSQUEAK2,  2, 190, 12, 16, -100, 100, -100,  100, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSQUEAK3,  2, 190, 12, 16, -100, 100, -100,  100, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSQUEAK4,  2, 190, 12, 16, -100, 100, -100,  100, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSQUEAK5,  2, 190, 12, 16, -100, 100, -100,  100, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBANG1,    2, 190, 12, 16, -100, 100, -100,  100, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBANG2,    2, 190, 12, 16, -100, 100, -100,  100, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBANG3,    2, 190, 12, 16, -100, 100, -100,  100, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBANG4,    2, 190, 12, 16, -100, 100, -100,  100, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBANG5,    2, 190, 12, 16, -100, 100, -100,  100, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBANG6,    2, 190, 12, 16, -100, 100, -100,  100, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBBGRN1,   5,  50, 17, 37, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBBGRN2,   5,  50, 17, 37, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBBGRN3,   5,  50, 17, 37, -100, 100, -101, -101, 0, 0);
}

void SceneScriptUG03::SceneLoaded() {
	Obstacle_Object("=WALL_RIGHT_HOLE", true);
	Unobstacle_Object("=HOLERUBBLE1", true);
	Clickable_Object("CHAIR_HEADZAPPER");
	Clickable_Object("CHAIR_BACK");
	Clickable_Object("CHAIR_SEAT");
	Clickable_Object("CHAIR_STRAPLEGLEFT");
	Clickable_Object("CHAIR_STRAPLEGRIGHT");
#if BLADERUNNER_ORIGINAL_BUGS
#else
	if (Actor_Clue_Query(kActorMcCoy, kClueScaryChair)) {
		Unclickable_Object("CHAIR_HEADZAPPER");
		Unclickable_Object("CHAIR_BACK");
		Unclickable_Object("CHAIR_SEAT");
		Unclickable_Object("CHAIR_STRAPLEGLEFT");
		Unclickable_Object("CHAIR_STRAPLEGRIGHT");
	}
#endif // BLADERUNNER_ORIGINAL_BUGS
	//Added in the Bakers badge clue to the set.
	if (_vm->_cutContent &&
		!Actor_Clue_Query(kActorMcCoy, kClueBakersBadge)) {
		Item_Add_To_World(kItemBakersBadge, kModelAnimationBadge, kSetUG03, -158.78, 0.25, -39.55, 0, 12, 12, false, true, false, true);
	}
}

bool SceneScriptUG03::MouseClick(int x, int y) {
	return false;
}

bool SceneScriptUG03::ClickedOn3DObject(const char *objectName, bool a2) {
	if (Object_Query_Click("CHAIR_BACK", objectName)
	 || Object_Query_Click("CHAIR_SEAT", objectName)
	 || Object_Query_Click("CHAIR_HEADZAPPER", objectName)
#if BLADERUNNER_ORIGINAL_BUGS
#else
	 || Object_Query_Click("CHAIR_STRAPLEGLEFT", objectName)
	 || Object_Query_Click("CHAIR_STRAPLEGRIGHT", objectName)
#endif // BLADERUNNER_ORIGINAL_BUGS
	) {
		if (!Loop_Actor_Walk_To_Scene_Object(kActorMcCoy, "CHAIR_BACK", 36, true, false)) {
			Actor_Face_Object(kActorMcCoy, "CHAIR_BACK", true);
			if (!Actor_Clue_Query(kActorMcCoy, kClueScaryChair)) {
				Actor_Voice_Over(2550, kActorVoiceOver);
				Actor_Voice_Over(2560, kActorVoiceOver);
				Actor_Voice_Over(2570, kActorVoiceOver);
				Actor_Voice_Over(2580, kActorVoiceOver);
				Actor_Voice_Over(2590, kActorVoiceOver);
				Actor_Clue_Acquire(kActorMcCoy, kClueScaryChair, true, -1);
#if BLADERUNNER_ORIGINAL_BUGS
#else
				Unclickable_Object("CHAIR_HEADZAPPER");
				Unclickable_Object("CHAIR_BACK");
				Unclickable_Object("CHAIR_SEAT");
				Unclickable_Object("CHAIR_STRAPLEGLEFT");
				Unclickable_Object("CHAIR_STRAPLEGRIGHT");
#endif // BLADERUNNER_ORIGINAL_BUGS
			}
		}
	}
	return false;
}

bool SceneScriptUG03::ClickedOnActor(int actorId) {
	return false;
}

bool SceneScriptUG03::ClickedOnItem(int itemId, bool a2) {
	//Code for picking up Bakers badge.
	if (itemId == kItemBakersBadge) {
		if (!Loop_Actor_Walk_To_Item(kActorMcCoy, kItemBakersBadge, 12, true, false)) {
			Actor_Face_Item(kActorMcCoy, kItemBakersBadge, true);
			Actor_Clue_Acquire(kActorMcCoy, kClueBakersBadge, true, -1);
			Item_Pickup_Spin_Effect(kModelAnimationBadge, 13, 298);
			Item_Remove_From_World(kItemBakersBadge);
			Actor_Says(kActorMcCoy, 8855, 12); //00-8855.AUD	Baker's badge.
		}
	}			
	return true;
}

bool SceneScriptUG03::ClickedOnExit(int exitId) {
	if (exitId == 0) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -139.0f, 0.0f, -13.0f, 0, true, false, false)) {
			if (Global_Variable_Query(kVariableChapter) < 4) {
				Actor_Says(kActorMcCoy, 8522, 14);
			} else {
				Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
				Ambient_Sounds_Remove_All_Looping_Sounds(1u);
				Game_Flag_Set(kFlagUG03toUG10);
				Set_Enter(kSetUG10, kSceneUG10);
			}
		}
		return true;
	}

	if (exitId == 1) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -51.0f, 0.0f, 255.0f, 0, true, false, false)) {
			Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
			Ambient_Sounds_Remove_All_Looping_Sounds(1u);
			Game_Flag_Set(kFlagUG03toUG04);
			Set_Enter(kSetUG04, kSceneUG04);
		}
		return true;
	}
	return false;
}

bool SceneScriptUG03::ClickedOn2DRegion(int region) {
	return false;
}

void SceneScriptUG03::SceneFrameAdvanced(int frame) {
}

void SceneScriptUG03::ActorChangedGoal(int actorId, int newGoal, int oldGoal, bool currentSet) {
}

void SceneScriptUG03::PlayerWalkedIn() {
	//Code for the scene where McCoy confronts a dying Holloway and he shows McCoy the incept photo.
	if (_vm->_cutContent) {
		if (Global_Variable_Query(kVariableChapter) == 3) {
			if (!Game_Flag_Query(kFlagHollowayTalk)) {
				Delay (1000);
				Actor_Face_Heading(kActorMcCoy, 511, false);
				Actor_Says (kActorHolloway, 0, kAnimationModeTalk); //33-0000.AUD	(Coughs) You're a Rep, McCoy. I've seen your incept photo with my own eyes.
				Actor_Says(kActorMcCoy, 5520, 18); //00-5520.AUD	Oh, yeah?
				Delay (1000);
				Item_Pickup_Spin_Effect(kModelAnimationPhoto, 602, 435);
				Actor_Voice_Over(4240, kActorVoiceOver); //99-4240.AUD	That can't be me.
				Actor_Clue_Acquire(kActorMcCoy, kClueMcCoyIncept, true, kActorHolloway);
				Delay (1000);
				Actor_Says (kActorHolloway, 10, kAnimationModeTalk); //33-0010.AUD	It's all over the place. You don't got a chance. (groans)
				Actor_Says(kActorMcCoy, 5530, 15); //00-5530.AUD	Photos can be doctored. Who showed you this piece of art?
				Delay (2000);
				Actor_Says(kActorMcCoy, 5525, 14); //00-5525.AUD	Who’s behind this? Who set me up?
				Delay (3000);
				Actor_Says(kActorMcCoy, 170, 12); //00-0170.AUD	Damn.
				Actor_Clue_Acquire(kActorMcCoy, kClueHollowayInterview, true, kActorHolloway);
				Game_Flag_Set(kFlagHollowayTalk);
			}
		}
	}
	// Addded in some dispatcher dialogue.
	if (_vm->_cutContent) {
		if (Global_Variable_Query(kVariableChapter) == 4) {
			if (!Game_Flag_Query(kFlagDispatcherTalkMcCoy)) {
				ADQ_Add(kActorDispatcher, 40, kAnimationModeTalk); //38-0040.AUD	Attention all units. Be on the lookout for Ray McCoy. Last seen in the Fourth Sector. Subject is armed and extremely dangerous. Repeat armed and extremely dangerous.
				Game_Flag_Set(kFlagDispatcherTalkMcCoy);	 
			}
		}
	}
}

void SceneScriptUG03::PlayerWalkedOut() {
}

void SceneScriptUG03::DialogueQueueFlushed(int a1) {
}

} // End of namespace BladeRunner
