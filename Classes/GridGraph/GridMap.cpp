//
//  GridMap.cpp
//  TowerDemo
//
//  Created by chao on 14-9-24.
//
//

#include "GridMap.h"



GridMap::GridMap(int width,int height):width(width),height(height)
{
    if (width == 0 || height == 0) {
        printf("error width or height is zero");
        return;
    }
    
    p = new int * [width];
    for (int i = 0 ; i < width; i++) {
        p[i] = new int[height];
    }
    
    for (int row = 0; row < width; row++) {
        for (int col = 0; col < height; col++) {
            p[row][col] = vertex_default;
        }
    }
}

GridMap::~GridMap()
{
    for (int row = 0; row < width; row++) {
        delete  [] p[row];
    }
    delete p;
}

void GridMap::setGridVertexType(int x, int y, vertex_type type)
{
    if (x >= width || y >= height) {
        return;
    }
    
    p[x][y] = type;
}