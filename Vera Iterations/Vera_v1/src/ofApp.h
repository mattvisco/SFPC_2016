#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{
    
private:
    int GUTTER = 10;
    int VERTLINES = 150;
    // Combos I like 50, 3
    int VERTICES = 20;
    int VETICESNOISEVERT = 4;
    int VETICESNOISEHORZ = 2;
    int vertFourth, vertThreeFourth;
    ofPoint originPoint, endPoint, horzOriginPoint, horzEndPoint;
    float distanceBtwLines, distanceVertBtwLines;
    bool noiseOn = false;
    
    void drawWigglyLine(ofPoint pt1, ofPoint pt2, bool inX=true);
    
public:
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
    
};
