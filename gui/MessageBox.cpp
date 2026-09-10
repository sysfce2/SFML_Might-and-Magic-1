#include "MessageBox.h"
#include "Utility.h"

MessageBox::MessageBox(sf::RenderWindow* target, int viewWidth, int viewHeight, const sf::Font* font)
:window (target)
{
    sf::Text txt(*font);
    mText.push_back(txt);

	float X, Y;
	X = viewWidth/2 - (5/14.0)*viewWidth;
	Y= viewHeight - 0.2*viewHeight;
	mShape.setPosition({X,Y});
	X = (5/7.0)*viewWidth;
	Y= 0.2*viewHeight;
	mShape.setSize(sf::Vector2f(X,Y));
//	centerOrigin(mShape);

	mShape.setFillColor(sf::Color::Black);
	mShape.setOutlineColor(sf::Color::Green);
	mShape.setOutlineThickness(2);

	mText[0].setPosition({viewWidth/2.0 ,mShape.getPosition().y});
	centerOrigin(mText[0]);

}

void MessageBox::setTextString(sf::String str){
	if (str != "")	mText[0].setString(str);
    centerOrigin(mText[0]);
}

void MessageBox::clean(){
	mText[0].setString("");
}

void MessageBox::draw()
{
	//window.draw(mSprite);
	window->draw(mShape);
	window->draw(mText[0]);
}

