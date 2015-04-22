//
//  GUIAxes.cpp
//  ViZa
//
//  Created by martin hermant on 22/04/15.
//
//

#include "GUIAxes.h"



void GUIAxes::guiEvent(ofxUIEventArgs &e){
    string name = e.getName();
    
    
    int axe = getNumAxe(e.widget);
    // attributes and aggregator modification
    if(axe!=-1 && attr[axe]->getSelected().size()>0 && aggr[axe]->getSelected().size()>0 && scaleType[axe]->getSelectedIndeces().size()>0){
        string parentName = e.getParent()->getName();
        if(isAnAttributeList(e.widget)){
            shouldUpdateAggregator = axe;
        }
        else {
            string attrtmp =attr[axe]->getSelected()[0]->getName();
            string aggrtmp = aggr[axe]->getSelected()[0]->getName();
            if(aggrtmp=="None"){
                aggrtmp = "";
            }
            int scaletmp =scaleType[axe]->getSelectedIndeces()[0];
            Physics::orderByAttributes(attrtmp+"."+aggrtmp, axe, scaletmp);
            checkMinsMaxsChanged(name != "range"  );
        }
        
    }
    
    
    // mins maxs modifications
    else if (e.getKind() == OFX_UI_WIDGET_NUMBERDIALER){
        axe = getNumAxe(e.widget);
        float s =((ofxUINumberDialer*)e.widget)->getValue();
        
        ofVec3f mask(axe==0?1:0,axe==1?1:0,axe==2?1:0);
        if(name.substr(0,name.length()-1)=="min"){
            Physics::mins = s*mask + (-mask+ofVec3f(1))*Physics::mins;
        }
        if(name.substr(0,name.length()-1)=="max"){
            Physics::maxs = s*mask + (-mask+ofVec3f(1))*Physics::maxs;
        }
        scaleType[axe]->getToggles()[2]->setValue(true);
        scaleType[axe]->getToggles()[2]->triggerSelf();
        Physics::orderByAttributes(attr[axe]->getSelected()[0]->getName()+"."+aggr[axe]->getSelected()[0]->getName(), axe, scaleType[axe]->getSelectedIndeces()[0]);
        
    }
}

// Async GUI modifications
void GUIAxes::async(){
    
    //update Aggregator list for Selected Attribute in given Axe
    if(shouldUpdateAggregator!=-1){
        int axe = shouldUpdateAggregator;
        string attrtmp =attr[axe]->getSelected()[0]->getName();
        string oldAggr =aggr[axe]->getSelected()[0]->getName();
        aggr[axe]->clearToggles();
        vector<string>  newAggr = Container::getAggregators(attrtmp);
        int idx = ofFind(newAggr, oldAggr);
        if(idx == newAggr.size())idx = 0;
        aggr[axe]->addToggles(newAggr);
        aggr[axe]->getToggles()[idx]->setValue(true);
        aggr[axe]->getToggles()[idx]->triggerSelf();
        
        shouldUpdateAggregator = -1;
    }
}


// update numboxes for min max  of each attributes/aggregator
void GUIAxes::checkMinsMaxsChanged(bool updateVal){
    
    for(int i = 0 ; i < 3 ; i++){
        
        if(attr[i]->getSelected().size()*aggr[i]->getSelected().size()>0  ){
            int idxAttr =getFullAttrIdx(attr[i]->getSelected()[0]->getName(),aggr[i]->getSelected()[0]->getName());
            max[i]->min = Container::mins[idxAttr] - Container::stddevs[idxAttr];
            max[i]->max = Container::maxs[idxAttr]+ Container::stddevs[idxAttr];
            min[i]->min = Container::mins[idxAttr]- Container::stddevs[idxAttr];
            min[i]->max = Container::maxs[idxAttr]+ Container::stddevs[idxAttr];
            if(updateVal){
                max[i]->setValue(Physics::maxs.get()[i]);
                min[i]->setValue(Physics::mins.get()[i]);
            }
        }
    }
    
}

// get Attr idx in Data world
int GUIAxes::getFullAttrIdx(const string & attr,const string &  aggr ){
    string attrN = attr+"."+aggr;
    bool found = false;
    for (vector<string> ::iterator it = Container::attributeNames.begin(); it!=Container::attributeNames.end(); ++it) {
        if(*it==attrN){
            found = true;
            break;
        }
        
    }
    if(!found){
        attrN = ofSplitString(attrN, ".")[0];
    }
    return ofFind(Container::attributeNames, attrN );;
}



bool GUIAxes::isAnAttributeList(ofxUIWidget * w){
    for(int i = 0 ; i < 3 ; i++){
        if(w == attr[i])return true;
    }
    return false;
}

int GUIAxes::getNumAxe(ofxUIWidget* w){
    for (int i = 0 ; i < 3 ; i++){
        if(w == attr[i]||
           w == aggr[i]||
           w == max[i]||
           w == min[i]||
           w== scaleType[i]
           
           ){
            return i;
        }
    }
    return -1;
}

