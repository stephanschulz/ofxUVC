//
//  UVC_controller.h
//
//  Created by Stephan Schulz on 2015-10-20.
//
//

#ifndef UVC_controller_h
#define UVC_controller_h

#include "ofxUVCProber.h" // <- To use the prober, you need include this header BEFORE including "ofxUVC.h"!
#include "ofxUVC.h"

#include "ofParameterGroup.h"
#include "ofParameter.h"

class UVC_controller
{
    
    
public:
    
    bool bDebug_UVC_controller = false;
    
    ofEventListeners listeners;
    
    ofxUVC uvcControl;
    
    vector<ofxUVCControl> controls;
    
    ofxPanel gui_UVCcontroller;
    
    ofParameter<bool> getExposureValues;
    ofParameter<bool> getFocusValues;
    ofParameter<bool> getWhiteBalanceValues;
    
    ofParameter<bool> bChangeUsbCamControlls;
    ofParameter<bool> getCamValues;
    ofParameter<bool> aFocus;
    ofParameter<bool> aExposure;
    ofParameter<bool> aWhiteBalance;
    
    ofParameter<bool> aLed,old_aLed;
    
    ofParameter<float> focusValue;
    ofParameter<float> exposureTimeAbsolute;
    ofParameter<float> whiteBalanceValue;
    ofParameter<float> gainValue;
    ofParameter<float> sharpValue;
    ofParameter<float> saturationValue;
    ofParameter<float> contrastValue;
    ofParameter<float> brightnessValue;
    
    ofParameter<int> powerLineFrequency;
    ofParameter<bool> backLightCompensation;
    ofParameter<bool> aHue;
    ofParameter<float> hueValue;
    ofParameter<float> gammaValue;
    
    ofParameter<float> zoomAbsoluteValue;
    ofParameter<float> panValueAbsolute;
    ofParameter<float> tiltValueAbsolute;
    ofParameter<float> rollValue;
    
    ofParameter<float> incrementalExposureValue;
    ofParameter<float> scanningModeValue;
    ofParameter<int> aeMode;
    ofParameter<float> aePriorityValue;
    ofParameter<float> exposureTimeRelativeValue;
    ofParameter<float> focusRelativeValue;
    ofParameter<float> irisAbsoluteValue;
    ofParameter<float> irisRelativeValue;
    ofParameter<float> privacyValue;
    ofParameter<float> focusSimpleValue;
    ofParameter<float> digitalWindowValue;
    ofParameter<float> regionOfInterestValue;

    ofParameter<bool> printDefaults;
    
    bool bShowGUI;
    bool initDone;
    ofParameter<string> initDone_str;
    int initStage;
    float initTimer;
    float initStartTime;
    float initDuration;
    float lastControlSetTime;
    float controlSetDelay = 0.1; // 100ms delay between setting controls
    float autoModeDelay = 0.5;   // 500ms delay after setting auto modes
    float relatedControlDelay = 0.2; // 200ms delay between related controls
    float cameraInitDelay = 1.0; // 1 second delay after camera initialization
    bool initValuesStarted = false;
    int currentControlIndex = 0;
    float lastAutoModeSetTime = 0;
    bool autoModesSet = false;
    float cameraInitTime = 0;
    bool cameraInitialized = false;
    int camID = -1;
    string uniqueID = "";
    
    //    int vendorId, productId;
    
    //    void setup(string _name, int _camID, unsigned int locationID, int _vendorId, int _productId){
    UVC_controller(){
        
        getCamValues = false;
        
        
    }
    
