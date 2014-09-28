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
private:
    float startX;
    float startY;
protected:
    GridMap * mapGraph;
public:
    
    TiledMapLayer();
    virtual ~TiledMapLayer();
    
    CREATE_FUNC(TiledMapLayer);
    virtual bool init();
    virtual bool onTouchBegan(Touch *touch, Event *unused_event); 
    virtual void onTouchMoved(Touch *touch, Event *unused_event); 
};

#endif /* defined(__TowerDemo__TiledMapLayer__) */
