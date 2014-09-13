//
//  dot_scan_point.h
//  mov_scanner
//
//  Created by hiroshi matoba on 9/13/14.
//
//

#pragma once

#include "ofMain.h"

class dot_scan_point{
    
public:

    dot_scan_point( float x, float y ){
        pos.set( x, y );
        ui_size = 10;
    }
  
    void draw(){
        ofSetRectMode( OF_RECTMODE_CENTER );
        ofNoFill();
        ofSetLineWidth( 2 );
        ofSetColor( 255, 0, 0 );
        ofRect( pos, ui_size, ui_size);
        ofSetRectMode( OF_RECTMODE_CORNER );
    }
    
    void touch( int x, int y, int button ){
        float dist = pos.distance( ofVec2f(x,y) );
        if( dist <= ui_size ){
            static float sence = 0.8;
            pos = pos*sence + ofVec2f(x, y)*0.2;
        }
    }
    
    ofVec2f pos;
    int ui_size;
};