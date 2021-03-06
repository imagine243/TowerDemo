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
#include "stdlib.h"

void Dijkstra::Execute(GridMap & gridMap, int startId ,int endId)
{
    this->pathTree.clear();
    
    const auto & vertexs = gridMap.getVertexs();
    
    Vertex * pStart = vertexs.find(startId)->second;
//    std::vector<Vertex *> Q;
    std::unordered_set<Vertex *> Q;
    
    //每一个节点的cost初始化为一个极大值
    for (auto & it :vertexs) {
        it.second->setCost(MAXCOST);
//        Q.push_back(it.second);
//        printf("vertex cost %f \n", it.second->getCost());
    }
    
    //起点的前置节点为0
    this->pathTree[pStart] = nullptr;
    pStart->setCost(0);
    
//    Q.push_back(pStart);
    Q.insert(pStart);
    
    bool flag = true;
    
    for (; Q.size() > 0; ) {
        auto v = ExtractMin(Q);
        
        if (endId == v->getId()) {
            
            return;
        }
        
        std::vector<Vertex *> roundVertexs;
        gridMap.getRoundVertex(v, roundVertexs);
        
        
        printf("relax one vertex x %d y %d cost %f \n", v->getX(), v->getY() ,v->getCost());
        
        //对所有的边松弛
        for ( auto & it : roundVertexs) {
            if (it == v) {
                continue;
            }
            
            float weight = abs(it->getX() - v->getX()) + abs(it->getY() - v->getY());
            
            if (weight > 1) {
                weight = SQRT_2;
            }
            
//            if (endId == it->getId()) {
//                this->pathTree[it] = v;
//                printf("end per vertex x %d y %d       vertex x %d y %d \n",v->getX(),v->getY(), it->getX(),it->getY());
//                return;
//            }
            
            bool isRelax = relax(v, it, weight);
            
            if (isRelax) {
                Q.insert(it);
                flag = true;
            }
        }
    }
}

Vertex * Dijkstra::ExtractMin(std::unordered_set<Vertex *> & Q)
{
    Vertex * ret = nullptr;
//    ret = Q[0];
//    int pos = 0;
//    unsigned long size = Q.size();
//    for (int i = 1; i < size; i++) {
////        printf("min vertex x %d y %d cost %f \n", Q[i]->getX(),Q[i]->getY(),Q[i]->getCost());
//        if (ret->getCost() > Q[i]->getCost()) {
//            ret = Q[i];
//            pos = i;
//        }
//    }
//    
//    Q.erase(Q.begin() + pos);
    
    
    auto it = Q.begin();
    ret = *it;
    it++;
    for (; it != Q.end(); it++) {
        if (ret->getCost() > (*it)->getCost()) {
            ret = *it;
        }
    }
    
    Q.erase(ret);
    
    return ret;
}

bool Dijkstra::relax(Vertex * v1, Vertex * v2 ,float weight)
{
    float cost = v1->getCost() + weight;
    if (cost < v2->getCost()) {
        v2->setCost(cost);
        this->pathTree[v2] = v1;
        printf("per vertex x %d y %d cost %f      vertex x %d y %d cost %f \n",v1->getX(),v1->getY(),v1->getCost(), v2->getX(),v2->getY(),v2->getCost());
        
        return true;
    }
    
    return false;
}
