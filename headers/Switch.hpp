#pragma once

#include "Gate.hpp"

class Switch : public Gate {
private:
    int m_state = 0;
    sf::RectangleShape m_line;

public:
    Switch(/* args */) : Gate("Switch") {
        this->m_gateType = GateType::INPUT_G;

        Pin pin;
        pin.setType(1);
        this->m_outputPins.push_back(pin);

        this->m_outputPinCount = 1;

        compute_shape();
    }

    void onClick() override {
        this->m_state = !this->m_state;
    }

    void compute() override {
        this->m_outputPins[0].setState(this->m_state);
    }

    void compute_shape() override {
        pin_settings& pin_settings_ref = *pin_settings::get_instance();
        // this->m_name.setPosition({
        //     this->m_pos.x + this->m_size.x / 2 - this->m_name.getGlobalBounds().width / 2,
        //     this->m_pos.y + this->m_size.y / 2 - this->m_name.getGlobalBounds().height / 2
        // });

        this->m_size = {
            (float)60,
            (float)60
        };

        this->m_shape.setSize(this->m_size);
        this->m_shape.setOutlineThickness(4);

        float spacing_y = (this->m_size.y - pin_settings_ref.pin_size.x) / (2.0f);
        this->m_pinSpacing = {0.0f, spacing_y};

        this->m_line.setSize({(float)40, (float)4});
    }

    void draw(sf::RenderWindow& window) override {
        pin_settings& pin_settings_ref = *pin_settings::get_instance();

        sf::Vector2f pin_pos = {
            this->m_pos.x + this->m_size.x - pin_settings_ref.pin_size.x / 2.0f - pin_settings_ref.pin_outline_thickness / 2.0f + 40,
            this->m_pos.y + m_pinSpacing.y
        };

        this->m_line.setPosition({
            pin_pos.x - 40,
            pin_pos.y + pin_settings_ref.pin_size.y / 2.0f - 2.0f
        });

        window.draw(this->m_line);

        if (this->m_state == 0) {
            this->m_shape.setFillColor(pin_settings_ref.pin_inactive_fill_color);
        } else {
            this->m_shape.setFillColor(pin_settings_ref.pin_active_fill_color);
        }

        this->m_shape.setPosition(this->m_pos);

        window.draw(this->m_shape);
        // window.draw(this->m_name);

        this->m_outputPins[0].setPos(pin_pos);
        this->m_outputPins[0].draw(window);
    }
};