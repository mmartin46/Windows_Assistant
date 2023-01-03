// Mark 16:16
#ifndef GAME_H
#define GAME_H

// Runs the game.
class Game
{
    private:
        int run;
    
    public:
        Game();
        bool status();
};

// Checks if the game is running.
bool Game::status()
{
    if (run)
    {
        return 0;
    }
    return 1;
}


// Starts the game
Game::Game()
{
    run = 0;
}


#endif