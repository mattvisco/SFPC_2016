#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(201, 197, 212);
    ofSetColor(0);
    
    originPoint = ofPoint(GUTTER, GUTTER);
    vertFourth = (VERTLINES) / 4;
    vertThreeFourth = vertFourth * 3;
}

//--------------------------------------------------------------
void ofApp::update(){
    endPoint = ofPoint(0, ofGetHeight() - GUTTER*2);
    distanceBtwLines = ( ofGetWidth() - GUTTER*2 ) / (float)VERTLINES;
    distanceVertBtwLines = ( ofGetHeight() - GUTTER ) / (float)VERTLINES;
    horzOriginPoint = originPoint + ofPoint(distanceBtwLines * vertFourth, 0);
    horzEndPoint = originPoint + ofPoint(distanceBtwLines * vertThreeFourth, 0);
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSeedRandom(0);
    for(int i = 0; i < VERTLINES; i++) {
        ofPoint pt1 = originPoint + ofPoint(distanceBtwLines*i, 0);
        ofPoint pt2 = pt1 + endPoint;
        drawWigglyLine(pt1, pt2);
        if( i > vertFourth && i < vertFourth*3 ) {
            float currY = distanceVertBtwLines*i;
            ofPoint hPt1 = horzOriginPoint + ofPoint(0, currY);
            ofPoint hPt2 = horzEndPoint + ofPoint(0, currY);
            drawWigglyLine(hPt1, hPt2, false);
        }
    }
}

void ofApp::drawWigglyLine(ofPoint pt1, ofPoint pt2, bool inX) {
    vector<ofPoint> pts;
    float j, lineLength, endLine;
    if(inX) {
        j = pt1.y;
        lineLength = pt2.y - j;
        endLine = pt2.y;
    } else {
        j = pt1.x;
        endLine = pt2.x;
        lineLength = pt2.x - j;
    }
    ofPoint vertex;
    while( j  <= endLine ) {
        if(inX) vertex = ofPoint(pt1.x + ofRandom(0,VETICESNOISEVERT),j);
        else vertex = ofPoint(j, pt1.y + ofRandom(0,VETICESNOISEHORZ));
        pts.push_back(vertex);
        j += lineLength / VERTICES;
    }
    if(inX) vertex = ofPoint(pt1.x + ofRandom(0,VETICESNOISEVERT),endLine);
    else vertex = ofPoint(endLine, pt1.y + ofRandom(0,VETICESNOISEHORZ));
    pts.push_back(vertex);
    ofPolyline currLine(pts);
    currLine.draw();
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
