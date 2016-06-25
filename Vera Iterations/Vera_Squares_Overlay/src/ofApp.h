#pragma once

#include "ofMain.h"
#include "LineSquare.h"

class ofApp : public ofBaseApp{
    
    private:
        int GRID = 9; // Creates 9x9 grid of squares
        vector<LineSquare> squares;
        int GITTERAMOUNT = 5;
        float dt = 0;
        bool animate = false;
    
	public:
		void setup();
		void update();
		void draw();
        void makeSquares();
    
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
