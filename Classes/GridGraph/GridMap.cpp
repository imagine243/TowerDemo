//
//  GridMap.cpp
//  TowerDemo
//
//  Created by chao on 14-9-24.
//
//

#include "GridMap.h"
#include "Vertex.h"

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
    
    for (auto & kv : vertexs) {
        delete kv.second;
    }
}

void GridMap::setGridVertexType(int x, int y, vertex_type type)
{
    if (x >= width || y >= height) {
        return;
    }
    
    p[x][y] = type;
    
    Vertex * vertex = nullptr;
    if (vertexs.find(x * 10 + y) != vertexs.end())
    {
        vertex = vertexs.find(x * 10 + y)->second;
    }
    
    if (type == vertex_vertex) {
        //add to vertexs
        if (vertex == nullptr) {
            vertex = new Vertex(x,y);
        }
        
        vertexs[x * 10 + y] = vertex;
    }else{
        //delete form vertexs
        if (vertex) {
            vertexs.erase(x * 10 + y);
            delete vertex;
        }
        
    }
    
}
int GridMap::getGridVertexType(int x, int y)
{
    if (x >= width || y >= height) {
        return vertex_default;
    }
    
    return p[x][y];
}

std::vector<Vertex *> & GridMap::getRoundVertex()
{
    
}