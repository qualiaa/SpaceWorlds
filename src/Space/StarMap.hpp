#pragma once

#include <memory>
#include <Tank/System/Entity.hpp>
#include <Tank/Geometry/GeometricLookup.hpp>

class StarMap : public tank::Entity
{
    struct Star : public tank::Entity {
        Star(tank::Vectorf pos);
    };
    using StarPtr = std::unique_ptr<StarMap::Star>;
    using StarList = tank::GeometricLookup<StarPtr,
                                           tank::CoordsFromTransformablePtr<double>>;

    static constexpr int numberOfStars = 1000;

    //int currentGroup = 0;
    StarList stars_;
    // FIXME: HAHAHAHHAHAHAHAHAHAAHAHAHAHA
    decltype(stars_.within_region({},{})) currentList;
public:

    StarMap(tank::Vectori topLeft, tank::Vectori bottomRight);

    virtual void draw(tank::Camera const&) override;
};
