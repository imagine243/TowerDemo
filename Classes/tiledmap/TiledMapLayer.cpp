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
        
        printf("path tree length %d \n", dij.pathTree.size());
        
        
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
        
        
        return true;
    }
    
    return false;
}