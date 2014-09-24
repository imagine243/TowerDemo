//
//  TiledMapScene.cpp
//  TowerDemo
//
//  Created by chao on 14-9-24.
//
//

#include "TiledMapScene.h"
#include "TiledMapLayer.h"


bool TiledMapScene::init()
{
    if (Layer::init()) {
        
        auto tiledMaplayer = TiledMapLayer::create();
        tiledMaplayer->setScale(0.75);
        tiledMaplayer->setAnchorPoint(Vec2(0.0f,0.0f));
        tiledMaplayer->setPosition(Vec2(0.0f, 0.0f));
        this->addChild(tiledMaplayer);
        
        return true;
    }
    return false;
}

Scene * TiledMapScene::createScene()
{
    auto scene = Scene::create();
    auto layer = TiledMapScene::create();
    scene->addChild(layer);
    return scene;
}