    void setup(string _name, string _uniqueID) {
        uniqueID = _uniqueID;
        gui_UVCcontroller.setup(_name,"gui_UVCcontroller.json");
        gui_UVCcontroller.setPosition(10,50);
        // Log the UID we're trying to use
        ofLog() << "Attempting to use camera with UID: " << _uniqueID;
        
        // Check if the UID matches any known camera format
        if (_uniqueID.find("0x") == string::npos) {
            ofLogError() << "Invalid UID format. UID should start with '0x'";
            return;
        }
        
        // Get list of available cameras before trying to use the camera
        auto cams = ofxUVCProber::getList();
        bool cameraFound = false;
        
        for (size_t i = 0; i < cams.size(); i++) {
            string name = std::get<0>(cams[i]);
            int vendorID = std::get<1>(cams[i]);
            int productID = std::get<2>(cams[i]);
            string camUID = std::get<3>(cams[i]);
            int locationID = std::get<4>(cams[i]);
            
            ofLog() << "Available camera: " << name << ": UID = " << camUID 
                     << ", VendorID = " << vendorID 
                     << ", ProductID = " << productID;
            
            if (camUID == _uniqueID) {
                cameraFound = true;
                ofLog() << "Found matching camera: " << name;
            }
        }
        
        if (!cameraFound) {
            ofLogError() << "Camera with UID " << _uniqueID << " not found in available cameras";
            return;
        }
        
        // Try to initialize the camera
        try {
        uvcControl.useCameraByUID(_uniqueID);
            ofLog() << "Successfully initialized camera with UID: " << _uniqueID;
        } catch (const std::exception& e) {
            ofLogError() << "Failed to initialize camera with UID: " << _uniqueID;
            ofLogError() << "Error: " << e.what();
        }
    }
    
    void setup(string _name, int _camID) {
        camID = _camID;
        gui_UVCcontroller.setup(_name,"gui_UVCcontroller.json");
        gui_UVCcontroller.setPosition(10,50);
        uvcControl.useCameraByDeviceIndex(_camID);
    }
    
    void init(){
        ofLog() << "init()";
        
        controls = uvcControl.getCameraControls();
        
    gui_UVCcontroller.setPosition(10, 10);
   
        // Populate GUI based on available controls
        populateGUIBasedOnControls();
        
         gui_UVCcontroller.loadFromFile("gui_UVCcontroller.json");

        initStage = 0;
        initDone = false;
        initStartTime = ofGetElapsedTimef();
        initTimer = ofGetElapsedTimef();
        initDuration = 3;
        initDone_str = initDone ? "true":"false";
        
        // Set camera initialization time
        cameraInitTime = ofGetElapsedTimef();
        cameraInitialized = false;
        
        // Log camera model for debugging
        ofLog() << "Camera UID: " << uniqueID;
        ofLog() << "Camera initialized at: " << ofGetTimestampString();
    }
    
    void update(){
        float currentTime = ofGetElapsedTimef();
        
        // Wait for camera to stabilize after initialization
        if (!cameraInitialized && currentTime - cameraInitTime > cameraInitDelay) {
            cameraInitialized = true;
            ofLog() << "Camera stabilization period complete at: " << ofGetTimestampString();
        }
        
        if (!initDone && cameraInitialized) {
            if (!initValuesStarted) {
                initAllValues();
            } else {
                initAllValues();
            }
        }
        
        if (bShowGUI) {
            // changeCamSettings();
        }
    }
    
    
    // Method to check if a specific control is available
    bool isControlAvailable(const string& controlName) {
        for (const auto& control : controls) {
            if (control.name == controlName && (control.supportsGet() || control.supportsSet())) {
                return true;
            }
        }
        return false;
    }
    
    // Helper function to check if a control exists and is supported
    bool hasControl(const string& name) {
        for (const auto& control : controls) {
            if(bDebug_UVC_controller) ofLog() << "Checking control: " << control.name << " (supportsGet: " << control.supportsGet()<< ", supportsSet: " << control.supportsSet() << ")";
            if (control.name == name && (control.supportsGet() || control.supportsSet())) {
                return true;
            }
        }
        return false;
    }
    
    // Method to get control status
    ofxUVCControl* getControl(const string& controlName) {
        for (auto& control : controls) {
            if (control.name == controlName) {
                return &control;
            }
        }
        return nullptr;
    }
    
