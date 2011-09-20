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
 * \file main.h
 * \brief Main file (HEADER).
 *
 * Start the programme, initialize libraries and launch the menu.
 */

#ifndef MAIN_H
#define MAIN_H
/* ************************************************************************** */

// C++ standard library
#include <iostream>

// SDL Library
#include "sdlgfx/SDL_framerate.h"

// Windows Library
#ifdef WIN32
#include "windows.h"
#endif

// Local file(s)
#include "StateManager.h"
#include "ConfigManager.h"
#include "GfxManager.h"
#include "EventManager.h"
#include "SoundManager.h"

#include "menu.h"
#include "game_world.h"

#ifdef WIN32
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
#else
int main(int argc, char **argv);
#endif

/* ************************************************************************** */
#endif
