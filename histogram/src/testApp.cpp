/*
 Ê* Êhistrogram test
 Ê* Êborrowed and slightly modified from: 
 Ê*	http://dasl.mem.drexel.edu/~noahKuntz/openCVTut6.html
 Ê*
 Ê* ÊCreated by Andreas on 04.08.11.
 .* Modified by AndrewLB
 Ê* ÊCopyright 2011 invertednothing. All rights reserved.
 Ê*
 Ê*/

#include "testApp.h"

using namespace cv;
using namespace ofxCv;

    //--------------------------------------------------------------
void testApp::setup(){
    
    cam.initGrabber(640,480);
    
    
    
    
}

    // not really meant to run in a loop ---------------------------
void testApp::update(){	
    cam.update();
    if(cam.isFrameNew()) {
    ofBackground(100,100,100);
        CvHistogram* hist;
        IplImage* iplImageGray;
        IplImage** plane;
        
        iplImageGray = ofxCv::toCv(cam.getPixels());
        plane = &iplImageGray;
        
        int hist_size[] = { 30 };
        float range[] = { 0, 180 };
        float* ranges[] = { range };
        hist = cvCreateHist( 1, hist_size, CV_HIST_ARRAY, ranges, 1 );
        
        cvCalcHist( plane, hist, 0, 0 ); 
        cvNormalizeHist( hist, 20*255 ); // Normalize it
        
        cvCalcBackProject( plane, grayBack, hist );// Calculate back projection
        cvNormalizeHist( hist, 1.0 ); // Normalize it
        
        cvReleaseHist( &hist );

    }
}

    //--------------------------------------------------------------
void testApp::draw(){

        // draw the incoming, the grayscale, the bg and the thresholded difference
    ofSetHexColor(0xffffff);
    drawMat(grayBack,0,0);
}


