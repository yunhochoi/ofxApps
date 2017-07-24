//
//  rectangle.h
//  02lineGraphicsWithSerial
//
//  Created by Yunho Choi on 7/20/17.
//
//

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "ofMain.h"

class rectangle {
    
public:
    
    rectangle();
    
    void update();
    void draw();
    void interpolateByPct(float myPct);
    
    ofPoint		pos;
    ofPoint		posa;
    ofPoint		posb;
    
    float		pct;	// what pct are we between "a" and "b"
        
};

#endif // RECTANGLE_H
