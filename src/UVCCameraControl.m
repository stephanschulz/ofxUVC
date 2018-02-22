#import "UVCCameraControl.h"

//http://www.usb.org/developers/docs/devclass_docs/
//http://www.usb.org/developers/docs/devclass_docs/USB_Video_Class_1_5.zip
//UVC 1.5 Class specification.pdf

//const uvc_controls_t uvc_controls = {
//	.autoExposure = {
//		.unit = UVC_INPUT_TERMINAL_ID,
//		.selector = 0x02, //CT_AE_MODE_CONTROL
//		.size = 1,
//        .name = @"autoExposure",
//	},
//	.exposure = {
//		.unit = UVC_INPUT_TERMINAL_ID,
//		.selector = 0x04, //CT_EXPOSURE_TIME_ABSOLUTE_CONTROL
//		.size = 4,
//	},
//    
//    .incremental_exposure = {
//		.unit = UVC_INPUT_TERMINAL_ID,
//		.selector = 0x05, //CT_EXPOSURE_TIME_ABSOLUTE_CONTROL
//		.size = 1,
//	},
//	.absoluteFocus = {
//		.unit = 0x09,
//		.selector = 0x03,
//		.size = 8,
//	},	
//	.autoFocus = {
//		.unit = UVC_INPUT_TERMINAL_ID,
//		.selector = 0x08, //CT_FOCUS_AUTO_CONTROL
//		.size = 1,
//	},
//	.focus = {
//		.unit = UVC_INPUT_TERMINAL_ID,
//		.selector = 0x06, //CT_FOCUS_ABSOLUTE_CONTROL
//		.size = 2,
//	},
//	.brightness = {
//		.unit = UVC_PROCESSING_UNIT_ID,
//		.selector = 0x02,
//		.size = 2,
//	},
//	.contrast = {
//		.unit = UVC_PROCESSING_UNIT_ID,
//		.selector = 0x03,
//		.size = 2,
//	},
//	.gain = {
//		.unit = UVC_PROCESSING_UNIT_ID,
//		.selector = 0x04,
//		.size = 2,
//	},
//	.saturation = {
//		.unit = UVC_PROCESSING_UNIT_ID,
//		.selector = 0x07,
//		.size = 2,
//	},
//	.sharpness = {
//		.unit = UVC_PROCESSING_UNIT_ID,
//		.selector = 0x08,
//		.size = 2,
//	},
//	.whiteBalance = {
//		.unit = UVC_PROCESSING_UNIT_ID,
//		.selector = 0x0A,
//		.size = 2,
//	},
//	.autoWhiteBalance = {
//		.unit = UVC_PROCESSING_UNIT_ID,
//		.selector = 0x0B,
//		.size = 1,
//	},
//    .powerLineFrequency = {
//        .unit = UVC_PROCESSING_UNIT_ID,
//        .selector = 0x05,
//        .size = 1,
//    },
//    .backlightCompensation = {
//        .unit = UVC_PROCESSING_UNIT_ID,
//        .selector = 0x01,
//        .size = 2,
//    },
//    .autoHue = {
//        .unit = UVC_PROCESSING_UNIT_ID,
//        .selector = 0x10, //PU_HUE_AUTO_CONTROL
//        .size = 1,
//    },
//    .hue = {
//        .unit = UVC_PROCESSING_UNIT_ID,
//        .selector = 0x06,
//        .size = 2,
//    },
//    .gamma = {
//        .unit = UVC_PROCESSING_UNIT_ID,
//        .selector = 0x09,
//        .size = 2,
//    },
//    .zoom = {
//        .unit = UVC_INPUT_TERMINAL_ID, //CT_ZOOM_ABSOLUTE_CONTROL
//        .selector = 0x0B,
//        .size = 2,
//        .name = @"zoom",
//    },
//    .pantilt = {
//        .unit = UVC_INPUT_TERMINAL_ID, //CT_PANTILT_ABSOLUTE_CONTROL
//        .selector = 0x0D,
//        .size = 4,
//        .name = @"pantilt",
//    },
//    .roll = {
//        .unit = UVC_INPUT_TERMINAL_ID, //CT_ROLL_ABSOLUTE_CONTROL
//        .selector = 0x0F,
//        .size = 2,
//    },
//};


@implementation UVCCameraControl


