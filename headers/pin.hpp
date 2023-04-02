#pragma once

#include <SFML/Graphics.hpp>

#include "pin_settings.hpp"

class pin {
private:
    int m_pin_type = 0; // 0 = input, 1 = output
    int m_pin_id = 0;
    int m_pin_state = 0;  // 0 = inactive, 1 = active
    sf::Vector2f m_pin_pos = {0, 0};

    sf::RectangleShape m_pin_shape;

    const pin_settings* m_pin_settings_ref;  // reference to pin_settings

    /* data */
public:
    pin();
    ~pin() = default;

    void set_pin_type(int pin_type);
    void set_pin_id(int pin_id);
    void set_pin_state(int pin_state);
    void set_pin_pos(sf::Vector2f pin_pos);

    int get_pin_type() const;
    int get_pin_id() const;
    int get_pin_state() const;
    sf::Vector2f get_pin_pos() const;

    void draw(sf::RenderWindow& window);
};