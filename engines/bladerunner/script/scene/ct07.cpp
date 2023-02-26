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

void SceneScriptCT07::InitializeScene() {
	Setup_Scene_Information(202.32f, -58.23f, -12.86f, 225);
	Actor_Put_In_Set(kActorZuben, kSetCT07);
	Actor_Set_At_XYZ(kActorZuben, -9.68f, -58.23f, 11.14f, 250);

	Ambient_Sounds_Add_Looping_Sound(kSfxCTRAIN1,  30,  90, 1);
	Ambient_Sounds_Add_Looping_Sound(kSfxCTDRONE1, 20,   1, 1);
	Ambient_Sounds_Add_Looping_Sound(kSfxCTAMBR1,  40, 100, 1);
	Ambient_Sounds_Add_Speech_Sound(kActorBlimpGuy,  0, 10u, 260u, 17, 24, -100, 100, -101, -101, 1, 1);
	Ambient_Sounds_Add_Speech_Sound(kActorBlimpGuy, 20, 10u, 260u, 17, 24, -100, 100, -101, -101, 1, 1);
	Ambient_Sounds_Add_Speech_Sound(kActorBlimpGuy, 40, 10u, 260u, 17, 24, -100, 100, -101, -101, 1, 1);
	Ambient_Sounds_Add_Speech_Sound(kActorBlimpGuy, 50, 10u, 260u, 17, 24, -100, 100, -101, -101, 1, 1);
	Ambient_Sounds_Add_Sound(kSfxSPIN2A,  80, 180, 16,  25,   0,   0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSPIN2B,  50, 180, 16,  25,   0,   0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxTHNDR2,  10,  60, 50, 100,   0,   0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxTHNDER2,  6,  50, 50, 100,   0,   0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxTHNDER4, 10,  70, 50, 100,   0,   0, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxDISH1,   10,  30, 12,  14, 100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxDISH2,   10,  30, 12,  14, 100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxDISH3,   10,  30, 12,  14, 100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxDISH4,   10,  30, 12,  14, 100, 100, -101, -101, 0, 0);
}

void SceneScriptCT07::SceneLoaded() {
	Obstacle_Object("BOX01", true);
	Obstacle_Object("BOX02", true);
	Obstacle_Object("BOX03", true);
	Obstacle_Object("BOX04", true);
	Unclickable_Object("BOX01");
	Unclickable_Object("BOX02");
	Unclickable_Object("BOX03");
	Unclickable_Object("BOX04");
}

bool SceneScriptCT07::MouseClick(int x, int y) {
	return true;
}

bool SceneScriptCT07::ClickedOn3DObject(const char *objectName, bool a2) {
	return false;
}

bool SceneScriptCT07::ClickedOnActor(int actorId) {
	return false;
}

bool SceneScriptCT07::ClickedOnItem(int itemId, bool a2) {
	return false;
}

bool SceneScriptCT07::ClickedOnExit(int exitId) {
	return false;
}

bool SceneScriptCT07::ClickedOn2DRegion(int region) {
	return false;
}

void SceneScriptCT07::SceneFrameAdvanced(int frame) {
}

void SceneScriptCT07::ActorChangedGoal(int actorId, int newGoal, int oldGoal, bool currentSet) {
}

