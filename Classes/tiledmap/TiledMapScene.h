//
//  TiledMapScene.h
//  TowerDemo
//
//  Created by chao on 14-9-24.
//
//

#ifndef __TowerDemo__TiledMapScene__
#define __TowerDemo__TiledMapScene__

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class TiledMapScene : public Layer {
public:
    CREATE_FUNC(TiledMapScene);
    virtual bool init();
    static Scene * createScene();
};

#endif /* defined(__TowerDemo__TiledMapScene__) */
