#include "Ship.h"

std::string Ship::getName(void) const {
    return name;
}

uint8_t Ship::getSize(void) const {
    return size;
}

bool Ship::isSunk(void) const {
    return !life;
}

void Ship::hit()
{
    life--;
}

bool Ship::validCoord(uint8_t r1, uint8_t c1, uint8_t r2, uint8_t c2)
{
    if(r1 == r2)
    {
        return size == std::abs(c1 - c2) + 1;
    }

    if(c1 == c2)
    {
        return size == std::abs(r1 - r2) + 1;
    }

    return false;
}












