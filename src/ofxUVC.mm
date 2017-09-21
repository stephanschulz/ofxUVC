#include "ofxUVC.h"
#include "UVCCameraControl.h"

ofxUVC::ofxUVC(){
    cameraInited = false;
//    cout<<"when using logitech c920 uncomment #define USE_C920";
}

void ofxUVC::useCamera(int vendorId, int productId, int _interfaceNum){
	cameraControl = [[UVCCameraControl alloc] initWithVendorID:vendorId productID:productId interfaceNum:_interfaceNum];
    cameraInited = true;
}
void ofxUVC::useCamera2(int vendorId, int productId, int _interfaceNum,int _locationID){
  //  cameraControl = [[UVCCameraControl alloc] initWithVendorID:vendorId productID:productId interfaceNum:_interfaceNum];
    cameraControl = [[UVCCameraControl alloc] initWithLocationID:_locationID]; //] VendorID:vendorId productID:productId interfaceNum:_interfaceNum];

    cameraInited = true;
}

ofxUVC::~ofxUVC(){
    if(cameraInited){
        [cameraControl release];
    }
}

void ofxUVC::setAutoExposure(bool enable){
    if(enable){
        [cameraControl setAutoExposure:YES];
    } else {
        [cameraControl setAutoExposure:NO];
    }
}

bool ofxUVC::getAutoExposure(){
    return [cameraControl getAutoExposure];
}

void ofxUVC::setExposure(float value){
    [cameraControl setExposure:value];
}

float ofxUVC::getExposure(){
    return [cameraControl getExposure];
}

void ofxUVC::setAutoFocus(bool enabled){
    [cameraControl setAutoFocus:enabled];
}

bool ofxUVC::getAutoFocus(){
    return [cameraControl getAutoFocus];
}

void ofxUVC::setAbsoluteFocus(float value){
    [cameraControl setAbsoluteFocus:value];
}

float ofxUVC::getAbsoluteFocus(){
    return [cameraControl getAbsoluteFocus];
}

void ofxUVC::setAutoWhiteBalance(bool enabled){
    [cameraControl setAutoWhiteBalance:enabled];
}

bool ofxUVC::getAutoWhiteBalance(){
    return [cameraControl getAutoWhiteBalance];
}

void ofxUVC::setWhiteBalance(float value){
    [cameraControl setWhiteBalance:value];
}

float ofxUVC::getWhiteBalance(){
    return [cameraControl getWhiteBalance];
}

void ofxUVC::setGain(float value){
    [cameraControl setGain:value];
}

float ofxUVC::getGain(){
    return [cameraControl getGain];
}

void ofxUVC::setBrightness(float value){
    [cameraControl setBrightness:value];
}

float ofxUVC::getBrightness(){
    return [cameraControl getBrightness];
}

void ofxUVC::setContrast(float value){
    [cameraControl setContrast:value];
}

float ofxUVC::getContrast(){
    return [cameraControl getContrast];
}

void ofxUVC::setSaturation(float value){
    [cameraControl setSaturation:value];
}

float ofxUVC::getSaturation(){
    return [cameraControl getSaturation];
}

void ofxUVC::setSharpness(float value){
    [cameraControl setSharpness:value];
}

float ofxUVC::getSharpness(){
    return [cameraControl getSharpness];
}

//-----newly added
void ofxUVC::setPowerLineFrequency(float value){
    [cameraControl setPowerLineFrequency:value];
}
float ofxUVC::getPowerLineFrequency(){
    return [cameraControl getPowerLineFrequency];
}

void ofxUVC::setBacklightCompensation(float value){
    [cameraControl setBacklightCompensation:value];
}

float ofxUVC::getBacklightCompensation(){
    return [cameraControl getBacklightCompensation];
}

void ofxUVC::setAutoHue(bool enabled){
    [cameraControl setAutoHue:enabled];
}

bool ofxUVC::getAutoHue(){
    return [cameraControl getAutoHue];
}
float ofxUVC::getHue(){
    return [cameraControl getHue];
}

void ofxUVC::setHue(float value){
    [cameraControl setHue:value];
}

float ofxUVC::getGamma(){
    return [cameraControl getGamma];
}

void ofxUVC::setGamma(float value){
    [cameraControl setGamma:value];
}

float ofxUVC::getZoom(){
    return [cameraControl getZoom];
}

void ofxUVC::setZoom(float value){
    printf("ofxUVC::setZoom\n");
    [cameraControl setZoom:value];
}

float ofxUVC::getPantilt(){
    return [cameraControl getPantilt];
}

void ofxUVC::setPantilt(float* value){
    [cameraControl setPantilt:value];
}

