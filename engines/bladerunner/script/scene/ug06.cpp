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

void SceneScriptUG06::InitializeScene() {
	if (Game_Flag_Query(kFlagChapter4Intro)) {
		Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
		Ambient_Sounds_Remove_All_Looping_Sounds(1u);
		Outtake_Play(kOuttakeMovieC1, false, -1);
		if (Game_Flag_Query(kFlagLutherLanceIsReplicant)) {
			Outtake_Play(kOuttakeMovieC3, false, -1);
		} else {
			Outtake_Play(kOuttakeMovieC2, false, -1);
		}
		Game_Flag_Reset(kFlagChapter4Intro);
	}

	if (Game_Flag_Query(kFlagUG04toUG06)) {
		Setup_Scene_Information(  23.0f,   0.0f,  321.0f,   0);
	} else if (Game_Flag_Query(kFlagNR01toUG06)) {
		Setup_Scene_Information(  66.0f, 153.0f, -301.4f, 512);
	} else {
		Setup_Scene_Information(-165.0f,   1.0f,   89.0f, 990);
	}
	Scene_Exit_Add_2D_Exit(0,   0,  0,  30, 479, 3);
	Scene_Exit_Add_2D_Exit(1, 294, 68, 544, 236, 0);

	Ambient_Sounds_Add_Looping_Sound(kSfxFIREBD1, 18, 0, 1);
	Ambient_Sounds_Add_Looping_Sound(kSfxUGBED1,  40, 0, 1);
	Ambient_Sounds_Add_Looping_Sound(kSfxUGBED2,  40, 0, 1);
	Ambient_Sounds_Add_Sound(kSfxPIPER1,   2, 190, 12, 16, -100, 100, -100,  100, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSQUEAK1,  2, 190, 12, 16, -100, 100, -100,  100, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxYELL1M2,  2, 120, 11, 12, -100, 100, -100,  100, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxYELL1M3,  2, 120, 11, 12, -100, 100, -100,  100, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxGRUNT1M1, 2, 120, 11, 12, -100, 100, -100,  100, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxGRUNT2M3, 2, 120, 11, 12, -100, 100, -100,  100, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSQUEAK3,  2, 190, 12, 16, -100, 100, -100,  100, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxSQUEAK5,  2, 190, 12, 16, -100, 100, -100,  100, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBANG2,    2, 190, 12, 16, -100, 100, -100,  100, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBANG4,    2, 190, 12, 16, -100, 100, -100,  100, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBANG5,    2, 190, 12, 16, -100, 100, -100,  100, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBANG6,    2, 190, 12, 16, -100, 100, -100,  100, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBBGRN1,   5,  50, 17, 37, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBBGRN2,   5,  50, 17, 37, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxBBGRN3,   5,  50, 17, 37, -100, 100, -101, -101, 0, 0);
}

void SceneScriptUG06::SceneLoaded() {
	Obstacle_Object("BOX06", true);
	Unobstacle_Object("BOX06", true);
	Unobstacle_Object("BOX07", true);
	Unobstacle_Object("BOX16", true);
	Unobstacle_Object("BOX05", true);
}

bool SceneScriptUG06::MouseClick(int x, int y) {
	return false;
}

bool SceneScriptUG06::ClickedOn3DObject(const char *objectName, bool a2) {
	return false;
}

bool SceneScriptUG06::ClickedOnActor(int actorId) {
	return false;
}

bool SceneScriptUG06::ClickedOnItem(int itemId, bool a2) {
	return false;
}

bool SceneScriptUG06::ClickedOnExit(int exitId) {
	if (exitId == 0) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, 23.0f, 0.0f, 321.0f, 0, true, false, false)) {
			Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
			Ambient_Sounds_Remove_All_Looping_Sounds(1u);
			Game_Flag_Set(kFlagUG06toUG04);
			Set_Enter(kSetUG04, kSceneUG04);
		}
		return true;
	}

	if (exitId == 1) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, 66.0f, 0.0f, -90.0f, 0, true, false, false)) {
			Actor_Face_Heading(kActorMcCoy, 0, false);
			Loop_Actor_Travel_Stairs(kActorMcCoy, 17, true, kAnimationModeIdle);
			Loop_Actor_Walk_To_XYZ(kActorMcCoy, 66.0f, 153.0f, -446.0f, 0, false, false, false);
			Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
			Ambient_Sounds_Remove_All_Looping_Sounds(1u);
			Game_Flag_Set(kFlagUG06toNR01);
			Set_Enter(kSetNR01, kSceneNR01);
		}
		return true;
	}
	return false;
}

