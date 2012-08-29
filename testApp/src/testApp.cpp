#include "testApp.h"

void testApp::setup() {
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofEnableNormalizedTexCoords(); ofDisableArbTex();
    graph.allocate(1200, 400, OF_IMAGE_COLOR);
    buffer.allocate(1200,400,GL_RGBA,1);
    testImg2.loadImage("graph.png");
    ofEnableSmoothing();
    center = ofVec3f();
    setupUI();
    setupVar();
    setupTCP();
    generateMesh(&points);
}

void testApp::update(){
    updateConditions();
    generateTexture();
    generateMesh(&points); 
    updateTexture();
}

void testApp::draw(){
    ofBackgroundGradient(ofColor(65,62,50),ofColor(25,22,10) );
    ofSetColor(255);
    ofPushMatrix();
    ofTranslate(200,0);
    glEnable(GL_DEPTH_TEST); // Manually enable for controlpanel
    camera.begin();
    
    //Create mesh
    if(panel.getValueB("manualCamera")) {
        camera.setPosition(ofVec3f(panel.getValueF("lightx"),panel.getValueF("lighty"),panel.getValueF("lightz")));
    }
    
    ofRotateZ(152.0f);
    ofRotateX(panel.getValueF("rotate"));
    
    //Draw loop

    graph.bind();
        if(panel.getValueB("wireframe")) {
            mesh.drawWireframe();
        } else { 
            mesh.draw(); 
        }
    graph.unbind();
    camera.end();
    ofPopMatrix();
    glDisable(GL_DEPTH_TEST); // Manually disable, then draw text + ofxACP
    drawHUD();
}

void testApp::mouseMoved(int x, int y ){

}


/************************************************
 *       Supporting functions for drawing       *
 ************************************************/

void testApp::updateTexture() {
    // mesh.clearTexCoords();
    /*
    for(int i = 1; i < points.size(); i++) {
        ofVec3f thisPoint = points[i-1];
        ofVec3f nextPoint = points[i];
        mesh.addTexCoord(ofVec2f((i-1) / points.size(),0.0f));
        
        if(i%1) {
            mesh.addTexCoord(ofVec2f(i / points.size(),0));
            
        } else {
            mesh.addTexCoord(ofVec2f(i / points.size(),1.0));
        }
     } */
    /*
   mesh.clearTexCoords(); 
   for(int i = 1; i < points.size()-1; i++) {
        mesh.addTexCoord(ofVec2f(i-1 / points.size(), 1));
        
        if(i%1) {
            mesh.addTexCoord(ofVec2f(i / points.size(), 1));
            
        } else {
            mesh.addTexCoord(ofVec2f(i+1 / points.size(), 0));
        }
    }

        // mesh.addTexCoord(ofVec2f(0,0));
        //    mesh.addTexCoord(ofVec2f(testImg2.width, testImg2.height));
*/
}

