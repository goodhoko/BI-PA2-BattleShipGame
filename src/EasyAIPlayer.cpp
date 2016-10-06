#include "EasyAIPlayer.h"

Ship *EasyAIPlayer::move(Board &attackBoard, Board &myBoard) {
    uint8_t row, col;
    do {
        getRandomCoord(&row, &col);
    } while (attackBoard.isHit(row, col));

    return attackBoard.shoot(row, col);
}