#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    //yaml.load("camera_settings.yml");
    
    int cameraToUse;
    //yaml.doc["cameraToUse"] >> cameraToUse;
    
    //[notice ] productID 0 = 082d
    //[notice ] vendorID 0 = 046d
    
    // CHECK bin/data/camera_settings.yaml for some proper values
//    int vendorId = 0x46d, productId = 0x821, interfaceNum = 0x2;
    int vendorId = 0x46d, productId = 0x82d, interfaceNum = 0x2;

    unsigned int locationID = 0x14100000;
    cameraName = "HD Pro Webcam C920 #8";
    camWidth = 1920;
    camHeight = 1080;
    //yaml.doc["cameras"][cameraToUse]["vendorId"] >> vendorId;
    //yaml.doc["cameras"][cameraToUse]["productId"] >> productId;
    //yaml.doc["cameras"][cameraToUse]["interfaceNum"] >> interfaceNum;
    //yaml.doc["cameras"][cameraToUse]["name"] >> cameraName;
    //yaml.doc["cameras"][cameraToUse]["width"] >> camWidth;
    //yaml.doc["cameras"][cameraToUse]["height"] >> camHeight;
  
    
    int deviceId = 0;
    vector<string> availableCams = vidGrabber.listVideoDevices();

    for(int i = 0; i < availableCams.size(); i++){
        ofLog()<<i<<" availableCams.at(i) "<<availableCams.at(i);
        if(availableCams.at(i) == cameraName){
            deviceId = i;
        }
    }
    
    vidGrabber.setDeviceID(deviceId);
    
    vidGrabber.setup(camWidth, camHeight);

    focus = 0.1;
    
     uvcControl.useCamera2(vendorId, productId, interfaceNum,(int) locationID);
//    uvcControl.useCamera(vendorId, productId, interfaceNum); 
//    uvcControl.setAutoExposure(true);
    controls = uvcControl.getCameraControls();
    
    ofLog()<<"setup done";
}

//--------------------------------------------------------------
void testApp::update(){
    vidGrabber.update();
    if(vidGrabber.isFrameNew())
    {
        tex.loadData(vidGrabber.getPixels());
    }
    controls = uvcControl.getCameraControls();
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(0);
    tex.draw(0,0, camWidth, camHeight);

    ofSetColor(255);
    stringstream s;
    s << "Camera name: " << cameraName << "\nAuto-exposure: " << uvcControl.getAutoExposure() << "\nAuto-focus: " << uvcControl.getAutoFocus() <<
    "\nAbsolute focus: " << uvcControl.getAbsoluteFocus() <<
    "\nPress 'e' to toggle auto-exposure.\nPress 'f' to toggle auto-focus.\nPress +/- to set absolute foucs.\n\nResult of GET_STATUS for each feature\non this camera:\n";
        
    
    for(int i = 0; i < controls.size(); i++){
    
        s << controls.at(i).name << ": " << controls.at(i).status << "\n";

    }
    
    
    ofDrawBitmapString(s.str(), 650, 10);

}

void testApp::exit(){
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    if(key == 'e'){
        uvcControl.setAutoExposure(!uvcControl.getAutoExposure());
    }
    
    if(key == 'f'){
        uvcControl.setAutoFocus(!uvcControl.getAutoFocus());
    }
    
    if(key == '='){
        focus += 0.1;
        uvcControl.setAbsoluteFocus(focus);
    }
    
    if(key == '-'){
        focus -= 0.1;
        uvcControl.setAbsoluteFocus(focus);

    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}