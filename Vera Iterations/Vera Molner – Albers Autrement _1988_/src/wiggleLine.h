//
//  wiggleLine.h
//  Vera Molner – Albers Autrement _1988_
//
//  Created by Matthew Visco on 6/9/16.
//
//

#ifndef WiggleLine_h
#define WiggleLine_h
#include "ofMain.h" // we need to include this to have a reference to the openFrameworks framework

class WiggleLine {
    
    private:
        ofPoint origin;
        ofPoint endPoint;
        int totalVertices;
        int noise;
        int dir;
        vector<ofPoint> vertices;
        ofPolyline mLine;
        void makeLine();
        ofPoint wiggle(float xOrY);
    
    
    public: // place public functions or variables declarations here
    
        enum { VERT, HORZ, BOTH };
        // methods, equivalent to specific functions of your class objects
        void setup();	// setup method, use this to setup your object's initial state
        void update();  // update method, used to refresh your objects properties
        void draw();    // draw method, this where you'll do the object's drawing
        void updatePoints(ofPoint p1, ofPoint p2);
        WiggleLine(ofPoint p1, ofPoint p2, int vertices, int noise, int dir);
    
    
};

#endif /* WiggleLine_h */
