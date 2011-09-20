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
 * \file game_world.cpp
 * \brief the game !
 *
 * This file contain the game core.
 */

#include "game_world.h"

/* ************************************************************************** */
/* ************************************************************************** */

GameWorld::GameWorld()
{
    std::cout << "GameWorld::GameWorld" << std::endl;            // debug

    // Get resolution
    ConfigManager &pCONFIG= ConfigManager::getInstance();
    resx= pCONFIG.getX();
    resy= pCONFIG.getY();
    ratio= (static_cast<double>(resx)/1280.0);

    // init
    gamestate= 0;
    gamepaused= 0;

    gamemenuposition= 0;
    gamemenupositioncursor= 0;

    menuactive= false;
    pauseactive= false;

    gamelevel= 1;
    gamestage= 1;
    gamediff= 1;

    totalSessionTime= 7000;

    // Cursors
    nextbutton= false;
    rusercursor.x= 0;
    rusercursor.y= 0;

    // Scores
    gamescore= 0;
    pointsdistance= 0;
    pointstime= 0;

    // init Timer
    pTIMER= new Timer();

    // init Parser
    pPARSER= new Parser();

    // Locations
    TotalLocation= 6;
    TotalLevel= 10;
    ActualLocation= 0;
    for(short i= 0; i < TotalLocation; i++)
    {
        city[i]= new City();
    }

    // Parse x cities
    SessionParse();
}

/* ************************************************************************** */

GameWorld::~GameWorld()
{
    std::cout << "GameWorld::~GameWorld" << std::endl;            // debug

    delete pTIMER;
    delete pPARSER;
    //delete []city;
}

/* ************************************************************************** */
/* ************************************************************************** */

short GameWorld::getGameState()
{
    //std::cout << "(function) GameWorld::getGameState" << std::endl;    // debug

    return gamestate;
}

void GameWorld::setGameState(short new_gamestate)
{
    //std::cout << "(function) GameWorld::setGameState" << std::endl;    // debug

    if (new_gamestate >= 0 && new_gamestate <= 6)
    {
        gamestate= new_gamestate;
    }
    else
    {
        std::cerr << "setGameState error : new_gamestate out of range (" << new_gamestate << ")" << std::endl;
    }
}

/* ************************************************************************** */

short GameWorld::getGamePaused()
{
    //std::cout << "(function) GameWorld::getGamePaused" << std::endl;    // debug

    return gamepaused;
}

void GameWorld::setGamePaused(short new_gamepaused)
{
    //std::cout << "(function) GameWorld::setGamePaused" << std::endl;    // debug

    if (new_gamepaused >= 0 && new_gamepaused <= 2)
    {
        gamepaused= new_gamepaused;
    }
    else
    {
        std::cerr << "setGamePaused error : new_gamepaused out of range (" << new_gamepaused << ")" << std::endl;
    }
}

/* ************************************************************************** */

short GameWorld::getGameMenuPosition()
{
    //std::cout << "(function) GameWorld::getGameMenuPosition" << std::endl;    // debug

    return gamemenuposition;
}

void GameWorld::setGameMenuPosition(short new_gamemenuposition)
{
    //std::cout << "(function) GameWorld::setGameMenuPosition" << std::endl;    // debug

    if (new_gamemenuposition >= 0 && new_gamemenuposition <= 50)
    {
        gamemenuposition= new_gamemenuposition;
    }
    else
    {
        std::cerr << "setGameMenuPosition error : new_gamemenuposition out of range (" << new_gamemenuposition << ")" << std::endl;
    }
}

/* ************************************************************************** */

short GameWorld::getGameMenuPositionCursor()
{
    //std::cout << "(function) GameWorld::getGameMenuPositionCursor" << std::endl;    // debug

    return gamemenupositioncursor;
}

void GameWorld::setGameMenuPositionCursor(short new_gamemenupositioncursor)
{
    //std::cout << "(function) GameWorld::setGameMenuPositionCursor" << std::endl;    // debug

    if (new_gamemenupositioncursor >= 0 && new_gamemenupositioncursor <= 2)
    {
        gamemenupositioncursor= new_gamemenupositioncursor;
    }
    else
    {
        std::cerr << "setGameMenuPositionCursor error : new_gamemenupositiocursorn out of range (" << new_gamemenupositioncursor << ")" << std::endl;
    }
}

/* ************************************************************************** */

void GameWorld::setGameUpMenu(bool new_menuactive, bool new_pauseactive)
{
    //std::cout << "(function) GameWorld::setGameUpMenu" << std::endl;    // debug

    if (new_menuactive == true)
    {
        menuactive= true;
        pauseactive= false;
    }
    else if (new_pauseactive == true)
    {
        menuactive= false;
        pauseactive= true;
    }
    else
    {
        menuactive= false;
        pauseactive= false;
    }
}

/* ************************************************************************** */

void GameWorld::setUserCursorPosition(short x, short y)
{
    //std::cout << "(function) GameWorld::setUserCursorPosition" << std::endl;    // debug

    rusercursor.x= x;
    rusercursor.y= y;
}

