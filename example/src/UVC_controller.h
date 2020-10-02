//
//  UVC_controller.h
//  zoomP_simulation_3
//
//  Created by Stephan Schulz on 2015-10-20.
//
//

#ifndef zoomP_simulation_3_UVC_controller_h
#define zoomP_simulation_3_UVC_controller_h

#include "ofxUVCProber.h" // <- To use the prober, you need include this header BEFORE including "ofxUVC.h"!
#include "ofxUVC.h"

#include "ofParameterGroup.h"
#include "ofParameter.h"

class UVC_controller
{
    
    
public:
    
    ofxUVC uvcControl;
    
    vector<ofxUVCControl> controls;
    
    ofParameterGroup parameters;
    
    ofParameter<bool> getExposureValues;
    ofParameter<bool> getFocusValues;
    ofParameter<bool> getWhiteBalanceValues;
    
    ofParameter<bool> bChangeUsbCamControlls;
    ofParameter<bool> getCamValues;
    ofParameter<bool> aFocus,old_aFocus;
    ofParameter<bool> aExposure,old_aExposure;
    ofParameter<bool> aWhiteBalance, old_aWhiteBalance;
    
    ofParameter<float> focusValue, old_focusValue;
    ofParameter<float> exposureValue, old_exposureValue;
    ofParameter<float> whiteBalanceValue, old_whiteBalanceValue;
    ofParameter<float> gainValue, old_gainValue;
    ofParameter<float> sharpValue,old_sharpValue;
    ofParameter<float> saturationValue,old_saturationValue;
    ofParameter<float> contrastValue,old_contrastValue;
    ofParameter<float> brightnessValue,old_brightnessValue;
    
    ofParameter<float> powerLineFrequency,old_powerLineFrequency;
    ofParameter<float> backLightCompensation,old_backLightCompensation;
    //    ofParameter<bool> aHue, old_aHue;
    //    ofParameter<float> hueValue, old_hueValue;
    //    ofParameter<float> gammaValue, old_gammaValue;
    
    ofParameter<float> zoomValue, old_zoomValue;
    ofParameter<float> panValue, old_panValue;
    ofParameter<float> tiltValue, old_tiltValue;
    ofParameter<float> rollValue, old_rollValue;
    
    ofParameter<bool> printDefaults;
    
    bool bShowGUI;
    bool initDone;
    int initStage;
    float initTimer;
    int camID;
    
    //    int vendorId, productId;
    
