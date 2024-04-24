#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	vert1.amount = 0;
	vert1.length = 736;
	vert1.locx = 736;
	vert1.locy = 0;
	vert1.fraction = .75;

	hori1.isVertical = false;
	hori1.amount = 0;
	hori1.length = 736;
	hori1.locx = 0;
	hori1.locy = 736;
	hori1.fraction = .25;

	csel.setup();
	csel.locx = 768;
	csel.locy = 256;

	loadbtn.init("Open", 806, 512);
	savebtn.init("Save", 806, 606);

	open();
	spectrum.load("Images/spectrum.png");
	checker.load("Images/checker.png");

	imgHandler.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
	imgHandler.fillColor = csel.col;
	if (fir) {
		cout << csel.col.a << "\n";
		fir = false;
	}
	if (imgHandler.selsig) {
		csel.clearSelect();
		imgHandler.selsig = true;
	}
	if (csel.selsig) {
		imgHandler.clearSelect();
		csel.selsig = false;
	}
	if (loadbtn.isPressed) {
		loadbtn.isPressed = false;
		open();
	}
	if (savebtn.isPressed) {
		savebtn.isPressed = false;
		save();
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofFill();
	ofSetColor(255);
	checker.draw(768, 0);
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 3; x++) checker.draw(x * 256, y * 256);
	}
	ofDrawRectangle(736, 736, 32, 32);
	ofDrawRectangle(768, 256, 256, 512);
	imgHandler.draw();
	flatime++;
	if (flatime >= 30) {
		flatime = 0;
		imgHandler.updateFlash();		
	}
	vert1.draw();
	hori1.draw();

	ofSetColor(255);
	spectrum.draw(896, 256);

	ofFill();
	ofColor acol = csel.col;
	ofSetColor(acol);
	ofDrawRectangle(896, 256, 128, 128);

	ofSetColor(255);
	csel.draw();

	loadbtn.draw();
	savebtn.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	imgHandler.sendKey(key);
	csel.sendKey(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	vert1.Mouse(x, y);
	hori1.Mouse(x, y);
	imgHandler.Mouse(x, y);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	imgHandler.sendClick(x, y);
	csel.mouse(x, y);
	loadbtn.mouse(x, y);
	savebtn.mouse(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	vert1.clMouse();
	hori1.clMouse();
	imgHandler.clMouse();
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

void ofApp::open()
{
	std::vector<char> fileName;
	fileName.resize(MAX_PATH + 1);
	fileName[0] = '\0';

	OPENFILENAMEA ofn;
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = ofGetWin32Window();
	ofn.lpstrFilter = "All Files (*.*)\0*.*\0";
	ofn.lpstrFile = fileName.data();
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrDefExt = 0;

	if (GetOpenFileNameA(&ofn)) {
		ofImage temp;
		if (temp.load(fileName.data())) {
			string iname = "";
			infileName = fileName.data();
			for (int i = infileName.length() - 1; i > -1; i--) {
				if (infileName.substr(i, 1) == "\\") break;
				iname = infileName.substr(i, 1) + iname;
			}
			imgHandler.loaded(temp, iname);
			if (imgHandler.psizex < 736) {
				hori1.fraction = 1;
			}
			else {
				hori1.fraction = 736.0f / (float)imgHandler.psizex;
			}
			if (imgHandler.psizey < 736) {
				vert1.fraction = 1;
			}
			else {
				vert1.fraction = 736.0f / (float)imgHandler.psizey;
			}


		}
	}
}

wchar_t* convertCharArrayToLPCWSTR(const char* charArray)
{
	wchar_t* wString = new wchar_t[4096];
	MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
	return wString;
}

void ofApp::save()
{
	OPENFILENAME ofn = { sizeof(OPENFILENAME) };

	char szFile[_MAX_PATH] = "";
	strcpy(szFile, infileName.c_str());
	const char szExt[] = "png\0"; 

	ofn.hwndOwner = GetConsoleWindow();
	wchar_t wtext[_MAX_PATH];
	mbstowcs(wtext, szFile, strlen(szFile) + 1);
	LPWSTR ptr = wtext;
	ofn.lpstrFile = ptr; 
	ofn.nMaxFile = sizeof(szFile) / sizeof(szFile[0]);
	LPCWSTR sz = convertCharArrayToLPCWSTR(szExt);
	ofn.lpstrFilter = ofn.lpstrDefExt = sz;
	ofn.Flags = OFN_SHOWHELP | OFN_OVERWRITEPROMPT;
	if (GetSaveFileName(&ofn)) {	
		wstring ws(ofn.lpstrFile);
		string path = string(ws.begin(), ws.end());
		
		ofImage simg = imgHandler.save();
		simg.save(path, OF_IMAGE_QUALITY_BEST);
	}
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
