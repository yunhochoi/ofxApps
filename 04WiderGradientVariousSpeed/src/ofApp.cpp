#include "ofApp.h"
#include "ofxEasing.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true); 	// macs by default run on non vertical sync, which can make animation very, very fast
    ofBackground(0);
    bSendSerialMessage = false;
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    // Easing
    positions.resize(5);
    initTime = 0;
    endPosition = ofGetWidth()*2;
    
    easingNames = {
        "linear",
        "quad",
        "cubic",
        "bounce",
        "back",
    };
    
    // Serial
    
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
    
    gui.add(drawLines.setup("PatternLines", false));
    gui.add(easeLines.setup("EasingLines", false));
    gui.add(drawRectangles.setup("Rectangles", false));
    gui.add(drawParticles.setup("Particles", false));
    gui.add(easeWiderRect.setup("WiderRects", false));
    gui.add(gradient.setup("Gradient", false));
    gui.add(lineRotation.setup("LineRotation", false));

    gui.add(distance.setup("line distance", 1280, 50, 1500));
    gui.add(speed.setup("speed", 0.1, 0, 1));
    gui.add(thickness.setup("thickness", 1, 0.1, 10));
    gui.add(xPosOffset.setup("xPosOffset", 0, 0, 1000));
    
    bHide = false;
    mHide = false;
    
    // line position
//    xPos0 = 0;
//    xPos1 = 0;
    yPos = ofGetHeight();
    yPos1 = ofGetHeight();
    
    // ---------- GRADIENT MESH ----------
    
    mesh.addVertex(ofVec3f(0,0));
    mesh.addColor (ofColor(0,0,0,0));
    mesh.addVertex(ofVec3f(ofGetWidth(),0));
    mesh.addColor (ofColor(0,0,0,255));
    mesh.addVertex(ofVec3f(ofGetWidth(),ofGetHeight()));
    mesh.addColor (ofColor(0,0,0,255));
    mesh.addVertex(ofVec3f(0,ofGetHeight()));
    mesh.addColor (ofColor(0,0,0,0));
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_FAN);
    
    initialRectangles();
    
    // ---------- LINE PARTICLE ----------
    
    for (int i = 0; i < 200; i++){
        particle myParticle;
        vx = ofRandom(-2,2);
        vy = 0;
        myParticle.setInitialCondition(ofGetWidth()/2,ofGetHeight()-200,vx, vy);
        
        // more interesting with diversity :)
        // uncomment this:
        myParticle.damping = ofRandom(0.000, 0.000);
        particles.push_back(myParticle);
    }

}

