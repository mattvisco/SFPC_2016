#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(231,236,234);
    ofSetColor(0);
    
    // Make Squares
    ofSeedRandom(0);
    makeSquares();
}

void ofApp::makeSquares() {
    squares.clear();
    dt = 0;
    for (int i = 0; i < GRID; i++) {
        for (int j = 0; j < GRID; j++) {
            int gitterX = ofRandom(-1*GITTERAMOUNT, GITTERAMOUNT);
            int gitterY = ofRandom(-1*GITTERAMOUNT, GITTERAMOUNT);
            ofPoint gitter(gitterX, gitterY);
            ofPoint pos(LineSquare::WIDTHHEIGHT*i, LineSquare::WIDTHHEIGHT*j);
            pos += gitter;
            squares.push_back(LineSquare(pos, ofPoint(ofRandom(-5, 5),ofRandom(-5, 5))));
        }
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    if(animate) {
        for (auto& square : squares) {
            float noise = ofNoise( (dt * square.noise.x) / 100 );
            float yDelt = ofMap(noise, 0,1, -1, 1);
            noise = ofNoise( (dt * square.noise.y) / 100 );
            float xDelt = ofMap(noise, 0,1, -1, 1);
            square.pos.x += xDelt;
            square.pos.y += yDelt;
        }
        dt += 0.01;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    for (auto& square : squares) {
        square.draw();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 32) animate = true;;
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
