#include <iostream>
#include <ctime>

using namespace std;

class Player {
private:
    string _name;
    int _points;
    bool _elminated;
    int currentTossValue;
public:

    Player(string name, int points) {
        // initializing the random seed
        srand((unsigned) time(nullptr));
        this->_name = name;
        this->_points = points;
        _elminated = true;
        currentTossValue = -1;
    }

    // getters
    int getPoints() const {
        return _points;
    }

    void setPoints(int newPoint) {
        _points = newPoint;
        // if points become less than 1 then set _elminated to false
        if (_points < 1) {
            _elminated = false;
        }
    }

    void tossCoin() {
        // generate a random value between 0 and 1
        // if 0 then heads else tails
        currentTossValue = rand() % 2;
    }

    // get the current toss
    int getCurrentTossValue() const {
        return currentTossValue;
    }

    // check if the player is playing the game
    bool isPlayingGame() const {
        return _elminated;
    }

    // get the name of the player
    string getName() {
        return _name;
    }
};

int getTotalPlayersPlaying(Player *playerList, int totalPlayers) {
    // gets the total number of players playing the game
    int count = 0;
    for (int i = 0; i < totalPlayers; ++i) {
        // if the current player is playing the game then, add 1 to count
        if (playerList[i].isPlayingGame())
            count += 1;
    }
    // return total number of players playing the game
    return count;
}

int tossCoin(Player *playerList, int totalPlayers) {
    int totalCoinsTossed = 0;
    cout << "Outcome of the toss: ";
    for (int i = 0; i < totalPlayers; ++i) {
        if (playerList[i].isPlayingGame()) {
            playerList[i].tossCoin();
            totalCoinsTossed += 1;
            if (playerList[i].getCurrentTossValue() == 1) {
                cout << "Tail ";
            } else {
                cout << "Head ";
            }
        }
    }
    cout << endl;
    return totalCoinsTossed;
}

int getCurrentWinningCoinFace(Player *playerList, int totalPlayers) {
    // heads is denoted by 0 and tails is denoted by 1
    int countHeads = 0, countTails = 0;
    for (int i = 0; i < totalPlayers; ++i) {
        if (playerList[i].isPlayingGame()) {
            if (playerList[i].getCurrentTossValue() == 0)
                countHeads += 1;
            else if (playerList[i].getCurrentTossValue() == 1)
                countTails += 1;
        }
    }
    if (countHeads > countTails)
        return 0;
    else if (countHeads < countTails)
        return 1;
    else
        return -1;
}

void generatePoints(Player *playerList, int totalPlayers, int winningCoinFace, int pointChange) {
    // winningCoinface = 0 for heads 1 for tails
    for (int i = 0; i < totalPlayers; ++i) {
        if (playerList[i].isPlayingGame()) {
            // if the player's toss is same as the winning coin face, then add pointchange
            if (playerList[i].getCurrentTossValue() == winningCoinFace)
                playerList[i].setPoints(playerList[i].getPoints() + pointChange);
            else {
                // else subtract pointchange
                playerList[i].setPoints(playerList[i].getPoints() - pointChange);
            }
        }
    }
}

void printResults(Player *playerList, int totalPlayers) {
    for (int i = 0; i < totalPlayers; ++i) {
        if (playerList[i].isPlayingGame()) {
            cout << "Player Name: " << playerList[i].getName() << endl;
            cout << "Player Points: " << playerList[i].getPoints() << endl;
            cout << "--------------------------------\n";
        }
    }
}

void getWinners(Player *playerList, int totalPlayers) {
    int maxPoints = INT16_MIN;
    for (int i = 0; i < totalPlayers; ++i) {
        if (playerList[i].isPlayingGame()) {
            if (playerList[i].getPoints() > maxPoints) {
                maxPoints = playerList[i].getPoints();
            }
        }
    }

    cout << "Winners are: \n";
    for (int i = 0; i < totalPlayers; ++i) {
        if (playerList[i].getPoints() == maxPoints) {
            cout << playerList[i].getName() << " with " << maxPoints << " points." << endl;
        }
    }
}


int main() {
    int minimumPlayers = 2;
    int totalPlayers = 5;
    int P = 1;
    int totalCoinTosses = 0;
    int initialPoints = 1;
    int currentRound = 1;
    int maxRounds = 100;

    string values[2] = {"Heads", "Tails"};

    Player playerList[5] = {
            Player("Adam", initialPoints),
            Player("Jane", initialPoints),
            Player("Eva", initialPoints),
            Player("Sylvia", initialPoints),
            Player("Sam", initialPoints)
    };

    // printing out the initial players
    cout << "Players with initial points: \n";
    printResults(playerList, totalPlayers);
    cout << "\n\n";

    while (getTotalPlayersPlaying(playerList, totalPlayers) > minimumPlayers && currentRound <= maxRounds) {
        // toss the coins
        totalCoinTosses += tossCoin(playerList, totalPlayers);
        int winningCoin = getCurrentWinningCoinFace(playerList, totalPlayers);
        if (winningCoin == -1) {
            // it was a tie, so no change
            cout << "It was a tie, so no points will be added or deducted from the players\n";
        } else {
            cout << "The winning coin face was: " << values[winningCoin] << endl;
            generatePoints(playerList, totalPlayers, winningCoin, P);
        }
        // printing out the results
        cout << "Results of round " << currentRound << endl;
        printResults(playerList, totalPlayers);

        P += 1;
        currentRound += 1;
        cout << "\n===============================\n\n";
    }

    // getting the winners
    cout << "Total coins tossed: " << totalCoinTosses << endl;
    cout << "Total rounds played: " << currentRound << endl;
    cout << "Final value of P: " << P << endl;
    getWinners(playerList, totalPlayers);
	
		system("pause");
	return 0;
}