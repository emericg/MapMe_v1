cmake_minimum_required(VERSION 2.4)

## MapMe
##################################
PROJECT(MapMe)
SET( ${PROJECT_NAME}_MAJOR_VERSION 0 )
SET( ${PROJECT_NAME}_MINOR_VERSION 67 )


## Files
##################################
SET(SRC src/tinyxml/tinyxml.cpp src/tinyxml/tinyxmlerror.cpp src/tinyxml/tinystr.cpp src/tinyxml/tinyxmlparser.cpp
    src/sdlgfx/SDL_framerate.c src/sdlgfx/SDL_rotozoom.c
    src/Singleton.h src/StateManager.cpp src/ConfigManager.cpp src/GfxManager.cpp src/EventManager.cpp src/SoundManager.cpp
    src/utils.cpp src/timer.cpp src/menu.cpp src/locations.cpp src/parser.cpp src/game_world.cpp src/main.cpp)


## Looking for libraries
##################################
FIND_PACKAGE( SDL       REQUIRED )
FIND_PACKAGE( SDL_image REQUIRED )
FIND_PACKAGE( SDL_mixer REQUIRED )
FIND_PACKAGE( SDL_ttf   REQUIRED )

if( NOT SDL_FOUND )
    message ( FATAL_ERROR "SDL not found!" )
endif( NOT SDL_FOUND )
if( NOT SDLIMAGE_FOUND )
    message ( FATAL_ERROR "SDL_IMAGE not found!" )
endif ( NOT SDLIMAGE_FOUND )
if( NOT SDLMIXER_FOUND )
    message ( FATAL_ERROR "SDL_MIXER not found!" )
endif ( NOT SDLMIXER_FOUND )
if( NOT SDLTTF_FOUND )
    message ( FATAL_ERROR "SDL_TTF not found!" )
endif( NOT SDLTTF_FOUND )


## Includes for compilation
##################################
INCLUDE_DIRECTORIES( ${SDL_INCLUDE_DIR} ${SDLIMAGE_INCLUDE_DIR} ${SDLMIXER_INCLUDE_DIR} ${SDLTTF_INCLUDE_DIR} )


## Make
##################################
ADD_EXECUTABLE(MapMe ${SRC})


## Link
##################################
TARGET_LINK_LIBRARIES( MapMe ${SDL_LIBRARY} ${SDLIMAGE_LIBRARY} ${SDLMIXER_LIBRARY} ${SDLTTF_LIBRARY} )
