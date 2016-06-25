#include "ofApp.h"
#include "data.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetLineWidth(3);
    
    //----------------------------------------------------------------
    // the data is stored in a big flat array, let's copy it into something more managable
    for (int i = 0; i < 30; i++){
        for (int j = 0; j < 24; j++){
            float x = data3d[ i * 24 * 3  + j * 3 + 0 ];
            float y = data3d[ i * 24 * 3  + j * 3 + 1 ];
            float z = data3d[ i * 24 * 3  + j * 3 + 2 ];
            frames[i][j].set(x,y,z);
        }
    }
    
    n1.set(0, 0,1);
    n2.set(0,1,0);
    n3.set(0,0,1);
    plane1.set(ofPoint(0,0,300), n1);
    plane2.set(ofPoint(0,300,0), n2);
    plane3.set(ofPoint(0,0,-300),n3);
}

WalkVect ofApp::getWalkVect(int frame, int joint1, int joint2, int steps) {
    ofPoint velocity;
    for(int i = frame; i > (frame - steps) % 30; i--) {
        ofPoint currVect = frames[i][joint1] - frames[i][joint2];
        ofPoint prevVect = frames[i-1][joint1] - frames[i-1][joint2];
        velocity += currVect - prevVect;
    }
    velocity /= steps;
    ofPoint lastVect = frames[frame][joint1] - frames[frame][joint2];
    IsLine line(frames[frame][joint1], frames[frame][joint2]);
    return createWalkVect(velocity, lastVect, line);
}

WalkVect ofApp::getWalkVectFrom1(int frame, int joint, int length, int steps) {
    ofPoint velocity;
    for(int i = frame; i > (frame - steps) % 30; i--) {
        velocity += frames[i][joint] - frames[i-1][joint];
    }
    velocity /= steps;
    ofPoint lastVect = frames[frame][joint];
    IsLine line(frames[frame][joint] - ofPoint(length,0,0), frames[frame][joint] + ofPoint(length,0,0));
    return createWalkVect(velocity, lastVect, line);
}

WalkVect ofApp::createWalkVect(ofPoint velocity, ofPoint vector, IsLine line) {
    ofPoint dir = vector.normalize();
    if(velocity.y < 0) dir *= -1;
    WalkVect vect;
    vect.dir = dir;
    vect.spd = velocity.length();
    vect.line = line;
    return vect;
}

WalkVect ofApp::copyWalkVect(WalkVect vect) {
    WalkVect vectCopy;
    vectCopy.dir = vect.dir;
    vectCopy.spd = vect.spd;
    vectCopy.line = vect.line;
    vectCopy.circle = vect.circle;
    vectCopy.circlePos = vect.circlePos;
    vectCopy.radius = vect.radius;
    return vectCopy;
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){

    ofBackground(0);

    //----------------------------- 3d
    cam.begin();
    ofSetColor(255);
    
    //----------------------------- copy data into array
    ofPoint data3d[24];
    
    currFrame = (int)(ofGetFrameNum()*0.5) % 30;
//    cout << currFrame << endl;
    
    for (int i = 0; i < 24; i++){
        data3d[i] = frames[currFrame][i];
    }
    
    ofDrawLine(data3d[10]-ofPoint(10,0,0), data3d[10]+ofPoint(10,0,0));
    ofDrawLine(data3d[18], data3d[19]);
    ofDrawLine(data3d[22], data3d[23]);
    
//    if(currFrame == 14 || currFrame == 0) {
//        currWalks.push_back(getWalkVectFrom1(currFrame, 10, 5, 3));
//    }
    if(currFrame == 22) { // foot 1
        currWalks.push_back(getWalkVect(currFrame, 22, 23, 3));
    } else if (currFrame == 29) { // foot 2
        currWalks.push_back(getWalkVect(currFrame, 18, 19, 3));
    }
    
    for(auto& walk : currWalks) {
        if(walk.circle) {
//            if(walk.radius < walk.maxRadius) {
                ofNoFill();
                ofDrawCircle(walk.circlePos, walk.radius);
                walk.radius++;
//            } else {
                // TODO: erase element from vector and generate new lines
//                currWalks.erase(walk);
//            }
        } else {
            IsLine line = walk.line;
            ofPoint p0 = line.getP0() + (walk.dir * walk.spd);
            ofPoint p1 = line.getP1() + (walk.dir * walk.spd);
            walk.line.set(p0 , p1);
            IntersectionData inter1 = is.LinePlaneIntersection(walk.line, plane3);
            IntersectionData inter2 = is.LinePlaneIntersection(walk.line, plane1);
            IntersectionData inter3 = is.LinePlaneIntersection(walk.line, plane2);
            if(inter1.isIntersection){
                walk.circlePos = inter1.pos;
                walk.circle = true;
            } else if(inter2.isIntersection){
                walk.circlePos = inter2.pos;
                walk.circle = true;
            } else if(inter3.isIntersection){
                walk.circlePos = inter3.pos;
                walk.circle = true;
            } else {
                walk.line.draw();
            }
//            plane1.draw();
//            plane2.draw();
//            plane3.draw();
        }
    }
    
     
    
     
    
    
//     
//     ofSetColor(255, 255,255);
//     for(int i=0;i<1000;i++){
//         lines[i].draw();
//         idata=is.LinePlaneIntersection(lines[i], p1);
//         if(idata.isIntersection){
//         ofRect(idata.pos, 2,2);
//         }
//         idata=is.PointLineDistance(mousefinal, lines[i]);
//         if(idata.isIntersection){
//         ofRect(idata.pos, 3,3);
//         ofPushStyle();
//         ofSetColor(ofColor::red);
//         ofLine(idata.pos, mousefinal);
//         ofPopStyle();
//         };
//     }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 356) currFrame--;
    if(key == 358) currFrame++;
    currFrame %= 30;
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