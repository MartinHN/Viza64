//
//  ofxTSNE.h
//  ViZa
//
//  Created by martin hermant on 29/01/15.
//
//


#ifndef __ViZa__ofxTSNE__
#define __ViZa__ofxTSNE__

#include "tsne.h"
#include "ofMain.h"
#include "DSP.h"


class ofxTSNE : public ofThread{
    
    
    TSNE* tsne;
    
    int nData,dimData,outDim;
    float theta,perplexity;
    double *inVec = NULL;
    double *outVecCache = NULL;

    
    static ofxTSNE* instance;
    
    
    vector<ofVec3f> cache;
    
    typedef void (*CallbackType)(double*);
    CallbackType cb_func;

public:
    ofxTSNE(){
        tsne = new TSNE();
        ofAddListener(ofEvents().update, this, &ofxTSNE::update);
    }
    
    ~ofxTSNE(){
        delete(tsne);
        free(inVec);
        free(outVecCache);
    }
    void init(float * v, int dim,int nelem,float _theta,float _perp,int _outDim);
    
    
    void threadedFunction();
    
    static ofxTSNE* i(){
        if(instance == NULL){
            instance = new ofxTSNE();
        }
        return instance;
    }
    
    
    bool hasStopped;
    
    void update(ofEventArgs & a);
    
};



#endif /* defined(__ViZa__ofxTSNE__) */
