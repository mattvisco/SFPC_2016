#pragma once

#include "ofMain.h"
#include "WiggleLine.h"

class ofApp : public ofBaseApp{

    private:
        int GUTTER = 10;
        int VERTLINES = 150;
        // Combos I like 50, 3
        int VERTICES = 20;
        int NOISEVERT = 4;
        int NOISEHORZ = 2;
        vector<WiggleLine> lines;
        vector<WiggleLine> linesHorz;
        int vertFourth, vertThreeFourth;
        ofPoint originPoint, endPoint, horzOriginPoint, horzEndPoint;
        float distanceBtwLines, distanceVertBtwLines;
        bool noiseOn = false;
    
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
