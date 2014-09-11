#pragma once
#include <Tank/System/Entity.hpp>
#include <Tank/Graphics/CircleShape.hpp>
#include "../Dialog.hpp"

class Planet : public tank::Entity
{
    using Overlay = tank::observing_ptr<tank::CircleShape>;
    using Label = tank::observing_ptr<Dialog>;

    Overlay overlay_;
    Label label_;
    std::string name_;
    int uses_ {3};

    enum Type {Blue = 1, Green = 2, Red = 3} type_;

    void setNameVisible(bool visible) {
        label_->setVisible(visible);
    }

public:
    Planet(tank::Vectorf pos, const std::string& name);

    void onAdded() override;

    void update() override;
};
