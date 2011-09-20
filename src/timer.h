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
 * \file timer.h
 * \brief Simple timer class (HEADER).
 *
 * This file contain a timer class.
 */

#ifndef TIMER_H
#define TIMER_H
/* ************************************************************************** */

// SDL Library
#include <SDL/SDL.h>

/* ************************************************************************** */

/*!
 * \class Timer
 * \brief Simple timer class.
 *
 * This is a timer class, using SDL_GetTicks from SDL library.
 * The timer can be started, paused and stopped.
 */
class Timer
{
public:
    Timer();
    virtual ~Timer();

    void start();
    void stop();
    void pause();
    void unpause();

    unsigned int get_time();
    bool is_started();
    bool is_paused();

private:
    unsigned int startTicks;        /**< Time saved at timer start */
    unsigned int pausedTicks;    /**< Time saved when timer is paused. Used to unpause the timer */
    bool started;                /**< Is the timer started ? */
    bool paused;                /**< Is the timer paused ? */
};

/* ************************************************************************** */
#endif
