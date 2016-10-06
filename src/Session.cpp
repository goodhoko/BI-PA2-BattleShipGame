#include "Session.h"

using namespace std;

void Session::play() {
    ConsolePlayer::clear(cout);
    if (!loadShips()) {
        cout << "Error loading ships" << endl;
        return;
    }

    Game game(*player1, *player2, fleet);
    game.placeShips();

    while (!game.gameOver()) {
        game.gameUpdate();
    }
}

bool Session::loadShips() {
    ifstream file;
    file.open("ships.txt");
    if (!file.is_open())
        return false;

    string line;
    getline(file, line); //removing the <size> <name> line

    while (getline(file, line)) {
        stringstream stream(line);
        int size;
        string name;
        stream >> size;
        if(stream.get() != ' ')
            return false;
        getline(stream, name);

        fleet.push_back(Ship(name.c_str(), size));
        if (stream.bad())
            return false;
    }

    if (!cin.good())
        return false;

    return true;
}

Session::~Session() {
    delete(player1);
    delete(player2);
}

bool Session::initiate() {
    player1 = new ConsolePlayer("human");

    int option;
    ConsolePlayer::clear(cout);
    cout << "          BATTLESHIP GAME          \n";
    cout << "           by Jan Koutny           \n";
    cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n" << endl;
    cout << "Please select game mode." << endl;

    bool success = true;
    do {
        if (!success) {
            ConsolePlayer::clear(cout);
            cout << "Invalid option please try again." << endl;
        }

        cout << "1) Play vs dumb AI\n2) Play vs clever AI\n3) Play vs (unfairly) genius AI\n4) Play over network" << endl;
        if (!(cin >> option)) {
            cin.clear();
            cin.ignore(100, '\n');
            success = false;
            continue;
        }

        switch (option) {
            case 1:
                player2 = new EasyAIPlayer();
                success = true;
                break;
            case 2:
                player2 = new CleverAIPlayer();
                success = true;
                break;
            case 3:
                player2 = new GeniusAIPlayer();
                success = true;
                break;
            case 4: {
                NetworkPlayer *tmp = new NetworkPlayer();
                if (!tmp->initiate()) {
                    cout << "Can't open connection due to unknown error." << endl;
                    return false;
                }
                player2 = tmp;
                success = true;
            }
                break;
            default:
                success = false;
                continue;
        }
    } while (!success);

    return true;
}



