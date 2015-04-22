//
//  GUIclass.cpp
//  ViZa
//
//  Created by martin hermant on 22/04/15.
//
//

#include "GUIClass.h"


GUIClass::GUIClass(){
    vector<string> dumb;
    //    dumb.push_back("lol");
    
    //Classes////////////////////
    
    
    canvas = new ofxUIScrollableCanvas(0,0,scrollW,800);
    canvas->setName("Class");
    canvas->setScrollableDirections(false, true);
    
    classNamesDDList = new ofxUIDropDownList("ClassNames",dumb,0,0,0,OFX_UI_FONT_SMALL);
    classValueDDList = new ofxUIDropDownList("ClassValues",dumb ,0,0,0,OFX_UI_FONT_SMALL);
    
    classColor = new ofxUIToggle("ColorIt",false,10,10);
    
    canvas->setSnapping(true);
    
    
    
    
    canvas->addWidgetDown(classNamesDDList);
    canvas->addWidgetRight(classValueDDList);
    canvas->addWidgetRight(classColor);

    
    
}


void GUIClass::setup(){
    if(Container::getClassNames().size()>0){
        classValueDDList->setValue(true);
        classNamesDDList->clearToggles();
        vector <string> tmpName = Container::getClassNames();
        
        classNamesDDList->addToggles(tmpName);
        classNamesDDList->getToggles()[0]->setValue(true);
        classNamesDDList->getToggles()[0]->triggerSelf();
        
    }
}


void GUIClass::guiEvent(ofxUIEventArgs & e){
    
    if(e.getParent() ==classNamesDDList){
        updateClassValue = true;
    }
    
    else if(e.getParent() == classValueDDList){
        Container::selectClass(e.getName() =="None"?"":classNamesDDList->getSelectedNames()[0],e.getName());
    }
    
    else if(e.widget == classColor ){
        
        Container::ClassValueStruct *curV = &Container::classeMap[classNamesDDList->getSelectedNames()[0]];
        int idx =0;
        for(Container::ClassValueStruct::iterator it = curV->begin() ; it != curV->end(); ++it ){
            
            ofColor nC;
            if(classColor->getValue())
                nC = ofColor(Container::getColorForId(idx),255*Container::stateColor[0].a);
            else
                nC = ofColor(ofColor::white,255*Container::stateColor[0].a);
            
            
            for(int i = 0 ; i < it->second.size() ; i++){
                Physics::updateOneColor(it->second[i],nC);
            }
            idx++;
        }
        
    }
}


void GUIClass::async(){
    if(updateClassValue){
        classValueDDList->clearToggles();
        vector<string> tmpC = Container::getClassValues(classNamesDDList->getSelected()[0]->getName());
        if(tmpC.size() > 1000){
            tmpC.resize(1000);
        }
        tmpC.insert(tmpC.begin(), "None");
        classValueDDList->addToggles(tmpC);
        
        ((ofxUIDropDownList*)canvas->getWidgetsOfType(OFX_UI_WIDGET_DROPDOWNLIST)[0])->open();
        ofxUIRectangle * r =((ofxUIDropDownList*)canvas->getWidgetsOfType(OFX_UI_WIDGET_DROPDOWNLIST)[0])->getRect();
        
        canvas->setDimensions(scrollW,(MAX(classValueDDList->getToggles().size(),classNamesDDList->getToggles().size())+2)*r->height);
        
        updateClassValue = false;
    }
    
}