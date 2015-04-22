//
//  AttributeContainer.cpp
//  ViZa
//
//  Created by martin hermant on 23/01/15.
//
//

#include "AttributeContainer.h"


#include "Container.h"


float *  AttributeContainer::normalizedAttributes = NULL;
vector< int>  AttributeContainer::fixAttributes;
float *  AttributeContainer::attributesCache = NULL;
vector<string> AttributeContainer::attributeNames;


float *  AttributeContainer::reducedAttributeCache = NULL;
vector< int>  AttributeContainer::reducedAttributesNamesIdx;


vector<float > AttributeContainer::mins;
vector<float > AttributeContainer::maxs;
vector<float > AttributeContainer::means;
vector<float > AttributeContainer::stddevs;


int AttributeContainer::attrSize;
int AttributeContainer::numAttr = 0;

ofMutex AttributeContainer::staticMutex;



AttributeContainer::AttributeContainer(unsigned int curI){

    if(attrSize*(1+curI)>numAttr){
        ofLogError("AttributeContainer","resizing : " + ofToString(attrSize) +" : "+ ofToString(curI));
        ofScopedLock lock(staticMutex);
        numAttr = attrSize*(curI+1)*sizeof(float);
        attributesCache =
        (float*)realloc(attributesCache,numAttr);

    }
}
int AttributeContainer::getAttributeId(const string &n){

    int foundIdx = ofFind(attributeNames,n);
    
    if(foundIdx<0 || foundIdx >= attributeNames.size()) foundIdx=-1;
    return foundIdx;
    
}
void AttributeContainer::setAttribute(const string &n,const float v){
    
    ofScopedLock lock(staticMutex);
    
    int foundIdx = ofFind(attributeNames,n);
    if(foundIdx<0 || foundIdx >= attributeNames.size()) foundIdx=-1;
    if(foundIdx>=0 ){
        mins[foundIdx] = MIN(mins[foundIdx], v);
        maxs[foundIdx] = MAX(maxs[foundIdx], v);
   
    }
    
    
    //no dynamic add of new Attribute
    else{
        
        
        ofLogError("AttributeContainer","unConsistent json files : "+ n  + "found"+ofToString(foundIdx) );
        
        for (int i = 0 ; i < attributeNames.size() ; i++){
            cout << attributeNames[i] << endl;
        }
        
    }
    
    
    
    
    int curIdx = ((Container*)this)->globalIdx;

    attributesCache[attrSize * curIdx +foundIdx] = v;


}


void AttributeContainer::setAttribute(const int idx, const float v){
    int curIdx = ((Container*)this)->globalIdx;    
    attributesCache[attrSize * curIdx +idx] = v;
    mins[idx] = MIN(mins[idx], v);
    maxs[idx] = MAX(maxs[idx], v);

}

void AttributeContainer::preCacheAttr(vector<string> & attr){
    attributeNames = attr;
    attrSize = attributeNames.size();
    mins.resize(attrSize);
    maxs.resize(attrSize);

}

vector<string> AttributeContainer::getAggregators(string & s){
    vector<string > res;
    for(int i = 0 ;  i < attributeNames.size() ; i++){
        
        vector<string> split = ofSplitString(attributeNames[i], ".");
        if(split[0] == s && split.size()==2 ){
            res.push_back(split[1]);
        }
        
    }
    
    if(res.size()==0){
        res.push_back("None");
    }
    return res;
}

void AttributeContainer::CacheNormalized(int numCont){
    
//    int numCont = containers.size();
    int idx=0;
    
    means.resize(attrSize);
    stddevs.resize(attrSize);
    
    normalizedAttributes = (float*)realloc(normalizedAttributes, numCont * attrSize*sizeof(float));
    fixAttributes.clear();
    for(int i = 0 ; i < attrSize;i++){
        
        DSP_normalize(&attributesCache[i],attrSize, &normalizedAttributes[i], attrSize, &means[i], &stddevs[i], numCont);
        
        // fix attributes
        if(stddevs[i] ==0 || stddevs[i]!=stddevs[i]){
            fixAttributes.push_back(i);
            stddevs[i]=0;
            ofLogWarning("AttributeContainer","Fix Attribute : " +ofToString(attributeNames[i]) +" = " +ofToString(means[i]));
            for(int j=0 ; j<numCont ; j++){
                normalizedAttributes[i+j*attrSize] = 0;
            }
        }
        
    }
    //    fixAttributes.resize(fixAttributes.size()-1);
}
float & AttributeContainer::getAttributes(int i,bool normalized){
    return normalized?normalizedAttributes[attrSize * (((Container*)this)->globalIdx) +i]:attributesCache[attrSize * (((Container*)this)->globalIdx) +i];
};

void AttributeContainer::clearAll(){
    
    attributeNames.clear();
    free(attributesCache);
    attributesCache = NULL;
    free(normalizedAttributes);
    normalizedAttributes = NULL;
    fixAttributes.clear();
    maxs.clear();
    mins.clear();
    means.clear();

    attrSize = 0;
    
}