//
//  slam.h
//  testApp
//
//  Created by Andrew Lovett Barron on 12-07-28.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef slam_h
#define slam_h

#include <vector>
#include <string>
#include "ofMain.h"
#include "ofxKinect.h"
#include "ofxCv.h"

class ofxSLAM: public ofBaseApp {
    typedef std::vector<ofVec3f> points
    typedef std::vector<ofVec3f> framePoints
    
    public:
        void init();
        void update();
        
        bool record();
        
        void save();
        void exportFile();

        
    private:
        bool isRecording;
        bool isSaving;
    
    
}

#endif
