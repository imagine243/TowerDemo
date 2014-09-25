//
//  GraphPathFinding.h
//  TowerDemo
//
//  Created by chao on 14-9-25.
//
//

#ifndef __TowerDemo__GraphPathFinding__
#define __TowerDemo__GraphPathFinding__

#include <stdio.h>
#include <unordered_map>
#include "GridMap.h"

class Vertex;

class GraphPathFinding {
protected:
    std::unordered_map<Vertex * , Vertex *> pathTree;
public:
    GraphPathFinding(){};
    virtual ~GraphPathFinding(){};
    
    virtual void Execute(const GridMap & gridMap, int startId ,int endId) = 0;
};

#endif /* defined(__TowerDemo__GraphPathFinding__) */