    // Method to trigger all listeners and set all controls
    void triggerAllListeners() {
        // Trigger all parameter listeners
        ofLog()<<ofGetTimestampString()<<" triggerAllListeners()";
        if (hasControl("aeMode")) uvcControl.setAutoExposure(aeMode);
        if (hasControl("exposureTimeAbsolute")) uvcControl.setExposureTimeAbsolute(exposureTimeAbsolute);
        if (hasControl("focusAuto")) {
            uvcControl.setAutoFocus(aFocus);
            uvcControl.setAbsoluteFocus(focusValue);
        }
        if (hasControl("autoWhiteBalance")) {
            uvcControl.setAutoWhiteBalance(aWhiteBalance);
            uvcControl.setWhiteBalance(whiteBalanceValue);
        }
        if (hasControl("brightness")) uvcControl.setBrightness(brightnessValue);
        if (hasControl("contrast")) uvcControl.setContrast(contrastValue);
        if (hasControl("saturation")) uvcControl.setSaturation(saturationValue);
        if (hasControl("sharpness")) uvcControl.setSharpness(sharpValue);
        if (hasControl("gain")) uvcControl.setGain(gainValue);
        if (hasControl("powerLineFrequency")) uvcControl.setPowerLineFrequency(powerLineFrequency);
        if (hasControl("backlightCompensation")) uvcControl.setBacklightCompensation(backLightCompensation);
        if (hasControl("autoHue")) uvcControl.setAutoHue(aHue);
        if (hasControl("hue")) uvcControl.setHue(hueValue);
        if (hasControl("gamma")) uvcControl.setGamma(gammaValue);
        if (hasControl("zoomAbsolute")) uvcControl.setZoomAbsolute(zoomAbsoluteValue);
        if (hasControl("pantiltAbsolute")) uvcControl.setPanTiltAbsolute(panValueAbsolute, tiltValueAbsolute);
        if (hasControl("roll")) uvcControl.setRoll(rollValue);
        if (hasControl("led")) uvcControl.setLed(aLed);
        if (hasControl("scanningMode")) uvcControl.setScanningMode(scanningModeValue);
        if (hasControl("aePriority")) uvcControl.setAePriority(aePriorityValue);
        if (hasControl("exposureTimeRelative")) uvcControl.setExposureTimeRelative(exposureTimeRelativeValue);
        if (hasControl("focusRelative")) uvcControl.setFocusRelative(focusRelativeValue);
        if (hasControl("irisAbsolute")) uvcControl.setIrisAbsolute(irisAbsoluteValue);
        if (hasControl("irisRelative")) uvcControl.setIrisRelative(irisRelativeValue);
        if (hasControl("privacy")) uvcControl.setPrivacy(privacyValue);
        if (hasControl("focusSimple")) uvcControl.setFocusSimple(focusSimpleValue);
        if (hasControl("digitalWindow")) uvcControl.setDigitalWindow(digitalWindowValue);
        if (hasControl("regionOfInterest")) uvcControl.setRegionOfInterest(regionOfInterestValue);
    }
    
    
    // New method to dynamically populate GUI based on available controls
    void populateGUIBasedOnControls() {
        ofLog()<<ofGetTimestampString()<<" populateGUIBasedOnControls()";
        
        // Print available controls for debugging
        printAvailableControls();
        
        // Add parameters based on available controls
        if (hasControl("aeMode")) {
            gui_UVCcontroller.add(aeMode.set("AE Mode", 1, 0, 3));
            listeners.push(aeMode.newListener([this](int &) { uvcControl.setAutoExposure(aeMode); }));
        }
        if(hasControl("exposureTimeAbsolute")){
            gui_UVCcontroller.add(exposureTimeAbsolute.set("exposureTimeAbsolute", 0.5, 0, 1.0));
            listeners.push(exposureTimeAbsolute.newListener([this](float &) { uvcControl.setExposureTimeAbsolute(exposureTimeAbsolute); }));
        }
        
        if (hasControl("focusAuto")) {
            gui_UVCcontroller.add(aFocus.set("autoFocus", true));
            listeners.push(aFocus.newListener([this](bool &) { uvcControl.setAutoFocus(aFocus); }));
            gui_UVCcontroller.add(focusValue.set("focusValue", 0.5, 0, 1.0));
            listeners.push(focusValue.newListener([this](float &) { uvcControl.setAbsoluteFocus(focusValue); }));
        }
        
        if (hasControl("autoWhiteBalance")) {
            gui_UVCcontroller.add(aWhiteBalance.set("autoWhiteBalance", true));
            listeners.push(aWhiteBalance.newListener([this](bool &) { uvcControl.setAutoWhiteBalance(aWhiteBalance); }));
            gui_UVCcontroller.add(whiteBalanceValue.set("whiteBalanceValue", 0.5, 0, 1.0));
            listeners.push(whiteBalanceValue.newListener([this](float &) { uvcControl.setWhiteBalance(whiteBalanceValue); }));
        }
        if (hasControl("brightness")) {
            gui_UVCcontroller.add(brightnessValue.set("brightnessValue", 0.5, 0, 1.0));
            listeners.push(brightnessValue.newListener([this](float &) { uvcControl.setBrightness(brightnessValue); }));
        }
        
        if (hasControl("contrast")) {
            gui_UVCcontroller.add(contrastValue.set("contrastValue", 0.5, 0, 1.0));
            listeners.push(contrastValue.newListener([this](float &) { uvcControl.setContrast(contrastValue); }));
        }
        
        if (hasControl("saturation")) {
            gui_UVCcontroller.add(saturationValue.set("saturationValue", 0.5, 0, 1.0));
            listeners.push(saturationValue.newListener([this](float &) { uvcControl.setSaturation(saturationValue); }));
        }
        
        if (hasControl("sharpness")) {
            gui_UVCcontroller.add(sharpValue.set("sharpValue", 0.61, 0, 1.0));
            listeners.push(sharpValue.newListener([this](float &) { uvcControl.setSharpness(sharpValue); }));
        }
        
        if (hasControl("gain")) {
            gui_UVCcontroller.add(gainValue.set("gainValue", 0.06, 0, 1.0));
            listeners.push(gainValue.newListener([this](float &) { uvcControl.setGain(gainValue); }));
        }
        
        if (hasControl("powerLineFrequency")) {
            gui_UVCcontroller.add(powerLineFrequency.set("powerFreq", 0, 0, 2));
            listeners.push(powerLineFrequency.newListener([this](int &) { uvcControl.setPowerLineFrequency(powerLineFrequency); }));
        }
        if (hasControl("backlightCompensation")) {
            gui_UVCcontroller.add(backLightCompensation.set("backLight", false));
            listeners.push(backLightCompensation.newListener([this](bool &) { uvcControl.setBacklightCompensation(backLightCompensation); }));
        }
        
        if (hasControl("autoHue")) {
            gui_UVCcontroller.add(aHue.set("autoHue", true));
            listeners.push(aHue.newListener([this](bool &) { uvcControl.setAutoHue(aHue); }));
        }
        
        if (hasControl("hue")) {
            gui_UVCcontroller.add(hueValue.set("hueValue", 0.5, 0, 1.0));
            listeners.push(hueValue.newListener([this](float &) { uvcControl.setHue(hueValue); }));
        }
        
        if (hasControl("gamma")) {
            gui_UVCcontroller.add(gammaValue.set("gammaValue", 0, 0, 1.0));
            listeners.push(gammaValue.newListener([this](float &) { uvcControl.setGamma(gammaValue); }));
        }
        
        if (hasControl("zoomAbsolute")) {
            gui_UVCcontroller.add(zoomAbsoluteValue.set("zoomAbsolute", 0, 0, 1.0));
            listeners.push(zoomAbsoluteValue.newListener([this](float &) { uvcControl.setZoomAbsolute(zoomAbsoluteValue); }));
        } else{
            ofLogNotice("UVC_controller") << "zoomAbsolute control not available";
        }
        
        if (hasControl("pantiltAbsolute")) {
            gui_UVCcontroller.add(panValueAbsolute.set("panAbsolute", 0, 0, 1.0));
            gui_UVCcontroller.add(tiltValueAbsolute.set("tiltAbsolute", 0, 0, 1.0));
            listeners.push(panValueAbsolute.newListener([this](float &) { uvcControl.setPanTiltAbsolute(panValueAbsolute, tiltValueAbsolute); }));
            listeners.push(tiltValueAbsolute.newListener([this](float &) { uvcControl.setPanTiltAbsolute(panValueAbsolute, tiltValueAbsolute); }));
        } else{
            ofLogNotice("UVC_controller") << "pantiltAbsolute control not available";
        }
        
        if (hasControl("roll")) {
            gui_UVCcontroller.add(rollValue.set("roll", 0, 0, 1.0));
            listeners.push(rollValue.newListener([this](float &) { uvcControl.setRoll(rollValue); }));
        }
        if (hasControl("led")) {
            gui_UVCcontroller.add(aLed.set("led", false));
            listeners.push(aLed.newListener([this](bool &) { uvcControl.setLed(aLed); }));
        }
        
        // Add new controls from getCameraControls()
        if (hasControl("scanningMode")) {
            gui_UVCcontroller.add(scanningModeValue.set("scanningMode", 0, 0, 1.0));
            listeners.push(scanningModeValue.newListener([this](float &) { uvcControl.setScanningMode(scanningModeValue); }));
        }
        if (hasControl("aePriority")) {
            gui_UVCcontroller.add(aePriorityValue.set("aePriority", 0, 0, 1.0));
            listeners.push(aePriorityValue.newListener([this](float &) { uvcControl.setAePriority(aePriorityValue); }));
        }
        if (hasControl("exposureTimeRelative")) {
            gui_UVCcontroller.add(exposureTimeRelativeValue.set("exposureTimeRelative", 0, 0, 1.0));
            listeners.push(exposureTimeRelativeValue.newListener([this](float &) { uvcControl.setExposureTimeRelative(exposureTimeRelativeValue); }));
        }
        
        if (hasControl("focusRelative")) {
            gui_UVCcontroller.add(focusRelativeValue.set("focusRelative", 0, 0, 1.0));
            listeners.push(focusRelativeValue.newListener([this](float &) { uvcControl.setFocusRelative(focusRelativeValue); }));
        }
        if (hasControl("irisAbsolute")) {
            gui_UVCcontroller.add(irisAbsoluteValue.set("irisAbsolute", 0, 0, 1.0));
            listeners.push(irisAbsoluteValue.newListener([this](float &) { uvcControl.setIrisAbsolute(irisAbsoluteValue); }));
        }
        if (hasControl("irisRelative")) {
            gui_UVCcontroller.add(irisRelativeValue.set("irisRelative", 0, 0, 1.0));
            listeners.push(irisRelativeValue.newListener([this](float &) { uvcControl.setIrisRelative(irisRelativeValue); }));
        }
        if (hasControl("privacy")) {
            gui_UVCcontroller.add(privacyValue.set("privacy", 0, 0, 1.0));
            listeners.push(privacyValue.newListener([this](float &) { uvcControl.setPrivacy(privacyValue); }));
        }
        
        if (hasControl("focusSimple")) {
            gui_UVCcontroller.add(focusSimpleValue.set("focusSimple", 0, 0, 1.0));
            listeners.push(focusSimpleValue.newListener([this](float &) { uvcControl.setFocusSimple(focusSimpleValue); }));
        }
        if (hasControl("digitalWindow")) {
            gui_UVCcontroller.add(digitalWindowValue.set("digitalWindow", 0, 0, 1.0));
            listeners.push(digitalWindowValue.newListener([this](float &) { uvcControl.setDigitalWindow(digitalWindowValue); }));
        }
        
        if (hasControl("regionOfInterest")) {
            gui_UVCcontroller.add(regionOfInterestValue.set("regionOfInterest", 0, 0, 1.0));
            listeners.push(regionOfInterestValue.newListener([this](float &) { uvcControl.setRegionOfInterest(regionOfInterestValue); }));
        }
        // Add utility parameters
        gui_UVCcontroller.add(getCamValues.set("getCamValues", false));
        gui_UVCcontroller.add(initDone_str.set("initDone", "false"));
    }
    
