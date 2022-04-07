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

void SceneScriptPS09::InitializeScene() {
	if (Game_Flag_Query(kFlagMcCoyArrested)) {
		Setup_Scene_Information(-410.0f, 0.26f, -200.0f, 512);
	} else {
		Setup_Scene_Information(-559.0f, 0.0f, -85.06f, 250);
	}

	Scene_Exit_Add_2D_Exit(0, 0, 0, 30, 479, 3);

	Ambient_Sounds_Remove_All_Non_Looping_Sounds(false);
	Ambient_Sounds_Add_Looping_Sound(kSfxBRBED5X,  50, 0, 0);
	Ambient_Sounds_Add_Looping_Sound(kSfxPRISAMB1, 30, 0, 0);
	Ambient_Sounds_Add_Looping_Sound(kSfxPRISAMB3, 30, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxPRISSLM1, 15, 60, 7, 10, 100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxPRISSLM2, 25, 60, 7, 10, 100, 100, -101, -101, 0, 0);
	Ambient_Sounds_Add_Sound(kSfxPRISSLM3, 25, 60, 7, 10, 100, 100, -101, -101, 0, 0);

	if (!Game_Flag_Query(kFlagGrigorianArrested)) {
		Actor_Put_In_Set(kActorGrigorian, kSetPS09);
		Actor_Set_At_XYZ(kActorGrigorian, -417.88f, 0.0f, -200.74f, 512);
		Game_Flag_Set(kFlagGrigorianArrested);
	}
	if (Game_Flag_Query(kFlagMcCoyArrested)) {
		Actor_Put_In_Set(kActorGrigorian, kSetFreeSlotD);
		Actor_Set_At_XYZ(kActorGrigorian, 0.0f, 0.0f, 0.0f, 512);
	}
	if (Game_Flag_Query(kFlagIzoArrested)) {
		Actor_Put_In_Set(kActorIzo, kSetPS09);
		Actor_Set_At_XYZ(kActorIzo, -476.0f, 0.2f, -225.0f, 518);
	}
	if (Game_Flag_Query(kFlagCrazylegsArrested)) { // cut feature? it is impossible to arrest crazylegs
		Actor_Put_In_Set(kActorCrazylegs, kSetPS09);
#if BLADERUNNER_ORIGINAL_BUGS
		Actor_Set_At_XYZ(kActorCrazylegs, -290.0f, 0.33f, -235.0f, 207);
#else
		// Correct orientation for CrazyLegs
		Actor_Set_At_XYZ(kActorCrazylegs, -290.0f, 0.33f, -235.0f, 583);
#endif
	}
}

void SceneScriptPS09::SceneLoaded() {
	Obstacle_Object("OFFICE DOOR", true);
	Unobstacle_Object("OFFICE DOOR", true);
	Unclickable_Object("OFFICE DOOR");
}

bool SceneScriptPS09::MouseClick(int x, int y) {
	return false;
}

bool SceneScriptPS09::ClickedOn3DObject(const char *objectName, bool a2) {
	return false;
}

