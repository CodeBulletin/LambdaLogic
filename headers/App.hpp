#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <imgui.h>
#include <imgui-SFML.h>

#include <string>

#include "sfhelper/sfh_color.hpp"


class App {
public:
	App() = default;
	App(App& app) = delete;
	// App operator=(App& app) = delete;
	~App() = default;

	void create_window(std::string name, uint32_t style, sf::Vector3<uint32_t> vec = {500u, 500u, 32u}) {
		// Create the window
		this->m_name = name;
		this->m_style = style;
		this->m_videoMode = sf::VideoMode({vec.x, vec.y}, vec.z);
		this->m_window.create(this->m_videoMode, this->m_name, this->m_style = style, this->m_settings);
		this->m_width = this->m_videoMode.size.x;
		this->m_height = this->m_videoMode.size.y;
		this->m_window.setVerticalSyncEnabled(true);
	}

	virtual void run() {
		// Run the app
		setup();
		while (this->m_window.isOpen()) {
			this->m_frameTime = this->m_clock.getElapsedTime().asSeconds();
			sf::Time time = this->m_clock.restart();
			this->m_frameRate = std::round(1.0f / this->m_frameTime);
			while (this->m_window.pollEvent(this->m_event)) {
				if (this->m_guiEnabled) ImGui::SFML::ProcessEvent(this->m_event);
				eventManager();
				if (!this->m_window.isOpen()) return;
			}
			if (this->m_guiEnabled) {
				ImGui::SFML::Update(this->m_window, time);
				gui();
			}
			loop();
			if (this->m_guiEnabled) {
				ImGui::SFML::Render(this->m_window);
			}
			this->m_window.display();
		}
	}

	virtual void setup() = 0;  // Setup the app
	virtual void loop() = 0;  // Loop the app

	virtual void close() {  // Close the app
		this->m_window.close();
	}

	virtual void gui() {}

	virtual void keyPressedEvent() {}  // Event manager key pressed
	virtual void keyReleasedEvent() {}  // Event manager key released
	virtual void mouseButtonPressedEvent() {}  // Event manager mouse button pressed
	virtual void mouseButtonReleasedEvent() {}  // Event manager mouse button released
	virtual void closedEvent() {  // Event manager is window closed
		close();
	}
	virtual void lostFocusEvent() {}  // Event manager has window lost focus
	virtual void gainedFocusEvent() {}  // Event manager has window gained focus
	virtual void mouseEnteredEvent() {}  // Event manager has mouse entered window
	virtual void mouseLeftEvent() {}  // Event manager has mouse left window
	virtual void mouseMovedEvent() {}  // Event manager has mouse moved
	virtual void mouseWheelScrolledEvent() {}  // Event manager has mouse wheel scrolled
	virtual void textEnteredEvent() {}  // Event manager has text entered
	virtual void resizeEvent() {}  // Event manager has window resized

	virtual void eventManager() {
		// Manage events
		switch (this->m_event.type) {
		case sf::Event::KeyPressed:
			keyPressedEvent();
			break;
		case sf::Event::KeyReleased:
			keyReleasedEvent();
			break;
		case sf::Event::MouseButtonPressed:
			mouseButtonPressedEvent();
			break;
		case sf::Event::MouseButtonReleased:
			mouseButtonReleasedEvent();
			break;
		case sf::Event::Closed:
			closedEvent();
			break;
		case sf::Event::LostFocus:
			lostFocusEvent();
			break;
		case sf::Event::GainedFocus:
			gainedFocusEvent();
			break;
		case sf::Event::MouseEntered:
			mouseEnteredEvent();
			break;
		case sf::Event::MouseLeft:
			mouseLeftEvent();
			break;
		case sf::Event::MouseMoved:
			mouseMovedEvent();
			break;
		case sf::Event::MouseWheelScrolled:
			mouseWheelScrolledEvent();
			break;
		case sf::Event::TextEntered:
			textEnteredEvent();
			break;
		case sf::Event::Resized:
			resizeEvent();
			break;
		default:
			break;
		}
	}

protected:
	sf::RenderWindow m_window;
	sf::VideoMode m_videoMode;
	sf::ContextSettings m_settings;
	sf::Event m_event = sf::Event();
	sf::Clock m_clock;

	std::string m_name;

	uint32_t m_style;
	bool m_guiEnabled = true;
	float m_frameTime;
	int m_frameRate;
	int m_width = 0, m_height = 0;
};