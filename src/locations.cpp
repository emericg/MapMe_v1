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
 * \file locations.cpp
 * \brief Contains cities, capitals and countries classes.
 * 
 * Contains cities, capitals and countries classes use by the game.
 */

#include "locations.h"

/* ************************************************************************** */
/* ************************************************************************** */

Country::Country()
{
    //std::cout << "Country::Country()" << std::endl;            // debug
    
    name= "empty";
    
    area= 0;
    color[0]= 0;
    color[1]= 0;
    color[2]= 0;
}

/* ************************************************************************** */

Country::~Country()
{
    //std::cout << "Country::~Country()" << std::endl;            // debug
    
    // do nothing
}

/* ************************************************************************** */
/* ************************************************************************** */

City::City()
{
    //std::cout << "City::City()" << std::endl;                // debug
    
    name= "empty";
    country= "empty";
    type= "";
    unparsed_coordinates= "empty";
    
    coordinates_x= 0;
    coordinates_y= 0;
}

/* ************************************************************************** */

City::~City()
{
    //std::cout << "City::~City()" << std::endl;                // debug
    
    // do nothing
}

/* ************************************************************************** */
/* ************************************************************************** */

void City::city_parse_coordinates()
{
    //std::cout << "City::city_parse_coordinates()" << std::endl;        // debug
    
    // COORDINATES FORMAT  :  xx°xx'N xx°xx'E
    
    // Cut latitude-longitude
        std::string::size_type cutter= unparsed_coordinates.find(" ");
        std::string latitude_degreesminutesdirection= trim(unparsed_coordinates.substr(0,cutter));
        std::string longitude_degreesminutesdirection= trim(unparsed_coordinates.substr(cutter+1));
    
    // Parse latitude
        std::string::size_type cutter_la1= latitude_degreesminutesdirection.find("'");
            latitude_direction= trim(latitude_degreesminutesdirection.substr(cutter_la1+1));
            std::string latitude_degreesminutes= trim(latitude_degreesminutesdirection.substr(0, cutter_la1));
    
        std::string::size_type cutter_la2= latitude_degreesminutes.find("*");
            std::istringstream la1( trim(latitude_degreesminutes.substr(0,cutter_la2)) );
            la1 >> latitude_degrees;
            
            std::istringstream la2( trim(latitude_degreesminutes.substr(cutter_la2+1)) );
            la2 >> latitude_minutes;
    
    // Parse longitude
        std::string::size_type cutter_lo1= longitude_degreesminutesdirection.find("'");
            longitude_direction= trim(longitude_degreesminutesdirection.substr(cutter_lo1+1));
            std::string longitude_degreesminutes= trim(longitude_degreesminutesdirection.substr(0, cutter_lo1));

        std::string::size_type cutter_lo2= longitude_degreesminutes.find("*");
            std::istringstream lo1( trim(longitude_degreesminutes.substr(0,cutter_lo2)) );
            lo1 >> longitude_degrees;
        
            std::istringstream lo2( trim(longitude_degreesminutes.substr(cutter_lo2+1)) );
            lo2 >> longitude_minutes;
}

/* ************************************************************************** */

