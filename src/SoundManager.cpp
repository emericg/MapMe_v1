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
 * \file SoundManager.cpp
 * \brief Sound MANAGER
 *
 * Initialize SDL_mixer library with proper parameters.
 */

#include "SoundManager.h"

/* ************************************************************************** */

/*!
 * \fn SoundManager()
 *
 * Empty SoundManager constructor.
 * Note : this constructor is private and can only be called by the singleton.
 */
SoundManager::SoundManager()
{
    std::cout << "SoundManager::SoundManager" << std::endl;        // debug
}

/*!
 * \fn ~SoundManager()
 *
 * SoundManager destructor. Incharge to kill the SDL_mixer library.
 * Note : this constructor is private and can only be called by the singleton.
 */
SoundManager::~SoundManager()
{
    std::cout << "SoundManager::~SoundManager -->  ";            // debug

    // Free ressources
    //Mix_FreeChunk(clic_sound);

    // Close library
    //Mix_CloseAudio();
}

/*!
 * \fn bool initAudio()
 * \return true if initialization work, else false.
 *
 * This is where SDL_mixer is initialized. It load sound volume from ConfigManager.
 */
bool SoundManager::initAudio()
{
    //std::cout << "(function) SoundManager::initialization" << std::endl;    // debug

    // Access configuration
    ConfigManager &ConfigManager= ConfigManager::getInstance();

    // SDL_mixer initialization
    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 1, 2048) < 0)
    {
        std::cerr << "   ERROR : Unable to initialize SDL_mixer : " << SDL_GetError() << std::endl;
        return false;
    }
    else
    {
        // Allocate multiple channels
        //Mix_AllocateChannels(8);

        // Set volumes levels
        Mix_Volume(-1, ((ConfigManager.conf_vMaster/100)*128));
        Mix_VolumeMusic((ConfigManager.conf_vMusic/100)*128);
    }

    return true;
}

/*!
 * \fn void loadRessources()
 *
 * This is where all sounds are loaded into system memory.
 */
void SoundManager::loadRessources()
{
    //std::cout << "(function) SoundManager::loadRessources" << std::endl;    // debug

    // Load sound
    clic_sound= Mix_LoadWAV("ressources/audio/clic.ogg");
}

/*!
 * \fn void playClickSound();
 *
 * You could hear a nice sound when this function is called.
 */
void SoundManager::playClickSound()
{
    //std::cout << "(function) SoundManager::playClickSound" << std::endl;    // debug

    Mix_PlayChannel(-1, clic_sound, 0);
}

/* ************************************************************************** */
