#pragma once
#include <Tank/System/Entity.hpp>
#include <Tank/Graphics/Graphic.hpp>
#include <Tank/Graphics/RectangleShape.hpp>

class MainMenuPlay : public tank::Entity
{
    tank::observing_ptr<tank::RectangleShape> background_;

public:
    MainMenuPlay(tank::Vectorf pos);
    
    void onAdded() override;
};
