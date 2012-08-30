#include "ofMain.h"
#include "face.h"

ofFace::ofFace(ofImage & _face, ofVec3f _faceLocation)
{
    theFace = _face;
    faceLocation = _faceLocation;
    x = ofRandom(0,ofGetWidth());
    y = ofRandom(0,ofGetHeight());
    radius = ofRandom(0,ofGetWidth()/20);
    bActive = true;
    age = 0;
    resolution = 64;
    genCircle();
    center = ofVec3f(x,y);
    tween = 0.0f;
    tweenStep = 0.01;
    inactiveTimer = 0;
    inactiveTimerStep = 0.01f;
    changeThresh = 100;
}

ofFace::~ofFace() 
{
    
}

void ofFace::update() {
    if(circle.size() <= 1) {
        genCircle();
    }
    
    if(!bActive && inactiveTimer < 1.0) {
        inactiveTimer += inactiveTimerStep;
    }
    
    if(tween < 1.0) tween += tweenStep;
    else if (tween > 1.0) tween = 1.0f;
    
    tweenStep += tweenStep / 2;
    
    center = ofPoint(x,y);
    age += 1;
}

bool ofFace::setInactiveFace() {
    bActive = false;
}

bool ofFace::setActiveFace() {
    if(inactiveTimer < 1.0) {
        bActive = true;
        return true;
    }
    return false;
}

ofVec3f ofFace::cvFaceLocation() {
    // This might be better suited with a scale factor in future?
    return faceLocation;
}

void ofFace::updateFace(ofImage _face, ofVec3f _newLocation) {
    //I should have some kind of checking here, or something.
    inactiveTimer = 0;
    theFace = _face;  
    faceLocation = _newLocation;
}

bool ofFace::isWithinRange(ofVec3f _difference) {
    if(faceLocation.distance(_difference) < changeThresh) return true;
    else return false;
}

void ofFace::draw(int _x, int _y) {
    glPushMatrix();  
        theFace.reloadTexture();
        theFace.bind();  
        glTranslatef(_x,_y,0.0f);
        glBegin(GL_POLYGON);                  
        for(int i = 0; i < circleTex.size(); i++){  
            glTexCoord2f(circleTex[i].x, circleTex[i].y);  
            glVertex2f( circle[i].x * (radius*tween),  circle[i].y * (radius*tween));  
        }  
        glEnd();  
        
        theFace.unbind();  
    glPopMatrix();
}

void ofFace::draw() {
    ofFace::draw(x,y);
}

void ofFace::genCircle() {
    float angle = 0.0;  
    float step  = TWO_PI / (float)(resolution-1);  
    for(int i = 0; i < resolution; i++){  

        float px = cos(angle);  
        float py = sin(angle);  
        
        circle.push_back( ofPoint(px, py) );  
        
        float tx = ofMap( px, -1.0, 1.0, 0, theFace.getWidth());  
        float ty = ofMap( py, -1.0, 1.0, 0, theFace.getHeight());  
        
        circleTex.push_back( ofPoint(tx, ty) );  
        
        angle += step;  
    }  
}

float ofFace::distance(ofVec3f point) {
    return center.squareDistance(point);
}

void ofFace::reset() {
    circle.clear();
    circleTex.clear();
}