#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main( ){
    /* shader
     ofGLWindowSettings settings;
     settings.setGLVersion(3,2);
     ofCreateWindow(settings);
     */
//    
//    ofGLWindowSettings settings;
//    settings.setGLVersion(3,2);
//    ofCreateWindow(settings);
    
    ofAppGlutWindow window;
    ofSetupOpenGL(&window, 1920,1080, OF_FULLSCREEN);			// <-------- setup the GL context
    

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
