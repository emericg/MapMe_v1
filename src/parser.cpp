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
 * \file parser.cpp
 * \brief Databases parser.
 *
 * Used to parse cities, capitals and countries databases used by the game.
 */

#include "parser.h"

/* ************************************************************************** */
/* ******************************************* */

Parser::Parser()
{
    std::cout << "Parser::Parser" << std::endl;                // debug

    // Get resolution ratio
    ConfigManager &ConfigManager= ConfigManager::getInstance();
    ratio= (((double)ConfigManager.getX())/1280.0);

    // Get language
    strncpy(lng, ConfigManager.conf_lLng.c_str(), 4);

    countriesdb_statut= false;
    citiesdb_statut= false;

    totalcountries= 0;
    totalcities= 0;
}

/* ******************************************* */

Parser::~Parser()
{
    std::cout << "Parser::~Parser" << std::endl;                // debug
}

/* ******************************************* */
/* ******************************************* */

bool Parser::CheckCountriesFile()
{
    std::cout << "(position) Parser::CheckCountriesFile" << std::endl;    // debug

    // Countries DB
    strncpy(countriesdb_path, "databases/", 512);
    strncat(countriesdb_path, lng , 4);
    strncat(countriesdb_path, "/countries.xml", 512);
    //std::cout << "   path : " << countriesdb_path << std::endl;

    TiXmlDocument countriesdb(countriesdb_path);
    if (!countriesdb.LoadFile())
    {
        std::cerr << "   Unable to open countries database ! ERROR #" << countriesdb.ErrorId() << " , " << countriesdb.ErrorDesc() << std::endl;
        return EXIT_FAILURE;
    }
    else
    {
        TiXmlHandle docHandle(&countriesdb);
        infos= docHandle.FirstChildElement("database").FirstChild("infos").ToElement();

        if (!infos)
            countriesdb_statut= false;
        else
        {
            infos->QueryDoubleAttribute("version", &countriesdb_version);
            if (countriesdb_version != 1.0)
                countriesdb_statut= false;
            else
                countriesdb_statut= true;
        }
    }
}

/* ******************************************* */

bool Parser::ParseCountriesFile(Country *country[], short nb, short lv)
{
    std::cout << "(position) Parser::ParseCountriesFile" << std::endl;    // debug

    // Open 'database'
    TiXmlDocument countriesdb(countriesdb_path);
    if (!countriesdb.LoadFile())
    {
        std::cerr << "   Unable to open countriesdb database ! ERROR #" << countriesdb.ErrorId() << " : " << countriesdb.ErrorDesc() << std::endl;
        return false;
    }
    else if (countriesdb_statut == false)
    {
        std::cerr << "   Unable to load countriesdb database ! internal format ERROR" << std::endl;
        return false;
    }
    else
    {
        std::cout << "   countriesdb database successfully opened !" << std::endl;
    }

    // XML paths
    TiXmlHandle docHandle(&countriesdb);

    std::ostringstream oss;
    oss << lv;
    std::string llv= oss.str();
    std::string level= ("level" + llv);

    // Loading loop
    for(short i= 0; i<nb; i++)
    {
        countrynode= docHandle.FirstChildElement("database").FirstChild(level.c_str()).Child("country", i).ToElement();

        // load values
        country[i]->name= countrynode->Attribute("name");
        countrynode->QueryIntAttribute("area", &country[i]->area);

        //color?


        // loop
        if (countrynode->NextSiblingElement("country") == 0)
            break;
    }

    return true;
}

/* ******************************************* */

void Parser::PrintCountriesHeap(Country *country[], short nb, short lv)
{
    std::cout << "(position) Parser::PrintCountriesHeap" << std::endl;    // debug


    std::cout << "\n=== LEVEL : " << lv << " ===========================================";
    for(short i= 0; i<nb; i++)
    {
        std::cout << "\nname : " << country[i]->name
            << "\narea : " << country[i]->area
            << "\ncolor : " << country[i]->color[0] << " " << country[i]->color[1] << " " << country[i]->color[2];
    }
    std::cout << "\n==========================================================\n" << std::endl;
}

/* ******************************************* */
/* ******************************************* */

