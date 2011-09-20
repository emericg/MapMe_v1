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
 * \file parser.h
 * \brief Databases parser (HEADER).
 *
 * Used to parse cities, capitals and countries databases, use by the game.
 */

#ifndef PARSER_H
#define PARSER_H

/* *************************************************************************** */

// C++ standard libraries
#include <iostream>
#include <string>
#include <fstream>

// C standard libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Tiny XML library
#include "tinyxml/tinyxml.h"

// Local file(s)
#include "ConfigManager.h"
#include "locations.h"

/* ************************************************************************** */

/*!
 * \class Parser
 * \brief Databases parser.
 *
 * Used to parse cities, capitals and countries databases, use by the game.
 */
class Parser
{
public:
    Parser();
    ~Parser();

    bool CheckCountriesFile();
    bool ParseCountriesFile(Country *country[], short nb, short lv);
    void PrintCountriesHeap(Country *country[], short nb, short lv);

    bool CheckCitiesFile();
    bool ParseCitiesFile(City *city[], short nb, short lv);
    void PrintCitiesHeap(City *city[], short nb, short lv);

    bool CheckCapitalsFile();
    bool ParseCapitalsFile(City *city[], short nb, short lv);
    void PrintCapitalsHeap(City *city[], short nb, short lv);

private:
    double ratio;
    char lng[4];
    TiXmlElement *infos;

/*    Countries db    */
    short totalcountries;
    bool countriesdb_statut;
    char countriesdb_path[512];
    double countriesdb_version;
    TiXmlElement *countrynode;

/*    Cities db    */
    short totalcities;
    bool citiesdb_statut;
    char citiesdb_path[512];
    double citiesdb_version;
    TiXmlElement *citynode;

/*    Capitals db    */
    short totalcapitals;
    bool capitalsdb_statut;
    char capitalsdb_path[512];
    double capitalsdb_version;
    TiXmlElement *capitalnode;
};

/* ************************************************************************** */
#endif
