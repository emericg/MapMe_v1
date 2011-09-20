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
 * \file menu.h
 * \brief Menu class (HEADER).
 *
 * This file handle the menu.
 */

#ifndef MENU_H
#define MENU_H
/* ************************************************************************** */

// C++ standard library
#include <iostream>

// Local file(s)
#include "GfxManager.h"
#include "EventManager.h"

/* ************************************************************************** */

/*!
 * \class Menu
 * \brief Menu class.
 *
 * This class handle the menu.
 */
class Menu
{
public:
    Menu();
    ~Menu();

    short getMenuPosition();
    void setMenuPosition(short new_menuposition);
    short getMenuPositionCursor();
    void setMenuPositionCursor(short new_menupositioncursor);
    void MenuPipe();

private:
    short menuposition;        /**< current menu position */
    short menupositioncursor;    /**< cursor menu position */
};

/* ************************************************************************** */
#endif
