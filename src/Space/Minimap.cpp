#include "Minimap.hpp"
#include <Tank/System/World.hpp>
#include <Tank/System/Keyboard.hpp>
#include <Tank/System/Game.hpp>
#include <Tank/Utility/Resources.hpp>

Minimap::Minimap()
{
    //Nothing to see here please move on
    makeGraphic(Resources::get<tank::Image>("assets/graphics/minimap.png"));
    setPos(tank::Game::window()->getSize() - getGraphic()->getSize()*2);
    getGraphic()->setScale(2);
    setLayer(101);
}

void Minimap::onAdded()
{
    using kbd = tank::Keyboard;
    using key = tank::Key;
    
    auto toggle = kbd::KeyPress(key::M);
    connect(toggle, [this](){
        getGraphic()->setVisible(!getGraphic()->isVisible());
    });
}

void Minimap::draw(const tank::Camera& cam)
{
    Entity::draw({});
}
