#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255);
    letter1.load("ArialBlack.ttf", 150, true, true, true);
    ofFill();
    ofSetLineWidth(0.1);
    ofSetColor(100);
//    ofSetColor(220,220,220,0.4);
}

//--------------------------------------------------------------
void ofApp::update(){

}

ofPath polysToPath(vector<ofPolyline> polylines) {
    ofPath path;
    for(int outline = 0; outline < polylines.size(); ++outline) {
        for (int i = 0; i < polylines[outline].getVertices().size(); i++){
            if ( i == 0 )
                path.moveTo(polylines[outline].getVertices()[i].x,polylines[outline].getVertices()[i].y);
            else
                path.lineTo(polylines[outline].getVertices()[i].x,polylines[outline].getVertices()[i].y);
        }
        path.close();
    }
    return path;
}

//--------------------------------------------------------------
void ofApp::draw(){
    makeLetter(83, ofPoint(100,150));
    makeLetter(70, ofPoint(250,150));
    makeLetter(80, ofPoint(400,150));
    makeLetter(67, ofPoint(550,150));
//    makeLetter(84, ofPoint(100,150));
}

void ofApp::makeLetter(int charNum, ofPoint pos) {
    ofTTFCharacter charPts = letter1.getCharacterAsPoints(charNum);
    ofPolyline letter = charPts.getOutline()[0];
    letter = letter.getResampledBySpacing(2);
    float min = 999999;
    float max = -1;
    vector<ofPolyline> letterLines;
    for(auto& pt : letter) {
        if(pt.x < min) min = pt.x;
        if(pt.x > max) max = pt.x;
        pt.x += pos.x;
        pt.y += pos.y;
        letterLines.push_back(ofPolyline());
    }
    min += pos.x;
    max += pos.x;
    float width = max - min;
    float height = ofGetHeight() - pos.y;
    int letterSize = letter.size();
    for(float i = 0; i <= height; i+=.1) {
        int index = 0;
        float heightRatio = i / height;
        float diffToAdd = (width/2) * heightRatio;
        for(auto& pt : letter) {
            float currMin = min + diffToAdd;
            float currMax = max - diffToAdd;
            float currPt = currMin + ( (pt.x - min)/width * (currMax - currMin) );
            if(pt.x < (width/2) + pos.x) {
                currMax = currMax - (currPt - currMin);
                currMin = currPt;
            }
            else {
                currMax = currMin + (currMax - currPt);
                currMin = currPt;
            }
            ofPoint point = ofPoint(ofMap(cos( (i+pt.x) / 20 ), -1, 1, currMin, currMax), pt.y + i);
//            if(index > letterSize/2) {
            letterLines[index].addVertex(point);
                ofDrawCircle(point, 0.1);
//            }
            index++;
        }
    }
//    for(auto& line : letterLines) {
//        line.draw();
//    }
    
    vector<ofPolyline> pLine = {letter};
    ofPath path = polysToPath(pLine);
    path.setFilled(true);
    path.setFillColor(ofColor::black);
    path.draw();
//    path.getOutline()[0].draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
