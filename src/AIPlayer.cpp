#include "AIPlayer.h"

void AIPlayer::placeShip(Ship &s, Board& b) {
    b.addShipRandom(s);
}

void AIPlayer::win(Board &attackBoard, Board &myBoard) { }

void AIPlayer::lose(Board &attackBoard, Board &myBoard) { }

void AIPlayer::getRandomCoord(uint8_t *r, uint8_t *c) {
    *r = rand() % Board::boardSize;
    *c = rand() % Board::boardSize;
}