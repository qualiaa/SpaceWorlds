#include "Universe.hpp"
#include "PlayerSpaceship.hpp"
#include "Planet.hpp"
#include "Minimap.hpp"
#include <Tank/System/Game.hpp>
#include "../Dialog.hpp"
#include <random>

Universe::Universe()
{
    makeEntity<PlayerSpaceship>();
    makeEntity<Minimap>();
    camera.setScale(2);
    tank::Game::window()->setBackgroundColor({9,21,31});

    genWorld();
}

void Universe::genWorld()
{
	const std::vector<std::string> names {
		"alpha",	"beta",		"gamma",	"delta",
		"epsilon",	"diamond",	"apple",	"tango",
		"foxtrot",	"disco",	"astor",	"cerulean"
	};

	std::vector<tank::observing_ptr<Planet>> planets = {};

    std::mt19937 rand_eng {3};
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
        
        int genx = rand_x(rand_eng);
        int geny = rand_y(rand_eng);
        
        for (const auto& p : planets) {
            auto pos = p->getPos();
            float dx = pos.x - genx;
            float dy = pos.y - geny;
            if (std::sqrt(dx*dx + dy*dy) < 300) {
                genx = rand_x(rand_eng);
                geny = rand_y(rand_eng);
            }
        }
        
        planets.emplace_back(
             makeEntity<Planet>(tank::Vectorf{genx, geny}, name.str()));
    }

}