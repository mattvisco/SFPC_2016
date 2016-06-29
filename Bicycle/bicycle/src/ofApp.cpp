#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // replace the string below with the serial port for your Arduino board
    // you can get this from the Arduino application or via command line
    // for OSX, in your terminal type "ls /dev/tty.*" to get a list of serial devices
    ard.connect("/dev/cu.usbserial-AM01QPE4", 57600);
    
    // listen for EInitialized notification. this indicates that
    // the arduino is ready to receive commands and it is safe to
    // call setupArduino()
    ofAddListener(ard.EInitialized, this, &ofApp::setupArduino);
    bSetupArduino	= false;	// flag so we setup arduino when its ready, you don't need to touch this :)
}

//--------------------------------------------------------------
void ofApp::update(){
    updateArduino();
}

//switch (key) {
//    case OF_KEY_RIGHT:
//        // rotate servo head to 180 degrees
//        ard.sendServo(9, 180, false);
//        ard.sendDigital(18, ARD_HIGH);  // pin 20 if using StandardFirmata from Arduino 0022 or older
//        break;
//    case OF_KEY_LEFT:
//        // rotate servo head to 0 degrees
//        ard.sendServo(9, 0, false);
//        ard.sendDigital(18, ARD_LOW);  // pin 20 if using StandardFirmata from Arduino 0022 or older
//        break;
//    default:
//        break;
//}


//--------------------------------------------------------------
void ofApp::draw(){
//    bgImage.draw(0,0);
//    
//    ofEnableAlphaBlending();
//    ofSetColor(0, 0, 0, 127);
//    ofDrawRectangle(510, 15, 275, 150);
//    ofDisableAlphaBlending();
//    
//    ofSetColor(255, 255, 255);
//    if (!bSetupArduino){
//        font.drawString("arduino not ready...\n", 515, 40);
//    } else {
//        font.drawString(potValue + "\n" + buttonState +
//                        "\nsending pwm: " + ofToString((int)(128 + 128 * sin(ofGetElapsedTimef()))), 515, 40);
//        
//        ofSetColor(64, 64, 64);
//        smallFont.drawString("If a servo is attached, use the left arrow key to rotate "
//                             "\ncounterclockwise and the right arrow key to rotate clockwise.", 200, 550);
//        ofSetColor(255, 255, 255);
//        
//    }
}

//--------------------------------------------------------------
void ofApp::setupArduino(const int & version) {
    
    // remove listener because we don't need it anymore
    ofRemoveListener(ard.EInitialized, this, &ofApp::setupArduino);
    
    // it is now safe to send commands to the Arduino
    bSetupArduino = true;
    
    // print firmware name and version to the console
    ofLogNotice() << ard.getFirmwareName();
    ofLogNotice() << "firmata v" << ard.getMajorFirmwareVersion() << "." << ard.getMinorFirmwareVersion();
    
    // Note: pins A0 - A5 can be used as digital input and output.
    // Refer to them as pins 14 - 19 if using StandardFirmata from Arduino 1.0.
    // If using Arduino 0022 or older, then use 16 - 21.
    // Firmata pin numbering changed in version 2.3 (which is included in Arduino 1.0)
    
    // set pins D4 and D6 to digital input
    ard.sendDigitalPinMode(4, ARD_INPUT);
    ard.sendDigitalPinMode(6, ARD_INPUT);
    
    // set pin D5 & D7 as digital output
    ard.sendDigitalPinMode(5, ARD_OUTPUT);
    ard.sendDigitalPinMode(7, ARD_OUTPUT);
    
    // Listen for changes on the digital and analog pins
    ofAddListener(ard.EDigitalPinChanged, this, &ofApp::digitalPinChanged);
}

//--------------------------------------------------------------
void ofApp::updateArduino(){
    
    // update the arduino, get any data or messages.
    // the call to ard.update() is required
    ard.update();
    
    // do not send anything until the arduino has been set up
    if (bSetupArduino) {
        // fade the led connected to pin D11
//        ard.sendPwm(11, (int)(128 + 128 * sin(ofGetElapsedTimef())));   // pwm...
    }
    
}

// digital pin event handler, called whenever a digital pin value has changed
// note: if an analog pin has been set as a digital pin, it will be handled
// by the digitalPinChanged function rather than the analogPinChanged function.

//--------------------------------------------------------------
void ofApp::digitalPinChanged(const int & pinNum) {
    // do something with the digital input. here we're simply going to print the pin number and
    // value to the screen each time it changes
    buttonState = "digital pin: " + ofToString(pinNum) + " = " + ofToString(ard.getDigital(pinNum));
    int state;
    if(ard.getDigital(pinNum)) state = ARD_HIGH;
    else state = ARD_LOW;
    if(pinNum == 4) {
        ard.sendDigital(5, state);
    } else if(pinNum == 6) {
        ard.sendDigital(7, state);
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
