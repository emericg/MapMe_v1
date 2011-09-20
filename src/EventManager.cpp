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
 * \file EventManager.cpp
 * \brief Event MANAGER
 *
 * Handle events from various input devices.
 */

#include "EventManager.h"

/* ************************************************************************** */

/*!
 * \fn void EventManager()
 *
 * Empty EventManager constructor.
 * Note : this constructor is private and can only be called by the singleton.
 */
EventManager::EventManager()
{
    std::cout << "EventManager::EventManager" << std::endl;            // debug
}

/*!
 * \fn void ~EventManager()
 *
 * Empty EventManager destructor.
 * Note : this destructor is private and can only be called by the singleton.
 */
EventManager::~EventManager()
{
    std::cout << "EventManager::~EventManager -->  ";            // debug
}

/*!
 * \fn void MenuEvents(Menu &menu);
 * \param menu A reference to a 'Menu' object.
 *
 * Handle every events while player is in the main menu.
 */
void EventManager::MenuEvents(Menu &menu)
{
    //std::cout << "(function) EventManager::MenuEvents" << std::endl;    // debug

    // States access
    StateManager &StateManager= StateManager::getInstance();

    // Configuration access
    ConfigManager &ConfigManager= ConfigManager::getInstance();
    short resx= ConfigManager.getX();
    short resy= ConfigManager.getY();
    double ratio= (static_cast<double>(resx)/1280.0);

    // Sound access
    SoundManager &SoundManager= SoundManager::getInstance();

    // Events polling
    while(SDL_PollEvent(&events))
    {
// ============ main menu ======================================================
        if (menu.getMenuPosition() < 4)
        switch(events.type)
        {
            case SDL_MOUSEMOTION:
            if (events.motion.y > (resy*0.92) && events.motion.y < ((resy*0.92)+(resy*0.0833)))
            {
                if (events.motion.x > (resx*0.0156) && events.motion.x < ((resx*0.0156)+(resx*0.14)))
                {
                    menu.setMenuPositionCursor(1);    // play menu
                }
                if (events.motion.x > (resx*0.390) && events.motion.x < ((resx*0.390)+(resx*0.115)))
                {
                    menu.setMenuPositionCursor(2);    // infos menu
                }
                if (events.motion.x > (resx*0.5515) && events.motion.x < ((resx*0.5515)+(resx*0.166)))
                {
                    menu.setMenuPositionCursor(3);    // options menu
                }
                if (events.motion.x > (resx*0.837) && events.motion.x < ((resx*0.837)+(resx*0.163)))
                {
                    menu.setMenuPositionCursor(4);    // exit menu
                }
            }
            else
            {
                //menu.setMenuPositionCursor(menu.getMenuPosition());    // too tricky for now...
            }
            break;

            case SDL_MOUSEBUTTONDOWN:
            if (events.button.button == SDL_BUTTON_LEFT)
            {
                if (events.motion.y > (resy*0.92) && events.motion.y < ((resy*0.92)+(resy*0.0833)))
                {
                    if (events.motion.x > (resx*0.0156) && events.motion.x < ((resx*0.0156)+(resx*0.14)))
                    {
                        //SoundManager.playClickSound();
                        menu.setMenuPosition(1);        // play menu
                        StateManager.setSoftwareState(2);    // launch game
                    }
                    if (events.motion.x > (resx*0.390) && events.motion.x < ((resx*0.390)+(resx*0.115)))
                    {
                        SoundManager.playClickSound();
                        if (menu.getMenuPositionCursor() == 2 && menu.getMenuPosition() == 2)
                            menu.setMenuPosition(0);    // main menu
                        else if (menu.getMenuPositionCursor() && menu.getMenuPosition() != 2)
                            menu.setMenuPosition(2);    // infos menu
                    }
                    if (events.motion.x > (resx*0.5515) && events.motion.x < ((resx*0.5515)+(resx*0.166)))
                    {
                        SoundManager.playClickSound();
                        if (menu.getMenuPositionCursor() == 3 && menu.getMenuPosition() == 3)
                            menu.setMenuPosition(0);    // main menu
                        else if (menu.getMenuPositionCursor() == 3 && menu.getMenuPosition() != 3)
                            menu.setMenuPosition(3);    // options menu
                    }
                    if (events.motion.x > (resx*0.837) && events.motion.x < ((resx*0.837)+(resx*0.163)))
                    {
                        SoundManager.playClickSound();
                        menu.setMenuPosition(4);    // exit menu
                        menu.setMenuPositionCursor(4);
                    }
                }
            }
            break;

            case SDL_KEYDOWN:
            if (events.key.keysym.sym == SDLK_LEFT && menu.getMenuPositionCursor() == 1)
                menu.setMenuPositionCursor(4);
            else if (events.key.keysym.sym == SDLK_LEFT)
                menu.setMenuPositionCursor(menu.getMenuPositionCursor()-1);
            if (events.key.keysym.sym == SDLK_RIGHT && menu.getMenuPositionCursor() == 4)
                menu.setMenuPositionCursor(1);
            else if (events.key.keysym.sym == SDLK_RIGHT)
                menu.setMenuPositionCursor(menu.getMenuPositionCursor()+1);
            if (events.key.keysym.sym == SDLK_q)
            {
                std::cout << "VERY EXIT CODE (menu)" << std::endl;
                StateManager.setExitCode(true);    // VERY EXIT !!
            }
            if (events.key.keysym.sym == SDLK_ESCAPE)
            {
                std::cout << "EXIT CODE (menu)" << std::endl;
                menu.setMenuPosition(4);    // exit menu
                menu.setMenuPositionCursor(4);
            }

            if (events.key.keysym.sym == SDLK_RETURN)
            {
                if (menu.getMenuPositionCursor() == 1)
                {
                    //SoundManager.playClickSound();
                    menu.setMenuPosition(1);        // play menu
                    StateManager.setSoftwareState(2);    // launch game
                }
                else if (menu.getMenuPositionCursor() == 2 && menu.getMenuPosition() == 2)
                    menu.setMenuPosition(0);    // main menu
                else if (menu.getMenuPositionCursor() == 2 && menu.getMenuPosition() != 2)
                    menu.setMenuPosition(2);    // infos menu
                else if (menu.getMenuPositionCursor() == 3 && menu.getMenuPosition() == 3)
                    menu.setMenuPosition(0);    // main menu
                else if (menu.getMenuPositionCursor() == 3 && menu.getMenuPosition() != 3)
                    menu.setMenuPosition(3);    // options menu
                else if (menu.getMenuPositionCursor() == 4)
                {
                    std::cout << "EXIT CODE (menu)" << std::endl;
                    menu.setMenuPosition(4);    // exit menu
                    menu.setMenuPositionCursor(4);
                }
            }
            break;

            case SDL_QUIT:
                std::cout << "EXIT CODE (menu)" << std::endl;
                menu.setMenuPosition(4);    // exit menu
                menu.setMenuPositionCursor(4);
            break;
        }
// ============ /main menu =====================================================



// ============ exit menu ======================================================
        else if (menu.getMenuPosition() >= 4)
        switch(events.type)
        {
            case SDL_MOUSEMOTION:
            if (events.motion.y > (resy*0.44) && events.motion.y < ((resy*0.44)+(resy*0.0833)))
            {
                if (events.motion.x > (resx*0.385) && events.motion.x < ((resx*0.385)+(resx*0.086)))
                {
                    menu.setMenuPositionCursor(4);    // yes
                }
                if (events.motion.x > (resx*0.516) && events.motion.x < ((resx*0.516)+(resx*0.1)))
                {
                    menu.setMenuPositionCursor(5);    // no
                }
            }
            break;

            case SDL_MOUSEBUTTONDOWN:
            if (events.button.button == SDL_BUTTON_LEFT)
            {
                if (events.motion.y > (resy*0.44) && events.motion.y < ((resy*0.44)+(resy*0.0833)))
                {
                    if (events.motion.x > (resx*0.385) && events.motion.x < ((resx*0.385)+(resx*0.086)))
                    {
                        //Mix_PlayChannel( -1, clic_sound, 0 );
                        StateManager.setExitCode(true);    // VERY EXIT !!
                    }

                    if (events.motion.x > (resx*0.516) && events.motion.x < ((resx*0.516)+(resx*0.1)))
                    {
                        SoundManager.playClickSound();
                        menu.setMenuPosition(0);
                        menu.setMenuPositionCursor(4);
                    }
                }
            }
            break;

            case SDL_KEYDOWN:
            if (events.key.keysym.sym == SDLK_ESCAPE)
            {
                menu.setMenuPosition(0);
                menu.setMenuPositionCursor(4);
            }
            if (events.key.keysym.sym == SDLK_LEFT)
                menu.setMenuPositionCursor(4);    // yes
            if (events.key.keysym.sym == SDLK_RIGHT)
                menu.setMenuPositionCursor(5);    // no
            if (events.key.keysym.sym == SDLK_RETURN)
            {
                if (menu.getMenuPositionCursor() == 4)
                {
                    StateManager.setExitCode(true);    // VERY EXIT !!
                }
                else if (menu.getMenuPositionCursor() == 5)
                {
                    menu.setMenuPosition(0);    // main menu
                    menu.setMenuPositionCursor(4);
                }
            }
            break;

            case SDL_QUIT:
            {
                // disable, alredy trying to exit...
            }
            break;
        }
// ============ /exit menu =====================================================
    }
}

