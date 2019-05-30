#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    vidGrabber.setDeviceID(1); // or 1, or 2, ...

    vidGrabber.setup(camWidth, camHeight);
    
     uvcControl.useCameraByDeviceIndex(4); // <- convenient!
    
    // or, even more conveniently,
    // uvcControl.useFirstCamera();
    
    // if (for some odd reason) you'd like to get & set the vendor ID and product ID yourself:
    // int vendorID, productID;
    // tie(vendorID, productID) = ofxUVCProber::getVendorIDAndProductIDByDeviceIndex(0);
    // uvcControl.useCamera(vendorID, productID, 0x00);
    
    // if you prefer using names instead of indices:
    // vector<string> myCameraNames = ofxUVCProber::getDeviceNameList();
    // uvcControl.useCameraByDeviceName(myCameraNames[0]); // or "myAwesomeCam" if you already knew it by name!
    
    // again, if you'd like to set the ID's manually from device name:
    // int vendorID, productID;
    // tie(vendorID, productID) = ofxUVCProber::getVendorIDAndProductIDByDeviceName(myCameraNames[0]);
    // uvcControl.useCamera(vendorID, productID, 0x00);
    
    // hey, I don't want your stupid getters, I want all the RAW data!
    // vector<tuple<string,int,    int, string>> bigFatList = ofxUVCProber::getList();
    //                ^     ^       ^     ^
    //               name vendID prodID uniqID
    // now say you want the unique ID of the 3rd camera:
    // string cam3UniqueID = get<3>(bigFatList[2]); // <- don't run this unless u have 3 webcams plugged in!
    
    
    uvcControl.setAutoExposure(false);
    controls = uvcControl.getCameraControls();
}

//--------------------------------------------------------------
void ofApp::update(){
    vidGrabber.update();
    controls = uvcControl.getCameraControls();
}

//--------------------------------------------------------------
void ofApp::draw(){

    vidGrabber.draw(0,0,ofGetWidth(),ofGetWidth()*(camHeight/float(camWidth)));
    
    ofSetColor(255);
    stringstream s;
    s << "Auto-exposure: " << uvcControl.getAutoExposure() 
    << "\nAuto-focus: " << uvcControl.getAutoFocus() 
    << "\nAuto-WB: " << uvcControl.getAutoWhiteBalance() 
    << "\nAbsolute focus: " << uvcControl.getAbsoluteFocus() 
    << "\nPress 'e' to toggle auto-exposure.\nPress 'f' to toggle auto-focus.\nPress +/- to set absolute foucs.\n\nResult of GET_STATUS for each feature\non this camera:\n";
    
    for(int i = 0; i < controls.size(); i++){
        s << controls.at(i).name << ": " << controls.at(i).status << "\n";
    }
    
    ofDrawBitmapString(s.str(), 650, 10);

}

void ofApp::exit(){
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'e'){
        uvcControl.setAutoExposure(!uvcControl.getAutoExposure());
    }
    if(key == 'f'){
        uvcControl.setAutoFocus(!uvcControl.getAutoFocus());
    }
    if(key == '='){
        uvcControl.setAbsoluteFocus(uvcControl.getAbsoluteFocus()+0.1);
    }
    if(key == '-'){
        uvcControl.setAbsoluteFocus(uvcControl.getAbsoluteFocus()-0.1);

    }
    if(key == 'q'){
        uvcControl.setAutoWhiteBalance(!uvcControl.getAutoWhiteBalance());
    }
    if(key == 'w'){
        uvcControl.setWhiteBalance(uvcControl.getWhiteBalance()+0.1);
    }
    if(key == 's'){
         uvcControl.setWhiteBalance(uvcControl.getWhiteBalance()-0.1);
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
