//
//  Dijkstra.h
//  TowerDemo
//
//  Created by chao on 14-9-25.
//
//

#ifndef __TowerDemo__Dijkstra__
#define __TowerDemo__Dijkstra__

#include <stdio.h>
#include <vector>
#include "GridMap.h"
#include "GraphPathFinding.h"

class Dijkstra :public GraphPathFinding {
public:
    Dijkstra(){};
    virtual ~Dijkstra(){};
    
public:
    virtual void Execute(GridMap & gridMap, int startId ,int endId);
    Vertex * ExtractMin(std::vector<Vertex *> & Q);
    void relax(Vertex * v1, Vertex * v2 ,float weight);
};

#endif /* defined(__TowerDemo__Dijkstra__) */
