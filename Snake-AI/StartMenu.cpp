#include "StartMenu.hpp"

StartMenu::StartMenu() {
	if (!papyrus.loadFromFile("papyrus.ttf")) {
	}
	if (!buttonTexture.loadFromFile(FileName + "/Button.png")) {
	}
	if (!backgroundTexture.loadFromFile(FileName + "/background.png")) {
	}


	//choiceOfGameMod_button.setFillColor(sf::Color::White);
	choiceOfGameMod_button.setSize(sf::Vector2f(180,180));
	choiceOfGameMod_button.setOrigin(10, 10);
	choiceOfGameMod_button.setPosition(WINDOW_SIZE / 2.f, WINDOW_SIZE / 2.f + 70);
	//choiceOfGameMod_button.setOutlineThickness(2);
	//choiceOfGameMod_button.setOutlineColor(sf::Color::Cyan);
	choiceOfGameMod_button.setTexture(&buttonTexture);
	//choiceOfGameMod_button.setTexture();

	choiceOfGameMod.setFont(papyrus);
	choiceOfGameMod.setFillColor(sf::Color::Red);
	choiceOfGameMod.setString("Mino je borec");
	choiceOfGameMod.setCharacterSize(70);
	choiceOfGameMod.setOrigin(choiceOfGameMod.getLocalBounds().width / 2, choiceOfGameMod.getLocalBounds().height / 2);
	choiceOfGameMod.setPosition(WINDOW_SIZE / 2.f, WINDOW_SIZE / 2.f - 100);
	choiceOfGameMod.setStyle(sf::Text::Bold);

	background.setTexture(&backgroundTexture);
	background.setOrigin(WINDOW_SIZE / 2, WINDOW_SIZE / 2);
	background.setSize(sf::Vector2f(800, 800));
	background.setPosition(WINDOW_SIZE / 2, WINDOW_SIZE / 2);

}

void StartMenu::draw(sf::RenderWindow& window)
{
	window.draw(background);
	window.draw(choiceOfGameMod_button);
	window.draw(choiceOfGameMod);
}

void StartMenu::assignFilenames(std::vector<std::string>& textureFiles, int numberOfSkins) {
	for (int i = 0; i < numberOfSkins; i++) {
		textureFiles.push_back("Snake_texture" + std::to_string(i + 1));
	}
	return;
}

void StartMenu::anotherSkin(int& skinChose, int &numberOfSkins) {
	skinChose++;
	if(skinChose > numberOfSkins){
		skinChose = 1;
	}
}

bool StartMenu::click(const sf::RenderWindow& window)
{
	return choiceOfGameMod_button.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
}
