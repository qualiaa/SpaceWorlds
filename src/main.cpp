#include <Tank/System/Game.hpp>
#include "Space/Universe.hpp"

int main()
{
    tank::Game::initialize({800,600});
    tank::Game::makeWorld<Universe>();
    tank::Game::run();
}
