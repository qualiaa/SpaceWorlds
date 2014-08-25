#pragma once
#include <Tank/System/Entity.hpp>
#include <Tank/Graphics/FrameList.hpp>

class PlayerSpaceship : public tank::Entity
{
    tank::observing_ptr<tank::FrameList> sprite;
    tank::Vectorf velocity {0,0};
    tank::Vectorf direction {0,-1};
    const float rotationAngle {1};

public:
    static const float acceleration;
    PlayerSpaceship();

    void onAdded() override;
    void update() override;
    void setRotation(float angle) override;
};
