
#include "ImageSample.h"
#include "FillPat.h"

class ImageHandler {

public:
	ImageHandler();
	void setup();
	void draw();
	void updateScroll(int x, int y);
	void updateFlash();
	void sendKey(int key);
	
	void loaded(ofImage inimg, string name);
	ofImage save();
	void clMouse();
	void Mouse(int x, int y);
	void MouseMove(int x, int y);
	void sendClick(int x, int y);
	void clearSelect();
	bool selsig = false;
	int psizex = 0, psizey = 0;
	ofColor fillColor;
private:
	void addpos();
	void fill();
	FillPat fpat;
	
	ofTrueTypeFont displayFont;
	vector<glm::ivec2> selLocs;
	bool isSelected = false;
	glm::ivec2 selpix;
	bool psel = false;
	ofImage display;
	ImageSample imgSample;
	int plocx = 100;
	int plocy = 100;
	bool mdown = false;
	bool flash = false;
	bool isFilled = false;
	bool xmin = false;
	bool ymin = false;
	int sizex = 736, sizey = 736;
	int oldx = 0, oldy = 0;
	int slocx = 0;
	int slocy = 0;
};