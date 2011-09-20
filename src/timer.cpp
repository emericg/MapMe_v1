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
 * \file timer.cpp
 * \brief Simple timer class.
 *
 * This file contain a timer class.
 */

#include "timer.h"

/* ************************************************************************** */

/*!
 * \fn Timer();
 *
 * Timer constructor.
 */
Timer::Timer()
{
    // States and variables initialization
    started= false;
    paused= false;

    startTicks= 0;
    pausedTicks= 0;
}

/*!
 * \fn ~Timer();
 *
 * emty Timer destructor.
 */
Timer::~Timer()
{
    // empty
}

/*!
 * \fn void start();
 *
 * Start the timer, and reset it from start if timer is already running.
 */
void Timer::start()
{
    // Start the timer
    started= true;
    paused= false;

    // Get actual time.
    startTicks= SDL_GetTicks();
}

/*!
 * \fn void stop();
 *
 * Stop the timer.
 */
void Timer::stop()
{
    // Stop the timer
    started= false;
    paused= false;
}

/*!
 * \fn void pause();
 *
 * Pause the timer. It must be running and unpaused, otherwise this function do nothing.
 */
void Timer::pause()
{
    if ((started == true) && (paused == false))
    {
        paused= true;

        // Get the time when paused signal is encountered
        pausedTicks= SDL_GetTicks() - startTicks;
    }
}

/*!
 * \fn void unpause();
 *
 * Unpause the timer. Must be paused, otherwise this function do nothing.
 */
void Timer::unpause()
{
    if (paused == true)
    {
        paused= false;

        // Remove the paused time from the total time
        startTicks= SDL_GetTicks() - pausedTicks;
        pausedTicks= 0;
    }
}

/*!
 * \fn unsigned int get_time();
 * \return time elapsed, in millisecond.
 *
 * Return elapsed time from timer start.
 */
unsigned int Timer::get_time()
{
    if (started == true)
    {
        if (paused == true)
        {
            return pausedTicks;
        }
        else
        {
            return SDL_GetTicks() - startTicks;
        }
    }
    else
    {
        return 0;
    }
}

/*!
 * \fn bool is_started();
 * \return true if timer is started, else false.
 *
 * Return timer global state.
 */
bool Timer::is_started()
{
    return started;
}

/*!
 * \fn bool is_paused();
 * \return true if timer is paused, else false.
 *
 * Return timer pause state.
 */
bool Timer::is_paused()
{
    return paused;
}

/* ************************************************************************** */
