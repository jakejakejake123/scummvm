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

void SceneScriptHC01::InitializeScene() {
	int loop = kMusicLoopRepeat;
	if (_vm->_cutContent && Random_Query(0, 2) == 1) {
		loop = kMusicLoopRepeatRandomStart;
	}
	Music_Play(kMusicArabLoop, 31, 0, 2, -1, loop, 2);
	if (Game_Flag_Query(kFlagHC02toHC01)) {
		Setup_Scene_Information( 64.0f, 0.14f,  83.0f, 266);
	} else if (Game_Flag_Query(kFlagHC03toHC01)) {
		Setup_Scene_Information(607.0f, 0.14f,   9.0f, 530);
	} else {
		Setup_Scene_Information(780.0f, 0.14f, 153.0f, 815);
	}

	Scene_Exit_Add_2D_Exit(0, 0, 460, 639, 479, 2);
	if (Game_Flag_Query(kFlagHC03Available)) {
		Scene_Exit_Add_2D_Exit(1, 394, 229, 485, 371, 1);
	}
	Scene_Exit_Add_2D_Exit(2, 117, 0, 286, 319, 0);
	if (_vm->_cutContent && !Game_Flag_Query(kFlagMcCoyCommentsOnAnimoids)) {
		Scene_2D_Region_Add(0, 110, 385, 200, 450); // cage 1
		Scene_2D_Region_Add(1, 20, 249, 110, 319);  // cage 2
	}
	// There is unused dialogue where McCoy tells Izo that he tried to convince Crystal that Izo isn't smuggling weapons and Izo says that he'll work things out with Crystal.
	// I decided to implement this scenario where McCoy does indeed try to convince Crystal. I will add the options Crystal and Voight kampff when you are talking to Izo and if you
	// to warn Izo about Crystal you can catch him in the sewers. This scene will also use cut dialogue and  will also tigger a scene where you talk to Crystal and 
	// try to convince her. In act 3 Izo will be outside his shop and you can warn him again about Crystal and this will lead to his weapons not being taken by the place like he says 
	// in unused dialogue later on.  This code will put Izo into the set if you did help him out. 
	if (_vm->_cutContent) {
		if (Global_Variable_Query(kVariableChapter) == 3) {
			if	(Game_Flag_Query(kFlagIzoWarned)) {
				Actor_Put_In_Set(kActorIzo, kSetHC01_HC02_HC03_HC04);
				Actor_Set_At_XYZ(kActorIzo, 605.53, 0.95, 39.46, 524);
			}
		}
	}

	Ambient_Sounds_Add_Looping_Sound(kSfxRAINAWN1, 50, 50, 0);
	Ambient_Sounds_Add_Looping_Sound(kSfxHCLOOP1,  50, 50, 0);
	Ambient_Sounds_Add_Sound(kSfxHCANM8,   3, 30, 16, 16, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxHCANM2,   3, 30, 16, 16, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxHCANM3,   3, 30, 16, 16, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxHCANM4,   3, 30, 16, 16, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxHCANM5,   3, 30, 16, 16, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxHCANM6,   3, 30, 16, 16, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxHCANM7,   3, 30, 16, 16, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxHCANM1,   3, 30, 16, 16, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0470R, 5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0480R, 5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0500R, 5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0540R, 5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0560R, 5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0870R, 5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0900R, 5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0940R, 5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_0960R, 5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_1070R, 5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_1080R, 5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_1100R, 5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_1140R, 5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfx67_1160R, 5, 70, 12, 12, -100, 100, -101, -101, 0, 0);
	Scene_Loop_Set_Default(0);
}

void SceneScriptHC01::SceneLoaded() {
	Obstacle_Object("PILLAR", true);
	if (Game_Flag_Query(kFlagAR01toHC01)) {
		Preload(kModelAnimationMcCoyIdle);
		Preload(kModelGenWalkerHattedPersonWithUmbrellaStandsStill);
		Preload(kModelGenWalkerHoodedPersonWithUmbrellaStandsStill);
		Preload(kModelGenWalkerHattedLadyWithWoodenUmbrellaStandsStill);
		Preload(kModelGenWalkerHattedPersonNoUmbrellaStandsStill);
		Preload(kModelGenWalkerPunkPersonWithGlassesAndBeardStandsStill);
		Preload(kModelGenWalkerPunkPersonWithGlassesStandsStill);
		Preload(kModelGenWalkerHattedPersonWithUmbrella);
		Preload(kModelGenWalkerHoodedPersonWithUmbrella);
		Preload(kModelGenWalkerHattedPersonWithWoodenUmbrella);
		Preload(kModelGenWalkerPunkPersonWithGlassesAndBeard);
		Preload(kModelGenWalkerHattedPersonNoUmbrellaSmallSteps);
		Preload(kModelGenWalkerPunkPersonWithGlasses);
	}
}

bool SceneScriptHC01::MouseClick(int x, int y) {
	return false;
}

bool SceneScriptHC01::ClickedOn3DObject(const char *objectName, bool a2) {
	return false;
}

