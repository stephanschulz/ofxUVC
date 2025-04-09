#include "ofxUVC.h"
#include "UVCCameraControl.h"

ofxUVC::ofxUVC() {
    cameraControl = nil;
}

ofxUVC::~ofxUVC() {
    cameraControl = nil;
}

bool ofxUVC::setup(int vendorID, int productID, int interfaceNum) {
    cameraControl = nil;
    cameraControl = [[UVCCameraControl alloc] initWithVendorID:vendorID productID:productID interfaceNum:interfaceNum];
    return (cameraControl != nil);
}

bool ofxUVC::setup(int locationID) {
    cameraControl = nil;
    cameraControl = [[UVCCameraControl alloc] initWithLocationID:locationID];
    return (cameraControl != nil);
}

void ofxUVC::useCameraByLocationID(int vendorId, int productId, int interfaceNum, unsigned int locationID) {
    cameraControl = nil;
    cameraControl = [[UVCCameraControl alloc] initWithLocationID:locationID];
}

void ofxUVC::setAutoExposure(int mode) {
    // Clamp mode to valid range (0-3)
    mode = std::max(0, std::min(3, mode));
    [(UVCCameraControl*)cameraControl setAeMode:mode];
}

void ofxUVC::setExposure(float value) {
    [(UVCCameraControl*)cameraControl setExposure:value];
}

float ofxUVC::getExposure() {
    return [(UVCCameraControl*)cameraControl getExposure];
}

void ofxUVC::setAutoWhiteBalance(bool enabled) {
    [(UVCCameraControl*)cameraControl setAutoWhiteBalance:enabled];
}

void ofxUVC::setWhiteBalance(float value) {
    [(UVCCameraControl*)cameraControl setWhiteBalance:value];
}

float ofxUVC::getWhiteBalance() {
    return [(UVCCameraControl*)cameraControl getWhiteBalance];
}

void ofxUVC::setGain(float value) {
    [(UVCCameraControl*)cameraControl setGain:value];
}

float ofxUVC::getGain() {
    return [(UVCCameraControl*)cameraControl getGain];
}

void ofxUVC::setBrightness(float value) {
    [(UVCCameraControl*)cameraControl setBrightness:value];
}

float ofxUVC::getBrightness() {
    return [(UVCCameraControl*)cameraControl getBrightness];
}

void ofxUVC::setContrast(float value) {
    [(UVCCameraControl*)cameraControl setContrast:value];
}

float ofxUVC::getContrast() {
    return [(UVCCameraControl*)cameraControl getContrast];
}

void ofxUVC::setSaturation(float value) {
    [(UVCCameraControl*)cameraControl setSaturation:value];
}

float ofxUVC::getSaturation() {
    return [(UVCCameraControl*)cameraControl getSaturation];
}

void ofxUVC::setSharpness(float value) {
    [(UVCCameraControl*)cameraControl setSharpness:value];
}

float ofxUVC::getSharpness() {
    return [(UVCCameraControl*)cameraControl getSharpness];
}

void ofxUVC::setLed(bool enable) {
    [(UVCCameraControl*)cameraControl setLED:enable];
}

void ofxUVC::setHue(float value) {
    [(UVCCameraControl*)cameraControl setHue:value];
}

void ofxUVC::setGamma(float value) {
    [(UVCCameraControl*)cameraControl setGamma:value];
}

void ofxUVC::setZoomAbsolute(float value) {
    [(UVCCameraControl*)cameraControl setZoomAbsolute:value];
}

void ofxUVC::setPanTiltAbsolute(float panValue, float tiltValue) {
    [(UVCCameraControl*)cameraControl setPanTiltAbsolute:panValue tiltValue:tiltValue];
}

void ofxUVC::setRoll(float value) {
    [(UVCCameraControl*)cameraControl setRollAbsolute:value];
}

void ofxUVC::setIncrementalExposure(float value) {
    [(UVCCameraControl*)cameraControl setExposureTimeRelative:value];
}

void ofxUVC::setScanningMode(float value) {
    [(UVCCameraControl*)cameraControl setScanningMode:value];
}

float ofxUVC::getScanningMode() {
    return [(UVCCameraControl*)cameraControl getScanningMode];
}

void ofxUVC::setExposureTimeAbsolute(float value) {
    [(UVCCameraControl*)cameraControl setExposureTimeAbsolute:value];
}

float ofxUVC::getExposureTimeAbsolute() {
    return [(UVCCameraControl*)cameraControl getExposure];
}

void ofxUVC::setDefaultExposure() {
    [(UVCCameraControl*)cameraControl setDefaultExposure];
}

