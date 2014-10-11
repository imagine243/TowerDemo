//
//  BevTree.cpp
//  TowerDemo
//
//  Created by chao on 14/10/11.
//
//

#include "BevTree.h"
using namespace BehaviorTree;

bool BevNodePrioritySelector::_DoEvaluate(const InputParam& input)
{
    currentSelectIndex = Limited_InvalidChildNodeIndex;
    for (int i = 0; i < childCount; i++) {
        BevNode * obn = childNodeList[i];
        if (obn->Evaluate(input)) {
            currentSelectIndex = i;
            return true;
        }
    }
    
    return false;
}

void BevNodePrioritySelector::_DoTransition(const InputParam& input)
{
    if (_CheckIndex(lastSelectIndex)) {
        BevNode* obn = childNodeList[lastSelectIndex];
        obn->Transition(input);
    }
    lastSelectIndex = Limited_InvalidChildNodeIndex;
}

BevRunningStatus BevNodePrioritySelector::_DoTick(const InputParam & input, const OutputParam & output)
{
    
}