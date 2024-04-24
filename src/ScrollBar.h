#pragma once
#include "ofMain.h"
class ScrollBar
{
public:
	ScrollBar();
	void draw();	
	void Mouse(int x, int y);
	void clMouse();
	int length = 0;
	int locx = 0;
	int locy = 0;
	bool isVertical = true;
	float fraction = .5;
	float amount = 0;
private:
	bool fmouse = true;
	float oldval;
	ofImage up;
	ofImage right;
	ofImage down;
	ofImage left;
};

