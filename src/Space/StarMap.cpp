#include "StarMap.hpp"

#include <random>
#include <sstream>
#include <Tank/Graphics/Image.hpp>
#include <Tank/Graphics/FrameList.hpp>
#include "Universe.hpp"

StarMap::Star::Star(tank::Vectorf pos)
    : tank::Entity(pos)
{
    auto& randEng = Universe::randEng;
    std::exponential_distribution<> expDist {3};
    std::stringstream graphicFile;
    int n = ceil(expDist(randEng));
    graphicFile << "assets/graphics/"
                << "star"
                << 4 - n
                << ".png";
    makeGraphic<tank::Image>(graphicFile.str());
}

StarMap::StarMap(tank::Vectori topLeft, tank::Vectori bottomRight)
    : tank::Entity(topLeft)
{
    auto& rand = Universe::randEng;
    std::uniform_int_distribution<> x {topLeft.x, bottomRight.x},
                                    y {topLeft.y, bottomRight.y};

    for (int i = 0; i < numberOfStars; ++i) {
        stars_.emplace_back(new Star(tank::Vectori{x(rand),y(rand)}));
    }
}

void StarMap::draw(tank::Camera const& c) {
    for (auto& star : stars_) {
        star->draw(c);
    }
}
