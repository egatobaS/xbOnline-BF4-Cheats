#include "Main.h"

GAME_ADDRESSES_BF4* Addresses;

Detour* (*GetDetour)();
void(*XNotify)(wchar_t*);
void*(*user_memcpy)(void*, void*, size_t);
char*(*user_strcpy)(char*, const char*);
void*(*user_memset)(void*, int, size_t);
int(*user_strcmp)(const char*, const char*);
void*(*xbOHookFunction)(Detour* a, void* b, void* c);

void(*drawText)(int UIImmediateModeRenderer, int UITextObject, Vector4* rect, float scale);
void(*setText)(int UITextObject, const char* text, bool disableUpdateFromData);
void(*setAlignment)(int UITextObject, int halign, int valign);
int(*create)(int UITextObject, const char* text, int style);
void(*drawRect)(int _this, Vector4* Coords, Vector4* Color, long long unk);
int(*SetKit)(int r3, int r4, int r5);
int(*GetKit)(int r3, const char* r4, int r5);
void(*ApplyPatches)();
void(*SuperJumpPatchON)();
void(*SuperJumpPatchOff)();
int(*ResolveTextureByName)(int r3, const char* r4, int r5, int r6, int r7, int r8);
void(*DrawTextureFromHandle)(int r3, int r4, int* r5, int* r6, int* r7, long long r8);
void(*AddVector)(Vector3 From, Vector3 To, Vector3& Out);
float(*GetDistance)(Vector3 c1, Vector3 c2);
float(*VectorLength2D)(Vector3* pV);
void(*GetFullAmmo)();
void(*DrawRotatedShader)(float x, float y, float width, float height, float angle, Vector4* Color);
void(*DrawLine)(float X1, float Y1, float X2, float Y2, float Width, Vector4* LineColor);
void(*SendChatMessage)(wchar_t *Message);

__int64 __declspec(naked) HvxGetVersion(unsigned int key, __int64 type, __int64 SourceAddress, __int64 DestAddress, __int64 lenInBytes)
{
	__asm
	{
		li r0, 0x0
		sc
		blr
	}
}

unsigned int HVGetVersionsPeekDWORD(unsigned long long Address)
{
	unsigned int *data = (unsigned int *)XPhysicalAlloc(4, MAXULONG_PTR, 0, PAGE_READWRITE); ;

	__int64 dest = 0x8000000000000000ULL + (unsigned int)MmGetPhysicalAddress((unsigned int*)data);

	HvxGetVersion(0x72627472, 5, Address, dest, 4);

	unsigned int retData = *(unsigned int*)data;

	XPhysicalFree(data);

	return retData;
}

unsigned int ReverseInt(unsigned int val)
{
	int RetVal = ((val << 24)) | (((val << 8) & 0x00ff0000)) | (((val >> 8) & 0x0000ff00)) | (((val >> 24) & 0x000000ff));

	return (RetVal + 0x90E00000);
}

#if defined(DEVKIT)

DWORD Real_ResolveFunction(PCHAR ModuleName, DWORD Ordinal)
{
	HANDLE hModule; DWORD Address;
	XexGetModuleHandle(ModuleName, &hModule);
	XexGetProcedureAddress(hModule, Ordinal, &Address);
	return Address;
}

DWORD Real_XNotifyThread(wchar_t *Message)
{
	while (((int(*)(DWORD exnq, DWORD dwUserIndex, ULONGLONG qwAreas, PWCHAR displayText, PVOID contextData))Real_ResolveFunction("xam.xex", 0x290))(34, 0xFF, 2, Message, 0) == ERROR_ACCESS_DENIED)
		Sleep(10);

	return 0;
}

int * Real_GetDetours()
{
	return (int*)new Detour();
}

VOID Real_XNotify(CONST PWCHAR NotifyText)
{
	ExCreateThread(0, 0, 0, 0, (LPTHREAD_START_ROUTINE)Real_XNotifyThread, NotifyText, 0);
}

void* Real_HookFunction(Detour* a, void* b, void* c)
{
	return (void*)a->HookFunction((unsigned int)b, (void*)c);
}

void Real_drawText(int UIImmediateModeRenderer, int UITextObject, Vector4* rect, float scale)
{
	void(*drawText)(int, int, Vector4*, float) = (void(*)(int, int, Vector4*, float))Addresses->_0x88AA3798;
	drawText(UIImmediateModeRenderer, UITextObject, rect, scale);
}

