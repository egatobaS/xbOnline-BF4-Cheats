#pragma once

extern "C" 	VOID XapiThreadStartup( VOID(__cdecl *StartRoutine)(VOID *), PVOID StartContext, DWORD dwExitCode );

extern "C" 	BOOL MmIsAddressValid(PVOID Address);
extern "C" 	PVOID MmGetPhysicalAddress(PVOID Address);
extern "C"  DWORD ExCreateThread(PHANDLE pHandle, DWORD dwStackSize, LPDWORD lpThreadId, PVOID apiThreadStartup, LPTHREAD_START_ROUTINE lpStartAddress, LPVOID lpParameter, DWORD dwCreationFlagsMod);
extern "C" 	long XexGetModuleHandle(PSZ moduleName, PHANDLE hand);
extern "C" 	DWORD XexGetProcedureAddress(HANDLE hand, DWORD dwOrdinal, PVOID Address);

extern int(*DbgPrintf)(const char*, ...);
extern int(*g_snprintf)(char* _Dest, size_t Count, const char* _Format, ...);
extern int(*Com_Sprintf)(char *Buffer, int size, const char *fmt, ...);

extern Vector2 pSilent;

extern ClientVehicleEntity* pCVE;

extern unsigned int WaitTime;
extern unsigned int TimeCount;

extern int NearestPlayer;

extern bool SetSilentAimFlags;
extern bool isClientWallable[24];
extern bool Autowallable;

enum miscKey_t {
	KEY_LT = 0x5555,
	KEY_RT = 0x6666
};

int GetAsyncKeyState(DWORD KEY);

void DrawBorderBox(float x, float y, float width, float height, float thickness, Vector4 * color);

bool GetBone(ClientSoldierEntity * pEnt, Vector3 * vOut, int BoneId);

bool WorldToScreen(Vector3 WorldPos, Vector3 * ScreenPos);

void DrawBoneLine(ClientPlayer * entity, int tagname1, int tagname2, Vector4 * col);

void DoAllBones(ClientPlayer * Client, Vector4 * boneESPCol);

void DoFlyHack(ClientPlayer * GetLocalPlayer);

void SendSpottingMessage(ClientPlayer * LocalPlayer, ClientPlayer * Target, SpotType type, float Frequency);

void ESP(int USP);

void DrawAmmoBoxs(ClientPlayer * LocalEntity, int USP);

void DrawVehicles(ClientPlayer * LocalEntity, int USP);

void DrawCircle(float points, float radius, Vector3 Pos, Vector4 Color);

void DrawExplosives(ClientPlayer * LocalPlayer, int sp);

void DrawGrenade(ClientPlayer * LocalPlayer, int sp);

void DrawPickups(ClientPlayer * LocalPlayer, int sp);

void VehicleESP(ClientVehicleEntity * pVehicle, Vector4 * cVeh, Vector3 Pos);

void TeamHealing(ClientPlayer * localPlayer);

void DoInvisible();

void SendDamageMessage(ClientPlayer * Target, ClientPlayer * LocalPlayer, float damage, SoldierWeaponUnlockAsset * Weapon, int HitType);

void DoEntityDrawings(int r3);

void DrawRadar();

bool Draw2DBox(ClientPlayer* pPlayer, Vector4 color, float size);

bool TransformDrawAABB(ClientVehicleEntity * pEnt, Vector4 color, float size);

void Wait(int time);

DWORD GetModuleImport(HANDLE HModule, HANDLE HImportedModule, DWORD Ordinal);

DWORD GetAddr(DWORD dwModuleBaseAddr, int Ordinal);

bool MmIsAddressValidPtr(void* ptr);

typedef struct _UNICODE_STRING {
	USHORT Length;
	USHORT MaximumLength;
	PWSTR  Buffer;
} UNICODE_STRING, *PUNICODE_STRING;

typedef struct _STRING {
	USHORT Length;
	USHORT MaximumLength;
	PCHAR Buffer;
} STRING, *PSTRING;

typedef struct _LDR_DATA_TABLE_ENTRY {
	LIST_ENTRY InLoadOrderLinks;
	LIST_ENTRY InClosureOrderLinks;
	LIST_ENTRY InInitializationOrderLinks;
	PVOID NtHeadersBase;
	PVOID ImageBase;
	DWORD SizeOfNtImage;
	UNICODE_STRING FullDllName;
	UNICODE_STRING BaseDllName;
	DWORD Flags;
	DWORD SizeOfFullImage;
	PVOID EntryPoint;
	WORD LoadCount;
	WORD ModuleIndex;
	PVOID DllBaseOriginal;
	DWORD CheckSum;
	DWORD ModuleLoadFlags;
	DWORD TimeDateStamp;
	PVOID LoadedImports;
	PVOID XexHeaderBase;
	union {
		STRING LoadFileName;
		struct {
			PVOID ClosureRoot; // LDR_DATA_TABLE_ENTRY
			PVOID TraversalParent; // LDR_DATA_TABLE_ENTRY
		} asEntry;
	} inf;
} LDR_DATA_TABLE_ENTRY, *PLDR_DATA_TABLE_ENTRY;

extern "C" {
	PVOID XexPcToFileHeader(PVOID address, PLDR_DATA_TABLE_ENTRY* ldatOut);

	PVOID RtlImageXexHeaderField(PVOID XexHeaderBase, DWORD ImageField);
}

typedef struct _DETOUR_XEX_IMPORT_DESCRIPTOR
{
	DWORD Size;
	DWORD NameTableSize;
	DWORD ModuleCount;
} DETOUR_XEX_IMPORT_DESCRIPTOR, *PDETOUR_XEX_IMPORT_DESCRIPTOR;
