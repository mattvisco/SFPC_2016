#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(201, 197, 212);
    ofSetColor(0);
    ofSoundStreamSetup(0, 1, this, 44100, beat.getBufferSize(), 4);
    
    originPoint = ofPoint(GUTTER, GUTTER);
    vertFourth = (LINETOTAL) / 4;
    vertThreeFourth = vertFourth * 3;
    soundPlayer.load("01-burn_the_witch.mp3");
    soundPlayer.play();
}

//--------------------------------------------------------------
void ofApp::update(){
    endPoint = ofPoint(0, ofGetHeight() - GUTTER*2);
    distanceBtwLines = ( ofGetWidth() - GUTTER*2 ) / (float)LINETOTAL;
    distanceVertBtwLines = ( ofGetHeight() - GUTTER ) / (float)LINETOTAL;
    horzOriginPoint = originPoint + ofPoint(distanceBtwLines * vertFourth, 0);
    horzEndPoint = originPoint + ofPoint(distanceBtwLines * vertThreeFourth, 0);
    
//    beat.update(ofGetElapsedTimeMillis());
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSeedRandom(0);
    for(int i = 0; i < LINETOTAL; i++) {
        ofPoint pt1 = originPoint + ofPoint(distanceBtwLines*i, 0);
        ofPoint pt2 = pt1 + endPoint;
        drawWigglyLine(pt1, pt2, *ofSoundGetSpectrum(i+shiftVert));
        if( i > vertFourth && i < vertFourth*3 ) {
            float currY = distanceVertBtwLines*i;
            ofPoint hPt1 = horzOriginPoint + ofPoint(0, currY);
            ofPoint hPt2 = horzEndPoint + ofPoint(0, currY);
            drawWigglyLine(hPt1, hPt2, *ofSoundGetSpectrum(i+1), false);
        }
    }
    
//    if( beat.hihat() ) {
//        ofBackground(0, 0, 255);
//    } else {
//        ofBackground(201, 197, 212);
//    }
//    cout << beat.kick() << "," << beat.snare() << "," << beat.hihat() << endl;
}

void ofApp::drawWigglyLine(ofPoint pt1, ofPoint pt2, float freq, bool inX) {
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
        if(inX) vertex = ofPoint(pt1.x + ofRandom(0,freq),j);
        else vertex = ofPoint(j, pt1.y + ofRandom(0,freq));
        pts.push_back(vertex);
        j += lineLength / VERTICES;
    }
    if(inX) vertex = ofPoint(pt1.x + ofRandom(0,freq),endLine);
    else vertex = ofPoint(endLine, pt1.y + ofRandom(0,freq));
    pts.push_back(vertex);
    ofPolyline currLine(pts);
    currLine.draw();
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if ( key == 356 ) {
        shiftVert++;
        shiftVert = min(shiftVert, BANDS-VERTICES);
    } else if ( key == 358 ) {
        shiftVert--;
        shiftVert = max(shiftVert, 1);
    } else if ( key == 357 ) {
        LINETOTAL--;
    } else if ( key == 359 ) {
        LINETOTAL++;
    }
}

void ofApp::audioReceived(float* input, int bufferSize, int nChannels) {
    beat.audioReceived(input, bufferSize, nChannels);
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
