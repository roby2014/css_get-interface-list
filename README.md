# CS:S Get interface list

**Just a quick example on how to get interface list from game modules with <a href="https://github.com/ValveSoftware/source-sdk-2013/blob/master/sp/src/public/tier1/interface.h#L72">s_pInterfaceRegs</a> (<a href="https://github.com/ValveSoftware/source-sdk-2013/blob/master/sp/src/tier1/interface.cpp#L68">CreateInterfaceInternal</a>), in CS:S. :alien:**  

_Well you could sigscan for every interface pointer OR use exported "CreateInterface", but this way is easier/cleaner imo. (and gets u everything u need basically)_ 
   
   
> Signatures btw:
```
client_interface_list;         /* 89 01 a1 ? ? ? ? 89 41 08 8b c1 (client.dll)   */
engine_interface_list;         /* a1 ? ? ? ? 89 41 08 8b c1 (engine.dll)         */
vguimatsurface_interface_list; /* a1 ? ? ? ? 89 41 08 8b c1 (vguimatsurface.dll) */
vstdlib_interface_list;        /* a1 ? ? ? ? 89 41 08 8b c1 (vstdlib.dll)        */
vgui2_interface_list;          /* a1 ? ? ? ? 89 41 08 8b c1 (vgui2.dll)          */
```
   

> By getting the interface list, you can easily get a pointer to your desired interface.
```c++
InterfaceReg* client_interface_list         
      = **(InterfaceReg***)utils::find_pattern((char*)"\x89\x01\xa1\x00\x00\x00\x00\x89\x41\x08\x8b\xc1 ", (char*)"xxx????xxxxx", dll_client, 0x552EC8, 3);

InterfaceReg* engine_interface_list         
      = **(InterfaceReg***)utils::find_pattern((char*)"\xa1\x00\x00\x00\x00\x89\x41\x08\x8b\xc1", (char*)"x????xxxxx", dll_engine, 0x243FF5 , 1);

InterfaceReg* vgui2_interface_list          
      = **(InterfaceReg***)utils::find_pattern((char*)"\xa1\x00\x00\x00\x00\x89\x41\x08\x8b\xc1", (char*)"x????xxxxx", dll_vgui2, 0x1EE45 , 1);

InterfaceReg* vstdlib_interface_list        
      = **(InterfaceReg***)utils::find_pattern((char*)"\xa1\x00\x00\x00\x00\x89\x41\x08\x8b\xc1", (char*)"x????xxxxx", dll_vstdlib, 0xBCDA , 1);

InterfaceReg* vguimatsurface_interface_list 
      = **(InterfaceReg***)utils::find_pattern((char*)"\xa1\x00\x00\x00\x00\x89\x41\x08\x8b\xc1", (char*)"x????xxxxx", dll_vguimatsurface, 0x6DF51 , 1);
```
```c++
uintptr_t* client      = get_interface_ptr<uintptr_t*>("VClient017", client_interface_list);
uintptr_t* engine      = get_interface_ptr<uintptr_t*>("VEngineClient013", engine_interface_list);
uintptr_t* panel       = get_interface_ptr<uintptr_t*>("VGUI_Panel009", vgui2_interface_list); 
uintptr_t* entity_list = get_interface_ptr<uintptr_t*>("VClientEntityList003", client_interface_list);
uintptr_t* cvar        = get_interface_ptr<uintptr_t*>("VEngineCvar004", vstdlib_interface_list);
uintptr_t* surface     = get_interface_ptr<uintptr_t*>("VGUI_Surface030", vguimatsurface_interface_list);
```
![alt text](https://i.imgur.com/3KVj9o3.jpeg)

   

> If you want to debug all interfaces from the list:
```c++
debug_interface_list(InterfaceReg* interface_list);
```
![alt text](https://i.imgur.com/cqLRhaO.jpeg)

<br/><br/>
**Now you can use interface pointers and do what you want! :wink:  
Anyways, nothing special, (my code sucks) but enjoy. :+1:**  
