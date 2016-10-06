#ifndef BATTLESHIPGAME_COORD_H
#define BATTLESHIPGAME_COORD_H

#include <stdint-gcc.h>
/**
 * Class representing pair of coordinates
 */
class Coord {
public:
    /** Construtors */
    Coord(uint8_t r, uint8_t c) : row(r), col(c) { }
    Coord() : row(0), col(0) { }

    /** Variables to hold the coordinates */
    uint8_t row, col;
};

#endif //BATTLESHIPGAME_COORD_H
