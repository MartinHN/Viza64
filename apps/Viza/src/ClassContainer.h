//
//  ClassContainer.h
//  ViZa
//
//  Created by martin hermant on 23/01/15.
//
//

#ifndef __ViZa__ClassContainer__
#define __ViZa__ClassContainer__


#include "ofMain.h"


class ClassContainer{
public:
    
    typedef map<string,vector <unsigned int> > ClassValueStruct;
    typedef map < string,ClassValueStruct  >  ClassMapStruct;
    
    static ClassMapStruct classeMap;
    
    
//    map < string, string > classes;
    
    

    ClassContainer(){};
    virtual  ~ClassContainer(){};
    

    void setClass(const string cl,const string  v);

    static const vector<string> getClassValues(const string & cName);
    static const vector<string> getClassNames();
    const string getClass(const string & cName);
    
    static vector<ofColor> classColor;
    static ofColor getColorForId(int id);
    static void initColors();
    
    static void clearAll();
private:
    static ofMutex ClassStaticMutex;
    
};

#endif /* defined(__ViZa__ClassContainer__) */
