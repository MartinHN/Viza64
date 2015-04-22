//
//  GUI.h
//  ViZa
//
//  Created by martin hermant on 14/10/14.
//
//

#ifndef __ViZa__GUI__
#define __ViZa__GUI__

#define MYPARAM(nom,init,min,max) nom.setName(#nom);nom.setMin(min);nom.setMax(max);settings.add(nom);nom=init;


#include "GUIUtils.h"
#include "GUIAxes.h"
#include "GUIClass.h"


#include "Camera.h"
#include "Midi.h"
#include "SliceFitter.h"
#include "ofxTSNE.h"

class GUI{
public:

    GUI();
    ~GUI();
    
    GUIAxes guiAxe;
    GUIClass guiClass;
    
    ofxUITabBar * global;
    



    
    ofxUISuperCanvas * logCanvas;
    ofxUITextArea * Logger;
    
    ofxUISuperCanvas * viewCanvas;
    ofxUISlider * alphaView;
    ofxUIToggle * selBrightest;
    ofxUIToggle * linkClasses;
    ofxUIToggle * orthoCam;
    ofxUISlider * pointSize;
    ofxUIToggle * isClipping;
    ofxUIToggle * show2dViews;
    ofxUISlider *fishEyeStrength;
    ofxUISlider *fishEyeRadius;

    
    ofxUISuperCanvas * fitterCanvas;
    ofxUISlider * samplingPct;
    ofxUIDropDownList * typeOfFit;
    ofxUIToggle * keepResults;
    ofxUIButton * fitIt;
    ofxUIButton * applyIt;

    
    ofxUISuperCanvas * clusterCanvas;
    ofxUIButton * findClusters;
    ofxUISlider *clusterEps;
    ofxUISlider * clusterMinK;
    ofxUISlider * minClusterSize;
    ofxUIToggle * tSNE2D;
    ofxUISlider * tSNEPerp;
    ofxUISlider * tSNEtheta;
    ofxUIButton * findtSNE;
    ofxUIButton * applyTsne;
    
    ofxUISuperCanvas * midiCanvas;
    ofxUIDropDownList * midiPorts;
    ofxUIRangeSlider * midiVel;
    ofxUISlider * midiRadius;
    ofxUIToggle * midiHold;
    ofxUIToggle * midiLink2Cam;
    ofxUIToggle * link2x;
    
    
    ofxUISuperCanvas * playBack;
    ofxUIToggle * continuousPB;
    ofxUIToggle * holdPB;
    
    
    
    int pad=50;
    
    
     void guiEvent(ofxUIEventArgs &e);
    
    static GUI * instance(){if(inst == NULL){inst = new GUI;} return inst;   }
    
    void setup();
    void registerListener();

    
    static GUI * inst;
    int lastFramenum;
    string lastName;
    
    
    void checkMinsMaxsChanged(bool updateVal);

    static void LogIt(string s );
    bool isOver(int x,int y);
    
    void update(ofEventArgs & a);
private:

    void asyncGUI();

    void checkOverlapingDDL(ofxUIEventArgs & e);
    
    
};



#endif /* defined(__ViZa__GUI__) */
