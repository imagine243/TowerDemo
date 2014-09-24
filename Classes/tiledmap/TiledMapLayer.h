//
//  TiledMapLayer.h
//  TowerDemo
//
//  Created by chao on 14-9-24.
//
//

#ifndef __TowerDemo__TiledMapLayer__
#define __TowerDemo__TiledMapLayer__

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class GridMap;

class TiledMapLayer :public Layer {
protected:
    GridMap * mapGraph;
public:
    
    TiledMapLayer():mapGraph(nullptr){};
    virtual ~TiledMapLayer(){};
    
    CREATE_FUNC(TiledMapLayer);
    virtual bool init();
};

#endif /* defined(__TowerDemo__TiledMapLayer__) */
