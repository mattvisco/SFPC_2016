#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "particle.h"
#include "spring.h"

#include "ofxFaceTracker.h"

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
	
	ofVideoGrabber cam;
	ofxFaceTracker tracker;
    
    int currBlob = 0;
    vector<vector <particle>> particleVects;
    vector<vector <spring>> springVects;
};
