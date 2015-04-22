//
//  GUIAxes.h
//  ViZa
//
//  Created by martin hermant on 22/04/15.
//
//

#ifndef __ViZa__GUIAxes__
#define __ViZa__GUIAxes__

#include "ofMain.h"
#include "GUIUtils.h"

class GUIAxes{
    public :
    GUIAxes();
    ~GUIAxes(){};
    
    ofxUISuperCanvas *canvas;
    ofxUIDropDownList * attr[3], *aggr[3];
    ofxUIDropDownList *scaleType[3];
    ofxUINumberDialer * min[3],*max[3];
    ofxUIDropDownList * coordinateType;
    ofxUIToggle* clampValues;
    
    
    void guiEvent(ofxUIEventArgs &e);
    void checkMinsMaxsChanged(bool updateVal);
    void setup();
    void async();
    
    vector<string> attrNames;
    vector<string> aggrNames;
    
    private :
    
    vector<string> coordinateTypeNames;
    vector<string> typeScales;
    int shouldUpdateAggregator;
    
    bool isAnAttributeList(ofxUIWidget * w);
    int getNumAxe(ofxUIWidget* w);
    string numToAxe(int i);
    int getFullAttrIdx(const string & attr,const string &  aggr );
    
    
    
};

#endif /* defined(__ViZa__GUIAxes__) */
