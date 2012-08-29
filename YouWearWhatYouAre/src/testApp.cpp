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
    panel.addSlider("faceScale", .2, 0.05, 1.0, false);
    panel.addSlider("minAreaRadius", 7, 0, 640, true);
    panel.addSlider("maxAreaRadius", 100, 0, 640, true);
    panel.addLabel("Background Subtraction");
    panel.addSlider("learningTime",900,0,2000,true);
    panel.addSlider("backgroundThresh",10,0,50,true);
    panel.addToggle("resetFaces", false);
    panel.addToggle("debug",false);
    
    ofBackground(0);
    
    cam.initGrabber(640, 480);
    thresh.allocate(640, 480, OF_IMAGE_GRAYSCALE);
    bgThresh.allocate(640,480,OF_IMAGE_GRAYSCALE);
    background.setThresholdValue(panel.getValueI("backgroundThresh"));
    background.setLearningTime(panel.getValueI("learningTime"));

    
    scaleFactor = panel.getValueF("faceScale");
    classifier.load(ofToDataPath("haarcascade_frontalface_alt2.xml"));
    graySmall.allocate(cam.getWidth() * scaleFactor, cam.getHeight() * scaleFactor, OF_IMAGE_GRAYSCALE);
    debug = false;
    canvas1 = new ofCanvas();
}
void testApp::update() {
    background.setLearningTime(panel.getValueI("learningTime"));
    background.setThresholdValue(panel.getValueI("backgroundThresh"));
    if(scaleFactor != panel.getValueF("faceScale")) {
            graySmall.allocate(cam.getWidth() * panel.getValueF("faceScale"), cam.getHeight() * panel.getValueF("faceScale"), OF_IMAGE_GRAYSCALE);
    }
    scaleFactor = panel.getValueF("faceScale");
    if(panel.getValueB("debug")) {
        debug = true;
    } else {
        debug = false;
    }
    cam.update();
    if(panel.getValueB("resetFaces")) {
        faces.clear();
        panel.setValueB("resetFaces",false);
    }
    if(cam.isFrameNew()) {
            //convertColor(cam, thresh, CV_RGB2GRAY);
        background.update(cam, thresh);
        thresh.update();


        
        //Face Tracking stuff
        convertColor(cam, gray, CV_RGB2GRAY);
        resize(gray, graySmall);
        Mat graySmallMat = toCv(graySmall);
        if(ofGetMousePressed()) {
            equalizeHist(graySmallMat, graySmallMat);
        }
        graySmall.update();
        
        classifier.detectMultiScale(graySmallMat, objects, 1.06, 1,
                                    //CascadeClassifier::DO_CANNY_PRUNING |
                                    //CascadeClassifier::FIND_BIGGEST_OBJECT |
                                    //CascadeClassifier::DO_ROUGH_SEARCH |
                                    0);

        canvas1->update();   
    }
}

void testApp::draw() {
    
        //ofSetBackgroundAuto(true);
    ofBackground(100);
    ofPushMatrix();
        ofTranslate(panelWidth, 0);
            ofSetColor(255);
        if(debug) {
            cam.draw(0, 0);
            contourFinder.draw();
            
            graySmall.draw(cam.width, 0, 2, 256,192);
            thresh.draw(cam.width, 192, 2, 256,192);
            ofNoFill();
                //ofScale(1 / scaleFactor, 1 / scaleFactor);
            for(int i = 0; i < objects.size(); i++) {
                ofLog() << "Drawing face #" << ofToString(i);
                ofRect(toOf(objects[i]));
            }
        }
    
        ofPushMatrix();
            if(debug) {
                ofScale(.1,.1);
                int offset = 0;
                for(int i=0; i<faces.size(); i++) {
                    faces[i].draw(offset,0);
                    offset += faces[i].radius;
                }
            }
            //ofScale(.4,.4);
        ofPopMatrix();
        ofNoFill();
        canvas1->draw(0,0);
    ofPopMatrix(); // For panel
}

void testApp::keyPressed(int key) {
    if(key == ' ') {
        saveFace();
    }
}

void testApp::mouseMoved(int x, int y ){
    
}

void testApp::saveFace() {
    for(int i=0; i < objects.size(); i++) {   
        
        ofImage newFace;
        newFace.allocate((int)objects[i].width * (1 / scaleFactor), (int)objects[i].height * (1 / scaleFactor), OF_IMAGE_COLOR);
        int x = objects[i].x * (1 / scaleFactor);
        int y = objects[i].y * (1 / scaleFactor);
        int w = objects[i].width * (1 / scaleFactor);
        int h = objects[i].height * (1 / scaleFactor);
        ofLog() << "x" << ofToString(x) << " y" << ofToString(y) << " w" << ofToString(w) << " h" << ofToString(h);
        
        ofImage pixels;
        pixels.setFromPixels(cam.getPixels(), cam.width, cam.height, OF_IMAGE_COLOR);
        newFace.cropFrom(pixels, x, y, w, h );
        newFace.reloadTexture();
        ofFace theFace = ofFace(newFace);
        faces.push_back( ofFace(newFace) );
        canvas1->add( &theFace );
    }
}


