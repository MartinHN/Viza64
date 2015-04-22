//
//  Container.cpp
//  ViZa
//
//  Created by martin hermant on 09/10/14.
//
//

#include "Container.h"
//#include "ofxTweener.h"





vector<Container*> Container::containers;
vector< vector<unsigned int> > Container::songsContainers;
vector<Container::SongMeta > Container::songMeta;
int Container::numContainer = 0;

pair<string,string> Container::selectedClass;
ofMutex Container::staticContainerMutex;

int Container::hoverIdx;
bool Container::colorInit = true;




float Container::radius = 10;
ofFloatColor Container::stateColor[4];





void Container::registerListener(){
    
    
    for(int i = 0 ; i < containers.size() ; i++){
        containers[i]->state = ofParameter<float>();
        containers[i]->state.addListener(containers[i], &Container::setState);
        containers[i]->state = 0;
        
        containers[i]->isSelected = ofParameter<bool>();
        containers[i]->isSelected.addListener(containers[i], &Container::setSelected);
        containers[i]->isSelected = false;
        
        
        containers[i]->isHovered = ofParameter<bool>();
        containers[i]->isHovered.addListener(containers[i], &Container::setHovered);
        containers[i]->isHovered = false;
        
        
    }

    
    
}

void Container::setSelected(bool & s){
    Physics::updateOneColor(globalIdx,getColor(),true,s==0);
    
}


void Container::setState(float & s){
    Physics::updateOneColor(globalIdx,getColor(),s==1,s==0);
    if(s<=1){AudioPlayer::instance()->Play(*this,(int)s);}
    
    
}

void Container::setHovered(bool & s){

    Physics::updateOneColor(globalIdx,getColor(),true,!s);
    
}

void Container::selectClass(string _name,string _value){
    if(selectedClass!=pair<string,string>("","")){
        vector<unsigned int> conts = Container::classeMap[selectedClass.first][selectedClass.second];
        for(vector<unsigned int>::iterator it = conts.begin() ; it!=conts.end() ; ++it){
            containers[(*it)]->isSelected = false;
            
        }
    }

    if(_name!=""&& _value!="" && classeMap.count(_name)>0 && classeMap[_name].count(_value)>0){
        selectedClass = pair<string,string>(_name,_value);
        vector<unsigned int> conts = classeMap[_name][_value];
        for(vector<unsigned int>::iterator it = conts.begin() ; it!=conts.end() ; ++it){
            containers[(*it)]->isSelected = true;
        }

        Physics::setSelected(&Container::classeMap[_name][_value]);
        Physics::updateAllColorsAlpha();
    }
    else{

        Physics::setSelected(NULL);
        Physics::reinitAllColors();
        selectedClass=pair<string,string>("","");
    }
}

bool Container::hoverContainer(int  idx){
    if(idx!=hoverIdx){
        if(hoverIdx!=-1)containers[hoverIdx]->isHovered= false;
        hoverIdx=idx;
        if(hoverIdx!=-1)containers[hoverIdx]->isHovered= true;
        return true;
    }
    return false;
}


void Container::clearAll(){
    hoverIdx = -1;
    AttributeContainer::clearAll();
    ClassContainer::clearAll();
    
    containers.clear();

    songsContainers.clear();
    songMeta.clear();

    

    
    
}

string Container::getFilename() const{
   return songMeta[songIdx].name;
//    for(map<string,vector<unsigned  int> >::iterator it = songsContainers.begin() ; it!=songsContainers.end() ; ++it){
//        for (int i = 0 ; i < it->second.size();i++){
//            if(containers[it->second[i]]==this){
//                return it->first;
//            }
//        }
//        
//        }
//    return "not Found";
}

string Container::getAudioPath() const{
    return songMeta[songIdx].audioPath;
}
string Container::getAnnotationPath()const{
    return songMeta[songIdx].annotationPath;
}



ofFloatColor Container::getColor() const{
    if(colorInit){
        Container::stateColor[0] = ofFloatColor::white;
        Container::stateColor[0].a=.3;
        Container::stateColor[1] =ofFloatColor::red;
        Container::stateColor[1].a=.6;
        Container::stateColor[2] =ofFloatColor::green;
        Container::stateColor[2].a=.5;
        Container::stateColor[3] =ofFloatColor::white;
        Container::stateColor[3].a=1;
        colorInit = false;
    }
    ofColor c =ofColor(stateColor[(int)state==1?1:isHovered?3:isSelected?2:0]);

    return c;
}



ofVec3f Container::getPos() const{
    return Physics::vs[globalIdx]+.5;
}