    // Method to print available camera controls
    void printAvailableControls() {
        ofLogNotice("UVC_controller") << "Available camera controls:";
        for (const auto& control : controls) {
            string status = "";
            if (control.supportsGet()) status += "GET ";
            if (control.supportsSet()) status += "SET ";
            if (control.disabledDueToAutomaticControl()) status += "DISABLED ";
            if (control.underAutomaticControl()) status += "AUTO ";
            
            ofLogNotice("UVC_controller") << "  " << control.name << ": " << status;
        }
    }
    
    // Method to initialize all values with delay between each
    void initAllValues() {
        if (!initValuesStarted) {
            initValuesStarted = true;
            currentControlIndex = 0;
            lastControlSetTime = ofGetElapsedTimef();
            lastAutoModeSetTime = ofGetElapsedTimef();
            autoModesSet = false;
            ofLog() << ofGetTimestampString() << " Starting to initialize all values";
        }
        
        float currentTime = ofGetElapsedTimef();
        
        // First set all auto modes
        if (!autoModesSet) {
            if (currentTime - lastControlSetTime < controlSetDelay) {
                return;
            }
            
            lastControlSetTime = currentTime;
            
            try {
                switch (currentControlIndex++) {
                    case 0:
                        if (hasControl("aeMode")) {
                            setControlValue("aeMode", aeMode);
                            ofLog() << "Setting aeMode: " << aeMode;
                        }
                        break;
                    case 1:
                        if (hasControl("focusAuto")) {
                            setControlValue("focusAuto", aFocus ? 1.0 : 0.0);
                            ofLog() << "Setting auto focus: " << aFocus;
                        }
                        break;
                    case 2:
                        if (hasControl("autoWhiteBalance")) {
                            setControlValue("autoWhiteBalance", aWhiteBalance ? 1.0 : 0.0);
                            ofLog() << "Setting auto white balance: " << aWhiteBalance;
                        }
                        break;
                    default:
                        autoModesSet = true;
                        lastAutoModeSetTime = currentTime;
                        currentControlIndex = 0;
                        ofLog() << "Auto modes set, waiting before setting manual values";
                        return;
                }
            } catch (const std::exception& e) {
                ofLogError() << "Error setting auto mode: " << e.what();
                // Continue to next control even if there's an error
                currentControlIndex++;
            }
            return;
        }
        
        // Wait after setting auto modes
        if (currentTime - lastAutoModeSetTime < autoModeDelay) {
            return;
        }
        
        // Then set manual values
        if (currentTime - lastControlSetTime < controlSetDelay) {
            return;
        }
        
        lastControlSetTime = currentTime;
        
        // Set controls one by one with error handling
        try {
            switch (currentControlIndex++) {
                case 0:
                    if (hasControl("exposureTimeAbsolute")) {
                        setControlValue("exposureTimeAbsolute", exposureTimeAbsolute);
                        ofLog() << "Setting exposureTimeAbsolute: " << exposureTimeAbsolute;
                    }
                    break;
                case 1:
                    if (hasControl("focusValue")) {
                        // Add extra delay before setting focus
                        ofSleepMillis(100);
                        setControlValue("focusValue", focusValue);
                        ofLog() << "Setting focus value: " << focusValue;
                    }
                    break;
                case 2:
                    if (hasControl("autoWhiteBalance")) {
                        setControlValue("autoWhiteBalance", aWhiteBalance ? 1.0 : 0.0);
                        ofLog() << "Setting white balance value: " << whiteBalanceValue;
                    }
                    break;
                case 3:
                    if (hasControl("brightness")) {
                        setControlValue("brightness", brightnessValue);
                        ofLog() << "Setting brightness: " << brightnessValue;
                    }
                    break;
                case 4:
                    if (hasControl("contrast")) {
                        setControlValue("contrast", contrastValue);
                        ofLog() << "Setting contrast: " << contrastValue;
                    }
                    break;
                case 5:
                    if (hasControl("saturation")) {
                        setControlValue("saturation", saturationValue);
                        ofLog() << "Setting saturation: " << saturationValue;
                    }
                    break;
                case 6:
                    if (hasControl("sharpness")) {
                        setControlValue("sharpness", sharpValue);
                        ofLog() << "Setting sharpness: " << sharpValue;
                    }
                    break;
                case 7:
                    if (hasControl("gain")) {
                        setControlValue("gain", gainValue);
                        ofLog() << "Setting gain: " << gainValue;
                    }
                    break;
                case 8:
                    if (hasControl("powerLineFrequency")) {
                        setControlValue("powerLineFrequency", powerLineFrequency);
                        ofLog() << "Setting power line frequency: " << powerLineFrequency;
                    }
                    break;
                case 9:
                    if (hasControl("backlightCompensation")) {
                        setControlValue("backlightCompensation", backLightCompensation ? 1.0 : 0.0);
                        ofLog() << "Setting backlight compensation: " << backLightCompensation;
                    }
                    break;
                case 10:
                    if (hasControl("autoHue")) {
                        setControlValue("autoHue", aHue ? 1.0 : 0.0);
                        ofLog() << "Setting auto hue: " << aHue;
                    }
                    break;
                case 11:
                    if (hasControl("hue")) {
                        setControlValue("hue", hueValue);
                        ofLog() << "Setting hue: " << hueValue;
                    }
                    break;
                case 12:
                    if (hasControl("gamma")) {
                        setControlValue("gamma", gammaValue);
                        ofLog() << "Setting gamma: " << gammaValue;
                    }
                    break;
                case 13:
                    if (hasControl("zoomAbsolute")) {
                        setControlValue("zoomAbsolute", zoomAbsoluteValue);
                        ofLog() << "Setting zoom: " << zoomAbsoluteValue;
                    }
                    break;
                case 14:
                    if (hasControl("pantiltAbsolute")) {
                        // This is handled separately with two parameters
                        return;
                    }
                    break;
                case 15:
                    if (hasControl("roll")) {
                        setControlValue("roll", rollValue);
                        ofLog() << "Setting roll: " << rollValue;
                    }
                    break;
                case 16:
                    if (hasControl("led")) {
                        setControlValue("led", aLed ? 1.0 : 0.0);
                        ofLog() << "Setting LED: " << aLed;
                    }
                    break;
                case 17:
                    if (hasControl("scanningMode")) {
                        setControlValue("scanningMode", scanningModeValue);
                        ofLog() << "Setting scanning mode: " << scanningModeValue;
                    }
                    break;
                case 18:
                    if (hasControl("aePriority")) {
                        setControlValue("aePriority", aePriorityValue);
                        ofLog() << "Setting AE priority: " << aePriorityValue;
                    }
                    break;
                case 19:
                    if (hasControl("exposureTimeRelative")) {
                        setControlValue("exposureTimeRelative", exposureTimeRelativeValue);
                        ofLog() << "Setting exposure time relative: " << exposureTimeRelativeValue;
                    }
                    break;
                case 20:
                    if (hasControl("focusRelative")) {
                        setControlValue("focusRelative", focusRelativeValue);
                        ofLog() << "Setting focus relative: " << focusRelativeValue;
                    }
                    break;
                case 21:
                    if (hasControl("irisAbsolute")) {
                        setControlValue("irisAbsolute", irisAbsoluteValue);
                        ofLog() << "Setting iris absolute: " << irisAbsoluteValue;
                    }
                    break;
                case 22:
                    if (hasControl("irisRelative")) {
                        setControlValue("irisRelative", irisRelativeValue);
                        ofLog() << "Setting iris relative: " << irisRelativeValue;
                    }
                    break;
                case 23:
                    if (hasControl("privacy")) {
                        setControlValue("privacy", privacyValue);
                        ofLog() << "Setting privacy: " << privacyValue;
                    }
                    break;
                case 24:
                    if (hasControl("focusSimple")) {
                        setControlValue("focusSimple", focusSimpleValue);
                        ofLog() << "Setting focus simple: " << focusSimpleValue;
                    }
                    break;
                case 25:
                    if (hasControl("digitalWindow")) {
                        setControlValue("digitalWindow", digitalWindowValue);
                        ofLog() << "Setting digital window: " << digitalWindowValue;
                    }
                    break;
                case 26:
                    if (hasControl("regionOfInterest")) {
                        setControlValue("regionOfInterest", regionOfInterestValue);
                        ofLog() << "Setting region of interest: " << regionOfInterestValue;
                    }
                    break;
                case 27:
                    if (hasControl("saturation")) {
                        setControlValue("saturation", saturationValue);
                        ofLog() << "Setting saturation: " << saturationValue;
                        lastControlSetTime = currentTime + relatedControlDelay; // Add extra delay after saturation
                    }
                    break;
                case 28:
                    if (hasControl("hue")) {
                        setControlValue("hue", hueValue);
                        ofLog() << "Setting hue: " << hueValue;
                    }
                    break;
                default:
                    // All controls have been set
                    initValuesStarted = false;
                    currentControlIndex = 0;
                    ofLog() << ofGetTimestampString() << " Finished initializing all values";
                    initDone = true;
                    break;
            }
        } catch (const std::exception& e) {
            ofLogError() << "Error setting control at index " << currentControlIndex-1 << ": " << e.what();
            // Continue to next control even if there's an error
            currentControlIndex++;
        }
    }
    
