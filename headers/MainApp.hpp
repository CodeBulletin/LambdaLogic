#pragma once

#include "App.hpp"
#include "chip.hpp"
#include "FontManager.hpp"

class MainApp : public App {
private:
	pin_settings& pin_setting = *pin_settings::get_instance();
	chip_settings& chip_setting = *chip_settings::get_instance();

public:
	explicit MainApp(sf::Vector3<uint32_t> vec = {500u, 500u, 32u}) {
		m_settings.antialiasingLevel = 8;
		create_window("LambdaLogic", sf::Style::Default, vec);
		FontManager::get_instance()->get_font("Roboto-Regular.ttf");
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

		chip c1("AND");
		chip c2("OR");

		c1.set_chip_pos({100, 100});
		c1.set_chip_color(sf::Color::Red);
		c2.set_chip_pos({600, 100});
		c2.set_chip_color(sf::Color::Blue);

		chips.push_back(c1);
		chips.push_back(c2);
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

		for (auto& c : chips) {
			c.draw(m_window);
		}
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
};
