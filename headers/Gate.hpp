#pragma once

#include <SFML/Graphics.hpp>

#include "Pin.hpp"
#include "chip_settings.hpp"

class Gate {
private:
    sf::Text m_name;
    sf::RectangleShape m_shape;
    sf::Vector2f m_pos = {0, 0};
    sf::Vector2f m_size = {0, 0};
    sf::Color m_color;
    sf::Vector2f m_pinSpacing = {0, 0};

    int m_id = 0;
    int m_type = 0;  // 0 = input, 1 = output, 2 = logic, 3 = memory, 4 = custom
    int m_inputPinCount = 0; // number of input pins
    int m_outputPinCount = 0; // number of output pins

    std::vector<Pin> m_InputPins; // input pins
    std::vector<Pin> m_outputPins; // output pins

    const chip_settings& m_gate_settings_ref = *chip_settings::get_instance();  // reference to chip_settings


public:
    explicit Gate(const std::string&);
    Gate() = default;
    Gate(const Gate& other) : m_name(other.m_name), m_shape(other.m_shape),
                              m_pos(other.m_pos), m_size(other.m_size), m_color(other.m_color),
                              m_pinSpacing(other.m_pinSpacing), m_id(other.m_id), m_type(other.m_type),
                              m_inputPinCount(other.m_inputPinCount), m_outputPinCount(other.m_outputPinCount),
                              m_InputPins(other.m_InputPins), m_outputPins(other.m_outputPins) {}
    Gate(Gate&& other) noexcept : m_name(std::move(other.m_name)), m_shape(std::move(other.m_shape)) {
        m_pos = other.m_pos;
        m_size = other.m_size;
        m_color = other.m_color;
        m_pinSpacing = other.m_pinSpacing;
        m_id = other.m_id;
        m_type = other.m_type;
        m_inputPinCount = other.m_inputPinCount;
        m_outputPinCount = other.m_outputPinCount;
        m_InputPins = std::move(other.m_InputPins);
        m_outputPins = std::move(other.m_outputPins);
    }
    Gate& operator=(const Gate& other) {
        m_name = other.m_name;
        m_shape = other.m_shape;
        m_pos = other.m_pos;
        m_size = other.m_size;
        m_color = other.m_color;
        m_pinSpacing = other.m_pinSpacing;
        m_id = other.m_id;
        m_type = other.m_type;
        m_inputPinCount = other.m_inputPinCount;
        m_outputPinCount = other.m_outputPinCount;
        m_InputPins = other.m_InputPins;
        m_outputPins = other.m_outputPins;
        return *this;
    }
    Gate& operator=(Gate&& other) noexcept {
        m_name = std::move(other.m_name);
        m_shape = std::move(other.m_shape);
        m_pos = other.m_pos;
        m_size = other.m_size;
        m_color = other.m_color;
        m_pinSpacing = other.m_pinSpacing;
        m_id = other.m_id;
        m_type = other.m_type;
        m_inputPinCount = other.m_inputPinCount;
        m_outputPinCount = other.m_outputPinCount;
        m_InputPins = std::move(other.m_InputPins);
        m_outputPins = std::move(other.m_outputPins);
        return *this;
    }
    ~Gate() = default;

    // setters and getters
    virtual void setPos(sf::Vector2f chip_pos);
    virtual void setSize(sf::Vector2f chip_size);
    virtual void setColor(sf::Color chip_color);
    virtual void setId(int chip_id);
    virtual void setType(int chip_type);

    virtual sf::Vector2f getPos();
    virtual sf::Vector2f getSize();
    virtual sf::Color getColor();
    virtual int getId();
    virtual int getType();
    virtual int getInputPinCount();
    virtual int getOutputPinCount();
    virtual std::vector<Pin>& getInputPins();
    virtual std::vector<Pin>& getOutputPins();

    // other functions
    virtual void compute_shape();
    virtual void draw(sf::RenderWindow& window);

    // pure virtual functions
    // virtual void set_pins() = 0;
    // virtual void compute() = 0;
};