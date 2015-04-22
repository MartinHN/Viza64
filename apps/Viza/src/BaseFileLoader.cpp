//
//  BaseFileLoader.cpp
//  ViZa
//
//  Created by martin hermant on 07/04/15.
//
//

#include "BaseFileLoader.h"


#include "JsonLoader.h"
#include "ProtoLoader.h"



vector<string> BaseFileLoader::attrSubset(0);
BaseFileLoader::loaders_map_type * BaseFileLoader::loadersMap;
bool BaseFileLoader::init ;




BaseFileLoader::BaseFileLoader(const std::string& name):Poco::Task(name){
    
}

BaseFileLoader::~BaseFileLoader(){
    
}

void BaseFileLoader::runTask(){
    
    
    
    loadFile();
    
    {
        ofScopedLock lock (Container::staticContainerMutex);
        
        int locSongIdx = containerBlock.songIdx;
        int locContIdx = containerBlock.containerIdx;
        Container::songMeta[locSongIdx] = containerBlock.song;
        string name = containerBlock.song.name;
        Container::songMeta[locSongIdx].idx = locSongIdx;
        Container::songMeta[locSongIdx].annotationPath=containerBlock.song.annotationPath;
        
        for (int i =  locContIdx ; i < locContIdx+containerBlock.song.numSlices ; i++){
            Container::songsContainers[locSongIdx].push_back(Container::containers[i]->globalIdx);
            Container::containers[i]->songIdx = locSongIdx;
        }
        
        if(!globalInfo.hasMeta){
            for (int i =  locContIdx ; i < locContIdx+containerBlock.song.numSlices ; i++){
                Container::containers[i]->setClass("songName",containerBlock.song.name);
            }
            
        }
        locContIdx+=containerBlock.song.numSlices;
        locSongIdx++;
        
        
        
        
    }
    
    
    
}


void BaseFileLoader::linkLoaders(){
    getMap()->insert(std::make_pair("json", &createT<JsonLoader>));
    getMap()->insert(std::make_pair("vizad", &createT<ProtoLoader>));
}

BaseFileLoader * BaseFileLoader::getLoader(const string &extension,const string & name){
    
    loaders_map_type::iterator it = getMap()->find(extension);
    if(it == getMap()->end())
        return 0;
    return it->second(extension + " : " + name);
    
}

BaseFileLoader::loaders_map_type * BaseFileLoader::getMap() {
    // never delete'ed. (exist until program termination)
    // because we can't guarantee correct destruction order
    if(!loadersMap) { loadersMap = new loaders_map_type; }
    return loadersMap;
}
