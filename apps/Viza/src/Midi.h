//
//  Midi.h
//  ViZa
//
//  Created by martin hermant on 21/10/14.
//
//

#ifndef __ViZa__Midi__
#define __ViZa__Midi__

#include <iostream>

#include "ofxMidi.h"
#include "Physics.h"
#include "Container.h"
//#include "ofApp.h"
class Container;


typedef struct swaplist{
    swaplist(){
        front = new vector<ofxMidiMessage>;
        back = new vector<ofxMidiMessage>;
    }
    
    void swap(){
        vector<ofxMidiMessage> * tmp = front;
        front = back;
        back = tmp;
    }
    vector<ofxMidiMessage> * front;
    vector<ofxMidiMessage> * back;
    
}swaplist;

class Midi:public ofxMidiListener {
    public :
    
    Midi(){midiIn.addListener(this);getPorts();midiIn.openPort(0);}
    ~Midi(){midiIn.closePort();
        midiIn.removeListener(this);}
    
    static Midi* instance(){
        if(midi==NULL){midi = new Midi;}
        return midi;
    };
    
    void setup();
    static void draw();
    static void update();
    vector<string> getPorts();
    void newMidiMessage(ofxMidiMessage& msg);
    
    static int midiModulo;
    static int midiRoot;
    static int midiMax;
    static float radius;
    static ofVec2f velScale;
    
    
    static map<int,ofPoint> curpoints;
    static map<int,Container * > curCont;
    static ofxMidiIn midiIn;
    

    static swaplist msg;
    static bool isReading;
    static bool hold;
    static bool link2Cam;
private:
    static Midi* midi;

};




#endif /* defined(__ViZa__Midi__) */