bool SceneScriptHC01::ClickedOnActor(int actorId) {
	if (actorId == kActorIzo
	 && (Actor_Query_Goal_Number(kActorIzo) == kGoalIzoGoToHC01
	  || Actor_Query_Goal_Number(kActorIzo) == kGoalIzoDefault
	 )
	) {
		AI_Movement_Track_Pause(kActorIzo);
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, 624.43f, 0.14f, 83.0f, 0, true, false, false)) {
			if (!Game_Flag_Query(kFlagHC01IzoTalk1)) {
				Actor_Face_Actor(kActorIzo, kActorMcCoy, true);
				Actor_Face_Actor(kActorMcCoy, kActorIzo, true);
				if (_vm->_cutContent) {
					if (Player_Query_Agenda() != kPlayerAgendaPolite) {	
						Actor_Says(kActorMcCoy, 4560, 23); //00-4560.AUD	McCoy, LPD.
					} else {
						Actor_Says(kActorMcCoy, 1280, 23); //00-1280.AUD	McCoy, LPD. Mind if I ask you a couple of questions?
					}
					if (Game_Flag_Query(kFlagIzoIsReplicant)) {
						Actor_Says_With_Pause(kActorIzo, 0, 0.2f, 13); //07-0000.AUD	There's a clock I always set.
						Actor_Says_With_Pause(kActorIzo, 10, 0.2f, 13); //07-0010.AUD	Two minutes.
						Actor_Says(kActorIzo, 20, 17); //07-0020.AUD	That's how much time I give every stranger that wanders in here off the street.
						if (Player_Query_Agenda() != kPlayerAgendaPolite) {
							Actor_Says(kActorMcCoy, 1035, 18); //00-1035.AUD	Sell a lot of stuff that way?
						} else {
							Actor_Says(kActorMcCoy, 4880, 13); //00-4880.AUD	Is that right?
						}
						Actor_Says_With_Pause(kActorIzo, 30, 0.2f, 17); //07-0030.AUD	I don't encourage browsers.
						if (Actor_Query_Intelligence(kActorIzo) == 85) {
							Actor_Says_With_Pause(kActorIzo, 40, 0.0f, 13); //07-0040.AUD	What impresses me are people who know what they want
							Actor_Says(kActorIzo, 50, 12); //07-0050.AUD	and are not afraid to pay for it.
						}
						Actor_Says(kActorMcCoy, 8320, 13); // 00-8320.AUD	Really?
						Actor_Says(kActorIzo, 80, 18); //07-0080.AUD	Everything here is guaranteed. The finest most authentic anyone can get.
						if (Player_Query_Agenda() == kPlayerAgendaSurly 
						|| Player_Query_Agenda() == kPlayerAgendaErratic) {
							Actor_Says(kActorMcCoy, 8575, 14); // More useless junk.
							Actor_Says(kActorIzo, 410, 18); //07-0410.AUD	I won't lie to you detective.
							Actor_Says(kActorMcCoy, 2485, 13); //00-2485.AUD	I’ve a hard time believing that.
							Actor_Modify_Friendliness_To_Other(kActorIzo, kActorMcCoy, -2);
						} else {
							Actor_Says_With_Pause(kActorMcCoy, 1040, 1.2f, 13); //00-1040.AUD	What's the most expensive thing you got in here?
							if (Actor_Query_Intelligence(kActorIzo) == 85) {	
								Actor_Says(kActorIzo, 60, 16); //07-0060.AUD	Value is a relative notion.
								Actor_Says_With_Pause(kActorIzo, 70, 1.0f, 13); //07-0070.AUD	What's significant to you might be meaningless to me.
								Actor_Says_With_Pause(kActorMcCoy, 1045, 0.6f, 14); //00-1045.AUD	And vice versa.
							} else if (Actor_Query_Intelligence(kActorIzo) == 65) {
								Actor_Says(kActorIzo, 80, 18); //07-0080.AUD	Everything here is guaranteed. The finest most authentic anyone can get.
							}
						}
					} else {
						Delay (1000);
						Actor_Says(kActorIzo, 440, 12); //07-0440.AUD	I am nothing but a humble salesman.
						if (Player_Query_Agenda() == kPlayerAgendaSurly 
						|| Player_Query_Agenda() == kPlayerAgendaErratic) {
							Actor_Says(kActorMcCoy, 7835, 13); //00-7835.AUD	Is that so?
							Actor_Says(kActorIzo, 410, 18); //07-0410.AUD	I won't lie to you detective.
							Actor_Says(kActorMcCoy, 2485, 13); //00-2485.AUD	I’ve a hard time believing that.
							Actor_Modify_Friendliness_To_Other(kActorIzo, kActorMcCoy, -2);
						} else {
							Actor_Says(kActorMcCoy, 7940, 13); //00-7940.AUD	Right.
							Delay(500);
							Actor_Says_With_Pause(kActorMcCoy, 1040, 1.2f, 13); //00-1040.AUD	What's the most expensive thing you got in here?
							if (Actor_Query_Intelligence(kActorIzo) > 75) {	
								Actor_Says(kActorIzo, 60, 16); //07-0060.AUD	Value is a relative notion.
								Actor_Says_With_Pause(kActorIzo, 70, 1.0f, 13); //07-0070.AUD	What's significant to you might be meaningless to me.
								Actor_Says_With_Pause(kActorMcCoy, 1045, 0.6f, 14); //00-1045.AUD	And vice versa.
							} else if (Actor_Query_Intelligence(kActorIzo) == 65) {
								Actor_Says(kActorIzo, 80, 18); //07-0080.AUD	Everything here is guaranteed. The finest most authentic anyone can get.
							}
						}		
					}
				} else {
					Actor_Says_With_Pause(kActorIzo, 10, 0.2f, 13); //07-0010.AUD	Two minutes.
					Actor_Says(kActorIzo, 20, 17); //07-0020.AUD	That's how much time I give every stranger that wanders in here off the street.
					Actor_Says(kActorMcCoy, 1035, 18); //00-1035.AUD	Sell a lot of stuff that way?
					Actor_Says_With_Pause(kActorIzo, 30, 0.2f, 17);
					Actor_Says_With_Pause(kActorIzo, 40, 0.0f, 13);
					Actor_Says(kActorIzo, 50, 12);
					Actor_Says_With_Pause(kActorMcCoy, 1040, 1.2f, 13);
					Actor_Says(kActorIzo, 60, 16);
					Actor_Says_With_Pause(kActorIzo, 70, 1.0f, 13);
					Actor_Says_With_Pause(kActorMcCoy, 1045, 0.6f, 14);
					Actor_Says(kActorIzo, 80, 18); //07-0080.AUD	Everything here is guaranteed. The finest most authentic anyone can get.
				}
				Game_Flag_Set(kFlagHC01IzoTalk1);
			} else {
				Actor_Face_Actor(kActorMcCoy, kActorIzo, true);
				Actor_Face_Actor(kActorIzo, kActorMcCoy, true);
				dialogueWithIzo();
			}
		}
		AI_Movement_Track_Unpause(kActorIzo);
	}
