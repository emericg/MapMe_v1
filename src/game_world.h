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
 * \file game_world.h
 * \brief the game ! (HEADER)
 *
 * This file is the core of the game.
 */

#ifndef GAME_WORLD_H
#define GAME_WORLD_H
/* ************************************************************************** */

// C++ standard libraries
#include <iostream>
#include <string>
#include <fstream>

// Local file(s)
#include "ConfigManager.h"
#include "GfxManager.h"
#include "EventManager.h"

#include "timer.h"
#include "parser.h"
#include "locations.h"


/* ************************************************************************** */

/*!
 * \class GameWorld
 * \brief GameWorld class.
 *
 * This class IS the game.
 */
class GameWorld
{
public:
    GameWorld();
    ~GameWorld();

    void GamePipe();

    short getGameState();
    void setGameState(short new_gamestate);

    short getGamePaused();
    void setGamePaused(short new_gamepaused);

    short getGameMenuPosition();
    void setGameMenuPosition(short new_gamemenuposition);

    short getGameMenuPositionCursor();
    void setGameMenuPositionCursor(short new_gamemenupositioncursor);

    void setGameUpMenu(bool new_menuactive, bool new_pauseactive);

    void setUserCursorPosition(short x, short y);
    void setUserCursor_nextbutton(bool new_nextbutton);

    Timer & getTimer();

private:
/*    Functions    */
    void SessionParse();
    void SessionStart();
    void SessionActive();
    void SessionStop();
    void SessionPassive();
    void SessionNext();

    void CalcDistance();
    void CalcPointsDistance();
    void CalcPointsTime();
    void CalcGameScore();

/*    Variables    */
    short gamestate;    // 0: newstage
                // 1: newstage s2
                // 2: session start
                // 3: session active
                // 4: session stop
                // 5: session passive
                // 6: session next

    short gamepaused;    // 0: playing
                // 1: pause signal
                // 2: paused

    short totalSessionTime;

    short gamemenuposition, gamemenupositioncursor;
    bool menuactive, pauseactive;

    short gamelevel, gamestage, gamediff;

    // Cursor
    bool nextbutton;
    SDL_Rect rusercursor;

    // Stats
    unsigned int gamescore;
    short distancepx, distancekm, pointsdistance, pointstime;
    double accuracy;

    // Resolution
    double ratio;
    short resx, resy;

    // Timer
    Timer *pTIMER;
    unsigned int Time;

    // Parser
    Parser *pPARSER;

    // Locations
    short ActualLocation;
    short TotalLocation;
    short TotalLevel;
    City* city[8];
};

/* ************************************************************************** */
#endif
