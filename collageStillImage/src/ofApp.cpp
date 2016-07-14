#include "ofApp.h"

double ColourDistance(ofColor e1, ofColor e2)
{
    long rmean = ( (long)e1.r + (long)e2.r ) / 2;
    long r = (long)e1.r - (long)e2.r;
    long g = (long)e1.g - (long)e2.g;
    long b = (long)e1.b - (long)e2.b;
    return sqrt((((512+rmean)*r*r)>>8) + 4*g*g + (((767-rmean)*b*b)>>8));
}

//--------------------------------------------------------------
void ofApp::setup(){
    
    incBy = 5;
    
//    gui = new ofxDatGui( ofxDatGuiAnchor::TOP_RIGHT );
//    alphaSlider = gui->addSlider("alpha", 0.0, 1.0, 0.8);
//    alphaSlider->setPrecision(0);
//    betaSlider = gui->addSlider("beta", 0.0, 1.0, 0.2);
//    betaSlider->setPrecision(0);
//    gammaSlider = gui->addSlider("gamma", 0.0, 1.0, 0.0);
//    gammaSlider->setPrecision(0);
//    gui->onSliderEvent(this, &ofApp::onSliderEvent);
//
    alpha = 1.0;
    beta = 1.0;
    gamma = 1.0;
    
    // Form Image
    image = ofImage();
    image.load("smith.jpg");
    image.resize(width, height);
    // Source Image
    ofImage sourceImage = ofImage();
    sourceImage.load("justin2.jpg");
    sourceImage.resize(width, height);
    int index = 0;
    for(int i = 0; i < width; i+=incBy) {
        for(int j = 0; j < height; j+=incBy) {
            ofImage img;
            img.clone(sourceImage);
            img.crop(i, j, incBy, incBy);
            sourceTiles.push_back(img);
            ofImage resized;
            resized.clone(img);
            resized.resize(3,3);
            sourceTilesResized.push_back(resized);
            ofImage imgTile;
            imgTile.clone(image);
            imgTile.crop(i, j, incBy, incBy);
            imgTile.resize(3, 3);
            imageTiles.push_back(imgTile);
            sourceTilesIndices.push_back(index);
            index++;
        }
    }
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

void ofApp::setPixels(int inc) {
    int size = sourceTilesResized.size();
    
    for(int index = 0; index < inc; index++) {
        
        int index1 = ofRandom(size-1);
        int index2 = ofRandom(size-1);
        
        ofImage sourceTile1 = sourceTilesResized[sourceTilesIndices[index1]];
        ofImage sourceTile2 = sourceTilesResized[sourceTilesIndices[index2]];
        ofImage imageTile1 = imageTiles[index1];
        ofImage imageTile2 = imageTiles[index2];
        
        // Color
        float colDistTot = getColorDistance(sourceTile1, imageTile1) + getColorDistance(sourceTile2, imageTile2);
        float swapColDistTot = getColorDistance(sourceTile1, imageTile2) + getColorDistance(sourceTile2, imageTile1);
        
        // Brightness
        float colBrightTot = getBrightDiff(sourceTile1, imageTile1) + getBrightDiff(sourceTile2, imageTile2);
        float swapColBrightTot = getBrightDiff(sourceTile1, imageTile2) + getBrightDiff(sourceTile2, imageTile1);
        
        // Hue
        float colHueTot = getHueDiff(sourceTile1, imageTile1) + getHueDiff(sourceTile2, imageTile2);
        float swapColHueTot = getHueDiff(sourceTile1, imageTile2) + getHueDiff(sourceTile2, imageTile1);
        
        if( colDistTot*alpha + colBrightTot*beta + colHueTot*gamma > swapColDistTot*alpha + swapColBrightTot*beta + swapColHueTot*gamma ) {
            int tmpIndex = sourceTilesIndices[index2];
            sourceTilesIndices[index2] = sourceTilesIndices[index1];
            sourceTilesIndices[index1] = tmpIndex;
        }
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    if(mosaic) setPixels(1000);
}

//--------------------------------------------------------------
void ofApp::draw(){
    int ind = 0;
    for(auto& index : sourceTilesIndices) {
        int i = ( (ind * incBy) / height ) * incBy;
        int j = (ind * incBy) % height;
        sourceTiles[index].draw(i,j);
        ind++;
    }
    image.draw(500, 0);
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
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == ' ') mosaic = !mosaic;
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
