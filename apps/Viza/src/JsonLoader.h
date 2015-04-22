//
//  JsonLoader.h
//  ViZa
//
//  Created by martin hermant on 09/10/14.
//
//

#ifndef __ViZa__JsonLoader__
#define __ViZa__JsonLoader__

#include <iostream>
//#include "stdio.h"

#include "BaseFileLoader.h"



#include "ofxJSONElement.h"



class JsonLoader : public BaseFileLoader{
 public:
    
    JsonLoader(const std::string& name);
    
    
    
    bool fillGlobalInfo(const string & annotationdir)override;
    bool fillContainerBlock(const string & annotationPath) override;
    
protected:
    bool loadFile() override;


    
private:
    
    void  crawl(Json::Value j,unordered_map<string,vector<float> > & RES);
};

#endif /* defined(__ViZa__JsonLoader__) */
