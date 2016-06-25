#pragma once

#include "ofMain.h"
#include "ofxIntersection.h"

struct WalkVect {
    
    ofPoint dir;
    float spd;
    IsLine line;
    
    bool circle = false;
    ofPoint circlePos;
    int radius = 1;
//    int maxRadius = 100;
};

class ofApp : public ofBaseApp{
    
    
private:
    WalkVect foot1;
    WalkVect foot2;
    vector<WalkVect> currWalks;
    ofxIntersection is;
    ofVec3f n1,n2,n3;
    IsPlane plane1, plane2,plane3;
    
	public:
    int currFrame = 0;
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        WalkVect getWalkVect(int frame, int joint1, int joint2, int steps=1);
        WalkVect getWalkVectFrom1(int frame, int joint, int length, int steps=1);
        WalkVect createWalkVect(ofPoint velocity, ofPoint vector, IsLine line);
        WalkVect copyWalkVect(WalkVect vect);
    
        ofEasyCam cam;
    
        ofPoint frames[30][24];         // 30 frames, 24 points per frame
        ofPoint frames2d[30][24];         // 30 frames, 24 points per frame
    
    
};