//--------------------------------------------------------------
void ofApp::update(){
    
    // ------------ EASING ------------
    
    auto duration = 2.5f;
    auto endTime = initTime + duration;
    auto now = ofGetElapsedTimef();
    positions[0] = ofxeasing::map_clamp(now, initTime, endTime, 0, endPosition, &ofxeasing::cubic::easeOut);
    
    myRectangle.update();
    myRectangle.interpolateByPct(pct);		// go between pta and ptb
    myRectangle1.interpolateByPct(pct);		// go between pta and ptb
    myRectangle1.update();
    
    // ----- SERIAL COMMUNICATION -----
    
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
    
    // --------- PARTICLE ---------
    
    for (int i = 0; i < particles.size(); i++){
        //particles[i].resetForce();
        //particles[i].addForce(0,0.04);  // gravity
        //particles[i].addDampingForce();
        particles[i].update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    // ------------------ WIDE LINES ---------------------
    
    if(easeWiderRect){
        
        ofSetColor(255);
        auto h = ofGetHeight();
        auto y = ofGetHeight()/2;
        auto i = 0;

        ofDrawRectangle(0, y, positions[0], h);
        ofLog(positions[0]);
   
    } else {
        initTime = ofGetElapsedTimef();
//        ofSetColor(0);
//        auto h = ofGetHeight();
//        auto y = ofGetHeight()/2;
//        auto i = 0;
//        ofDrawRectangle(0, y, positions[0], h);
//        ofLog(positions[0]);
    }
    
    // ----------------- PATTERNED LINES -------------------
    
    if(drawLines){
        for (int i = 0; i < 50; i++){
            ofSetLineWidth(thickness);
            ofSetColor(255);
            ofDrawLine(xPos0-distance * 10 + (distance * i), -10, xPos1-distance * 10 + (distance * i), yPos+10);
            //ofDrawLine(0, xPos0-distance * 5 + (distance * i), ofGetWidth(),xPos0-distance * 5 + (distance * i));
            
            if(xPos0 > distance + xPosOffset) {
                xPos0 = xPosOffset;
                xPos1 = 0;
            }
            if(lineRotation){
                xPos0 = xPosOffset + speed;
            }
            
            xPos0 = xPos0 + speed;
            xPos1 = xPos1 + speed;
        }

    } else {
        xPos0 = 0;
        xPos1 = 0;
    }
    
    // -------------------- EASING -----------------------
    
    if(easeLines){
      
        float dx = ofGetWidth()/2+300 - xPos2;
        float dx2 = ofGetWidth() - xPos4;
        float easing = 0.02;

        ofSetLineWidth(thickness);
        ofSetColor(255);
        ofDrawLine(xPos2, 0, xPos2, ofGetHeight());
        ofDrawLine(xPos4, 0, xPos4, ofGetHeight());
        ofDrawLine(xPos3, 0, xPos3, ofGetHeight());
        
        xPos2 += dx * easing;
        xPos3 -= dx * easing;
        xPos4 += dx * easing;

    } else {
        xPos2 = 0;
        xPos3 = ofGetWidth();
    }

    // --------------- TWO WIDER RECTANLES ----------------
    
    if(drawRectangles){
        myRectangle.draw();
        myRectangle1.draw();

        //pct += 0.01f;		// increase by a certain amount
        pct += speed/50;
        if (pct > 1) {
            pct = 0;	// just between 0 and 1 (0% and 100%)
        }
    } else {
        initialRectangles();
    }
    
    if(!bHide){
        gui.draw();
        ofShowCursor();
    }
    
    // ------------------ LINE PARTICLES -------------------
    
    if(drawParticles){
        for (int i = 0; i < particles.size(); i++){
            particles[i].draw();
            particles[i].rectH += ofRandom(1,2);
        }
    } else {
        for (int i = 0; i < particles.size(); i++){
            //initialize positions
            //particles[i].pos.x = ofGetWidth()/2;
            particles[i].pos.x = ofRandom(ofGetWidth());
            particles[i].pos.y = ofGetHeight();
            
            particles[i].rectH = 1;
            particles[i].rectW = ofRandom(1,3);
        }
    }
    
    // ------------------ GRADIENT MESH -------------------
    
    if(gradient){
        mesh.draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed  (int key){
    
    // ---------------- GRAPHICS CONTROL ------------------
    
    if(key == 'q'){
        drawLines = !drawLines;
        xPos0 = 0;
        xPos1 = 0;
    }
    else if(key == 'w'){
        easeLines =! easeLines;
    }
    else if(key == 'e'){
        drawRectangles =! drawRectangles;
    }
    else if(key == 'r'){
        easeWiderRect =! easeWiderRect;
    }
    else if(key == 't'){
        drawParticles =! drawParticles;
    }
    else if(key == 'y'){
        gradient =! gradient;
    }
    else if(key == 'i'){
        lineRotation =! lineRotation;
    }

    // ------------ STEPPER MOTORS CONTROL ----------------
    
    else if(key == 's'){
        serial.writeByte('s');  // stop All
    }
    else if(key == 'a'){
        serial.writeByte('a');  // move All
    }
    else if(key == 'd'){
        serial.writeByte('d');  // direction
    }
    else if(key == 'f'){
        serial.writeByte('f');  // fuss
    }
    else if(key == 'p'){
        serial.writeByte('p');  // fuzz
    }
    else if(key == 'o'){
        serial.writeByte('o');  // speedDown
    }
    else if(key == 'c'){
        serial.writeByte('c');  // cancel various mode
    }
    else if(key == 'v'){
        serial.writeByte('v');  // various mode
    }
    else if(key == 'b'){
        serial.writeByte('b');  // back and forth
    }
    else if(key == 'z'){
        serial.writeByte('z');  // back and forth
    }
    else if(key == 'x'){
        serial.writeByte('x');  // back and forth
    }
    
    // ------------ SPEED CONTROL ----------------
    
    else if(key == '`'){
        speed = 0;
    }
    else if(key == '1'){
        speed = 0.1;
        distance = 1280;
    }
    else if(key == '2'){
        speed = 0.1;
        distance = 640;  // back and forth
    }

    // ------------ GUI CONTROL ----------------
    
    else if(key == 'h'){ // hide gui
        bHide = !bHide;
        ofHideCursor();
    }
    else if(key == 'l'){
        gui.loadFromFile("settings.xml");
    }
}
//--------------------------------------------------------------
void ofApp::initialRectangles(){
    ofSetRectMode(OF_RECTMODE_CENTER);
    myRectangle.posa.x = ofGetWidth();
    myRectangle.posa.y = ofGetHeight()/2;
    myRectangle.posb.x = 0;
    myRectangle.posb.y = ofGetHeight()/2;
    myRectangle.interpolateByPct(0);	// start at 0 pct
    
    myRectangle1.posa.x = 0;
    myRectangle1.posa.y = ofGetHeight()/2;
    myRectangle1.posb.x = ofGetWidth();
    myRectangle1.posb.y = ofGetHeight()/2;
    myRectangle1.interpolateByPct(0);	// start at 0 pct
    
    pct = 0;
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