void GameWorld::setUserCursor_nextbutton(bool new_nextbutton)
{
    //std::cout << "(function) GameWorld::setUserCursor_nextbutton" << std::endl;    // debug

    nextbutton= new_nextbutton;
}

/* ************************************************************************** */

Timer & GameWorld::getTimer()
{
    //std::cout << "(function) GameWorld::getTimer" << std::endl;        //debug

    return *pTIMER;
}

/* ************************************************************************** */
/* ************************************************************************** */

void GameWorld::GamePipe()
{
    //std::cout << "(function) GameWorld::GamePipe" << std::endl;        //debug

    // Gfx access
    GfxManager &GfxManager= GfxManager::getInstance();

    // Events access
    EventManager &EventManager= EventManager::getInstance();
    EventManager.GameEvents(*this);

    // Game Pipeline
    if (gamepaused == 0)
    {
        // Update timer
        Time= pTIMER->get_time();

        if (gamestate < 2)
        {
            ////////////////////////////////////////////////////////
            if (Time == 0)            // Start notification
            {
                std::cout << "  New gamelevel: " << gamelevel << ". Gamestage: " << gamestage << ". Gamediff: " << gamediff << std::endl;    //debug

                GfxManager.GenerateNotificationTexts(gamelevel, gamestage, gamediff);

                gamestate= 0;
                pTIMER->start();
            }

            if (gamestate == 0 || Time <= 4000)    // Draw notification
            {
                GfxManager.DrawGameMap();
                GfxManager.DrawGameNotification((Time/4000.0), nextbutton);
            }

            if (gamestate == 1 || Time > 4000)    // Stop drawing notification
            {
                pTIMER->stop();
                gamestate= 2;

                // Generate hud before begining the game
                GfxManager.GenerateGUI(*city[ActualLocation], gamescore);
            }
            ////////////////////////////////////////////////////////
        }

        if (gamestate >= 2)
        {
            // Draw map
            GfxManager.DrawGameMap();

            ////////////////////////////////////////////////////////
            if (gamestate < 5)
            {
                // Update timer
                Time= pTIMER->get_time();

                // Start session
                if (Time == 0)
                {
                    SessionStart();
                    GfxManager.GenerateGUI(*city[ActualLocation], gamescore);
                }

                // Session 'active'
                if (gamestate == 3 && Time < totalSessionTime)
                {
                    SessionActive();
                    GfxManager.DrawGameGUI(static_cast<double>(Time)/static_cast<double>(totalSessionTime));
                    GfxManager.DrawGameUpMenu(menuactive, pauseactive);
                }

                // Stop session
                if (gamestate == 4 || Time >= totalSessionTime)
                {
                    SessionStop();
                    GfxManager.GenerateLocationInfos(*city[ActualLocation], distancekm, pointsdistance, Time, pointstime, gamescore);
                }
            }
            ////////////////////////////////////////////////////////

            // Draw results
            if (gamestate == 5 && pTIMER->get_time() < 4000)
            {
                SessionPassive();
                GfxManager.DrawGameLocationInfos(rusercursor);
                GfxManager.DrawGameGUI(1);
                GfxManager.DrawGameUpMenu(menuactive, pauseactive);
            }

            // Stop session, and prepare the next one
            if ((gamestate == 5 && pTIMER->get_time() > 4000) || gamestate == 6)
            {
                pTIMER->stop();
                SessionNext();
            }
        }

        // Draw gamemenu ?
        if (gamemenuposition != 0)
            GfxManager.DrawGameMenu(gamemenuposition, gamemenupositioncursor);
    }
    else if (gamepaused == 1)
    {
        GfxManager.DrawGamePaused();
        gamepaused= 2;
    }
    else
    {
        GfxManager.DrawGameUpMenu(menuactive, true);
    }
}

/* ************************************************************************** */
/* ************************************************************************** */

void GameWorld::SessionParse()
{
    std::cout << "(function) GameWorld::SessionParse" << std::endl;        // debug

    // Parse x Capitals
    if (gamestage == 1)
    {
        bool ok=pPARSER->CheckCapitalsFile();
        if (ok == true)
            ok= pPARSER->ParseCapitalsFile(city, TotalLocation, gamediff);
        //if (ok == true)
        //    pPARSER->PrintCapitalsHeap(city, TotalLocation, gamediff);
    }
    // Parse x Cities
    else //if (gamestage == 2)
    {
        bool ok=pPARSER->CheckCitiesFile();
        if (ok == true)
            ok= pPARSER->ParseCitiesFile(city, TotalLocation, gamediff);
        //if (ok == true)
        //    pPARSER->PrintCitiesHeap(city, TotalLocation, gamediff);
    }
}

/* ************************************************************************** */

void GameWorld::SessionStart()
{
    std::cout << "(function) GameWorld::SessionStart" << std::endl;        // debug

    // Print actual city
    std::cout << "   - location: " << city[ActualLocation]->name.c_str() << std::endl;

    // Reset cursors
    nextbutton= false;
    rusercursor.x= 0;
    rusercursor.y= 0;

    // Update game state
    gamestate++;

    // Start timer
    pTIMER->start();
}