bool Parser::CheckCitiesFile()
{
    std::cout << "(position) Parser::CheckCitiesFile" << std::endl;        // debug

    // Path
    strncpy(citiesdb_path, "databases/", 512);
    strncat(citiesdb_path, lng, 4);
    strncat(citiesdb_path, "/cities.xml", 512);
    //std::cout << "   path : " << citiesdb_path << std::endl;

    // Open
    TiXmlDocument citiesdb(citiesdb_path);
    if (!citiesdb.LoadFile())
    {
        std::cerr << "   Unable to open cities database ! ERROR #" << citiesdb.ErrorId() << " : " << citiesdb.ErrorDesc() << std::endl;
        return false;
    }
    else
    {
        TiXmlHandle docHandle(&citiesdb);
        infos= docHandle.FirstChildElement("database").FirstChild("infos").ToElement();

        if (!infos)
        {
            citiesdb_statut=false;
            return false;
        }
        else
        {
            infos->QueryDoubleAttribute("version", &citiesdb_version);
            if (citiesdb_version != 1.0)
            {
                citiesdb_statut=false;
                return false;
            }
            else
            {
                citiesdb_statut=true;
                return true;
                std::cout << "   citiesdb database successfully opened !" << std::endl;
            }
        }
    }
}

/* ******************************************* */

bool Parser::ParseCitiesFile(City *city[], short nb, short lv)
{
    std::cout << "(position) Parser::ParseCitiesFile" << std::endl;        // debug

    // Open 'database'
    TiXmlDocument database(citiesdb_path);
    if (!database.LoadFile())        // redondant ?
    {
        std::cerr << "   Unable to open citiesdb database ! ERROR #" << database.ErrorId() << " , " << database.ErrorDesc() << std::endl;
        return false;
    }
    else if (citiesdb_statut == false)    // redondant ?
    {
        std::cerr << "   Unable to load citiesdb database ! internal format ERROR" << std::endl;
        return false;
    }

    // XML paths
    TiXmlHandle docHandle(&database);

    std::ostringstream oss;
    oss << lv;
    std::string llv= oss.str();
    std::string level= ("level" + llv);

    // XML node
    citynode= docHandle.FirstChild("database").FirstChild(level.c_str()).Child("city", 0).ToElement();

    // Count nodes
    totalcities= 0;
    while(citynode)
    {
        totalcities++;
        citynode= citynode->NextSiblingElement();
    }

    //citynode->FirstChildElement();
    std::cout << "  " << totalcities << " cities in this node." << std::endl;

    // City list
    short totalcities_tab[totalcities];
    for(short i=0; i<totalcities; i++)
        totalcities_tab[i]= 0;

    // Initialize random seed
    srand(time(NULL));

    // Random loading loop
    for(short i=0; i<nb; i++)
    {
        short a= rand() % totalcities;
        if (totalcities_tab[a] != 1)
        {
            citynode= docHandle.FirstChild("database").FirstChild(level.c_str()).Child("city", a).ToElement();

            // load values
            city[i]->name= citynode->Attribute("name");
            city[i]->country= citynode->Attribute("country");
            city[i]->unparsed_coordinates= citynode->Attribute("coordinates");

            // convert coordinates
            city[i]->city_parse_coordinates();
            city[i]->city_convert_coordinates(ratio);
            //city[i]->city_print_coordinates();            // debug

            // update usetable
            totalcities_tab[a]= 1;
        }
        else
        {
            i--;
        }
    }

    return true;
}

/* ******************************************* */

void Parser::PrintCitiesHeap(City *city[], short nb, short lv)
{
    std::cout << "(position) Parser::PrintCitiesHeap" << std::endl;    // debug

    std::cout << "\n=== LEVEL : " << lv << " ===========================================";
    for(short i= 0; i<nb; i++)
    {
        std::cout << "\nname : " << city[i]->name
            << "\ncountry : " << city[i]->country
            << "\ncoordinates (pixels) : " << city[i]->coordinates_x << " " << city[i]->coordinates_y;
    }
    std::cout << "\n==========================================================\n" << std::endl;
}

/* ******************************************* */
/* ******************************************* */

