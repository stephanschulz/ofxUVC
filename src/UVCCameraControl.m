#import "UVCCameraControl.h"

// Add missing constant
#define kUSBDescTypeCSInterface 0x24

@implementation UVCCameraControls

bool bDebug_UVCCameraControl = false;

- (void)initializeWithProcessingUnitID:(int)processingUnitID {
    // Initialize the controls structure with default values
    uvc_control_info_t temp;
    
    // scanningMode
    temp.unit = UVC_INPUT_TERMINAL_ID;
    temp.selector = UVCCameraTerminal_scanningMode;
    temp.size = 1;
    temp.name = @"scanningMode";
    self.scanningMode = temp;
    
    // aeMode
    temp.unit = UVC_INPUT_TERMINAL_ID;
    temp.selector = UVCCameraTerminal_aeMode;
    temp.size = 1;
    temp.name = @"aeMode";
    self.aeMode = temp;
    
    // aePriority
    temp.unit = UVC_INPUT_TERMINAL_ID;
    temp.selector = UVCCameraTerminal_aePriority;
    temp.size = 1;
    temp.name = @"aePriority";
    self.aePriority = temp;
    
    // exposureTimeAbsolute
    temp.unit = UVC_INPUT_TERMINAL_ID;
    temp.selector = UVCCameraTerminal_exposureTimeAbsolute;
    temp.size = 4;
    temp.name = @"exposureTimeAbsolute";
    self.exposureTimeAbsolute = temp;
    
    // exposureTimeRelative
    temp.unit = UVC_INPUT_TERMINAL_ID;
    temp.selector = UVCCameraTerminal_exposureTimeRelative;
    temp.size = 1;
    temp.name = @"exposureTimeRelative";
    self.exposureTimeRelative = temp;
    
    // focusAbsolute
    temp.unit = UVC_INPUT_TERMINAL_ID;
    temp.selector = UVCCameraTerminal_focusAbsolute;
    temp.size = 2;
    temp.name = @"focusAbsolute";
    self.focusAbsolute = temp;
    
    // focusRelative
    temp.unit = UVC_INPUT_TERMINAL_ID;
    temp.selector = UVCCameraTerminal_focusRelative;
    temp.size = 1;
    temp.name = @"focusRelative";
    self.focusRelative = temp;
    
    // focusAuto
    temp.unit = UVC_INPUT_TERMINAL_ID;
    temp.selector = UVCCameraTerminal_focusAuto; // == 0x08
    temp.size = 1;
    temp.name = @"focusAuto";
    self.focusAuto = temp;
    
    // irisAbsolute
    temp.unit = UVC_INPUT_TERMINAL_ID;
    temp.selector = UVCCameraTerminal_irisAbsolute;
    temp.size = 8; //2;
    temp.name = @"irisAbsolute";
    self.irisAbsolute = temp;
    
    // irisRelative
    temp.unit = UVC_INPUT_TERMINAL_ID;
    temp.selector = UVCCameraTerminal_irisRelative;
    temp.size = 1;
    temp.name = @"irisRelative";
    self.irisRelative = temp;
    
    // brightness
    temp.unit = processingUnitID;
    temp.selector = UVCProcessingUnit_brightness;
    temp.size = 2;
    temp.name = @"brightness";
    self.brightness = temp;
    
    // contrast
    temp.unit = processingUnitID;
    temp.selector = UVCProcessingUnit_contrast;
    temp.size = 2;
    temp.name = @"contrast";
    self.contrast = temp;
    
    // gain
    temp.unit = processingUnitID;
    temp.selector = UVCProcessingUnit_gain;
    temp.size = 2;
    temp.name = @"gain";
    self.gain = temp;
    
    // saturation
    temp.unit = processingUnitID;
    temp.selector = UVCProcessingUnit_saturation;
    temp.size = 2;
    temp.name = @"saturation";
    self.saturation = temp;
    
    // sharpness
    temp.unit = processingUnitID;
    temp.selector = UVCProcessingUnit_sharpness;
    temp.size = 2;
    temp.name = @"sharpness";
    self.sharpness = temp;
    
    // whiteBalance
    temp.unit = processingUnitID;
    temp.selector = UVCProcessingUnit_whiteBalanceTemperature;
    temp.size = 2;
    temp.name = @"whiteBalance";
    self.whiteBalance = temp;
    
    // autoWhiteBalance
    temp.unit = processingUnitID;
    temp.selector = UVCProcessingUnit_whiteBalanceTemperatureAuto;
    temp.size = 1;
    temp.name = @"autoWhiteBalance";
    self.autoWhiteBalance = temp;
    
    // incremental_exposure
    temp.unit = UVC_INPUT_TERMINAL_ID;
    temp.selector = UVCCameraTerminal_exposureTimeRelative;
    temp.size = 1;
    temp.name = @"incremental_exposure";
    self.incremental_exposure = temp;
    
    // powerLineFrequency
    temp.unit = processingUnitID;
    temp.selector = UVCProcessingUnit_powerLineFrequency;
    temp.size = 1;
    temp.name = @"powerLineFrequency";
    self.powerLineFrequency = temp;
    
    // backlightCompensation
    temp.unit = processingUnitID;
    temp.selector = UVCProcessingUnit_backlightCompensation;
    temp.size = 2;
    temp.name = @"backlightCompensation";
    self.backlightCompensation = temp;
    
    // autoHue
    temp.unit = processingUnitID;
    temp.selector = UVCProcessingUnit_hueAuto;
    temp.size = 1;
    temp.name = @"autoHue";
    self.autoHue = temp;
    
    // hue
    temp.unit = processingUnitID;
    temp.selector = UVCProcessingUnit_hue;
    temp.size = 2;
    temp.name = @"hue";
    self.hue = temp;
    
    // gamma
    temp.unit = processingUnitID;
    temp.selector = UVCProcessingUnit_gamma;
    temp.size = 2;
    temp.name = @"gamma";
    self.gamma = temp;
    
    // zoomAbsolute
    temp.unit = UVC_INPUT_TERMINAL_ID;
    temp.selector = UVCCameraTerminal_zoomAbsolute;
    temp.size = 2;
    temp.name = @"zoomAbsolute";
    self.zoomAbsolute = temp;
    
    // pantiltAbsolute
    temp.unit = UVC_INPUT_TERMINAL_ID;
    temp.selector = UVCCameraTerminal_pantiltAbsolute;
    temp.size = 8;
    temp.name = @"pantiltAbsolute";
    self.pantiltAbsolute = temp;
    
    // rollAbsolute
    temp.unit = UVC_INPUT_TERMINAL_ID;
    temp.selector = UVCCameraTerminal_rollAbsolute;
    temp.size = 2;
    temp.name = @"rollAbsolute";
    self.rollAbsolute = temp;
    
    // rollRelative
    temp.unit = UVC_INPUT_TERMINAL_ID;
    temp.selector = UVCCameraTerminal_rollRelative;
    temp.size = 1;
    temp.name = @"rollRelative";
    self.rollRelative = temp;
    
    // privacy
    temp.unit = UVC_INPUT_TERMINAL_ID;
    temp.selector = UVCCameraTerminal_privacy;
    temp.size = 1;
    temp.name = @"privacy";
    self.privacy = temp;
    
    // focusSimple
    temp.unit = UVC_INPUT_TERMINAL_ID;
    temp.selector = UVCCameraTerminal_focusSimple;
    temp.size = 1;
    temp.name = @"focusSimple";
    self.focusSimple = temp;
    
    // digitalWindow
    temp.unit = UVC_INPUT_TERMINAL_ID;
    temp.selector = UVCCameraTerminal_digitalWindow;
    temp.size = 8;
    temp.name = @"digitalWindow";
    self.digitalWindow = temp;
    
    // regionOfInterest
    temp.unit = UVC_INPUT_TERMINAL_ID;
    temp.selector = UVCCameraTerminal_regionOfInterest;
    temp.size = 8;
    temp.name = @"regionOfInterest";
    self.regionOfInterest = temp;
    
    // led
    temp.unit = processingUnitID;
    temp.selector = UVCProcessingUnit_analogVideoStandard; // Using a placeholder, adjust as needed
    temp.size = 1;
    temp.name = @"led";
    self.led = temp;
    
}

