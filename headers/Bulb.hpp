#pragma once

#include "Gate.hpp"

class Bulb : public Gate {
    sf::CircleShape m_shape;
    sf::RectangleShape m_line;

public:
    Bulb() : Gate("Bulb") {
        this->m_gateType = GateType::OUTPUT_G;

        Pin pin;
        pin.setType(0);
        this->m_InputPins.push_back(pin);

        this->m_inputPinCount = 1;

        compute_shape();
    }

    void compute() override {
        this->m_shape.setFillColor(this->m_InputPins[0].getState() ? sf::Color::Yellow : sf::Color::Black);
    }
    void compute_shape() override {
        pin_settings& pin_settings_ref = *pin_settings::get_instance();

        this->m_size = {
            (float)60,
            (float)0
        };

        this->m_shape.setRadius(this->m_size.x / 2.0f);
        this->m_shape.setOutlineThickness(4);

        float spacing_x = (this->m_size.x - pin_settings_ref.pin_size.x) / (2.0f);
        this->m_pinSpacing = {spacing_x, 0.0f};

        this->m_line.setSize({(float)40, (float)4});
    }
    void draw(sf::RenderWindow& window) override {
        pin_settings& pin_settings_ref = *pin_settings::get_instance();

        sf::Vector2f pin_pos = {
            this->m_pos.x + pin_settings_ref.pin_size.x / 2.0f + pin_settings_ref.pin_outline_thickness / 2.0f - 40,
            this->m_pos.y + this->m_pinSpacing.x
        };

        this->m_line.setPosition({
            pin_pos.x,
            pin_pos.y + pin_settings_ref.pin_size.y / 2.0f - 2.0f
        });

        window.draw(this->m_line);

        this->m_shape.setPosition(this->m_pos);

        window.draw(this->m_shape);

        this->m_InputPins[0].setPos(pin_pos);
        this->m_InputPins[0].draw(window);
    }

    sf::FloatRect getBounds() const override {
        sf::FloatRect fr(this->m_shape.getPosition(), {2 * m_shape.getRadius(), 2 * m_shape.getRadius()});
        return fr;
    }
};