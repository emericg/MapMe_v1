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
 * \file utils.h
 * \brief Various utilities.
 *
 * Functions to perform various tasks on strings.
 */

// C++ standard libraries
#include <iostream>
#include <sstream>
#include <string>

/* ************************************************************************** */

template<typename T>
std::string to_string(const T & Value);

template<typename T>
bool from_string(const std::string & Str, T & Dest);

std::string trim(const std::string & s);

/* ************************************************************************** */
