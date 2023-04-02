#pragma once

#include <SFML/Graphics.hpp>


// Singleton class

struct pin_settings {
    sf::Vector2f pin_size;
    float space_between_pins{};
    sf::Color pin_outline_color;
    float pin_outline_thickness{};
    sf::Color pin_active_fill_color;
    sf::Color pin_inactive_fill_color;
    sf::Color pin_active_fill_color_hover;
    sf::Color pin_inactive_fill_color_hover;

    static pin_settings* instance;
    static pin_settings* get_instance() {
        if (instance == nullptr) {
            instance = new pin_settings();
        }
        return instance;
    }
};