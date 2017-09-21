#import <Foundation/Foundation.h>
#include <CoreFoundation/CoreFoundation.h>

#include <IOKit/IOKitLib.h>
#include <IOKit/IOMessage.h>
#include <IOKit/IOCFPlugIn.h>
#include <IOKit/usb/IOUSBLib.h>

//http://phoboslab.org/log/2009/07/uvc-camera-control-for-mac-os-x#comment107

#define USE_C920 //or BRIO


#define UVC_INPUT_TERMINAL_ID 0x01

#ifdef USE_C920
#define UVC_PROCESSING_UNIT_ID 0x03 //changed this to work with c920, might not work with others
#else
#define UVC_PROCESSING_UNIT_ID 0x02
#endif


#define UVC_CONTROL_INTERFACE_CLASS 14
#define UVC_CONTROL_INTERFACE_SUBCLASS 1

//	video class-specific request codes
#define UVC_SET_CUR	0x01
#define UVC_GET_CUR	0x81
#define UVC_GET_MIN	0x82
#define UVC_GET_MAX	0x83
#define UVC_GET_INFO 0x86
#define UVC_GET_DEF 0x87


//https://github.com/ktossell/libuvc/blob/master/src/ctrl-gen.c
/** Converts an int16 into an unaligned two-byte little-endian integer */
#define SHORT_TO_SW(s, p) \
(p)[0] = (s); \
(p)[1] = (s) >> 8;

/** Converts an int32 into an unaligned four-byte little-endian integer */
#define INT_TO_DW(i, p) \
(p)[0] = (i); \
(p)[1] = (i) >> 8; \
(p)[2] = (i) >> 16; \
(p)[3] = (i) >> 24;

typedef struct {
	int min, max;
} uvc_range_t;

typedef struct {
	int unit;
	int selector;
	int size;
    NSString *name;
} uvc_control_info_t;

typedef struct {
	uvc_control_info_t autoExposure;
	uvc_control_info_t exposure;
	uvc_control_info_t absoluteFocus;
	uvc_control_info_t autoFocus;
	uvc_control_info_t focus;
	uvc_control_info_t brightness;
	uvc_control_info_t contrast;
	uvc_control_info_t gain;
	uvc_control_info_t saturation;
	uvc_control_info_t sharpness;
	uvc_control_info_t whiteBalance;
	uvc_control_info_t autoWhiteBalance;
    uvc_control_info_t incremental_exposure;
    uvc_control_info_t powerLineFrequency;
    uvc_control_info_t backlightCompensation;
    uvc_control_info_t autoHue;
    uvc_control_info_t hue;
    uvc_control_info_t gamma;
    uvc_control_info_t zoom;
    uvc_control_info_t pantilt;
    uvc_control_info_t roll;
} uvc_controls_t ;

const uvc_controls_t uvc_controls = {
    .autoExposure = {
        .unit = UVC_INPUT_TERMINAL_ID,
        .selector = 0x02, //CT_AE_MODE_CONTROL
        .size = 1,
        .name = @"autoExposure",
    },
    .exposure = {
        .unit = UVC_INPUT_TERMINAL_ID,
        .selector = 0x04, //CT_EXPOSURE_TIME_ABSOLUTE_CONTROL
        .size = 4,
        .name = @"exposure",
    },
    
    .incremental_exposure = {
        .unit = UVC_INPUT_TERMINAL_ID,
        .selector = 0x05, //CT_EXPOSURE_TIME_ABSOLUTE_CONTROL
        .size = 1,
        .name = @"incremental_exposure",
    },
    .absoluteFocus = {
        .unit = 0x09,
        .selector = 0x03,
        .size = 8,
        .name = @"absoluteFocus",
    },
    .autoFocus = {
        .unit = UVC_INPUT_TERMINAL_ID,
        .selector = 0x08, //CT_FOCUS_AUTO_CONTROL
        .size = 1,
        .name = @"autoFocus",
    },
    .focus = {
        .unit = UVC_INPUT_TERMINAL_ID,
        .selector = 0x06, //CT_FOCUS_ABSOLUTE_CONTROL
        .size = 2,
        .name = @"focus",
    },
    .brightness = {
        .unit = UVC_PROCESSING_UNIT_ID,
        .selector = 0x02,
        .size = 2,
        .name = @"brightness",
    },
    .contrast = {
        .unit = UVC_PROCESSING_UNIT_ID,
        .selector = 0x03,
        .size = 2,
        .name = @"contrast",
    },
    .gain = {
        .unit = UVC_PROCESSING_UNIT_ID,
        .selector = 0x04,
        .size = 2,
        .name = @"gain",
    },
    .saturation = {
        .unit = UVC_PROCESSING_UNIT_ID,
        .selector = 0x07,
        .size = 2,
        .name = @"saturation",
    },
    .sharpness = {
        .unit = UVC_PROCESSING_UNIT_ID,
        .selector = 0x08,
        .size = 2,
        .name = @"sharpness",
    },
    .whiteBalance = {
        .unit = UVC_PROCESSING_UNIT_ID,
        .selector = 0x0A,
        .size = 2,
        .name = @"whiteBalance",
    },
    .autoWhiteBalance = {
        .unit = UVC_PROCESSING_UNIT_ID,
        .selector = 0x0B,
        .size = 1,
        .name = @"autoWhiteBalance",
    },
    .powerLineFrequency = {
        .unit = UVC_PROCESSING_UNIT_ID,
        .selector = 0x05,
        .size = 1,
        .name = @"powerLineFrequency",
    },
    .backlightCompensation = {
        .unit = UVC_PROCESSING_UNIT_ID,
        .selector = 0x01,
        .size = 2,
        .name = @"backlightCompensation",
    },
    .autoHue = {
        .unit = UVC_PROCESSING_UNIT_ID,
        .selector = 0x10, //PU_HUE_AUTO_CONTROL
        .size = 1,
        .name = @"autoHue",
    },
    .hue = {
        .unit = UVC_PROCESSING_UNIT_ID,
        .selector = 0x06,
        .size = 2,
        .name = @"hue",
    },
    .gamma = {
        .unit = UVC_PROCESSING_UNIT_ID,
        .selector = 0x09,
        .size = 2,
        .name = @"gamma",
    },
    .zoom = {
        .unit = UVC_INPUT_TERMINAL_ID, //CT_ZOOM_ABSOLUTE_CONTROL
        .selector = 0x0B,
        .size = 2,
        .name = @"zoom",
    },
    .pantilt = {
        .unit = UVC_INPUT_TERMINAL_ID, //CT_PANTILT_ABSOLUTE_CONTROL
        .selector = 0x0D,
        .size = 4,
        .name = @"pantilt",
    },
    .roll = {
        .unit = UVC_INPUT_TERMINAL_ID, //CT_ROLL_ABSOLUTE_CONTROL
        .selector = 0x0F,
        .size = 2,
        .name = @"roll",
    },
};



