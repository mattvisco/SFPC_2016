#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"

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
    void setPixels(int inc);
    
    ofImage image;
    vector<ofImage> imageTiles;
    vector<ofImage> sourceTiles;
    vector<ofImage> sourceTilesResized;
    vector<int> sourceTilesIndices;
    vector<ofPoint> colors;
    vector<float> brightnesses;
    vector<float> hues;
    
    int incBy;
    int height = 500;
    int width = 500;
    bool mosaic = false;
    
    float alpha;
    float beta;
    float gamma;
		
    ofxDatGui* gui;
    ofxDatGuiSlider* alphaSlider;
    ofxDatGuiSlider* betaSlider;
    ofxDatGuiSlider* gammaSlider;
    
    void onSliderEvent(ofxDatGuiSliderEvent e);
};
