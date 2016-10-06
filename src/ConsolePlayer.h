#ifndef BATTLESHIPGAME_CONSOLEPLAYER_H
#define BATTLESHIPGAME_CONSOLEPLAYER_H

#include <iostream>
#include <utility>

#include "Player.h"

/**
 * Class for local player communicating thru console
 */
class ConsolePlayer : public Player{
public:
    /** constructor */
    ConsolePlayer(const char* n) : Player(n) { }
    /** destructor */
    ~ConsolePlayer() { }

    /** clears the terminal by printing out 50 new lines */
    static void clear(ostream& out);

    /** Asks user for ship placement */
    void placeShip(Ship& s, Board& b);
    /**Asks user for coordinates to shoot at */
    Ship* move(Board& attackBoard, Board& myBoard);
    /** converts user representation of column into uint8_t version */
    static uint8_t letterToCoord(char c);
    /** converts user representation of row into uint8_t version */
    static uint8_t numberToCoord(char c);
    /** Display message about winning the game */
    void win(Board& attackBoard, Board& myBoard);
    /** Display message about losing the game */
    void lose(Board& attackBoard, Board& myBoard);

protected:
    /**read input for ship placement from terminal */
    bool readShipPlacement(char* r1, char* c1, char* r2, char* c2, istream& in);
    /**read input for shooting from terminal */
    bool readShot(char* r, char* c, istream& in);
};

#endif //BATTLESHIPGAME_CONSOLEPLAYER_H