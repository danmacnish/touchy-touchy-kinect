#include "ofApp.h"

//Connect to Kinect
//Get the latest depth image and assign to openCV grayscale image
//display to screen

//--------------------------------------------------------------
void ofApp::setup(){
    //set logging level
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    //add listener methods for GUI sliders
    nearClip.addListener(this, &ofApp::nearClipChanged);
    farClip.addListener(this, &ofApp::farClipChanged);
    
    //init gui
    gui.setup();
    //add slider to GUI for near clipping level, init slider to value of 500mm, range 500 to 4000
    gui.add(nearClip.setup("near clipping", 500, 500, 4000));
    //add slider to GUI for far clipping level, init slider to value of 500mm, range 500 to 4000
    gui.add(farClip.setup("far clipping", 4000, 500, 4000));
    
    //init kinect
    kinect.init();
    kinect.open();
    
    //log that we are connected
    if(kinect.isConnected()) {
        ofLogNotice() << "connected to Kinect";
    } else {
        ofLogNotice() << "failed to connect";
    };
    
    //init video recorder
    ofAddListener(recorder.outputFileCompleteEvent, this, &ofApp::recordingComplete);
    fileName = "kinect data";
    fileExtension = ".gif";
    // override the default codecs if you like
    // run 'ffmpeg -codecs' to find out what your implementation supports (or -formats on some older versions)
    recorder.setVideoCodec("gif");
    recorder.setPixelFormat("gray");
    recorder.setOutputPixelFormat("gray");
    //recorder.setVideoBitrate("800k");
    
    //set angle of kinect
    angle = 0;
    kinect.setCameraTiltAngle(angle);
    
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
        if(recording) {
            bool success = recorder.addFrame(depthImage.getPixels());
            if (!success) {
                ofLogWarning("This frame was not added!");
            }
        }
    }
    
    // Check if the video recorder encountered any error while writing video frame or audio smaples.
    if (recorder.hasVideoError()) {
        ofLogWarning("The video recorder failed to write some frames!");
    }
    //update cv images
    //depthImage.flagImageChanged();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255, 255, 255);
    
    //draw depth image on screen
    depthImage.draw(300,10,400,300);
    
    //draw gui
    gui.draw();
    
    //write framerate and other info to screen
    stringstream ss;
    ss << "Framerate: " << ofToString(ofGetFrameRate(),0) << "\n";
    ss << "video queue size: " << recorder.getVideoQueueSize() << endl;
    ss << "width: " << depthImage.getWidth() << " height: " << depthImage.getHeight() << endl;
    ss << "Up key: tilt kinect up \n";
    ss << "Down key: tilt kinect down \n";
    ss << "press r to record, c to close video file";
    ofDrawBitmapString(ss.str().c_str(), 20, 100);

}

//-------------------------------------------------------------
void ofApp::nearClipChanged(float & val) {
    //set depth clipping. sets scale factor from raw depth data (12 bit) to grayscale (8 bit)
    //i.e. setting a smaller depth range will increase depth resolution of grayscale image
    kinect.setDepthClipping(val, farClip);
    
}

//-------------------------------------------------------------
void ofApp::farClipChanged(float & val) {
    //set depth clipping. sets scale factor from raw depth data (12 bit) to grayscale (8 bit)
    //i.e. setting a smaller depth range will increase depth resolution of grayscale image
    kinect.setDepthClipping(nearClip, val);
    
}

//--------------------------------------------------------------
void ofApp::recordingComplete(ofxVideoRecorderOutputFileCompleteEventArgs& args){
    cout << "The recoded video file is now complete." << endl;
}

//exit-------------------------------------------------

void ofApp::exit() {
    kinect.setCameraTiltAngle(0);
    kinect.close();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch(key) {
        case OF_KEY_UP:
            angle++;
            if(angle>30) angle=30;
            kinect.setCameraTiltAngle(angle);
            break;
            
        case OF_KEY_DOWN:
            angle--;
            if(angle<-30) angle=-30;
            kinect.setCameraTiltAngle(angle);
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    if(key=='r'){
        recording = !recording;
        if(recording && !recorder.isInitialized()) {
            recorder.setup(fileName+ofGetTimestampString()+fileExtension, depthImage.getWidth(), depthImage.getHeight(), 30); // no audio
            
            // Start recording
            recorder.start();
        }
        else if(!recording && recorder.isInitialized()) {
            recorder.setPaused(true);
        }
        else if(recording && recorder.isInitialized()) {
            recorder.setPaused(false);
        }
    }
    if(key=='c'){
        recording = false;
        recorder.close();
    }
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
