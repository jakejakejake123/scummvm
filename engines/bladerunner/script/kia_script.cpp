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

#include "bladerunner/script/kia_script.h"

#include "bladerunner/bladerunner.h"
#include "bladerunner/mouse.h"
#include "bladerunner/ui/kia.h"

namespace BladeRunner {

KIAScript::KIAScript(BladeRunnerEngine *vm) : ScriptBase(vm) {}

void KIAScript::playClueAssetScript(int notUsed, int clueId) {
	_vm->_kia->playerReset();
	_vm->_mouse->disable();
	SCRIPT_KIA_DLL_Play_Clue_Asset_Script(notUsed, clueId);
	_vm->_mouse->enable();
}

void KIAScript::SCRIPT_KIA_DLL_Play_Clue_Asset_Script(int notUsed, int clueId) {
	switch (clueId) {
	case kClueOfficersStatement:
		KIA_Play_Actor_Dialogue(kActorOfficerLeary, 40);
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorOfficerLeary, 50); //23-0050.AUD	The shop's been thrashed. You ought to see this tiger cub they got in there.
			KIA_Play_Actor_Dialogue(kActorOfficerLeary, 60); //23-0060.AUD	It's a goddamn tragedy.
		}
		break;
	case kClueDoorForced2:
		// Made it so the door forced 2 contains the entire dialogue for both door force clues. It makes no sense for the player to check the door later to inspect the broken lock because
		// because after you investigate the place and the police are gone from act 2 onwards the door is LOCKED, meaning the lock has been replaced. It wouldn't make much sense for McCoy to inspect a LOCKED door only to say that the lock had been forced
		// So I reappropriated door force 1 to play the unused dialogue where McCoy comments on Sebastians door being forced instead. I mean the reps broke into his place after all and he knows about it,
		// So it must be because he saw that the lock was broken 
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 1870); //99-1870.AUD	Whoever did it showed some serious strength. They busted the lock clean off.
		} else {
			KIA_Play_Actor_Dialogue(kActorOfficerLeary, 0); //23-0000.AUD	I already checked for a crowbar or some kind of tool. No luck but it looks like we've got some latents.
		}
		break;
	case kClueDoorForced1:
		if (_vm->_gameVars[kVariableChapter] == 1) {
			// keep in mind, this line in only available in Act 1 (1.TLK) unless _vm->_cutContent is selected (provided that cut content now loads all TLKs)
			// Without cut content it will be silent in subsequent Acts
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 1870);
		}
		// Made it so the other door forced clue is acquired when you enter Sebastians place which now has the door forced dialogue play just before you enter.
		// This is the dialogoue that will be included in this clue.
		else if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 0); //99-0000.AUD	The lock had been forced.
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 10); //99-0010.AUD	Tyrell sub-cons might have been a little dingy...
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 20); //99-0020.AUD	But I didn't think they'd bust down their own doors, if they forgot their keys.
		}
		break;
	case kClueLimpingFootprints:
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 1970);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 1980);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 1990);
		break;
	case kClueGracefulFootprints:
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 1970);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 1980);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 1990);
		break;
	case kClueShellCasings:
		KIA_Play_Slice_Model(kModelAnimationShellCasings);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 1960);
		break;
	case kClueCandy:
		KIA_Play_Slice_Model(kModelAnimationCandy);
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 8735);//00-8735.AUD	A candy bar.
		}
		break;
	case kClueToyDog:
		KIA_Play_Slice_Model(kModelAnimationToyDog);
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 8740);//00-8740.AUD	A toy dog.
		}
		break;
	case kClueChopstickWrapper:
		KIA_Play_Slice_Model(kModelAnimationChopstickWrapper);
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 8745); //00-8745.AUD	A chopstick wrapper.
		} else {
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 2010);
		}
		break;
	case kClueSushiMenu:
		KIA_Play_Photograph(6);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 2020);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 2030);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 2040);
		break;
	case kClueLabCorpses:
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorKlein, 100); //30-0100.AUD	We got the animal corpses from Runciter's but there wasn't a whole lot to work with.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 4145); //00-4145.AUD	Bone marrow?
			KIA_Play_Actor_Dialogue(kActorKlein, 110); //30-0110.AUD	About 50% were real. The rest were fakes.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 4150); //00-4150.AUD	So, Runciter was ripping his customers off.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 4160); //00-4160.AUD	What about the wounds?
		}
		KIA_Play_Actor_Dialogue(kActorKlein, 140); //30-0140.AUD	Most of them were shot point-blank but we're looking at some others… pteh, sloppy cuts with a knife. Like the perp was really pissed off at something.
		// Similar fix to PS07:
		// quote 150 is *boop* in ENG version
		// it is redundant in DEU and FRA versions (identical to second half of quote 140)
		// it is required in ESP and ITA versions. It is the missing second half of quote 140.
		if (_vm->_cutContent
		    && (_vm->_language == Common::ES_ESP
		        || _vm->_language == Common::IT_ITA)
		) {
			KIA_Play_Actor_Dialogue(kActorKlein, 150);
		}
		break;
	case kClueLabShellCasings:
		KIA_Play_Actor_Dialogue(kActorKlein, 50); //30-0050.AUD	The shell casings from Runciter's should be in the Museum of military history.
		KIA_Play_Actor_Dialogue(kActorKlein, 60); //30-0060.AUD	They're from an Ender rifle. It's standard-issue Off-World military hardware.
		if (!_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorKlein, 70); //30-0070.AUD	Heavy caliber. That puppy can punch right through a tank.
		}
		KIA_Play_Actor_Dialogue(kActorKlein, 80); //30-0080.AUD	Whoever used this piece didn't just walk into their local sporting goods store and buy it.
		KIA_Play_Actor_Dialogue(kActorKlein, 90); //30-0090.AUD	Those babies are collectibles and they ain't cheap.
		break;
	case kClueRuncitersVideo:
		KIA_Play_Slice_Model(kModelAnimationVideoDisc);
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 4545); //00-4545.AUD	You got any discs from that camera?
			KIA_Play_Actor_Dialogue(kActorRunciter, 30); //15-0030.AUD	I believe this is the disc from last night.
		}
		break;
	case kClueLucy:
		KIA_Play_Photograph(5);
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 4040); //99-4040.AUD	Hello there Lucy.
		}
		break;
	case kClueDragonflyAnklet:
		KIA_Play_Photograph(4);
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 1600);//00-1600.AUD	Lucy?
		} else {
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 4050);
		}
		break;
	case kClueReferenceLetter:
		KIA_Play_Slice_Model(kModelAnimationReferenceLetter);
		KIA_Play_Actor_Dialogue(kActorRunciter, 280);
		KIA_Play_Actor_Dialogue(kActorRunciter, 290);
		break;
	case kClueCrowdInterviewA:
		if (_vm->_cutContent
		    && (_vm->_language == Common::ES_ESP
		        || _vm->_language == Common::IT_ITA)
		) {
			// Same fix as in RC01:
			// Quote 110 is the second half of the sentence about Lucy hanging around with Zuben ("a fat guy")
			// in ENG, DEU and FRA it is redundant, but it's needed in ESP and ITA
			KIA_Play_Actor_Dialogue(kActorOfficerLeary, 100);
			KIA_Play_Actor_Dialogue(kActorOfficerLeary, 110);
		} else {
			KIA_Play_Actor_Dialogue(kActorOfficerLeary, 100);
		}
		break;
	case kClueCrowdInterviewB:
		KIA_Play_Actor_Dialogue(kActorOfficerLeary, 120);
		KIA_Play_Actor_Dialogue(kActorOfficerLeary, 130);
		break;
	case kClueZubenInterview:
		KIA_Play_Actor_Dialogue(kActorMcCoy, 380);
		KIA_Play_Actor_Dialogue(kActorZuben, 30);
		KIA_Play_Actor_Dialogue(kActorZuben, 40);
		KIA_Play_Actor_Dialogue(kActorMcCoy, 410);
		KIA_Play_Actor_Dialogue(kActorZuben, 50);
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 415); //00-0415.AUD	North, huh?
		}
		break;
	case kClueZubenSquadPhoto:
		KIA_Play_Photograph(33);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 350);
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagZubenRetired)) {
				KIA_Play_Actor_Dialogue(kActorVoiceOver, 360); //99-0360.AUD	I'd retired a war hero.
				KIA_Play_Actor_Dialogue(kActorVoiceOver, 370); //99-0370.AUD	Someone who'd fought for the freedom of the Off-World colonists.
			}
		}
		break;
	case kClueBigManLimping:
		KIA_Play_Actor_Dialogue(kActorTransient, 10); //12-0010.AUD	Thanks. The big man. He kind of limping.
		KIA_Play_Actor_Dialogue(kActorTransient, 20); //12-0020.AUD	That way.
		break;
	case kClueRunciterInterviewA:
		KIA_Play_Actor_Dialogue(kActorRunciter, 40);
		KIA_Play_Actor_Dialogue(kActorRunciter, 50);
		if (!_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 4565);
			KIA_Play_Actor_Dialogue(kActorRunciter, 60); //15-0060.AUD	No, of course not! It was two men acting in concert with her, obviously.
		} else {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 4585); //00-4585.AUD	Tell me about this Lucy.
			KIA_Play_Actor_Dialogue(kActorRunciter, 270); //15-0270.AUD	She's about fourteen years old with pink hair. A very attractive young thing.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 4665); //00-4665.AUD	She got a desk or some place where she worked?
			KIA_Play_Actor_Dialogue(kActorRunciter, 350); //15-0350.AUD	She used to eat over there.
		}
		break;
	case kClueRunciterInterviewB1:
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 4760); //00-4760.AUD	About the girl.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 8514); //00-8514.AUD	Got anything new to tell me?
			KIA_Play_Actor_Dialogue(kActorRunciter, 250); //15-0250.AUD	There's not a lot I can tell you. She's only worked for me for about a month.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 4645); //00-4645.AUD	How did you find her? 
			if (!Game_Flag_Query(kFlagLucyIsReplicant)) {
				KIA_Play_Actor_Dialogue(kActorRunciter, 280); //15-0280.AUD	She came to me with a reference from Ogilvies in the North West Zone.
				KIA_Play_Actor_Dialogue(kActorRunciter, 290); //15-0290.AUD	And he's a very reputable wholesaler.
			} else {
				KIA_Play_Actor_Dialogue(kActorRunciter, 1180); //15-1180.AUD	I…
				KIA_Play_Actor_Dialogue(kActorRunciter, 1190); //15-1190.AUD	I'm not answering that.
			}
			KIA_Play_Actor_Dialogue(kActorRunciter, 4650); //00-4650.AUD	You treat her well? 
			KIA_Play_Actor_Dialogue(kActorRunciter, 320); //15-0320.AUD	As well as any young tart should be treated.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 4655); //00-4655.AUD	What did she do around here? Feed the animals?
			if (Game_Flag_Query(kFlagRunciterIsReplicant)) {
				KIA_Play_Actor_Dialogue(kActorRunciter, 330); //15-0330.AUD	I'm the only one who handles my animals, detective.
				KIA_Play_Actor_Dialogue(kActorMcCoy, 4660); //00-4660.AUD	So what did she do?
				KIA_Play_Actor_Dialogue(kActorRunciter, 340); //15-0340.AUD	Unskilled labor, mostly. She was perfect for that. As if she were made for it.
			} else {
				KIA_Play_Actor_Dialogue(kActorRunciter, 1260); //15-1260.AUD	Sometimes.
			}
		} else {
			KIA_Play_Actor_Dialogue(kActorRunciter, 250); //15-0250.AUD	There's not a lot I can tell you. She's only worked for me for about a month.
			KIA_Play_Actor_Dialogue(kActorRunciter, 270); //15-0270.AUD	She's about fourteen years old with pink hair. A very attractive young thing.
		}
		break;
	case kClueRunciterInterviewB2:
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 4760); //00-4760.AUD	About the girl.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 8514); //00-8514.AUD	Got anything new to tell me?
			KIA_Play_Actor_Dialogue(kActorRunciter, 260); //15-0260.AUD	There's not a lot I can tell you. She's only worked for me for a short while.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 4645); //00-4645.AUD	How did you find her? 
			if (!Game_Flag_Query(kFlagLucyIsReplicant)) {
				KIA_Play_Actor_Dialogue(kActorRunciter, 280); //15-0280.AUD	She came to me with a reference from Ogilvies in the North West Zone.
				KIA_Play_Actor_Dialogue(kActorRunciter, 290); //15-0290.AUD	And he's a very reputable wholesaler.
			} else {
				KIA_Play_Actor_Dialogue(kActorRunciter, 1180); //15-1180.AUD	I…
				KIA_Play_Actor_Dialogue(kActorRunciter, 1190); //15-1190.AUD	I'm not answering that.
			}
			KIA_Play_Actor_Dialogue(kActorRunciter, 4650); //00-4650.AUD	You treat her well? 
			KIA_Play_Actor_Dialogue(kActorRunciter, 320); //15-0320.AUD	As well as any young tart should be treated.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 4655); //00-4655.AUD	What did she do around here? Feed the animals?
			if (Game_Flag_Query(kFlagRunciterIsReplicant)) {
				KIA_Play_Actor_Dialogue(kActorRunciter, 330); //15-0330.AUD	I'm the only one who handles my animals, detective.
				KIA_Play_Actor_Dialogue(kActorMcCoy, 4660); //00-4660.AUD	So what did she do?
				KIA_Play_Actor_Dialogue(kActorRunciter, 340); //15-0340.AUD	Unskilled labor, mostly. She was perfect for that. As if she were made for it.
			} else {
				KIA_Play_Actor_Dialogue(kActorRunciter, 1260); //15-1260.AUD	Sometimes.
			}
		} else {
			KIA_Play_Actor_Dialogue(kActorRunciter, 260); //15-0260.AUD	There's not a lot I can tell you. She's only worked for me for a short while.
			KIA_Play_Actor_Dialogue(kActorRunciter, 270); //15-0270.AUD	She's about fourteen years old with pink hair. A very attractive young thing.
		}
		break;
	case kClueHowieLeeInterview:
		KIA_Play_Actor_Dialogue(kActorMcCoy, 295);
		KIA_Play_Actor_Dialogue(kActorHowieLee, 90);
		KIA_Play_Actor_Dialogue(kActorHowieLee, 100);
		break;
	case kCluePaintTransfer:
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 1880);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 1890);
		break;
	case kClueChromeDebris:
		KIA_Play_Slice_Model(kModelAnimationChromeDebris);
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 8755); //00-8755.AUD	A piece of chrome.
		}
		break;
	case kClueRuncitersViewA:
		KIA_Play_Photograph(11);
		break;
	case kClueRuncitersViewB:
		KIA_Play_Photograph(12);
		break;
	case kClueCarColorAndMake:
		KIA_Play_Photograph(10);
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 4070); //99-4070.AUD	A black ground car. Looks like it's been around the block a few times.
		}
		break;
	case kCluePartialLicenseNumber:
		KIA_Play_Photograph(9);
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 4120); //99-4120.AUD	Local license plate. 
		}
		break;
	case kClueBriefcase:
		KIA_Play_Slice_Model(kModelAnimationBriefcase);
		KIA_Play_Actor_Dialogue(kActorMcCoy, 5870);
		KIA_Play_Actor_Dialogue(kActorGuzza, 810);
		if (!_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorGuzza, 820);
		}
		break;
	case kClueGaffsInformation:
		KIA_Play_Actor_Dialogue(kActorGaff, 20);
		KIA_Play_Actor_Dialogue(kActorMcCoy, 680);
		KIA_Play_Actor_Dialogue(kActorGaff, 30); //53-0030.AUD	Disappeared into thin air. Bryant thinks it crashed out in the Kipple.
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 685); //00-0685.AUD	How many Reps we're talking about?
			KIA_Play_Actor_Dialogue(kActorGaff, 40); //53-0040.AUD	Enough. They're Nexus-6s, so don't take too much slack.
		}
		break;
	case kClueLicensePlate:
		KIA_Play_Slice_Model(kModelAnimationLicensePlate);
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 8760); //00-8760.AUD	A license plate.
		}
		break;
	case kClueLabPaintTransfer:
		KIA_Play_Actor_Dialogue(kActorKlein, 170); //30-0170.AUD	That black paint you found on the fire hydrant is from a ground car.
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 4180); //00-4180.AUD	You sure?
		}
		KIA_Play_Actor_Dialogue(kActorKlein, 180); //30-0180.AUD	The angle of impact was almost head-on.
		KIA_Play_Actor_Dialogue(kActorKlein, 190);
		KIA_Play_Actor_Dialogue(kActorKlein, 200);
		break;
	case kClueDispatchHitAndRun:
		KIA_Play_Actor_Dialogue(kActorDispatcher, 90);
		KIA_Play_Actor_Dialogue(kActorDispatcher, 100);
		KIA_Play_Actor_Dialogue(kActorDispatcher, 110);
		KIA_Play_Actor_Dialogue(kActorDispatcher, 120);
		KIA_Play_Actor_Dialogue(kActorDispatcher, 130);
		KIA_Play_Actor_Dialogue(kActorDispatcher, 140);
		KIA_Play_Actor_Dialogue(kActorDispatcher, 150);
		break;
	case kCluePhoneCallGuzza:
		KIA_Play_Actor_Dialogue(kActorGuzza, 30); //04-0030.AUD	One of Tyrell's employees got his fat face splattered all over the marble interior of the Tyrell Building.
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 2695); //00-2695.AUD	Inside?
			KIA_Play_Actor_Dialogue(kActorGuzza, 40); //04-0040.AUD	That's right. But we also got a sweet little break at it.
		}
		KIA_Play_Actor_Dialogue(kActorGuzza, 50); //04-0050.AUD	Tyrell's surveillance system recorded the whole shebang.
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 2700); //00-2700.AUD	Beautiful! How many perps?
			KIA_Play_Actor_Dialogue(kActorGuzza, 60); //04-0060.AUD	Just one. I don't know if it's related to the Runciter deal or not.
		}
		KIA_Play_Actor_Dialogue(kActorGuzza, 70); //04-0070.AUD	Tyrell security will have the disk for you when you get there. You be good, killer.
		break;
	case kClueDragonflyEarring:
		KIA_Play_Slice_Model(kModelAnimationDragonflyEarring);
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 8765); //00-8765.AUD	An earring.
		} else {
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 2140);
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 2150);
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 2160);
		}
		break;
	case kClueTyrellSecurity:
		KIA_Play_Slice_Model(kModelAnimationVideoDisc);
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorTyrellGuard, 20); //17-0020.AUD	Ah-- here's the footage from the security cameras. You get a pretty good look at the man's face.
		}
		break;
	case kClueTyrellGuardInterview:
		KIA_Play_Actor_Dialogue(kActorMcCoy, 5140); //00-5140.AUD	How did he get past you guys?
		KIA_Play_Actor_Dialogue(kActorTyrellGuard, 30);
		KIA_Play_Actor_Dialogue(kActorTyrellGuard, 40);
		break;
	case kClueBombingSuspect:
		KIA_Play_Photograph(31);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 2140);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 2150);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 2160);
		break;
	case kClueDetonatorWire:
		KIA_Play_Slice_Model(kModelAnimationDetonatorWire);
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 8770); // 00-8770.AUD	A piece of detonator wire.
		} else {
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 2320); //99-2320.AUD	The detonator wire I pulled out of his skull told the whole story.
			if (Game_Flag_Query(kFlagSadikIsReplicant)) {
				KIA_Play_Actor_Dialogue(kActorVoiceOver, 2330);
				KIA_Play_Actor_Dialogue(kActorVoiceOver, 2340);
			}
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 2350);
		}
		break;
	case kClueVictimInformation:
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 5165); //00-5165.AUD	You friendly with Eisenduller?
		}
		KIA_Play_Actor_Dialogue(kActorTyrellGuard, 100); //17-0100.AUD	Most of the employees I see coming in morning and night, but old Marcus...
		KIA_Play_Actor_Dialogue(kActorTyrellGuard, 110); //17-0110.AUD	er, I mean Dr. Eisenduller, he almost never left his lab.
		KIA_Play_Actor_Dialogue(kActorTyrellGuard, 120); //17-0120.AUD	I think it had something to do with the air outside and the germs.
		KIA_Play_Actor_Dialogue(kActorTyrellGuard, 130); //17-0130.AUD	I once heard him complain about it.
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 5190); //00-5190.AUD	Smart. What was his job?
			KIA_Play_Actor_Dialogue(kActorTyrellGuard, 140); //17-0140.AUD	Grav Test Chief Engineer.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 8320); //	00-8320.AUD	Really?
			KIA_Play_Actor_Dialogue(kActorTyrellGuard, 430); ////17-0430.AUD	Here's what I heard just a little while ago.
			KIA_Play_Actor_Dialogue(kActorTyrellGuard, 150); //17-0150.AUD	The lab runs tests to see how a Replicant would perform in different planetary gravitational fields. That kind of thing.
			KIA_Play_Actor_Dialogue(kActorTyrellGuard, 170); //17-0170.AUD	One of the other engineers could tell you more.
		}
		break;
	case kClueAttemptedFileAccess:
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 2170);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 2180);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 2190);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 2200);
		break;
	case kClueCrystalsCase:
		if (!_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorSteele, 2230); //01-2230.AUD	(laughs) Oh, in a pig's ass, Slim. No, I'm following up on my own.
		}
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 5250); //00-5250.AUD	How's yours connected to mine?
		}
		KIA_Play_Actor_Dialogue(kActorSteele, 2260); //01-2260.AUD	You know the moonbus massacre that went down last month?
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 5265); //00-5265.AUD	Gaff mentioned something about it.
		}
		KIA_Play_Actor_Dialogue(kActorSteele, 2270); //01-2270.AUD	The rogue skin-jobs probably flew to earth.
		KIA_Play_Actor_Dialogue(kActorSteele, 2280); //01-2280.AUD	And one of them is a demolitions expert. Similar MO to your vic upstairs.
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 5270); //00-5270.AUD	Hell of a coincidence.
		}
		break;
	case kClueKingstonKitchenBox1:
		KIA_Play_Slice_Model(kModelAnimationKingstonKitchenBox);
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagHC04Visited)) {
				KIA_Play_Actor_Dialogue(kActorVoiceOver, 4140); //99-4140.AUD	Kingston Kitchens. That's down at Hawker's Circle.
			} else {
				KIA_Play_Actor_Dialogue(kActorVoiceOver, 4150); //99-4150.AUD	Kingston Kitchens. Where have I heard that before?
			}
		} else if (Query_Difficulty_Level() == kGameDifficultyEasy) {
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 4140);
		} else {
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 4150);
		}
		break;
	case kClueTyrellSalesPamphletEntertainModel:
		KIA_Play_Slice_Model(kModelAnimationTyrellSalesPamphletKIA);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 4280);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 4290);
		break;
	case kClueTyrellSalesPamphletLolita:
		KIA_Play_Slice_Model(kModelAnimationTyrellSalesPamphletKIA);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 4280);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 4300);
		break;
	case kCluePeruvianLadyInterview:
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorInsectDealer, 80); //16-0080.AUD	Ah, the Dragon.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 80); //00-0080.AUD	Dragon?
		}
		KIA_Play_Actor_Dialogue(kActorInsectDealer, 90); //16-0090.AUD	Sí, Anisoptera! Dragonfly late of the American South Swampland.
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 85); //00-0085.AUD	You sell jewelry with dragonflies?
		}
		KIA_Play_Actor_Dialogue(kActorInsectDealer, 100); //16-0100.AUD	Item like that very special significance.
		KIA_Play_Actor_Dialogue(kActorInsectDealer, 110); //16-0110.AUD	Very rare, señor. Estate item and most likely part of large collection.
		KIA_Play_Actor_Dialogue(kActorInsectDealer, 120); //16-0120.AUD	Person must have plentys money to obtain a collection.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 90); //00-0090.AUD	More than I can afford.
		KIA_Play_Actor_Dialogue(kActorInsectDealer, 130); //16-0130.AUD	You try Hawker's Circle. Might want to trade for this.
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorInsectDealer, 140); //16-0140.AUD	With luck, you may find.
		}
		break;
	case kClueHasanInterview:
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorHasan, 70); //20-0070.AUD	Certainly the LPD must have better things to do than to question a humble merchant over and over again about the same things.
		}
		KIA_Play_Actor_Dialogue(kActorHasan, 90); //20-0090.AUD	Why aren't you out arresting criminals like that disreputable Bob fellow.		
		KIA_Play_Actor_Dialogue(kActorHasan, 100); //20-0100.AUD	He owns the armament shop up the street. He is insane, noble one. Insane.
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorHasan, 110); //20-0110.AUD	He takes peculiar pleasure in agitating all the vendors around here.
			KIA_Play_Actor_Dialogue(kActorHasan, 120); //20-0120.AUD	I cannot even go out for a Shish-Taouk without worrying whether Bob is going to sabotage my snakes.
		}
		break;
	case kClueBobInterview1:
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 4995); //00-4995.AUD	Somebody shot up Runciter's shop with one.
			KIA_Play_Actor_Dialogue(kActorBulletBob, 1860); //14-1860.AUD	Runciter? You mean that animal dealer down the street?
			KIA_Play_Actor_Dialogue(kActorMcCoy, 8535);	//00-8535.AUD	Yeah.
			if (Game_Flag_Query(kFlagBulletBobIsReplicant)) {
				KIA_Play_Actor_Dialogue(kActorBulletBob, 270); //14-0270.AUD	Sucker had it coming. I'm sure of that.
				KIA_Play_Actor_Dialogue(kActorMcCoy, 5005); //00-5005.AUD	Why is that?
				KIA_Play_Actor_Dialogue(kActorBulletBob, 280); //14-0280.AUD	Runciter is always putting on those airs like he's better than everybody else.
				KIA_Play_Actor_Dialogue(kActorBulletBob, 290); //14-0290.AUD	But he'll do anything for a buck. Sell anything to anybody.
				KIA_Play_Actor_Dialogue(kActorBulletBob, 300); //14-0300.AUD	That's where I draw the line. If it's suspicious
				KIA_Play_Actor_Dialogue(kActorBulletBob, 310); //14-0310.AUD	it's out of here. Got no place at Bullet Bob's.
			} else {
				KIA_Play_Actor_Dialogue(kActorBulletBob, 1700); //14-1700.AUD	Damn. You know I'm getting to be an old man and I ain't gonna...
				KIA_Play_Actor_Dialogue(kActorMcCoy, 3730); // 00-3730.AUD	Animal murder is pretty horrible.
				KIA_Play_Actor_Dialogue(kActorBulletBob, 1550); //14-1550.AUD	I'd kick the crap out of that sicko.
				KIA_Play_Actor_Dialogue(kActorBulletBob, 1340); //14-1340.AUD	You know what I mean?
			}
			KIA_Play_Actor_Dialogue(kActorMcCoy, 5010); //00-5010.AUD	You know anyone who might sell Ender rifles?
		}
		KIA_Play_Actor_Dialogue(kActorBulletBob, 320); //14-0320.AUD	There's one other guy around here who dips into that stuff.
		KIA_Play_Actor_Dialogue(kActorBulletBob, 330); //14-0330.AUD	Got a pawn shop down the street. Goes by the name of Izo.
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorBulletBob, 340); //14-0340.AUD	But who knows what the real title is.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 5015); //00-5015.AUD	Izo, huh. Sounds like you don't like him.
			if (!Game_Flag_Query(kFlagBulletBobIsReplicant)) {
				KIA_Play_Actor_Dialogue(kActorBulletBob, 350); //14-0350.AUD	I've been around here a long time, Ray.
				KIA_Play_Actor_Dialogue(kActorBulletBob, 360); 
				KIA_Play_Actor_Dialogue(kActorBulletBob, 370);
				KIA_Play_Actor_Dialogue(kActorMcCoy, 5020); //00-5020.AUD	How long has Izo been around?
				KIA_Play_Actor_Dialogue(kActorBulletBob, 390); //14-0390.AUD	I went over to introduce myself when he first moved in and he practically ignored me!
				KIA_Play_Actor_Dialogue(kActorMcCoy, 7805); //00-7805.AUD	Answer the question.	
				KIA_Play_Actor_Dialogue(kActorBulletBob, 400); //14-0400.AUD	Said he was too busy to talk. Don't think I didn't consider kicking his ass, too.
				KIA_Play_Actor_Dialogue(kActorMcCoy, 5080); //00-5080.AUD	Just answer the question.
				KIA_Play_Actor_Dialogue(kActorBulletBob, 380); //14-0380.AUD	He's brand-new. He's a cold son of a bitch, too.
			} else {
				KIA_Play_Actor_Dialogue(kActorBulletBob, 410); //14-0410.AUD	Izo is okay. He's run the Green Pawn for a while.
				KIA_Play_Actor_Dialogue(kActorBulletBob, 420); //14-0420.AUD	We're friendly competitors, I guess. But I don't appreciate his politics.
				KIA_Play_Actor_Dialogue(kActorMcCoy, 5025); //00-5025.AUD	Yeah?
				KIA_Play_Actor_Dialogue(kActorBulletBob, 430); //14-0430.AUD	Rumors that's all they are.
			}
		} else {
			KIA_Play_Actor_Dialogue(kActorBulletBob, 350); //14-0350.AUD	I've been around here a long time, Ray.
			KIA_Play_Actor_Dialogue(kActorBulletBob, 360); 
			KIA_Play_Actor_Dialogue(kActorBulletBob, 370);
			KIA_Play_Actor_Dialogue(kActorMcCoy, 5020);	
			KIA_Play_Actor_Dialogue(kActorBulletBob, 380);
			KIA_Play_Actor_Dialogue(kActorBulletBob, 390);
			KIA_Play_Actor_Dialogue(kActorBulletBob, 400);
			KIA_Play_Actor_Dialogue(kActorBulletBob, 630);
			KIA_Play_Actor_Dialogue(kActorMcCoy, 5050);	
			KIA_Play_Actor_Dialogue(kActorBulletBob, 440);
			KIA_Play_Actor_Dialogue(kActorBulletBob, 450);
		}
		break;
	case kClueBobInterview2:
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorBulletBob, 1940); //14-1940.AUD	The department's been infiltrated, right?
			KIA_Play_Actor_Dialogue(kActorBulletBob, 1950); //14-1950.AUD	That's the only way Davy could have been taken out like he was.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 8970); //00-8970.AUD	Holden is good. No question.
		} else {
			KIA_Play_Actor_Dialogue(kActorBulletBob, 320); //14-0320.AUD	There's one other guy around here who dips into that stuff.
			KIA_Play_Actor_Dialogue(kActorBulletBob, 330); //14-0330.AUD	Got a pawn shop down the street. Goes by the name of Izo.
			KIA_Play_Actor_Dialogue(kActorBulletBob, 410); //14-0410.AUD	Izo is okay. He's run the Green Pawn for a while.
			KIA_Play_Actor_Dialogue(kActorBulletBob, 420); //14-0420.AUD	We're friendly competitors, I guess. But I don't appreciate his politics.
		}
		break;
	case kClueIzoInterview:
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 1070); //00-1070.AUD	Ever see this piece? Real elite stuff.
			KIA_Play_Actor_Dialogue(kActorIzo, 200); //07-0200.AUD	If it truly belongs to the elite, it won't show up around here.
		}
		KIA_Play_Actor_Dialogue(kActorIzo, 210); //07-0210.AUD	That's a white market item.
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 1115); //00-1115.AUD	What do you mean “white market”?
		}
		KIA_Play_Actor_Dialogue(kActorIzo, 220); //07-0220.AUD	When something is so valuable, it's sold so fast that it's never even seen on the street.
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorIzo, 230); //07-0230.AUD	That's the white market.
		}
		KIA_Play_Actor_Dialogue(kActorIzo, 240); //07-0240.AUD	If this piece is real, it could only belong to the wife of a very rich man.
		break;
	case kClueIzosWarning:
		KIA_Play_Actor_Dialogue(kActorIzo, 750); //07-0750.AUD	Clovis is looking for you, McCoy.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 6755); //00-6755.AUD	He wants to talk to me?!
		KIA_Play_Actor_Dialogue(kActorIzo, 910); //07-0910.AUD	He would have made that clear.
		if (Game_Flag_Query(kFlagZubenRetired)) {
			KIA_Play_Actor_Dialogue(kActorIzo, 760); //07-0760.AUD	He knows all about you. Knows what happened with Zuben.
		}
		if (!Actor_Clue_Query(kActorMcCoy, kClueAmateurBomber)) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 5500); //00-5500.AUD	Is Clovis the Tyrell bomber?
			KIA_Play_Actor_Dialogue(kActorIzo, 770); //07-0770.AUD	You really are groping in the dark.
			KIA_Play_Actor_Dialogue(kActorIzo, 780); //07-0780.AUD	No. The bomb belonged to Sadik. It was his signature.
		}
		break;
	case kClueRadiationGoggles:
		KIA_Play_Slice_Model(kModelAnimationRadiationGoggles);
		KIA_Play_Actor_Dialogue(kActorMcCoy, 8785); //00-8785.AUD	Radiation goggles.
		break;
	case kClueGogglesReplicantIssue:
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 4970); //00-4970.AUD	You ever seen anything like these?
		}
		KIA_Play_Actor_Dialogue(kActorBulletBob, 560); //14-0560.AUD	Those are real beauties. Radiation goggles from the Off-World Wars. The 2017 model.
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 5045); //00-5045.AUD	Would a Replicant need something like this?
		}
		KIA_Play_Actor_Dialogue(kActorBulletBob, 570); //14-0570.AUD	Hell, the skin-jobs were the only ones who wore 'em.
		KIA_Play_Actor_Dialogue(kActorBulletBob, 580); //14-0580.AUD	The humans weren't allowed to get that close to the flash point. 
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 8190);	// 00-8190.AUD	Why?
			KIA_Play_Actor_Dialogue(kActorBulletBob, 1800); //14-1800.AUD	You're gonna love this, McCoy. I couldn't believe it when I heard.
			KIA_Play_Actor_Dialogue(kActorBulletBob, 590); //14-0590.AUD	U.N. Command figured it out, because the Rep skin held up...
			KIA_Play_Actor_Dialogue(kActorBulletBob, 600); //14-0600.AUD	but their eyes melted inside two kilometers from Ground Zero.
		}
		break;
	case kClueFishLadyInterview:
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 40); //00-0040.AUD	Is this scale from a fish?
		}
		KIA_Play_Actor_Dialogue(kActorFishDealer, 120); //29-0120.AUD	Same as other one. Not fish. Snake scale.
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 45); //00-0045.AUD	What other one?
		}
		KIA_Play_Actor_Dialogue(kActorFishDealer, 130); //29-0130.AUD	Other police show me scale from same snake.
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorFishDealer, 140); //29-0140.AUD	I sent him to Abdul Hasan.
		}
		break;
	case kClueDogCollar1:
		KIA_Play_Slice_Model(kModelAnimationDogCollar);
		if (!_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 4160);
		} else {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 8790); //00-8790.AUD	A dog collar.
		}
		break;
	case kClueWeaponsCache:
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 2430);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 2440);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 2450); //99-2450.AUD	Izo wasn't some small-time fence but a big-time arms dealer.
		break;
	case kClueChewInterview:
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 770); //00-0770.AUD	You were close to Eisenduller?
			KIA_Play_Actor_Dialogue(kActorChew, 110); //52-0110.AUD	Eisenduller? Ha, ha, no, no. No time for him. No go to lab.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 835); //00-0835.AUD	Marcus is dead.
			KIA_Play_Actor_Dialogue(kActorChew, 130); //52-0130.AUD	Chew work hard all night, all day. No stop, no break. No OT (paid overtime).
		}
		if (!_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorChew, 140); //52-0140.AUD	Of course I hear you! You-- you think I'm deaf? (mumbles) Hmph, your time more important, man?
		}
		KIA_Play_Actor_Dialogue(kActorChew, 150); //52-0150.AUD	Eisenduller dead. Moraji maybe dead. You out chasing skirts?
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 845);  //00-0845.AUD	Moraji?
		}
		KIA_Play_Actor_Dialogue(kActorChew, 170); //52-0170.AUD	Chew eat supper with Moraji every night, no fail. Sometimes Chinese, sometimes Indian, sometimes home cook.
		KIA_Play_Actor_Dialogue(kActorChew, 180); //52-0180.AUD	Sometimes we go up and eat with twins.
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 870); //00-0870.AUD	What does he work on?
			KIA_Play_Actor_Dialogue(kActorChew, 290); //52-0290.AUD	Skin. Did skin for Nexus-6. Beautiful work. You go see.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 875); //00-0875.AUD	Where do I find him?
			KIA_Play_Actor_Dialogue(kActorChew, 300); //52-0300.AUD	He at “Dermo Design” across street. You find him, you tell him I wait.
		}
		if (!_vm->_cutContent) {	
			KIA_Play_Actor_Dialogue(kActorChew, 190); //52-0190.AUD	I call. I knock. Ten minutes ago. Door locked, no answer.
		}
		break;
	case kClueMorajiInterview:
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMoraji, 0); //35-0000.AUD	You must warn the twins.
			KIA_Play_Actor_Dialogue(kActorMoraji, 10); //35-0010.AUD	Up-- Up there. Up... the stairs.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 950); //00-0950.AUD	The twins? Did they do this?
		}
		KIA_Play_Actor_Dialogue(kActorMoraji, 20); //35-0020.AUD	No. Tall man with dreadlocks, the bomber.
		KIA_Play_Actor_Dialogue(kActorMoraji, 30); //35-0030.AUD	And another with beard. Piercing eyes.
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 955); //00-0955.AUD	What did they want?
		}
		KIA_Play_Actor_Dialogue(kActorMoraji, 40); //35-0040.AUD	D-- DNA information. Gah-- God, forgive me! I told them.
		KIA_Play_Actor_Dialogue(kActorMoraji, 50); //35-0050.AUD	Told them about the twins.
		break;
	case kClueGordoInterview1:
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 6485); //00-6485.AUD	You know anything about that bomb that just rocked the street?
			if (Game_Flag_Query(kFlagGordoIsReplicant)) {
				KIA_Play_Actor_Dialogue(kActorGordo, 1010); //02-1010.AUD	Bombing? I've never bombed in my life. My act is always happening. Always now.
				KIA_Play_Actor_Dialogue(kActorMcCoy, 6500);
				KIA_Play_Actor_Dialogue(kActorGordo, 1030);
			} else {
				KIA_Play_Actor_Dialogue(kActorGordo, 1040); //02-1040.AUD	Bombing? I had a cousin who bombed at Tyrell's niece's wedding.
				KIA_Play_Actor_Dialogue(kActorGordo, 1050);
				KIA_Play_Actor_Dialogue(kActorMcCoy, 6505);
				KIA_Play_Actor_Dialogue(kActorGordo, 1060);
				KIA_Play_Actor_Dialogue(kActorGordo, 1070);
			}
		} else {
			KIA_Play_Actor_Dialogue(kActorGordo, 1010); //02-1010.AUD	Bombing? I've never bombed in my life. My act is always happening. Always now.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 6495);
			KIA_Play_Actor_Dialogue(kActorGordo, 1020);
			KIA_Play_Actor_Dialogue(kActorMcCoy, 6500);
			KIA_Play_Actor_Dialogue(kActorGordo, 1030);
		}
		break;
	case kClueGordoInterview2:
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorGordo, 6600); //00-6600.AUD	Why the big deal over food?
			KIA_Play_Actor_Dialogue(kActorGordo, 1310); //02-1310.AUD	It was just some cheese, McCoy. And some takeout cartons.
			if (Actor_Clue_Query(kActorMcCoy, kClueKingstonKitchenBox1)
			|| Actor_Clue_Query(kActorMcCoy, kClueKingstonKitchenBox2)) {
				KIA_Play_Actor_Dialogue(kActorMcCoy, 6595); ///00-6595.AUD	And you gave the takeout cartons to Sadik.
			}
			KIA_Play_Actor_Dialogue(kActorMcCoy, 6555); //00-6555.AUD	Let’s hear the rest of it.
			if (Game_Flag_Query(kFlagLucyIsReplicant)) {
				KIA_Play_Actor_Dialogue(kActorGordo, 1330); //02-1330.AUD	Anything good is damn hard to come by. Poor Lucy wasn’t doing so hot.
				KIA_Play_Actor_Dialogue(kActorGordo, 1340); //02-1340.AUD	She couldn’t keep anything down.
				KIA_Play_Actor_Dialogue(kActorGordo, 1350); //02-1350.AUD	So, I thought… maybe something different to eat would help.
			} else {
				KIA_Play_Actor_Dialogue(kActorGordo, 1360); //02-1360.AUD	Clovis… well, he’s been getting sick. He can’t keep anything down.
				KIA_Play_Actor_Dialogue(kActorGordo, 1370); //02-1370.AUD	I thought… maybe something a little different to eat.
			}
		} else {
			KIA_Play_Actor_Dialogue(kActorGordo, 1040); //02-1040.AUD	Bombing? I had a cousin who bombed at Tyrell's niece's wedding.
			KIA_Play_Actor_Dialogue(kActorGordo, 1050);
			KIA_Play_Actor_Dialogue(kActorMcCoy, 6505);
			KIA_Play_Actor_Dialogue(kActorGordo, 1060);
			KIA_Play_Actor_Dialogue(kActorGordo, 1070);
			KIA_Play_Actor_Dialogue(kActorMcCoy, 6510);
			KIA_Play_Actor_Dialogue(kActorGordo, 1080);
		}
		break;
	case kClueAnsweringMachineMessage:
		KIA_Play_Actor_Dialogue(kActorSebastian, 0);
		KIA_Play_Actor_Dialogue(kActorSebastian, 10);
		KIA_Play_Actor_Dialogue(kActorSebastian, 20);
		KIA_Play_Actor_Dialogue(kActorSebastian, 30);
		KIA_Play_Actor_Dialogue(kActorSebastian, 40);
		KIA_Play_Actor_Dialogue(kActorSebastian, 50);
		break;
	case kClueChessTable:
		if (!_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 80);
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 90);
		} else {
			KIA_Play_Actor_Dialogue(kActorSebastian, 390); //56-0390.AUD	Dr. Tyrell and I play chess every week. I've only beaten him once.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 7140);
			KIA_Play_Actor_Dialogue(kActorSebastian, 400);
			KIA_Play_Actor_Dialogue(kActorMcCoy, 7145);
			KIA_Play_Actor_Dialogue(kActorSebastian, 410);
			KIA_Play_Actor_Dialogue(kActorMcCoy, 7150);
			KIA_Play_Actor_Dialogue(kActorSebastian, 420);
			KIA_Play_Actor_Dialogue(kActorSebastian, 430);
		}
		break;
	case kClueStaggeredbyPunches:
		if (!_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 4370);
		} else {
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 3560); //99-3560.AUD	Ugh. This was all too familiar territory. Jackhammers were drilling through my brain and my stomach felt like it had been bathed in battery acid.
		}
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 4380);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 4390);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 4400);
		break;
	case kClueMaggieBracelet:
		KIA_Play_Slice_Model(kModelAnimationMaggieBracelet);
		if (_vm->_cutContent) {
			if (!Player_Query_Agenda() == kPlayerAgendaPolite) { 
				KIA_Play_Actor_Dialogue(kActorVoiceOver, 4030);
			} else {
				KIA_Play_Actor_Dialogue(kActorMcCoy, 8795); //00-8795.AUD	A bracelet.
			}
		}
		break;
	case kClueEnvelope:
		KIA_Play_Slice_Model(kModelAnimationEnvelope);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 850);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 860);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 870);
		if (!_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 880);
		}
		break;
	case kClueIzosFriend:
		KIA_Play_Photograph(25);
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 4080); //99-4080.AUD	He looks familiar.
		}
		break;
	case kClueChinaBarSecurityPhoto:
		KIA_Play_Photograph(20);
		break;
	case kCluePurchasedScorpions:
		KIA_Play_Actor_Dialogue(kActorMcCoy, 220);
		KIA_Play_Actor_Dialogue(kActorInsectDealer, 320);
		KIA_Play_Actor_Dialogue(kActorMcCoy, 225);
		KIA_Play_Actor_Dialogue(kActorInsectDealer, 330);
		KIA_Play_Actor_Dialogue(kActorMcCoy, 230);
		KIA_Play_Actor_Dialogue(kActorInsectDealer, 340); //16-0340.AUD	What people like to do with them I do not ask.
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorInsectDealer, 350); //16-0350.AUD	It's much better to mind my own business.
		}
		break;
	case kClueWeaponsOrderForm:
		KIA_Play_Slice_Model(kModelAnimationWeaponsOrderForm);
		break;
	case kClueShippingForm:
		if (_vm->_cutContent) {
			KIA_Play_Slice_Model(kModelAnimationOriginalShippingForm);
		} else {
			KIA_Play_Slice_Model(kModelAnimationWeaponsOrderForm);
		}
		break;
	case kClueGuzzasCash:
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 4000); //00-4000.AUD	Can the department float me some chinyen? This investigation's getting expensive.
		}
		KIA_Play_Actor_Dialogue(kActorGuzza, 520); //04-0520.AUD	Look, this ain't on the department tab, okay? This is a personal loan.
		KIA_Play_Actor_Dialogue(kActorGuzza, 530); //04-0530.AUD	This goddamn city doesn't know how to manage funds. They've been flush for years.
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 4060); //00-4060.AUD	I thought we were under budget.
		}
		KIA_Play_Actor_Dialogue(kActorGuzza, 540); //04-0540.AUD	Trust me. Ain't nobody getting rich unless they're sneaking some on the side.
		KIA_Play_Actor_Dialogue(kActorGuzza, 550); //04-0550.AUD	Hell, I can barely pay for the fuel for my car.
		break;
	case kClueHysteriaToken:
		KIA_Play_Slice_Model(kModelAnimationHysteriaToken);
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 420); // 99-0420.AUD	Hysteria Hall was an arcade. Down near Nightclub Row.
		}
		break;
	case kClueRagDoll:
		KIA_Play_Slice_Model(kModelAnimationRagDoll);
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 8815); //00-8815.AUD	A creepy looking doll.
		}
		break;
	case kClueMoonbus1:
		KIA_Play_Photograph(34);
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 8527); // 00-8527.AUD	Strange.
		}
		break;
	case kClueCheese:
		KIA_Play_Slice_Model(kModelAnimationCheese);
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 480); //99-0480.AUD	It felt and smelled like real cheese.
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 490); //99-0490.AUD	Dairy products were choice contraband. Scarce and mucho expensive.
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 500); //99-0500.AUD	Selling them was a Class A felony.
		}
		break;
	case kClueDektorasDressingRoom:
		KIA_Play_Photograph(16);
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 4100); //99-4100.AUD	They look familiar.
		}
		break;
	case kClueEarlyQsClub:
		KIA_Play_Slice_Model(kModelAnimationVideoDisc);
		if (_vm->_cutContent) {
			if (Actor_Clue_Query(kActorMcCoy, kClueEarlyQAndLucy)) {
				KIA_Play_Actor_Dialogue(kActorVoiceOver, 4260); //99-4260.AUD	Early, you sick bastard.
			} else {
				KIA_Play_Actor_Dialogue(kActorVoiceOver, 1620); //99-1620.AUD	I didn’t know what was on the disc…
				KIA_Play_Actor_Dialogue(kActorVoiceOver, 1630); //99-1630.AUD	but the way Early had hidden it, it was bound to be dirty laundry.
			}
		}
		break;
	case kClueDragonflyCollection:
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 205); //00-0205.AUD	Any luck finding more of that dragonfly jewelry?
		}
		KIA_Play_Actor_Dialogue(kActorInsectDealer, 290); //16-0290.AUD	Ah! Sí, sí, I was right. Piece you show me was part of a collection.
		KIA_Play_Actor_Dialogue(kActorInsectDealer, 300); //16-0300.AUD	Bought for nightclub in Fourth Sector.
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 210); //00-0210.AUD	You know the name of the nightclub owner?
			KIA_Play_Actor_Dialogue(kActorInsectDealer, 310); //16-0310.AUD	No, señor. But my friend, he says the man is not selling.
		}
		break;
	case kClueDragonflyBelt:
		KIA_Play_Slice_Model(kModelAnimationDragonflyBelt);
		KIA_Play_Actor_Dialogue(kActorMcCoy, 8825); // 00-8825.AUD	A dragonfly belt.
		break;
	case kClueEarlyQInterview:
		KIA_Play_Actor_Dialogue(kActorEarlyQ, 140);
		if (!_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorEarlyQ, 150);
		}
		break;
	case kClueStrangeScale1:
		KIA_Play_Slice_Model(kModelAnimationStrangeScale);
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 8830); //00-8830.AUD	A strange scale.
		}
		break;
	case kClueDektoraInterview1:
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 3660); //00-3660.AUD	There’s a little test I’d like you to take.
		}
		KIA_Play_Actor_Dialogue(kActorDektora, 650); //03-0650.AUD	Do you think I’m a Replicant? Is that what this is about?
		if (_vm->_cutContent) {
			if (!Game_Flag_Query(kFlagEarlyQIsReplicant)) {
				KIA_Play_Actor_Dialogue(kActorDektora, 660); //03-0660.AUD	If it’s Early Q, I’ll help you any way you want.
				KIA_Play_Actor_Dialogue(kActorMcCoy, 3665); //00-3665.AUD	Not exactly.
			}
		} else {
			KIA_Play_Actor_Dialogue(kActorDektora, 660); //03-0660.AUD	If it’s Early Q, I’ll help you any way you want.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 3665); //00-3665.AUD	Not exactly.
		}
		if (!_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorDektora, 670); //03-0670.AUD	This is insane. I have a family, a daughter for heaven’s sake.
		}
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagEarlyQIsReplicant)) {
				KIA_Play_Actor_Dialogue(kActorMcCoy, 8325); //00-8325.AUD	It's just a test.
				KIA_Play_Actor_Dialogue(kActorMcCoy, 400); //00-0400.AUD	It won't take too long.
			} else {
				KIA_Play_Actor_Dialogue(kActorDektora, 680); //03-0680.AUD	Look, I’m willing to testify against Early Q.
				if (Actor_Query_Intelligence(kActorDektora) == 90) {
					KIA_Play_Actor_Dialogue(kActorDektora, 690); //03-0690.AUD	A Replicant wouldn’t do that, would it?
				}
			}
		} else {
			KIA_Play_Actor_Dialogue(kActorDektora, 680); //03-0680.AUD	Look, I’m willing to testify against Early Q.
			KIA_Play_Actor_Dialogue(kActorDektora, 690); //03-0690.AUD	A Replicant wouldn’t do that, would it?
		}
		break;
	case kClueDektoraInterview2:
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 3625); //00-3625.AUD	That’s such an unusual belt. Is it antique?
			KIA_Play_Actor_Dialogue(kActorDektora, 570); //03-0570.AUD	They say it’s from the last century.
		}
		KIA_Play_Actor_Dialogue(kActorDektora, 580); //03-0580.AUD	Those little creatures have always been my favorites.
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 3630); //00-3630.AUD	Dragonflies?
			KIA_Play_Actor_Dialogue(kActorDektora, 590); //03-0590.AUD	Yes.
			KIA_Play_Actor_Dialogue(kActorDektora, 600); //03-0600.AUD	And the whole class that contains them.
		}
		break;
	case kClueDektoraInterview3:
		KIA_Play_Actor_Dialogue(kActorMcCoy, 3600); //00-3600.AUD	The flowers are beautiful.
		KIA_Play_Actor_Dialogue(kActorDektora, 550); //03-0550.AUD	And extremely rare. They were a gift from my lover.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 3605); 
		KIA_Play_Actor_Dialogue(kActorDektora, 590); //03-0590.AUD	Yes.
		break;
	case kClueDektorasCard:
		KIA_Play_Slice_Model(kModelAnimationDektorasCard);
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 1690); //99-1690.AUD	“Never seek to tell thy love, love that never told can be.”
		}
		break;
	case kClueCrazysInvolvement:
		// RESTORED CONTENT
		KIA_Play_Slice_Model(kModelAnimationLetter);
		break;
	case kClueGrigoriansNote:
		KIA_Play_Slice_Model(kModelAnimationGrigoriansNote);
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 8840); //00-8840.AUD	A note.
		}
		break;
	case kClueCollectionReceipt:
		KIA_Play_Slice_Model(kModelAnimationCollectionReceipt);
		if (_vm->_cutContent) {
			if (!Game_Flag_Query(kFlagEarlyQIsReplicant)) {
				KIA_Play_Actor_Dialogue(kActorVoiceOver, 1560);
			}
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 1570); //99-1570.AUD	There were three pieces. A belt, earrings and an anklet.
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 1580); //99-1580.AUD	Early had bought them last month at an auction…
		}
		break;
	case kClueSpecialIngredient:
		KIA_Play_Actor_Dialogue(kActorMurray, 210);
		KIA_Play_Actor_Dialogue(kActorMurray, 220);
		KIA_Play_Actor_Dialogue(kActorMia, 140);
		KIA_Play_Actor_Dialogue(kActorMurray, 230);
		break;
	case kClueStolenCheese:
		KIA_Play_Actor_Dialogue(kActorIsabella, 210); //59-0210.AUD	You know, funny thing you asking about the cheese. Last week this ugly little man, he ran by. Grab whole box of empty takeout cartons right off the counter.
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorIsabella, 240); //59-0240.AUD	Police next door they just laugh. Say the guy not be so happy when he opens them cartons. (scoffs)
			KIA_Play_Actor_Dialogue(kActorMcCoy, 1385); //00-1385.AUD	What's that have to do with the cheese?
		}
		KIA_Play_Actor_Dialogue(kActorIsabella, 260); //59-0260.AUD	Cheese hidden in that box, mon. Keeping it safe till I cook up a new batch. So how can I tell police to bring back box. They find cheese, they shut me down.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 1390); //00-1390.AUD	This guy who robbed you. What did he look like?
		KIA_Play_Actor_Dialogue(kActorIsabella, 300); //59-0300.AUD	Short, real short. Bad clothes, colors way too bright. Funny bow tie.
		break;
	case kClueGordoInterview3:
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorGordo, 440); //02-0440.AUD	Between you and me I hear they are all over the place down here.
		}
		KIA_Play_Actor_Dialogue(kActorGordo, 450); //02-0450.AUD	You ought to call in a few more of the hunters to clear the place out.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 3280); //00-3280.AUD	Hunter? Ain’t too often I hear ‘em called that.
		break;
	case kClueGordoConfession:
		KIA_Play_Actor_Dialogue(kActorMcCoy, 3250); //00-3250.AUD	You like cheese, Gordo?
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorGordo, 530); //02-0530.AUD	Think that bad man. My jokes are fresh. Real hip.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 3300); //00-3300.AUD	No, I mean real cheese. Dairy products. You know, from Kingston Kitchen?
		}
		KIA_Play_Actor_Dialogue(kActorGordo, 540); //02-0540.AUD	So you’re wasting shoplifters instead of Replicants these days?
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 3305); //00-3305.AUD	That an admission of guilt?
		}
		KIA_Play_Actor_Dialogue(kActorGordo, 550); //02-0550.AUD	For crying out loud. Can’t a guy make a living in this fakakta place without being hassled?
		break;
	case kClueGordosLighterReplicant:
		KIA_Play_Slice_Model(kModelAnimationGordosLighterReplicant);
		if (_vm->_cutContent) {
			if (Actor_Clue_Query(kActorMcCoy, kClueZubenSquadPhoto)) {
				KIA_Play_Actor_Dialogue(kActorVoiceOver, 1450);
			} else {
				KIA_Play_Actor_Dialogue(kActorVoiceOver, 350);
			}
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 1460);
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 1470);
		} else {
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 350);
		}
		break;
	case kClueGordosLighterHuman:
		KIA_Play_Slice_Model(kModelAnimationGordosLighterHuman);
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 8850); //00-8850.AUD	A lighter.
		}
		break;
	case kClueDektoraInterview4:
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 3620); //00-3620.AUD	You like scorpions, huh?
			KIA_Play_Actor_Dialogue(kActorDektora, 840); //03-0840.AUD	Scorpions?
			KIA_Play_Actor_Dialogue(kActorMcCoy, 3745); //00-3745.AUD	Insects. Fakes. From Animoid Row. You buy a box of them?
			KIA_Play_Actor_Dialogue(kActorDektora, 850);
			KIA_Play_Actor_Dialogue(kActorDektora, 860);
			KIA_Play_Actor_Dialogue(kActorDektora, 870); //03-0870.AUD	I just had to have the whole set. 
			KIA_Play_Actor_Dialogue(kActorMcCoy, 3750); //00-3750.AUD	Did you know they were poisonous?
			KIA_Play_Actor_Dialogue(kActorDektora, 880);
			KIA_Play_Actor_Dialogue(kActorMcCoy, 3755); //00-3755.AUD	And that doesn’t scare you? 
			KIA_Play_Actor_Dialogue(kActorDektora, 890);
			KIA_Play_Actor_Dialogue(kActorDektora, 900); // Who would need to add insects to the list?
		} else {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 3860); //00-3860.AUD	And you’re lovers?
			KIA_Play_Actor_Dialogue(kActorDektora, 1030); //03-1030.AUD	We were once. But now we’ve evolved beyond that.
			KIA_Play_Actor_Dialogue(kActorDektora, 1040); //03-1040.AUD	They are still my family. Clovis and Lucy.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 3865); //00-3865.AUD	What’s Clovis looking for?
			KIA_Play_Actor_Dialogue(kActorDektora, 1050); //03-1050.AUD	Information. Data. Four years isn’t enough time, Mr. McCoy.
			KIA_Play_Actor_Dialogue(kActorDektora, 1060); //03-1060.AUD	If anyone deserves more than four years, it’s Clovis. If you could only meet him.
		}
		break;
	case kClueHollowayInterview:
		KIA_Play_Actor_Dialogue(kActorHolloway, 0); //33-0000.AUD	(Coughs) You're a Rep, McCoy. I've seen your incept photo with my own eyes.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 5520); //00-5520.AUD	Oh, yeah?
		KIA_Play_Actor_Dialogue(kActorMcCoy, 8990); //00-8990.AUD	What have you got there?
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 4240); //99-4240.AUD	That can't be me.
		KIA_Play_Actor_Dialogue(kActorHolloway, 10); //33-0010.AUD	It's all over the place. You don't got a chance. (groans)
		break;
	case kClueBakersBadge:
		KIA_Play_Slice_Model(kModelAnimationBadge);
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 8855); //00-8855.AUD	Baker's badge.
		}
		break;
	case kClueHoldensBadge:
		KIA_Play_Slice_Model(kModelAnimationBadge);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 4420);
		break;
	case kClueCarIdentified:
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 3780);
		if (_vm->_cutContent) {
			if (Actor_Clue_Query(kActorMcCoy, kCluePaintTransfer)) {
				KIA_Play_Actor_Dialogue(kActorVoiceOver, 3790); //99-3790.AUD	The car from Chinatown was the same vehicle that had smacked the hydrant at Runciter's.
			} else {
				KIA_Play_Actor_Dialogue(kActorMcCoy, 690); //00-0690.AUD	Gotcha.
			}
		} else {
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 3790);
		}
		break;
	case kClueCarRegistration1:
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 3800);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 3810);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 3820);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 3830);
		break;
	case kClueCarRegistration2:
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 3840);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 3850);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 3860);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 3870);
		break;
	case kClueCarRegistration3:
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 3880);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 3890);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 3900);
		break;
	case kClueCrazylegsInterview1:
		if (_vm->_cutContent) {
			if (Actor_Clue_Query(kActorMcCoy, kClueCarRegistration1)) {
				KIA_Play_Actor_Dialogue(kActorMcCoy, 1895); //00-1895.AUD	I gotta know more about the woman, Crazy.
				KIA_Play_Actor_Dialogue(kActorCrazylegs, 620); //09-0620.AUD	Like I said, she was tall and blonde. Real woo bait.
				KIA_Play_Actor_Dialogue(kActorCrazylegs, 630); //09-0630.AUD	She was tooling around with a short guy in a bow tie.
				KIA_Play_Actor_Dialogue(kActorMcCoy, 2000); //00-2000.AUD	And she wanted a car.
				KIA_Play_Actor_Dialogue(kActorCrazylegs, 640); //09-0640.AUD	At first, she was looking for a very hard to find item.
				KIA_Play_Actor_Dialogue(kActorCrazylegs, 650); //09-0650.AUD	Something that doesn’t show up on the lot too often.
				KIA_Play_Actor_Dialogue(kActorCrazylegs, 660); //09-0660.AUD	A… police-issue vehicle.
				KIA_Play_Actor_Dialogue(kActorMcCoy, 2005); //00-2005.AUD	A Spinner?
				KIA_Play_Actor_Dialogue(kActorMcCoy, 2010); //00-2010.AUD	But you didn’t have one.
				KIA_Play_Actor_Dialogue(kActorCrazylegs, 670); //09-0670.AUD	Well, not one that would actually fly.
				KIA_Play_Actor_Dialogue(kActorCrazylegs, 680); //09-0680.AUD	I told them to check back in a couple of days.
				KIA_Play_Actor_Dialogue(kActorCrazylegs, 690); //09-0690.AUD	So, then they got looking at that Sedan.
			} else if (Actor_Clue_Query(kActorMcCoy, kClueCarRegistration3)) {
				KIA_Play_Actor_Dialogue(kActorMcCoy, 1915); //00-1915.AUD	You sell a black Sedan a few days ago?
				KIA_Play_Actor_Dialogue(kActorCrazylegs, 820); //09-0820.AUD	Black Sedan? Hey, I got standards. If it ain’t Sporty, I got no room for it.
				KIA_Play_Actor_Dialogue(kActorMcCoy, 2085); //00-2085.AUD	You sold this to a Blake Williams. I’ve seen the registration.
				KIA_Play_Actor_Dialogue(kActorCrazylegs, 900); //09-0900.AUD	Ooh-- Oh, that hurt Sedan.
				KIA_Play_Actor_Dialogue(kActorMcCoy, 2090); //00-2090.AUD	Blake Williams is a fake name.
				KIA_Play_Actor_Dialogue(kActorCrazylegs, 910); //09-0910.AUD	You just never know about some people.
				KIA_Play_Actor_Dialogue(kActorMcCoy, 2105); //00-2105.AUD	What did this guy look like?
				KIA_Play_Actor_Dialogue(kActorCrazylegs, 950); //09-0950.AUD	Nothing special. Beard, dark hair. Had these eyes, kinda…
				KIA_Play_Actor_Dialogue(kActorCrazylegs, 960); //09-0960.AUD	Yeah. Pretty scary. But, heck, I never turn away a customer.
			}
		} else {
			KIA_Play_Actor_Dialogue(kActorCrazylegs, 830); //09-0830.AUD	Oh-- Ooh, that Sedan.
			KIA_Play_Actor_Dialogue(kActorCrazylegs, 840); //09-0840.AUD	Hey, look. A sexy blonde wants to pay top dollar for the ugliest car in the place…
			KIA_Play_Actor_Dialogue(kActorCrazylegs, 850); //09-0850.AUD	who am I to say no?
		}
		break;
	case kClueLichenDogWrapper:
		KIA_Play_Slice_Model(kModelAnimationLichenDogWrapper);
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 550); //99-0550.AUD	The wrapper was from a vendor I knew. Best lichen-dogs in the Fourth Sector.
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 560); //99-0560.AUD	That wasn't saying a whole lot...
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 570); //99-0570.AUD	but with an arcade next door and a dozen Nightclubs down the street...
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 580); //99-0580.AUD	Mia and Murray's stand saw more action in a night than my spinster aunt saw all last century.
		}
		break;
	case kClueRequisitionForm:
		KIA_Play_Slice_Model(kModelAnimationRequisitionForm);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 3930);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 3940);
		break;
	case kClueScaryChair:
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 2550);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 2560);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 2570);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 2580);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 2590);
		break;
	case kClueIzosStashRaided:
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 2470);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 2480);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 2490);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 2500);
		break;
	case kClueHomelessManInterview1:
		if (!_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 5615);  //00-5615.AUD	Describe ‘em to me.
		}
		KIA_Play_Actor_Dialogue(kActorTransient, 170); //12-0170.AUD	Well, there’s the Japanese guy with the coat and the glasses.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 5625);
		KIA_Play_Actor_Dialogue(kActorTransient, 180);
		KIA_Play_Actor_Dialogue(kActorMcCoy, 5630);
		KIA_Play_Actor_Dialogue(kActorTransient, 190);
		if (_vm->_cutContent) {
			if (!Game_Flag_Query(kFlagCT04HomelessTalk)) {
				KIA_Play_Actor_Dialogue(kActorMcCoy, 3230); //00-3230.AUD	You know the chef at Howie’s?
				KIA_Play_Actor_Dialogue(kActorTransient, 200); //12-0200.AUD	Nah, the other fat man. You know him. Rough voice, always eating.
			} else {
				KIA_Play_Actor_Dialogue(kActorMcCoy, 5635); //00-5635.AUD	Fat man? The one I was chasing from the sushi bar.
				KIA_Play_Actor_Dialogue(kActorTransient, 200); //12-0200.AUD	Nah, the other fat man. You know him. Rough voice, always eating.
			}
		} else {
			KIA_Play_Actor_Dialogue(kActorTransient, 200); //12-0200.AUD	Nah, the other fat man. You know him. Rough voice, always eating.
		}
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorTransient, 210); //12-0210.AUD	Saw him wail on the Jap guy once.
		}
		break;
	case kClueHomelessManInterview2:
		KIA_Play_Actor_Dialogue(kActorMcCoy, 5640);
		if (_vm->_cutContent) {
			if (!Game_Flag_Query(kFlagGuzzaIsStupid)) {
				KIA_Play_Actor_Dialogue(kActorTransient, 230);
				KIA_Play_Actor_Dialogue(kActorMcCoy, 5645);
				KIA_Play_Actor_Dialogue(kActorTransient, 240);		
				if (!Actor_Clue_Query(kActorMcCoy, kClueBigManLimping)) {
					KIA_Play_Actor_Dialogue(kActorTransient, 250); //12-0250.AUD	Dumped them in a sewer. They’re gone now. You sure you ain’t got nothing to drink?
				}
			} KIA_Play_Actor_Dialogue(kActorTransient, 160); //12-0160.AUD	Sure you don’t got that drink?
		} else {
			KIA_Play_Actor_Dialogue(kActorTransient, 250);
		}
		KIA_Play_Actor_Dialogue(kActorMcCoy, 5650);
		KIA_Play_Actor_Dialogue(kActorTransient, 260);
		break;
	case kClueHomelessManKid:
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 5670); //00-5670.AUD	About that fat man you saw.
		}
		KIA_Play_Actor_Dialogue(kActorTransient, 340); //12-0340.AUD	You’re "kid".
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 5690); //00-5690.AUD	Huh?
		}
		KIA_Play_Actor_Dialogue(kActorTransient, 350); //12-0350.AUD	No, you’re his kid. That’s what it is.
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 5695); //00-5695.AUD	How’s that?
		}
		KIA_Play_Actor_Dialogue(kActorTransient, 360); //12-0360.AUD	Hell, I seen you guys together. Three weeks ago. At the speech. You remember.
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 2710);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 2730);
		break;
	case kClueFolder:
		KIA_Play_Slice_Model(kModelAnimationFolder);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 2740);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 2750);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 2760);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 2770);
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 3430); //99-3430.AUD	The info I’d gotten from Luther and Lance finally made some sense.
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 3440); //99-3440.AUD	The Reps must had found out about Guzza’s career's sidelines…
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 3450); //99-3450.AUD	and pressured him to set me up in order to get me off their backs.
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 3460); //99-3460.AUD	This nasty business he was only too willing to do.
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 3470); //99-3470.AUD	But I wasn’t gonna eat crow that easily.
		}	
		break;
	case kClueGuzzaFramedMcCoy:
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 3320);
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 3340); //99-3340.AUD	He set up a Black Market network…
			if (Actor_Clue_Query(kActorMcCoy, kClueWeaponsCache)) {
				KIA_Play_Actor_Dialogue(kActorVoiceOver, 3350); //99-3350.AUD	Moving surplus LPD weapons through Izo and the Green Pawn.
			} 
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 3360); 
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 3370); 
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 3380); 
			if (Game_Flag_Query(kFlagGuzzaIsStupid)) {
				KIA_Play_Actor_Dialogue(kActorVoiceOver, 3390); 
				KIA_Play_Actor_Dialogue(kActorVoiceOver, 3400); 
				KIA_Play_Actor_Dialogue(kActorVoiceOver, 3420);
			}
		}
		break;
	case kClueOriginalShippingForm:
		KIA_Play_Slice_Model(kModelAnimationOriginalShippingForm);
		break;
	case kClueOriginalRequisitionForm:
		KIA_Play_Slice_Model(kModelAnimationOriginalRequisitionForm);
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 3950); //99-3950.AUD	The paper was a copy of the requisition form for the station's new shipment of guns.
			if (Actor_Clue_Query(kActorMcCoy, kClueRequisitionForm)) {
				KIA_Play_Actor_Dialogue(kActorVoiceOver, 3960); //99-3960.AUD	But it was for three cases instead of two.
				KIA_Play_Actor_Dialogue(kActorVoiceOver, 3970); //99-3970.AUD	It all smelled pretty damn fishy and Guzza was the guy mixing up the tartar sauce.
				KIA_Play_Actor_Dialogue(kActorVoiceOver, 3980); //99-3980.AUD	If this copy of the shipping form was right...
				KIA_Play_Actor_Dialogue(kActorVoiceOver, 3900); //99-3990.AUD	the LPD should have gotten three cases of weapons not two.
				KIA_Play_Actor_Dialogue(kActorVoiceOver, 4000); //99-4000.AUD	Guns were getting swiped somewhere along the line.
			}
		}
		break;
	case kClueCandyWrapper:
		KIA_Play_Slice_Model(kModelAnimationCandyWrapper);
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 3300); //99-3300.AUD	I recognized the wrapper.
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 3310); //99-3310.AUD	The same brand of candy that Lucy had on her desk at Runciter’s.
		}
		break;
	case kClueFlaskOfAbsinthe:
		KIA_Play_Slice_Model(kModelAnimationFlaskOfAbsinthe);
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 8880); //00-8880.AUD	A flask of absinthe.
		}
		break;
	case kClueLutherLanceInterview:
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 5740); //00-5740.AUD	Tyrell says the four year lifespan can’t be extended.
			KIA_Play_Actor_Dialogue(kActorLance, 180); //13-0180.AUD	Of course he’s gonna say that but he’s wrong.
			KIA_Play_Actor_Dialogue(kActorLuther, 220); //10-0220.AUD	Very wrong.
			KIA_Play_Actor_Dialogue(kActorLance, 190); //13-0190.AUD	We got the research right here that will prove it.
		}
		KIA_Play_Actor_Dialogue(kActorLuther, 240); //10-0240.AUD	Tyrell’s dictate was that every body part would fail. And only the designer’s of each would know exactly how it worked.
		KIA_Play_Actor_Dialogue(kActorLuther, 250);	
		if (_vm->_cutContent) {
			if (Actor_Query_Intelligence(kActorClovis) == 100) {
				KIA_Play_Actor_Dialogue(kActorLance, 200); //13-0200.AUD	Clovis has already unlocked the secret of the skin. That was Moraji.
			}
		} else {
				KIA_Play_Actor_Dialogue(kActorLance, 200); //13-0200.AUD	Clovis has already unlocked the secret of the skin. That was Moraji.
		}
		KIA_Play_Actor_Dialogue(kActorLuther, 260);
		KIA_Play_Actor_Dialogue(kActorLuther, 270); //10-0270.AUD	A lot of retrograde viruses were built into the eyes.
		KIA_Play_Actor_Dialogue(kActorLance, 210);
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 5810); //00-5810.AUD	Did you tell Clovis all this?
			if (Actor_Query_Intelligence(kActorClovis) == 100) {
				KIA_Play_Actor_Dialogue(kActorLance, 220); //13-0220.AUD	He didn’t ask, he already knew.
				KIA_Play_Actor_Dialogue(kActorLance, 230); //13-0230.AUD	He knows all about you too.
			} else if (Actor_Query_Intelligence(kActorClovis) == 80) {
				KIA_Play_Actor_Dialogue(kActorLance, 290); //13-0290.AUD	He’s sharp this one.
			}
		}
		break;
	case kCluePhoneCallDektora1:
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 2500); //00-2500.AUD	I got nothing to keep me here anymore. That’s for sure. You got a plan?
			KIA_Play_Actor_Dialogue(kActorDektora, 360); //03-0360.AUD	There’s a used car place in the Fourth Sector near the arcade.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 2510); //00-2510.AUD	I know it.
		} else {
			KIA_Play_Actor_Dialogue(kActorDektora, 360); //03-0360.AUD	There’s a used car place in the Fourth Sector near the arcade.
		}
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagDektoraIsReplicant)) {
				KIA_Play_Actor_Dialogue(kActorDektora, 370); //03-0370.AUD	Gordo and I went there before looking for a vehicle.
				KIA_Play_Actor_Dialogue(kActorDektora, 380); //03-0380.AUD	The owner was nice to us. He’ll probably help us, if we pay him.
			}
			KIA_Play_Actor_Dialogue(kActorMcCoy, 2515); ////00-2515.AUD	We’d need a Spinner to be able to get anywhere.
			KIA_Play_Actor_Dialogue(kActorDektora, 390); //03-0390.AUD	He’s got a couple for sale.
		} else {
			KIA_Play_Actor_Dialogue(kActorDektora, 380); //03-0380.AUD	The owner was nice to us. He’ll probably help us, if we pay him.
		}
		break;
	case kCluePhoneCallDektora2:
		KIA_Play_Actor_Dialogue(kActorMcCoy, 2505);
		KIA_Play_Actor_Dialogue(kActorDektora, 430);
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagDektoraIsReplicant)) {
				KIA_Play_Actor_Dialogue(kActorDektora, 440);
			}
		} else {
			KIA_Play_Actor_Dialogue(kActorDektora, 440);
		}
		KIA_Play_Actor_Dialogue(kActorMcCoy, 2530);
		KIA_Play_Actor_Dialogue(kActorDektora, 450);
		KIA_Play_Actor_Dialogue(kActorMcCoy, 2535);
		KIA_Play_Actor_Dialogue(kActorDektora, 460);
		KIA_Play_Actor_Dialogue(kActorDektora, 470); //03-0470.AUD	It comes out right near the moonbus.
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorDektora, 480); //03-0480.AUD	I need you, Ray. I can’t watch my friends die. Not alone.
			if (Game_Flag_Query(kFlagDektoraIsReplicant)) {
				KIA_Play_Actor_Dialogue(kActorDektora, 490); //03-0490.AUD	And if you can’t come, adieu my love.
			} else {
				KIA_Play_Actor_Dialogue(kActorMcCoy, 1825);	//00-1825.AUD	Okay
				KIA_Play_Actor_Dialogue(kActorDektora, 420); //03-0420.AUD	Then meet me there. I’ll be there within the hour.
			}
		}
		break;
	case kCluePhoneCallLucy1:
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorLucy, 570); //06-0570.AUD	But-- I thought we were going away together. Just you and me.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 2560); //00-2560.AUD	Maybe we’ll do it after I talk to him.
			KIA_Play_Actor_Dialogue(kActorLucy, 580); //06-0580.AUD	You promise?
		}
		KIA_Play_Actor_Dialogue(kActorLucy, 590); //06-0590.AUD	We could buy a car. From that place next to the arcade.
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 2565); //00-2565.AUD	A ground car wouldn’t get us too far.
			KIA_Play_Actor_Dialogue(kActorLucy, 600); //06-0600.AUD	One of those flying cars would though.
			KIA_Play_Actor_Dialogue(kActorLucy, 610); //06-0610.AUD	It could take us all the way out to that beautiful lake.
			KIA_Play_Actor_Dialogue(kActorLucy, 620); //06-0620.AUD	You know, the one with the trees and the flowers.
			KIA_Play_Actor_Dialogue(kActorLucy, 6805); //00-6805.AUD	I-- I promise you. But for now we gotta be careful. You should stay hidden for a while.
		}
		KIA_Play_Actor_Dialogue(kActorLucy, 630); //06-0630.AUD	I’ll meet you there, okay? At the place where he sells the cars.
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 2575);
			KIA_Play_Actor_Dialogue(kActorLucy, 640); //06-0640.AUD	Oh, I love you so much Ray.
		}
		break;
	case kCluePhoneCallLucy2:
		KIA_Play_Actor_Dialogue(kActorLucy, 540);
		KIA_Play_Actor_Dialogue(kActorLucy, 550);
		KIA_Play_Actor_Dialogue(kActorMcCoy, 2550);
		KIA_Play_Actor_Dialogue(kActorLucy, 560); //06-0560.AUD	Out in the Kipple, by the moonbus. Way out where the tunnel ends.
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 2555); //00-2555.AUD	Tell him to stay where he is, until I can find a way for all of us to escape.
			KIA_Play_Actor_Dialogue(kActorLucy, 570);
			KIA_Play_Actor_Dialogue(kActorMcCoy, 2560); //00-2560.AUD	Maybe we’ll do it after I talk to him.
			KIA_Play_Actor_Dialogue(kActorLucy, 580); // You promise?
			KIA_Play_Actor_Dialogue(kActorLucy, 6805); //00-6805.AUD	I-- I promise you. But for now we gotta be careful. You should stay hidden for a while.
			KIA_Play_Actor_Dialogue(kActorLucy, 640); //06-0640.AUD	Oh, I love you so much Ray.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 2570); //00-2570.AUD	Lucy, there’s a good chance--
			KIA_Play_Actor_Dialogue(kActorMcCoy, 2575);
		}
		break;
	case kCluePhoneCallClovis:
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorClovis, 2610); //00-2610.AUD	How do I know who I really am?
			KIA_Play_Actor_Dialogue(kActorClovis, 450); //05-0450.AUD	Guzza must have programmed you as an experiment.
			KIA_Play_Actor_Dialogue(kActorClovis, 460); //05-0460.AUD	To see if you could really act as one of them.
			KIA_Play_Actor_Dialogue(kActorClovis, 470); //05-0470.AUD	He wiped out all your memories of our time together.
			KIA_Play_Actor_Dialogue(kActorClovis, 480); //05-0480.AUD	As soldiers during the Phobos wars.
			KIA_Play_Actor_Dialogue(kActorClovis, 490); //05-0490.AUD	The battle of the Gemini. Firefights on the top of the Olympus Mountains!
			KIA_Play_Actor_Dialogue(kActorMcCoy, 2615); //00-2615.AUD	I don’t remember.
			KIA_Play_Actor_Dialogue(kActorClovis, 1230); //05-1230.AUD	That’s what I remember.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 8565); //00-8565.AUD	Really?
			KIA_Play_Actor_Dialogue(kActorClovis, 500); //05-0500.AUD	But if you dig real deep and feel, you’ll know what’s real.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 2620); //00-2620.AUD	Okay. What do we do next?
			KIA_Play_Actor_Dialogue(kActorClovis, 510); //05-0510.AUD	In the sewers near the police station is a tunnel that leads out to the Kipple.
			KIA_Play_Actor_Dialogue(kActorClovis, 520); //05-0520.AUD	Do you know it?
			KIA_Play_Actor_Dialogue(kActorMcCoy, 2625); //00-2625.AUD	I can find it.
		}
		if (!_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorClovis, 530); //05-0530.AUD	It’s a passage to freedom, McCoy. To your destiny.
			KIA_Play_Actor_Dialogue(kActorClovis, 540); //05-0540.AUD	An underground railroad to carry you from bondage. We’ll be waiting.
		}
		break;
	case kCluePhoneCallCrystal:
		KIA_Play_Actor_Dialogue(kActorSteele, 700); //01-0700.AUD	I got a line on where the skin-jobs are holing up.
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 2640); //00-2640.AUD	Not the Yukon?
			KIA_Play_Actor_Dialogue(kActorSteele, 710); //01-0710.AUD	Yesterdays news. Remember Gaff was talking about that moonbus massacre?
			KIA_Play_Actor_Dialogue(kActorSteele, 720); //01-0720.AUD	I found out where they crash-landed it. And five will get you ten they’ll be licking their wounds there.
		}
		KIA_Play_Actor_Dialogue(kActorSteele, 750); //01-0750.AUD	It’s way the shit out there in the Kipple. Way, way out.
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 2650); //00-2650.AUD	How are they getting into the city?
		}
		KIA_Play_Actor_Dialogue(kActorSteele, 760); //01-0760.AUD	They’ve been accessing through an old sewer tunnel.
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorSteele, 770); //01-0770.AUD	That son of a bitch, Clovis, was climbing in and out of a manhole right next to the police station and nobody ever noticed.
			if (Game_Flag_Query(kFlagGuzzaArrested)
			|| !Game_Flag_Query(kFlagGuzzaSaved)) {	
				KIA_Play_Actor_Dialogue(kActorMcCoy, 2655); //00-2655.AUD	Figures. With incompetents like Guzza at the helm.	
				if (Game_Flag_Query(kFlagGuzzaArrested)) {
					KIA_Play_Actor_Dialogue(kActorSteele, 790); //01-0790.AUD	I think we can forget about Guzza. That guy’s gonna be fed to the barracudas.
				}
			}
		}
		break;
	case kCluePowerSource:
		KIA_Play_Slice_Model(kModelAnimationPowerSource);
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorSadik, 240); //08-0240.AUD	There got to be something around here, mon.
			KIA_Play_Actor_Dialogue(kActorSadik, 250); //08-0250.AUD	Old reactor cores. Anything still got a glow.
			KIA_Play_Actor_Dialogue(kActorSadik, 260); //08-0260.AUD	The generator? It take almost anything.
		}
		break;
	case kClueBomb:
		KIA_Play_Slice_Model(kModelAnimationBomb);
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 1020); //99-1020.AUD	It was one of Sadik’s bombs. Was it a lie?
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 1030); //99-1030.AUD	Had she been planning to kill me all along?
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 1040); //99-1040.AUD	Or was it just insurance? Something extra to defend herself.
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 1050); //99-1050.AUD	I’d never know.
		}
		break;
	case kClueDNATyrell:
	case kClueDNASebastian:
	case kClueDNAChew:
	case kClueDNAMoraji:
	case kClueDNALutherLance:
	case kClueDNAMarcus:
		{
			int dnaEvidences = Global_Variable_Query(kVariableDNAEvidence);
			if (_vm->_cutContent) {
				if (dnaEvidences == 1) {
					KIA_Play_Slice_Model(kModelAnimationDNAEvidence01OutOf6);
				} else if (dnaEvidences == 2) {
					KIA_Play_Slice_Model(kModelAnimationDNAEvidence02OutOf6);
				} else if (dnaEvidences == 3) {
					KIA_Play_Slice_Model(kModelAnimationDNAEvidence03OutOf6);
				} else if (dnaEvidences == 4) {
					KIA_Play_Slice_Model(kModelAnimationDNAEvidence04OutOf6);
				} else if (dnaEvidences == 5) {
					KIA_Play_Slice_Model(kModelAnimationDNAEvidence05OutOf6);
				} else if (dnaEvidences >= 6) {
					KIA_Play_Slice_Model(kModelAnimationDNAEvidenceComplete);
				}
			} else if (dnaEvidences == 1) {
				KIA_Play_Slice_Model(kModelAnimationDNAEvidence01OutOf6);
			} else if (dnaEvidences == 2) {
				KIA_Play_Slice_Model(kModelAnimationDNAEvidence03OutOf6);
			} else if (dnaEvidences == 3) {
				KIA_Play_Slice_Model(kModelAnimationDNAEvidence04OutOf6);
			} else if (dnaEvidences >= 4) {
				KIA_Play_Slice_Model(kModelAnimationDNAEvidenceComplete);
			}
		}
		break;
	case kClueGarterSnake:
		KIA_Play_Slice_Model(kModelAnimationGarterSnake);
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 8895); //00-8895.AUD	A fake garter snake.
		}
		break;
	case kClueSlug:
		KIA_Play_Slice_Model(kModelAnimationSlug);
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 8900); //00-8900.AUD	An electric slug.
		}
		break;
	case kClueGoldfish:
		KIA_Play_Slice_Model(kModelAnimationGoldfish);
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 8905); //00-8905.AUD	A mechanical goldfish.
		}
		break;
	case kClueZubenTalksAboutLucy1:
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 7295); //00-7295.AUD	The girl. I need to know where's the girl.
			if (Game_Flag_Query(kFlagZubenIsReplicant)) {
				KIA_Play_Actor_Dialogue(kActorZuben, 200); //19-0200.AUD	Girl?
				KIA_Play_Actor_Dialogue(kActorMcCoy, 7315); //00-7315.AUD	Lucy.
			}
			KIA_Play_Actor_Dialogue(kActorZuben, 210); //19-0210.AUD	She daughter. She with Clovis.
			KIA_Play_Actor_Dialogue(kActorZuben, 220); //19-0220.AUD	You not hurt her.	
			KIA_Play_Actor_Dialogue(kActorMcCoy, 7320); //00-7320.AUD	Is she a Replicant?
		}
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagZubenIsReplicant)) {
				KIA_Play_Actor_Dialogue(kActorZuben, 230); //19-0230.AUD	Daughter sick. Only four years to live. Four years. Daughter Zuben whole family.
				KIA_Play_Actor_Dialogue(kActorZuben, 240); //19-0240.AUD	But Clovis he fix.
			} else {
				KIA_Play_Actor_Dialogue(kActorMcCoy, 1885); //00-1885.AUD	I’ll take that as a yes.
			}
		} else {
			KIA_Play_Actor_Dialogue(kActorZuben, 230); //19-0230.AUD	Daughter sick. Only four years to live. Four years. Daughter Zuben whole family.
			KIA_Play_Actor_Dialogue(kActorZuben, 240); //19-0240.AUD	But Clovis he fix.
		}
		break;
	case kClueZubenTalksAboutLucy2:
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 7295); //00-7295.AUD	The girl. I need to know where's the girl.
			if (Game_Flag_Query(kFlagZubenIsReplicant)) {
				KIA_Play_Actor_Dialogue(kActorZuben, 200); //19-0200.AUD	Girl?
				KIA_Play_Actor_Dialogue(kActorMcCoy, 7315); //00-7315.AUD	Lucy.
			}
			KIA_Play_Actor_Dialogue(kActorZuben, 210); //19-0210.AUD	She daughter. She with Clovis.
			KIA_Play_Actor_Dialogue(kActorZuben, 220); //19-0220.AUD	You not hurt her.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 7320); //00-7320.AUD	Is she a Replicant?
		}
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagZubenIsReplicant)) {
				KIA_Play_Actor_Dialogue(kActorZuben, 250); //19-0250.AUD	Daughter not like me.
			}
		} else {
			KIA_Play_Actor_Dialogue(kActorZuben, 250); //19-0250.AUD	Daughter not like me.
		}
		KIA_Play_Actor_Dialogue(kActorMcCoy, 7335); //00-7335.AUD	She's not a Replicant?
		KIA_Play_Actor_Dialogue(kActorZuben, 260); //19-0260.AUD	She good girl. She stay with Clovis.
		break;
	case kClueZubensMotive:
		if (_vm->_cutContent) {
			if (!Actor_Clue_Query(kActorMcCoy, kClueLucyInterview)) {
				KIA_Play_Actor_Dialogue(kActorMcCoy, 7300); //00-7300.AUD	Did you kill the animals?
			} else {
				KIA_Play_Actor_Dialogue(kActorMcCoy, 7355); //00-7355.AUD	All those animals died.
			}
			KIA_Play_Actor_Dialogue(kActorZuben, 270); //19-0270.AUD	Because he bad.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 7350); //00-7350.AUD	Runciter?
		} 
		KIA_Play_Actor_Dialogue(kActorZuben, 280); //19-0280.AUD	He not pay. Bad to Lucy. Bad to everybody. Make people starve.
		if (!_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 7355); //00-7355.AUD	All those animals died.
		}
		KIA_Play_Actor_Dialogue(kActorZuben, 290); //19-0290.AUD	He made Lucy do bad things. Lucy hurt. Clovis more angry.
		if (Game_Flag_Query(kFlagLucyIsReplicant)) {
			KIA_Play_Actor_Dialogue(kActorZuben, 300); //19-0300.AUD	Girl was forced to do bad things Off-World. Clovis thought Terra better.
			KIA_Play_Actor_Dialogue(kActorZuben, 310); //19-0310.AUD	But Terra's no better for young girls. Runciter bad to Lucy.
		}
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 7360); //00-7360.AUD	Did he do things to Lucy?
			KIA_Play_Actor_Dialogue(kActorMcCoy, 2390); //00-2390.AUD	Oh, God. No.
			KIA_Play_Actor_Dialogue(kActorZuben, 320); //19-0320.AUD	Clovis say Runciter love animals. Runciter still alive so he hurt now. Know what pain is.
			KIA_Play_Actor_Dialogue(kActorZuben, 330); //19-0330.AUD	Kill him, he not hurt. Just dead.
		}
		break;
	case kClueVKDektoraReplicant:
		KIA_Play_Actor_Dialogue(kActorAnsweringMachine, 420);
		KIA_Play_Actor_Dialogue(kActorAnsweringMachine, 430);
		break;
	case kClueVKDektoraHuman:
		KIA_Play_Actor_Dialogue(kActorAnsweringMachine, 420);
		KIA_Play_Actor_Dialogue(kActorAnsweringMachine, 440);
		break;
	case kClueVKBobGorskyReplicant:
		KIA_Play_Actor_Dialogue(kActorAnsweringMachine, 420);
		KIA_Play_Actor_Dialogue(kActorAnsweringMachine, 430);
		break;
	case kClueVKBobGorskyHuman:
		KIA_Play_Actor_Dialogue(kActorAnsweringMachine, 420);
		KIA_Play_Actor_Dialogue(kActorAnsweringMachine, 440);
		break;
	case kClueVKLutherLanceReplicant:
		KIA_Play_Actor_Dialogue(kActorAnsweringMachine, 420);
		KIA_Play_Actor_Dialogue(kActorAnsweringMachine, 430);
		break;
	case kClueVKLutherLanceHuman:
		KIA_Play_Actor_Dialogue(kActorAnsweringMachine, 420);
		KIA_Play_Actor_Dialogue(kActorAnsweringMachine, 440);
		break;
	case kClueVKGrigorianReplicant:
		KIA_Play_Actor_Dialogue(kActorAnsweringMachine, 420);
		KIA_Play_Actor_Dialogue(kActorAnsweringMachine, 430);
		break;
	case kClueVKGrigorianHuman:
		KIA_Play_Actor_Dialogue(kActorAnsweringMachine, 420);
		KIA_Play_Actor_Dialogue(kActorAnsweringMachine, 440);
		break;
	case kClueVKIzoReplicant:
		KIA_Play_Actor_Dialogue(kActorAnsweringMachine, 420);
		KIA_Play_Actor_Dialogue(kActorAnsweringMachine, 430);
		break;
	case kClueVKIzoHuman:
		KIA_Play_Actor_Dialogue(kActorAnsweringMachine, 420);
		KIA_Play_Actor_Dialogue(kActorAnsweringMachine, 440);
		break;
	case kClueVKCrazylegsReplicant:
		KIA_Play_Actor_Dialogue(kActorAnsweringMachine, 420);
		KIA_Play_Actor_Dialogue(kActorAnsweringMachine, 430);
		break;
	case kClueVKCrazylegsHuman:
		KIA_Play_Actor_Dialogue(kActorAnsweringMachine, 420);
		KIA_Play_Actor_Dialogue(kActorAnsweringMachine, 440);
		break;
	case kClueVKRunciterReplicant:
		KIA_Play_Actor_Dialogue(kActorAnsweringMachine, 420);
		KIA_Play_Actor_Dialogue(kActorAnsweringMachine, 430);
		break;
	case kClueVKRunciterHuman:
		KIA_Play_Actor_Dialogue(kActorAnsweringMachine, 420);
		KIA_Play_Actor_Dialogue(kActorAnsweringMachine, 440);
		break;
	case kClueVKEarlyQReplicant:
		KIA_Play_Actor_Dialogue(kActorAnsweringMachine, 420);
		KIA_Play_Actor_Dialogue(kActorAnsweringMachine, 430);
		break;
	case kClueVKEarlyQHuman:
		KIA_Play_Actor_Dialogue(kActorAnsweringMachine, 420);
		KIA_Play_Actor_Dialogue(kActorAnsweringMachine, 440);
		break;
	case kClueCrimeSceneNotes:
		KIA_Play_Actor_Dialogue(kActorSteele, 3310);
		KIA_Play_Actor_Dialogue(kActorSteele, 3320);
		if (_vm->_cutContent
		    && (_vm->_language == Common::ES_ESP
		        || _vm->_language == Common::IT_ITA)
		) {
			//
			// in ITA and ESP the 3340 quote is the second half of the sentence starting in previous quote (3330)
			KIA_Play_Actor_Dialogue(kActorSteele, 3330);
			KIA_Play_Actor_Dialogue(kActorSteele, 3340);
		} else if (_vm->_cutContent
		           && _vm->_language == Common::FR_FRA
		) {
			// in FRA the 3340 quote has the full sentence rendering the previous quote (3330) redundant
			// FRA (Restored Content) version needs only 3340
			KIA_Play_Actor_Dialogue(kActorSteele, 3340);
		} else {
			// ENG and DEU and non-restored content versions need only 3330
			// the 3340 quote is *BOOP* in the ENG and DEU versions
			KIA_Play_Actor_Dialogue(kActorSteele, 3330); //01-3330.AUD	It'll take a day or so to analyze the debris but there's no doubt in my mind that we're dealing with a bomber here.
		}
		if (_vm->_cutContent) {
			if (Actor_Query_Intelligence(kActorSteele) == 90) {
				KIA_Play_Actor_Dialogue(kActorSteele, 3350); //01-3350.AUD	Right now it looks like the protesters had nothing to do with it.
				KIA_Play_Actor_Dialogue(kActorSteele, 3360); //01-3360.AUD	They were in too close proximity to have been in on the deal.
			}
		} else {
			KIA_Play_Actor_Dialogue(kActorSteele, 3350); //01-3350.AUD	Right now it looks like the protesters had nothing to do with it.
			KIA_Play_Actor_Dialogue(kActorSteele, 3360); //01-3360.AUD	They were in too close proximity to have been in on the deal.
		}
		KIA_Play_Actor_Dialogue(kActorSteele, 3370); //01-3370.AUD	No M.O.'s or identities are rolling up just yet…
		if (_vm->_cutContent) {
			if (Actor_Query_Intelligence(kActorSteele) == 90) {
				KIA_Play_Actor_Dialogue(kActorSteele, 3380); //01-3380.AUD	and I'm still going through the incept files to see if any Replicant munitions' experts are unaccounted for.
			}
		} else {
			KIA_Play_Actor_Dialogue(kActorSteele, 3380); //01-3380.AUD	and I'm still going through the incept files to see if any Replicant munitions' experts are unaccounted for.
		}
		break;
	case kClueGrigorianInterviewA:
		KIA_Play_Actor_Dialogue(kActorSteele, 3390);
		KIA_Play_Actor_Dialogue(kActorSteele, 3400);
		KIA_Play_Actor_Dialogue(kActorSteele, 3410);
		// TODO this line of Grigorian is supposedly interrupted by Steele's following line
		//      maybe implement a way to not wait before the next line is played, similar to Actor_Says_With_Pause()
		//       (look into tick() for kia.cpp)
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagGrigorianIsReplicant)) {
				KIA_Play_Actor_Dialogue(kActorGrigorian, 1260); //11-1260.AUD	I once again ask that my attorney--
				if (Actor_Query_Intelligence(kActorSteele) == 70) {
					KIA_Play_Actor_Dialogue(kActorSteele, 3420); //01-3420.AUD	Shut it, shitbird.
				}
				KIA_Play_Actor_Dialogue(kActorSteele, 3430); //01-3430.AUD	I'm asking the questions.
			}
		} else {
			KIA_Play_Actor_Dialogue(kActorGrigorian, 1260); //11-1260.AUD	I once again ask that my attorney--
			KIA_Play_Actor_Dialogue(kActorSteele, 3420); //01-3420.AUD	Shut it, shitbird.
			KIA_Play_Actor_Dialogue(kActorSteele, 3430); //01-3430.AUD	I'm asking the questions.
		}
		if (_vm->_cutContent) {
			if (Actor_Query_Intelligence(kActorSteele) == 90) {
				KIA_Play_Actor_Dialogue(kActorSteele, 3440); //01-3440.AUD	We've already put you on the machine, so we know you're not a skin-job.
				KIA_Play_Actor_Dialogue(kActorGrigorian, 1270); //11-1270.AUD	That term offends me.
				KIA_Play_Actor_Dialogue(kActorSteele, 3450); //01-3450.AUD	Okay, so you're not one of those biomechanical scumbags.
			}
		} else {
			KIA_Play_Actor_Dialogue(kActorSteele, 3440); //01-3440.AUD	We've already put you on the machine, so we know you're not a skin-job.
			KIA_Play_Actor_Dialogue(kActorGrigorian, 1270); //11-1270.AUD	That term offends me.
			KIA_Play_Actor_Dialogue(kActorSteele, 3450); //01-3450.AUD	Okay, so you're not one of those biomechanical scumbags.
		}
		KIA_Play_Actor_Dialogue(kActorSteele, 3460); //01-3460.AUD	You claim to not know anything about the bombing at Tyrell.
		KIA_Play_Actor_Dialogue(kActorGrigorian, 1280); //11-1280.AUD	This is true. We advocate equal rights under the Law for Replicants. We have nothing against Tyrell corporation for creating them.
		if (_vm->_cutContent) {
			if (Actor_Query_Intelligence(kActorSteele) == 90) {
				KIA_Play_Actor_Dialogue(kActorSteele, 3470); //01-3470.AUD	That's some sick logic.
			}
		} else {
			KIA_Play_Actor_Dialogue(kActorSteele, 3470); //01-3470.AUD	That's some sick logic.
		}
		KIA_Play_Actor_Dialogue(kActorGrigorian, 1300); //11-1300.AUD	The Replicants are living organisms, whether people like you like it or not.
		KIA_Play_Actor_Dialogue(kActorGrigorian, 1310); //11-1310.AUD	Replicants contribute greatly to the economic well-being of our culture. They cannot be discounted as such.
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorSteele, 3260); // And eliminating the glitches...
			KIA_Play_Actor_Dialogue(kActorSteele, 3480); //01-3480.AUD	Hell, it would be no skin off my nose if each and every one of them was hosed down for good.
		    if (_vm->_language == Common::ES_ESP
		        || _vm->_language == Common::IT_ITA) {
				//
				// in ITA and ESP the 3490 quote is the second half of the sentence starting in previous quote (3480)
				KIA_Play_Actor_Dialogue(kActorSteele, 3490); //
			}
		} else {
			// the 3490 quote is *BOOP* in the ENG and DEU versions
			// the 3490 quote is also redundant in FRA version, since it's only the first half of the previous quote (3480)
			KIA_Play_Actor_Dialogue(kActorSteele, 3480); //
		}
		KIA_Play_Actor_Dialogue(kActorSteele, 3500); //01-3500.AUD	You've ever seen this guy?
		if (_vm->_cutContent) {
			if (!Game_Flag_Query(kFlagGrigorianIsReplicant)) {
				KIA_Play_Actor_Dialogue(kActorGrigorian, 1320); //11-1320.AUD	Why, yes. Actually, I have. He was present at the protest.
				KIA_Play_Actor_Dialogue(kActorGrigorian, 1330); //11-1330.AUD	He's not part of our group but outsiders are usually welcome.
				KIA_Play_Actor_Dialogue(kActorSteele, 3510); //01-3510.AUD	How many new faces showed up that day?
				KIA_Play_Actor_Dialogue(kActorGrigorian, 1340); //11-1340.AUD	Not too many. A handful at most.
				KIA_Play_Actor_Dialogue(kActorSteele, 3520); //01-3520.AUD	Describe them to me.
				KIA_Play_Actor_Dialogue(kActorGrigorian, 1350); //11-1350.AUD	I don't know if I can.
			} else {
				KIA_Play_Actor_Dialogue(kActorGrigorian, 550); //11-0550.AUD	No.
			}
		} else {
			KIA_Play_Actor_Dialogue(kActorGrigorian, 1320); //11-1320.AUD	Why, yes. Actually, I have. He was present at the protest.
			KIA_Play_Actor_Dialogue(kActorGrigorian, 1330); //11-1330.AUD	He's not part of our group but outsiders are usually welcome.
			KIA_Play_Actor_Dialogue(kActorSteele, 3510); //01-3510.AUD	How many new faces showed up that day?
			KIA_Play_Actor_Dialogue(kActorGrigorian, 1340); //11-1340.AUD	Not too many. A handful at most.
			KIA_Play_Actor_Dialogue(kActorSteele, 3520); //01-3520.AUD	Describe them to me.
			
		}	
		if (_vm->_cutContent) {
			if (Actor_Query_Intelligence(kActorSteele) == 70) {
				KIA_Play_Actor_Dialogue(kActorSteele, 3530); //01-3530.AUD	Oh, no?
			}
		} else {
			KIA_Play_Actor_Dialogue(kActorSteele, 3530); //01-3530.AUD	Oh, no?
		}
		KIA_Play_Actor_Dialogue(kActorSteele, 3540); //01-3540.AUD	Recording off.
		break;
	case kClueGrigorianInterviewB1:
		// Izo is a Replicant
		KIA_Play_Actor_Dialogue(kActorSteele, 3550); // Describe them to me again.
		KIA_Play_Actor_Dialogue(kActorGrigorian, 1360); // Just the Rastafarian fellow. And that-- that friend of his. A slim blond man, Asian. With-- with a ponytail.
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagGrigorianIsReplicant)) {
				KIA_Play_Actor_Dialogue(kActorGrigorian, 1370); //11-1370.AUD	Can I see my attorney?
			}
		} else {
			KIA_Play_Actor_Dialogue(kActorGrigorian, 1370); //11-1370.AUD	Can I see my attorney?
		}
		if (_vm->_cutContent) {
			if (Actor_Query_Intelligence(kActorSteele) == 90) {
				KIA_Play_Actor_Dialogue(kActorSteele, 3620); // Let me ask you a question.
				KIA_Play_Actor_Dialogue(kActorSteele, 3630); //01-3630.AUD	Who the hell bankrolls your operation?
				if (!Game_Flag_Query(kFlagGrigorianIsReplicant)) {
					KIA_Play_Actor_Dialogue(kActorGrigorian, 1380); //11-1380.AUD	Well, we have a number of anonymous donors.
					KIA_Play_Actor_Dialogue(kActorSteele, 3640);  // such as
					KIA_Play_Actor_Dialogue(kActorGrigorian, 1390); //11-1390.AUD	So anonymous even I don't know who they are. People with resources.
				} else {
					KIA_Play_Actor_Dialogue(kActorGrigorian, 770); //11-0770.AUD	I'm not answering that.
				}
			}
		}
		if (_vm->_cutContent) {
			if (!Game_Flag_Query(kFlagGrigorianIsReplicant)) {
				KIA_Play_Actor_Dialogue(kActorSteele, 3560); // Bravo, Spencer.
				KIA_Play_Actor_Dialogue(kActorSteele, 3570); //01-3570.AUD	You've done your civic duty for the day.
			}
		} else {
			KIA_Play_Actor_Dialogue(kActorSteele, 3560); // Bravo, Spencer.
			KIA_Play_Actor_Dialogue(kActorSteele, 3570); //01-3570.AUD	You've done your civic duty for the day.
		}
		break;
	case kClueGrigorianInterviewB2:
		// Izo is a human
		KIA_Play_Actor_Dialogue(kActorSteele, 3580); // Describe them for me again.
		KIA_Play_Actor_Dialogue(kActorGrigorian, 1400); // There was that Rastafarian fellow and one of our ex members showed up.
		KIA_Play_Actor_Dialogue(kActorSteele, 3590); //01-3590.AUD	Who's that?
		KIA_Play_Actor_Dialogue(kActorGrigorian, 1410); // A Japanese man named Izo.
		KIA_Play_Actor_Dialogue(kActorSteele, 3600); //01-3600.AUD	Why did you get rid of him?
		if (_vm->_cutContent) {
			if (!Game_Flag_Query(kFlagGrigorianIsReplicant)) {
				KIA_Play_Actor_Dialogue(kActorGrigorian, 1420); // We're a pacifist organization and we have rules
				KIA_Play_Actor_Dialogue(kActorGrigorian, 1430); // Izo refused to check in his samurai sword
			} else {
				KIA_Play_Actor_Dialogue(kActorGrigorian, 770); //11-0770.AUD	I'm not answering that.
			}
		} else {
			KIA_Play_Actor_Dialogue(kActorGrigorian, 1420); // We're a pacifist organization and we have rules
			KIA_Play_Actor_Dialogue(kActorGrigorian, 1430); // Izo refused to check in his samurai sword
		}
		KIA_Play_Actor_Dialogue(kActorSteele, 3610); //01-3610.AUD	Where can I find this Izo?
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagGrigorianIsReplicant)) {
				KIA_Play_Actor_Dialogue(kActorGrigorian, 1090); //11-1090.AUD	I wanna see my attorney, now!
			} else {
				KIA_Play_Actor_Dialogue(kActorGrigorian, 1440); //11-1440.AUD	He owns one of those little second-hand stores downtown.
			}	
			if (Actor_Query_Intelligence(kActorSteele) == 90) {
				KIA_Play_Actor_Dialogue(kActorSteele, 3620); // Let me ask you a question.
				KIA_Play_Actor_Dialogue(kActorSteele, 3630); //01-3630.AUD	Who the hell bankrolls your operation?
				if (Game_Flag_Query(kFlagGrigorianIsReplicant)) {
					KIA_Play_Actor_Dialogue(kActorGrigorian, 1060); //11-1060.AUD	This conversation is over, detective. I don't have to sit here and take abuse.
				} else {
					KIA_Play_Actor_Dialogue(kActorGrigorian, 1450); //11-1450.AUD	We have a number of anonymous donors. People with resources and sources.
					KIA_Play_Actor_Dialogue(kActorSteele, 3640);  // such as
					KIA_Play_Actor_Dialogue(kActorGrigorian, 1460); //11-1460.AUD	So anonymous even I don't know who they are.
					KIA_Play_Actor_Dialogue(kActorSteele, 3650); //01-3650.AUD	I almost believe you.
				}
			}
		} else {
			KIA_Play_Actor_Dialogue(kActorSteele, 3620); // Let me ask you a question.
			KIA_Play_Actor_Dialogue(kActorSteele, 3630); //01-3630.AUD	Who the hell bankrolls your operation?
			KIA_Play_Actor_Dialogue(kActorGrigorian, 1450); //11-1450.AUD	We have a number of anonymous donors. People with resources and sources.
			KIA_Play_Actor_Dialogue(kActorSteele, 3640);  // such as
			KIA_Play_Actor_Dialogue(kActorGrigorian, 1460); //11-1460.AUD	So anonymous even I don't know who they are.
			KIA_Play_Actor_Dialogue(kActorSteele, 3650); //01-3650.AUD	I almost believe you.
		}
		break;
	case kClueAnimalMurderSuspect:
		KIA_Play_Photograph(7);
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 4080); //99-4080.AUD	He looks familiar.
		}
		break;
	case kClueMilitaryBoots:
		KIA_Play_Photograph(8);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 4110);
		break;
	case kClueOuterDressingRoom:
		KIA_Play_Photograph(15);
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagNR07McCoyIsCop)
			|| Game_Flag_Query(kFlagDektoraIdentified)) {
				Actor_Says(kActorMcCoy, 7960, 3); //00-7960.AUD	Dektora?
			} else {
				KIA_Play_Actor_Dialogue(kActorVoiceOver, 4090); //99-4090.AUD	She looks familiar.
			}
		}
		break;
	case kCluePhotoOfMcCoy1:
		KIA_Play_Photograph(17);
		break;
	case kCluePhotoOfMcCoy2:
		KIA_Play_Photograph(18);
		break;
	case kClueEarlyQAndLucy:
		KIA_Play_Photograph(1);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 4260);
		break;
	case kClueClovisFlowers:
		KIA_Play_Photograph(3);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 4230);
		break;
	case kClueLucyWithDektora:
		KIA_Play_Photograph(2);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 4040);
		break;
	case kClueWomanInAnimoidRow:
		KIA_Play_Photograph(21);
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagNR07McCoyIsCop)
			|| Game_Flag_Query(kFlagDektoraIdentified)) {
				Actor_Says(kActorMcCoy, 7960, 3); //00-7960.AUD	Dektora?
			} else if (Game_Flag_Query(kFlagGuzzaIsStupid)
			&& Game_Flag_Query(kFlagDektoraIsReplicant)) {
				KIA_Play_Actor_Dialogue(kActorVoiceOver, 4090); //99-4090.AUD	She looks familiar.
			} else {
				Actor_Says(kActorMcCoy, 8935, 3);
			}
		}
		break;
	case kClueScorpions:
		KIA_Play_Photograph(22);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 4180); //99-4180.AUD	Scorpions.
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagAR02ScorpionsChecked)) {
				KIA_Play_Actor_Dialogue(kActorVoiceOver, 4200); //99-4200.AUD	Where have I seen those before?
			}
		}
		break;
	case kClueStrangeScale2:
		KIA_Play_Photograph(23);
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 8830); //00-8830.AUD	A strange scale.
		}
		break;
	case kClueChinaBarSecurityCamera:
		KIA_Play_Photograph(24);
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 6975); //00-6975.AUD	Interesting.
		}
		break;
	case kClueIzo:
		KIA_Play_Photograph(26);
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 4170); //99-4170.AUD	I've seen that guy around town.
		}
		break;
	case kClueGuzza:
		KIA_Play_Photograph(27);
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 4210); //99-4210.AUD	Guzza?
		}
		break;
	case kClueChinaBarSecurityDisc:
		KIA_Play_Slice_Model(kModelAnimationVideoDisc);
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 4545); //00-4545.AUD	You got any discs from that camera?
			KIA_Play_Actor_Dialogue(kActorHawkersBarkeep, 110); // 32-0110.AUD	You've been a good customer, so I'll bent the rules just this once and tell you.
			KIA_Play_Actor_Dialogue(kActorHawkersBarkeep, 170); //32-0170.AUD	The truth ain't gonna do you no good.
			KIA_Play_Actor_Dialogue(kActorHawkersBarkeep, 180); //32-0180.AUD	But if you're gonna sit there until I cough it up, well, here it is.
		}
		break;
	case kClueScorpionbox:
		KIA_Play_Photograph(0);
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagAR02ScorpionsChecked)) {
				KIA_Play_Actor_Dialogue(kActorVoiceOver, 4190); //99-4190.AUD	Where have I seen that before?
			}
		}
		break;
	case kClueTyrellSecurityPhoto:
		KIA_Play_Photograph(28);
		break;
	case kClueChinaBar:
		KIA_Play_Photograph(19);
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagNR07McCoyIsCop)
			|| Game_Flag_Query(kFlagDektoraIdentified)) {
				Actor_Says(kActorMcCoy, 7960, 3); //00-7960.AUD	Dektora?
			} else if (Game_Flag_Query(kFlagGuzzaIsStupid)
			&& Game_Flag_Query(kFlagDektoraIsReplicant)) {
				KIA_Play_Actor_Dialogue(kActorVoiceOver, 4090); //99-4090.AUD	She looks familiar.
			} else {
				Actor_Says(kActorMcCoy, 8935, 3);
			}
		}
		break;
	case kCluePlasticExplosive:
		KIA_Play_Photograph(32);
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 8890); //00-8890.AUD	A bomb.
		}
		break;
	case kClueDogCollar2:
		KIA_Play_Photograph(30);
		if (!_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 4160);
		} else {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 8790); //00-8790.AUD	A dog collar.
		}
		break;
	case kClueKingstonKitchenBox2:
		KIA_Play_Photograph(29);
		if (_vm->_cutContent) {
			if (Game_Flag_Query(kFlagHC04Visited)) {
				KIA_Play_Actor_Dialogue(kActorVoiceOver, 4140); //99-4140.AUD	Kingston Kitchens. That's down at Hawker's Circle.
			} else {
				KIA_Play_Actor_Dialogue(kActorVoiceOver, 4150); //99-4150.AUD	Kingston Kitchens. Where have I heard that before?
			}
		} else if (Query_Difficulty_Level() == kGameDifficultyEasy) {
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 4140);
		} else {
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 4150);
		}
		break;
	case kClueCrystalsCigarette:
		KIA_Play_Slice_Model(kModelAnimationCrystalsCigarette);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 1770);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 1150);
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 1160);
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 1170);
		}
		if (!_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 1180);
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 1190);
		}
		break;
	case kClueSpinnerKeys:
		KIA_Play_Slice_Model(kModelAnimationSpinnerKeys);
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 1720); //00-1720.AUD	Any of your Spinners up and running?
			KIA_Play_Actor_Dialogue(kActorCrazylegs, 20); //09-0020.AUD	Uh… Sure, got one up on the roof.
			KIA_Play_Actor_Dialogue(kActorCrazylegs, 30); //09-0030.AUD	A real beaut. Ain’t a cheap ride, though, I’ll tell you right now.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 1725); //00-1725.AUD	I gotta take it for a test drive.
		}
		break;
	case kClueExpertBomber:
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 730);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 740);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 750);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 760); //99-0760.AUD	And that expertise could only come with extensive on-the-job Off-World training.
		break;
	case kClueAmateurBomber:
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 670);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 680);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 700);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 710); //99-0710.AUD	If my instincts were right, he was the same joker who lit up the Tyrell Building.
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 720);
		break;
	case kClueVKLucyReplicant:
		KIA_Play_Actor_Dialogue(kActorAnsweringMachine, 420);
		KIA_Play_Actor_Dialogue(kActorAnsweringMachine, 430);
		break;
	case kClueVKLucyHuman:
		KIA_Play_Actor_Dialogue(kActorAnsweringMachine, 420);
		KIA_Play_Actor_Dialogue(kActorAnsweringMachine, 440);
		break;
	case kClueLucyInterview:
		KIA_Play_Actor_Dialogue(kActorMcCoy, 1645); //00-1645.AUD	Why’d they kill Runciter’s animals?
		KIA_Play_Actor_Dialogue(kActorLucy, 240); //06-0240.AUD	I didn’t want them to. But father, he was so angry.
		KIA_Play_Actor_Dialogue(kActorLucy, 250); //06-0250.AUD	And Sadik said Mr. Runciter deserved it for treating me that way.
		if (!_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 1675); //00-1675.AUD	Who else was there that night?
		}
		KIA_Play_Actor_Dialogue(kActorLucy, 260); //06-0260.AUD	It’s so funny. I’m worth less than those animals.
		KIA_Play_Actor_Dialogue(kActorLucy, 270); //06-0270.AUD	I guess I should hate them. But I don’t.
		if (_vm->_cutContent) {
			if (!Actor_Clue_Query(kActorMcCoy, kClueLabCorpses)) {
				KIA_Play_Actor_Dialogue(kActorMcCoy, 1665); //00-1665.AUD	So, all the animals were real?
				if (!Game_Flag_Query(kFlagRunciterIsReplicant)) {
					KIA_Play_Actor_Dialogue(kActorLucy, 280); //06-0280.AUD	Mr. Runciter also used to buy some of the… others.
					KIA_Play_Actor_Dialogue(kActorMcCoy, 1670); //00-1670.AUD	Artificial?
					KIA_Play_Actor_Dialogue(kActorLucy, 290); //06-0290.AUD	He used to tell me that he was protected.
					KIA_Play_Actor_Dialogue(kActorLucy, 300); //06-0300.AUD	That they came from somebody close to the source.
				} else {
					KIA_Play_Actor_Dialogue(kActorLucy, 1130); //06-1130.AUD	Uh-huh.
				}
			}
		}
		KIA_Play_Actor_Dialogue(kActorMcCoy, 1675); //00-1675.AUD	Who else was there that night?
		KIA_Play_Actor_Dialogue(kActorLucy, 310); //06-0310.AUD	Father and uncle Zuben.
		break;
	case kClueMoonbusReflection:
		KIA_Play_Photograph(35);
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 8705); //00-8705.AUD	That's damn strange.
		}
		break;
	case kClueMcCoyAtMoonbus:
		KIA_Play_Photograph(36);
		if (_vm->_cutContent) {
			if (Actor_Clue_Query(kActorMcCoy, kClueMoonbusReflection)) {
				KIA_Play_Actor_Dialogue(kActorVoiceOver, 4250); //99-4250.AUD	That's not me.
				KIA_Play_Actor_Dialogue(kActorVoiceOver, 4010); //99-4010.AUD	A cardboard cutout or maybe a mannequin.
				KIA_Play_Actor_Dialogue(kActorVoiceOver, 4020); //99-4020.AUD	I didn't know what it was but I did know it wasn't me.
			} else {
				KIA_Play_Actor_Dialogue(kActorVoiceOver, 4240);
			}
		} else {
			// original re-uses the "That can't be me" from the ESPER
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 4240);
		}
		break;
	case kClueClovisAtMoonbus:
		KIA_Play_Photograph(37);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 4220);
		break;
	case kClueSadikAtMoonbus:
		KIA_Play_Photograph(38);
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 4170);
		}
		break;
	case kClueRachaelInterview:
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 5355); //00-5355.AUD	Fair enough. I wanted to ask about Marcus Eisenduller.
			KIA_Play_Actor_Dialogue(kActorRachael, 590); //57-0590.AUD	I can't tell you who killed him, if that's what you're asking.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 5360); //00-5360.AUD	We've already got a suspect.
		}
		KIA_Play_Actor_Dialogue(kActorMcCoy, 5365); //00-5365.AUD	What I want to know is why the killer would be interested in Replicant DNA information.
		if (!_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorRachael, 600);
			KIA_Play_Actor_Dialogue(kActorMcCoy, 5370);
		}
		KIA_Play_Actor_Dialogue(kActorRachael, 610); //57-0610.AUD	Your suspect is obviously a Replicant. A very dangerous one.
		break;
	case kClueTyrellInterview:
		KIA_Play_Actor_Dialogue(kActorTyrell, 0);
		KIA_Play_Actor_Dialogue(kActorTyrell, 10);
		KIA_Play_Actor_Dialogue(kActorTyrell, 20);
		KIA_Play_Actor_Dialogue(kActorTyrell, 30); //51-0030.AUD	That's hardly a death sentence. That's life.
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 5425); //00-5425.AUD	I thought you weren't meeting with any more Blade Runners today.
			KIA_Play_Actor_Dialogue(kActorTyrell, 40); //51-0040.AUD	Well I decided to make an exception, Mr. eh... McCoy, isn't it?
			KIA_Play_Actor_Dialogue(kActorTyrell, 50); //51-0050.AUD	You do understand the need for the Nexus-6 to have an identity.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 5435); //00-5435.AUD	I do see why a Replicant who has an identity would want to steal Eisenduller's files.
			KIA_Play_Actor_Dialogue(kActorTyrell, 60); //51-0060.AUD	Please, enlighten me.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 5440); //00-5440.AUD	They want more life.
			KIA_Play_Actor_Dialogue(kActorTyrell, 70); //51-0070.AUD	They're wasting their time.
		}
		break;
	case kClueRuncitersConfession1:
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 4770); //00-4770.AUD	You raped her.
			KIA_Play_Actor_Dialogue(kActorRunciter, 590); //-	15-0590.AUD	What? Who?
			KIA_Play_Actor_Dialogue(kActorMcCoy, 4775); //-	00-4775.AUD	Lucy.
			if (!Game_Flag_Query(kFlagRunciterIsReplicant)) {
				KIA_Play_Actor_Dialogue(kActorRunciter, 1180); //15-1180.AUD	I…
				KIA_Play_Actor_Dialogue(kActorMcCoy, 4780); //00-4780.AUD	Go ahead little man, lie to me. You'll only do it once.
				KIA_Play_Actor_Dialogue(kActorRunciter, 1170); //15-1170.AUD	No doubt I made a mistake.
				KIA_Play_Actor_Dialogue(kActorMcCoy, 4800); //00-4800.AUD	You son of a bitch she couldn't object.
				if (Game_Flag_Query(kFlagLucyIsReplicant)) {
					KIA_Play_Actor_Dialogue(kActorRunciter, 660); //15-0660.AUD	Please, I wouldn't-- you know I wouldn't have done that to a human girl. I swear it.
				} else {
					KIA_Play_Actor_Dialogue(kActorRunciter, 530); //15-0530.AUD	My precious one. She was my baby.
				}
				KIA_Play_Actor_Dialogue(kActorMcCoy, 2255); //00-2255.AUD	She was innocent, you bastard!
			} else {
				KIA_Play_Actor_Dialogue(kActorRunciter, 600); //-	15-0600.AUD	That's ridiculous. I—
				KIA_Play_Actor_Dialogue(kActorMcCoy, 4780); //-	00-4780.AUD	Go ahead little man, lie to me. You'll only do it once.
				KIA_Play_Actor_Dialogue(kActorRunciter, 610); //-	15-0610.AUD	You're no better! No better than those thugs who attacked me.
				KIA_Play_Actor_Dialogue(kActorMcCoy, 4785); //-	00-4785.AUD	Maybe not, but I'm better than you. She's a little girl.
				if (Game_Flag_Query(kFlagLucyIsReplicant)) {
					KIA_Play_Actor_Dialogue(kActorRunciter, 630); // 15-0630.AUD	She's... You know what she is.
					KIA_Play_Actor_Dialogue(kActorRunciter, 640); //15-0640.AUD	You know why Tyrell built her to look they way she does.
					KIA_Play_Actor_Dialogue(kActorMcCoy, 4790); // 00-4790.AUD	Bullshit!
					KIA_Play_Actor_Dialogue(kActorRunciter, 650); //15-0650.AUD	It's true.
					KIA_Play_Actor_Dialogue(kActorMcCoy, 4800); // 00-4800.AUD	You son of a bitch she couldn't object.
					KIA_Play_Actor_Dialogue(kActorRunciter, 660); // 15-0660.AUD	Please, I wouldn't-- you know I wouldn't have done that to a human girl. I swear it.
				} else {
					KIA_Play_Actor_Dialogue(kActorRunciter, 620); //15-0620.AUD	It wasn't like that.
					KIA_Play_Actor_Dialogue(kActorMcCoy, 4800); //00-4800.AUD	You son of a bitch she couldn't object.
				}
			}
		} else {
			KIA_Play_Actor_Dialogue(kActorRunciter, 630); // 15-0630.AUD	She's... You know what she is.
			KIA_Play_Actor_Dialogue(kActorRunciter, 640); //15-0640.AUD	You know why Tyrell built her to look they way she does.
			KIA_Play_Actor_Dialogue(kActorRunciter, 650); //15-0650.AUD	It's true.
		}
		break;
	default:
		break;
	}

	if (!_vm->_cutContent) {
		return;
	}

	// The rest are clues that were cut from the game.

	switch (clueId) {
	case kClueRuncitersConfession2:
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4625); //00-4625.AUD	Do you know anybody who works at Tyrell Corporation?
		KIA_Play_Actor_Dialogue(kActorRunciter, 210); //15-0210.AUD	A couple of genetic designers are old friends of mine.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4630); //00-4630.AUD	Such as?
		KIA_Play_Actor_Dialogue(kActorRunciter, 220); //15-0220.AUD	Well, you know how tight security is there.
		KIA_Play_Actor_Dialogue(kActorRunciter, 230);  //15-0230.AUD	It would be a betrayal of trusts to mention names. And they have nothing to do with this.
		break;
	case kClueRuncitersConfession3:
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4740); //00-4740.AUD	Lie to me. Go ahead. You'll only do it once.
		KIA_Play_Actor_Dialogue(kActorRunciter, 500); //15-0500.AUD	Animals. It was my animals. Some of them were...
		KIA_Play_Actor_Dialogue(kActorRunciter, 510); //15-0510.AUD	F-- fake. You won't-- You can't tell anyone. My reputation.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4745); //00-4745.AUD	Your reputation?!
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4750); //00-4750.AUD	Unbelievable.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4755); //00-4755.AUD	Was the tiger a fake?
		if (!Game_Flag_Query(kFlagRunciterIsReplicant)) {
			KIA_Play_Actor_Dialogue(kActorRunciter, 520); //15-0520.AUD	No! The tiger was real. I swear it.
			KIA_Play_Actor_Dialogue(kActorRunciter, 530);
			KIA_Play_Actor_Dialogue(kActorRunciter, 540);
		} else {
			KIA_Play_Actor_Dialogue(kActorRunciter, 9005); 
		}
		break;
	case kClueZubenIncept:
		KIA_Play_Slice_Model(kModelAnimationPhoto);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 4080); //99-4080.AUD	He looks familiar.
		break;
	case kClueClovisIncept:
		KIA_Play_Slice_Model(kModelAnimationPhoto);
		break;
	case kClueSadikIncept:
		KIA_Play_Slice_Model(kModelAnimationPhoto);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 4220); //99-4220.AUD	That guy sure gets around.
		break;
	case kClueDektoraIncept:
		KIA_Play_Slice_Model(kModelAnimationPhoto);
		KIA_Play_Actor_Dialogue(kActorMcCoy, 7690); //00-7960.AUD	Dektora?
		break;
	case kClueIzoIncept:
		KIA_Play_Slice_Model(kModelAnimationPhoto);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 4170); //99-4170.AUD	I've seen that guy around town.
		break;
	case kClueGordoIncept:
		KIA_Play_Slice_Model(kModelAnimationPhoto);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 4170); //99-4170.AUD	I've seen that guy around town.
		break;
	case kClueLucyIncept:
		KIA_Play_Slice_Model(kModelAnimationPhoto);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 4040); //99-4040.AUD	Hello there Lucy.
		break;
	case kClueMcCoyIncept:
		KIA_Play_Slice_Model(kModelAnimationPhoto);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 4240); //99-4240.AUD	That can't be me.
		break;
	case kClueInceptShotRoy:
		KIA_Play_Slice_Model(kModelAnimationPhoto);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 4080); //99-4080.AUD	He looks familiar.
		break;
	case kClueInceptShotsLeon:
		KIA_Play_Slice_Model(kModelAnimationPhoto);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 4170); //99-4170.AUD	I've seen that guy around town.
		break;
	case kClueCarWasStolen:
		KIA_Play_Actor_Dialogue(kActorMcCoy, 3615); //00-3615.AUD	You buy a vehicle lately? A black Sedan?
		KIA_Play_Actor_Dialogue(kActorDektora, 770); //03-0770.AUD	I wasn’t aware that was a crime.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 3720); //00-3720.AUD	Buying the car isn’t. Using the car in an animal murder, well...
		KIA_Play_Actor_Dialogue(kActorDektora, 780); //03-0780.AUD	Animal murder? That’s horrible.
		KIA_Play_Actor_Dialogue(kActorDektora, 790); //03-0790.AUD	I haven’t seen the car for two days. It was stolen the day after I bought it.
		break;
	case kClueGrigoriansResources:
		KIA_Play_Actor_Dialogue(kActorGrigorian, 320); //11-0320.AUD	We're not children, detective. We have resources.
		KIA_Play_Actor_Dialogue(kActorGrigorian, 330); //11-0330.AUD	Friends with access to vehicles, to escape routes.
		KIA_Play_Actor_Dialogue(kActorGrigorian, 340); //11-0340.AUD	The world is changing.
		break;
	case kClueCar:
		if (Game_Flag_Query(kFlagCarFound)) {
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 510); //99-0510.AUD	The car looked a lot like the one I'd been tracking.
		}
		if (Game_Flag_Query(kFlagKleinCarIdentityTalk)) {
			if (Actor_Query_Intelligence(kActorGordo) == 80) {
				KIA_Play_Actor_Dialogue(kActorVoiceOver, 520); //99-0520.AUD	The driver had been smart enough to pull the license plate.
				KIA_Play_Actor_Dialogue(kActorVoiceOver, 530); //99-0530.AUD	But the vehicle identification number was still there.
				KIA_Play_Actor_Dialogue(kActorVoiceOver, 540); //99-0540.AUD	If I ran it through the Mainframe back at the station, I could ID the owner.
			}
		}
		break;
	case kClueLicensePlateMatch:
		KIA_Play_Actor_Dialogue(kActorAnsweringMachine, 390); // 39-0390.AUD	Begin test.
		KIA_Play_Actor_Dialogue(kActorAnsweringMachine, 420); //39-0420.AUD	Positive result.
		KIA_Play_Actor_Dialogue(kActorAnsweringMachine, 470); //39-0470.AUD	End test.
		break;
	case kClueCrazylegsInterview2:
		if (Game_Flag_Query(kFlagCrazylegsTalkGrigorian)) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 1910); //00-1910.AUD	You know a man named Spencer Grigorian?
			KIA_Play_Actor_Dialogue(kActorCrazylegs, 790); //09-0790.AUD	Gotta be a thousand dealers in the city and you’re picking on me.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 2050); //00-2050.AUD	I know you know about CARS.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 1890); //00-1890.AUD	You recognize this?
			KIA_Play_Actor_Dialogue(kActorMcCoy, 4385); //00-4385.AUD	"Help these lost souls." Isn't that what it said?
			KIA_Play_Actor_Dialogue(kActorMcCoy, 2055); //00-2055.AUD	Grigorian was talking about friends with resources.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 2060); //00-2060.AUD	People who could set them up with vehicles.
			KIA_Play_Actor_Dialogue(kActorCrazylegs, 800); //09-0800.AUD	Give me a break, will ya? I’m just trying to make an honest buck.
		} else {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 1890); //00-1890.AUD	You recognize this?
			KIA_Play_Actor_Dialogue(kActorCrazylegs, 510); //09-0510.AUD	Sure I do. I get them printed out by the thousand.
			KIA_Play_Actor_Dialogue(kActorCrazylegs, 520); //09-0520.AUD	Kind of an old fashioned advertising approach.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 1920); //00-1920.AUD	Okay, you recognize this?
			KIA_Play_Actor_Dialogue(kActorMcCoy, 1925); //00-1925.AUD	This your handwriting, Crazy?
			KIA_Play_Actor_Dialogue(kActorCrazylegs, 530); //09-0530.AUD	A few customers I give the royal treatment to, you know. I’m a businessman.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 1930); //00-1930.AUD	I found this in the possession of a Replicant.
			KIA_Play_Actor_Dialogue(kActorCrazylegs, 540); //09-0540.AUD	Huh, what--?
			KIA_Play_Actor_Dialogue(kActorMcCoy, 1935); //00-1935.AUD	A Replicant.
			KIA_Play_Actor_Dialogue(kActorCrazylegs, 550); //09-0550.AUD	That’s impossible.
		}
		break;
	case kClueGordoBlabs:
		KIA_Play_Actor_Dialogue(kActorMcCoy, 6530); //00-6530.AUD	Somebody set me up, Gordo. Who’s behind it? Clovis?
		KIA_Play_Actor_Dialogue(kActorGordo, 1120); //02-1120.AUD	Clovis ain’t no zipper-head He’s capable of pulling a string or two.
		KIA_Play_Actor_Dialogue(kActorGordo, 1130); //02-1130.AUD	But no way he’s a one-man show.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 6990); //00-6990.AUD	Enlighten me.
		KIA_Play_Actor_Dialogue(kActorGordo, 1160); //02-1160.AUD	Shoot. All you gotta do is look to your own.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 6565); //00-6565.AUD	Someone inside the Blade Runner unit?
		break;
	case kClueGuzzaAgreesToMeet:
		KIA_Play_Actor_Dialogue(kActorGuzza, 1470); //04-1470.AUD	Okay, okay. How do we work this out? We can’t talk over the damn phone.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 6685); //00-6685.AUD	The sewers. I know you wanna be comfortable and I figured it’s kinda like your second home down there.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 6695); //00-6695.AUD	At the bottom of the old elevator there’s a gate.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 6700); //00-6700.AUD	Past it there’s a chamber. It’s got a round platform--
		KIA_Play_Actor_Dialogue(kActorGuzza, 1480); //04-1480.AUD	Yeah, I know it.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 6705); //00-6705.AUD	Be there! Alone. You’d better hold up your end or Bryant gets it all.
		break;
	case kClueWarRecordsGordoFrizz:
		KIA_Play_Actor_Dialogue(kActorSteele, 2920); //01-2920.AUD	Frizz was at the battle of the Gemini. Just like I suspected.
		KIA_Play_Actor_Dialogue(kActorSteele, 2930); //01-2930.AUD	The front line units were the first to receive Tyrell’s entertainment models.
		KIA_Play_Actor_Dialogue(kActorSteele, 2940); //01-2940.AUD	Singers who sounded like Frank Sinatra.
		KIA_Play_Actor_Dialogue(kActorSteele, 2950); //01-2950.AUD	Comedians whose shtick was ripped from everybody from Jerry Lewis to Eddie Murphy.
		KIA_Play_Actor_Dialogue(kActorSteele, 2960); //01-2960.AUD	They were supposed to build morale.
		KIA_Play_Actor_Dialogue(kActorSteele, 2970); //01-2970.AUD	But ol’ Gordo only short-circuited...
		KIA_Play_Actor_Dialogue(kActorSteele, 2980); //01-2980.AUD	emptying a shotgun into the audience after his act bombed.
		if (Actor_Query_Intelligence(kActorGordo) == 80) {
			KIA_Play_Actor_Dialogue(kActorSteele, 2990); //01-2990.AUD	They locked him up in a PoW shuttle but he escaped and hadn’t been heard from since.
		}
		break;
	case kClueGrigoriansResponse1:
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4275); //00-4275.AUD	I want to know about the people who were there.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4280); //00-4280.AUD	The Rastafarian and the Asian guy with the sunglasses.
		if (!Game_Flag_Query(kFlagIzoIsReplicant)) {
			KIA_Play_Actor_Dialogue(kActorGrigorian, 130); //11-0130.AUD	I didn't know the Rastafarian.
			KIA_Play_Actor_Dialogue(kActorGrigorian, 140); //11-0140.AUD	The Asian fellow was one of our ex members. Izo was his name.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 4305); //00-4305.AUD	How long did you know him for?
			KIA_Play_Actor_Dialogue(kActorGrigorian, 150); //11-0150.AUD	Let's see... I met him about five years ago.
			KIA_Play_Actor_Dialogue(kActorGrigorian, 160); //11-0160.AUD	He seemed so smart and balanced. He really wanted to help the Replicant people.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 4310); //00-4310.AUD	Then what?
			KIA_Play_Actor_Dialogue(kActorGrigorian, 170); //11-0170.AUD	He started associating with the more militant factions.
			KIA_Play_Actor_Dialogue(kActorGrigorian, 180); //11-0180.AUD	I was astounded when I heard he was supplying weapons to some of them.
		} else {
			KIA_Play_Actor_Dialogue(kActorGrigorian, 60); //11-0060.AUD	I don't know them.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 4285); //00-4285.AUD	Were they together?
			KIA_Play_Actor_Dialogue(kActorGrigorian, 70); //11-0070.AUD	They seemed to be. I saw them talking.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 4290); //00-4290.AUD	Before or after the explosion?
			KIA_Play_Actor_Dialogue(kActorGrigorian, 80); //11-0080.AUD	Before. I didn't see them at all after.
			KIA_Play_Actor_Dialogue(kActorGrigorian, 90); //11-0090.AUD	That's all I know, I swear. I wouldn't even know where to find explosives. I-- I'm not a violent man.
		}
		break;	
	case kClueGrigoriansResponse2:
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4260); //00-4260.AUD	You've been helping Reps, pal?
		KIA_Play_Actor_Dialogue(kActorGrigorian, 360); //11-0360.AUD	Through peaceful protest only.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4380); //00-4380.AUD	So talk to me about the Reps with the black Sedan. I found your note in their car.	
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4385); //00-4385.AUD	"Help these lost souls." Isn't that what it said?
		KIA_Play_Actor_Dialogue(kActorGrigorian, 370); //11-0370.AUD	We still have freedom of speech in this country. I can write whatever I please.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4395); //00-4395.AUD	How was Crazy-legs supposed to help them?
		KIA_Play_Actor_Dialogue(kActorGrigorian, 380); //11-0380.AUD	You'll have to ask him yourself. I'm not ashamed of what I did. And I'm sure he's not either.
		break;
	case kClueCrazylegGrovels:
		KIA_Play_Actor_Dialogue(kActorMcCoy, 1955); //00-1955.AUD	We’re taking a little drive downtown.
		KIA_Play_Actor_Dialogue(kActorCrazylegs, 580); //09-0580.AUD	Look, I know we can work out some kind of deal here.
		KIA_Play_Actor_Dialogue(kActorCrazylegs, 590); //09-0590.AUD	You like that Bishy Caddy, right? I’ll give it to you at the absolute lowest price.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 1990); //00-1990.AUD	Sounds like a bribe to me.
		KIA_Play_Actor_Dialogue(kActorCrazylegs, 600); //09-0600.AUD	Not a bribe. Just a gift. You know, out of friendship.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 1995); //00-1995.AUD	We ain’t friends, Crazy.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 1960); //00-1960.AUD	Give me your wheelchair’s ignition key and put your hands on top of your head.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 1980); //00-1980.AUD	Give me your phone.
		break;
	case kClueEarlyInterviewB1:
		KIA_Play_Actor_Dialogue(kActorMcCoy, 3515); //00-3515.AUD	You ever seen this woman before?
		if (Actor_Clue_Query(kActorMcCoy, kClueEarlyInterviewA)) {
			KIA_Play_Actor_Dialogue(kActorEarlyQ, 580);	//18-0580.AUD	Hey. That kinda looks like Hecuba. The one I lent the jewelry to?
			KIA_Play_Actor_Dialogue(kActorMcCoy, 3560); 
			KIA_Play_Actor_Dialogue(kActorEarlyQ, 590); //18-0590.AUD	That’s it.
		} else {
			Actor_Says(kActorEarlyQ, 560, 14); //18-0560.AUD	Nah, she ain’t one of mine.
		}
		if (Actor_Clue_Query(kActorMcCoy, kClueEarlyInterviewA)) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 3565); //00-3565.AUD	There hasn’t been an exotic dancer who used her real name since Jesus was a pup.
		} else {
			KIA_Play_Actor_Dialogue(kActorEarlyQ, 6995); //00-6995.AUD	That's not what I heard. You wanna set the record straight?
			KIA_Play_Actor_Dialogue(kActorMcCoy, 6985); //00-6985.AUD	Got the straight scoop for me or what?
		}
		KIA_Play_Actor_Dialogue(kActorEarlyQ, 600); //18-0600.AUD	(laughs) Okay, you got me. Dektora is the name on her work card. Let me tell you, General. She works it like a freaking house of fire.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 3570); //00-3570.AUD	I’m gonna want to talk to her. When is she up?
		KIA_Play_Actor_Dialogue(kActorEarlyQ, 620); //18-0620.AUD	Next, General. Have a couple of drinks, relax a little. But wait until her act is over. I don’t want to deprive a lady of her livelihood.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 3575); //00-3575.AUD	Oh, god forbid.
		break;
	case kClueEarlyInterviewB2:
		KIA_Play_Actor_Dialogue(kActorEarlyQ, 210); //18-0210.AUD	Hey, check out Dektora’s bearded boy-toy.
		KIA_Play_Actor_Dialogue(kActorEarlyQ, 220); //18-0220.AUD	Eh, he’s here all the time. You can be sure he ain’t coming around for the witty conversation.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 3430); //00-3430.AUD	What makes you think he’s a Replicant?
		KIA_Play_Actor_Dialogue(kActorEarlyQ, 240); //18-0240.AUD	He walked right by my dancers. Didn’t even pop a stiffy.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 3435); //00-3435.AUD	Maybe he swings another way.
		KIA_Play_Actor_Dialogue(kActorEarlyQ, 250); //18-0250.AUD	Oh, come on, McCoy. Have you seen my girls? Besides, I heard him talking to Dektora. They got friends who are gonna help them get Off-World. I’m telling you, they got a whole little Replicant love fest going on.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 3440); //00-3440.AUD	You hear him say anything else?
		KIA_Play_Actor_Dialogue(kActorEarlyQ, 280); //18-0280.AUD	No, General. I ain’t the nosy type.
		break;
	case kClueCrazylegsInterview3:
		KIA_Play_Actor_Dialogue(kActorGrigorian, 300); //11-0300.AUD	You support the cause, don't you Larry?
		KIA_Play_Actor_Dialogue(kActorCrazylegs, 1010); //09-1010.AUD	Hey, now don’t bring me into it.
		KIA_Play_Actor_Dialogue(kActorGrigorian, 420); //11-0420.AUD	You don't have to be afraid of the truth, Larry.
		KIA_Play_Actor_Dialogue(kActorCrazylegs, 1120); //09-1120.AUD	I don’t know what you’re talking about.
		KIA_Play_Actor_Dialogue(kActorGrigorian, 310); //11-0310.AUD	You don't have to be ashamed of your feelings tow---
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4345); //00-4345.AUD	Are you supplying vehicles for this venture, Crazy?
		KIA_Play_Actor_Dialogue(kActorCrazylegs, 1020); //09-1020.AUD	Well, for some kind of Underground Railroad why would I waste my inventory on that?
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4350); //00-4350.AUD	You tell me.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4360); //00-4360.AUD	Tell it straight or I'm gonna make sure you get the same as he gets. Full conspiracy, payable for 25.
		KIA_Play_Actor_Dialogue(kActorCrazylegs, 1030); //09-1030.AUD	I don’t care whether they’re Reps or humans as long as the chinyen is real.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4355); //00-4355.AUD	So you were ready to do business with the Reps who dropped by your place.
		if (Game_Flag_Query(kFlagDektoraIsReplicant)) {
			KIA_Play_Actor_Dialogue(kActorCrazylegs, 1040); //09-1040.AUD	Hey, I didn’t know what that broad was.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 2485); //00-2485.AUD	I’ve a hard time believing that.
		}
		KIA_Play_Actor_Dialogue(kActorCrazylegs, 1050); //09-1050.AUD	Look. Now I believe in laissez-faire.
		KIA_Play_Actor_Dialogue(kActorCrazylegs, 1060); //09-1060.AUD	I believe everyone can do what they gotta do. For a price, okay?
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4370); //00-4370.AUD	You're a real humanitarian.
		KIA_Play_Actor_Dialogue(kActorCrazylegs, 1070); //09-1070.AUD	Hey, McCoy, I’ve lost the use of my legs defending these goddamn people Off-World.
		KIA_Play_Actor_Dialogue(kActorCrazylegs, 1080); //09-1080.AUD	I don’t owe them anything.
		break;
	case kClueSightingZuben:
		KIA_Play_Actor_Dialogue(kActorSteele, 2820); //01-2820.AUD	I caught a glimpse of that big dumb log of a skin-job Zuben. The one that ditched McCoy.
		KIA_Play_Actor_Dialogue(kActorSteele, 2830); //01-2830.AUD	He must have known who I was because he high-tailed it down to the sewers.
		KIA_Play_Actor_Dialogue(kActorSteele, 2840); //01-2840.AUD	No way was I gonna soil my outfit just because McCoy can’t figure out which twin has the Toni.
		break;
	case kClueSightingGordo:
		KIA_Play_Actor_Dialogue(kActorSteele, 2860); //01-2860.AUD	I spotted the entertainment model. That little weasel in the loud coat.
		KIA_Play_Actor_Dialogue(kActorSteele, 2870); //01-2870.AUD	Loitering around the Chinatown District.
		KIA_Play_Actor_Dialogue(kActorSteele, 2880); //01-2880.AUD	You can bet he made a break for it as soon as he saw me.
		break;
	case kClueCrystalTestedCrazylegs:
		KIA_Play_Actor_Dialogue(kActorSteele, 3150); //01-3150.AUD	The rookie had it wrong. I put Crazylegs on the Machine and he came up human.
		KIA_Play_Actor_Dialogue(kActorSteele, 3020); //01-3020.AUD	Though knowing him, he might have been yanking my chain on purpose.
		break;
	case kClueCrystalArrestedCrazylegs:
		KIA_Play_Actor_Dialogue(kActorSteele, 3080); //01-3080.AUD	I don’t know what McCoy’s been smoking but Crazylegs ain’t no Rep.
		KIA_Play_Actor_Dialogue(kActorSteele, 3090); //01-3090.AUD	Hell, he can’t even walk.
		KIA_Play_Actor_Dialogue(kActorSteele, 3100); //01-3100.AUD	And I’ve never known Tyrell to build something that didn’t work right.
		KIA_Play_Actor_Dialogue(kActorSteele, 3160); //01-3160.AUD	But it turns out he had some Rep friends and he might have even sold them a car.
		KIA_Play_Actor_Dialogue(kActorSteele, 3170); //01-3170.AUD	I dragged his sorry ass downtown just on principle.
		KIA_Play_Actor_Dialogue(kActorSteele, 3180); //01-3180.AUD	Maybe if I lean on him, he will cough up the whereabouts of his little artificial buddies.
		break;
	case kClueCrystalTestedRunciter:
		KIA_Play_Actor_Dialogue(kActorSteele, 3190); //01-3190.AUD	Runciter read as human when I re-tested him.
		break;
	case kClueCrystalTestedBulletBob:
		KIA_Play_Actor_Dialogue(kActorSteele, 3000); //01-3000.AUD	Bullet Bob may be a grade A psycho but he ain’t no Replicant.
		KIA_Play_Actor_Dialogue(kActorSteele, 3030); //01-3030.AUD	Either way he’s got some explaining to do.
		break;
	case kClueCrystalRetiredRunciter1:
		KIA_Play_Actor_Dialogue(kActorSteele, 3210); //01-3210.AUD	The Runciter Rep went down nice and easy.	
		break;
		// Split this clue up into two pieces.
	case kClueCrystalRetiredRunciter2:
		if (Game_Flag_Query(kFlagRunciterTested)) {
			KIA_Play_Actor_Dialogue(kActorSteele, 3220); //01-3220.AUD	I’m tempted to split the bonus with McCoy since he did all the V-K work, but I’m getting real good at resisting temptation.
		}
		KIA_Play_Actor_Dialogue(kActorSteele, 3240); //01-3240.AUD	I just hope the lab boys don’t drag their feet on the bone marrow test.
		KIA_Play_Actor_Dialogue(kActorSteele, 3250); //01-3250.AUD	I got an electric bill to pay.
		break;
	case kClueCrystalRetiredBob:
		KIA_Play_Actor_Dialogue(kActorSteele, 3040); //01-3040.AUD	I took out the Bullet Bob Rep that ran the Gun Shop. Clean work. One shot and he dropped.
		KIA_Play_Actor_Dialogue(kActorSteele, 3050); //01-3050.AUD	Beats me why McCoy didn’t retire it, but I ain’t gonna share the bonus.
		KIA_Play_Actor_Dialogue(kActorSteele, 3010); //01-3010.AUD	I’m starting to think McCoy can’t run the Machine worth diddly.
		KIA_Play_Actor_Dialogue(kActorSteele, 3200); //01-3200.AUD	I got to teach McCoy how to run the Machine before he hurts somebody.
		KIA_Play_Actor_Dialogue(kActorSteele, 3060); //01-3060.AUD	Memo to the lieutenant. Try to hurry the lab boys along, will ya?
		KIA_Play_Actor_Dialogue(kActorSteele, 3070); //01-3070.AUD	They take forever with the bone marrow tests and I just got my cable bill.
		break;
	case kClueCrystalRetiredCrazylegs:
		KIA_Play_Actor_Dialogue(kActorSteele, 3110); //01-3110.AUD	Chalk one up for the good guys. The Crazylegs Larry Replicant was pretty clever.
		KIA_Play_Actor_Dialogue(kActorSteele, 3130); //01-3130.AUD	The wheelchair almost had me fooled, but if there’s one thing the rookie knows how to do is spot a skin-job.
		KIA_Play_Actor_Dialogue(kActorSteele, 3140); //01-3140.AUD	Let’s hope the lab boys don’t sit on the bone marrow test. My phone bill is due next week.
		break;
	case kClueDektoraConfession:
		KIA_Play_Actor_Dialogue(kActorMcCoy, 1915); //00-1915.AUD	You sell a black Sedan a few days ago?
		KIA_Play_Actor_Dialogue(kActorCrazylegs, 820); //09-0820.AUD	Black Sedan? Hey, I got standards. If it ain’t Sporty, I got no room for it.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 2075); //00-2075.AUD	I’ve seen the registration. I know a woman bought it from you.
		KIA_Play_Actor_Dialogue(kActorCrazylegs, 830); //09-0830.AUD	Oh-- Ooh, that Sedan.
		KIA_Play_Actor_Dialogue(kActorCrazylegs, 840);//09-0840.AUD	Hey, look. A sexy blonde wants to pay top dollar for the ugliest car in the place…
		KIA_Play_Actor_Dialogue(kActorCrazylegs, 850);//09-0850.AUD	who am I to say no?
		KIA_Play_Actor_Dialogue(kActorMcCoy, 2080); //00-2080.AUD	Did you know who she was?
		KIA_Play_Actor_Dialogue(kActorCrazylegs, 860); //09-0860.AUD	No, but I’d like to know her in the biblical sense, if you catch what I’m saying.
		KIA_Play_Actor_Dialogue(kActorCrazylegs, 870); //09-0870.AUD	Look, Ray. It ain’t a crime for me to make a living.
		break;
	case kClueClovisOrdersMcCoysDeath:
		KIA_Play_Actor_Dialogue(kActorClovis, 650); //05-0650.AUD	So, what should we do with this detective. He’s been so persistent, so industrious.
		KIA_Play_Actor_Dialogue(kActorSadik, 370); //08-0370.AUD	You know what I would do, mon.
		KIA_Play_Actor_Dialogue(kActorClovis, 1320); //05-1320.AUD	Perhaps you’re right. It’s over.
		break;
	case kClueMcCoyRetiredGordo:
		if (Game_Flag_Query(kFlagMcCoyShotGordoHostage)) {
			KIA_Play_Actor_Dialogue(kActorSteele, 1080); //01-1080.AUD	I really must be sick. I actually live for those moments.
			if (Actor_Query_Intelligence(kActorSteele) == 70) {
				KIA_Play_Actor_Dialogue(kActorSteele, 1100); //01-1100.AUD	Pathetic. Maybe he wasn’t a combat model after all.
				KIA_Play_Actor_Dialogue(kActorSteele, 1110); //01-1110.AUD	Heard Tyrell was making a few lounge act versions. You know, for the troop shows Off-World.
			}
			KIA_Play_Actor_Dialogue(kActorSteele, 1140); //01-1140.AUD	Let’s call a uniform and have ‘em clean this up. Your vehicle close by?
		} else {
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 1440); //99-1440.AUD	All those bad jokes. It was only an entertainment model.
		}
		break;
	case kClueMcCoyRetiredZuben:
		KIA_Play_Actor_Dialogue(kActorGaff, 50); //53-0050.AUD	You V-K the mark before retirement?
		KIA_Play_Actor_Dialogue(kActorMcCoy, 695); //00-0695.AUD	Didn't have to.
		KIA_Play_Actor_Dialogue(kActorGaff, 60); //53-0060.AUD	That's why they call it “the magic”. 
		break;
	case kClueMcCoyRecoveredHoldensBadge:
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4015); //00-4015.AUD	I found Holden's badge.
		KIA_Play_Actor_Dialogue(kActorGuzza, 630); //04-0630.AUD	Damn. Let me guess, you found it in that hotel down in Chinatown.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4085); //00-4085.AUD	Yeah, someone from the department had already been through the room.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4090); //00-4090.AUD	I guess they just missed it.
		KIA_Play_Actor_Dialogue(kActorGuzza, 640); //04-0640.AUD	That's the old-timer's case. The one we brought back on contract.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4095); 
		KIA_Play_Actor_Dialogue(kActorGuzza, 680); 
		KIA_Play_Actor_Dialogue(kActorMcCoy, 8170); //00-8170.AUD	There you go.
		break;
	case kClueCrystalRetiredGordo:
		KIA_Play_Actor_Dialogue(kActorSteele, 1070); //01-1070.AUD	Guess whose killer instinct wasn’t quite killer enough.
		KIA_Play_Actor_Dialogue(kActorSteele, 1270); //01-1270.AUD	If you were just a little faster, the retirement money would have been yours.
		KIA_Play_Actor_Dialogue(kActorSteele, 1290); //01-1290.AUD	I better call this in. Your vehicle close by?
		break;
	case kClueSuspectDektora:
		KIA_Play_Actor_Dialogue(kActorSteele, 1510); //01-1510.AUD	That stripper you interviewed. She’s one of them.
		KIA_Play_Actor_Dialogue(kActorSteele, 1520); //01-1520.AUD	Figure it out! She must have made the call to Baker and that other Bozo.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 8320); //00-8320.AUD	Really?
		KIA_Play_Actor_Dialogue(kActorSteele, 1400); //01-1400.AUD	Something ain’t right. That setup underground? I didn’t see a V-K Machine down there.
		KIA_Play_Actor_Dialogue(kActorSteele, 1410); //01-1410.AUD	Baker wasn’t gonna take you downtown and he wasn’t gonna test you.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 3135); ///00-3135.AUD	No kidding.
		break;
	case kClueSightingDektora:
		KIA_Play_Actor_Dialogue(kActorSteele, 2890); //01-2890.AUD	I knew I’d seen her somewhere before, but I had to dig real deep to find it.
		KIA_Play_Actor_Dialogue(kActorSteele, 2900); //01-2900.AUD	Somebody had tried to bury the incept photos and files of all the Reps who came down on the moonbus.
		break;
	case kClueSightingSadikBradbury:
		KIA_Play_Actor_Dialogue(kActorClovis, 0); 
		KIA_Play_Actor_Dialogue(kActorSadik, 0); //08-0000.AUD	How you think he found us, mon?
		KIA_Play_Actor_Dialogue(kActorClovis, 20); //05-0020.AUD	One of the Design sub-cons must have talked.
		KIA_Play_Actor_Dialogue(kActorClovis, 30); //05-0030.AUD	Unstable personalities to say the least.
		if (Actor_Query_Intelligence(kActorSadik) == 70) {
			KIA_Play_Actor_Dialogue(kActorSadik, 10); //08-0010.AUD	I told you we should have blown up the whole block.
			KIA_Play_Actor_Dialogue(kActorClovis, 40); //05-0040.AUD	It would have created problems down the line.
			KIA_Play_Actor_Dialogue(kActorSadik, 10); //08-0020.AUD	We got problem now, mon.
		}
		KIA_Play_Actor_Dialogue(kActorSadik, 220); //08-0220.AUD	Clovis wants to see you. Bring you back into family.
		break;
	case kClueCrystalRetiredIzo:
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4825); //00-4825.AUD	What are you doing here?
		KIA_Play_Actor_Dialogue(kActorSteele, 1870); //01-1870.AUD	Tracking this piece of shit.
		KIA_Play_Actor_Dialogue(kActorSteele, 1910); //01-1910.AUD	I'll wait for the uniforms. Why don't you grab yourself a slice of quiche or something.
		break;
	case kClueMcCoyRetiredDektora:
		KIA_Play_Actor_Dialogue(kActorSteele, 1750); //01-1750.AUD	Been pretty busy haven’t you, Slim?
		KIA_Play_Actor_Dialogue(kActorSteele, 1760); //01-1760.AUD	You had to clear out everything else up here too.
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 180); //99-0180.AUD	Sometimes my trigger finger starts to itch.
		KIA_Play_Actor_Dialogue(kActorSteele, 2110); //01-2110.AUD	That's okay.
		if (!Game_Flag_Query(kFlagEarlyQDead)
		&& !Game_Flag_Query(kFlagNR04EarlyQStungByScorpions)) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 3820); //00-3820.AUD	Hope Early’s got insurance.
			KIA_Play_Actor_Dialogue(kActorSteele, 1770); //01-1770.AUD	Putz employs Replicants, he oughta expect the worst.
		}
		KIA_Play_Actor_Dialogue(kActorSteele, 1780); //01-1780.AUD	(sigh) Sorry I missed all the laughs.
		KIA_Play_Actor_Dialogue(kActorSteele, 1740); //01-1740.AUD	Come on, let’s blow while the getting's good.
		KIA_Play_Actor_Dialogue(kActorSteele, 140); //01-0140.AUD	Maybe Guzza's got some answers about those guys who grabbed you up.
		break;
	case kClueMcCoyRetiredLucy:
		KIA_Play_Actor_Dialogue(kActorMcCoy, 1560); //00-1560.AUD	Commerce is our business.
		KIA_Play_Actor_Dialogue(kActorSteele, 90); ////01-0090.AUD	Just another stroll in the park.
		if (Actor_Query_Intelligence(kActorSteele) == 70) {
			KIA_Play_Actor_Dialogue(kActorSteele, 100); //01-0100.AUD	Unless Tyrell can design a faster brain processor, I’m gonna get pretty damn bored with this gig.
		}
		KIA_Play_Actor_Dialogue(kActorMcCoy, 1575); //00-1575.AUD	You don’t feel bad about juicing a little girl?
		KIA_Play_Actor_Dialogue(kActorSteele, 130); //01-0130.AUD	Let’s go find your Spinner. Report in.
		KIA_Play_Actor_Dialogue(kActorSteele, 140); //01-0140.AUD	Maybe Guzza's got some answers about those guys who grabbed you up.
		break;
	case kClueSightingClovis:
		KIA_Play_Actor_Dialogue(kActorMcCoy, 5745); //00-5745.AUD	Where’s Clovis now?
		if (!Game_Flag_Query(kFlagLutherLanceIsReplicant)) {
			KIA_Play_Actor_Dialogue(kActorLuther, 340); //10-0340.AUD	Clovis has gone to see Eldon.
		} else {
			KIA_Play_Actor_Dialogue(kActorLance, 240); //13-0240.AUD	Gone to have a little heart to heart with Eldon.
		}
		KIA_Play_Actor_Dialogue(kActorLuther, 280); //10-0280.AUD	We showed him how to get in through the basement.
		break;
	case kClueMoonbus2:
		KIA_Play_Actor_Dialogue(kActorMcCoy, 5390); //00-5390.AUD	You heard about the moonbus hijacking?
		KIA_Play_Actor_Dialogue(kActorMcCoy, 5395); //00-5395.AUD	Yeah, I guess you would have. 50 people dead.
		KIA_Play_Actor_Dialogue(kActorRachael, 630); // 57-0630.AUD	You can't blame--
		KIA_Play_Actor_Dialogue(kActorRachael, 650); //57-0650.AUD	They-- There are safeguards in the design.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 5415); //00-5415.AUD	Yeah, I've seen the data. Implanted memories. A four-year lifespan.
		break;
	case kClueEarlyInterviewA:
		KIA_Play_Actor_Dialogue(kActorMcCoy, 3505); //00-3505.AUD	You buy some jewelry at an auction recently? Real old elite stuff?
		KIA_Play_Actor_Dialogue(kActorEarlyQ, 440); //18-0440.AUD	Eh, those pieces ain’t hot. I got the papers to prove it. I picked them up at a legitimate auction. Cost me nearly a pound of flesh too.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 3535); //00-3535.AUD	You give this stuff to a girlfriend, Early?
		KIA_Play_Actor_Dialogue(kActorEarlyQ, 460); //18-0460.AUD	You kiddin’? I ain’t that stupid. No, no, no, no. I was letting one of my dancers use the stuff in her act. Kind of a tribute to the ancient swamp lands, you know what I mean?
		KIA_Play_Actor_Dialogue(kActorMcCoy, 3540); //00-3540.AUD	Which dancer?
		KIA_Play_Actor_Dialogue(kActorEarlyQ, 490); //18-0490.AUD	Hecuba. She’s going on in a few.
		KIA_Play_Actor_Dialogue(kActorEarlyQ, 500);	//18-0500.AUD	She’s one of my biggest earners too. She ain’t in any trouble now, is she?
		break;
	case kClueBobRobbed:
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4965); //00-4965.AUD	I hear you've been waving guns around on Animoid Row.
		KIA_Play_Actor_Dialogue(kActorBulletBob, 470); //14-0470.AUD	Who's been telling you that crap? That lying Egyptian snake oil salesman?
		KIA_Play_Actor_Dialogue(kActorMcCoy, 5035); //00-5035.AUD	Hasan?
		if (Game_Flag_Query(kFlagBulletBobIsReplicant)) {
			KIA_Play_Actor_Dialogue(kActorBulletBob, 480); //14-0480.AUD	That's the one. I should have popped him when I had the chance. 
		}
		KIA_Play_Actor_Dialogue(kActorBulletBob, 490); //14-0490.AUD	You want to know what really happened?
		if (!Game_Flag_Query(kFlagBulletBobIsReplicant)) {
			KIA_Play_Actor_Dialogue(kActorBulletBob, 500); //14-0500.AUD	I wanted to get my daughter a present for her birthday, right?
		}
		KIA_Play_Actor_Dialogue(kActorBulletBob, 510); //14-0510.AUD	I bought an Iguana from that crook Hasan.
		KIA_Play_Actor_Dialogue(kActorBulletBob, 520); //14-0520.AUD	And the damn thing ran out of juice...
		KIA_Play_Actor_Dialogue(kActorBulletBob, 530); //14-0530.AUD	just two days after I plucked down a shitload of chinyen.
		KIA_Play_Actor_Dialogue(kActorBulletBob, 540); //14-0540.AUD	Son of a bitch wouldn't give me a refund. So I threatened to burn down his shop.
		break;
	case kClueMcCoysDescription:
		KIA_Play_Actor_Dialogue(kActorDispatcher, 0); //38-0000.AUD	Attention all units. All points bulletin has been issued for: Ray McCoy. Formerly BR-61661.
		KIA_Play_Actor_Dialogue(kActorDispatcher, 10); //38-0010.AUD	Confirm one civilian kill. Izo. Considered armed and dangerous.
		KIA_Play_Actor_Dialogue(kActorDispatcher, 20); //38-0020.AUD	Photo and descriptive information available on ESPER.
		break;
	case kClueLabAnalysisGoldChain:
		KIA_Play_Slice_Model(kModelAnimationMaggieBracelet);
		KIA_Play_Actor_Dialogue(kActorMcCoy, 115); //00-0115.AUD	Maggie.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 5270); //00-5270.AUD	Hell of a coincidence.
		break;
	case kClueWantedPoster:
		KIA_Play_Slice_Model(kModelAnimationGrigoriansNote);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 4080);	//99-4080.AUD	He looks familiar.
		break;
		// This clue uses dialogue that I put together for the Early Q earrest scene.
	case kClueEarlyAttemptedToSeduceLucy:
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4760); // 00-4760.AUD	About the girl
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4765); // 00-4765.AUD	Lucy. I know what you did.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 840); //00-0840.AUD	Did you hear me?
		KIA_Play_Actor_Dialogue(kActorEarlyQ, 540); //18-0540.AUD	Of course, she ain’t half bad looking. My pappy always used to say ‘if there’s grass on the field, it’s time to play ball’.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4800); //00-4800.AUD	You son of a bitch she couldn't object.
		KIA_Play_Actor_Dialogue(kActorEarlyQ, 50); //18-0050.AUD	Hey, hey, I don’t hassle you about your private life.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 2255); //00-2255.AUD	She was innocent, you bastard!
		KIA_Play_Actor_Dialogue(kActorEarlyQ, 530); //18-0530.AUD	This ain’t no daycare center, General.
		break;
	case kClueMcCoyLetZubenEscape:
		KIA_Play_Actor_Dialogue(kActorGaff, 80); //53-0080.AUD	Your target give you the slip?
		KIA_Play_Actor_Dialogue(kActorGaff, 90); //53-0090.AUD	What happened, McCoy? You feel sorry for it?
		KIA_Play_Actor_Dialogue(kActorMcCoy, 705); //00-0705.AUD	My game must have been off.
		break;
		// This clue uses dialogue that I put together for the Bullet Bob replicant path when he tries to shoot you.
	case kClueBobShotInSelfDefense:
		KIA_Play_Actor_Dialogue(kActorMcCoy, 6865); //00-6865.AUD	You're a Replicant.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 840); //00-0840.AUD	Did you hear me?
		KIA_Play_Actor_Dialogue(kActorMcCoy, 180); //00-0180.AUD	Bob?
		KIA_Play_Actor_Dialogue(kActorBulletBob, 1270); //14-1270.AUD	(Laughing) I guess I picked the right line of work.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 490); //00-0490.AUD	Suck on this, skin-job!
		break;
		// This clue uses the dialogue that I added in for when you find the form at the homeless mans place.
	case kCluePoliceWeaponUsed:
		KIA_Play_Slice_Model(kModelAnimationAmmoType00);
		KIA_Play_Actor_Dialogue(kActorMcCoy, 8705); //00-8705.AUD	That's damn strange.
		break;
		// These next set of clues may be incriminating but this is near the end of act 4 and in act 5 when McCoy is at the point of no return.
	case kClueMcCoyKilledRunciter1:
		KIA_Play_Actor_Dialogue(kActorMcCoy, 6865); //00-6865.AUD	You're a Replicant.
		KIA_Play_Actor_Dialogue(kActorRunciter, 1070); //15-1070.AUD	I'm not a Replicant for heaven's sakes.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 1610); //00-1610.AUD	Yes. You are.
		KIA_Play_Actor_Dialogue(kActorRunciter, 600); //15-0600.AUD	That's ridiculous. I--.
		KIA_Play_Actor_Dialogue(kActorRunciter, 720); //15-0720.AUD	I have nothing more to say to you, detective.
		KIA_Play_Actor_Dialogue(kActorRunciter, 9020); //15-9020.AUD	Argh!
		break;
	case kClueMcCoyKilledRunciter2:
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 2050); //99-2050.AUD	Clovis wanted Runciter to suffer, but I wanted him dead.
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 2080); //99-2080.AUD	I’d done the city a favor.
		if (!Game_Flag_Query(kFlagMcCoyShotRunciter)) {
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 920); //99-0920.AUD	Easy money.
		} else {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 8508); //00-8508.AUD	No retirement swag.
		}
		break;
	case kClueMcCoyBetrayal:
		KIA_Play_Actor_Dialogue(kActorSteele, 400); //01-0400.AUD	How could you… double cross me?
		KIA_Play_Actor_Dialogue(kActorMcCoy, 2165); //00-2165.AUD	You should have left them alone.
		KIA_Play_Actor_Dialogue(kActorSteele, 410); //01-0410.AUD	My job… had my orders.
		KIA_Play_Actor_Dialogue(kActorSteele, 420); //01-0420.AUD	Eat shit, Slim.
		break;
	case kClueMcCoyShotGuzza:
		KIA_Play_Actor_Dialogue(kActorGuzza, 1220); //04-1220.AUD	Who the hell do you think you’re kidding, McCoy? You’re gonna fry!
		KIA_Play_Actor_Dialogue(kActorSadik, 360); //08-0360.AUD	The Hunter? He do us a favor, mon. He bagged us a traitor.
		KIA_Play_Actor_Dialogue(kActorSadik, 380); //08-0380.AUD	You better than I thought, mon.
		KIA_Play_Actor_Dialogue(kActorClovis, 660); //05-0660.AUD	Brother! You’ve killed a human. There’s no going back now.
		KIA_Play_Actor_Dialogue(kActorClovis, 680); //05-0680.AUD	You’ve wasted much precious time already.
		KIA_Play_Actor_Dialogue(kActorClovis, 690); //05-0690.AUD	No more choices, Ray McCoy.
		KIA_Play_Actor_Dialogue(kActorClovis, 700); //05-0700.AUD	Meet us at the moonbus and together we will face the tigers that wait in the night’s forest.
		break;
	case kClueMoonbusCloseup:
		KIA_Play_Actor_Dialogue(kActorMcCoy, 2315); //00-2315.AUD	The moonbus up and running yet?
		KIA_Play_Actor_Dialogue(kActorSadik, 210); //08-0210.AUD	All it needs is fuel.
		KIA_Play_Actor_Dialogue(kActorSadik, 240); //08-0240.AUD	There got to be something around here, mon.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 730); //00-0730.AUD	What are we talking about?
		KIA_Play_Actor_Dialogue(kActorSadik, 250); //08-0250.AUD	Old reactor cores. Anything still got a glow.
		KIA_Play_Actor_Dialogue(kActorSadik, 260); //08-0260.AUD	The generator? It take almost anything.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 2750); //00-2750.AUD	Okay, I get the picture.
		break;
		// This clue is the dialogue when Sadik shoots Guzza in the sewers.
	case kClueSadiksGun:
		KIA_Play_Actor_Dialogue(kActorGuzza, 1150); //04-1150.AUD	You might as well give it up, Clovis. You and your people don’t have a chance.
		KIA_Play_Actor_Dialogue(kActorClovis, 600); //05-0600.AUD	We stand a greater chance of success than you, Lieutenant.
		if (Game_Flag_Query(kFlagGuzzaIsStupid)) {
			KIA_Play_Actor_Dialogue(kActorGuzza, 1160); //04-1160.AUD	McCoy and I were just talking about how to get you guys out of your jam.
			KIA_Play_Actor_Dialogue(kActorGuzza, 1170); //04-1170.AUD	We came up with a plan.
			KIA_Play_Actor_Dialogue(kActorGuzza, 1180); //04-1180.AUD	But you got to show yourself first. We-- we got to do this in person.
		}	
		if (!Game_Flag_Query(kFlagGuzzaIsStupid)) {
			KIA_Play_Actor_Dialogue(kActorGuzza, 1190); //04-1190.AUD	Without me, you for sure ain’t going nowhere.
		}
		KIA_Play_Actor_Dialogue(kActorClovis, 610); //05-0610.AUD	(laughs) And if I told you that Sadik has a pulse rifle trained right at your heart?
		KIA_Play_Actor_Dialogue(kActorClovis, 620); //05-0620.AUD	Lieutenant, we have everything we need. And that doesn’t include you.
		if (Game_Flag_Query(kFlagGuzzaIsStupid)) {
			KIA_Play_Actor_Dialogue(kActorGuzza, 1200); //04-1200.AUD	Too bad. We were becoming such good friends.
		} else {
			KIA_Play_Actor_Dialogue(kActorGuzza, 9000); //004-9000.AUD	Help!
		}
		KIA_Play_Actor_Dialogue(kActorClovis, 630); //05-0630.AUD	"Whatever is born of mortal birth, must be consumed with the earth."
		KIA_Play_Actor_Dialogue(kActorClovis, 640); //05-0640.AUD	"To rise from Generation free, then what have I to do with thee?"
		KIA_Play_Actor_Dialogue(kActorGuzza, 1210); //04-1210.AUD	Kiss… my… ass!
		break;
		// This is of some dialogue that I slightly modified where Runciters tells McCoy what the the suspects motives were and Runcitter confesses that he wsihed they killed him because
		// his life is now ruined.
	case kClueRunciterConfession1:
		KIA_Play_Actor_Dialogue(kActorMcCoy, 5760);
		if (!Game_Flag_Query(kFlagLutherLanceIsReplicant)) {
			KIA_Play_Actor_Dialogue(kActorLuther, 370);
		}
		KIA_Play_Actor_Dialogue(kActorLance, 340); //13-0340.AUD	We just wanted to make some extra cash on the side.
		KIA_Play_Actor_Dialogue(kActorLance, 350); //13-0350.AUD	So, I sold Runciter some of Tyrell’s state of the art animals.
		KIA_Play_Actor_Dialogue(kActorLance, 360);  //13-0360.AUD	He was going to pawn them off as real.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 5840); 
		KIA_Play_Actor_Dialogue(kActorLance, 380); //13-0380.AUD	It was all just a coincidence.
		KIA_Play_Actor_Dialogue(kActorLance, 390); //13-0390.AUD	We just happened to be doing business with the same scumbag.
		break;
		// This the dialogue where Runciter confesses that he has a couple of friends who are genetic designers.
	case kClueRunciterConfession2:
		KIA_Play_Actor_Dialogue(kActorMcCoy, 7095); //00-7095.AUD	What do you think the deal was with Runciter and the twins?
		KIA_Play_Actor_Dialogue(kActorSebastian, 520); //56-0520.AUD	There were rumors that the twins were selling some of the animal prototypes to him.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 7180); //00-7180.AUD	Do you think that had something to do with their being fired?
		KIA_Play_Actor_Dialogue(kActorSebastian, 530); //56-0530.AUD	Dr. Tyrell doesn't like anyone going around behind his back.
		break;
		// This clue is not a sighting OF Bullet Bob, but instead is a sighting MADE by Bullet Bob. Specifically his observations of Runciter and his possible
		// illegal activities.
	case kClueSightingBulletBob:
		KIA_Play_Actor_Dialogue(kActorBulletBob, 0); //14-0000.AUD	That a .45 blaster under your coat or you're just happy to be here?
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4870); //00-4870.AUD	Ray McCoy, Rep Detect.
		KIA_Play_Actor_Dialogue(kActorBulletBob, 20); //14-0020.AUD	Blade Runner, huh?
		if (Game_Flag_Query(kFlagBulletBobIsReplicant)) {
			KIA_Play_Actor_Dialogue(kActorBulletBob, 40); //14-0040.AUD	I heard of you.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 4880); //00-4880.AUD	Is that right?
			KIA_Play_Actor_Dialogue(kActorBulletBob, 50); //14-0050.AUD	You ain't done much.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 4875); //00-4875.AUD	I just got assigned.
			KIA_Play_Actor_Dialogue(kActorBulletBob, 60); //14-0060.AUD	Guys like you get hurt real easy.
		} else {
			KIA_Play_Actor_Dialogue(kActorBulletBob, 30); //14-0030.AUD	How come I never heard of you?
			KIA_Play_Actor_Dialogue(kActorMcCoy, 4875); //00-4875.AUD	I just got assigned.
			KIA_Play_Actor_Dialogue(kActorBulletBob, 80); //14-0080.AUD	Yeah, I'm kind of buddies with Davy Holden. How's he doing?
			KIA_Play_Actor_Dialogue(kActorMcCoy, 4900); //00-4900.AUD	Word is he's gonna be okay.
			KIA_Play_Actor_Dialogue(kActorBulletBob, 90); //14-0090.AUD	That skin-job must have been pretty damn quick getting by Davy like that.
			KIA_Play_Actor_Dialogue(kActorBulletBob, 100); //14-0100.AUD	He's the best in the business.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 4905); //00-4905.AUD	He'll be back on the job soon.
		}
		break;
		// This a clue you receive if Zuben is spared and Crystal receives enough clues from you so she can track him down and retire him.
	case kClueCrystalRetiredZuben:
		KIA_Play_Actor_Dialogue(kActorSteele, 2820); //01-2820.AUD	I caught a glimpse of that big dumb log of a skin-job Zuben. The one that ditched McCoy.
		KIA_Play_Actor_Dialogue(kActorSteele, 2880); //01-2880.AUD	You can bet he made a break for it as soon as he saw me.
		KIA_Play_Actor_Dialogue(kActorSteele, 3050); //01-3050.AUD	Beats me why McCoy didn’t retire it, but I ain’t gonna share the bonus.
		KIA_Play_Actor_Dialogue(kActorSteele, 3240); //01-3240.AUD	I just hope the lab boys don’t drag their feet on the bone marrow test.
		KIA_Play_Actor_Dialogue(kActorSteele, 3070); //01-3070.AUD	They take forever with the bone marrow tests and I just got my cable bill.
		break;
	case kClueBobShotInColdBlood:
		KIA_Play_Actor_Dialogue(kActorMcCoy, 7125); //00-7125.AUD	He was murdered. Probably by a Replicant.
		break;
		// This is when McCoy asks human Izo about Grigorian and Izo insults and threatens McCoy to which McCoy replies with a couple of warnings.
	case kClueMcCoyWarnedIzo:
		KIA_Play_Actor_Dialogue(kActorIzo, 490); //07-0490.AUD	Don't you wish I gave a damn about what you think?
		KIA_Play_Actor_Dialogue(kActorMcCoy, 1205); //00-1205.AUD	I can make you give a damn..
		KIA_Play_Actor_Dialogue(kActorIzo, 500); //07-0500.AUD	(snickers) Let me give you a little word of advice, detective.
		KIA_Play_Actor_Dialogue(kActorIzo, 510); //07-0510.AUD	Stay out of my business.
		KIA_Play_Actor_Dialogue(kActorIzo, 520); //07-0520.AUD	More importantly stay out of my face.
		KIA_Play_Actor_Dialogue(kActorIzo, 530); //07-0530.AUD	All I'd have to do is make one vid-call and you would be shoveling shit Off-World for the rest of your career.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 1210); //00-1210.AUD	Talk to me like that some more and you'll be eating it.
		break;
		// The dialogue for when Sadik blows up Maggie.
	case kClueMcCoyRetiredSadik: 
		KIA_Play_Actor_Dialogue(kActorSadik, 60); //08-0060.AUD	You like my present, mon?
		KIA_Play_Actor_Dialogue(kActorMcCoy, 2240); //00-2240.AUD	You bastard! She was an innocent!
		KIA_Play_Actor_Dialogue(kActorSadik, 70); //08-0070.AUD	She a fake, mon. A machine. Like you!
		KIA_Play_Actor_Dialogue(kActorSadik, 80); //08-0080.AUD	Tyrell? He make her more doggy than dog, ya know?
		KIA_Play_Actor_Dialogue(kActorMcCoy, 2245); //00-2245.AUD	That-- that’s a lie!
		KIA_Play_Actor_Dialogue(kActorSadik, 90); //08-0090.AUD	You don’t remember it I’m thinking.
		KIA_Play_Actor_Dialogue(kActorSadik, 100); //08-0100.AUD	None of it. Them false memories. They really worked you good.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 2250); //00-2250.AUD	Come out and show yourself, you coward!
		break; 
		// The dialogue for when you pull your gun on the twins and shoot them when they are replicants.
	case kClueMcCoyRetiredLutherLance:
		KIA_Play_Actor_Dialogue(kActorMcCoy, 5720); //00-5720.AUD	Just a moment of your time, please.
		KIA_Play_Actor_Dialogue(kActorLuther, 80); //10-0080.AUD	I am sick and tired of people waving those things around.
		KIA_Play_Actor_Dialogue(kActorLance, 40); ////13-0040.AUD	Just give it up. You got no jurisdiction down here.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 8508); //00-8508.AUD	No retirement swag.
		break;
	case kClueCrystalVisitedRunciters:
		KIA_Play_Slice_Model(kModelAnimationCrystalsCigarette);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 1770); //99-1770.AUD	Lucky Strikes. Crystal's brand.
		break;
	case kClueCrystalVisitedChinatown:
		KIA_Play_Slice_Model(kModelAnimationCrystalsCigarette);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 1770); //99-1770.AUD	Lucky Strikes. Crystal's brand.
		break;
	case kClueSightingMcCoyRuncitersShop:
		KIA_Play_Slice_Model(kModelAnimationKnife);
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4165);
		break;
	case kClueMcCoyIsABladeRunner:
		KIA_Play_Actor_Dialogue(kActorGuzza, 950); //04-0950.AUD	Clovis is still gonna come gunning for me, kid.
		KIA_Play_Actor_Dialogue(kActorGuzza, 960); //04-0960.AUD	You and Crystal gotta take him down. Then my problems are over. Our problems are over.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 5935); //00-5935.AUD	That’s my job, Guzza. I’m still a Blade Runner.
		break;
	case kClueMcCoyHelpedDektora:
		KIA_Play_Actor_Dialogue(kActorMcCoy, 3840); //00-3840.AUD	(panting) Listen. Dektora, I wanna help.
		if (!Actor_Clue_Query(kActorDektora, kClueMcCoyHelpedDektora)) {
			KIA_Play_Actor_Dialogue(kActorDektora, 990);  ///03-0990.AUD	You say a lot of things, Mr. McCoy.
			KIA_Play_Actor_Dialogue(kActorDektora, 1000);  //03-1000.AUD	But you’re a Blade Runner. It’s hard to know what’s real.
		}
		KIA_Play_Actor_Dialogue(kActorMcCoy, 3845);  //00-3845.AUD	One of my associates is after you and your friends.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 2090); //03-2090.AUD	Oh.
		if (Game_Flag_Query(kFlagDektoraIsReplicant)) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 3850); //00-3850.AUD	I’m not sure I can hold her off much longer.
			KIA_Play_Actor_Dialogue(kActorDektora, 1010);  //03-1010.AUD	I’m not worried. She may kill some of us but not all of us. Clovis will see to that.
		} else {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 6535); //00-6535.AUD	I need to see Clovis ASAP.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 3870); //00-3870.AUD	Can you take me to him?
			if (!Actor_Clue_Query(kActorDektora, kClueMcCoyHelpedDektora)) {
				KIA_Play_Actor_Dialogue(kActorMcCoy, 2060);//03-2060.AUD	No.
			} else {
				KIA_Play_Actor_Dialogue(kActorMcCoy, 1070);
				KIA_Play_Actor_Dialogue(kActorDektora, 1080); //03-1080.AUD	Clovis will find you, when he’s ready.
			}
		}
		KIA_Play_Actor_Dialogue(kActorMcCoy, 3865); //00-3865.AUD	What’s Clovis looking for?
		if (!Actor_Clue_Query(kActorDektora, kClueMcCoyHelpedDektora)) {
			KIA_Play_Actor_Dialogue(kActorDektora, 1440); //03-1440.AUD	I don't see why you need to know that.
			if (Game_Flag_Query(kFlagDektoraIsReplicant)) {
				KIA_Play_Actor_Dialogue(kActorMcCoy, 3870); //00-3870.AUD	Can you take me to him?
				KIA_Play_Actor_Dialogue(kActorDektora, 2060); //03-2060.AUD	No.
			}
		} else {
			KIA_Play_Actor_Dialogue(kActorDektora, 1040); //03-1040.AUD	They are still my family. Clovis and Lucy..
			KIA_Play_Actor_Dialogue(kActorMcCoy, 3865);  //00-3865.AUD	What’s Clovis looking for?
			KIA_Play_Actor_Dialogue(kActorDektora, 1050); //03-1050.AUD	Information. Data. Four years isn’t enough time, Mr. McCoy.
			KIA_Play_Actor_Dialogue(kActorDektora, 1060);  //03-1060.AUD	If anyone deserves more than four years, it’s Clovis. If you could only meet him.
			if (Game_Flag_Query(kFlagDektoraIsReplicant)) {
				KIA_Play_Actor_Dialogue(kActorMcCoy, 3870); //00-3870.AUD	Can you take me to him?
				KIA_Play_Actor_Dialogue(kActorDektora, 1070);  //03-1070.AUD	I’m afraid that’s impossible right now.
				KIA_Play_Actor_Dialogue(kActorDektora, 1080); //03-1080.AUD	Clovis will find you, when he’s ready.
			}	
		}
		KIA_Play_Actor_Dialogue(kActorMcCoy, 3875); //00-3875.AUD	You’d better go now. Take the fire escape.
		KIA_Play_Actor_Dialogue(kActorDektora, 1090);  //03-1090.AUD	I… appreciate it, Mr. McCoy.
		break;
	case kClueMcCoyHelpedLucy:
		KIA_Play_Actor_Dialogue(kActorMcCoy, 1695); //00-1695.AUD	Lucy? Come on out. I’m not the hunter anymore.
		KIA_Play_Actor_Dialogue(kActorLucy, 350); //06-0350.AUD	I saw you with that woman who smokes.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 1705);  //00-1705.AUD	I have to deal with her just to keep up appearances. I can be more effective that way. 
		KIA_Play_Actor_Dialogue(kActorLucy, 360); //06-0360.AUD	She scares me.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 1710);  //00-1710.AUD	She’s being paid to kill your family.
		KIA_Play_Actor_Dialogue(kActorLucy, 370); //06-0370.AUD	I’ll tell them. What you did. That you helped me.
		break;
	case kClueMcCoyHelpedGordo:
		KIA_Play_Actor_Dialogue(kActorSteele, 1160); //01-1160.AUD	Dah! What the hell?! Now we’ll never catch it.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 3035); //00-3035.AUD	You were gonna shoot!
		KIA_Play_Actor_Dialogue(kActorMcCoy, 3045); //00-3045.AUD	You think Bryant is gonna keep you on if you start wasting civilians in the middle of the street?
		KIA_Play_Actor_Dialogue(kActorMcCoy, 3055); //00-3055.AUD	I just saved your job, Steele.
		KIA_Play_Actor_Dialogue(kActorSteele, 1210); //01-1210.AUD	We’d better call this in. Maybe we can seal off the sewers and get a search team out here. Your vehicle close by?
		break;
	case kClueMcCoyShotZubenInTheBack:
		KIA_Play_Actor_Dialogue(kActorMcCoy, 480); //00-0480.AUD	I'm McCoy, LPD Rep detect unit.
		KIA_Play_Actor_Dialogue(kActorZuben, 130); //19-0130.AUD	Rep detect?
		KIA_Play_Actor_Dialogue(kActorMcCoy, 485); //00-0485.AUD	Sometimes we're called Blade Runners.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 490); //00-0490.AUD	Suck on this, skin-job!
		break;
	case kClueZubenRunsAway:
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 4270); //99-4270.AUD	The guy dumped nu-sooch all over my coat and didn't even stick around to apologize. Looked like someone with a guilty conscience to me.
		break;
	case kClueMcCoyPulledAGun:
		KIA_Play_Actor_Dialogue(kActorCrazylegs, 480); //09-0480.AUD	Hey, keep your paws off that, Ray!
		KIA_Play_Actor_Dialogue(kActorMcCoy, 525); //00-0525.AUD	I've seen you before...
		KIA_Play_Actor_Dialogue(kActorCrazylegs, 540); //09-0540.AUD	Huh, what--?
		KIA_Play_Actor_Dialogue(kActorMcCoy, 7260); //00-7260.AUD	Didn't I see an incept tape at the—
		KIA_Play_Actor_Dialogue(kActorCrazylegs, 1120); //09-1120.AUD	I don’t know what you’re talking about.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 6865); //00-6865.AUD	You're a Replicant.
		KIA_Play_Actor_Dialogue(kActorCrazylegs, 550); //09-0550.AUD	That’s impossible.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 2755); //00-2755.AUD	You all right? You look a little pale.
		KIA_Play_Actor_Dialogue(kActorCrazylegs, 1000); //09-1000.AUD	I got customers on the line, so I ain’t got time to chit chat.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 8955); //00-8955.AUD	Stop!
		break;
	case kClueMcCoyIsKind:
		KIA_Play_Actor_Dialogue(kActorLucy, 940); //06-0940.AUD	You’re a good man.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 6780); 
		KIA_Play_Actor_Dialogue(kActorLucy, 950); //06-0950.AUD	You’re gentle. Father used to be like that too.
		KIA_Play_Actor_Dialogue(kActorLucy, 960); //06-0960.AUD	He would read to me and tell me stories. Pretty stories so I would have pretty dreams.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 6785); //00-6785.AUD	He doesn’t do that anymore?
		KIA_Play_Actor_Dialogue(kActorLucy, 970); //06-0970.AUD	He’s out with Sadik every night. And he and mother…
		KIA_Play_Actor_Dialogue(kActorLucy, 980); 
		if (Game_Flag_Query(kFlagDektoraIsReplicant)) {
			KIA_Play_Actor_Dialogue(kActorLucy, 990);
		}
		if (Game_Flag_Query(kFlagDektoraIsReplicant)
		&& Game_Flag_Query(kFlagLucyIsReplicant)) {
			KIA_Play_Actor_Dialogue(kActorLucy, 1000); //06-1000.AUD	I’ve seen death before. But the other day…
		}
		KIA_Play_Actor_Dialogue(kActorLucy, 1010);
		KIA_Play_Actor_Dialogue(kActorLucy, 1020);
		break;
	case kCluePoliceIssueWeapons:
		KIA_Play_Actor_Dialogue(kActorMcCoy, 6710); //00-6710.AUD	How’s business these days, Izo?
		KIA_Play_Actor_Dialogue(kActorIzo, 850); //07-0850.AUD	Non existent. You and Steele made sure of that. Scavengers took the rest.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 6740); //00-6740.AUD	What exactly did the scavengers take?
		KIA_Play_Actor_Dialogue(kActorIzo, 970); //07-0970.AUD	Some of the police-issue weapons and electronics. They took them down into the sewers.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 7835); //00-7835.AUD	Is that so?
		break;
	default:
		break;
	}
}

} // End of namespace BladeRunner
