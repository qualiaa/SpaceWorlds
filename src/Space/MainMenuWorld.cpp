#include "MainMenuWorld.hpp"
#include <Tank/System/Game.hpp>
#include "MainMenuPlay.hpp"
#include "MainMenuBackground.hpp"

MainMenuWorld::MainMenuWorld()
{
    makeEntity<MainMenuBackground>();
    makeEntity<MainMenuPlay>(tank::Vectorf{400, 400});
    tank::Game::window()->setBackgroundColor({255,255,255});
}
