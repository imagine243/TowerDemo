//
//  BevTree.h
//  TowerDemo
//
//  Created by chao on 14/10/11.
//
//

#ifndef __TowerDemo__BevTree__
#define __TowerDemo__BevTree__

#include <stdio.h>
#include <string>
#include "BevUtil.h"

namespace BehaviorTree {
    
#define Limited_MaxChildNodeCount               16
#define Limited_InvalidChildNodeIndex           Limited_MaxChildNodeCount
    
    enum BevRunningStatus
    {
        BRS_Executing					= 0,
        BRS_Finish                      = 1,
        BRS_ERROR_Transition			= -1,
    };
    
    enum TerminalNodeStaus
    {
        TNS_Ready         = 1,
        TNS_Running       = 2,
        TNS_Finish        = 3,
    };
    
    enum ParallelFinishCondition
    {
        PFC_OR = 1,
        PFC_AND
    };
    
    typedef AnyData InputParam;
    typedef AnyData OutputParam;
    
    class BevNodePrecondition
    {
    public:
        virtual bool ExternalCondition(const InputParam & input) const = 0;
        virtual ~BevNodePrecondition() = default;
    };
    
    class BevNodePreconditionTRUE : public BevNodePrecondition
    {
    public:
        virtual bool ExternalCondition(const InputParam & input) const{
            return true;
        }
    };
    
    class BevNodePreconditionFALSE : public BevNodePrecondition
    {
    public:
        virtual bool ExternalCondition(const InputParam & input) const{
            return false;
        };
    };
    
    class BevNodePreconditionNOT : public BevNodePrecondition
    {
    public:
        BevNodePreconditionNOT(BevNodePrecondition * _lhs):lhs(_lhs){
            ASSERT(lhs);
        }
        
        ~BevNodePreconditionNOT()
        {
            SAFE_DELETE(lhs);
        }
        
        
        virtual bool ExternalCondition(const InputParam & input) const{
            return !lhs->ExternalCondition(input);
        }
        
    private:
        BevNodePrecondition * lhs;
    };
    
    class BevNodePreconditionAND : public BevNodePrecondition
    {
    public:
        BevNodePreconditionAND(BevNodePrecondition * _lhs, BevNodePrecondition * _rhs)
        :lhs(_lhs),rhs(_rhs)
        {
            ASSERT(lhs);
            ASSERT(rhs);
        }
        
        ~BevNodePreconditionAND()
        {
            SAFE_DELETE(lhs);
            SAFE_DELETE(rhs);
        }
        
        virtual bool ExternalCondition(const InputParam & input) const{
            return lhs->ExternalCondition(input) && rhs->ExternalCondition(input);
        }
    private:
        BevNodePrecondition * lhs;
        BevNodePrecondition * rhs;
    };
    
    class BevNodePreconditionOR : public BevNodePrecondition
    {
    public:
        BevNodePreconditionOR(BevNodePrecondition * _lhs, BevNodePrecondition * _rhs)
        :lhs(_lhs),rhs(_rhs)
        {
            ASSERT(lhs);
            ASSERT(rhs);
        }
        
        ~BevNodePreconditionOR()
        {
            SAFE_DELETE(lhs);
            SAFE_DELETE(rhs);
        }
        virtual bool ExternalCondition(const InputParam & input) const{
            return lhs->ExternalCondition(input) || rhs->ExternalCondition(input);
        }
    private:
        BevNodePrecondition * lhs;
        BevNodePrecondition * rhs;
    };
    
    class BevNodePreconditionXOR : public BevNodePrecondition
    {
    public:
        BevNodePreconditionXOR(BevNodePrecondition * _lhs, BevNodePrecondition * _rhs)
        :lhs(_lhs),rhs(_rhs)
        {
            ASSERT(lhs);
            ASSERT(rhs);
        }
        
