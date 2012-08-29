//
//#pragma once
//
//#include "ofMain.h"
//#include "ofxAutoControlPanel.h"
//#include "ofxCv.h"
//
//class testApp : public ofBaseApp{
//public:
//    void setup();
//    void update();
//    void draw();
//    void mouseMoved(int x, int y);
//    void keyPressed( int key );
//    void checkUpdate();
//    void debugDraw();
//    void exit();
//    
//    ofTrueTypeFont type;
//    
//    ofImage gray, graySmall, frame;
//    
//    cv::CascadeClassifier classifier;
//    vector<cv::Rect> objects;
//    float scaleFactor;
//    
//    
//    ofxAutoControlPanel panel;
//        //ofxCv::RunningBackground background;
//    int panelWidth;
//    
//        // Setup methods
//    bool setupCamera();
//    bool setupPanel();
//    bool setupType();
//    void uiConditions();
//    
//        // update methods
//    bool runFaceLoop();
//    
//    ofVideoGrabber cam;
//};
//
//
//
//#include "testApp.h"
//
//using namespace cv;
//using namespace ofxCv;
//
//void testApp::setup() {
//    ofSetLogLevel(OF_LOG_VERBOSE);
//    ofSetFrameRate(60);
//    ofSetVerticalSync(true);
//    ofBackground(0);
//    
//        //Setup panel
//    if(setupCamera()) ofLog() << "face borked";
//    if(setupType()) ofLog() << "Type messed up";
//    if(setupPanel()) ofLog() << "Panel failed";    
//}
//
//void testApp::update() {
//        //    uiConditions();
//    if(runFaceLoop())
//        ofLog() << "Error running face loop";
//    if(cam.isInitialized()) cam.update();
//    
//    if(cam.isFrameNew()) {
//        ofLog() << "New frame";
//            //convertColor(cam, gray, CV_RGB2GRAY);
//            //resize(gray, graySmall);
//        frame.setFromPixels(cam.getPixels(),cam.getWidth(),cam.getHeight(),OF_IMAGE_COLOR);
//        Mat graySmallMat = toCv(graySmall);
//        if(ofGetMousePressed()) {
//                //equalizeHist(graySmallMat, graySmallMat);
//        }
//            //        graySmall.update();
//            ///        blur(cam, 10);
//            //   classifier.detectMultiScale(graySmallMat, objects, 1.06, 1,
//            //CascadeClassifier::DO_CANNY_PRUNING |
//            //CascadeClassifier::FIND_BIGGEST_OBJECT |
//            //CascadeClassifier::DO_ROUGH_SEARCH |
//            //   0);
//    } else {
//        ofLog() << "No new frame";
//    }
//}
//
//void testApp::draw() {
//    cam.draw(0,0);
//    cam.videoSettings();    
//    /*
//     ofSetBackgroundAuto(1);
//     ofPushMatrix();
//     ofTranslate(panelWidth, 0);
//     //graySmall.draw(0, 0, 640, 480);
//     cam.draw(0, 0);
//     frame.draw(cam.getWidth(),0);
//     
//     /*  ofNoFill();
//     
//     ofScale(1 / scaleFactor, 1 / scaleFactor);
//     for(int i = 0; i < objects.size(); i++) {
//     ofRect(toOf(objects[i]));
//     }
//     */
//    /*ofDrawBitmapString("Testing", 10, 20);
//     ofPopMatrix(); // For panel
//     */
//}
//
//void testApp::keyPressed(int key) {
//    if(key == ' ') {
//        
//    }
//}
//
//void testApp::mouseMoved(int x, int y ){
//    
//}
//
//bool testApp::runFaceLoop() {
//    
//    
//    return 0;
//}
//
//bool testApp::setupCamera() {
//    cam.setVerbose(1);
//    cam.setUseTexture(true);
//    cam.initGrabber(640, 480, true);
//    gray.allocate(640, 480, OF_IMAGE_GRAYSCALE);
//    graySmall.allocate(640,480,OF_IMAGE_GRAYSCALE);
//    
//    classifier.load(ofToDataPath("haarcascade_frontalface_alt2.xml"));
//    scaleFactor = .25;
//    frame.allocate(cam.getWidth(),cam.getHeight(), OF_IMAGE_COLOR);
//        //    graySmall.allocate(cam.getWidth() * scaleFactor, cam.getHeight() * scaleFactor, OF_IMAGE_GRAYSCALE);
//    
//    return 0;
//}
//
//bool testApp::setupType() {
//    ofTrueTypeFont::setGlobalDpi(72);
//    type.loadFont("Raleway-Thin.ttf", 32, true, true);
//    type.setLineHeight(18.0f);
//    type.setLetterSpacing(1.037);
//    return 0;
//}
//
//bool testApp::setupPanel() {
//    int panelWidth = 200;
//    panel.setup(panelWidth, 480);
//    panel.addPanel("Computer vision");
//    panel.addLabel("Image Processing");
//    panel.addSlider("maxThreshold", 15, 0, 255, true);
//    panel.addSlider("minAreaRadius", 7, 0, 640, true);
//    panel.addSlider("maxAreaRadius", 100, 0, 640, true);
//    panel.addLabel("Face Tracking");
//    panel.addSlider("learningTime",900,0,2000,true);
//    panel.addSlider("backgroundThresh",10,0,50,true);
//    panel.addToggle("resetBg", false);
//    panel.addToggle("startCamera", false);
//    panel.addToggle("playRecording", false);
//    return 0;
//}
//
//void testApp::debugDraw() {    
//}
//
//void testApp::uiConditions() {
//    if(panel.getValueB("startCamera")) {
//        ofLog() << "Restarting camera";
//        
//        panel.setValueB("startCamera",false);
//    }
//    if(panel.getValueB("resetBg")) {
//        ofLog() << "Reseting background";
//        
//        panel.setValueB("resetBg",false);
//    }
//    
//}
//
//
//    //--------------------------------------------------------------
//void testApp::exit() {
//    
//} 
