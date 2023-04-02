#include "chip.hpp"
#include "FontManager.hpp"

chip::chip(const std::string& chip_name): m_chip_settings_ref(*chip_settings::get_instance()) {
    this->m_chip_name.setString(chip_name);
    this->m_chip_name.setFont(FontManager::get_instance()->get_font("Roboto-Regular.ttf"));

    for (int i = 0; i < 2; i++) {
        this->m_chip_input_pins.emplace_back();
        this->m_chip_input_pins[i].set_pin_type(0);
    }

    for (int i = 0; i < 1; i++) {
        this->m_chip_output_pins.emplace_back();
        this->m_chip_output_pins[i].set_pin_type(1);
    }

    this->m_chip_pin_count_input = 2;
    this->m_chip_pin_count_output = 1;

    //calculate size of the chip
    compute_shape();
}


// setters and getters
void chip::set_chip_pos(sf::Vector2f chip_pos) {
    this->m_chip_pos = chip_pos;
}

void chip::set_chip_size(sf::Vector2f chip_size) {
    this->m_chip_size = chip_size;
}

void chip::set_chip_color(sf::Color chip_color) {
    this->m_chip_color = chip_color;
}

void chip::set_chip_id(int chip_id) {
    this->m_chip_id = chip_id;
}

void chip::set_chip_type(int chip_type) {
    this->m_chip_type = chip_type;
}

sf::Vector2f chip::get_chip_pos() {
    return this->m_chip_pos;
}

sf::Vector2f chip::get_chip_size() {
    return this->m_chip_size;
}

sf::Color chip::get_chip_color() {
    return this->m_chip_color;
}

int chip::get_chip_id() {
    return this->m_chip_id;
}

int chip::get_chip_type() {
    return this->m_chip_type;
}

int chip::get_chip_pin_count_input() {
    return this->m_chip_pin_count_input;
}

int chip::get_chip_pin_count_output() {
    return this->m_chip_pin_count_output;
}

std::vector<pin>& chip::get_chip_input_pins() {
    return this->m_chip_input_pins;
}

std::vector<pin>& chip::get_chip_output_pins() {
    return this->m_chip_output_pins;
}


// other functions
void chip::compute_shape() {
    pin_settings& pin_settings_ref = *pin_settings::get_instance();

    float size_x; // size of the chip in x direction
    float size_y; // size of the chip in y direction

    int max_pin_count = std::max(this->m_chip_pin_count_input, this->m_chip_pin_count_output);
    size_y = (float) max_pin_count * pin_settings_ref.pin_size.x + ((float) max_pin_count + 1.0f) * pin_settings_ref.space_between_pins;
    size_x = this->m_chip_name.getGlobalBounds().width + 2 * this->m_chip_settings_ref.chip_text_padding + 2 * this->m_chip_settings_ref.chip_outline_thickness;
    this->m_chip_size = {size_x, size_y};

    this->m_chip_shape.setSize(this->m_chip_size);

    float spacing_x; // spacing between input pins
    float spacing_y; // spacing between output pins

    // calculate spacing between pins
    spacing_x = (this->m_chip_size.y - (float)this->m_chip_pin_count_input * pin_settings_ref.pin_size.x) / ((float)this->m_chip_pin_count_input + 1.0f);
    spacing_y = (this->m_chip_size.y - (float)this->m_chip_pin_count_output * pin_settings_ref.pin_size.x) / ((float)this->m_chip_pin_count_output + 1.0f);
    this->m_pin_spacing = {spacing_x, spacing_y};
}

void chip::draw(sf::RenderWindow& window) {
    //drawing chip
    this->m_chip_shape.setPosition(this->m_chip_pos);
    this->m_chip_shape.setOutlineColor(this->m_chip_settings_ref.chip_outline_color);
    this->m_chip_shape.setOutlineThickness(this->m_chip_settings_ref.chip_outline_thickness);
    this->m_chip_shape.setFillColor(this->m_chip_color);
    window.draw(this->m_chip_shape);

    //drawing pins
    pin_settings& pin_settings_ref = *pin_settings::get_instance();
    for (int i = 0; i < this->m_chip_pin_count_input; i++) {
        //calculating position of the ith input pin
        sf::Vector2f pin_pos = {
                this->m_chip_pos.x - pin_settings_ref.pin_size.x / 2.0f - pin_settings_ref.pin_outline_thickness / 2.0f,
                this->m_chip_pos.y + (float)i * pin_settings_ref.pin_size.y + (float)(i + 1) * m_pin_spacing.x
        };
        this->m_chip_input_pins[i].set_pin_pos(pin_pos);
        this->m_chip_input_pins[i].draw(window);
    }

    for (int i = 0; i < this->m_chip_pin_count_output; i++) {
        //calculating position of the ith output pin
        sf::Vector2f pin_pos = {
                this->m_chip_pos.x + this->m_chip_size.x - pin_settings_ref.pin_size.x / 2.0f - pin_settings_ref.pin_outline_thickness / 2.0f,
                this->m_chip_pos.y + (float)i * pin_settings_ref.pin_size.y + (float)(i + 1) * m_pin_spacing.y
        };
        this->m_chip_output_pins[i].set_pin_pos(pin_pos);
        this->m_chip_output_pins[i].draw(window);
    }

    //drawing chip name
    this->m_chip_name.setPosition({
                                          this->m_chip_pos.x + this->m_chip_size.x / 2.0f - this->m_chip_name.getGlobalBounds().width / 2.0f,
                                          this->m_chip_pos.y + this->m_chip_size.y / 2.0f - this->m_chip_name.getGlobalBounds().height
    });
    this->m_chip_name.setFillColor(this->m_chip_settings_ref.chip_text_color);
    window.draw(this->m_chip_name);
}