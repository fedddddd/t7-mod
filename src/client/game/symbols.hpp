#pragma once

#define WEAK __declspec(selectany)

namespace game
{
	// Functions

	WEAK symbol<void(int localClientNum, const char* text)> Cbuf_AddText{0x1404F75B0};

	WEAK symbol<void(const char* cmdName, void(), cmd_function_s* allocedCmd)> Cmd_AddCommandInternal{0x1404F8210};
	WEAK symbol<void(int localClientNum, int controllerIndex, const char* text, bool fromRemoteConsole)> Cmd_ExecuteSingleCommand{0x1404F8890};

	WEAK symbol<void(const char* file, int line, errorParm code, const char* message, ...)> Com_Error{0x140501470};

	WEAK symbol<dvar_t*(dvarStrHash_t hash, const char* dvarName, int value, int min, int max, unsigned int flags, const char* description)> Dvar_RegisterInt{0x14057B370};
	WEAK symbol<dvar_t*(dvarStrHash_t hash, const char* dvarName, bool value, unsigned int flags, const char* description)> Dvar_RegisterBool{0x14057B500};
	WEAK symbol<dvar_t*(dvarStrHash_t hash, const char* dvarName, float value, float min, float max, unsigned int flags, const char* description)> Dvar_RegisterFloat{0x14057B430};
	WEAK symbol<dvar_t*(dvarStrHash_t hash, const char* dvarName, const char* value, unsigned int flags, const char* description)> Dvar_RegisterString{0x14057B890};
	WEAK symbol<unsigned int(const char* name)> Dvar_GenerateHash{0x140185800};

	WEAK symbol<TLSData*()> Sys_GetTLS{0x140525EB0};
	WEAK symbol<bool()> Sys_IsDatabaseReady2{0x1405261B0};

	// Variables

	WEAK symbol<DWORD> threadIds{0x14A0368B0};

	namespace hks
	{
		WEAK symbol<lua_State*> lua_state{0x14858C408};
		WEAK symbol<void(lua_State* s, const char* str, unsigned int l)> hksi_lua_pushlstring{0x1401DE6F0};
		WEAK symbol<void(lua_State* s, const HksObject* tbl, const HksObject* key, const HksObject* val)> hks_obj_settable{0x1403F41B0};
		WEAK symbol<HksObject* (HksObject* result, lua_State* s, const HksObject* table, const HksObject* key)> hks_obj_gettable{0x1403F3750};
		WEAK symbol<void(lua_State* s, int nargs, int nresults, const unsigned int* pc)> vm_call_internal{0x140418E40};
		WEAK symbol<HashTable*(lua_State* s, unsigned int arraySize, unsigned int hashSize)> Hashtable_Create{0x1403E46D0};
		WEAK symbol<cclosure*(lua_State* s, lua_function function, int num_upvalues, 
			int internal_, int profilerTreatClosureAsFunc)> cclosure_Create{0x1403E48C0};
		WEAK symbol<int(lua_State* s, int t)> hksi_luaL_ref{0x1403F5CF0};
		WEAK symbol<void(lua_State* s, int t, int ref)> hksi_luaL_unref{0x1403F5E70};
	}
}