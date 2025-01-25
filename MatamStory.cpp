#include <algorithm>
#include "MatamStory.h"
#include <string>
#include "Utilities.h"
#include <vector>
#include "Players/Player.h"

/////////////////

void MatamStory::eventsStreamReader(std::istream& eventsStream) {
    std::string event;
    while (eventsStream >> event) {
        if(event == "SolarEclipse") {
            events.push_back(std::make_shared<SolarEclipse>());
        } else if (event == "PotionsMerchant") {
            events.push_back(std::make_shared<PotionsMerchant>());
        } else if (event == "Snail") {
            events.push_back(std::make_shared<Snail>());
        } else if (event == "Slime") {
            events.push_back(std::make_shared<Slime>());
        } else if (event == "Balrog") {
            events.push_back(std::make_shared<Balrog>());
        } else if (event == "Pack") {
            int num_of_events;
            eventsStream >> num_of_events;
            if (num_of_events < 2) {
                throw std::invalid_argument("Invalid Events File");
            }
            std::vector<std::shared_ptr<Encounter>> pack_events = readFromPack(eventsStream, num_of_events);
            events.push_back(std::make_shared<Pack>(pack_events));
        } else {
            throw std::invalid_argument("Invalid Events File");
        }
    }
}

MatamStory::MatamStory(std::istream& eventsStream, std::istream& playersStream) {


    eventsStreamReader(eventsStream);

    if (events.size() < 2) {
        throw EventException();
    }

    readPlayers(playersStream);

    if (players.size() < 2 || players.size() > 6) {
        throw PlayersException();
    }

    this->m_turnIndex = 1;
    this->m_roundIndex = 0;
}

void MatamStory::playTurn(Player& player) {
    if (m_roundIndex >= events.size()) {
        m_roundIndex = 0;
    }

    auto current_event = events[m_roundIndex];
    printTurnDetails(m_turnIndex, player, *current_event);
    std::cout << current_event->apply(player) << std::endl << std::endl;
   // printTurnOutcome(current_event->getDescription());

    m_turnIndex++;
    m_roundIndex++;
}

void sortPlayers(std::vector<std::unique_ptr<Player>>& players) {
    std::sort(players.begin(), players.end(), [](const auto& lhs, const auto& rhs) {
        if (lhs->getLevel() != rhs->getLevel()) {
            return lhs->getLevel() > rhs->getLevel();
        }
        if (lhs->getCoins() != rhs->getCoins()) {
            return lhs->getCoins() > rhs->getCoins();
        }
        return lhs->getName() < rhs->getName();
    });
}

void MatamStory::playRound() {
    printRoundStart();

    for (auto& player : players) {
        if (!player->isDead()) {
            playTurn(*player);
        }
    }


    vector<std::unique_ptr<Player>> sortedPlayers;

    for (const auto& player : players) {
        sortedPlayers.push_back(std::make_unique<Player>(*player));
    }

    sortPlayers(sortedPlayers);

    printRoundEnd();

    printLeaderBoardMessage();

    int index = 1;
    for (const auto& player : sortedPlayers) {
        printLeaderBoardEntry(index++, *player);
    }

    printBarrier();
}

bool winner(const std::vector<std::unique_ptr<Player>>& players) {
    return std::any_of(players.begin(), players.end(), [](const auto& player) {
        return player->getLevel() == 10;
    });
}

bool allDead(const std::vector<std::unique_ptr<Player>>& players) {
    return std::all_of(players.begin(), players.end(), [](const auto& player) {
        return player->isDead();
    });
}

bool MatamStory::isGameOver() const {
    return winner(players) || allDead(players);
}

void MatamStory::play() {
    printStartMessage();

    int index = 1;
    for (const auto& player : players) {
        printStartPlayerEntry(index++, *player);
    }

    printBarrier();

    while (!isGameOver()) {
        playRound();
    }

    printGameOver();

    if (winner(players)) {
        sortPlayers(players);
        printWinner(*players[0]);
    } else {
        printNoWinners();
    }
}

std::vector<std::shared_ptr<Encounter>> MatamStory::readFromPack(std::istream& eventsStream, int size) {
    std::vector<std::shared_ptr<Encounter>> pack_events;
    for (int i = 0; i < size; ++i) {
        std::string event;
        eventsStream >> event;

        if (event == "Snail") {
            pack_events.push_back(std::make_shared<Snail>());
        } else if (event == "Slime") {
            pack_events.push_back(std::make_shared<Slime>());
        } else if (event == "Balrog") {
            pack_events.push_back(std::make_shared<Balrog>());
        } else if (event == "Pack") {
            int num_of_events;
            eventsStream >> num_of_events;
            if (num_of_events < 2) {
                throw std::invalid_argument("Invalid Events File");
            }
            auto nested_pack = readFromPack(eventsStream, num_of_events);
            pack_events.push_back(std::make_shared<Pack>(nested_pack));
        } else {
            throw std::invalid_argument("Invalid Events File");
        }
    }
    return pack_events;
}

bool isNameValid(const std::string& name) {
    if (name.size() < 3 || name.size() > 15) {
        return false;
    }
    return std::all_of(name.begin(), name.end(), [](char c) {
        return std::isalpha(c);
    });
}

void MatamStory::readPlayers(std::istream& playersStream) {
    std::string name, character, job;
    while (playersStream >> name >> job >> character) {
        if (!isNameValid(name)) {
            throw PlayersException();
        }

        if (character != "RiskTaking" && character != "Responsible") {
            throw PlayersException();
        }

        if (job != "Warrior" && job != "Magician" && job != "Archer") {
            throw PlayersException();
        }

        players.push_back(std::make_unique<Player>(name, character, job));
    }

    if (players.size() < 2 || players.size() > 6) {
        throw PlayersException();
    }
}
