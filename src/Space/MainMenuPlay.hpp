#pragma once
#include <Tank/System/Entity.hpp>
#include <Tank/Graphics/Graphic.hpp>

class MainMenuPlay : public tank::Entity
{
    tank::observing_ptr<tank::Graphic> graphicInactive_, graphicActive_;
    bool mouseHoverOver_ = false;

public:
    MainMenuPlay(tank::Vectorf pos);
    
    void update() override;
};
