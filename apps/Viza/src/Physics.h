//
//  Physics.h
//  ViZa
//
//  Created by martin hermant on 09/10/14.
//
//

#ifndef __ViZa__Physics__
#define __ViZa__Physics__


#include "ofMain.h"
#include "Container.h"
//#include "ofApp.h"
#include "ofxNearestNeighbour.h"
#include "FitEquation.h"
#include <iostream>

//#define COMPLEX_DESCRIPTOR_TEST
#define COMPLEX_DESCRIPTOR_TEST_NOISE .0

class Container;

class Physics{
    
public:
   
    
    static vector<ofVec3f> vs;
    static vector<ofVec2f> vScreen;
    static vector<ofFloatColor> cols;
    static vector<unsigned int> idxs;
    static ofVec3f curAttributesIndex;
    
    static vector<ofVec3f> * fits;
    static ofVbo vbo;
    static ofVbo fitsVbo;
    
    static ofParameter<ofVec3f> mins;
    static ofParameter<ofVec3f> maxs;
    
    static void updateVBO();
    static void resizeVBO();
    static void freeVbo();
    static void updateAllColors();
    static void reinitAllColors();
    static void updateAllColorsAlpha();
    static void updateOneColor(int idx,ofColor col,bool temp = false,bool callback =false);
    static void updateOnePos(int idx,ofVec3f & pos);
    static void orderByAttributes(string attr,int axe,int type);
    static void orderByClass(string className,int axe);
    static void updateVScreen();
    static bool applyFit();
    
    static Container * nearestOnScreen( ofVec3f mouse);
    static Container * hoveredOnScreen( ofVec2f mouse,float addRadius=2);
    static vector<Container *> containedInRect( ofRectangle rect);
    static Container* nearest(ofVec3f point,float radius = 0 );

    
    static vector<Container*> dragged;
    static vector<ofVec3f> originDrag;
    static void draw();
    vector<float> ks;
    static vector<unsigned int> * selectedIdx;
    static void setSelected(vector<unsigned int> * selected);
    static bool linkClasses;

   static bool drawFits;

    
//    
//    ofFbo pos;
//    ofFbo vel;
    
    
    string curAttribute;
    
    Physics * instance(){if(inst == NULL){inst = this;}    }
    
    void buildNetwork();
    void updatePhy(float time);
    static bool updateDrag(ofVec2f mouse);
    static void setFits(vector<ofVec3f> & fi);
    static void  applyEquation(FitEquation feq);
    static ofxNearestNeighbour3D kNN;
    static ofxNearestNeighbour2D kNNScreen;

private:
     static Physics* inst;
    

    
};
#endif /* defined(__ViZa__Physics__) */
