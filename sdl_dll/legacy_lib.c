#include <stdio.h>
#include "lib_impl.h"

static void LibInit(void);

static const LibInfo lib_info =
{
    .head = {
        .name = "Legacy Library",
        .abi_version = ABI_VERSION-1, // You shouldn't usually change ABI_VERSION,
                                      // just for demonstration
    },
    .init = &LibInit,
    .description = "This is a dynamic library for testing dll versioning",
};

const LibInfoHead* GetLibInfo(void)
{
    return &lib_info.head;
}

static void LibInit(void)
{
    printf("Initializing library called \"%s\"\n", lib_info.head.name);
}
