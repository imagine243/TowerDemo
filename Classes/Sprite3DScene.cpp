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
        
        auto background = Sprite::create("Sprite3DTest/map-001.png");
        
        Size size = Director::getInstance()->getWinSize();
        
        background->setPosition(size.width/2, 0);
        background->setAnchorPoint(Vec2(0.5f,0.0f));
        background->setScale(0.5);
        this->addChild(background);
        
        std::string filename = "Sprite3DTest/orc.c3b";
        auto sprite = Sprite3D::create(filename);
        sprite->setScale(6);
        sprite->setRotation3D(Vec3(0,180,0));
//        sprite->setPosition(Vec2(size.width/2, size.height));
        sprite->setPosition3D(Vec3(size.width/2, size.height/2, 0.0f));
        
        addChild(sprite);
        
        auto animation = Animation3D::create(filename);
        if (animation) {
            auto animate = Animate3D::create(animation);
            animate->setSpeed(1);
            sprite->runAction(RepeatForever::create(animate));
        }
        
//        sprite->runAction(MoveTo::create(5, Vec2(size.width/2,size.height)));
        
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


