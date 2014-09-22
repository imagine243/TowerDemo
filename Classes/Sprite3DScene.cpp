//
//  Sprite3DScene.cpp
//  TowerDemo
//
//  Created by chao on 14-9-22.
//
//

#include "Sprite3DScene.h"

bool Sprite3DScene::init()
{
    if (Layer::init()) {
        
        auto background = Sprite::create("Sprite3DTest/1-1.jpg");
        
        Size size = Director::getInstance()->getWinSize();
        
        background->setPosition(size.width/2, 0);
        background->setAnchorPoint(Vec2(0.5f,0.0f));
        this->addChild(background);
        
        return true;
    }
    
    return false;
}
    
Scene * Sprite3DScene::createScene()
{
    auto scene = Scene::create();
    
    auto layer = Sprite3DScene::create();
    
    scene->addChild(layer);
    return scene;
}


