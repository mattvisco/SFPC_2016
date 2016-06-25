#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofBackground(201, 197, 212);
    ofSetColor(0);
    originPoint = ofPoint(GUTTER, GUTTER);
    vertFourth = (VERTLINES) / 4;
    vertThreeFourth = vertFourth * 3;
    
    endPoint = ofPoint(0, ofGetHeight() - GUTTER*2);
    distanceBtwLines = ( ofGetWidth() - GUTTER*2 ) / (float)VERTLINES;
    distanceVertBtwLines = ( ofGetHeight() - GUTTER ) / (float)VERTLINES;
    horzOriginPoint = originPoint + ofPoint(distanceBtwLines * vertFourth, 0);
    horzEndPoint = originPoint + ofPoint(distanceBtwLines * vertThreeFourth, 0);
}

//--------------------------------------------------------------
void ofApp::update(){
    ofSeedRandom(0);
    for(int i = 0; i < VERTLINES; i++) {
        ofPoint pt1 = originPoint + ofPoint(distanceBtwLines*i, 0);
        ofPoint pt2 = pt1 + endPoint;
        linesHorz.push_back(WiggleLine(pt1, pt2, VERTICES, NOISEVERT, WiggleLine::VERT));
        if( i > vertFourth && i < vertFourth*3 ) {
            float currY = distanceVertBtwLines*i;
            ofPoint hPt1 = horzOriginPoint + ofPoint(0, currY);
            ofPoint hPt2 = horzEndPoint + ofPoint(0, currY);
            linesHorz.push_back(WiggleLine(hPt1, hPt2, VERTICES, NOISEHORZ, WiggleLine::HORZ));
        }
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    for (vector<WiggleLine>::iterator line = lines.begin() ; line != lines.end(); ++line) {
        ((WiggleLine)*line).draw();
    }
    for (vector<WiggleLine>::iterator line = linesHorz.begin() ; line != linesHorz.end(); ++line) {
        ((WiggleLine)*line).draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if( key == 32 ) noiseOn = !noiseOn;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
