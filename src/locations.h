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
 * \file locations.h
 * \brief Contains cities, capitals and countries classes.
 *
 * Contains cities, capitals and countries classes use by the game.
 */

#ifndef LOCATIONS_H
#define LOCATIONS_H
/* ************************************************************************** */

// C++ standard libraries
#include <iostream>
#include <fstream>
#include <string>

// C standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Local file(s)
#include "utils.h"

/* ************************************************************************** */
/*!
 * \class Country
 * \brief class that contain caracteristics of a country
 *
 * This class that contain caracteristics of a country :
 * name ; total area ; color (used to find it on the map)
 */
class Country
{
public:
    Country();
    ~Country();

    void country_print();

    std::string name;
    int area;
    int color[3];
};

/* ************************************************************************** */

/*!
 * \class City
 * \brief class that contain caracteristics of a city
 *
 * This class that contain caracteristics of a city/capital :
 * name ; country ; type (used by capitals only) ; and unparsed coordinates exctracts from database
 */
class City
{
public:
    City();
    ~City();

    void city_parse_coordinates();
    void city_convert_coordinates(double ratio);
    void city_print_coordinates();

    std::string name;
    std::string country;
    std::string type;    // for capitals only
    std::string unparsed_coordinates;

    // temp
    int latitude_degrees;
    int latitude_minutes;
    double latitude;
    std::string latitude_direction;

    int longitude_degrees;
    int longitude_minutes;
    double longitude;
    std::string longitude_direction;

    // final
    int coordinates_x;
    int coordinates_y;
};

/* ************************************************************************** */
#endif
