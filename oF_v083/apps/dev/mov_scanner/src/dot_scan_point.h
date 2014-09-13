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
  
    void draw( int ch ){
        ofSetRectMode( OF_RECTMODE_CENTER );
        ofNoFill();
        ofSetLineWidth( 1 );
        ofSetColor( 255, 0, 0 );
        ofRect( pos, ui_size, ui_size);
        ofSetRectMode( OF_RECTMODE_CORNER );
        
        // ch
        ofDrawBitmapString( ofToString(ch), pos+ofVec2f(4,-10) );
    }
    
    void pressed( int x, int y, int button ){
        float dist = pos.distance( ofVec2f(x,y) );
        if( dist <= ui_size ){
            bTouched = true;
        }
    }
    
    void dragged( int x, int y, int button ){
        if( bTouched ){
            static float sence = 0.9;
            pos = pos*(1.0-sence) + ofVec2f(x, y)*sence;
        }
    }
    
    void released( int x, int y, int button ){
        bTouched = false;
    }
  
    bool bTouched;
    ofVec2f pos;
    int ui_size;
};