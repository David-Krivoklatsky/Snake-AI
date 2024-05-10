#pragma once

#include "Globals.hpp"
#include "DrawObjects.hpp"
#include <vector>
#include <SFML/Audio.hpp>

#include <SFML/Graphics.hpp>

class StartMenu : public DrawObject {
public:
	int button;
	StartMenu();

	int numberOfSkins = 2;
	bool sound = false;
	int mode = 0;
	virtual void draw(sf::RenderWindow&) override;

	bool clickSkin(const sf::RenderWindow&);
	bool clickMode(const sf::RenderWindow&);
	bool clickStart(const sf::RenderWindow&);
	bool clickSound(const sf::RenderWindow&);

	void assignFilenames(std::vector<std::string>&, int);

	void anotherSkin(int&, int&);
	void setPressed(int&);
	void setUnpressed(int&);
	void changeMod();
	void turnSound();


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
	std::string gameModes[4] = { "Classic", "Peaceful", "     AI    ", "AI - noob"};

	sf::RectangleShape background;
	sf::RectangleShape choiceOfGameMod_button;
	sf::RectangleShape changeSkin_button;
	sf::RectangleShape Start_button;
	sf::RectangleShape sound_button;
};
