#ifndef BATTLESHIPGAME_BOARD_H
#define BATTLESHIPGAME_BOARD_H

#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Ship.h"
#include "BoardTile.h"

/**
 * Class for representing board for one player.
 */
class Board {
public:
    /** length of the edge. (Board is always square shaped) */
    static uint8_t const boardSize = 10;

    /** constructor */
    Board();

    /** Add ship to the fleet vector, and to tiles between pair of coordinates passed as arguments
     * correctness of the coordinates must be checked ouside of this method*/
    void addShip(Ship& s, uint8_t r1, uint8_t c1, uint8_t r2, uint8_t c2);
    /** Add ship to random place in board */
    void addShipRandom(Ship& s);
    /** Return true if there's a ship between pair of coordinates passed as arguments */
    bool collide(uint8_t r1, uint8_t c1, uint8_t r2, uint8_t c2) const;
    /** returns true if all the ships are sunk */
    bool fleetSunk() const;
    /** Method to shoot at given coordinates. @return pointer to ship that was hit or NULL otherwise */
    Ship* shoot(uint8_t r, uint8_t c);
    /** Check if given cordinates are within the board */
    bool inBoard(uint8_t r, uint8_t c) const;
    /**returns true if tile at the coordinates is hit */
    bool isHit(uint8_t r, uint8_t c);
    /** Prints itself to given ostream as it should appear to board"s owner */
    void defencePrint(std::ostream& out);
    /** Prints itself to given ostream as it should appear to board"s owner's opponent */
    void attackPrint(std::ostream& out);

private:
    /** container for the ships */
    std::vector<Ship> fleet;
    /** container for the board tiles */
    std::vector<BoardTile> board;
    /** returns position in the board vector for given coordinates */
    uint8_t vectorIndex(uint8_t r, uint8_t c) const;
};

#endif //BATTLESHIPGAME_BOARD_H