@end

@implementation UVCCameraControl

- (void)initializeControls {
    rangeCache = [[NSMutableDictionary alloc] init];
    // Create a new UVCCameraControls instance
    controls = [[UVCCameraControls alloc] init];
    
    // Initialize with default processing unit ID (will be updated later)
    [controls initializeWithProcessingUnitID:0x02];
}

- (id)initWithLocationID:(UInt32)locationID {
    self = [super init];
    if (self) {
        [self initializeControls];
        
        // Get device interface
        IOUSBDeviceInterface **deviceInterface = [self getDeviceInterfaceWithLocationID:locationID];
        if (!deviceInterface) {
            NSLog(@"Failed to get device interface");
            return nil;
        }
        
        // Extract processing unit ID before getting control interface
        processingUnitID = [self extractProcessingUnitID:deviceInterface];
        NSLog(@"Using processing unit ID: 0x%02x", processingUnitID);
        
        // Now get the control interface
        controlInterface = [self getControlInferaceWithDeviceInterface:deviceInterface];
        if (!controlInterface) {
            NSLog(@"Failed to get control interface");
            (*deviceInterface)->Release(deviceInterface);
            return nil;
        }
        
        // Update control units with the extracted processing unit ID
        [controls initializeWithProcessingUnitID:processingUnitID];
    }
    return self;
}

- (id)initWithVendorID:(UInt16)vendorID productID:(UInt16)productID interfaceNum:(UInt8)interfaceNum {
    self = [super init];
    if (self) {
        [self initializeControls];
        
        // Get device interface
        IOUSBDeviceInterface **deviceInterface = [self getDeviceInterfaceWithVendorID:vendorID productID:productID];
        if (!deviceInterface) {
            NSLog(@"Failed to get device interface");
            return nil;
        }
        
        // Extract processing unit ID before getting control interface
        processingUnitID = [self extractProcessingUnitID:deviceInterface];
        NSLog(@"Using processing unit ID: 0x%02x", processingUnitID);
        
        // Now get the control interface
        controlInterface = [self getControlInferaceWithDeviceInterface:deviceInterface];
        if (!controlInterface) {
            NSLog(@"Failed to get control interface");
            (*deviceInterface)->Release(deviceInterface);
            return nil;
        }
        
        // Update control units with the extracted processing unit ID
        [controls initializeWithProcessingUnitID:processingUnitID];
    }
    return self;
}

