
#include <algorithm>
#include "MatamStory.h"
#include <string>
#include "Utilities.h"



void MatamStory::eventsStreamReader(std::istream& eventsStream) {
    string event;
    std::vector<shared_ptr<Event>> pack_events;
    while (eventsStream >> event) {
        if(event == "SolarEclipse") {
            events.push_back(std::make_shared<SolarEclipse>());
        } else if (event == "PotionsMerchant") {
            events.push_back(std::make_shared<PotionsMerchant>());
        } else if (event == "Snail") {
            events.push_back(std::make_shared<Snail>());
        } else if (event == "Slime") {
            events.push_back(std::make_shared<Slime>());
        } else if (event == "Barlog") {
            events.push_back(std::make_shared<Barlog>());
        } else if (event == "Pack") {
            int num_of_events;
            eventsStream >> num_of_events;
            if (num_of_events < 2) {
                throw std::invalid_argument("Pack must be at least 2");
            }
        }
    }
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

    //check if turn index is bigger than the events size
    if (m_roundIndex >= events.size()) {
        m_roundIndex = 0;
    }
    /**
     * Steps to implement (there may be more, depending on your design):
     * 1. Get the next event from the events list
     * 2. Print the turn details with "printTurnDetails"
     * 3. Play the event
     * 4. Print the turn outcome with "printTurnOutcome"
    */

    shared_ptr<Event> current_event = events[m_roundIndex];
    printTurnDetails(m_turnIndex, player, *current_event);
    cout << current_event->apply(player) << endl << endl;
    printTurnOutcome(current_event->getDescription());
    m_turnIndex++;
    m_roundIndex++;
}

bool comparingPlayers(const std::unique_ptr<Player>& Player_A, const std::unique_ptr<Player>& Player_B) {
    if (Player_A->getLevel() == Player_B->getLevel()) {
        if (Player_A->getForce() == Player_B->getForce()) {
            if (Player_A->getHealthPoints() == Player_B->getHealthPoints()) {
                return Player_A->getCoins() > Player_B->getCoins();
            }
            return Player_A->getHealthPoints() > Player_B->getHealthPoints();
        }
        return Player_A->getForce() > Player_B->getForce();
    }
    return Player_A->getLevel() > Player_B->getLevel();
}

void sortPlayers(vector<std::unique_ptr<Player>>& players) {
    std::sort(players.begin(), players.end(), comparingPlayers);
}

void MatamStory::playRound() {

    int players_num = this->m_numOfPlayers;
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
        for (int i = 0; i < m_numOfPlayers ; i++) {
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
        for(char i : name) {
            if ((i < 'a' || i > 'z') && (i < 'A' || i > 'Z')) {
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
    this->m_numOfPlayers = num_of_players;
    if (num_of_players < 2 || num_of_players > 6) {
        throw PlayersException();
    }

}