#if BLADERUNNER_ORIGINAL_BUGS
#else
	// barkeep is click-able from afar
	// Add behavior similar to Howie Lee (CT12), Hasan, and Insect Dealer (AR01).
	else if (actorId == kActorHawkersBarkeep) {
		Actor_Face_Actor(kActorMcCoy, actorId, true);
		Actor_Says(kActorMcCoy, 8910, 14); 
		// This is the code for the conversation that you have with Izo if you warned him about Crystal.
	} else if (_vm->_cutContent
	&& actorId == kActorIzo 
	&& Game_Flag_Query(kFlagIzoWarned)) {
		if (!Game_Flag_Query(kFlagIzoPrepared)) {
			Loop_Actor_Walk_To_XYZ(kActorMcCoy, 624.43f, 0.14f, 83.0f, 0, true, false, false);
			Actor_Face_Actor(kActorMcCoy, kActorIzo, true);
			Actor_Face_Actor(kActorIzo, kActorMcCoy, true);
			Actor_Says(kActorMcCoy, 6745, 13); //00-6745.AUD	Izo, we gotta talk.
			Actor_Says(kActorMcCoy, 3845, 15); //00-3845.AUD	One of my associates is after you and your friends.
			Actor_Says(kActorMcCoy, 6715, 14); //00-6715.AUD	I tried to convince her that you weren’t running weapons to the Rep Underground.
			Actor_Says(kActorIzo, 860, 17); //07-0860.AUD	I’ll meet up with her some day. We’ll clear the air.
			Actor_Says(kActorMcCoy, 6725, 15); //00-6725.AUD	Clovis and Sadik are a dangerous group to hang with. And Crystal is on to them.
			Actor_Says(kActorMcCoy, 6720, 18); //00-6720.AUD	Watch your back.
			Actor_Says(kActorIzo, 710, 17); //07-0710.AUD	You’re a better man than I imagined.
			Game_Flag_Set(kFlagIzoPrepared);
		} else {
			Loop_Actor_Walk_To_XYZ(kActorMcCoy, 624.43f, 0.14f, 83.0f, 0, true, false, false);
			Actor_Face_Actor(kActorMcCoy, kActorIzo, true);
			Actor_Face_Actor(kActorIzo, kActorMcCoy, true);
			Actor_Says(kActorMcCoy, 2860, 13); // YouTakeCareOfYourself
		}
	}
#endif // BLADERUNNER_ORIGINAL_BUGS
	return false;
}

bool SceneScriptHC01::ClickedOnItem(int itemId, bool a2) {
	if (itemId == kItemCamera) {
		Item_Remove_From_World(kItemCamera);
		Item_Pickup_Spin_Effect(kModelAnimationIzoCamera, 361, 381);
		Delay(1500);
		Item_Pickup_Spin_Effect(kModelAnimationPhoto, 377, 397);
		Delay(1500);
		Item_Pickup_Spin_Effect(kModelAnimationPhoto, 330, 384);
		if (Game_Flag_Query(kFlagAR02DektoraBoughtScorpions)) {
			Actor_Clue_Acquire(kActorMcCoy, kCluePhotoOfMcCoy1, true, kActorIzo);
		} else {
			Actor_Clue_Acquire(kActorMcCoy, kCluePhotoOfMcCoy2, true, kActorIzo);
		}
		Actor_Clue_Acquire(kActorMcCoy, kClueChinaBar, true, kActorIzo);
		if (!Game_Flag_Query(kFlagDNARowAvailableTalk)) {
			if (Player_Query_Agenda() == kPlayerAgendaSurly 
			|| Player_Query_Agenda() == kPlayerAgendaErratic
			|| !Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {	
				Player_Set_Combat_Mode(true);
			}
		}
		return true;
	}
	return false;
}

bool SceneScriptHC01::ClickedOnExit(int exitId) {
	if (exitId == 0) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, 814.0f, 0.14f, 153.0f, 0, true, false, false)) {
			Music_Adjust(12, 0, 2u);
			Game_Flag_Set(kFlagHC01toAR01);
			Set_Enter(kSetAR01_AR02, kSceneAR01);
			Game_Flag_Reset(kFlagMcCoyInHawkersCircle);
			Game_Flag_Set(kFlagMcCoyInAnimoidRow);
		}
		return true;
	}

	if (exitId == 1) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, 607.0f, 0.14f, 9.0f, 0, true, false, false)) {
			Set_Enter(kSetHC01_HC02_HC03_HC04, kSceneHC03);
		}
		return true;
	}

	if (exitId == 2) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, 105.0f, 0.14f, 103.0f, 0, true, false, false)) {
			Game_Flag_Set(kFlagHC01toHC02);
			Async_Actor_Walk_To_XYZ(kActorMcCoy, -57.0f, 0.14f, 83.0f, 0, false);
			Set_Enter(kSetHC01_HC02_HC03_HC04, kSceneHC02);
		}
		return true;
	}
	return false;
}

bool SceneScriptHC01::ClickedOn2DRegion(int region) {
	if (_vm->_cutContent) {
		if (!Game_Flag_Query(kFlagMcCoyCommentsOnAnimoids) && (region == 0 || region == 1) ) {
			Game_Flag_Set(kFlagMcCoyCommentsOnAnimoids);
			//Actor_Face_Heading(kActorMcCoy, 389, false);
			Actor_Face_XYZ(kActorMcCoy, 740.89f, 60.29f, 220.12f, true);
			Actor_Voice_Over(890, kActorVoiceOver);
			if (!Game_Flag_Query(kFlagMcCoyIsHelpingReplicants)) {
				Actor_Voice_Over(900, kActorVoiceOver);
			}
			Scene_2D_Region_Remove(0);
			Scene_2D_Region_Remove(1);
			return true;
		}
	}
	return false;
}

void SceneScriptHC01::SceneFrameAdvanced(int frame) {
	Set_Fade_Color(1.0f, 1.0f, 1.0f);

	if (frame >= 61
	 && frame < 65
	) {
		Set_Fade_Density((frame - 61) / 4.0f);
	} else if (frame >= 65
	        && frame < 93
	) {
		Set_Fade_Density(1.0f);
	} else if (frame >= 93
	        && frame < 106
	) {
		Set_Fade_Density((105 - frame) / 13.0f);
	} else {
		Set_Fade_Density(0.0f);
	}

	if (frame == 61) {
		Ambient_Sounds_Play_Sound(kSfxCAMERA2,  90,   0,   0, 0);
	}

	if (frame == 65) {
		Ambient_Sounds_Play_Sound(kSfxRUNAWAY1, 50,   0, 100, 0);
	}

	if (frame == 80) {
		Ambient_Sounds_Play_Sound(kSfxTRPDOOR1, 40, 100, 100, 0);
		Item_Add_To_World(kItemGreenPawnLock, kModelAnimationBadge, kSetHC01_HC02_HC03_HC04, 582.0f, 27.0f, -41.0f, 0, 8, 8, true, true, false, true); // TODO a bug? reusing still animation of kModelAnimationBadge
	}
}

void SceneScriptHC01::ActorChangedGoal(int actorId, int newGoal, int oldGoal, bool currentSet) {
}

void SceneScriptHC01::PlayerWalkedIn() {
	if (Game_Flag_Query(kFlagHC02toHC01)) {
		Loop_Actor_Walk_To_XYZ(kActorMcCoy, 105.0f, 0.14f, 103.0f, 0, false, false, false);
		Game_Flag_Reset(kFlagHC02toHC01);
	}

	if (Game_Flag_Query(kFlagHC03toHC01)) {
		Game_Flag_Reset(kFlagHC03toHC01);
	}

	if (Game_Flag_Query(kFlagAR01toHC01)) {
		Game_Flag_Reset(kFlagAR01toHC01);
	}
}

