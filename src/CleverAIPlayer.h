#ifndef BATTLESHIPGAME_CLEVERAIPLAYER_H
#define BATTLESHIPGAME_CLEVERAIPLAYER_H

#include <list>

#include "AIPlayer.h"
#include "Coord.h"
#include "Strategy.h"

/**
 * AI version which tries to imitate human level skills. It shoots randomly until it hits ship. When it does, it starts to shoot around to figure out ship's orientation.
 */
class CleverAIPlayer : public AIPlayer {
public:
    /**constructor */
    CleverAIPlayer();

    /**destructor */
    ~CleverAIPlayer() { }

    /** implementation of the move
     * if possible it uses apriori knowledge */
    Ship *move(Board &attackBoard, Board &myBoard);

private:
    /** list of coordinates which are yet to be shoot at */
    list<Coord> coord;
    /** instance of the strategy class */
    Strategy strategy;
};

#endif //BATTLESHIPGAME_CLEVERAIPLAYER_H