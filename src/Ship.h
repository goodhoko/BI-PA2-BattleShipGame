#ifndef BATTLESHIPGAME_SHIP_H
#define BATTLESHIPGAME_SHIP_H

#include <string>
#include <vector>

/**
 * Class representing ships. Ship has size and life which on construction is same as the life. With each hit it decreases. When life == 0 ship is sunk.
 */
class Ship {
public:
    /** constructor */
    Ship(const char* n, uint8_t s) : life(s), size(s), name(n) { }

    /** Getter for name*/
    std::string getName() const;
    /** Getter for size*/
    uint8_t getSize() const;
    /** Return true if ship is sunk ~ it's life is 0 */
    bool isSunk() const;
    /** decreases life by one */
    void hit();
    /** checks if pair of endpoint coordinates fits ship's size */
    bool validCoord(uint8_t r1, uint8_t c1, uint8_t r2, uint8_t c2);

private:
    /** life of the ship */
    uint8_t life;
    /** size of the ship */
    uint8_t size;
    /** name of the ship */
    std::string name;
};

#endif //BATTLESHIPGAME_SHIP_H