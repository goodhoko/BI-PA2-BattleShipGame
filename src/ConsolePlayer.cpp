#include "ConsolePlayer.h"

void ConsolePlayer::clear(ostream& out) {
    out << std::string(50, '\n');
}

void ConsolePlayer::placeShip(Ship &s, Board &b) {
    bool success = true;
    do {
        clear(cout);
        b.defencePrint(std::cout);
        std::cout << "Position the ship by entering endpoints for each ship. Ex. Patrol Boat (size 2) \"1A 2A\"\n";
        if (!success)
            std::cout << "Invalid coordinates, please try again. (ex. \"1A 3A\")\n";
        std::cout << s.getName() << " (size: " << unsigned(s.getSize()) << "): ";

        while (cin.get() != '\n');

        char tmpr1, tmpc1, tmpr2, tmpc2;
        if (!readShipPlacement(&tmpr1, &tmpc1, &tmpr2, &tmpc2, cin)) {
            success = false;
            continue;
        }

        uint8_t r1 = numberToCoord(tmpr1);
        uint8_t r2 = numberToCoord(tmpr2);
        uint8_t c1 = letterToCoord(tmpc1);
        uint8_t c2 = letterToCoord(tmpc2);

        if (!b.inBoard(r1, c1) || !b.inBoard(r2, c2) || b.collide(r1, c1, r2, c2) || !s.validCoord(r1, c1, r2, c2)) {
            success = false;
            continue;
        }

        b.addShip(s, r1, c1, r2, c2);
        success = true;

    } while (!success);

    std::cout << "Waiting for the opponent to place a ship" << endl;
}

bool ConsolePlayer::readShipPlacement(char *r1, char *c1, char *r2, char *c2, istream& in) {
    char c;
    string str;

    while (in.get(c) && isdigit(c))
        str.push_back(c);

    *r1 = atoi(str.c_str());

    str.clear();

    if (isalpha(c))
        *c1 = toupper(c);
    else{
        cout << "first" << endl;
        in.putback(c);
        return false;
    }

    in.get(c);
    if (c != ' ') {
        in.putback(c);
        cout << "second" << endl;
        cout << ":" << c << ":" << endl;
        return false;
    }

    while (in.get(c) && isdigit(c))
        str.push_back(c);

    *r2 = atoi(str.c_str());

    if (isalpha(c))
        *c2 = toupper(c);
    else{
        cout << "third" << endl;
        in.putback(c);
        return false;
    }

    return true;
}

Ship *ConsolePlayer::move(Board &attackBoard, Board &myBoard) {
    bool success = true;
    uint8_t r, c;
    do {
        clear(cout);
        std::cout << "       Your board" << std::endl;
        myBoard.defencePrint(std::cout);
        std::cout << "\n";
        std::cout << "     Opponents's board" << std::endl;
        attackBoard.attackPrint(std::cout);
        std::cout << "~~~Legend~~~\nO Ship\n@ Ship with hit\nX Missed hit\n" << endl;
        if (!success)
            std::cout << "Invalid coordinates, please try again (ex. \"4A\")" << std::endl;
        else
            std::cout << "Enter your shot (ex. 6H)" << endl;

        char tmpr, tmpc;
        while (cin.get() != '\n');
        if (!readShot(&tmpr, &tmpc, cin)) {
            success = false;
            continue;
        }
        r = numberToCoord(tmpr);
        c = letterToCoord(tmpc);

        if (!attackBoard.inBoard(r, c)) {
            success = false;
            continue;
        }

        success = true;
    } while (!success);

    std::cout << "Waiting for the opponent's move." << endl;
    return attackBoard.shoot(r, c);
}

uint8_t ConsolePlayer::letterToCoord(char c) {
    return c - 65;
}

uint8_t ConsolePlayer::numberToCoord(char c) {
    return c - 1;
}

bool ConsolePlayer::readShot(char *r, char *c, istream& in) {
    char tmp;
    string str;

    while (in.get(tmp) && isdigit(tmp))
        str.push_back(tmp);

    *r = atoi(str.c_str());

    str.clear();

    if (isalpha(tmp)) {
        *c = toupper(tmp);
        return true;
    }

    in.putback(tmp);
    return false;
}

void ConsolePlayer::win(Board &attackBoard, Board &myBoard) {
    clear(cout);
    std::cout << "       Your board" << std::endl;
    myBoard.defencePrint(std::cout);
    std::cout << "\n";
    std::cout << "     Opponents's board" << std::endl;
    attackBoard.attackPrint(std::cout);
    std::cout << "~~~Legend~~~\nO Ship\n@ Ship with hit\nX Missed hit\n" << endl;
    std::cout << "YOU WON!" << endl;
}

void ConsolePlayer::lose(Board &attackBoard, Board &myBoard) {
    clear(cout);
    std::cout << "       Your board" << std::endl;
    myBoard.defencePrint(std::cout);
    std::cout << "\n";
    std::cout << "     Opponents's board" << std::endl;
    attackBoard.attackPrint(std::cout);
    std::cout << "~~~Legend~~~\nO Ship\n@ Ship with hit\nX Missed hit\n" << endl;
    std::cout << "YOU LOSE!" << endl;
}