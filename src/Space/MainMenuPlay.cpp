#include "MainMenuPlay.hpp"
#include <Tank/System/World.hpp>
#include <Tank/System/Mouse.hpp>
#include <Tank/System/Game.hpp>
#include "Universe.hpp"

MainMenuPlay::MainMenuPlay(tank::Vectorf pos)
    : Entity{pos}
{
    graphicInactive_ = makeGraphic("assets/graphics/mainmenu_playbutton_inactive.png");
    graphicActive_ = makeGraphic("assets/graphics/mainmenu_playbutton_active.png");
    graphicActive_->setVisible(false);
}

void MainMenuPlay::update()
{
    bool mouseHoverOverNow = tank::Mouse::isInEntity(*this);
    if (mouseHoverOverNow != mouseHoverOver_) {
        graphicActive_->setVisible(mouseHoverOverNow);
        graphicInactive_->setVisible(!mouseHoverOverNow);
        mouseHoverOver_ = mouseHoverOverNow;
    }
    
    if (mouseHoverOverNow && tank::Mouse::isButtonPressed()) {
        tank::Game::makeWorld<Universe>();
    }
}
