/*
 *  tsne.h
 *  Header file for t-SNE.
 *
 *  Created by Laurens van der Maaten.
 *  Copyright 2012, Delft University of Technology. All rights reserved.
 *
 */


#ifndef TSNE_H
#define TSNE_H


static inline float sign(float x) { return (x == .0 ? .0 : (x < .0 ? -1.0 : 1.0)); }


class TSNE
{    
public:
    void run(float* X, int N, int D, float* Y, int no_dims, float perplexity, float theta);


    void symmetrizeMatrix(int** row_P, int** col_P, float** val_P, int N); // should be static?!

    
private:
    void computeGradient(float* P, int* inp_row_P, int* inp_col_P, float* inp_val_P, float* Y, int N, int D, float* dC, float theta);
    void computeExactGradient(float* P, float* Y, int N, int D, float* dC);
    float evaluateError(float* P, float* Y, int N);
    float evaluateError(int* row_P, int* col_P, float* val_P, float* Y, int N, float theta);
    void zeroMean(float* X, int N, int D);
    void computeGaussianPerplexity(float* X, int N, int D, float* P, float perplexity);
    void computeGaussianPerplexity(float* X, int N, int D, int** _row_P, int** _col_P, float** _val_P, float perplexity, int K);
    void computeGaussianPerplexity(float* X, int N, int D, int** _row_P, int** _col_P, float** _val_P, float perplexity, float threshold);
    void computeSquaredEuclideanDistance(float* X, int N, int D, float* DD);
    float randn();
};

#endif

