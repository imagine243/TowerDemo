//
//  Dijkstra.cpp
//  TowerDemo
//
//  Created by chao on 14-9-25.
//
//

#include "Dijkstra.h"
#include "GridMap.h"
#include "Vertex.h"

const float MAXCOST = 100000000.0f;

void Dijkstra::Execute(const GridMap & gridMap, int startId ,int endId)
{
    this->pathTree.clear();
    
    const auto & vertexs = gridMap.getVertexs();
    
    Vertex * pStart = vertexs.find(startId)->second;
    std::vector<Vertex *> Q;
    
    //每一个节点的cost初始化为一个极大值
    for (auto & it :vertexs) {
        it.second->setCost(MAXCOST);
        Q.push_back(it.second);
    }
    
    //起点的前置节点为0
    this->pathTree[pStart] = nullptr;
    pStart->setCost(0);
    
    for (; Q.size() > 0; ) {
        auto v = ExtractMin(Q);
    }
}

Vertex * Dijkstra::ExtractMin(std::vector<Vertex *> & Q)
{
    Vertex * ret = nullptr;
    ret = Q[0];
    int pos = 0;
    for (int i = 1,size = Q.size(); i < size; i++) {
        if (ret->getCost() > Q[i]->getCost()) {
            ret = Q[i];
            pos = i;
        }
    }
    
    Q.erase(Q.begin() + pos);
    return ret;
}

