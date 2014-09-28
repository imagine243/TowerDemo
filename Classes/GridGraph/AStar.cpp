//
//  AStar.cpp
//  TowerDemo
//
//  Created by chao on 14-9-28.
//
//

#include "AStar.h"
#include "GridMap.h"
#include "Vertex.h"
#include "stdlib.h"

void AStar::Execute(GridMap & gridMap, int startId ,int endId)
{
    this->pathTree.clear();
    
    const auto & vertexs = gridMap.getVertexs();
    
    Vertex * pStart = vertexs.find(startId)->second;
    Vertex * pEnd = vertexs.find(endId)->second;
    end = pEnd;
    //    std::vector<Vertex *> Q;
    std::unordered_set<Vertex *> Q;
    
    //每一个节点的cost初始化为一个极大值
    for (auto & it :vertexs) {
        it.second->setCost(MAXCOST);
        it.second->setHeuristic(MAXCOST);
        //        Q.push_back(it.second);
        //        printf("vertex cost %f \n", it.second->getCost());
    }
    
    //起点的前置节点为0
    this->pathTree[pStart] = nullptr;
    pStart->setCost(0);
    pStart->setHeuristic(estimate(pStart, pEnd));
    
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
            
            bool isRelax = relax(v, it, weight);
            
            if (isRelax) {
                Q.insert(it);
                flag = true;
            }
        }
    }
}

Vertex * AStar::ExtractMin(std::unordered_set<Vertex *> & Q)
{
    Vertex * ret = nullptr;
    
    auto it = Q.begin();
    ret = *it;
    it++;
    for (; it != Q.end(); it++) {
        if (ret->getHeuristic() > (*it)->getHeuristic()) {
            ret = *it;
        }
    }
    
    Q.erase(ret);
    
    return ret;
}

bool AStar::relax(Vertex * v1, Vertex * v2 ,float weight)
{
    float G = v1->getCost() + weight;
    float h = estimate(v2, end);
    float heuristic = G + h;
    
    if (heuristic < v2->getHeuristic()) {
        v2->setCost(G);
        v2->setHeuristic(heuristic);
        this->pathTree[v2] = v1;
        printf("per vertex x %d y %d cost %f      vertex x %d y %d cost %f \n",v1->getX(),v1->getY(),v1->getCost(), v2->getX(),v2->getY(),v2->getCost());
        
        return true;
    }
    
    return false;
}

float AStar::estimate(Vertex * v1, Vertex * end )
{
    int width = abs(v1->getX() - end->getX());
    int height = abs(v1->getY()- end->getY());
    
    float length = abs(width - height) * SQRT_2 + ((width - height) > 0 ? (width - height) : (height - width));
    return length;
}