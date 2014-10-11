//
//  util.h
//  TowerDemo
//
//  Created by chao on 14/10/11.
//
//

#ifndef __TowerDemo__util__
#define __TowerDemo__util__

#include <stdio.h>
#include <assert.h>

namespace utils {
#define ASSERT(cond) assert(cond)

#define SAFE_DELETE(p)           do { delete (p); (p) = nullptr; } while(0)
#define SAFE_DELETE_ARRAY(p)     do { if(p) { delete[] (p); (p) = nullptr; } } while(0)
#define SAFE_FREE(p)             do { if(p) { free(p); (p) = nullptr; } } while(0)
#define BREAK_IF(cond)           if(cond) break
    
#define OUTPUT(format, ... )     printf(format, ##__VA_ARGS__)
}

#endif /* defined(__TowerDemo__util__) */
