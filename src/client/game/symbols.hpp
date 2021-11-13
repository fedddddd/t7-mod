#pragma once

#define WEAK __declspec(selectany)

namespace game
{
	// Functions

	WEAK symbol<void(int localClientNum, const char* text)> Cbuf_AddText{0x1404F75B0};

	WEAK symbol<void(const char* cmdName, void(), cmd_function_s* allocedCmd)> Cmd_AddCommandInternal{0x1404F8210};
	WEAK symbol<void(int localClientNum, int controllerIndex, const char* text, bool fromRemoteConsole)> Cmd_ExecuteSingleCommand{0x1404F8890};

	WEAK symbol<dvar_t*(dvarStrHash_t hash, const char* dvarName, int value, int min, int max, unsigned int flags, const char* description)> Dvar_RegisterInt{0x14057B370};
	WEAK symbol<dvar_t*(dvarStrHash_t hash, const char* dvarName, bool value, unsigned int flags, const char* description)> Dvar_RegisterBool{0x14057B500};
	WEAK symbol<dvar_t*(dvarStrHash_t hash, const char* dvarName, float value, float min, float max, unsigned int flags, const char* description)> Dvar_RegisterFloat{0x14057B430};
	WEAK symbol<dvar_t*(dvarStrHash_t hash, const char* dvarName, const char* value, unsigned int flags, const char* description)> Dvar_RegisterString{0x14057B890};
	WEAK symbol<unsigned int(const char* name)> Dvar_GenerateHash{0x140185800};

	WEAK symbol<TLSData*()> Sys_GetTLS{0x140525EB0};

	// Variables

	namespace hks
	{
		WEAK symbol<lua_State*> lua_state{0x14858C408};
	}
}