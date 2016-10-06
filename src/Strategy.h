#ifndef BATTLESHIPGAME_STRATEGY_H
#define BATTLESHIPGAME_STRATEGY_H

#include "Coord.h"
#include "Board.h"

/**
 * Class that maintain strateg logic for the CleverAIPlayer
 */
class Strategy {
public:
    /** enum of probabilities */
    typedef enum {NOCHANCE, NOTLIKELY, MAYBE, LIKELY} Chance;
    /** enum of directions */
    typedef enum {NONE, LEFT, UP, RIGHT, DOWN} Direction;

    /** constructor */
    Strategy() : left(MAYBE), up(MAYBE), right(MAYBE), down(MAYBE), lastDirection(NONE), succesful(true), valid(false) { }

    /*returns true if there's any apriory knowledge to use and therefore makes sense to use the strategy logic */
    bool isValid();
    /** Is called if shooting to coordinates passed as arguments has been successful ~ a ship has been hit */
    void update(uint8_t r, uint8_t c);
    /** promts strategy to come up with next best move */
    bool getMove(uint8_t* r, uint8_t* c);

private:
    /** resets the strategy to it's original state. It's called after ship has been sunk. */
    void reset();
    /** if ship is hit for the first time this method sets the strategy to search around it */
    void set(uint8_t r, uint8_t c);

    /** variables to hold probabilities for each direction from last move */
    Chance left, up, right, down;
    /** variable to hold last direction the shooting moved in */
    Direction lastDirection;
    /** bool to hold wheter the last move was successful and if there asi any apriori knowledge to use and therefore makes sense to use the strategy logic */
    bool succesful, valid;
    /** variables to hold coordinates of the last move an move when the ship was hit for the first time */
    Coord firstTry, lastTry;
};

#endif //BATTLESHIPGAME_STRATEGY_H