bool SceneScriptPS09::ClickedOnActor(int actorId) {
	if (actorId == kActorGrigorian) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -381.11f, 0.0f, -135.55f, 0, true, false, false)) {
			Actor_Face_Actor(kActorMcCoy, kActorGrigorian, true);
			Actor_Face_Actor(kActorGrigorian, kActorMcCoy, true);

			if (!Game_Flag_Query(kFlagPS09GrigorianTalk1)) {
				Actor_Says(kActorGrigorian, 0, 12);
				Actor_Says(kActorMcCoy, 4235, 18);
				Actor_Says(kActorGrigorian, 10, 13);
				Game_Flag_Set(kFlagPS09GrigorianTalk1);
				return true;
			}

			if ( Game_Flag_Query(kFlagPS09GrigorianTalk1)
			 && !Game_Flag_Query(kFlagPS09GrigorianTalk2)
			 && !Actor_Clue_Query(kActorMcCoy, kClueGrigorianInterviewA)
			 && !Actor_Clue_Query(kActorMcCoy, kClueGrigorianInterviewB1)
			 && !Actor_Clue_Query(kActorMcCoy, kClueGrigorianInterviewB2)
			) {
				Actor_Says(kActorMcCoy, 4245, 14);
				Actor_Says(kActorGrigorian, 20, 14);
				Game_Flag_Set(kFlagPS09GrigorianTalk2);
				return true;
			}

			if (!Game_Flag_Query(kFlagPS09GrigorianDialogue)
			 &&  Game_Flag_Query(kFlagPS09GrigorianTalk1)
			 &&  (Actor_Clue_Query(kActorMcCoy, kClueGrigorianInterviewA)
			  ||  Actor_Clue_Query(kActorMcCoy, kClueGrigorianInterviewB1)
			  ||  Actor_Clue_Query(kActorMcCoy, kClueGrigorianInterviewB2)
			  ||  Actor_Clue_Query(kActorMcCoy, kClueGrigoriansNote)
			 )
			) {
				Game_Flag_Set(kFlagPS09GrigorianDialogue);
				Actor_Says(kActorMcCoy, 4240, 13);
				Actor_Says(kActorGrigorian, 550, 15); //11-0550.AUD	No.
				//Jake - Restored some dialogue for Grigorian and McCoy.
				if (_vm->_cutContent) {
            		Actor_Says(kActorMcCoy, 6995, 18); //00-6995.AUD	That's not what I heard. You wanna set the record straight?
					Delay (1000);
					Actor_Says(kActorGrigorian, 1230, 15); //11-1230.AUD	Well, I'm afraid you've caught me, detective.
					Actor_Says(kActorMcCoy, 5705, 18); //00-5705.AUD	Uh-huh.
     		 	} 
				Actor_Says(kActorGrigorian, 480, 16);
				dialogueWithGrigorian();
				return true;
			}

			if (Game_Flag_Query(kFlagGrigorianDislikeMcCoy)) {
				Actor_Says(kActorMcCoy, 4270, 18);
				Actor_Says(kActorGrigorian, 30, 14);
				Actor_Says(kActorGrigorian, 40, 13);
				return true;
			}

			// TODO Missing kClueGrigorianInterviewB2 for this?
			if (Game_Flag_Query(kFlagPS09GrigorianDialogue)
			 && Game_Flag_Query(kFlagPS09GrigorianTalk1)
			 && (Actor_Clue_Query(kActorMcCoy, kClueGrigorianInterviewA)
			  || Actor_Clue_Query(kActorMcCoy, kClueGrigorianInterviewB1)
			  || Actor_Clue_Query(kActorMcCoy, kClueGrigorianInterviewB2)
			  || Actor_Clue_Query(kActorMcCoy, kClueGrigoriansNote)
			 )
			) {
				dialogueWithGrigorian();
				return true;
			}

			Actor_Says(kActorMcCoy, 4270, 18);
			Actor_Says(kActorGrigorian, 30, 14);
			Actor_Says(kActorGrigorian, 40, 13);
			return true;
		}
	}

	if (actorId == kActorIzo) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -473.0f, 0.2f, -133.0f, 12, true, false, false)) {
			Actor_Face_Actor(kActorMcCoy, kActorIzo, true);
			Actor_Face_Actor(kActorIzo, kActorMcCoy, true);

			if (!Game_Flag_Query(kFlagPS09IzoTalk1)) {
				Actor_Says(kActorMcCoy, 4200, 14);
				Actor_Says(kActorIzo, 570, kAnimationModeTalk);
				Actor_Says(kActorMcCoy, 4205, 18);
				Game_Flag_Set(kFlagPS09IzoTalk1);
				return true;
			}

			if ( Game_Flag_Query(kFlagPS09IzoTalk1)
			 && !Game_Flag_Query(kFlagPS09IzoTalk2)
			) {
				Actor_Says(kActorMcCoy, 4210, 18);
				Actor_Says(kActorIzo, 580, kAnimationModeTalk);
				Actor_Says(kActorMcCoy, 4215, 14);
				Actor_Says(kActorIzo, 590, kAnimationModeTalk);
				Actor_Says(kActorIzo, 600, kAnimationModeTalk);
				Actor_Says(kActorMcCoy, 4220, 18);
				Actor_Says(kActorIzo, 610, kAnimationModeTalk);
				Actor_Says(kActorMcCoy, 4225, 19);
				Actor_Says(kActorIzo, 620, kAnimationModeTalk);
				Actor_Says(kActorMcCoy, 4230, 14);
				Game_Flag_Set(kFlagPS09IzoTalk2);
				return true;
			}
			if (_vm->_cutContent) {
				if (Player_Query_Agenda() == kPlayerAgendaSurly
		  	  	|| Player_Query_Agenda() == kPlayerAgendaErratic) {
					Actor_Says(kActorMcCoy, 4200, 13); 
				} else {
					Actor_Says(kActorMcCoy, 8590, 13); //00-8590.AUD	Not the talkative type.
				}
			} else {
				Actor_Says(kActorMcCoy, 4200, 13);
			}
			return true;
		}
	}

	if (actorId == kActorCrazylegs) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -295.0f, 0.34f, -193.0f, 12, true, false, false)) {
			Actor_Face_Actor(kActorMcCoy, kActorCrazylegs, true);
			Actor_Face_Actor(kActorCrazylegs, kActorMcCoy, true);
			// Made it so McCoy only taunts Crazylegs if he is surly or erratic.
			if (!Game_Flag_Query(kFlagPS09CrazylegsTalk1)) {
				if (!Actor_Clue_Query(kActorMcCoy, kClueCrazylegsInterview3)) {
					if (Player_Query_Agenda() == kPlayerAgendaSurly
					|| Player_Query_Agenda() == kPlayerAgendaErratic) {			
						Actor_Says(kActorMcCoy, 4415, 18); //00-4415.AUD	Guess you can't sell a whole lot of cars from down here, Crazy.
					} else {
						Actor_Says(kActorMcCoy, 8920, 18); //00-8920.AUD	I gotta ask you a question.
					}
					Actor_Says(kActorCrazylegs, 1090, kAnimationModeTalk); //09-1090.AUD	I’m being railroaded! All I did was conduct business as per usual.
					//Restored some dialogue between Crazylegs and McCoy. Originally this dialogue only played if Grigorian was not arrested but since that can
					//not happen it only seems fair to include it here.
					if (_vm->_cutContent) {
						Actor_Says(kActorMcCoy, 7835, 18); //00-7835.AUD	Is that so?
						Actor_Says(kActorCrazylegs, 1100, kAnimationModeTalk); //09-1100.AUD	Whatever happened I was ignorant, McCoy.
						Actor_Says(kActorMcCoy, 4430, 17); //00-4430.AUD	I figured you for a lot of things but ignorant wasn't one of them.
						Actor_Says(kActorCrazylegs, 1110, kAnimationModeTalk); //09-1110.AUD	You’d know what I mean.
					}
					Actor_Says(kActorMcCoy, 4420, 18); //00-4420.AUD	Contacting business with Reps is against the Law.
					Game_Flag_Set(kFlagPS09CrazylegsTalk1);
				}
			}

			if ( Game_Flag_Query(kFlagPS09CrazylegsTalk1)
			 &&  Game_Flag_Query(kFlagGrigorianArrested)
			 && !Game_Flag_Query(kFlagPS09CrazylegsGrigorianTalk)
			) {
				Actor_Face_Actor(kActorGrigorian, kActorCrazylegs, true);
				Actor_Says(kActorGrigorian, 420, 14); //11-0420.AUD	You don't have to be afraid of the truth, Larry.
				Actor_Face_Actor(kActorCrazylegs, kActorGrigorian, true);
				Actor_Says(kActorCrazylegs, 1120, kAnimationModeTalk); //09-1120.AUD	I don’t know what you’re talking about.		
				Actor_Face_Actor(kActorMcCoy, kActorGrigorian, true);
				// Made it so McCoys comment towards Grigorian isn't as harsh if McCoy isn't surly or erratic.
				if (Actor_Clue_Query(kActorMcCoy, kClueGrigorianInterviewA)) {
					if (Player_Query_Agenda() == kPlayerAgendaSurly
		  			|| Player_Query_Agenda() == kPlayerAgendaErratic) {
						Actor_Says(kActorMcCoy, 4435, 14); //00-4435.AUD	You got a bad case of diarrhea of the mouth, Spencer.
						Actor_Says(kActorGrigorian, 430, 16); //11-0430.AUD	In that case I'll zip my lips.
						Actor_Modify_Friendliness_To_Other(kActorGrigorian, kActorMcCoy, -5);
#if !BLADERUNNER_ORIGINAL_BUGS
						Actor_Face_Heading(kActorGrigorian, 512, true);
#endif
						Actor_Says(kActorCrazylegs, 1130, kAnimationModeTalk); //09-1130.AUD	Damn good idea!
					} else {
						Actor_Says(kActorMcCoy, 7915, 14);	//00-7915.AUD	We're not finished yet.
						Actor_Says(kActorGrigorian, 430, 16); //11-0430.AUD	In that case I'll zip my lips.
						Delay (1000);
						Actor_Says(kActorMcCoy, 8370, 14); //00-8370.AUD	It's okay. I got what I need.
					}
					Game_Flag_Set(kFlagPS09CrazylegsGrigorianTalk);
#if !BLADERUNNER_ORIGINAL_BUGS
				Actor_Face_Actor(kActorCrazylegs, kActorMcCoy, true);
#endif
					return true;
				}
			}
			// Removed the code that only plays certain dialogue with Crazylegs if Grigorian is not present.

			Actor_Says(kActorMcCoy, 4425, 18);
			Actor_Says(kActorCrazylegs, 1160, kAnimationModeTalk);
			return true;
		}
	}
	return false;

	if (actorId == kActorEarlyQ) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -381.11f, 0.0f, -135.55f, 0, true, false, false)) {
			Actor_Face_Actor(kActorMcCoy, kActorEarlyQ, true);
			Actor_Face_Actor(kActorEarlyQ, kActorMcCoy, true);
			Actor_Says(kActorMcCoy, 8513, 18); //00-8513.AUD	Early, how's it hanging?
			Actor_Says(kActorEarlyQ, 340, kAnimationModeTalk); //18-0340.AUD	No more free drinks for you, buddy boy.
			return true;
		}
	}
	if (actorId == kActorDektora) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -295.0f, 0.34f, -193.0f, 12, true, false, false)) {
			Actor_Face_Actor(kActorMcCoy, kActorDektora, true);
			Actor_Face_Actor(kActorDektora, kActorMcCoy, true);
			Actor_Says(kActorMcCoy, 6985, 16); //00-6985.AUD	Got the straight scoop for me or what?
			Actor_Says(kActorDektora, 620, kAnimationModeTalk); //03-0620.AUD	I’m sure I don’t know what you mean.
			return true;
		}
	}
}

