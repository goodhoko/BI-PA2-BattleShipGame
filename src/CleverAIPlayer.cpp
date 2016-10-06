#include "CleverAIPlayer.h"

Ship *CleverAIPlayer::move(Board &attackBoard, Board &myBoard)
{
    bool success = false;
    uint8_t r = 0;
    uint8_t c = 0;
    while(strategy.isValid() && !success){
        strategy.getMove(&r, &c);
        for (list<Coord>::iterator it = coord.begin(); it != coord.end() ; ++it) {
            if(r == it->row && c == it->col) {
                success = true;
                coord.erase(it);
                break;
            }
        }
    }

    Ship* tmp;

    if(success){
        tmp = attackBoard.shoot(r, c);
        if(tmp)
            strategy.update(r, c);
    }
    else{
        list<Coord>::iterator it = coord.begin();
        int count = rand() % coord.size();
        while(count--)
            it++;

        r = it->row;
        c = it->col;
        tmp = attackBoard.shoot(r, c);
        coord.erase(it);
        if(tmp)
            strategy.update(r, c);
    }

    return tmp;
}

CleverAIPlayer::CleverAIPlayer() {
    for (uint8_t i = 0; i < Board::boardSize; ++i)
    {
        for (uint8_t j = 0; j < Board::boardSize; ++j) {
            coord.push_back(Coord(i, j));
        }
    }
}

