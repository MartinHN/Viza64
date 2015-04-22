/*
 *  quadtree.h
 *  Header file for a quadtree.
 *
 *  Created by Laurens van der Maaten.
 *  Copyright 2012, Delft University of Technology. All rights reserved.
 *
 */

#ifndef QUADTREE_H
#define QUADTREE_H

//using namespace std;

static inline float min(float x, float y) { return (x <= y ? x : y); }
static inline float max(float x, float y) { return (x <= y ? y : x); }
static inline float abs(float x) { return (x < .0 ? -x : x); }

class Cell {
    
public:
    float x;
    float y;
    float hw;
    float hh;
    bool   containsPoint(float point[]);
};


class QuadTree
{
    
    // Fixed constants    
    static const int QT_NO_DIMS = 2;
    static const int QT_NODE_CAPACITY = 1;

    // A buffer we use when doing force computations
    float buff[QT_NO_DIMS];
    
    // Properties of this node in the tree
    QuadTree* parent;
    bool is_leaf;
    int size;
    int cum_size;
        
    // Axis-aligned bounding box stored as a center with half-dimensions to represent the boundaries of this quad tree
    Cell boundary;
    
    // Indices in this quad tree node, corresponding center-of-mass, and list of all children
    float* data;
    float center_of_mass[QT_NO_DIMS];
    int index[QT_NODE_CAPACITY];
    
    // Children
    QuadTree* northWest;
    QuadTree* northEast;
    QuadTree* southWest;
    QuadTree* southEast;
    
public:
    QuadTree(float* inp_data, int N);
    QuadTree(float* inp_data, float inp_x, float inp_y, float inp_hw, float inp_hh);
    QuadTree(float* inp_data, int N, float inp_x, float inp_y, float inp_hw, float inp_hh);
    QuadTree(QuadTree* inp_parent, float* inp_data, int N, float inp_x, float inp_y, float inp_hw, float inp_hh);
    QuadTree(QuadTree* inp_parent, float* inp_data, float inp_x, float inp_y, float inp_hw, float inp_hh);
    ~QuadTree();
    void setData(float* inp_data);
    QuadTree* getParent();
    void construct(Cell boundary);
    bool insert(int new_index);
    void subdivide();
    bool isCorrect();
    void rebuildTree();
    void getAllIndices(int* indices);
    int getDepth();
    void computeNonEdgeForces(int point_index, float theta, float neg_f[], float* sum_Q);
    void computeEdgeForces(int* row_P, int* col_P, float* val_P, int N, float* pos_f);    
    void print();
    
private:
    void init(QuadTree* inp_parent, float* inp_data, float inp_x, float inp_y, float inp_hw, float inp_hh);
    void fill(int N);
    int getAllIndices(int* indices, int loc);
    bool isChild(int test_index, int start, int end);
};

#endif
