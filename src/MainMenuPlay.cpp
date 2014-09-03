#include "MainMenuPlay.hpp"
#include <Tank/Utility/Resources.hpp>
#include <Tank/System/Mouse.hpp>
#include <Tank/Graphics/Text.hpp>

MainMenuPlay::MainMenuPlay(tank::Vectorf pos)
    : Entity{pos}
{
    using res = tank::Resources;
    background_ = makeGraphic<tank::RectangleShape>(tank::Vectorf{400,60});
    background_->centreOrigin();
    background_->setFillColor({0,0,0,0});

    auto& font = res::get<tank::Font>("assets/fonts/PlanetFont.ttf");
    auto label = makeGraphic<tank::Text>(font);
    label->setPos({0.0,-8.0});
    label->setText("play");
    label->centreOrigin();
    label->setPos(tank::Vectori{label->getPos()});

    auto const& oldHitbox = getHitbox();
    setHitbox({
        -oldHitbox.w / 2.0,
        -oldHitbox.h / 2.0,
         oldHitbox.w,
         oldHitbox.h
     });
}

void MainMenuPlay::onAdded()
{
    connect(tank::Mouse::InEntity(*this), [this] {
                background_->setFillColor({0,0,0,100}); });
    connect(tank::fnot(tank::Mouse::InEntity(*this)), [this] {
                background_->setFillColor({0,0,0,0}); });
}
