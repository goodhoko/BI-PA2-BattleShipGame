#include "Board.h"

using namespace std;

Board::Board() {
    for (uint8_t row = 0; row < boardSize; ++row) {
        for (uint8_t col = 0; col < boardSize; ++col) {
            board.push_back(BoardTile(row, col));
        }
    }

    fleet.reserve(boardSize * boardSize);
}

void Board::addShip(Ship &s, uint8_t r1, uint8_t c1, uint8_t r2, uint8_t c2) {
    fleet.push_back(s);

    if (r1 == r2) {
        if (c2 > c1) {
            for (; c1 <= c2; ++c1) {
                board[vectorIndex(r1, c1)].setShip(fleet.back());
            }
        }
        else {
            for (; c2 <= c1; ++c2) {
                board[vectorIndex(r1, c2)].setShip(fleet.back());
            }
        }
    }
    else {
        if (r2 > r1) {
            for (; r1 <= r2; ++r1) {
                board[vectorIndex(r1, c1)].setShip(fleet.back());
            }
        }
        else {
            for (; r2 <= r1; ++r2) {
                board[vectorIndex(r2, c1)].setShip(fleet.back());
            }
        }
    }
}

uint8_t Board::vectorIndex(uint8_t r, uint8_t c) const {
    return boardSize * r + c;
}

void Board::addShipRandom(Ship &s) {
    bool success = false;
    while (!success) {
        uint8_t row1 = rand() % boardSize;
        uint8_t col1 = rand() % boardSize;
        uint8_t row2, col2;

        uint8_t dirSeed = rand() % 4;
        uint8_t i = 0;

        while (i < 4 && !success) {
            uint8_t direction = (dirSeed + i) % 4;
            switch (direction) {
                case 0: //up
                    row2 = row1 - s.getSize() + 1;
                    col2 = col1;
                    break;
                case 1: //right
                    row2 = row1;
                    col2 = col1 + s.getSize() - 1;
                    break;
                case 2: // down
                    row2 = row1 + s.getSize() - 1;
                    col2 = col1;
                default: //case 3, left
                    row2 = row1;
                    col2 = col1 - s.getSize() + 1;
                    break;
            }
            i++;
            if (!inBoard(row2, col2) || this->collide(row1, col1, row2, col2))
                continue;

            this->addShip(s, row1, col1, row2, col2);
            success = true;
        }
    }
}

bool Board::collide(uint8_t r1, uint8_t c1, uint8_t r2, uint8_t c2) const {
    if (r1 == r2) {
        if (c2 > c1) {
            for (; c1 <= c2; ++c1) {
                if (board[vectorIndex(r1, c1)].isShip())
                    return true;
            }
        }
        else {
            for (; c2 <= c1; ++c2) {
                if (board[vectorIndex(r1, c2)].isShip())
                    return true;
            }
        }
    }
    else {
        if (r2 > r1) {
            for (; r1 <= r2; ++r1) {
                if (board[vectorIndex(r1, c1)].isShip())
                    return true;
            }
        }
        else {
            for (; r2 <= r1; ++r2) {
                if (board[vectorIndex(r2, c1)].isShip())
                    return true;
            }
        }
    }
    return false;
}

bool Board::fleetSunk() const {
    for (std::vector<Ship>::const_iterator it = fleet.begin(); it != fleet.end(); ++it) {
        if (!it->isSunk()) {
            return false;
        }
    }
    return true;
}

Ship *Board::shoot(uint8_t r, uint8_t c) {
    BoardTile &tile = board[vectorIndex(r, c)];

    if (tile.isShip()) {
        if (!tile.isHit()) {
            tile.setHit();
            tile.isShip()->hit();
            return tile.isShip();
        }
        return NULL;
    }

    tile.setHit();
    return NULL;
}

bool Board::inBoard(uint8_t r, uint8_t c) const {
    return !(r < 0 || r > boardSize - 1 || c < 0 || c > boardSize - 1);
}

bool Board::isHit(uint8_t r, uint8_t c) {
    return board[vectorIndex(r, c)].isHit();
}

void Board::defencePrint(ostream& out) {
    char c = 'A';

    out << "  |";
    for (char i = 0; i < boardSize; ++i) {
        out << c << "|";
        c++;
    }
    out << "\n";

    for (uint8_t i = 0; i < boardSize; ++i) {
        if(i < 9)
            out << " ";
        out << unsigned(i + 1) << "|";
        for (uint8_t j = 0; j < boardSize; ++j) {
            board[vectorIndex(i, j)].defencePrint(out);
        }
        out << "\n";
    }
}

void Board::attackPrint(std::ostream &out) {
    char c = 'A';

    out << "  |";
    for (char i = 0; i < boardSize; ++i) {
        out << c << "|";
        c++;
    }
    out << "\n";

    for (uint8_t i = 0; i < boardSize; ++i) {
        if(i < 9)
            out << " ";
        out << unsigned(i + 1) << "|";
        for (uint8_t j = 0; j < boardSize; ++j) {
            board[vectorIndex(i, j)].attackPrint(out);
        }
        out << "\n";
    }
}