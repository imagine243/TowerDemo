//
//  TiledMapLayer.cpp
//  TowerDemo
//
//  Created by chao on 14-9-24.
//
//

#include "TiledMapLayer.h"
#include "GridMap.h"
#include "Dijkstra.h"
#include "Vertex.h"
#include "AStar.h"

TiledMapLayer::TiledMapLayer():mapGraph(nullptr)
{
    
}
TiledMapLayer::~TiledMapLayer()
{
    CC_SAFE_DELETE(mapGraph);
}
bool TiledMapLayer::init()
{
    if (Layer::init()) {
        
        auto map = TMXTiledMap::create("tiledmap/TestMap.tmx");
        map->setAnchorPoint(Vec2(0.0f, 0.0f));
        map->setPosition(0, 0);
        this->addChild(map);
        
        
        auto mapLayer = map->getLayer("layer1");
        
        Size maxSize = mapLayer->getLayerSize();
        CCLOG("maplayer maxwidth %f maxheight %f" , maxSize.width,maxSize.height);
        
        mapGraph = new GridMap((int)maxSize.width,(int)maxSize.height);
        
        for (int row = 0; row < maxSize.width; row++) {
            for (int col = 0; col < maxSize.height; col++) {
                int gid = mapLayer->getTileGIDAt(Vec2(row,col));
                printf(" %d",gid);
                
                if (gid == 10) {
                    mapGraph->setGridVertexType(row, col, vertex_vertex);
                }
            }
            printf("\n");
        }
        
        Dijkstra dij;
        dij.Execute(*mapGraph, 10, 39 * ID_PARA + 13);
        Vertex * vertex = mapGraph->getVertex(39, 13);
        

//        AStar dij;
//        dij.Execute(*mapGraph, 10, 39 * ID_PARA + 13);
//        Vertex * vertex = mapGraph->getVertex(39, 13);
        
        printf("path tree length %lld \n", dij.pathTree.size());
        
        
//        for (auto it = dij.pathTree.find(vertex) , end = dij.pathTree.end(); it->second != 0&& it != end ; it= dij.pathTree.find(it->second)) {
//            mapLayer->setTileGID(31, Vec2(vertex->getX(), vertex->getY()));
//            vertex = it->second;
//        }
        
        auto end = dij.pathTree.end();
        while (vertex != nullptr) {
            mapLayer->setTileGID(31, Vec2(vertex->getX(), vertex->getY()));
            auto it = dij.pathTree.find(vertex);
            if (it != end && it->second != nullptr) {
                vertex = it->second;
            }else{
                vertex = nullptr;
            }
        }
        
        auto dispatcher = Director::getInstance()->getEventDispatcher();
        auto listener = EventListenerTouchOneByOne::create();
        
        listener->onTouchBegan = CC_CALLBACK_2(TiledMapLayer::onTouchBegan, this);
        listener->onTouchMoved = CC_CALLBACK_2(TiledMapLayer::onTouchMoved, this);
        listener->onTouchEnded = CC_CALLBACK_2(TiledMapLayer::onTouchEnded, this);
        dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
        
        return true;
    }
    
    return false;
}

void TiledMapLayer::onTouchMoved(Touch *touch, Event *unused_event)
{
    Layer::onTouchMoved(touch, unused_event);
    
    float mx = touch->getLocation().x - startX;
    float my = touch->getLocation().y - startY;
    
    Vec2 pos = this->getPosition();
    this->setPosition(Vec2(pos.x + mx, pos.y + my));
    
    this->startX = touch->getLocation().x;
    this->startY = touch->getLocation().y;
    
    
}


bool TiledMapLayer::onTouchBegan(Touch *touch, Event *unused_event)
{
//    Layer::onTouchBegan(touch, unused_event);
    this->startX = touch->getLocation().x;
    this->startY = touch->getLocation().y;
    
    return true;
}