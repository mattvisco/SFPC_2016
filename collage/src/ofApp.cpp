#include "ofApp.h"

static int getAvgBrightness(ofImage img) {
    int total = 0;
    int width = img.getWidth();
    int height = img.getHeight();
    for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++) {
            total += img.getPixels().getColor(i, j).getBrightness();
        }
    }
    return total / (width*height);
}

static ofPoint getAvgColor(ofImage img) {
    ofPoint total(0,0,0);
    int width = img.getWidth();
    int height = img.getHeight();
    ofPixels pixels = img.getPixels();
    for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++) {
            ofColor col = pixels.getColor(i, j);
            total += ofPoint(col.r, col.g, col.b);
        }
    }
    return total / (width*height);
}

static bool sortOnBrightness( ofImage A, ofImage B ){
    return ( getAvgBrightness(A) < getAvgBrightness(B) );
}

static bool sortOnInt( int A, int B ){
    return ( A < B );
}

//static bool sortOnInt( int A, int B ){
//    return ( A < B );
//}

//--------------------------------------------------------------
void ofApp::setup(){
    grabber.setup(500, 500);
    ofSetRectMode(OF_RECTMODE_CENTER);
    
    img = ofImage();
    img.load("church.jpg");
    int w = img.getWidth();
    int h = img.getHeight();
    float aspect = w/ ((float)h);
//    if(w > h) img.resize(500, 500 * aspect);
//    else img.resize(500 / aspect, 500 );
    img.resize(500, 500);
    incBy = 10;
    
    for(int i = 0; i < img.getWidth(); i+=incBy) {
        for(int j = 0; j < img.getHeight(); j+=incBy) {
            ofImage tmpImg;
            tmpImg.clone(img);
            tmpImg.crop(i, j, incBy, incBy);
            images.push_back(tmpImg);
        }
    }
//    ofSort(images, sortOnBrightness);
    
    for(auto& img : images) {
        brightness.push_back(getAvgBrightness(img));
        colors.push_back(getAvgColor(img));
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    grabber.update();
}

void ofApp::drawImageRGBNoRepeat2() {
    bool used[colors.size()];
    for(int i = 0; i < colors.size(); i++) {
        used[i] = false;
    }
    for (int i = 0; i < grabber.getWidth(); i+=incBy) {
        for (int j = 0; j < grabber.getHeight(); j+=incBy) {
            
            ofColor pixColor = grabber.getPixels().getColor(i, j);
            ofPoint colorPt(pixColor.r, pixColor.g, pixColor.b);
            float brightness = pixColor.getBrightness();
            
            int currClosest = 99999;
            int currClosestIndex = 0;
            int index = 0;
            for(auto& col : colors) {
                if(!used[index]) {
                    int tmpDist = col.distance(colorPt);
                    if (tmpDist < currClosest) {
                        currClosestIndex = index;
                        currClosest = tmpDist;
                    }
                }
                index++;
            }
            used[currClosestIndex] = true;
            images[currClosestIndex].draw(i,j);
        }
    }
}

void ofApp::drawImageClosestRGB() {
    for (int i = 0; i < grabber.getWidth(); i+=incBy) {
        for (int j = 0; j < grabber.getHeight(); j+=incBy) {
            
            ofColor pixColor = grabber.getPixels().getColor(i, j);
            ofPoint colorPt(pixColor.r, pixColor.g, pixColor.b);
            float brightness = pixColor.getBrightness();
            
            int currClosest = 99999;
            int currClosestIndex = 0;
            int index = 0;
            for(auto& col : colors) {
                int tmpDist = col.distance(colorPt);
                if (tmpDist < currClosest) {
                    currClosestIndex = index;
                    currClosest = tmpDist;
                }
                index++;
            }
            images[currClosestIndex].draw(i,j);
        }
    }
}

void ofApp::drawImageRGBNoRepeat() {
    int size = (grabber.getWidth() / incBy) * (grabber.getHeight() / incBy);
    bool used[size];
    for(int i = 0; i < size; i++) {
        used[i] = false;
    }
    int index = 0;
    for(auto& img : images) {
        int currClosest = 99999;
        int currClosestIndex = 0;
        ofPoint imgPos;
        for (int i = 0; i < grabber.getWidth(); i+=incBy) {
            for (int j = 0; j < grabber.getHeight(); j+=incBy) {
                int usedIndex = ((i/incBy) * (grabber.getWidth()/incBy)) + (j/incBy);
                if(!used[usedIndex]) {
                    ofColor pixColor = grabber.getPixels().getColor(i, j);
                    ofPoint colorPt(pixColor.r, pixColor.g, pixColor.b);
                    int tmpDist = colors[index].distance(colorPt);
                    if (tmpDist < currClosest) {
                        imgPos = ofPoint(i,j);
                        currClosestIndex = usedIndex;
                        currClosest = tmpDist;
                    }
                }
            }
        }
        img.draw(imgPos.x,imgPos.y);
        index++;
        used[currClosestIndex] = true;
    }
}

void ofApp::drawImageRGBNoRepeat3() {
    int size = images.size();
    int height = (int)grabber.getHeight();
    ofPixels pixels = grabber.getPixels();
    
    for(int index = 0; index < size; index++) {
        int i = ( (index * incBy) / height ) * incBy;
        int j = (index * incBy) % height;
        ofColor pixColor = pixels.getColor(i, j);
        ofPoint colorPt(pixColor.r, pixColor.g, pixColor.b);
        int tmpDist = colors[index].distance(colorPt);
        int lowestEnery = 9999;
        int currIndex = index;
        
        for(int ind = index+1; ind < size; ind++) {
            int k = ( (ind * incBy) / height ) * incBy;
            int l = (ind * incBy) % height;
            
            ofColor pixColorNext = pixels.getColor(k, l);
            ofPoint colorPtNext(pixColorNext.r, pixColorNext.g, pixColorNext.b);
            
            int tmpDistNext = colors[ind].distance(colorPtNext);
            int tmpDistSwap = colors[index].distance(colorPtNext);
            int tmpDistNextSwap = colors[ind].distance(colorPt);
            
            if(tmpDist+tmpDistNext > tmpDistSwap + tmpDistNextSwap && tmpDistSwap + tmpDistNextSwap < lowestEnery) {
                lowestEnery = tmpDistSwap + tmpDistNextSwap;
                currIndex = ind;
            }
        }
        
        images[currIndex].draw(i, j);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
//    drawImageRGBNoRepeat3();
    drawImageClosestRGB();
}

void ofApp::oldImageDrawingStuff() {
    bool used[colors.size()];
    for(int i = 0; i < colors.size(); i++) {
        used[i] = false;
    }
    // proper way to mosaic is to average the image, but we're just gonna step by 10
    float time = ofGetElapsedTimef();
    //    float inc = 20;//ofMap(sin(time / 100), -1, 1, 5, 30);
    for (int i = 0; i < grabber.getWidth(); i+=incBy) {
        for (int j = 0; j < grabber.getHeight(); j+=incBy) {
            
            ofColor pixColor = grabber.getPixels().getColor(i, j);
            ofPoint colorPt(pixColor.r, pixColor.g, pixColor.b);
            float brightness = pixColor.getBrightness();
            
            
            // OLD CODE DOING MY OTHER SHEEEIT Ñ
            
            //            ofPoint pix;
            //            if(brightness > 127) {
            //                for (int i = 255; i >= 0; i--) {
            //                    <#statements#>
            //                }
            //            } else {
            //
            //            }
            
            //            int bucket = brightness / bucketSize;
            //
            //            images[bucket].draw(i, j);
            
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
            //            if(brightness < 127) {
            ////                pixColor.g = 255;//(brightness/255);
            ////                pixColor.b = 255;// (brightness/255);
            ////                pixColor.r = 255;//(brightness/255);
            ////                ofSetColor(pixColor);
            ////                ofDrawLine(i, j, i+10, j);
            //
            //                pixColor = ofColor(199, 90, 0) * (brightness/255);
            //                ofSetColor(pixColor);
            //                ofDrawRectangle(i, j, inc*3/4, inc * 4/3);
            //
            //////                ofDrawLine(i, j , i+10, j-10);
            ////                pixColor.g *= (brightness/255) * ofMap(sin(ofGetElapsedTimef()),-1,1,0,1);
            ////                pixColor.b *= (brightness/255) * ofMap(sin(ofGetElapsedTimef()),-1,1,0,1);
            ////                pixColor.r *= (brightness/255) * ofMap(sin(ofGetElapsedTimef()),-1,1,0,1);
            ////                ofSetColor(pixColor);
            //////                ofDrawCircle(i, j, 20);
            ////                ofDrawRectangle(i, j, ofMap(sin(ofGetElapsedTimef()),-1,1,1,20), ofMap(sin(ofGetElapsedTimef()/2 + PI),-1,1,1,20));
            //            }
            //            else {
            //                pixColor = ofColor(0, 119, 119) * (brightness/255) * ofMap(sin(i*time/50 + PI),-1,1,0,1);
            //                ofSetColor(pixColor);
            //                ofDrawRectangle(i + ofMap(sin(j*time/50),-1,1,-10,10), j, inc*3/4, inc * 4/3);
            //
            ////                ofDrawLine(i, j, i+ofMap(sin(ofGetElapsedTimef() / 3),-1,1,1,10), j);
            ////                ofPushMatrix();
            ////                ofTranslate(i, j);
            ////                ofRotateZ(ofMap(sin(ofGetElapsedTimef()),-1,1,0,90));
            ////                ofDrawLine(0, 0, 10, 0);
            ////                ofPopMatrix();
            //            }
            
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
