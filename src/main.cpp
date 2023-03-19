#include "App.hpp"
#include "sfhelper/sfhelper.hpp"
#include "sfhelper/sfh_debug.hpp"

class LambdaLogic : public App {
public:
	LambdaLogic() {
		name = "LambdaLogic";
		create_window();
	}

	void setup() override {
		using namespace std;
		cout << "Width: " << width << " Height: " << height << "\n";
	}

	void loop() override {
		window.clear(sf::Color::Black);
	}

	void gui() override {
		ImGui::Begin("My Window");

		if (ImGui::Button("Click me!")) {
			// Do something when the button is clicked
		}

		ImGui::End();
	}
};

int main() {
	LambdaLogic App;
	App.run();
	return 0;
}