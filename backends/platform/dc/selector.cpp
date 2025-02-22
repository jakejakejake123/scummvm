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

#define FORBIDDEN_SYMBOL_ALLOW_ALL

#include <common/scummsys.h>
#include <engines/engine.h>
#include <engines/metaengine.h>
#include <engines/game.h>
#include <base/plugins.h>
#include <common/fs.h>
#include <common/events.h>
#include <common/config-manager.h>
#include "dc.h"
#include "icon.h"
#include "label.h"
#include "dcutils.h"

#include <ronin/gddrive.h>


#define MAX_GAMES 100
#define MAX_DIR 100
#define MAX_PLUGIN_DIRS 100


struct Game
{
  char dir[256];
  char engine_id[256];
  char filename_base[256];
  char text[256];
  Common::Language language;
  Common::Platform platform;
  Icon icon;
  Label label;
};

struct Dir
{
  char name[252];
  char deficon[256];
  Common::FSNode node;
};

static Game the_game;

static bool isIcon(const Common::FSNode &entry)
{
	return entry.getName().hasSuffixIgnoreCase(".ICO");
}

static bool loadIcon(Game &game, Dir *dirs, int num_dirs)
{
  char icofn[520];
  sprintf(icofn, "%s%s.ICO", game.dir, game.filename_base);
  if (game.icon.load(icofn))
	return true;
  for (int i=0; i<num_dirs; i++)
	if (!strcmp(dirs[i].name, game.dir) &&
	   dirs[i].deficon[0]) {
	  sprintf(icofn, "%s%s", game.dir, dirs[i].deficon);
	  if (game.icon.load(icofn))
	return true;
	  break;
	}
  return false;
}

static void makeDefIcon(Icon &icon)
{
#include "deficon.h"
  icon.load(scummvm_icon, sizeof(scummvm_icon));
}

static bool sameOrSubdir(const char *dir1, const char *dir2)
{
  int l1 = strlen(dir1), l2 = strlen(dir2);
  if (l1<=l2)
	return !strcmp(dir1, dir2);
  else
	return !memcmp(dir1, dir2, l2);
}

static bool uniqueGame(const char *base, const char *dir,
		       Common::Language lang, Common::Platform plf,
		       Game *games, int cnt)
{
  while (cnt--)
	if (/*Don't detect the same game in a subdir,
	  this is a workaround for the detector bug in toon... */
	sameOrSubdir(dir, games->dir) &&
	/*!strcmp(dir, games->dir) &&*/
	!scumm_stricmp(base, games->filename_base) &&
	lang == games->language &&
	plf == games->platform)
	  return false;
	else
	  games++;
  return true;
}

