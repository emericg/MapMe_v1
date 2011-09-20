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
 * \file GfxManager.cpp
 * \brief Gfx MANAGER
 *
 * Handle graphics ressources of the software...
 */

#include "GfxManager.h"

/* ************************************************************************** */
/* ************************************************************************** */

GfxManager::GfxManager()
{
    std::cout << "GfxManager::GfxManager" << std::endl;                    // debug

    //
}

/* ************************************************************************** */

GfxManager::~GfxManager()
{
    std::cout << "GfxManager::~GfxManager -->  ";                        // debug

    // Close libraries
    //TTF_Quit();
    //SDL_Quit();
}

/* ************************************************************************** */
/* ************************************************************************** */

bool GfxManager::createScreen()
{
    std::cout << "(function) GfxManager::createScreen" << std::endl;            // debug

    // Configuration access
    ConfigManager &ConfigManager= ConfigManager::getInstance();
    resx= ConfigManager.getX();
    resy= ConfigManager.getY();
    ratio= static_cast<double>(resx/1280.0);


    // Initialize SDL video
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cerr << "   ERROR : Unable to initialize SDL video mode : " << SDL_GetError() << std::endl;
        return false;
    }

    // Set video flags
    int videoFlags= SDL_SWSURFACE | SDL_RLEACCEL;// | SDL_ANYFORMAT;
    if (ConfigManager.getFS())
    {
        videoFlags |= SDL_FULLSCREEN;
    }

    // Create a new window
    std::cout << "   Creating " << resx << "x" << resy << " video window." << std::endl;
    screen= SDL_SetVideoMode(resx, resy, 32, videoFlags);
    if (!screen)
    {
        std::cerr << "   ERROR : Unable to initialize a video window : " << SDL_GetError() << std::endl;
        return false;
    }

    if (ConfigManager.getFS() == 0)
    {
        // Window icon
        SDL_Surface *icon= IMG_Load("ressources/gfx/icons/icon.png");
        SDL_WM_SetIcon(icon, NULL);
        SDL_FreeSurface(icon);

        // Window caption
        SDL_WM_SetCaption("MapMe    [0.67dev]", NULL);
    }

    // Show cursor
    SDL_ShowCursor(SDL_ENABLE);

    //Initialize SDL_ttf
    if (TTF_Init() < 0)
    {
        std::cerr << "   ERROR : Unable to initialize SDL_ttf : " << SDL_GetError() << std::endl;
        return false;
    }

    return true;
}

/* ************************************************************************** */

bool GfxManager::destroyScreen()
{
    std::cout << "(function) GfxManager::destroyScreen" << std::endl;    // debug

    // Free screen
    SDL_FreeSurface(screen);

    if (screen == NULL)
        return true;

    return false;
}

/* ************************************************************************** */

void GfxManager::loadingScreen()
{
    std::cout << "(function) GfxManager::loadingScreen" << std::endl;    // debug

    // Load, draw, unload !
    SDL_Surface *loading;
    SDL_Rect rloading;
        loading= IMG_Load("ressources/gfx/menu/loading.png");
        rloading.x= static_cast<int>(resx/2.0 - 200);
        rloading.y= static_cast<int>(resy/2.0 - 112);

    SDL_BlitSurface(loading, NULL, screen, &rloading);
    SDL_FreeSurface(loading);

    // Flip video buffers
    flipVideoBuffers();
}

/* ************************************************************************** */