void testApp::generateTexture() {
    
    int currentDay = panel.getValueI("currentDay");
    int currentTime = panel.getValueI("currentTime");
    int meaningful = panel.getValueI("meaningful");
    int maxDays = panel.getValueI("maxDays");
    int multi = 5; // size multiplier
    
    ofPolyline currentMeaning;
    ofPolyline theTime;
    ofPolyline avgTime;
    bool bIsPastCurrentDate = false;
    
    for(int days=1; days<=maxDays; days++) {
        for(int hours=0; hours<23; hours++) {
            int index = ((hours+1)/24) + days;
            //This randomly generates a meanginful time
            bool bNoMoreMeaning=false;
            int fakeMeaning = fakeMeaning + ofRandom(3);
            if( ofRandom(4) == 0 ) {
                bNoMoreMeaning = true;
            }
            if(days==currentDay) {
                if( hours == currentTime ) {
                    bIsPastCurrentDate = true;  
                }
            }
            
            if(!bIsPastCurrentDate) {
                theTime.addVertex(index*multi,0);
            } else {
                theTime.addVertex(index*multi,buffer.getHeight());
            }
            
            if(!bNoMoreMeaning) {
                currentMeaning.addVertex(index*multi, fakeMeaning*multi);
            } else {
                currentMeaning.addVertex(index*multi,0);
            }
                // Alright, enough fake meaning. On to time.
            
       }            
    }
    currentMeaning.addVertex(points.size() * multi, 0);
    currentMeaning.addVertex(0,0);
    currentMeaning.setClosed(true);
    theTime.addVertex(points.size() * multi, 0);
    theTime.addVertex(0,0);
    theTime.setClosed(true);
    avgTime.addVertex(points.size() * multi, 0);
    avgTime.addVertex(0,0);
    avgTime.setClosed(true);

    //Begin writing to the FbO
    buffer.begin();
    ofBackground(255);
    /*for(int i=0;i<buffer.getWidth();i++){
        ofSetColor(ofRandom(255),ofRandom(255),ofRandom(255));
        ofLine(i,i,ofRandom(i),buffer.getHeight()+ofRandom(buffer.getHeight()));
    } */
    int scaleX = panel.getValueF("scaleX");
    int scaleY = panel.getValueF("scaleY");
    
    glPushMatrix();
    ofFill();
    ofSetLineWidth(5);
    ofScale(scaleX,scaleY);
    ofSetColor(255,0,0);
    theTime.draw();
    ofSetColor(0,255,0);
    avgTime.draw();
    ofSetColor(0,0,255);
    currentMeaning.draw();
    glPopMatrix();
    ofSetLineWidth(1);
    buffer.end();
    graph = buffer.getTextureReference();
    
    
    
}

void testApp::makeMesh() {
    mesh.clear();
    mesh.enableTextures();
    mesh.enableNormals();
    
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    
    for(int i = 1; i < points.size(); i++) {
        ofVec3f thisPoint = points[i-1];
        ofVec3f nextPoint = points[i];
        mesh.addVertex(thisPoint);
        //mesh.addTexCoord(ofVec2f((i / points.size()) * testImg2.width, testImg2.height));
        
        mesh.addTexCoord(ofVec2f((i-1)/points.size(),1.0f));
        mesh.addNormal(thisPoint);
        if(i%1 == 0){
            mesh.addVertex(ofVec3f(center.x, center.y, thisPoint.z)); 
            mesh.addTexCoord(ofVec2f(((i-1)/points.size(), 0.0f)));
                //mesh.addTexCoord(ofVec2f((i / points.size()) * testImg2.width, 1));
            mesh.addNormal(ofVec3f(center.x, center.y, center.z));
            }
        }
    ofLog() << "Vert:" << mesh.getNumVertices() << " Tex: " << mesh.getNumTexCoords()
    << "Norm: " << mesh.getNumNormals() << endl;
     /*
    glBegin(GL_TRIANGLE_STRIP);
        for(int i = 1; i < points.size(); i++) {
            ofVec3f thisPoint = points[i-1];
            ofVec3f nextPoint = points[i];
            
            glTexCoord3f((i-1)/points.size(), 1.0f, 0.0f);
            glVertex3f(thisPoint.x, thisPoint.y, thisPoint.z);
            if(i%1 == 0){
                glTexCoord3f((i-1)/points.size(), 0.0f, 0.0f);
                glVertex3f(center.x, center.y, thisPoint.z); 
            }
        }
    glEnd(); */
}

void testApp::generateMesh(vector<ofVec3f> * array) { 
    //Create initial mesh
    float depth = panel.getValueF("depth");
    float radius = panel.getValueF("radius");
    int maxDays = panel.getValueI("maxDays");
    
    array->clear();
    for(int days=1; days<=maxDays; days++) {
        for(int hours=0; hours<23; hours++) {
            unwrapPoint = 1.0f;
            float rotation = (hours*(TWO_PI * unwrapPoint)) / 23;
            float x = radius * cos(rotation);
            float y = radius * sin(rotation);
            float z = (depth * (hours+1)/24) + (depth * days);
            
            ofVec3f clockPosition(x,y,z);
            array->push_back(clockPosition);
        }
    }
    makeMesh();
}

void testApp::drawHUD() {
    // Debugging business
    graph.draw(ofGetWindowWidth() - graph.getWidth()/2,0,graph.getWidth()/2,graph.getHeight()/2);
    raleway.drawString(ofToString(panel.getValueI("currentDay")) + " at " + ofToString(panel.getValueI("currentTime")) + "pm", 400, 35);   
}

