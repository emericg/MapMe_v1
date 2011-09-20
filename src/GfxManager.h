/*
    This file is a part of MapMe.

    MapMe is a free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*!
 * \file GfxManager.h
 * \brief Gfx MANAGER (HEADER)
 *
 * Handle graphics ressources of the software...
 */

#ifndef GRAPHMANAGER_H
#define GRAPHMANAGER_H
/* ************************************************************************** */

// C++ standard libraries
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

// C standard library
#include <math.h>

// SDL libraries
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include "sdlgfx/SDL_rotozoom.h"

// Local file(s)
#include "Singleton.h"
#include "ConfigManager.h"
#include "locations.h"

/* ************************************************************************** */

class City;

/*!
 * \class GfxManager
 * \brief Class in charge of drawing everything.
 *
 * This class handle the drawing of the menu and game. Kind of important...
 */
class GfxManager : public Singleton<GfxManager>
{
friend class Singleton<GfxManager>;

public:
    bool createScreen();
    bool destroyScreen();

    void loadRessources(short choice);
    void unloadRessources(short choice);
    void loadingScreen();

    void flipVideoBuffers();

    void menuDraw(short menuposition, short menupositioncursor);
    void menuDrawArea(short menuposition, short menupositioncursor);

    void GenerateNotificationTexts(short gamelevel, short gamestage, short gamediff);
    void GenerateGUI(City &city, int gamescore);
    void GenerateLocationInfos(City &city, short distancekm, short pointsdistance, unsigned int time, short pointstime, int gamescore);

    void DrawGameMap();
    void DrawGameNotification(double time, bool nextbutton);
    void DrawGameGUI(double time);
    void DrawGameLocationInfos(SDL_Rect &rusercursor);
    void DrawGameUpMenu(bool menuactive, bool pauseactive);
    void DrawGameMenu(short gamemenuposition, short gamemenuposition_cursor);

    void DrawGamePaused();

private:
    GfxManager();
    ~GfxManager();

    void menuLoadOnly();
    void menuLoadAndResize();
    void gameLoadOnly();
    void gameLoadAndResize();

/*    SCREEN    */
    SDL_Surface *screen;
    short resx;
    short resy;
    double ratio;

/*    Ressources    */
    // MENU
    SDL_Surface *background;

    SDL_Rect rmenubar;
    SDL_Surface *menubar_play;
    SDL_Surface *menubar_infos;
    SDL_Surface *menubar_options;
    SDL_Surface *menubar_exit;
        SDL_Rect rmenubar_exit;
        SDL_Surface *menubar_exit_yes;
        SDL_Surface *menubar_exit_no;

    SDL_Rect rarea;
    SDL_Rect rmenubutton;
    SDL_Surface *area_infos;
    SDL_Surface *area_options;
        SDL_Rect rselection_options;
        SDL_Surface *area_options_selection;
        SDL_Surface *area_options_button_apply;

    // GAME
    SDL_Surface *map;

    SDL_Surface *cursor_user;
    SDL_Surface *cursor_system;
        SDL_Rect rcursor_system;

    SDL_Surface *button1, *button2, *buttontemp1;
        double button_zoompos;
        SDL_Rect rbutton;
        SDL_Rect rnotificationtime_src;
        SDL_Rect rnotificationtime_dest;
    SDL_Surface *notify1;
        short notify_fadepos;
        double notify_zoompos;

    SDL_Surface *gamemenu_exit_yes;
    SDL_Surface *gamemenu_exit_no;
    SDL_Surface *gamemenu_exit_menu;
        SDL_Rect rgamemenu;

    // New GUI
    SDL_Surface *gui_notification_up;
    SDL_Surface *gui_notification_down;
        SDL_Rect rgui_notification;
        SDL_Rect rgui_notification_up;
        SDL_Rect rgui_notification_down;

    SDL_Surface *gui_upmenu;
        SDL_Rect rgui_upmenu;

    SDL_Surface *gui_location_left;
        SDL_Rect rgui_location_left;
    SDL_Surface *gui_location_center;
        SDL_Rect rgui_location_center_src;
        SDL_Rect rgui_location_center_dest;
    SDL_Surface *gui_location_right;
        SDL_Rect rgui_location_right;
    SDL_Surface *gui_time_zone;
    SDL_Surface *gui_time_icon;
        SDL_Rect rgui_time_zone;
    SDL_Surface *gui_time;
        SDL_Rect rgui_time_src;
        SDL_Rect rgui_time_dest;
    SDL_Surface *gui_score;
        SDL_Rect rgui_score;

    // Fonts
    TTF_Font *font_gui_28, *font_gui_30, *font_gui_32, *font_gui_52;

    // Colors
    SDL_Color color_white, color_black;
    SDL_Color color_grey, color_orange;

    // Strings
    SDL_Rect rtxt_upmenu_src;
    SDL_Surface *txt_upmenu_menu;
    SDL_Surface *txt_upmenu_menu_active;
        SDL_Rect rtxt_upmenu_menu;
    SDL_Surface *txt_upmenu_pause;
    SDL_Surface *txt_upmenu_pause_active;
        SDL_Rect rtxt_upmenu_pause;
    SDL_Surface *txt_notification_button1;
        SDL_Rect rtxt_notification_button1_src;
        SDL_Rect rtxt_notification_button1_dest;

    std::string level, stage, diff, score;
    SDL_Surface *txt_gamelevel;
        SDL_Rect rtxt_gamelevel;
    SDL_Surface *txt_gamestage_legend;
        SDL_Rect rtxt_gamestage_legend;
    SDL_Surface *txt_gamestage;
        SDL_Rect rtxt_gamestage;
    SDL_Surface *txt_gamediff_legend;
        SDL_Rect rtxt_gamediff_legend;
    SDL_Surface *txt_gamediff;
        SDL_Rect rtxt_gamediff;
    SDL_Surface *txt_location;
        SDL_Rect rtxt_location;

    std::string title, points1, points2;
    SDL_Surface *txt_gamescore;
        SDL_Rect rtxt_gamescore;
    SDL_Surface *txt_score1;
        SDL_Rect rtxt_score1;
    SDL_Surface *txt_score2;
        SDL_Rect rtxt_score2;
};

/* ************************************************************************** */
#endif
