#include "Pin.hpp"

Pin::Pin(): m_settingsRef(pin_settings::get_instance()) {
    this->m_shape.setSize(this->m_settingsRef->pin_size);
    this->m_shape.setOutlineColor(this->m_settingsRef->pin_outline_color);
    this->m_shape.setOutlineThickness(this->m_settingsRef->pin_outline_thickness);
}

void Pin::setType(int pin_type) {
    this->m_type = pin_type;
}

void Pin::setId(int pin_id) {
    this->m_id = pin_id;
}

void Pin::setState(int pin_state) {
    this->m_state = pin_state;
}

void Pin::setPos(sf::Vector2f pin_pos) {
    this->m_pos = pin_pos;
    this->m_shape.setPosition(this->m_pos);
}

int Pin::getType() const {
    return this->m_type;
}

int Pin::getId() const {
    return this->m_id;
}

int Pin::getState() const {
    return this->m_state;
}

sf::Vector2f Pin::getPos() const {
    return this->m_pos;
}

void Pin::draw(sf::RenderWindow& window) {
    // if (this->m_state == 0) {
    //     this->m_shape.setFillColor(this->m_settingsRef->pin_inactive_fill_color);
    // } else {
    //     this->m_shape.setFillColor(this->m_settingsRef->pin_active_fill_color);
    // }
    this->m_shape.setFillColor(sf::Color::Red);
    window.draw(this->m_shape);
}

// Path: src/Pin.cpp