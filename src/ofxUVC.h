#pragma once 


#ifdef __OBJC__
@class UVCCameraControl;
#endif

#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include "ofLog.h"

using namespace std;

struct ofxUVCControl{
    string name;
    long status;
    
    bool supportsGet() const { 
        bool result = ((unsigned int)status & 0x00000001) > 0;  // Bit 0
//        stringstream ss;
//        ss << "Control " << name << " supportsGet: " << result << " (status: 0x" << hex << status << ")";
//        ofLog() << ss.str();
        return result;
    }
    
    bool supportsSet() const { 
        bool result = ((unsigned int)status & 0x00000002) > 0;  // Bit 1
//        stringstream ss;
//        ss << "Control " << name << " supportsSet: " << result << " (status: 0x" << hex << status << ")";
//        ofLog() << ss.str();
        return result;
    }
    
    bool disabledDueToAutomaticControl() const { 
        bool result = ((unsigned int)status & 0x00000004) > 0;  // Bit 2
//        stringstream ss;
//        ss << "Control " << name << " disabledDueToAutomaticControl: " << result << " (status: 0x" << hex << status << ")";
//        ofLog() << ss.str();
        return result;
    }
    
    bool underAutomaticControl() const { 
        bool result = ((unsigned int)status & 0x00000008) > 0;  // Bit 3
//        stringstream ss;
//        ss << "Control " << name << " underAutomaticControl: " << result << " (status: 0x" << hex << status << ")";
//        ofLog() << ss.str();
        return result;
    }
} ;


class ofxUVC {
    
    public:
    ofxUVC();
    ~ofxUVC();

    void useCameraByInterfaceNum(int vendorId, int productId, int interfaceNum);
    void useCameraByLocationID(int vendorId, int productId, int interfaceNum, unsigned int locationID);

    void setAutoExposure(int mode);
    bool getAutoExposure();
    void setExposure(float value);
    float getExposure();
    void incrementExposure();
    void decrementExposure();
    void setDefaultExposure();
    
    void setAutoFocus(bool enabled);
    bool getAutoFocus();
    void setAbsoluteFocus(float value);
    float getAbsoluteFocus();
    
    void setAutoWhiteBalance(bool enabled);
    bool getAutoWhiteBalance();
    void setWhiteBalance(float value);
    float getWhiteBalance();
    
    
    void setGain(float value);
    float getGain();
    void setBrightness(float value);
    float getBrightness();
    void setContrast(float value);
    float getContrast();
    void setSaturation(float value);
    float getSaturation();
    void setSharpness(float value);
    float getSharpness();

    void setLed(bool enable);
    bool getLed();
    
    void setBacklightCompensation(bool enable);
    bool getBacklightCompensation();
    void setPowerLineFrequency(int frequency);
    bool getPowerLineFrequency();
    
    void setAutoHue(bool enabled);
    bool getAutoHue();
    void setHue(float value);
    float getHue();
    void setGamma(float value);
    float getGamma();

    void setZoomAbsolute(float value);
    float getZoomAbsolute();
    void setPanTiltAbsolute(float panValue, float tiltValue);
    float getPanTiltAbsolute();
    void setRoll(float value);
    float getRoll();

    void setIncrementalExposure(float value);
    float getIncrementalExposure();
    
    void setScanningMode(float value);
    float getScanningMode();
    
    void setAeMode(bool enable);
    float getAeMode();
    
    void setAePriority(float value);
    float getAePriority();
    
    void setExposureTimeAbsolute(float value);
    float getExposureTimeAbsolute();
    void setExposureTimeRelative(float value);
    float getExposureTimeRelative();
    
    void setFocusRelative(float value);
    float getFocusRelative();
    
    void setIrisAbsolute(float value);
    float getIrisAbsolute();
    
    void setIrisRelative(float value);
    float getIrisRelative();
    
    void setPrivacy(float value);
    float getPrivacy();
    
    void setFocusSimple(float value);
    float getFocusSimple();
    
    void setDigitalWindow(float value);
    float getDigitalWindow();
    
    void setRegionOfInterest(float value);
    float getRegionOfInterest();
    
    vector<ofxUVCControl> getCameraControls();
    
    bool setup(int vendorID, int productID, int interfaceNum = 0);
    bool setup(int locationID);
    
    void setRollRelative(float value);
    float getRollRelative();
    
#include "ofxUVCUseProber.h"
    
  protected:
    
    bool cameraInited;
    
    #ifdef __OBJC__
    UVCCameraControl* cameraControl;
    #else
    void* cameraControl;
    #endif
    
};
