#include "main.h"

bool ShouldSetIni = false;
bool ShouldEndThread = false;

int RestoreHooks()
{
	ShouldEndThread = true;

	Sleep(1000);

	RayCastHookDetour->RestoreFunction();
	GameUnhandledExceptionFilterDetour->RestoreFunction();
	UnhandledExceptionFilterDetour->RestoreFunction();
	DrawingDetour->RestoreFunction();
	BulletHookDetour->RestoreFunction();
	AddMoveHook->RestoreFunction();
	XamInputGetStateDetour->RestoreFunction();

	UNKDrawingCrash->RestoreFunction();

	*(int*)(Addresses->_0x887620c0) = Addresses->_0x915C00F0;
	*(int*)(Addresses->_0x88762008) = Addresses->_0x4BFFFAD9;
	*(int*)(Addresses->_0x88759DBC) = Addresses->_0x913F00F0;

	long long va0 = Addresses->_0x48A94BE1;

	*(long long*)Addresses->_0x8873E1E4 = (va0 << 32) | Addresses->_0x60000000;

	long long va1 = Addresses->_0x484c5711;

	*(long long*)Addresses->_0x88D0D6AC = (va1 << 32) | Addresses->_0x60000000;

	return 0;
}

int InitData()
{
	LoadINI();

#if defined(DEVKIT)
	*(unsigned int*)(0x88A23F1C) = 0x7ff80000;
#endif


	printf("eeee %s\n", __FUNCDNAME__);




	ApplyPatches();

	UnhandledExceptionFilterDetour = new Detour;//GetDetour();
	GameUnhandledExceptionFilterDetour = new Detour;//GetDetour();
	XamInputGetStateDetour = new Detour;//GetDetour();
	UNKDrawingCrash = new Detour;//GetDetour();
	RayCastHookDetour = new Detour;//GetDetour();
	BulletHookDetour = new Detour;//GetDetour();
	AddMoveHook = new Detour;//GetDetour();
	DrawingDetour = new Detour;//GetDetour();


	UnhandledExceptionFilterStub = (pUnhandledExceptionFilter)UnhandledExceptionFilterDetour->HookFunction((unsigned int)UnhandledExceptionFilter, NewUnhandledExceptionFilter);

	GameUnhandledExceptionFilterStub = (pUnhandledExceptionFilter)GameUnhandledExceptionFilterDetour->HookFunction((unsigned int)Addresses->_0x882FB7B8, GameUnhandledExceptionFilter);

	XamInputGetStateDetour->HookFunction(GetAddr(0x88000000, 0x191), XamInputGetStateHook);

	pUnkDrawingStub = (pUnkDrawingHook)UNKDrawingCrash->HookFunction(0x88707E88, DrawingFix);

	AddMenuOptions();

	RayCastHookStub = (pRayCastHook)RayCastHookDetour->HookFunction((unsigned int)Addresses->_0x88B9FD58, RayCastHook);

	Bullet = (pBulletHook)BulletHookDetour->HookFunction((unsigned int)Addresses->_0x88AD3A28, BulletHook);

	AddMoveOriginal = (AddMoveStub)AddMoveHook->HookFunction(Addresses->_0x88D0D6A8, (void*)AddMove);

	DrawingDetour->HookFunction((int)Addresses->_0x88763360, DrawingHook);

	XNotify(L"xbOnline Cheats [Battlefield 4] Loaded!\nDeveloped By Sabotage & Trojan [Teh1337wasHere]");


	while (!ShouldEndThread)
	{
		if (ShouldSetIni)
		{
			SetInit();
			ShouldSetIni = false;
		}
		Sleep(10);
	}


	return 0;
}

BOOL WINAPI DllMain(HANDLE ModuleHandle, unsigned int fdwReason, LPVOID lpReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH) {

		LoadAddresses();

		HANDLE hThread; DWORD hThreadID;
		ExCreateThread(&hThread, 0x1000, &hThreadID, (PVOID)XapiThreadStartup, (LPTHREAD_START_ROUTINE)InitData, NULL, 0x2);
		XSetThreadProcessor(hThread, 4);
		ResumeThread(hThread);
		CloseHandle(hThread);
	}
	else if (fdwReason == DLL_PROCESS_DETACH) {

		RestoreHooks();

		Sleep(1000);
	}
	return true;
}