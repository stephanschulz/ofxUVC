#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxDropdown.h"
#include "ofxVideoGrabber.h"
#include "UVC_controller.h"


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
    
    int camID;
    int camWidth, camHeight;
    ofxVideoGrabber vidSource;
     UVC_controller uvcController;
    
    bool bShowGUI;
    private:
        bool bUVCInitialized;
        float initTimer;
    
    ofxPanel gui_vidSource;
    ofParameter<string> usb_selectedUid = {"Selected Video Source", ""};
    unique_ptr<ofxDropdown> usb_strDropdown;

    ofEventListener uidListener;
    void setupDropdown();
    void setupListener();
    void selectedCameraChanged(string &);
};
