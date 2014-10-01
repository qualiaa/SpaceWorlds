#pragma once
#include <random>
#include <SFML/Graphics/View.hpp>
#include <Tank/System/World.hpp>
#include <Tank/Audio/Music.hpp>
#include "../HudDialog.hpp"

class Player;

class Universe : public tank::World
{
    using PlayerPtr = tank::observing_ptr<Player>;
    using PlayerView = std::pair<PlayerPtr, sf::View>;
    using PlayerList = std::vector<PlayerView>;

    tank::Music fightMusic_;
    PlayerList players_;
    tank::observing_ptr<Player> player_;
	tank::observing_ptr<HudDialog> hud_;

public:
    Universe();
    virtual ~Universe();

    void draw() override;
    virtual void onAdded() override;

    static int score;

    static const int worldWidth;
    static const int worldHeight;

    auto getPlayer() {return player_;}

    static std::mt19937 randEng;

private:
    void genWorld();
    void createPlayers();
};
