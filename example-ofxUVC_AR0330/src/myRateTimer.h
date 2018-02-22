//
//  myRateTimer.h
//  faceBlender
//
//  Created by Stephan Schulz on 2017-08-16.
//
//

#ifndef myRateTimer_h
#define myRateTimer_h

class myRateTimer {
protected:
    float lastTick, averagePeriod, smoothing;
    bool secondTick;
public:
    myRateTimer() :
    smoothing(.9) {
        reset();
    }
    void reset() {
        lastTick = 0, averagePeriod = 0, secondTick = false;
    }
    void setSmoothing(float smoothing) {
        this->smoothing = smoothing;
    }
    float getFramerate() {
        return averagePeriod == 0 ? 0 : 1 / averagePeriod;
    }
    void tick() {
        float curTick = ofGetElapsedTimef();
        if(lastTick == 0) {
            secondTick = true;
        } else {
            float curDiff = curTick - lastTick;;
            if(secondTick) {
                averagePeriod = curDiff;
                secondTick = false;
            } else {
                averagePeriod = ofLerp(curDiff, averagePeriod, smoothing);
            }
        }
        lastTick = curTick;
    }
};


#endif /* myRateTimer_h */
