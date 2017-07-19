#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
    ofBackground(0);

	// we add this listener before setting up so the initial circle resolution is correct
	circleResolution.addListener(this, &ofApp::circleResolutionChanged);
	ringButton.addListener(this, &ofApp::ringButtonPressed);

	gui.setup(); // most of the time you don't need a name
	gui.add(drawCircle.setup("drawCircle", false));
    gui.add(drawLines.setup("drawLines", true));

	gui.add(radius.setup("radius", 50, 10, 300));
    gui.add(circleResolution.setup("circle res", 30, 3, 90));
	gui.add(color.setup("color", ofColor(255), ofColor(255), ofColor(255)));
	gui.add(twoCircles.setup("two circles"));
	gui.add(ringButton.setup("ring"));
	gui.add(screenSize.setup("screen size", ofToString(ofGetWidth())+"x"+ofToString(ofGetHeight())));
    gui.add(distance.setup("line distance", 300, 150, 1000));
    gui.add(speed.setup("speed", 0.1, 0, 1));
    gui.add(thickness.setup("thickness", 1, 0.1, 10));
    gui.add(xPosOffset.setup("xPosOffset", 0, 0, 1000));

    //	gui.add(center.setup("center", ofVec2f(ofGetWidth()*.5, ofGetHeight()*.5), ofVec2f(0, 0), ofVec2f(ofGetWidth(), ofGetHeight())));

    bHide = false;
    
	ring.load("ring.wav");
    
    xPos0 = 0;
    xPos1 = 0;
    yPos = ofGetHeight();
    
    whiteBall.x = ofGetWidth()/2;
    whiteBall.y = 100;
    whiteBall.vx = ofRandom(-10,10);
    whiteBall.vy = ofRandom(-10,10);
    
}

//--------------------------------------------------------------
void ofApp::exit(){
	ringButton.removeListener(this, &ofApp::ringButtonPressed);
}

//--------------------------------------------------------------
void ofApp::circleResolutionChanged(int &circleResolution){
	ofSetCircleResolution(circleResolution);
}

//--------------------------------------------------------------
void ofApp::ringButtonPressed(){
	ring.play();
}

//--------------------------------------------------------------
void ofApp::update(){
	ofSetCircleResolution(circleResolution);
    
    whiteBall.y = whiteBall.y + whiteBall.vy;

    if (whiteBall.y<0+radius || whiteBall.y > ofGetHeight()-radius) {
        whiteBall.vy = -whiteBall.vy;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
//    ofBackgroundGradient(ofColor::white, ofColor::gray);
    
	if(drawCircle)
    {
        ofDrawCircle(mouseX, mouseY, radius);
        ofDrawCircle(whiteBall.x, whiteBall.y, radius);
    }
    
    if(drawLines)
    {
        for (int i = 0; i < 20; i++){
            ofSetLineWidth(thickness);
//            ofRotateX(45);
            ofDrawLine(xPos0-distance*5 + (distance * i), -10, xPos1-distance*5 + (distance * i), yPos+10);

            if(xPos0 > distance + xPosOffset) {
                xPos0 = xPosOffset;
                xPos1 = 0;
            }
            xPos0 = xPos0 + speed;
            xPos1 = xPos1 + speed;
        }
    }

	ofSetColor(color);
	if(twoCircles)
    {
		ofDrawCircle(center->x-radius*.5, center->y, radius );
		ofDrawCircle(center->x+radius*.5, center->y, radius );
	}
    
	// auto draw?
	// should the gui control hiding?
	if(!bHide){
		gui.draw();
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if(key == 'h'){
		bHide = !bHide;
	}
	else if(key == 's'){
		gui.saveToFile("settings.xml");
	}
	else if(key == 'l'){
		gui.loadFromFile("settings.xml");
	}
	else if(key == ' '){
		color = ofColor(255);
	}
    else if(key == 'b'){
        ofBackground(0);
    }
    else if(key == 'w'){
        ofBackground(255);
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    screenSize = ofToString(w) + "x" + ofToString(h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
	
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
	
}
