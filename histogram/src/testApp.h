/*
 �* �histrogram test
 �* �borrowed and slightly modified from: 
 �*	http://dasl.mem.drexel.edu/~noahKuntz/openCVTut6.html
 �*
 �* �Created by Andreas on 04.08.11.
 �* �Copyright 2011 invertednothing. All rights reserved.
 �*
 �*/

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

