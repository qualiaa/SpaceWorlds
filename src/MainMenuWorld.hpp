#pragma once
#include <Tank/System/World.hpp>
#include <Tank/Audio/Music.hpp>

class MainMenuWorld : public tank::World
{
    tank::Music music_;

public:
    MainMenuWorld();
    virtual ~MainMenuWorld();

    void startGame();
};
