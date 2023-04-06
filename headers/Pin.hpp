#pragma once

#include <SFML/Graphics.hpp>

#include "Object.hpp"
#include "pin_settings.hpp"

#include "Connection.hpp"

enum PinType {
    INPUT = 0,
    OUTPUT = 1
};

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
    std::vector<Connection*> getConnections() const;

    void draw(sf::RenderWindow& window);
    void addConnection(Connection* connection);
    void removeConnection(Connection* connection);

    void addState(int state);
    void computeState();

private:
    int m_type = PinType::INPUT; // 0 = input, 1 = output
    int m_state = 0;  // 0 = inactive, 1 = active

    sf::Vector2f m_pos = {0, 0};  // position of the pin
    sf::RectangleShape m_shape;  // shape of the pin

    const pin_settings* m_settingsRef;  // reference to pin_settings

    std::vector<Connection*> m_connections;  // vector of pointer to connection

    std::vector<int> m_states;  // vector of states
};