void City::city_convert_coordinates(double ratio)
{
    //std::cout << "City:city_convert_coordinates()" << std::endl;        // debug
    
    
    // Calcul effective latitude and longitude
    latitude= (latitude_degrees + ((latitude_minutes * (5.0/3.0)) / 100.0));
    longitude= (longitude_degrees + ((longitude_minutes * (5.0/3.0)) / 100.0));
    
    
    // Setup robinson table
    double pos[91][2];
    for(int i=0; i < 91; i++)
    {
        pos[i][1]= i;
    }
    pos[0][2]= 1; // From robinson table
        pos[1][2]= 0.9998;
        pos[2][2]= 0.9995;
        pos[3][2]= 0.9992;
        pos[4][2]= 0.9989;
    pos[5][2]= 0.9986; // From robinson table
        pos[6][2]= 0.9994;
        pos[7][2]= 0.9984;
        pos[8][2]= 0.9974;
        pos[9][2]= 0.9964;
    pos[10][2]= 0.9954; // From robinson table
        pos[11][2]= 0.9944;
        pos[12][2]= 0.9934;
        pos[13][2]= 0.9924;
        pos[14][2]= 0.9914;
    pos[15][2]= 0.9900; // From robinson table
        pos[16][2]= 0.9880;
        pos[17][2]= 0.9865;
        pos[18][2]= 0.9850;
        pos[19][2]= 0.9835;
    pos[20][2]= 0.9822; // From robinson table
        pos[21][2]= 0.9802;
        pos[22][2]= 0.9782;
        pos[23][2]= 0.9762;
        pos[24][2]= 0.9742;
    pos[25][2]= 0.9730; // From robinson table
        pos[26][2]= 0.9700;
        pos[27][2]= 0.9670;
        pos[28][2]= 0.9650;
        pos[29][2]= 0.9620;
    pos[30][2]= 0.9600; // From robinson table
        pos[31][2]= 0.9560;
        pos[32][2]= 0.9520;
        pos[33][2]= 0.9480;
        pos[34][2]= 0.9450;
    pos[35][2]= 0.9427; // From robinson table
        pos[36][2]= 0.9366;
        pos[37][2]= 0.9326;
        pos[38][2]= 0.9286;
        pos[39][2]= 0.9256;
    pos[40][2]= 0.9216; // From robinson table
        pos[41][2]= 0.9162;
        pos[42][2]= 0.9112;
        pos[43][2]= 0.9072;
        pos[44][2]= 0.9022;
    pos[45][2]= 0.8962; // From robinson table
        pos[46][2]= 0.8909;
        pos[47][2]= 0.8859;
        pos[48][2]= 0.8799;
        pos[49][2]= 0.8729;
    pos[50][2]= 0.8679; // From robinson table
        pos[51][2]= 0.8600;
        pos[52][2]= 0.8510;
        pos[53][2]= 0.8450;
        pos[54][2]= 0.8400;
    pos[55][2]= 0.8350; // From robinson table
        pos[56][2]= 0.8306;
        pos[57][2]= 0.8256;
        pos[58][2]= 0.8156;
        pos[59][2]= 0.8086;
    pos[60][2]= 0.7986; // From robinson table
        pos[61][2]= 0.7917;
        pos[62][2]= 0.7827;
        pos[63][2]= 0.7727;
        pos[64][2]= 0.7657;
    pos[65][2]= 0.7597; // From robinson table
        pos[66][2]= 0.7586;
        pos[67][2]= 0.7486;
        pos[68][2]= 0.7386;
        pos[69][2]= 0.7256;
    pos[70][2]= 0.7186; // From robinson table
        pos[71][2]= 0.7102;
        pos[72][2]= 0.7032;
        pos[73][2]= 0.6932;
        pos[74][2]= 0.6832;
    pos[75][2]= 0.6732; // From robinson table
        pos[76][2]= 0.6613;
        pos[77][2]= 0.6513;
        pos[78][2]= 0.6413;
        pos[79][2]= 0.6313;
    pos[80][2]= 0.6213; // From robinson table
        pos[81][2]= 0.6122;
        pos[82][2]= 0.6022;
        pos[83][2]= 0.5922;
        pos[84][2]= 0.5822;
    pos[85][2]= 0.5722; // From robinson table
        pos[86][2]= 0.56922;
        pos[87][2]= 0.5622;
        pos[88][2]= 0.5552;
        pos[89][2]= 0.5422;
        pos[89][2]= 0.5352;
    pos[90][2]= 0.5322; // From robinson table
    
    
    // Convert coordinates in geographic format to pixel, using "ROBINSON projection"
    // http://en.wikipedia.org/wiki/Robinson_projection
    if (latitude_direction == "N" || latitude_direction == "n")
        coordinates_y= static_cast<int>(ratio*(401.5 - latitude*4.500));
    else if (latitude_direction == "S" || latitude_direction == "s")
        coordinates_y= static_cast<int>(ratio*(401.5 + latitude*4.512));
    
    if (longitude_direction == "E" || longitude_direction == "e")
        coordinates_x= static_cast<int>(ratio*(573.0 + (longitude*4.135)*(pos[static_cast<int>(latitude)][2])));
    else if (longitude_direction == "W" || longitude_direction == "w")
        coordinates_x= static_cast<int>(ratio*(573.0 - (longitude*4.205)*(pos[static_cast<int>(latitude)][2])));    // + ?
}

/* ************************************************************************** */

void City::city_print_coordinates()
{
    //std::cout << "City:city_print_coordinates()" << std::endl;            // debug
    
    // City :
    std::cout << "================================" << std::endl;
    std::cout << "city : " << name << std::endl;
    
    // Check parsing
    std::cout << "unparsed  : " << unparsed_coordinates << std::endl;
    std::cout << "latitude  : " << latitude_degrees << " ° " << latitude_minutes << " ' " << latitude_direction << std::endl;
    std::cout << "longitude : " << longitude_degrees << " ° " << longitude_minutes << " ' " << longitude_direction << std::endl;
    
    // Check convertion
    std::cout << "latitude  : " << coordinates_y << "y pixels" << std::endl;
    std::cout << "longitude : " << coordinates_x << "x pixels"<< std::endl;
}

/* ************************************************************************** */
/* ************************************************************************** */
