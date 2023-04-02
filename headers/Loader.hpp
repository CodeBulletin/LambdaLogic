#pragma once

#include "App.hpp"
#include "sfhelper/sfh_debug.hpp"

class Loader : private App {
private: 
	sf::View m_view;
	std::vector<std::string> m_modes;
	bool m_isSelected = true;
	int m_selected = 0;
	std::string m_selectedMode = "Select a file";
	std::string m_fontFile = "./Assets/Fonts/OpenSans-Regular.ttf";

public:
	uint32_t m_win_width = 0;
	uint32_t m_win_height = 0;
	uint32_t m_win_bitsPerPixel = 0;
	float combo_box_width = 0.f;
	ImFont* font = nullptr;

public:
    Loader() {
		m_settings.antialiasingLevel = 8;
		create_window("Loader", sf::Style::Default, {600, 800, 32});
		m_view = sf::View(sf::FloatRect({0.0f, 0.0f}, {(float)m_width, (float)m_height}));
    	m_window.setView(m_view);
	}

	void run() override {
		App::run();
	}

	sf::RenderWindow& getWindow(){
		return this->m_window;
	}

private:

	void setup() override {
        std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
		int i = 0;
		for (auto& mode : modes) {
			if (mode.bitsPerPixel != 32) {
				continue;
			}
			sfh::debug::log("Mode: ", mode.size.x, "x", mode.size.y, "x", mode.bitsPerPixel);
			std::string m = std::to_string(mode.size.x) + "x" + std::to_string(mode.size.y) + "x" + std::to_string(mode.bitsPerPixel);
			m_modes.push_back(m);
		}
		styleGui();
        m_selectedMode = m_modes[0];
	}

	void loop() override {
		m_window.clear(sf::Color::Black);
	}

	void styleGui() {
		ImGuiStyle& style = ImGui::GetStyle();
		style.Colors[ImGuiCol_WindowBg] = ImVec4(0.09f, 0.09f, 0.15f, 0.0f);
		// style.Colors[ImGuiCol_ScrollbarBg] = 
		ImGuiIO& io = ImGui::GetIO();
		font = io.Fonts->AddFontFromFileTTF(m_fontFile.c_str(), 20.f);
		// io.FontGlobalScale = 0.5f;
		if (!ImGui::SFML::UpdateFontTexture()) {
			sfh::debug::log("Error updating font texture");
		}
	}

	void gui() override {
		// ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[1]);

		ImGui::SetNextWindowSize({(float)m_width, (float)m_height});
		ImGui::SetNextWindowPos({0, 0});

		ImGui::Begin("Main Window", nullptr, ImGuiWindowFlags_NoMove | 
            ImGuiWindowFlags_NoResize | 
            ImGuiWindowFlags_NoTitleBar);

		ImGui::PushFont(font);

		if (combo_box_width == 0.f) {
			for (std::string s : m_modes) {
				float w = ImGui::CalcTextSize(s.c_str()).x;
				if (w > combo_box_width) {
					combo_box_width = w;
				}
			}
			combo_box_width += 50.f;
		}

		//imgui combobox here
		// alignCenterImgui(m_selectedMode.c_str(), 0.5f);
		ImGui::SetNextItemWidth(combo_box_width);
		alignCenterImgui(combo_box_width, 0.5f);
		if (ImGui::BeginCombo("##combo", m_selectedMode.c_str())) {
			int i = 0;
			for (std::string& mode : m_modes) {
				bool is_selected = (m_selected == i);
				if (ImGui::Selectable(mode.c_str(), is_selected)) {
					m_selected = i;
                    m_isSelected = true;
                    m_selectedMode = mode;
				}
				if (is_selected) {
					ImGui::SetItemDefaultFocus();
				}
				i++;
			}
			ImGui::EndCombo();
		}

		alignCenterImgui("Start", 0.5f);
		if (ImGui::Button("Start")) {
			m_win_width = std::stoi(m_selectedMode.substr(0, m_selectedMode.find("x")));
			m_win_height = std::stoi(m_selectedMode.substr(m_selectedMode.find("x") + 1, m_selectedMode.find("x", m_selectedMode.find("x") + 1)));
			m_win_bitsPerPixel = std::stoi(m_selectedMode.substr(m_selectedMode.find("x", m_selectedMode.find("x") + 1) + 1, m_selectedMode.length()));
			close();
		}

		ImGui::PopFont();

		ImGui::End();
		// ImGui::PopFont();
	}

	void resizeEvent() override{
		m_width = m_event.size.width;
		m_height = m_event.size.height;
		m_view.setSize({(float)m_width, (float)m_height});
		m_window.setView(m_view);
	}

	void alignCenterImgui(const std::string& str, float alignment) {
		float avail = ImGui::GetContentRegionAvail().x;
		float size = ImGui::CalcTextSize(str.c_str()).x + ImGui::GetStyle().FramePadding.x * 2.0f;
		float off = (avail - size) * alignment;
		if (off > 0.0f)
			ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);
	}

	void alignCenterImgui(float w_width, float alignment) {
		float avail = ImGui::GetContentRegionAvail().x;
		float off = (avail - w_width) * alignment;
		if (off > 0.0f)
			ImGui::SetCursorPosX(ImGui::GetCursorPosX() + off);
	}
};