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
 * \file utils.cpp
 * \brief Various utilities.
 *
 * Functions to performe various tasks, mostly on String.
 */

#include "utils.h"

/* ************************************************************************** */

template<typename T>
/*!
 * \fn std::string to_string(const T & Value);
 * \param Value A template which could be a variable of any type.
 * \return This function return a string, converted from the param
 *
 * Convertion tool which can convert 'anything' into a string, by writing it into an outpout stream (std::ostringstream)
 */
std::string to_string(const T & Value)
{
    std::ostringstream oss;
    oss << Value;

    return oss.str();
}

template<typename T>
/*!
 * \fn bool from_string(const std::string & Str, T & Dest);
 * \param Str A reference to the string to convert.
 * \param Dest A reference to a template which could be a variable of any type.
 * \return This function return true if the convertion succed, else false.
 *
 * Convertion tool which can convert a string into 'anything', by writing the source string into an input stream (std::istringstream), and writing it's content into 'Dest'.
 */
bool from_string(const std::string & Str, T & Dest)
{
    // Creat stream from 'Ster'
    std::istringstream iss(Str);

    // Try convertion to 'Dest'
    return iss >> Dest != 0;
}

/*!
 * \fn std::string trim(const std::string & s);
 * \param s A reference to the 'cut' string.
 * \return This function return a string, but cutted.
 *
 * Convertion tool which can cut a string when encounter the string passed in parameter.
 */
std::string trim(const std::string & s)
{
    if (s.length() == 0)
        return s;

    int b= s.find_first_not_of(" \t\r");
    int e= s.find_last_not_of(" \t\r");

    if (b == -1) // No non-spaces
        return "";

    return std::string(s, b, e - b + 1);
}

/* ************************************************************************** */
