#include <SDL2/SDL.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "share.h"
typedef void* LibHandle;

char* StrTrim(char* str)
{
    for(; *str && isspace(*str); ++str);
    char* start = str;
    char* end = str;
    for(; *str; ++str) if(!isspace(*str)) end = str+1;
    *end = '\0';
    return start;
}


static void PrintLibInfo(const char* lib_filename)
{
    printf("Loading library from %s\n", lib_filename);

    LibHandle lib = SDL_LoadObject(lib_filename);

    if(!lib)
    {
        printf("    Library %s couldn't be loaded\n", lib_filename);
        return;
    }

    void* pGetLibInfo = SDL_LoadFunction(lib, "GetLibInfo");
    if(pGetLibInfo != NULL)
    {
        const LibInfoHead* info_head = ((GetLibInfo_Func)pGetLibInfo)();
        printf("    Name: %s\n", info_head->name);
        printf("    ABI Version: %i\n", info_head->abi_version);
        if(info_head->abi_version == ABI_VERSION)
        {
            const LibInfo* info = (LibInfo*)info_head;
            printf("    Description: %s\n", info->description);
            printf("    Now calling init()\n");
            info->init();
        }
        else // incompatible abi
        {
            printf("    No further information available due to incompatible abi version:\n");
            printf("        Expected version: %i\n"
                   "        Provided version: %i\n", 
                   ABI_VERSION,
                   info_head->abi_version);

        }
    }
    else
    {
        printf("    No information available, because library does not provide \"GetLibInfo\"\n");
    }
    SDL_UnloadObject(lib);
}



extern void SharedFunc(void)
{
    printf("SharedFunc\n");
}

int main(int argc, char** argv)
{
    printf("Starting...\n");
    printf("ABI Version: %i\n", ABI_VERSION);

    FILE* lib_list = fopen("libraries.txt", "r");
    while(!feof(lib_list))
    {
        char buf[1024];
        if(fgets(buf, sizeof(buf), lib_list) == NULL)
            break;

        char* line = StrTrim(buf);
        size_t line_len = strlen(line);
        if(line_len && line[0] != '#') // not an empty line or comment
        {
#ifdef __WINNT__
            strncpy(line+line_len, ".dll", (buf+sizeof(buf))-(line+line_len));
            buf[sizeof(buf)-1] = '\0';
#endif
            const char* lib_name = line;
            PrintLibInfo(lib_name);
        }
    }
    fclose(lib_list);

    return 0;
}
