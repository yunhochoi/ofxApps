#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true); 	// macs by default run on non vertical sync, which can make animation very, very fast
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
    
    // gui
    gui.setup(); // most of the time you don't need a name
    gui.add(bgColor.setup("color", ofColor(0,0,0,255), ofColor(0,0,0,0), ofColor(255,255,255,255)));
    
    gui.add(drawLines.setup("Lines", false));
    gui.add(drawRectangles.setup("Rectangles", false));
    gui.add(drawParticles.setup("Particles", false));
    
    
    gui.add(distance.setup("line distance", 1200, 50, 1500));
    gui.add(speed.setup("speed", 0.1, 0, 1));
    gui.add(thickness.setup("thickness", 1, 0.1, 10));
    gui.add(xPosOffset.setup("xPosOffset", 0, 0, 1000));
    
    gui.add(s1PosX.setup("s1PosX", ofGetWidth()/2, 0, ofGetWidth()));
    gui.add(s1PosY.setup("s1PosY", ofGetHeight()/2, 0, ofGetHeight()));
    gui.add(s1width.setup("s1width", 50, 1, ofGetWidth()));
    gui.add(s1height.setup("s1height", 50, 1, ofGetHeight()));
    bHide = false;
    
    // line position
    xPos0 = 0;
    xPos1 = 0;
    yPos = ofGetHeight();
    
    // gradient mesh
    mesh.addVertex(ofVec3f(0,0));
    mesh.addColor (ofColor(0,0,0,0));
    mesh.addVertex(ofVec3f(ofGetWidth(),0));
    mesh.addColor (ofColor(0,0,0,255));
    mesh.addVertex(ofVec3f(ofGetWidth(),ofGetHeight()));
    mesh.addColor (ofColor(0,0,0,255));
    mesh.addVertex(ofVec3f(0,ofGetHeight()));
    mesh.addColor (ofColor(0,0,0,0));
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
    
    // rectangle
    myRectangle.posa.x = ofGetWidth();
    myRectangle.posa.y = 0;
    myRectangle.posb.x = 0;
    myRectangle.posb.y = 0;
    myRectangle.interpolateByPct(0);	// start at 0 pct
    
    myRectangle1.posa.x = 0;
    myRectangle1.posa.y = 0;
    myRectangle1.posb.x = ofGetWidth();
    myRectangle1.posb.y = 0;
    myRectangle1.interpolateByPct(0);	// start at 0 pct
    
    pct = 0.1;
    
    // practice
    for (int i = 0; i < 100; i++){
        particle myParticle;
        float vx = ofRandom(-1,1);
        float vy = ofRandom(-1,1);
        myParticle.setInitialCondition(ofRandom(ofGetWidth()),ofGetHeight()/2,vx, vy);
        
        // more interesting with diversity :)
        // uncomment this:
        myParticle.damping = ofRandom(0.01, 0.05);
        particles.push_back(myParticle);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    
    myRectangle.update();
    myRectangle.interpolateByPct(pct);		// go between pta and ptb
    myRectangle1.interpolateByPct(pct);		// go between pta and ptb
    //    myRectangle1.update();
    
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
    
    // to see pct in the console
    //printf("%f \n", pct);
    
    pct += 0.001f;							// increase by a certain amount
    if (pct > 1) {
        pct = 0;							// just between 0 and 1 (0% and 100%)
    }
    
    // pratice
    for (int i = 0; i < particles.size(); i++){
        //particles[i].resetForce();
        //particles[i].addForce(0,0.04);  // gravity
        //particles[i].addDampingForce();
        particles[i].update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // lines
    ofBackground(bgColor);
    
    if(drawLines){
        for (int i = 0; i < 20; i++){
            ofSetLineWidth(thickness);
            ofSetColor(255);
            ofDrawLine(xPos0-distance * 5 + (distance * i), -10, xPos1-distance * 5 + (distance * i), yPos+10);
            ofDrawLine(0, xPos0-distance * 5 + (distance * i), ofGetWidth(),xPos0-distance * 5 + (distance * i));
            
            if(xPos0 > distance + xPosOffset) {
                xPos0 = xPosOffset;
                xPos1 = 0;
            }
            xPos0 = xPos0 + speed;
            xPos1 = xPos1 + speed;
        }
        // mesh.draw();
    }
    
    if(drawRectangles){
        myRectangle.draw();
        myRectangle1.draw();
    }
    
    if(!bHide){
        gui.draw();
    }
    // particles
    if(drawParticles){
        for (int i = 0; i < particles.size(); i++){
            particles[i].draw();
            particles[i].rectH += 1;
            particles[i].rectW += 1;
        }
    } else {
        for (int i = 0; i < particles.size(); i++){
            
            particles[i].rectH = 1;
            particles[i].rectW = 1;
        }
        
    }
  
    //
    //    for (int i = 0; i < ofGetWidth(); i+=20){
    //        for (int j = 0; j < ofGetHeight(); j+=20){
    //
    //            ofPoint pt(i,j);
    //            ofPoint diff = ofPoint(mouseX, mouseY) - pt;
    //
    //            float angle = atan2(diff.y, diff.x);
    //            float dist = diff.length();
    //
    //            if (dist < 200){
    //                ofDrawLine(pt.x, pt.y, pt.x - 10 * sin(angle), pt.y + 10 * cos(angle));
    //            }
    //
    //        }
    //    }
    
    //    if (nBytesRead > 0 && ((ofGetElapsedTimef() - readTime) < 0.5f)){
    //        ofSetColor(0);
    //    } else {
    //        ofSetColor(220);
    //    }
    //    string msg;
    //    msg += "click to test serial:\n";
    //    msg += "nBytes read " + ofToString(nBytesRead) + "\n";
    //    msg += "nTimes read " + ofToString(nTimesRead) + "\n";
    //    msg += "read: " + ofToString(bytesReadString) + "\n";
    //    msg += "(at time " + ofToString(readTime, 3) + ")";
    //    font.drawString(msg, 50, 100);
    //    if (ofToString(bytesReadString) == "s")
    //    {
    //     printf("received s");
    //    }
    
    // practice
    
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
        //        ofBackground(0);
        bgColor = (0,0,0);
    }
    else if(key == 'w'){
        //        ofBackground(255);
        bgColor = (255);
    }
    else if(key == 'l'){
        gui.loadFromFile("settings.xml");
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
}

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
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}

