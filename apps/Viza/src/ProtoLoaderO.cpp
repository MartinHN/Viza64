//
//  ProtoLoader.cpp
//  ViZa
//
//  Created by martin hermant on 08/04/15.
//
//

#include "ProtoLoader.h"

unordered_map<string,vector<string > > ProtoLoader::classes;
// can be partially filled
vector<Container::SongMeta>  ProtoLoader::songs;




ProtoLoader::ProtoLoader(const std::string& name):BaseFileLoader(name){
    
}

bool ProtoLoader::fillGlobalInfo(const string & annotationDir){
    Viza::GlobalList glob;
    open(annotationDir+"GlobalViza.viza",glob);
    
    // fill attributeNames
    globalInfo.attributeNames.resize(glob.attributesnames_size());
    for(int i = 0; i < glob.attributesnames_size() ; i++){
        //        GlobalInfo
        globalInfo.attributeNames[i] = glob.attributesnames(i);
    }
    
    globalInfo.totalContainers = glob.numcontainer();
    globalInfo.hasMeta = true;
    
    
    
    // local indexing
    // fill songs
    songs.resize(glob.songs_size());
    for(int i = 0; i < glob.songs_size() ; i++){
        //        GlobalInfo
        songs[i].length = glob.songs(i).length();
        songs[i].audioPath = glob.songs(i).audiopath();
        songs[i].numSlices = glob.songs(i).numslice();
        songs[i].idx = i;
    }
    
    // fill classes
//    classes.reserve(glob.classes_size());
    for(int i = 0; i < glob.classes_size() ; i++){
        //        GlobalInfo
        classes[glob.classes(i).name()] = vector<string>();
        classes[glob.classes(i).name()].resize(glob.classes(i).values_size());
        for (int j = 0 ; j < glob.classes(i).values_size() ; j++){
            classes[glob.classes(i).name()][j] = glob.classes(i).values(j);
        }
    }
    
    
    
    
    
}



bool ProtoLoader::fillContainerBlock(const string & annotationPath){
    if(init){
        init = false;
    }
    Viza::ContainerList protobuf;
    open(annotationPath,protobuf);
    
    containerBlock.numElements = protobuf.containers_size();
    int locIdx = protobuf.songidx();
    containerBlock.song = songs[locIdx];

    
    
}


bool ProtoLoader::loadFile(){
    Viza::ContainerList protobuf;
    open(containerBlock.parsedFile,protobuf);
    
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    
    
    
    int containerNum = containerBlock.containerIdx;
    for(int i = 0 ; i < containerBlock.numElements ; i++){
        Viza::Container cont = protobuf.containers(i);
        Container::containers[containerNum] = new Container(  cont.slicebegin(), cont.sliceend(), containerNum,cont.sliceidx());
        for(int j = 0 ; j < cont.attributevalues_size() ; j++){
            Container::containers[containerNum]->setAttribute(j,cont.attributevalues(j));
        }
        
        int j = 0;
        for(unordered_map<string , vector<string> >::iterator it = classes.begin();it!= classes.end();++it){
            int classI = cont.classes(j);
            if(classI>it->second.size()){
            
                ofLogError()<< it->first << "/" <<containerBlock.parsedFile;
            }
            else{
            Container::containers[containerNum]->setClass(it->first,it->second[classI]);
            }
            
        }
        
        
        containerNum++;
        
    }
    
    
    
}

bool ProtoLoader::open(const string & p,google::protobuf::Message & msg){
    ofFile buf;
    if (!buf.open(p,ofFile::ReadOnly)) {
        ofLogError("ProtoLoader", p + ": File not found.  Creating a new file.");
        return false;
    }
    else if (!msg.ParseFromIstream(&buf)) {
        ofLogError("ProtoLoader", "Failed to parse file : " + p);
        return false;
    }
    return true;
}

