#pragma once

#include "ofMain.h"
#include "ofxAutoControlPanel.h"
#include "ofxCv.h"
#include "ofxKinect.h"
#include "ofxNetwork.h"

class testApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    void mouseMoved(int x, int y);
    void keyPressed( int key );
    void checkUpdate();
    void listTracked();
    void debugDraw();
    
    ofxKinect kinect;
    
        //Mesh points
    vector<ofVec3f> points;
    ofTrueTypeFont raleway;
    
    ofxAutoControlPanel panel;
    ofImage thresh;
    ofImage bgThresh;
    ofxCv::RunningBackground background;
        // Network business
    /*
     JSON format
     {
     time: JSON date format w/ hours
     , msg: String
     , duration: Integer
     }
     */
    ofxTCPClient tcpClient;
    bool connected;
    string msgTx, msgRx;
    bool weConnected;
		float counter;
		int connectTime;
		int deltaTime;
    int panelWidth;
    
        //Demo
    
    float threshold;
    ofVideoGrabber cam;
    ofxCv::ContourFinder contourFinder;
    bool showLabels;
};

