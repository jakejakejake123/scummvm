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
#include "common/debug.h"

namespace BladeRunner {

void SceneScriptDR03::InitializeScene() {
	if (Game_Flag_Query(kFlagDR02toDR03)) {
		Game_Flag_Reset(kFlagDR02toDR03);
		Setup_Scene_Information(330.31f, 4.27f, -910.91f, 297);
	}

	Setup_Scene_Information(330.31f, 4.27f, -910.91f, 297);

	Scene_Exit_Add_2D_Exit(0, 377, 122, 445, 266, 0);

	if (Global_Variable_Query(kVariableChapter) == 3) {
		Actor_Put_In_Set(kActorChew, kSetDR03);
		// Made it so in act 3 Chew appears in the same place that he did in act 2. The original code for act 3 had him appearing offscreen for some reason.
		Actor_Set_At_XYZ(kActorChew, 360.77f, 4.4f, -806.67f, 126);
	} else {
		Actor_Put_In_Set(kActorChew, kSetDR03);
		Actor_Set_At_XYZ(kActorChew, 360.77f, 4.4f, -806.67f, 126);
	}

	Ambient_Sounds_Remove_All_Looping_Sounds(1u);
	Ambient_Sounds_Add_Looping_Sound(kSfxRESPRTR1,  7,  0, 1);
	Ambient_Sounds_Add_Looping_Sound(kSfxBRBED3,   50,  0, 1);
	// Added in some some effects for Chews lab.
	if (_vm->_cutContent) {
		Ambient_Sounds_Add_Looping_Sound(kSfxLABAMB1,  20, 70, 1);
		Ambient_Sounds_Add_Looping_Sound(kSfxLABAMB2,  20, 70, 1);
	}
	Ambient_Sounds_Add_Looping_Sound(kSfxBOILPOT2, 20, 70, 1);
}

void SceneScriptDR03::SceneLoaded() {
	Obstacle_Object("W2-CENTCASE02", true);
	Obstacle_Object("W2-CARTTOP", true);
	Obstacle_Object("W2-TANKAFLUID01", true);
}

bool SceneScriptDR03::MouseClick(int x, int y) {
	return false;
}

bool SceneScriptDR03::ClickedOn3DObject(const char *objectName, bool a2) {
	return false;
}

bool SceneScriptDR03::ClickedOnActor(int actorId) {
	if (actorId == kActorChew) {
		Actor_Face_Actor(kActorMcCoy, kActorChew, true);
		Actor_Face_Actor(kActorChew, kActorMcCoy, true);

		if (!Game_Flag_Query(kFlagDR03ChewTalk1)) {
			// Made it so McCoy only complains about the cold if he is surly or erratic. If he is neither surly or erratic he is nicer to Chew and simply ignores the cold.
			if (_vm->_cutContent) {
				if (Player_Query_Agenda() == kPlayerAgendaSurly 
				|| Player_Query_Agenda() == kPlayerAgendaErratic) {
					Actor_Says(kActorMcCoy, 750, 14);
					Actor_Says(kActorChew, 0, 14); //52-0000.AUD	Hmph, of course cold. What do you expect, heat? Eyes go bad at room temperature. You buy winter coat. Like this, see, like this. Very comfy.
					Actor_Says(kActorChew, 670, 14); //52-0670.AUD	Hmph.  [mumbles in Chinese]
					Actor_Modify_Friendliness_To_Other(kActorChew, kActorMcCoy, -2);
				} else {
					Actor_Says(kActorMcCoy, 755, 18);
					Actor_Says(kActorChew, 10, 14); //52-0010.AUD	Deliveries to rear!
				}
			} else {
				Actor_Says(kActorMcCoy, 755, 18);
				Actor_Says(kActorChew, 10, 14); //52-0010.AUD	Deliveries to rear!
			}
			if (_vm->_cutContent) {
				Actor_Says(kActorMcCoy, 760, 23); //00-0760.AUD	LPD. I got a couple of questions.
			} else {
				Actor_Says(kActorMcCoy, 760, 18);
			}
			if (_vm->_cutContent) {
				if (Actor_Query_Friendliness_To_Other(kActorChew, kActorMcCoy) < 50) {
					Actor_Says(kActorChew, 20, 14); //52-0020.AUD	Hmm. Talk, talk, talk, always talk. You wait. You no take up time. Busy, busy.
				} else {
					Actor_Says(kActorChew, 670, 14); //52-0670.AUD	Hmph.  [mumbles in Chinese]
				}
			} else {
				Actor_Says(kActorChew, 20, 14);
			}
			Actor_Says(kActorMcCoy, 765, 18);
			Actor_Says(kActorChew, 30, 14);
			Game_Flag_Set(kFlagDR03ChewTalk1);
			return true;
		}

		if (!Actor_Clue_Query(kActorMcCoy, kClueChewInterview)) {
			Actor_Says(kActorMcCoy, 770, 12);
			Actor_Says(kActorChew, 110, 12); //52-0110.AUD	Eisenduller? Ha, ha, no, no. No time for him. No go to lab.
			if (_vm->_cutContent) {
				if (Actor_Query_Friendliness_To_Other(kActorChew, kActorMcCoy) > 49) {
					Actor_Says(kActorChew, 120, 13); //52-0120.AUD	Eisenduller test Off-World gravity. Chew work important organs. Visual Center, you see?
				}
			} else {
				Actor_Says(kActorChew, 120, 13); //52-0120.AUD	Eisenduller test Off-World gravity. Chew work important organs. Visual Center, you see?
			}
			Actor_Says(kActorMcCoy, 835, 13); //00-0835.AUD	Marcus is dead.
			Actor_Says(kActorChew, 130, 14); //52-0130.AUD	Chew work hard all night, all day. No stop, no break. No OT (paid overtime).
			if (_vm->_cutContent) {
				if (Player_Query_Agenda() == kPlayerAgendaSurly 
				|| Player_Query_Agenda() == kPlayerAgendaErratic) {
					Actor_Says(kActorMcCoy, 840, 16); //00-0840.AUD	Did you hear me?
					Actor_Says(kActorChew, 140, 15); //52-0140.AUD	Of course I hear you! You-- you think I'm deaf? (mumbles) Hmph, your time more important, man?
					Actor_Modify_Friendliness_To_Other(kActorChew, kActorMcCoy, -2);
				} else if (Player_Query_Agenda() == kPlayerAgendaPolite) {
					Actor_Says(kActorMcCoy, 2305, 13); //00-2305.AUD	I’m sorry.
					Actor_Modify_Friendliness_To_Other(kActorChew, kActorMcCoy, 2);
					Delay(1000);
				} else {
					Actor_Says(kActorMcCoy, 4880, 13); //00-4880.AUD	Is that right?
					Delay(1000);
				}
			} else {
				Actor_Says(kActorMcCoy, 840, 16); //00-0840.AUD	Did you hear me?
				Actor_Says(kActorChew, 140, 15); //52-0140.AUD	Of course I hear you! You-- you think I'm deaf? (mumbles) Hmph, your time more important, man?
			}
			if (_vm->_cutContent) {
				Actor_Says(kActorChew, 150, 13); //52-0150.AUD	Eisenduller dead. Moraji maybe dead. You out chasing skirts?
				Actor_Says(kActorMcCoy, 845, 17); //00-0845.AUD	Moraji?
				Actor_Says(kActorChew, 170, 18);
				Actor_Says(kActorChew, 180, 16); //52-0180.AUD	Sometimes we go up and eat with twins.
				// Added in some more dialogue. Also made it so the dialogue of McCoy asking Chew where to find Moraji and Chew directing McCoy to dermo design
				// and explaining Moraji didn't show up only plays if McCoy did not have his encounter with Moraji.
				Actor_Says(kActorMcCoy, 870, 13); //00-0870.AUD	What does he work on?
				Actor_Says(kActorChew, 290, 12); //52-0290.AUD	Skin. Did skin for Nexus-6. Beautiful work. You go see.
				Actor_Says(kActorMcCoy, 875, 15); //00-0875.AUD	Where do I find him?
				Actor_Says(kActorChew, 300, 18); //52-0300.AUD	He at “Dermo Design” across street. You find him, you tell him I wait.
				Actor_Clue_Acquire(kActorMcCoy, kClueChewInterview, true, kActorChew);
				if (!Game_Flag_Query(kFlagDR05BombExploded)) {				
					if (Player_Query_Agenda() != kPlayerAgendaSurly 
					&& Player_Query_Agenda() != kPlayerAgendaErratic) {
						Actor_Says(kActorMcCoy, 850, 15); //00-0850.AUD	Moraji didn't show? Did you call him?
						Actor_Says(kActorChew, 190, 14);//52-0190.AUD	I call. I knock. Ten minutes ago. Door locked, no answer.
						Actor_Says(kActorChew, 200, 13);
						Actor_Says(kActorMcCoy, 855, 18);
						Actor_Says(kActorChew, 210, 12);
					}
				}
			} else if (!Game_Flag_Query(kFlagDR03ChewTalkExplosion)) {
				Actor_Says(kActorChew, 150, 13);
				Actor_Says(kActorMcCoy, 845, 17);
				Actor_Says(kActorChew, 170, 18);
				Actor_Says(kActorChew, 180, 16); //52-0180.AUD	Sometimes we go up and eat with twins.
				if (!Game_Flag_Query(kFlagDR05BombExploded)) {
					Actor_Says(kActorMcCoy, 850, 15);
					Actor_Says(kActorChew, 190, 14);
					Actor_Says(kActorChew, 200, 13);
					Actor_Says(kActorMcCoy, 855, 18);
					Actor_Says(kActorChew, 210, 12);
				}
				Actor_Clue_Acquire(kActorMcCoy, kClueChewInterview, true, kActorChew);
			}
		return true;
		}

		if (Game_Flag_Query(kFlagDR05JustExploded)
		&& Game_Flag_Query(kFlagDR03ChewTalk1)) {
			if (_vm->_cutContent) {
				if (Player_Query_Agenda() == kPlayerAgendaSurly 
				|| Player_Query_Agenda() == kPlayerAgendaErratic) {
					Actor_Says(kActorMcCoy, 815, 14); //00-0815.AUD	Listen to me!
					Actor_Modify_Friendliness_To_Other(kActorChew, kActorMcCoy, -2);
				} else {
					Actor_Says(kActorMcCoy, 3970, 18); //00-3970.AUD	Hey.
				}
			} else {
				Actor_Says(kActorMcCoy, 815, 18);
			}
			if (_vm->_cutContent) {
				if (Actor_Query_Friendliness_To_Other(kActorChew, kActorMcCoy) < 50) {
					Actor_Says(kActorChew, 60, 14); //52-0060.AUD	Busy, busy. You not delivery man. You go away!
				}
				Actor_Says(kActorChew, 70, 16); //52-0070.AUD	(mumbles) Distraction all day long. Never stop.
				Actor_Says(kActorChew, 80, 13); //52-0080.AUD	Loud noises on the street. Beep, beep, bonk, gonk, gonk. (sigh) Always make me drop eyes.
			} else {
				Actor_Says(kActorChew, 60, 14); //52-0060.AUD	Busy, busy. You not delivery man. You go away!
				Actor_Says(kActorChew, 70, 14); //52-0070.AUD	(mumbles) Distraction all day long. Never stop.
				Actor_Says(kActorChew, 80, 14); //52-0080.AUD	Loud noises on the street. Beep, beep, bonk, gonk, gonk. (sigh) Always make me drop eyes.
			}
			Actor_Says(kActorMcCoy, 820, 18);
			Actor_Says(kActorChew, 90, 14); //52-0090.AUD	Oh, what-- what of Moraji?
			// Made it so if McCoy saves Moraji it is acknowledged in this dialogue.
			if (_vm->_cutContent) {
				if (Game_Flag_Query(kFlagMorajiAlive)) { 
					Actor_Says(kActorMcCoy, 4900, 13); //00-4900.AUD	Word is he's gonna be okay.
					if (Game_Flag_Query(kFlagMorajiTalkSuspects)) { 
						Actor_Clue_Acquire(kActorMcCoy, kClueMorajiInterview, true, kActorMoraji);
					}
				} else {
					Actor_Says(kActorMcCoy, 825, 13); //00-0825.AUD	He didn't make it.
					CDB_Set_Crime(kClueDoorForced1, kCrimeMorajiMurder);
				}
			} else {
				Actor_Says(kActorMcCoy, 825, 13); //00-0825.AUD	He didn't make it.
			}
			if (_vm->_cutContent) {
				Delay(2000);
				Actor_Says(kActorMcCoy, 4270, 18); //00-4270.AUD	I got some more questions for you.
				if (Actor_Query_Friendliness_To_Other(kActorChew, kActorMcCoy) < 50) {
					Actor_Says(kActorChew, 100, 13); //52-0100.AUD	You leave now, okay? Very busy. Must work. Must work, ah.
					Actor_Says(kActorMcCoy, 5600, 14);               // Let me ask you
					Actor_Says(kActorChew, 730, 15); //52-0730.AUD	Oy, I tell you something then you go, okay?
				}
			} else {
				Actor_Says(kActorChew, 100, 14); //52-0100.AUD	You leave now, okay? Very busy. Must work. Must work, ah.
			}		
			Game_Flag_Reset(kFlagDR05JustExploded);
			Game_Flag_Set(kFlagDR03ChewTalkExplosion);
			return true;
		}

		if ((Actor_Clue_Query(kActorMcCoy, kClueDNATyrell)
		  || Actor_Clue_Query(kActorMcCoy, kClueAnsweringMachineMessage)
		  || Actor_Clue_Query(kActorMcCoy, kClueEnvelope)
		  || Actor_Clue_Query(kActorMcCoy, kClueChewInterview)
		 )
		 && Game_Flag_Query(kFlagDR03ChewTalkExplosion)
		) {
			dialogueWithChew();
		} else {
			if (_vm->_cutContent) {
				if (Actor_Query_Friendliness_To_Other(kActorChew, kActorMcCoy) > 49) {
					if (Player_Query_Agenda() == kPlayerAgendaPolite) {
						Actor_Says(kActorMcCoy, 805, 3); //00-0805.AUD	Sorry to bother you.
					} else {
						Actor_Says(kActorMcCoy, 4595, 3); //00-4595.AUD	Stick around. I may not be finished with you.
					}
				} else {
					Actor_Says(kActorMcCoy, 810, 18);
					Actor_Says(kActorChew, 40, 14);
					Actor_Says(kActorChew, 50, 14); //52-0050.AUD	I very busy. Eyes will wait for nothing.
					Actor_Says(kActorChew, 740, 14); //52-0740.AUD	[speaks Chinese] Do eyes, do eyes! No time for yip yap yap yap yap yap gossip.
					if (Player_Query_Agenda() == kPlayerAgendaSurly 
					|| Player_Query_Agenda() == kPlayerAgendaErratic) {
						Actor_Says(kActorMcCoy, 8715, 14); //00-8715.AUD	Weirdo.
					}
				}
			} else {
				Actor_Says(kActorMcCoy, 810, 18);
				Actor_Says(kActorChew, 40, 14);
				Actor_Says(kActorChew, 50, 14); //52-0050.AUD	I very busy. Eyes will wait for nothing.
			}
		}
		return true;
	}

	return false;
}

bool SceneScriptDR03::ClickedOnItem(int itemId, bool a2) {
	return false;
}

bool SceneScriptDR03::ClickedOnExit(int exitId) {
	if (exitId == 0) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, 330.31f, 4.27f, -910.91f, 24, true, false, false)) {
			Game_Flag_Set(kFlagDR03toDR02);
			Set_Enter(kSetDR01_DR02_DR04, kSceneDR02);
		}
		return true;
	}
	return false;
}

