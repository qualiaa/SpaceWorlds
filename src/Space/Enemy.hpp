#pragma once
#include <random>
#include <Tank/Graphics/FrameList.hpp>
#include <Tank/Utility/Timer.hpp>
#include "Hittable.hpp"
#include "Universe.hpp"
class PlayerSpaceship;

class Enemy : public Hittable
{
    tank::observing_ptr<tank::FrameList> sprite_;
    
    tank::Vectorf velocity {0,0};
    tank::Vectorf direction {0,-1};
    tank::Timer timer;
    tank::Timer bulletTimer;

    std::uniform_real_distribution<float> angles {0, 360};
    
    tank::observing_ptr<PlayerSpaceship> player_;
    
    void setRotation(float angle);

    void onRemoved() override {
        Universe::score++;
        getWorld()->makeEntity<Enemy>();
    }
    
public:
    Enemy();
    
    static const float speed;
    
    void onAdded() override;
    
    void update() override;
};
