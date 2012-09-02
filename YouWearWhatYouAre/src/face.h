#ifndef _face_h
#define _face_h

#include "ofMain.h"

class ofFace {

public:
    
    ofFace(ofImage & _face, ofVec3f _faceLocation, ofVec3f _circleLoc);
    ~ofFace();
    
    void update();
    void draw(int x, int y);
    void draw();
    void reset();
    void remove();
    
    int x;
    int y;
    ofVec3f loc;
    float tween; // Multiplied by radius to control anim
    float tweenStep; // Stepping the tween value
    
    ofPoint center;
    int radius;
    bool bActive;
    long age;
    int resolution;
    
    float distance(ofVec3f point);
    
    ofImage theFace;
    ofVec3f cvFaceLocation();
    ofVec3f faceLocation;
    
    // This is for tracking still active faces
    float inactiveTimer;
    float inactiveTimerStep;

    // change b/w frames
    // Gets rounded down to pixel
    float changeThresh;
    
    void updateFace(ofImage _face, ofVec3f _newLocation);
    bool isWithinRange(ofVec3f _difference);
    bool isActive();
private:
    vector<ofPoint> circle;
    vector<ofPoint> circleTex;
    void genCircle();
    
};


#endif
