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


void ofApp::setup(){
    bShowMov = false;
	bHorizon = true;
    bSendOsc = true;
    bSendMidi = false;
    bUseMov = true;
    
    indicator = 0;
    indicator_speed = 1;
    noise_threashold = 0.04;
    track_num = 8;
    prm_num = 10;
    mov_num = 0;
    selected_mov = 0;
    
    ofSetWindowPosition(0, 0);
	ofBackground( 0, 0, 0 );
    ofSetFrameRate( 60 );

    mov_num = mov_dir.listDir("movies");
    if( bUseMov ){
        // Load Movie
        if ( mov_num==0 ) {
            cout << "cant find movie files in movies directory" << endl;
            ofExit();
        }else{
            change_mov();
        }
    }else{
        bool ok = img.loadImage("img/skymap_1.png");
        if(!ok) ofExit();
    }
    
    
    set_window_size();
    
	if( bUseMov ){
        mov_w = mov.getWidth();
        mov_h = mov.getHeight();
    }else{
        mov_w = img.getWidth();
        mov_h = img.getHeight();
    }
    
	dot_pos.resize( mov_w * mov_h );
	dot_col.resize( mov_w * mov_h );
	dot_vbo.setVertexData( &dot_pos[0], dot_pos.size(), GL_DYNAMIC_DRAW );
	dot_vbo.setColorData( &dot_col[0], dot_col.size(), GL_DYNAMIC_DRAW );
    
    line_pos.resize( track_num*prm_num*10 );
    line_col.resize( track_num*prm_num*10 );
    line_vbo.setVertexData( &line_pos[0], line_pos.size(), GL_DYNAMIC_DRAW );
    line_vbo.setColorData( &line_col[0], line_col.size(), GL_DYNAMIC_DRAW );
    
    
    // midi
    midi_out.listPorts();
    midi_out.openVirtualPort( "from_mov_scanner" );

	// osc
	string address = "localhost";
	osc_s.setup(address, 12345);
}

void ofApp::update(){
    
    if( bUseMov ){
        mov_w = mov.getWidth();
        mov_h = mov.getHeight();
    }else{
        mov_w = img.getWidth();
        mov_h = img.getHeight();
    }
    
    indicator += indicator_speed;
    indicator %= (int)mov_w;
    
    if( indicator_speed!=0 && indicator/indicator_speed ){
        int over = indicator%indicator_speed;
        indicator -= over;
    }
    mov.update();
    
    scan_mov();
}

void ofApp::scan_mov(){
    unsigned char * pixels;;
    int dot_quality = 2;
    int scan_resolution = 4;
    int ch = 0;

    if( bUseMov ){
        mov_w = mov.getWidth();
        mov_h = mov.getHeight();
        pixels = mov.getPixels();
        ch = mov.getPixelsRef().getNumChannels();
    }else{
        mov_w = img.getWidth();
        mov_h = img.getHeight();
        pixels = img.getPixels();
        ch = img.getPixelsRef().getNumChannels();
    }
    
    int trackH = floor( (float)mov_h / (float)track_num );
    int total_prm = track_num * prm_num;
    
    bundle.clear();
    dot_pos.clear();
    dot_col.clear();
    line_pos.clear();
    line_col.clear();

    // scan all pixels
    for( int i=0; i<mov_w; i+=dot_quality ){
        for( int j=0; j<mov_h; j+=dot_quality ){
            unsigned char r = pixels[ (j*mov_w + i) * ch ];
            unsigned char g = pixels[ (j*mov_w + i) * ch ];
            unsigned char b = pixels[ (j*mov_w + i) * ch ];
            int val_i = (r+g+b)/3.0;
            float val = ( (float)val_i / 255.0f );
            if (val>noise_threashold) {
                dot_pos.push_back( ofVec2f( i, j ) );
                dot_col.push_back( ofFloatColor( 1, 1, 1, val) );
            }
        }
    }
    
    // scan indicator line only
    for(int i=0; i<track_num; i++){
        for(int j=0; j<prm_num; j++){
            // Prms
            int y = i*trackH + j*scan_resolution;
            int index = y*mov_w + indicator;
            unsigned char r = pixels[ index * ch + 0];
            unsigned char g = pixels[ index * ch + 1];
            unsigned char b = pixels[ index * ch + 2];
            int val_i = (r+g+b)/3.0;
            float val =  (float)val_i / 255.0;

            bool on = val>noise_threashold;
            if( on ){
                if( bSendMidi ){
                    int cc_value = val * 127.0;
                    midi_out.sendControlChange( i+1, j+100, cc_value );
                }
                
                if( bSendOsc ){
                    ofxOscMessage m;
                    m.setAddress( "/" + ofToString(i) + "/" + ofToString(j) );
                    m.addIntArg( val_i );
                    bundle.addMessage( m );
                }
                
                // draw dot in line
                dot_pos.push_back( ofVec2f( indicator, y ) );
                dot_col.push_back( ofFloatColor( 0.6, 0, 0.6, 1) );
            }
            
            // draw line in right side
            int len = val * 100;
            ofFloatColor prm_line_color( 0.5 );
            if( on ) prm_line_color.set(1.0, 0, 0.4, 1);
            
            line_pos.push_back( ofVec2f(indicator+20, y) );
            line_pos.push_back( ofVec2f(indicator+20+len, y) );
            line_col.push_back( prm_line_color );
            line_col.push_back( prm_line_color );

            line_pos.push_back( ofVec2f(mov_w+20, y) );
            line_pos.push_back( ofVec2f(mov_w+20+len, y) );
            line_col.push_back( prm_line_color );
            line_col.push_back( prm_line_color );
        }
    }

    if(bSendOsc) osc_s.sendBundle(bundle);
}