- (IOUSBInterfaceInterface190 **)getControlInferaceWithDeviceInterface:(IOUSBDeviceInterface **)deviceInterface {
    
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
        IOUSBInterfaceInterface190 **controlInterface;
        
        //Create an intermediate plug-in
        SInt32 score;
        kern_return_t kr;
        
        kr = IOCreatePlugInInterfaceForService( usbInterface, kIOUSBInterfaceUserClientTypeID, kIOCFPlugInInterfaceID, &plugInInterface, &score );
        
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
            NSLog( @"CameraControl Error: Couldn't create a device interface for the interface (%08x)", (int) result );
            return NULL;
        }
        
        return controlInterface;
    }
    
    return NULL;
}


- (void)dealloc {
    if( controlInterface ) {
        (*controlInterface)->USBInterfaceClose(controlInterface);
        (*controlInterface)->Release(controlInterface);
    }
//    [super dealloc];
}


- (BOOL)sendControlRequest:(IOUSBDevRequest)controlRequest {
    if( !controlInterface ){
        NSLog( @"CameraControl Error: No interface to send request" );
        return NO;
    }
    
    //Now open the interface. This will cause the pipes associated with
    //the endpoints in the interface descriptor to be instantiated
    bool successful1 = true;
    kern_return_t kr = (*controlInterface)->USBInterfaceOpen(controlInterface);
    if (kr != kIOReturnSuccess)    {
        //        NSLog( @"CameraControl Error: Unable to open interface (%08x)\n", kr );
        //        return NO;
        successful1 = false;
    }
    
    bool successful2 = true;
    kern_return_t kr2 = (*controlInterface)->ControlRequest( controlInterface, 0, &controlRequest );
    if( kr2 != kIOReturnSuccess ) {
        kr2 = (*controlInterface)->USBInterfaceClose(controlInterface);
        //        NSLog( @"CameraControl Error: Control request failed: %08x", kr );
        //        return NO;
        successful2 = false;
    }
    
    if(successful1 == true || successful2 == true){
        kr = (*controlInterface)->USBInterfaceClose(controlInterface);
        
        return YES;
    }
    else{
        if (successful1 == false) {
            NSLog( @"CameraControl Error: Unable to open interface (%08x)\n", kr );
        }
        if (successful2 == false) {
            NSLog( @"CameraControl Error: Control request failed (%08x)\n", kr );
        }
        return NO;
    }
}


- (long) getInfoForControl:(uvc_control_info_t *)control{
    return [self getDataFor:UVC_GET_INFO withLength:1  fromSelector:control->selector at:control->unit];
    
}

- (BOOL)setData:(long)value withLength:(int)length forSelector:(int)selector at:(int)unitId {
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
    return ( success ? value : 0 );
}


// Get Range (min, max)
    - (uvc_range_t)getRangeForControl:(const uvc_control_info_t *)control {
    if (!control) {
        uvc_range_t defaultRange = {0, 0};
        return defaultRange;
    }

    // Check cache first using a unique key based on unit and selector
    NSString *key = [NSString stringWithFormat:@"%d_%d", control->unit, control->selector];
    NSValue *cachedRange = [rangeCache objectForKey:key];
    if (cachedRange) {
        uvc_range_t range;
        [cachedRange getValue:&range];
        if(bDebug_UVCCameraControl) NSLog(@"Found cached range for key %@: min=%d, max=%d", key, range.min, range.max);
        return range;
    }
        
        // Get the data length for this control
        int dataLength = control->size;
        
        // Get the minimum and maximum values
        long minValue = [self getDataFor:UVC_GET_MIN withLength:dataLength fromSelector:control->selector at:control->unit];
        long maxValue = [self getDataFor:UVC_GET_MAX withLength:dataLength fromSelector:control->selector at:control->unit];
        
    uvc_range_t range;
    
    // Handle different data sizes and signed/unsigned values
    switch (dataLength) {
        case 1: // 8-bit
            if (control->selector == UVCProcessingUnit_brightness) {
                range.min = (int8_t)minValue;
                range.max = (int8_t)maxValue;
            } else {
                range.min = (uint8_t)minValue;
                range.max = (uint8_t)maxValue;
            }
            break;
        
        case 2: // 16-bit
            if (control->selector == UVCProcessingUnit_brightness || control->selector == UVCProcessingUnit_hue) {
                range.min = (int16_t)minValue;
                range.max = (int16_t)maxValue;
            } else {
                range.min = (uint16_t)minValue;
                range.max = (uint16_t)maxValue;
            }
            break;
        
        case 4: // 32-bit
            range.min = (int32_t)minValue;
            range.max = (int32_t)maxValue;
            break;
        
        default:
            range.min = minValue;
            range.max = maxValue;
            break;
    }
    
    // Cache the range
    [rangeCache setObject:[NSValue valueWithBytes:&range objCType:@encode(uvc_range_t)] forKey:key];
    
    if (bDebug_UVCCameraControl) {
        NSLog(@"Range for control %@ (unit: %d, selector: %d): min=%d, max=%d", 
              control->name, control->unit, control->selector, range.min, range.max);
    }
        
        return range;
    }

