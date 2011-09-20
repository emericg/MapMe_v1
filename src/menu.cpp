/*
    This program is free software: you can redistribute it and/or modify
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
 * \file menu.cpp
 * \brief Menu class.
 *
 * This file handle the menu.
 */

#include "menu.h"

/* ************************************************************************** */

/*!
 * \fn Menu()
 *
 * Menu constructor. Some variables initialization are in there.
 */
Menu::Menu()
{
    std::cout << "Menu::Menu" << std::endl;                // debug

    menuposition= 1;
    menupositioncursor= 1;
}

/*!
 * \fn ~Menu()
 *
 * empty Menu destructor.
 */
Menu::~Menu()
{
    std::cout << "Menu::~Menu" << std::endl;                            // debug
}

/*!
 * \fn short getMenuPosition()
 * \return It return the 'menuposition' variable.
 *
 * 'menuposition' accessor.
 */
short Menu::getMenuPosition()
{
    //std::cout << "(function) Menu::getMenuPosition" << std::endl;            // debug

    return menuposition;
}

/*!
 * \fn void setMenuPosition(short new_menuposition)
 * \param new_menuposition The new position in the menu.
 *
 * 'menuposition' mutator.
 */
void Menu::setMenuPosition(short new_menuposition)
{
    //std::cout << "(function) Menu::setMenuPosition" << std::endl;            // debug

    if (new_menuposition >= 0 && new_menuposition <= 4)
    {
        menuposition= new_menuposition;
    }
    else
    {
        std::cerr << "setMenuPosition error : new_menuposition out of range (" << new_menuposition << ")" << std::endl;
    }
}

/*!
 * \fn short getMenuPositionCursor()
 * \return It return the 'menuposition' variable
 *
 * 'menupositioncursor' accessor.
 */
short Menu::getMenuPositionCursor()
{
    //std::cout << "(function) Menu::getMenuPositionCursor" << std::endl;        // debug

    return menupositioncursor;
}

/*!
 * \fn void setMenuPositionCursor(short new_menupositioncursor)
 * \param new_menupositioncursor The new position of the cursor.
 *
 * 'menupositioncursor' accessor.
 */
void Menu::setMenuPositionCursor(short new_menupositioncursor)
{
    //std::cout << "(function) Menu::setMenuPositionCursor" << std::endl;        // debug

    if (new_menupositioncursor >= 0 && new_menupositioncursor <= 5)
    {
        menupositioncursor= new_menupositioncursor;
    }
    else
    {
        std::cerr << "setMenuPositionCursor error : new_menupositioncursor out of range (" << new_menupositioncursor << ")" << std::endl;
    }
}

/*!
 * \fn void MenuPipe()
 *
 * This function is the menu pipeline.
 * Directly called by the main function, handle everything related to the menu (events handeling, drawing).
 */
void Menu::MenuPipe()
{
    //std::cout << "(function) Menu::MenuPipe" << std::endl;                // debug

    EventManager &EventManager= EventManager::getInstance();
    GfxManager &GfxManager= GfxManager::getInstance();

    // Handle events
    EventManager.MenuEvents(*this);

    // Draw
    GfxManager.menuDraw(menuposition, menupositioncursor);
    GfxManager.menuDrawArea(menuposition, menupositioncursor);
}

/* ************************************************************************** */
