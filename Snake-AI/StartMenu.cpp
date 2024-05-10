#include "StartMenu.hpp"

StartMenu::StartMenu() {
	if (!papyrus.loadFromFile("papyrus.ttf")) {
	}
	if (!buttonTexture.loadFromFile(FileName + "/Button2.png")) {
	}
	if (!backgroundTexture.loadFromFile(FileName + "/background1.png")) {
	}
	if (!pressedButtonTexture.loadFromFile(FileName + "/Button3.png")) {
	}
	if (!music.openFromFile(FileName + "/Snake.mp3")) {
	}
	if (!Sound_textureOff.loadFromFile(FileName + "/soundOff.png")) {
	}
	if (!Sound_textureOn.loadFromFile(FileName + "/soundOn0.png")) {
	}

	music.setVolume(50);         // reduce the volume
	music.setLoop(true);         // make it loop

	choiceOfGameMod_button.setSize(sf::Vector2f(180,60));
	choiceOfGameMod_button.setPosition((WINDOW_SIZE / 3.f) * 3 - 225, WINDOW_SIZE / 2.f + 115);
	choiceOfGameMod_button.setTexture(&buttonTexture);


	Start_button.setSize(sf::Vector2f(225, 75));
	Start_button.setPosition((WINDOW_SIZE / 3.f) * 2 - 245, WINDOW_SIZE / 2.f + 110);
	Start_button.setTexture(&buttonTexture);

	changeSkin_button.setSize(sf::Vector2f(180, 60));
	changeSkin_button.setPosition((WINDOW_SIZE / 3.f) * 1 - 225, WINDOW_SIZE / 2.f + 115);
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

	choiceOfGameMod.setFont(papyrus);
	choiceOfGameMod.setFillColor(sf::Color::White);
	choiceOfGameMod.setString(gameModes[mode]);
	choiceOfGameMod.setCharacterSize(20);
	choiceOfGameMod.setOrigin(choiceOfGameMod.getLocalBounds().width / 2, choiceOfGameMod.getLocalBounds().height / 2);
	choiceOfGameMod.setPosition((WINDOW_SIZE / 3.f) * 3 - 140, WINDOW_SIZE / 2.f + 145);
	choiceOfGameMod.setStyle(sf::Text::Bold);

	changeSkin.setFont(papyrus);
	changeSkin.setFillColor(sf::Color::White);
	changeSkin.setString("Change skin");
	changeSkin.setCharacterSize(20);
	changeSkin.setOrigin(changeSkin.getLocalBounds().width / 2, changeSkin.getLocalBounds().height / 2);
	changeSkin.setPosition((WINDOW_SIZE / 3.f) * 1 - 140, WINDOW_SIZE / 2.f + 145);
	changeSkin.setStyle(sf::Text::Bold);

	Start.setFont(papyrus);
	Start.setFillColor(sf::Color::White);
	Start.setString("Start");
	Start.setCharacterSize(30);
	Start.setOrigin(Start.getLocalBounds().width / 2, Start.getLocalBounds().height / 2);
	Start.setPosition((WINDOW_SIZE / 3.f) * 2 - 140, WINDOW_SIZE / 2.f + 145);
	Start.setStyle(sf::Text::Bold);


	background.setTexture(&backgroundTexture);
	background.setOrigin(WINDOW_SIZE / 2, WINDOW_SIZE / 2);
	background.setSize(sf::Vector2f(800, 800));
	background.setPosition(WINDOW_SIZE / 2, WINDOW_SIZE / 2);

	sound_button.setSize(sf::Vector2f(80, 80));
	sound_button.setPosition(WINDOW_SIZE - 100, 20);
	sound_button.setTexture(&Sound_textureOff);

	if (sound) {
		music.play();
	}

}

void StartMenu::draw(sf::RenderWindow& window)
{	
	window.draw(background);
	window.draw(choiceOfGameMod_button);
	window.draw(gameName);
	window.draw(changeSkin_button);
	window.draw(Start_button);
	window.draw(choiceOfGameMod);
	window.draw(changeSkin);
	window.draw(Start);
	window.draw(sound_button);
}

void StartMenu::assignFilenames(std::vector<std::string>& textureFiles, int numberOfSkins) {
	for (int i = 0; i < numberOfSkins; i++) {
		textureFiles.push_back("Snake_texture" + std::to_string(i + 1));
	}
}

void StartMenu::anotherSkin(int& skinChose, const int numberOfSkins) {
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

bool StartMenu::clickMode(const sf::RenderWindow& window)
{
	return choiceOfGameMod_button.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
}

bool StartMenu::clickSound(const sf::RenderWindow& window)
{
	return sound_button.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
}

void StartMenu::setPressed(int &button) {
	if (button == 1) {
		changeSkin_button.setTexture(&pressedButtonTexture);
	}
	else if (button == 2) {
		Start_button.setTexture(&pressedButtonTexture);
	}
	else if (button == 3) {
	choiceOfGameMod_button.setTexture(&pressedButtonTexture);
	}
}

void StartMenu::setUnpressed(int& button) {
	if (button == 1) {
		changeSkin_button.setTexture(&buttonTexture);
	}
	else if (button == 2) {
		Start_button.setTexture(&buttonTexture);
	}
	else if (button == 3) {
		choiceOfGameMod_button.setTexture(&buttonTexture);
	}
}

void StartMenu::changeMod(){
	mode++;
	mode %= number_of_modes;

	choiceOfGameMod.setString(gameModes[mode]);
}

void StartMenu::turnSound() {
	if (sound) {
		sound = false;
		music.pause();
		sound_button.setTexture(&Sound_textureOff);
	}
	else {
		sound = true;
		music.play();
		sound_button.setTexture(&Sound_textureOn);
	}

}