static int findGames(Game *games, int max, bool use_ini)
{
  Dir *dirs = new Dir[MAX_DIR];
  int curr_game = 0, curr_dir = 0, num_dirs = 0;

  if (use_ini) {
	Common::ConfigManager::Domain *appDomain =
	  ConfMan.getDomain(Common::ConfigManager::kApplicationDomain);
	Common::ConfigManager::Domain savedAppDomain = *appDomain;
	ConfMan.loadDefaultConfigFile();
	*appDomain = savedAppDomain;
	const Common::ConfigManager::DomainMap &game_domains = ConfMan.getGameDomains();
	for(Common::ConfigManager::DomainMap::const_iterator i =
	  game_domains.begin(); curr_game < max && i != game_domains.end(); i++) {
	  Common::String path = (*i)._value["path"];
	  if (path.size() && path.lastChar() != '/')
	path += "/";
	  int j;
	  for (j=0; j<num_dirs; j++)
	if (path.equals(dirs[j].node.getPath()))
	  break;
	  if (j >= num_dirs) {
	if (num_dirs >= MAX_DIR)
	  continue;
	dirs[j = num_dirs++].node = Common::FSNode(path);
	  }
	  if (curr_game < max) {
	strcpy(games[curr_game].filename_base, (*i)._key.c_str());
	strncpy(games[curr_game].engine_id, (*i)._value["engineid"].c_str(), 256);
	games[curr_game].engine_id[255] = '\0';
	strncpy(games[curr_game].dir, dirs[j].node.getPath().c_str(), 256);
	games[curr_game].dir[255] = '\0';
	games[curr_game].language = Common::UNK_LANG;
	games[curr_game].platform = Common::kPlatformUnknown;
	strcpy(games[curr_game].text, (*i)._value["description"].c_str());
	curr_game++;
	  }
	}
  } else {
	dirs[num_dirs++].node = Common::FSNode("");
  }

  while ((curr_game < max || use_ini) && curr_dir < num_dirs) {
	strncpy(dirs[curr_dir].name, dirs[curr_dir].node.getPath().c_str(), 251);
	dirs[curr_dir].name[250] = '\0';
	if (!dirs[curr_dir].name[0] ||
	dirs[curr_dir].name[strlen(dirs[curr_dir].name)-1] != '/')
	  strcat(dirs[curr_dir].name, "/");
	dirs[curr_dir].deficon[0] = '\0';
	Common::FSList files, fslist;
	dirs[curr_dir++].node.getChildren(fslist, Common::FSNode::kListAll);
	for (Common::FSList::const_iterator entry = fslist.begin(); entry != fslist.end();
	 ++entry) {
	  if (entry->isDirectory()) {
	if (!use_ini && num_dirs < MAX_DIR) {
	  dirs[num_dirs].node = *entry;
	  num_dirs++;
	}
	/* Toonstruck detector needs directories to be present too */
	if(!use_ini)
	  files.push_back(*entry);
	  } else
	if (isIcon(*entry))
	  strcpy(dirs[curr_dir-1].deficon, entry->getName().c_str());
	else if(!use_ini)
	  files.push_back(*entry);
	}

	if (!use_ini) {
	  DetectionResults detectionResults = EngineMan.detectGames(files);
	  DetectedGames candidates = detectionResults.listRecognizedGames();

	  for (DetectedGames::const_iterator ge = candidates.begin();
	   ge != candidates.end(); ++ge)
	if (curr_game < max) {
	  strcpy(games[curr_game].engine_id, ge->engineId.c_str());
	  strcpy(games[curr_game].filename_base, ge->gameId.c_str());
	  strcpy(games[curr_game].dir, dirs[curr_dir-1].name);
	  games[curr_game].language = ge->language;
	  games[curr_game].platform = ge->platform;
	  if (uniqueGame(games[curr_game].filename_base,
			 games[curr_game].dir,
			 games[curr_game].language,
			 games[curr_game].platform, games, curr_game)) {

	    strcpy(games[curr_game].text, ge->description.c_str());
#if 0
	    printf("Registered game <%s> (l:%d p:%d) in <%s> <%s> because of <%s> <*>\n",
		   games[curr_game].text,
		   (int)games[curr_game].language,
		   (int)games[curr_game].platform,
		   games[curr_game].dir, games[curr_game].filename_base,
		   dirs[curr_dir-1].name);
#endif
	    curr_game++;
	  }
	}
	}
  }

  for (int i=0; i<curr_game; i++)
	if (!loadIcon(games[i], dirs, num_dirs))
	  makeDefIcon(games[i].icon);
  delete[] dirs;
  return curr_game;
}

static void drawBackground()
{
  draw_solid_quad(20.0, 20.0, 620.0, 460.0,
		  0xff0000, 0x00ff00, 0x0000ff, 0xffffff);
}

namespace {
  class SelectorDiscSwap : public DiscSwap {
    using DiscSwap::DiscSwap;
  protected:
    virtual void background() override {
	drawBackground();
    }
    virtual void interact() override {
	int mousex = 0, mousey = 0;
	byte shiftFlags;

	int mask = getimask();
	setimask(15);
	handleInput(locked_get_pads(), mousex, mousey, shiftFlags);
	setimask(mask);
    }
  };
}

void waitForDisk()
{
  //printf("waitForDisk, cdstate = %d\n", getCdState());
  SelectorDiscSwap("Please insert game CD.", 0xffff2020).run();
}

static void drawGameLabel(Game &game, int pal, float x, float y,
			  unsigned int argb, int fade = 0, float scale = 1.0)
{
  unsigned int fade_alpha = (255-fade)<<24;

  game.icon.draw(x, y, x+32.0*scale, y+32.0*scale, pal, 0xffffff|fade_alpha);
  game.label.draw(x+54.0*scale, y+4.0*scale, argb|fade_alpha, scale);
}

