#pragma once
#include <vector>

#include "../core/State.h"
#include "../core/Application.h"
#include "../gui/Button.h"
#include "../ResourceIdentifiers.h"
//#include "../Definitions.h"
#include "SFML/Graphics.hpp"


class MenuState : public State
{
	public:
		MenuState (GlobalDataRef gData);

        void init();
       	void handleInput(const sf::Event& event);
        void update (float dt);
        void draw(float dt );
		void stop();
        
	private:
		GlobalDataRef   gData;

        std::vector<sf::Sprite>  _background;
		//std::vector<sf::Text>	titleText;

        std::vector<Button> _buttons;
};
