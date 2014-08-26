#pragma once
#include <Tank/System/Entity.hpp>
#include <Tank/Graphics/Graphic.hpp>

class Minimap : public tank::Entity
{
    tank::observing_ptr<tank::Graphic> graphicSmall_;
    tank::observing_ptr<tank::Graphic> graphicBig_;
    enum class State { None, Small, Large } state {State::None};

public:
    
    Minimap();
    
    void onAdded() override;
    void draw(const tank::Camera& cam) override;
    void update() override;
};
