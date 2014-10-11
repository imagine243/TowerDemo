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
    BevRunningStatus bIsFinish = BRS_Finish;
    if (_CheckIndex(currentSelectIndex)) {
        if (currentSelectIndex != lastSelectIndex) {
            if (_CheckIndex(lastSelectIndex)) {
                BevNode * obn = childNodeList[lastSelectIndex];
                obn->Transition(input);
            }
            lastSelectIndex = currentSelectIndex;
        }
    }
    
    if (_CheckIndex(lastSelectIndex)) {
        BevNode* obn = childNodeList[lastSelectIndex];
        bIsFinish = obn->Tick(input, output);
        if (bIsFinish) {
            lastSelectIndex = Limited_InvalidChildNodeIndex;
        }
    }
    
    return bIsFinish;
}


bool BevNodeNonePrioritySelector::_DoEvaluate(const InputParam& input)
{
    if (_CheckIndex(currentSelectIndex)) {
        BevNode * obn = childNodeList[currentSelectIndex];
        if (obn->Evaluate(input)) {
            return true;
        }
    }
    return BevNodePrioritySelector::_DoEvaluate(input);
}


bool BevNodeSequence::_DoEvaluate(const InputParam& input)
{
    unsigned int testNode;
    if (currentNodeIndex == Limited_InvalidChildNodeIndex) {
        testNode = 0;
    }else{
        testNode = currentNodeIndex;
    }
    
    if (_CheckIndex(testNode)) {
        BevNode * obn = childNodeList[testNode];
        if (obn->Evaluate(input)) {
            return true;
        }
    }
    
    return false;
}

void BevNodeSequence::_DoTransition(const InputParam& input)
{
    if (_CheckIndex(currentNodeIndex)) {
        BevNode * obn = childNodeList[currentNodeIndex];
        obn->Transition(input);
    }
    currentNodeIndex = Limited_InvalidChildNodeIndex;
}

BevRunningStatus BevNodeSequence::_DoTick(const InputParam & input, const OutputParam & output)
{
    BevRunningStatus bIsFinish = BRS_Finish;
    
    //First time
    if (currentNodeIndex == Limited_InvalidChildNodeIndex) {
        currentNodeIndex =0;
    }
    
    BevNode* obn = childNodeList[currentNodeIndex];
    bIsFinish = obn->Tick(input, output);
    
    if (bIsFinish == BRS_Finish) {
        ++currentNodeIndex;
        if (currentNodeIndex == childCount) {
            currentNodeIndex = Limited_InvalidChildNodeIndex;
        }else{
            bIsFinish = BRS_Executing;
        }
    }
    
    if (bIsFinish < 0) {
        currentNodeIndex = Limited_InvalidChildNodeIndex;
    }
    return bIsFinish;
}

