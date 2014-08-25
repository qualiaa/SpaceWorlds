#pragma once
#include <Tank/System/Entity.hpp>
#include <Tank/Graphics/Graphic.hpp>

class Minimap : public tank::Entity
{
    tank::observing_ptr<tank::Graphic> graphic_;

public:
    
    Minimap();
    
    void onAdded() override;
    void draw(const tank::Camera& cam) override;
};
