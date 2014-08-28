#include "ofApp.h"

/*
 *      Pixel read format
 *
 *      Prm0    vel
 *      Prm1    note
 *
 *      Prm2    CC102
 *      Prm3    CC103
 *       ...
 *
 *      noteOn
 */


/*
 *      OSC format
 *
 *      /ch value (0-255)
 *      
 *          e.g. /1 12
 *
 */

nr_track::nr_track()
:
prm_num( 10 ),
on( false )
{
    prm.resize(prm_num);
}

void ofApp::setup(){
    bShowMov = true;
	bHorizon = true;
    indicator = 0;
    indicator_speed = 2;
    noise_threashold = 0.3;
    track_num = 12;
    tracks = new nr_track[ track_num ];
    mov_num = 0;
    selected_mov = 0;
    
    ofSetWindowPosition(0, 0);
	ofBackground( 0, 0, 0 );
    ofSetFrameRate( 60 );
    
    {
        // Load Movie
        mov_num = mov_dir.listDir("movies");
        if ( mov_num==0 ) {
            cout << "cant find movie files in movies directory" << endl;
            ofExit();
            exit();
        }else{
            change_mov();
        }
    }

    set_window_size();
    
	mov_w = mov.getWidth();
    mov_h = mov.getHeight();
	dot_pos.resize( mov_w * mov_h );
	dot_col.resize( mov_w * mov_h );
	dot_vbo.setVertexData( &dot_pos[0], dot_pos.size(), GL_DYNAMIC_DRAW );
	dot_vbo.setColorData( &dot_col[0], dot_col.size(), GL_DYNAMIC_DRAW );
    
    line_pos.resize( 1000 );
    line_col.resize( 1000 );
    line_vbo.setVertexData( &line_pos[0], line_pos.size(), GL_DYNAMIC_DRAW );
    line_vbo.setColorData( &line_col[0], line_col.size(), GL_DYNAMIC_DRAW );
    
    
#ifdef SEND_MIDI
    midi_out.listPorts();
    midi_out.openVirtualPort( "from_mov_scaner" );
#endif
	
#ifdef SEND_OSC
	// osc
	string address = "localhost";
	osc_s.setup(address, 12345);
#endif
}

void ofApp::update(){
    
    indicator += indicator_speed;
    indicator %= (int)mov.getWidth();
    
    if( indicator_speed!=0 && indicator/indicator_speed ){
        int over = indicator%indicator_speed;
        indicator -= over;
    }
    mov.update();
    
    scan_mov();
}

void ofApp::scan_mov(){
    mov_w = mov.getWidth();
    mov_h = mov.getHeight();
    int quality = 3;
    int trackH = floor( (float)mov_h / (float)track_num );
    int total_prm = track_num * tracks[0].prm_num;
    unsigned char * pixels = mov.getPixels();
    ofPixelsRef pixelsRef = mov.getPixelsRef();
    
#ifdef SEND_OSC
    ofxOscBundle bundle;
#endif
    
    dot_pos.clear();
    dot_col.clear();
    line_pos.clear();
    line_col.clear();

    // scan all pixels
    for( int i = 0; i < mov_w; i+=quality ){
        for( int j = 0; j < mov_h; j+=quality ){
            unsigned char r = pixels[ (j*mov_w + i) * pixelsRef.getNumChannels() ];
            float val = ( (float)r / 255.0f );
            if (val>noise_threashold) {
                dot_pos.push_back( ofVec2f( i, j ) );
                dot_col.push_back( ofFloatColor( 0, 0, 0.6, 0.2+val) );
            }
        }
    }
    
    // scan indicator line only
    for(int i=0; i<track_num; i++){
        for(int j=0; j<tracks[0].prm_num+1; j++){
            int scan_resolution = 3;
            int y = i*trackH + j*scan_resolution;
            unsigned char r = pixels[ (y*mov_w + indicator) * pixelsRef.getNumChannels() ];
            int val_i = r;
            float val = ( (float)r / 255.0f );
			
            nr_track & track = tracks[i];
			
            // Prms
            if ( j < track.prm_num) {
                if( track.on ){
                    
                    // send CC
                    if( j >= 2 ){
                        val = MIN(val*1.4, 0.95);
                        track.prm[j] = val;
#ifdef SEND_MIDI
                        int cc_value = val * 127.0;
                        midi_out.sendControlChange( i+1, j+100, cc_value );
#endif
                    }else{
                        track.prm[j] = val;
                    }
                    
                    // draw
                    dot_pos.push_back( ofVec2f( indicator, y ) );
                    dot_col.push_back( ofFloatColor( 0.6, 0, 0.6, 1) );
                    
                }else{
                    if( j == 0 ){
                        track.prm[0] = val;
                    }
                }
                
                int len = track.prm[j] * 100;
                ofFloatColor prm_line_color( 0.5 );
                if( track.on ) prm_line_color.set(0, 0, 1);
                
                line_pos.push_back( ofVec2f(mov_w+20, y) );
                line_pos.push_back( ofVec2f(mov_w+20+len, y) );
                line_col.push_back( prm_line_color );
                line_col.push_back( prm_line_color );
            }
			
            else if (j == track.prm_num ){
                if( val>noise_threashold) {
                    if( track.on == false ){
                        
                        track.on = true;
                        
#ifdef SEND_MIDI
                        // send midi
                        int vel = track.prm[0] * 100.0;
                        int note = track.prm[1] * 127.0;

                        // batterry setup
                        midi_out.sendNoteOn(i+1, note, vel);
                        track.current_note = note;
#endif
                    }
                    
#ifdef SEND_OSC
                    ofxOscMessage m;
                    m.setAddress("/"+ofToString(i));
                    m.addIntArg(val_i);
                    bundle.addMessage(m);
#endif
                    
                    // draw on/off
                    dot_pos.push_back( ofVec2f(indicator, y) );
                    dot_col.push_back( ofFloatColor(1, 0, 0, 1) );
                    
                    line_pos.push_back( ofVec2f(mov_w+10, i*trackH) );
                    line_pos.push_back( ofVec2f(mov_w+10, i*trackH+trackH-4) );
                    line_col.push_back( ofFloatColor(0, 0, 1) );
                    line_col.push_back( ofFloatColor(0, 0, 1) );
                }else{
#ifdef SEND_MIDI
                    if (track.on ){
                        midi_out.sendNoteOff(i+1, track.current_note );
                    }
#endif
                    track.on = false;
                }
            }
        }
    }

#ifdef	SEND_OSC
    osc_s.sendBundle(bundle);
#endif
}

