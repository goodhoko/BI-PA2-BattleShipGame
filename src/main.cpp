#include "Session.h"
#include "Client.h"

/**
 * @mainpage
 *
 * BattleShip Game
 * by Jan Koutny
 *
 * Classic guessing game for two players. You can either play against one of three versions of AI or against other human over network. (He must use the separate client program.)
 */

int main(int argc, char* argv[]) {

    if(argc < 2) {
        Session session;
        if (!session.initiate())
            return 1;

        session.play();
    }
    else if(string(argv[1]) == "-c")
        client();
    else{
        cout << "usage:\nno arguments: play vs AI or create server\n -c connect to a server player and play as a client" << endl;
        return 1;
    }

    return 0;
}