#ifndef BATTLESHIPGAME_BOARDTILE_H
#define BATTLESHIPGAME_BOARDTILE_H

#include <iostream>

#include "Ship.h"

using namespace std;

string const shipNoHit = "O|";
string const shipHit = "@|";
string const noShipNoHit = " |";
string const noShipHit = "X|";

/**
 * Class representing one tile of the game board. It holds information whether it has been hit and whether it holds a ship.
 */
class BoardTile
{
public:
    /** Constructor */
    BoardTile(uint8_t r, uint8_t c) : row(r), col(c), hit(false), ship(NULL) { }

    /** returns true if the tile has been hit */
    bool isHit() const;
    /** return pointer to to ship the tile holds. If it doesn't hold any ship, returns null */
    Ship* isShip() const;
    /** setter for hit */
    void setHit(void);
    /** setter for the ship pointer */
    void setShip(Ship& s);
    /** tile prints itself as it should appear to it's owner to the outstream */
    void defencePrint(std::ostream& out) const;
    /** tile prints itself as it should appear to oppoent of ti's owner to the outstream */
    void attackPrint(std::ostream& out) const;

private:
    /** coordinates of the tile */
    uint8_t  row, col;
    /** variable to hold if the tile is hit or not */
    bool hit;
    /** pointer to ship the tile holds. Null if it doesn't hold any ship */
    Ship* ship;
};

#endif //BATTLESHIPGAME_BOARDTILE_H
