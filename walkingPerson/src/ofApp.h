#pragma once

#include "ofMain.h"
#include "ofxIntersection.h"

#define CIRCLE 0x01
#define RECT 0x02
#define BREAKYLINE 0x04

struct BreakyLine {
    ofPoint start;
    ofPoint curr;
    ofPoint dir;
    int minDist = 50;
    int maxDist = 100;
    int currDist = -1;
    int incrementBy = 1;
    bool end = false;
    ofPolyline pLine;
};

struct WalkVect {
    
    ofPoint dir;
    float spd;
    IsLine line;
    
    unsigned char flag = 0x00;
    ofPoint intersectionPt;
    int size = 1;
    int maxSize = 1000;
    int startTime;
    int maxTime = 500;
    
    BreakyLine bLine;
};

bool operator!=(const ofPolyline& lhs, const ofPolyline& rhs);
bool operator==(const ofPolyline& lhs, const ofPolyline& rhs);

class ofApp : public ofBaseApp{
    
    
private:
    bool on = true;
//    unsigned char flags = CIRCLE | RECT | BREAKYLINE;
    WalkVect foot1;
    WalkVect foot2;
    vector<WalkVect> currWalks;
    ofxIntersection is;
    ofVec3f n1,n2,n3;
    IsPlane plane1, plane2,plane3;
    int prevFrame;
    
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
    
    void drawbreakyLine(BreakyLine &line);
    void initBLine(BreakyLine &line, ofPoint pt);
    
        ofEasyCam cam;
    
        ofPoint frames[30][24];         // 30 frames, 24 points per frame
        ofPoint frames2d[30][24];         // 30 frames, 24 points per frame
    
    
};
