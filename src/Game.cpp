#include "Game.h"

void Game::placeShips() {
    for (vector<Ship>::iterator it = fleet.begin(); it != fleet.end(); ++it) {
        player1.placeShip(*it, p1Board);
        player2.placeShip(*it, p2Board);
    }
}

void Game::endGame() {
    gameO = true;
}

bool Game::gameOver() const {
    return gameO;
}

void Game::gameUpdate() {

    player1.move(p2Board, p1Board);
    if (p2Board.fleetSunk()) {
        player1.win(p2Board, p1Board);
        player2.lose(p1Board, p2Board);
        this->endGame();
        return;
    }

    player2.move(p1Board, p2Board);
    if (p1Board.fleetSunk()) {
        player2.win(p1Board, p2Board);
        player1.lose(p2Board, p1Board);
        this->endGame();
        return;
    }
}







