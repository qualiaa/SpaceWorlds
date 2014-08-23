#include <Tank/System/Game.hpp>
#include "Universe.hpp"

int main()
{
    tank::Game::initialize({800,600});
    tank::Game::makeWorld<Universe>();
    tank::Game::run();
}
