#pragma once

#include <SFML/Graphics.hpp>

class FontManager {
public:

    // find font in map, if not found, load it from file
    sf::Font& get_font(const std::string& font_name) {
        if (m_fonts.find(font_name) == m_fonts.end()) {
            if (!m_fonts[font_name].loadFromFile("Assets/Fonts/" + font_name)) {
                return m_fonts["arial.ttf"];
            }
        }
        return m_fonts[font_name];
    }
    
    static FontManager* instance;
    static FontManager* get_instance() {
        if (instance == nullptr) {
            instance = new FontManager();
        }
        return instance;
    }

private:
    std::unordered_map<std::string, sf::Font> m_fonts;
};