// Used to de-/normalize values
- (float)mapValue:(float)value fromMin:(float)fromMin max:(float)fromMax toMin:(float)toMin max:(float)toMax {
    return toMin + (toMax - toMin) * ((value - fromMin) / (fromMax - fromMin));
}


// Get a normalized value
- (float)getValueForControl:(const uvc_control_info_t *)control {
    // TODO: Cache the range somewhere?
    uvc_range_t range = [self getRangeForControl:(uvc_control_info_t *)control];
    
    int intval = [self getDataFor:UVC_GET_CUR withLength:control->size fromSelector:control->selector at:control->unit];
    return [self mapValue:intval fromMin:range.min max:range.max toMin:0 max:1];
}


// Set a normalized value
- (BOOL)setValue:(float)value forControl:(const uvc_control_info_t *)control {
    // TODO: Cache the range somewhere?
    uvc_range_t range = [self getRangeForControl:(uvc_control_info_t *)control];
if(bDebug_UVCCameraControl){
    NSLog(@"setValue() %f with range %d %d",value, range.min, range.max);
   NSLog(@"control->name %@ unit %d with selector %d",control->name,control->unit, control->selector);
}
    int intval = [self mapValue:value fromMin:0 max:1 toMin:range.min max:range.max];
    return [self setData:intval withLength:control->size forSelector:control->selector at:control->unit];
}





// ================================================================

// Set/Get the actual values for the camera
//

// - (BOOL)setAutoExposure:(BOOL)enabled {
//     int intval = (enabled ? 0x01 : 0x00);
//     printf("setAutoExposure = %i \n", enabled);
//     return [self setData:intval 
//               withLength:controls.aeMode.size 
//              forSelector:controls.aeMode.selector 
//                       at:controls.aeMode.unit];
// }
// 
// - (BOOL)getAutoExposure {
//     int intval = [self getDataFor:UVC_GET_CUR 
//                        withLength:controls.aeMode.size 
//                      fromSelector:controls.aeMode.selector 
//                                at:controls.aeMode.unit];
//     
//     return (intval ? YES : NO);
// }



// - (BOOL)setExposure:(float)value {
//     printf("exposure value %f \n",value);
//     // value = 1 - value;
//     return [self setValue:value forControl:&uvc_controls.exposure];
// }
- (BOOL)setExposure:(float)value {
     printf("setExposure value %f \n",value);
    uvc_control_info_t control = controls.exposureTimeAbsolute;
    return [self setValue:value forControl:&control];
}

- (float)getExposure {
    uvc_control_info_t control = controls.exposureTimeAbsolute;
    return [self getValueForControl:&control];
}

// - (float)getExposure {
//     float value = [self getValueForControl:&uvc_controls.exposure];
// //    printf("getExposure = %f \n",value);
//     return 1 - value;
// }

// - (void) incrementExposure {
//     [self setData:0x01 
//        withLength:uvc_controls.exposure.size 
//       forSelector:uvc_controls.exposure.selector 
//                at:uvc_controls.exposure.unit];
// }

// - (void) decrementExposure {
//     [self setData:0xFF
//        withLength:uvc_controls.exposure.size 
//       forSelector:uvc_controls.exposure.selector 
//                at:uvc_controls.exposure.unit];
// }

- (void)incrementExposure {
    [self setIncrementalExposure:1.0];
}

- (void)decrementExposure {
    [self setIncrementalExposure:-1.0];
}

- (void) setDefaultExposure {
    uvc_control_info_t control = controls.exposureTimeAbsolute;
    uvc_range_t range = [self getRangeForControl:&control];
    float defaultValue = (range.max + range.min) / 2.0;
    [self setExposure:defaultValue];
}

- (UVCCameraControls *) getControls {
    return controls;
}



//-----focus
- (BOOL)setAutoFocus:(BOOL)enabled {
    int intval = (enabled ? 0x01 : 0x00);
    printf("setAutoFocus = %i \n", enabled);
    uvc_control_info_t control = controls.focusAuto;
    NSLog(@"setAutoFocus control - unit: %d, selector: %d, size: %d, name: %@",control.unit, control.selector, control.size, control.name);

    return [self setData:intval 
              withLength:controls.focusAuto.size 
             forSelector:controls.focusAuto.selector 
                      at:controls.focusAuto.unit];
}
- (BOOL)getAutoFocus {
    int intval = [self getDataFor:UVC_GET_CUR 
                       withLength:controls.focusAuto.size 
                     fromSelector:controls.focusAuto.selector 
                               at:controls.focusAuto.unit];
    
    return (intval ? YES : NO);
}
- (BOOL)setAbsoluteFocus:(float)value {
    uvc_control_info_t control = controls.focusAbsolute;
    if(bDebug_UVCCameraControl) NSLog(@"focusAbsolute control - unit: %d, selector: %d, size: %d, name: %@, value: %f",
          control.unit, control.selector, control.size, control.name, value);
    return [self setValue:value forControl:&control];
}
- (float)getAbsoluteFocus {
    uvc_control_info_t control = controls.focusAbsolute;
    return [self getValueForControl:&control];
}


