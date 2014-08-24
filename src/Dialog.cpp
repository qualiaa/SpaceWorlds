#include "Dialog.hpp"

tank::Font Dialog::font;

Dialog::Dialog(tank::Vectorf pos, std::string text) : Entity(pos)
{
    font.loadFromFile("/Users/david/Library/Fonts/Monaco+for+Powerline.otf");
    text_ = makeGraphic<tank::Text>(font);
    text_->setText(text);
    text_->setColor(tank::Color::White);
}
