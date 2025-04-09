#ifdef __OFX_UVC_PROBER__
void useCameraByDeviceIndex(int i){
    int vendorID, productID;
    unsigned int locationID;
    tie(vendorID,productID,locationID) = ofxUVCProber::getVendorIDAndProductIDAndUniqueIDByDeviceIndex(i);
    
    ofLog()<<"index "<<i<<", vendorID "<<vendorID<<" productID "<<productID<<" locationID "<<locationID;
    useCameraByLocationID(vendorID,productID,0x00,locationID);
}

void useFirstCamera(){
    useCameraByDeviceIndex(0);
}

void useCameraByDeviceName(std::string s){
    int vendorID, productID;
    tie(vendorID,productID) = ofxUVCProber::getVendorIDAndProductIDByDeviceName(s);
    useCameraByInterfaceNum(vendorID,productID,0x00);
}

void useCameraByUID(std::string s){
    ofLog()<<"useCameraByUID "<<s;
    int vendorID, productID;
    unsigned int locationID;
    tie(vendorID,productID,locationID) = ofxUVCProber::getVendorIDAndProductIDAndUniqueIDByUID(s);

    ofLog()<<"useCameraByUID() vendorID "<<vendorID<<" productID "<<productID<<" locationID_int "<<locationID;
    useCameraByLocationID(vendorID,productID,0x00,locationID);
}

void setup(std::string name, std::string uniqueID) {
    ofLog()<<"Setting up UVC controller with unique ID: "<<uniqueID;
    useCameraByUID(uniqueID);
}

void setup(std::string name, int deviceIndex) {
    ofLog()<<"Setting up UVC controller with device index: "<<deviceIndex;
    useCameraByDeviceIndex(deviceIndex);
}

void getList(){
    ofLog()<<"ofxUVCUseProber getList()";
    ofxUVCProber::getList();
}
#endif
