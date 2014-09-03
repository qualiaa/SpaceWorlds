#include "Hittable.hpp"

#include <thread>
#include <algorithm>
#include <boost/range/algorithm.hpp>
#include <boost/range/algorithm_ext.hpp>
#include <Tank/Utility/Timer.hpp>

Hittable::Hittable(tank::Vectorf pos, int health)
        : Entity(pos)
        , maxHealth_{health}
        , health_ {health}
{
    damageTimer.start();
}

void Hittable::update()
{
    checkHit();

    if (health_ <= 0) {
        die();
    }

    if (flashHalfFrames > 0)
    {
        if (flashTimer.getTime() > flashTime) {
            getGraphic()->setVisible(not getGraphic()->isVisible());
            flashTimer.start();
            --flashHalfFrames;
        }
    } else {
        flashTimer.stop();
    }
}

void Hittable::checkHit()
{
    using namespace boost::range;
    using namespace std::literals;
    auto bullets = collide("bullet");

    /* Remove my bullets */
    auto const& myTypes = getTypes();
    boost::remove_erase_if(bullets, [&myTypes](auto bullet) {
        return myTypes.end() !=
               boost::find_if(myTypes, std::bind(&tank::Entity::isType,
                                                 bullet.get(),
                                                 std::placeholders::_1));
        });

    /* Take damage */
    if (not bullets.empty()) {
        std::this_thread::sleep_for(50ms);
        hit();
    }
    /* Remove bullets */
    for (auto& bullet : bullets) {
        bullet->remove();
    }
}

void Hittable::hit(int damage)
{
    if (damageTimer.getTime() > damageTime) {
        health_ -= damage;
        flash(3);
        damageTimer.start();
    }
}

void Hittable::heal(int amount)
{
	health_ += amount;
	if(health_ + amount > maxHealth_) {
		health_ = maxHealth_;
	}
}

void Hittable::flash(int frames)
{
    flashHalfFrames += 2*frames;
    flashTimer.start();
}

void Hittable::die()
{
    remove();
}
