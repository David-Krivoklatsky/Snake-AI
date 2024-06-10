#pragma once

#include "Globals.hpp"
#include "DrawObjects.hpp"
#include <vector>
#include <SFML/Audio.hpp>

#include <SFML/Graphics.hpp>

class StartMenu : public DrawObject {
public:
	StartMenu();

	virtual void draw(sf::RenderWindow&) override;

	bool clickSkin(const sf::RenderWindow&);
	bool clickMode(const sf::RenderWindow&);
	bool clickStart(const sf::RenderWindow&);
	bool clickSound(const sf::RenderWindow&);

	void anotherSkin(int&, const int);
	void setPressed(int&);
	void setUnpressed(int&);
	void changeMod();
	void turnSound();

	int button = 0;
	bool sound = false;
	int mode = 0;
	std::string gameModes[number_of_modes] = { "Classic", "Random Mode", "Train AI", "    AI    ", "Freesnake" , "AI - noob", "Battle Royale"};

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
	sf::Texture Sound_textureOn;
	sf::Texture Sound_textureOff;

	std::string FileName = "StartMenu";


	sf::Music music;
	/*
	sf::Text restart;
	sf::Text godMod;
	sf::Text skin;
	sf::speedValue;
	*/

	sf::RectangleShape background;
	sf::RectangleShape choiceOfGameMod_button;
	sf::RectangleShape changeSkin_button;
	sf::RectangleShape Start_button;
	sf::RectangleShape sound_button;
};
