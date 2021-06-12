#ifdef LIB_IMPL_H
#error You should only include lib_impl.h in your main library source
#else
#define LIB_IMPL_H
#endif

#include "share.h"
const LibInfoHead* GetLibInfo(void);
