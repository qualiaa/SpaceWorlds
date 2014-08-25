#include "Universe.hpp"
#include "PlayerSpaceship.hpp"
#include "Planet.hpp"
#include <Tank/System/Game.hpp>
#include "../Dialog.hpp"
#include "iostream"

Universe::Universe()
{
    makeEntity<PlayerSpaceship>();
    camera.setScale(3);
    tank::Game::window()->setBackgroundColor({9,21,31});

    genWorld(3);
}

void Universe::genWorld(unsigned seed)
{
	//Set universe seed
	std::srand(seed);

	const std::vector<std::string> names = {
		"alpha",	"beta",		"gamma",	"delta",
		"epsilon",	"diamond",	"apple",	"tango",
		"foxtrot",	"disco",	"astor",	"cerulean"
	};

	std::vector<tank::observing_ptr<Planet>> planets = {};

	for(int i=0; i<names.size(); ++i) {
		//Generate name
		std::string name = "";
		float chance = 1;
		while(static_cast<float>(std::rand())/RAND_MAX < chance) {
			chance /= 2.5;
			name += *(names.begin() + std::rand() % names.size()) + "-";
		}

		//Number
		chance=1.0;
		while(static_cast<float>(std::rand())/RAND_MAX < chance) {
			chance /= 2.5;
			name += std::to_string(std::rand() % 10);
		}

		//10% chance of bonus end bit
		while(static_cast<float>(std::rand())/RAND_MAX < 0.1) {
			name += "-" + *(names.begin() + std::rand() % names.size());
		}


		int genx = std::rand() % worldWidth;
		int geny = std::rand() % worldHeight;
		//Position away from other worlds
		for(auto p : planets) {
			tank::Vectorf pos = p->getPos();
			float dx = pos.x - genx;
			float dy = pos.y - geny;
			if(std::sqrt(dx * dx + dy * dy) < 300 /*HARD CODED DISTANCE*/) {
				genx = std::rand() % worldWidth;
				geny = std::rand() % worldHeight;
			}
		}

   		auto planet = makeEntity<Planet>(
   			tank::Vectorf{genx, geny}, name);


   		planets.push_back(planet);



	}


}