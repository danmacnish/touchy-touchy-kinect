#include "ofApp.h"

//Connect to Kinect
//Get the latest depth image and assign to openCV grayscale image
//display to screen

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);
    kinect.init();
    kinect.open();
    
    //log that we are connected
    if(kinect.isConnected()) {
        ofLogNotice() << "connected to Kinect";
    } else {
        ofLogNotice() << "failed to connect";
    };
    
    //allocate mem for depth image
    depthImage.allocate(kinect.width, kinect.height);

}

//--------------------------------------------------------------
void ofApp::update(){
    ofBackground(100, 100, 100);
    
    kinect.update();
    
    //if there is a new depth frame available
    if(kinect.isFrameNewDepth()) {
        //get the depth frame
        depthImage.setFromPixels(kinect.getDepthPixels());
    }
    
    //update cv images
    //depthImage.flagImageChanged();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255, 255, 255);
    
    //draw depth image on screen
    depthImage.draw(10,10,400,300);
    
    //write framerate and other info to screen
    stringstream ss;
    ss << "Framerate: " << ofToString(ofGetFrameRate(),0) << "\n";
    ofDrawBitmapString(ss.str().c_str(), 20, 20);

}

//exit-------------------------------------------------

void ofApp::exit() {
    kinect.setCameraTiltAngle(0);
    kinect.close();
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
