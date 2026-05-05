#include"Game.hpp"
void Game::addButton(State s,Button  b)
{
    this->activableButtons[s].push_back(b);
}