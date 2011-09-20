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
 * \file StateManager.h
 * \brief State MANAGER (HEADER)
 *
 * Handle gamestates like game paused, playing, exiting...
 */

#ifndef STATEMANAGER_H
#define STATEMANAGER_H
/* ************************************************************************** */

// C++ standard library
#include <iostream>

// Local file(s)
#include "Singleton.h"

/* ************************************************************************** */

/*!
 * \class StateManager
 * \brief class for handeling program states.
 *
 * This class handle the different programme states, like menu, playing, paused...
 */
class StateManager : public Singleton<StateManager>
{
friend class Singleton<StateManager>;

public:
    short getSoftwareState();
    void setSoftwareState(short new_softwarestate);
    bool isExitCode();
    void setExitCode(bool new_exitcode);

private:
    StateManager();
    ~StateManager();

    short softwarestate;    /*!< softwarestate: 1 for menu, 2 for game */
    bool exitcode;        /*!< exitcode : if true, time to stop the software */
};

/* ************************************************************************** */
#endif
