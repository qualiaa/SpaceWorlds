#pragma once
#include "Hittable.hpp"
#include <Tank/Graphics/FrameList.hpp>
#include <Tank/Utility/Timer.hpp>
#include <random>
class PlayerSpaceship;

class Enemy : public Hittable
{
    tank::observing_ptr<tank::FrameList> sprite_;
    
    tank::Vectorf velocity {0,0};
    tank::Vectorf direction {0,-1};
    tank::Timer timer;
    tank::Timer bulletTimer;
    
    std::mt19937 rand_eng{std::random_device()()};
    std::uniform_real_distribution<float> angles {0, 360};
    
    tank::observing_ptr<PlayerSpaceship> player_;
    
    void setRotation(float angle);
    
public:
    Enemy();
    
    static const float speed;
    
    void onAdded() override;
    
    void update() override;
};
