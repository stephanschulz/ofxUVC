#pragma once 


#ifdef __OBJC__
@class UVCCameraControl;
#endif

#import <vector>
#import <string>

using namespace std;

typedef struct { 
    string name;
    long status;
    
    // FIXME:
    // these are the right bit masks according to the spec
    // but right now for some reason they're not working
    // maybe an endianness problem?
    bool supportsGet(){ return ((unsigned int)status & 0x00000001) > 0; }
    bool supportsSet(){ return ((unsigned int)status & 0x00000010) > 0; }
    bool disabledDueToAutomaticControl(){ return ((unsigned int)status & 0x00000100) > 0; }
    bool underAutomaticControl(){ return ((unsigned int)status & 0x00001000) > 0; }

    
} ofxUVCControl;


class ofxUVC {
    
	public:
    ofxUVC();
    ~ofxUVC();

    void useCamera(int vendorId, int productId, int interfaceNum);
    void useCamera2(int vendorId, int productId, int _interfaceNum,int _locationID);
    
    void setAutoExposure(bool enable);
    bool getAutoExposure();
    void setExposure(float value);
    float getExposure();
    
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

    //-----newly added
    void setPowerLineFrequency(float value);
    float getPowerLineFrequency();
    void setBacklightCompensation(float value);
    float getBacklightCompensation();
    
    void setAutoHue(bool enabled);
    bool getAutoHue();
    void setHue(float value);
    float getHue();
    
    void setGamma(float value);
    float getGamma();
    
    
    void setZoom(float value);
    float getZoom();
//    void setPantilt(float pan, float tilt);
    void setPantilt(float* value);
    float getPantilt();
    void setRoll(float value);
    float getRoll();
    
    void printDefaults();
    
    vector<ofxUVCControl> getCameraControls();
    
  protected:
    
    bool cameraInited;
    
    #ifdef __OBJC__
    UVCCameraControl* cameraControl;
    #else
    void* cameraControl;
    #endif
    
};
