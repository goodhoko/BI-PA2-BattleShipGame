#include "BoardTile.h"

bool BoardTile::isHit() const {
    return hit;
}

Ship* BoardTile::isShip() const {
    return ship;
}

void BoardTile::setHit(void) {
    hit = true;
}

void BoardTile::setShip(Ship &s) {
    ship = &s;
}

void BoardTile::defencePrint(std::ostream& out) const {
    int tmp = (isHit() << 1) + (bool) isShip(); //0, 1, 2 or 3

    switch (tmp) {
        case 0:
            out << noShipNoHit;
            break;
        case 1:
            out << shipNoHit;
            break;
        case 2:
            out << noShipHit;
            break;
        case 3: //3
            out << shipHit;
            break;
    }
}

void BoardTile::attackPrint(std::ostream &out) const {
    int tmp = (isHit() << 1) + (bool) isShip(); //0, 1, 2 or 3

    switch (tmp) {
        case 0:
            out << noShipNoHit;
            break;
        case 1:
            out << noShipNoHit;
            break;
        case 2:
            out << noShipHit;
            break;
        case 3:
            out << shipHit;
            break;
    }
}

















