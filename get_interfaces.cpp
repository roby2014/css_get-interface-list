
#include "get_interfaces.h"

void init::get_interfaces() 
{
    // Get dll modules
    uintptr_t dll_client         = (uintptr_t) GetModuleHandleA("client.dll");
    uintptr_t dll_engine         = (uintptr_t) GetModuleHandleA("engine.dll");
    uintptr_t dll_vgui2          = (uintptr_t) GetModuleHandleA("vgui2.dll");
    uintptr_t dll_vstdlib        = (uintptr_t) GetModuleHandleA("vstdlib.dll");
    uintptr_t dll_vguimatsurface = (uintptr_t) GetModuleHandleA("vguimatsurface.dll");

    // Get interface list
    InterfaceReg* client_interface_list         
        = **(InterfaceReg***)utils::find_pattern((char*)"\x89\x01\xa1\x00\x00\x00\x00\x89\x41\x08\x8b\xc1 ", (char*)"xxx????xxxxx", dll_client, 0x552EC8, 3);

    InterfaceReg *engine_interface_list         
        = **(InterfaceReg***)utils::find_pattern((char*)"\xa1\x00\x00\x00\x00\x89\x41\x08\x8b\xc1", (char*)"x????xxxxx", dll_engine, 0x243FF5 , 1);

    InterfaceReg *vgui2_interface_list          
        = **(InterfaceReg***)utils::find_pattern((char*)"\xa1\x00\x00\x00\x00\x89\x41\x08\x8b\xc1", (char*)"x????xxxxx", dll_vgui2, 0x1EE45 , 1);

    InterfaceReg *vstdlib_interface_list        
        = **(InterfaceReg***)utils::find_pattern((char*)"\xa1\x00\x00\x00\x00\x89\x41\x08\x8b\xc1", (char*)"x????xxxxx", dll_vstdlib, 0xBCDA , 1);

    InterfaceReg *vguimatsurface_interface_list 
        = **(InterfaceReg***)utils::find_pattern((char*)"\xa1\x00\x00\x00\x00\x89\x41\x08\x8b\xc1", (char*)"x????xxxxx", dll_vguimatsurface, 0x6DF51 , 1);
    
    // Debug 'em
    dbgprint(client_interface_list);
    dbgprint(engine_interface_list);
    dbgprint(vguimatsurface_interface_list);
    dbgprint(vstdlib_interface_list);
    dbgprint(vgui2_interface_list);

    // Get interface pointers
    uintptr_t* client      = get_interface_ptr<uintptr_t*>("VClient017", client_interface_list);
    uintptr_t* engine      = get_interface_ptr<uintptr_t*>("VEngineClient013", engine_interface_list);
    uintptr_t* panel       = get_interface_ptr<uintptr_t*>("VGUI_Panel009", vgui2_interface_list); 
    uintptr_t* entity_list = get_interface_ptr<uintptr_t*>("VClientEntityList003", client_interface_list);
    uintptr_t* cvar        = get_interface_ptr<uintptr_t*>("VEngineCvar004", vstdlib_interface_list);
    uintptr_t* surface     = get_interface_ptr<uintptr_t*>("VGUI_Surface030", vguimatsurface_interface_list);

    // Debug all interfaces if you want
    debug_interface_list(client_interface_list);

    // ...
}


// UTILS (s/o BigMo/Zat-s-CSGO-Simple)
// You can use your find pattern function anyways.
uintptr_t utils::find_pattern(char* pattern, char* mask, uintptr_t start, uintptr_t end, uintptr_t offset) 
{
	int patternLength = strlen(mask);
	bool found = false;

	//For each byte from start to end
	for (uintptr_t i = start; i < (start+end) - patternLength; i++)
	{
		found = true;
		//For each byte in the pattern
		for (int idx = 0; idx < patternLength; idx++)
		{
			if (mask[idx] == 'x' && pattern[idx] != *(char*)(i + idx))
			{
				found = false;
				break;
			}
		}
		if (found)
		{
			return i + offset;
		}
	}
	return 0;
}
