//https://www.usb.org/document-library/video-class-v15-document-set

#ifndef UVCCameraControl_h
#define UVCCameraControl_h

#import <Foundation/Foundation.h>
#include <CoreFoundation/CoreFoundation.h>

#include <IOKit/IOKitLib.h>
#include <IOKit/IOMessage.h>
#include <IOKit/IOCFPlugIn.h>
#include <IOKit/usb/IOUSBLib.h>

// Remove hardcoded defines
#define UVC_INPUT_TERMINAL_ID 0x01

// UVC_PROCESSING_UNIT_ID will be determined dynamically

#define UVC_CONTROL_INTERFACE_CLASS 0x0E // 14
#define UVC_CONTROL_INTERFACE_SUBCLASS 0x01 //1

#define UVC_SET_CUR    0x01
#define UVC_GET_CUR    0x81
#define UVC_GET_MIN    0x82
#define UVC_GET_MAX    0x83
#define UVC_GET_INFO 0x86

// UVC descriptor types
#define UVC_DT_HEADER                   0x0c
#define UVC_DT_INPUT_TERMINAL           0x02
#define UVC_DT_PROCESSING_UNIT          0x05
#define UVC_DT_OUTPUT_TERMINAL          0x03
#define UVC_DT_SELECTOR_UNIT            0x04
#define UVC_DT_EXTENSION_UNIT           0x06

typedef struct {
    int min, max;
} uvc_range_t;

typedef struct {
    int unit;
    int selector;
    int size;
    NSString *name;
} uvc_control_info_t;

// UVC Camera Terminal Control Selectors
typedef enum {
    UVCCameraTerminal_scanningMode = 0x01,
    UVCCameraTerminal_aeMode = 0x02,
    UVCCameraTerminal_aePriority = 0x03,
    UVCCameraTerminal_exposureTimeAbsolute = 0x04,
    UVCCameraTerminal_exposureTimeRelative = 0x05,
    UVCCameraTerminal_focusAbsolute = 0x06,
    UVCCameraTerminal_focusRelative = 0x07,
    UVCCameraTerminal_focusAuto = 0x08,
    UVCCameraTerminal_irisAbsolute = 0x09,
    UVCCameraTerminal_irisRelative = 0x0A,
    UVCCameraTerminal_zoomAbsolute = 0x0B,
    UVCCameraTerminal_pantiltAbsolute = 0x0D,
    UVCCameraTerminal_rollAbsolute = 0x0F,
    UVCCameraTerminal_rollRelative = 0x10,
    UVCCameraTerminal_privacy = 0x11,
    UVCCameraTerminal_focusSimple = 0x12,
    UVCCameraTerminal_digitalWindow = 0x13,
    UVCCameraTerminal_regionOfInterest = 0x14
} UVCCameraTerminal;

// UVC Processing Unit Control Selectors
typedef enum {
    UVCProcessingUnit_brightness = 0x02,
    UVCProcessingUnit_contrast = 0x03,
    UVCProcessingUnit_gain = 0x04,
    UVCProcessingUnit_saturation = 0x07,
    UVCProcessingUnit_sharpness = 0x08,
    UVCProcessingUnit_whiteBalanceTemperature = 0x0A,
    UVCProcessingUnit_whiteBalanceTemperatureAuto = 0x0B,
    UVCProcessingUnit_powerLineFrequency = 0x05,
    UVCProcessingUnit_backlightCompensation = 0x01,
    UVCProcessingUnit_hueAuto = 0x10,
    UVCProcessingUnit_hue = 0x06,
    UVCProcessingUnit_gamma = 0x09,
    UVCProcessingUnit_analogVideoStandard = 0x07
} UVCProcessingUnit;

// Define a class to hold all the controls
@interface UVCCameraControls : NSObject

@property (nonatomic, assign) uvc_control_info_t scanningMode;
@property (nonatomic, assign) uvc_control_info_t aeMode;
@property (nonatomic, assign) uvc_control_info_t aePriority;
@property (nonatomic, assign) uvc_control_info_t exposureTimeAbsolute;
@property (nonatomic, assign) uvc_control_info_t exposureTimeRelative;
@property (nonatomic, assign) uvc_control_info_t focusAbsolute;
@property (nonatomic, assign) uvc_control_info_t focusRelative;
@property (nonatomic, assign) uvc_control_info_t focusAuto;
@property (nonatomic, assign) uvc_control_info_t irisAbsolute;
@property (nonatomic, assign) uvc_control_info_t irisRelative;
@property (nonatomic, assign) uvc_control_info_t brightness;
@property (nonatomic, assign) uvc_control_info_t contrast;
@property (nonatomic, assign) uvc_control_info_t gain;
@property (nonatomic, assign) uvc_control_info_t saturation;
@property (nonatomic, assign) uvc_control_info_t sharpness;
@property (nonatomic, assign) uvc_control_info_t whiteBalance;
@property (nonatomic, assign) uvc_control_info_t autoWhiteBalance;
@property (nonatomic, assign) uvc_control_info_t incremental_exposure;
@property (nonatomic, assign) uvc_control_info_t powerLineFrequency;
@property (nonatomic, assign) uvc_control_info_t backlightCompensation;
@property (nonatomic, assign) uvc_control_info_t autoHue;
@property (nonatomic, assign) uvc_control_info_t hue;
@property (nonatomic, assign) uvc_control_info_t gamma;
@property (nonatomic, assign) uvc_control_info_t zoomAbsolute;
@property (nonatomic, assign) uvc_control_info_t pantiltAbsolute;
@property (nonatomic, assign) uvc_control_info_t rollAbsolute;
@property (nonatomic, assign) uvc_control_info_t rollRelative;
@property (nonatomic, assign) uvc_control_info_t privacy;
@property (nonatomic, assign) uvc_control_info_t focusSimple;
@property (nonatomic, assign) uvc_control_info_t digitalWindow;
@property (nonatomic, assign) uvc_control_info_t regionOfInterest;
@property (nonatomic, assign) uvc_control_info_t led;

