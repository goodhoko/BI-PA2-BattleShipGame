#ifndef BATTLESHIPGAME_NETWORKPLAYER_H
#define BATTLESHIPGAME_NETWORKPLAYER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <sstream>

#include "Player.h"
#include "ConsolePlayer.h"

/** server name / address */
const char* const SRV_NAME = "localhost";
/** port */
const char* const SRV_PORT = "2666";

/**
 * Class for player locally representing client at the other side of the network.
 */
class NetworkPlayer : public ConsolePlayer{
public:

    /** constructor */
    NetworkPlayer() : ConsolePlayer("opponent"), clientSocket(0), acceptSocket(0) { }

    /** Opens server and waits till the client connects. */
    bool initiate();
    /**Technically the same as Console Player implementation but communicates over network rather than directly thru terminal */
    Ship *move(Board &attackBoard, Board &myBoard);
    /**Technically the same as Console Player implementation but communicates over network rather than directly thru terminal */
    void placeShip(Ship& s, Board& b);
    /** Send message about winning to the client. */
    void win(Board& attackBoard, Board& myBoard);
    /** Send message about losing to the client.*/
    void lose(Board& attackBoard, Board& myBoard);

private:
    /**opens connection and saves the socket to accept socket */
    bool openServer();

    /** variable to hold socket for communication with client */
    int clientSocket;
    /** variable to hold socket for accepting client connection*/
    int acceptSocket;
};

#endif //BATTLESHIPGAME_NETWORKPLAYER_H
