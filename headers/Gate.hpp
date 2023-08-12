#pragma once

#include <SFML/Graphics.hpp>

#include "Object.hpp"
#include "Pin.hpp"
#include "chip_settings.hpp"

#include "FontManager.hpp"


enum GateType {
    INPUT_G = 0,
    OUTPUT_G = 1,
    LOGIC = 2,
    MEMORY = 3,
    CUSTOM = 4
};

class Gate : public Object {
public:
    explicit Gate(const std::string&);
    Gate() = default;

    virtual ~Gate();
    void operator delete (void* ptr) {
        free(ptr);
    }

    // setters and getters
    virtual void setPos(sf::Vector2f chip_pos);
    virtual void setSize(sf::Vector2f chip_size);
    virtual void setColor(sf::Color chip_color);
    virtual void setGateType(int chip_type);

    virtual sf::Vector2f getPos() const;
    virtual sf::Vector2f getSize() const;
    virtual sf::Color getColor() const;
    virtual int getInputPinCount() const;
    virtual int getOutputPinCount() const;
    virtual std::vector<Pin>& getInputPins();
    virtual std::vector<Pin>& getOutputPins();
    virtual std::string getName() const;
    virtual sf::FloatRect getBounds() const;
    virtual int getGateType() const;

    // other functions
    virtual void compute_shape();
    virtual void draw(sf::RenderWindow& window);
    virtual void onClick() {}

    // pure virtual functions
    virtual void compute() = 0;

protected:
    sf::Text m_name = sf::Text(FontManager::get_instance()->get_font("Roboto-Regular.ttf"), "", 30);  // name of the chip
    sf::RectangleShape m_shape;  // shape of the chip
    sf::Vector2f m_pos = {0, 0};  // position of the chip
    sf::Vector2f m_size = {0, 0};  // size of the chip
    sf::Color m_color;  // color of the chip
    sf::Vector2f m_pinSpacing = {0, 0};  // spacing between pins

    int m_gateType = 0;  // 0 = input, 1 = output, 2 = logic, 3 = memory, 4 = custom
    int m_inputPinCount = 0;  // number of input pins
    int m_outputPinCount = 0;  // number of output pins

    std::vector<Pin> m_InputPins;  // input pins
    std::vector<Pin> m_outputPins;  // output pins

    const chip_settings* m_gate_settings_ref = chip_settings::get_instance();  // reference to chip_settings
};