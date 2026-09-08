#include "TitleState.h"
#include "MenuState.h"
//#include "headers/Utility.h"
#include <iostream>

TitleState::TitleState(GlobalDataRef gData) : gData(gData)
{
	gData -> mAssets.loadTexture(Textures::IntroBook, "media/images/MM1-book.png");
	gData -> mAssets.loadTexture(Textures::Intro0, "media/images/intro/screen0.png");
	gData -> mAssets.loadTexture(Textures::Intro1, "media/images/intro/screen1.png");
	gData -> mAssets.loadTexture(Textures::Intro2, "media/images/intro/screen2.png");
	gData -> mAssets.loadTexture(Textures::Intro3, "media/images/intro/screen3.png");
	gData -> mAssets.loadTexture(Textures::Intro4, "media/images/intro/screen4.png");
	gData -> mAssets.loadTexture(Textures::Intro5, "media/images/intro/screen5.png");
	gData -> mAssets.loadTexture(Textures::Intro6, "media/images/intro/screen6.png");
	gData -> mAssets.loadTexture(Textures::Intro7, "media/images/intro/screen7.png");
	gData -> mAssets.loadTexture(Textures::Intro8, "media/images/intro/screen8.png");
	gData -> mAssets.loadTexture(Textures::Intro9, "media/images/intro/screen9.png");

	gData -> mMusic.play(Music::MainTheme);
}

void TitleState::init() {
    sf::Sprite _sprite(gData -> mAssets.getTexture(Textures::IntroBook));

	_background.push_back(_sprite);
    for(int i=0; i<10; i++){
         sf::Sprite sprite(gData -> mAssets.getTexture(Textures::Intro0));
        _slides.push_back(sprite);
    }
	_slides[0].setTexture (gData -> mAssets.getTexture(Textures::Intro0));
	_slides[1].setTexture (gData -> mAssets.getTexture(Textures::Intro1));
	_slides[2].setTexture (gData -> mAssets.getTexture(Textures::Intro2));
	_slides[3].setTexture (gData -> mAssets.getTexture(Textures::Intro3));
	_slides[4].setTexture (gData -> mAssets.getTexture(Textures::Intro4));
	_slides[5].setTexture (gData -> mAssets.getTexture(Textures::Intro5));
	_slides[6].setTexture (gData -> mAssets.getTexture(Textures::Intro6));
	_slides[7].setTexture (gData -> mAssets.getTexture(Textures::Intro7));
	_slides[8].setTexture (gData -> mAssets.getTexture(Textures::Intro8));
	_slides[9].setTexture (gData -> mAssets.getTexture(Textures::Intro9));

	sf::VideoMode _videoMode = sf::VideoMode::getDesktopMode();
	gData -> mWindow.create(_videoMode, "", sf::State::Fullscreen);

	sf::Vector2f scale;
	scale.y = 1.0*_videoMode.size.y / (_background[0].getTextureRect().size.y);
	scale.x = scale.y;

	_background[0].setOrigin({_background[0].getTextureRect().size.x/2, _background[0].getTextureRect().size.y/2});
	_background[0].setPosition({_videoMode.size.x/2 , _videoMode.size.y/2});

	_background[0].setScale(scale);

	float bookWidth = _background[0].getGlobalBounds().size.x;

	for (int i=0; i<10; i++){
		scale.x = 1.0*(bookWidth -40) / _slides[i].getTextureRect().size.x;
		scale.y = scale.x;
		_slides[i].setOrigin({_slides[i].getTextureRect().size.x/2, _slides[i].getTextureRect().size.y});
		_slides[i].setScale(scale);
		_slides[i].setPosition({_videoMode.size.x/2, _videoMode.size.y -5});
	}
	timer =0.0;
	_currentSlide = -1;
}

void TitleState::handleInput(const sf::Event& event) {
	if (event.is<sf::Event::MouseButtonPressed>()) { nextSlide();}
	if (const auto* keyPressed = event.getIf<sf::Event::KeyPressed>()) {
		if (keyPressed->scancode == sf::Keyboard::Scancode::Escape){
			gData -> mStates.replaceState(StatePtr(new MenuState(gData)));
		}
		else {nextSlide();}
	}
}

void TitleState::update (float dt){
	timer += dt;
	if (timer > SLIDE_DELAY) { nextSlide();}
}

void TitleState::draw(float dt){
	gData -> mWindow.draw(_background[0]);
	if ((_currentSlide>=0)&&(_currentSlide<10)){
		gData -> mWindow.draw(_slides[_currentSlide]);
	}
}

void TitleState::stop(){
	gData -> mAssets.deleteTexture(Textures::IntroBook);
	gData -> mAssets.deleteTexture(Textures::Intro0);
	gData -> mAssets.deleteTexture(Textures::Intro1);
	gData -> mAssets.deleteTexture(Textures::Intro2);
	gData -> mAssets.deleteTexture(Textures::Intro3);
	gData -> mAssets.deleteTexture(Textures::Intro4);
	gData -> mAssets.deleteTexture(Textures::Intro5);
	gData -> mAssets.deleteTexture(Textures::Intro6);
	gData -> mAssets.deleteTexture(Textures::Intro7);
	gData -> mAssets.deleteTexture(Textures::Intro8);
	gData -> mAssets.deleteTexture(Textures::Intro9);

//temporary non full screen
	int height = sf::VideoMode::getDesktopMode().size.y -25;
	int width = sf::VideoMode::getDesktopMode().size.x;

	width = 800;
	height=600;

    gData -> mWindow.create (sf::VideoMode({width, height}), APP_NAME, sf::Style::Close);
	gData -> mWindow.setPosition (sf::Vector2i({0,0}));

}

void TitleState::nextSlide (){
	_currentSlide ++;
	timer = 0.0;
	if (_currentSlide <=10) {return;}
	else {
		gData -> mStates.replaceState(StatePtr(new MenuState(gData)));
	}
}
