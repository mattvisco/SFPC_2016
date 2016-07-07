#include "ofApp.h"

using namespace ofxCv;

void ofApp::setup() {
	cam.initGrabber(1280, 720);
	tracker.setup();
}

void ofApp::update() {
	cam.update();
	if(cam.isFrameNew()) {
		tracker.update(toCv(cam));
	}
    
    ofPolyline mouth = tracker.getImageFeature(ofxFaceTracker::OUTER_MOUTH);
    //    mouth.draw();
    float jawOpen = tracker.getGesture(ofxFaceTracker::JAW_OPENNESS);
    
    if(jawOpen >= 23) {
        for(auto& pt : mouth) {
            
        }
        for (int i = 0; i < particles.size(); i++){
            spring mySpring;
            mySpring.distance		= 10;
            mySpring.springiness	= 0.2f;
            mySpring.particleA = & (particles[i  ]);
            mySpring.particleB = & (particles[(i+1) % particles.size()]);
            springs.push_back(mySpring);
        }
    }
    
    for (int i = 0; i < particles.size(); i++){
        particles[i].resetForce();
    }
    
    for (int i = 0; i < particles.size(); i++){
        
        particles[i].addRepulsionForce(mouseX, mouseY, 200, 0.7f);
        
        for (int j = 0; j < i; j++){
            particles[i].addRepulsionForce(particles[j], 20, 0.1);
        }
    }
    
    for (int i = 0; i < springs.size(); i++){
        springs[i].update();
    }
    
    
    for (int i = 0; i < particles.size(); i++){
        particles[i].bounceOffWalls();
        particles[i].addDampingForce();
        particles[i].update();
    }
}

void ofApp::draw() {
    ofSetColor(255);
	cam.draw(0, 0);
    
    
}

void ofApp::keyPressed(int key) {
	if(key == 'r') {
		tracker.reset();
	}
}
