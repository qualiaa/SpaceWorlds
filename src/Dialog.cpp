#include "Dialog.hpp"
#include <Tank/Utility/Resources.hpp>

tank::Font Dialog::font;
bool Dialog::font_loaded = false;

Dialog::Dialog(tank::Vectorf pos, std::string text) : Entity(pos)
{
    using res = tank::Resources;
    auto& font = res::get<tank::Font>("assets/fonts/PlanetFont.ttf");
    text_ = makeGraphic<tank::Text>(font, 30, text);
    text_->setColor(tank::Color::White);
    text_->setScale(1.0/3);
}