- (id)initWithLocationID:(UInt32)locationID {
    
   
   
    
	if( self = [super init] ) {
		interface = NULL;
		
		// Find All USB Devices, get their locationId and check if it matches the requested one
        NSLog( @"Find All USB Devices");
        
		CFMutableDictionaryRef matchingDict = IOServiceMatching(kIOUSBDeviceClassName);
		io_iterator_t serviceIterator;
		IOServiceGetMatchingServices( kIOMasterPortDefault, matchingDict, &serviceIterator );
		
		io_service_t camera;
		while( (camera = IOIteratorNext(serviceIterator)) ) {
			// Get DeviceInterface
			IOUSBDeviceInterface **deviceInterface = NULL;
			IOCFPlugInInterface	**plugInInterface = NULL;
			SInt32 score;
			kern_return_t kr = IOCreatePlugInInterfaceForService( camera, kIOUSBDeviceUserClientTypeID, kIOCFPlugInInterfaceID, &plugInInterface, &score );
			if( (kIOReturnSuccess != kr) || !plugInInterface ) {
				NSLog( @"CameraControl Error: IOCreatePlugInInterfaceForService returned 0x%08x.", kr );
				continue;
			}
			
			HRESULT res = (*plugInInterface)->QueryInterface(plugInInterface, CFUUIDGetUUIDBytes(kIOUSBDeviceInterfaceID), (LPVOID*) &deviceInterface );
			(*plugInInterface)->Release(plugInInterface);
			if( res || deviceInterface == NULL ) {
				NSLog( @"CameraControl Error: QueryInterface returned %d.\n", (int)res );
				continue;
			}
			
			UInt32 currentLocationID = 0;
			(*deviceInterface)->GetLocationID(deviceInterface, &currentLocationID);
			
            NSLog( @"currentLocationID %d ", (int)currentLocationID );
            
			if( currentLocationID == locationID ) {
				// Yep, this is the USB Device that was requested!
                 NSLog( @"Yep, this is the USB Device that was requested %d ", (int)currentLocationID );
                
				interface = [self getControlInferaceWithDeviceInterface:deviceInterface];
				return self;
			}
		} // end while
		
      
	}
	return self;
}


- (id)initWithVendorID:(long)vendorID productID:(long)productID interfaceNum:(long)interNum {
	if( self = [super init] ) {
		interface = NULL;
        
        interfaceNum = interNum;
		
		// Find USB Device
		CFMutableDictionaryRef matchingDict = IOServiceMatching(kIOUSBDeviceClassName);
		CFNumberRef numberRef;
		
		numberRef = CFNumberCreate(kCFAllocatorDefault, kCFNumberSInt32Type, &vendorID);
		CFDictionarySetValue( matchingDict, CFSTR(kUSBVendorID), numberRef );
		CFRelease(numberRef);
		
		numberRef = CFNumberCreate(kCFAllocatorDefault, kCFNumberSInt32Type, &productID);
		CFDictionarySetValue( matchingDict, CFSTR(kUSBProductID), numberRef );
		CFRelease(numberRef);
		io_service_t camera = IOServiceGetMatchingService( kIOMasterPortDefault, matchingDict );
		
		
		// Get DeviceInterface
		IOUSBDeviceInterface **deviceInterface = NULL;
		IOCFPlugInInterface	**plugInInterface = NULL;
		SInt32 score;
		kern_return_t kr = IOCreatePlugInInterfaceForService( camera, kIOUSBDeviceUserClientTypeID, kIOCFPlugInInterfaceID, &plugInInterface, &score );
        if( (kIOReturnSuccess != kr) || !plugInInterface ) {
            NSLog( @"CameraControl Error: IOCreatePlugInInterfaceForService returned 0x%08x.", kr );
			return self;
        }
		
        HRESULT res = (*plugInInterface)->QueryInterface(plugInInterface, CFUUIDGetUUIDBytes(kIOUSBDeviceInterfaceID), (LPVOID*) &deviceInterface );
        (*plugInInterface)->Release(plugInInterface);
        if( res || deviceInterface == NULL ) {
            NSLog( @"CameraControl Error: QueryInterface returned %d.\n", (int)res );
            return self;
        }
		
		interface = [self getControlInferaceWithDeviceInterface:deviceInterface];
	}
	return self;
}