int gameMenu(Game *games, int num_games)
{
  int top_game = 0, selector_pos = 0;
  int mousex = 0, mousey = 0;
  float y;

  if (!num_games)
	return -1;

  for (;;) {

	if (getCdState()>=6)
	  return -1;

	ta_begin_frame();

	drawBackground();

	ta_commit_end();

	y = 40.0;
	for (int i=top_game, cnt=0; cnt<10 && i<num_games; i++, cnt++) {
	  int pal = 48+(i&15);

	  if (cnt == selector_pos)
	draw_trans_quad(100.0, y, 590.0, y+32.0,
			0x7000ff00, 0x7000ff00, 0x7000ff00, 0x7000ff00);

	  games[i].icon.setPalette(pal);
	  drawGameLabel(games[i], pal, 50.0, y, (cnt == selector_pos?
					     0xffff00 : 0xffffff));
	  y += 40.0;
	}

	ta_commit_frame();

	byte shiftFlags;
	int event;

	int mask = getimask();
	setimask(15);
	event = handleInput(locked_get_pads(), mousex, mousey, shiftFlags);
	setimask(mask);

	if (event==-Common::EVENT_LBUTTONDOWN || event==Common::KEYCODE_RETURN || event==Common::KEYCODE_F5) {
	  int selected_game = top_game + selector_pos;

	  for (int fade=0; fade<=256; fade+=4) {

	ta_begin_frame();

	drawBackground();

	ta_commit_end();

	y = 40.0;

	if (fade < 256)
	  for (int i=top_game, cnt=0; cnt<10 && i<num_games;
	      i++, cnt++, y += 40.0)
	    if (cnt != selector_pos)
	      drawGameLabel(games[i], 48+(i&15), 50.0, y, 0xffffff, fade);

	y = (40.0/256.0 * (selector_pos + 1))*(256-fade) + 80.0/256.0*fade;
	float x = 50.0/256.0*(256-fade) + 160.0/256.0*fade;
	float scale = 1.0+9.0/256.0*fade;

	drawGameLabel(games[selected_game], 48+(selected_game&15), x, y,
		      0xffff00, 0, scale);

	ta_commit_frame();
	  }
	  return selected_game;
	}

	if (mousey>=16) {
	  if (selector_pos + top_game + 1 < num_games)
	if (++selector_pos >= 10) {
	  --selector_pos;
	  ++top_game;
	}
	  mousey -= 16;
	} else if (mousey<=-16) {
	  if (selector_pos + top_game > 0)
	if (--selector_pos < 0) {
	  ++selector_pos;
	  --top_game;
	}
	  mousey += 16;
	}
  }
}

bool selectGame(char *&engineId, char *&ret, char *&dir_ret, Common::Language &lang_ret, Common::Platform &plf_ret, Icon &icon)
{
  Game *games = new Game[MAX_GAMES];
  int selected, num_games;

  for (;;) {
	num_games = findGames(games, MAX_GAMES, true);
	if (!num_games)
	  num_games = findGames(games, MAX_GAMES, false);

	{
	  TextureStack txstack;

	  for (int i=0; i<num_games; i++) {
	    games[i].icon.create_texture();
	    games[i].label.create_texture(games[i].text);
	  }

	  selected = gameMenu(games, num_games);
	}

	if (selected == -1)
	  waitForDisk();
	else
	  break;
  }

  if (selected >= num_games)
	selected = -1;

  if (selected >= 0)
	the_game = games[selected];

  delete[] games;

  if (selected>=0) {
#if 0
	chdir(the_game.dir);
#else
	chdir("/");
	dir_ret = the_game.dir;
#endif
	engineId = the_game.engine_id;
	ret = the_game.filename_base;
	lang_ret = the_game.language;
	plf_ret = the_game.platform;
	icon = the_game.icon;
	return true;
  } else
	return false;
}

#ifdef DYNAMIC_MODULES
static int findPluginDirs(Game *plugin_dirs, int max, const Common::FSNode &base)
{
  Common::FSList fslist;
  int curr_dir = 0;
  base.getChildren(fslist, Common::FSNode::kListDirectoriesOnly);
  for (Common::FSList::const_iterator entry = fslist.begin(); entry != fslist.end();
	   ++entry) {
	if (entry->isDirectory()) {
	  if (curr_dir >= max)
	break;
	  strncpy(plugin_dirs[curr_dir].dir, (*entry).getPath().c_str(), 256);
	  strncpy(plugin_dirs[curr_dir].text, (*entry).getName().c_str(), 256);
	  plugin_dirs[curr_dir].icon.load(NULL, 0, 0);
	  curr_dir++;
	}
  }
  return curr_dir;
}

bool selectPluginDir(Common::String &selection, const Common::FSNode &base)
{
  Game *plugin_dirs = new Game[MAX_PLUGIN_DIRS];
  int selected, num_plugin_dirs;

  num_plugin_dirs = findPluginDirs(plugin_dirs, MAX_PLUGIN_DIRS, base);

  {
    TextureStack txstack;

    for (int i=0; i<num_plugin_dirs; i++) {
	plugin_dirs[i].icon.create_texture();
	plugin_dirs[i].label.create_texture(plugin_dirs[i].text);
    }

    selected = gameMenu(plugin_dirs, num_plugin_dirs);
  }

  if (selected >= num_plugin_dirs)
	selected = -1;

  if (selected >= 0)
	selection = plugin_dirs[selected].dir;

  delete[] plugin_dirs;

  return selected >= 0;
}
#endif
