#ifndef BATTLESHIPGAME_EASYAIPLAYER_H
#define BATTLESHIPGAME_EASYAIPLAYER_H

#include "AIPlayer.h"

/**
 * Very very dumb version of computer player - it only shoots randomly at tiles that haven't been yet hit
 */
class EasyAIPlayer : public AIPlayer {
    /** destructor */
    ~EasyAIPlayer() { }

    /** implementation of the move */
    Ship* move(Board& attackBoard, Board& myBoard);
};

#endif //BATTLESHIPGAME_EASYAIPLAYER_H