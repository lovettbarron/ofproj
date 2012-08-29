#pragma once

#include "ofMain.h"
#include "ofxAutoControlPanel.h"
#include "ofxCv.h"
#include "ofxKinect.h"
#include "ofxKinectRecorder.h"
#include "ofxKinectPlayer.h"

class testApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    void mouseMoved(int x, int y);
    void keyPressed( int key );
    void checkUpdate();
    void debugDraw();
    void exit();

    ofxKinect kPlayer;
    ofxKinectRecorder kRecord;
    
    bool bPlay;
    bool bRecord;
    string filePath;
    
    ofxKinect kinect;
    
    //Mesh points
    vector<ofVec3f> points;
    ofTrueTypeFont type;
    
    ofxAutoControlPanel panel;
    ofImage thresh;
    ofImage bgThresh;
    ofxCv::RunningBackground background;
    
    float threshold;
    ofxCv::ContourFinder contourFinder;
    bool showLabels;
    int panelWidth;
    
    // Setup methods
    bool setupKinect();
    bool setupPanel();
    bool setupType();
    void uiConditions();
    
    ofVec2f kinectPosition;
    void getKinectPosition();
};

