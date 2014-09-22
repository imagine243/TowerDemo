//
//  Sprite3DScene.h
//  TowerDemo
//
//  Created by chao on 14-9-22.
//
//

#ifndef __TowerDemo__Sprite3DScene__
#define __TowerDemo__Sprite3DScene__

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;

class Sprite3DScene :public Layer {
public:
    
    CREATE_FUNC(Sprite3DScene);
    virtual bool init();
    
    static Scene * createScene();
    
};

#endif /* defined(__TowerDemo__Sprite3DScene__) */
