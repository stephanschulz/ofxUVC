#ifdef __OFX_UVC_PROBER__
void useCameraByDeviceIndex(int i){
    int vendorID, productID;
    unsigned int locationID;
//    tie(vendorID,productID) = ofxUVCProber::getVendorIDAndProductIDByDeviceIndex(i);
    tie(vendorID,productID,locationID) = ofxUVCProber::getVendorIDAndProductIDAndUniqueIDByDeviceIndex(i);
    

    
    ofLog()<<"index "<<i<<", vendorID "<<vendorID<<" productID "<<productID<<" locationID "<<locationID;
//    useCamera(vendorID,productID,0x00);
    useCamera2(vendorID,productID,0x00,(int)locationID);
}
void useFirstCamera(){
    useCameraByDeviceIndex(0);
}
void useCameraByDeviceName(std::string s){
    int vendorID, productID;
    tie(vendorID,productID) = ofxUVCProber::getVendorIDAndProductIDByDeviceName(s);
    useCamera(vendorID,productID,0x00);
}
#endif