        ~BevNodePreconditionXOR()
        {
            SAFE_DELETE(lhs);
            SAFE_DELETE(rhs);
        }
        virtual bool ExternalCondition(const InputParam & input) const{
            return lhs->ExternalCondition(input) ^ rhs->ExternalCondition(input);
        }
        
    private:
        BevNodePrecondition * lhs;
        BevNodePrecondition * rhs;
    };
    
    class BevNode
    {
    public:
        BevNode(BevNode * _parentNode , BevNodePrecondition * _NodePrecondition = nullptr)
        :childCount(0)
        ,debugName("UNNAMED")
        ,activeNode(nullptr)
        ,lastActiveNode(nullptr)
        ,nodePrecondition(nullptr)
        {
            for (int i = 0; i < Limited_MaxChildNodeCount; i++) {
                childNodeList[i] = nullptr;
            }
            _SetParentNode(_parentNode);
            SetNodePrecondition(_NodePrecondition);
        }
        
        virtual ~BevNode()
        {
            for (int i = 0; i < childCount; i++) {
                SAFE_DELETE(childNodeList[i]);
            }
            
            SAFE_DELETE(nodePrecondition);
        }
        
        bool Evaluate(const InputParam & input)
        {
            return  (nodePrecondition == nullptr || nodePrecondition->ExternalCondition(input)) && _DoEvaluate(input);
        }
        
        void Transition(const InputParam & input)
        {
            _DoTransition(input);
        }
        
        BevRunningStatus Tick(const InputParam& input, const OutputParam& output)
        {
            return _DoTick(input, output);
        }
        
        BevNode& AddChildNode(BevNode * _ChildNode)
        {
            if (childCount == Limited_MaxChildNodeCount) {
                OUTPUT("number of child is %d \n", 100);
                ASSERT(0);
                return (*this);
            }
            childNodeList[childCount] = _ChildNode;
            ++childCount;
            return (*this);
        }
        
        BevNode& SetNodePrecondition(BevNodePrecondition * _NodePrecondition)
        {
            if (nodePrecondition != _NodePrecondition) {
                if (nodePrecondition) {
                    SAFE_DELETE(nodePrecondition);
                    nodePrecondition = _NodePrecondition;
                }
            }
            return (*this);
        }
        
        BevNode& SetDebugName(const char * _debugName)
        {
            debugName = _debugName;
            return(*this);
        }
        
        const char* GetDebugName() const
        {
            return debugName.c_str();
        }
        
        
        void SetActiveNode(BevNode * _node)
        {
            lastActiveNode = activeNode;
            activeNode = _node;
            if (parentNode != nullptr) {
                parentNode->SetActiveNode(_node);
            }
        }
        
        const BevNode * GetLastActiveNode() const
        {
            return lastActiveNode;
        }
        
    protected:
        
        virtual bool _DoEvaluate(const InputParam& input)
        {
            return true;
        }
        
        virtual void _DoTransition(const InputParam& input)
        {
        }
        
        virtual BevRunningStatus _DoTick(const InputParam & input, const OutputParam & output)
        {
            return BRS_Finish;
        }
        
    protected:
        void _SetParentNode(BevNode * _parentNode)
        {
            parentNode = _parentNode;
        }
        
        bool _CheckIndex(int _index) const
        {
            return _index >= 0 && _index < childCount;
        }
    protected:
        BevNode * childNodeList[Limited_MaxChildNodeCount];
        int childCount;
        BevNode * parentNode;
        BevNode * activeNode;
        BevNode * lastActiveNode;
        BevNodePrecondition * nodePrecondition;
        std::string debugName;
    };
    