//white balance
- (BOOL)setAutoWhiteBalance:(BOOL)enabled {
    int intval = (enabled ? 0x01 : 0x00);
   if(bDebug_UVCCameraControl)  printf("setAutoWhiteBalance = %i \n", enabled);
    return [self setData:intval 
              withLength:controls.autoWhiteBalance.size 
             forSelector:controls.autoWhiteBalance.selector 
                      at:controls.autoWhiteBalance.unit];
}

- (BOOL)getAutoWhiteBalance {
    int intval = [self getDataFor:UVC_GET_CUR 
                       withLength:controls.autoWhiteBalance.size 
                     fromSelector:controls.autoWhiteBalance.selector 
                               at:controls.autoWhiteBalance.unit];
    
    return (intval ? YES : NO);
}

- (BOOL)setWhiteBalance:(float)value {
    uvc_control_info_t control = controls.whiteBalance;
    return [self setValue:value forControl:&control];
}

- (float)getWhiteBalance {
    uvc_control_info_t control = controls.whiteBalance;
    return [self getValueForControl:&control];
}

//---rest---

- (BOOL)setGain:(float)value {
    uvc_control_info_t control = controls.gain;
    return [self setValue:value forControl:&control];
}

- (float)getGain {
    uvc_control_info_t control = controls.gain;
    return [self getValueForControl:&control];
}

- (BOOL)setBrightness:(float)value {
    uvc_control_info_t control = controls.brightness;
    if(bDebug_UVCCameraControl) NSLog(@"setBrightness control - unit: %d, selector: %d, size: %d, name: %@, value: %f",
          control.unit, control.selector, control.size, control.name, value);
    
    return [self setValue:value forControl:&control];
}

- (float)getBrightness {
    uvc_control_info_t control = controls.brightness;
    return [self getValueForControl:&control];
}

- (BOOL)setContrast:(float)value {
    uvc_control_info_t control = controls.contrast;
    return [self setValue:value forControl:&control];
}

- (float)getContrast {
    uvc_control_info_t control = controls.contrast;
    return [self getValueForControl:&control];
}

- (BOOL)setSaturation:(float)value {
    uvc_control_info_t control = controls.saturation;
    return [self setValue:value forControl:&control];
}

- (float)getSaturation {
    uvc_control_info_t control = controls.saturation;
    return [self getValueForControl:&control];
}

- (BOOL)setSharpness:(float)value {
    uvc_control_info_t control = controls.sharpness;
    return [self setValue:value forControl:&control];
}

- (float)getSharpness {
    uvc_control_info_t control = controls.sharpness;
    return [self getValueForControl:&control];
}

//white balance
- (BOOL)setLED:(BOOL)enabled {
    int intval = (enabled ? 0x01 : 0x00);
    printf("setLED = %i \n", enabled);
    return [self setData:intval 
              withLength:controls.led.size 
             forSelector:controls.led.selector 
                      at:controls.led.unit];
}

- (BOOL)getLED {
    int intval = [self getDataFor:UVC_GET_CUR 
                       withLength:controls.led.size 
                     fromSelector:controls.led.selector 
                               at:controls.led.unit];
    
    return (intval ? YES : NO);
}

- (BOOL)setBacklightCompensation:(bool)enabled {
    uvc_control_info_t control = controls.backlightCompensation;
    return [self setValue:enabled forControl:&control];
}
- (float)getBacklightCompensation {
    uvc_control_info_t control = controls.backlightCompensation;
    return [self getValueForControl:&control];
}
- (BOOL)setPowerLineFrequency:(float)value {
    uvc_control_info_t control = controls.powerLineFrequency;
    return [self setValue:value forControl:&control];
}

- (BOOL)getPowerLineFrequency {
    uvc_control_info_t control = controls.powerLineFrequency;
    float value = [self getValueForControl:&control];
    return (value > 0);
}

- (BOOL)setAutoHue:(BOOL)enabled {
    uvc_control_info_t control = controls.autoHue;
    return [self setValue:enabled forControl:&control];
}

- (BOOL)getAutoHue {
    uvc_control_info_t control = controls.autoHue;
    return [self getValueForControl:&control];
}

- (BOOL)setHue:(float)value {
    uvc_control_info_t control = controls.hue;
    return [self setValue:value forControl:&control];
}

- (float)getHue {
    uvc_control_info_t control = controls.hue;
    return [self getValueForControl:&control];
}

- (BOOL)setGamma:(float)value {
    uvc_control_info_t control = controls.gamma;
    return [self setValue:value forControl:&control];
}

- (float)getGamma {
    uvc_control_info_t temp = controls.exposureTimeAbsolute;
    return [self getValueForControl:&temp];
}

