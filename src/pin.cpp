#include "pin.hpp"

pin::pin(): m_pin_settings_ref(pin_settings::get_instance()) {
    this->m_pin_shape.setSize(this->m_pin_settings_ref->pin_size);
    this->m_pin_shape.setOutlineColor(this->m_pin_settings_ref->pin_outline_color);
    this->m_pin_shape.setOutlineThickness(this->m_pin_settings_ref->pin_outline_thickness);
}

void pin::set_pin_type(int pin_type) {
    this->m_pin_type = pin_type;
}

void pin::set_pin_id(int pin_id) {
    this->m_pin_id = pin_id;
}

void pin::set_pin_state(int pin_state) {
    this->m_pin_state = pin_state;
}

void pin::set_pin_pos(sf::Vector2f pin_pos) {
    this->m_pin_pos = pin_pos;
    this->m_pin_shape.setPosition(this->m_pin_pos);
}

int pin::get_pin_type() const {
    return this->m_pin_type;
}

int pin::get_pin_id() const {
    return this->m_pin_id;
}

int pin::get_pin_state() const {
    return this->m_pin_state;
}

sf::Vector2f pin::get_pin_pos() const {
    return this->m_pin_pos;
}

void pin::draw(sf::RenderWindow& window) {
    // if (this->m_pin_state == 0) {
    //     this->m_pin_shape.setFillColor(this->m_pin_settings_ref->pin_inactive_fill_color);
    // } else {
    //     this->m_pin_shape.setFillColor(this->m_pin_settings_ref->pin_active_fill_color);
    // }
    this->m_pin_shape.setFillColor(sf::Color::Red);
    window.draw(this->m_pin_shape);
}

// Path: src/pin.cpp