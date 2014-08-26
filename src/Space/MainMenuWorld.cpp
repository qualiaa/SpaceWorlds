#include "MainMenuWorld.hpp"
#include <Tank/System/Game.hpp>
#include <Tank/Utility/Resources.hpp>
#include "MainMenuPlay.hpp"
#include "MainMenuBackground.hpp"

MainMenuWorld::MainMenuWorld()
{
    makeEntity<MainMenuBackground>();
    makeEntity<MainMenuPlay>(tank::Vectorf{200, 400});
    tank::Game::window()->setBackgroundColor({255,255,255});
    music_ = Resources::get<tank::Music>("assets/music/title1.ogg");
    music_.setVolume(25);
    music_.setLoop(true);
    //music_.play();
}

MainMenuWorld::~MainMenuWorld()
{
    music_.stop();
}