- (BOOL)setExposureTimeAbsolute:(float)value {
    uvc_control_info_t temp = controls.exposureTimeAbsolute;
    return [self setValue:value forControl:&temp];
}

- (float)getExposureTimeAbsolute {
    uvc_control_info_t temp = controls.exposureTimeAbsolute;
    return [self getValueForControl:&temp];
}

- (BOOL)setZoomAbsolute:(float)value {
   if(bDebug_UVCCameraControl)  printf("Setting zoomAbsolute to %f\n", value);
    
    // Get the valid range for zoomAbsolute
    uvc_control_info_t control = controls.zoomAbsolute;
    uvc_range_t range = [self getRangeForControl:&control];
   if(bDebug_UVCCameraControl) NSLog(@"zoomAbsolute range - Min: %d, Max: %d", range.min, range.max);
    
    // Map the 0-1 value to the actual range and clamp it
    long rawValue = (long)round(value * (range.max - range.min) + range.min);
    rawValue = MAX(range.min, MIN(rawValue, range.max));
    if(bDebug_UVCCameraControl) NSLog(@"Setting zoom - Raw value: %ld, Normalized value: %f", rawValue, value);
    
    return [self setData:rawValue 
              withLength:control.size
             forSelector:control.selector
                      at:control.unit];
}   

- (float)getZoomAbsolute {
    uvc_control_info_t control = controls.zoomAbsolute;
    long rawValue = [self getDataFor:UVC_GET_CUR 
                          withLength:control.size
                        fromSelector:control.selector
                                  at:control.unit];
    
    uvc_range_t range = [self getRangeForControl:&control];
    float normalizedValue = (float)(rawValue - range.min) / (range.max - range.min);
    if(bDebug_UVCCameraControl) NSLog(@"Getting zoomAbsolute - Raw value: %ld, Normalized value: %f", rawValue, normalizedValue);
    return normalizedValue;
}

- (BOOL)setPanTiltAbsolute:(float)panValue tiltValue:(float)tiltValue {
   if(bDebug_UVCCameraControl)  printf("Setting pan to %f, tilt to %f\n", panValue, tiltValue);
    
    // Get the actual ranges from the device
    uvc_control_info_t control = controls.pantiltAbsolute;
    int dataLength = control.size;
    long minValue = [self getDataFor:UVC_GET_MIN withLength:dataLength fromSelector:control.selector at:control.unit];
    long maxValue = [self getDataFor:UVC_GET_MAX withLength:dataLength fromSelector:control.selector at:control.unit];
    
    // Split the 64-bit value into pan and tilt ranges
    int32_t tiltMax = (int32_t)((maxValue >> 32) & 0xFFFFFFFF);
    int32_t panMax = (int32_t)(maxValue & 0xFFFFFFFF);
    
    // Convert from device units to degrees (divide by 3600)
    tiltMax = tiltMax / 3600;
    panMax = panMax / 3600;
    
    if(bDebug_UVCCameraControl) NSLog(@"Device ranges - Tilt: ±%d degrees, Pan: ±%d degrees", tiltMax, panMax);
    
    // Map the normalized values (0-1) to their respective ranges
    // Use the actual device ranges
    long panRawValue = (long)round(panValue * (panMax * 2) - panMax) * 3600;  // Convert back to device units
    long tiltRawValue = (long)round(tiltValue * (tiltMax * 2) - tiltMax) * 3600;  // Convert back to device units
    
    // Clamp the values to their respective ranges
    panRawValue = MAX(-panMax * 3600, MIN(panRawValue, panMax * 3600));
    tiltRawValue = MAX(-tiltMax * 3600, MIN(tiltRawValue, tiltMax * 3600));
    
    // Combine pan and tilt into a single value
    // UVC protocol typically expects tilt in the high 32 bits and pan in the low 32 bits
    long combinedValue = (tiltRawValue << 32) | (panRawValue & 0xFFFFFFFF);
    
    if(bDebug_UVCCameraControl) NSLog(@"Setting pan/tilt - Combined value: %ld (Pan: %ld, Tilt: %ld)", combinedValue, panRawValue, tiltRawValue);
    
    return [self setData:combinedValue 
              withLength:control.size
             forSelector:control.selector
                      at:control.unit];
}

- (float)getPanTiltAbsolute {
    uvc_control_info_t control = controls.pantiltAbsolute;
    long rawValue = [self getDataFor:UVC_GET_CUR 
                          withLength:control.size 
                        fromSelector:control.selector
                                  at:control.unit];
    
    uvc_range_t range = [self getRangeForControl:&control];
    float normalizedValue = (float)(rawValue - range.min) / (range.max - range.min);
    if(bDebug_UVCCameraControl) NSLog(@"Getting pan/tilt - Raw value: %ld, Normalized value: %f", rawValue, normalizedValue);
    return normalizedValue;
}

- (BOOL)setRollAbsolute:(float)value {
    uvc_control_info_t control = controls.rollAbsolute;
    return [self setValue:value forControl:&control];
}