bool SceneScriptPS09::ClickedOnItem(int itemId, bool a2) {
	return false;
}

bool SceneScriptPS09::ClickedOnExit(int exitId) {
	if (exitId == 0) {
		if (!Loop_Actor_Walk_To_XYZ(kActorMcCoy, -559.15f, 0.0f, -85.06f, 0, true, false, false)) {
			Ambient_Sounds_Remove_All_Non_Looping_Sounds(true);
			Ambient_Sounds_Remove_All_Looping_Sounds(1u);
			Set_Enter(kSetPS02, kScenePS02);
			Game_Flag_Reset(kFlagPS09Entered);
		}
		return true;
	}
	return false;
}

bool SceneScriptPS09::ClickedOn2DRegion(int region) {
	return false;
}

void SceneScriptPS09::SceneFrameAdvanced(int frame) {
	if (frame == 1
	 || frame == 15
	 || frame == 20
	 || frame == 31
	 || frame == 33
	 || frame == 35
	 || frame == 52
	 || frame == 54
	) {
		Sound_Play(kSfxNEON7, Random_Query(50, 33), 10, 10, 50);
	}
	//return true;
}

void SceneScriptPS09::ActorChangedGoal(int actorId, int newGoal, int oldGoal, bool currentSet) {
}

void SceneScriptPS09::PlayerWalkedIn() {
	if (Game_Flag_Query(kFlagMcCoyArrested)) {
		Player_Loses_Control();
		Delay(2000);
		Actor_Retired_Here(kActorMcCoy, 6, 6, 1, -1);
		//return true;
		return;
	}
	if (!Game_Flag_Query(kFlagPS09Entered)) {
		Player_Loses_Control();
		Loop_Actor_Walk_To_XYZ(kActorMcCoy, -491.15f, 0.0f, -73.06f, 0, false, false, false);
		Player_Gains_Control();
		Game_Flag_Set(kFlagPS09Entered);
	}
	if (Game_Flag_Query(kFlagPS02toPS09)) {
		Game_Flag_Reset(kFlagPS02toPS09);
		//return true;
		return;
	}
	//return false;
}

