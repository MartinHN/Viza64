//
//  ofxKdTree.h
//  ViZa
//
//  Created by martin hermant on 23/10/14.
//
//

#ifndef ViZa_ofxKdTree_h
#define ViZa_ofxKdTree_h

#include "ofMain.h"
#include "flann.hpp"



class ofxKdTree{
public:
    
    void buildIdx(const vector<ofVec3f> vects);
    
    vector<ofVec3f> getNearest(const ofVec3f p,int nn=1);
    
    int nElements;
    int nFeatures;
    
    
    static ofxKdTree* instance(){
        if(inst==NULL){
            inst = new ofxKdTree;
        }
        return inst;
    }
    

    
    FILE* saveIdx;
    cvflann::Matrix<float> datasetMat;

    
    
    vector<ofVec3f> indexes;
    
    
    
private:
    static ofxKdTree* inst;
    
};

#endif
