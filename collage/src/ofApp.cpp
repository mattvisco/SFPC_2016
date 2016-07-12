#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    grabber.setup(640, 480);
    ofSetRectMode(OF_RECTMODE_CENTER);
}

//--------------------------------------------------------------
void ofApp::update(){
    grabber.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    
    // proper way to mosaic is to average the image, but we're just gonna step by 10
    float time = ofGetElapsedTimef();
    float inc = 5;//ofMap(sin(time / 100), -1, 1, 5, 30);
    for (int i = 0; i < grabber.getWidth(); i+=inc) {
        for (int j = 0; j < grabber.getHeight(); j+=inc) {
            
            ofColor pixColor = grabber.getPixels().getColor(i, j);
            float brightness = pixColor.getBrightness();
            
//            if(pixColor.r > pixColor.b && pixColor.r > pixColor.g) {
//                pixColor.r = 43;
//                pixColor.g = 75;
//                pixColor.b = 111;
//            }
////            else if (pixColor.g > pixColor.b && pixColor.g > pixColor.r){
////                pixColor.r = 115;
////                pixColor.g = 140;
////                pixColor.b = 166;
////            }
//            else {
//                pixColor.r = 4;
//                pixColor.g = 29;
//                pixColor.b = 55;
//            }
            
            // White
//            pixColor.g = 255 * (brightness/255);
//            pixColor.b = 255 * (brightness/255);
//            pixColor.r = 255 * (brightness/255);
            
           
            
            
//            ofPushMatrix();
//            ofTranslate(i, j);
//            ofRotateZ(ofMap(brightness, 0, 255, 0, 90));
//            ofDrawLine(0, 0, 3, 3);
//            ofPopMatrix();
//            ofDrawLine(i, j, i + 10, j);
//            pixColor = ofColor(228, 196, 0) * (brightness/255) * ofMap(sin(i*time/50 + PI),-1,1,0,1);
//            ofSetColor(pixColor);
//            ofDrawRectangle(i + ofMap(sin(j*time/50),-1,1,-10,10), j, inc*3/4, inc * 4/3);
            if(brightness < 127) {
//                pixColor.g = 255;//(brightness/255);
//                pixColor.b = 255;// (brightness/255);
//                pixColor.r = 255;//(brightness/255);
//                ofSetColor(pixColor);
//                ofDrawLine(i, j, i+10, j);
                
                pixColor = ofColor(199, 90, 0) * (brightness/255);
                ofSetColor(pixColor);
                ofDrawRectangle(i, j, inc*3/4, inc * 4/3);
            
////                ofDrawLine(i, j , i+10, j-10);
//                pixColor.g *= (brightness/255) * ofMap(sin(ofGetElapsedTimef()),-1,1,0,1);
//                pixColor.b *= (brightness/255) * ofMap(sin(ofGetElapsedTimef()),-1,1,0,1);
//                pixColor.r *= (brightness/255) * ofMap(sin(ofGetElapsedTimef()),-1,1,0,1);
//                ofSetColor(pixColor);
////                ofDrawCircle(i, j, 20);
//                ofDrawRectangle(i, j, ofMap(sin(ofGetElapsedTimef()),-1,1,1,20), ofMap(sin(ofGetElapsedTimef()/2 + PI),-1,1,1,20));
            }
            else {
                pixColor = ofColor(0, 119, 119) * (brightness/255) * ofMap(sin(i*time/50 + PI),-1,1,0,1);
                ofSetColor(pixColor);
                ofDrawRectangle(i + ofMap(sin(j*time/50),-1,1,-10,10), j, inc*3/4, inc * 4/3);
                
//                ofDrawLine(i, j, i+ofMap(sin(ofGetElapsedTimef() / 3),-1,1,1,10), j);
//                ofPushMatrix();
//                ofTranslate(i, j);
//                ofRotateZ(ofMap(sin(ofGetElapsedTimef()),-1,1,0,90));
//                ofDrawLine(0, 0, 10, 0);
//                ofPopMatrix();
            }
            
//            ofSetColor(pixColor);
//            if (brightness <= 100) {
//                ofPushMatrix();
//                ofTranslate(i, j);
//                ofRotateZ(ofMap(brightness, 0, 100, 0, 90));
//                ofDrawLine(0, 0, 3, 3);
//                ofPopMatrix();
//                ofDrawLine(i, j, i + 10, j);
//            } //ofDrawLine(i, j, i + 3, j + 3);
//            else ofDrawRectangle(0, 0, ofMap(brightness, 100, 255, 0, 3), 3);
        }
    }
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
