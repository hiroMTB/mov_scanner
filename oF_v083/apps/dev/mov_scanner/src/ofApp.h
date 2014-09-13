#pragma once

#include "ofMain.h"
#include "ofQTKitPlayer.h"

#include "ofxOsc.h"
#include "ofxMidi.h"

class ofApp : public ofBaseApp {

public:
    void setup();
    void update();
    void scan_mov();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
	void windowResized(int w, int h);
    void exit();
    
    void set_window_size();
    void change_mov();
    
    bool bHorizon;
	bool bShowMov;
    bool bUseMov;
    
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
};
