#pragma once

#include "ofMain.h"



#include "ofxGui.h"


//check inside UVCCameraControl if #define USE_C920 is set
#include "UVC_controller.h"
#include "ofxCameraDeviceTree.h"


class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    void exit();
    
//     ofVideoGrabber vidSource;
    ofQTKitGrabber vidSource;
     ofTexture tex;
    
    int camWidth, camHeight;
    
    bool bShowGUI;
    
    void collectCameraInfo();
    UVC_controller uvcController;
     ofxPanel gui_UVCcontroller;
    
    ofxCameraDeviceTree cameraDeviceManager;
    vector<string> allCameraNames;
    vector<string> allUniqueIDs;
    vector<unsigned int> allLocationIDs;
    
};