void SceneScriptPS09::PlayerWalkedOut() {
}

void SceneScriptPS09::DialogueQueueFlushed(int a1) {
}

void SceneScriptPS09::dialogueWithGrigorian() {
	Dialogue_Menu_Clear_List();
	if (Actor_Clue_Query(kActorMcCoy, kClueGrigorianInterviewA)
	 || Actor_Clue_Query(kActorMcCoy, kClueGrigorianInterviewB1)
	 || Actor_Clue_Query(kActorMcCoy, kClueGrigorianInterviewB2)
	) {
		// There is unused dialogue that suggests that McCoy could have been either nice or mean to Grigorian and as a result Grigorian would have responded to McCoy
		// differently. I have adjusted the dialogue slightly so McCoy is not as harsh to Grigorian if he is not surly or erratic. The lines of Grigorian addressing how
		// McCoy has treated him only plays when you select the protest option. However it is only during the cars conversation where McCoy is either nice or mean to Grigorian.
		// In order for this to work I have made it so the protest option only becomes available if the cars option is picked. When the cars option is picked the player gains the 
		// restored clue Grigorians resources and this activates the protest option. It would make no sense for the player to pick the protest option and Grigorian talks about McCoys 
		// treatment of him before that even happens, so this change feels necessary.
		if (_vm->_cutContent) {
			if (Actor_Clue_Query(kActorMcCoy, kClueGrigoriansResources)) {
				DM_Add_To_List_Never_Repeat_Once_Selected(170,  5, 5, 3); // PROTEST
			}
		} else {
			 DM_Add_To_List_Never_Repeat_Once_Selected(170,  5, 5, 3); // PROTEST
		}
		DM_Add_To_List_Never_Repeat_Once_Selected(180, -1, 5, 5); // CARS
		if ((_vm->_cutContent
		     && (!Game_Flag_Query(kFlagPS09GrigorianVKChosen)
		     && (!Actor_Clue_Query(kActorMcCoy, kClueVKGrigorianHuman) && !Actor_Clue_Query(kActorMcCoy, kClueVKGrigorianReplicant))))
		    || !_vm->_cutContent
		) {
			if (_vm->_cutContent) {
				Dialogue_Menu_Clear_Never_Repeat_Was_Selected_Flag(200);
			}
			DM_Add_To_List_Never_Repeat_Once_Selected(200, -1, 3, 6); // VOIGT-KAMPFF
		}
	}
	if (Actor_Clue_Query(kActorMcCoy, kClueGrigoriansNote) // Restored feature - Original: it is impossible to obtain this clue
	 && (Actor_Clue_Query(kActorMcCoy, kClueGrigorianInterviewA)
	  || Actor_Clue_Query(kActorMcCoy, kClueGrigorianInterviewB1)
	  || Actor_Clue_Query(kActorMcCoy, kClueGrigorianInterviewB2)
	 )
	) {
		DM_Add_To_List_Never_Repeat_Once_Selected(190, 5, 6, -1); // NOTE
	}
#if BLADERUNNER_ORIGINAL_BUGS
	Dialogue_Menu_Add_To_List(210); // DONE // A bug? why not Dialogue_Menu_Add_DONE_To_List?
#else
	Dialogue_Menu_Add_DONE_To_List(210); // DONE
#endif // BLADERUNNER_ORIGINAL_BUGS

	Dialogue_Menu_Appear(320, 240);
	int answer = Dialogue_Menu_Query_Input();
	Dialogue_Menu_Disappear();

	switch (answer) {
	case 170: // PROTEST
		Actor_Says(kActorMcCoy, 4270, 13);
		Actor_Says(kActorMcCoy, 4250, 18);
		Actor_Says(kActorGrigorian, 50, 13);
		Actor_Says(kActorMcCoy, 4275, 18);
		Actor_Says(kActorMcCoy, 4280, 19);
		// Altered Grigorians response to McCoy depending on his behaviour towards him.
		if (_vm->_cutContent) {
			if (Actor_Query_Friendliness_To_Other(kActorGrigorian, kActorMcCoy) < 43) {
				//McCoy was mean.
				Actor_Says(kActorGrigorian, 1210, 13); //11-1210.AUD	Tell me, detective. What possible interest would I have in telling you the truth? You're a killer!
				Actor_Says(kActorMcCoy, 8519, 18); ////00-8519.AUD	What do you say we dish each other the straight goods.
				Actor_Says(kActorGrigorian, 1190, 13); //11-1190.AUD	I haven't heard anything that could possibly be of even remote interest to you, detective.
			} else if (Actor_Query_Friendliness_To_Other(kActorGrigorian, kActorMcCoy) > 43) {		
				if (Game_Flag_Query(kFlagIzoIsReplicant)) {
					Actor_Says(kActorGrigorian, 1240, 13); //11-1240.AUD	I can't imagine what you think this information will do for you but... here's the truth.
					Actor_Says(kActorGrigorian, 60, 14); //11-0060.AUD	I don't know them.
					Actor_Says(kActorMcCoy, 4285, 13);
					Actor_Says(kActorGrigorian, 70, 12);
					Actor_Says(kActorMcCoy, 4290, 13);
					Actor_Says(kActorGrigorian, 80, 13);
					Actor_Says(kActorGrigorian, 90, 13);
					Actor_Says(kActorMcCoy, 4295, 18);
					Actor_Says(kActorGrigorian, 110, 14);
					Actor_Says(kActorMcCoy, 4300, 17);
				} else {
					Actor_Says(kActorGrigorian, 1170, 13); //11-1170.AUD	Well, normally I wouldn't talk to a detective. Especially a killer like you.
					Actor_Says(kActorGrigorian, 1180, 13); //11-1180.AUD	But you have been quite decent to me. I did hear something you might find interesting.
					Actor_Says(kActorMcCoy, 3415, 18); //00-3415.AUD	Let’s hear what you got.
					Actor_Says(kActorGrigorian, 130, 15); //11-0130.AUD	I didn't know the Rastafarian.
					Actor_Says(kActorGrigorian, 140, 13);
					Actor_Says(kActorMcCoy, 4305, 13);
					Actor_Says(kActorGrigorian, 150, 14);
					Actor_Says(kActorGrigorian, 160, 12);
					Actor_Says(kActorMcCoy, 4310, 13);
					Actor_Says(kActorGrigorian, 170, 15);
					Actor_Says(kActorGrigorian, 180, 16);
					Actor_Says(kActorMcCoy, 4315, 18);
					Actor_Says(kActorGrigorian, 190, kAnimationModeTalk);
					Actor_Says(kActorGrigorian, 200, 13);
					Actor_Clue_Acquire(kActorMcCoy, kClueGrigoriansResponse1, true, kActorGrigorian);
				}
			}
		} else if (Game_Flag_Query(kFlagIzoIsReplicant)) {
			Actor_Says(kActorGrigorian, 60, 14);
			Actor_Says(kActorMcCoy, 4285, 13);
			Actor_Says(kActorGrigorian, 70, 12);
			Actor_Says(kActorMcCoy, 4290, 13);
			Actor_Says(kActorGrigorian, 80, 13);
			Actor_Says(kActorGrigorian, 90, 13);
			Actor_Says(kActorMcCoy, 4295, 18);
			Actor_Says(kActorGrigorian, 110, 14);
			Actor_Says(kActorMcCoy, 4300, 17);
		} else {
			Actor_Says(kActorGrigorian, 130, 15);
			Actor_Says(kActorGrigorian, 140, 13);
			Actor_Says(kActorMcCoy, 4305, 13);
			Actor_Says(kActorGrigorian, 150, 14);
			Actor_Says(kActorGrigorian, 160, 12);
			Actor_Says(kActorMcCoy, 4310, 13);
			Actor_Says(kActorGrigorian, 170, 15);
			Actor_Says(kActorGrigorian, 180, 16);
			Actor_Says(kActorMcCoy, 4315, 18);
			if (_vm->_cutContent
			    && (_vm->_language == Common::ES_ESP
			        || _vm->_language == Common::IT_ITA)
			) {
				// In ESP and ITA versions:
				// Quote 190 is the full quote.
				// "Everything and anything. Guns so new that even the police had hardly used them I heard."
				// Quote 200 is muted in ESP and becomes redundant in ITA
				Actor_Says(kActorGrigorian, 190, kAnimationModeTalk);
				// TODO: When mixing ESP or ITA voiceover with subtitles from other languages,
				//       those subtitles would have to be merged with the 190 quote
				//       in order to show up in the ESP amd ITA version
				//       Also, the spoken quote appears in ESP version only in restored content mode!
			} else if (_vm->_cutContent) {
				// TODO is RUS version covered by this case?
				// In ENG, FRA and DEU versions:
				// Quote 190 is the first half:
				// "Everything and anything."
				// and quote 200 is the second half:
				// "Guns so new that even the police had hardly used them I heard."
				Actor_Says(kActorGrigorian, 190, kAnimationModeTalk);
				Actor_Says(kActorGrigorian, 200, 13);
			} else {
				// vanilla version (non-restored content)
				// This plays only the second half of the full quote in ENG, FRA, DEU and ITA versions
#if BLADERUNNER_ORIGINAL_BUGS
				Actor_Says(kActorGrigorian, 200, 13);
#else
				// Quote 200 is muted in the ESP version
				if (_vm->_language != Common::ES_ESP) {
					Actor_Says(kActorGrigorian, 200, 13);
				}
#endif // BLADERUNNER_ORIGINAL_BUGS
			}
			return;
		}
		break;

	case 180: // CARS
		Actor_Says(kActorMcCoy, 4270, 18);
		Actor_Says(kActorMcCoy, 4255, kAnimationModeTalk);
#if BLADERUNNER_ORIGINAL_BUGS
		Actor_Says(kActorGrigorian, 210, 12);
		Actor_Says(kActorGrigorian, 220, 13);
		Actor_Says(kActorGrigorian, 230, 14);
#else
		if (_vm->_language != Common::ES_ESP) {
			Actor_Says(kActorGrigorian, 210, 12);
			Actor_Says(kActorGrigorian, 220, 13);
			// pause (after the quote is spoken) is set to 0.0f here
			// Grigorian is interrupted by McCoy here, so there shouldn't be any pause after his quote
			Actor_Says_With_Pause(kActorGrigorian, 230, 0.0f, 15); //11-0230.AUD	The “Citizens Against Replicant Slavery” will spearhead the movement towards--
		} else {
			// In ESP version, quote 210 contains the full quote,
			// and quotes 220 and 230 are muted.
			// The pause (after the quote is spoken) is set to 0.0f here, because Grigorian is interrupted in the end
			Actor_Says_With_Pause(kActorGrigorian, 210, 0.0f, 12);
			// we skip the muted quotes for the ESP version
			// TODO: When mixing ESP voiceover with subtitles from other languages,
			//       those subtitles would have to be merged with the previous full quote (210)
			//       in order to show up in the ESP version
		}
#endif // BLADERUNNER_ORIGINAL_BUGS
		// Added in code so McCoy is either nice or mean to Grigorian based on his agenda. Also being mean will set the Grigorian upset flag and Grigorian will treat you accordingly.
		if (_vm->_cutContent) {
		   if (Player_Query_Agenda() == kPlayerAgendaSurly 
			|| Player_Query_Agenda() == kPlayerAgendaErratic) {
				Actor_Says(kActorMcCoy, 4320, 14); //00-4320.AUD	Save the pitch for someone who gives a shit.
			} else {
				Actor_Says(kActorMcCoy, 2750, kAnimationModeTalk); //00-2750.AUD	Okay, I get the picture.
			}
		} else { 
			Actor_Says(kActorMcCoy, 4320, 14);           
		}
		if (_vm->_cutContent) {
			// "What else do you guys do besides wave signs"
			if (Player_Query_Agenda() == kPlayerAgendaSurly 
			|| Player_Query_Agenda() == kPlayerAgendaErratic) {
				Actor_Says(kActorMcCoy, 4325, kAnimationModeTalk);
				// McCoy was mean, Grigorian friendliness drop.
				Actor_Modify_Friendliness_To_Other(kActorGrigorian, kActorMcCoy, -5);
			}
		} else {
			Actor_Says(kActorMcCoy, 4325, kAnimationModeTalk);
		}
		Actor_Says(kActorGrigorian, 240, 16);
		Actor_Says(kActorGrigorian, 250, 15);
		Actor_Says(kActorMcCoy, 4330, 13);
		Actor_Says(kActorGrigorian, 260, 13);
		Actor_Says(kActorGrigorian, 270, 12);
		if (_vm->_cutContent) {
			// In the ESP version quote 280 is muted. The previous quote (270) already contains the full quote.
			// Essentially, the full quote is not removed content in the vanilla ESP version
			// TODO: When mixing ESP voiceover with subtitles from other languages,
			//       those subtitles would have to be merged with the previous full quote (270)
			//       in order to show up in the ESP version
			if (_vm->_language != Common::ES_ESP) {
				// "A way for the slaves to escape"
				Actor_Says(kActorGrigorian, 280, 12);
			}
		}
		Actor_Says(kActorMcCoy, 4335, 18);
		Actor_Says(kActorGrigorian, 290, 15);
		Actor_Says(kActorMcCoy, 4340, 13);
		// Since the protest option is triggered by McCoy gaining the Grigorians resources clue I have moved to conversation with Crazylegs and Grigorian to the end
		// of the conversation. This is because it would be unfair for the player not to access the protest option just because Crazylegs was there and that stops them from gaining the Grigorians
		// resources clue.
			Actor_Says(kActorGrigorian, 320, 13);
			if (_vm->_cutContent) {
				// In the ESP version quote 330 is muted. The previous quote (320) already contains the full quote.
				// Essentially, the full quote is not removed content in the vanilla ESP version
				// TODO: When mixing ESP voiceover with subtitles from other languages,
				//       those subtitles would have to be merged with the previous full quote (320)
				//       in order to show up in the ESP version
				if (_vm->_language != Common::ES_ESP) {
					// "Friends with access to vehicles"
					Actor_Says(kActorGrigorian, 330, kAnimationModeTalk);
				}
			}
#if BLADERUNNER_ORIGINAL_BUGS
			Actor_Says(kActorGrigorian, 340, 14);
			Actor_Says(kActorGrigorian, 350, 12);
#else
			if (_vm->_language != Common::ES_ESP) {
				Actor_Says(kActorGrigorian, 340, 14);
				Actor_Says_With_Pause(kActorGrigorian, 350, 0.0f, 15);
			} else {
				// quote 350 is muted in ESP version. The quote 340 contains the full quote
				// TODO: When mixing ESP voiceover with subtitles from other languages,
				//       those subtitles would have to be merged with the previous full quote (340)
				//       in order to show up in the ESP version
				Actor_Says_With_Pause(kActorGrigorian, 340, 0.0f, 14);
			}
			Actor_Clue_Acquire(kActorMcCoy, kClueGrigoriansResources, true, kActorGrigorian);
			if (_vm->_cutContent) {
				CDB_Set_Crime(kClueGrigoriansResources, kCrimeReplicantHarboring);
			}
#endif // BLADERUNNER_ORIGINAL_BUGS
		//Altered code so McCoy can be nice.
		if (_vm->_cutContent) {
		    if (Player_Query_Agenda() == kPlayerAgendaSurly
		   	|| Player_Query_Agenda() == kPlayerAgendaErratic) {
				Actor_Says(kActorMcCoy, 4375, 14); //00-4375.AUD	A lot of them will wake up dead, if Reps are allowed to run amok on Terra, jerk.
				Actor_Modify_Friendliness_To_Other(kActorGrigorian, kActorMcCoy, -5);
			} else {
				Actor_Says(kActorMcCoy, 1510, kAnimationModeTalk); //00-1510.AUD	Okay, okay. Just forget it.
			}
		} else { 
			Actor_Says(kActorMcCoy, 4375, 14);           
		} 
	 //Moved Grigorians interaction with Crazylegs here so the player will be able to gain the Grigorians resources clue and acces the protest option.
		if (Game_Flag_Query(kFlagCrazylegsArrested)) {
			Actor_Says(kActorGrigorian, 300, 12);
			Actor_Face_Actor(kActorCrazylegs, kActorGrigorian, true);
			Actor_Says(kActorCrazylegs, 1010, kAnimationModeTalk);
			Actor_Face_Actor(kActorGrigorian, kActorCrazylegs, true);
#if BLADERUNNER_ORIGINAL_BUGS
			Actor_Says(kActorGrigorian, 310, 16);
#else
			// Grigorian is interrupted here
			Actor_Says_With_Pause(kActorGrigorian, 310, 0.0f, 16);
#endif // BLADERUNNER_ORIGINAL_BUGS
			Actor_Face_Actor(kActorMcCoy, kActorCrazylegs, true);
			Actor_Says(kActorMcCoy, 4345, 14); 
			Actor_Face_Actor(kActorCrazylegs, kActorMcCoy, true);
			Actor_Says(kActorCrazylegs, 1020, kAnimationModeTalk);
			Actor_Says(kActorMcCoy, 4350, 18); 
			Delay(1000);
			if (Player_Query_Agenda() == kPlayerAgendaSurly
			|| Player_Query_Agenda() == kPlayerAgendaErratic) {
				Actor_Says(kActorMcCoy, 4360, 16); //00-4360.AUD	Tell it straight or I'm gonna make sure you get the same as he gets. Full conspiracy, payable for 25.
				Actor_Says(kActorCrazylegs, 1030, kAnimationModeTalk);
				Actor_Says(kActorMcCoy, 4355, 19); // 00-4355.AUD	So you were ready to do business with the Reps who dropped by your place.
				// Added code so Crazylegs only says he didn't know what that broad was only if Dektora is a rep.
				if (Game_Flag_Query(kFlagDektoraIsReplicant)) {
					Actor_Says(kActorCrazylegs, 1040, kAnimationModeTalk); //09-1040.AUD	Hey, I didn’t know what that broad was.
				}
				// Added in code so McCoy is nice or mean to Crazylegs based on his agenda.
				Actor_Says(kActorCrazylegs, 1050, kAnimationModeTalk); //09-1050.AUD	Look. Now I believe in laissez-faire.
				Actor_Says(kActorCrazylegs, 1060, kAnimationModeTalk);			
				Actor_Says(kActorMcCoy, 4370, 14);
				Actor_Says(kActorCrazylegs, 1070, kAnimationModeTalk);
				Actor_Says(kActorCrazylegs, 1080, kAnimationModeTalk);
				Actor_Clue_Acquire(kActorMcCoy, kClueCrazylegsInterview3, true, kActorCrazylegs);
			} else {
				Actor_Says(kActorMcCoy, 6985, 16); //00-4360.AUD	Got the straight scoop for me or what?
				Actor_Says(kActorCrazylegs, 1160, kAnimationModeTalk); //09-1160.AUD	Take a ride, McCoy. I already told you everything.
			}
		}
		break;

	case 190: // NOTE
		Actor_Says(kActorMcCoy, 4270, 18);
		Actor_Says(kActorMcCoy, 4260, kAnimationModeTalk);
		Actor_Says(kActorGrigorian, 360, 16);
		Actor_Says(kActorMcCoy, 4380, 19);
		Actor_Says(kActorMcCoy, 4385, 19);
		Actor_Says(kActorGrigorian, 370, 13);
		Actor_Says(kActorMcCoy, 4390, 19);
#if !BLADERUNNER_ORIGINAL_BUGS
		// McCoy needs to have the Registration Clues (1 or 3)
		// and probably have talked at least once with CrazyLegs (TODO?)
		// for this next quote to make sense
		// If arrested, Crazylegs will be right there, but he won't say anything relevant, so this won't make much sense.
		// So Crazylegs:
		// - should not be arrested yet
		// - nor talked to about (Grigorian's) Note already
		if ((!Game_Flag_Query(kFlagCrazylegsArrested))
		&& (Actor_Clue_Query(kActorMcCoy, kClueCarRegistration1)
		|| Actor_Clue_Query(kActorMcCoy, kClueCarRegistration3))
		) {
			Actor_Says(kActorMcCoy, 4395, 18);    // How was Crazylegs supposed to help them?
			Actor_Says(kActorGrigorian, 380, 14);
			if (_vm->_cutContent) {
				if (Player_Query_Agenda() == kPlayerAgendaSurly 
				|| Player_Query_Agenda() == kPlayerAgendaErratic) {
					//Added in some extra dialogue if McCoy is surly or erratic.
					Actor_Says(kActorMcCoy, 8519, 14); //00-8519.AUD	What do you say we dish each other the straight goods.
					Actor_Says(kActorGrigorian, 1200, 13); //11-1200.AUD	I think perhaps you should talk to my attorney, Mr. McCoy.
				}
				//Resored the clue Grigorians response 2.
				Actor_Clue_Acquire(kActorMcCoy, kClueGrigoriansResponse2, true, kActorGrigorian);
			}
		}
#else
		Actor_Says(kActorMcCoy, 4395, 18);    // How was Crazylegs supposed to help them?
		Actor_Says(kActorGrigorian, 380, 14);
		Actor_Says(kActorGrigorian, 390, 12); // boop placeholder
#endif // BLADERUNNER_ORIGINAL_BUGS
		Actor_Modify_Friendliness_To_Other(kActorGrigorian, kActorMcCoy, -5);
		break;

	case 200: // VOIGT-KAMPFF
		if (_vm->_cutContent) {
			Game_Flag_Set(kFlagPS09GrigorianVKChosen);
		}
		Actor_Says(kActorMcCoy, 4265, 14);
		Actor_Says(kActorGrigorian, 400, 13);
		//Altered code so McCoy is nice or mean to Grigorian when he VKS him depending on his agenda.
		if (_vm->_cutContent) {
		    if (Player_Query_Agenda() == kPlayerAgendaSurly 
			|| Player_Query_Agenda() == kPlayerAgendaErratic) {
				Actor_Says(kActorMcCoy, 4400, 13); //00-4400.AUD	Aha, look, I gotta check out the equipment and you're the only stiff around.
				Actor_Says_With_Pause(kActorGrigorian, 410, 0.0f, 16);
				Actor_Says(kActorMcCoy, 4405, 14); //00-4405.AUD	Your lawyer would tell you I got the authority to V-K the mayor, if I want.
				Actor_Says(kActorMcCoy, 4410, 15); //00-4410.AUD	And he'd have to smile and nod and kiss my butt until I cleared him. So sit down!
				Voight_Kampff_Activate(kActorGrigorian, 20);
				Actor_Modify_Friendliness_To_Other(kActorGrigorian, kActorMcCoy, -5);
				if (!Actor_Clue_Query(kActorMcCoy, kClueVKGrigorianReplicant)) {
					//Added in some lines when the test is finished.
					Actor_Says(kActorMcCoy, 6880, 14); //00-6880.AUD	The test says you're human.
					Actor_Says(kActorGrigorian, 20, 15); //11-0020.AUD	Please leave me alone. My migraine's acting up.
				}
				//Nice McCoy, the test starts immediately.
			} else {
				Actor_Says(kActorMcCoy, 400, 14); // 	00-0400.AUD	It won't take too long.
				Voight_Kampff_Activate(kActorGrigorian, 20);
				if (!Actor_Clue_Query(kActorMcCoy, kClueVKGrigorianReplicant)) {
					Actor_Says(kActorMcCoy, 6880, 14); //00-6880.AUD	The test says you're human.
					Actor_Modify_Friendliness_To_Other(kActorGrigorian, kActorMcCoy, -3);
				}
			}
		} else {
		
#if BLADERUNNER_ORIGINAL_BUGS
			Actor_Says(kActorGrigorian, 410, 16);
#else
			// Grigorian is interrupted here, so pause has to be 0.0f
			Actor_Says_With_Pause(kActorGrigorian, 410, 0.0f, 16);
#endif 		// BLADERUNNER_ORIGINAL_BUGS
			Actor_Says(kActorMcCoy, 4405, 14);
			Actor_Says(kActorMcCoy, 4410, 15);
			Voight_Kampff_Activate(kActorGrigorian, 20);
			Actor_Modify_Friendliness_To_Other(kActorGrigorian, kActorMcCoy, -10);
		}
		break;			

	case 210: // DONE
	if (_vm->_cutContent) {
		//Altered code so McCoy is nicer to Grigorian if he did not upset him.
		if (Actor_Query_Friendliness_To_Other(kActorGrigorian, kActorMcCoy) < 43) {
			Actor_Says(kActorMcCoy, 8600, 18);
			Actor_Says(kActorGrigorian, 20, 15);
		} else {
			Actor_Says(kActorGrigorian, 0, 15);	//11-0000.AUD	Are they letting me out?
			Actor_Says(kActorMcCoy, 8345, 18); //00-8345.AUD	I wouldn't know.
			}
		} else {
			Actor_Says(kActorMcCoy, 8600, 18);
			Actor_Says(kActorGrigorian, 20, 15);
		}
		break;
	}
}

} // End of namespace BladeRunner
