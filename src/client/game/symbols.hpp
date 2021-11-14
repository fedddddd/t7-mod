#pragma once

#define WEAK __declspec(selectany)

namespace game
{
	// Functions

	WEAK symbol<void(int inst, VariableValue* value)> AddRefToValue{0x1401657E0};
	WEAK symbol<void(int inst, unsigned int id)> AddRefToObject{0x140165990};
	WEAK symbol<unsigned int(int inst, unsigned int id)> AllocThread{0x140165D70};
	WEAK symbol<void(int inst, VariableValue* value)> RemoveRefToValue{0x14016C7C0};
	WEAK symbol<void(int inst, unsigned int id)> RemoveRefToObject{0x14016C950};

	WEAK symbol<void(int localClientNum, const char* text)> Cbuf_AddText{0x1404F75B0};

	WEAK symbol<void(const char* cmdName, void(), cmd_function_s* allocedCmd)> Cmd_AddCommandInternal{0x1404F8210};
	WEAK symbol<void(int localClientNum, int controllerIndex, const char* text, bool fromRemoteConsole)> Cmd_ExecuteSingleCommand{0x1404F8890};

	WEAK symbol<void(const char* file, int line, errorParm code, const char* message, ...)> Com_Error{0x140501470};

	WEAK symbol<dvar_t*(dvarStrHash_t hash, const char* dvarName, int value, 
		int min, int max, unsigned int flags, const char* description)> Dvar_RegisterInt{0x14057B370};
	WEAK symbol<dvar_t*(dvarStrHash_t hash, const char* dvarName, bool value, 
		unsigned int flags, const char* description)> Dvar_RegisterBool{0x14057B500};
	WEAK symbol<dvar_t*(dvarStrHash_t hash, const char* dvarName, float value, 
		float min, float max, unsigned int flags, const char* description)> Dvar_RegisterFloat{0x14057B430};
	WEAK symbol<dvar_t*(dvarStrHash_t hash, const char* dvarName, 
		const char* value, unsigned int flags, const char* description)> Dvar_RegisterString{0x14057B890};
	WEAK symbol<unsigned int(const char* name)> Dvar_GenerateHash{0x140185800};

	WEAK symbol<unsigned int(int inst, int entnum, unsigned int classnum, int localclientnum)> FindEntityId{0x14016A830};
	WEAK symbol<VariableValue(int inst, unsigned int classnum, EntRefUnion entRefUnion, 
		unsigned int clientNum, int offset)> GetEntityFieldValue{0x140170DB0};

	WEAK symbol<const float* (int inst, const float* v)> Scr_AllocVector{0x140166070};
	WEAK symbol<void(int inst)> Scr_ClearOutParams{0x14016FD50};
	WEAK symbol<scr_entref_t(int inst, unsigned int entId)> Scr_GetEntityIdRef{0x14016ADC0};
	WEAK symbol<int(unsigned int classnum, EntRefUnion entnum, int offset)> Scr_SetObjectField{0x1402F62F0};
	WEAK symbol<void(int inst, int clientNum, unsigned int id,
		scr_string_t stringValue, unsigned int paramcount)> Scr_NotifyId{0x1401D4E20};

	WEAK symbol<scr_string_t(const char* str)> SL_GenerateCanonicalString{0x140159970};
	WEAK symbol<const char*(scr_string_t stringValue)> SL_ConvertToString{0x1401632C0};
	WEAK symbol<const char*(scr_string_t stringValue)> SL_LookupCanonicalString{0x140159BD0};
	WEAK symbol<scr_string_t(const char* str, unsigned int user, int type)> SL_GetString{0x140163D90};

	WEAK symbol<unsigned int(int inst, unsigned int localId,
		const char* pos, unsigned int paramcount)> VM_Execute{0x140173690};

	WEAK symbol<TLSData*()> Sys_GetTLS{0x140525EB0};
	WEAK symbol<bool()> Sys_IsDatabaseReady2{0x1405261B0};

	WEAK symbol<void*(jmp_buf* Buf, int Value)> longjmp{0x140ABC7B0};
	WEAK symbol<int(jmp_buf* Buf)> _setjmp{0x140ABC8B0};

	// Variables

	WEAK symbol<DWORD> threadIds{0x14A0368B0};

	WEAK symbol<int> level_time{0x1474FDC94};

	WEAK symbol<int> g_script_error_level{0x1426D7678};
	WEAK symbol<jmp_buf> g_script_error{0x1426D7710};
	WEAK symbol<unsigned int> levelEntityId{0x1426BE0AC};

	WEAK symbol<scrVmPub_t> scr_VmPub{0x1426BE190};
	WEAK symbol<scrVarGlob_t> scr_VarGlob{0x1426BDF00};
	WEAK symbol<const char*> scr_error_message{0x1426BE090};

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