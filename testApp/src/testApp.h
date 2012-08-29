#pragma once

#include "ofMain.h"
#include "ofxAutoControlPanel.h"
#include "ofxNetwork.h"


class testApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    void mouseMoved(int x, int y);
    void checkUpdate();
    void makeMesh();
    
    void setupMesh();
    void setupUI();
    void setupVar();
    void setupTCP();
    
    void generateMesh(vector<ofVec3f> * array);
    void animateMesh(vector<ofVec3f> * array);
    void generateTexture();
    
    void updateConditions();
    void updateTexture();
    void drawHUD();

    //Mesh points
    vector<ofVec3f> points;
    ofTrueTypeFont raleway;
    ofxAutoControlPanel panel;
    ofFbo buffer;
    
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
    bool weConnected;
    string msgTx, msgRx;
		float counter;
		int connectTime;
		int deltaTime;

    ofTexture graph;
    ofTexture graphTex;
    ofImage testImg2;
    ofMesh mesh;
    ofVec3f center;
    ofCamera camera;
    int currentDayUnwrapped;
    bool unwrap;
    bool alreadyUnwrapped;
    float wrapPoint;
    float unwrapPoint;
    
};

