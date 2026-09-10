#include "QuickRefState.h"
#include "CharacterDetailState.h"
#include "../model/character.h"
//#include "../gui/Utility.h"
#include <iostream>

QuickRefState::QuickRefState(GlobalDataRef gData) 
: gData(gData)
{
    sf::Text txt(gData-> mAssets.getFont(Fonts::Main));
	txt.setFillColor(sf::Color(255, 255, 255));
	for (int i=0; i<3; i++)	{
		titleText.push_back(txt);
	}
	for (int i=0; i<12; i++)	{
		charInfoText.push_back(txt);
	}

	//titleText[0].setString(gData -> mStringsDB.getString(ViewAllCharacters));
	titleText[1].setString(gData -> mStringsDB.getString(PressToViewChar));
	titleText[2].setString(gData -> mStringsDB.getString(EscToGoBack));
	int ChrSize [] = {30, 25, 25}; //font sizes	
	int textX [] = {150, 100, 150}; //X positions
	int textY [] = {10, 520, 550}; //Y positions

	for (int i=0; i<3; i++)	{
		titleText[i].setCharacterSize(ChrSize[i]);
		titleText[i].setPosition({textX[i], textY[i]});
	}
	for (int i=0; i<12; i++) {
		charInfoText[i].setFont(gData-> mAssets.getFont(Fonts::Main));
		charInfoText[i].setFillColor(sf::Color(255, 255, 255));
		charInfoText[i].setCharacterSize(16);
	}
	for (int i=0; i<6; i++)	{
		charInfoText[i].setPosition({10, 50+25*i});
		charInfoText[6+i].setPosition({10, 100+25*(6+i)});
	}
}

void QuickRefState::init() {
	std::string txt;
	Character* character;
	for (int i=0; i<6; i++)
	{
		character = gData-> mGameModel._party.getCharacter(i);
		txt = "";
		txt.push_back(char(0x31+i));
		txt += "  ";
		txt = txt + character-> _name + "  "; 
		txt = txt + std::to_string(character-> _HP._temporary) + " / ";
		txt = txt + std::to_string(character-> _HP._permanent) + "            ";
		txt = txt + std::to_string(character-> _SP._temporary) + " / ";
		txt = txt + std::to_string(character-> _SP._permanent) + "             ";
		txt = txt + std::to_string(character-> _AC._temporary);
		charInfoText[i].setString(txt);

		txt = "";
		txt.push_back(char(0x31+i));
		txt += "  FOOD= ";
		txt = txt + std::to_string(character-> _food) + "  COND= "; 
		Condition cond = character -> getWorstCondition();
		switch (cond) {
			case GOOD: txt = txt + "Good"; break;
			case ERADICATED: txt = txt + "Eradicated"; break;
			case DEAD: txt = txt + "Dead"; break;
			case STONED: txt = txt + "Stoned"; break;
			case UNCONSCIOUS: txt = txt + "Unconscious"; break;
			case PARALYZED: txt = txt + "Paralyzed"; break;
			case POISONED: txt = txt + "Poisoned"; break;
			case DISEASED: txt = txt + "Diseased"; break;
			case SILENCED: txt = txt + "Silenced"; break;
			case BLINDED: txt = txt + "Blinded"; break;
			case ASLEEP: txt = txt + "Asleep"; break;
		}
		charInfoText[6+i].setString(txt);
	}
}

void QuickRefState::handleInput(const sf::Event& event)
{
	if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>())
        {
		if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
			gData -> mStates.removeState();
		}
		else if ((keyPressed->scancode >= sf::Keyboard::Scancode::Num1)&&(keyPressed->scancode <=sf::Keyboard::Scancode::Num6)) {
			int num = int (keyPressed->scancode)-26;
			Character* character = gData-> mGameModel._party.getCharacter(num);
			if (character != nullptr){
				gData -> mStates.addState(StatePtr (new CharacterDetailState(gData, character)));
			}
		}
	}
}

void QuickRefState::update (float dt){
	
}

void QuickRefState::draw(float dt) {

	//temporary display clean. To delete when the state will be implemented.
	gData -> mWindow.clear(); //TO BE DELETED

	for (int i=0; i<3; i++)
	{
		gData -> mWindow.draw(titleText[i]);
	}
	for (int i=0; i<12; i++)
	{
		gData -> mWindow.draw(charInfoText[i]);
	}
}

void QuickRefState::stop ()
{}
