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
 * \file EventManager.h
 * \brief Events MANAGER (HEADER)
 *
 * Handle events from various input devices...
 */

#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H
/* ************************************************************************** */

// C++ standard library
#include <iostream>

// SDL libraries
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

// Local file(s)
#include "Singleton.h"
#include "ConfigManager.h"
#include "StateManager.h"
#include "SoundManager.h"
#include "menu.h"
#include "game_world.h"

/* ************************************************************************** */

class Menu;
class GameWorld;

/*!
 * \class EventManager
 * \brief class for handeling events.
 *
 * This class handle events from input devices like keyboard, mouse and joystick...
 */
class EventManager : public Singleton<EventManager>
{
friend class Singleton<EventManager>;

public:
    void MenuEvents(Menu &menu);
    void GameEvents(GameWorld &game);

private:
    EventManager();
    ~EventManager();

    SDL_Event events; /**< Events structure */
};

/* ************************************************************************** */
#endif
