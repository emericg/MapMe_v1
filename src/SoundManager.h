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
 * \file SoundManager.h
 * \brief Sound MANAGER (HEADER)
 *
 * Initialize SDL_mixer library with proper parameters.
 */

#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H
/* ************************************************************************** */

// C++ standard library
#include <iostream>

// SDL library
#include <SDL/SDL_mixer.h>

// Local file(s)
#include "Singleton.h"
#include "ConfigManager.h"

/* ************************************************************************** */

/*!
 * \class SoundManager
 * \brief Sound class for handeling sound.
 *
 * Initialize SDL_mixer library with proper parameters.
 */
class SoundManager : public Singleton<SoundManager>
{
friend class Singleton<SoundManager>;

public:
    bool initAudio();
    void loadRessources();
    void playClickSound();

private:
    SoundManager();
    ~SoundManager();

    // Ressources
    Mix_Chunk *clic_sound; /*!< Click sound */
};

/* ************************************************************************** */
#endif
