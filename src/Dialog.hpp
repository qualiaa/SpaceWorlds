#pragma once
#include <Tank/System/Entity.hpp>
#include <Tank/Graphics/Font.hpp>
#include <Tank/Graphics/Text.hpp>

class Dialog : public tank::Entity
{
    static tank::Font font;
    tank::observing_ptr<tank::Text> text_;
    static bool font_loaded;
    
public:
    Dialog(tank::Vectorf pos, std::string text);
    
    void setText(std::string text) {
        text_->setText(text);
    }
    
    std::string getText() {
        return text_->getText();
    }
    
    void setVisible(bool visible) {text_->setVisible(visible);}
};