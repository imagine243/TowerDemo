//
//  TiledMapLayer.cpp
//  TowerDemo
//
//  Created by chao on 14-9-24.
//
//

#include "TiledMapLayer.h"
#include "GridMap.h"

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
        
        return true;
    }
    
    return false;
}