- (IOUSBInterfaceInterface190 **)getControlInferaceWithDeviceInterface:(IOUSBDeviceInterface **)deviceInterface {
	IOUSBInterfaceInterface190 **controlInterface;
	
	io_iterator_t interfaceIterator;
	IOUSBFindInterfaceRequest interfaceRequest;
	interfaceRequest.bInterfaceClass = UVC_CONTROL_INTERFACE_CLASS;
	interfaceRequest.bInterfaceSubClass = UVC_CONTROL_INTERFACE_SUBCLASS;
	interfaceRequest.bInterfaceProtocol = kIOUSBFindInterfaceDontCare;
	interfaceRequest.bAlternateSetting = kIOUSBFindInterfaceDontCare;
	
	IOReturn success = (*deviceInterface)->CreateInterfaceIterator( deviceInterface, &interfaceRequest, &interfaceIterator );
	if( success != kIOReturnSuccess ) {
		return NULL;
	}
	
	io_service_t usbInterface;
	HRESULT result;
	
	
	if( (usbInterface = IOIteratorNext(interfaceIterator)) ) {
		IOCFPlugInInterface **plugInInterface = NULL;
		
		//Create an intermediate plug-in
		SInt32 score;
		kern_return_t kr = IOCreatePlugInInterfaceForService( usbInterface, kIOUSBInterfaceUserClientTypeID, kIOCFPlugInInterfaceID, &plugInInterface, &score );
		
		//Release the usbInterface object after getting the plug-in
		kr = IOObjectRelease(usbInterface);
		if( (kr != kIOReturnSuccess) || !plugInInterface ) {
			NSLog( @"CameraControl Error: Unable to create a plug-in (%08x)\n", kr );
			return NULL;
		}
		
		//Now create the device interface for the interface
		result = (*plugInInterface)->QueryInterface( plugInInterface, CFUUIDGetUUIDBytes(kIOUSBInterfaceInterfaceID), (LPVOID *) &controlInterface );
		
		//No longer need the intermediate plug-in
		(*plugInInterface)->Release(plugInInterface);
		
		if( result || !controlInterface ) {
			NSLog( @"CameraControl Error: Couldn’t create a device interface for the interface (%08x)", (int) result );
			return NULL;
		}
		
		return controlInterface;
	}
	
	return NULL;
}


- (void)dealloc {
	if( interface ) {
		(*interface)->USBInterfaceClose(interface);
		(*interface)->Release(interface);
	}
	[super dealloc];
}


- (BOOL)sendControlRequest:(IOUSBDevRequest)controlRequest {
	if( !interface ){
		NSLog( @"CameraControl Error: No interface to send request" );
		return NO;
	}
	
	//Now open the interface. This will cause the pipes associated with
	//the endpoints in the interface descriptor to be instantiated
	kern_return_t kr = (*interface)->USBInterfaceOpen(interface);
	if (kr != kIOReturnSuccess)	{
		NSLog( @"CameraControl Error: Unable to open interface (%08x)\n", kr );
		return NO;
	}
	
	kr = (*interface)->ControlRequest( interface, 0, &controlRequest );
	if( kr != kIOReturnSuccess ) {
		kr = (*interface)->USBInterfaceClose(interface);
		NSLog( @"CameraControl Error: Control request failed: %08x", kr );
		return NO;
	}
	
	kr = (*interface)->USBInterfaceClose(interface);
	
	return YES;
}

- (BOOL)setData:(int)value withLength:(int)length forSelector:(int)selector at:(int)unitId {
    
    
//     printf("setData %lu \n",value);
 printf("setData %d \n",value);
    
//    value = 0; //2047; //985087;
    
//    long vv = value<<16; //985087;
    
//     printf("setData %lu \n",vv);
    
	IOUSBDevRequest controlRequest;
	controlRequest.bmRequestType = USBmakebmRequestType( kUSBOut, kUSBClass, kUSBInterface );
	controlRequest.bRequest = UVC_SET_CUR;
	controlRequest.wValue = (selector << 8) | interfaceNum;
	controlRequest.wIndex = (unitId << 8) | interfaceNum;
	controlRequest.wLength = length;
	controlRequest.wLenDone = 0;
    controlRequest.pData = &value;
	return [self sendControlRequest:controlRequest];
}
/*
 support pointer value of setData
https://github.com/kazu/UVCCameraControl
 */

