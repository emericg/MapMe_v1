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
 * \file StateManager.cpp
 * \brief States MANAGER
 *
 * Handle gamestates like game paused, playing, exiting...
 */

#include "StateManager.h"

/* ************************************************************************** */

/*!
 * \fn StateManager()
 *
 * StateManager constructor. Some variables initialization are in there.
 * Note : this constructor is private and can only be called by the singleton.
 */
StateManager::StateManager()
{
    std::cout << "StateManager::StateManager" << std::endl;        // debug

    //
    softwarestate= 0;
    exitcode= false;
}

/*!
 * \fn ~StateManager()
 *
 * Empty StateManager destructor.
 * Note : this constructor is private and can only be called by the singleton.
 */
StateManager::~StateManager()
{
    std::cout << "StateManager::~StateManager -->  ";            // debug
}

/*!
 * \fn short getSoftwareState()
 * \return It return the 'softwarestate' variable.
 *
 * 'softwarestate' accessor.
 */
short StateManager::getSoftwareState()
{
    //std::cout << "(function) StateManager::getSoftwareState" << std::endl;    // debug

    return softwarestate;
}

/*!
 * \fn void setSoftwareState(short new_softwarestate)
 * \param new_softwarestate The new software state (0: init, 1:menu, 2:game).
 *
 * 'menuposition' mutator.
 */
void StateManager::setSoftwareState(short new_softwarestate)
{
    //std::cout << "(function) StateManager::setSoftwareState" << std::endl;    // debug

    if (new_softwarestate >= 0 && new_softwarestate <= 3)
    {
        softwarestate= new_softwarestate;
    }
    else
    {
        std::cerr << "setSoftwareState error : new_softwarestate out of range (" << new_softwarestate << ")" << std::endl;
    }
}

/*!
 * \fn void isExitCode()
 * \return It return the 'exitcode' boolean
 *
 * 'exitcode' accessor.
 */
bool StateManager::isExitCode()
{
    //std::cout << "(function) StateManager::isExitCode" << std::endl;    // debug

    return exitcode;
}

/*!
 * \fn void setExitCode(bool new_exitcode)
 * \param new_exitcode Exit code.
 *
 * 'exitcode' mutator.
 */
void StateManager::setExitCode(bool new_exitcode)
{
    //std::cout << "(function) StateManager::setExitCode" << std::endl;    // debug

    exitcode= new_exitcode;
}

/* ************************************************************************** */
