#include "ofApp.h"

/*
 - name: 292A-IPC-AR0330
 vendorId : 0x0c45
 productId: 0x6366
 interfaceNum: 0x00
 width: 1920
 height: 1080
 
 292A-IPC-AR0330:
 
 Model ID:	UVC Camera VendorID_3141 ProductID_25446
 Unique ID:	0x145000000c456366
 
 http://kurokesu.com/main/2016/01/16/manual-usb-camera-settings-in-linux/
 
 list available devices: 
 ffmpeg -f avfoundation -list_devices true -i ""
 or
 ffmpeg -f qtkit -list_devices true -i ""
 
 UVC codes
 http://libuvcc.dm9.se/group__uvcc__plf__returns.html
 
 */

//for logitech c920 set #define USE_C920 in UVCCameraControl.h
//--------------------------------------------------------------
void ofApp::setup(){
    
//    unsigned short int x = 65472;
//    short int y = *(short int*)&x;
//    
//    cout<<"x "<<x;
//    printf("%d\n", y);
    
    collectCameraInfo();
    
      int camID = 1;
    camWidth = 1920; //640;
    camHeight = 1080;//480;
    

    vidSource.setVerbose(false);
    vidSource.setDeviceID(camID);
    // vidSource.setDesiredFrameRate(60);
//    vidSource.initGrabber(camWidth,camHeight);
    vidSource.setup(camWidth,camHeight);
   
    ofLog()<<"camID "<<camID<<", allLocationIDs[camID] "<<allLocationIDs[camID];
    uvcController.setup("camera",camID,allLocationIDs[camID]);
    
 
    gui_UVCcontroller.setup("UVC");
//    gui_UVCcontroller.setDefaultWidth(300);
//    gui_UVCcontroller.setWidthElements(300);
  gui_UVCcontroller.setName("UVC");
   
    gui_UVCcontroller.setPosition(10,10);
      
    gui_UVCcontroller.add(uvcController.parameters);
    gui_UVCcontroller.loadFromFile("gui_UVCcontroller.xml");
//     gui_UVCcontroller.setWidthElements(100);
//    gui_UVCcontroller.minimizeAll();
    
    uvcController.initDone = true;
    uvcController.init();


    bShowGUI = true;
}

//--------------------------------------------------------------
void ofApp::update(){
    
    vidSource.update();
    if(vidSource.isFrameNew())
    {
        tex.loadData(vidSource.getPixels());
    }
    
    uvcController.bShowGUI = bShowGUI;
    uvcController.update();
}

//--------------------------------------------------------------
void ofApp::draw(){

//    vidSource.draw(0, 0);
//    tex.draw(0,0, ofGetWidth(), ofGetHeight());
    tex.draw(0,0, camWidth/1.3, camHeight/1.3);
    
    if(bShowGUI){
        gui_UVCcontroller.draw();
    }
}

void ofApp::exit(){
}

void ofApp::collectCameraInfo(){
    allCameraNames.clear();
    allCameraNames = cameraDeviceManager.listVideoDevicesByName();
    
    if(allCameraNames.size() > 0){
        for(int i=0; i<allCameraNames.size();i++){
            ofLog()<<" device "<<i<<" = "<<allCameraNames[i];
        }
    }else{
        ofLog()<<"no devices found";
    }
    
    allUniqueIDs.clear();
    allLocationIDs.clear();
    allUniqueIDs = cameraDeviceManager.listVideoDevicesByUniqueID();
    
    if(allUniqueIDs.size() > 0){
        for(int i=0; i<allUniqueIDs.size();i++){
            
            int str_length = allUniqueIDs[i].length();
            //ofLog()<<"str_length "<<i<<" = "<<str_length;
            int vendorID_length = 4;
            int productID_length = 4;
            
            string productID = allUniqueIDs[i].substr(str_length - productID_length                   ,productID_length);
            ofLog()<<"productID "<<i<<" = "<<productID;
            
            string vendorID = allUniqueIDs[i].substr(str_length - vendorID_length - productID_length  ,vendorID_length);
            ofLog()<<"vendorID "<<i<<" = "<<vendorID;
            
            string locationID = allUniqueIDs[i].substr(0                                               ,str_length - vendorID_length - productID_length);
            
            
            // int hexAddrToInt = ofHexToInt(locationID);
            std::stringstream converter(locationID);
            unsigned int hexAddrToInt;
            converter >> std::hex >> hexAddrToInt;
            
            allLocationIDs.push_back(hexAddrToInt);
            ofLog()<<"allLocationIDs[i] "<<i<<" = "<<allLocationIDs[i];
            ofLog()<<"locationID "<<i<<" = "<<locationID;
            ofLog()<<"full UniqueID "<<i<<" = "<<allUniqueIDs[i];
        }
    }else{
        ofLog()<<"no devices found";
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
//    if(key == 'e'){
//        uvcControl.setAutoExposure(!uvcControl.getAutoExposure());
//    }
//    
    if(key == 'f'){
        ofToggleFullscreen();
         gui_UVCcontroller.saveToFile("gui_UVCcontroller.xml");
    }
//
//    if(key == '='){
//        focus += 0.1;
//        uvcControl.setAbsoluteFocus(focus);
//    }
//    
//    if(key == '-'){
//        focus -= 0.1;
//        uvcControl.setAbsoluteFocus(focus);
//
//    }

    if(key == 'g') bShowGUI = !bShowGUI;
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
