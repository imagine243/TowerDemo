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
#include <unordered_map>
#include <vector>

class Vertex;

enum vertex_type{
    vertex_default,
    vertex_vertex
};

class GridMap {
protected:
    int **p;
    
    int width;
    int height;
    
    std::unordered_map<int , Vertex *> vertexs;
    
public:
    
    GridMap(int width,int height);
    ~GridMap();
    
    //设置每个节点的类型
    void setGridVertexType(int x, int y, vertex_type type);
    int getGridVertexType(int x, int y);
    
    const std::unordered_map<int , Vertex *>& getVertexs()const {return vertexs;};
    
    std::vector<Vertex *> & getRoundVertex();
    
public:
};

#endif /* defined(__TowerDemo__GridMap__) */