void ofApp::draw(){

    ofEnableAlphaBlending();
    ofEnableAntiAliasing();
    ofEnableSmoothing();
    
    if( bUseMov ){
        mov_w = mov.getWidth();
        mov_h = mov.getHeight();
    }else{
        mov_w = img.getWidth();
        mov_h = img.getHeight();
    }
    
    
	ofPushMatrix();{

        if(bHorizon){
            ofTranslate(20, 20);
        }else{
            ofRotate(90, 0, 0, 1);
            ofTranslate(20, -mov_h - 20);
        }
        
        // Movie
        if( bShowMov ){
            ofSetHexColor( 0xFFFFFF );
            if( bUseMov)
                mov.draw( 0, 0 );
            else
                img.draw(0, 0);
        }
        
        // indicator
        ofSetColor( 125, 125, 130 );
        ofLine( indicator, 0, indicator, mov_h+4 );

        // Track Line
        ofSetColor( 70 );
        ofSetLineWidth( 2 );
        ofLine( mov_w+20+100, 0, mov_w+20+100, mov_h );
    
        glPointSize( 2 );
		dot_vbo.bind();
		dot_vbo.updateVertexData( &dot_pos[0], dot_pos.size() );
		dot_vbo.updateColorData( &dot_col[0], dot_col.size() );
		dot_vbo.draw( GL_POINTS, 0, dot_pos.size() );
		dot_vbo.unbind();

        glLineWidth( 2 );
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
        if( bSendMidi ) ofDrawBitmapString( "MIDI", 0, 60 );
        if( bSendOsc ) ofDrawBitmapString( "OSC", 0, 75 );
    }ofPopMatrix();
}

void ofApp::keyPressed(int key){
    
    switch(key){
        case OF_KEY_LEFT:
            if( ofGetKeyPressed(OF_KEY_SHIFT) ){
                indicator_speed -= 1;
            }else{
                noise_threashold-=0.01;
            }
            break;

        case OF_KEY_RIGHT:
            if( ofGetKeyPressed(OF_KEY_SHIFT) ){
                indicator_speed += 1;
            }else{
                noise_threashold += 0.01;
            }
            break;
        
        case ' ': mov.setPaused( !mov.isPaused() ); break;

		case 's': bShowMov = !bShowMov; break;
			
		case 'd':
            bHorizon = !bHorizon;
            set_window_size();
            break;

        case 'o': bSendOsc = !bSendOsc; break;

        case 'm': bSendMidi = !bSendMidi; break;
            
		default: break;
    }
    
    if( 49<=key && key<=58 ){
        int mov_now = selected_mov;
        selected_mov = key - 49;
        if(mov_now != selected_mov) change_mov();
    }

}

void ofApp::set_window_size(){
    if( bUseMov ){
        mov_w = mov.getWidth();
        mov_h = mov.getHeight();
    }else{
        mov_w = img.getWidth();
        mov_h = img.getHeight();
    }
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
    midi_out.closePort();
}