bool SceneScriptUG06::ClickedOn2DRegion(int region) {
	return false;
}

void SceneScriptUG06::SceneFrameAdvanced(int frame) {
}

void SceneScriptUG06::ActorChangedGoal(int actorId, int newGoal, int oldGoal, bool currentSet) {
}

void SceneScriptUG06::PlayerWalkedIn() {
	if (Game_Flag_Query(kFlagUG04toUG06)) {
		Loop_Actor_Walk_To_XYZ(kActorMcCoy, 23.0f, 0.0f, 273.0f, 0, false, false, false);
		Game_Flag_Reset(kFlagUG04toUG06);
	}

	if (Game_Flag_Query(kFlagNR01toUG06)) {
		Loop_Actor_Travel_Stairs(kActorMcCoy, 17, false, kAnimationModeIdle);
		Loop_Actor_Walk_To_XYZ(kActorMcCoy, 66.0f, 0.0f, -36.91f, 0, false, false, false);
		Game_Flag_Reset(kFlagNR01toUG06);
	}

	if ( Global_Variable_Query(kVariableChapter) == 4
	 && !Game_Flag_Query(kFlagUG06Chapter4Started)
	) {
		Player_Loses_Control(); 
		Actor_Voice_Over(2620, kActorVoiceOver); 
		Actor_Voice_Over(2630, kActorVoiceOver); 
		Actor_Voice_Over(2640, kActorVoiceOver); //99-2640.AUD	I didn’t know what it was. I didn’t know who I was.
		Actor_Voice_Over(2650, kActorVoiceOver); //99-2650.AUD	A cop dangling on the short end of the stick or a Rep whose memory banks had ran out.
		// Made it so McCoy only mentions not killing Izo if he actually didn't do that.
		if (_vm->_cutContent) {
			if (!Game_Flag_Query(kFlagMcCoyShotIzo)) {
				Actor_Voice_Over(2660, kActorVoiceOver); //99-2660.AUD	One thing I was sure of was that I didn’t kill Izo.
				Actor_Voice_Over(2670, kActorVoiceOver); //99-2670.AUD	That I know I experienced. And this misinformation…
				Actor_Voice_Over(2680, kActorVoiceOver); //99-2680.AUD	maybe it was the key to everything that was happening.
			}
		} else {
			Actor_Voice_Over(2660, kActorVoiceOver); //99-2660.AUD	One thing I was sure of was that I didn’t kill Izo.
			Actor_Voice_Over(2670, kActorVoiceOver); //99-2670.AUD	That I know I experienced. And this misinformation…
			Actor_Voice_Over(2680, kActorVoiceOver); //99-2680.AUD	maybe it was the key to everything that was happening.
		}
		Actor_Voice_Over(2690, kActorVoiceOver); //99-2690.AUD	Maybe there was a lot more than what met my eye.
		Actor_Voice_Over(2700, kActorVoiceOver); //99-2700.AUD	All I had to do was stay alive long enough to find out.
		if (_vm->_cutContent) {
			Delay(1000);
			Actor_Says(kActorMcCoy, 115, -1); //00-0115.AUD	Maggie.
			Delay(1000);
			Actor_Says(kActorMcCoy, 170, -1);
			Delay(1500);
			Actor_Says(kActorMcCoy, 6875, -1); //00-6875.AUD	I gotta go.
			if (Actor_Query_Goal_Number(kActorZuben) < kGoalZubenGone
			&& !Game_Flag_Query(kFlagZubenArrested)
			&& !Actor_Clue_Query(kActorMcCoy, kClueZubensMotive)) {
				Delay(1000);
				Actor_Put_In_Set(kActorZuben, kSetUG06);
				Actor_Set_At_XYZ(kActorZuben, 23.0f, 0.0f, 321.0f, 0);
				Loop_Actor_Walk_To_XYZ(kActorZuben, 59.61f, 0.41f, 172.63f, 0, false, false, false);
				Actor_Face_Actor(kActorZuben, kActorMcCoy, true);
				Actor_Face_Actor(kActorMcCoy, kActorZuben, true);
				Delay(1000);
				Actor_Says(kActorMcCoy, 8910, 11); //00-8910.AUD	Hey you.
				if (Game_Flag_Query(kFlagZubenIsReplicant)) {
					Actor_Says(kActorZuben, 140, 14); //19-0140.AUD	Stay away!
					Actor_Says(kActorMcCoy, 7280, 11); //00-7280.AUD	You remember me?
					Actor_Says(kActorZuben, 150, 15); //19-0150.AUD	You chased Zuben.
					if (Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
						Actor_Says(kActorMcCoy, 7285, 12); //00-7285.AUD	But I didn't kill you, did I?
					} else {
						Actor_Says(kActorMcCoy, 2790, 18); //00-2790.AUD	Uh-huh.
					}
				} else {
					Actor_Says(kActorZuben, 120, 18); //19-0120.AUD	Aah, police...
					Actor_Says(kActorMcCoy, 2790, 18); //00-2790.AUD	Uh-huh.
					Actor_Says(kActorZuben, 160, 13); //19-0160.AUD	You following me?
					Actor_Says(kActorMcCoy, 7305, 15); //00-7305.AUD	No, it's just a coincidence.
					Delay(1000);	
				}
				Actor_Says(kActorMcCoy, 4270, kAnimationModeTalk); //00-4270.AUD	I got some more questions for you.
				Delay(500);
				if (Actor_Query_Goal_Number(kActorLucy) < kGoalLucyGone 
				&& Global_Variable_Query(kVariableAffectionTowards) == kAffectionTowardsLucy) {
					Actor_Says(kActorMcCoy, 7295, 11); //00-7295.AUD	The girl. I need to know where's the girl.
					if (Game_Flag_Query(kFlagZubenIsReplicant)) {
						Actor_Says(kActorZuben, 200, 12); //19-0200.AUD	Girl?
						Actor_Says(kActorMcCoy, 7315, 16); //00-7315.AUD	Lucy.
					}
					Actor_Says(kActorZuben, 210, 12); //19-0210.AUD	She daughter. She with Clovis.
					Actor_Says(kActorZuben, 220, 14); //19-0220.AUD	You not hurt her.
					if (Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
						Actor_Says(kActorMcCoy, 7940, 13);	//00-7940.AUD	Right.
						Delay(1000);
					}
					if (!Actor_Clue_Query(kActorMcCoy, kClueVKLucyHuman)
					&& !Actor_Clue_Query(kActorMcCoy, kClueVKLucyReplicant)) {
						Actor_Says(kActorMcCoy, 7320, 17); //00-7320.AUD	Is she a Replicant?
						if (Game_Flag_Query(kFlagLucyIsReplicant)) {
							if (Game_Flag_Query(kFlagZubenIsReplicant)) {
								Actor_Says(kActorZuben, 230, 14); //19-0230.AUD	Daughter sick. Only four years to live. Four years. Daughter Zuben whole family.
								Actor_Says(kActorMcCoy, 7325, 17); //00-7325.AUD	I know.
							} else {
								Delay(2000);
								Actor_Says(kActorMcCoy, 2750, kAnimationModeTalk); //00-2750.AUD	Okay, I get the picture.
							}
							Actor_Says(kActorZuben, 240, 15); //19-0240.AUD	But Clovis he fix.
							if (Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
								Actor_Says(kActorMcCoy, 7330, 16); //00-7330.AUD	Let's hope so.
							}
							Actor_Clue_Acquire(kActorMcCoy, kClueZubenTalksAboutLucy1, false, kActorZuben);
						} else {
							if (Game_Flag_Query(kFlagZubenIsReplicant)) {
								Actor_Says(kActorZuben, 250, 14); //19-0250.AUD	Daughter not like me.
							} else {
								Delay(2000);
							}
							Actor_Says(kActorMcCoy, 7335, 14); //00-7335.AUD	She's not a Replicant?
							Actor_Says(kActorZuben, 260, 15); //19-0260.AUD	She good girl. She stay with Clovis.
							Actor_Says(kActorMcCoy, 7340, 16); //00-7340.AUD	I know.
							Actor_Says(kActorZuben, 340, 15); //19-0340.AUD	You promise no hurt.
							if (Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {	
								Actor_Says(kActorMcCoy, 7345, 12); //00-7345.AUD	Right, no hurt. No hurt anymore.
							} else {
								Delay(1000);
							}
							Actor_Clue_Acquire(kActorMcCoy, kClueZubenTalksAboutLucy2, false, kActorZuben);
						}
					}
				}
				Delay(500);
				if (!Actor_Clue_Query(kActorMcCoy, kClueLucyInterview)) {
					Actor_Says(kActorMcCoy, 7300, 13); //00-7300.AUD	Did you kill the animals?
				} else {
					Actor_Says(kActorMcCoy, 7355, 14); //00-7355.AUD	All those animals died.
				}
				Actor_Says(kActorZuben, 270, 15); //19-0270.AUD	Because he bad.
				Actor_Says(kActorMcCoy, 7350, 14);	//00-7350.AUD	Runciter?
				Actor_Says(kActorZuben, 280, 12); //19-0280.AUD	He not pay. Bad to Lucy. Bad to everybody. Make people starve.
				if (!Actor_Clue_Query(kActorMcCoy, kClueLucyInterview)) {
					Actor_Says(kActorMcCoy, 7355, 14); //00-7355.AUD	All those animals died.
				}
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
				Delay(1000);
				if (Player_Query_Agenda() != kPlayerAgendaPolite) {
					Actor_Says(kActorMcCoy, 7365, 12);	//00-7365.AUD	You should have killed him.
				}
				Actor_Says(kActorZuben, 320, 12); //19-0320.AUD	Clovis say Runciter love animals. Runciter still alive so he hurt now. Know what pain is.
				Actor_Says(kActorZuben, 330, 12); //19-0330.AUD	Kill him, he not hurt. Just dead.
				Actor_Clue_Acquire(kActorMcCoy, kClueZubensMotive, false, kActorZuben);
				Delay(2000);
				Actor_Says(kActorMcCoy, 7290, 12); //00-7290.AUD	Listen it's very important I talked to Clovis.
				if (!Game_Flag_Query(kFlagZubenIsReplicant)) {
					Actor_Says(kActorZuben, 180, 15); //19-0180.AUD	No way. You enemy of Clovis.
					if (Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
						Actor_Says(kActorMcCoy, 7310, 16); //00-7310.AUD	No, I'm trying to help him and you.
						Actor_Says(kActorZuben, 190, 15); //19-0190.AUD	We do good without you. Do good without anybody.
						Actor_Says(kActorMcCoy, 5065, 18); //00-5065.AUD	Is that right?
						Delay(2000);
					} else {
						Delay(2000);
					}
				} else {
					Delay(2000);
				}
				Actor_Says(kActorZuben, 170, 14); //19-0170.AUD	Now I go.
				if (Player_Query_Agenda() == kPlayerAgendaPolite) {
					Delay(1000);
					Actor_Says(kActorMcCoy, 2860, 13); // YouTakeCareOfYourself
				}
				Loop_Actor_Walk_To_XYZ(kActorZuben, 23.0f, 0.0f, 321.0f, 0, true, false, false);
				Actor_Put_In_Set(kActorZuben, kSetUG04);
				Player_Gains_Control();
			}
		}
		Player_Gains_Control();
		Game_Flag_Set(kFlagUG06Chapter4Started);
		Autosave_Game(2);
	}
	//return false;
}

void SceneScriptUG06::PlayerWalkedOut() {
}

void SceneScriptUG06::DialogueQueueFlushed(int a1) {
}

} // End of namespace BladeRunner
