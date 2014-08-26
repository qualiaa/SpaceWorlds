#pragma once
#include <Tank/System/Entity.hpp>

class Hittable : public tank::Entity
{
    int health_;
    std::string bulletType_;

public:
    Hittable(int health, std::string bulletType)
        : health_{health}
        , bulletType_{bulletType}
    {}
    
    virtual void checkHit();
    
    int getHealth() {return health_;}
};
