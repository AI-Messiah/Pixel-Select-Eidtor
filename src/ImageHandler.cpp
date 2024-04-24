#include "ImageHandler.h"

ImageHandler::ImageHandler()
{
	display.allocate(736, 736, ofImageType::OF_IMAGE_COLOR_ALPHA);
}

void ImageHandler::setup()
{
	displayFont.loadFont("micross.ttf", 14);
}

void ImageHandler::draw()
{
	ofSetColor(255);
	display.draw(0, 0);
	if (flash) {
		ofSetColor(255, 255, 0);
	}
	else {
		ofSetColor(0, 0, 0);
	}
	ofNoFill();
	ofDrawRectangle(plocx - 2, plocy - 2, 36, 36);
	ofDrawRectangle(plocx - 1, plocy - 1, 34, 34);
	if (psel) ofDrawRectangle(selpix.x, selpix.y, 1, 1);
	if (isSelected) {
		for (int i = 0; i < selLocs.size(); i++) {
			int x = selLocs.at(i).x;
			int y = selLocs.at(i).y;
			ofDrawRectangle(x, y, 1, 1);
		}
	}
	ofFill();
	for (int y = 0; y < 32; y++) {
		for (int x = 0; x < 32; x++) {
			ofColor sam = ofColor(0);
			if (plocx + x < sizex && plocy + y < sizey && plocx + x >= 0 && plocy + y >= 0) {
				sam = imgSample.Sample.getColor(plocx + x, plocy + y);
			}
			else {
				sam = ofColor(0);
			}
			
			ofSetColor(sam);
			ofDrawRectangle(768 + x * 8, y * 8, 8, 8);
		}
	}
	if (psel) {
		if (flash) {
			ofSetColor(255, 255, 0);
		}
		else {
			ofSetColor(0, 0, 0);
		}
		ofDrawRectangle(768 + (selpix.x - plocx) * 8, (selpix.y - plocy) * 8, 8, 8);
	}
	if (isSelected) {
		for (int i = 0; i < selLocs.size(); i++) {
			int x = selLocs.at(i).x;
			int y = selLocs.at(i).y;
			if (x >= plocx && x < plocx + 32 && y >= plocy && y < plocy + 32) {
				ofDrawRectangle(768 + (x - plocx) * 8, (y - plocy) * 8, 8, 8);
			}
		}
	}
	ofSetColor(0);
	if (isFilled) displayFont.drawString("Filled", 800, 400);	
}

void ImageHandler::updateScroll(int x, int y)
{
	imgSample.get();
	sizex = 736;
	sizey = 736;
	if (imgSample.Sample.getWidth() < 736) sizex = imgSample.Sample.getWidth();
	if (imgSample.Sample.getHeight() < 736) sizey = imgSample.Sample.getHeight();
	for (int yy = 0; yy < sizey; yy++) {
		for (int xx = 0; xx < sizex; xx++) {
			ofColor sam = imgSample.Sample.getColor(slocx + xx, slocy + yy);
			display.setColor(xx, yy, sam);
		}
	}
	display.update();
}

void ImageHandler::updateFlash()
{
	flash = !flash;
}

void ImageHandler::sendKey(int key)
{
	if (psel) {
		switch (key) {
		case 19: //ctrl s
			isSelected = true;
			break;
		case 57357: //up
			
			if (selpix.y > 0) {
				selpix.y--;
				addpos();
			}
			plocy--;
			break;
		case 57359: //down	
			
			if (selpix.y < sizey - 1) {
				selpix.y++;
				addpos();
			}
			plocy++;
			break;
		case 57356: //left 	
			
			if (selpix.y > 0) {
				selpix.x--;
				addpos();
			}
			plocx--;
			break;
		case 57358: //right	
			
			if (selpix.x < sizex - 1) {
				selpix.x++;
				addpos();
			}
			plocx++;
			break;
		}
	}
}

void ImageHandler::loaded(ofImage inimg, string name)
{
	imgSample.Sample = inimg;
	imgSample.set();
	fpat.init(inimg.getWidth(), inimg.getHeight());
	psizex = inimg.getWidth();
	psizey = inimg.getHeight();
	updateScroll(0, 0);
}

ofImage ImageHandler::save()
{
	imgSample.get();
	return imgSample.Sample;
}

void ImageHandler::clMouse()
{
	mdown = false;
}

void ImageHandler::Mouse(int x, int y)
{
	if (x >= 0 && x < 736 && y >= 0 && y < 736) {
		if (mdown) {
			plocx += x - oldx;
			plocy += y - oldy;
			oldx = x;
			oldy = y;
			if (plocx < 0) plocx = 0;
			if (plocy < 0) plocy = 0;
		}
		else {
			oldx = x;
			oldy = y;
			mdown = true;
		}
	}
}

void ImageHandler::MouseMove(int x, int y)
{
}

void ImageHandler::sendClick(int x, int y)
{
	if (x > 767 && y < 256) {
		selsig = true;
		psel = true;
		selpix = glm::ivec2(plocx + (x - 768) / 8, plocy + y / 8);
		if (isFilled) {
			fpat.seed(selpix.x, selpix.y);
			fill();
			isFilled = false;
			isSelected = false;
			selLocs.clear();
		}
	}
	else {
		selsig = false;
		psel = false;
	}
}

void ImageHandler::clearSelect()
{
	psel = false;
	isSelected = false;
	isFilled = false;
}

void ImageHandler::addpos()
{
	if (isSelected) {
		for (int i = 0; i < selLocs.size(); i++) if (selLocs.at(i) == selpix) {
			isFilled = true;

			fpat.setBounds(selLocs);
			return;
		}
		if (!isFilled) selLocs.push_back(selpix);
		
	}
}

void ImageHandler::fill()
{
	imgSample.get();
	for (int y = 0; y < imgSample.Sample.getHeight(); y++) {
		for (int x = 0; x < imgSample.Sample.getWidth(); x++) {
			if (fpat.sample(x, y)) {				
				imgSample.Sample.setColor(x, y, fillColor);				
			}
		}
	}
	imgSample.set();
	updateScroll(0, 0);
}
