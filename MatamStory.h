
#pragma once

#include <iostream>
#include "Players/Player.h"
#include "Events/Event.h"
#include <vector>
#include <memory>


using std::vector;

#include "Players/Player.h"
#include "Events/Event.h"



class MatamStory{


private:
    vector<std::unique_ptr<Player>> players;
    vector<std::shared_ptr<Event>> events;


    unsigned int m_turnIndex = 1;
    int m_roundIndex = 1;

    /**
     * Playes a single turn for a player
     *
     * @param player - the player to play the turn for
     *
     * @return - void
    */
    void playTurn(Player& player);

    /**
     * Plays a single round of the game
     *
     * @return - void
    */
    void playRound();

    /**
     * Checks if the game is over
     *
     * @return - true if the game is over, false otherwise
    */
    bool isGameOver() const;

public:
    /**
     * Constructor of MatamStory class
     *
     * @param eventsStream - events input stream (file)
     * @param playersStream - players input stream (file)
     *
     * @return - MatamStory object with the given events and players
     *
    */
    MatamStory(std::istream& eventsStream, std::istream& playersStream);

    //i want do a function that reads pack from the stream and returns a vector of shared pointers to the events
    /**
     * Plays the entire game
     *
     * @return - void
    */
    void play();

    void eventsStreamReader(std::istream &eventsStream);

    vector<shared_ptr<Encounter>> readFromPack(istream &eventsStream, int size);

    void readPlayers(istream &playersStream);
};


class PlayersException : public std::exception {
    const char* what() const noexcept override {
        return "Players exception occurred!";
    }
};

class EventException : public std::exception {
    const char* what() const noexcept override {
        return "EventException exception occurred!";
    }
};