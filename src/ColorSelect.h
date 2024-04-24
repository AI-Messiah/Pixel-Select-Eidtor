#pragma once
#include "ofMain.h"

class ColorSelect
{
public:
	ColorSelect();
	void setup();
	void draw();
	int locx = 0;
	int locy = 0;
	ofColor col = ofColor(255, 255, 255, 0);
	void clearSelect();
	void mouse(int x, int y);
	void sendKey(int key);	
	bool selsig = false;
private:
	int ncol[4] = { 255, 255, 255, 0 };
	string labels[4] = { "Red", "Green", "Blue", "Alpha" };
	ofTrueTypeFont displayFont;
	bool selected = false;
	int selNum = 0;
};