void ofxUVC::setAutoFocus(bool enabled) {
    [(UVCCameraControl*)cameraControl setAutoFocus:enabled];
}

bool ofxUVC::getAutoFocus() {
    return [(UVCCameraControl*)cameraControl getAutoFocus];
}

void ofxUVC::setAbsoluteFocus(float value) {
    [(UVCCameraControl*)cameraControl setAbsoluteFocus:value];
}

float ofxUVC::getAbsoluteFocus() {
    return [(UVCCameraControl*)cameraControl getAbsoluteFocus];
}

void ofxUVC::setRollRelative(float value) {
    [(UVCCameraControl*)cameraControl setRollRelative:value];
}

float ofxUVC::getRollRelative() {
    return [(UVCCameraControl*)cameraControl getRollRelative];
}

void ofxUVC::setAeMode(bool enable) {
    [(UVCCameraControl*)cameraControl setAeMode:enable];
}

float ofxUVC::getAeMode() {
    return [(UVCCameraControl*)cameraControl getAeMode];
}

void ofxUVC::setAePriority(float value) {
    [(UVCCameraControl*)cameraControl setAePriority:value];
}

float ofxUVC::getAePriority() {
    return [(UVCCameraControl*)cameraControl getAePriority];
}

void ofxUVC::setExposureTimeRelative(float value) {
    [(UVCCameraControl*)cameraControl setExposureTimeRelative:value];
}

float ofxUVC::getExposureTimeRelative() {
    return [(UVCCameraControl*)cameraControl getExposureTimeRelative];
}

void ofxUVC::setFocusRelative(float value) {
    [(UVCCameraControl*)cameraControl setFocusRelative:value];
}

float ofxUVC::getFocusRelative() {
    return [(UVCCameraControl*)cameraControl getFocusRelative];
}

void ofxUVC::setIrisAbsolute(float value) {
    [(UVCCameraControl*)cameraControl setIrisAbsolute:value];
}

float ofxUVC::getIrisAbsolute() {
    return [(UVCCameraControl*)cameraControl getIrisAbsolute];
}

void ofxUVC::setIrisRelative(float value) {
    [(UVCCameraControl*)cameraControl setIrisRelative:value];
}

float ofxUVC::getIrisRelative() {
    return [(UVCCameraControl*)cameraControl getIrisRelative];
}

void ofxUVC::setPrivacy(float value) {
    [(UVCCameraControl*)cameraControl setPrivacy:value];
}

float ofxUVC::getPrivacy() {
    return [(UVCCameraControl*)cameraControl getPrivacy];
}

void ofxUVC::setFocusSimple(float value) {
    [(UVCCameraControl*)cameraControl setFocusSimple:value];
}

float ofxUVC::getFocusSimple() {
    return [(UVCCameraControl*)cameraControl getFocusSimple];
}

void ofxUVC::setDigitalWindow(float value) {
    [(UVCCameraControl*)cameraControl setDigitalWindow:value];
}

float ofxUVC::getDigitalWindow() {
    return [(UVCCameraControl*)cameraControl getDigitalWindow];
}

void ofxUVC::setRegionOfInterest(float value) {
    [(UVCCameraControl*)cameraControl setRegionOfInterest:value];
}

float ofxUVC::getRegionOfInterest() {
    return [(UVCCameraControl*)cameraControl getRegionOfInterest];
}

void ofxUVC::setAutoHue(bool enabled) {
    [(UVCCameraControl*)cameraControl setAutoHue:enabled];
}

bool ofxUVC::getAutoHue() {
    return [(UVCCameraControl*)cameraControl getAutoHue];
}

void ofxUVC::setPowerLineFrequency(int frequency) {
    [(UVCCameraControl*)cameraControl setPowerLineFrequency:frequency];
}

bool ofxUVC::getPowerLineFrequency() {
    return [(UVCCameraControl*)cameraControl getPowerLineFrequency];
}

void ofxUVC::setBacklightCompensation(bool enable) {
    [(UVCCameraControl*)cameraControl setBacklightCompensation:enable];
}

bool ofxUVC::getBacklightCompensation() {
    return [(UVCCameraControl*)cameraControl getBacklightCompensation];
}

