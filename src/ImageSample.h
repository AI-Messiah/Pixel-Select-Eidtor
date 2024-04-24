#pragma once
#include "ofMain.h"
class ImageSample
{
public:
	ImageSample();
	~ImageSample();
	int idx = 0;
	ofImage Sample;
	void get();
	void set();
private:
	ofImage img1;
	ofImage img2;
};

