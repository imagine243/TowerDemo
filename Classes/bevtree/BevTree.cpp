//
//  BevTree.cpp
//  TowerDemo
//
//  Created by chao on 14/10/11.
//
//

#include "BevTree.h"
using namespace BehaviorTree;

namespace BehaviorTree {

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


void BevNodeTerminal::_DoTransition(const InputParam& input)
{
    if (isNeedExit) {
        _DoExit(input, BRS_ERROR_Transition);
    }
    
    SetActiveNode(nullptr);
    myStatus = TNS_Ready;
    isNeedExit = false;
    
}

BevRunningStatus BevNodeTerminal::_DoTick(const InputParam & input, OutputParam & output)
{
    BevRunningStatus bIsFinish = BRS_Finish;
    
    if (myStatus == TNS_Ready) {
        _DoEnter(input);
        isNeedExit = true;
        myStatus = TNS_Running;
        SetActiveNode(this);
    }
    
    if (myStatus == TNS_Running) {
        bIsFinish = _DoExecute(input, output);
        SetActiveNode(this);
        if (bIsFinish == BRS_Finish || bIsFinish < 0) {
            myStatus = TNS_Finish;
        }
    }
    
    if (myStatus == TNS_Finish) {
        if (isNeedExit) {
            _DoExit(input, bIsFinish);
        }
        
        myStatus = TNS_Ready;
        isNeedExit = false;
        SetActiveNode(nullptr);
    }
    
    return bIsFinish;
}


bool BevNodeParallel::_DoEvaluate(const InputParam& input)
{
    for (unsigned int i = 0; i < childCount; ++i) {
        BevNode * obn = childNodeList[i];
        if (childNodeStatusList[i] == BRS_Executing) {
            if (!obn->Evaluate(input)) {
                return false;
            }
        }
    }
    return true;
}

void BevNodeParallel::_DoTransition(const InputParam& input)
{
    for (unsigned int i = 0; i < childCount; i++) {
        childNodeStatusList[i] = BRS_Executing;
    }
    
    for (unsigned int i = 0; i < childCount; i++) {
        BevNode* obn = childNodeList[i];
        obn->Transition(input);
    }
}

BevRunningStatus BevNodeParallel::_DoTick(const InputParam & input, const OutputParam & output)
{
    unsigned int finishedChildCount = 0;
    for (unsigned int i = 0; i < childCount; i++) {
        BevNode * obn = childNodeList[i];
        if (myFinishCondition == PFC_OR) {
            if (childNodeStatusList[i] == BRS_Executing) {
                childNodeStatusList[i] = obn->Tick(input, output);
            }
            
            if (childNodeStatusList[i] != BRS_Executing) {
                for (unsigned int i = 0; i < Limited_MaxChildNodeCount; i++) {
                    childNodeStatusList[i] = BRS_Executing;
                    return BRS_Finish;
                }
            }
        }else if (myFinishCondition == PFC_AND){
            if (childNodeStatusList[i] == BRS_Executing) {
                childNodeStatusList[i] = obn->Tick(input, output);
            }
            if (childNodeStatusList[i] != BRS_Executing) {
                finishedChildCount++;
            }
        }else{
            ASSERT(0);
        }
    }
    
    if (finishedChildCount == childCount) {
        for (unsigned int i = 0; i < Limited_MaxChildNodeCount; i++) {
            childNodeStatusList[i] = BRS_Executing;
        }
        return BRS_Finish;
    }
    return BRS_Executing;
}
        
BevNodeParallel& BevNodeParallel::SetFinishCondition(ParallelFinishCondition _condition)
{
    myFinishCondition = _condition;
    return (*this);
}

bool BevNodeLoop::_DoEvaluate(const InputParam& input)
{
    bool checkLoopCount = (myLoopCount == kInfinishLoop) || myCurrentCount < myLoopCount;
    
    if (!checkLoopCount) {
        return false;
    }
    
    if (_CheckIndex(0)) {
        BevNode * obn = childNodeList[0];
        if (obn->Evaluate(input)) {
            return true;
        }
    }
    
    return false;
}

void BevNodeLoop::_DoTransition(const InputParam& input)
{
    if (_CheckIndex(0)) {
        BevNode * obn = childNodeList[0];
        obn->Transition(input);
    }
    
    myCurrentCount = 0;
}

BevRunningStatus BevNodeLoop::_DoTick(const InputParam & input, const OutputParam & output)
{
    BevRunningStatus bIsFinish = BRS_Finish;
    
    if (_CheckIndex(0)) {
        BevNode * obn = childNodeList[0];
        bIsFinish = obn->Tick(input, output);
        
        if (bIsFinish == BRS_Finish) {
            if (myLoopCount != kInfinishLoop) {
                myCurrentCount++;
                if (myCurrentCount == myLoopCount) {
                    bIsFinish = BRS_Executing;
                }
            }else{
                bIsFinish = BRS_Executing;
            }
        }
    }
    
    if (bIsFinish) {
        myCurrentCount = 0;
    }
    
    return bIsFinish;
}



}










