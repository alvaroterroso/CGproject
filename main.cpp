//Ficheiro extras META1
//�lvaro Fonta�nhas Terroso 
//2021213782

//TODO
//MATERIALS
//TEXTURES
//SPOT CONFIG
//COMPONENT OFF AND ON
#include "ofMain.h"
#include "ofApp.h"
//TODO:
// submeter
//========================================================================
int main( ){

	//Use ofGLFWWindowSettings for more options like multi-monitor fullscreen
	ofGLWindowSettings settings;
	settings.setSize(1024, 768);
	settings.windowMode = OF_WINDOW; //can also be OF_FULLSCREEN
	
	auto window = ofCreateWindow(settings);
	ofRunApp(window, make_shared<ofApp>());
	ofRunMainLoop();

}
