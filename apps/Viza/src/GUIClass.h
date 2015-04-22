//
//  GUIclass.h
//  ViZa
//
//  Created by martin hermant on 22/04/15.
//
//

#ifndef __ViZa__GUIClass__
#define __ViZa__GUIClass__

#include "GUIUtils.h"

class GUIClass{
public:
    
    GUIClass();
    ~GUIClass(){};
    
    void setup();
    ofxUIScrollableCanvas * canvas;
    
    void guiEvent(ofxUIEventArgs & e);
    void async();
    
private:
    ofxUIDropDownList * classNamesDDList;
    ofxUIDropDownList * classValueDDList;
    ofxUIToggle * classColor;
        bool updateClassValue = false;
    int scrollW = 700;
};


#endif /* defined(__ViZa__GUIclass__) */
