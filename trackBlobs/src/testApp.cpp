#include "testApp.h"

using namespace cv;
using namespace ofxCv;

void testApp::setup() {
    ofSetLogLevel(OF_LOG_VERBOSE);
    ofSetFrameRate(60);
    ofSetVerticalSync(true);

    
    //Setup panel
    if(setupPanel())
        ofLog() << "Panel failed";
    if(setupKinect())
        ofLog() << "Kinect borked";
    if(setupType()) 
        ofLog() << "Type messed up";
    ofBackground(0);
    
    thresh.allocate(kinect.width, kinect.height, OF_IMAGE_GRAYSCALE);
    bgThresh.allocate(640,480,OF_IMAGE_GRAYSCALE);

}

void testApp::update() {
    uiConditions();
    if(!bPlay) {
        kinect.update();
        if(kinect.isFrameNew()) {
            background.update(kinect, thresh);
            thresh.update();
            if(bRecord) {
                if(kRecord.isOpened())
                    kRecord.newFrame(kinect.getPixels(), kinect.getRawDepthPixels());   
            }
        }
    } else {
        
    }
}

void testApp::draw() {
    ofBackground(0);
    ofPushMatrix();
        ofTranslate(panelWidth, 0);
        kinect.drawDepth(0,0,kinect.width, kinect.height);
        thresh.draw(kinect.width, 0, 2, 256,192);
        bgThresh.draw(kinect.width, 192, 2, 256,192);
        ofPushMatrix();
            ofTranslate(kinect.width,192);
            ofScale(.4,.4);
            
        ofPopMatrix();
    ofPopMatrix(); // For panel
}

void testApp::keyPressed(int key) {
    if(key == ' ') {
        showLabels = !showLabels;
    }
}

void testApp::mouseMoved(int x, int y ){

}

bool testApp::setupKinect() {
    kinect.setRegistration(true);    
    kinect.init();
        //    kinect.setVerbose(true);
    kinect.open();
    kinect.enableDepthNearValueWhite(true);
    return 0;
}

bool testApp::setupType() {
    ofTrueTypeFont::setGlobalDpi(72);
    type.loadFont("Raleway-Thin.ttf", 32, true, true);
    type.setLineHeight(18.0f);
    type.setLetterSpacing(1.037);
    filePath = "kinectDummyData.so";
    return 0;
}

bool testApp::setupPanel() {
    int panelWidth = 200;
    panel.setup(panelWidth, 800);
    panel.addPanel("Tracking Bits");
    panel.addLabel("Image Processing");
    panel.addSlider("maxThreshold", 15, 0, 255, true);
    panel.addSlider("minAreaRadius", 7, 0, 640, true);
    panel.addSlider("maxAreaRadius", 100, 0, 640, true);
    panel.addLabel("Background Subtraction");
    panel.addSlider("learningTime",900,0,2000,true);
    panel.addSlider("backgroundThresh",10,0,50,true);
    panel.addToggle("resetBg", false);
    panel.addToggle("initKinect", false);
    panel.addToggle("playRecording", false);
    return 0;
}

void testApp::debugDraw() {    
}

void testApp::uiConditions() {
    if(panel.getValueB("initKinect")) {
        kinect.close();
        setupKinect();
        panel.setValueB("initKinect",false);
    }
    if(panel.getValueB("resetBg")) {
        background.reset();
        panel.setValueB("resetBg",false);
    }
    if(panel.getValueB("playRecording") && !bPlay && !bRecord) {
        if(ofToBool(filePath)) {
            bPlay = true;
            try {
                    // kPlayer.setup(filePath,true);
            } catch(char e) { ofLog() << "Error playing: " << e << endl; }
        } else { ofLog() << "No file there"; }
    } else if (!panel.getValueB("playRecording")) {
        bPlay = false;
        kPlayer.close();
    }
    if(panel.getValueB("makeRecording") && !bPlay && !bRecord) {
        if(ofToBool(filePath)) {
            bRecord = true;
            try {
                kRecord.init(filePath);
            } catch(char e) { ofLog() << "Error recording: " << e << endl; }
        } else { ofLog() << "No file there"; }
    } else if (!panel.getValueB("playRecording")) {
        bRecord = false;
        kRecord.close();
    }
}

void testApp::getKinectPosition() {
    kinectPosition[0] = kinect.getAccelRoll();    
    kinectPosition[1] = kinect.getAccelPitch();
}

//--------------------------------------------------------------
void testApp::exit() {
    kinect.setCameraTiltAngle(0); // zero the tilt on exit
    kinect.close();
    
#ifdef USE_TWO_KINECTS
    kinect2.close();
#endif
}