- (float)getRollAbsolute {
    uvc_control_info_t control = controls.rollAbsolute;
    return [self getValueForControl:&control];
}

- (BOOL)setRollRelative:(float)value {
    uvc_control_info_t control = controls.rollRelative;
    return [self setValue:value forControl:&control];
}

- (float)getRollRelative {
    uvc_control_info_t control = controls.rollRelative;
    return [self getValueForControl:&control];
}

- (BOOL)setIncrementalExposure:(float)value {
    uvc_control_info_t control = controls.incremental_exposure;
    return [self setValue:value forControl:&control];
}

- (float)getIncrementalExposure {
    uvc_control_info_t control = controls.incremental_exposure;
    return [self getValueForControl:&control];
}

- (BOOL)setScanningMode:(float)value {
    uvc_control_info_t control = controls.scanningMode;
    return [self setValue:value forControl:&control];
}

- (float)getScanningMode {
    uvc_control_info_t control = controls.scanningMode;
    return [self getValueForControl:&control];
}

- (BOOL)setAeMode:(BOOL)enabled {
//        0x01: Manual Mode
//    0x02: Auto Mode
//    0x04: Shutter Priority
//    0x08: Aperture Priority
    int intval = (enabled ? 0x08 : 0x01); // "auto exposure modes" ar NOT boolean (on|off) as it seems
  if(bDebug_UVCCameraControl)   printf("setAeMode = %i \n", enabled);
    return [self setData:intval 
              withLength:controls.aeMode.size 
             forSelector:controls.aeMode.selector 
                      at:controls.aeMode.unit];
}


- (float)getAeMode {
    uvc_control_info_t control = controls.aeMode;
    return [self getValueForControl:&control];
}

- (BOOL)setAePriority:(float)value {
    uvc_control_info_t control = controls.aePriority;
    return [self setValue:value forControl:&control];
}

- (float)getAePriority {
    uvc_control_info_t control = controls.aePriority;
    return [self getValueForControl:&control];
}

- (BOOL)setExposureTimeRelative:(float)value {
    uvc_control_info_t control = controls.exposureTimeRelative;
    return [self setValue:value forControl:&control];
}

- (float)getExposureTimeRelative {
    uvc_control_info_t control = controls.exposureTimeRelative;
    return [self getValueForControl:&control];
}

- (BOOL)setFocusRelative:(float)value {
    uvc_control_info_t control = controls.focusRelative;
    return [self setValue:value forControl:&control];
}

- (float)getFocusRelative {
    uvc_control_info_t control = controls.focusRelative;
    return [self getValueForControl:&control];
}

- (BOOL)setIrisAbsolute:(float)value {
    uvc_control_info_t control = controls.irisAbsolute;
    return [self setValue:value forControl:&control];
}

- (float)getIrisAbsolute {
    uvc_control_info_t control = controls.irisAbsolute;
    return [self getValueForControl:&control];
}

- (BOOL)setIrisRelative:(float)value {
    uvc_control_info_t control = controls.irisRelative;
    return [self setValue:value forControl:&control];
}

- (float)getIrisRelative {
    uvc_control_info_t control = controls.irisRelative;
    return [self getValueForControl:&control];
}

- (BOOL)setPrivacy:(float)value {
    uvc_control_info_t control = controls.privacy;
    return [self setValue:value forControl:&control];
}

- (float)getPrivacy {
    uvc_control_info_t control = controls.privacy;
    return [self getValueForControl:&control];
}

- (BOOL)setFocusSimple:(float)value {
    uvc_control_info_t control = controls.focusSimple;
    return [self setValue:value forControl:&control];
}

- (float)getFocusSimple {
    uvc_control_info_t control = controls.focusSimple;
    return [self getValueForControl:&control];
}

- (BOOL)setDigitalWindow:(float)value {
    uvc_control_info_t control = controls.digitalWindow;
    return [self setValue:value forControl:&control];
}

- (float)getDigitalWindow {
    uvc_control_info_t control = controls.digitalWindow;
    return [self getValueForControl:&control];
}

- (BOOL)setRegionOfInterest:(float)value {
    uvc_control_info_t control = controls.regionOfInterest;
    return [self setValue:value forControl:&control];
}

- (float)getRegionOfInterest {
    uvc_control_info_t control = controls.regionOfInterest;
    return [self getValueForControl:&control];
}