void SceneScriptHC01::PlayerWalkedOut() {
	Set_Fade_Density(0.0f);
	Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
	Ambient_Sounds_Remove_All_Looping_Sounds(1u);
}

void SceneScriptHC01::DialogueQueueFlushed(int a1) {
}

void SceneScriptHC01::dialogueWithIzo() {
	if (!Game_Flag_Query(kFlagHC01IzoTalk2)) {
		Actor_Says(kActorMcCoy, 1055, 13);
		if (_vm->_cutContent) {
			Actor_Says(kActorIzo, 130, 13);
			if (Player_Query_Agenda() != kPlayerAgendaPolite) {
				Actor_Says_With_Pause(kActorMcCoy, 1060, 0.2f, 13); //00-1060.AUD	Doesn't matter. I don't read anyhow. What's your name?
			} else {
				Actor_Says(kActorMcCoy, 7395, 13); //00-7395.AUD	What's your name?
			}
		} else {
			Actor_Says(kActorIzo, 130, 13);
			Actor_Says_With_Pause(kActorMcCoy, 1060, 0.2f, 13); //00-1060.AUD	Doesn't matter. I don't read anyhow. What's your name?
		}
		Actor_Says(kActorIzo, 140, 13);
		Game_Flag_Set(kFlagHC01IzoTalk2);
	}

	Dialogue_Menu_Clear_List();
	if (_vm->_cutContent) {
		if (Actor_Clue_Query(kActorMcCoy, kCluePeruvianLadyInterview)
		&& !Actor_Clue_Query(kActorMcCoy, kClueIzoInterview)) {
			DM_Add_To_List_Never_Repeat_Once_Selected(1020, 6, 7, 8); // DRAGONFLY JEWERLY
		} else if (Actor_Clue_Query(kActorMcCoy, kClueDragonflyEarring)
				|| Actor_Clue_Query(kActorMcCoy, kClueBombingSuspect)
				|| Actor_Clue_Query(kActorMcCoy, kClueDragonflyAnklet)
		) {
			DM_Add_To_List_Never_Repeat_Once_Selected(1010, 6, 7, 8); // INSECT JEWELRY
		}
	} else if (Actor_Clue_Query(kActorMcCoy, kCluePeruvianLadyInterview)) {
		DM_Add_To_List_Never_Repeat_Once_Selected(1020, 6, 7, 3); // DRAGONFLY JEWERLY
	} else if (Actor_Clue_Query(kActorMcCoy, kClueDragonflyEarring)
	        || Actor_Clue_Query(kActorMcCoy, kClueBombingSuspect)
	        || Actor_Clue_Query(kActorMcCoy, kClueDragonflyAnklet)
	) {
		DM_Add_To_List_Never_Repeat_Once_Selected(1010, 6, 7, 3); // INSECT JEWELRY
	}
	if (Actor_Clue_Query(kActorMcCoy, kClueBobInterview1)) {
		DM_Add_To_List_Never_Repeat_Once_Selected(1030, 4, 5, 7); // WEAPONS
	} else if (Actor_Clue_Query(kActorMcCoy, kClueShellCasings)) {
		DM_Add_To_List_Never_Repeat_Once_Selected(1040, 4, 5, 6); // SHELL CASINGS
	}
	// Added in the options to VK Izo and warn him about Crystal.
	if (_vm->_cutContent) {
		if (Actor_Clue_Query(kActorMcCoy, kClueGrigorianInterviewB1)
		|| Actor_Clue_Query(kActorMcCoy, kClueGrigorianInterviewB2)) {
			if (Player_Query_Agenda() != kPlayerAgendaPolite) {
				DM_Add_To_List(1100, -1, 2, 3); // VOIGT-KAMPFF
			} else {
				DM_Add_To_List(1110, 2, -1, -1); // CRYSTAL
			}			
		}
	}
#if BLADERUNNER_ORIGINAL_BUGS
	if (Actor_Clue_Query(kActorMcCoy, kClueGrigorianInterviewB2)) {
		DM_Add_To_List_Never_Repeat_Once_Selected(1050, -1, 3, 8); // GRIGORIAN 1
	} else if (Actor_Clue_Query(kActorMcCoy, kClueGrigorianInterviewB1)) {
		DM_Add_To_List_Never_Repeat_Once_Selected(1060, -1, 3, 8); // GRIGORIAN 2
	}
#else
	// When McCoy has kClueGrigorianInterviewB1 then Izo is a Replicant
	// and when he has kClueGrigorianInterviewB2 then Izo is a human
	// However the dialogue menu options are actually reversed in the original
	// and inconsistent with what Grigorian says in his interviews.
	// The 1050 dialogue menu option belongs to the case where Izo is a Replicant
	// because in that dialogue McCoy mentions that Grigorian described him to a tee (which he does in kClueGrigorianInterviewB1)
	// And the 1060 dialogue menu option belongs to the case where Izo is a human
	// because in that dialogue McCoy talks about how Izo is a psychopath and was thrown out of CARS
	// which is what Grigorian says in kClueGrigorianInterviewB2
	if (_vm->_cutContent) {
		if (Actor_Clue_Query(kActorMcCoy, kClueGrigorianInterviewB1)) {
			DM_Add_To_List_Never_Repeat_Once_Selected(1050, 3, 4, 5); // GRIGORIAN 1
		} else if (Actor_Clue_Query(kActorMcCoy, kClueGrigorianInterviewB2)) {
			DM_Add_To_List_Never_Repeat_Once_Selected(1060, 3, 4, 5); // GRIGORIAN 2
		}
	} else if (Actor_Clue_Query(kActorMcCoy, kClueGrigorianInterviewB1)) {
		DM_Add_To_List_Never_Repeat_Once_Selected(1050, -1, 3, 8); // GRIGORIAN 1
	} else if (Actor_Clue_Query(kActorMcCoy, kClueGrigorianInterviewB2)) {
		DM_Add_To_List_Never_Repeat_Once_Selected(1060, -1, 3, 8); // GRIGORIAN 2
	}
#endif // BLADERUNNER_ORIGINAL_BUGS

	if (Dialogue_Menu_Query_List_Size() == 0) {
		Actor_Says_With_Pause(kActorMcCoy, 1105, 1.2f, 13);
		if (Actor_Query_Friendliness_To_Other(kActorIzo, kActorMcCoy) < 50) {
			if (_vm->_cutContent) {
				if (Game_Flag_Query(kFlagIzoIsReplicant)) {
					Actor_Says(kActorIzo, 550, 15);
				} else {
					Delay(2000);
					Actor_Says(kActorMcCoy, 8395, 18); //00-8395.AUD	You don't have anything to say?
					Delay(1000);
				}
			} else {
				Actor_Says(kActorIzo, 550, 15);
			}
			Actor_Says(kActorMcCoy, 1220, 14); // you can bet...
			Actor_Says(kActorIzo, 560, kAnimationModeTalk); // i'll be here
		} else {
			Actor_Says(kActorIzo, 250, 13);
			Actor_Modify_Friendliness_To_Other(kActorIzo, kActorMcCoy, -1);
			if (Actor_Query_Friendliness_To_Other(kActorIzo, kActorMcCoy) < 47
			 && Query_Difficulty_Level() == kGameDifficultyEasy
			) {
				takePhotoAndRunAway();
			}
		}
		return;
	}

	Dialogue_Menu_Add_DONE_To_List(100); // DONE

	bool end = false;
	do {
		Dialogue_Menu_Appear(320, 240);
		int answer = Dialogue_Menu_Query_Input();
		Dialogue_Menu_Disappear();
		if (answer == 1010) { // INSECT JEWELRY
			Dialogue_Menu_Remove_From_List(1010);
			if (_vm->_cutContent) { 
				Actor_Says(kActorMcCoy, 1105, 13); //00-1105.AUD	I'm looking for some jewelry in the shape of an insect.
				Delay(500);
				Actor_Says(kActorMcCoy, 1070, 23); //00-1070.AUD	Ever see this piece? Real elite stuff.
			} else {
				Actor_Says(kActorMcCoy, 1070, 13); //00-1070.AUD	Ever see this piece? Real elite stuff.
			}
			if (_vm->_cutContent) { 
				if (Actor_Query_Intelligence(kActorIzo) == 85) {
					Actor_Says(kActorIzo, 150, kAnimationModeTalk); //07-0150.AUD	Not for many years. You should try elsewhere.
				} else {
					if (Actor_Query_Friendliness_To_Other(kActorIzo, kActorMcCoy) > 49) {
						Actor_Says(kActorIzo, 200, 17);
						Actor_Says(kActorIzo, 210, 12);
						Actor_Says(kActorMcCoy, 1115, 12);
						Actor_Says(kActorIzo, 220, 16);
						Actor_Says(kActorIzo, 230, kAnimationModeTalk);
						Actor_Says(kActorIzo, 240, 15);
						Actor_Clue_Acquire(kActorMcCoy, kClueIzoInterview, false, kActorIzo);
					} else {
						Actor_Says(kActorIzo, 150, kAnimationModeTalk); //07-0150.AUD	Not for many years. You should try elsewhere.
					}
				}
			} else {
				Actor_Says(kActorIzo, 200, 17);
				Actor_Says(kActorIzo, 210, 12);
				Actor_Says(kActorMcCoy, 1115, 12);
				Actor_Says(kActorIzo, 220, 16);
				Actor_Says(kActorIzo, 230, kAnimationModeTalk);
				Actor_Says(kActorIzo, 240, 15);
				Actor_Clue_Acquire(kActorMcCoy, kClueIzoInterview, false, kActorIzo);
				if (Query_Difficulty_Level() < kGameDifficultyHard) {
					Actor_Modify_Friendliness_To_Other(kActorIzo, kActorMcCoy, -1);
				}
			}
		}
		if (answer == 1020) { // DRAGONFLY JEWERLY
			Dialogue_Menu_Remove_From_List(1020);
			Actor_Says(kActorMcCoy, 1065, 15); //00-1065.AUD	You move a lot of valuable goods through here? Valuable and exotic?
			Actor_Says(kActorIzo, 160, kAnimationModeTalk); //07-0160.AUD	How exotic?
			Actor_Says(kActorMcCoy, 1110, 16);
			if (_vm->_cutContent) { 	
				if (Actor_Query_Friendliness_To_Other(kActorIzo, kActorMcCoy) < 50
				|| Game_Flag_Query(kFlagIzoIsReplicant)) {
					Actor_Says(kActorIzo, 150, kAnimationModeTalk); //07-0150.AUD	Not for many years. You should try elsewhere.
				} else {
					Actor_Says(kActorIzo, 170, kAnimationModeTalk); //07-0170.AUD	Ah, they were so majestic.
					Actor_Says(kActorIzo, 180, kAnimationModeTalk); //07-0180.AUD	I remember them from my childhood.
					Actor_Says(kActorIzo, 190, 12); //07-0190.AUD	And that was the last time I've seen them.
				}
			} else {
				Actor_Says(kActorIzo, 160, kAnimationModeTalk);
				Actor_Says(kActorMcCoy, 1110, 16);
				Actor_Says(kActorIzo, 170, kAnimationModeTalk);
				Actor_Says(kActorIzo, 180, kAnimationModeTalk);
				Actor_Says(kActorIzo, 190, 12); //07-0190.AUD	And that was the last time I've seen them.
			}
			if (!_vm->_cutContent) { 
				if (Query_Difficulty_Level() < kGameDifficultyHard) {
					Actor_Modify_Friendliness_To_Other(kActorIzo, kActorMcCoy, -2);
				}
			}
		}
		if (answer == 1010 // INSECT JEWELRY
		 || answer == 1020 // DRAGONFLY JEWERLY
		) {
			Actor_Says_With_Pause(kActorMcCoy, 1120, 0.9f, 17);
			if (_vm->_cutContent) { 
				if (Actor_Query_Friendliness_To_Other(kActorIzo, kActorMcCoy) < 50
				|| Game_Flag_Query(kFlagIzoIsReplicant)) {
					Actor_Says(kActorIzo, 370, 13);	//07-0370.AUD	I don't have time for such pursuits.
					Actor_Says(kActorMcCoy, 1125, 14);
				} else {
					Actor_Says(kActorIzo, 250, 13); //07-0250.AUD	If I see something and you can match whatever my collectors will pay, it's all yours.
					if (Player_Query_Agenda() == kPlayerAgendaPolite) {
						Actor_Says(kActorMcCoy, 3140, 15); //00-3140.AUD	Thanks.
					} else {
						Actor_Says(kActorMcCoy, 1125, 14);
					}
				}
			} else {
				Actor_Says(kActorMcCoy, 1125, 14);
				if (Actor_Query_Friendliness_To_Other(kActorIzo, kActorMcCoy) < 47) {
					takePhotoAndRunAway();				
				}
			}
			end = true;
		}
		if (answer == 1030) { // WEAPONS
			Dialogue_Menu_Remove_From_List(1030);
			if (_vm->_cutContent) { 
				if (Player_Query_Agenda() == kPlayerAgendaSurly
				|| (Player_Query_Agenda() == kPlayerAgendaErratic)) {
					Actor_Modify_Friendliness_To_Other(kActorIzo, kActorMcCoy, -2);
					Actor_Says(kActorMcCoy, 1075, 14); //00-1075.AUD	How many illegal automatic weapons move through here?
					Actor_Says(kActorIzo, 260, 12); //07-0260.AUD	Automatic weapons hold little mystique for me.
					Actor_Says(kActorIzo, 270, 16); //07-0270.AUD	That's why I don't sell them.
					Actor_Says(kActorMcCoy, 1130, 14); //00-1130.AUD	Then what are those things in your back room there?
					Actor_Says(kActorIzo, 280, 17); //07-0280.AUD	Semi-automatic.
					Actor_Says(kActorMcCoy, 1135, 15); //00-1135.AUD	Big difference.
				} else {
					Actor_Says(kActorMcCoy, 4955, 18); //00-4955.AUD	You sell any Off-World stuff? Like Ender rifles?
					Actor_Says(kActorIzo, 320, 17); //07-0320.AUD	I don't deal in anything from the Off-World. Much too hard to authenticate.
					Actor_Says(kActorIzo, 270, 16); //07-0270.AUD	That's why I don't sell them.
				}
			} else {
				Actor_Says(kActorMcCoy, 1075, 18); //00-1075.AUD	How many illegal automatic weapons move through here?
				Actor_Says(kActorIzo, 260, 12); //07-0260.AUD	Automatic weapons hold little mystique for me.
				Actor_Says(kActorIzo, 270, 16); //07-0270.AUD	That's why I don't sell them.
				Actor_Says(kActorMcCoy, 1130, 14); //00-1130.AUD	Then what are those things in your back room there?
				Actor_Says(kActorIzo, 280, 17); //07-0280.AUD	Semi-automatic.
				Actor_Says(kActorMcCoy, 1135, 15); //00-1135.AUD	Big difference.
			}
			if (_vm->_cutContent) { 
				if (Actor_Query_Friendliness_To_Other(kActorIzo, kActorMcCoy) > 49) {
					Actor_Says(kActorIzo, 290, 15); //07-0290.AUD	There was a time when men operated with a code of honor
					Actor_Says(kActorIzo, 300, 12); //07-0300.AUD	Guns and rifles weren't necessary.
					Actor_Says(kActorIzo, 310, 17); //07-0310.AUD	The very presence of a sword was enough to ensure stability.
					Actor_Says(kActorMcCoy, 1140, kAnimationModeTalk); //00-1140.AUD	Well, times have changed.
				}
			} else {
				Actor_Says(kActorIzo, 290, 15); //07-0290.AUD	There was a time when men operated with a code of honor
				Actor_Says(kActorIzo, 300, 12); //07-0300.AUD	Guns and rifles weren't necessary.
				Actor_Says(kActorIzo, 310, 17); //07-0310.AUD	The very presence of a sword was enough to ensure stability.
				Actor_Says(kActorMcCoy, 1140, kAnimationModeTalk); //00-1140.AUD	Well, times have changed.
			}
			if (!_vm->_cutContent) {
				if (Query_Difficulty_Level() < kGameDifficultyHard) {
					Actor_Modify_Friendliness_To_Other(kActorIzo, kActorMcCoy, -2);
				}
			}
			if (!_vm->_cutContent) {
				if (Actor_Query_Friendliness_To_Other(kActorIzo, kActorMcCoy) < 47) {
					takePhotoAndRunAway();
				}
			}
			end = true;
		}
		if (answer == 1040) { // SHELL CASINGS
			Dialogue_Menu_Remove_From_List(1040);
			Actor_Says(kActorMcCoy, 1080, 15); //00-1080.AUD	How about Off-World assault weapons?
			Actor_Says(kActorMcCoy, 1085, 17); //00-1085.AUD	You got anything that's a match for these?
			Actor_Says(kActorIzo, 320, 17); //07-0320.AUD	I don't deal in anything from the Off-World. Much too hard to authenticate.
			if (_vm->_cutContent) { 
				if (Player_Query_Agenda() == kPlayerAgendaPolite) {
					Actor_Says(kActorMcCoy, 1145, 13); //00-1145.AUD	A man of your expertise could probably tell though.
				} else {
					Actor_Says(kActorMcCoy, 3910, 16); //00-3910.AUD	You’re lying.
				}
			} else {
				Actor_Says(kActorMcCoy, 1145, 13); //00-1145.AUD	A man of your expertise could probably tell though.
			}
			Actor_Says(kActorIzo, 330, 17); //07-0330.AUD	I don't even like to have them in here.
			//Considering that a main factor as to whether or not someone is a rep is whether or not they mention having any friends or family it feels appropriate for
			//Izo only to say these lines if he is human.
			if (_vm->_cutContent) {
				if (Actor_Query_Friendliness_To_Other(kActorIzo, kActorMcCoy) > 49
				&& !Game_Flag_Query(kFlagIzoIsReplicant)) {
					Actor_Says(kActorIzo, 340, 13); //07-0340.AUD	My friend Shoshane Yuri picked up the EOS plague from some gunner's space helmet.
					Actor_Says(kActorIzo, 350, 12); //07-0350.AUD	He was vomiting blood for days.
				}
			} else {
				Actor_Says(kActorIzo, 340, 13); //07-0340.AUD	My friend Shoshane Yuri picked up the EOS plague from some gunner's space helmet.
				Actor_Says(kActorIzo, 350, 12); //07-0350.AUD	He was vomiting blood for days.
			}
			end = true;
		}
		// When you choose to VK or warn Izo he immediately flashes you with his camera so since he knows that you are a blade runner.
		// If you try to VK him this will spook Izo and he will immediately escape into the sewers and the scene where Cystal asks you where Izo is will play.
		// If you warn him you can catch up to him in the sewers and talk to him and this will lead to the scenario where McCoy tries to convince Crystal that Izo is
		// innocent.
		if (answer == 1100) { // VK
			Actor_Says(kActorMcCoy, 5480, 15); //00-5480.AUD	Look, just come along with me. You’re gonna have to take a little personality test.
			Actor_Modify_Friendliness_To_Other(kActorIzo, kActorMcCoy, -2);	
			Game_Flag_Reset(kFlagMcCoyIsHelpingReplicants);
			Game_Flag_Set(kFlagIzoOnTheRun);
			takePhotoAndRunAway();
			end = true;
		}
		if (answer == 1110) { // CRYSTAL
			Actor_Says(kActorMcCoy, 3690, 14); //00-3690.AUD	Look. I wanna warn you. There’s a woman looking for you and your friends.
			// Added in two flags here, the first one is so the scene with Izo in the sewers will play and then will be reset so the scene doesn't repaet. The other will be used in the endgame to decide Steeles status towards McCoy.	
			Actor_Modify_Friendliness_To_Other(kActorIzo, kActorMcCoy, 2);
			Game_Flag_Set(kFlagMcCoyIsHelpingReplicants);
			Game_Flag_Set(kFlagIzoGotAway);
			Game_Flag_Set(kFlagIzoFled);
			Game_Flag_Set(kFlagIzoWarnedAboutCrystal);
			takePhotoAndRunAway();
			end = true;	
		}
		if (answer == 1050) { // GRIGORIAN 1 // Izo is Replicant
			Dialogue_Menu_Remove_From_List(1050);
			Actor_Says(kActorMcCoy, 1090, 18); // Ever consort with a group called CARS? C.A.R.S.?
			Actor_Says(kActorIzo, 360, 14); //07-0360.AUD	CARS. What is that?
			Actor_Says(kActorMcCoy, 1150, 17); //00-1150.AUD	Citizens Against Replicant Slavery.
			if (_vm->_cutContent) {
				if (Actor_Query_Friendliness_To_Other(kActorIzo, kActorMcCoy) < 50) {
					Actor_Says(kActorIzo, 370, 13); //07-0370.AUD	I don't have time for such pursuits.
					Actor_Says(kActorMcCoy, 1155, 15); //00-1155.AUD	How about Spencer Grigorian?
					Actor_Says(kActorIzo, 380, 12); //07-0380.AUD	The same goes for him whoever he is.
					Actor_Says(kActorMcCoy, 1160, 14); // He described you to a tee
					if (Player_Query_Agenda() == kPlayerAgendaSurly 
					|| Player_Query_Agenda() == kPlayerAgendaErratic) {	
						Actor_Says(kActorMcCoy, 1165, 18); // Even down to that stupid little ponytail you got.
						Actor_Says(kActorIzo, 390, 16);
						Actor_Modify_Friendliness_To_Other(kActorIzo, kActorMcCoy, -2);
					}
					Delay(1000);
					Actor_Says(kActorMcCoy, 1170, 12); //00-1170.AUD	What would you say if I told you Grigorian named you as one of the people who was there when the Tyrell Building blew up.
					Actor_Says(kActorIzo, 400, 13); //07-0400.AUD	There's a mistake somewhere along the chain of communication.
					Actor_Says(kActorMcCoy, 1180, 14); // So, you're denying all involvement?
					Actor_Says(kActorIzo, 440, 13); //07-0440.AUD	I am nothing but a humble salesman.
				} else {
					Actor_Says(kActorIzo, 410, 12); //07-0410.AUD	I won't lie to you detective.
					Actor_Says(kActorIzo, 420, 16); //07-0420.AUD	There was a time in my life when I might have been involved with such an organization.
					Actor_Says(kActorIzo, 430, 17); //07-0430.AUD	I actually cared. But now all I care about is my business.
					Actor_Says(kActorIzo, 440, 13); //07-0440.AUD	I am nothing but a humble salesman.
				}
			} else {
				Actor_Says(kActorIzo, 370, 13); //07-0370.AUD	I don't have time for such pursuits.
				Actor_Says(kActorMcCoy, 1155, 15); //00-1155.AUD	How about Spencer Grigorian?
				Actor_Says(kActorIzo, 380, 12); //07-0380.AUD	The same goes for him whoever he is.
				Actor_Says(kActorMcCoy, 1160, 14); // He described you to a tee
				Actor_Says(kActorMcCoy, 1165, 18); // Even down to that stupid little ponytail you got.
				Actor_Says(kActorIzo, 390, 16);
				Actor_Says(kActorMcCoy, 1170, 12); //00-1170.AUD	What would you say if I told you Grigorian named you as one of the people who was there when the Tyrell Building blew up.
				Actor_Says(kActorIzo, 400, 13); //07-0400.AUD	There's a mistake somewhere along the chain of communication.
				Actor_Says(kActorMcCoy, 1180, 14); // So, you're denying all involvement?
				Actor_Says(kActorIzo, 410, 12); //07-0410.AUD	I won't lie to you detective.
				Actor_Says(kActorIzo, 420, 16); //07-0420.AUD	There was a time in my life when I might have been involved with such an organization.
				Actor_Says(kActorIzo, 430, 17); //07-0430.AUD	I actually cared. But now all I care about is my business.
				Actor_Says(kActorIzo, 440, 13); //07-0440.AUD	I am nothing but a humble salesman.
			}
			if (!_vm->_cutContent) {
				Actor_Modify_Friendliness_To_Other(kActorIzo, kActorMcCoy, -2);
			}
			if (!_vm->_cutContent) {
				if (Actor_Query_Friendliness_To_Other(kActorIzo, kActorMcCoy) < 47) {
					takePhotoAndRunAway();
				}
			}
			end = true;
		}
		if (answer == 1060) { // GRIGORIAN 2 - Izo is a human, ex member of CARS
			Dialogue_Menu_Remove_From_List(1060);
			Actor_Says(kActorMcCoy, 1095, 15); //00-1095.AUD	You say everything's top-quality here.
			Actor_Says_With_Pause(kActorMcCoy, 1100, 1.2f, 18); // That go for your old buddy Spencer Grigorian, too?
			if (_vm->_cutContent) {
				if (Actor_Query_Intelligence(kActorIzo) == 65) {
					Actor_Says(kActorIzo, 450, 12); //07-0450.AUD	I met him a while back. He bought some calfskin gloves from me.
					Actor_Says(kActorIzo, 460, 13); //07-0460.AUD	Said he wanted to do some gardening.
					Actor_Says(kActorMcCoy, 1185, 18); // Calfskin?
					Actor_Says(kActorIzo, 470, 14); //
				} else if (Actor_Query_Intelligence(kActorIzo) == 85) {
					Delay(2000);
					Actor_Says(kActorMcCoy, 1170, 12); //00-1170.AUD	What would you say if I told you Grigorian named you as one of the people who was there when the Tyrell Building blew up.
					Actor_Says(kActorIzo, 400, 13); //07-0400.AUD	There's a mistake somewhere along the chain of communication.
					Actor_Says(kActorMcCoy, 1180, 14); // So, you're denying all involvement?
					Actor_Says(kActorIzo, 440, 13); //07-0440.AUD	I am nothing but a humble salesman.
				}
			} else {
				Actor_Says(kActorIzo, 450, 12); //07-0450.AUD	I met him a while back. He bought some calfskin gloves from me.
				Actor_Says(kActorIzo, 460, 13); //07-0460.AUD	Said he wanted to do some gardening.
				Actor_Says(kActorMcCoy, 1185, 18); // Calfskin?
				Actor_Says(kActorIzo, 470, 14); //
			}
			if (_vm->_cutContent) {
				if (!Game_Flag_Query(kFlagGrigorianIsReplicant)) {
					Actor_Says(kActorMcCoy, 1190, 14); //00-1190.AUD	Grigorian said you were thrown out of C.A.R.S. for having violent tendencies.
					Actor_Says(kActorIzo, 480, 13); //07-0480.AUD	Whoever Grigorian is, he's lying.
					if (Player_Query_Agenda() == kPlayerAgendaSurly 
					|| Player_Query_Agenda() == kPlayerAgendaErratic) {	
						Actor_Says(kActorMcCoy, 1195, 16); //00-1195.AUD	He also said you were a borderline sociopath who ought to be locked up.
						Actor_Says(kActorMcCoy, 1200, 18); //00-1200.AUD	But I'm inclined to agree.
						if (Actor_Query_Friendliness_To_Other(kActorIzo, kActorMcCoy) < 50) {
							Actor_Says(kActorIzo, 490, 12); //07-0490.AUD	Don't you wish I gave a damn about what you think?
							Actor_Modify_Friendliness_To_Other(kActorIzo, kActorMcCoy, -2);
							Actor_Says(kActorMcCoy, 1205, 14); //00-1205.AUD	I can make you give a damn.
							Actor_Says(kActorIzo, 500, 14); //07-0500.AUD	(snickers) Let me give you a little word of advice, detective.
							Actor_Says(kActorIzo, 510, 17); //07-0510.AUD	Stay out of my business.
							Actor_Says(kActorIzo, 520, 16); //07-0520.AUD	More importantly stay out of my face.
							Actor_Says(kActorIzo, 530, 15); //07-0530.AUD	All I'd have to do is make one vid-call and you would be shoveling shit Off-World for the rest of your career.
							Actor_Says(kActorMcCoy, 1210, 16); //00-1210.AUD	Talk to me like that some more and you'll be eating it.
							Actor_Change_Animation_Mode(kActorMcCoy, 23);
							Actor_Says(kActorIzo, 980, 15); //07-0980.AUD	(laughs) (grunts)
							Actor_Says(kActorMcCoy, 7275, 14); //  00-7275.AUD	Sometimes I just can't help myself.
							Actor_Clue_Acquire(kActorMcCoy, kClueMcCoyWarnedIzo, true, kActorIzo);
						} else {
							Delay(1000);	
							Actor_Says(kActorIzo, 440, 13); //07-0440.AUD	I am nothing but a humble salesman.
							Actor_Says(kActorMcCoy, 4880, 16); //00-4880.AUD	Is that right?
						}
					} else {
						Actor_Says(kActorMcCoy, 1180, 14); // So, you're denying all involvement?
						Actor_Says(kActorIzo, 440, 13); //07-0440.AUD	I am nothing but a humble salesman.
					}
				} else {
					Actor_Says(kActorMcCoy, 8320, 18); //00-8320.AUD	Really?
					Actor_Says(kActorIzo, 440, 13); //07-0440.AUD	I am nothing but a humble salesman.
					Actor_Says(kActorMcCoy, 4880, 16); //00-4880.AUD	Is that right?
				}
			} else {
				Actor_Says(kActorMcCoy, 1195, 16); //00-1195.AUD	He also said you were a borderline sociopath who ought to be locked up.
				Actor_Says(kActorMcCoy, 1200, 18); //00-1200.AUD	But I'm inclined to agree.
				Actor_Says(kActorIzo, 490, 12); //07-0490.AUD	Don't you wish I gave a damn about what you think?							
				Actor_Says(kActorMcCoy, 1205, 14); //00-1205.AUD	I can make you give a damn.
				Actor_Says(kActorIzo, 500, 14); //07-0500.AUD	(snickers) Let me give you a little word of advice, detective.
				Actor_Says(kActorIzo, 510, 17); //07-0510.AUD	Stay out of my business.
				Actor_Says(kActorIzo, 520, 16); //07-0520.AUD	More importantly stay out of my face.
				Actor_Says(kActorIzo, 530, 15); //07-0530.AUD	All I'd have to do is make one vid-call and you would be shoveling shit Off-World for the rest of your career.
				Actor_Says(kActorMcCoy, 1210, 16); //00-1210.AUD	Talk to me like that some more and you'll be eating it.
				Actor_Modify_Friendliness_To_Other(kActorIzo, kActorMcCoy, -4);
				if (Actor_Query_Friendliness_To_Other(kActorIzo, kActorMcCoy) < 47) {
					takePhotoAndRunAway();
				}
			}
			end = true;
		}
		if (answer == 100) { // DONE
			if (_vm->_cutContent) {
				Actor_Says(kActorMcCoy, 1215, 16); // All right
			}
			end = true;
		}
	} while (!end);
}

