//
//  LineSquare.h
//  Vera_Squares_Overlay
//
//  Created by Matthew Visco on 6/14/16.
//
//

#ifndef LineSquare_h
#define LineSquare_h

#include "ofMain.h"
class LineSquare {
    
    private:
        int distanceBetween;

    public:
        static const int LINETOTAL = 20;
        static const int WIDTHHEIGHT = 80;
        ofPoint pos;
        ofPoint noise;
        void draw();
        LineSquare(ofPoint position, ofPoint noise);
};

#endif /* LineSquare_h */
