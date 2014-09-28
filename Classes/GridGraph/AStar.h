//
//  AStar.h
//  TowerDemo
//
//  Created by chao on 14-9-28.
//
//

#ifndef __TowerDemo__AStar__
#define __TowerDemo__AStar__

#include <stdio.h>
#include <unordered_set>
#include "GraphPathFinding.h"

class AStar : public GraphPathFinding{
private:
    Vertex * end;
protected:
    
public:
    
    AStar(){};
    virtual ~AStar(){};
public:
    
    virtual void Execute(GridMap & gridMap, int startId ,int endId);
    Vertex * ExtractMin(std::unordered_set<Vertex *> & Q);
    bool relax(Vertex * v1, Vertex * v2 ,float weight);
    float estimate(Vertex * v1,Vertex * end );
};

#endif /* defined(__TowerDemo__AStar__) */
