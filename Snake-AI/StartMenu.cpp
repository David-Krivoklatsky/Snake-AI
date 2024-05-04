#include "StartMenu.hpp"

StartMenu::StartMenu() {
	if (!papyrus.loadFromFile("papyrus.ttf")) {
	}
	if (!buttonTexture.loadFromFile(FileName + "/Button.png")) {
	}
	if (!backgroundTexture.loadFromFile(FileName + "/background1.png")) {
	}


	choiceOfGameMod_button.setSize(sf::Vector2f(180,180));
	choiceOfGameMod_button.setPosition((WINDOW_SIZE / 3.f) * 3 - 225, WINDOW_SIZE / 2.f + 70);
	choiceOfGameMod_button.setTexture(&buttonTexture);


	Start_button.setSize(sf::Vector2f(225, 225));
	Start_button.setPosition((WINDOW_SIZE / 3.f) * 2 - 245, WINDOW_SIZE / 2.f + 45);
	Start_button.setTexture(&buttonTexture);

	changeSkin_button.setSize(sf::Vector2f(180, 180));
	changeSkin_button.setPosition((WINDOW_SIZE / 3.f) * 1 - 225, WINDOW_SIZE / 2.f + 70);
	changeSkin_button.setTexture(&buttonTexture);

	gameName.setFont(papyrus);
	gameName.setFillColor(sf::Color::Red);
	gameName.setOutlineThickness(2);
	gameName.setOutlineColor(sf::Color::Black);
	gameName.setString("Snake-AI");
	gameName.setCharacterSize(90);
	gameName.setOrigin(gameName.getLocalBounds().width / 2, gameName.getLocalBounds().height / 2 - 55);
	gameName.setPosition(WINDOW_SIZE / 2.f, WINDOW_SIZE / 2.f - 100);
	gameName.setStyle(sf::Text::Bold);

	background.setTexture(&backgroundTexture);
	background.setOrigin(WINDOW_SIZE / 2, WINDOW_SIZE / 2);
	background.setSize(sf::Vector2f(800, 800));
	background.setPosition(WINDOW_SIZE / 2, WINDOW_SIZE / 2);

}

void StartMenu::draw(sf::RenderWindow& window)
{
	window.draw(background);
	window.draw(choiceOfGameMod_button);
	window.draw(gameName);
	window.draw(changeSkin_button);
	window.draw(Start_button);
}

void StartMenu::assignFilenames(std::vector<std::string>& textureFiles, int numberOfSkins) {
	for (int i = 0; i < numberOfSkins; i++) {
		textureFiles.push_back("Snake_texture" + std::to_string(i + 1));
	}
	return;
}

void StartMenu::anotherSkin(int& skinChose, int &numberOfSkins) {
	skinChose++;
	if(skinChose >= numberOfSkins){
		skinChose = 0;
	}
	if (!backgroundTexture.loadFromFile(FileName + "/background" + std::to_string(skinChose + 1) + ".png")) {
	}
}

bool StartMenu::clickSkin(const sf::RenderWindow& window)
{
	return changeSkin_button.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
}

bool StartMenu::clickStart(const sf::RenderWindow& window)
{
	return Start_button.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
}
bool StartMenu::clickMod(const sf::RenderWindow& window)
{
	return choiceOfGameMod_button.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
}