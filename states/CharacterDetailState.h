#pragma once
#include <vector>

#include "../core/State.h"
#include "../core/Application.h"
//#include "../gui/Button.h"
#include "../ResourceIdentifiers.h"
//#include "../Definitions.h"
#include "SFML/Graphics.hpp"

const int LABELS_COUNT = 48;

class CharacterDetailState : public State
{
	public:
		CharacterDetailState (GlobalDataRef gData, Character* currentCharacter);

        	void init();
       		void handleInput(const sf::Event& event);
        	void update (float dt);
        	void draw(float dt );
		void stop();

		void changeCharacter (Character* newCharacter);
		void changeCharacter (int characterId);
		void charDataUpdate();
        
	private:
		GlobalDataRef   gData;
		Character* _character;
		int _charId;
        	//sf::Sprite  _background;

		std::vector<sf::Text>	_txtLabel;
};
