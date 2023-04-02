#include "App.hpp"
#include "Loader.hpp"
#include "MainApp.hpp"

chip_settings* chip_settings::instance = chip_settings::get_instance();
pin_settings* pin_settings::instance = pin_settings::get_instance();
FontManager* FontManager::instance = FontManager::get_instance();

int main() { 
	
	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_bitsPerPixel;

    Loader loader;
    ImGui::CreateContext();
    if (!ImGui::SFML::Init(loader.getWindow())) {
        exit(1);
    }
    loader.run();
    ImGui::SFML::Shutdown();
    m_width = loader.m_win_width;
    m_height = loader.m_win_height;
    m_bitsPerPixel = loader.m_win_bitsPerPixel;

    if (m_width == 0 || m_height == 0 || m_bitsPerPixel == 0) {
        exit(1);
    }

    MainApp app({m_width, m_height, m_bitsPerPixel});
    ImGui::CreateContext();
    if (!ImGui::SFML::Init(app.getWindow())) {
        exit(1);
    }
    app.run();
    ImGui::SFML::Shutdown();
    return 0;
}