/* ************************************************************************** */

void GameWorld::SessionActive()
{
    //std::cout << "(function) GameWorld::SessionActive" << std::endl;    // debug

    // Do nothing... Just Wait...
}

/* ************************************************************************** */

void GameWorld::SessionStop()
{
    std::cout << "(function) GameWorld::SessionStop" << std::endl;        // debug

    // Stop timer
    pTIMER->stop();

    // Stats :
    CalcDistance();
    CalcPointsDistance();
    CalcPointsTime();
    CalcGameScore();

    // Update game state
    gamestate++;

    // Restart timer
    pTIMER->start();
}

/* ************************************************************************** */

void GameWorld::SessionPassive()
{
    //std::cout << "(function) GameWorld::SessionPassive() << std::endl;    // debug

    // Do nothing... Just Wait...
}

/* ************************************************************************** */

void GameWorld::SessionNext()
{
    std::cout << "(function) GameWorld::SessionNext" << std::endl;    // debug

    // Next location
    if (ActualLocation < (TotalLocation-1))
    {
        ActualLocation++;
        gamestate= 2;
    }
    else
    {
        // END OF THE GAME
        if (gamelevel >= TotalLevel)
        {
            // GAME REBOOT
            std::cout << "  -  Reboot :-)" << std::endl;        // debug

            ActualLocation= 0;
            gamelevel= 1;
            gamestage= 1;
            gamediff= 1;

            gamestate= 0;    // ask for notification

            // Parse new locations
            SessionParse();
        }
        // Next gamestage
        else if (gamestage == 1)
        {
            std::cout << "  -  New gamestage coming !!" << std::endl;// debug

            ActualLocation= 0;
            gamestage= 2;

            gamestate= 0;    // ask for notification

            // Parse new locations
            SessionParse();
        }
        // Next gamelevel
        else if (gamestage == 2)
        {
            std::cout << "  -  New gamelevel coming !!" << std::endl;// debug

            ActualLocation= 0;
            gamelevel++;
            gamestage= 1;
            gamediff++;

            gamestate= 0;    // ask for notification

            // Parse new locations
            SessionParse();
        }
    }
}

/* ************************************************************************** */
/* ************************************************************************** */

void GameWorld::CalcDistance()
{
    std::cout << "(function) GameWorld::CalcDistance" << std::endl;    // debug

    if (rusercursor.x == 0 && rusercursor.y == 0)    // if no click detected
        distancepx = distancekm = 0;
    else
    {
        short outmargex= 0, outmargey= 0;
        short a= 0, b= 0;

        short p1x= rusercursor.x + static_cast<short>(48*ratio);
        short p1y= rusercursor.y + static_cast<short>(21*ratio);

        short p2x= city[ActualLocation]->coordinates_x;
        short p2y= city[ActualLocation]->coordinates_y;


        // NORMAL calcul
        if (p1x >= p2x)
            a= p1x - p2x;
        else
            a= p2x - p1x;

        if (p1y >= p2y)
            b= p1y - p2y;
        else
            b= p2y - p1y;

/*
        // INVERTED calcul
        if (p1x < p2x)
            a= p1x + (resx - p2x) + outmargex;
        else //if ((p2x < (static_cast<double>(resx)/2.0)) && (p1x > (static_cast<double>(resx)/2.0)))
            a= p2x + (resx - p1x) + outmargex;

        if (p1y < p2x)
            b= (resy - p1y) + p2y;
        else
            b= (resy - p2y) + p1y;

        distancepx= static_cast<short>(sqrt(a*a + b*b));
        distancekm= static_cast<short>(sqrt(a*a + b*b)*24);
        std::cout << "distance inversée : " << distancepx << "px, " << distancekm << "km." << std::endl;
*/


        // Results
        distancepx= static_cast<short>(sqrt(a*a + b*b));
        distancekm= static_cast<short>(sqrt(a*a + b*b)*22);
        //std::cout << "distance : " << distancepx << "px, " << distancekm << "km." << std::endl;
    }
}

/* ************************************************************************** */

void GameWorld::CalcPointsDistance()
{
    std::cout << "(function) GameWorld::CalcPointsDistance" << std::endl;    // debug

    if (distancepx == 0 || (180-distancepx)*4 <= 0)
        pointsdistance= 0;
    else
        pointsdistance= static_cast<short>((180-distancepx)*4);
}

/* ************************************************************************** */

void GameWorld::CalcPointsTime()
{
    std::cout << "(function) GameWorld::CalcPointsTime" << std::endl;    // debug


    if (pointsdistance == 0 || (static_cast<double>(Time)/static_cast<double>(totalSessionTime)) >= 0.5)
        pointstime= 0;
    else
    {
        pointstime= static_cast<short>(pointsdistance * (static_cast<double>(Time)/static_cast<double>(totalSessionTime)/2.0));
    }
}

/* ************************************************************************** */

void GameWorld::CalcGameScore()
{
    std::cout << "(function) GameWorld::CalcGameScore" << std::endl;    // debug

    gamescore+= pointsdistance + pointstime;
}

/* ************************************************************************** */
/* ************************************************************************** */
