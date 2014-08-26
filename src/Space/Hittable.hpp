#pragma once
#include <chrono>
#include <Tank/System/Entity.hpp>
#include <Tank/Utility/Timer.hpp>

class Hittable : public tank::Entity
{
    int maxHealth_;
    int health_;
    std::string bulletType_;

    tank::Timer flashTimer;
    int flashFrames = 0;
    const unsigned flashTime {50};

public:
    Hittable(int health, std::string bulletType)
        : maxHealth_{health}
        , health_ {health}
        , bulletType_{bulletType}
    {}
    
    virtual void checkHit();
    void heal(int amt);
    
    int getHealth() {return health_;}
    
    void update() override {checkHit();}
};
