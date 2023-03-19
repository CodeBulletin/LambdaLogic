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

	virtual void create_window() {
		settings.antialiasingLevel = 8;
		vid = sf::VideoMode::getFullscreenModes()[10];

		window.create(vid, name, sf::Style::Resize | sf::Style::Close | sf::Style::Titlebar, settings);

		width = vid.size.x;
		height = vid.size.y;

		window.setVerticalSyncEnabled(true);

		ImGui::SFML::Init(window);
	}

	virtual void run() {
		setup();
		while (window.isOpen()) {
			if (GUI) ImGui::SFML::ProcessEvent(event);
			frameTime = clock.getElapsedTime().asSeconds();
			sf::Time time = clock.restart();
			frameRate = std::round(1.0f / frameTime);
			while (window.pollEvent(event)) {
				eventManager();
			}
			if (GUI) {
				ImGui::SFML::Update(window, time);
				gui();
			}
			loop();
			if (GUI) ImGui::SFML::Render(window);
			window.display();
		}
	}

	virtual void setup() = 0;
	virtual void loop() = 0;

	virtual void Close() {
		window.close();
	}

	virtual void gui() {}
	virtual void KeyPressedEvent() {}
	virtual void KeyReleasedEvent() {}
	virtual void MouseButtonPressedEvent() {}
	virtual void MouseButtonReleasedEvent() {}
	virtual void ClosedEvent() {
		Close();
	}
	virtual void LostFocusEvent() {}
	virtual void GainedFocusEvent() {}
	virtual void MouseEnteredEvent() {}
	virtual void MouseLeftEvent() {}
	virtual void MouseMovedEvent() {}
	virtual void MouseWheelScrolledEvent() {}
	virtual void TextEnteredEvent() {}

	virtual void eventManager() {
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			KeyPressedEvent();
			break;
		case sf::Event::KeyReleased:
			KeyReleasedEvent();
			break;
		case sf::Event::MouseButtonPressed:
			MouseButtonPressedEvent();
			break;
		case sf::Event::MouseButtonReleased:
			MouseButtonReleasedEvent();
			break;
		case sf::Event::Closed:
			ClosedEvent();
			break;
		case sf::Event::LostFocus:
			LostFocusEvent();
			break;
		case sf::Event::GainedFocus:
			GainedFocusEvent();
			break;
		case sf::Event::MouseEntered:
			MouseEnteredEvent();
			break;
		case sf::Event::MouseLeft:
			MouseLeftEvent();
			break;
		case sf::Event::MouseMoved:
			MouseMovedEvent();
			break;
		case sf::Event::MouseWheelScrolled:
			MouseWheelScrolledEvent();
			break;
		case sf::Event::TextEntered:
			TextEnteredEvent();
			break;
		default:
			break;
		}
	}
protected:
	sf::RenderWindow window;
	sf::VideoMode vid;
	sf::ContextSettings settings;
	std::string name;
	sf::Event event = sf::Event();
	sf::Clock clock;
	int width = 0, height = 0;
	float frameTime;
	int frameRate;
	bool GUI = true;
};