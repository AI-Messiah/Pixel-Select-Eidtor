#include "ScrollBar.h"

ScrollBar::ScrollBar()
{
	up.loadImage("Images/uparrow.png");
	right.loadImage("Images/rightarrow.png");
	down.loadImage("Images/downarrow.png");
	left.loadImage("Images/leftarrow.png");
}

void ScrollBar::draw()
{
	if (isVertical) {
		ofSetColor(255);
		up.draw(locx, locy);
		down.draw(locx, locy + length - 32);
		ofFill();
		ofSetColor(255);
		ofDrawRectangle(locx + 2, locy + 34, 28, length - 70);
		ofSetColor(127);
		ofDrawRectangle(locx + 2, locy + 34 + amount, 28, (length - 70) * fraction);
		ofNoFill();
		ofSetColor(0);
		ofDrawRectangle(locx, locy + 32, 32, length - 64);
		ofDrawRectangle(locx, locy + 33, 30, length - 66);
	}
	else {
		ofSetColor(255);
		left.draw(locx, locy);
		right.draw(locx + length - 32, locy);
		ofFill();
		ofSetColor(255);
		ofDrawRectangle(locx + 34, locy + 2, length - 70, 28);
		ofSetColor(127);
		ofDrawRectangle(locx + 34 + amount, locy + 2 , (length - 70) * fraction, 28 );
		ofNoFill();
		ofSetColor(0);
	}
}

void ScrollBar::Mouse(int x, int y)
{
	
	if (x >= locx && x < locx + 32 && y >= locy && y < locy + length && isVertical) {
		
		if (fmouse) {
			oldval = y;
			fmouse = false;
		}
		else {
			float mov = ((float)y - oldval);
			oldval = y;
			//float adto = (float)mov / (float)(length - 64);
			amount += mov;//adto * (1 - fraction) / 20;
			if (amount < 0) amount = 0;
			if (amount + (length - 70) * fraction > length - 70) amount = (length - 70) - (length - 70) * fraction;
			//if (amount > 1 - fraction) amount = 1 - fraction;
		}
		
	}
	else if (x >= locx && x < locx + length && y >= locy && y < locy + 32 && !isVertical) {
		if (fmouse) {
			oldval = x;
			fmouse = false;
		}
		else {
			float mov = ((float)x - oldval);
			oldval = x;
			//float adto = (float)mov / (float)(length - 64);
			amount += mov;//adto * (1 - fraction) / 20;
			if (amount < 0) amount = 0;
			if (amount + (length - 70) * fraction > length - 70) amount = (length - 70) - (length - 70) * fraction;
		}
	}else{
		fmouse = true;
	}
	
}

void ScrollBar::clMouse()
{
	fmouse = true;
}
