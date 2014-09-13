#pragma once

#include "ofMain.h"
#include "ofQTKitPlayer.h"

#include "ofxOsc.h"
#include "ofxMidi.h"
#include "dot_scan_point.h"

class ofApp : public ofBaseApp {

public:
    void setup();
    void update();
    void dot_scan();
    void line_scan();
    
    void draw();
    void draw_mov();
    void draw_dot_scan();
    void draw_line_scan();
    void draw_info();
    
    void mousePressed( int x, int y, int button );
    void mouseReleased( int x, int y, int button );
    void mouseDragged( int x, int y, int button );
    void keyPressed(int key);
    void keyReleased(int key);
	void windowResized(int w, int h);
    void exit();
    
    void set_window_size();
    void change_mov();
    
    bool bHorizon;
	bool bShowMov;
    bool bUseMov;
    bool bUseLineScan;
    
    int track_num;
    int mov_num;
    int selected_mov;
    int mov_w;
    int mov_h;
    int indicator;
    int indicator_speed;
    int prm_num;

    float noise_threashold;

    // mov
    ofQTKitPlayer mov;
    
    // img
    ofImage img;

    // vbo draw
    ofVbo dot_vbo;
    vector<ofVec2f> dot_pos;
    vector<ofFloatColor> dot_col;

	ofVbo line_vbo;
    vector<ofVec2f> line_pos;
    vector<ofFloatColor> line_col;
    
    // output
    bool bSendOsc, bSendMidi;
	ofxOscSender osc_s;
    ofxMidiOut midi_out;
	ofxOscBundle bundle;
    
    // mov dir
    ofDirectory mov_dir;
    
    vector<dot_scan_point> dot_scan_points;
};