void SceneScriptCT07::PlayerWalkedIn() {
	if (_vm->_cutContent) {
		Player_Gains_Control();
		if (Game_Flag_Query(kFlagZubenIsReplicant)) {
			Non_Player_Actor_Combat_Mode_On(kActorZuben, kActorCombatStateIdle, false, kActorMcCoy, 2, kAnimationModeCombatIdle, kAnimationModeCombatWalk, kAnimationModeCombatRun, 0, 0, 100, 15, 300, false);
			Game_Flag_Set(kFlagCT07ZubenAttack);
		}
		Actor_Face_Actor(kActorMcCoy, kActorZuben, true);
		// Made it so if McCoy decided to spare replicant Runciter he will automatically spare Zuben.
		if (Game_Flag_Query(kFlagZubenIsReplicant)) {
			if (Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)	
			&& !Game_Flag_Query(kFlagMcCoyShotAtZuben)) {
				Delay(1000);
				Non_Player_Actor_Combat_Mode_Off(kActorZuben);
				Game_Flag_Reset(kFlagCT07ZubenAttack);
				AI_Movement_Track_Flush(kActorZuben);
				Actor_Modify_Friendliness_To_Other(kActorZuben, kActorMcCoy, 5);
				Actor_Set_Goal_Number(kActorZuben, kGoalZubenCT07Spared);
				Game_Flag_Set(kFlagCT01ZubenGone);
				AI_Movement_Track_Flush(kActorZuben);
				Actor_Face_Actor(kActorZuben, kActorMcCoy, true);
				Player_Set_Combat_Mode(false);
				Actor_Says(kActorMcCoy, 455, -1); //00-0455.AUD	Relax. Nobody's gonna get retired. Okay?
				Actor_Says(kActorZuben, 100, 19);
				Actor_Says(kActorMcCoy, 470, 12); //00-0470.AUD	Just talk. That's all.
				Actor_Says(kActorZuben, 110, 18); //19-0110.AUD	So talk. 
				Actor_Says(kActorMcCoy, 475, 12);
				Actor_Says(kActorZuben, 120, 15); //19-0120.AUD	Aah, police…
				Actor_Says(kActorMcCoy, 480, 16);
				Actor_Says(kActorZuben, 130, 17); //19-0130.AUD	Rep detect?
				Actor_Says(kActorMcCoy, 485, 14);
				if (Player_Query_Agenda() == kPlayerAgendaSurly 
				|| Player_Query_Agenda() == kPlayerAgendaErratic) {
					Actor_Set_Goal_Number(kActorZuben, kGoalZubenCT07RunToFreeSlotA);
					Player_Set_Combat_Mode(true);
					Delay(1500);
					Actor_Face_Actor(kActorMcCoy, kActorZuben, true);
					Actor_Start_Speech_Sample(kActorMcCoy, 490); //00-0490.AUD	Suck on this, skin-job!
					Sound_Play(kSfxGUNH1A, 100, 0, 0, 50);
					Actor_Change_Animation_Mode(kActorMcCoy, 6);
					Actor_Modify_Friendliness_To_Other(kActorSteele, kActorMcCoy, 1);
					Actor_Modify_Friendliness_To_Other(kActorGuzza, kActorMcCoy, 1);
					Actor_Modify_Friendliness_To_Other(kActorClovis, kActorMcCoy, -1);
					Actor_Modify_Friendliness_To_Other(kActorHowieLee, kActorMcCoy, -1);
					Actor_Clue_Acquire(kActorZuben, kClueMcCoyShotZubenInTheBack, true, -1);
					Actor_Clue_Lose(kActorZuben, kClueMcCoyLetZubenEscape);
					Actor_Clue_Acquire(kActorMcCoy, kClueMcCoyShotZubenInTheBack, true, kActorZuben);
					Game_Flag_Reset(kFlagMcCoyIsHelpingReplicants);
					Game_Flag_Set(kFlagZubenEncounter);
					Actor_Set_Goal_Number(kActorGaff, kGoalGaffCT05Wait);
				} else {
					Actor_Set_Goal_Number(kActorZuben, kGoalZubenCT07RunToFreeSlotA);
					Game_Flag_Set(kFlagZubenSpared);
					Game_Flag_Set(kFlagZubenEncounter);
					Actor_Set_Goal_Number(kActorGaff, kGoalGaffCT05Wait);
					Actor_Clue_Acquire(kActorZuben, kClueMcCoyLetZubenEscape, true, -1);
					Actor_Clue_Acquire(kActorLucy, kClueMcCoyLetZubenEscape, true, -1);
					Actor_Modify_Friendliness_To_Other(kActorSteele, kActorMcCoy, -2);
					Actor_Modify_Friendliness_To_Other(kActorGuzza, kActorMcCoy, -2);
					Actor_Modify_Friendliness_To_Other(kActorClovis, kActorMcCoy, 2);
					Actor_Modify_Friendliness_To_Other(kActorHowieLee, kActorMcCoy, 2);
				}
				if (Random_Query(1, 3) < 3) {
					Actor_Clue_Acquire(kActorZuben, kClueMcCoysDescription, true, -1);
				}
				if (Random_Query(1, 5) < 5) {
					Actor_Clue_Acquire(kActorZuben, kClueMcCoyIsABladeRunner, true, -1);
				}
			} 
		} else {
			Actor_Says(kActorZuben, 100, 19);
			Actor_Says(kActorMcCoy, 470, 12); //00-0470.AUD	Just talk. That's all.
			Actor_Says(kActorZuben, 110, 18);
			Actor_Says(kActorMcCoy, 475, 12);
			Actor_Says(kActorMcCoy, 480, 16);
			Actor_Says(kActorMcCoy, 485, 14);
			Delay(1000);
			Actor_Says(kActorMcCoy, 7295, 11); //00-7295.AUD	The girl. I need to know where's the girl.
			if (Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
				Actor_Says(kActorZuben, 210, 12); //19-0210.AUD	She daughter. She with Clovis.
				Actor_Says(kActorZuben, 220, 14); //19-0220.AUD	You not hurt her.
				Actor_Says(kActorMcCoy, 7940, 13);	//00-7940.AUD	Right.
				Delay(1000);
				Actor_Says(kActorMcCoy, 7320, 17); //00-7320.AUD	Is she a Replicant?
				if (Game_Flag_Query(kFlagLucyIsReplicant)) {
					Delay(2000);
					Actor_Says(kActorMcCoy, 1885, kAnimationModeTalk); //00-1885.AUD	I’ll take that as a yes.
					Actor_Clue_Acquire(kActorMcCoy, kClueZubenTalksAboutLucy1, false, kActorZuben);
				} else {
					Delay(2000);
					Actor_Says(kActorMcCoy, 7335, 14); //00-7335.AUD	She's not a Replicant?
					Actor_Says(kActorZuben, 260, 15); //19-0260.AUD	She good girl. She stay with Clovis.
					Actor_Says(kActorZuben, 340, 15); //19-0340.AUD	You promise no hurt.
					Actor_Says(kActorMcCoy, 7345, 12); //00-7345.AUD	Right, no hurt. No hurt anymore.
					Actor_Clue_Acquire(kActorMcCoy, kClueZubenTalksAboutLucy2, false, kActorZuben);
				}
				Delay(1000);
				Actor_Says(kActorMcCoy, 7300, 13); //00-7300.AUD	Did you kill the animals?
				Actor_Says(kActorZuben, 270, 15); //19-0270.AUD	Because he bad.
				Actor_Says(kActorMcCoy, 7350, 14);	//00-7350.AUD	Runciter?
				Actor_Says(kActorZuben, 280, 12); //19-0280.AUD	He not pay. Bad to Lucy. Bad to everybody. Make people starve.
				Actor_Says(kActorMcCoy, 7355, 14); //00-7355.AUD	All those animals died.
				Music_Play(kMusicCrysDie1, 25, 0, 1, -1, kMusicLoopPlayOnce, 1);
				Actor_Says(kActorZuben, 290, 15); //19-0290.AUD	He made Lucy do bad things. Lucy hurt. Clovis more angry.
				if (Game_Flag_Query(kFlagLucyIsReplicant)) {
					Actor_Says(kActorZuben, 300, 14); //19-0300.AUD	Girl was forced to do bad things Off-World. Clovis thought Terra better.
					Actor_Says(kActorZuben, 310, 13); //19-0310.AUD	But Terra's no better for young girls. Runciter bad to Lucy.
				}
				Delay(2000);
				Actor_Says(kActorMcCoy, 7360, 11); //00-7360.AUD	Did he do things to Lucy?
				Delay(2000);
				Actor_Says(kActorMcCoy, 2390, kAnimationModeIdle); //00-2390.AUD	Oh, God. No.
				Delay(2000);
				if (Player_Query_Agenda() != kPlayerAgendaPolite) {
					Actor_Says(kActorMcCoy, 7365, 12);	//00-7365.AUD	You should have killed him.
				}
				Actor_Says(kActorZuben, 320, 12); //19-0320.AUD	Clovis say Runciter love animals. Runciter still alive so he hurt now. Know what pain is.
				Actor_Says(kActorZuben, 330, 12); //19-0330.AUD	Kill him, he not hurt. Just dead.
				Delay(1000);
				Actor_Says(kActorMcCoy, 7290, 12); //00-7290.AUD	Listen it's very important I talked to Clovis.
				Actor_Says(kActorZuben, 180, 15); //19-0180.AUD	No way. You enemy of Clovis.
				Actor_Says(kActorMcCoy, 7310, 16); //00-7310.AUD	No, I'm trying to help him and you.
				Actor_Says(kActorZuben, 190, 15); //19-0190.AUD	We do good without you. Do good without anybody.
				Actor_Says(kActorMcCoy, 5065, 18); //00-5065.AUD	Is that right?
				Actor_Clue_Acquire(kActorMcCoy, kClueZubensMotive, false, kActorZuben);
				Delay(2000);
				Actor_Says(kActorZuben, 170, 14); //19-0170.AUD	Now I go.
				Actor_Says(kActorMcCoy, 2860, 13); // YouTakeCareOfYourself
				Actor_Set_Goal_Number(kActorZuben, kGoalZubenCT07RunToFreeSlotA);
				Game_Flag_Set(kFlagZubenSpared);
				Game_Flag_Set(kFlagZubenEncounter);
				Actor_Set_Goal_Number(kActorGaff, kGoalGaffCT05Wait);
				Actor_Clue_Acquire(kActorZuben, kClueMcCoyLetZubenEscape, true, -1);
				Actor_Clue_Acquire(kActorLucy, kClueMcCoyLetZubenEscape, true, -1);
				Actor_Modify_Friendliness_To_Other(kActorSteele, kActorMcCoy, -2);
				Actor_Modify_Friendliness_To_Other(kActorGuzza, kActorMcCoy, -2);
				Actor_Modify_Friendliness_To_Other(kActorClovis, kActorMcCoy, 2);
				Actor_Modify_Friendliness_To_Other(kActorHowieLee, kActorMcCoy, 2);
			} else {
				Delay(2000);
				Actor_Says(kActorMcCoy, 8590, 13);  // Not the talkative type
				Delay(2000);
				Actor_Says(kActorZuben, 170, 14); //19-0170.AUD	Now I go.
				Actor_Says(kActorMcCoy, 7860, 14); //00-7860.AUD	Stay right where you are.
				Delay(1000);
				Actor_Says(kActorMcCoy, 3090, 15); //00-3090.AUD	You may not be a Rep but you’re a damn Rep sympathizer for sure.
				Actor_Says(kActorMcCoy, 3095, 14); //00-3095.AUD	Now we’re gonna take a little ride downtown.
				Game_Flag_Set(kFlagZubenSpared);
				Game_Flag_Set(kFlagZubenEncounter);
				Actor_Modify_Friendliness_To_Other(kActorSteele, kActorMcCoy, 1);
				Actor_Modify_Friendliness_To_Other(kActorGuzza, kActorMcCoy, 1);
				Actor_Modify_Friendliness_To_Other(kActorClovis, kActorMcCoy, -1);
				Actor_Modify_Friendliness_To_Other(kActorHowieLee, kActorMcCoy, -1);
				Actor_Clue_Acquire(kActorClovis, kClueMcCoyRetiredZuben, true, -1);
				Delay (1000);
				Music_Stop(1u);
				Game_Flag_Set(kFlagZubenArrested);
				Actor_Put_In_Set(kActorZuben, kSetPS09);
				Actor_Set_At_XYZ(kActorZuben, -399.5f, 0.2f, -255.0f, 512);
				Game_Flag_Reset(kFlagSpinnerAtCT01);
				Game_Flag_Set(kFlagSpinnerAtPS01);
				Scene_Exits_Enable();
				Game_Flag_Reset(kFlagMcCoyInChinaTown);
				Game_Flag_Set(kFlagMcCoyInPoliceStation);
				Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
				Ambient_Sounds_Remove_All_Looping_Sounds(1u);
				Actor_Set_Targetable(kActorZuben, false);
				Set_Enter(kSetPS09, kScenePS09);
			}
		}
	} else {
		Player_Gains_Control();
		Non_Player_Actor_Combat_Mode_On(kActorZuben, kActorCombatStateIdle, false, kActorMcCoy, 2, kAnimationModeCombatIdle, kAnimationModeCombatWalk, kAnimationModeCombatRun, 0, 0, 100, 15, 300, false);
		Game_Flag_Set(kFlagCT07ZubenAttack);
		Actor_Face_Actor(kActorMcCoy, kActorZuben, true);
	}
}

void SceneScriptCT07::PlayerWalkedOut() {
	Music_Stop(2u);
}

void SceneScriptCT07::DialogueQueueFlushed(int a1) {
}

} // End of namespace BladeRunner
