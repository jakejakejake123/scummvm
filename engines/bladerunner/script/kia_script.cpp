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
		break;
	case kClueDoorForced2:
		// Made it so the door forced 2 contains the entire dialogue for both door force clues. It makes no sense for the player to check the door later to inspect the broken lock because
		// because after you investigate the place and the police are gone from act 2 onwards the door is LOCKED, meaning the lock has been replaced. It wouldn't make much sense for McCoy to inspect a LOCKED door only to say that the lock had been forced
		// So I reappropriated door force 1 to play the unused dialogue where McCoy comments on Sebastians door being forced instead. I mean the reps broke into his place after all and he knows about it,
		// So it must be because he saw that the lock was broken 
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 1870); //99-1870.AUD	Whoever did it showed some serious strength. They busted the lock clean off.
			KIA_Play_Actor_Dialogue(kActorOfficerLeary, 180); //23-0180.AUD	Gaff said you didn't need to hear this, but I guess you deserve to know.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 2635); ////00-2635.AUD	I’m all ears.
			KIA_Play_Actor_Dialogue(kActorOfficerLeary, 0); //23-0000.AUD	I already checked for a crowbar or some kind of tool. No luck but it looks like we've got some latents.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 4495); //00-4495.AUD	Make sure the lab boys run them through the mainframe. Human and Rep.
		}
		KIA_Play_Actor_Dialogue(kActorOfficerLeary, 0); //23-0000.AUD	I already checked for a crowbar or some kind of tool. No luck but it looks like we've got some latents.
		break;
	case kClueDoorForced1:
		if (_vm->_gameVars[kVariableChapter] == 1) {
			// keep in mind, this line in only available in Act 1 (1.TLK) unless _vm->_cutContent is selected (provided that cut content now loads all TLKs)
			// Without cut content it will be silent in subsequent Acts
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 1870);
		}
		// Made it so the other door forced clue is acquired when you enter Sebastians place which now has the door forced dialogue play just before you enter.
		// This is the dialogoue that will be included in this clue.
		if (_vm->_cutContent) {
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
		break;
	case kClueToyDog:
		KIA_Play_Slice_Model(kModelAnimationToyDog);
		break;
	case kClueChopstickWrapper:
		KIA_Play_Slice_Model(kModelAnimationChopstickWrapper);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 2010);
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
			KIA_Play_Actor_Dialogue(kActorKlein, 120); //30-0120.AUD	State-of-the-art fakes. Miles beyond the crap you see on Animoid Row.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 4155); //00-4155.AUD	The kind that comes from legit manufacturers?
			KIA_Play_Actor_Dialogue(kActorKlein, 130); //30-0130.AUD	Eh, they're the ones that usually produce the quality.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 4160); //00-4160.AUD	What about the wounds?
		}
		KIA_Play_Actor_Dialogue(kActorKlein, 140); //30-0140.AUD	Most of them were shot point-blank but we're looking at some others… pteh, sloppy cuts with a knife. Like the perp was really pissed off at something.
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 4165); //00-4165.AUD	Butcher knife?
			KIA_Play_Actor_Dialogue(kActorKlein, 160); //30-0160.AUD	Could be. But who cuts meat anymore?
		}
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
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 4135); //00-4135.AUD	How's that?
		}
		KIA_Play_Actor_Dialogue(kActorKlein, 60); //30-0060.AUD	They're from an Ender rifle. It's standard-issue Off-World military hardware.
		KIA_Play_Actor_Dialogue(kActorKlein, 70); //30-0070.AUD	Heavy caliber. That puppy can punch right through a tank.
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 4140); //00-4140.AUD	What can I conclude from that?
		}
		KIA_Play_Actor_Dialogue(kActorKlein, 80); //30-0080.AUD	Whoever used this piece didn't just walk into their local sporting goods store and buy it.
		KIA_Play_Actor_Dialogue(kActorKlein, 90); //30-0090.AUD	Those babies are collectibles and they ain't cheap.
		break;
	case kClueRuncitersVideo:
		KIA_Play_Slice_Model(kModelAnimationVideoDisc);
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 4545); //00-4545.AUD	You got any discs from that camera?
			KIA_Play_Actor_Dialogue(kActorRunciter, 0); //15-0000.AUD	It's irrelevant.
			KIA_Play_Actor_Dialogue(kActorRunciter, 10); //15-0010.AUD	Those murderers also destroyed the camera. Thousands of chinyens' worth.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 4550); //00-4550.AUD	Maybe it photographed them, before they shot it out.
			KIA_Play_Actor_Dialogue(kActorRunciter, 20); //15-0020.AUD	Hmm, I guess you've got a point at that.
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
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 4050);
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
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 360); //99-0360.AUD	I'd retired a war hero.
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 370); //99-0370.AUD	Someone who'd fought for the freedom of the Off-World colonists.
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 380); //99-0380.AUD	The poor guy kind of reminded me of one of those Buffalo Soldiers...
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 390); //99-0390.AUD	Blacks who had killed and died for America...
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 400); //99-0400.AUD	yet weren't allowed to drink alongside whites.
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 410); //99-0410.AUD	And maybe, just maybe, the photograph validated his own existence.
		}
		break;
	case kClueBigManLimping:
		KIA_Play_Actor_Dialogue(kActorTransient, 10); //12-0010.AUD	Thanks. The big man. He kind of limping.
		KIA_Play_Actor_Dialogue(kActorTransient, 20); //12-0020.AUD	That way.
		break;
	case kClueRunciterInterviewA:
		KIA_Play_Actor_Dialogue(kActorRunciter, 40);
		KIA_Play_Actor_Dialogue(kActorRunciter, 50);
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4565);
		KIA_Play_Actor_Dialogue(kActorRunciter, 60); //15-0060.AUD	No, of course not! It was two men acting in concert with her, obviously.
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 4570); //
			KIA_Play_Actor_Dialogue(kActorRunciter, 70); //15-0070.AUD	Big and scary and absolutely malevolent.
		}
		break;
	case kClueRunciterInterviewB1:
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 4585); //00-4585.AUD	Tell me about this Lucy.
		}
		KIA_Play_Actor_Dialogue(kActorRunciter, 250); //15-0250.AUD	There's not a lot I can tell you. She's only worked for me for about a month.
		KIA_Play_Actor_Dialogue(kActorRunciter, 270); //15-0270.AUD	She's about fourteen years old with pink hair. A very attractive young thing.
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 4645); //00-4645.AUD	How did you find her? 
			KIA_Play_Actor_Dialogue(kActorRunciter, 280); //15-0280.AUD	She came to me with a reference from Ogilvies in the North West Zone.
			KIA_Play_Actor_Dialogue(kActorRunciter, 290); //15-0290.AUD	And he's a very reputable wholesaler.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 4650); //00-4650.AUD	You treat her well? 
			KIA_Play_Actor_Dialogue(kActorRunciter, 320); //15-0320.AUD	As well as any young tart should be treated.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 4655); //00-4655.AUD	What did she do around here? Feed the animals?
			KIA_Play_Actor_Dialogue(kActorRunciter, 330); //15-0330.AUD	I'm the only one who handles my animals, detective.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 4660); //00-4660.AUD	So what did she do?
			KIA_Play_Actor_Dialogue(kActorRunciter, 340); //15-0340.AUD	Unskilled labor, mostly. She was perfect for that. As if she were made for it.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 4665); //00-4665.AUD	She got a desk or some place where she worked?
			KIA_Play_Actor_Dialogue(kActorRunciter, 350); //15-0350.AUD	She used to eat over there.
		}
		break;
	case kClueRunciterInterviewB2:
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 4585); //00-4585.AUD	Tell me about this Lucy.
		}
		KIA_Play_Actor_Dialogue(kActorRunciter, 260); //15-0260.AUD	There's not a lot I can tell you. She's only worked for me for a short while.
		KIA_Play_Actor_Dialogue(kActorRunciter, 270); //15-0270.AUD	She's about fourteen years old with pink hair. A very attractive young thing.
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 4645); //00-4645.AUD	How did you find her? 
			KIA_Play_Actor_Dialogue(kActorRunciter, 280); //15-0280.AUD	She came to me with a reference from Ogilvies in the North West Zone.
			KIA_Play_Actor_Dialogue(kActorRunciter, 290); //15-0290.AUD	And he's a very reputable wholesaler.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 4650); //00-4650.AUD	You treat her well? 
			KIA_Play_Actor_Dialogue(kActorRunciter, 320); //15-0320.AUD	As well as any young tart should be treated.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 4655); //00-4655.AUD	What did she do around here? Feed the animals?
			KIA_Play_Actor_Dialogue(kActorRunciter, 330); //15-0330.AUD	I'm the only one who handles my animals, detective.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 4665); //00-4665.AUD	She got a desk or some place where she worked?
			KIA_Play_Actor_Dialogue(kActorRunciter, 350); //15-0350.AUD	She used to eat over there.
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
			KIA_Play_Actor_Dialogue(kActorOfficerLeary, 20); //23-0020.AUD	Find something? 
			KIA_Play_Actor_Dialogue(kActorMcCoy, 4505); //00-4505.AUD	Piece of chrome.
			KIA_Play_Actor_Dialogue(kActorOfficerLeary, 30); //23-0030.AUD	From a car?
			KIA_Play_Actor_Dialogue(kActorMcCoy, 4510); //No, I think it's horse chrome. Bag it and tag it.
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
		KIA_Play_Actor_Dialogue(kActorGuzza, 820);
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
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 2140);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 2150);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 2160);
		break;
	case kClueTyrellSecurity:
		KIA_Play_Slice_Model(kModelAnimationVideoDisc);
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorTyrellGuard, 20); //17-0020.AUD	Ah-- here's the footage from the security cameras. You get a pretty good look at the man's face.
		}
		break;
	case kClueTyrellGuardInterview:
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorTyrellGuard, 20); //17-0020.AUD	Ah-- here's the footage from the security cameras. You get a pretty good look at the man's face.
		}
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
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 2300); //99-2300.AUD	Obviously, he'd been killed with an explosive.
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 2310); //99-2310.AUD	And not just because he'd been plastered on the wall with a thousand strokes.
		}
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 2320); //99-2320.AUD	The detonator wire I pulled out of his skull told the whole story.
		if (Game_Flag_Query(kFlagSadikIsReplicant)) {
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 2330);
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 2340);
		}
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 2350);
		break;
	case kClueVictimInformation:
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 5165); //00-5165.AUD	You friendly with Eisenduller?
		}
		KIA_Play_Actor_Dialogue(kActorTyrellGuard, 100); //17-0100.AUD	Most of the employees I see coming in morning and night, but old Marcus...
		KIA_Play_Actor_Dialogue(kActorTyrellGuard, 110); //17-0110.AUD	er, I mean Dr. Eisenduller, he almost never left his lab.
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 5185); //00-5185.AUD	He afraid of somebody?
		}
		KIA_Play_Actor_Dialogue(kActorTyrellGuard, 120); //17-0120.AUD	I think it had something to do with the air outside and the germs.
		KIA_Play_Actor_Dialogue(kActorTyrellGuard, 130); //17-0130.AUD	I once heard him complain about it.
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 5190); //00-5190.AUD	Smart. What was his job?
			KIA_Play_Actor_Dialogue(kActorTyrellGuard, 140); //17-0140.AUD	Grav Test Chief Engineer.
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
		KIA_Play_Actor_Dialogue(kActorSteele, 2230); //01-2230.AUD	(laughs) Oh, in a pig's ass, Slim. No, I'm following up on my own.
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorSteele, 2240); //01-2240.AUD	Could be it's linked to this Tyrell debacle.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 5250); //00-5250.AUD	How's yours connected to mine?
			KIA_Play_Actor_Dialogue(kActorSteele, 2250); //01-2250.AUD	I'm still fitting the pieces together.
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
		if (Query_Difficulty_Level() == kGameDifficultyEasy) {
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
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 90); //00-0090.AUD	More than I can afford.
		}
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
		if (!_vm->_cutContent) {	
				KIA_Play_Actor_Dialogue(kActorHasan, 100);
		}
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorHasan, 110); //20-0110.AUD	He takes peculiar pleasure in agitating all the vendors around here.
			KIA_Play_Actor_Dialogue(kActorHasan, 120); //20-0120.AUD	I cannot even go out for a Shish-Taouk without worrying whether Bob is going to sabotage my snakes.
		}
		break;
	case kClueBobInterview1:
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 5010); //00-5010.AUD	You know anyone who might sell Ender rifles?
		}
		KIA_Play_Actor_Dialogue(kActorBulletBob, 320); //14-0320.AUD	There's one other guy around here who dips into that stuff.
		KIA_Play_Actor_Dialogue(kActorBulletBob, 330); //14-0330.AUD	Got a pawn shop down the street. Goes by the name of Izo.
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorBulletBob, 340); //14-0340.AUD	But who knows what the real title is.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 5015); //00-5015.AUD	Izo, huh. Sounds like you don't like him.
		}
		KIA_Play_Actor_Dialogue(kActorBulletBob, 350); //14-0350.AUD	I've been around here a long time, Ray.
		KIA_Play_Actor_Dialogue(kActorBulletBob, 360); 
		KIA_Play_Actor_Dialogue(kActorBulletBob, 370);
		KIA_Play_Actor_Dialogue(kActorMcCoy, 5020);	
		KIA_Play_Actor_Dialogue(kActorBulletBob, 380);
		KIA_Play_Actor_Dialogue(kActorBulletBob, 390);
		KIA_Play_Actor_Dialogue(kActorBulletBob, 400);
		break;
	case kClueBobInterview2:
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 5010); //00-5010.AUD	You know anyone who might sell Ender rifles?
		}
		KIA_Play_Actor_Dialogue(kActorBulletBob, 320); //14-0320.AUD	There's one other guy around here who dips into that stuff.
		KIA_Play_Actor_Dialogue(kActorBulletBob, 330); //14-0330.AUD	Got a pawn shop down the street. Goes by the name of Izo.
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorBulletBob, 340); //14-0340.AUD	But who knows what the real title is.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 5015); //00-5015.AUD	Izo, huh. Sounds like you don't like him.
		}
		KIA_Play_Actor_Dialogue(kActorBulletBob, 410); //14-0410.AUD	Izo is okay. He's run the Green Pawn for a while.
		KIA_Play_Actor_Dialogue(kActorBulletBob, 420); //14-0420.AUD	We're friendly competitors, I guess. But I don't appreciate his politics.
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 5025); //00-5025.AUD	Yeah?
			KIA_Play_Actor_Dialogue(kActorBulletBob, 430); //14-0430.AUD	Rumors that's all they are.
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
		KIA_Play_Actor_Dialogue(kActorIzo, 750);
		KIA_Play_Actor_Dialogue(kActorIzo, 760);
		KIA_Play_Actor_Dialogue(kActorMcCoy, 5500);
		KIA_Play_Actor_Dialogue(kActorIzo, 780);
		KIA_Play_Actor_Dialogue(kActorIzo, 790);
		break;
	case kClueRadiationGoggles:
		KIA_Play_Slice_Model(kModelAnimationRadiationGoggles);
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
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 4160);
		break;
	case kClueWeaponsCache:
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 2430);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 2440);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 2450); //99-2450.AUD	Izo wasn't some small-time fence but a big-time arms dealer.
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 2460); //99-2460.AUD	The exact arms that renegade Replicants would be looking for to survive in the big city.
		}
		break;
	case kClueChewInterview:
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 840); //00-0840.AUD	Did you hear me?
		}
		KIA_Play_Actor_Dialogue(kActorChew, 140); //52-0140.AUD	Of course I hear you! You-- you think I'm deaf? (mumbles) Hmph, your time more important, man?
		KIA_Play_Actor_Dialogue(kActorChew, 150); //52-0150.AUD	Eisenduller dead. Moraji maybe dead. You out chasing skirts?
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 845);  //00-0845.AUD	Moraji?
		}
		KIA_Play_Actor_Dialogue(kActorChew, 170); //52-0170.AUD	Chew eat supper with Moraji every night, no fail. Sometimes Chinese, sometimes Indian, sometimes home cook.
		KIA_Play_Actor_Dialogue(kActorChew, 180); //52-0180.AUD	Sometimes we go up and eat with twins.
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 870); //00-0870.AUD	What does he work on?
			KIA_Play_Actor_Dialogue(kActorChew, 190); //52-0290.AUD	Skin. Did skin for Nexus-6. Beautiful work. You go see.
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
		}
		KIA_Play_Actor_Dialogue(kActorGordo, 1010); //02-1010.AUD	Bombing? I've never bombed in my life. My act is always happening. Always now.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 6495);
		KIA_Play_Actor_Dialogue(kActorGordo, 1020);
		KIA_Play_Actor_Dialogue(kActorMcCoy, 6500);
		KIA_Play_Actor_Dialogue(kActorGordo, 1030);
		break;
	case kClueGordoInterview2:
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 6485); //00-6485.AUD	You know anything about that bomb that just rocked the street?
		}
		KIA_Play_Actor_Dialogue(kActorGordo, 1040); //02-1040.AUD	Bombing? I had a cousin who bombed at Tyrell's niece's wedding.
		KIA_Play_Actor_Dialogue(kActorGordo, 1050);
		KIA_Play_Actor_Dialogue(kActorMcCoy, 6505);
		KIA_Play_Actor_Dialogue(kActorGordo, 1060);
		KIA_Play_Actor_Dialogue(kActorGordo, 1070);
		KIA_Play_Actor_Dialogue(kActorMcCoy, 6510);
		KIA_Play_Actor_Dialogue(kActorGordo, 1080);
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
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 80);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 90);
		break;
	case kClueStaggeredbyPunches:
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 4370);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 4380);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 4390);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 4400);
		break;
	case kClueMaggieBracelet:
		KIA_Play_Slice_Model(kModelAnimationMaggieBracelet);
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 4030);
		}
		break;
	case kClueEnvelope:
		KIA_Play_Slice_Model(kModelAnimationEnvelope);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 850);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 860);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 870);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 880);
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
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 4055); //00-4055.AUD	Thanks, Lieutenant.
		}
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
		break;
	case kClueMoonbus1:
		KIA_Play_Photograph(34);
		break;
	case kClueCheese:
		KIA_Play_Slice_Model(kModelAnimationCheese);
		break;
	case kClueDektorasDressingRoom:
		KIA_Play_Photograph(16);
		break;
	case kClueEarlyQsClub:
		KIA_Play_Slice_Model(kModelAnimationVideoDisc);
		break;
	case kClueDragonflyCollection:
		KIA_Play_Actor_Dialogue(kActorInsectDealer, 290);
		KIA_Play_Actor_Dialogue(kActorInsectDealer, 300);
		break;
	case kClueDragonflyBelt:
		KIA_Play_Slice_Model(kModelAnimationDragonflyBelt);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 4050);
		break;
	case kClueEarlyQInterview:
		KIA_Play_Actor_Dialogue(kActorEarlyQ, 140);
		KIA_Play_Actor_Dialogue(kActorEarlyQ, 150);
		break;
	case kClueStrangeScale1:
		KIA_Play_Slice_Model(kModelAnimationStrangeScale);
		break;
	case kClueDektoraInterview1:
		KIA_Play_Actor_Dialogue(kActorDektora, 650);
		KIA_Play_Actor_Dialogue(kActorDektora, 660);
		KIA_Play_Actor_Dialogue(kActorMcCoy, 3665);
		KIA_Play_Actor_Dialogue(kActorDektora, 670);
		KIA_Play_Actor_Dialogue(kActorDektora, 680);
		KIA_Play_Actor_Dialogue(kActorDektora, 690);
		break;
	case kClueDektoraInterview2:
		KIA_Play_Actor_Dialogue(kActorDektora, 580);
		break;
	case kClueDektoraInterview3:
		KIA_Play_Actor_Dialogue(kActorMcCoy, 3600);
		KIA_Play_Actor_Dialogue(kActorDektora, 550);
		break;
	case kClueDektorasCard:
		KIA_Play_Slice_Model(kModelAnimationDektorasCard);
		break;
	case kClueCrazysInvolvement:
		// RESTORED CONTENT
		KIA_Play_Slice_Model(kModelAnimationLetter);
		break;
	case kClueGrigoriansNote:
		KIA_Play_Slice_Model(kModelAnimationGrigoriansNote);
		break;
	case kClueCollectionReceipt:
		KIA_Play_Slice_Model(kModelAnimationCollectionReceipt);
		break;
	case kClueSpecialIngredient:
		KIA_Play_Actor_Dialogue(kActorMurray, 210);
		KIA_Play_Actor_Dialogue(kActorMurray, 220);
		KIA_Play_Actor_Dialogue(kActorMia, 140);
		KIA_Play_Actor_Dialogue(kActorMurray, 230);
		break;
	case kClueStolenCheese:
		KIA_Play_Actor_Dialogue(kActorIsabella, 210);
		KIA_Play_Actor_Dialogue(kActorIsabella, 260);
		KIA_Play_Actor_Dialogue(kActorMcCoy, 1390);
		KIA_Play_Actor_Dialogue(kActorIsabella, 300);
		break;
	case kClueGordoInterview3:
		KIA_Play_Actor_Dialogue(kActorGordo, 450);
		KIA_Play_Actor_Dialogue(kActorMcCoy, 3280);
		break;
	case kClueGordoConfession:
		KIA_Play_Actor_Dialogue(kActorMcCoy, 3250);
		KIA_Play_Actor_Dialogue(kActorGordo, 540);
		KIA_Play_Actor_Dialogue(kActorGordo, 550);
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
		break;
	case kClueDektoraInterview4:
		KIA_Play_Actor_Dialogue(kActorMcCoy, 3860);
		KIA_Play_Actor_Dialogue(kActorDektora, 1030);
		KIA_Play_Actor_Dialogue(kActorDektora, 1040);
		KIA_Play_Actor_Dialogue(kActorMcCoy, 3865);
		KIA_Play_Actor_Dialogue(kActorDektora, 1050);
		KIA_Play_Actor_Dialogue(kActorDektora, 1060);
		break;
	case kClueHollowayInterview:
		KIA_Play_Actor_Dialogue(kActorHolloway, 0);
		KIA_Play_Actor_Dialogue(kActorHolloway, 10);
		break;
	case kClueBakersBadge:
		KIA_Play_Slice_Model(kModelAnimationBadge);
		break;
	case kClueHoldensBadge:
		KIA_Play_Slice_Model(kModelAnimationBadge);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 4420);
		break;
	case kClueCarIdentified:
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 3780);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 3790);
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
		KIA_Play_Actor_Dialogue(kActorCrazylegs, 830);
		KIA_Play_Actor_Dialogue(kActorCrazylegs, 840);
		KIA_Play_Actor_Dialogue(kActorCrazylegs, 850);
		break;
	case kClueLichenDogWrapper:
		KIA_Play_Slice_Model(kModelAnimationLichenDogWrapper);
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
		KIA_Play_Actor_Dialogue(kActorMcCoy, 5615);
		KIA_Play_Actor_Dialogue(kActorTransient, 170);
		KIA_Play_Actor_Dialogue(kActorMcCoy, 5625);
		KIA_Play_Actor_Dialogue(kActorTransient, 180);
		KIA_Play_Actor_Dialogue(kActorMcCoy, 5630);
		KIA_Play_Actor_Dialogue(kActorTransient, 190);
		KIA_Play_Actor_Dialogue(kActorMcCoy, 5635);
		KIA_Play_Actor_Dialogue(kActorTransient, 200);
		break;
	case kClueHomelessManInterview2:
		KIA_Play_Actor_Dialogue(kActorMcCoy, 5640);
		KIA_Play_Actor_Dialogue(kActorTransient, 230);
		KIA_Play_Actor_Dialogue(kActorMcCoy, 5645);
		KIA_Play_Actor_Dialogue(kActorTransient, 240);
		KIA_Play_Actor_Dialogue(kActorTransient, 250);
		KIA_Play_Actor_Dialogue(kActorMcCoy, 5650);
		KIA_Play_Actor_Dialogue(kActorTransient, 260);
		break;
	case kClueHomelessManKid:
		KIA_Play_Actor_Dialogue(kActorTransient, 340);
		KIA_Play_Actor_Dialogue(kActorTransient, 350);
		KIA_Play_Actor_Dialogue(kActorTransient, 360);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 2710);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 2730);
		break;
	case kClueFolder:
		KIA_Play_Slice_Model(kModelAnimationFolder);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 2740);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 2750);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 2760);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 2770);
		break;
	case kClueGuzzaFramedMcCoy:
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 3320);
		break;
	case kClueOriginalShippingForm:
		KIA_Play_Slice_Model(kModelAnimationOriginalShippingForm);
		break;
	case kClueOriginalRequisitionForm:
		KIA_Play_Slice_Model(kModelAnimationOriginalRequisitionForm);
		break;
	case kClueCandyWrapper:
		KIA_Play_Slice_Model(kModelAnimationCandyWrapper);
		break;
	case kClueFlaskOfAbsinthe:
		KIA_Play_Slice_Model(kModelAnimationFlaskOfAbsinthe);
		break;
	case kClueLutherLanceInterview:
		KIA_Play_Actor_Dialogue(kActorLuther, 240);
		KIA_Play_Actor_Dialogue(kActorLance, 200);
		KIA_Play_Actor_Dialogue(kActorLance, 210);
		KIA_Play_Actor_Dialogue(kActorLuther, 260);
		KIA_Play_Actor_Dialogue(kActorLuther, 270);
		break;
	case kCluePhoneCallDektora1:
		KIA_Play_Actor_Dialogue(kActorDektora, 360);
		KIA_Play_Actor_Dialogue(kActorDektora, 380);
		break;
	case kCluePhoneCallDektora2:
		KIA_Play_Actor_Dialogue(kActorMcCoy, 2505);
		KIA_Play_Actor_Dialogue(kActorDektora, 430);
		KIA_Play_Actor_Dialogue(kActorDektora, 440);
		KIA_Play_Actor_Dialogue(kActorMcCoy, 2530);
		KIA_Play_Actor_Dialogue(kActorDektora, 450);
		KIA_Play_Actor_Dialogue(kActorMcCoy, 2535);
		KIA_Play_Actor_Dialogue(kActorDektora, 460);
		KIA_Play_Actor_Dialogue(kActorDektora, 470);
		break;
	case kCluePhoneCallLucy1:
		KIA_Play_Actor_Dialogue(kActorLucy, 590);
		KIA_Play_Actor_Dialogue(kActorLucy, 630);
		break;
	case kCluePhoneCallLucy2:
		KIA_Play_Actor_Dialogue(kActorLucy, 540);
		KIA_Play_Actor_Dialogue(kActorLucy, 550);
		KIA_Play_Actor_Dialogue(kActorMcCoy, 2550);
		KIA_Play_Actor_Dialogue(kActorLucy, 560);
		break;
	case kCluePhoneCallClovis:
		KIA_Play_Actor_Dialogue(kActorClovis, 530);
		KIA_Play_Actor_Dialogue(kActorClovis, 540);
		break;
	case kCluePhoneCallCrystal:
		KIA_Play_Actor_Dialogue(kActorSteele, 700);
		KIA_Play_Actor_Dialogue(kActorSteele, 750);
		KIA_Play_Actor_Dialogue(kActorSteele, 760);
		break;
	case kCluePowerSource:
		KIA_Play_Slice_Model(kModelAnimationPowerSource);
		break;
	case kClueBomb:
		KIA_Play_Slice_Model(kModelAnimationBomb);
		break;
	case kClueDNATyrell:
	case kClueDNASebastian:
	case kClueDNAChew:
	case kClueDNAMoraji:
	case kClueDNALutherLance:
	case kClueDNAMarcus:
		{
			int dnaEvidences = Global_Variable_Query(kVariableDNAEvidence);
			if (dnaEvidences == 1) {
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
		break;
	case kClueSlug:
		KIA_Play_Slice_Model(kModelAnimationSlug);
		break;
	case kClueGoldfish:
		KIA_Play_Slice_Model(kModelAnimationGoldfish);
		break;
	case kClueZubenTalksAboutLucy1:
		KIA_Play_Actor_Dialogue(kActorZuben, 230);
		KIA_Play_Actor_Dialogue(kActorZuben, 240);
		break;
	case kClueZubenTalksAboutLucy2:
		KIA_Play_Actor_Dialogue(kActorZuben, 250);
		KIA_Play_Actor_Dialogue(kActorZuben, 260);
		break;
	case kClueZubensMotive:
		KIA_Play_Actor_Dialogue(kActorZuben, 280);
		KIA_Play_Actor_Dialogue(kActorMcCoy, 7350);
		KIA_Play_Actor_Dialogue(kActorZuben, 290);
		KIA_Play_Actor_Dialogue(kActorZuben, 300);
		KIA_Play_Actor_Dialogue(kActorZuben, 310);
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
			KIA_Play_Actor_Dialogue(kActorSteele, 3330);
		}
		KIA_Play_Actor_Dialogue(kActorSteele, 3350);
		KIA_Play_Actor_Dialogue(kActorSteele, 3360);
		KIA_Play_Actor_Dialogue(kActorSteele, 3370);
		KIA_Play_Actor_Dialogue(kActorSteele, 3380);
		break;
	case kClueGrigorianInterviewA:
		KIA_Play_Actor_Dialogue(kActorSteele, 3390);
		KIA_Play_Actor_Dialogue(kActorSteele, 3400);
		KIA_Play_Actor_Dialogue(kActorSteele, 3410);
		// TODO this line of Grigorian is supposedly interrupted by Steele's following line
		//      maybe implement a way to not wait before the next line is played, similar to Actor_Says_With_Pause()
		//       (look into tick() for kia.cpp)
		KIA_Play_Actor_Dialogue(kActorGrigorian, 1260);
		KIA_Play_Actor_Dialogue(kActorSteele, 3420);
		KIA_Play_Actor_Dialogue(kActorSteele, 3430);
		KIA_Play_Actor_Dialogue(kActorSteele, 3440);
		KIA_Play_Actor_Dialogue(kActorGrigorian, 1270);
		KIA_Play_Actor_Dialogue(kActorSteele, 3450);
		KIA_Play_Actor_Dialogue(kActorSteele, 3460);
		KIA_Play_Actor_Dialogue(kActorGrigorian, 1280);
		KIA_Play_Actor_Dialogue(kActorSteele, 3470);
		KIA_Play_Actor_Dialogue(kActorGrigorian, 1300);
		KIA_Play_Actor_Dialogue(kActorGrigorian, 1310);
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorSteele, 3260); // And eliminating the glitches...
			KIA_Play_Actor_Dialogue(kActorSteele, 3480);
		    if (_vm->_language == Common::ES_ESP
		        || _vm->_language == Common::IT_ITA) {
				//
				// in ITA and ESP the 3490 quote is the second half of the sentence starting in previous quote (3480)
				KIA_Play_Actor_Dialogue(kActorSteele, 3490);
			}
		} else {
			// the 3490 quote is *BOOP* in the ENG and DEU versions
			// the 3490 quote is also redundant in FRA version, since it's only the first half of the previous quote (3480)
			KIA_Play_Actor_Dialogue(kActorSteele, 3480);
		}
		KIA_Play_Actor_Dialogue(kActorSteele, 3500);
		KIA_Play_Actor_Dialogue(kActorGrigorian, 1320);
		KIA_Play_Actor_Dialogue(kActorGrigorian, 1330);
		KIA_Play_Actor_Dialogue(kActorSteele, 3510);
		KIA_Play_Actor_Dialogue(kActorGrigorian, 1340);
		KIA_Play_Actor_Dialogue(kActorSteele, 3520);
		KIA_Play_Actor_Dialogue(kActorGrigorian, 1350);
		KIA_Play_Actor_Dialogue(kActorSteele, 3530);
		KIA_Play_Actor_Dialogue(kActorSteele, 3540);
		break;
	case kClueGrigorianInterviewB1:
		// Izo is a Replicant
		KIA_Play_Actor_Dialogue(kActorSteele, 3550); // Describe them to me again.
		KIA_Play_Actor_Dialogue(kActorGrigorian, 1360); // Just the Rastafarian fellow. And that-- that friend of his. A slim blond man, Asian. With-- with a ponytail.
		KIA_Play_Actor_Dialogue(kActorGrigorian, 1370);
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorSteele, 3620); // Let me ask you a question.
			KIA_Play_Actor_Dialogue(kActorSteele, 3630);
			KIA_Play_Actor_Dialogue(kActorGrigorian, 1380);
			KIA_Play_Actor_Dialogue(kActorSteele, 3640);  // such as
			KIA_Play_Actor_Dialogue(kActorGrigorian, 1390);
		}
		KIA_Play_Actor_Dialogue(kActorSteele, 3560); // Bravo, Spencer.
		KIA_Play_Actor_Dialogue(kActorSteele, 3570);
		break;
	case kClueGrigorianInterviewB2:
		// Izo is a human
		KIA_Play_Actor_Dialogue(kActorSteele, 3580); // Describe them for me again.
		KIA_Play_Actor_Dialogue(kActorGrigorian, 1400); // There was that Rastafarian fellow and one of our ex members showed up.
		KIA_Play_Actor_Dialogue(kActorSteele, 3590);
		KIA_Play_Actor_Dialogue(kActorGrigorian, 1410); // A Japanese man named Izo.
		KIA_Play_Actor_Dialogue(kActorSteele, 3600);
		KIA_Play_Actor_Dialogue(kActorGrigorian, 1420); // We're a pacifist organization and we have rules
		KIA_Play_Actor_Dialogue(kActorGrigorian, 1430); // Izo refused to check in his samurai sword
		KIA_Play_Actor_Dialogue(kActorSteele, 3610);
		KIA_Play_Actor_Dialogue(kActorGrigorian, 1440);
		KIA_Play_Actor_Dialogue(kActorSteele, 3620); // Let me ask you a question.
		KIA_Play_Actor_Dialogue(kActorSteele, 3630);
		KIA_Play_Actor_Dialogue(kActorGrigorian, 1450);
		KIA_Play_Actor_Dialogue(kActorSteele, 3640);  // such as
		KIA_Play_Actor_Dialogue(kActorGrigorian, 1460);
		KIA_Play_Actor_Dialogue(kActorSteele, 3650);
		break;
	case kClueAnimalMurderSuspect:
		KIA_Play_Photograph(7);
		break;
	case kClueMilitaryBoots:
		KIA_Play_Photograph(8);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 4110);
		break;
	case kClueOuterDressingRoom:
		KIA_Play_Photograph(15);
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
		break;
	case kClueScorpions:
		KIA_Play_Photograph(22);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 4180);
		break;
	case kClueStrangeScale2:
		KIA_Play_Photograph(23);
		break;
	case kClueChinaBarSecurityCamera:
		KIA_Play_Photograph(24);
		break;
	case kClueIzo:
		KIA_Play_Photograph(26);
		break;
	case kClueGuzza:
		KIA_Play_Photograph(27);
		break;
	case kClueChinaBarSecurityDisc:
		KIA_Play_Slice_Model(kModelAnimationVideoDisc);
		break;
	case kClueScorpionbox:
		KIA_Play_Photograph(0);
		break;
	case kClueTyrellSecurityPhoto:
		KIA_Play_Photograph(28);
		break;
	case kClueChinaBar:
		KIA_Play_Photograph(19);
		break;
	case kCluePlasticExplosive:
		KIA_Play_Photograph(32);
		break;
	case kClueDogCollar2:
		KIA_Play_Photograph(30);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 4160);
		break;
	case kClueKingstonKitchenBox2:
		KIA_Play_Photograph(29);
		if (Query_Difficulty_Level() == kGameDifficultyEasy) {
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 4140);
		} else {
			KIA_Play_Actor_Dialogue(kActorVoiceOver, 4150);
		}
		break;
	case kClueCrystalsCigarette:
		KIA_Play_Slice_Model(kModelAnimationCrystalsCigarette);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 1770);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 1150);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 1180);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 1190);
		break;
	case kClueSpinnerKeys:
		KIA_Play_Slice_Model(kModelAnimationSpinnerKeys);
		break;
	case kClueExpertBomber:
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 730);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 740);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 750);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 760);
		break;
	case kClueAmateurBomber:
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 670);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 680);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 700);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 710);
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
		KIA_Play_Actor_Dialogue(kActorMcCoy, 1645);
		KIA_Play_Actor_Dialogue(kActorLucy, 240);
		KIA_Play_Actor_Dialogue(kActorLucy, 250);
		KIA_Play_Actor_Dialogue(kActorMcCoy, 1675);
		KIA_Play_Actor_Dialogue(kActorLucy, 260);
		KIA_Play_Actor_Dialogue(kActorLucy, 270);
		break;
	case kClueMoonbusReflection:
		KIA_Play_Photograph(35);
		break;
	case kClueMcCoyAtMoonbus:
		KIA_Play_Photograph(36);
		if (_vm->_cutContent) {
			if (Actor_Clue_Query(kActorMcCoy, kClueMoonbusReflection)) {
				KIA_Play_Actor_Dialogue(kActorVoiceOver, 4250);
			} else {
				KIA_Play_Actor_Dialogue(kActorVoiceOver, 4010);
				KIA_Play_Actor_Dialogue(kActorVoiceOver, 4020);
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
		KIA_Play_Actor_Dialogue(kActorMcCoy, 5365);
		KIA_Play_Actor_Dialogue(kActorRachael, 600);
		KIA_Play_Actor_Dialogue(kActorMcCoy, 5370);
		KIA_Play_Actor_Dialogue(kActorRachael, 610);
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 5375);
			KIA_Play_Actor_Dialogue(kActorMcCoy, 5380);
			KIA_Play_Actor_Dialogue(kActorRachael, 620);
			KIA_Play_Actor_Dialogue(kActorMcCoy, 5385);
		}
		break;
	case kClueTyrellInterview:
		KIA_Play_Actor_Dialogue(kActorTyrell, 0);
		KIA_Play_Actor_Dialogue(kActorTyrell, 10);
		KIA_Play_Actor_Dialogue(kActorTyrell, 20);
		KIA_Play_Actor_Dialogue(kActorTyrell, 30);
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 5425);
			KIA_Play_Actor_Dialogue(kActorTyrell, 40);
			KIA_Play_Actor_Dialogue(kActorTyrell, 50);
			KIA_Play_Actor_Dialogue(kActorMcCoy, 5430);
			KIA_Play_Actor_Dialogue(kActorMcCoy, 5435);
			KIA_Play_Actor_Dialogue(kActorTyrell, 60);
			KIA_Play_Actor_Dialogue(kActorMcCoy, 5440);
			KIA_Play_Actor_Dialogue(kActorTyrell, 70);
			KIA_Play_Actor_Dialogue(kActorMcCoy, 5445);
			KIA_Play_Actor_Dialogue(kActorTyrell, 80);
		}
		break;
	case kClueRuncitersConfession1:
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 4770); //00-4770.AUD	You raped her.
			KIA_Play_Actor_Dialogue(kActorRunciter, 590); //-	15-0590.AUD	What? Who?
			KIA_Play_Actor_Dialogue(kActorMcCoy, 4775); //-	00-4775.AUD	Lucy.
			KIA_Play_Actor_Dialogue(kActorRunciter, 600); //-	15-0600.AUD	That's ridiculous. I—
			KIA_Play_Actor_Dialogue(kActorMcCoy, 4780); //-	00-4780.AUD	Go ahead little man, lie to me. You'll only do it once.
			KIA_Play_Actor_Dialogue(kActorRunciter, 610); //-	15-0610.AUD	You're no better! No better than those thugs who attacked me.
			KIA_Play_Actor_Dialogue(kActorMcCoy, 4785); //-	00-4785.AUD	Maybe not, but I'm better than you. She's a little girl.
		}
		KIA_Play_Actor_Dialogue(kActorRunciter, 630); // 15-0630.AUD	She's... You know what she is.
		KIA_Play_Actor_Dialogue(kActorRunciter, 640); //15-0640.AUD	You know why Tyrell built her to look they way she does.
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 4790); // 00-4790.AUD	Bullshit!
		}
		KIA_Play_Actor_Dialogue(kActorRunciter, 650); //15-0650.AUD	It's true.
		if (_vm->_cutContent) {
			KIA_Play_Actor_Dialogue(kActorMcCoy, 4800); // 00-4800.AUD	You son of a bitch she couldn't object.
			KIA_Play_Actor_Dialogue(kActorRunciter, 660); // 15-0660.AUD	Please, I wouldn't-- you know I wouldn't have done that to a human girl. I swear it.
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
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4770); //00-4770.AUD	You raped her.
		KIA_Play_Actor_Dialogue(kActorRunciter, 590); //15-0590.AUD	What? Who?
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4775); //-	00-4775.AUD	Lucy.
		KIA_Play_Actor_Dialogue(kActorRunciter, 600); //15-0600.AUD	That's ridiculous. I—
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4780); //00-4780.AUD	Go ahead little man, lie to me. You'll only do it once.
		KIA_Play_Actor_Dialogue(kActorRunciter, 610); //15-0610.AUD	You're no better! No better than those thugs who attacked me.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4785); //00-4785.AUD	Maybe not, but I'm better than you. She's a little girl.
		KIA_Play_Actor_Dialogue(kActorRunciter, 620); //15-0620.AUD	It wasn't like that.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4800); //00-4800.AUD	You son of a bitch she couldn't object.
		KIA_Play_Actor_Dialogue(kActorRunciter, 670); //15-0670.AUD	She...
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4795); //00-4795.AUD	If you say she asked for it, you're dead.
		break;
	case kClueRuncitersConfession3:
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4730); //00-4730.AUD	Tell me about Luther and Lance!
		KIA_Play_Actor_Dialogue(kActorRunciter, 480); //15-0480.AUD	There's-- Who? I don't...
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4735); //00-4735.AUD	You're paying the sub-cons on DNA Row. Why?
		KIA_Play_Actor_Dialogue(kActorRunciter, 490); //15-0490.AUD	No. You heard it wrong.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4740); //00-4740.AUD	Lie to me. Go ahead. You'll only do it once.
		KIA_Play_Actor_Dialogue(kActorRunciter, 500); //15-0500.AUD	Animals. It was my animals. Some of them were...
		KIA_Play_Actor_Dialogue(kActorRunciter, 510); //15-0510.AUD	F-- fake. You won't-- You can't tell anyone. My reputation.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4745); //00-4745.AUD	Your reputation?!
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4750); //00-4750.AUD	Unbelievable.
		break;
	case kClueZubenIncept:
		KIA_Play_Slice_Model(kModelAnimationPhoto);
		break;
	case kClueClovisIncept:
		KIA_Play_Slice_Model(kModelAnimationPhoto);
		break;
	case kClueSadikIncept:
		KIA_Play_Slice_Model(kModelAnimationPhoto);
		break;
	case kClueDektoraIncept:
		KIA_Play_Slice_Model(kModelAnimationPhoto);
		break;
	case kClueIzoIncept:
		KIA_Play_Slice_Model(kModelAnimationPhoto);
		break;
	case kClueGordoIncept:
		KIA_Play_Slice_Model(kModelAnimationPhoto);
		break;
	case kClueLucyIncept:
		KIA_Play_Slice_Model(kModelAnimationPhoto);
		break;
	case kClueMcCoyIncept:
		KIA_Play_Slice_Model(kModelAnimationPhoto);
		break;
	case kClueInceptShotRoy:
		KIA_Play_Slice_Model(kModelAnimationPhoto);
		break;
	case kClueInceptShotsLeon:
		KIA_Play_Slice_Model(kModelAnimationPhoto);
		break;
	case kClueCarWasStolen:
		KIA_Play_Actor_Dialogue(kActorMcCoy, 3615); //00-3615.AUD	You buy a vehicle lately? A black Sedan?
		KIA_Play_Actor_Dialogue(kActorDektora, 770); //03-0770.AUD	I wasn’t aware that was a crime.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 3720); //00-3720.AUD	Buying the car isn’t. Using the car in an animal murder, well...
		KIA_Play_Actor_Dialogue(kActorDektora, 780); //03-0780.AUD	Animal murder? That’s horrible.
		KIA_Play_Actor_Dialogue(kActorDektora, 790); //03-0790.AUD	I haven’t seen the car for two days. It was stolen the day after I bought it.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 3725); //00-3725.AUD	Is that right? Any reason you didn’t tell me that right off?
		KIA_Play_Actor_Dialogue(kActorDektora, 800); //03-0800.AUD	You didn’t ask.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 3730); //00-3730.AUD	Animal murder is pretty horrible.
		KIA_Play_Actor_Dialogue(kActorDektora, 810); //03-0810.AUD	Yes.
		KIA_Play_Actor_Dialogue(kActorDektora, 820); //03-0820.AUD	Any murder is horrible. And unfortunate.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 3735); //00-3735.AUD	Some are worse than others.
		KIA_Play_Actor_Dialogue(kActorDektora, 830); //03-0830.AUD	But death is the same for all.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 3740); //00-3740.AUD	No argument there.
		break;
	case kClueGrigoriansResources:
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4335); //00-4335.AUD	So you help Replicants escape the city.
		KIA_Play_Actor_Dialogue(kActorGrigorian, 290); //11-0290.AUD	I'm talking figuratively, detective.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4340); //00-4340.AUD	Sure you are.
		KIA_Play_Actor_Dialogue(kActorGrigorian, 320); //11-0320.AUD	We're not children, detective. We have resources.
		KIA_Play_Actor_Dialogue(kActorGrigorian, 330); //11-0330.AUD	Friends with access to vehicles, to escape routes.
		KIA_Play_Actor_Dialogue(kActorGrigorian, 340); //11-0340.AUD	The world is changing.
		break;
	case kClueCar:
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 510); //99-0510.AUD	The car looked a lot like the one I'd been tracking.
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 520); //99-0520.AUD	The driver had been smart enough to pull the license plate.
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 530); //99-0530.AUD	But the vehicle identification number was still there.
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 540); //99-0540.AUD	If I ran it through the Mainframe back at the station, I could ID the owner.
		break;
	case kClueLicensePlateMatch:
		KIA_Play_Actor_Dialogue(kActorAnsweringMachine, 390); // 39-0390.AUD	Begin test.
		KIA_Play_Actor_Dialogue(kActorAnsweringMachine, 420); //39-0420.AUD	Positive result.
		KIA_Play_Actor_Dialogue(kActorAnsweringMachine, 470); //39-0470.AUD	End test.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 7200); //00-7200.AUD	Bingo.
		break;
	case kClueCrazylegsInterview2:
		KIA_Play_Actor_Dialogue(kActorMcCoy, 1915); //00-1915.AUD	You sell a black Sedan a few days ago?
		KIA_Play_Actor_Dialogue(kActorCrazylegs, 820); //09-0820.AUD	Black Sedan? Hey, I got standards. If it ain’t Sporty, I got no room for it.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 2085); //00-2085.AUD	You sold this to a Blake Williams. I’ve seen the registration.
		KIA_Play_Actor_Dialogue(kActorCrazylegs, 900); //09-0900.AUD	Ooh-- Oh, that hurt Sedan.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 2090); //00-2090.AUD	Blake Williams is a fake name.
		KIA_Play_Actor_Dialogue(kActorCrazylegs, 910); //09-0910.AUD	You just never know about some people.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 2095); //Did you forget to run a credit check?
		KIA_Play_Actor_Dialogue(kActorCrazylegs, 920); // 09-0920.AUD	He paid cash.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 2100); //00-2100.AUD	And people come in here and buy cars with cash every day!
		KIA_Play_Actor_Dialogue(kActorCrazylegs, 930); //09-0930.AUD	In this neighborhood every hour is more like it.
		KIA_Play_Actor_Dialogue(kActorCrazylegs, 940); //09-0940.AUD	But then again I do have the best selection in town.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 2105); //00-2105.AUD	What did this guy look like?
	 	KIA_Play_Actor_Dialogue(kActorCrazylegs, 950); //09-0950.AUD	Nothing special. Beard, dark hair. Had these eyes, kinda…
		KIA_Play_Actor_Dialogue(kActorMcCoy, 2110); //00-2110.AUD	Piercing?
		KIA_Play_Actor_Dialogue(kActorCrazylegs, 960); //09-0960.AUD	Yeah. Pretty scary. But, heck, I never turn away a customer.
		break;
	case kClueGordoBlabs:
		KIA_Play_Actor_Dialogue(kActorMcCoy, 6530); //00-6530.AUD	Somebody set me up, Gordo. Who’s behind it? Clovis?
		KIA_Play_Actor_Dialogue(kActorGordo, 1120); //02-1120.AUD	Clovis ain’t no zipper-head He’s capable of pulling a string or two.
		KIA_Play_Actor_Dialogue(kActorGordo, 1130); //02-1130.AUD	But no way he’s a one-man show.
		KIA_Play_Actor_Dialogue(kActorGordo, 1160); //02-1160.AUD	Shoot. All you gotta do is look to your own.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 6565); //00-6565.AUD	Someone inside the Blade Runner unit?
		KIA_Play_Actor_Dialogue(kActorGordo, 1170); //02-1170.AUD	Smart. Real genius level you are.
		break;
	case kClueGuzzaAgreesToMeet:
		KIA_Play_Actor_Dialogue(kActorGuzza, 1450); //04-1450.AUD	What do you want, McCoy?
		KIA_Play_Actor_Dialogue(kActorMcCoy, 6670); //00-6670.AUD	Remove the frame, clear my name and get that guy out of my apartment!
		KIA_Play_Actor_Dialogue(kActorMcCoy, 6675); //00-6675.AUD	I want my life back.
		KIA_Play_Actor_Dialogue(kActorGuzza, 1460); //04-1460.AUD	I can’t do that.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 6680); //00-6680.AUD	You better start finding a way ‘cause I got another call to make.
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
		KIA_Play_Actor_Dialogue(kActorSteele, 2990); //01-2990.AUD	They locked him up in a PoW shuttle but he escaped and hadn’t been heard from since.
		break;
	case kClueGrigoriansResponse1:
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4275); //00-4275.AUD	I want to know about the people who were there.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4280); //00-4280.AUD	The Rastafarian and the Asian guy with the sunglasses.
		KIA_Play_Actor_Dialogue(kActorGrigorian, 130); //11-0130.AUD	I didn't know the Rastafarian.
		KIA_Play_Actor_Dialogue(kActorGrigorian, 140); //11-0140.AUD	The Asian fellow was one of our ex members. Izo was his name.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4305); //00-4305.AUD	How long did you know him for?
		KIA_Play_Actor_Dialogue(kActorGrigorian, 150); //11-0150.AUD	Let's see... I met him about five years ago.
		KIA_Play_Actor_Dialogue(kActorGrigorian, 160); //11-0160.AUD	He seemed so smart and balanced. He really wanted to help the Replicant people.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4310); //00-4310.AUD	Then what?
		KIA_Play_Actor_Dialogue(kActorGrigorian, 170); //11-0170.AUD	He started associating with the more militant factions.
		KIA_Play_Actor_Dialogue(kActorGrigorian, 180); //11-0180.AUD	I was astounded when I heard he was supplying weapons to some of them.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4315); //00-4315.AUD	What kind of weapons?
		KIA_Play_Actor_Dialogue(kActorGrigorian, 190); //11-0190.AUD	Everything and anything.
		KIA_Play_Actor_Dialogue(kActorGrigorian, 200); //11-0200.AUD	Guns so new that even the police had hardly used them I heard.
		break;	
	case kClueGrigoriansResponse2:
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4270); //00-4270.AUD	I got some more questions for you.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4260); //00-4260.AUD	You've been helping Reps, pal?
		KIA_Play_Actor_Dialogue(kActorGrigorian, 360); //11-0360.AUD	Through peaceful protest only.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4380); //00-4380.AUD	So talk to me about the Reps with the black Sedan. I found your note in their car.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4385); //00-4385.AUD	"Help these lost souls." Isn't that what it said?
		KIA_Play_Actor_Dialogue(kActorGrigorian, 370); //11-0370.AUD	We still have freedom of speech in this country. I can write whatever I please.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4390); //00-4390.AUD	This little exercise of your right smells like criminal conspiracy to me, pal.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4395); //00-4395.AUD	How was Crazy-legs supposed to help them?
		KIA_Play_Actor_Dialogue(kActorGrigorian, 380); //11-0380.AUD	You'll have to ask him yourself. I'm not ashamed of what I did. And I'm sure he's not either.
		break;
	case kClueCrazylegGrovels:
		KIA_Play_Actor_Dialogue(kActorMcCoy, 1940); //00-1940.AUD	You know it’s illegal to sell anything to a Replicant.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 1945); //00-1945.AUD	Or to help a Replicant in any way.
		KIA_Play_Actor_Dialogue(kActorCrazylegs, 560); //09-0560.AUD	I didn’t know! I mean it. I was just trying to make a sale--
		KIA_Play_Actor_Dialogue(kActorMcCoy, 1950); //00-1950.AUD	Unscrupulous businessman, eh?
		KIA_Play_Actor_Dialogue(kActorCrazylegs, 570); //09-0570.AUD	Hey, they came to me first. I didn’t go to them.
		KIA_Play_Actor_Dialogue(kActorCrazylegs, 580); //09-0580.AUD	Look, I know we can work out some kind of deal here.
		KIA_Play_Actor_Dialogue(kActorCrazylegs, 590); //09-0590.AUD	You like that Bishy Caddy, right? I’ll give it to you at the absolute lowest price.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 1990); //00-1990.AUD	Sounds like a bribe to me.
		KIA_Play_Actor_Dialogue(kActorCrazylegs, 600); //09-0600.AUD	Not a bribe. Just a gift. You know, out of friendship.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 1995); //00-1995.AUD	We ain’t friends, Crazy.
		break;
	case kClueEarlyInterviewB1:
		KIA_Play_Actor_Dialogue(kActorMcCoy, 3510); //00-3510.AUD	This girl one of yours?
		KIA_Play_Actor_Dialogue(kActorEarlyQ, 580); //18-0580.AUD	Hey. That kinda looks like Hecuba. The one I lent the jewelry to?
		KIA_Play_Actor_Dialogue(kActorMcCoy, 3560); //00-3560.AUD	Yeah? What’s her real name?
		KIA_Play_Actor_Dialogue(kActorEarlyQ, 590); //18-0590.AUD	That’s it.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 3565); //00-3565.AUD	There hasn’t been an exotic dancer who used her real name since Jesus was a pup.
		KIA_Play_Actor_Dialogue(kActorEarlyQ, 600); //18-0600.AUD	(laughs) Okay, you got me. Dektora is the name on her work card. Let me tell you, General. She works it like a freaking house of fire.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 3570); //00-3570.AUD	I’m gonna want to talk to her. When is she up?
		KIA_Play_Actor_Dialogue(kActorEarlyQ, 620); //18-0620.AUD	Next, General. Have a couple of drinks, relax a little. But wait until her act is over. I don’t want to deprive a lady of her livelihood.
		break;
	case kClueEarlyInterviewB2:
		KIA_Play_Actor_Dialogue(kActorEarlyQ, 200); //18-0200.AUD	But I know you’re gonna be thankful I put those cameras in.
		KIA_Play_Actor_Dialogue(kActorEarlyQ, 210); //18-0210.AUD	Hey, check out Dektora’s bearded boy-toy.
		KIA_Play_Actor_Dialogue(kActorEarlyQ, 220); //18-0220.AUD	Eh, he’s here all the time. You can be sure he ain’t coming around for the witty conversation.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 3430); //00-3430.AUD	What makes you think he’s a Replicant?
		KIA_Play_Actor_Dialogue(kActorEarlyQ, 240); //18-0240.AUD	He walked right by my dancers. Didn’t even pop a stiffy.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 3435); //00-3435.AUD	Maybe he swings another way.
		KIA_Play_Actor_Dialogue(kActorEarlyQ, 250); //18-0250.AUD	Oh, come on, McCoy. Have you seen my girls? Besides, I heard him talking to Dektora. They got friends who are gonna help them get Off-World. I’m telling you, they got a whole little Replicant love fest going on.
		break;
	case kClueCrazylegsInterview3:
		KIA_Play_Actor_Dialogue(kActorGrigorian, 300); //11-0300.AUD	You support the cause, don't you Larry?
		KIA_Play_Actor_Dialogue(kActorCrazylegs, 1010); //09-1010.AUD	Hey, now don’t bring me into it.
		KIA_Play_Actor_Dialogue(kActorGrigorian, 310); //11-0310.AUD	You don't have to be ashamed of your feelings tow---
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4345); //00-4345.AUD	Are you supplying vehicles for this venture, Crazy?
		KIA_Play_Actor_Dialogue(kActorCrazylegs, 1020); //09-1020.AUD	Well, for some kind of Underground Railroad why would I waste my inventory on that?
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4350); //00-4350.AUD	You tell me.
		KIA_Play_Actor_Dialogue(kActorCrazylegs, 1030); //09-1030.AUD	I don’t care whether they’re Reps or humans as long as the chinyen is real.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4355); //00-4355.AUD	So you were ready to do business with the Reps who dropped by your place.
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
		KIA_Play_Actor_Dialogue(kActorSteele, 3200); //01-3200.AUD	I got to teach McCoy how to run the Machine before he hurts somebody.
		break;
	case kClueCrystalTestedBulletBob:
		KIA_Play_Actor_Dialogue(kActorSteele, 3000); //01-3000.AUD	Bullet Bob may be a grade A psycho but he ain’t no Replicant.
		KIA_Play_Actor_Dialogue(kActorSteele, 3010); //01-3010.AUD	I’m starting to think McCoy can’t run the Machine worth diddly.
		KIA_Play_Actor_Dialogue(kActorSteele, 3020); //01-3020.AUD	Though knowing him, he might have been yanking my chain on purpose.
		KIA_Play_Actor_Dialogue(kActorSteele, 3030); //01-3030.AUD	Either way he’s got some explaining to do.
		break;
	case kClueDektoraConfession:
		KIA_Play_Actor_Dialogue(kActorDektora, 1010); //03-1010.AUD	I’m not worried. She may kill some of us but not all of us. Clovis will see to that.
		break;
	case kClueClovisOrdersMcCoysDeath:
		KIA_Play_Actor_Dialogue(kActorClovis, 650); //05-0650.AUD	So, what should we do with this detective. He’s been so persistent, so industrious.
		KIA_Play_Actor_Dialogue(kActorSadik, 370); //08-0370.AUD	You know what I would do, mon.
		KIA_Play_Actor_Dialogue(kActorClovis, 1320); //05-1320.AUD	Perhaps you’re right. It’s over.
		break;
	case kClueMcCoyRetiredGordo:
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 1410); //99-1410.AUD	I’d retired another Replicant so more money was headed my way but I didn’t feel so good about it.
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 1430); //99-1430.AUD	Even though Gordo had almost nailed me first.
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 1440); //99-1440.AUD	All those bad jokes. It was only an entertainment model.
		break;
	case kClueMcCoyRetiredZuben:
		KIA_Play_Actor_Dialogue(kActorGaff, 50); //53-0050.AUD	You V-K the mark before retirement?
		KIA_Play_Actor_Dialogue(kActorMcCoy, 695); //00-0695.AUD	Didn't have to.
		KIA_Play_Actor_Dialogue(kActorGaff, 60); //53-0060.AUD	That's why they call it “the magic”.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 700); //00-0700.AUD	I'm starting to understand.
		KIA_Play_Actor_Dialogue(kActorGaff, 70); //53-0070.AUD	You ever retire human, your career is over. Remember that.
		break;
	case kClueMcCoyRecoveredHoldensBadge:
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4015); //00-4015.AUD	I found Holden's badge.
		KIA_Play_Actor_Dialogue(kActorGuzza, 630); //04-0630.AUD	Damn. Let me guess, you found it in that hotel down in Chinatown.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4085); //00-4085.AUD	Yeah, someone from the department had already been through the room.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4090); //00-4090.AUD	I guess they just missed it.
		KIA_Play_Actor_Dialogue(kActorGuzza, 640); //04-0640.AUD	That's the old-timer's case. The one we brought back on contract.
		KIA_Play_Actor_Dialogue(kActorGuzza, 650); //04-0650.AUD	Bryant's got faith in this guy but I gotta wonder about any son of a bitch who can miss a badge in a room that small.
		KIA_Play_Actor_Dialogue(kActorGuzza, 670); //04-0670.AUD	This Deckard, he feels too much, you know? He's too far along the curve.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4095); //00-4095.AUD	Did he retire the Rep who shot Holden?
		KIA_Play_Actor_Dialogue(kActorGuzza, 680); //04-0680.AUD	Bryant said he did, yeah. I guess he's getting the job done.
		KIA_Play_Actor_Dialogue(kActorGuzza, 690); //04-0690.AUD	Holden will be glad to get this back, kid. You've done good.
		break;
	case kClueCrystalRetiredGordo:
		KIA_Play_Actor_Dialogue(kActorSteele, 1070); //01-1070.AUD	Guess whose killer instinct wasn’t quite killer enough.
		KIA_Play_Actor_Dialogue(kActorSteele, 1260); //01-1260.AUD	Screwed the pooch, Slim.
		KIA_Play_Actor_Dialogue(kActorSteele, 1270); //01-1270.AUD	If you were just a little faster, the retirement money would have been yours.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 3065); //00-3065.AUD	You mean we’re not gonna share?
		KIA_Play_Actor_Dialogue(kActorSteele, 1280); //01-1280.AUD	This is the real world, Slim. Not some candy-ass video game.
		KIA_Play_Actor_Dialogue(kActorSteele, 1290); //01-1290.AUD	I better call this in. Your vehicle close by?
		break;
	case kClueSightingDektora:
		KIA_Play_Actor_Dialogue(kActorSteele, 1510); //01-1510.AUD	That stripper you interviewed. She’s one of them.
		KIA_Play_Actor_Dialogue(kActorSteele, 1520); //01-1520.AUD	Figure it out! She must have made the call to Baker and that other Bozo.
		KIA_Play_Actor_Dialogue(kActorSteele, 1530); //01-1530.AUD	Let’s attend to some business.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 3170); //00-3170.AUD	I’m there.
		break;
	case kClueSuspectDektora:
		KIA_Play_Actor_Dialogue(kActorSteele, 2890); //01-2890.AUD	I knew I’d seen her somewhere before, but I had to dig real deep to find it.
		KIA_Play_Actor_Dialogue(kActorSteele, 2900); //01-2900.AUD	Somebody had tried to bury the incept photos and files of all the Reps who came down on the moonbus.
		break;
	case kClueSightingSadikBradbury:
		KIA_Play_Actor_Dialogue(kActorClovis, 0); //05-0000.AUD	That'll do, Sadik.
		KIA_Play_Actor_Dialogue(kActorClovis, 10); //05-0010.AUD	Enough!
		KIA_Play_Actor_Dialogue(kActorSadik, 0); //08-0000.AUD	How you think he found us, mon?
		KIA_Play_Actor_Dialogue(kActorClovis, 20); //05-0020.AUD	One of the Design sub-cons must have talked.
		KIA_Play_Actor_Dialogue(kActorClovis, 30); //05-0030.AUD	Unstable personalities to say the least.
		KIA_Play_Actor_Dialogue(kActorSadik, 10); //08-0010.AUD	I told you we should have blown up the whole block.
		KIA_Play_Actor_Dialogue(kActorClovis, 40); //05-0040.AUD	It would have created problems down the line.
		KIA_Play_Actor_Dialogue(kActorSadik, 20); //08-0020.AUD	We got problem now, mon.
		KIA_Play_Actor_Dialogue(kActorClovis, 50); //05-0050.AUD	This one? He's not a problem. He's an opportunity.
		KIA_Play_Actor_Dialogue(kActorClovis, 60); //05-0060.AUD	You're weak my friend. I expected so much more from you.
		KIA_Play_Actor_Dialogue(kActorSadik, 30); //08-0030.AUD	I'm thinkin' our brother not hearin' too good.
		KIA_Play_Actor_Dialogue(kActorClovis, 70); //05-0070.AUD	Oh, he hears us.
		KIA_Play_Actor_Dialogue(kActorClovis, 80); //05-0080.AUD	Isn't that right, McCoy?
		KIA_Play_Actor_Dialogue(kActorSadik, 40); //08-0040.AUD	You ready to give up fruitless nightmare, mon?
		KIA_Play_Actor_Dialogue(kActorSadik, 50); //08-0050.AUD	Come back to family?
		KIA_Play_Actor_Dialogue(kActorClovis, 90); //05-0090.AUD	He doesn't have a choice.
		KIA_Play_Actor_Dialogue(kActorClovis, 100); //05-0100.AUD	He never did.
		break;
	case kClueCrystalRetiredIzo:
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4825); //00-4825.AUD	What are you doing here?
		KIA_Play_Actor_Dialogue(kActorSteele, 1870); //01-1870.AUD	Tracking this piece of shit.
		KIA_Play_Actor_Dialogue(kActorSteele, 1880); ////01-1880.AUD What are you doing here besides putting your nuts on the chopping block?
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4830); //00-4830.AUD	Investigating Izo. Maybe we should compare notes.
		KIA_Play_Actor_Dialogue(kActorSteele, 1910); //01-1910.AUD	I'll wait for the uniforms. Why don't you grab yourself a slice of quiche or something.
		break;
	case kClueMcCoyRetiredDektora:
		KIA_Play_Actor_Dialogue(kActorSteele, 1750); //01-1750.AUD	Been pretty busy haven’t you, Slim?
		KIA_Play_Actor_Dialogue(kActorMcCoy, 3815); //00-3815.AUD	I think we can safely say that one’s in bio-mechanical purgatory.
		KIA_Play_Actor_Dialogue(kActorSteele, 1760); //01-1760.AUD	You had to clear out everything else up here too.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 3820); //00-3820.AUD	Hope Early’s got insurance.
		KIA_Play_Actor_Dialogue(kActorSteele, 1770); //01-1770.AUD	Putz employs Replicants, he oughta expect the worst.
		KIA_Play_Actor_Dialogue(kActorSteele, 1780); //01-1780.AUD	(sigh) Sorry I missed all the laughs.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 3825); //00-3825.AUD	Next time.
		break;
	case kClueMcCoyRetiredLucy:
		KIA_Play_Actor_Dialogue(kActorMcCoy, 1560); //00-1560.AUD	Commerce is our business.
		KIA_Play_Actor_Dialogue(kActorSteele, 100); //01-0100.AUD	Unless Tyrell can design a faster brain processor, I’m gonna get pretty damn bored with this gig.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 1575); //00-1575.AUD	You don’t feel bad about juicing a little girl?
		KIA_Play_Actor_Dialogue(kActorSteele, 120); //01-0120.AUD	She was an it, Slim. Don’t you forget that.
		KIA_Play_Actor_Dialogue(kActorSteele, 130); //01-0130.AUD	Let’s go find your Spinner. Report in.
		break;
	case kClueSightingClovis:
		KIA_Play_Actor_Dialogue(kActorMcCoy, 5745); //00-5745.AUD	Where’s Clovis now?
		KIA_Play_Actor_Dialogue(kActorLuther, 340); //10-0340.AUD	Clovis has gone to see Eldon.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 8695); //00-8965.AUD	What for?
		KIA_Play_Actor_Dialogue(kActorLance, 240); //13-0240.AUD	Gone to have a little heart to heart with Eldon.
		KIA_Play_Actor_Dialogue(kActorLuther, 280); //10-0280.AUD	We showed him how to get in through the basement.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 5815); //00-5815.AUD	He’ll kill Tyrell, if he gets to him.
		KIA_Play_Actor_Dialogue(kActorLance, 250); //13-0250.AUD	Isn’t that just too bad.	 
		KIA_Play_Actor_Dialogue(kActorLuther, 290); //10-0290.AUD	I won’t shed any tears. Tyrell is killing us all. Four years isn’t enough, is it?
		KIA_Play_Actor_Dialogue(kActorLance, 260); //13-0260.AUD	If Clovis snaps his neck, it will be merciful and quick. That’s a hell of a lot more than we’ve been given.
		break;
	case kClueMoonbus2:
		KIA_Play_Actor_Dialogue(kActorMcCoy, 5390); //00-5390.AUD	You heard about the moonbus hijacking?
		KIA_Play_Actor_Dialogue(kActorMcCoy, 5395); //00-5395.AUD	Yeah, I guess you would have. 50 people dead.
		KIA_Play_Actor_Dialogue(kActorRachael, 630); // 57-0630.AUD	You can't blame--
		KIA_Play_Actor_Dialogue(kActorMcCoy, 5400);	 //00-5400.AUD	I'm surprised you are not doing spin control.
		KIA_Play_Actor_Dialogue(kActorRachael, 650); //57-0650.AUD	They-- There are safeguards in the design.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 5415); //00-5415.AUD	Yeah, I've seen the data. Implanted memories. A four-year lifespan.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 5420); //00-5420.AUD	I'd probably get a little crazy too but I don't think I'd start killing people.
		KIA_Play_Actor_Dialogue(kActorRachael, 660); //	57-0660.AUD	Wouldn't you?
		break;
	case kClueEarlyInterviewA:
		KIA_Play_Actor_Dialogue(kActorMcCoy, 3505); //00-3505.AUD	You buy some jewelry at an auction recently? Real old elite stuff?
		KIA_Play_Actor_Dialogue(kActorEarlyQ, 420); //18-0420.AUD	Who’s asking?
		KIA_Play_Actor_Dialogue(kActorEarlyQ, 430); //18-0430.AUD	You ain’t with Robbery-Homicide.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 3530); //00-3530.AUD	No, sir.
		KIA_Play_Actor_Dialogue(kActorEarlyQ, 440); //18-0440.AUD	Eh, those pieces ain’t hot. I got the papers to prove it. I picked them up at a legitimate auction. Cost me nearly a pound of flesh too.
		KIA_Play_Actor_Dialogue(kActorMcCoy, 3535); //00-3535.AUD	You give this stuff to a girlfriend, Early?
		KIA_Play_Actor_Dialogue(kActorEarlyQ, 460); //18-0460.AUD	You kiddin’? I ain’t that stupid. No, no, no, no. I was letting one of my dancers use the stuff in her act. Kind of a tribute to the ancient swamp lands, you know what I mean?
		KIA_Play_Actor_Dialogue(kActorMcCoy, 3540); //00-3540.AUD	Which dancer?
		KIA_Play_Actor_Dialogue(kActorEarlyQ, 490); //18-0490.AUD	Hecuba. She’s going on in a few.
		KIA_Play_Actor_Dialogue(kActorEarlyQ, 500);	//18-0500.AUD	She’s one of my biggest earners too. She ain’t in any trouble now, is she?
		KIA_Play_Actor_Dialogue(kActorMcCoy, 3545); //00-3545.AUD	Not yet.
		KIA_Play_Actor_Dialogue(kActorEarlyQ, 520); //18-0520.AUD	(sighs) Good, good. Wouldn’t wanna slaughter the goose that lays them golden eggs.
		break;
	case kClueBobRobbed:
		KIA_Play_Actor_Dialogue(kActorMcCoy, 4965); //00-4965.AUD	I hear you've been waving guns around on Animoid Row.
		KIA_Play_Actor_Dialogue(kActorBulletBob, 470); //14-0470.AUD	Who's been telling you that crap? That lying Egyptian snake oil salesman?
		KIA_Play_Actor_Dialogue(kActorMcCoy, 5035); //00-5035.AUD	Hasan?
		KIA_Play_Actor_Dialogue(kActorBulletBob, 480); //14-0480.AUD	That's the one. I should have popped him when I had the chance. 
		KIA_Play_Actor_Dialogue(kActorBulletBob, 490); //14-0490.AUD	You want to know what really happened?
		KIA_Play_Actor_Dialogue(kActorBulletBob, 500); //14-0500.AUD	I wanted to get my daughter a present for her birthday, right?
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
		break;
	case kClueWantedPoster:
		KIA_Play_Slice_Model(kModelAnimationGrigoriansNote);
		KIA_Play_Actor_Dialogue(kActorVoiceOver, 4080);	//99-4080.AUD	He looks familiar.
		break;
	default:
		break;
	}
}

} // End of namespace BladeRunner
