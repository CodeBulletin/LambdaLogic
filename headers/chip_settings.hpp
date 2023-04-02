#pragma once

#include <SFML/Graphics.hpp>

// Singleton class

class chip_settings {
public:
    sf::Color chip_outline_color;
    float chip_outline_thickness;
    sf::Color chip_text_color;
    float chip_text_padding;
    float pin_distance;


    static chip_settings* instance;
    static chip_settings* get_instance() {
        if (instance == nullptr) {
            instance = new chip_settings();
        }
        return instance;
    }
};