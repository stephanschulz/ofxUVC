#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
     camWidth = 1280;
     camHeight = 720;

//    camWidth = 3840;
//    camHeight = 2160;
  
    gui_vidSource.setup("video source","gui_vidSource.json");
    setupDropdown();
    gui_vidSource.add(usb_strDropdown.get());
    setupListener();
    gui_vidSource.loadFromFile("gui_vidSource.json");

    bUVCInitialized = false;
    initTimer = ofGetElapsedTimef();
    
    bShowGUI = true; //only when  uvcController.bShowGUI is true does GUI have any effect
    
    ofLog()<<ofGetTimestampString()<<" setup() done";
}

//--------------------------------------------------------------
void ofApp::update(){
    // Add camera initialization check
    if (!bUVCInitialized && usb_selectedUid.get() != "") {
        // Wait 2 seconds after setup before initializing UVC controls
        if (ofGetElapsedTimef() - initTimer > 3.0) {
            uvcController.setup("camera", usb_selectedUid);
            uvcController.init();
            // Populate GUI parameters based on available controls
            uvcController.initTimer = ofGetElapsedTimef();
            bUVCInitialized = true;
            ofLog()<<ofGetTimestampString()<<" bUVCInitialized == true";
        }
    }
    
   if(vidSource.isInitialized()) vidSource.update();
    
    if(bUVCInitialized){
        uvcController.bShowGUI = bShowGUI;
        uvcController.update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    vidSource.draw(0,0,ofGetWidth(),ofGetWidth()*(camHeight/float(camWidth)));

    if(bShowGUI){
        if(bUVCInitialized) uvcController.gui_UVCcontroller.draw();
    }
    
    gui_vidSource.draw();
}

void ofApp::setupDropdown()
{
    usb_strDropdown = make_unique<ofxDropdown>(usb_selectedUid);
    usb_strDropdown->disableMultipleSelection();
    usb_strDropdown->enableCollapseOnSelection();

    // get back a list of devices.
    vector<ofVideoDevice> devices = vidSource.listDevices();

    for (size_t i = 0; i < devices.size(); i++)
    {
        if (devices[i].bAvailable)
        {
            usb_strDropdown->add(devices[i].serialID, devices[i].deviceName + " _ " + devices[i].serialID);
        }
    }
}
void ofApp::setupListener()
{

    uidListener = usb_selectedUid.newListener(this, &ofApp::selectedCameraChanged);
}

void ofApp::selectedCameraChanged(string &)
{
    ofLog() << "usbCamera: usb_onChange usb_selectedUid " << usb_selectedUid;

    if (vidSource.isInitialized() == true)
    {
        vidSource.close();
    }
    ofLog() << "camWidth " << camWidth << "x" << camHeight;
    //        vidSource.setDeviceID(camID);
    vidSource.setUniqueID(usb_selectedUid);
    vidSource.setup(camWidth, camHeight);

    bUVCInitialized = false;
    initTimer = ofGetElapsedTimef();
    
}

void ofApp::exit(){
    gui_vidSource.saveToFile("gui_vidSource.json");
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if(key =='g'){
        bShowGUI = !bShowGUI;
        if(bShowGUI == false){
            gui_vidSource.saveToFile("gui_vidSource.json");
            uvcController.gui_UVCcontroller.saveToFile("gui_UVCcontroller.json");
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
