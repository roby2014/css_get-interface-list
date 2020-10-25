#pragma once

#include <Windows.h>
#include <stdio.h>
#include <string>

#define dbgprint(x)  printf_s("%32s found at 0x%8x\n", #x, x);
#define dbglist(x,y) printf_s("%50s => %8x \n", x, y);


namespace init {
    void get_interfaces(void);
}

namespace utils {
    uintptr_t find_pattern(char *pattern, char *mask, uintptr_t start, uintptr_t end, uintptr_t offset);
}


/* https://github.com/ValveSoftware/source-sdk-2013/blob/master/sp/src/public/tier1/interface.h#L69#L83
 */
typedef void *(*InstantiateInterfaceFn)();
struct InterfaceReg {
    InstantiateInterfaceFn m_CreateFn;
    const char *m_pName;
    InterfaceReg *m_pNext;
};

template <typename T> 
inline T get_interface_ptr(const char *name, InterfaceReg *interface_list) 
{
    for (InterfaceReg *current = interface_list; current; current = current->m_pNext) {
        if (!strcmp(name, current->m_pName)) {
            printf("\n %32s => %8x", current->m_pName, current->m_CreateFn());
            return (T)current->m_CreateFn();
        }
    }
    printf("\n [ GetInterfacePtr() ] Interface \"%s\" not found :( \n", name);
}

inline void debug_interface_list(InterfaceReg *interface_list) 
{
    printf("\n\n\n");
    for (InterfaceReg *current = interface_list; current; current = current->m_pNext) // s/o aixxe tut
        dbglist(current->m_pName, current->m_CreateFn());
    printf("\n\n");
}