bool SceneScriptDR03::ClickedOn2DRegion(int region) {
	return false;
}

void SceneScriptDR03::SceneFrameAdvanced(int frame) {
	if (frame == 1
	 || frame == 4
	 || frame == 8
	 || frame == 10
	 || frame == 19
	 || frame == 21
	 || frame == 22
	 || frame == 23
	 || frame == 30
	 || frame == 31
	 || frame == 32
	 || frame == 33
	 || frame == 46
	 || frame == 49
	) {
		if (Random_Query(0, 1)) {
			Sound_Play(kSfxNEON7, Random_Query(20, 33), 80, 80, 50);
		} else {
			Sound_Play(kSfxNEON5, Random_Query(5, 6), 80, 80, 50);
		}
	}
}

void SceneScriptDR03::ActorChangedGoal(int actorId, int newGoal, int oldGoal, bool currentSet) {
}

void SceneScriptDR03::PlayerWalkedIn() {
	// Restored the scene of McCoy encountering Chew in act 3 after he was attacked by Roy and Leon. McCoy will treat Chew differently based on his agenda and Chew
	// will hand over his DNA information to McCoy.
		if (_vm->_cutContent) {
			if (!Game_Flag_Query(kFlagChewTalkGiveData)
			&& (Global_Variable_Query(kVariableChapter) == 3))	{	
				Actor_Face_Actor(kActorMcCoy, kActorChew, true);
				Actor_Face_Actor(kActorChew, kActorMcCoy, true);
				Actor_Says(kActorChew, 510, 15); //52-0510.AUD	Oh, what, what, what? Oh, LPD. You late. Too late.
				Actor_Says(kActorMcCoy, 910, 15); //00-0910.AUD	Okay, Chew.
				Actor_Says(kActorMcCoy, 915, 13); //00-0915.AUD	What happened?
				Actor_Says(kActorChew, 520, 13); //52-0520.AUD	Two Nexus-6 break in here. They harass me.
				// Made it McCoy only mentions Clovis' description if he has a clue which gave him information on what Clovis looked like. McCoy never actually sees Clovis on the Bradbury roof since he was knocked out
				// by Sadik so he should only mention Clovis' description if he has clue that gave him said information.
				if (Actor_Clue_Query(kActorMcCoy, kClueAnimalMurderSuspect)
				|| Actor_Clue_Query(kActorMcCoy, kClueMorajiInterview)
				|| Actor_Clue_Query(kActorMcCoy, kClueIzosFriend)
				|| Actor_Clue_Query(kActorMcCoy, kClueMoonbus1)
				|| Actor_Clue_Query(kActorMcCoy, kClueDektorasDressingRoom)) {
					Actor_Says(kActorMcCoy, 920, 13); //00-0920.AUD	A tall Rastafarian and a guy with a beard?
					Actor_Says(kActorChew, 530, 18); //52-0530.AUD	No, no! One with white hair, cruel face.
					Actor_Says(kActorChew, 540, 13); //52-0540.AUD	Other stupid looking. Mustache.
				}
				Actor_Says(kActorChew, 550, 12); //52-0550.AUD	They touch eyes, destroy coat. Have to start all over.
				if (Actor_Clue_Query(kActorMcCoy, kClueAnimalMurderSuspect)
				|| Actor_Clue_Query(kActorMcCoy, kClueMorajiInterview)
				|| Actor_Clue_Query(kActorMcCoy, kClueIzosFriend)
				|| Actor_Clue_Query(kActorMcCoy, kClueMoonbus1)
				|| Actor_Clue_Query(kActorMcCoy, kClueDektorasDressingRoom)) {
					Actor_Says(kActorMcCoy, 925, 18); //00-0925.AUD	You sure about the descriptions?
					Actor_Says(kActorChew, 560, 13); //52-0560.AUD	Hey! I got eyes.
				}
				Actor_Says(kActorMcCoy, 930, 13); //00-0930.AUD	What did they want?
				if (Actor_Query_Friendliness_To_Other(kActorChew, kActorMcCoy) < 50) {
					Actor_Says(kActorChew, 700, 14); //52-0700.AUD	I not know. Feet hurt.
					Actor_Says(kActorMcCoy, 3910, 14); // 00-3910.AUD	You’re lying.
					Actor_Says(kActorChew, 760, 15); //52-0760.AUD	Ha. Been called worse than liar before. You go now.
					Actor_Says(kActorMcCoy, 8190, 14); //00-8190.AUD	Why?
					Actor_Says(kActorChew, 770, 14); //52-0770.AUD	Truth bad! You no like, that's why. I tell you anyway, then you go.
					Actor_Says(kActorMcCoy, 1825, 15); //00-1825.AUD	Okay.
					Actor_Says(kActorMcCoy, 955, 13); //00-0955.AUD	What did they want?
				}
				Actor_Says(kActorChew, 570, 12); //52-0570.AUD	DNA information. Incept dates. Stuff like that.
				Actor_Says(kActorChew, 580, 13); // 52-0580.AUD	I give copies. Heh, heh. Still pressure me. Thought they kill me.
				Actor_Says(kActorMcCoy, 935, 15); //00-0935.AUD	I need a copy too.
				if (Actor_Query_Friendliness_To_Other(kActorChew, kActorMcCoy) > 49) {
					Actor_Face_Heading(kActorChew, 310, true);
					Delay (2000);
					Loop_Actor_Walk_To_Actor(kActorChew, kActorMcCoy, 24, true, false);
					Actor_Face_Actor(kActorMcCoy, kActorChew, true);
					Actor_Face_Actor(kActorChew, kActorMcCoy, true);
					Actor_Change_Animation_Mode(kActorMcCoy, 23);
					Actor_Change_Animation_Mode(kActorChew, 23);
					Delay(800);
					Item_Pickup_Spin_Effect_From_Actor(kModelAnimationDNADataDisc, kActorMcCoy, 0, 0);
					Delay(800);
					Actor_Clue_Acquire(kActorMcCoy, kClueDNAChew, true, kActorChew);
					if (Player_Query_Agenda() == kPlayerAgendaPolite) {
						Actor_Says(kActorMcCoy, 3935, 13);	// Thanks.
						Delay(500);	
					}
					Actor_Says(kActorMcCoy, 5150, 18); //00-5150.AUD	One more thing.
					Actor_Says(kActorChew, 440, 18); //52-0440.AUD	You! But how in the world?
					Actor_Says(kActorMcCoy, 2755, 18);                  // AreYouAlrightALittlePale
					Actor_Says(kActorChew, 470, 13); //52-0470.AUD	I do. I see you before.
					Actor_Says(kActorMcCoy, 900, 18); //00-0900.AUD	Yeah, I've been around.
					Actor_Says(kActorChew, 480, 12); //52-0480.AUD	No. Your eyes. Seen eyes.
					Actor_Says(kActorMcCoy, 880, 13); //00-0880.AUD	That so?	
					Delay(2000);
					Actor_Says(kActorMcCoy, 2860, 14);                    // YouTakeCareOfYourself
					Delay(2000);
					Game_Flag_Set(kFlagChewTalkGiveData);	
					Game_Flag_Set(kFlagDR03toDR02);
					Set_Enter(kSetDR01_DR02_DR04, kSceneDR02);
					Player_Gains_Control();
					Scene_Exits_Enable();
				} else {
					Actor_Says(kActorChew, 450, 15); //52-0450.AUD	I told you, told others. I just do eyes. Er...Sebastian! Maybe he know.
					// Made it so if McCoy threatens Chew he walks up to him and gives him the data. This leads to Chew getting a close look at McCoys eyes and commenting on them.
					// If McCoy doesn't threaten Chew he tells McCoy that he is busy and he should leave and the scene with McCoys eyes doesn't happen. 
					if (Player_Query_Agenda() == kPlayerAgendaSurly 
					|| Player_Query_Agenda() == kPlayerAgendaErratic) {
						Actor_Says(kActorMcCoy, 895, 14); //00-0895.AUD	I need whatever Replicant DNA information you have. Now!
						Actor_Says(kActorChew, 630, 15); //52-0630.AUD	No, no, no, no, no, no, no.
						Actor_Says(kActorMcCoy, 8445, 14); //00-8445.AUD	Cough it up!
						Delay(1000);
						Actor_Says(kActorMcCoy, 1805, 14); //00-1805.AUD	Now!
						Actor_Says(kActorChew, 460, 18); //52-0460.AUD	(whimpers) Okay, sure. I find something.
						Actor_Modify_Friendliness_To_Other(kActorChew, kActorMcCoy, -2);
						Actor_Face_Heading(kActorChew, 310, true);
						Delay (2000);
						Loop_Actor_Walk_To_Actor(kActorChew, kActorMcCoy, 24, true, false);
						Actor_Face_Actor(kActorMcCoy, kActorChew, true);
						Actor_Face_Actor(kActorChew, kActorMcCoy, true);
						Actor_Change_Animation_Mode(kActorMcCoy, 23);
						Actor_Change_Animation_Mode(kActorChew, 23);
						Delay(800);
						Item_Pickup_Spin_Effect_From_Actor(kModelAnimationDNADataDisc, kActorMcCoy, 0, 0);
						Delay(800);
						Actor_Clue_Acquire(kActorMcCoy, kClueDNAChew, true, kActorChew);
						Actor_Says(kActorChew, 670, 14); // 52-0670.AUD	Hmph.  [mumbles in Chinese]
						Actor_Says(kActorMcCoy, 905, 18); //00-0905.AUD	You light up my life too, pal. That's all you have?
						Actor_Says(kActorChew, 590, 14); // 52-0590.AUD	Hah. LPD, you go arrest criminals. You no bother me anymore, huh? Gotta get back to work.
						Actor_Says(kActorMcCoy, 5150, 14); //00-5150.AUD	One more thing.
						Actor_Says(kActorChew, 600, 14); // 52-0600.AUD	No, no time! You go. Find Nexus-6. That's your job. Ah.	
						Delay(1000);
						Actor_Says(kActorChew, 440, 18); //52-0440.AUD	You! But how in the world?
						Actor_Says(kActorMcCoy, 8940, 14); //00-8940.AUD	What are you staring at?
						Actor_Says(kActorChew, 470, 13); //52-0470.AUD	I do. I see you before.
						Actor_Says(kActorMcCoy, 900, 18); //00-0900.AUD	Yeah, I've been around.
						Actor_Says(kActorChew, 480, 12); //52-0480.AUD	No. Your eyes. Seen eyes.
						Actor_Says(kActorMcCoy, 880, 13); //00-0880.AUD	That so?	
						Actor_Says(kActorChew, 490, 18); //52-0490.AUD	All I know. About eyes. Please go! (whimpers) That's all I know. I promise.
						Actor_Says(kActorMcCoy, 940, 15); //00-0940.AUD	I need to ask you--
						Actor_Says(kActorChew, 500, 18); //52-0500.AUD	No, no no. No, no, you please go. I give you all I have. Ah, no more. See, see? No more.
						Actor_Says(kActorMcCoy, 815, 14); //00-0815.AUD	Listen to me!
						Actor_Says(kActorChew, 640, 14); //52-0640.AUD	[speaks in Chinese] You! You bad.
						Actor_Says(kActorChew, 650, 15); //	52-0650.AUD	You go away! Never come back.
						Delay(1000);
						Actor_Face_Heading(kActorChew, 310, true);
						Actor_Says(kActorChew, 610, 14); //52-0610.AUD	(whimpers) My eyes! They fog. Eyes melting, getting slimy. Oh, please eye! Oh, you so mushy!
						Actor_Says(kActorChew, 660, 15); //52-0660.AUD	(yells) Ah!
						Actor_Change_Animation_Mode(kActorChew, 48);
						Delay(2000);
						Actor_Says(kActorMcCoy, 3970, 14); //00-3970.AUD	Hey.
						Delay (1000);
						Actor_Says(kActorTransient, 400, -1); //12-0400.AUD	Zzz…
						Actor_Says(kActorTransient, 410, -1); //12-0410.AUD	Zzz…
						Actor_Says(kActorMcCoy, 8527, 13); //00-8527.AUD	Strange.
						Actor_Says(kActorTransient, 40, -1); //12-0040.AUD	Zzz…
						Delay (1000);
						Game_Flag_Set(kFlagChewTalkGiveData);	
						Game_Flag_Set(kFlagDR03toDR02);
						Set_Enter(kSetDR01_DR02_DR04, kSceneDR02);
						Player_Gains_Control();
						Scene_Exits_Enable();
					} else {
						Actor_Says(kActorMcCoy, 4880, 13); //00-4880.AUD	Is that right?
						Delay(2000);
						Actor_Says(kActorMcCoy, 5150, 14); //00-5150.AUD	One more thing.
						Actor_Says(kActorChew, 600, 14); // 52-0600.AUD	No, no time! You go. Find Nexus-6. That's your job. Ah.			
						Actor_Says(kActorMcCoy, 940, 15); //00-0940.AUD	I need to ask you--
						Actor_Says(kActorChew, 630, 15); //52-0630.AUD	No, no, no, no, no, no, no.
						Delay(2000);
						Game_Flag_Set(kFlagChewTalkGiveData);	
						Game_Flag_Set(kFlagDR03toDR02);
						Set_Enter(kSetDR01_DR02_DR04, kSceneDR02);
						Player_Gains_Control();
						Scene_Exits_Enable();
					}					
				}
			} else if (Global_Variable_Query(kVariableChapter) == 2
			&& Actor_Clue_Query(kActorMcCoy, kClueAnsweringMachineMessage)
			&& Actor_Query_Intelligence(kActorClovis) == 100) {
				Actor_Face_Actor(kActorMcCoy, kActorChew, true);
				Actor_Face_Actor(kActorChew, kActorMcCoy, true);
				Actor_Says(kActorChew, 510, 15); //52-0510.AUD	Oh, what, what, what? Oh, LPD. You late. Too late.
				Actor_Says(kActorMcCoy, 910, 15); //00-0910.AUD	Okay, Chew.
				Actor_Says(kActorMcCoy, 915, 13); //00-0915.AUD	What happened?
				Actor_Says(kActorChew, 520, 13); //52-0520.AUD	Two Nexus-6 break in here. They harass me.
				// Made it McCoy only mentions Clovis' description if he has a clue which gave him information on what Clovis looked like. McCoy never actually sees Clovis on the Bradbury roof since he was knocked out
				// by Sadik so he should only mention Clovis' description if he has clue that gave him said information.
				if (Actor_Clue_Query(kActorMcCoy, kClueAnimalMurderSuspect)
				|| Actor_Clue_Query(kActorMcCoy, kClueMorajiInterview)
				|| Actor_Clue_Query(kActorMcCoy, kClueIzosFriend)) {
					Actor_Says(kActorMcCoy, 920, 13); //00-0920.AUD	A tall Rastafarian and a guy with a beard?
				}
				Actor_Says(kActorChew, 550, 12); //52-0550.AUD	They touch eyes, destroy coat. Have to start all over.
				Actor_Says(kActorMcCoy, 930, 13); //00-0930.AUD	What did they want?
				if (Actor_Query_Friendliness_To_Other(kActorChew, kActorMcCoy) < 50) {
					Actor_Says(kActorChew, 700, 14); //52-0700.AUD	I not know. Feet hurt.
					Actor_Says(kActorMcCoy, 3910, 14); // 00-3910.AUD	You’re lying.
					Actor_Says(kActorChew, 760, 15); //52-0760.AUD	Ha. Been called worse than liar before. You go now.
					Actor_Says(kActorMcCoy, 8190, 14); //00-8190.AUD	Why?
					Actor_Says(kActorChew, 770, 14); //52-0770.AUD	Truth bad! You no like, that's why. I tell you anyway, then you go.
					Actor_Says(kActorMcCoy, 1825, 15); //00-1825.AUD	Okay.
					Actor_Says(kActorMcCoy, 955, 13); //00-0955.AUD	What did they want?
				}
				Actor_Says(kActorChew, 570, 12); //52-0570.AUD	DNA information. Incept dates. Stuff like that.
				Actor_Says(kActorChew, 580, 13); // 52-0580.AUD	I give copies. Heh, heh. Still pressure me. Thought they kill me.
				Actor_Says(kActorMcCoy, 935, 15); //00-0935.AUD	I need a copy too.
				if (Actor_Query_Friendliness_To_Other(kActorChew, kActorMcCoy) > 49) {
					Actor_Face_Heading(kActorChew, 310, true);
					Delay (2000);
					Loop_Actor_Walk_To_Actor(kActorChew, kActorMcCoy, 24, true, false);
					Actor_Face_Actor(kActorMcCoy, kActorChew, true);
					Actor_Face_Actor(kActorChew, kActorMcCoy, true);
					Actor_Change_Animation_Mode(kActorMcCoy, 23);
					Actor_Change_Animation_Mode(kActorChew, 23);
					Delay(800);
					Item_Pickup_Spin_Effect_From_Actor(kModelAnimationDNADataDisc, kActorMcCoy, 0, 0);
					Delay(800);
					Actor_Clue_Acquire(kActorMcCoy, kClueDNAChew, true, kActorChew);
					if (Player_Query_Agenda() == kPlayerAgendaPolite) {
						Actor_Says(kActorMcCoy, 3935, 13);	// Thanks.	
					}
					Delay(1000);
					Actor_Says(kActorMcCoy, 5600, 14);               // Let me ask you.
					Actor_Says(kActorMcCoy, 795, 3);
					Actor_Says(kActorChew, 330, 12);
					Actor_Says(kActorChew, 340, 15);
					Actor_Says(kActorMcCoy, 875, 16);
					Actor_Says(kActorChew, 350, 12);
					Actor_Says(kActorChew, 360, 15);
					Game_Flag_Set(kFlagBB01Available);
					Actor_Says(kActorMcCoy, 5150, 18); //00-5150.AUD	One more thing.
					Actor_Says(kActorChew, 440, 18); //52-0440.AUD	You! But how in the world?
					Actor_Says(kActorMcCoy, 2755, 18);                  // AreYouAlrightALittlePale
					Actor_Says(kActorChew, 470, 13); //52-0470.AUD	I do. I see you before.
					Actor_Says(kActorMcCoy, 900, 18); //00-0900.AUD	Yeah, I've been around.
					Actor_Says(kActorChew, 480, 12); //52-0480.AUD	No. Your eyes. Seen eyes.
					Actor_Says(kActorMcCoy, 880, 13); //00-0880.AUD	That so?	
					Delay(2000);
					Actor_Says(kActorMcCoy, 2860, 14);                    // YouTakeCareOfYourself
					Delay(2000);
					Game_Flag_Set(kFlagChewTalkGiveData);	
					Game_Flag_Set(kFlagDR03toDR02);
					Set_Enter(kSetDR01_DR02_DR04, kSceneDR02);
					Player_Gains_Control();
					Scene_Exits_Enable();
				} else {
					Actor_Says(kActorChew, 450, 15); //52-0450.AUD	I told you, told others. I just do eyes. Er...Sebastian! Maybe he know.
					// Made it so if McCoy threatens Chew he walks up to him and gives him the data. This leads to Chew getting a close look at McCoys eyes and commenting on them.
					// If McCoy doesn't threaten Chew he tells McCoy that he is busy and he should leave and the scene with McCoys eyes doesn't happen. 
					if (Player_Query_Agenda() == kPlayerAgendaSurly 
					|| Player_Query_Agenda() == kPlayerAgendaErratic) {
						Actor_Says(kActorMcCoy, 895, 14); //00-0895.AUD	I need whatever Replicant DNA information you have. Now!
						Actor_Says(kActorChew, 630, 15); //52-0630.AUD	No, no, no, no, no, no, no.
						Actor_Says(kActorMcCoy, 8445, 14); //00-8445.AUD	Cough it up!
						Delay(1000);
						Actor_Says(kActorMcCoy, 1805, 14); //00-1805.AUD	Now!
						Actor_Says(kActorChew, 460, 18); //52-0460.AUD	(whimpers) Okay, sure. I find something.
						Actor_Modify_Friendliness_To_Other(kActorChew, kActorMcCoy, -2);
						Actor_Face_Heading(kActorChew, 310, true);
						Delay (2000);
						Loop_Actor_Walk_To_Actor(kActorChew, kActorMcCoy, 24, true, false);
						Actor_Face_Actor(kActorMcCoy, kActorChew, true);
						Actor_Face_Actor(kActorChew, kActorMcCoy, true);
						Actor_Change_Animation_Mode(kActorMcCoy, 23);
						Actor_Change_Animation_Mode(kActorChew, 23);
						Delay(800);
						Item_Pickup_Spin_Effect_From_Actor(kModelAnimationDNADataDisc, kActorMcCoy, 0, 0);
						Delay(800);
						Actor_Clue_Acquire(kActorMcCoy, kClueDNAChew, true, kActorChew);
						Actor_Says(kActorChew, 670, 14); // 52-0670.AUD	Hmph.  [mumbles in Chinese]
						Actor_Says(kActorMcCoy, 905, 18); //00-0905.AUD	You light up my life too, pal. That's all you have?
						Actor_Says(kActorChew, 590, 14); // 52-0590.AUD	Hah. LPD, you go arrest criminals. You no bother me anymore, huh? Gotta get back to work.
						Delay(1000);
						Actor_Says(kActorMcCoy, 5600, 14);               // Let me ask you.
						Actor_Says(kActorMcCoy, 795, 3);
						Actor_Says(kActorChew, 330, 12);
						Actor_Says(kActorChew, 340, 15);
						Actor_Says(kActorMcCoy, 875, 16);
						Actor_Says(kActorChew, 350, 12);
						Actor_Says(kActorChew, 360, 15);
						Game_Flag_Set(kFlagBB01Available);
						Actor_Says(kActorMcCoy, 5150, 14); //00-5150.AUD	One more thing.
						Actor_Says(kActorChew, 600, 14); // 52-0600.AUD	No, no time! You go. Find Nexus-6. That's your job. Ah.	
						Delay(1000);
						Actor_Says(kActorChew, 440, 18); //52-0440.AUD	You! But how in the world?
						Actor_Says(kActorMcCoy, 8940, 14); //00-8940.AUD	What are you staring at?
						Actor_Says(kActorChew, 470, 13); //52-0470.AUD	I do. I see you before.
						Actor_Says(kActorMcCoy, 900, 18); //00-0900.AUD	Yeah, I've been around.
						Actor_Says(kActorChew, 480, 12); //52-0480.AUD	No. Your eyes. Seen eyes.
						Actor_Says(kActorMcCoy, 880, 13); //00-0880.AUD	That so?	
						Actor_Says(kActorChew, 490, 18); //52-0490.AUD	All I know. About eyes. Please go! (whimpers) That's all I know. I promise.
						Actor_Says(kActorMcCoy, 940, 15); //00-0940.AUD	I need to ask you--
						Actor_Says(kActorChew, 500, 18); //52-0500.AUD	No, no no. No, no, you please go. I give you all I have. Ah, no more. See, see? No more.
						Actor_Says(kActorMcCoy, 815, 14); //00-0815.AUD	Listen to me!
						Actor_Says(kActorChew, 640, 14); //52-0640.AUD	[speaks in Chinese] You! You bad.
						Actor_Says(kActorChew, 650, 15); //	52-0650.AUD	You go away! Never come back.
						Delay(1000);
						Actor_Face_Heading(kActorChew, 310, true);
						Actor_Says(kActorChew, 610, 14); //52-0610.AUD	(whimpers) My eyes! They fog. Eyes melting, getting slimy. Oh, please eye! Oh, you so mushy!
						Actor_Says(kActorChew, 660, 15); //52-0660.AUD	(yells) Ah!
						Actor_Change_Animation_Mode(kActorChew, 48);
						Delay(2000);
						Actor_Says(kActorMcCoy, 3970, 14); //00-3970.AUD	Hey.
						Delay (1000);
						Actor_Says(kActorTransient, 400, -1); //12-0400.AUD	Zzz…
						Actor_Says(kActorTransient, 410, -1); //12-0410.AUD	Zzz…
						Actor_Says(kActorMcCoy, 8710, 13); //00-8710.AUD	Weird.
						Actor_Says(kActorTransient, 40, -1); //12-0040.AUD	Zzz…
						Delay (1000);
						Game_Flag_Set(kFlagChewTalkGiveData);	
						Game_Flag_Set(kFlagDR03toDR02);
						Set_Enter(kSetDR01_DR02_DR04, kSceneDR02);
						Player_Gains_Control();
						Scene_Exits_Enable();
					} else {
						Actor_Says(kActorMcCoy, 4880, 13); //00-4880.AUD	Is that right?
						Delay(1000);
						Actor_Says(kActorMcCoy, 795, 3);
						Actor_Says(kActorChew, 330, 12);
						Actor_Says(kActorChew, 340, 15);
						Actor_Says(kActorMcCoy, 875, 16);
						Actor_Says(kActorChew, 350, 12);
						Actor_Says(kActorChew, 360, 15);
						Game_Flag_Set(kFlagBB01Available);
						Actor_Says(kActorMcCoy, 5150, 14); //00-5150.AUD	One more thing.
						Actor_Says(kActorChew, 600, 14); // 52-0600.AUD	No, no time! You go. Find Nexus-6. That's your job. Ah.			
						Actor_Says(kActorMcCoy, 940, 15); //00-0940.AUD	I need to ask you--
						Actor_Says(kActorChew, 630, 15); //52-0630.AUD	No, no, no, no, no, no, no.
						Delay(2000);
						Game_Flag_Set(kFlagChewTalkGiveData);	
						Game_Flag_Set(kFlagDR03toDR02);
						Set_Enter(kSetDR01_DR02_DR04, kSceneDR02);
						Player_Gains_Control();
						Scene_Exits_Enable();
					}					
				}
			}
		}
	    if (Global_Variable_Query(kVariableChapter) == 2) {
			if (_vm->_cutContent) {
				Actor_Face_Actor(kActorMcCoy, kActorChew, true);
				Actor_Face_Actor(kActorChew, kActorMcCoy, true);
				if (!Game_Flag_Query(kFlagDR03ChewTalk1)) {
					Actor_Says(kActorChew, 660, 14); // (yells) Ah!
					Actor_Says(kActorChew, 680, 14); // What you want? I busy.
				} else { 
					if (Actor_Query_Friendliness_To_Other(kActorChew, kActorMcCoy) < 50) {
						Actor_Says(kActorChew, 690, 14); // Not good time now, come back later.
						Actor_Says(kActorChew, 710, 14); // (Mumbles in Chinese)
					} else {
						Actor_Says(kActorChew, 670, 14); // Hmph. (mumbles in Chinese)
						Actor_Says(kActorChew, 620, 14); // (yells) What you do, huh?
					}
				}
			} else {
				if (Random_Query(1, 2) == 1) {
					Actor_Face_Actor(kActorChew, kActorMcCoy, true);
					Actor_Says(kActorChew, 660, 14); // (yells) Ah!
					Actor_Says(kActorChew, 680, 14); // What you want? I busy.
				} else if (Random_Query(1, 2) == 2) {
					Actor_Face_Actor(kActorChew, kActorMcCoy, true);
					Actor_Says(kActorChew, 670, 14); // Hmph. (mumbles in Chinese)
					Actor_Says(kActorChew, 620, 14); // (yells) What you do, huh?
				} else {
					Actor_Face_Actor(kActorChew, kActorMcCoy, true);
					Actor_Says(kActorChew, 690, 14); // Not good time now, come back later.
					Actor_Says(kActorChew, 710, 14); // (Mumbles in Chinese)
				}
			}
		}
	}