vector<ofxUVCControl> ofxUVC::getCameraControls() {
    vector<ofxUVCControl> result;
    
    // Get the controls from the camera
    UVCCameraControls *cameraControls = [(UVCCameraControl*)cameraControl getControls];
    
    // Add all available controls to the vector
    ofxUVCControl control;
    
    // Scanning Mode
    control.name = [cameraControls.scanningMode.name UTF8String];
    uvc_control_info_t scanningMode = cameraControls.scanningMode;
    control.status = [(UVCCameraControl*)cameraControl getInfoForControl:&scanningMode];
    result.push_back(control);
    
    // AE Mode
    control.name = [cameraControls.aeMode.name UTF8String];
    uvc_control_info_t aeMode = cameraControls.aeMode;
    control.status = [(UVCCameraControl*)cameraControl getInfoForControl:&aeMode];
    result.push_back(control);
    
    // AE Priority
    control.name = [cameraControls.aePriority.name UTF8String];
    uvc_control_info_t aePriority = cameraControls.aePriority;
    control.status = [(UVCCameraControl*)cameraControl getInfoForControl:&aePriority];
    result.push_back(control);
    
    // Exposure Time Absolute
    control.name = [cameraControls.exposureTimeAbsolute.name UTF8String];
    uvc_control_info_t exposureTimeAbsolute = cameraControls.exposureTimeAbsolute;
    control.status = [(UVCCameraControl*)cameraControl getInfoForControl:&exposureTimeAbsolute];
    result.push_back(control);
    
    // Exposure Time Relative
    control.name = [cameraControls.exposureTimeRelative.name UTF8String];
    uvc_control_info_t exposureTimeRelative = cameraControls.exposureTimeRelative;
    control.status = [(UVCCameraControl*)cameraControl getInfoForControl:&exposureTimeRelative];
    result.push_back(control);
    
    // Focus Absolute
    control.name = [cameraControls.focusAbsolute.name UTF8String];
    uvc_control_info_t focusAbsolute = cameraControls.focusAbsolute;
    control.status = [(UVCCameraControl*)cameraControl getInfoForControl:&focusAbsolute];
    result.push_back(control);
    
    // Focus Relative
    control.name = [cameraControls.focusRelative.name UTF8String];
    uvc_control_info_t focusRelative = cameraControls.focusRelative;
    control.status = [(UVCCameraControl*)cameraControl getInfoForControl:&focusRelative];
    result.push_back(control);
    
    // Focus Auto
    control.name = [cameraControls.focusAuto.name UTF8String];
    uvc_control_info_t focusAuto = cameraControls.focusAuto;
    control.status = [(UVCCameraControl*)cameraControl getInfoForControl:&focusAuto];
    result.push_back(control);
    
    // Iris Absolute
    control.name = [cameraControls.irisAbsolute.name UTF8String];
    uvc_control_info_t irisAbsolute = cameraControls.irisAbsolute;
    control.status = [(UVCCameraControl*)cameraControl getInfoForControl:&irisAbsolute];
    result.push_back(control);
    
    // Iris Relative
    control.name = [cameraControls.irisRelative.name UTF8String];
    uvc_control_info_t irisRelative = cameraControls.irisRelative;
    control.status = [(UVCCameraControl*)cameraControl getInfoForControl:&irisRelative];
    result.push_back(control);
    
    // Brightness
    control.name = [cameraControls.brightness.name UTF8String];
    uvc_control_info_t brightness = cameraControls.brightness;
    control.status = [(UVCCameraControl*)cameraControl getInfoForControl:&brightness];
    result.push_back(control);
    
    // Contrast
    control.name = [cameraControls.contrast.name UTF8String];
    uvc_control_info_t contrast = cameraControls.contrast;
    control.status = [(UVCCameraControl*)cameraControl getInfoForControl:&contrast];
    result.push_back(control);
    
    // Gain
    control.name = [cameraControls.gain.name UTF8String];
    uvc_control_info_t gain = cameraControls.gain;
    control.status = [(UVCCameraControl*)cameraControl getInfoForControl:&gain];
    result.push_back(control);
    
    // Saturation
    control.name = [cameraControls.saturation.name UTF8String];
    uvc_control_info_t saturation = cameraControls.saturation;
    control.status = [(UVCCameraControl*)cameraControl getInfoForControl:&saturation];
    result.push_back(control);
    
    // Sharpness
    control.name = [cameraControls.sharpness.name UTF8String];
    uvc_control_info_t sharpness = cameraControls.sharpness;
    control.status = [(UVCCameraControl*)cameraControl getInfoForControl:&sharpness];
    result.push_back(control);
    
    // White Balance
    control.name = [cameraControls.whiteBalance.name UTF8String];
    uvc_control_info_t whiteBalance = cameraControls.whiteBalance;
    control.status = [(UVCCameraControl*)cameraControl getInfoForControl:&whiteBalance];
    result.push_back(control);
    
    // Auto White Balance
    control.name = [cameraControls.autoWhiteBalance.name UTF8String];
    uvc_control_info_t autoWhiteBalance = cameraControls.autoWhiteBalance;
    control.status = [(UVCCameraControl*)cameraControl getInfoForControl:&autoWhiteBalance];
    result.push_back(control);
    
    // Incremental Exposure
    control.name = [cameraControls.incremental_exposure.name UTF8String];
    uvc_control_info_t incremental_exposure = cameraControls.incremental_exposure;
    control.status = [(UVCCameraControl*)cameraControl getInfoForControl:&incremental_exposure];
    result.push_back(control);
    
    // Power Line Frequency
    control.name = [cameraControls.powerLineFrequency.name UTF8String];
    uvc_control_info_t powerLineFrequency = cameraControls.powerLineFrequency;
    control.status = [(UVCCameraControl*)cameraControl getInfoForControl:&powerLineFrequency];
    result.push_back(control);
    
    // Backlight Compensation
    control.name = [cameraControls.backlightCompensation.name UTF8String];
    uvc_control_info_t backlightCompensation = cameraControls.backlightCompensation;
    control.status = [(UVCCameraControl*)cameraControl getInfoForControl:&backlightCompensation];
    result.push_back(control);
    
    // Auto Hue
    control.name = [cameraControls.autoHue.name UTF8String];
    uvc_control_info_t autoHue = cameraControls.autoHue;
    control.status = [(UVCCameraControl*)cameraControl getInfoForControl:&autoHue];
    result.push_back(control);
    
    // Hue
    control.name = [cameraControls.hue.name UTF8String];
    uvc_control_info_t hue = cameraControls.hue;
    control.status = [(UVCCameraControl*)cameraControl getInfoForControl:&hue];
    result.push_back(control);
    
    // Gamma
    control.name = [cameraControls.gamma.name UTF8String];
    uvc_control_info_t gamma = cameraControls.gamma;
    control.status = [(UVCCameraControl*)cameraControl getInfoForControl:&gamma];
    result.push_back(control);
    
    // Zoom Absolute
    control.name = [cameraControls.zoomAbsolute.name UTF8String];
    uvc_control_info_t zoomAbsolute = cameraControls.zoomAbsolute;
    control.status = [(UVCCameraControl*)cameraControl getInfoForControl:&zoomAbsolute];
    result.push_back(control);
    
    // Pan/Tilt Absolute
    control.name = [cameraControls.pantiltAbsolute.name UTF8String];
    uvc_control_info_t pantiltAbsolute = cameraControls.pantiltAbsolute;
    control.status = [(UVCCameraControl*)cameraControl getInfoForControl:&pantiltAbsolute];
    result.push_back(control);
    
    // Roll Absolute
    control.name = [cameraControls.rollAbsolute.name UTF8String];
    uvc_control_info_t rollAbsolute = cameraControls.rollAbsolute;
    control.status = [(UVCCameraControl*)cameraControl getInfoForControl:&rollAbsolute];
    result.push_back(control);
    
    // Roll Relative
    control.name = [cameraControls.rollRelative.name UTF8String];
    uvc_control_info_t rollRelative = cameraControls.rollRelative;
    control.status = [(UVCCameraControl*)cameraControl getInfoForControl:&rollRelative];
    result.push_back(control);
    
    // Privacy
    control.name = [cameraControls.privacy.name UTF8String];
    uvc_control_info_t privacy = cameraControls.privacy;
    control.status = [(UVCCameraControl*)cameraControl getInfoForControl:&privacy];
    result.push_back(control);
    
    // Focus Simple
    control.name = [cameraControls.focusSimple.name UTF8String];
    uvc_control_info_t focusSimple = cameraControls.focusSimple;
    control.status = [(UVCCameraControl*)cameraControl getInfoForControl:&focusSimple];
    result.push_back(control);
    
    // Digital Window
    control.name = [cameraControls.digitalWindow.name UTF8String];
    uvc_control_info_t digitalWindow = cameraControls.digitalWindow;
    control.status = [(UVCCameraControl*)cameraControl getInfoForControl:&digitalWindow];
    result.push_back(control);
    
    // Region of Interest
    control.name = [cameraControls.regionOfInterest.name UTF8String];
    uvc_control_info_t regionOfInterest = cameraControls.regionOfInterest;
    control.status = [(UVCCameraControl*)cameraControl getInfoForControl:&regionOfInterest];
    result.push_back(control);
    
    // LED
    control.name = [cameraControls.led.name UTF8String];
    uvc_control_info_t led = cameraControls.led;
    control.status = [(UVCCameraControl*)cameraControl getInfoForControl:&led];
    result.push_back(control);
    
    return result;
}
