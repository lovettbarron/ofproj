#ifndef _face_h
#define _face_h

#include "ofMain.h"

class ofFace {

public:
    
    ofFace(ofImage & _face);
    ~ofFace();
    
    void update();
    void draw(int x, int y);
    void draw();
    void reset();
    
    int x;
    int y;
    float tween; // Multiplied by radius to control anim
    float tweenStep; // Stepping the tween value
    ofPoint center;
    int radius;
    bool bActive;
    long age;
    int resolution;
    
    float distance(ofVec3f point);
    
    ofImage theFace;
    
private:
    vector<ofPoint> circle;
    vector<ofPoint> circleTex;
    void genCircle();
    
};


#endif
