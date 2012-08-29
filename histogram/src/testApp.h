/*
 Ê* Êhistrogram test
 Ê* Êborrowed and slightly modified from: 
 Ê*	http://dasl.mem.drexel.edu/~noahKuntz/openCVTut6.html
 Ê*
 Ê* ÊCreated by Andreas on 04.08.11.
 Ê* ÊCopyright 2011 invertednothing. All rights reserved.
 Ê*
 Ê*/

#pragma once

#include "ofMain.h"
#include "ofxCv.h"


class testApp : public ofBaseApp{
    
public:
		void setup();
		void update();
		void draw();
    
		ofVideoGrabber cam;
    cv::Mat		colorImg;
    
    cv::Mat 	grayImage;
    cv::Mat   grayBack;
    
    
};

