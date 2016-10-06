#ifndef BATTLESHIPGAME_GENIUSAIPLAYER_H
#define BATTLESHIPGAME_GENIUSAIPLAYER_H

#include "AIPlayer.h"

/**
 * AI version which cheats to sunk all your ships as fast as possible
 */
class GeniusAIPlayer : public AIPlayer {
public:
    /** destructor */
    ~GeniusAIPlayer() { }

    /** implementation of the move - it iterates thru the board until it find tile with ship that hasn't been hit yet and then shoots at it */
    Ship* move(Board& attackBoard, Board& myBoard);
};

#endif //BATTLESHIPGAME_GENIUSAIPLAYER_H