void Real_setText(int UITextObject, const char* text, bool disableUpdateFromData)
{
	void(*setText)(int, const char*, bool) = (void(*)(int, const char*, bool))Addresses->_0x88AA5E40;
	setText(UITextObject, text, disableUpdateFromData);
}

void Real_setAlignment(int UITextObject, int halign, int valign)
{
	void(*setAlignment)(int, int, int) = (void(*)(int, int, int))Addresses->_0x88A9F9B8;
	setAlignment(UITextObject, halign, valign);
}

int Real_create(int UITextObject, const char* text, int style)
{
	int(*CreateText)(int, const char*, int) = (int(*)(int, const char*, int))Addresses->_0x8852B0A0;
	return CreateText(UITextObject, text, style);
}

void Real_drawRect(int _this, Vector4* Coords, Vector4* Color, long long unk)
{
	void(*DrawRect)(int, Vector4 *, Vector4*, long long) = (void(*)(int, Vector4*, Vector4*, long long))Addresses->_0x88AA2C80;
	DrawRect(_this, Coords, Color, unk);
}

int Real_SetKit(int r3, int r4, int r5)
{
	int(*SetKit)(int x, int y, int z) = (int(*)(int x, int y, int z))Addresses->_0x88548C90;
	return SetKit(r3, r4, r5);
}

int Real_GetKit(int r3, const char* r4, int r5)
{
	int(*GetKit)(int x, const char* y, int z) = (int(*)(int x, const char*, int z))Addresses->_0x88A94758;
	return GetKit(r3, r4, r5);
}

void Real_ApplyPatches()
{
	*(int*)(Addresses->_0x886608C4 + 0x0) = Addresses->_0x3D6089A3;
	*(int*)(Addresses->_0x886608C4 + 0x4) = Addresses->_0x616BF168;
	*(int*)(Addresses->_0x886608C4 + 0x8) = Addresses->_0x906B0000;
	*(int*)(Addresses->_0x886608C4 + 0xC) = Addresses->_0x60000000;
	*(int*)(Addresses->_0x886608C4 + 0x10) = Addresses->_0x60000000;
	*(int*)(Addresses->_0x886608C4 + 0x14) = Addresses->_0x60000000;
	*(int*)(Addresses->_0x886608C4 + 0x18) = Addresses->_0x60000000;

	*(int*)(Addresses->_0x887620c0) = Addresses->_0x60000000;
	*(int*)(Addresses->_0x88762008) = Addresses->_0x60000000;
	*(int*)(Addresses->_0x88759DBC) = Addresses->_0x60000000;

	long long va0 = Addresses->_0x48A94BE1;

	*(long long*)Addresses->_0x8873E1E4 = (va0 << 32) | Addresses->_0x60000000;

	long long va1 = Addresses->_0x484c5711;

	*(long long*)Addresses->_0x88D0D6AC = (va1 << 32) | Addresses->_0x60000000;
}

void Real_SuperJumpPatchON()
{
	*(int*)Addresses->_0x8815DB54 = Addresses->_0x497423f0;
	*(int*)Addresses->_0x89158D00 = Addresses->_0x4800004C;
	*(int*)Addresses->_0x885F4E54 = Addresses->_0x48000034;
	*(int*)Addresses->_0x885F4EEC = Addresses->_0x480002FC;
	*(int*)Addresses->_0x885F410C = Addresses->_0x60000000;
	*(int*)Addresses->_0x885F4114 = Addresses->_0x60000000;
	*(int*)Addresses->_0x885F4DB8 = Addresses->_0x60000000;
	*(int*)Addresses->_0x885F4E1C = Addresses->_0x60000000;

	*(int*)Addresses->_0x88623830 = Addresses->_0x60000000;
	*(int*)Addresses->_0x88623838 = Addresses->_0x60000000;
	*(int*)Addresses->_0x886236EC = Addresses->_0x60000000;
	*(int*)Addresses->_0x88628E40 = Addresses->_0x60000000;
}