void SceneScriptDR03::PlayerWalkedOut() {
}

void SceneScriptDR03::DialogueQueueFlushed(int a1) {
}

void SceneScriptDR03::dialogueWithChew() {
	Dialogue_Menu_Clear_List();
	if (_vm->_cutContent) {
		if (Actor_Clue_Query(kActorMcCoy, kClueChewInterview)) {
			DM_Add_To_List_Never_Repeat_Once_Selected(650, 6, 7, 8); // TWINS
		}
	} else if (Actor_Clue_Query(kActorMcCoy, kClueChewInterview)
	 || Actor_Clue_Query(kActorMcCoy, kClueAnsweringMachineMessage)
	 || Actor_Clue_Query(kActorMcCoy, kClueMorajiInterview)
	) {
		DM_Add_To_List_Never_Repeat_Once_Selected(650, 5, 5, 5); // TWINS
	}
	if (Actor_Clue_Query(kActorMcCoy, kClueChewInterview)) {
		DM_Add_To_List_Never_Repeat_Once_Selected(660, 5, 5, 5); // MORAJI
	}
	// Made it so McCoy only warns Chew about the reps if he is not surly or erratic.
	if (_vm->_cutContent) {
		if (Player_Query_Agenda() != kPlayerAgendaSurly 
		&& Player_Query_Agenda() != kPlayerAgendaErratic) {
			DM_Add_To_List_Never_Repeat_Once_Selected(640, 6, 5, -1); // EISENDULLER
		}
	} else if (Actor_Clue_Query(kActorMcCoy, kClueTyrellInterview)) {
		DM_Add_To_List_Never_Repeat_Once_Selected(670, 6, 5, 2); // TYRELL
	}
	if (Game_Flag_Query(kFlagDR03ChewTalkExplosion)) {
		if (Actor_Clue_Query(kActorMcCoy, kClueAnsweringMachineMessage)) {
			DM_Add_To_List_Never_Repeat_Once_Selected(680, 7, 8, 9); // SEBASTIAN
		}
		if (_vm->_cutContent) {
			if (Actor_Clue_Query(kActorMcCoy, kClueEnvelope)
			&& Actor_Clue_Query(kActorMcCoy, kClueChewInterview)) {
				DM_Add_To_List_Never_Repeat_Once_Selected(1270, 2, 3, 4); // LANCE'S ENVELOPE
			}
		} else if (Actor_Clue_Query(kActorMcCoy, kClueEnvelope)) {
			DM_Add_To_List_Never_Repeat_Once_Selected(1270, 2, 5, 7); // LANCE'S ENVELOPE
		}
	}
	Dialogue_Menu_Add_DONE_To_List(690); // DONE

	Dialogue_Menu_Appear(320, 240);
	int answer = Dialogue_Menu_Query_Input();
	Dialogue_Menu_Disappear();

	switch (answer) {
	case 640: // EISENDULLER
		if (_vm->_cutContent) {
			Actor_Says(kActorMcCoy, 765, 12); 
			Actor_Says_With_Pause(kActorMcCoy, 785, 0.80f, 18); 
			Actor_Says(kActorMcCoy, 790, 13);
			Actor_Says(kActorChew, 310, 12);
			if (_vm->_cutContent) {
				if (Actor_Query_Friendliness_To_Other(kActorChew, kActorMcCoy) < 50) {
					Actor_Says(kActorChew, 320, 3);
				}
			} else {
				Actor_Says(kActorChew, 320, 3);
			}
		} else {
			Actor_Says(kActorMcCoy, 770, 12);
			Actor_Says(kActorChew, 110, 12);
			Actor_Says(kActorChew, 120, 13);
			Actor_Says(kActorMcCoy, 835, 13);
			Actor_Says(kActorChew, 130, 14);
			Actor_Says(kActorMcCoy, 840, 16);
			Actor_Says(kActorChew, 140, 15);
			if (!Game_Flag_Query(kFlagDR03ChewTalkExplosion)) {
				Actor_Says(kActorChew, 150, 13);
				Actor_Says(kActorMcCoy, 845, 17);
				Actor_Says(kActorChew, 170, 18);
				Actor_Says(kActorChew, 180, 16);
				Actor_Says(kActorMcCoy, 850, 15);
				Actor_Says(kActorChew, 190, 14);
				Actor_Says(kActorChew, 200, 13);
				Actor_Says(kActorMcCoy, 855, 18);
				Actor_Says(kActorChew, 210, 12);
				Actor_Clue_Acquire(kActorMcCoy, kClueChewInterview, true, kActorChew);
			}
		}
		break;

	case 650: // TWINS
		Actor_Says(kActorMcCoy, 775, 11);
		if (_vm->_cutContent) {
			if (Actor_Query_Friendliness_To_Other(kActorChew, kActorMcCoy) < 50) {
				Actor_Says(kActorChew, 40, 14); //52-0040.AUD	Hey, LPD, you deaf or something, huh, LPD?
				Actor_Says(kActorChew, 50, 14); //52-0050.AUD	I very busy. Eyes will wait for nothing.
				Actor_Says(kActorChew, 250, 14); //52-0250.AUD	I waste no more time. You think I nose around everybody's business, huh?
			} else {
				Actor_Says(kActorChew, 220, 14);
				Actor_Says(kActorMcCoy, 860, 11); //00-0860.AUD	They're genetic designers?
				Actor_Says(kActorChew, 230, 14);
				Actor_Says(kActorMcCoy, 865, 11);
				Actor_Says(kActorChew, 240, 14);
			}
		} else {
			Actor_Says(kActorChew, 220, 14);
			Actor_Says(kActorMcCoy, 860, 11);
			Actor_Says(kActorChew, 230, 14);
			Actor_Says(kActorMcCoy, 865, 11);
			Actor_Says(kActorChew, 240, 14);
			Actor_Says(kActorChew, 250, 14);
		}
		break;

	case 660: // MORAJI
		Actor_Says(kActorMcCoy, 780, 13);
		if (Game_Flag_Query(kFlagDR03ChewTalkExplosion)) {
			if (_vm->_cutContent) {
				if (Actor_Query_Friendliness_To_Other(kActorChew, kActorMcCoy) > 49) {
					Actor_Says(kActorChew, 260, 14);
					Actor_Says(kActorChew, 270, 13);
					Actor_Says(kActorChew, 280, 12);
				} else {
					Actor_Says(kActorChew, 60, 14); //52-0060.AUD	Busy, busy. You not delivery man. You go away!
				}
			} else {
				Actor_Says(kActorChew, 260, 14);
				Actor_Says(kActorChew, 270, 13);
				Actor_Says(kActorChew, 280, 12);
			}
		} else {
			Actor_Says(kActorChew, 260, 14);
			Actor_Says(kActorChew, 270, 13);
			Actor_Says(kActorChew, 280, 12);
			Actor_Says(kActorMcCoy, 870, 18);
			Actor_Says(kActorChew, 290, 15);
			if (!Game_Flag_Query(kFlagDR05JustExploded)) {
				Actor_Says(kActorChew, 300, 12);
			}
		}
		break;

	case 670: // TYRELL
		Actor_Says(kActorMcCoy, 765, 12);
		Actor_Says(kActorMcCoy, 790, 13);
		Actor_Says(kActorChew, 310, 12);
		Actor_Says(kActorChew, 320, 3);
		break;

	case 680: // SEBASTIAN
		Actor_Says(kActorMcCoy, 795, 3);
		if (Game_Flag_Query(kFlagDR03ChewTalkExplosion)) {
			Actor_Says(kActorChew, 330, 12);
			Actor_Says(kActorChew, 340, 15);
			Actor_Says(kActorMcCoy, 875, 16);
			Actor_Says(kActorChew, 350, 12);
			Actor_Says(kActorChew, 360, 15);
			Game_Flag_Set(kFlagBB01Available);
		} else {
			Actor_Says(kActorChew, 320, 13);
			Actor_Says(kActorChew, 150, 14);
			Game_Flag_Set(kFlagBB01Available);
		}
		break;

	case 690: // DONE
		if (_vm->_cutContent) {
			if (Player_Query_Agenda() == kPlayerAgendaPolite) {
				Actor_Says(kActorMcCoy, 805, 3); //00-0805.AUD	Sorry to bother you.
			} else if (Player_Query_Agenda() == kPlayerAgendaSurly 
			|| Player_Query_Agenda() == kPlayerAgendaErratic) {
				Actor_Says(kActorMcCoy, 8715, 17); //00-8715.AUD	Weirdo.
			} else {
				Actor_Says(kActorMcCoy, 4595, 14); //00-4595.AUD	Stick around. I may not be finished with you.
			}	
		} else {
			Actor_Says(kActorMcCoy, 4595, 14);
		}
		break;

	case 1270: // LANCE'S ENVELOPE
		Actor_Says(kActorMcCoy, 800, 16);
		if (_vm->_cutContent) {
			if (Actor_Query_Friendliness_To_Other(kActorChew, kActorMcCoy) > 49) {
				Actor_Says(kActorChew, 370, 3);
				Actor_Says(kActorMcCoy, 880, 15);
				Actor_Says(kActorChew, 380, 13);
				Actor_Says(kActorChew, 390, 12);
				Actor_Says(kActorMcCoy, 885, 14);
				Actor_Says(kActorChew, 400, 13);
				Actor_Says(kActorChew, 410, 15);
				Actor_Says(kActorMcCoy, 890, 18);
				Actor_Says(kActorChew, 420, 13);
				if (Player_Query_Agenda() != kPlayerAgendaPolite) {
					Actor_Says(kActorMcCoy, 2485, 18); //00-2485.AUD	I’ve a hard time believing that.
					Actor_Says(kActorChew, 720, 14); //52-0720.AUD	Pah! You believe what you believe, McCoy.
				} else {
					Actor_Says(kActorChew, 430, 12);
				}
			} else {
				Actor_Says(kActorChew, 20, 14);//52-0020.AUD	Hmm. Talk, talk, talk, always talk. You wait. You no take up time. Busy, busy.
			}
		} else {
			Actor_Says(kActorChew, 370, 3);
			Actor_Says(kActorMcCoy, 880, 15);
			Actor_Says(kActorChew, 380, 13);
			Actor_Says(kActorChew, 390, 12);
			Actor_Says(kActorMcCoy, 885, 14);
			Actor_Says(kActorChew, 400, 13);
			Actor_Says(kActorChew, 410, 15);
			Actor_Says(kActorMcCoy, 890, 18);
			Actor_Says(kActorChew, 420, 13);
			Actor_Says(kActorChew, 430, 12);
		}
		break;
	}
}

} // End of namespace BladeRunner