void ofApp::draw(){
    mov_w = mov.getWidth();
    mov_h = mov.getHeight();
    
    ofEnableAlphaBlending();
    
	ofPushMatrix();{

        if(bHorizon){
            ofTranslate(20, 20);
        }else{
            ofRotate(90, 0, 0, 1);
            ofTranslate(20, -mov_h - 20);
        }
        
        if( bShowMov){
            ofSetHexColor( 0xFFFFFF );
            mov.draw( 0, 0 );
        }
        
        // indicator
        ofSetColor( 55, 55, 100 );
        ofLine( indicator, 0, indicator, mov_h+4 );

        // Track Line
        ofSetColor( 50 );
        ofSetLineWidth( 1 );
        ofLine( mov_w+20+100, 0, mov_w+20+100, mov_h );
    
        glPointSize( 2 );
		dot_vbo.bind();
		dot_vbo.updateVertexData( &dot_pos[0], dot_pos.size() );
		dot_vbo.updateColorData( &dot_col[0], dot_col.size() );
		dot_vbo.draw( GL_POINTS, 0, dot_pos.size() );
		dot_vbo.unbind();

        glLineWidth( 1 );
        line_vbo.bind();
		line_vbo.updateVertexData( &line_pos[0], line_pos.size() );
		line_vbo.updateColorData( &line_col[0], line_col.size() );
		line_vbo.draw( GL_LINES, 0, line_pos.size() );
		line_vbo.unbind();
    }ofPopMatrix();

    // info
    ofPushMatrix();{
		if(bHorizon){
			ofTranslate( mov_w+40, mov_h+20 );
		}else{
			ofTranslate( mov_h+30, mov_w+30 );
		}
		ofSetColor( 100 );
		ofDrawBitmapString( "th:" + ofToString(noise_threashold), 0, 20 );
		ofDrawBitmapString( "sp:" + ofToString( indicator_speed ), 0, 35 );
    }ofPopMatrix();
}

void ofApp::keyPressed(int key){
    
    switch(key){
        case OF_KEY_LEFT:
            if( ofGetKeyPressed(OF_KEY_SHIFT) ){
                indicator_speed -= 1;
            }else{
                noise_threashold-=0.1;
            }
            break;

        case OF_KEY_RIGHT:
            if( ofGetKeyPressed(OF_KEY_SHIFT) ){
                indicator_speed += 1;
            }else{
                noise_threashold += 0.1;
            }
            break;
        
        case ' ': mov.setPaused( !mov.isPaused() ); break;

		case 'm': bShowMov = !bShowMov; break;
			
		case 'd':
            bHorizon = !bHorizon;
            set_window_size();
            break;

		default: break;
    }
    
    if( 49<=key && key<=58 ){
        int mov_now = selected_mov;
        selected_mov = key - 49;
        if(mov_now != selected_mov) change_mov();
    }

}

void ofApp::set_window_size(){
    int mov_w = mov.getWidth();
    int mov_h = mov.getHeight();
    if(bHorizon) ofSetWindowShape( mov_w+150, mov_h+100 );
    else ofSetWindowShape( mov_h+100, mov_w+150 );
    ofSetWindowPosition(0, 0);
}

void ofApp::change_mov(){
    if( selected_mov<mov_num ){
        mov.stop();
        mov.close();
        string mov_name = mov_dir.getName( selected_mov );
        mov.loadMovie( "movies/"+ mov_name, OF_QTKIT_DECODE_PIXELS_AND_TEXTURE );
        mov.play();
        set_window_size();
        indicator = 0;
    }
}

void ofApp::keyReleased(int key){}
void ofApp::windowResized(int w, int h){}
void ofApp::exit(){
#ifdef SEND_MIDI
    midi_out.closePort();
#endif
}