void Real_SuperJumpPatchOff()
{
	*(int*)Addresses->_0x885F4E54 = Addresses->_0x409A0034;
	*(int*)Addresses->_0x885F4EEC = Addresses->_0x1000038C;
	*(int*)Addresses->_0x8815DB54 = Addresses->_0x41300000;
	*(int*)Addresses->_0x89158D00 = Addresses->_0x4099004C;
	*(int*)Addresses->_0x885F410C = Addresses->_0xD3350020;
	*(int*)Addresses->_0x885F4114 = Addresses->_0x92D50040;
	*(int*)Addresses->_0x885F4DB8 = Addresses->_0x419A0430;
	*(int*)Addresses->_0x885F4E1C = Addresses->_0x409900D0;

	*(int*)Addresses->_0x88623830 = Addresses->_0x11BFD9C3;
	*(int*)Addresses->_0x88623838 = Addresses->_0x915F0040;
	*(int*)Addresses->_0x886236EC = Addresses->_0x11BED9C3;
	*(int*)Addresses->_0x88628E40 = Addresses->_0x7FE3FB78;
}

int Real_ResolveTextureByName(int r3, const char* r4, int r5, int r6, int r7, int r8)
{
	int(*ResolveTextureByName)(int, const char*, int, int, int, int) = (int(*)(int, const char*, int, int, int, int))Addresses->_0x88679E80;
	return ResolveTextureByName(r3, r4, r5, r6, r7, r8);
}

void Real_DrawTextureFromHandle(int r3, int r4, int* r5, int* r6, int* r7, long long r8)
{
	void(*DrawTextureFromHandle)(int, int, int*, int*, int*, long long) = (void(*)(int, int, int*, int*, int*, long long))Addresses->_0x88AA1FC8;
	DrawTextureFromHandle(r3, r4, r5, r6, r7, r8);
}

void Real_AddVector(Vector3 From, Vector3 To, Vector3& Out)
{
	Out.x = From.x + To.x;
	Out.y = From.y + To.y;
	Out.z = From.z + To.z;
}

float Real_GetDistance(Vector3 c1, Vector3 c2)
{
	float dx = c2.x - c1.x;
	float dy = c2.y - c1.y;
	float dz = c2.z - c1.z;
	return sqrt((float)((dx * dx) + (dy * dy) + (dz * dz)));
}

float Real_VectorLength2D(Vector3* pV)
{
	return	sqrtf(pV->x * pV->x + pV->z * pV->z);
}

void Real_GetFullAmmo()
{
	int CurSlot = *(int*)(Addresses->_0x8991B78C) + Addresses->_0x150;

	int Kit = Real_GetKit(CurSlot, "SelectedKit", 0);

	if (!MmIsAddressValid(GetLocalPlayer()))
		return;

	Real_SetKit(Kit, GetLocalPlayer()->m_TeamID, 0);
}

void Real_DrawRotatedShader(float x, float y, float width, float height, float angle, Vector4* Color)
{
	MatrixCoords ShaderMatrix;

	Vector4 ImagePosition = Vector4(0.5f, 0.0f, 0.5f, 0.0f);
	Vector4 _color = Vector4(Color->x, Color->y, Color->z, Color->a);

	float f11 = x + width;
	float f10 = y + height;

	Vector2 Center = { (f11 + x) / 2, (y + f10) / 2 };

	ShaderMatrix.TL.x = Center.x + (x - Center.x)*cos(-angle) + (y - Center.y)*sin(-angle);
	ShaderMatrix.TL.y = Center.y - (x - Center.x)*sin(-angle) + (y - Center.y)*cos(-angle);
	ShaderMatrix.TL.z = 0;

	ShaderMatrix.TR.x = Center.x + (f11 - Center.x)*cos(-angle) + (y - Center.y)*sin(-angle);
	ShaderMatrix.TR.y = Center.y - (f11 - Center.x)*sin(-angle) + (y - Center.y)*cos(-angle);;
	ShaderMatrix.TR.z = 0;

	ShaderMatrix.BR.x = Center.x + (f11 - Center.x)*cos(-angle) + (f10 - Center.y)*sin(-angle);
	ShaderMatrix.BR.y = Center.y - (f11 - Center.x)*sin(-angle) + (f10 - Center.y)*cos(-angle);
	ShaderMatrix.BR.z = 0;

	ShaderMatrix.BL.x = Center.x + (x - Center.x)*cos(-angle) + (f10 - Center.y)*sin(-angle);
	ShaderMatrix.BL.y = Center.y - (x - Center.x)*sin(-angle) + (f10 - Center.y)*cos(-angle);
	ShaderMatrix.BL.z = 0;

	int TextureHandle = Real_ResolveTextureByName(0, "xhttps://eaassets-a.akamaihd.net/dice-commerce/battlefield4/topstory/prod/20170412-01/Easterfest_ConversionMissionv2_510x144.jpg", 1, 1, 0, 0);

	if (!TextureHandle)
		return;

	Real_DrawTextureFromHandle(*(int*)(Addresses->_0x8991B90C), *(int*)(TextureHandle), (int*)&ShaderMatrix, (int*)&_color, (int*)&ImagePosition, 0xA100000000);
}

