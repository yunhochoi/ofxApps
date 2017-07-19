#pragma once

#include "ofMain.h"
#include "ofxGui.h"

struct Ball {
    int x;
    int y;
    int vx;
    int vy;
};

class ofApp : public ofBaseApp{
	
public:
	void setup();
	void update();
	void draw();
	
	void exit();

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

	void circleResolutionChanged(int & circleResolution);
	void ringButtonPressed();

	bool bHide;

	ofxFloatSlider radius;
	ofxColorSlider color;
	ofxVec2Slider center;
	ofxIntSlider circleResolution;
	ofxToggle drawCircle;
    ofxToggle drawLines;
	ofxButton twoCircles;
	ofxButton ringButton;
	ofxLabel screenSize;

	ofxPanel gui;

	ofSoundPlayer ring;
    
    ofxFloatSlider distance;
    ofxFloatSlider thickness;
    ofxFloatSlider speed;
    ofxFloatSlider xPosOffset;
    float xPos0;
    float xPos1;
    float yPos;
    
    Ball whiteBall;
    
};

