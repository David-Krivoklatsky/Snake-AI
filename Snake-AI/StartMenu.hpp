#pragma once

#include "Globals.hpp"
#include "DrawObjects.hpp"
#include <vector>

#include <SFML/Graphics.hpp>

class StartMenu : public DrawObject {
public:
	StartMenu();

	int numberOfSkins = 2;
	virtual void draw(sf::RenderWindow&) override;

	bool click(const sf::RenderWindow&);

	void assignFilenames(std::vector<std::string>&, int);

	void anotherSkin(int& skinChose, int& numberOfSkins);


private:
	sf::Font papyrus; //toto by sa mohlo zdedit asi 

	sf::Text choiceOfGameMod;

	sf::Texture buttonTexture;
	sf::Texture backgroundTexture;

	std::string FileName = "StartMenu";
	/*
	sf::Text restart;
	sf::Text godMod;
	sf::Text skin;
	sf::speedValue;
	*/
	sf::RectangleShape background;
	sf::RectangleShape choiceOfGameMod_button;
};
