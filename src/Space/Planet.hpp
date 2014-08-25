#pragma once
#include <Tank/System/Entity.hpp>
#include <Tank/Graphics/Graphic.hpp>
#include "../Dialog.hpp"

class Planet : public tank::Entity
{
    tank::observing_ptr<tank::Graphic> graphic_;
    tank::observing_ptr<Dialog> label_;
    std::string name_;

    enum {Blue = 1, Green = 2, Red = 3} type_;

    void setNameVisible(bool visible) {
        label_->setVisible(visible);
    }

public:
    Planet(tank::Vectorf pos, const std::string& name);
    
    void onAdded() override;
    
    void update() override;
};
