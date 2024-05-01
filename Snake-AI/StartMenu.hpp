#pragma once

#include "Globals.hpp"
#include "DrawObjects.hpp"

#include <SFML/Graphics.hpp>

class StartMenu : public DrawObject {
public:
	StartMenu();
	//~StartMenu(); useless

	virtual void draw(sf::RenderWindow&) override;

	bool click(const sf::RenderWindow&);
	bool startMenu = true;

private:
	sf::Font papyrus; //toto by sa mohlo zdedit asi 

	sf::Text choiceOfGameMod;
	/*
	sf::Text restart;
	sf::Text godMod;
	sf::Text skin;
	sf::speedValue;
	*/
	
	sf::RectangleShape choiceOfGameMod_button;
};
