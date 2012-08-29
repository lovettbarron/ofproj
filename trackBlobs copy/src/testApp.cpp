#include "testApp.h"

using namespace cv;
using namespace ofxCv;

void testApp::setup() {
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofTrueTypeFont::setGlobalDpi(72);
    raleway.loadFont("Raleway-Thin.ttf", 32, true, true);
    raleway.setLineHeight(18.0f);
    raleway.setLetterSpacing(1.037);
    
    //Setup panel
    panelWidth = 200;
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
    
    ofSetVerticalSync(true);
    ofBackground(0);
    
    cam.initGrabber(640, 480);
    thresh.allocate(640, 480, OF_IMAGE_GRAYSCALE);
    bgThresh.allocate(640,480,OF_IMAGE_GRAYSCALE);
    background.setThresholdValue(panel.getValueI("backgroundThresh"));
    background.setLearningTime(panel.getValueI("learningTime"));
    contourFinder.setMinAreaRadius(panel.getValueI("minAreaRadius"));
    contourFinder.setMaxAreaRadius(panel.getValueI("maxAreaRadius"));
    contourFinder.setThreshold(panel.getValueI("maxThreshold"));
        // wait for half a frame before forgetting something
    contourFinder.getTracker().setPersistence(15);
        // an object can move up to 32 pixels per frame
    contourFinder.getTracker().setMaximumDistance(32);
    

}
void testApp::update() {
    contourFinder.setMinAreaRadius(panel.getValueI("minAreaRadius"));
    contourFinder.setMaxAreaRadius(panel.getValueI("maxAreaRadius"));
    contourFinder.setThreshold(panel.getValueI("maxThreshold"));
    background.setLearningTime(panel.getValueI("learningTime"));
    background.setThresholdValue(panel.getValueI("backgroundThresh"));
    
    cam.update();
    if(panel.getValueB("resetBg")) {
        background.reset();
        panel.setValueB("resetBg",false);
    }
    if(cam.isFrameNew()) {
            //convertColor(cam, thresh, CV_RGB2GRAY);
        
        
        
        background.update(cam, thresh);
            //ofxCv::threshold(thresh, panel.getValueI("maxThreshold"));
        thresh.update();
            //        bgThresh.update();
        blur(cam, 10);
        contourFinder.findContours(cam);
    }
}

void testApp::draw() {
    
    ofSetBackgroundAuto(showLabels);
    RectTracker& tracker = contourFinder.getTracker();
    
    ofPushMatrix();
    ofTranslate(panelWidth, 0);
    if(showLabels) {
        ofSetColor(255);
        cam.draw(0, 0);
        contourFinder.draw();
        for(int i = 0; i < contourFinder.size(); i++) {
            ofPoint center = toOf(contourFinder.getCenter(i));
            ofPushMatrix();
            ofTranslate(center.x, center.y);
            int label = contourFinder.getLabel(i);
            string msg = ofToString(label) + ":" + ofToString(tracker.getAge(label));
            ofDrawBitmapString(msg, 0, 0);
            ofVec2f velocity = toOf(contourFinder.getVelocity(i));
            ofScale(5, 5);
            ofLine(0, 0, velocity.x, velocity.y);
            ofPopMatrix();
        }
    } else {
        for(int i = 0; i < contourFinder.size(); i++) {
            unsigned int label = contourFinder.getLabel(i);
                // only draw a line if this is not a new label
            if(tracker.existsPrevious(label)) {
                    // use the label to pick a random color
                ofSeedRandom(label << 24);
                ofSetColor(ofColor::fromHsb(ofRandom(255), 255, 255));
                    // get the tracked object (cv::Rect) at current and previous position
                cv::Rect& previous = tracker.getPrevious(label);
                cv::Rect& current = tracker.getCurrent(label);
                    // get the centers of the rectangles
                ofVec2f previousPosition(previous.x + previous.width / 2, previous.y + previous.height / 2);
                ofVec2f currentPosition(current.x + current.width / 2, current.y + current.height / 2);
                ofLine(previousPosition, currentPosition);
            }
        }
    }
    
        // this chunk of code visualizes the creation and destruction of labels
    vector<unsigned int>& currentLabels = tracker.getCurrentLabels();
    vector<unsigned int>& previousLabels = tracker.getPreviousLabels();
    vector<unsigned int>& newLabels = tracker.getNewLabels();
    vector<unsigned int>& deadLabels = tracker.getDeadLabels();
    ofSetColor(cyanPrint);
    for(int i = 0; i < currentLabels.size(); i++) {
        int j = currentLabels[i];
        ofLine(j, 0, j, 4);
    }
    ofSetColor(magentaPrint);
    for(int i = 0; i < previousLabels.size(); i++) {
        int j = previousLabels[i];
        ofLine(j, 4, j, 8);
    }
    ofSetColor(yellowPrint);
    for(int i = 0; i < newLabels.size(); i++) {
        int j = newLabels[i];
        ofLine(j, 8, j, 12);
    }
    ofSetColor(ofColor::white);
    for(int i = 0; i < deadLabels.size(); i++) {
        int j = deadLabels[i];
        ofLine(j, 12, j, 16);
    }
    thresh.draw(cam.width, 0, 2, 256,192);
    bgThresh.draw(cam.width, 192, 2, 256,192);
        ofPushMatrix();
        ofTranslate(cam.width,192);
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


void listTracked() {
    

}

void debugDraw() {    
}