string GUIAxes::numToAxe(int i){
    switch(i){
        case 0:
            return "X";
        case 1:
            return "Y";
        case 2:
            return "Z";
        default:
            break;
    }
    return "";
}




GUIAxes::GUIAxes(){
    
    shouldUpdateAggregator = -1;
    
    
    //AXES/////////////
    canvas = new ofxUISuperCanvas("Axes",0,0,900,150);
    canvas->setName("Axes");
    
    
    coordinateTypeNames.push_back("cartesian");
    coordinateTypeNames.push_back("cylindrical");
    coordinateTypeNames.push_back("Toroidal");
    coordinateTypeNames.push_back("spherical");
    
    //Hack for memory corruption
    attrNames.clear();
    aggrNames.clear();
    
    for(int i = 0  ;i< 10 ; i++){
        attrNames.push_back(ofToString(i)+" attr");
        aggrNames.push_back(ofToString(i)+" aggr");
        
        
    }
    
    
    typeScales.push_back("min/max");
    typeScales.push_back("standard deviation");
    typeScales.push_back("range");
    
    for(int i = 0 ; i < 3 ; i++){
        attr[i] =           new ofxUIDropDownList("Attribute"+numToAxe(i), attrNames,150,0,0,OFX_UI_FONT_SMALL);
        aggr[i] =         new ofxUIDropDownList("Aggregate"+numToAxe(i), aggrNames,150,0,0,OFX_UI_FONT_SMALL);
        scaleType[i] =    new ofxUIDropDownList("scaleType"+numToAxe(i), typeScales,150,0,0,OFX_UI_FONT_SMALL);
        min[i] =          new ofxUINumberDialer(0,1,0.0f,4,"min"+numToAxe(i),OFX_UI_FONT_SMALL);
        max[i] =          new ofxUINumberDialer(0,1,1.0f,4,"max"+numToAxe(i),OFX_UI_FONT_SMALL);
        
    }
    
    coordinateType =  new ofxUIDropDownList("coordinateType",coordinateTypeNames,150,0,0,OFX_UI_FONT_SMALL);
    coordinateType->activateToggle("cartesian");
    
    clampValues = new ofxUIToggle("clampValues",false,10,10);
    
    
    // place
    
    
    
    for(int i=0;i<3;i++){
        canvas->addWidgetDown(attr[i]);
        canvas->addWidgetRight(aggr[i] );
        canvas->addWidgetRight(scaleType[i] );
        canvas->addWidgetRight(min[i] );
        canvas->addWidgetRight(max[i] );
    }
    canvas->addWidgetDown(coordinateType);
    canvas->addWidgetRight(clampValues);
    
    
    
    
    vector<ofxUIWidget*> ddls = canvas->getWidgetsOfType(OFX_UI_WIDGET_DROPDOWNLIST);
    for(int i = 0 ; i < ddls.size(); i++){
        ((ofxUIDropDownList*) ddls[i])->setAutoClose(true);
        ((ofxUIDropDownList*) ddls[i])->setShowCurrentSelected(true);
    }
    
    
    
}


void GUIAxes::setup(){
    
    coordinateType->triggerEvent(coordinateType->getToggles()[0]);
    
    attrNames.clear();
    aggrNames.clear();
    
    
    
    
    if(Container::attributeNames.size()>0){
        
        for(vector<string>::iterator it = Container::attributeNames.begin() ; it != Container::attributeNames.end() ;++it){
            vector <string> nnn =ofSplitString(*it, ".");
            {
                bool found = false;
                for(vector<string>::iterator itt = attrNames.begin() ; itt!= attrNames.end() ; ++itt){
                    if(*itt==nnn[0]){
                        found = true;
                        break;
                    }
                }
                if(!found)attrNames.push_back(nnn[0]);
            }
            if(nnn.size()>1 ){
                bool found = false;
                for(vector<string>::iterator itt = aggrNames.begin() ; itt!= aggrNames.end() ; ++itt){
                    if(*itt==nnn[1]){
                        found = true;
                        break;
                    }
                }
                if(!found)aggrNames.push_back(nnn[1]);
            }
        }
        
        
        
        for(int i = 0 ; i < 3 ; i++){
            attr[i]->clearToggles();
            attr[i]->addToggles(attrNames);
            aggr[i]->clearToggles();
            aggr[i]->addToggles(aggrNames);
            
            attr[i]->getToggles()[i]->setValue(true);
            aggr[i]->getToggles()[0]->setValue(true);
            scaleType[i]->getToggles()[i==0?0:1]->setValue(true);
            
            
            scaleType[i]->getToggles()[1]->triggerSelf();
            attr[i]->getToggles()[i]->triggerSelf();
            aggr[i]->getToggles()[0]->triggerSelf();
        }
        
    }
    
    float ddSize = 100;
    
    for(int i = 0 ; i < 3;i++){
        attr[i]->getToggles()[i]->triggerSelf();
    }
    
    
}