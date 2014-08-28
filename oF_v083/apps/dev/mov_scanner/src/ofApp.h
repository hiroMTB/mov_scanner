#pragma once

#include "ofMain.h"
#include "ofQTKitPlayer.h"

#define SEND_OSC 1
#ifdef SEND_OSC
#include "ofxOsc.h"
#endif

//#define SEND_MIDI 1
#ifdef SEND_MIDI
#include "ofxMidi.h"
#endif

class nr_track{
    
public:
    nr_track();
    int prm_num;
    bool on;
    vector<float> prm;

    int current_note;
};

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
    
    int track_num;
    int mov_num;
    int selected_mov;
    int mov_w;
    int mov_h;
    int indicator;
    int indicator_speed;
    float noise_threashold;
    
	nr_track * tracks;

    ofQTKitPlayer mov;

    // vbo draw
    ofVbo dot_vbo;
    vector<ofVec2f> dot_pos;
    vector<ofFloatColor> dot_col;

	ofVbo line_vbo;
    vector<ofVec2f> line_pos;
    vector<ofFloatColor> line_col;
    
    // output

#ifdef SEND_OSC
	ofxOscSender osc_s;
#endif

#ifdef SEND_MIDI
    ofxMidiOut midi_out;
#endif
	
    // mov dir
    ofDirectory mov_dir;
};
