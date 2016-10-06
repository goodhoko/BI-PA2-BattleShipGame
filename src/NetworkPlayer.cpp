#include "NetworkPlayer.h"

/*
 * Following lines include code I didn't wrote. It has been copied from sample which can be found on:
 * https://edux.fit.cvut.cz/courses/BI-PA2/semestralka
 */

bool NetworkPlayer::initiate()
{
    if(!openServer())
        return false;

    struct sockaddr addr;
    socklen_t addrLen = sizeof(addr);
    cout << "waiting for the opponent to connect..." << endl;
    clientSocket = accept(acceptSocket, &addr, &addrLen);

    string message = "Connected!\nWaiting for the opponent.\n";
    send(clientSocket, message.c_str(), message.size(), 0);

    cout << "Connected!" << endl;


    return true;
}

bool NetworkPlayer::openServer() {

    struct addrinfo* ai;

    if(getaddrinfo(SRV_NAME, SRV_PORT, NULL, &ai) != 0) {
        cout << "addr";
        return false;
    }

    acceptSocket = socket(ai->ai_family, SOCK_STREAM, 0);
    if(acceptSocket == -1){
        freeaddrinfo(ai);
        cout << "socket";
        return false;
    }

    if(bind(acceptSocket, ai->ai_addr, ai->ai_addrlen) != 0){
        close(acceptSocket);
        freeaddrinfo(ai);
        cout << "bind";
        return false;
    }

    if(listen(acceptSocket, 5) != 0){
        close(acceptSocket);
        freeaddrinfo(ai);
        cout << "listen";
        return false;
    }

    freeaddrinfo(ai);
    return true;
}

void NetworkPlayer::placeShip(Ship &s, Board &b) {
    bool success = true;
    do {
        ostringstream ostream;

        clear(ostream);
        b.defencePrint(ostream);
        ostream << "Position the ship by entering endpoints for each ship. Ex. Patrol Boat (size 2) \"1A 2A\"\n";
        if (!success)
            ostream << "Invalid coordinates, please try again. (ex. \"1A 3A\")\n";
        ostream << s.getName() << " (size: " << unsigned(s.getSize()) << "): ";

        string sendBuffer = ostream.str();
        send(clientSocket, sendBuffer.c_str(), sendBuffer.size(), 0);

        char recvBuffer[100];
        int l = recv(clientSocket, recvBuffer, sizeof(recvBuffer), 0);
        cout << recvBuffer << endl;

        if(l <= 0){
            success = false;
            continue;
        }

        istringstream istream(string(recvBuffer, l + 1));

        //while (istream.get() != '\n');

        char tmpr1, tmpc1, tmpr2, tmpc2;
        if (!readShipPlacement(&tmpr1, &tmpc1, &tmpr2, &tmpc2, istream)) {
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

    string message = "Waiting for the opponent.\n";
    send(clientSocket, message.c_str(), message.size(), 0);
}

Ship *NetworkPlayer::move(Board &attackBoard, Board &myBoard) {
    bool success = true;
    uint8_t r, c;
    do {
        ostringstream ostream;

        clear(ostream);
        ostream << "       Your board" << std::endl;
        myBoard.defencePrint(ostream);
        ostream << "\n";
        ostream << "     Opponents's board" << std::endl;
        attackBoard.attackPrint(ostream);
        ostream << "~~~Legend~~~\nO Ship\n@ Ship with hit\nX Missed hit\n" << endl;
        if (!success)
            ostream << "Invalid coordinates, please try again (ex. \"4A\")" << std::endl;
        else
            ostream << "Enter your shot (ex. 6H)" << endl;

        string sendBuffer = ostream.str();
        send(clientSocket, sendBuffer.c_str(), sendBuffer.size(), 0);

        char recvBuffer[100];
        int l = recv(clientSocket, recvBuffer, sizeof(recvBuffer), 0);

        if(l <= 0){
            success = false;
            continue;
        }

        istringstream istream(string(recvBuffer, l + 1));

        char tmpr, tmpc;
        //while (istream.get() != '\n');
        if (!readShot(&tmpr, &tmpc, istream)) {
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

    string message = "Waiting for the opponent.\n";
    send(clientSocket, message.c_str(), message.size(), 0);
    return attackBoard.shoot(r, c);
}

void NetworkPlayer::win(Board &attackBoard, Board &myBoard) {
    ostringstream stream;

    clear(stream);
    stream << "       Your board" << endl;
    myBoard.defencePrint(stream);
    stream << "\n";
    stream << "     Opponents's board" << endl;
    attackBoard.attackPrint(stream);
    stream << "~~~Legend~~~\nO Ship\n@ Ship with hit\nX Missed hit\n" << endl;
    stream << "YOU WON!" << endl;

    string sendBuffer = stream.str();
    send(clientSocket, sendBuffer.c_str(), sendBuffer.size(), 0);
}

void NetworkPlayer::lose(Board &attackBoard, Board &myBoard) {
    ostringstream stream;

    clear(stream);
    stream << "       Your board" << endl;
    myBoard.defencePrint(stream);
    stream << "\n";
    stream << "     Opponents's board" << endl;
    attackBoard.attackPrint(stream);
    stream << "~~~Legend~~~\nO Ship\n@ Ship with hit\nX Missed hit\n" << endl;
    stream << "YOU LOSE!" << endl;

    string sendBuffer = stream.str();
    send(clientSocket, sendBuffer.c_str(), sendBuffer.size(), 0);
}











