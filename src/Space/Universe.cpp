#include "Universe.hpp"

#include <ctime>
#include <algorithm>
#include <Tank/System/Game.hpp>
#include <Tank/System/Controller.hpp>
#include <Tank/Graphics/Text.hpp>
#include <Tank/Utility/Resources.hpp>
#include "../Dialog.hpp"
#include "../HudDialog.hpp"
#include "Planet.hpp"
#include "StarMap.hpp"
#include "Player.hpp"
#include "Enemy.hpp"
#include "Minimap.hpp"

int Universe::score = 0;
const int Universe::worldWidth = 1000;
const int Universe::worldHeight = 1000;
std::mt19937 Universe::randEng {static_cast<unsigned>(std::time(nullptr))};

Universe::Universe()
{
    camera.setScale(2);
    using res = tank::Resources;

    struct bg : public tank::Entity {
        bg() : tank::Entity({-250,-250}) {
            makeGraphic(res::get<tank::Image>("assets/graphics/starmap.png"));
            setLayer(std::numeric_limits<int>::min());
        }
    };

    makeEntity<bg>();
    //makeEntity<StarMap>(Vecf{}, Vecf{worldWidth,worldHeight});

    createPlayers();
    tank::Game::window()->setBackgroundColor({9,21,31});

    genWorld();

    fightMusic_ = res::get<tank::Music>("assets/music/get_fire.ogg");
    fightMusic_.setLoop(true);
    fightMusic_.setVolume(200);
    score = 0;
}

void Universe::onAdded()
{
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

	std::vector<tank::observing_ptr<Planet>> planets = {};;
    std::uniform_real_distribution<float> rand_floats {0,1};
    std::uniform_int_distribution<std::size_t> rand_ints {0, names.size()-1};
    std::uniform_int_distribution<int> rand_x {0, worldWidth};
    std::uniform_int_distribution<int> rand_y {0, worldHeight};
    std::uniform_int_distribution<int> rand_digit {0,9};

    for (std::size_t i = 0; i < names.size(); ++i) {
        std::stringstream name;
        float chance {1};

        while (rand_floats(randEng) < chance) {
            chance /= 2.5;
            name << names[rand_ints(randEng)] << "-";
        }

        chance = 1;
        while (rand_floats(randEng) < chance) {
            chance /= 2.5;
            name << rand_digit(randEng);
        }

        if (rand_floats(randEng) < 0.1) {
            name << "-" << names[rand_ints(randEng)];
        }

        int genx, geny;
        bool safePlacement;

        do {
            genx = rand_x(randEng);
            geny = rand_y(randEng);
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

void Universe::createPlayers()
{
    const auto controllers = tank::Controllers::getConnectedControllers();
    const auto windowSize = tank::Game::window()->SFMLWindow().getSize();
    const auto def = tank::Game::window()->SFMLWindow().getDefaultView();
    sf::View d,c,b,a = def;
    tank::observing_ptr<tank::Controller> controller = nullptr;
    if (not controllers.empty()) {
        controller = controllers.front();
    }

    switch(controllers.size()) {
        case 0:
        case 1:
            players_.emplace_back(makeEntity<Player>(controller), def);
            for (int i = 0; i < 10; ++i) {
                makeEntity<Enemy>();
            }
            break;
        case 2:
            a.setSize(windowSize.x / 2, windowSize.y);
            b = a;
            a.setViewport({0.0,0.0,0.5,1});
            b.setViewport({0.5,0.0,0.5,1});
            players_.emplace_back(makeEntity<Player>(controllers.front()), a);
            players_.emplace_back(makeEntity<Player>(controllers.back()), b);
            break;
        default:
        case 4:
            a.setSize(windowSize.x / 2, windowSize.y / 2);
            d = c = b = a;
            a.setViewport({0.0,0.0,0.5,0.5});
            b.setViewport({0.5,0.0,0.5,0.5});
            c.setViewport({0.0,0.5,0.5,0.5});
            d.setViewport({0.5,0.5,0.5,0.5});
            players_.emplace_back(makeEntity<Player>(controllers[3]), d);
        case 3:
            players_.emplace_back(makeEntity<Player>(controllers[0]), a);
            players_.emplace_back(makeEntity<Player>(controllers[1]), b);
            players_.emplace_back(makeEntity<Player>(controllers[2]), c);
            break;
    }
    player_ = players_.back().first;
}

void Universe::draw()
{
    auto oldCam = camera;

    for (auto& playerView : players_) {
        camera = playerView.first->getCamera();
        tank::Game::window()->SFMLWindow().setView(playerView.second);
        tank::World::draw();
    }
    const auto def = tank::Game::window()->SFMLWindow().getDefaultView();
    tank::Game::window()->SFMLWindow().setView(def);

    camera = oldCam;
}
