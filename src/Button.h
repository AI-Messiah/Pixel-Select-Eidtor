#pragma once
#include "ofMain.h"
class Button
{
public:
	void init(string cap, int x, int y);
	void draw();
	void mouse(int x, int y);
	bool isPressed = false;
private:
	ofTrueTypeFont font;
	string caption;
	int locx, locy;
	int cenx;
};