    //    void setup(string _name, int _camID, unsigned int locationID, int _vendorId, int _productId){
    void setup(string _name, int _camID){
        
        camID = _camID;
        //        vendorId = _vendorId;
        //        productId = _productId;
        
        parameters.setName(_name);
        parameters.add(getCamValues.set("getCamValues",false));
        parameters.add(printDefaults.set("printDefaults",false));
        
        parameters.add(getFocusValues.set("getFocus",false));
        parameters.add(aFocus.set("aFocus",false));
        parameters.add(focusValue.set("focusValue",0.225,0,1.0));
        //   parameters.getFloatSlider("focusValue").setFineStep(0.01);
        
        parameters.add(getExposureValues.set("getExposure",false));
        parameters.add(aExposure.set("aExposure",false));
        parameters.add(exposureValue.set("exposureValue",0.935,0,1.0));
        //  parameters.getFloatSlider("exposureValue").setFineStep(0.01);
        parameters.add(aWhiteBalance.set("aWhiteBalance",false));
        parameters.add(whiteBalanceValue.set("whiteBalanceValue",0.845,0,1.0));
        //  parameters.getFloatSlider("whiteBalanceValue").setFineStep(0.01);
        //        parameters.add(aFocus.set("aFocus",false));
        
        parameters.add(getWhiteBalanceValues.set("getWhiteBalance",false));
        parameters.add(brightnessValue.set("brightnessValue",0.5,0,1.0));
        //  parameters.getFloatSlider("brightnessValue").setFineStep(0.01);
        parameters.add(contrastValue.set("contrastValue",0.12,0,1.0));
        //  parameters.getFloatSlider("contrastValue").setFineStep(0.01);
        parameters.add(saturationValue.set("saturationValue",0.245,0,1.0));
        // parameters.getFloatSlider("saturationValue").setFineStep(0.01);
        parameters.add(sharpValue.set("sharpValue",0.61,0,1.0));
        // parameters.getFloatSlider("sharpValue").setFineStep(0.01);
        parameters.add(gainValue.set("gainValue",0.06,0,1.0));
        //  parameters.getFloatSlider("gainValue").setFineStep(0.01);
        
        parameters.add(powerLineFrequency.set("powerFreq",0,0,1.0));
        parameters.add(backLightCompensation.set("backLight",0,0,1.0));
        //        parameters.add(aHue.set("autoHue",false));
        //        parameters.add(hueValue.set("hue",0,0,1.0));
        //        parameters.add(gammaValue.set("gamma",0,0,1.0));
        
        parameters.add(zoomValue.set("zoom",0,0,1.0));
        parameters.add(panValue.set("pan",0,0,1.0));
        parameters.add(tiltValue.set("tilt",0,0,1.0));
        parameters.add(rollValue.set("roll",0,0,1.0));
        
        
        getCamValues = false;
        
        //uvcControl.useCamera(vendorId, productId, interfaceNum);
        //http://www.binaryhexconverter.com/hex-to-decimal-converter
        //        int t[2];
        //        t[1] = 4194304; //0x00400000 / 2
        //        t[0] = 3145728; //0x00300000 / 1
        //        t[0] = 336592896;  //0x14100000 / 10 left usb port on mbp
        
        //        ofLogNotice("UVC_controller")<<"locationID "<<locationID;
        //        ofLogNotice("UVC_controller")<<"vendorID "<<vendorId;
        //        ofLogNotice("UVC_controller")<<"productID "<<productId;
        
        int interfaceNum;
        
        //    !!! change UVC_PROCESSING_UNIT_ID to 0x02 int UVCCameraControl.h to work with 292A-IPC-AR0330 !!!
        //    name: 292A-IPC-AR0330
        //    vendorId : 0x0c45
        //    productId: 0x6366
        //    interfaceNum: 0x00
        
        //    !!! change UVC_PROCESSING_UNIT_ID to 0x03 int UVCCameraControl.h to work with logitech c920 !!!
        //    logitech c920
        //    name:
        //    vendorId : 0x046d
        //    productId: 0x82d
        //    interfaceNum: 0x00
        
        //        vendorId = 0x046d;
        //        productId = 0x82d;
        
        //    !!! change UVC_PROCESSING_UNIT_ID to 0x03 int UVCCameraControl.h to work with logitech BRIO !!!
        //    logitech BRIO
        //    name:
        //    vendorId : 0x046d
        //    productId: 0x85e
        //    interfaceNum: 0x00
        
        //        vendorId = 0x046d;
        //        productId = 0x85e;
        
        //        productId = 0x82d; //logitech c920
        
        //
        //         productId = 0x6366; //logitech IPC
        
        //        vendorId = 0x85e;
        //        productId = 0x6366;
        
        
        
    }
    
