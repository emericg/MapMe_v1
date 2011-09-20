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
 * \file ConfigManager.h
 * \brief Configuration MANAGER (HEADER)
 *
 * Handle the configuration values of the game.
 */

#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H
/* ************************************************************************** */

// C++ standard libraries
#include <iostream>
#include <fstream>
#include <string>

// Tiny XML library
#include "tinyxml/tinyxml.h"

#ifdef WIN32
    // WINDOWS library ?
#else
    // UNIX specifics libraries
    #include <sys/stat.h>
    #include <sys/types.h>
#endif

// Local file(s)
#include "Singleton.h"

/* ************************************************************************** */

/*!
 * \class ConfigManager
 * \brief class for handeling configuration.
 *
 * This class load and save configuration values.
 */
class ConfigManager : public Singleton<ConfigManager>
{
friend class Singleton<ConfigManager>;

public:
    bool LoadConfig();
    bool SaveConfig();
    void Print();

/*    Getters    */
    int getX();
    int getY();
    bool getFS();

    char *system_user;    /*!< system user, extracted from environment variable */
    char *system_lng;    /*!< system langage, extracted from environment variable */

/*    Values    */
    double    conf_rameVersion;
    int    conf_rResx;
    int    conf_rResy;
    double    conf_rRatio;
    bool    conf_rFullscreen;
    std::string    conf_lLng;
    int    conf_vMaster;
    int    conf_vMusic;
    std::string    conf_nUser;
    int    conf_nPort;

private:
    ConfigManager();
    ~ConfigManager();

    bool Create();
    bool Read();
    bool Write();

    char path[254];    /*!< configuration file path */

/*    XML paths    */
    TiXmlElement *game;
    TiXmlElement *resolution;
    TiXmlElement *language;
    TiXmlElement *volumes;
    TiXmlElement *network;

/*    Default values    */
    double    conf_rameVersion_default;
    int        conf_rResx_default;
    int        conf_rResy_default;
    double    conf_rRatio_default;
    bool        conf_rFullscreen_default;
    std::string    conf_lLng_default;
    int        conf_vMaster_default;
    int        conf_vMusic_default;
    std::string    conf_nUser_default;
    int        conf_nPort_default;
};

/* ************************************************************************** */
#endif
