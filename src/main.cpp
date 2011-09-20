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
 * \file main.cpp
 * \brief Main file of MapMe.
 *
 * Start the game, initialize libraries and launch main menu.
 */

#include "main.h"

/* ************************************************************************** */

#ifdef WIN32
/*!
 * \fn WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
 * \param HINSTANCE hInstance ??.
 * \param HINSTANCE hPrevInstance ??.
 * \param LPSTR lpCmdLine ??.
 * \param int nCmdShow ??.
 * \return Return the program state at exit: 0 if everything is fine, 1 if an error has occured.
 *
 * Main function of MapMe.
 * Start the programme, initialize libraries, then start game pipe, wich contain menu and game.
 */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
/*!
 * \fn int main (int argc, char **argv)
 * \param argc Number of arguments.
 * \param argv Arguments.
 * \return Return the program state at exit: 0 if everything is fine, 1 if an error occur.
 *
 * Main function of MapMe.
 * Start the programme, initialize libraries, then start game pipe, wich contain menu and game.
 */
int main(int argc, char **argv)
#endif
{
    /*    States initialization        */
    StateManager &StateManager= StateManager::getInstance();
    StateManager.setSoftwareState(1);

    /*    Loading configuration        */
    ConfigManager &ConfigManager= ConfigManager::getInstance();
    if (ConfigManager.LoadConfig() == false)
    {
        std::cerr << "[X] Loading configuration : CRITICAL ERROR." << std::endl;// debug
        std::cerr << "[X] Attempt to shutdone." << std::endl;                   // debug

        return EXIT_FAILURE;
    }


    /*    Graphics initialization        */
    GfxManager &GfxManager= GfxManager::getInstance();
    if (GfxManager.createScreen() == false)
    {
        std::cerr << "[X] Screen initialization : CRITICAL ERROR." << std::endl;// debug
        std::cerr << "[X] Attempt to shutdone." << std::endl;                   // debug

        return EXIT_FAILURE;
    }

    // Temporary loading screen
    GfxManager.loadingScreen();

    // Load all gfx ressources
    GfxManager.loadRessources(0);


    /*    Events initialization        */
    EventManager &EventManager= EventManager::getInstance();


    /*    Audio initialization        */
    SoundManager &SoundManager= SoundManager::getInstance();
    if (SoundManager.initAudio() == false)
    {
        std::cerr << "[X] Audio initialization : CRITICAL ERROR." << std::endl; // debug
        std::cerr << "[X] Attempt to shutdone." << std::endl;                   // debug

        return EXIT_FAILURE;
    }
    SoundManager.loadRessources();

    /*    Menu and Game initialization    */
    GameWorld *pGAME= NULL;
    Menu *pMENU= NULL;


    /*    FPS manager initialization    */
    FPSmanager FramesManager;
    SDL_initFramerate(&FramesManager);
    SDL_setFramerate(&FramesManager, 30);


    // Main loop start
    /////////////////////
    std::cout << "[Y] Program started successfully !" << std::endl;
    while(StateManager.isExitCode() == false)
    {
        // Menu
        if ((StateManager.getSoftwareState() == 1) && (pMENU != NULL))
        {
            pMENU->MenuPipe();
        }
        else if ((StateManager.getSoftwareState() == 1) && (pMENU == NULL))
        {
            pMENU= new Menu();
            //GfxManager.loadRessources(1);
            if (pGAME != NULL)
            {
                delete pGAME;
                //GfxManager.unloadRessources(2);
                pGAME= NULL;
            }
        }

        // Game
        if ((StateManager.getSoftwareState() == 2) && (pGAME != NULL))
        {
            pGAME->GamePipe();
        }
        else if ((StateManager.getSoftwareState() == 2) && (pGAME == NULL))
        {
            pGAME= new GameWorld();
            //GfxManager.loadRessources(2);
            if (pMENU != NULL)
            {
                delete pMENU;
                //GfxManager.unloadRessources(1);
                pMENU= NULL;
            }
        }

        GfxManager.flipVideoBuffers();

        /* fps */
        SDL_framerateDelay(&FramesManager);
        //std::cout << "FPS : " << SDL_getFramerate(&FramesManager) << std::endl;
    }

    if (pMENU != NULL)
        delete pMENU;
    if (pGAME != NULL)
        delete pGAME;
    /////////////////////
    // Main loop end


    // Exit sequence
    std::cout << "[Y] Program shutting-done." << std::endl;                     // debug
    ConfigManager.destroyInstance();
    SoundManager.destroyInstance();
    GfxManager.destroyInstance();
    EventManager.destroyInstance();
    StateManager.destroyInstance();

return EXIT_SUCCESS;
}

/* ************************************************************************** */
