//
//  BevUtil.h
//  TowerDemo
//
//  Created by chao on 14/10/11.
//
//

#ifndef __TowerDemo__BevUtil__
#define __TowerDemo__BevUtil__

#include <stdio.h>
#include "util.h"

using namespace utils;

namespace BehaviorTree {
    class AnyData
    {
    public:
        template<typename RealDataType>
        AnyData(RealDataType * data):realData(data){};
        
        template<typename RealDataType>
        RealDataType& GetRealDataType(){
            ASSERT(realData);
            return *reinterpret_cast<RealDataType *>(realData);
        }
        
        template<typename RealDataType>
        RealDataType& GetRealDataType() const{
            ASSERT(realData);
            return *reinterpret_cast<const RealDataType *>(realData);
        }
        
        template<typename RealDataType>
        AnyData& operator =(RealDataType * _Data)
        {
            Set(_Data);
            return *this;
        }
    private:
        template<typename RealDataType>
        void Set(RealDataType* _Data)
        {
            realData = reinterpret_cast<void *>(_Data);
        }
    private:
        void* realData;
    };
};

#endif /* defined(__TowerDemo__BevUtil__) */
