#include <stdio.h>
#include "lib_impl.h"

static void LibInit(void);

static const LibInfo lib_info =
{
    .head = {
        .name = "Some Library",
        .abi_version = ABI_VERSION,
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
    printf(">>Initializing library called \"%s\"<<\n", lib_info.head.name);
}