void testApp::checkUpdate() {
    if(connected){
        if(tcpClient.send(msgTx)){
            
            //if data has been sent lets update our text
            string str = tcpClient.receive();
             
            if( str.length() > 0 ){
                msgRx = str;
            }
        }else if(!tcpClient.isConnected()){
            weConnected = false;
        }
    }else{
        //if we are not connected lets try and reconnect every 5 seconds
        deltaTime = ofGetElapsedTimeMillis() - connectTime;
        
        if( deltaTime > 5000 ){
            weConnected = tcpClient.setup("127.0.0.1", 11999);
            connectTime = ofGetElapsedTimeMillis();
        }
        
    }
}


void testApp::animateMesh(vector<ofVec3f> * array) {
    float depth = panel.getValueF("depth");
    float radius = panel.getValueF("radius");
    int maxDays = array->size() / 24;
    ofLog() << "Returned array size: " << ofToString(array->size() );
}


/************************************************
 * Series of setup functions to clean things up *
 ************************************************/
void testApp::setupMesh() {
    
}

void testApp::setupVar() {
    ofTrueTypeFont::setGlobalDpi(72);
    raleway.loadFont("Raleway-Thin.ttf", 32, true, true);
    raleway.setLineHeight(18.0f);
    raleway.setLetterSpacing(1.037);    
}

void testApp::setupTCP() {
        //Setup TCP
    connected = tcpClient.setup("127.0.0.1", 11999);
    tcpClient.setMessageDelimiter("\n");
}

void testApp::setupUI() {
    panel.setup(200, 800);
    
    panel.addPanel("Clock");
    panel.addSlider("currentDay", 3, 1, 7, true);
    panel.addSlider("maxDays", 7, 1, 31, true);
    panel.addSlider("currentTime", 17, 0, 23, true);
    panel.addSlider("meaningful", 8, 0, 23, true);
    panel.addSlider("centerx", 0, 0, 5, false);
    panel.addSlider("centery", 0, 0, 5, false);
    panel.addSlider("centerz", 0, 0, 5, false);
    panel.addToggle("clockView", true);
    panel.addToggle("wireframe", false);
    panel.addToggle("manualCamera", false);
    panel.addToggle("unwrap", false);
    panel.addSlider("unwrapStep",0.00001,0,0.001, false);
    panel.addSlider("radius", 0.4, 0, 10, false);
    panel.addSlider("depth", 1.9, 0, 10, false);
    panel.addSlider("rotate", 0, 0, 360, false);
    panel.addSlider("lightx", 0, -50, 50, false);
    panel.addSlider("lighty", 0, -50, 50, false);
    panel.addSlider("lightz", 0, -50, 50, false);
    panel.addPanel("graph");
    panel.addSlider("scaleX", 5, 0, 100, false);
    panel.addSlider("scaleY", 5, 0, 100, false);
    unwrapPoint = 1.0f;
}

void testApp::updateConditions() {
    if(panel.getValueB("clockView")) { // If primary clock view
        
    }
    center = (panel.getValueF("centerx"),panel.getValueF("centery"),panel.getValueF("centerz"));
    int maxDays = panel.getValueI("maxDays");
    
    if(panel.hasValueChanged("maxDays") || panel.hasValueChanged("radius") || panel.hasValueChanged("depth")) {
            //generateMesh(&points,panel);
    }
    
    if(!panel.getValueB("unwrap")) {
        currentDayUnwrapped = maxDays;
        unwrap = false;
        alreadyUnwrapped = false;
        unwrapPoint = 1.0f;
    } else { unwrap = true; }
    
    if(unwrap) {
        animateMesh(&points);
    }
    
    //Camera setup
    if (!panel.getValueB("manualCamera") ) {
        camera.setPosition(ofVec3f(center.x,center.y,points[points.size()-1].z));
        camera.setNearClip(points[panel.getValueI("currentDay")*24].z);
        camera.lookAt(ofVec3f(center.x, center.y, points[panel.getValueI("currentDay")+24].z));
    }
}