@interface UVCCameraControl : NSObject {
	long dataBuffer;
	IOUSBInterfaceInterface190 **interface;
    
    long interfaceNum;
}


- (id)initWithLocationID:(UInt32)locationID;
- (id)initWithVendorID:(long)vendorID productID:(long)productID interfaceNum:(long)interfaceNum;
- (IOUSBInterfaceInterface190 **)getControlInferaceWithDeviceInterface:(IOUSBDeviceInterface **)deviceInterface;

- (BOOL)sendControlRequest:(IOUSBDevRequest)controlRequest;
- (BOOL)setData:(int)value withLength:(int)length forSelector:(int)selector at:(int)unitID;
- (BOOL)setData2:(void*)value withLength:(int)length forSelector:(int)selector at:(int)unitID;
- (long)getDataFor:(int)type withLength:(int)length fromSelector:(int)selector at:(int)unitID;

- (uvc_range_t)getRangeForControl:(const uvc_control_info_t *)control;
- (float)mapValue:(float)value fromMin:(float)fromMin max:(float)fromMax toMin:(float)toMin max:(float)toMax;
- (float)getValueForControl:(const uvc_control_info_t *)control;
- (BOOL)setValue:(float)value forControl:(const uvc_control_info_t *)control;
- (BOOL)setValue2:(float*)value forControl:(const uvc_control_info_t *)control;

- (void) incrementExposure;
- (void) decrementExposure;
- (void) setDefaultExposure;

- (long) getInfoForControl:(const uvc_control_info_t *)control;
- (long) getDefaultForControl:(const uvc_control_info_t *)control;
- (uvc_controls_t *) getControls;

- (BOOL)setAutoExposure:(BOOL)enabled;
- (BOOL)getAutoExposure;
- (BOOL)setExposure:(float)value;
- (float)getExposure;

- (BOOL)setAutoFocus:(BOOL)enabled;
- (BOOL)getAutoFocus;
- (BOOL)setAbsoluteFocus:(float)value;
- (float)getAbsoluteFocus;

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
- (BOOL)setPowerLineFrequency:(float)value;
- (float)getPowerLineFrequency;
- (BOOL)setBacklightCompensation:(float)value;
- (float)getBacklightCompensation;

- (BOOL)setAutoHue:(BOOL)enabled;
- (BOOL)getAutoHue;
- (BOOL)setHue:(float)value;
- (float)getHue;

- (BOOL)setGamma:(float)value;
- (float)getGamma;

- (BOOL)setZoom:(float)value;
- (float)getZoom;
//- (BOOL)setPantilt:(float)value;
//- (BOOL)setPanTilt:(BOOL)reset withPan:(float)pan withTilt:(float)tilt;
- (BOOL)setPantilt:(float*)value;
- (float)getPantilt;
- (BOOL)setRoll:(float)value;
- (float)getRoll;

- (BOOL) resetToDefaults;
- (BOOL) printDefaults;
@end