- (BOOL)setData2:(void*)value withLength:(int)length forSelector:(int)selector at:(int)unitId
{
    
//    value[0] = int(100);
//    value[1] = int(100);
//     NSLog(@"setData2 pan %lu tilt %lu",value[0],value[1]);
    
//    printf("setData2 value0 %d \n",value[0]);
//    printf("setData2 value1 %d \n",value[1]);
    int p = 90*3600;
//    int t = 400;
//    
//    int vv = p << 16;
//    vv += t;
    
//    long pan = value[0];
//    int tilt = value[1];
//    uint8_t data[8];
//    INT_TO_DW(pan, data + 0);
//    INT_TO_DW(tilt, data + 4);
    
//     int vvv = 150; //985087;
    
//     printf("setData2 vvv %d \n",vvv);
//    unsigned char x = ...;
//    int y = x << 16;
    
    
//    long			tmpLong = 0x00000000;
//    memcpy(&tmpLong,value,length);
//
//    printf("setData2 vv %d \n",vv);
//    ret = libusb_control_transfer(
//                                  devh->usb_devh,
//                                  REQ_TYPE_SET, UVC_SET_CUR,
//                                  UVC_CT_PANTILT_ABSOLUTE_CONTROL << 8,
//                                  uvc_get_camera_terminal(devh)->bTerminalID << 8 | devh->info->ctrl_if.bInterfaceNumber,
//                                  data,
//                                  sizeof(data),
//                                  0);
    
//    printf("control->size %i \n",size);
    printf("setData2->selector %i \n",selector);
    printf("setData2->unit %i \n",unitId);
    printf("setData2->length %i \n",length);
  
    
    IOUSBDevRequest controlRequest;
    controlRequest.bmRequestType = USBmakebmRequestType( kUSBOut, kUSBClass, kUSBInterface );
    controlRequest.bRequest = UVC_SET_CUR;
    controlRequest.wValue = (selector << 8) | interfaceNum;
    controlRequest.wIndex = (unitId << 8) | interfaceNum;
    controlRequest.wLength = length;
    controlRequest.wLenDone = 0;
    controlRequest.pData = value;
    
//    printf("setData2 \n");
//    printf("length %i \n",length);

    
    return [self sendControlRequest:controlRequest];
}


- (long)getDataFor:(int)type withLength:(int)length fromSelector:(int)selector at:(int)unitId {
    long value = 0;
	IOUSBDevRequest controlRequest;
	controlRequest.bmRequestType = USBmakebmRequestType( kUSBIn, kUSBClass, kUSBInterface );
	controlRequest.bRequest = type;
	controlRequest.wValue = (selector << 8) | interfaceNum;
	controlRequest.wIndex = (unitId << 8) | interfaceNum;
	controlRequest.wLength = length;
	controlRequest.wLenDone = 0;
	controlRequest.pData = &value;
	BOOL success = [self sendControlRequest:controlRequest];
    
//    printf("getDataFor %lu \n",value);
//    printf("length %i \n",length);

//    short int signed_value = *(short int*)&value;
    int signed_value = *(int*)&value;
//    printf("signed_value %i \n",signed_value);
    
	return ( success ? signed_value : 0 );
}


// Get Range (min, max)
- (uvc_range_t)getRangeForControl:(const uvc_control_info_t *)control {
    printf("-------(uvc_range_t)getValueForControl-------\n");
	
    uvc_range_t range = { 0, 0 };
	range.min = [self getDataFor:UVC_GET_MIN withLength:control->size fromSelector:control->selector at:control->unit];
    printf("range.min %i \n",range.min);
	
    range.max = [self getDataFor:UVC_GET_MAX withLength:control->size fromSelector:control->selector at:control->unit];
    printf("range.max %i \n",range.max);
    
//    long t = [self getDefaultForControl:control];
//    printf("default %lu \n",t);
    
	return range;
}


// Used to de-/normalize values
- (float)mapValue:(float)value fromMin:(float)fromMin max:(float)fromMax toMin:(float)toMin max:(float)toMax {
	return toMin + (toMax - toMin) * ((value - fromMin) / (fromMax - fromMin));
}

- (long) getInfoForControl:(const uvc_control_info_t *)control{
    return [self getDataFor:UVC_GET_INFO withLength:control->size fromSelector:control->selector at:control->unit];
}
- (long) getDefaultForControl:(const uvc_control_info_t *)control{
//    printf("control->selector %i \n",control->selector);
    return [self getDataFor:UVC_GET_DEF withLength:control->size fromSelector:control->selector at:control->unit];
}

