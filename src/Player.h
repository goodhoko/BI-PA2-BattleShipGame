#ifndef BATTLESHIPGAME_PLAYER_H
#define BATTLESHIPGAME_PLAYER_H

#include <string>

#include "Board.h"

using namespace std;

/**
 * abstract class representing Player
 */
class Player {
public:
    /** constructor */
    Player(const char* n) : name(n) { }
    /** destructor */
    virtual ~Player() { }

    /**Prompt to player to play her move. */
    virtual Ship* move(Board& attackBoard, Board& myBoard) = 0;
    /**Prompt to player to place ship in to a board */
    virtual void placeShip(Ship& s, Board& b) = 0;
    /** Method to let the player know she has won */
    virtual void win(Board& attackBoard, Board& myBoard) = 0;
    /** Method to let the player know she has lose */
    virtual void lose(Board& attackBoard, Board& myBoard) = 0;

private:
    /** Name of the player --- Name is not used in this version */
    string name;
};

#endif //BATTLESHIPGAME_PLAYER_H