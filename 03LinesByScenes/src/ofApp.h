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
    
    ofTrueTypeFont		font;
    
    bool		bSendSerialMessage;			// a flag for sending serial
    char		bytesRead[3];				// data from serial, we will be trying to read 3
    char		bytesReadString[4];			// a string needs a null terminator, so we need 3 + 1 bytes
    int			nBytesRead;					// how much did we read?
    int			nTimesRead;					// how many times did we read?
    float		readTime;					// when did we last read?
    
    ofSerial	serial;
    
    ofxPanel gui;
    bool bHide;
    
    ofxToggle drawLines;
    ofxToggle drawRectangles;
    ofxToggle drawParticles;
    
    ofxFloatSlider distance;
    ofxFloatSlider thickness;
    ofxFloatSlider speed;
    ofxFloatSlider xPosOffset;
    ofxFloatSlider s1PosX;
    ofxFloatSlider s1PosY;
    ofxFloatSlider s1width;
    ofxFloatSlider s1height;
    
    ofxColorSlider bgColor;

    float xPos0;
    float xPos1;
    float yPos;
    float rectW;
    float rectH;
    
    rectangle myRectangle;
    rectangle myRectangle1;
    
    float pct;
    
    ofMesh mesh;
    
    // practice
    // let's make a vector of them
    vector <particle> particles;
   
    
};

