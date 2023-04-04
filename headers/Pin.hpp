#pragma once

#include <SFML/Graphics.hpp>

#include "Object.hpp"
#include "pin_settings.hpp"

#include "Connection.hpp"

class Pin : public Object{
public:
    Pin();
    ~Pin() = default;

    void setType(int pin_type);
    void setState(int pin_state);
    void setPos(sf::Vector2f pin_pos);

    int getPinType() const;
    int getState() const;
    sf::Vector2f getPos() const;
    const sf::RectangleShape& getRect() const;

    void draw(sf::RenderWindow& window);
    void addConnection(Connection* connection);

private:
    int m_type = 0; // 0 = input, 1 = output
    int m_state = 0;  // 0 = inactive, 1 = active

    sf::Vector2f m_pos = {0, 0};  // position of the pin
    sf::RectangleShape m_shape;  // shape of the pin

    const pin_settings* m_settingsRef;  // reference to pin_settings

    Connection* m_connection = nullptr;  // pointer to connection
};