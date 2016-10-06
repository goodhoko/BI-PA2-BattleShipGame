#ifndef BATTLESHIPGAME_AIEASYPLAYER_H
#define BATTLESHIPGAME_AIEASYPLAYER_H

#include "Player.h"

/**
 * Abstract class for 'artificial intelligence' player
 */
class AIPlayer : public Player {
public:
    /** constructor */
    AIPlayer() : Player("Computer") { }

    /** Place ship just randomly in the board */
    void placeShip(Ship& s, Board& b);
    /** Does actually nothing */
    void win(Board& attackBoard, Board& myBoard);
    /** Does actually nothing */
    void lose(Board& attackBoard, Board& myBoard);

protected:
    /**generates set of random coordinates */
    void getRandomCoord(uint8_t* r, uint8_t* c);
};

#endif //BATTLESHIPGAME_AIEASYPLAYER_H