void Real_DrawLine(float X1, float Y1, float X2, float Y2, float Width, Vector4* LineColor)
{
	float X, Y, L1, L2, H1;

	H1 = Y2 - Y1;
	L1 = X2 - X1;
	L2 = sqrt(L1 * L1 + H1 * H1);
	X = X1 + ((L1 - L2) / 2);
	Y = Y1 + (H1 / 2);

	Real_DrawRotatedShader(X, Y, L2, Width, (float)atan(H1 / L1), LineColor);
}

void Real_SendChatMessage(wchar_t *Message)
{
	int(*SendChat)(int chat, int ChannelID, int ReceiptMask, wchar_t*) = (int(*)(int, int ChannelID, int ReceiptMask, wchar_t*))Addresses->_0x8856A310;

	int ClientGameContext = *(int*)Addresses->_0x89916E78;
	int OnlineManager = *(int*)(ClientGameContext + Addresses->_0x34);
	int ClientPeer = *(int*)(OnlineManager + Addresses->_0x18);
	int Unk1 = *(int*)(ClientPeer + Addresses->_0x3644);

	if (Unk1 != 0)
	{
		int Unk2 = Unk1 - Addresses->_0x10;
		int Unk3 = *(int*)(Unk2 + Addresses->_0x2090);

		SendChat(Unk3, 0, ~0, Message);
	}
}

#endif


