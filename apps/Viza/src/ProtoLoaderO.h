//
//  ProtoLoader.h
//  ViZa
//
//  Created by martin hermant on 08/04/15.
//
//

#ifndef __ViZa__ProtoLoader__
#define __ViZa__ProtoLoader__



#include "ofMain.h"
#include "BaseFileLoader.h"
#include <iostream>
#include <fstream>

#undef TYPE_BOOL
#include "VizaImpl.pb.h"
#include "VizaGlobal.pb.h"

class ProtoLoader : public BaseFileLoader{
public:
    
    ProtoLoader(const std::string& name);
    
    
    bool fillContainerBlock(const string & annotationPath) override;
    bool fillGlobalInfo(const string & annotationdir) override;

    

protected:
    bool loadFile() override;
    
    bool open(const string & p,google::protobuf::Message & msg);
   static  unordered_map<string,vector<string > > classes;
    // can be partially filled
   static  vector<Container::SongMeta>  songs;
    
    
    
};


#endif /* defined(__ViZa__ProtoLoader__) */