// Get a normalized value
- (float)getValueForControl:(const uvc_control_info_t *)control {
    printf("-------(float)getValueForControl-------\n");
	// TODO: Cache the range somewhere?
	uvc_range_t range = [self getRangeForControl:control];
	
    printf("range.min %i \n",range.min);
    printf("range.max %i \n",range.max);

    
	int intval = [self getDataFor:UVC_GET_CUR withLength:control->size fromSelector:control->selector at:control->unit];
	return [self mapValue:intval fromMin:range.min max:range.max toMin:0 max:1];
}

//- (uvc_range_t)getRangeForControl:(const uvc_control_info_t *)control {

// Set a normalized value
- (BOOL)setValue:(float)value forControl:(const uvc_control_info_t *)control {
    
    printf("(BOOL)setValue:(float)value forControl\n");
    


	// TODO: Cache the range somewhere?
	uvc_range_t range = [self getRangeForControl:control];
	
	int intval = [self mapValue:value fromMin:0 max:1 toMin:range.min max:range.max];
    
    printf("setValue intval %i \n",intval);
    
    printf("control->size %i \n",control->size);
    printf("control->selector %i \n",control->selector);
     printf("control->unit %i \n",control->unit);
    
	return [self setData:intval withLength:control->size forSelector:control->selector at:control->unit];
}

// Set a normalized value
- (BOOL)setValue2:(float*)value forControl:(const uvc_control_info_t *)control {
    
    printf("(BOOL)setValue:(float)value forControl\n");
    
    // TODO: Cache the range somewhere?
    uvc_range_t range = [self getRangeForControl:control];
    
    int intval[2];
//    int intval[2];
    intval[0] = [self mapValue:value[0] fromMin:0 max:1 toMin:range.min max:range.max];
    printf("setValue intval[0] %i \n",intval[0]);
    intval[1] = [self mapValue:value[1] fromMin:0 max:1 toMin:range.min max:range.max];
    printf("setValue intval[1] %i \n",intval[1]);
    
    printf("control->size %i \n",control->size);
    printf("control->selector %i \n",control->selector);
    printf("control->unit %i \n",control->unit);
    
//    return [self setData2:(int*)intval withLength:control->size forSelector:control->selector at:control->unit];
//    return [self setData2:(void*)intval withLength:control->size forSelector:control->selector at:control->unit];
    return [self setData:intval[0] withLength:control->size forSelector:control->selector at:control->unit];

}




// ================================================================

// Set/Get the actual values for the camera
//


//------EXPOSURE
- (BOOL)setAutoExposure:(BOOL)enabled {
	int intval = (enabled ? 0x08 : 0x01); // "auto exposure modes" ar NOT boolean (on|off) as it seems
	printf("setAutoExposure = %i \n",enabled);
	return [self setData:intval 
			  withLength:uvc_controls.autoExposure.size 
			 forSelector:uvc_controls.autoExposure.selector 
					  at:uvc_controls.autoExposure.unit];
	
}
- (BOOL)getAutoExposure {
	int intval = [self getDataFor:UVC_GET_CUR 
					   withLength:uvc_controls.autoExposure.size 
					 fromSelector:uvc_controls.autoExposure.selector 
							   at:uvc_controls.autoExposure.unit];
	
	return ( intval == 0x08 ? YES : NO );
}
- (BOOL)setExposure:(float)value {
	printf("exposure value %f \n",value);
	value = 1 - value;
	return [self setValue:value forControl:&uvc_controls.exposure];
}
- (void) incrementExposure {
    [self setData:0x01 
       withLength:uvc_controls.exposure.size 
      forSelector:uvc_controls.exposure.selector 
               at:uvc_controls.exposure.unit];
}
- (void) decrementExposure {
    [self setData:0xFF
       withLength:uvc_controls.exposure.size 
      forSelector:uvc_controls.exposure.selector 
               at:uvc_controls.exposure.unit];
}
- (void) setDefaultExposure {
    [self setData:0x00
       withLength:uvc_controls.exposure.size 
      forSelector:uvc_controls.exposure.selector 
               at:uvc_controls.exposure.unit];
}
- (uvc_controls_t *) getControls{
    return (uvc_controls_t *)&uvc_controls;
}
- (float)getExposure {
	float value = [self getValueForControl:&uvc_controls.exposure];
	return 1 - value;
}

