#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGlutWindow.h" //0115

//========================================================================
int main( ){
	ofSetupOpenGL(1920, 1080,OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
//    ofAppGlutWindow window;
//    ofSetupOpenGL(&window, 1024,768, OF_WINDOW);
	ofRunApp(new ofApp());

}
