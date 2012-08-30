#ifndef _canvas_h
#define _canvas_h

#include "ofMain.h"
#include "face.h"

class ofCanvas {
    
public:
    
    ofCanvas();
    ~ofCanvas();
    
    void update();
    void draw(int _x, int _y);
    void reset();
    void configure();
    void add(ofFace * face);

    ofFace & get(int index);
    int width;
    int height;
    int cx;
    int cy;
    int size();
    bool bActive;
    long age;
    float padding;
    int newFaceTimer;
    int newFaceTimerThresh;
    vector<ofFace> canvas;
    
    void compareWithStillActive( vector<ofFace> * _faces);
    
private:
    void pack();
    float distance(ofFace & face1, ofFace & face2);
    float distance(ofPoint pt1, ofPoint pt2);
    bool compare(ofFace* face1, ofFace* face2);
};
#endif