//------FOCUS
- (BOOL)setAutoFocus:(BOOL)enabled {
	//int intval = (enabled ? 0x08 : 0x01); //that's how eposure does it
	int intval = (enabled ? 0x01 : 0x00); //that's how white balance does it
	printf("setAutoFocus = %i \n",enabled);
	return [self setData:intval 
			  withLength:uvc_controls.autoFocus.size 
			 forSelector:uvc_controls.autoFocus.selector 
					  at:uvc_controls.autoFocus.unit];
	
}
- (BOOL)getAutoFocus {
	int intval = [self getDataFor:UVC_GET_CUR 
					   withLength:uvc_controls.autoFocus.size 
					 fromSelector:uvc_controls.autoFocus.selector 
							   at:uvc_controls.autoFocus.unit];
	
	//return ( intval == 0x08 ? YES : NO );
	//return ( intval ? YES : NO );
	return ( intval == 0x01 ? YES : NO );
}
- (BOOL)setAbsoluteFocus:(float)value {
	printf("focus value %f \n",value);
	//value = 1 - value;
	return [self setValue:value forControl:&uvc_controls.focus];
	
}
- (float)getAbsoluteFocus {
	//float value = [self getValueForControl:&uvc_controls.absoluteFocus];
	//return 1 - value;
	return [self getValueForControl:&uvc_controls.focus];
}


//------WHITEBALANCE
- (BOOL)setAutoWhiteBalance:(BOOL)enabled {
	int intval = (enabled ? 0x01 : 0x00);
	printf("setAutoWhiteBalance = %i \n",enabled);
	return [self setData:intval 
			  withLength:uvc_controls.autoWhiteBalance.size 
			 forSelector:uvc_controls.autoWhiteBalance.selector 
					  at:uvc_controls.autoWhiteBalance.unit];
	
}
- (BOOL)getAutoWhiteBalance {
	int intval = [self getDataFor:UVC_GET_CUR 
					   withLength:uvc_controls.autoWhiteBalance.size 
					 fromSelector:uvc_controls.autoWhiteBalance.selector 
							   at:uvc_controls.autoWhiteBalance.unit];
	
	return ( intval ? YES : NO );
}
- (BOOL)setWhiteBalance:(float)value {
	printf("whiteBalance value %f \n",value);
	return [self setValue:value forControl:&uvc_controls.whiteBalance];
}
- (float)getWhiteBalance {
	return [self getValueForControl:&uvc_controls.whiteBalance];
}

//------GAIN
- (BOOL)setGain:(float)value {
	printf("gain value %f \n",value);
	
	return [self setValue:value forControl:&uvc_controls.gain];
}
- (float)getGain {
	return [self getValueForControl:&uvc_controls.gain];
}

//------BRIGHTNESS
- (BOOL)setBrightness:(float)value {
	printf("brightness value %f \n",value);
	return [self setValue:value forControl:&uvc_controls.brightness];
}
- (float)getBrightness {
	return [self getValueForControl:&uvc_controls.brightness];
}

//------CONTRAST
- (BOOL)setContrast:(float)value {
    printf("contrast value %f \n",value);
	return [self setValue:value forControl:&uvc_controls.contrast];
}
- (float)getContrast {
	return [self getValueForControl:&uvc_controls.contrast];
}

//------SATURATION
- (BOOL)setSaturation:(float)value {
    printf("saturation value %f \n",value);
	return [self setValue:value forControl:&uvc_controls.saturation];
}
- (float)getSaturation {
	return [self getValueForControl:&uvc_controls.saturation];
}

//------SHARP
- (BOOL)setSharpness:(float)value {
    printf("sharpness value %f \n",value);
	return [self setValue:value forControl:&uvc_controls.sharpness];
}
- (float)getSharpness {
	return [self getValueForControl:&uvc_controls.sharpness];
}

//------POWER FREQ
- (BOOL)setPowerLineFrequency:(float)value {
    printf("powerLineFrequency value %f \n",value);
    return [self setValue:value forControl:&uvc_controls.powerLineFrequency];
}
- (float)getPowerLineFrequency {
    return [self getValueForControl:&uvc_controls.powerLineFrequency];
}

//------BACKLIGHT
- (BOOL)setBacklightCompensation:(float)value {
    printf("backlightCompensation value %f \n",value);
    return [self setValue:value forControl:&uvc_controls.backlightCompensation];
}
- (float)getBacklightCompensation {
    return [self getValueForControl:&uvc_controls.backlightCompensation];
}

