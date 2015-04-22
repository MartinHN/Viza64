//
//  Midi.cpp
//  ViZa
//
//  Created by martin hermant on 21/10/14.
//
//

#include "Midi.h"
#include "Camera.h"

#define MAX_MIDI_QUEUE 60

Midi * Midi::midi;
ofxMidiIn Midi::midiIn;
map<int,ofPoint> Midi::curpoints;
int Midi::midiModulo=12;
int Midi::midiRoot=24;
int Midi::midiMax = 60;
float Midi::radius = .05;
ofVec2f Midi::velScale(0,1);
bool Midi::hold;
bool Midi::link2Cam=true;

bool Midi::isReading=false;
swaplist Midi::msg;
map<int,Container*> Midi::curCont;




vector<string> Midi::getPorts(){
    midiIn.listPorts();
    
    return midiIn.getPortList();

}

void Midi::newMidiMessage(ofxMidiMessage& msgin){
    if(!isReading){
    if(msg.back->size()<MAX_MIDI_QUEUE){
        msg.back->push_back(msgin);
        ofLogVerbose("Midi",  "midicallback at " + ofToString(ofGetElapsedTimef()));
    }
    }
    
    else {
        ofLogWarning("Midi", "dropping MIDI" );
        
    }
    


   
}

void Midi::update(){
    isReading = true;
    msg.swap();
    isReading = false;

    
    
    for(vector<ofxMidiMessage>::iterator it = msg.front->begin() ; it!=msg.front->end() ; ++it){
        
        if(it->status==MIDI_NOTE_ON && it->velocity!=0){
            ofLogVerbose("Midi", "Midi pitch " + ofToString(it->pitch) );
            ofVec3f v (((it->pitch-midiRoot)%(midiModulo) )*1.0/((midiModulo-1)) , //
                       ((int)((it->pitch-midiRoot)/(midiModulo)) + 0.5)*1.0/((midiMax-midiRoot)/midiModulo),
                       ofMap(it->velocity, 127, 0, velScale.x, velScale.y));
            
            
            Container* cc = NULL;
            if(link2Cam){

                v.y = 1-v.y;
                Camera * locCam = Camera::mainCam;
                v.z = locCam->toCamZ(v.z-.5);
                v*=ofVec3f(locCam->viewport.width,locCam->viewport.height,1);
               
                v=locCam->screenToWorld(v,locCam->viewport);
            }
            else{
                v-= ofVec3f(.5);
            }
               curpoints[it->pitch] = v;
//            v+= ofVec3f(0.5,0.5,0);
            ofLogNotice("Midi") << it->pitch <<":" << v;
             cc =Physics::nearest(v ,radius);
                      if(cc!=NULL && cc->state==0){
                          ofLogVerbose("Midi","call play " + ofToString(ofGetElapsedTimef()));
                          cc->state = 1;
                          curCont[it->pitch]=cc;
            }
            
        }
        else if(it->status==MIDI_NOTE_OFF || (it->status==MIDI_NOTE_ON && it->velocity==0)   ){
            ofLogNotice("Midi") << it->pitch <<" off" ;
            curpoints.erase(it->pitch);
            if(curCont[it->pitch]!=NULL){
                if(!hold)curCont[it->pitch]->state=0;
            
                curCont.erase(it->pitch);
            }
        }
    
    }
    


    msg.front->clear();
    
}


void Midi::draw(){
    ofPushMatrix();
    ofPushStyle();
//    ofVec3f r = ofApp::cam.getOrientationEuler();
    if(radius>0){
    ofColor c = ofColor::seaGreen;
    c.a = 100;
    ofSetColor(c);
    for(map<int,ofVec3f>::iterator it = curpoints.begin(); it!= curpoints.end() ; ++it){

        ofDrawSphere(it->second,radius);
        
    }
    }
    ofPopStyle();
    ofPopMatrix();
}