void SceneScriptHC01::takePhotoAndRunAway() {
	Actor_Set_Goal_Number(kActorIzo, kGoalIzoPrepareCamera);
	Player_Loses_Control();
	Actor_Says(kActorIzo, 90, kAnimationModeTalk);
	Actor_Face_Actor(kActorIzo, kActorMcCoy, true);
	Actor_Says(kActorIzo, 100, kAnimationModeTalk);
	Actor_Says(kActorIzo, 110, kAnimationModeTalk);
	if (_vm->_cutContent) {
		if (Game_Flag_Query(kFlagIzoWarnedAboutCrystal)) {
			Actor_Says(kActorMcCoy, 815, 14); //00-0815.AUD	Listen to me!
		} else if (Player_Query_Agenda() == kPlayerAgendaSurly 
		|| Player_Query_Agenda() == kPlayerAgendaErratic) {	
			Actor_Says(kActorMcCoy, 4320, 14); //00-4320.AUD	Save the pitch for someone who gives a shit.	
		} else {
			Actor_Says_With_Pause(kActorMcCoy, 1050, 0.2f, kAnimationModeTalk);
			Actor_Says(kActorIzo, 120, kAnimationModeTalk);
		}	
	} else {
		Actor_Says_With_Pause(kActorMcCoy, 1050, 0.2f, kAnimationModeTalk);
		Actor_Says(kActorIzo, 120, kAnimationModeTalk);
	}
	Actor_Set_Goal_Number(kActorIzo, kGoalIzoTakePhoto);
}

} // End of namespace BladeRunner
