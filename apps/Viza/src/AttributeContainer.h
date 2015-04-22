//
//  AttributeContainer.h
//  ViZa
//
//  Created by martin hermant on 23/01/15.
//
//

#ifndef __ViZa__AttributeContainer__
#define __ViZa__AttributeContainer__

#include "DSP.h"
#include "ofMain.h"




class Container;

class AttributeContainer{
    
public:
    
    static vector<string> attributeNames;
    static float * normalizedAttributes;
    static vector<  int > fixAttributes;
    static float * attributesCache;
    
    static float * reducedAttributeCache;
    static vector < int> reducedAttributesNamesIdx;
    
    
    
    static int attrSize;
    static int numAttr;
    
    static vector<float > mins;
    static vector<float> maxs;
    static vector<float > means;
    static vector<float > stddevs;
    
    
    static vector<unsigned int > total;
    
    

    AttributeContainer(){};
    AttributeContainer(unsigned int curI);

    virtual ~AttributeContainer(){};
    
    float & getAttributes(int i,bool normalized=false);
    void setAttribute(const string &n,const float v);
    void setAttribute(const int idx, const float v);
    
    static void preCacheAttr(vector<string> & attr);
    
    static vector<string> getAggregators(string & s);

    static void clearAll();
    
        static void CacheNormalized(int numCount);
    static int getAttributeId(const string &s);
    
    static ofMutex staticMutex;
    
};


#endif /* defined(__ViZa__AttributeContainer__) */
