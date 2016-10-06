# cmake_minimum_required(VERSION <specify CMake version here>)
project(BattleShipGame)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic -Wno-long-long -O0 -ggdb")

set(SOURCE_FILES main.cpp BoardTile.h Ship.cpp Ship.h BoardTile.cpp Board.cpp Board.h Game.cpp Game.h Player.h AIPlayer.cpp AIPlayer.h EasyAIPlayer.cpp EasyAIPlayer.h CleverAIPlayer.cpp CleverAIPlayer.h ConsolePlayer.cpp ConsolePlayer.h GeniusAIPlayer.cpp GeniusAIPlayer.h NetworkPlayer.cpp NetworkPlayer.h Session.cpp Session.h Coord.h Strategy.cpp Strategy.h)
add_executable(BattleShipGame ${SOURCE_FILES})