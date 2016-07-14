#include "ofApp.h"

double ColourDistance(ofColor e1, ofColor e2)
{
    long rmean = ( (long)e1.r + (long)e2.r ) / 2;
    long r = (long)e1.r - (long)e2.r;
    long g = (long)e1.g - (long)e2.g;
    long b = (long)e1.b - (long)e2.b;
    return sqrt((((512+rmean)*r*r)>>8) + 4*g*g + (((767-rmean)*b*b)>>8));
}

double getColorDistance(ofImage& image1, ofImage& image2) {
    ofPixels pixels1 = image1.getPixels();
    ofPixels pixels2 = image2.getPixels();
    double distance = 0;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            distance += ColourDistance(pixels1.getColor(i, j), pixels2.getColor(i, j));
        }
    }
    return distance / 9;
}

double getBrightDiff(ofImage& image1, ofImage& image2) {
    ofPixels pixels1 = image1.getPixels();
    ofPixels pixels2 = image2.getPixels();
    double distance = 0;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            distance += pixels1.getColor(i, j).getBrightness() - pixels2.getColor(i, j).getBrightness();
        }
    }
    return distance / 9;
}

double getHueDiff(ofImage& image1, ofImage& image2) {
    ofPixels pixels1 = image1.getPixels();
    ofPixels pixels2 = image2.getPixels();
    double distance = 0;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            distance += pixels1.getColor(i, j).getHue() - pixels2.getColor(i, j).getHue();
        }
    }
    return distance / 9;
}

// Invariant of 1st being the source tile b/c we want to rotate source
CompareData ofApp::getCompareData(ofImage image1, ofImage image2) {
    CompareData data;
    data.total = 999999; // Dono if this is needed
    for(int i = 0; i < 4; i++) {
        image1.rotate90(i);
        CompareData currData;
        currData.rotate = i;
        currData.colorDist = getColorDistance(image1, image2);
        currData.brightnessDiff = getBrightDiff(image1, image2);
        currData.hueDiff = getHueDiff(image1, image2);
        currData.total = currData.colorDist*alpha + currData.brightnessDiff*beta + currData.hueDiff*gamma;
        if (currData.total < data.total) data = currData;
    }
    return data;
}

//--------------------------------------------------------------
void ofApp::setup(){
    
    incBy = 5;
    
//    gui = new ofxDatGui( ofxDatGuiAnchor::TOP_RIGHT );
//    alphaSlider = gui->addSlider("Color", 0.0, 1.0, alpha);
//    betaSlider = gui->addSlider("Brightness", 0.0, 1.0, beta);
//    gammaSlider = gui->addSlider("Hue", 0.0, 1.0, gamma);
//    gui->onSliderEvent(this, &ofApp::onSliderEvent);
    
    // Form Image
    image = ofImage();
    image.load("turrell.jpg");
    image.resize(width, height);
    // Source Image
    ofImage sourceImage = ofImage();
    sourceImage.load("church.jpg");
    sourceImage.resize(width, height);
    
    // Uncomment if you want to process all at once (uncomment setPixel() below)
//    alpha = 0.8;
//    beta = 0.1;
//    gamma = 0.1;
    
    int index = 0;
    for(int i = 0; i < width; i+=incBy) {
        for(int j = 0; j < height; j+=incBy) {
            
            // Current Position
            ofPoint pos(i,j);
            
            // Form Image Tile
            ofImage imgTile;
            imgTile.clone(image);
            imgTile.crop(i, j, incBy, incBy);
            imgTile.resize(3, 3);
            imageTiles.push_back(imgTile);
            
            // Source Image Tile
            ofImage imgOg;
            imgOg.clone(sourceImage);
            imgOg.crop(i, j, incBy, incBy);
            // Source Image Tile Resize
            ofImage imgResized;
            imgResized.clone(imgOg);
            imgResized.resize(3,3);
            // Get Comparison Data
            CompareData data = getCompareData(imgResized, imgTile);
            Tile tile = {imgOg, imgResized, pos, index, data};
            sourceTiles.push_back(tile);
            
            index++;
        }
    }
    
    // Uncomment if you want to process all at once (uncomment scalars above)
//    setPixels(100000);
}

void ofApp::setPixels(int inc) {
    int size = sourceTiles.size();
    
    for(int index = 0; index < inc; index++) {
        
        int index1 = ofRandom(size-1);
        int index2 = ofRandom(size-1);
        
        Tile& sourceTile1 = sourceTiles[index1];
        Tile& sourceTile2 = sourceTiles[index2];
        ofImage imageTile1 = imageTiles[sourceTile1.displayImgIndex];
        ofImage imageTile2 = imageTiles[sourceTile2.displayImgIndex];
        
        CompareData swapData1 = getCompareData(sourceTile1.imageResized, imageTile2);
        CompareData swapData2 = getCompareData(sourceTile2.imageResized, imageTile1);
        
        if( sourceTile1.data.total + sourceTile2.data.total > swapData1.total + swapData2.total ) {
            int tmpIndex = sourceTile1.displayImgIndex;
            ofPoint tmpPos = sourceTile1.pos;
            sourceTile1.data = swapData1;
            sourceTile1.displayImgIndex = sourceTile2.displayImgIndex;
            sourceTile1.pos = sourceTile2.pos;
            sourceTile2.data = swapData2;
            sourceTile2.displayImgIndex = tmpIndex;
            sourceTile2.pos = tmpPos;
        }
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    if(mosaic) setPixels(1000);
}

//--------------------------------------------------------------
void ofApp::draw(){
    for(auto& tile : sourceTiles) {
        tile.originalImage.rotate90(tile.data.rotate);
        tile.data.rotate = 0;
        tile.originalImage.draw(tile.pos);
    }
    image.draw(500, 0);
}

void ofApp::recalculateTileTotals() {
    for(auto& tile : sourceTiles) {
        tile.data.total = tile.data.colorDist*alpha + tile.data.brightnessDiff*beta + tile.data.hueDiff*gamma;
    }
}

void ofApp::onSliderEvent(ofxDatGuiSliderEvent e) {
    float value = e.target->getValue();
    if (e.target == alphaSlider){
        alpha = value;
    } else if (e.target == betaSlider){
        beta = value;
    } else {
        gamma = value;
    }
    recalculateTileTotals();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == ' ') {
        mosaic = !mosaic;
        alpha = 0.8;
        beta = 0.1;
        gamma = 0.1;
        recalculateTileTotals();
    }
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