    // Method to safely set a control value with error handling
    bool setControlValue(const string& controlName, float value) {
        try {
            if (!hasControl(controlName)) {
                ofLogWarning() << "Control " << controlName << " not available";
                return false;
            }
            
            ofLog() << "Setting " << controlName << " to " << value;
            
            // Add a small delay before setting the control
            ofSleepMillis(50);
            
            if (controlName == "focusAuto") {
                uvcControl.setAutoFocus(value > 0.5);
            } else if (controlName == "focusValue") {
                uvcControl.setAbsoluteFocus(value);
            } else if (controlName == "exposureTimeAbsolute") {
                uvcControl.setExposureTimeAbsolute(value);
            } else if (controlName == "autoWhiteBalance") {
                uvcControl.setAutoWhiteBalance(value > 0.5);
            } else if (controlName == "whiteBalanceValue") {
                uvcControl.setWhiteBalance(value);
            } else if (controlName == "brightness") {
                uvcControl.setBrightness(value);
            } else if (controlName == "contrast") {
                uvcControl.setContrast(value);
            } else if (controlName == "saturation") {
                uvcControl.setSaturation(value);
            } else if (controlName == "sharpness") {
                uvcControl.setSharpness(value);
            } else if (controlName == "gain") {
                uvcControl.setGain(value);
            } else if (controlName == "powerLineFrequency") {
                uvcControl.setPowerLineFrequency((int)value);
            } else if (controlName == "backlightCompensation") {
                uvcControl.setBacklightCompensation(value > 0.5);
            } else if (controlName == "autoHue") {
                uvcControl.setAutoHue(value > 0.5);
            } else if (controlName == "hue") {
                uvcControl.setHue(value);
            } else if (controlName == "gamma") {
                uvcControl.setGamma(value);
            } else if (controlName == "zoomAbsolute") {
                uvcControl.setZoomAbsolute(value);
            } else if (controlName == "pantiltAbsolute") {
                // This is handled separately with two parameters
                return false;
            } else if (controlName == "roll") {
                uvcControl.setRoll(value);
            } else if (controlName == "led") {
                uvcControl.setLed(value > 0.5);
            } else if (controlName == "scanningMode") {
                uvcControl.setScanningMode(value);
            } else if (controlName == "aePriority") {
                uvcControl.setAePriority(value);
            } else if (controlName == "exposureTimeRelative") {
                uvcControl.setExposureTimeRelative(value);
            } else if (controlName == "focusRelative") {
                uvcControl.setFocusRelative(value);
            } else if (controlName == "irisAbsolute") {
                uvcControl.setIrisAbsolute(value);
            } else if (controlName == "irisRelative") {
                uvcControl.setIrisRelative(value);
            } else if (controlName == "privacy") {
                uvcControl.setPrivacy(value);
            } else if (controlName == "focusSimple") {
                uvcControl.setFocusSimple(value);
            } else if (controlName == "digitalWindow") {
                uvcControl.setDigitalWindow(value);
            } else if (controlName == "regionOfInterest") {
                uvcControl.setRegionOfInterest(value);
            } else if (controlName == "aeMode") {
                uvcControl.setAutoExposure((int)value);
            } else {
                ofLogWarning() << "Unknown control: " << controlName;
        return false;
    }
    
            if(bDebug_UVC_controller) ofLog() << "Successfully set " << controlName << " to " << value;
            return true;
        } catch (const std::exception& e) {
            ofLogError() << "Error setting " << controlName << " to " << value << ": " << e.what();
            return false;
        }
    }

};

#endif




