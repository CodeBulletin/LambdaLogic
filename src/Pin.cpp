#include "Pin.hpp"

Pin::Pin(): Object("Pin"), m_settingsRef(pin_settings::get_instance()) {
    this->m_shape.setSize(this->m_settingsRef->pin_size);
    this->m_shape.setOutlineColor(this->m_settingsRef->pin_outline_color);
    this->m_shape.setOutlineThickness(this->m_settingsRef->pin_outline_thickness);
}

void Pin::setType(int pin_type) {
    this->m_type = pin_type;
}

void Pin::setState(int pin_state) {
    this->m_state = pin_state;
}

void Pin::setPos(sf::Vector2f pin_pos) {
    this->m_pos = pin_pos;
    this->m_shape.setPosition(this->m_pos);
}

int Pin::getPinType() const {
    return this->m_type;
}

int Pin::getState() const {
    return this->m_state;
}

sf::Vector2f Pin::getPos() const {
    return this->m_pos;
}

void Pin::draw(sf::RenderWindow& window) {
    if (this->m_state == 0) {
        this->m_shape.setFillColor(this->m_settingsRef->pin_inactive_fill_color);
    } else {
        this->m_shape.setFillColor(this->m_settingsRef->pin_active_fill_color);
    }
    window.draw(this->m_shape);
}

void Pin::addConnection(Connection* connection) {
    this->m_connection = connection;
}

const sf::RectangleShape &Pin::getRect() const {
    return this->m_shape;
}

// Path: src/Pin.cpp