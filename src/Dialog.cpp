#include "Dialog.hpp"

tank::Font Dialog::font;

Dialog::Dialog(tank::Vectorf pos, std::string text) : Entity(pos)
{
    font.loadFromFile("assets/fonts/PlanetFont.ttf");
    text_ = makeGraphic<tank::Text>(font);
    text_->setText(text);
    text_->setColor(tank::Color::White);
    text_->setScale(1.0/3);
}
