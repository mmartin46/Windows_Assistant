// Mark 16:16
#ifndef GAME_H
#define GAME_H

#include "libraries.cpp"


// Runs the game.
class Game
{
    private:
        uint8_t run;
    
    public:
        Game();
        virtual ~Game();
        void set_status(uint8_t);
        bool get_status() const;
};

// Sets the current game status.
void Game::set_status(uint8_t t)
{
    run = t;
}

// Checks if the game is running.
bool Game::get_status() const
{
    if (!run)
    {
        return 0;
    }
    return 1;
}


// Starts the game
Game::Game()
{
    run = 1;
}

// Destroys the game
Game::~Game()
{
    run = 0;
}

#endif