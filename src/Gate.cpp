#include "Gate.hpp"
#include "FontManager.hpp"

Gate::Gate(const std::string& chip_name): Object("Gate"), m_gate_settings_ref(chip_settings::get_instance()) {
    this->m_name.setString(chip_name);
    this->m_name.setFont(FontManager::get_instance()->get_font("Roboto-Regular.ttf"));

    //calculate size of the Gate
    compute_shape();
}

Gate::~Gate() {
}


// setters and getters
void Gate::setPos(sf::Vector2f chip_pos) {
    this->m_pos = chip_pos;
}

void Gate::setSize(sf::Vector2f chip_size) {
    this->m_size = chip_size;
}

void Gate::setColor(sf::Color chip_color) {
    this->m_color = chip_color;
}

void Gate::setGateType(int chip_type) {
    this->m_gateType;
}

sf::Vector2f Gate::getPos() const {
    return this->m_pos;
}

sf::Vector2f Gate::getSize() const {
    return this->m_size;
}

sf::Color Gate::getColor() const {
    return this->m_color;
}

int Gate::getInputPinCount() const {
    return this->m_inputPinCount;
}

int Gate::getOutputPinCount() const {
    return this->m_outputPinCount;
}

std::vector<Pin>& Gate::getInputPins() {
    return this->m_InputPins;
}

std::vector<Pin>& Gate::getOutputPins() {
    return this->m_outputPins;
}

std::string Gate::getName() const {
    return this->m_name.getString();
}

int Gate::getGateType() const {
    return this->m_gateType;
}

// other functions
void Gate::compute_shape() {
    pin_settings& pin_settings_ref = *pin_settings::get_instance();

    float size_x; // size of the Gate in x direction
    float size_y; // size of the Gate in y direction

    int max_pin_count = std::max(this->m_inputPinCount, this->m_outputPinCount);
    size_y = (float) max_pin_count * pin_settings_ref.pin_size.x + ((float) max_pin_count + 1.0f) * pin_settings_ref.space_between_pins;
    size_x = this->m_name.getGlobalBounds().width + 2 * this->m_gate_settings_ref->chip_text_padding + 2 * this->m_gate_settings_ref->chip_outline_thickness;
    this->m_size = {size_x, size_y};

    this->m_shape.setSize(this->m_size);

    float spacing_x; // spacing between input pins
    float spacing_y; // spacing between output pins

    // calculate spacing between pins
    spacing_x = (this->m_size.y - (float)this->m_inputPinCount * pin_settings_ref.pin_size.x) / ((float)this->m_inputPinCount + 1.0f);
    spacing_y = (this->m_size.y - (float)this->m_outputPinCount * pin_settings_ref.pin_size.x) / ((float)this->m_outputPinCount + 1.0f);
    this->m_pinSpacing = {spacing_x, spacing_y};
}

void Gate::draw(sf::RenderWindow& window) {
    //drawing Gate
    this->m_shape.setPosition(this->m_pos);
    this->m_shape.setOutlineColor(this->m_gate_settings_ref->chip_outline_color);
    this->m_shape.setOutlineThickness(this->m_gate_settings_ref->chip_outline_thickness);
    this->m_shape.setFillColor(this->m_color);
    window.draw(this->m_shape);

    //drawing pins
    pin_settings& pin_settings_ref = *pin_settings::get_instance();
    for (int i = 0; i < this->m_inputPinCount; i++) {
        //calculating position of the ith input Pin
        sf::Vector2f pin_pos = {
                this->m_pos.x - pin_settings_ref.pin_size.x / 2.0f - pin_settings_ref.pin_outline_thickness / 2.0f,
                this->m_pos.y + (float)i * pin_settings_ref.pin_size.y + (float)(i + 1) * m_pinSpacing.x
        };
        this->m_InputPins[i].setPos(pin_pos);
        this->m_InputPins[i].draw(window);
    }

    for (int i = 0; i < this->m_outputPinCount; i++) {
        //calculating position of the ith output Pin
        sf::Vector2f pin_pos = {
                this->m_pos.x + this->m_size.x - pin_settings_ref.pin_size.x / 2.0f - pin_settings_ref.pin_outline_thickness / 2.0f,
                this->m_pos.y + (float)i * pin_settings_ref.pin_size.y + (float)(i + 1) * m_pinSpacing.y
        };
        this->m_outputPins[i].setPos(pin_pos);
        this->m_outputPins[i].draw(window);
    }

    //drawing Gate name
    this->m_name.setPosition({
        this->m_pos.x + this->m_size.x / 2.0f - this->m_name.getGlobalBounds().width / 2.0f,
        this->m_pos.y + this->m_size.y / 2.0f - this->m_name.getGlobalBounds().height
    });
    this->m_name.setFillColor(this->m_gate_settings_ref->chip_text_color);
    window.draw(this->m_name);
}

const sf::RectangleShape &Gate::getRect() const {
    return m_shape;
}
