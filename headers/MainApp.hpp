#pragma once

#include "App.hpp"
#include "FontManager.hpp"
#include "Simulation.hpp"
#include "Nand.hpp"

class MainApp : public App {
private:
    sf::View m_view;


	pin_settings& pin_setting = *pin_settings::get_instance();
	chip_settings& chip_setting = *chip_settings::get_instance();

public:
    Simulation sim;
    bool place_chip = false;
    bool is_mouse_pressed = false;

    int selected_pin_id = -1;

public:
	explicit MainApp(sf::Vector3<uint32_t> vec = {500u, 500u, 32u}) {
		m_settings.antialiasingLevel = 8;
		create_window("LambdaLogic", sf::Style::Default, vec);
		FontManager::get_instance()->get_font("Roboto-Regular.ttf");
        m_view = sf::View(sf::FloatRect({0.0f, 0.0f}, {(float)m_width, (float)m_height}));
        m_window.setView(m_view);
	}

	void setup() override {
		pin_setting.pin_size = {16, 16};
		pin_setting.space_between_pins = 16;
		pin_setting.pin_outline_color = sf::Color::White;
		pin_setting.pin_outline_thickness = 2;
		pin_setting.pin_active_fill_color = sf::Color::Green;
		pin_setting.pin_inactive_fill_color = sf::Color::Red;
		pin_setting.pin_active_fill_color_hover = sf::Color::Green;
		pin_setting.pin_inactive_fill_color_hover = sf::Color::Red;
		chip_setting.pin_distance = 10;
		chip_setting.chip_outline_thickness = 2;
		chip_setting.chip_text_color = sf::Color::White;
		chip_setting.chip_text_padding = 30;
		chip_setting.chip_outline_color = sf::Color::White;
		setupGUI();
	}

	static void setupGUI() {
		ImGuiStyle& style = ImGui::GetStyle();
		style.WindowRounding = 5.0f;
		
		sf::Color white = sfh::color::hexToRGBA(0xFFFFFFFF);
		sf::Color black = sfh::color::hexToRGBA(0x000000FF);
		sf::Color transparent = sfh::color::hexToRGBA(0x00000000);

		sf::Color Base = sfh::color::hexToRGBA(0x121212FF);
		sf::Color primary = sfh::color::hexToRGBA(0xBB86FCFF);

		sf::Color dp01 = sfh::color::lerp(Base, white, 0.05f);
		sf::Color dp02 = sfh::color::lerp(Base, white, 0.07f);
		sf::Color dp03 = sfh::color::lerp(Base, white, 0.08f);
		sf::Color dp06 = sfh::color::lerp(Base, white, 0.11f);
		sf::Color dp12 = sfh::color::lerp(Base, white, 0.14f);

		sf::Color primary_variant = sfh::color::lerp(primary, black, 0.25f);


		// ImColor A = sfh::color::hexToRGBA<ImColor>(0x2C2F3AFF);
		// style.FrameRounding = 5.0f;
		style.Colors[ImGuiCol_MenuBarBg] = dp06;
		style.Colors[ImGuiCol_Border] = transparent;
		style.Colors[ImGuiCol_PopupBg] = dp12;

		style.Colors[ImGuiCol_HeaderHovered] = primary;
		style.Colors[ImGuiCol_Header] = primary_variant;

		// style.Colors[ImGuiCol_Men] = sfh::color::hexToRGBA<ImColor>(0x21222DFF);
		style.FramePadding = {5.0f, 5.0f};

	}

	void loop() override {
		m_window.clear(sf::Color(0x121212ff));
        sim.run();
        sim.draw(m_window);
	}

	void gui() override {
		if (ImGui::BeginMainMenuBar()) {
			if (ImGui::BeginMenu("File")) {
				ImGui::EndMenu();
			}
			ImGui::EndMainMenuBar();
		}
	}

    sf::RenderWindow& getWindow(){
		return this->m_window;
	}

    sf::Vector2f old_pos;

    void mouseButtonPressedEvent() override {
        if (!ImGui::GetIO().WantCaptureMouse) {
            sf::Vector2f mouse_pos = m_window.mapPixelToCoords({m_event.mouseButton.x, m_event.mouseButton.y});
            if (place_chip) {
                if (m_event.mouseButton.button == sf::Mouse::Left) {
                    Nand *a = new Nand();
                    a->setPos(mouse_pos);
                    sim.addChip(a);
                }
            } else {
                Object *obj = sim.clicked(mouse_pos);
                if (m_event.mouseButton.button == sf::Mouse::Left) {
                    is_mouse_pressed = true;
                    old_pos = m_window.mapPixelToCoords({m_event.mouseButton.x, m_event.mouseButton.y});
                    if (obj == nullptr) {
                        selected_pin_id = -1;
                        return;
                    }
                    if (obj->getType() == "Pin") {
                        std::cout << "Pin clicked" << std::endl;
                        Pin *pin = (Pin *) obj;
                        if (selected_pin_id == -1) {
                            selected_pin_id = pin->getId();
                        } else {
                            sim.createConnection(selected_pin_id, pin->getId());
                            std::cout << "Connection created" << std::endl;
                            selected_pin_id = -1;
                        }
                    } else {
                        selected_pin_id = -1;
                    }
                }
                else if (m_event.mouseButton.button == sf::Mouse::Right) {
                    selected_pin_id = -1;
                    if (obj == nullptr) {
                        return;
                    }
                    if (obj->getType() == "Pin") {
                        Pin *pin = (Pin *) obj;
                        pin->setState(!pin->getState());
                    }
                } else if (m_event.mouseButton.button == sf::Mouse::Middle) {
                    selected_pin_id = -1;
                    if (obj == nullptr) {
                        return;
                    }
                    if (obj->getType() == "Gate") {
                        Gate *gate = (Gate *) obj;
                        sim.removeChip(gate->getId());
                    }
                }
            }
        }
    }

    void mouseButtonReleasedEvent() override {
        if (!ImGui::GetIO().WantCaptureMouse) {
            if (m_event.mouseButton.button == sf::Mouse::Left) {
                is_mouse_pressed = false;
            }
        }
    }

    void mouseMovedEvent() override {
        if (!ImGui::GetIO().WantCaptureMouse) {
            if (is_mouse_pressed) {
                sf::Vector2f new_pos = m_window.mapPixelToCoords({m_event.mouseMove.x, m_event.mouseMove.y});
                sf::Vector2f delta = new_pos - old_pos;
                m_view.move(-delta);
                m_window.setView(m_view);
            }
        }
    }

    void mouseWheelScrolledEvent() override {
        if (!ImGui::GetIO().WantCaptureMouse) {
            if (m_event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                if (m_event.mouseWheelScroll.delta > 0) {
                    m_view.zoom(0.9f);
                } else {
                    m_view.zoom(1.1f);
                }
                m_window.setView(m_view);
            }
        }
    }

    void keyReleasedEvent() override {
        if (m_event.key.code == sf::Keyboard::Escape) {
            place_chip = !place_chip;
        }
    }

    void resizeEvent() override{
        m_width = m_event.size.width;
        m_height = m_event.size.height;
        m_view.setSize({(float)m_width, (float)m_height});
        m_view.setCenter({(float)m_width/2, (float)m_height/2});
        m_window.setView(m_view);
    }
};
