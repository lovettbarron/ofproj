#include "ofMain.h"
#include "canvas.h"

ofCanvas::ofCanvas()
{
    width = 800;
    height = 480;
    cx = width/2;
    cy = height/2;
    padding = 0.1;
 }

ofCanvas::~ofCanvas() 
{
    
}

//Translated from http://www.openprocessing.org/sketch/57395
// second try: http://www.codeproject.com/Articles/42067/2D-Circle-Packing-algorithm-ported-to-C

bool ofCanvas::compare(ofFace* face1, ofFace* face2) {    
    float d1 = face1->distance(ofVec2f(cx,cy));
    float d2 = face2->distance(ofVec2f(cx,cy));
    if (d1 < d2)
        return 1;
    else if (d1 > d2)
        return -1;
    else return 0;
}

void ofCanvas::compareWithStillActive( vector<ofFace> * _faces ) {
    //ofLog() << "Starting compare";
    vector<ofFace> faces = *_faces;
    //ofLog() << "The compare array is " << ofToString(faces.size()) << " long";
    //ofLog() << "The primary array is " << ofToString(canvas.size()) << " long";
    if(canvas.size() == 0) canvas.push_back(faces[0]);
    for(int i=0;i<canvas.size();i++){
        for(int j=0;j<faces.size();j++){
            if(canvas[i].isWithinRange(faces[j].faceLocation)) {
                //ofLog() << "Updating " << ofToString(i) << " face";
                canvas[i].updateFace(faces[j].theFace, faces[j].faceLocation);
            } else {
                //ofLog() << "Adding a new face at" << ofToString(canvas.size());
                this->canvas.push_back(faces[j]);
            }
        }
    }
}


void ofCanvas::update() {
 
        // std::sort(canvas.begin(), canvas.end(), &compare);
    
    
    if(canvas.size() != 0) {
        float sepSq = .4 * .4;
        for (int i = 0; i < canvas.size() - 1; i++)
        {
            canvas[i].update();
            for (int j = i + 1; j < canvas.size(); j++)
            {
                
                if (i == j)
                    continue;
                
                ofVec2f AB = canvas[j].center - canvas[i].center;
                float r = canvas[i].radius + canvas[j].radius;
                
                
                    // Length squared = (dx * dx) + (dy * dy);
                float d = distance(canvas[i], canvas[j]);
                float minSepSq = ofClamp(d, 0, sepSq);
                d -= minSepSq;
                
                if (d < (r * r) - 0.01 )
                {
                    AB.normalize();
                    
                    AB *= (float)((r - sqrt(d)) * 0.5f);
                    canvas[j].x += AB.x;
                    canvas[j].y += AB.y;
                    canvas[i].x -= AB.x;
                    canvas[i].y -= AB.y;
                }
                
            }
        }
    }

}

void ofCanvas::draw(int _x, int _y) {
    for(int i=0;i<canvas.size();i++) {
        canvas[i].draw();
    }
}

void ofCanvas::configure() {

}

void ofCanvas::add(ofFace * face) {
    canvas.push_back(*face);
}


void ofCanvas::reset() {

}

int ofCanvas::size() {
    return canvas.size();
}

ofFace & ofCanvas::get( int index ) {
    return canvas.at(index);
}

float ofCanvas::distance(ofFace & face1, ofFace & face2) {
    return (face1.x - face2.x) * (face1.x - face2.x) + (face1.y - face2.y) * (face1.y - face2.y);

}

float ofCanvas::distance(ofPoint pt1, ofPoint pt2) {
    return (pt1.x - pt2.x) * (pt1.x - pt2.x) + (pt1.y - pt2.y) * (pt1.y - pt2.y);
    
}

    // via http://forum.openframeworks.cc/index.php?topic=886.0