    void init(){
        
        //        interfaceNum = 0x00;
        
        //        uvcControl.useCamera2(vendorId, productId, interfaceNum,(int) locationID);
        //  initWithLocationID
        uvcControl.useCameraByDeviceIndex(camID); // <- convenient!
        uvcControl.setAutoExposure(true);
        uvcControl.setAutoFocus(true);
        uvcControl.setAutoWhiteBalance(true);
        //        uvcControl.setAutoHue(true);
        controls = uvcControl.getCameraControls();
        
        initStage = 0;
        initDone = false;
        //         initDone = true;
        initTimer = 0;
        
        old_focusValue = focusValue;
        old_exposureValue = exposureValue;
        old_whiteBalanceValue = whiteBalanceValue;
        old_brightnessValue = brightnessValue;
        old_contrastValue = contrastValue;
        old_saturationValue = saturationValue;
        old_sharpValue = sharpValue;
        old_gainValue = gainValue;
        old_powerLineFrequency = powerLineFrequency;
        
        //        old_hueValue = hueValue;
        //        old_gammaValue = gammaValue;
        
        
        
        old_zoomValue = zoomValue;
        old_panValue = panValue;
        old_tiltValue = tiltValue;
        old_rollValue = rollValue;
        
        initTimer = ofGetElapsedTimef();
    }
    void update(){
        //         ofLog()<<"initDone == "<<initDone;
        //         ofLog()<<"bShowGUI == "<<bShowGUI;
        
        if(initDone == false){
            
            float waitDuration = 1; //0.5;
            
            
            //exposure
            if(ofGetElapsedTimef() > 5 && initStage == 0){
                cout<<ofGetTimestampString()<<endl;
                cout<<camID<<" start UVC setup"<<endl;
                initTimer = ofGetElapsedTimef();
                aExposure = !aExposure;
                old_aExposure = !aExposure;
                changeCamSettings();
                initStage++;
            }
            if(ofGetElapsedTimef() - initTimer > waitDuration && initStage == 1){
                initTimer = ofGetElapsedTimef();
                aExposure = !aExposure;
                old_aExposure = !aExposure;
                changeCamSettings();
                initStage++;
            }
            if(ofGetElapsedTimef() - initTimer > waitDuration  && initStage == 2){
                initTimer = ofGetElapsedTimef();
                old_exposureValue = -1;
                changeCamSettings();
                initStage++;
            }
            
            
            //white balance
            if(ofGetElapsedTimef() - initTimer > waitDuration && initStage == 3){
                initTimer = ofGetElapsedTimef();
                aWhiteBalance = !aWhiteBalance;
                old_aWhiteBalance = !aWhiteBalance;
                changeCamSettings();
                initStage++;
            }
            if(ofGetElapsedTimef() - initTimer > waitDuration && initStage == 4){
                initTimer = ofGetElapsedTimef();
                aWhiteBalance = !aWhiteBalance;
                old_aWhiteBalance = !aWhiteBalance;
                changeCamSettings();
                initStage++;
            }
            if(ofGetElapsedTimef() - initTimer > waitDuration  && initStage == 5){
                initTimer = ofGetElapsedTimef();
                old_whiteBalanceValue = -1;
                changeCamSettings();
                initStage++;
            }
            
            //all others
            if(ofGetElapsedTimef() - initTimer > waitDuration  && initStage == 6){
                initTimer = ofGetElapsedTimef();
                old_brightnessValue = -1;
                changeCamSettings();
                initStage++;
            }
            if(ofGetElapsedTimef() - initTimer > waitDuration  && initStage == 7){
                initTimer = ofGetElapsedTimef();
                old_contrastValue = -1;
                changeCamSettings();
                initStage++;
            }
            if(ofGetElapsedTimef() - initTimer > waitDuration  && initStage == 8){
                initTimer = ofGetElapsedTimef();
                old_saturationValue = -1;
                changeCamSettings();
                initStage++;
            }
            if(ofGetElapsedTimef() - initTimer > waitDuration  && initStage == 9){
                initTimer = ofGetElapsedTimef();
                old_sharpValue = -1;
                changeCamSettings();
                initStage++;
            }
            if(ofGetElapsedTimef() - initTimer > waitDuration  && initStage == 10){
                initTimer = ofGetElapsedTimef();
                old_gainValue = -1;
                changeCamSettings();
                initStage++;
            }
            
            //            if(ofGetElapsedTimef() - initTimer > waitDuration  && initStage == 11){
            //                initTimer = ofGetElapsedTimef();
            //                aExposure = !aExposure;
            //                old_aExposure = !aExposure;
            //                changeCamSettings();
            //                initStage++;
            //            }
            //            if(ofGetElapsedTimef() - initTimer > waitDuration && initStage == 12){
            //                initTimer = ofGetElapsedTimef();
            //                aExposure = !aExposure;
            //                old_aExposure = !aExposure;
            //                changeCamSettings();
            //                initStage++;
            //            }
            if(ofGetElapsedTimef() - initTimer > waitDuration  && initStage == 11){
                initTimer = ofGetElapsedTimef();
                old_exposureValue = -1;
                changeCamSettings();
                initStage++;
            }
            
            
            //done
            if(ofGetElapsedTimef() - initTimer > waitDuration  && initStage == 12){
                initTimer = ofGetElapsedTimef();
                initDone = true;
                initStage++;
                cout<<ofGetTimestampString()<<endl;
                cout<<camID<<" end UVC setup"<<endl;
            }
            
        } else {
            if(bShowGUI == true){
                changeCamSettings();
            }
        }
        
        if(getCamValues == true){
            
            aFocus = true;
            aExposure = true;
            aWhiteBalance = true;
            
            focusValue = uvcControl.getAutoFocus(); // [cameraControl getAutoFocus] ;
            exposureValue = uvcControl.getExposure(); //[cameraControl getExposure] ;
            whiteBalanceValue = uvcControl.getWhiteBalance(); //[cameraControl getWhiteBalance] ;
            gainValue = uvcControl.getGain(); //[cameraControl getGain] ;
            sharpValue = uvcControl.getSharpness(); //[cameraControl getSharpness] ;
            brightnessValue = uvcControl.getBrightness(); //[cameraControl getBrightness] ;
            contrastValue = uvcControl.getContrast(); //[cameraControl getContrast] ;
            saturationValue = uvcControl.getSaturation(); //[cameraControl getSaturation] ;
            
            cout<<"getAutoFocus "<<focusValue<<endl;//[cameraControl getAutoFocus]<<endl;
            cout<<"getExposure "<<exposureValue<<endl;//cameraControl getExposure]<<endl;
            cout<<"getWhiteBalance "<<whiteBalanceValue<<endl;//[cameraControl getWhiteBalance]<<endl;
            cout<<"getGain "<<gainValue<<endl;//[cameraControl getGain]<<endl;
            cout<<"getSharpness "<<sharpValue<<endl;//[cameraControl getSharpness]<<endl;
            cout<<"getBrightness "<<brightnessValue<<endl;//[cameraControl getBrightness]<<endl;
            cout<<"getContrast "<<contrastValue<<endl;//[cameraControl getContrast]<<endl;
            cout<<"getSaturation "<<saturationValue<<endl;//[cameraControl getSaturation]<<endl;
        }
        
        
    }
    
