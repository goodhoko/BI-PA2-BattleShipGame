#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <sstream>
#include <iostream>

using namespace std;

const char* const SRV_PORTC = "2666";

/*
 * Following lines include code I didn't wrote. It has been copied from sample which can be found on:
 * https://edux.fit.cvut.cz/courses/BI-PA2/semestralka
 */


/**
 * opens connection with the server
 */
int openClient(const char* srvAddr){

    struct addrinfo* ai;

    if(getaddrinfo(srvAddr, SRV_PORTC, NULL, &ai) != 0){
        return -1;
    }

    int s = socket(ai->ai_family, SOCK_STREAM, 0);
    if(s == -1){
        freeaddrinfo(ai);
        return -1;
    }

    if(connect(s, ai->ai_addr, ai->ai_addrlen) != 0){
        close(s);
        freeaddrinfo(ai);
        return -1;
    }

    freeaddrinfo(ai);

    return s;
}

/**
 * obtains server adress from the user
 */
const char* getAddr() {
    cout << "Please enter address of the server-side player." << endl;
    string tmp;

    cin >> tmp;

    return tmp.c_str();
}

/**
 * displays received data and sends back data loaded from terminal
 */
void communicate(int s){

    while(true){
        fd_set rd;
        FD_ZERO(&rd);
        FD_SET(s, &rd);
        FD_SET(STDIN_FILENO, &rd);

        select(s + 1, &rd, NULL, NULL, NULL);

        if(FD_ISSET(s, &rd)){
            char buffer[1024];
            int l = recv(s, buffer, sizeof(buffer) - 1, 0);
            if(l <= 0) break;
            write(STDOUT_FILENO, buffer, l);
        }

        if(FD_ISSET(STDIN_FILENO, &rd)){
            char buffer[100];
            int l = read(STDIN_FILENO, buffer, sizeof(buffer));
            send(s, buffer, l, 0);
        }
    }
}

int client(){
    cout << "          BATTLESHIP GAME          \n";
    cout << "           by Jan Koutny           \n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << endl;

    int s = openClient(getAddr());
    if(s == -1){
        cout << "Can't open connection due to unkown error" << endl;
        return 1;
    }

    communicate(s);
    close(s);

    return 0;
}

