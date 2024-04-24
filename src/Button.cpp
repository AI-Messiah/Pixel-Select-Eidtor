#include "Button.h"

void Button::init(string cap, int x, int y)
{
	caption = cap;
	locx = x;
	locy = y;
	font.loadFont("micross.ttf", 20);
	cenx = locx + 96 - font.stringWidth(caption) / 2;
}

void Button::draw()
{
	ofFill();
	ofSetColor(127);
	ofRect(locx, locy, 192, 64);
	ofSetColor(0);
	font.drawString(caption, cenx, locy + 40);
}

void Button::mouse(int x, int y)
{
	if (x >= locx && x < locx + 192 && y >= locy && y < locy + 64) isPressed = true;
}