- (void)initializeWithProcessingUnitID:(int)processingUnitID;

@end

@interface UVCCameraControl : NSObject {
    long dataBuffer;
    IOUSBInterfaceInterface190 **interface;
    IOUSBInterfaceInterface190 **controlInterface;
    
    long interfaceNum;
    int processingUnitID; // Store the dynamically determined processing unit ID
    UVCCameraControls *controls; // Store controls as a member variable
    NSMutableDictionary *rangeCache;  // Add rangeCache as instance variable
}

- (id)initWithLocationID:(UInt32)locationID;
- (id)initWithVendorID:(UInt16)vendorID productID:(UInt16)productID interfaceNum:(UInt8)interfaceNum;
- (IOUSBInterfaceInterface190 **)getControlInferaceWithDeviceInterface:(IOUSBDeviceInterface **)deviceInterface;

// New method to extract processing unit ID from device descriptor
- (int)extractProcessingUnitID:(IOUSBDeviceInterface **)deviceInterface;

- (BOOL)sendControlRequest:(IOUSBDevRequest)controlRequest;
- (BOOL)setData:(long)value withLength:(int)length forSelector:(int)selector at:(int)unitID;
- (long)getDataFor:(int)type withLength:(int)length fromSelector:(int)selector at:(int)unitID;

- (uvc_range_t)getRangeForControl:(const uvc_control_info_t *)control;
- (float)mapValue:(float)value fromMin:(float)fromMin max:(float)fromMax toMin:(float)toMin max:(float)toMax;
- (float)getValueForControl:(const uvc_control_info_t *)control;
- (BOOL)setValue:(float)value forControl:(const uvc_control_info_t *)control;


- (long) getInfoForControl:(uvc_control_info_t *)control;
- (UVCCameraControls *) getControls;


- (BOOL)setAutoWhiteBalance:(BOOL)enabled;
- (BOOL)getAutoWhiteBalance;
- (BOOL)setWhiteBalance:(float)value;
- (float)getWhiteBalance;


- (BOOL)setGain:(float)value;
- (float)getGain;
- (BOOL)setBrightness:(float)value;
- (float)getBrightness;
- (BOOL)setContrast:(float)value;
- (float)getContrast;
- (BOOL)setSaturation:(float)value;
- (float)getSaturation;
- (BOOL)setSharpness:(float)value;
- (float)getSharpness;

- (BOOL)setLED:(BOOL)enabled;
- (BOOL)getLED;

- (BOOL)setBacklightCompensation:(bool)enabled;
- (float)getBacklightCompensation;
- (BOOL)setPowerLineFrequency:(float)value;
- (BOOL)getPowerLineFrequency;

- (BOOL)setAutoHue:(BOOL)enabled;
- (BOOL)getAutoHue;
- (BOOL)setHue:(float)value;
- (float)getHue;

- (BOOL)setGamma:(float)value;  
- (float)getGamma;

- (BOOL)setExposureTimeAbsolute:(float)value;
- (float)getExposureTimeAbsolute;

- (BOOL)setZoomAbsolute:(float)value;
- (float)getZoomAbsolute;

- (BOOL)setPanTiltAbsolute:(float)panValue tiltValue:(float)tiltValue;
- (float)getPanTiltAbsolute;

- (BOOL)setRollAbsolute:(float)value;
- (float)getRollAbsolute;

- (BOOL)setRollRelative:(float)value;
- (float)getRollRelative;

- (BOOL)setIncrementalExposure:(float)value;
- (float)getIncrementalExposure;

- (BOOL)setScanningMode:(float)value;
- (float)getScanningMode;

- (BOOL)setAeMode:(BOOL)enabled;
- (float)getAeMode;

- (BOOL)setAePriority:(float)value;
- (float)getAePriority;

- (BOOL)setExposureTimeRelative:(float)value;
- (float)getExposureTimeRelative;

- (BOOL)setFocusRelative:(float)value;
- (float)getFocusRelative;

- (BOOL)setIrisAbsolute:(float)value;
- (float)getIrisAbsolute;

- (BOOL)setIrisRelative:(float)value;
- (float)getIrisRelative;

- (BOOL)setPrivacy:(float)value;
- (float)getPrivacy;

- (BOOL)setFocusSimple:(float)value;
- (float)getFocusSimple;

- (BOOL)setDigitalWindow:(float)value;
- (float)getDigitalWindow;

- (BOOL)setRegionOfInterest:(float)value;
- (float)getRegionOfInterest;

- (IOUSBDeviceInterface **)getDeviceInterfaceWithLocationID:(UInt32)locationID;
- (IOUSBDeviceInterface **)getDeviceInterfaceWithVendorID:(UInt16)vendorID productID:(UInt16)productID;

- (BOOL)setExposure:(float)value;
- (float)getExposure;
- (void)setDefaultExposure;
- (BOOL)setAutoFocus:(BOOL)enabled;
- (BOOL)getAutoFocus;
- (BOOL)setAbsoluteFocus:(float)value;
- (float)getAbsoluteFocus;
@end

#endif /* UVCCameraControl_h */
