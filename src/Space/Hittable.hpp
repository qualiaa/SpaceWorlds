#pragma once
#include <Tank/System/Entity.hpp>

class Hittable : public tank::Entity
{
    int maxHealth_;
    int health_;
    std::string bulletType_;
public:
    Hittable(int health, std::string bulletType)
        : maxHealth_{health}
        , health_ {health}
        , bulletType_{bulletType}
    {}
    
    virtual void checkHit();
    void heal(int amt);
    
    int getHealth() {return health_;}
};