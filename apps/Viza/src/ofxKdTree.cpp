
//  ofxKdTree.cpp
//  ViZa
//
//  Created by martin hermant on 23/10/14.
//
//

#include "ofxKdTree.h"
ofxKdTree* ofxKdTree::inst;



void ofxKdTree::buildIdx(const vector<ofVec3f> vects){
    nElements = vects.size();
    nFeatures = 3;
    
    datasetMat.cols=nFeatures;
    datasetMat.rows=nElements;
    
    datasetMat.data = (float*)&vects[0];
    
    cvflann::Index<cvflann::L2<float> > index(datasetMat, cvflann::AutotunedIndexParams());
    
    index.buildIndex();
    index.saveIndex(saveIdx);
    
}


vector<ofVec3f> ofxKdTree::getNearest(const ofVec3f v,int nn){
    

    
    cvflann::Matrix<float> query ((float*)&v,3,nn) ;
    vector<vector<int > > indices;//(new int[nn], 1, nn);
    vector<vector<float > > dists;//(new float[nn], query.rows, nn);
    cvflann::Index index(datasetMat, cvflann::SavedIndexParams("index.dat"), cvflann::FLANN_DIST_HAMMING);

    
    index.knnSearch(query, indices, dists, nn, cvflann::SearchParams(128));
    
    vector<ofVec3f> res;
    for(int i = 0 ; i < indices.size;i++){
        
        ofVec3f v;
        v.x = ((float* )(datasetMat[indices[i][0]]))[0];
        v.y = ((float* )(datasetMat[indices[i][0]]))[1];
        v.z = ((float* )(datasetMat[indices[i][0]]))[2];
        
    }
    
    
    
}