void LoadAddresses()
{
#if defined(DEVKIT)

	GetDetour = (Detour*(*)())Real_GetDetours;
	XNotify = (void(*)(wchar_t*))Real_XNotify;

	user_memcpy = (void*(*)(void*, void*, size_t))memcpy;
	user_strcpy = (char*(*)(char*, const char*))strcpy;
	user_memset = (void*(*)(void*, int, size_t))memset;
	user_strcmp = (int(*)(const char*, const char*))strcmp;

	xbOHookFunction = (void*(*)(Detour* a, void* b, void* c))Real_HookFunction;

	drawText = (void(*)(int UIImmediateModeRenderer, int UITextObject, Vector4* rect, float scale))Real_drawText;

	setText = (void(*)(int UITextObject, const char* text, bool disableUpdateFromData))Real_setText;

	setAlignment = (void(*)(int UITextObject, int halign, int valign))Real_setAlignment;

	create = (int(*)(int UITextObject, const char* text, int style))Real_create;

	drawRect = (void(*)(int _this, Vector4* Coords, Vector4* Color, long long unk))Real_drawRect;

	SetKit = (int(*)(int r3, int r4, int r5))Real_SetKit;

	GetKit = (int(*)(int r3, const char* r4, int r5))Real_GetKit;

	ApplyPatches = (void(*)())Real_ApplyPatches;

	SuperJumpPatchON = (void(*)())Real_SuperJumpPatchON;

	SuperJumpPatchOff = (void(*)())Real_SuperJumpPatchOff;

	ResolveTextureByName = (int(*)(int r3, const char* r4, int r5, int r6, int r7, int r8))Real_ResolveTextureByName;

	DrawTextureFromHandle = (void(*)(int r3, int r4, int* r5, int* r6, int* r7, long long r8))Real_DrawTextureFromHandle;

	AddVector = (void(*)(Vector3 From, Vector3 To, Vector3& Out))Real_AddVector;

	GetDistance = (float(*)(Vector3 c1, Vector3 c2))Real_GetDistance;

	VectorLength2D = (float(*)(Vector3* pV))Real_VectorLength2D;

	GetFullAmmo = (void(*)())Real_GetFullAmmo;

	DrawRotatedShader = (void(*)(float x, float y, float width, float height, float angle, Vector4* Color))Real_DrawRotatedShader;

	DrawLine = (void(*)(float X1, float Y1, float X2, float Y2, float Width, Vector4* LineColor))Real_DrawLine;

	SendChatMessage = (void(*)(wchar_t *Message))Real_SendChatMessage;

	Addresses = new GAME_ADDRESSES_BF4;
	Addresses->SetAddress();

#else
	GAME_ADDRESS_TRANSFER_BF4* Game_Functions = (GAME_ADDRESS_TRANSFER_BF4*)ReverseInt(HVGetVersionsPeekDWORD(0x800001000000BED0));
	int AddressLength = ReverseInt(HVGetVersionsPeekDWORD(0x800001000000BED4));
	SYS_FUNCTION_ADDRESS* Sys_Functions = (SYS_FUNCTION_ADDRESS*)ReverseInt(HVGetVersionsPeekDWORD(0x800001000000BED8));

	if (Sys_Functions)
	{
		GetDetour = (Detour*(*)())Sys_Functions->GetDetours;
		XNotify = (void(*)(wchar_t*))Sys_Functions->XNotify;

		user_memcpy = (void*(*)(void*, void*, size_t))Sys_Functions->memcpy;
		user_strcpy = (char*(*)(char*, const char*))Sys_Functions->strcpy;
		user_memset = (void*(*)(void*, int, size_t))Sys_Functions->memset;
		user_strcmp = (int(*)(const char*, const char*))Sys_Functions->strcmp;

		xbOHookFunction = (void*(*)(Detour* a, void* b, void* c))Sys_Functions->HookFunction;
	}

	if (Game_Functions)
	{
		Addresses = Game_Functions->Addresses;

		drawText = (void(*)(int UIImmediateModeRenderer, int UITextObject, Vector4* rect, float scale))(void*)ReverseInt((int)Game_Functions->drawText);

		setText = (void(*)(int UITextObject, const char* text, bool disableUpdateFromData))(void*)ReverseInt((int)Game_Functions->setText);

		setAlignment = (void(*)(int UITextObject, int halign, int valign))(void*)ReverseInt((int)Game_Functions->setAlignment);

		create = (int(*)(int UITextObject, const char* text, int style))(void*)ReverseInt((int)Game_Functions->create);

		drawRect = (void(*)(int _this, Vector4* Coords, Vector4* Color, long long unk))(void*)ReverseInt((int)Game_Functions->drawRect);

		SetKit = (int(*)(int r3, int r4, int r5))(void*)ReverseInt((int)Game_Functions->SetKit);

		GetKit = (int(*)(int r3, const char* r4, int r5))(void*)ReverseInt((int)Game_Functions->GetKit);

		ApplyPatches = (void(*)())(void*)ReverseInt((int)Game_Functions->ApplyPatches);

		SuperJumpPatchON = (void(*)())(void*)ReverseInt((int)Game_Functions->SuperJumpPatchON);

		SuperJumpPatchOff = (void(*)())(void*)ReverseInt((int)Game_Functions->SuperJumpPatchOff);

		ResolveTextureByName = (int(*)(int r3, const char* r4, int r5, int r6, int r7, int r8))(void*)ReverseInt((int)Game_Functions->ResolveTextureByName);

		DrawTextureFromHandle = (void(*)(int r3, int r4, int* r5, int* r6, int* r7, long long r8))(void*)ReverseInt((int)Game_Functions->DrawTextureFromHandle);

		AddVector = (void(*)(Vector3 From, Vector3 To, Vector3& Out))(void*)ReverseInt((int)Game_Functions->AddVector);

		GetDistance = (float(*)(Vector3 c1, Vector3 c2))(void*)ReverseInt((int)Game_Functions->GetDistance);

		VectorLength2D = (float(*)(Vector3* pV))(void*)ReverseInt((int)Game_Functions->VectorLength2D);

		GetFullAmmo = (void(*)())(void*)ReverseInt((int)Game_Functions->GetFullAmmo);

		DrawRotatedShader = (void(*)(float x, float y, float width, float height, float angle, Vector4* Color))(void*)ReverseInt((int)Game_Functions->DrawRotatedShader);

		DrawLine = (void(*)(float X1, float Y1, float X2, float Y2, float Width, Vector4* LineColor))(void*)ReverseInt((int)Game_Functions->DrawLine);

		SendChatMessage = (void(*)(wchar_t *Message))(void*)ReverseInt((int)Game_Functions->SendChatMessage);

	}
#endif
}