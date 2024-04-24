#include "ColorSelect.h"

ColorSelect::ColorSelect()
{
}

void ColorSelect::setup()
{
	displayFont.loadFont("micross.ttf", 12);
}

void ColorSelect::draw()
{
	ofSetColor(0);
	for (int i = 0; i < 4; i++) {
		string nst = ofToString(ncol[i]);
		displayFont.drawString(labels[i], locx + 20, locy + 22 + 32 * i);
		int tx = 108 - displayFont.stringWidth(nst);
		displayFont.drawString(nst, locx + tx, locy + 22 + 32 * i);
	}
	ofNoFill();
	if (selected) {
		ofDrawRectangle(locx, locy + selNum * 32, 128, 32);
		ofDrawRectangle(locx + 1, locy + 1 + selNum * 32, 126, 30);
		ofDrawRectangle(locx + 2, locy + 2 + selNum * 32, 124, 28);
	}
}

void ColorSelect::clearSelect()
{
	selected = false;
}

void ColorSelect::mouse(int x, int y)
{
	if (x >= locx && x < locx + 128 && y >= locy && y < locy + 128) {
		selNum = (y - locy) / 32;
		selected = true;
		selsig = true;
	}
	else {
		selected = false;
	}
}

void ColorSelect::sendKey(int key)
{
	if (selected) {
		if (key == 57356) {
			if (ncol[selNum] > 0) ncol[selNum]--;
		}
		else if (key == 57358) {
			if (ncol[selNum] < 255) ncol[selNum]++;
		}
		col = ofColor(ncol[0], ncol[1], ncol[2], ncol[3]);
	}
}
