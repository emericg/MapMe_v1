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
 * \file ConfigManager.cpp
 * \brief Configuration MANAGER
 *
 * Handle the configuration of the game.
 */

#include "ConfigManager.h"

/* ************************************************************************** */

/*!
 * \fn ConfigManager()
 *
 * ConfigManager constructor.
 * Some operating system variables initialization (system user, user path, software path).
 * Note : this constructor is private and can only be called by the singleton.
 */
ConfigManager::ConfigManager()
{
    std::cout << "ConfigManager::ConfigManager" << std::endl;                // debug

    // Default values
    conf_rameVersion_default= 1.0;
    conf_rResx_default      = 1280;
    conf_rResy_default      = 720;
    conf_rRatio_default     = 1.77;
    conf_rFullscreen_default= false;
    conf_lLng_default       = "fr";
    conf_vMaster_default    = 100;
    conf_vMusic_default     = 75;
    conf_nUser_default      = "User";
    conf_nPort_default      = 3615;

    // Values
    conf_rameVersion= -1;
    conf_rResx      = -1;
    conf_rResy      = -1;
    conf_rRatio     = -1;
    conf_rFullscreen= false;
    conf_lLng       = "fr";
    conf_vMaster    = -1;
    conf_vMusic     = -1;
    conf_nUser      = "User";
    conf_nPort      = -1;

    #ifdef WIN32
        // Set local file path
            strncpy(path, "config.xml", 254);

        // Get env variables
            //%HOMEPATH%
            //%USERNAME%
    #else
        // Set folder path
            char *HOME= getenv("HOME");
            strncat(path, HOME, 254);
            strncat(path, "/.config/ProjetKIWI", 254);

        // Create folder
            mkdir(path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

        // Set file path
            strncat(path, "/config.xml", 254);

        // Get env variables
            system_user= getenv("USER");
            system_lng= getenv("LANG");
    #endif

    /*
    std::cout << "system user : " << system_user << std::endl;
    std::cout << "system language : " << system_lng << std::endl;
    std::cout << "config file path : " << path << std::endl;
    */
}

/*!
 * \fn ~ConfigManager()
 *
 * ConfigManager destructor. Don't do anything.
 * Note : this destructor is private and can only be called by the singleton.
 */
ConfigManager::~ConfigManager()
{
    std::cout << "ConfigManager::~ConfigManager -->  ";                    // debug
}

/*!
 * \fn bool LoadConfig()
 * \return true if everything is allright, false else.
 *
 * This function check, load and parse configuration file, then affect values.
 */
bool ConfigManager::LoadConfig()
{
    //std::cout << "(function) ConfigManager::LoadConfig" << std::endl;        // debug


    /*    Check config file    */
    std::ifstream configfile_txt(path, std::ios::in);
    if (!configfile_txt)
    {
        std::cerr << "   Unable to open config file." << std::endl;

        /*    Create new file and retry    */
        if (Create() == false)
        {
            std::cerr << "   Unable to create default config file." << std::endl;
            return false;
        }
        else
        {
            std::cerr << "   Config file created with disponible or default values." << std::endl;
        }
    }
    else
    {
        configfile_txt.close();
    }


    /*    Open config file    */
    TiXmlDocument configfile_xml(path);
    if (!configfile_xml.LoadFile())
    {
        std::cerr << "   Unable to parse config file. xml error #" << configfile_xml.ErrorId() << " : " << configfile_xml.ErrorDesc() << std::endl;
        return false;
    }


    /*    Read config file    */
    if (Read() == false)
    {
        std::cerr << "   Corruption(s) detected in config file, correction..." << std::endl;

        if (Write() == true)
        {
            std::cerr << "   Corruption(s) successfully corrected." << std::endl;
        }
        else
        {
            std::cerr << "   Corruption(s) impossible to correct." << std::endl;
            return false;
        }
    }

    return true;
}

/*!
 * \fn bool SaveConfig()
 * \return true if everything is allright, false else.
 *
 * This function save every configuration variables into one config file.
 */
bool ConfigManager::SaveConfig()
{
    //std::cout << "(function) ConfigManager::SaveConfig" << std::endl;        // debug

    return true;
}

/*!
 * \fn int getX()
 * \brief conf_rResx getter.
 * \return the horizontal resolution
 */
int ConfigManager::getX()
{
    return conf_rResx;
}

/*!
 * \fn int getY()
 * \brief conf_rResy getter.
 * \return the vertical resolution
 */
int ConfigManager::getY()
{
    return conf_rResy;
}

/*!
 * \fn int getFS()
 * \brief conf_rFullscreen getter.
 * \return the full screen state.
 */
bool ConfigManager::getFS()
{
    return conf_rFullscreen;
}

/*!
 * \fn bool Create()
 * \return true if everything is allright, false else.
 *
 * This function create a new configuration file using default values.
 */
bool ConfigManager::Create()
{
    //std::cout << "(function) ConfigManager::Create" << std::endl;        // debug

    // Create default config file
    std::ofstream configfile(path, std::ios::out);
    if (!configfile)
    {
        return false;
    }
    else
    {
        //
        std::string fullscreen_temp;
        if (conf_rFullscreen_default == true)
            fullscreen_temp= "on";
        else
            fullscreen_temp= "off";

        // Edit
        configfile
        << "<?xml version=\"1.0\" encoding=\"ASCII\"?>"
                << "\n<!--  MapMe : configuration  -->"
        << "\n"
        << "\n<configuration>"
        << "\n    <game version=\"" << conf_rameVersion_default << "\" />"
        << "\n    <resolution resx=\"" << conf_rResx_default << "\" resy=\"" << conf_rResy_default << "\" fullscreen=\"" << fullscreen_temp << "\" />"
        << "\n    <language lng=\"" << conf_lLng_default << "\" />"
        << "\n    <volumes master=\"" << conf_vMaster_default << "\" music=\"" << conf_vMusic_default << "\" />"
        << "\n    <network name=\"" << conf_nUser_default << "\" port=\"" << conf_nPort_default << "\" />"
        << "\n</configuration>"
        << std::endl;

        // Close file
        configfile.close();

        // Update statut
        return true;
    }
}

/*!
 * \fn bool Read()
 * \return true if everything is allright, false else.
 *
 * This function read configuration file and extract saved values.
 */
bool ConfigManager::Read()
{
    //std::cout << "(function) ConfigManager::Read" << std::endl;                // debug

    bool file_corrupt= false;


    // Open *safe* config file
    TiXmlDocument configfile(path);
    configfile.LoadFile();


    // Set XML paths
    TiXmlHandle docHandle(&configfile);
    game= docHandle.FirstChild("configuration").FirstChild("game").ToElement();
    resolution= docHandle.FirstChild("configuration").FirstChild("resolution").ToElement();
    language= docHandle.FirstChild("configuration").FirstChild("language").ToElement();
    volumes= docHandle.FirstChild("configuration").FirstChild("volumes").ToElement();
    network= docHandle.FirstChild("configuration").FirstChild("network").ToElement();


// =============================================================================
    // Read 'game' node
    if (!game)
    {
        file_corrupt= true;
        std::cerr << "   Unable to reach game node ! Using default values." << std::endl;
        conf_rameVersion= conf_rameVersion_default;
    }
    else
    {
        game->QueryDoubleAttribute("version", &conf_rameVersion);
        if (conf_rameVersion != conf_rameVersion_default)
        {
            file_corrupt= true;
            conf_rameVersion= conf_rameVersion_default;
            std::cerr << "   Old configuration file detected. Automatic correction on the way." << std::endl;
        }
    }

    // Read 'resolution' node
    if (!resolution)
    {
        file_corrupt= true;
        std::cerr << "   Unable to reach resolution node ! Using default values." << std::endl;
        conf_rResx= conf_rResx_default;
        conf_rResy= conf_rResy_default;
        conf_rFullscreen= false;
    }
    else
    {
        resolution->QueryIntAttribute("resx", &conf_rResx);
        if (conf_rResx<0 || conf_rResx>2048)
        {
            file_corrupt= true;
            conf_rResx= conf_rResx_default;
        }
        resolution->QueryIntAttribute("resy", &conf_rResy);
        if (conf_rResy<0 || conf_rResy>2048 )
        {
            file_corrupt= true;
            conf_rResy= conf_rResy_default;
        }
        if (conf_rResy != static_cast<int>(conf_rResx/1.777777))
        {
            conf_rResy= static_cast<int>(conf_rResx/1.777777);
        }

        std::string conf_rFullscreen_temp= resolution->Attribute("fullscreen");
        if (conf_rFullscreen_temp == "on")
            conf_rFullscreen= true;
        else if (conf_rFullscreen_temp == "off")
            conf_rFullscreen= false;
        else
        {
            file_corrupt= true;
            conf_rFullscreen= false;
        }
    }

    // Read 'language' node
    if (!language)
    {
        file_corrupt= true;
        std::cerr << "   Unable to reach language node ! Using default values." << std::endl;
        conf_lLng= conf_lLng_default;
    }
    else
    {
        conf_lLng= language->Attribute("lng");
        if (conf_lLng != "fr")
        {
            file_corrupt= true;
            conf_lLng= conf_lLng_default;
        }
    }

    // Read 'volumes' node
    if (!volumes)
    {
        file_corrupt= true;
        std::cerr << "   Unable to reach volumes node ! Using default values." << std::endl;
        conf_vMaster= conf_vMaster_default;
        conf_vMusic= conf_vMusic_default;
    }
    else
    {
        volumes->QueryIntAttribute("master", &conf_vMaster);
        if (conf_vMaster<0 || conf_vMaster>100)
        {
            file_corrupt= true;
            conf_vMaster= conf_vMaster_default;
        }
        volumes->QueryIntAttribute("music", &conf_vMusic);
        if (conf_vMusic<0 || conf_vMusic>100)
        {
            file_corrupt= true;
            conf_vMusic= conf_vMusic_default;
        }
    }

    // Read 'network' node
    if (!network)
    {
        std::cerr << "   Unable to reach network node ! Using default values." << std::endl;
        file_corrupt= true;
        //conf_nUser= session_user;
        conf_nUser= conf_nUser_default;
        conf_nPort= conf_nPort_default;
    }
    else
    {
        conf_nUser= network->Attribute("name");
        if (strncmp(conf_nUser.c_str(), "User", 254) == 0)
        {
            //conf_nUser= session_user;
            conf_nUser= conf_nUser_default;
        }

        network->QueryIntAttribute("port", &conf_nPort);
        if (conf_nPort<1)
        {
            file_corrupt= true;
            conf_nPort= conf_nPort_default;
        }
    }
// =============================================================================

    if (file_corrupt == true)
    {
        return false;
    }

    return true;
}

/*!
 * \fn bool Write()
 * \return true if everything is allright, false else.
 *
 * This function write configuration file, using a combinaison values already
 * available and default values.
 */
bool ConfigManager::Write()
{
    std::cout << "(function) ConfigManager::Write" << std::endl;            // debug

    // Write config file
    std::ofstream configfile(path, std::ios::out);
    if (!configfile)
    {
        return false;
    }
    else
    {
        //
        std::string fullscreen_temp;
        if (conf_rFullscreen == true)
            fullscreen_temp= "on";
        else
            fullscreen_temp= "off";

        // Edit
        configfile
        << "<?xml version=\"1.0\" encoding=\"ASCII\"?>"
                << "\n<!--  MapMe : configuration  -->"
        << "\n"
        << "\n<configuration>"
        << "\n    <game version=\"" << conf_rameVersion << "\" />"
        << "\n    <resolution resx=\"" << conf_rResx << "\" resy=\"" << conf_rResy << "\" fullscreen=\"" << fullscreen_temp << "\" />"
        << "\n    <language lng=\"" << conf_lLng << "\" />"
        << "\n    <volumes master=\"" << conf_vMaster << "\" music=\"" << conf_vMusic << "\" />"
        << "\n    <network name=\"" << conf_nUser << "\" port=\"" << conf_nPort << "\" />"
        << "\n</configuration>"
        << std::endl;

        // Close file
        configfile.close();

        // Update statut
        return true;
    }
}

/*!
 * \fn void Print()
 *
 * This function print acutal configuration in a terminal.
 */
void ConfigManager::Print()
{
    std::cout << "(function) ConfigManager::Print" << std::endl;            // debug

    std::cout << "Config file :"
        << "\nversion : " << conf_rameVersion
        << "\nres : " << conf_rResx << ", " << conf_rResy << ", fullscreen :" << conf_rFullscreen
        << "\nscreenratio : " << conf_rRatio
        << "\nlanguage : " << conf_lLng
        << "\nnetwork name : " << conf_nUser << ", port : " << conf_nPort
        << "\nvolume master : " << conf_vMaster << ", music : " <<  conf_vMusic
        << std::endl;
}

/* ************************************************************************** */
