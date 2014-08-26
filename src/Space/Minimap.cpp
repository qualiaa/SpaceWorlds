#include "Minimap.hpp"
#include <Tank/System/World.hpp>
#include <Tank/System/Keyboard.hpp>
#include <Tank/System/Game.hpp>
#include <Tank/Utility/Resources.hpp>

Minimap::Minimap()
{
    //Nothing to see here please move on
    graphicSmall_ = makeGraphic(Resources::get<tank::Image>("assets/graphics/minimap.png"));
    graphicBig_ = makeGraphic(Resources::get<tank::Image>("assets/graphics/minimap2.png"));
    setPos(tank::Game::window()->getSize() - graphicSmall_->getSize());
    
    graphicSmall_->setScale(2);
    graphicSmall_->setVisible(false);
    graphicBig_->setScale(2);
    graphicBig_->setVisible(false);
    
    setLayer(101);
}

void Minimap::onAdded()
{
    using kbd = tank::Keyboard;
    using key = tank::Key;
    
    auto toggle = kbd::KeyPress(key::M);
    connect(toggle, [this](){
        switch (state) {
            case State::None    : state = State::Small; break;
            case State::Small   : state = State::Large; break;
            case State::Large   : state = State::None; break;
        }
    });
}

void Minimap::draw(const tank::Camera& cam)
{
    Entity::draw({});
}

void Minimap::update()
{
    switch (state) {
        case State::None    :
            graphicSmall_->setVisible(false);
            graphicBig_->setVisible(false);
            break;
        case State::Small   :
            graphicSmall_->setVisible(true);
            graphicBig_->setVisible(false);
            setPos(tank::Game::window()->getSize() - graphicSmall_->getSize());
            break;
        case State::Large   :
            graphicSmall_->setVisible(false);
            graphicBig_->setVisible(true);
            setPos(tank::Game::window()->getSize() - graphicBig_->getSize());
            break;
    }
}
