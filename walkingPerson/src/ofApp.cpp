#include "ofApp.h"
#include "data.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    ofSeedRandom(0);
    ofSetLineWidth(3);
    ofSetRectMode(OF_RECTMODE_CENTER);
    
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
    vectCopy.flag = vect.flag;
    vectCopy.intersectionPt = vect.intersectionPt;
    vectCopy.size = vect.size;
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
    
    for (int i = 0; i < 24; i++){
        data3d[i] = frames[currFrame][i];
    }
    
    ofDrawLine(data3d[10]-ofPoint(10,0,0), data3d[10]+ofPoint(10,0,0));
    ofDrawLine(data3d[18], data3d[19]);
    ofDrawLine(data3d[22], data3d[23]);
    
    ofDrawLine(data3d[6], data3d[7]); // right hand
    ofDrawLine(data3d[14], data3d[15]); // left hand
    
//    for (int i = 0; i < 24; i++){
//        ofDrawCircle(data3d[i], 5);
//        ofDrawBitmapString(i, data3d[i]);
//    }
    
    if(currFrame != prevFrame) {
        if(currFrame == 22) { // foot 1
            currWalks.push_back(getWalkVect(currFrame, 22, 23, 3)); // left foot
            // need rotation based on angle
    //        currWalks.push_back(getWalkVect(currFrame, 6, 7, 3)); // right hand
    //        currWalks.push_back(getWalkVect(currFrame, 14, 15, 3)); // left hand
        } else if (currFrame == 29) { // foot 2
            currWalks.push_back(getWalkVect(currFrame, 18, 19, 3)); // right foot
        }
    }
    vector<int> removeEls;
    int index = 0;
    for(auto& walk : currWalks) {
        if(walk.flag) {
            if(walk.size < walk.maxSize) {
                ofNoFill();
                if(walk.flag & CIRCLE) {
                    ofDrawCircle(walk.intersectionPt, walk.size);
                } else if(walk.flag & RECT) {
                    ofDrawRectangle(walk.intersectionPt, walk.size, walk.size);
                }
                walk.size++;
            } else {
                int removeIndex = index;
                removeEls.push_back(removeIndex);
                index++;
            }
        } else {
            IsLine line = walk.line;
            ofPoint p0 = line.getP0() + (walk.dir * walk.spd);
            ofPoint p1 = line.getP1() + (walk.dir * walk.spd);
            walk.dir.x += 0.1 * ofSignedNoise(walk.line.p0.x/10.0, walk.line.p0.y/10.0, ofGetElapsedTimef()*0.1, 0);
            walk.dir.y += 0.1 * ofSignedNoise(walk.line.p0.x/10.0, walk.line.p0.y/10.0, ofGetElapsedTimef()*0.1, 100);
            walk.line.set(p0 , p1);
            IntersectionData inter1 = is.LinePlaneIntersection(walk.line, plane3);
            IntersectionData inter2 = is.LinePlaneIntersection(walk.line, plane1);
            IntersectionData inter3 = is.LinePlaneIntersection(walk.line, plane2);
            if(inter1.isIntersection){
                walk.intersectionPt = inter1.pos;
                walk.flag = CIRCLE;
            } else if(inter2.isIntersection){
                walk.intersectionPt = inter2.pos;
                walk.flag = RECT;
            } else if(inter3.isIntersection){  // Unused plane right now
                walk.intersectionPt = inter3.pos;
                walk.flag = RECT;
            } else {
                walk.line.draw();
            }
//             walk.line.draw();
//            ofFill();
//            plane1.draw();
//            plane2.draw();
//            plane3.draw();
        }
    }
    for(auto& el : removeEls) {
        currWalks.erase(currWalks.begin()+el);
    }
    
    prevFrame = currFrame;
}

void ofApp::initBLine(BreakyLine &line, ofPoint pt) {
    line.start = pt;
    line.curr = pt; // Redundant for all but first time
    line.currDist = (int) floor(ofRandom(line.minDist, line.maxDist));
    ofVec2f pt2d(pt.x, pt.y);
    line.dir = ofPoint(ofRandom(-1, 1), ofRandom(-1, 1), 0).normalize() * line.incrementBy;
    line.pLine.addVertex(pt);
}

void ofApp::drawbreakyLine(BreakyLine &line) {
    if(!line.end) {
        if(line.start.distance(line.curr) >= line.currDist) {
            ofVec2f prevLine = line.curr - line.start;
            initBLine(line, line.curr);
            int choices[2] = {-1, 1};
            int choice = (int) floor(ofRandom(0, 2));
            line.dir = prevLine.getPerpendicular().normalize() * choices[choice] * line.incrementBy;
        }
        line.curr += line.dir;
        IsLine currLine(line.start, line.curr);
//        for(auto& walk : currWalks) {
//            if(walk.flag & BREAKYLINE) {
//                if(walk.bLine.pLine != line.pLine) {
//                    vector<ofPoint> vertices = walk.bLine.pLine.getVertices();
//                    for(int i = 5; i < vertices.size() - 1; i++) {
//                        IsLine interLine(vertices[i], vertices[i+1]);
//                        IntersectionData inter = is.LineLineIntersection(currLine, interLine);
//                        if(inter.isIntersection){
//                            line.curr = inter.pos;
//                            line.end = true;
//                        }
//                    }
//                }
//            }
//        }
        line.pLine.addVertex(line.curr);
    }
    line.pLine.draw();
}

bool operator==(const ofPolyline& lhs, const ofPolyline& rhs)
{
    vector<ofPoint> vertices1 = lhs.getVertices();
    vector<ofPoint> vertices2 = rhs.getVertices();
    if(vertices1.size() != vertices2.size()) return false;
    else {
        for(int i = 0; i < vertices1.size(); i++) {
            if(vertices1[i] != vertices2[i]) return false;
        }
    }
    return true;
}

bool operator!=(const ofPolyline& lhs, const ofPolyline& rhs)
{
    return !(lhs == rhs);
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