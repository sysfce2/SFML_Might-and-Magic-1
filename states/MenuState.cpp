#include "MenuState.h"
#include "GameState.h"
#include "ViewAllCharState.h"
#include "../gui/Utility.h"
#include <iostream>

MenuState::MenuState(GlobalDataRef gData) 
: gData(gData)
{
	gData -> mAssets.loadTexture(Textures::MainMenu, "media/images/MM1-map.png");
	gData -> mAssets.loadTexture(Textures::MenuButton, "media/images/gui/Button.png");
}

void MenuState::init() {
    int _screen_width = gData -> mWindow.getSize().x;
    int _screen_height = gData -> mWindow.getSize().y;

    sf::Sprite _sprite(gData -> mAssets.getTexture(Textures::MainMenu));
	_background.push_back(_sprite);
	_background[0].setOrigin({_background[0].getTextureRect().size.x/2, _background[0].getTextureRect().size.y/2});
	_background[0].setPosition({_screen_width/2, _screen_height/2});
	sf::Vector2f scale;
	scale.y = 1.0*_screen_height/ (_background[0].getTextureRect().size.y);
	scale.x = scale.y;
	_background[0].setScale(scale);

	//prepare buttons
	sf::Sprite sprite(gData -> mAssets.getTexture(Textures::MenuButton));
	sf::Text text(gData-> mAssets.getFont(Fonts::Main));

    sprite.setScale({1.5, 0.8});
	centerOrigin(sprite);

	//create new character
	text.setString(gData -> mStringsDB.getString(CreateNewCharacter));
	centerOrigin(text);
    _buttons.push_back(Button (sprite, text, sf::Vector2f(_screen_width/2,100)));

	//view all character
	text.setString(gData -> mStringsDB.getString(ViewAllCharacters));
	centerOrigin(text);
    _buttons.push_back(Button (sprite, text, sf::Vector2f(_screen_width/2,200)));

	//go to town
	text.setString(gData -> mStringsDB.getString(GoToTown));
	centerOrigin(text);
    _buttons.push_back(Button (sprite, text, sf::Vector2f(_screen_width/2,300)));

	//exit button
	text.setString(gData -> mStringsDB.getString(ExitGame));
	centerOrigin(text);
    _buttons.push_back(Button (sprite, text, sf::Vector2f(_screen_width/2,400)));
}

void MenuState::handleInput(const sf::Event& event)
{
	if (_buttons[1].isClicked(sf::Mouse::Button::Left, gData -> mWindow))	{
		gData -> mStates.addState(StatePtr (new ViewAllCharState(gData)));
	}
/*
	if (_buttons[0].isClicked(sf::Mouse::Button::Left, gData -> mWindow))	{
		gData -> mStates.addState(StatePtr (new CreateCharState(gData)));
	}

*/
	if (_buttons[2].isClicked(sf::Mouse::Button::Left, gData -> mWindow))	{
		gData -> mStates.replaceState(StatePtr (new GameState(gData, 1)));
	}
	if (_buttons[3].isClicked(sf::Mouse::Button::Left, gData -> mWindow)) {
		gData -> mStates.removeState();
		gData -> mMusic.stop();
	}
	
//temporary town selector
	if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
		if ((keyPressed->scancode >= sf::Keyboard::Scancode::Num1)&&(keyPressed->scancode <= sf::Keyboard::Scancode::Num5)){
			gData -> mStates.replaceState(StatePtr(new GameState(gData, (int(keyPressed->scancode)-26) )));
		}
		//temporary for test
		else if ((keyPressed->scancode == sf::Keyboard::Scancode::Num9)){
			gData -> mStates.replaceState(StatePtr(new GameState(gData, 24 )));
		}
	}

}

void MenuState::update (float dt)
{}

void MenuState::draw(float dt) {
	gData -> mWindow.draw(_background[0]);

    for(int i=0; i<4; i++){
        _buttons[i].draw(gData -> mWindow);
    }
}

void MenuState::stop ()
{}
