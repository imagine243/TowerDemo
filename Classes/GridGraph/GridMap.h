//
//  GridMap.h
//  TowerDemo
//
//  Created by chao on 14-9-24.
//
//

#ifndef __TowerDemo__GridMap__
#define __TowerDemo__GridMap__

#include <stdio.h>

enum vertex_type{
    vertex_default,
    vertex_vertex
};

class GridMap {
protected:
    int **p;
    
    int width;
    int height;
public:
    
    GridMap(int width,int height);
    ~GridMap();
    
    void setGridVertexType(int x, int y, vertex_type type);
    
};

#endif /* defined(__TowerDemo__GridMap__) */