    void changeCamSettings(){
        if(bShowGUI == false){
            ofLogNotice("UVC_controller")<<camID<<" changeCamSettings";
        }
        //used to be in mouseDragged
        if(gainValue != old_gainValue){
            //[cameraControl setGain:gainValue];
            uvcControl.setGain(gainValue);
            old_gainValue = gainValue;
        }
        if(sharpValue != old_sharpValue){
            //[cameraControl setSharpness:sharpValue];
            uvcControl.setSharpness(sharpValue);
            old_sharpValue = sharpValue;
        }
        if(brightnessValue != old_brightnessValue){
            //[cameraControl setBrightness:brightnessValue];
            uvcControl.setBrightness(brightnessValue);
            old_brightnessValue = brightnessValue;
        }
        if(contrastValue != old_contrastValue){
            //[cameraControl setContrast:contrastValue];
            uvcControl.setContrast(contrastValue);
            old_contrastValue = contrastValue;
        }
        if(saturationValue != old_saturationValue){
            //[cameraControl setSaturation:saturationValue];
            uvcControl.setSaturation(saturationValue);
            old_saturationValue = saturationValue;
        }
        
        if(aFocus == false && focusValue != old_focusValue){
            //[cameraControl setAbsoluteFocus:focusValue];
            uvcControl.setAbsoluteFocus(focusValue);
            old_focusValue = focusValue;
        }
        if(aExposure == false && exposureValue != old_exposureValue){
            //[cameraControl setExposure:ofMap(exposureValue, 0, 10, 1, 100000)];
            //[cameraControl setExposure:exposureValue];
            uvcControl.setExposure(exposureValue);
            old_exposureValue = exposureValue;
        }
        if(aWhiteBalance == false && whiteBalanceValue != old_whiteBalanceValue){
            //[cameraControl setWhiteBalance:whiteBalanceValue];
            uvcControl.setWhiteBalance(whiteBalanceValue);
            old_whiteBalanceValue = whiteBalanceValue;
        }
        
        
        //used to be in mouseRelease
        if(aFocus != old_aFocus){
            if(aFocus)  uvcControl.setAutoFocus(true); //[cameraControl setAutoFocus:YES];
            else  uvcControl.setAutoFocus(false); //[cameraControl setAutoFocus:NO];
            old_aFocus = aFocus;
        }
        if(aExposure != old_aExposure){
            if(aExposure)  uvcControl.setAutoExposure(true); //[cameraControl setAutoExposure:YES];
            else  uvcControl.setAutoExposure(false); //[cameraControl setAutoExposure:NO];
            old_aExposure = aExposure;
        }
        if(aWhiteBalance != old_aWhiteBalance){
            if(aWhiteBalance)  uvcControl.setAutoWhiteBalance(true); //[cameraControl setAutoWhiteBalance:YES];
            else  uvcControl.setAutoWhiteBalance(false); //[cameraControl setAutoWhiteBalance:NO];
            old_aWhiteBalance = aWhiteBalance;
        }
        
    }
};

#endif




