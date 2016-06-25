//
//  WiggleLine.cpp
//  Vera Molner – Albers Autrement _1988_
//
//  Created by Matthew Visco on 6/9/16.
//
//

#include "WiggleLine.h"

WiggleLine::WiggleLine(ofPoint p1, ofPoint p2, int totVert, int n, int direction) {
    origin = p1;
    endPoint = p2;
    totalVertices = totVert;
    noise = n;
    dir = direction;
    
    setup();
}

void WiggleLine::setup() {
    ofSetColor(0);
    makeLine();
}

void WiggleLine::makeLine() {
    float start, lineLength, end;
    float lineLengthX = endPoint.x - origin.x;
    float lineLengthY = endPoint.y - origin.y;
    
    if(dir == VERT) {
        start = origin.y;
        lineLength = lineLengthY;
        end = endPoint.y;
    } else if(dir == HORZ) {
        start = origin.x;
        lineLength = lineLengthX;
        end = endPoint.x;
    }
    
    ofPoint vertex;
    while( start  <= end ) {
        ofPoint vertex = wiggle(start);
        vertices.push_back(vertex);
        start += lineLength / totalVertices;
    }
    vertex = wiggle(end);
    vertices.push_back(vertex);
    mLine = ofPolyline(vertices);
}

ofPoint WiggleLine::wiggle(float xOrY) {
    if(dir == VERT) {
        return ofPoint(origin.x + ofRandom(0,noise), xOrY);
    } else if(dir == HORZ) {
        return ofPoint(xOrY, origin.y + ofRandom(0,noise));
    }
}

void WiggleLine::updatePoints(ofPoint p1, ofPoint p2) {
    origin = p1;
    endPoint = p2;
    makeLine();
}

void WiggleLine::update() {
    
}

void WiggleLine::draw() {
    mLine.draw();
}