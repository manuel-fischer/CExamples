#pragma once

typedef int AbiVersion;
#define ABI_VERSION 2

// Stable structure, that should not change!
typedef struct LibInfoHead
{
    const char* name;
    AbiVersion abi_version; // The abi version the dll was compiled against
} LibInfoHead;

// Structure that might change along the versions
typedef struct LibInfo
{
    LibInfoHead head;
    const char* description;
    void(*init)(void);
} LibInfo;

typedef const LibInfoHead* (*GetLibInfo_Func)(void);
