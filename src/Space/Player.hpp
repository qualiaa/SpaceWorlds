#pragma once
#include <Tank/System/Controller.hpp>
#include "Ship.hpp"

class Player : public Ship
{
    bool interacting_ {false};
    tank::Camera camera_;
    tank::observing_ptr<tank::Controller> controller_;
    const unsigned id_;
    static unsigned numPlayers;

public:
    Player(tank::observing_ptr<tank::Controller>);

    void onAdded() override;
    void onRemoved() override;
    void update() override;

    tank::Camera const& getCamera() { return camera_; }

private:
    void interact();
    void handleController();
};