//------HUE
- (BOOL)setAutoHue:(BOOL)enabled {
    int intval = (enabled ? 0x01 : 0x00);
    printf("setAutoHue = %i \n",enabled);
    return [self setData:intval
              withLength:uvc_controls.autoHue.size
             forSelector:uvc_controls.autoHue.selector
                      at:uvc_controls.autoHue.unit];
    
}
- (BOOL)getAutoHue {
    int intval = [self getDataFor:UVC_GET_CUR
                       withLength:uvc_controls.autoHue.size
                     fromSelector:uvc_controls.autoHue.selector
                               at:uvc_controls.autoHue.unit];
    
    printf("getAutoHue intval = %i \n",intval);
    return ( intval ? YES : NO );
}
- (BOOL)setHue:(float)value {
    printf("hue value %f \n",value);
    return [self setValue:value forControl:&uvc_controls.hue];
}
- (float)getHue {
    return [self getValueForControl:&uvc_controls.hue];
}

//------GAMMA
- (BOOL)setGamma:(float)value {
    printf("gamma value %f \n",value);
    return [self setValue:value forControl:&uvc_controls.gamma];
}
- (float)getGamma {
    return [self getValueForControl:&uvc_controls.gamma];
}

//------ZOOM
- (BOOL)setZoom:(float)value {
    printf("zoom value %f \n",value);
//    return [self setValue:value forControl:&uvc_controls.zoom];
    
    /*
    int			valToSend = 0x0000;
    valToSend = 100 + value*400 ;
    int paramSize = 8;
    void			*bytesToSend = malloc(paramSize);
    bzero(bytesToSend,paramSize);
    memcpy(bytesToSend,&valToSend,paramSize);
    
    [self setData2:bytesToSend
        withLength:uvc_controls.zoom.size
       forSelector:uvc_controls.zoom.selector
                at:uvc_controls.zoom.unit];
    */
    
    int zoomValue = value * 400;
    uint8_t data[2];
    SHORT_TO_SW(zoomValue, data + 0);
    for(int i=0; i<2; i++){
        //      printf("setPantilt data %d %d \n",i,data[i]);
        printf("%d , ",data[i]);
    }
    printf("\n");

    
    
    [self setData2:data //bytesToSend
        withLength:uvc_controls.zoom.size
       forSelector:uvc_controls.zoom.selector
                at:uvc_controls.zoom.unit];
    
}
- (float)getZoom {
    printf("getZoom value\n");
    return [self getValueForControl:&uvc_controls.zoom];
}

