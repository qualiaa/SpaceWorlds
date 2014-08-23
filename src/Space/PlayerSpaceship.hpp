#pragma once
#include <Tank/System/Entity.hpp>
#include <Tank/Graphics/Graphic.hpp>

class PlayerSpaceship : public tank::Entity
{
    tank::observing_ptr<tank::Graphic> graphic;
public:
    PlayerSpaceship();

    void onAdded() override;
    void update() override;
};
