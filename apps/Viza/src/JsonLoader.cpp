//
//  JsonLoader.cpp
//  ViZa
//
//  Created by martin hermant on 09/10/14.
//
//

#include "JsonLoader.h"
#define NUM_BEST 30


JsonLoader::JsonLoader(const std::string& name):BaseFileLoader(name){
    
}



bool JsonLoader::loadFile(){
    
    int containerNum = containerBlock.containerIdx;
    
    ofxJSONElement json;
    
    //only one file at time
    Container::SongMeta song = containerBlock.song;
    string name = containerBlock.song.name;
    
    json.open(song.annotationPath);
    
    
    
    unordered_map<string,vector<float> > onsets;
    crawl(json.get("values",0),onsets);
    
    
    
    //
    if(json["slice"]["time"].size()>0){
        
        
        map<string,vector<string> > classMap;
        // parse Class
        Json::Value classes =json.get("Class","");
        for (Json::Value::iterator it = classes.begin() ; it != classes.end() ; ++it ){
            string className = it.memberName();
            string classValue;
            if((*it).isString()){
                classValue = (*it).asString();
            }
            else if((*it).isArray()){
                ofLogError("JsonLoader","class Array not Supported Yet");
            }
            else ofLogError("JsonLoader", "wrongClass defined for " +className);
            if(!classMap.count(className))classMap[className] = vector<string>();
            classMap[className].push_back(classValue);
            
        }
        
        // add a container per slice
        // ATM only one slice domain is supported, so we need to have one of each descriptor value per slice for all descriptors
        
        // iterate over slices
        int sliceNum = 0;
        for(Json::Value::iterator it  = json["slice"]["time"].begin() ; it!= json["slice"]["time"].end() ; ++it){
            float begin = (*it)[0].asFloat();
            float end = (*it)[1].asFloat();
            
            Container::containers[containerNum] = new Container(begin,end,containerNum,sliceNum);
            for(unordered_map<string,vector<float> >::iterator itt=onsets.begin();itt!=onsets.end() ; ++itt){
                if(itt->first!="slice.time" && (attrSubset.size()==0 || ofContains(attrSubset,itt->first ))){
                    Container::containers[containerNum]->setAttribute(itt->first,itt->second[sliceNum]);
                }

                
            }
            // Add Meta Info
                Container::containers[containerNum]->setAttribute("length",end-begin);
                Container::containers[containerNum]->setAttribute("startTime",begin);
                Container::containers[containerNum]->setAttribute("relativeStartTime",containerBlock.song.length!=0?begin/(containerBlock.song.length):0);
            
            
            for(map<string,vector<string> >::iterator itc = classMap.begin() ; itc !=classMap.end() ; ++itc){
                Container::containers[containerNum]->setClass(itc->first, itc->second[sliceNum]);
            }
            
            sliceNum++;
            
            containerNum++;
            
        }
        
        
        
        
        
    }
    //            json.clear();
}


bool JsonLoader::fillContainerBlock(const string &  annotationPath){
    
    ofxJSONElement json;
    json.open(annotationPath);
    ofxJSONElement::Value onsets = json["values"];
    
    
    containerBlock.numElements = json["slice"]["time"].size();
    //look for audio path in json file
    string apath = json.get("audiopath","").asString();
    if(apath!=""){
        
        if (apath[0] == '.' && apath[1] == '.'){
            ofFile f(annotationPath);
            ofFile ddd = ofFile(f.getEnclosingDirectory() + apath);
            apath =  ddd.path();
        }
        string name = apath.substr(apath.find_last_of("/")+1);
        containerBlock.song = Container::SongMeta();
        containerBlock.song.length = json["slice"]["time"][containerBlock.numElements][1].asFloat();
        containerBlock.song.audioPath = apath;
        containerBlock.song.numSlices= containerBlock.numElements;
        containerBlock.song.annotationPath = annotationPath;
        containerBlock.song.name = name;
        
    }
    
    
    
    
    
    
    
    
    
}

bool JsonLoader::fillGlobalInfo(const string & annotationdir){
    
    globalInfo.hasMeta = false;
    
    
    ofDirectory folder;
    folder.open(annotationdir);
        folder.allowExt("json");
    
    folder.listDir();
    
    
    ofFile sampleFile = folder.getFile(0);
    
    ofxJSONElement json;
    json.open(sampleFile.path());
    ofxJSONElement::Value onsets = json["values"];
    
    
    // fill attribute Names
    ofxJSONElement::Value::Members names = onsets.getMemberNames();
    for(int i = 0 ; i < names.size() ; i++){
        string attrname = names[i];
        
        Json::Value::iterator itB = onsets[attrname].begin();
        Json::Value::iterator itE = onsets[attrname].end();
        for (Json::Value::iterator it = itB ; it != itE ; ++it ){
            
            string attrtype =it.memberName();
            globalInfo.attributeNames.push_back(attrname + "." + attrtype);
        }
        
    }
    
    // evaluate total number of containers kind of dangerous...
    int testedJSON = 10;
    bool safe_estimation = false;
    int estimation = 0;
    int i =0;
    for( ; i < testedJSON ; i++){
        // we have tested all json
        if(i>=folder.size()){
            safe_estimation = true;
            i--;
            break;
        }
        ofxJSONElement jsont;
        int numFile=i;
        
        string pathh=folder.getFile(numFile,ofFile::ReadOnly).path();
        
        
        if(!jsont.open(pathh)){
            ofLogError("JsonLoader", "cant import :" + folder.getFile(numFile).path());
        }
        estimation=max( jsont["slice"].size(),estimation);
        
    }
    estimation*=folder.size();
    if(!safe_estimation)
        estimation *= 2;
    globalInfo.totalContainers=estimation;
    
    
}




void JsonLoader::crawl(Json::Value j,unordered_map<string,vector<float> > & RES){
    
    
    Json::Value::iterator itB = j.begin();
    Json::Value::iterator itE = j.end();
    for (Json::Value::iterator it = itB ; it != itE ; ++it ){
        string attrname =it.memberName();
        Json::Value::iterator ittB = (*it).begin();
        Json::Value::iterator ittE = (*it).end();
        for (Json::Value::iterator itt = ittB ; itt != ittE ; ++itt ){
            string attrtype =itt.memberName();
            Json::Value::iterator itttB = (*itt).begin();
            Json::Value::iterator itttE = (*itt).end();
            RES[attrname+"."+attrtype] = std::vector<float>();
            RES[attrname+"."+attrtype].reserve((*itt).size());
            for (Json::Value::iterator ittt = itttB ; ittt != itttE ; ++ittt ){
                if((*ittt).isNumeric())
                    RES[attrname+"."+attrtype].push_back((*ittt).asFloat());
                else if ((*ittt).isArray()){
                    int i = 0;
                    for (Json::Value::iterator itttt = (*ittt).begin() ; itttt != (*ittt).end() ; ++itttt ){
                        RES[attrname+"."+attrtype+"."+ofToString(i)].push_back((*itttt).asFloat());
                        i++;
                    }
                    
                }
                
            }
            
        }
        
    }
    
}