void GfxManager::loadRessources(short choice)
{
    std::cout << "(function) GfxManager::loadRessources" << std::endl;        // debug

    if (choice == 0 || choice == 1)
    {
        // Load positions
        rarea.x= static_cast<int>(resx*0.0094);
        rarea.y= static_cast<int>(resy*0.017);
            rmenubutton.x= static_cast<int>(resx*0.050);
            rmenubutton.y= static_cast<int>(resy*0.764);
            rselection_options.x= 0;
            rselection_options.y= 0;
        rmenubar.x= 0;
        rmenubar.y= static_cast<int>(resy*0.922);
            rmenubar_exit.x= 0;
            rmenubar_exit.y= static_cast<int>(resy*0.360);

        // Load GFX
        if (ratio == 1)
            menuLoadOnly();
        else
            menuLoadAndResize();
    }


    if (choice == 0 || choice == 2)
    {
        // Load colors
        color_white.r= 255;
        color_white.g= 255;
        color_white.b= 255;
        color_black.r= 0;
        color_black.g= 0;
        color_black.b= 0;

        color_grey.r= 137;
        color_grey.g= 146;
        color_grey.b= 173;
        color_orange.r= 255;
        color_orange.g= 164;
        color_orange.b= 0;

        // Load fonts
        font_gui_28= TTF_OpenFont("ressources/fonts/FreeSans.ttf", static_cast<int>(28*ratio));
        font_gui_30= TTF_OpenFont("ressources/fonts/FreeSans.ttf", static_cast<int>(30*ratio));
        font_gui_52= TTF_OpenFont("ressources/fonts/DejaVuSerif-Bold.ttf", static_cast<int>(52*ratio));

        // Load positions
        rgui_upmenu.x= static_cast<int>(resx*0.0094);
        rgui_upmenu.y= 0;

        rgui_location_left.x= static_cast<int>(resx*0.0094);
        rgui_location_left.y= static_cast<int>(resy*0.9347);
        gui_location_center= SDL_CreateRGBSurface(SDL_SWSURFACE, static_cast<int>(resx*0.7*ratio), static_cast<int>(35*ratio), 32, 255, 255, 255, 0);
        SDL_FillRect(gui_location_center, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
            rgui_location_center_dest.x= static_cast<int>(resx*0.0362);
            rgui_location_center_dest.y= static_cast<int>(resy*0.9347);
            rgui_location_center_src.x= 0;
            rgui_location_center_src.y= 0;
            rgui_location_center_src.w= static_cast<int>(400*ratio);
            rgui_location_center_src.h= static_cast<int>(35*ratio);
        rgui_location_right.x= static_cast<int>(resx*0.0367);
        rgui_location_right.y= static_cast<int>(resy*0.9347);

        rgui_time_zone.x= -1;
        rgui_time_zone.y= static_cast<int>(resy*0.9347);
        gui_time= SDL_CreateRGBSurface(SDL_SWSURFACE, static_cast<int>(449*ratio), static_cast<int>(35*ratio), 32, 0, 0, 0, 0);
        SDL_FillRect(gui_time, NULL, SDL_MapRGB(screen->format, 255, 164, 0));
        rgui_time_src.x= 0;
        rgui_time_src.y= 0;
        rgui_time_src.w= -1;
        rgui_time_src.h= static_cast<int>(17*ratio);
        rgui_time_dest.x= -1;
        rgui_time_dest.y= static_cast<int>(resy*0.946);
        rgui_score.x= static_cast<int>(resx*0.8500);
        rgui_score.y= static_cast<int>(resy*0.9347);

        //
        button_zoompos= 1.0;
        notify_zoompos= 1.86;
        notify_fadepos= 0;
        button2= SDL_CreateRGBSurface(SDL_SWSURFACE, static_cast<int>(256*ratio), static_cast<int>(20*ratio), 32, 0, 0, 0, 0);
        SDL_FillRect(button2, NULL, SDL_MapRGB(screen->format, 67, 114, 126));

        rgui_notification.x= static_cast<int>(resx*0.3494);
        rgui_notification.y= static_cast<int>(resy*0.2337);
        rgui_notification.w= static_cast<int>(320*ratio);
        rgui_notification.h= static_cast<int>(345*ratio);

        rgui_notification_up.x= 0;
        rgui_notification_up.y= 0;
        rgui_notification_up.w= static_cast<int>(320*ratio);
        rgui_notification_up.h= static_cast<int>(80*ratio);

        rgui_notification_down.x= 0;
        rgui_notification_down.y= static_cast<int>(80*ratio);
        rgui_notification_down.w= static_cast<int>(320*ratio);
        rgui_notification_down.h= static_cast<int>(265*ratio);

        notify1= SDL_CreateRGBSurface(SDL_SWSURFACE, static_cast<int>(320*ratio), static_cast<int>(345*ratio), 32, 0, 0, 0, 0);
        SDL_SetAlpha(notify1, SDL_SRCALPHA | SDL_RLEACCEL, 220);

        rbutton.x= static_cast<int>(rgui_notification_down.w/2.0 - 256.0/2.0);
        rbutton.y= 0;
        rbutton.w= static_cast<int>(256*ratio);
        rbutton.h= static_cast<int>(32*ratio);

        rnotificationtime_src.x= 0;
        rnotificationtime_src.y= 0;
        rnotificationtime_src.w= -1;
        rnotificationtime_src.h= static_cast<int>(20*ratio);

        rnotificationtime_dest.x= 0;
        rnotificationtime_dest.y= static_cast<int>(6*ratio);

        buttontemp1= SDL_CreateRGBSurface(SDL_SWSURFACE, static_cast<int>(256*ratio), static_cast<int>(32*ratio), 32, 0, 0, 0, 0);
        //buttontemp2= SDL_CreateRGBSurface(SDL_SWSURFACE, static_cast<int>(resx*0.2), static_cast<int>(resy*0.1), 32, 0, 0, 0, 0);

        // Game menu
        rgamemenu.x= 0;
        rgamemenu.y= static_cast<int>(resy*0.35);

        // Notification texts
        rtxt_gamelevel.x= 0;
        rtxt_gamelevel.y= static_cast<int>(12*ratio);
        rtxt_gamestage_legend.x= static_cast<int>(10*ratio);
        rtxt_gamestage_legend.y= static_cast<int>(100*ratio);
        rtxt_gamediff_legend.x= static_cast<int>(10*ratio);
        rtxt_gamediff_legend.y= static_cast<int>(150*ratio);
        rtxt_gamestage.x= -1;
        rtxt_gamestage.y= static_cast<int>(100*ratio);
        rtxt_gamediff.x= -1;
        rtxt_gamediff.y= static_cast<int>(150*ratio);
        rtxt_notification_button1_src.x= 0;
        rtxt_notification_button1_src.y= static_cast<int>(4*ratio);
        rtxt_notification_button1_src.w= -1;
        rtxt_notification_button1_src.h= -1;
        rtxt_notification_button1_dest.x= static_cast<int>(rbutton.w*0.29);
        rtxt_notification_button1_dest.y= 0;


        // GUI texts
        rtxt_upmenu_menu.x= static_cast<int>(resx*0.014);
        rtxt_upmenu_menu.y= 0;
        rtxt_upmenu_pause.x= static_cast<int>(resx*0.0875);
        rtxt_upmenu_pause.y= 0;
            rtxt_upmenu_src.x= 0;
            rtxt_upmenu_src.y= static_cast<int>(4*ratio);
            rtxt_upmenu_src.w= -1;
            rtxt_upmenu_src.h= -1;

        rtxt_location.x= static_cast<int>(resx*0.03550);
        rtxt_location.y= static_cast<int>(resy*0.9315);
        rtxt_gamescore.x= static_cast<int>(resx*0.8780);
        rtxt_gamescore.y= static_cast<int>(resy*0.9310);

        rtxt_score2.x= static_cast<int>(resx*0.600);
        rtxt_score2.y= static_cast<int>(resy*0.9420);
        rtxt_score1.x= static_cast<int>(resx*0.776);
        rtxt_score1.y= static_cast<int>(resy*0.9420);

        txt_upmenu_menu= TTF_RenderUTF8_Blended(font_gui_30, "Menu", color_grey);
        txt_upmenu_menu_active= TTF_RenderUTF8_Blended(font_gui_30, "Menu", color_orange);
        txt_upmenu_pause= TTF_RenderUTF8_Blended(font_gui_30, "Pause", color_grey);
        txt_upmenu_pause_active= TTF_RenderUTF8_Blended(font_gui_30, "Pause", color_orange);
        txt_gamestage_legend= TTF_RenderUTF8_Blended(font_gui_30, "Challenge", color_orange);
        txt_gamediff_legend= TTF_RenderUTF8_Blended(font_gui_30, "Difficulté", color_orange);
        txt_notification_button1= TTF_RenderUTF8_Blended(font_gui_30, "Jouer !", color_white);

        // Load GFX
        if (ratio == 1)
            gameLoadOnly();
        else
            gameLoadAndResize();
    }
}

/* ************************************************************************** */

void GfxManager::unloadRessources(short choice)
{
    std::cout << "(function) GfxManager::unloadRessources" << std::endl;        // debug

    if (choice == 0 || choice == 1)    // MENU
    {
        // Surfaces
        SDL_FreeSurface(background);

        //SDL_FreeSurface(area_play);
        SDL_FreeSurface(area_infos);
        SDL_FreeSurface(area_options);
            SDL_FreeSurface(area_options_selection);
            SDL_FreeSurface(area_options_button_apply);

        SDL_FreeSurface(menubar_play);
        SDL_FreeSurface(menubar_infos);
        SDL_FreeSurface(menubar_options);
        SDL_FreeSurface(menubar_exit);
            SDL_FreeSurface(menubar_exit_yes);
            SDL_FreeSurface(menubar_exit_no);
    }

    if (choice == 0 || choice == 2)    // GAME
    {
        // Surfaces
        SDL_FreeSurface(map);

        SDL_FreeSurface(cursor_user);
        SDL_FreeSurface(cursor_system);

        SDL_FreeSurface(button1);
        SDL_FreeSurface(button2);
        SDL_FreeSurface(buttontemp1);
        SDL_FreeSurface(notify1);

        SDL_FreeSurface(gamemenu_exit_yes);
        SDL_FreeSurface(gamemenu_exit_no);
        SDL_FreeSurface(gamemenu_exit_menu);

        // Texts
        SDL_FreeSurface(txt_notification_button1);
        SDL_FreeSurface(txt_gamestage);
        SDL_FreeSurface(txt_gamediff);
        SDL_FreeSurface(txt_gamelevel);
        SDL_FreeSurface(txt_location);
        SDL_FreeSurface(txt_gamescore);
        SDL_FreeSurface(txt_score2);
        SDL_FreeSurface(txt_score1);

        // Fonts
        TTF_CloseFont(font_gui_28);
        TTF_CloseFont(font_gui_30);
        TTF_CloseFont(font_gui_52);
    }
}

/* ************************************************************************** */

void GfxManager::flipVideoBuffers()
{
    //std::cout << "(function) GfxManager::flipVideoBuffers" << std::endl;        // debug

    // Flip buffers
    SDL_Flip(screen);
}

/* ************************************************************************** */
/* ************************************************************************** */

void GfxManager::menuLoadOnly()
{
    std::cout << "(function) GfxManager::menuLoadOnly" << std::endl;        // debug

    SDL_Surface *temp;

    temp= IMG_Load("ressources/gfx/menu/background.png");
    background= SDL_DisplayFormat(temp);

    //temp= IMG_Load("ressources/gfx/menu/area_play.png");
    //area_play= SDL_DisplayFormatAlpha(temp);
    temp= IMG_Load("ressources/gfx/menu/area_infos.png");
    area_infos= SDL_DisplayFormatAlpha(temp);
    temp= IMG_Load("ressources/gfx/menu/area_options.png");
    area_options= SDL_DisplayFormatAlpha(temp);
        temp= IMG_Load("ressources/gfx/menu/area_options_selection.png");
        area_options_selection= SDL_DisplayFormatAlpha(temp);
        temp= IMG_Load("ressources/gfx/menu/area_options_button_apply.png");
        area_options_button_apply= SDL_DisplayFormatAlpha(temp);

    temp= IMG_Load("ressources/gfx/menu/menubar_play.png");
    menubar_play= SDL_DisplayFormatAlpha(temp);
    temp= IMG_Load("ressources/gfx/menu/menubar_infos.png");
    menubar_infos= SDL_DisplayFormatAlpha(temp);
    temp= IMG_Load("ressources/gfx/menu/menubar_options.png");
    menubar_options= SDL_DisplayFormatAlpha(temp);
    temp= IMG_Load("ressources/gfx/menu/menubar_exit.png");
    menubar_exit= SDL_DisplayFormatAlpha(temp);
        temp= IMG_Load("ressources/gfx/menu/menubar_exit_yes.png");
        menubar_exit_yes= SDL_DisplayFormatAlpha(temp);
        temp= IMG_Load("ressources/gfx/menu/menubar_exit_no.png");
        menubar_exit_no= SDL_DisplayFormatAlpha(temp);

    SDL_FreeSurface(temp);
}

/* ************************************************************************** */

void GfxManager::menuLoadAndResize()
{
    std::cout << "(function) GfxManager::menuLoadAndResize" << std::endl;        // debug

    SDL_Surface *temp, *temp2;

    temp= IMG_Load("ressources/gfx/menu/background.png");
    temp2= SDL_DisplayFormat(temp);
    background= zoomSurface(temp2, ratio, ratio, 1);

    //temp= IMG_Load("ressources/gfx/menu/area_play.png");
    //temp2= SDL_DisplayFormatAlpha(temp);
    //area_play= zoomSurface(temp2, ratio, ratio, 1);
    temp= IMG_Load("ressources/gfx/menu/area_infos.png");
    temp2= SDL_DisplayFormatAlpha(temp);
    area_infos= zoomSurface(temp2, ratio, ratio, 1);
    temp= IMG_Load("ressources/gfx/menu/area_options.png");
    temp2= SDL_DisplayFormatAlpha(temp);
    area_options= zoomSurface(temp2, ratio, ratio, 1);
        temp= IMG_Load("ressources/gfx/menu/area_options_selection.png");
        temp2= SDL_DisplayFormatAlpha(temp);
        area_options_selection= zoomSurface(temp2, ratio, ratio, 1);
        temp= IMG_Load("ressources/gfx/menu/area_options_button_apply.png");
        temp2= SDL_DisplayFormatAlpha(temp);
        area_options_button_apply= zoomSurface(temp2, ratio, ratio, 1);

    temp= IMG_Load("ressources/gfx/menu/menubar_play.png");
    temp2= SDL_DisplayFormatAlpha(temp);
    menubar_play= zoomSurface(temp2, ratio, ratio, 1);
    temp= IMG_Load("ressources/gfx/menu/menubar_infos.png");
    temp2= SDL_DisplayFormatAlpha(temp);
    menubar_infos= zoomSurface(temp2, ratio, ratio, 1);
    temp= IMG_Load("ressources/gfx/menu/menubar_options.png");
    temp2= SDL_DisplayFormatAlpha(temp);
    menubar_options= zoomSurface(temp2, ratio, ratio, 1);
    temp= IMG_Load("ressources/gfx/menu/menubar_exit.png");
    temp2= SDL_DisplayFormatAlpha(temp);
    menubar_exit= zoomSurface(temp2, ratio, ratio, 1);
        temp= IMG_Load("ressources/gfx/menu/menubar_exit_yes.png");
        temp2= SDL_DisplayFormatAlpha(temp);
        menubar_exit_yes= zoomSurface(temp2, ratio, ratio, 1);
        temp= IMG_Load("ressources/gfx/menu/menubar_exit_no.png");
        temp2= SDL_DisplayFormatAlpha(temp);
        menubar_exit_no= zoomSurface(temp2, ratio, ratio, 1);

    SDL_FreeSurface(temp);
    SDL_FreeSurface(temp2);
}

/* ************************************************************************** */

void GfxManager::menuDraw(short menuposition, short menupositioncursor)
{
    //std::cout << "(function) GfxManager::menuDraw" << std::endl;    // debug

    // Draw background
    SDL_BlitSurface(background, NULL, screen, NULL);

    // Draw menu
    if (menupositioncursor == 1)
    {
        SDL_BlitSurface(menubar_play, NULL, screen, &rmenubar);
    }
    else if (menupositioncursor == 2)
    {
        SDL_BlitSurface(menubar_infos, NULL, screen, &rmenubar);
    }
    else if (menupositioncursor == 3)
    {
        SDL_BlitSurface(menubar_options, NULL, screen, &rmenubar);
    }
    else if (menupositioncursor >= 4)
    {
        SDL_BlitSurface(menubar_exit, NULL, screen, &rmenubar);
    }
}

/* ************************************************************************** */

void GfxManager::menuDrawArea(short menuposition, short menupositioncursor)
{
    //std::cout << "(function) GfxManager::menuDrawArea" << std::endl;    // debug

    // draw area
    if (menuposition == 1)
    {
        //SDL_BlitSurface(area_play, NULL, screen, &rarea);
    }
    else if (menuposition == 2)
    {
        SDL_BlitSurface(area_infos, NULL, screen, &rarea);
    }
    else if (menuposition == 3)
    {
        SDL_BlitSurface(area_options, NULL, screen, &rarea);
    }
    else if (menuposition >= 4)
    {
        if (menupositioncursor == 4)
            SDL_BlitSurface(menubar_exit_yes, NULL, screen, &rmenubar_exit);

        if (menupositioncursor == 5)
            SDL_BlitSurface(menubar_exit_no, NULL, screen, &rmenubar_exit);
    }
}

/* ************************************************************************** */
/* ************************************************************************** */

void GfxManager::gameLoadOnly()
{
    std::cout << "(function) GfxManager::gameLoadOnly" << std::endl;        // debug

    SDL_Surface *temp;

    // Map
    temp= IMG_Load("ressources/gfx/maps/worldmap_color.png");
    map= SDL_DisplayFormat(temp);

    // Game
    temp= IMG_Load("ressources/gfx/icons/cursor_user_local.png");
    cursor_user= SDL_DisplayFormatAlpha(temp);
    temp= IMG_Load("ressources/gfx/icons/cursor_system.png");
    cursor_system= SDL_DisplayFormatAlpha(temp);

    // Game menu
    temp= IMG_Load("ressources/gfx/game/gamemenu_exit_yes.png");
    gamemenu_exit_yes= SDL_DisplayFormatAlpha(temp);
    temp= IMG_Load("ressources/gfx/game/gamemenu_exit_no.png");
    gamemenu_exit_no= SDL_DisplayFormatAlpha(temp);
    temp= IMG_Load("ressources/gfx/game/gamemenu_exit_menu.png");
    gamemenu_exit_menu= SDL_DisplayFormatAlpha(temp);

    // New GUI
    temp= IMG_Load("ressources/gfx/gui/gui_notification_up.png");
    gui_notification_up= SDL_DisplayFormat(temp);
    temp= IMG_Load("ressources/gfx/gui/gui_notification_down.png");
    gui_notification_down= SDL_DisplayFormat(temp);
    temp= IMG_Load("ressources/gfx/gui/button_play.png");
    button1= SDL_DisplayFormat(temp);

    temp= IMG_Load("ressources/gfx/gui/gui_upmenu.png");
    gui_upmenu= SDL_DisplayFormatAlpha(temp);

    temp= IMG_Load("ressources/gfx/gui/gui_location_left.png");
    gui_location_left= SDL_DisplayFormatAlpha(temp);
    temp= IMG_Load("ressources/gfx/gui/gui_location_right.png");
    gui_location_right= SDL_DisplayFormatAlpha(temp);

    temp= IMG_Load("ressources/gfx/gui/gui_time_zone.png");
    gui_time_zone= SDL_DisplayFormatAlpha(temp);
    temp= IMG_Load("ressources/gfx/gui/gui_time_icon.png");
    gui_time_icon= SDL_DisplayFormatAlpha(temp);
    temp= IMG_Load("ressources/gfx/gui/gui_score.png");
    gui_score= SDL_DisplayFormatAlpha(temp);

    // Free temporary surface
    SDL_FreeSurface(temp);
}

/* ************************************************************************** */

void GfxManager::gameLoadAndResize()
{
    std::cout << "(function) GfxManager::gameLoadAndResize" << std::endl;        // debug

    SDL_Surface *temp, *temp2;

    // Map
    temp= IMG_Load("ressources/gfx/maps/worldmap_color.png");
    temp2= SDL_DisplayFormat(temp);
    map= zoomSurface(temp2, ratio, ratio, 1);

    // Game
    temp= IMG_Load("ressources/gfx/icons/cursor_user_local.png");
    temp2= SDL_DisplayFormatAlpha(temp);
    cursor_user= zoomSurface(temp2, ratio, ratio, 1);
    temp= IMG_Load("ressources/gfx/icons/cursor_system.png");
    temp2= SDL_DisplayFormatAlpha(temp);
    cursor_system= zoomSurface(temp2, ratio, ratio, 1);

    // Game menu
    temp= IMG_Load("ressources/gfx/game/gamemenu_exit_yes.png");
    temp2= SDL_DisplayFormatAlpha(temp);
    gamemenu_exit_yes= zoomSurface(temp2, ratio, ratio, 1);
    temp= IMG_Load("ressources/gfx/game/gamemenu_exit_no.png");
    temp2= SDL_DisplayFormatAlpha(temp);
    gamemenu_exit_no= zoomSurface(temp2, ratio, ratio, 1);
    temp= IMG_Load("ressources/gfx/game/gamemenu_exit_menu.png");
    temp2= SDL_DisplayFormatAlpha(temp);
    gamemenu_exit_menu= zoomSurface(temp2, ratio, ratio, 1);

    // New GUI
    temp= IMG_Load("ressources/gfx/gui/gui_notification_up.png");
    temp2= SDL_DisplayFormatAlpha(temp);
    gui_notification_up= zoomSurface(temp2, ratio, ratio, 1);

    temp= IMG_Load("ressources/gfx/gui/gui_notification_down.png");
    temp2= SDL_DisplayFormatAlpha(temp);
    gui_notification_down= zoomSurface(temp2, ratio, ratio, 1);
    temp= IMG_Load("ressources/gfx/gui/button_play.png");
    temp2= SDL_DisplayFormatAlpha(temp);
    button1= zoomSurface(temp2, ratio, ratio, 1);

    temp= IMG_Load("ressources/gfx/gui/gui_upmenu.png");
    temp2= SDL_DisplayFormatAlpha(temp);
    gui_upmenu= zoomSurface(temp2, ratio, ratio, 1);

    temp= IMG_Load("ressources/gfx/gui/gui_location_left.png");
    temp2= SDL_DisplayFormatAlpha(temp);
    gui_location_left= zoomSurface(temp2, ratio, ratio, 1);
    temp= IMG_Load("ressources/gfx/gui/gui_location_right.png");
    temp2= SDL_DisplayFormatAlpha(temp);
    gui_location_right= zoomSurface(temp2, ratio, ratio, 1);

    temp= IMG_Load("ressources/gfx/gui/gui_time_zone.png");
    temp2= SDL_DisplayFormatAlpha(temp);
    gui_time_zone= zoomSurface(temp2, ratio, ratio, 1);
    temp= IMG_Load("ressources/gfx/gui/gui_time_icon.png");
    temp2= SDL_DisplayFormatAlpha(temp);
    gui_time_icon= zoomSurface(temp2, ratio, ratio, 1);
    temp= IMG_Load("ressources/gfx/gui/gui_score.png");
    temp2= SDL_DisplayFormatAlpha(temp);
    gui_score= zoomSurface(temp2, ratio, ratio, 1);

    // Free temporary surfaces
    SDL_FreeSurface(temp);
    SDL_FreeSurface(temp2);
}

/* ************************************************************************** */
/* ************************************************************************** */

void GfxManager::GenerateNotificationTexts(short gamelevel, short gamestage, short gamediff)
{
    std::cout << "(function) GfxManager::GenerateNotificationTexts" << std::endl;    // debug

    // Convertions
    std::ostringstream oss;
    oss << gamelevel;
    level= ("Niveau " + oss.str());

    // Reset notification parameters
    notify_fadepos= 0;
    notify_zoompos= 1.86;

    if (gamestage == 1)
    {
        stage= ("capitales");
    }
    else if (gamestage == 2)
    {
        stage= ("villes");
    }

    if (gamediff == 1)
    {
        diff= ("très facile");
    }
    else if (gamediff == 2)
    {
        diff= ("facile");
    }
    else if (gamediff == 3)
    {
        diff= ("moins facile");
    }
    else if (gamediff == 4)
    {
        diff= ("presque dur");
    }
    else
    {
        diff= ("difficile");
    }

    /*    Texts generation    */
    txt_gamelevel= TTF_RenderUTF8_Blended(font_gui_52, level.c_str(), color_white);
    txt_gamestage= TTF_RenderUTF8_Blended(font_gui_30, stage.c_str(), color_grey);
    txt_gamediff= TTF_RenderUTF8_Blended(font_gui_30, diff.c_str(), color_grey);

    /*    Positions generation    */
    rtxt_gamelevel.x= static_cast<int>(gui_notification_down->w/2.0 - txt_gamelevel->w/2.0);
    rtxt_gamestage.x= gui_notification_down->w - txt_gamestage->w - static_cast<int>(10*ratio);
    rtxt_gamediff.x= gui_notification_down->w - txt_gamediff->w - static_cast<int>(10*ratio);
}

/* ************************************************************************** */

void GfxManager::GenerateGUI(City &city, int gamescore)
{
    std::cout << "(function) GfxManager::GenerateGUI" << std::endl;    // debug


    /*    City    */
    if (city.type.empty() == true)
        title= (" " + city.name + " (" + city.country + ")");
    else
        title= (" " + city.name + " (capitale " + city.type + ", " + city.country + ")");


    /*    Types convertion    */
    std::ostringstream cgamescore;
    cgamescore << gamescore;
    score= cgamescore.str();


    /*    Texts generation    */
    txt_location= TTF_RenderUTF8_Blended(font_gui_30, title.c_str(), color_grey);
    txt_gamescore= TTF_RenderUTF8_Blended(font_gui_30, score.c_str(), color_grey);


    /*    Positions generation    */
    rgui_location_center_src.w= txt_location->w;
    rgui_location_right.x= rtxt_location.x + txt_location->w;
    rgui_time_zone.x= static_cast<int>(rgui_location_right.x + gui_location_right->w + 12*ratio);
    rgui_time_dest.x= rgui_time_zone.x;

    rcursor_system.x= static_cast<int>(city.coordinates_x - (13*ratio));
    rcursor_system.y= static_cast<int>(city.coordinates_y - (47*ratio));
    rtxt_gamescore.x= static_cast<int>(resx - txt_gamescore->w - (15*ratio));
}

/* ************************************************************************** */

void GfxManager::GenerateLocationInfos(City &city, short distancekm, short pointsdistance, unsigned int time, short pointstime, int gamescore)
{
    std::cout << "(function) GfxManager::GenerateLocationInfos" << std::endl;    // debug


    /*    Type convertions    */
    std::ostringstream cdistance, cdistancepoints, ctime, ctimepoints, cgamescore;
    cdistance << distancekm;
    cdistancepoints << pointsdistance;
    ctime << time;
    ctimepoints << pointstime;
    cgamescore << gamescore;

    title= city.name + " ";
    score= cgamescore.str();

    if (pointsdistance != 0)
        points1= ("~" + cdistance.str() + "km > " + cdistancepoints.str() + "pts");
    else
        points1= ("~" + cdistance.str() + "km");

    if (pointstime != 0)
        points2= ("bonus temps > " + ctimepoints.str() + "pts");
    else
        points2= (" ");


    /*    Text generations    */
    //txt_location= TTF_RenderUTF8_Blended(font_37, title.c_str(), color_white);
    //txt_score1= TTF_RenderUTF8_Blended(font_37, points1.c_str(), color_green2);
    //txt_score2= TTF_RenderUTF8_Blended(font_37, points2.c_str(), color_green2);
    //txt_gamescore= TTF_RenderUTF8_Blended(font_gui_30, score.c_str(), color_grey);


    /*    Position generations    */
/*
    rtxt_gamescore.x= resx - txt_gamescore->w - 15;
    rtxt_location.x= 7;
    rtxt_score1.x= rtxt_separation[0].x + txt_separation->w + 10;

    if (pointstime == 0)
    {
        rtxt_separation[1].x= 0;
        rtxt_score2.x= 0;
    }
    else
    {
        rtxt_separation[1].x= rtxt_score1.x + txt_score1->w + 10;
        rtxt_score2.x= rtxt_separation[1].x + txt_separation->w + 10;
    }
*/
}

/* ************************************************************************** */
/* ************************************************************************** */

void GfxManager::DrawGameMap()
{
    //std::cout << "(function) GfxManager::DrawGameMap" << std::endl;    // debug

    SDL_BlitSurface(map, NULL, screen, NULL);
}

/* ************************************************************************** */

void GfxManager::DrawGameNotification(double time, bool nextbutton)
{
    //std::cout << "(function) GfxManager::DrawGameNotification" << std::endl;    // debug

    // notification
    SDL_SetColorKey(notify1, SDL_SRCCOLORKEY, SDL_MapRGB(notify1->format, 0, 0, 0));
    SDL_BlitSurface(gui_notification_up, &rgui_notification_up, notify1, NULL);
    SDL_BlitSurface(gui_notification_down, NULL, notify1, &rgui_notification_down);

    SDL_BlitSurface(txt_gamelevel, NULL, notify1, &rtxt_gamelevel);
    SDL_BlitSurface(txt_gamestage_legend, NULL, notify1, &rtxt_gamestage_legend);
    SDL_BlitSurface(txt_gamestage, NULL, notify1, &rtxt_gamestage);
    SDL_BlitSurface(txt_gamediff_legend, NULL, notify1, &rtxt_gamediff_legend);
    SDL_BlitSurface(txt_gamediff, NULL, notify1, &rtxt_gamediff);

    // button
    rnotificationtime_src.w= static_cast<int>(256*ratio*time);

    SDL_BlitSurface(button1, NULL, buttontemp1, NULL);
    SDL_BlitSurface(button2, &rnotificationtime_src, buttontemp1, &rnotificationtime_dest);
    SDL_BlitSurface(txt_notification_button1, &rtxt_notification_button1_src, buttontemp1, &rtxt_notification_button1_dest);


    if (nextbutton == false)
    {
        if (button_zoompos <= 1.0)
        {
            //SDL_SetColorKey(buttontemp1, SDL_SRCCOLORKEY, SDL_MapRGB(buttontemp1->format, 0, 0, 0));

            rbutton.x= static_cast<int>(gui_notification_down->w/2.0 - (256.0*ratio)/2.0);
            rbutton.y= static_cast<int>((notify1->w*0.94));

            SDL_BlitSurface(buttontemp1, NULL, notify1, &rbutton);
        }
        else if (button_zoompos > 1.0)
        {
            button_zoompos -= 0.05;
            SDL_Surface *buttontemp2= zoomSurface(buttontemp1, button_zoompos, button_zoompos, 1);

            rbutton.x= static_cast<int>(gui_notification_down->w/2.0 - (256.0*ratio)*button_zoompos/2.0);
            rbutton.y= static_cast<int>((notify1->w*0.94) - (buttontemp2->h - buttontemp1->h)/2.0);

            SDL_SetColorKey(buttontemp2, SDL_SRCCOLORKEY, SDL_MapRGB(buttontemp2->format, 0, 0, 0));
            SDL_BlitSurface(buttontemp2, NULL, notify1, &rbutton);

            SDL_FreeSurface(buttontemp2);
        }
    }
    else
    {
        if (button_zoompos >= 1.2)
        {
            SDL_Surface *buttontemp2= zoomSurface(buttontemp1, button_zoompos, button_zoompos, 1);

            rbutton.x= static_cast<int>(gui_notification_down->w/2.0 - (256.0*ratio)*button_zoompos/2.0);
            rbutton.y= static_cast<int>((notify1->w*0.94) - (buttontemp2->h - buttontemp1->h)/2.0);

            //SDL_SetColorKey(buttontemp2, SDL_SRCCOLORKEY, SDL_MapRGB(buttontemp2->format, 0, 0, 0));
            SDL_BlitSurface(buttontemp2, NULL, notify1, &rbutton);

            SDL_FreeSurface(buttontemp2);
        }
        else if (button_zoompos < 1.2)
        {
            button_zoompos += 0.05;

            SDL_Surface *buttontemp2= zoomSurface(buttontemp1, button_zoompos, button_zoompos, 1);

            rbutton.x= static_cast<int>(gui_notification_down->w/2.0 - (256.0*ratio)*button_zoompos/2.0);
            rbutton.y= static_cast<int>((notify1->w*0.94) - (buttontemp2->h - buttontemp1->h)/2.0);

            //SDL_SetColorKey(buttontemp2, SDL_SRCCOLORKEY, SDL_MapRGB(buttontemp2->format, 0, 0, 0));
            SDL_BlitSurface(buttontemp2, NULL, notify1, &rbutton);

            SDL_FreeSurface(buttontemp2);
        }
    }


    // Zoom effect
    if (notify_zoompos > 1.0)
    {
        SDL_Surface *notify2= zoomSurface(notify1, notify_zoompos, notify_zoompos, 1);

        rgui_notification.x= static_cast<int>((resx-notify2->w)/2.0);
        rgui_notification.y= static_cast<int>((resy-notify2->h)/2.0);

        SDL_SetAlpha(notify2, SDL_SRCALPHA | SDL_RLEACCEL, notify_fadepos);
        SDL_SetColorKey(notify2, SDL_SRCCOLORKEY, SDL_MapRGB(notify1->format, 0, 0, 0));
        SDL_BlitSurface(notify2, NULL, screen, &rgui_notification);

        notify_zoompos -= 0.05733;
        notify_fadepos += 13;

        SDL_FreeSurface(notify2);
    }
    else
    {
        SDL_BlitSurface(notify1, NULL, screen, &rgui_notification);
    }
}

/* ************************************************************************** */

void GfxManager::DrawGameGUI(double time)
{
    //std::cout << "(function) GfxManager::DrawGameGUI" << std::endl;    // debug

    // New GUI
    SDL_BlitSurface(gui_location_left, NULL, screen, &rgui_location_left);
    SDL_BlitSurface(gui_location_center, &rgui_location_center_src, screen, &rgui_location_center_dest);
    SDL_BlitSurface(txt_location, NULL, screen, &rtxt_location);
    SDL_BlitSurface(gui_location_right, NULL, screen, &rgui_location_right);

    SDL_BlitSurface(gui_time_zone, NULL, screen, &rgui_time_zone);

    //
    rgui_time_src.w= static_cast<int>((349*ratio)*time);
    SDL_BlitSurface(gui_time, &rgui_time_src, screen, &rgui_time_dest);
    SDL_BlitSurface(gui_time_icon, NULL, screen, &rgui_time_zone);

    SDL_BlitSurface(gui_score, NULL, screen, &rgui_score);
    SDL_BlitSurface(txt_gamescore, NULL, screen, &rtxt_gamescore);
}

/* ************************************************************************** */

void GfxManager::DrawGameLocationInfos(SDL_Rect &rusercursor)
{
    //std::cout << "(function) GfxManager::DrawGameLocationInfos" << std::endl;    // debug

    if (rusercursor.x != 0 && rusercursor.y != 0)
    {
        SDL_BlitSurface(cursor_user, NULL, screen, &rusercursor);
    }

    SDL_BlitSurface(cursor_system, NULL, screen, &rcursor_system);

    /*
    //SDL_BlitSurface(txt_score1, NULL, screen, &rtxt_score1);

    if (rtxt_score2.x != 0)
    {
    //    SDL_BlitSurface(txt_score2, NULL, screen, &rtxt_score2);
    }

    SDL_BlitSurface(txt_gamescore, NULL, screen, &rtxt_gamescore);
    */
}

/* ************************************************************************** */

void GfxManager::DrawGameUpMenu(bool menuactive, bool pauseactive)
{
    //std::cout << "(function) GfxManager::DrawGameUpMenu" << std::endl;        // debug

    SDL_BlitSurface(gui_upmenu, NULL, screen, &rgui_upmenu);

    if (menuactive == true)
        SDL_BlitSurface(txt_upmenu_menu_active, &rtxt_upmenu_src, screen, &rtxt_upmenu_menu);
    else
        SDL_BlitSurface(txt_upmenu_menu, &rtxt_upmenu_src, screen, &rtxt_upmenu_menu);

    if (pauseactive == true)
        SDL_BlitSurface(txt_upmenu_pause_active, &rtxt_upmenu_src, screen, &rtxt_upmenu_pause);
    else
        SDL_BlitSurface(txt_upmenu_pause, &rtxt_upmenu_src, screen, &rtxt_upmenu_pause);
}

/* ************************************************************************** */

void GfxManager::DrawGameMenu(short gamemenuposition, short gamemenuposition_cursor)
{
    //std::cout << "(function) GfxManager::DrawGameMenu" << std::endl;        // debug

    if (gamemenuposition_cursor == 0)
        SDL_BlitSurface(gamemenu_exit_yes, NULL, screen, &rgamemenu);
    if (gamemenuposition_cursor == 1)
        SDL_BlitSurface(gamemenu_exit_no, NULL, screen, &rgamemenu);
    if (gamemenuposition_cursor == 2)
        SDL_BlitSurface(gamemenu_exit_menu, NULL, screen, &rgamemenu);
}

/* ************************************************************************** */

void GfxManager::DrawGamePaused()
{
    //std::cout << "(function) GfxManager::DrawGamePaused" << std::endl;        // debug

    /* Creat surface */
    SDL_Surface *pause;
    pause= SDL_CreateRGBSurface(SDL_SWSURFACE, resx, resy, 32, 0, 0, 0, 0);
    SDL_FillRect(pause, NULL, SDL_MapRGB(screen->format, 210, 210, 210));
    SDL_SetAlpha(pause, SDL_SRCALPHA | SDL_RLEACCEL, 220);

    /* Draw */
    SDL_BlitSurface(pause, NULL, screen, NULL);
    //SDL_BlitSurface(txt_gamepaused, NULL, screen, &rtxt_gamepaused);

    /* Free surface */
    SDL_FreeSurface(pause);
}

/* ************************************************************************** */
/* ************************************************************************** */
