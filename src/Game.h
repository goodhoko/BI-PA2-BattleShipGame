#ifndef BATTLESHIPGAME_GAME_H
#define BATTLESHIPGAME_GAME_H

#include <iostream>

#include "Player.h"

/**
 * Class for managing basics of the BattleShip game (placing boats, and moves)
 */
class Game {
public:
    /** constructor */
    Game(Player& p1, Player& p2, vector<Ship>& f) : player1(p1), player2(p2), fleet(f), gameO(false) { std::srand(unsigned(time(0))); }

    /**Prompts both players to place ships the game has in it's fleet */
    void placeShips();
    /** Prompts both players for move. If one of the board's fleets are completely sunk, it sets the GameO tu true */
    void gameUpdate();
    /** return true if game ended */
    bool gameOver() const;

private:
    /** sets GameO to true */
    void endGame();

    /**variable to hold the player */
    Player& player1;
    /**variable to hold the player */
    Player& player2;
    /**variables to hold the boards */
    Board p1Board, p2Board;
    /**container for the ships */
    vector<Ship>& fleet;
    /**variable to hold state of the game. true -> game is over, false -> game is on */
    bool gameO;
};

#endif //BATTLESHIPGAME_GAME_H