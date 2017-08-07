#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "rectangle.h"
#include "particle.h"


class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed  (int key);
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
    void initialRectangles();
    
    // ----------- EASING -----------
    
    std::vector<float> positions;
    std::vector<std::string> easingNames;
    float initTime;
    float endPosition;
    
    // ----------- SERIAL -----------
    
    bool		bSendSerialMessage;			// a flag for sending serial
    char		bytesRead[3];				// data from serial, we will be trying to read 3
    char		bytesReadString[4];			// a string needs a null terminator, so we need 3 + 1 bytes
    int			nBytesRead;					// how much did we read?
    int			nTimesRead;					// how many times did we read?
    float		readTime;					// when did we last read?
    
    ofSerial	serial;
    
    // ------------- GUI -------------
    
    ofxPanel gui;
    
    ofxToggle drawLines;
    ofxToggle easeLines;
    ofxToggle drawRectangles;
    ofxToggle drawParticles;
    ofxToggle easeWiderRect;
    ofxToggle gradient;
    ofxToggle lineRotation;
    
    ofxFloatSlider distance;
    ofxFloatSlider thickness;
    ofxFloatSlider speed;
    ofxFloatSlider xPosOffset;
    
    ofxColorSlider bgColor;
    
    bool bHide;
    bool mHide;
    
    // ----------- VARIABLES ------------

    float xPos0;
    float xPos1;
    float yPos;
    
    float xPos2;
    float xPos3;
    float xPos4;
    float yPos1;
    
    float vx;
    float vy;
    
    float pct;
    
    rectangle myRectangle;
    rectangle myRectangle1;
    ofMesh mesh;
    
    // practice
    // let's make a vector of them
    vector <particle> particles;
   
    
};

