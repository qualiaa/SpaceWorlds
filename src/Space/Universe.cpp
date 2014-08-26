#include "Universe.hpp"

#include <random>
#include <Tank/System/Game.hpp>
#include <Tank/Graphics/Text.hpp>
#include <Tank/Utility/Resources.hpp>
#include "../Dialog.hpp"
#include "../HudDialog.hpp"
#include "Planet.hpp"
#include "PlayerSpaceship.hpp"
#include "Enemy.hpp"
#include "Minimap.hpp"

const int Universe::worldWidth = 1000;
const int Universe::worldHeight = 1000;

Universe::Universe()
{

    struct bg : public tank::Entity {
        bg() {
            makeGraphic("assets/graphics/starmap.png");
            setLayer(std::numeric_limits<int>::min());
            moveBy({-250,-250});
        }
    };
    makeEntity<bg>();
    player_ = makeEntity<PlayerSpaceship>();
    for (int i = 0; i < 10; ++i) {
        makeEntity<Enemy>();
    }
    makeEntity<Minimap>();
    camera.setScale(2);
    tank::Game::window()->setBackgroundColor({9,21,31});

    hud = makeEntity<HudDialog>(tank::Vectorf{0,0}, "HELLO THERE");
    
    genWorld();

    fightMusic_ = Resources::get<tank::Music>("assets/music/get_fire.ogg");
    fightMusic_.setLoop(true);
    fightMusic_.setVolume(200);
    fightMusic_.play();
}

Universe::~Universe()
{
    fightMusic_.stop();
}

void Universe::genWorld()
{
	const std::vector<std::string> names {
		"alpha",	"beta",		"gamma",	"delta",
		"epsilon",	"diamond",	"apple",	"tango",
		"foxtrot",	"disco",	"astor",	"cerulean"
	};

	std::vector<tank::observing_ptr<Planet>> planets = {};

    std::mt19937 rand_eng {std::random_device()()};
    std::uniform_real_distribution<float> rand_floats {0,1};
    std::uniform_int_distribution<std::size_t> rand_ints {0, names.size()-1};
    std::uniform_int_distribution<int> rand_x {0, worldWidth};
    std::uniform_int_distribution<int> rand_y {0, worldHeight};
    std::uniform_int_distribution<int> rand_digit {0,9};
    
    for (std::size_t i = 0; i < names.size(); ++i) {
        std::stringstream name;
        float chance {1};
        
        while (rand_floats(rand_eng) < chance) {
            chance /= 2.5;
            name << names[rand_ints(rand_eng)] << "-";
        }
        
        chance = 1;
        while (rand_floats(rand_eng) < chance) {
            chance /= 2.5;
            name << rand_digit(rand_eng);
        }
        
        if (rand_floats(rand_eng) < 0.1) {
            name << "-" << names[rand_ints(rand_eng)];
        }
        

        int genx, geny;
        bool safePlacement;

        do {
            genx = rand_x(rand_eng);
            geny = rand_y(rand_eng);
            safePlacement = true;

            for(const auto& p : planets) {
                auto pos = p -> getPos();
                float dx = pos.x - genx;
                float dy = pos.y - geny;
                if(dx*dx+dy*dy < 40000) { //radius 200 
                    safePlacement = false;
                    break;
                }
            }
        }
        while (!safePlacement);

        planets.emplace_back(
             makeEntity<Planet>(tank::Vectorf{genx, geny}, name.str()));
    }
}

void Universe::update() {
    tank::World::update();

    hud->setText("SHIELDS: " + std::to_string(player_->getHealth()) + "0%");
}
