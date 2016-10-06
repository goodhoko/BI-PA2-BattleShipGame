#ifndef BATTLESHIPGAME_SESSION_H
#define BATTLESHIPGAME_SESSION_H

#include <iostream>
#include <fstream>
#include <sstream>

#include "ConsolePlayer.h"
#include "EasyAIPlayer.h"
#include "CleverAIPlayer.h"
#include "GeniusAIPlayer.h"
#include "NetworkPlayer.h"
#include "Game.h"
#include "Player.h"

/**
 * class maintianing start and updates of the game.
 */
class Session {
public:
    /** constructor  - asks user for the desired game mode and initiates Players*/
    Session() :  player1(NULL), player2(NULL) { }
    /** destructor */
    ~Session();

    /** selects the game mode, and initiate the players */
    bool initiate();
    /**load ships from ships.txt, start a game and keeps updating it until it is over */
    void play();

private:
    /**Loads ships from ships.txt file */
    bool loadShips();

    /**variable to hold pinter to player */
    Player* player1;
    /**variable to hold pinter to player */
    Player* player2;
    /**container to hold loaded ships*/
    vector<Ship> fleet;
};

#endif //BATTLESHIPGAME_SESSION_H