//
//  Vertex.h
//  TowerDemo
//
//  Created by chao on 14-9-25.
//
//

#ifndef __TowerDemo__Vertex__
#define __TowerDemo__Vertex__

#include <stdio.h>

const int ID_PARA = 10000;

class Vertex {
private:
    int id;
    int x;
    int y;
    float cost;
public:
    Vertex(int id,float cost = 0.0f);
    Vertex(int x, int y, float cost = 0.0f);
    ~Vertex();
    void setId(int id);
    void setXY(int x, int y);
    void setCost(float cost);
    int getId();
    int getX();
    int getY();
    float getCost();
    void getGridXYById(const int & id, int & x, int & y);
    int getGridIdByXY(const int & x , const int & y);
};

#endif /* defined(__TowerDemo__Vertex__) */