    class BevNodePrioritySelector : public BevNode
    {
    public:
        BevNodePrioritySelector(BevNode * _parentNode, BevNodePrecondition * _nodePrecondition = nullptr)
        :BevNode(_parentNode,_nodePrecondition)
        ,currentSelectIndex(Limited_InvalidChildNodeIndex)
        ,lastSelectIndex(Limited_InvalidChildNodeIndex)
        {
        }
    protected:
        virtual bool _DoEvaluate(const InputParam& input);
        virtual void _DoTransition(const InputParam& input);
        virtual BevRunningStatus _DoTick(const InputParam & input, const OutputParam & output);
    protected:
        int currentSelectIndex;
        int lastSelectIndex;
    };
    
    class BevNodeNonePrioritySelector : public BevNodePrioritySelector
    {
    public:
        BevNodeNonePrioritySelector(BevNode * _parentNode, BevNodePrecondition * _nodePrecondition = nullptr)
        :BevNodePrioritySelector(_parentNode,_nodePrecondition)
        {}
        
    protected:
        virtual bool _DoEvaluate(const InputParam& input);
    };
    
    class BevNodeSequence : public BevNode
    {
    public:
        BevNodeSequence(BevNode* _parentNode, BevNodePrecondition *_nodePrecondition = nullptr)
        :BevNode(_parentNode,_nodePrecondition)
        ,currentNodeIndex(Limited_InvalidChildNodeIndex)
        {}
    protected:
        virtual bool _DoEvaluate(const InputParam& input);
        virtual void _DoTransition(const InputParam& input);
        virtual BevRunningStatus _DoTick(const InputParam & input, const OutputParam & output);
    private:
        int currentNodeIndex;
    };
    
    class BevNodeTerminal : public BevNode
    {
    public:
        BevNodeTerminal(BevNode* _parentNode, BevNodePrecondition* _nodePrecondition = nullptr)
        :BevNode(_parentNode,_nodePrecondition)
        ,myStatus(TNS_Ready)
        ,isNeedExit(false)
        {}
    protected:
        virtual void _DoTransition(const InputParam& input);
        virtual BevRunningStatus _DoTick(const InputParam & input, OutputParam & output);
    protected:
        virtual void _DoEnter(const InputParam& input){};
        virtual BevRunningStatus _DoExecute(const InputParam& input ,OutputParam& output) {return BRS_Finish;};
        virtual void _DoExit(const InputParam& input, BevRunningStatus _exitId){};
    private:
        TerminalNodeStaus myStatus;
        bool isNeedExit;
    };
    
    class BevNodeParallel : public BevNode
    {
    public:
        BevNodeParallel(BevNode * _parentNode, BevNodePrecondition* _nodePrecondition = nullptr)
        :BevNode(_parentNode, _nodePrecondition)
        ,myFinishCondition(PFC_OR)
        {
            for (unsigned int i = 0; i < Limited_MaxChildNodeCount; i++) {
                childNodeStatusList[i] = BRS_Executing;
            }
        }
        
        virtual bool _DoEvaluate(const InputParam& input);
        virtual void _DoTransition(const InputParam& input);
        virtual BevRunningStatus _DoTick(const InputParam & input, const OutputParam & output);
        
        BevNodeParallel& SetFinishCondition(ParallelFinishCondition _condition);
    private:
        ParallelFinishCondition myFinishCondition;
        BevRunningStatus childNodeStatusList[Limited_MaxChildNodeCount];
    };
    
    class BevNodeLoop : public BevNode
    {
    public:
        static const int kInfinishLoop = -1;
    public:
        BevNodeLoop(BevNode * _parentNode, BevNodePrecondition * _nodePrecondition = nullptr, int _loopCount = kInfinishLoop)
        :BevNode(_parentNode,_nodePrecondition)
        ,myLoopCount(_loopCount)
        ,myCurrentCount(0)
        {}
        
        virtual bool _DoEvaluate(const InputParam& input);
        virtual void _DoTransition(const InputParam& input);
        virtual BevRunningStatus _DoTick(const InputParam & input, const OutputParam & output);
    private:
        int myLoopCount;
        int myCurrentCount;
    };
}

#endif /* defined(__TowerDemo__BevTree__) */
