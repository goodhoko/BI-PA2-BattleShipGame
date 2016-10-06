#include "GeniusAIPlayer.h"

Ship *GeniusAIPlayer::move(Board &attackBoard, Board &myBoard) {
    for (uint8_t i = 0; i < Board::boardSize; ++i) {
        for (uint8_t j = 0; j < Board::boardSize; ++j) {
            if (attackBoard.collide(i, j, i, j) && !attackBoard.isHit(i, j))
                return attackBoard.shoot(i, j);
        }
    }

    return nullptr;
}

