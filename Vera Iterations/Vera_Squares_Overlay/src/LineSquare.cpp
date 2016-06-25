//
//  LineSquare.cpp
//  Vera_Squares_Overlay
//
//  Created by Matthew Visco on 6/14/16.
//
//

#include "LineSquare.h"

LineSquare::LineSquare(ofPoint position, ofPoint noise) {
    pos = position;
    LineSquare::noise = noise;
    distanceBetween = WIDTHHEIGHT / LINETOTAL;
}

void LineSquare::draw() {
    for( int i = 0; i < LINETOTAL; i++) {
        ofPoint originPoint = pos + ofPoint(0, i*distanceBetween);
        ofPoint endPoint = originPoint + ofPoint(WIDTHHEIGHT, 0);
        ofDrawLine(originPoint, endPoint);
    }
}