float ofxUVC::getRoll(){
    return [cameraControl getRoll];
}

void ofxUVC::setRoll(float value){
    [cameraControl setRoll:value];
}

vector<ofxUVCControl> ofxUVC::getCameraControls(){
    vector<ofxUVCControl> result;
    
    ofxUVCControl autoFocus;
    autoFocus.name = "autoFocus";
    autoFocus.status = [cameraControl getInfoForControl:&[cameraControl getControls]->autoFocus];
    result.push_back(autoFocus);
    
    ofxUVCControl autoExposure;
    autoExposure.name = "autoExposure";
    autoExposure.status = [cameraControl getInfoForControl:&[cameraControl getControls]->autoExposure];
    result.push_back(autoExposure);
    
	ofxUVCControl exposure;
    exposure.name = "exposure";
    exposure.status = [cameraControl getInfoForControl:&[cameraControl getControls]->exposure];
    result.push_back(exposure);
    
	ofxUVCControl absoluteFocus;
    absoluteFocus.name = "absoluteFocus";
    absoluteFocus.status = [cameraControl getInfoForControl:&[cameraControl getControls]->absoluteFocus];
    result.push_back(absoluteFocus);

	ofxUVCControl focus;
    focus.name = "focus";
    focus.status = [cameraControl getInfoForControl:&[cameraControl getControls]->focus];
    result.push_back(focus);
    
	ofxUVCControl brightness;
    brightness.name = "brightness";
    brightness.status = [cameraControl getInfoForControl:&[cameraControl getControls]->brightness];
    result.push_back(brightness);
    
	ofxUVCControl contrast;
    contrast.name = "contrast";
    contrast.status = [cameraControl getInfoForControl:&[cameraControl getControls]->contrast];
    result.push_back(contrast);
    
	ofxUVCControl gain;
    gain.name = "gain";
    gain.status = [cameraControl getInfoForControl:&[cameraControl getControls]->gain];
    result.push_back(gain);
    
	ofxUVCControl saturation;
    saturation.name = "saturation";
    saturation.status = [cameraControl getInfoForControl:&[cameraControl getControls]->saturation];
    result.push_back(saturation);
    
	ofxUVCControl sharpness;
    sharpness.name = "sharpness";
    sharpness.status = [cameraControl getInfoForControl:&[cameraControl getControls]->sharpness];
    result.push_back(sharpness);
    
	ofxUVCControl whiteBalance;
    whiteBalance.name = "whiteBalance";
    whiteBalance.status = [cameraControl getInfoForControl:&[cameraControl getControls]->whiteBalance];
    result.push_back(whiteBalance);
    
	ofxUVCControl autoWhiteBalance;
    autoWhiteBalance.name = "autoWhiteBalance";
    autoWhiteBalance.status = [cameraControl getInfoForControl:&[cameraControl getControls]->autoWhiteBalance];
    result.push_back(autoWhiteBalance);
    
    ofxUVCControl powerLineFrequency;
    powerLineFrequency.name = "powerLineFrequency";
    powerLineFrequency.status = [cameraControl getInfoForControl:&[cameraControl getControls]->powerLineFrequency];
    result.push_back(powerLineFrequency);
    
    ofxUVCControl backLightCompensation;
    backLightCompensation.name = "backLightCompensation";
    backLightCompensation.status = [cameraControl getInfoForControl:&[cameraControl getControls]->backlightCompensation];
    result.push_back(powerLineFrequency);
    
    
    ofxUVCControl hue;
    hue.name = "hue";
    hue.status = [cameraControl getInfoForControl:&[cameraControl getControls]->hue];
    result.push_back(hue);
    ofxUVCControl autoHue;
    autoHue.name = "autoHue";
    autoHue.status = [cameraControl getInfoForControl:&[cameraControl getControls]->autoHue];
    result.push_back(autoHue);

    
    ofxUVCControl gamma;
    gamma.name = "gamma";
    gamma.status = [cameraControl getInfoForControl:&[cameraControl getControls]->gamma];
    result.push_back(gamma);

    ofxUVCControl zoom;
    zoom.name = "zoom";
    zoom.status = [cameraControl getInfoForControl:&[cameraControl getControls]->zoom];
    result.push_back(zoom);
    
    ofxUVCControl pantilt;
    pantilt.name = "pantilt";
    pantilt.status = [cameraControl getInfoForControl:&[cameraControl getControls]->pantilt];
    result.push_back(pantilt);
    
    ofxUVCControl roll;
    roll.name = "roll";
    roll.status = [cameraControl getInfoForControl:&[cameraControl getControls]->roll];
    result.push_back(roll);

    return result;
}
