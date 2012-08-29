#pragma once

#include "ofMain.h"
#include "ofxAutoControlPanel.h"
#include "ofxCv.h"

#include "face.h"
#include "canvas.h"

class testApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    void mouseMoved(int x, int y);
    void keyPressed( int key );
    
    vector<ofVec3f> points;
    ofTrueTypeFont raleway;
    
    ofxAutoControlPanel panel;
    ofImage thresh;
    ofImage bgThresh;
    ofxCv::RunningBackground background;

    int panelWidth;
    bool debug;
    
    float threshold;
    ofVideoGrabber cam;
    cv::Mat currentFrame;
    ofxCv::ContourFinder contourFinder;
    bool showLabels;
    
    //Face track
    ofImage gray, graySmall;
    cv::CascadeClassifier classifier;
    vector<cv::Rect> objects;
    float scaleFactor;
    
    // Face Object
    void saveFace();
        //    vector<ofImage> faces;
    vector<ofFace> faces;
    
    // Canvas object
private:
    ofCanvas * canvas1;
     
};