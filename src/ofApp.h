#pragma once
#include <Windows.h>
#include <Commdlg.h>
#include <iostream>
#include "ofMain.h"
#include "ScrollBar.h"
#include "ColorSelect.h"
#include "ImageHandler.h"
#include "Button.h"
class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
	private:
		void open();
		void save();
		ofImage spectrum;
		ofImage checker;

		Button loadbtn;
		Button savebtn;

		ScrollBar vert1;
		ScrollBar hori1;
		ImageHandler imgHandler;

		ColorSelect csel;

		string infileName;
		int flatime = 0;
		bool fir = true;
};
