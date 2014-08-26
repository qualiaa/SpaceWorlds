#include "Hittable.hpp"

#include <Tank/Utility/Timer.hpp>

void Hittable::checkHit()
{
    auto bullets = collide(bulletType_);
    for (auto& bullet : bullets) {
        health_ -= 1;
        bullet->remove();
        tank::Timer::delay(std::chrono::milliseconds(50));
        flashFrames += 6;
        flashTimer.start();
    }
    if (health_ <= 0) {
        remove();
    }

    if (flashFrames > 0)
    {
        if (flashTimer.isStarted()) {
            if (flashTimer.getTime<std::chrono::milliseconds>() > flashTime) {
                getGraphic()->setVisible(not getGraphic()->isVisible());
                flashTimer.start();
                --flashFrames;
            }

        }
    } else {
        flashTimer.stop();
    }
}

void Hittable::heal(int amt) {
	health_ += amt;
	if(health_ + amt > maxHealth_) {
		health_ = maxHealth_;
	}
}
