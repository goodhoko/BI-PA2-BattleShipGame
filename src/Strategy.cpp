#include "Strategy.h"

void Strategy::reset() {
    firstTry.row = 0;
    firstTry.col = 0;
    lastTry.row = 0;
    lastTry.col = 0;

    left = MAYBE;
    up = MAYBE;
    right = MAYBE;
    down = MAYBE;

    lastDirection = NONE;
    succesful = true;
    valid = false;
}

void Strategy::set(uint8_t r, uint8_t c) {
    firstTry.row = r;
    firstTry.col = c;
    lastTry.row = r;
    lastTry.col = c;

    valid = true;
}

bool Strategy::isValid() {
    return valid;
}

void Strategy::update(uint8_t r, uint8_t c) {
    if (!this->isValid())
        this->set(r, c);
    else {
        succesful = true;
        if (lastDirection == UP || lastDirection == DOWN) {
            left = NOTLIKELY;
            right = NOTLIKELY;
        }
        else {
            up = NOTLIKELY;
            down = NOTLIKELY;
        }
    }
}

bool Strategy::getMove(uint8_t *r, uint8_t *c) {
    if (!succesful) {
        switch (lastDirection) {
            case LEFT:
                left = NOTLIKELY;
                break;
            case UP:
                up = NOTLIKELY;
                break;
            case RIGHT:
                right = NOTLIKELY;
                break;
            case DOWN:
                down = NOTLIKELY;
            case NONE:
                break;
        }
    }

    bool success = false;
    while (!success) {
        if (left == MAYBE) {
            if (lastDirection != LEFT) {
                lastDirection = LEFT;
                lastTry = firstTry;
            }

            if (lastTry.col == 0)
                left = NOCHANCE;
            else {
                --lastTry.col;
                success = true;
            }
        }
        else if (up == MAYBE) {
            if (lastDirection != UP) {
                lastDirection = UP;
                lastTry = firstTry;
            }

            if (lastTry.row == 0)
                up = NOCHANCE;
            else {
                --lastTry.row;
                success = true;
            }
        }
        else if (right == MAYBE) {
            if (lastDirection != RIGHT) {
                lastDirection = RIGHT;
                lastTry = firstTry;
            }

            if (lastTry.col == Board::boardSize - 1)
                right = NOCHANCE;
            else {
                ++lastTry.col;
                success = true;
            }
        }
        else if (down == MAYBE) {
            if (lastDirection != DOWN) {
                lastDirection = DOWN;
                lastTry = firstTry;
            }

            if (lastTry.row == Board::boardSize - 1)
                down = NOCHANCE;
            else {
                ++lastTry.row;
                success = true;
            }
        }
        else {
            this->reset();
            return false;
        }
    }

    *r = lastTry.row;
    *c = lastTry.col;
    succesful = false;

    return true;
}
















