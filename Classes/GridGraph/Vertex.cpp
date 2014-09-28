//
//  Vertex.cpp
//  TowerDemo
//
//  Created by chao on 14-9-25.
//
//

#include "Vertex.h"

Vertex::Vertex(int id,float cost)
{
    this->cost = cost;
    this->setId(id);
    this->heuristic = 0;
}

Vertex::Vertex(int x, int y, float cost)
{
    this->cost = cost;
    this->setXY(x, y);
    this->heuristic = 0;
}

Vertex::~Vertex()
{
    
}

void Vertex::setId(int id)
{
    this->id = id;
    getGridXYById(this->id, this->x, this->y);
}

void Vertex::setXY(int x, int y)
{
    this->x = x;
    this->y = y;
    this->id = getGridIdByXY(this->x, this->y);
}

void Vertex::setCost(float cost)
{
    this->cost = cost;
}

int Vertex::getId()
{
    return id;
}

int Vertex::getX()
{
    return x;
}

int Vertex::getY()
{
    return y;
}

float Vertex::getCost()
{
    return this->cost;
}

float Vertex::getHeuristic()
{
    return this->heuristic;
}

void Vertex::setHeuristic(float heuristic)
{
    this->heuristic = heuristic;
}

void Vertex::getGridXYById(const int & id, int & x, int & y)
{
    x = id/ID_PARA;
    y = id % ID_PARA;
}

int Vertex::getGridIdByXY(const int & x , const int & y)
{
    return  x * ID_PARA + y;
}