bool Parser::CheckCapitalsFile()
{
    std::cout << "(position) Parser::CheckCapitalsFile" << std::endl;    // debug

    // Path
    strncpy(capitalsdb_path, "databases/", 512);
    strncat(capitalsdb_path, lng, 4);
    strncat(capitalsdb_path, "/capitals.xml", 512);
    //std::cout << "   path : " << capitalsdb_path << std::endl;

    // Open
    TiXmlDocument capitalsdb(capitalsdb_path);
    if (!capitalsdb.LoadFile())
    {
        std::cerr << "   Unable to open capitals database ! ERROR #" << capitalsdb.ErrorId() << " : " << capitalsdb.ErrorDesc() << std::endl;
        return false;
    }
    else
    {
        TiXmlHandle docHandle(&capitalsdb);
        infos= docHandle.FirstChildElement("database").FirstChild("infos").ToElement();

        if (!infos)
        {
            capitalsdb_statut=false;
            return false;
        }
        else
        {
            infos->QueryDoubleAttribute("version", &capitalsdb_version);
            if (capitalsdb_version != 1.0)
            {
                capitalsdb_statut=false;
                return false;
            }
            else
            {
                capitalsdb_statut=true;
                return true;
                std::cout << "   capitalsdb database successfully opened !" << std::endl;
            }
        }
    }
}

/* ******************************************* */

bool Parser::ParseCapitalsFile(City *city[], short nb, short lv)
{
    std::cout << "(position) Parser::ParseCapitalsFile" << std::endl;    // debug

    // Open 'database'
    TiXmlDocument database(capitalsdb_path);
    if (!database.LoadFile())        // redondant ?
    {
        std::cerr << "   Unable to open capitalsdb database ! ERROR #" << database.ErrorId() << " , " << database.ErrorDesc() << std::endl;
        return false;
    }
    else if (capitalsdb_statut == false)        // redondant ?
    {
        std::cerr << "   Unable to load capitalsdb database ! shorternal format ERROR" << std::endl;
        return false;
    }

    // XML paths
    TiXmlHandle docHandle(&database);

    std::ostringstream oss;
    oss << lv;
    std::string llv= oss.str();
    std::string level= ("level" + llv);

    // XML node
    capitalnode= docHandle.FirstChild("database").FirstChild(level.c_str()).Child("capital", 0).ToElement();

    // Count nodes
    totalcapitals= 0;
    while(capitalnode)
    {
        totalcapitals++;
        capitalnode= capitalnode->NextSiblingElement();
    }

    //capitalnode->FirstChildElement();
    std::cout << "  " << totalcapitals << " capitals in this node." << std::endl;

    // Capitals list
    short totalcapitals_tab[totalcapitals];
    for(short i= 0; i<totalcapitals; i++)
        totalcapitals_tab[i]= 0;

    // Initialize random seed
    srand(time(NULL));

    // Random loading loop
    for(short i=0; i<nb; i++)
    {
        short a= rand() % totalcapitals;
        if (totalcapitals_tab[a] != 1)
        {
            capitalnode= docHandle.FirstChild("database").FirstChild(level.c_str()).Child("capital", a).ToElement();

            // load values
            city[i]->name= capitalnode->Attribute("name");
            city[i]->country= capitalnode->Attribute("capitalof");
            if (capitalnode->Attribute("type") != NULL)
                city[i]->type= capitalnode->Attribute("type");
            else
                city[i]->type= "";
            city[i]->unparsed_coordinates= capitalnode->Attribute("coordinates");

            // convert coordinates
            city[i]->city_parse_coordinates();
            city[i]->city_convert_coordinates(ratio);
            //city[i]->city_print_coordinates();    // debug

            // update usetable
            totalcapitals_tab[a]= 1;
        }
        else
        {
            i--;
        }
    }

    return true;
}

/* ******************************************* */

void Parser::PrintCapitalsHeap(City *city[], short nb, short lv)
{
    std::cout << "(position) Parser::PrintCapitalsHeap" << std::endl;    // debug

    std::cout << "\n=== LEVEL : " << lv << " ===========================================";
    for(short i= 0; i<nb; i++)
    {
        std::cout << "\ncity : " << city[i]->name
            << "\ntype : " << city[i]->type
            << "\ncapital of : " << city[i]->country
            << "\ncoordinates (pixels) : " << city[i]->coordinates_x << " " << city[i]->coordinates_y;
    }
    std::cout << "\n==========================================================\n" << std::endl;
}

/* ******************************************* */
/* ******************************************* */
