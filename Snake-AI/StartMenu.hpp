#pragma once

#include "Globals.hpp"
#include "DrawObjects.hpp"
#include <vector>

#include <SFML/Graphics.hpp>

class StartMenu : public DrawObject {
public:
	int button;
	StartMenu();

	int numberOfSkins = 2;
	int gameMod = 0;
	virtual void draw(sf::RenderWindow&) override;

	bool clickSkin(const sf::RenderWindow&);
	bool clickMod(const sf::RenderWindow&);
	bool clickStart(const sf::RenderWindow&);

	void assignFilenames(std::vector<std::string>&, int);

	void anotherSkin(int& skinChose, int& numberOfSkins);
	void setPressed(int& button);
	void setUnpressed(int& button);
	void changeMod();


private:
	sf::Font papyrus; //toto by sa mohlo zdedit asi 

	sf::Text gameName;
	sf::Text changeSkin;
	sf::Text choiceOfGameMod;
	sf::Text Start;

	sf::Texture buttonTexture;
	sf::Texture pressedButtonTexture;
	sf::Texture backgroundTexture;
	sf::Texture SkinSelector_texture;

	std::string FileName = "StartMenu";
	/*
	sf::Text restart;
	sf::Text godMod;
	sf::Text skin;
	sf::speedValue;
	*/
	std::string gameMods[3] = { "Classic", "Peaceful", "     AI    " };

	sf::RectangleShape background;
	sf::RectangleShape choiceOfGameMod_button;
	sf::RectangleShape changeSkin_button;
	sf::RectangleShape Start_button;
};
