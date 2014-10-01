#pragma once
#include "Dialog.hpp"

class HudDialog : public Dialog
{
    tank::Camera c;

public:
    HudDialog(tank::Vectorf pos, std::string text) : Dialog{pos, text}
    {
        c.setOrigin({0,0});
        c.setScale(2);
        setLayer(101);
    }

    void draw(const tank::Camera& cam) override
    {
        Entity::draw(c);
    }

};