// Add the implementation of extractProcessingUnitID method
- (int)extractProcessingUnitID:(IOUSBDeviceInterface **)deviceInterface {
    // Default to a common value if we can't extract it
    int defaultID = 0x02;
    
    if (!deviceInterface) {
        NSLog(@"No device interface provided");
        return defaultID;
    }
    
    // Get device descriptor
    IOUSBConfigurationDescriptorPtr configDesc;
    kern_return_t kr = (*deviceInterface)->GetConfigurationDescriptorPtr(deviceInterface, 0, &configDesc);
    if (kr != kIOReturnSuccess) {
        NSLog(@"Failed to get configuration descriptor");
        return defaultID;
    }
    
    // Get first interface
    const IOUSBInterfaceDescriptor *interfaceDesc = (const IOUSBInterfaceDescriptor *)((UInt8 *)configDesc + configDesc->bLength);
    
    // Walk through all descriptors
    const UInt8 *p = (const UInt8 *)interfaceDesc;
    const UInt8 *end = (const UInt8 *)configDesc + USBToHostWord(configDesc->wTotalLength);
    
    while (p < end) {
        UInt8 len = p[0];
        UInt8 type = p[1];
        
        // Check for Video Control Interface descriptor
        if (type == kUSBDescTypeCSInterface) {
            UInt8 subtype = p[2];
            if (subtype == UVC_DT_PROCESSING_UNIT) {
                int unitID = p[3];
                NSLog(@"Found processing unit with ID: 0x%02x", unitID);
                return unitID;
            }
        }
        
        if (len == 0) break;  // Protect against zero-length descriptors
        p += len;
    }
    
    NSLog(@"Processing unit not found in descriptor, using default ID: 0x%02x", defaultID);
    return defaultID;
}

// Add a method to update the control units with the processing unit ID
- (void)updateControlUnits {
    // Update all controls that use the processing unit ID
    [controls initializeWithProcessingUnitID:processingUnitID];
    NSLog(@"Updated control units with processing unit ID: 0x%02x", processingUnitID);
}

// Add implementation of getDeviceInterfaceWithLocationID
- (IOUSBDeviceInterface **)getDeviceInterfaceWithLocationID:(UInt32)locationID {
    CFMutableDictionaryRef matchingDict = IOServiceMatching(kIOUSBDeviceClassName);
    io_iterator_t serviceIterator;
    IOServiceGetMatchingServices(kIOMasterPortDefault, matchingDict, &serviceIterator);
    
    io_service_t camera;
    while ((camera = IOIteratorNext(serviceIterator))) {
        IOUSBDeviceInterface **deviceInterface = NULL;
        IOCFPlugInInterface **plugInInterface = NULL;
        SInt32 score;
        
        kern_return_t kr = IOCreatePlugInInterfaceForService(camera, kIOUSBDeviceUserClientTypeID, kIOCFPlugInInterfaceID, &plugInInterface, &score);
        if ((kIOReturnSuccess != kr) || !plugInInterface) {
            NSLog(@"CameraControl Error: IOCreatePlugInInterfaceForService returned 0x%08x.", kr);
            continue;
        }
        
        HRESULT res = (*plugInInterface)->QueryInterface(plugInInterface, CFUUIDGetUUIDBytes(kIOUSBDeviceInterfaceID), (LPVOID*)&deviceInterface);
        (*plugInInterface)->Release(plugInInterface);
        if (res || deviceInterface == NULL) {
            NSLog(@"CameraControl Error: QueryInterface returned %d.", (int)res);
            continue;
        }
        
        UInt32 currentLocationID = 0;
        (*deviceInterface)->GetLocationID(deviceInterface, &currentLocationID);
        
        if (currentLocationID == locationID) {
            NSLog(@"Found USB Device with location ID: %d", (int)currentLocationID);
            return deviceInterface;
        }
        
        (*deviceInterface)->Release(deviceInterface);
    }
    
    return NULL;
}

// Add implementation of getDeviceInterfaceWithVendorID
- (IOUSBDeviceInterface **)getDeviceInterfaceWithVendorID:(UInt16)vendorID productID:(UInt16)productID {
    CFMutableDictionaryRef matchingDict = IOServiceMatching(kIOUSBDeviceClassName);
    CFNumberRef numberRef;
    
    numberRef = CFNumberCreate(kCFAllocatorDefault, kCFNumberSInt32Type, &vendorID);
    CFDictionarySetValue(matchingDict, CFSTR(kUSBVendorID), numberRef);
    CFRelease(numberRef);
    
    numberRef = CFNumberCreate(kCFAllocatorDefault, kCFNumberSInt32Type, &productID);
    CFDictionarySetValue(matchingDict, CFSTR(kUSBProductID), numberRef);
    CFRelease(numberRef);
    
    io_service_t camera = IOServiceGetMatchingService(kIOMasterPortDefault, matchingDict);
    if (!camera) {
        return NULL;
    }
    
    IOUSBDeviceInterface **deviceInterface = NULL;
    IOCFPlugInInterface **plugInInterface = NULL;
    SInt32 score;
    
    kern_return_t kr = IOCreatePlugInInterfaceForService(camera, kIOUSBDeviceUserClientTypeID, kIOCFPlugInInterfaceID, &plugInInterface, &score);
    if ((kIOReturnSuccess != kr) || !plugInInterface) {
        NSLog(@"CameraControl Error: IOCreatePlugInInterfaceForService returned 0x%08x.", kr);
        return NULL;
    }
    
    HRESULT res = (*plugInInterface)->QueryInterface(plugInInterface, CFUUIDGetUUIDBytes(kIOUSBDeviceInterfaceID), (LPVOID*)&deviceInterface);
    (*plugInInterface)->Release(plugInInterface);
    if (res || deviceInterface == NULL) {
        NSLog(@"CameraControl Error: QueryInterface returned %d.", (int)res);
        return NULL;
    }
    
    return deviceInterface;
}

@end
