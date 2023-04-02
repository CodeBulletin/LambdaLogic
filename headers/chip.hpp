#pragma once

#include <SFML/Graphics.hpp>

#include "pin.hpp"
#include "chip_settings.hpp"

class chip {
private:
    sf::Text m_chip_name;
    sf::RectangleShape m_chip_shape;
    sf::Vector2f m_chip_pos = {0, 0};
    sf::Vector2f m_chip_size = {0, 0};
    sf::Color m_chip_color;
    sf::Vector2f m_pin_spacing = {0, 0};

    int m_chip_id = 0;
    int m_chip_type = 0;  // 0 = input, 1 = output, 2 = logic, 3 = memory, 4 = custom
    int m_chip_pin_count_input = 0; // number of input pins
    int m_chip_pin_count_output = 0; // number of output pins

    std::vector<pin> m_chip_input_pins; // input pins
    std::vector<pin> m_chip_output_pins; // output pins

    const chip_settings& m_chip_settings_ref = *chip_settings::get_instance();  // reference to chip_settings


public:
    explicit chip(const std::string&);
    chip() = default;
    chip(const chip& other) : m_chip_name(other.m_chip_name), m_chip_shape(other.m_chip_shape),
        m_chip_pos(other.m_chip_pos), m_chip_size(other.m_chip_size), m_chip_color(other.m_chip_color),
        m_pin_spacing(other.m_pin_spacing), m_chip_id(other.m_chip_id), m_chip_type(other.m_chip_type),
        m_chip_pin_count_input(other.m_chip_pin_count_input), m_chip_pin_count_output(other.m_chip_pin_count_output),
        m_chip_input_pins(other.m_chip_input_pins), m_chip_output_pins(other.m_chip_output_pins) {}
    chip(chip&& other) noexcept : m_chip_name(std::move(other.m_chip_name)), m_chip_shape(std::move(other.m_chip_shape)) {
        m_chip_pos = other.m_chip_pos;
        m_chip_size = other.m_chip_size;
        m_chip_color = other.m_chip_color;
        m_pin_spacing = other.m_pin_spacing;
        m_chip_id = other.m_chip_id;
        m_chip_type = other.m_chip_type;
        m_chip_pin_count_input = other.m_chip_pin_count_input;
        m_chip_pin_count_output = other.m_chip_pin_count_output;
        m_chip_input_pins = std::move(other.m_chip_input_pins);
        m_chip_output_pins = std::move(other.m_chip_output_pins);
    }
    chip& operator=(const chip& other) {
        m_chip_name = other.m_chip_name;
        m_chip_shape = other.m_chip_shape;
        m_chip_pos = other.m_chip_pos;
        m_chip_size = other.m_chip_size;
        m_chip_color = other.m_chip_color;
        m_pin_spacing = other.m_pin_spacing;
        m_chip_id = other.m_chip_id;
        m_chip_type = other.m_chip_type;
        m_chip_pin_count_input = other.m_chip_pin_count_input;
        m_chip_pin_count_output = other.m_chip_pin_count_output;
        m_chip_input_pins = other.m_chip_input_pins;
        m_chip_output_pins = other.m_chip_output_pins;
        return *this;
    }
    chip& operator=(chip&& other) noexcept {
        m_chip_name = std::move(other.m_chip_name);
        m_chip_shape = std::move(other.m_chip_shape);
        m_chip_pos = other.m_chip_pos;
        m_chip_size = other.m_chip_size;
        m_chip_color = other.m_chip_color;
        m_pin_spacing = other.m_pin_spacing;
        m_chip_id = other.m_chip_id;
        m_chip_type = other.m_chip_type;
        m_chip_pin_count_input = other.m_chip_pin_count_input;
        m_chip_pin_count_output = other.m_chip_pin_count_output;
        m_chip_input_pins = std::move(other.m_chip_input_pins);
        m_chip_output_pins = std::move(other.m_chip_output_pins);
        return *this;
    }
    ~chip() = default;

    // setters and getters
    virtual void set_chip_pos(sf::Vector2f chip_pos);
    virtual void set_chip_size(sf::Vector2f chip_size);
    virtual void set_chip_color(sf::Color chip_color);
    virtual void set_chip_id(int chip_id);
    virtual void set_chip_type(int chip_type);
    // virtual void set_chip_pin_count_input(int m_chip_pin_count_input);
    // virtual void set_chip_pin_count_output(int m_chip_pin_count_output);
    // virtual void set_chip_input_pins(std::vector<pin> m_chip_input_pins);
    // virtual void set_chip_output_pins(std::vector<pin> m_chip_output_pins);

    virtual sf::Vector2f get_chip_pos();
    virtual sf::Vector2f get_chip_size();
    virtual sf::Color get_chip_color();
    virtual int get_chip_id();
    virtual int get_chip_type();
    virtual int get_chip_pin_count_input();
    virtual int get_chip_pin_count_output();
    virtual std::vector<pin>& get_chip_input_pins();
    virtual std::vector<pin>& get_chip_output_pins();

    // other functions
    virtual void compute_shape();
    virtual void draw(sf::RenderWindow& window);

    // pure virtual functions
    // virtual void set_pins() = 0;
    // virtual void compute() = 0;
};