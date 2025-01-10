
#include <algorithm>
#include "MatamStory.h"

#include "Utilities.h"



void MatamStory::eventsStreamReader(std::istream& eventsStream) {
    string event;
    std::vector<shared_ptr<Event>> pack_events;

}


MatamStory::MatamStory(std::istream& eventsStream, std::istream& playersStream) {

    eventsStreamReader(eventsStream);

    if (events.size() < 2) {
        throw EventException();
    }

    /*===== TODO: Open and read events file =====*/
    eventsStreamReader(eventsStream);
    /*==========================================*/
    /*===== TODO: Open and Read players file =====*/
    readPlayers(playersStream);
    //we check 2<=players<=6 in the readPlayers function
    /*============================================*/

    this->m_turnIndex = 1;
    this->m_roundIndex = 0;

}

void MatamStory::playTurn(Player& player) {

    /**
     * Steps to implement (there may be more, depending on your design):
     * 1. Get the next event from the events list
     * 2. Print the turn details with "printTurnDetails"
     * 3. Play the event
     * 4. Print the turn outcome with "printTurnOutcome"
    */


}



void MatamStory::playRound() {

    int players_num = players.size();
    printRoundStart();

    /*===== TODO: Play a turn for each player =====*/

    for (int i = 0; i < players_num; i++) {
        Player *current_player = players[i].get();
        if (!(*current_player).isDead()) {
            {
                playTurn(*current_player);
            }
        }

        /*=============================================*/


        printRoundEnd();

        printLeaderBoardMessage();
        sortPlayers(players);


        /*===== TODO: Print leaderboard entry for each player using "printLeaderBoardEntry" =====*/
        for (int j = 0; j < players_num; j++) {
            printLeaderBoardEntry(i + 1, *players[j]);
        }
        /*=======================================================================================*/

        printBarrier();
    }
}

bool winner(const vector<std::unique_ptr<Player>>& players) {
    for (const auto& player : players) {
        if (player->getLevel() == 10) {
            return true;
        }
    }
    return false;
}
bool allDead(const vector<std::unique_ptr<Player>>& players) {
    for (const auto& player : players) {
        if (!player->isDead()) {
            return false;
        }
    }
    return true;
}


    bool MatamStory::isGameOver() const {
        /*===== TODO: Implement the game over condition =====*/
        if (winner(players) || allDead(players)) {
            return true;
        }

        return false; // Replace this line
        /*===================================================*/
    }

    void MatamStory::play() {
        printStartMessage();
        /*===== TODO: Print start message entry for each player using "printStartPlayerEntry" =====*/
        for (int i = 0; i < players.size(); i++) {
            printStartPlayerEntry(i + 1, *players[i]);
        }
        /*=========================================================================================*/
        printBarrier();

        while (!isGameOver()) {

            playRound();
        }

        printGameOver();
        /*===== TODO: Print either a "winner" message or "no winner" message =====*/
        if (winner(players)) {
            //sort the players by the rules and take the first one (use sort that i made)
            sort(players.begin(), players.end(), comparingPlayers);
            printWinner(*players[0]);
        }
        if(allDead(players)) {
            printNoWinners();
        }
        /*========================================================================*/
    }

    vector<std::shared_ptr<Encounter>> MatamStory::readFromPack(istream &eventsStream, int size) {
        //get the events from the stream that are inside the pack, note pack can has packs too so check if the event is pack
        vector<shared_ptr<Encounter>> pack_events;
        for (int i = 0; i < size; i++) {
            string event;
            eventsStream >> event;
            if (event == "Snail") {
                pack_events.push_back(std::make_shared<Snail>());
            } else if (event == "Slime") {
                pack_events.push_back(std::make_shared<Slime>());
            } else if (event == "Barlog") {
                pack_events.push_back(std::make_shared<Barlog>());
            } else if (event == "Pack") {
                int num_of_events;
                eventsStream >> num_of_events;
                if (num_of_events < 2) {
                    throw std::invalid_argument("Pack must be at least 2");
                }
                vector<shared_ptr<Encounter>> Pack_loop = readFromPack(eventsStream, num_of_events);
                pack_events.push_back(std::make_shared<Pack>(Pack_loop));
            }
        }
        return pack_events;
}

//checks if the name is valid + no numbers etc
    bool isNameValid(const string &name) {

        //check if the name between 3-15 after that check if the name is valid
        if (name.size() < 3 || name.size() > 15) {
            return false;
        }
        for (int i = 0; i < name.size(); i++) {
            if ((name[i] < 'a' || name[i] > 'z') && (name[i] < 'A' || name[i] > 'Z')) {
                return false;
            }
        }
        return true;
    }


//read people from file and initialize the players vector
void MatamStory::readPlayers(istream &playersStream) {

    int num_of_players = 0;
    string name;
    string character;
    string job;
    while (playersStream >> name >> character >> job) {
        if (!isNameValid(name)) {
            throw PlayersException();
        }
        if (character != "RiskTaking" && character != "Responsible") {
            throw PlayersException();
        }
        if (job != "Warrior" && job != "Magic" && job != "Archer") {
            throw PlayersException();
        }
        players.push_back(std::make_unique<Player>(name, character, job));
        num_of_players++;
    }
    if (num_of_players < 2 || num_of_players > 6) {
        throw PlayersException();
    }
}

