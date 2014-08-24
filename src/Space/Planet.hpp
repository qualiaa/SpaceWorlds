#pragma once
#include <Tank/System/Entity.hpp>
#include <Tank/Graphics/Graphic.hpp>
#include "../Dialog.hpp"

class Planet : public tank::Entity
{
    tank::observing_ptr<tank::Graphic> graphic_;
    tank::observing_ptr<Dialog> label_;
    std::string name_;

public:
    Planet(tank::Vectorf pos, const std::string& name = "");
    
    void onAdded() override;
    
    void setNameVisible(bool visible) {
        label_->setVisible(visible);
    }
    
    void update() override;
};
