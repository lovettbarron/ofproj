#include "ofMain.h"
#include "face.h"

ofFace::ofFace(ofImage & _face)
{
    theFace = _face;
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
}

ofFace::~ofFace() 
{
    
}

void ofFace::update() {
    if(circle.size() <= 1) {
        genCircle();
    }
    if(tween <= 1.0) {
    tween += tweenStep;
    } else if (tween > 1.0) {
        tween = 1.0f;
    }
    center = ofPoint(x,y);
    age += 1;
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