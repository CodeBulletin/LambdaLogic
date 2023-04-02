#pragma once

#include <SFML/Graphics.hpp>

class FontManager {
private:
    std::unordered_map<std::string, sf::Font> fonts;
public:
    sf::Font& get_font(const std::string& font_name) {
        if (fonts.find(font_name) == fonts.end()) {
            if (!fonts[font_name].loadFromFile("Assets/Fonts/" + font_name)) {
                return fonts["arial.ttf"];
            }
        }
        return fonts[font_name];
    }
    
    static FontManager* instance;
    static FontManager* get_instance() {
        if (instance == nullptr) {
            instance = new FontManager();
        }
        return instance;
    }
};
