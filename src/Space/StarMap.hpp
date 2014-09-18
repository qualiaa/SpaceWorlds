#pragma once

#include <memory>
#include <Tank/System/Entity.hpp>

class StarMap : public tank::Entity
{
    struct Star : public tank::Entity {
        Star(tank::Vectorf pos);
    };
    using StarList = std::vector<std::unique_ptr<StarMap::Star>>;

    static constexpr int numberOfStars = 1000;
    static constexpr int groups = numberOfStars / 8;

    //int currentGroup = 0;
    StarList stars_;
public:

    StarMap(tank::Vectori topLeft, tank::Vectori bottomRight);

    virtual void draw(tank::Camera const&) override;
};
