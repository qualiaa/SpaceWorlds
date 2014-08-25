#include "Dialog.hpp"

tank::Font Dialog::font;
bool Dialog::font_loaded = false;

Dialog::Dialog(tank::Vectorf pos, std::string text) : Entity(pos)
{
    if (!font_loaded) {
        font.loadFromFile("assets/fonts/PlanetFont.ttf");
        font_loaded = true;
    }
    text_ = makeGraphic<tank::Text>(font, 30, text);
    text_->setColor(tank::Color::White);
    text_->setScale(1.0/3);
}
