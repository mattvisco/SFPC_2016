#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"

struct CompareData {
    int rotate = 0;
    float colorDist ;
    float brightnessDiff;
    float hueDiff;
    float total;
};
struct Tile {
    ofImage originalImage;
    ofImage imageResized;
    ofPoint pos;
    int displayImgIndex;
    CompareData data;
};

class ofApp : public ofBaseApp{

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
    
    CompareData getCompareData(ofImage image1, ofImage image2);
    void recalculateTileTotals();
    void setPixels(int inc);
    
    ofImage image;
    vector<ofImage> imageTiles;
    vector<Tile> sourceTiles;
    
    int incBy;
    int height = 500;
    int width = 500;
    bool mosaic = false;
    
    float alpha = 0.0;
    float beta = 0.0;
    float gamma = 0.0;
		
    ofxDatGui* gui;
    ofxDatGuiSlider* alphaSlider;
    ofxDatGuiSlider* betaSlider;
    ofxDatGuiSlider* gammaSlider;
    
    void onSliderEvent(ofxDatGuiSliderEvent e);
};
