#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    camID = 0;
    vidGrabber.setDeviceID(camID); // or 1, or 2, ...
    
    camWidth = 640;
    camHeight = 480;
    vidGrabber.setup(camWidth, camHeight);
    
    uvcController.setup("camera", camID); //,camID,allLocationIDs[camID]);
    
    bShowGUI = true; //only when  uvcController.bShowGUI is true does GUI have any effect
    
    gui_UVCcontroller.setup("UVC");
    //    gui_UVCcontroller.setPosition(gui_x+=gui_w,gui_y);
    gui_UVCcontroller.setPosition(10, 10);
    gui_UVCcontroller.add(uvcController.parameters);
    gui_UVCcontroller.loadFromFile("gui_UVCcontroller.xml");
    //    gui_UVCcontroller.minimizeAll();
    uvcController.init();
    

}

//--------------------------------------------------------------
void ofApp::update(){
    vidGrabber.update();
    
    uvcController.bShowGUI = bShowGUI;
    uvcController.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
<<<<<<< HEAD
    
    vidGrabber.draw(0,0,ofGetWidth(),ofGetWidth()*(camHeight/float(camWidth)));
=======
    ofSetColor(255);
    vidGrabber.draw(0,0,320,240);
//    vidGrabber.draw(0,0,ofGetWidth(),ofGetWidth()*(camHeight/float(camWidth)));
>>>>>>> 809309ed6d91ee018deab675565f9a73ad629c10
    
    if(bShowGUI){
        gui_UVCcontroller.draw();
    }
    
}

void ofApp::exit(){
     
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if(key =='g'){
        bShowGUI = !bShowGUI;
        if(bShowGUI == false){
            gui_UVCcontroller.saveToFile("gui_UVCcontroller.xml");
        }
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
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
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}