/*!
 * \fn void GameEvents(GameWorld &game);
 * \param game A reference to a 'Game' object.
 *
 * Handle every ingame events.
 */
void EventManager::GameEvents(GameWorld &game)
{
    //std::cout << "(function) EventManager::GameEvents(GameWorld &game)" << std::endl;    // debug

    // States access
    StateManager &StateManager= StateManager::getInstance();

    // Configuration access
    ConfigManager &ConfigManager= ConfigManager::getInstance();
    short resx= ConfigManager.getX();
    short resy= ConfigManager.getY();
    double ratio= (static_cast<double>(resx)/1280.0);

    // Sound access
    SoundManager &SoundManager= SoundManager::getInstance();

    // Events polling
    while(SDL_PollEvent(&events))
    {
        switch(events.type)
        {
            case SDL_MOUSEMOTION:
            if (game.getGameMenuPosition() != 0 && events.motion.y > (resy*0.447) && events.motion.y < ((resy*0.447)+(resy*0.075)))
            {
                if (events.motion.x > (resx*0.190) && events.motion.x < ((resx*0.190)+(resx*0.084)))
                {
                    game.setGameMenuPositionCursor(0);    // exit - yes
                }
                if (events.motion.x > (resx*0.320) && events.motion.x < ((resx*0.320)+(resx*0.100)))
                {
                    game.setGameMenuPositionCursor(1);    // exit - no
                }
                if (events.motion.x > (resx*0.465) && events.motion.x < ((resx*0.465)+(resx*0.347)))
                {
                    game.setGameMenuPositionCursor(2);    // exit - menu
                }
            }
            if (game.getGameState() == 0 && events.motion.y > (resy*0.670) && events.motion.y < ((resy*0.670) + (resy*0.0669)))
            {
                if (events.motion.x > (resx*0.425) && events.motion.x < ((resx*0.425)+(resx*0.15)))
                {
                    game.setUserCursor_nextbutton(true);    // MouseOver "skip notification" button
                }
            }
            else
            {
                game.setUserCursor_nextbutton(false);
            }

            // Up menu
            game.setGameUpMenu(false, false);
            if (events.motion.y < (0 + (32*ratio)))
            {
                if (events.motion.x > (12*ratio) && events.motion.x < ((12*ratio) + ((82*ratio))))
                {
                    game.setGameUpMenu(true, false);    // MouseOver "menu" button
                }
                else if (events.motion.x > (108*ratio) && events.motion.x < ((108*ratio) + (94*ratio)))
                {
                    game.setGameUpMenu(false, true);    // MouseOver "pause" button
                }
            }
            break;

            case SDL_MOUSEBUTTONDOWN:
            if (events.motion.y < (0 + (32*ratio)))    // UPMENU ZONE
            {
                if (events.motion.x > (12*ratio) && events.motion.x < ((12*ratio) + ((82*ratio))) && (game.getGameState() == 3 || game.getGameState() == 5))    // Click on "menu" button
                {
                    // Play sound
                    SoundManager.playClickSound();

                    if (game.getGameMenuPosition() == 0)
                    {
                        game.setGameMenuPosition(1);
                    }
                    else
                    {
                        game.setGameMenuPosition(0);
                    }
                }
                else if (events.motion.x > (108*ratio) && events.motion.x < ((108*ratio) + (94*ratio)) && game.getGameState() == 5)    // Click on "pause" button
                {
                    // Play sound
                    SoundManager.playClickSound();

                    if (game.getGamePaused() == 0 && game.getGameMenuPosition() == 0 && game.getGameState() >= 3)
                    {
                        game.getTimer().pause();
                        game.setGamePaused(1);
                    }
                    else
                    {
                        game.getTimer().unpause();
                        game.setGamePaused(0);
                    }
                }
            }
            else if (events.motion.y > (resy-(64*ratio)))    // GUI ZONE
            {
                //
            }
            else    // GAME ZONE
            {
                if (events.button.button == SDL_BUTTON_LEFT && game.getGameState() == 0 && events.motion.y > (resy*0.670) && events.motion.y < ((resy*0.670) + (resy*0.0669)))
                {
                    if (events.motion.x > (resx*0.425) && events.motion.x < ((resx*0.425)+(resx*0.15)))
                    {
                        game.setGameState(1);    // skip notification
                    }
                }
                if (events.button.button == SDL_BUTTON_LEFT && game.getGameState() == 3 && game.getGameMenuPosition() == 0 && game.getGamePaused() == 0)
                {
                    // Update cursor
                    game.setUserCursorPosition(static_cast<short>(events.motion.x-(47*ratio)), static_cast<short>(events.motion.y-(21*ratio)));

                    // Update gamestate
                    game.setGameState(4);    // session end

                    // Play sound
                    SoundManager.playClickSound();
                }
                if (events.button.button == SDL_BUTTON_RIGHT && game.getGameState() == 5 && game.getGameMenuPosition() == 0 && game.getGamePaused() == 0)
                {
                    game.setGameState(6);    // session next (skip results)
                }
                if (game.getGameMenuPosition() != 0 && events.motion.y > (resy*0.447) && events.motion.y < ((resy*0.447)+(resy*0.075)))
                {
                    if (events.motion.x > (resx*0.190) && events.motion.x < ((resx*0.190)+(resx*0.084)))
                    {
                        StateManager.setExitCode(true);    // EXIT !!
                    }
                    if (events.motion.x > (resx*0.320) && events.motion.x < ((resx*0.320)+(resx*0.100)))
                    {
                        game.setGameMenuPosition(0);    // exit gamemenu
                        SoundManager.playClickSound();
                    }
                    if (events.motion.x > (resx*0.465) && events.motion.x < ((resx*0.465)+(resx*0.347)))
                    {
                        StateManager.setSoftwareState(1);    // go to the main menu
                    }
                }
            }
            break;

            case SDL_KEYDOWN:
            if (events.key.keysym.sym == SDLK_LEFT && game.getGameMenuPositionCursor() == 0)
                game.setGameMenuPositionCursor(2);
            else if (events.key.keysym.sym == SDLK_LEFT )
                game.setGameMenuPositionCursor(game.getGameMenuPositionCursor()-1); //menupos_temp--;
            if (events.key.keysym.sym == SDLK_RIGHT && game.getGameMenuPositionCursor() == 2)
                game.setGameMenuPositionCursor(0);
            else if (events.key.keysym.sym == SDLK_RIGHT)
                game.setGameMenuPositionCursor(game.getGameMenuPositionCursor()+1); //menupos_temp++;

            if (events.key.keysym.sym == SDLK_RETURN && game.getGameState() == 0)
                    game.setGameState(1);    // skip notification

            if (events.key.keysym.sym == SDLK_RETURN)
            {
                if (game.getGameMenuPosition() != 0)
                {
                    if (game.getGameMenuPositionCursor() == 0)
                    {
                        StateManager.setExitCode(true);    // EXIT !!
                    }
                    else if (game.getGameMenuPositionCursor() == 1)
                    {
                        game.setGameMenuPosition(0);    // exit gamemenu
                    }
                    else if (game.getGameMenuPositionCursor() == 2)
                    {
                        StateManager.setSoftwareState(1);    // go to the main menu
                    }
                }
            }
            if (events.key.keysym.sym == SDLK_ESCAPE && game.getGamePaused() == 0 && (game.getGameState() == 3 || game.getGameState() == 5))
            {
                if (game.getGameMenuPosition() != 0)
                {
                    game.setGameMenuPosition(0);
                }
                else
                {
                    std::cout << "EXIT CODE (game)" << std::endl;
                    game.setGameMenuPosition(1);
                }
            }
            if (events.key.keysym.sym == SDLK_PAUSE || events.key.keysym.sym == SDLK_SPACE)
            {
                if (game.getGamePaused() == 0 && game.getGameMenuPosition() == 0 && game.getGameState() == 5)
                {
                    game.getTimer().pause();
                    game.setGamePaused(1);
                }
                else
                {
                    game.getTimer().unpause();
                    game.setGamePaused(0);
                }
            }
            if (events.key.keysym.sym == SDLK_q)
            {
                std::cout << "VERY EXIT CODE (game)" << std::endl;
                StateManager.setExitCode(true);    // VERY EXIT !!
            }
            break;

            case SDL_QUIT:
            if (game.getGamePaused() == 0 && game.getGameState() >= 3)
                {
                    std::cout << "EXIT CODE (game)" << std::endl;
                    game.setGameMenuPosition(1);
                }
            break;
        }
    }
}

/* ************************************************************************** */
