#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetVerticalSync(true);
    ofBackground(0);

	
	bSendSerialMessage = false;
	ofBackground(0);
	ofSetLogLevel(OF_LOG_VERBOSE);
	
	font.load("DIN.otf", 64);
	
	serial.listDevices();
	vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
	
	// this should be set to whatever com port your serial device is connected to.
	// (ie, COM4 on a pc, /dev/tty.... on linux, /dev/tty... on a mac)
	// arduino users check in arduino app....
	int baud = 9600;
	serial.setup(1, baud); //open the first device
	//serial.setup("COM4", baud); // windows example
	//serial.setup("/dev/tty.usbserial-A4001JEC", baud); // mac osx example
	//serial.setup("/dev/ttyUSB0", baud); //linux example
	
	nTimesRead = 0;
	nBytesRead = 0;
	readTime = 0;
	memset(bytesReadString, 0, 4);
    
    //gui
    gui.setup(); // most of the time you don't need a name
//    gui.add(color.setseup("color", ofColor(255), ofColor(255), ofColor(255)));
    gui.add(distance.setup("line distance", 300, 150, 1000));
    gui.add(speed.setup("speed", 0.1, 0, 1));
    gui.add(thickness.setup("thickness", 1, 0.1, 10));
    gui.add(xPosOffset.setup("xPosOffset", 0, 0, 1000));
    bHide = false;
    
    xPos0 = 0;
    xPos1 = 0;
    yPos = ofGetHeight();


}

//--------------------------------------------------------------
void ofApp::update(){
	
	if (bSendSerialMessage){
		
		// (1) write the letter "a" to serial:
		serial.writeByte('s');
		
		// (2) read
		// now we try to read 3 bytes
		// since we might not get them all the time 3 - but sometimes 0, 6, or something else,
		// we will try to read three bytes, as much as we can
		// otherwise, we may have a "lag" if we don't read fast enough
		// or just read three every time. now, we will be sure to 
		// read as much as we can in groups of three...
		
		nTimesRead = 0;
		nBytesRead = 0;
		int nRead  = 0;  // a temp variable to keep count per read
		
		unsigned char bytesReturned[3];
		
		memset(bytesReadString, 0, 4);
		memset(bytesReturned, 0, 3);
		
        // a while loop that attempts to read three bytes from the device:
		while( (nRead = serial.readBytes( bytesReturned, 3)) > 0){
			nTimesRead++;	
			nBytesRead = nRead;
		};
		
		memcpy(bytesReadString, bytesReturned, 3);
		
		bSendSerialMessage = false;
		readTime = ofGetElapsedTimef();
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
//	if (nBytesRead > 0 && ((ofGetElapsedTimef() - readTime) < 0.5f)){
//		ofSetColor(0);
//	} else {
//		ofSetColor(220);
//	}
//	string msg;
//	msg += "click to test serial:\n";
//	msg += "nBytes read " + ofToString(nBytesRead) + "\n";
//	msg += "nTimes read " + ofToString(nTimesRead) + "\n";
//	msg += "read: " + ofToString(bytesReadString) + "\n";
//	msg += "(at time " + ofToString(readTime, 3) + ")";
//	font.drawString(msg, 50, 100);
//    
    //lines
    ofSetColor(255);

    for (int i = 0; i < 20; i++){
        ofSetLineWidth(thickness);
        ofDrawLine(xPos0-distance * 5 + (distance * i), -10, xPos1-distance * 5 + (distance * i), yPos+10);
        
        if(xPos0 > distance + xPosOffset) {
            xPos0 = xPosOffset;
            xPos1 = 0;
        }
        xPos0 = xPos0 + speed;
        xPos1 = xPos1 + speed;
    }
    
    if(!bHide){
        gui.draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed  (int key){
    if(key == 's'){ // disableAll
        serial.writeByte('s');
    }
    else if(key == 'a'){ // angleRotatePair
        serial.writeByte('a');
    }
    else if(key == 'e'){ // enableAll
        serial.writeByte('e');
    }
    else if(key == '1'){ // speedDown
        serial.writeByte('1');
    }
    else if(key == 'p'){ // speedUp
        serial.writeByte('p');
    }
    else if(key == 'o'){ // speedDown
        serial.writeByte('o');
    }
    else if(key == 'h'){ // hide gui
        bHide = !bHide;
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
void ofApp::mouseMoved(int x, int y){
	
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	bSendSerialMessage = true;
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
	
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
	
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
	
}

