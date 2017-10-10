#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(0, 0, 0);

//    ofSetFrameRate(30);

//    vid_calm.load("test2.mov");
    vid_calm.load("720_30fps.mp4");
    vid_calm.play();
    vid_calm.setLoopState(OF_LOOP_NORMAL);


}

//--------------------------------------------------------------
void ofApp::update(){
    vid_calm.update();

}

//--------------------------------------------------------------
void ofApp::draw(){
    vid_calm.draw(0, 0);
//    vid_calm.draw(<#float x#>, <#float y#>, <#float w#>, <#float h#>)

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