//------PANTILT
//- (BOOL)setPantilt:(float)value {
//    printf("pantilt value %f \n",value);
//    return [self setValue:value forControl:&uvc_controls.pantilt];
//}
// resetTiltPan support only logitech Orbit.
//- (BOOL)setPanTilt:(BOOL)reset withPan:(float)pan withTilt:(float)tilt {
- (BOOL)setPantilt:(float*)value {

//    float value[2];
    BOOL ret;
    
      printf("setPantilt value0 %f \n",value[0]);
      printf("setPantilt value1 %f \n",value[1]);
    
 
//    value[0] = tilt*100;
//    value[1] = pan*100;
    
#ifdef DEBUG_UVC_CAMERA
    NSLog(@"setPanTilt pan %d tilt %d",value[0],value[1]);
#endif
    
//    int16_t value2[2];
//    
//    value2[0] = 100;
//    value2[1] = 700;
    //https://github.com/ktossell/libuvc/blob/master/src/ctrl-gen.c
    //https://github.com/ghafran/ptz
    //https://int80k.com/libuvc/doc/
//    int pan = (0.5-value[0])*3600;
//    int tilt = (0.5-value[1])*3600;
    int pan =  (0.5 - value[0]) * 36000*2; //- 18000;
    int tilt = (0.5 - value[1]) * 36000*2;// - 18000;

    
    printf("INT_TO_DW pan %d \n",pan);
    printf("INT_TO_DW tilt %d \n",tilt);
    
    uint8_t data[8];
    INT_TO_DW(pan, data + 0); //pan
    INT_TO_DW(tilt, data + 4); //tilt
    for(int i=0; i<8; i++){
//      printf("setPantilt data %d %d \n",i,data[i]);
         printf("%d , ",data[i]);
    }
    printf("\n");
    
    
    int			valToSend = 0x0000;
    
    //    valToSend = (int)labs(param->val);
    //    //NSLog(@"\t\tabs val is %d",valToSend);
    //    if (param->val < 0)
    //        valToSend = (~valToSend + 1);
    
    valToSend =  value[0]*36000 ;
    //    NSLog(@"\t\tabs val is %d",valToSend);
    int paramSize = 8;
    void			*bytesToSend = malloc(paramSize);
    bzero(bytesToSend,paramSize);
    memcpy(bytesToSend,&valToSend,paramSize);
    
    printf("bytesToSend %p",bytesToSend);
//    for(int i=0; i<8; i++){
//        //      printf("setPantilt data %d %d \n",i,data[i]);
//        printf("%d , ",bytesToSend[i]);
//    }
//    printf("\n");

    
//     printf("setPantilt data %d \n",data);
//    printf("setPantilt sizeof %lu \n",sizeof(data));
//    printf("setPantilt size %i \n", uvc_controls.pantilt.size);
   
//    int vv = 2000;
//    NSLog(@"setPanTilt pan %d tilt %d",value2[0],value2[1]);
    
//    int			valToSend = 0x0000;
    
//    valToSend = (int)labs(param->val);
//    //NSLog(@"\t\tabs val is %d",valToSend);
//    if (param->val < 0)
//        valToSend = (~valToSend + 1);

//    valToSend = value2[1] ;
//    NSLog(@"\t\tabs val is %d",valToSend);
//    int paramSize = 8;
//    void			*bytesToSend = malloc(paramSize);
//    bzero(bytesToSend,paramSize);
//    memcpy(bytesToSend,&data,paramSize);

    
    [self setData2:data
        withLength:uvc_controls.pantilt.size
       forSelector:uvc_controls.pantilt.selector
                at:uvc_controls.pantilt.unit];


    
//    [self setData2:(int)vv
//        withLength:uvc_controls.pantilt.size
//       forSelector:uvc_controls.pantilt.selector
//                at:uvc_controls.pantilt.unit];
    
//     return [self setValue:value[0] forControl:&uvc_controls.pantilt];
    

//    int8_t val = 3;
//    return [self setData2:&val
//               withLength:uvc_controls.pantilt.size
//              forSelector:uvc_controls.pantilt.selector
//                       at:uvc_controls.pantilt.unit];
    
//   return [self setValue2:(float*)value forControl:&uvc_controls.pantilt];
//   ret = [self setData2:(void *)value
//              withLength:uvc_controls.pantiltrel.size
//             forSelector:uvc_controls.pantiltrel.selector
//                      at:uvc_controls.pantiltrel.unit];
//    if(ret){
//        NSLog(@"setPanTilt: success");
//    }else{
//        NSLog(@"setPanTilt: fail");
//    }
//    return ret;
}
- (float)getPantilt {
    return [self getValueForControl:&uvc_controls.pantilt];
}

//------ROLL
- (BOOL)setRoll:(float)value {
    printf("roll value %f \n",value);
    return [self setValue:value forControl:&uvc_controls.roll];
}
- (float)getRoll {
    return [self getValueForControl:&uvc_controls.roll];
}

- (BOOL) printDefaults{
//    NSLog(@"%s",__func__);

    printf("default %s %lu \n", [uvc_controls.autoExposure.name UTF8String], [self getDefaultForControl:&uvc_controls.autoExposure]);
    printf("default %s %lu \n", [uvc_controls.pantilt.name UTF8String], [self getDefaultForControl:&uvc_controls.pantilt]);
    printf("default %s %lu \n", [uvc_controls.zoom.name UTF8String], [self getDefaultForControl:&uvc_controls.zoom]);
    printf("default %s %lu \n", [uvc_controls.brightness.name UTF8String], [self getDefaultForControl:&uvc_controls.brightness]);
    printf("default %s %lu \n", [uvc_controls.contrast.name UTF8String], [self getDefaultForControl:&uvc_controls.contrast]);
    printf("default %s %lu \n", [uvc_controls.sharpness.name UTF8String], [self getDefaultForControl:&uvc_controls.sharpness]);
       printf("default %s %lu \n", [uvc_controls.saturation.name UTF8String], [self getDefaultForControl:&uvc_controls.saturation]);
      printf("default %s %lu \n", [uvc_controls.gain.name UTF8String], [self getDefaultForControl:&uvc_controls.gain]);
}
@end
