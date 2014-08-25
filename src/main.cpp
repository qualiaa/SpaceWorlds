#include <Tank/System/Game.hpp>
#include "Space/MainMenuWorld.hpp"

int main()
{
    tank::Game::initialize({800,600});
    tank::Game::makeWorld<MainMenuWorld>();
    tank::Game::run();
}
