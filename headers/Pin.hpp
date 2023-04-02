#pragma once

#include <SFML/Graphics.hpp>

#include "pin_settings.hpp"

class Pin {
private:
    int m_type = 0; // 0 = input, 1 = output
    int m_id = 0;
    int m_state = 0;  // 0 = inactive, 1 = active
    sf::Vector2f m_pos = {0, 0};

    sf::RectangleShape m_shape;

    const pin_settings* m_settingsRef;  // reference to pin_settings

    /* data */
public:
    Pin();
    ~Pin() = default;

    void setType(int pin_type);
    void setId(int pin_id);
    void setState(int pin_state);
    void setPos(sf::Vector2f pin_pos);

    int getType() const;
    int getId() const;
    int getState() const;
    sf::Vector2f getPos() const;

    void draw(sf::RenderWindow& window);
};