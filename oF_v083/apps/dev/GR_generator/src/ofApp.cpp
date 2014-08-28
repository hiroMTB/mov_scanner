#include "ofApp.h"


void ofApp::setup(){


    int ch_num = 16;
    int prm_num = 10;
    
    xml.addChild("remotedescription");
    xml.setTo("remotedescription");
    xml.setAttribute("version", "1.1");
    
    xml.addChild("ctrltable");
    xml.setTo("ctrltable");
    xml.setAttribute("name", "Standard MIDI");
    
    for(int ch=1; ch<=ch_num; ch++){
        for(int prm=1; prm<=prm_num; prm++){
            ofXml cc;
            cc.addChild("ctrl");
            string cc_name = "ch" + ofToString(ch) + "-Prm" + ofToString(prm);
            cc.addValue("name", cc_name);
            cc.addValue("stat", "176");
            cc.addValue("chan", ofToString(ch-1)); // cubase midi ch start from 0
            cc.addValue("addr", ofToString(102 + prm -1));     // this is Midi CC number
            cc.addValue("max", "127");
            cc.addValue("flags", "1");
            
            xml.addXml(cc);
        }
    }
    
    xml.setToParent(1);
    
    int cubase_offset_ch = 16;
    xml.addChild("bank");
    xml.setTo("bank");
    xml.setAttribute("name", "VST 1-16");
    for(int ch=1; ch<=ch_num; ch++){
        for(int prm=1; prm<=prm_num; prm++){
            ofXml entry;
            entry.addChild("entry");
            entry.setTo("entry");
            string cc_name = "ch" + ofToString(ch) + "-Prm" + ofToString(prm);
            entry.setAttribute("ctrl", cc_name);
            
            
            ofXml v;
            v.addChild("value");
            v.setTo("value");
            v.addValue("device", "Mixer");
            
            v.addValue("chan", ofToString(ch+cubase_offset_ch));
            switch (prm) {
                case 1:
                    v.addValue("name", "panner:panX");
                    break;
                    
                default:
                    v.addValue("name", "sends/slot"+ofToString(prm-1)+":volume");
                    break;
            }
            
            v.addValue("flags", "0");
            
            entry.addXml(v);
            xml.addXml(entry);
        }
    }
    
    // save
    string path = "Cubase_Generic_Remote_" + ofGetTimestampString()+ ".xml";
    //xml.save(path);
    
    string s = xml.toString();
    s.insert(0, "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");
    ofBuffer buf(s);
    ofBufferToFile(path, buf);
    
}


void ofApp::draw(){

    ofBackground(0);
    ofSetColor(0, 230, 0);
    string s = xml.toString();
    ofDrawBitmapString(s, 10, 10);
}
