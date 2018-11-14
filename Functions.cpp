#include "main.h"

int(*DbgPrintf)(const char*, ...) = (int(*)(const char*, ...))0x896405CC;
int(*g_snprintf)(char* _Dest, size_t Count, const char* _Format, ...) = (int(*)(char* _Dest, size_t Count, const char* _Format, ...))0x8963FB3C;
int(*Com_Sprintf)(char *Buffer, int size, const char *fmt, ...) = (int(*)(char *Buffer, int size, const char *fmt, ...))0x88948818;

const DWORD MMIORangeTable[] =
{
	0x7FC80000,
	0x7FC9FFFF,
	0x7FD00000,
	0x7FDFFFFF,
	0x7FEA0000,
	0x7FEAFFFF,
	0x7FED0000,
	0x7FEDFFFF,
	0x7FED0000,
	0x7FEDFFFF,
	0x8FFF0000,
	0x8FFF0FFF,
	0x8FFF1000,
	0x8FFF1FFF,
	0x00000000,
	0x00000000,
};

unsigned int WaitTime = 0;
unsigned int TimeCount = 0;

int NearestPlayer = -1;

bool isClientWallable[24] = { 0 };
bool Autowallable = false;

Vector2 pSilent;

Vector3 Multiply(Vector3 vec, Matrix* mat)
{
	return Vector3(mat->operator()(0, 0) * vec.x + mat->operator()(1, 0)* vec.y + mat->operator()(2, 0)* vec.z,
		mat->operator()(0, 1)* vec.x + mat->operator()(1, 1)* vec.y + mat->operator()(2, 1)* vec.z,
		mat->operator()(0, 2)* vec.x + mat->operator()(1, 2)* vec.y + mat->operator()(2, 2)* vec.z);
}

void DoEntityDrawings(int r3)
{
	ESP(r3);

	if (bDrawRadar)
		DrawRadar();

	if (bDrawExplosive)
		DrawExplosives(GetLocalPlayer(), r3);

	if (bDrawGrenade)
		DrawGrenade(GetLocalPlayer(), r3);

	if (bDrawPickups)
		DrawPickups(GetLocalPlayer(), r3);

	if (bDrawSupply)
		DrawAmmoBoxs(GetLocalPlayer(), r3);

	if (bDrawUnusedVehicles)
		DrawVehicles(GetLocalPlayer(), r3);
}

float Angle(Vector3 d, const Vector3 v)
{
	return acos(d.DotProduct(v) / (d.Length() * v.Length()));
}

void DrawRadar()
{
	if (MmIsAddressValid(GameRenderer::GetInstance()))
	{
		Vector3 myposition = GameRenderer::GetInstance()->m_pRenderView->m_viewMatrixInverse.Translation();
		Vector3 myforward = GameRenderer::GetInstance()->m_pRenderView->m_viewMatrixInverse.Forward();
		Vector3 myright = GameRenderer::GetInstance()->m_pRenderView->m_viewMatrixInverse.Right();

		//myforward.x = 0;

		for (int i = 0; i < 24; i++)
		{
			ClientPlayer* pEnemy = GetClientPlayer(i);
			if (isClientAlive(pEnemy) && pEnemy->m_TeamID != GetLocalPlayer()->m_TeamID)
			{
				Vector4 C = !isClientWallable[i] ? Vector4(1, 0, 0, 1) : Vector4(1, 1, 0, 1);

				Vector3 projectedenemypos = Vector3(0, 0, 0);

				Vector3 enemyposition = pEnemy->m_pControlledControllable->m_ClientSoliderPrediction->Position;

				Vector3 EyePos = Vector3(0, 0, 0);

				if (GetBone(GetLocalPlayer()->m_pControlledControllable, &EyePos, BONE_HEAD))
				{
					projectedenemypos.x = enemyposition.x - (myforward.DotProduct(enemyposition) + myposition.Length()) * myforward.x;
					projectedenemypos.y = enemyposition.y - (myforward.DotProduct(enemyposition) + myposition.Length()) * myforward.y;
					projectedenemypos.z = enemyposition.z - (myforward.DotProduct(enemyposition) + myposition.Length()) * myforward.z;

					Vector3 dir = projectedenemypos - GetLocalPlayer()->m_pControlledControllable->m_ClientSoliderPrediction->Position;
					dir.Normalize();

					float angle = atan2((myright.crossVector3D(dir)).DotProduct(myforward), dir.DotProduct(myright));

					Vector4 screenrect(260, 260, 1280 - 260 * 2, 720 - 260 * 2);
					Vector2 circlexyvector = { cos(angle), sin(angle) };

					float magnitude;
					if (screenrect.z / 2 * fabs(circlexyvector.y) <= screenrect.a / 2 * fabs(circlexyvector.x))
						magnitude = screenrect.z / 2 / fabs(circlexyvector.x);
					else
						magnitude = screenrect.a / 2 / fabs(circlexyvector.y);

					Vector2 xyscaled = { 0 };
					xyscaled.x = circlexyvector.x * magnitude;
					xyscaled.y = circlexyvector.y * magnitude;

					float sa = sin(angle);
					float ca = cos(angle);
					float x1 = 150.0f * ca;
					float y1 = 150.0f * sa;
					float x2 = 160.0f * ca;
					float y2 = 160.0f * sa;

					bool draw = true;
					Vector3 s;
					if (WorldToScreen(projectedenemypos, &s))
					{
						s.x -= 20.0f;
						s.y -= 20.0f;
						s.z = 0;

						if (s.Length() < 250.0f)
							draw = false;
					}

					if (draw)
					{
						DrawLine(1280 / 2 + x1, 720 / 2 + y1, 1280 / 2 + x2, 720 / 2 + y2, 5, &C);
					}
				}
			}
		}
	}
}

bool Draw2DBox(ClientPlayer* pPlayer, Vector4 color, float size)
{
	Matrix trans;
	Vector3 Pos;

	TransformAABBStruct TransAABB;

	if (!isClientAlive(pPlayer))
		return false;

	pPlayer->m_pControlledControllable->GetAABB(TransAABB);

	ClientVehicleEntity* pEnt = { 0 };

	pEnt = (ClientVehicleEntity*)pPlayer->m_pControlledControllable;

	pEnt->GetTransform(&trans);
	Pos = Vector3(trans.operator()(3, 0), trans.operator()(3, 1), trans.operator()(3, 2));

	AxisAlignedBox aabb = TransAABB.AABB;

	Vector3 aabbMin = Vector3(aabb.m_Min.x, aabb.m_Min.y, aabb.m_Min.z);
	Vector3 aabbMax = Vector3(aabb.m_Max.x, aabb.m_Max.y, aabb.m_Max.z);
	Vector3 min = aabbMin * size;
	Vector3 max = aabbMax * size;
	Vector3 crnr2 = Pos + Multiply(Vector3(max.x, min.y, min.z), &trans);
	Vector3 crnr3 = Pos + Multiply(Vector3(max.x, min.y, max.z), &trans);
	Vector3 crnr4 = Pos + Multiply(Vector3(min.x, min.y, max.z), &trans);
	Vector3 crnr5 = Pos + Multiply(Vector3(min.x, max.y, max.z), &trans);
	Vector3 crnr6 = Pos + Multiply(Vector3(min.x, max.y, min.z), &trans);
	Vector3 crnr7 = Pos + Multiply(Vector3(max.x, max.y, min.z), &trans);

	min = Pos + Multiply(min, &trans);
	max = Pos + Multiply(max, &trans);

	if (WorldToScreen(min, &min) && WorldToScreen(max, &max) && WorldToScreen(crnr2, &crnr2) && WorldToScreen(crnr3, &crnr3) && WorldToScreen(crnr4, &crnr4) && WorldToScreen(crnr5, &crnr5) && WorldToScreen(crnr6, &crnr6) && WorldToScreen(crnr7, &crnr7))
	{
		Vector3 arr[] = { min, max, crnr2, crnr3, crnr4, crnr5, crnr6, crnr7 };

		float l = min.x; // left
		float t = min.y; // top
		float r = min.x; // right
		float b = min.y; // bottom

		for (int i = 1; i < 8; i++)
		{
			if (l > arr[i].x) l = arr[i].x;
			if (t < arr[i].y) t = arr[i].y;
			if (r < arr[i].x) r = arr[i].x;
			if (b > arr[i].y) b = arr[i].y;
		}

		//float fHeight = t - b;
		//
		//float clientHealth = pPlayer->m_pControlledControllable->m_pBFClientSoldierHealthComponent->m_fhealth;
		//float MaxHealth = pPlayer->m_pControlledControllable->m_pBFClientSoldierHealthComponent->m_MaxHealth;
		//
		//float healthSize = clientHealth * ((fHeight) / MaxHealth);
		//
		//float sum = b * (MaxHealth / clientHealth);
		//
		//DrawLine(l, b, l, t, 4, &Vector4(0, 0, 0, 1));
		//DrawLine(l, sum >= t ? t : sum, l, t, 2, &Vector4((float)1 - (clientHealth / 100), (float)clientHealth / 100, 0, 1));

		DrawLine(l, b, l, t, 1, &color);
		DrawLine(l, t, r, t, 1, &color);
		DrawLine(r, t, r, b, 1, &color);
		DrawLine(r, b, l, b, 1, &color);
	}

	return true;
}

bool TransformDrawAABB(ClientVehicleEntity* pEnt, Vector4 color, float size)
{
	Matrix trans;
	Vector3 Pos;

	TransformAABBStruct TransAABB;
	pEnt->GetAABB(TransAABB);

	pEnt->GetTransform(&trans);
	Pos = Vector3(trans.operator()(3, 0), trans.operator()(3, 1), trans.operator()(3, 2));

	AxisAlignedBox aabb = TransAABB.AABB;

	Vector3 aabbMin = Vector3(aabb.m_Min.x, aabb.m_Min.y, aabb.m_Min.z);
	Vector3 aabbMax = Vector3(aabb.m_Max.x, aabb.m_Max.y, aabb.m_Max.z);
	Vector3 min = aabbMin * size;
	Vector3 max = aabbMax * size;
	Vector3 crnr2 = Pos + Multiply(Vector3(max.x, min.y, min.z), &trans);
	Vector3 crnr3 = Pos + Multiply(Vector3(max.x, min.y, max.z), &trans);
	Vector3 crnr4 = Pos + Multiply(Vector3(min.x, min.y, max.z), &trans);
	Vector3 crnr5 = Pos + Multiply(Vector3(min.x, max.y, max.z), &trans);
	Vector3 crnr6 = Pos + Multiply(Vector3(min.x, max.y, min.z), &trans);
	Vector3 crnr7 = Pos + Multiply(Vector3(max.x, max.y, min.z), &trans);

	min = Pos + Multiply(min, &trans);
	max = Pos + Multiply(max, &trans);

	if (WorldToScreen(min, &min) && WorldToScreen(max, &max) && WorldToScreen(crnr2, &crnr2) && WorldToScreen(crnr3, &crnr3) && WorldToScreen(crnr4, &crnr4) && WorldToScreen(crnr5, &crnr5) && WorldToScreen(crnr6, &crnr6) && WorldToScreen(crnr7, &crnr7))
	{
		//From min to 2, 4 and 6
		DrawLine(min.x, min.y, crnr2.x, crnr2.y, 1, &color);
		DrawLine(min.x, min.y, crnr4.x, crnr4.y, 1, &color);
		DrawLine(min.x, min.y, crnr6.x, crnr6.y, 1, &color);

		//From max to 5, 7 and 3
		DrawLine(max.x, max.y, crnr5.x, crnr5.y, 1, &color);
		DrawLine(max.x, max.y, crnr7.x, crnr7.y, 1, &color);
		DrawLine(max.x, max.y, crnr3.x, crnr3.y, 1, &color);

		//From 2 to 7 and 3
		DrawLine(crnr2.x, crnr2.y, crnr7.x, crnr7.y, 1, &color);
		DrawLine(crnr2.x, crnr2.y, crnr3.x, crnr3.y, 1, &color);

		//From 4 to 5 and 3
		DrawLine(crnr4.x, crnr4.y, crnr5.x, crnr5.y, 1, &color);
		DrawLine(crnr4.x, crnr4.y, crnr3.x, crnr3.y, 1, &color);

		//From 6 to 5 and 7
		DrawLine(crnr6.x, crnr6.y, crnr5.x, crnr5.y, 1, &color);
		DrawLine(crnr6.x, crnr6.y, crnr7.x, crnr7.y, 1, &color);
	}
	return true;
}

BOOL FIsMmIoAddress(PVOID addr)
{
	int i = 0;

	for (i = 0; MMIORangeTable[i]; i += 2) {
		if (((DWORD)addr > MMIORangeTable[i]) && ((DWORD)addr < MMIORangeTable[i + 1]))
			return TRUE;
	}

	return FALSE;
}

bool MmIsAddressValidPtr(void* ptr)
{
	if (((int)ptr > 0x30000000))
		return (!FIsMmIoAddress(ptr) && MmIsAddressValid(ptr));

	return false;
}

void Wait(int time)
{
	TimeCount = GetTickCount();
	WaitTime = time;
}

DWORD GetModuleImport(HANDLE HModule, HANDLE HImportedModule, DWORD Ordinal)
{
	PDETOUR_XEX_IMPORT_DESCRIPTOR importTable;
	DWORD dwModuleCountIndex = 0;
	DWORD dwModuleIndex = 0;
	CHAR szModuleName[0x100];
	CHAR szHImportedModule[0x100];

	DWORD dwImportAddress = (DWORD)GetProcAddress((HMODULE)HImportedModule, (LPCSTR)Ordinal);

	if (dwImportAddress == NULL || HModule == NULL)
		return 0;

	importTable = (PDETOUR_XEX_IMPORT_DESCRIPTOR)
		RtlImageXexHeaderField((void*)*(DWORD *)((DWORD)HModule + 0x58), 0x000103FF);

	if (importTable == NULL)
		return 0;

	WideCharToMultiByte(CP_UTF8, NULL, (wchar_t*)*(DWORD*)((DWORD)HImportedModule + 0x30), -1, szHImportedModule, 0x100, NULL, NULL);

	for (DWORD dwModuleCount = 0; dwModuleCount < importTable->ModuleCount; dwModuleCount++)
	{
		DWORD i = dwModuleCountIndex;

		DWORD dwPointer = (DWORD)importTable + 0x0C + importTable->NameTableSize + dwModuleIndex;

		DWORD dwModuleSectionSize = *(DWORD *)dwPointer;

		dwPointer += 0x24 + 4;

		dwModuleIndex += dwModuleSectionSize;

		dwModuleSectionSize -= 0x24 + 4;

		dwModuleCountIndex += strlen((char*)((DWORD)importTable + 0x0C + i));

		strcpy(szModuleName, (char*)((DWORD)importTable + 0x0C + i));

		if (!strcmp(szModuleName, szHImportedModule))
		{
			for (DWORD dwSize = 0; dwSize < dwModuleSectionSize; dwSize += 8)
			{
				DWORD dwTempAddr = *(DWORD *)*(DWORD *)(dwPointer + dwSize);
				if (dwTempAddr == dwImportAddress)
					return *(DWORD *)(dwPointer + dwSize + 4);
			}
		}
	}
	return 0;
}

DWORD GetAddr(DWORD dwModuleBaseAddr, int Ordinal)
{
	HANDLE hModule;
	XexPcToFileHeader((PVOID)dwModuleBaseAddr, (PLDR_DATA_TABLE_ENTRY*)&hModule);
	HANDLE hImportedModule = (HANDLE)GetModuleHandle("xam.xex");
	return GetModuleImport(hModule, hImportedModule, Ordinal);
}

int GetAsyncKeyState(DWORD KEY)
{
	XINPUT_STATE InputState;
	XInputGetState(0, &InputState);

	if (!KEY)
		return true;

	if (KEY == KEY_LT) {
		return (InputState.Gamepad.bLeftTrigger / 30) > 0;
	}

	if (KEY == KEY_RT)
		return (InputState.Gamepad.bRightTrigger / 30) > 0;

	return InputState.Gamepad.wButtons & KEY;
}

void DrawBorderBox(float x, float y, float width, float height, float thickness, Vector4* color)
{
	Drawing.DrawRect(x, y, width, thickness, color);
	Drawing.DrawRect(x, y, thickness, height, color);
	Drawing.DrawRect((x + width), y, thickness, height, color);
	Drawing.DrawRect(x, (y + height), width + thickness, thickness, color);
}

bool GetBone(ClientSoldierEntity* pEnt, Vector3 *vOut, int BoneId)
{
	ClientRagDollComponent* pRag = pEnt->m_pClientRagdollComponent;

	if (!MmIsAddressValidPtr(pRag))
		return false;

	UpdatePoseResultData PoseResult = pRag->m_ragdollTransform;

	UpdatePoseResultData::QuatTransform* pQuat = PoseResult.m_ActiveWorldTransform;

	if (!MmIsAddressValidPtr(pQuat))
		return false;

	Vector3 Temp = pQuat[BoneId].m_transandScale;

	vOut->x = Temp.x;
	vOut->y = Temp.y;
	vOut->z = Temp.z;

	return true;
}

bool WorldToScreen(Vector3 WorldPos, Vector3* ScreenPos)
{
	GameRenderer* Usage = GameRenderer::GetInstance();
	Matrix viewProj = Usage->m_pRenderView->m_ViewProj;

	float mX = 1280.0f * 0.5f;
	float mY = 720.0f * 0.5f;

	float w =

		viewProj(0, 3) * WorldPos.x +
		viewProj(1, 3) * WorldPos.y +
		viewProj(2, 3) * WorldPos.z +
		viewProj(3, 3);

	if (w < 0.65f)
	{
		return false;
	}

	float x =
		viewProj(0, 0) * WorldPos.x +
		viewProj(1, 0) * WorldPos.y +
		viewProj(2, 0) * WorldPos.z +
		viewProj(3, 0);

	float y =
		viewProj(0, 1) * WorldPos.x +
		viewProj(1, 1) * WorldPos.y +
		viewProj(2, 1) * WorldPos.z +
		viewProj(3, 1);

	ScreenPos->x = (mX + mX * x / w);
	ScreenPos->y = (mY - mY * y / w);
	ScreenPos->z = w;

	return true;
}

void DrawBoneLine(ClientPlayer* entity, int tagname1, int tagname2, Vector4* col)
{
	Vector3 Origin1, Origin2;

	if (GetBone(entity->m_pControlledControllable, &Origin1, tagname1) && GetBone(entity->m_pControlledControllable, &Origin2, tagname2))
	{
		Vector3 Loc1, Loc2;
		if (WorldToScreen(Origin1, &Loc1) && WorldToScreen(Origin2, &Loc2))
			DrawLine(Loc1.x, Loc1.y, Loc2.x, Loc2.y, 1.8f, col);
	}
}

void DoAllBones(ClientPlayer* Client, Vector4* boneESPCol)
{
	//neck
	DrawBoneLine(Client, BONE_HEAD, BONE_NECK, boneESPCol);

	//left arm
	DrawBoneLine(Client, BONE_NECK, BONE_LEFTSHOULDER, boneESPCol);
	DrawBoneLine(Client, BONE_LEFTSHOULDER, BONE_LEFTELBOWROLL, boneESPCol);
	DrawBoneLine(Client, BONE_LEFTELBOWROLL, BONE_RIGHTHAND, boneESPCol);

	//right arm
	DrawBoneLine(Client, BONE_NECK, BONE_RIGHTSHOULDER, boneESPCol);
	DrawBoneLine(Client, BONE_RIGHTSHOULDER, BONE_RIGHTELBOWROLL, boneESPCol);
	DrawBoneLine(Client, BONE_RIGHTELBOWROLL, BONE_RIGHTHAND, boneESPCol);

	//spine
	DrawBoneLine(Client, BONE_NECK, BONE_SPINE, boneESPCol);

	//left leg
	DrawBoneLine(Client, BONE_SPINE, BONE_LEFTKNEEROLL, boneESPCol);
	DrawBoneLine(Client, BONE_LEFTKNEEROLL, BONE_LEFTFOOT, boneESPCol);

	//right leg
	DrawBoneLine(Client, BONE_SPINE, BONE_RIGHTKNEEROLL, boneESPCol);
	DrawBoneLine(Client, BONE_RIGHTKNEEROLL, BONE_RIGHTFOOT, boneESPCol);
}

VOID __declspec(naked) Break()
{
	__asm
	{
		twi 31, r0, 22
		li r3, 0
		blr
	}
}

struct Struct2
{
	int FirstPtr;
	int SecondPtr;
};

struct Struct1
{
	int FirstPtr;
	int SecondPtr;
};

void SendSpottingMessage(ClientPlayer* LocalPlayer, ClientPlayer* Target, SpotType type, float Frequency) //To fix
{
	int(*SendSpot)(ClientSpottingComponent* CSC, ClientPlayer* LocalPlayer, int type, int WeakPTRARRAY, int unk) = (int(*)(ClientSpottingComponent* CSC, ClientPlayer* LocalPlayer, int type, int WeakPTRARRAY, int unk))0x885700A8;

	if (!isClientAlive(Target))
		return;

	int firstptr = ((int)(Target->m_pControlledControllable)) + 0x4;
	int secondptr = (int)&firstptr;

	SendSpot(GetLocalPlayer()->m_pControlledControllable->m_pClientSpottingComponent, GetLocalPlayer(), 1, (int)&secondptr, 0);
}

void ESP(int USP)
{
	Matrix VehiclePos = Matrix();
	Matrix trans = Matrix();

	Vector3 inFoot = Vector3(0, 0, 0);
	Vector3 POS = Vector3(0, 0, 0);
	Vector3 crnr2 = Vector3(0, 0, 0);
	Vector3 crnr3 = Vector3(0, 0, 0);
	Vector3 crnr4 = Vector3(0, 0, 0);
	Vector3 crnr5 = Vector3(0, 0, 0);
	Vector3 crnr6 = Vector3(0, 0, 0);
	Vector3 crnr7 = Vector3(0, 0, 0);
	Vector3 min = Vector3(0, 0, 0);
	Vector3 max = Vector3(0, 0, 0);
	Vector3 inHead = Vector3(0, 0, 0);
	Vector3 headPos = Vector3(0, 0, 0);

	Vector4 Cerulean = Vector4(0, 0.4823529411764706, 0.6549019607843137, 1);
	Vector4 CRED = Vector4(1, 0, 0, 1);
	Vector4 CYELLOW = Vector4(1, 1, 0, 1);
	Vector4 CGREEN = Vector4(0, 1, 0, 1);
	Vector4 CORANGE = Vector4(255 / 255, 105 / 255, 5 / 255, 1 / 255);
	Vector4 ESP_AimTarget = Vector4(1, 0.67, 0, 1);
	Vector4 cESP = Vector4(0, 0, 0, 0);
	Vector4 CWHITE = Vector4(1, 1, 1, 1);
	Vector4 tBlue = Vector4(0.5, 0.4, 1, 1);
	Vector4 vMin = Vector4(0, 0, 0, 0);
	Vector4 vMax = Vector4(0, 0, 0, 0);

	char text[200] = { 0 };

	for (int i = 0; i < 26; i++)
	{
		ClientPlayer* Players = GetClientPlayer(i);
		ClientPlayer* LocalEntity = GetLocalPlayer();

		if (MmIsAddressValid(Players))
		{
			if (Players != LocalEntity)
			{
				if (Players->m_pAttachedControllable)
				{
					if (Players->m_TeamID == LocalEntity->m_TeamID)
					{
						if (bVehicleESP)
							VehicleESP(Players->m_pAttachedControllable, &CGREEN, Vector3(NULL, NULL, NULL));
					}
					else
					{
						Players->m_pAttachedControllable->m_EngineChams = bVehicleChams == false ? 0x20 : 0x90;

						if (bVehicleESP)
							VehicleESP(Players->m_pAttachedControllable, &CRED, Vector3(NULL, NULL, NULL));
					}
				}

				if (MmIsAddressValid(Players->m_pControlledControllable))
				{
					if (Players->m_pControlledControllable->m_pBFClientSoldierHealthComponent->m_fhealth > 1.0f)
					{
						Players->m_pControlledControllable->EngineChamsBehingBigWalls = 0x9f;

						if (bESPFriendly || bDrawBonesF || bFriendName || bDrawSnapLinesF)
						{
							if (Players->m_TeamID == LocalEntity->m_TeamID)
							{
								Players->m_pControlledControllable->m_EngineChams = bPlayerChamsF == true ? 0x20 : 0x90;

								inHead = Players->m_pControlledControllable->m_Transforms[10].m_position;
								inHead.x -= 1.5f;
								inHead.y -= 1.0f;
								inFoot = Players->m_pControlledControllable->m_ClientSoliderPrediction->Position;

								headPos = Players->m_pControlledControllable->m_Transforms[10].m_position;
								headPos.y += 0.2f;

								Vector3 feetPos = Players->m_pControlledControllable->m_ClientSoliderPrediction->Position;

								Vector3 headScreen, feetScreen;
								inFoot = Players->m_pControlledControllable->m_ClientSoliderPrediction->Position;

								Vector3 HeadBone = Vector3(0, 0, 0);
								Vector3 FeetBone = Vector3(0, 0, 0);

								if (bFriendName && (WorldToScreen(headPos, &headScreen) && WorldToScreen(feetPos, &feetScreen)))
									Drawing.DrawText(Players->Name, 8.0f, &Vector4((feetScreen.x - (strlen(Players->Name)) * (8.0f / 3.5f)), 0, 3234354, (headScreen.y * 2) - 25.0f), &CWHITE);//


								switch (ESPType)
								{
								case 1:
								{
									Draw2DBox(Players, CGREEN, 0.8);
									break;
								}
								case 0:
								{
									TransformDrawAABB((ClientVehicleEntity*)Players->m_pControlledControllable, CGREEN, 0.8);
									break;
								}
								}
								if (bDrawSnapLinesF)
								{
									if (WorldToScreen(inFoot, &inFoot))
									{
										switch (SnapArrayEnumaratorF)
										{
										case 0:
											DrawLine(1280 / 2, 0, inFoot.x, (inFoot.y), 1, &CGREEN);
											break;

										case 1:
											DrawLine(1280 / 2, 720 / 2, inFoot.x, (inFoot.y), 1, &CGREEN);
											break;

										case 2:
											DrawLine(1280 / 2, 720, inFoot.x, (inFoot.y), 1, &CGREEN);
											break;
										}
									}
								}

								if (bDrawBonesF)
									DoAllBones(Players, &Cerulean);
							}
						}

						if (bEnemyName || bESPEnemy || (bDrawSnapLinesE) || (bDrawBonesF || bDrawBonesE))
						{
							if (Players->m_TeamID != LocalEntity->m_TeamID)
							{
								Players->m_pControlledControllable->m_EngineChams = bPlayerChamsE == true ? 0x20 : 0x90;

								Vector3 inHead = Players->m_pControlledControllable->m_Transforms[10].m_position;
								inHead.x -= 1.5f;
								inHead.y -= 1.0f;
								inFoot = Players->m_pControlledControllable->m_ClientSoliderPrediction->Position;

								Vector3 headPos = Players->m_pControlledControllable->m_Transforms[10].m_position;
								headPos.y += 0.2f;

								Vector3 feetPos = Players->m_pControlledControllable->m_ClientSoliderPrediction->Position;

								Vector3 Test;
								Vector3 headScreen, feetScreen;

								if (bEnemyName && (WorldToScreen(headPos, &headScreen) && WorldToScreen(feetPos, &feetScreen)))
									Drawing.DrawText(Players->Name, 8.0f, &Vector4((feetScreen.x - (strlen(Players->Name)) * (8.0f / 3.5f)), 0, 3234354, (headScreen.y * 2) - 25.0f), &CWHITE);

								if (bESPEnemy)
								{
									switch (ESPType)
									{
									case 1:
									{
										Draw2DBox(Players, isClientWallable[i] == 0 ? CRED : CYELLOW, 0.8);
										break;
									}
									case 0:
									{
										TransformDrawAABB((ClientVehicleEntity*)Players->m_pControlledControllable, isClientWallable[i] == 0 ? CRED : CYELLOW, 0.8);
										break;
									}
									case 2:
										if (WorldToScreen(headPos, &headScreen) && WorldToScreen(feetPos, &feetScreen))
										{
											float height = feetScreen.y - headScreen.y;
											float width = height / 2;

											ESP_AimTarget.a = 0.2;
											CRED.a = 0.2;
											CYELLOW.a = 0.2;
											Drawing.DrawRect(headScreen.x - (width / 2), headScreen.y, width, height, isClientWallable[i] == 0 ? &CRED : &CYELLOW);
										}
										break;
									}
								}
								if (bDrawSnapLinesE)
								{
									if (WorldToScreen(feetPos, &inFoot))
									{
										switch (SnapArrayEnumaratorE)
										{
										case 0:
											DrawLine(1280 / 2, 0, inFoot.x, inFoot.y, 1.0f, isClientWallable[i] == 0 ? &CRED : &CYELLOW);
											break;

										case 1:
											DrawLine(1280 / 2, 720 / 2, inFoot.x, inFoot.y, 1.0f, isClientWallable[i] == 0 ? &CRED : &CYELLOW);
											break;

										case 2:
											DrawLine(1280 / 2, 720, inFoot.x, inFoot.y, 1.0f, isClientWallable[i] == 0 ? &CRED : &CYELLOW);
											break;
										}
									}
								}

								if (bDrawBonesE)
									DoAllBones(Players, &Cerulean);
							}
						}
					}
				}
			}
		}
	}
}

void DrawAmmoBoxs(ClientPlayer* LocalEntity, int USP)
{
	GameContext*  pGContext = GameContext::GetInstance();
	if (!MmIsAddressValid(pGContext))
		return;
	ClientLevel* pLevel = pGContext->m_PlayerLevel;
	if (!MmIsAddressValid(pLevel))
		return;
	void* pWorld = (void*)pLevel->m_pGameWorld;
	if (!MmIsAddressValid(pWorld))
		return;

	EntityIterator<ClientSupplySpherePre> flags(pWorld, (void*)Addresses->_0x89A39F28, Addresses->_0x5C);
	if (flags.front())
	{
		do
		{
			ClientSupplySpherePre *pResupplySphere = flags.front()->getObject(Addresses->_0x20);

			if (!MmIsAddressValid(pResupplySphere))
				continue;

			if (!MmIsAddressValid(pResupplySphere->m_ClientSupplySphereEntity))
				continue;

			TransformDrawAABB((ClientVehicleEntity*)pResupplySphere->m_ClientSupplySphereEntity, Vector4(0.2, 0.8, 0.2, 1), 1);
		} while (flags.next());
	}
}

void DrawVehicles(ClientPlayer* LocalEntity, int USP)
{
	Matrix trans;
	Vector3 Pos;

	GameContext*  pGContext = GameContext::GetInstance();
	if (!MmIsAddressValid(pGContext))
		return;
	ClientLevel* pLevel = pGContext->m_PlayerLevel;
	if (!MmIsAddressValid(pLevel))
		return;
	void* pWorld = (void*)pLevel->m_pGameWorld;
	if (!MmIsAddressValid(pWorld))
		return;

	EntityIterator<ClientVehicleEntity> flags(pWorld, (void*)Addresses->_0x89A10B10, Addresses->_0x5C);
	if (flags.front())
	{
		do
		{
			ClientVehicleEntity *pVehicle = flags.front()->getObject(Addresses->_0x20);

			if (!MmIsAddressValid(pVehicle))
				continue;

			Vector4 White = Vector4(1, 1, 1, 1);
			Vector4 Red = Vector4(1, 0, 0, 1);

			if (MmIsAddressValid(LocalEntity->m_pControlledControllable))
			{
				for (int i = 0; i < 24; i++)
				{
					ClientPlayer* pCP = GetClientPlayer(i);

					if (!MmIsAddressValid(pCP))
						continue;

					if (pVehicle->m_TeamId != 0)
						continue;

					if (!MmIsAddressValid(pCP->m_pAttachedControllable))
						continue;

					TransformDrawAABB(pVehicle, Vector4(1, 1, 1, 1), 1);
				}
			}
		} while (flags.next());
	}
}

void DrawCircle(float points, float radius, Vector3 Pos, Vector4 Color)
{
	for (int i = 0; i < points; ++i)
	{
		float angle1 = i * 2 * 3.141592653589793f / points;
		float angle2 = (i + 1) * 2 * 3.141592653589793f / points;
		DrawLine(Pos.x + radius * cos(angle1), (Pos.y + radius * sin(angle1)) / 2, Pos.x + radius * cos(angle2), (Pos.y + radius * sin(angle2)) / 2, 2, &Color);
	}
}

void DrawExplosives(ClientPlayer* LocalPlayer, int sp)
{
	GameContext*  pGContext = GameContext::GetInstance();
	if (!MmIsAddressValid(pGContext))
		return;

	ClientLevel* pLevel = pGContext->m_PlayerLevel;
	if (!MmIsAddressValid(pLevel))
		return;

	void* pWorld = (void*)pLevel->m_pGameWorld;
	if (!MmIsAddressValid(pWorld))
		return;

	EntityIterator<ClientExplosionPackEntityPre> flags(pWorld, (void*)Addresses->_0x89A39D48, Addresses->_0x5C);
	if (flags.front())
	{
		do
		{
			ClientExplosionPackEntityPre *pExplosive = flags.front()->getObject(Addresses->_0x20);

			if (!MmIsAddressValid(pExplosive))
				continue;

			if (!MmIsAddressValid(pExplosive->m_ClientExplosionPackEntity))
				continue;

			if (pExplosive->m_ClientExplosionPackEntity->m_TeamID != GetLocalPlayer()->m_TeamID)
				TransformDrawAABB((ClientVehicleEntity*)pExplosive->m_ClientExplosionPackEntity, Vector4(0.6, 0.4, 1, 1), 1);

		} while (flags.next());
	}
}

void DrawGrenade(ClientPlayer* LocalPlayer, int sp)
{
	GameContext*  pGContext = GameContext::GetInstance();
	if (!MmIsAddressValid(pGContext))
		return;
	ClientLevel* pLevel = pGContext->m_PlayerLevel;
	if (!MmIsAddressValid(pLevel))
		return;
	void* pWorld = (void*)pLevel->m_pGameWorld;
	if (!MmIsAddressValid(pWorld))
		return;

	EntityIterator<ClientGrenadePre> flags(pWorld, (void*)Addresses->_0x89A39DE8, Addresses->_0x5C);
	if (flags.front())
	{
		do
		{
			Matrix* pMatrix = new Matrix;
			ClientGrenadePre *pPickupEntity = flags.front()->getObject(Addresses->_0x20);

			Vector4 Red = Vector4(0.7725490196, 0.25882352941, 0.95686274509, 1);

			if (MmIsAddressValid(LocalPlayer->m_pControlledControllable))
			{
				Vector3 ResupplySphereV;
				if (!MmIsAddressValid(pPickupEntity))
					return;

				if (!MmIsAddressValid(pPickupEntity->m_GrenadeEntityData))
					return;

				if (!MmIsAddressValid(pPickupEntity->m_ClientGrenadeEntity))
					return;

				TransformDrawAABB((ClientVehicleEntity*)pPickupEntity, Vector4(1, 0.6, 0.2, 1), 1.5);
			}
		} while (flags.next());
	}
}

void DrawPickups(ClientPlayer* LocalPlayer, int sp)
{
	GameContext*  pGContext = GameContext::GetInstance();
	if (!MmIsAddressValid(pGContext))
		return;
	ClientLevel* pLevel = pGContext->m_PlayerLevel;
	if (!MmIsAddressValid(pLevel))
		return;
	void* pWorld = (void*)pLevel->m_pGameWorld;
	if (!MmIsAddressValid(pWorld))
		return;

	EntityIterator<ClientPickupEntity> flags(pWorld, (void*)Addresses->_0x89A38D38, Addresses->_0x5C);
	if (flags.front())
	{
		do
		{
			if (MmIsAddressValid(flags.front()) && MmIsAddressValid(flags.front()->getObject(0x20)))
				continue;

			ClientPickupEntity *pPickupEntity = flags.front()->getObject(Addresses->_0x20);
			if (!MmIsAddressValid(pPickupEntity))
				continue;

			Vector4 Red = Vector4(0.7725490196, 0.25882352941, 0.95686274509, 1);

			if (MmIsAddressValid(LocalPlayer->m_pControlledControllable))
			{
				Vector3 PickupV;

				if (!MmIsAddressValid(pPickupEntity))
					return;

				if (!MmIsAddressValid(pPickupEntity->m_PositionData))
					return;

				if (!MmIsAddressValid(pPickupEntity->m_data))
					return;

				if (!MmIsAddressValid(&pPickupEntity->m_PositionData->m_Position))
					return;

				PickupV = pPickupEntity->m_PositionData->m_Position;

				if (WorldToScreen(PickupV, &PickupV))
				{
					if (MmIsAddressValid(pPickupEntity->m_PickupName) && MmIsAddressValid(pPickupEntity->m_PickupName->m_name))
					{
						Drawing.DrawText(pPickupEntity->m_PickupName->m_name, 10, &Vector4(PickupV.x - 20.0f, 0, 3234354, (PickupV.y - 30.0f) * 2), &Vector4(1, 1, 1, 1));
					}
				}

				TransformDrawAABB((ClientVehicleEntity*)pPickupEntity, Vector4(1, 0, 1, 1), 0.9);
			}
		} while (flags.next());
	}
}

void VehicleESP(ClientVehicleEntity * pVehicle, Vector4 * cVeh, Vector3 Pos = Vector3(NULL, NULL, NULL))
{
	ClientPlayer* LocalEntity = GetLocalPlayer();

	if (MmIsAddressValid(pVehicle))
	{
		TransformDrawAABB(pVehicle, *cVeh, 1);
		pVehicle->m_EngineChams = bVehicleChams == false ? 0x20 : 0x90;
	}
}

void TeamHealing(ClientPlayer* localPlayer)
{
	ClientPlayer* pTeammate;

	for (int i = 0; i < 24; i++)
	{
		pTeammate = GetClientPlayer(i);

		if (isClientAlive(pTeammate))
		{
			if (pTeammate->m_TeamID == localPlayer->m_TeamID)
			{
				SendDamageMessage(pTeammate, localPlayer, -100, 0, 0);
			}
		}
	}
}

void DoInvisible()
{
	int Round2 = (int)GetLocalPlayer()->Customize;
	int VeniceCustomize = (int)GetLocalPlayer()->Customize;

	VeniceCustomize = *(int*)(VeniceCustomize + 0x18);
	VeniceCustomize = *(int*)(VeniceCustomize + 0x8);
	VeniceCustomize = *(int*)(VeniceCustomize + 0x4);
	VeniceCustomize = *(int*)(VeniceCustomize + 0x10);
	VeniceCustomize = *(int*)(VeniceCustomize);

	Round2 = *(int*)(Round2 + 0x18);
	Round2 = *(int*)(Round2 + 0x8);
	Round2 = *(int*)(Round2);
	Round2 = *(int*)(Round2 + 0x10);

	*(int*)Round2 = VeniceCustomize;
}

void SendDamageMessage(ClientPlayer* Target, ClientPlayer* LocalPlayer, float damage, SoldierWeaponUnlockAsset* Weapon, int HitType)
{
	if (Target->m_pControlledControllable)
	{
		int(*SendClientDamageMessage)(int, char, damagemsg_t* Damage, int, ClientPlayer*, int, int, float) = (int(*)(int, char, damagemsg_t* Damage, int, ClientPlayer*, int, int, float))0x885A8A70;

		damagemsg_t* Damage = new damagemsg_t;
		memset(Damage, 0, sizeof(damagemsg_t));
		Damage->vfptr = Addresses->_0x880330E8;
		*(int*)(Addresses->_0x897C150C) = (int)LocalPlayer;
		Damage->ClientPlayerPtr = Addresses->_0x897C150C;

		if (bSpoofTarget)
		{
			if (MmIsAddressValid(Target) && MmIsAddressValid(Target->m_pControlledControllable) && MmIsAddressValid(Target->m_pControlledControllable->m_ClientSoliderWeaponComponent) && MmIsAddressValid(Target->m_pControlledControllable->m_ClientSoliderWeaponComponent->GetActiveWeapon()) && MmIsAddressValid(Target->m_pControlledControllable->m_ClientSoliderWeaponComponent->GetActiveWeapon()->m_pWeapon) && MmIsAddressValid(Target->m_pControlledControllable->m_ClientSoliderWeaponComponent->GetActiveWeapon()->m_pWeapon->m_pModifier) && MmIsAddressValid(Target->m_pControlledControllable->m_ClientSoliderWeaponComponent->GetActiveWeapon()->m_pWeapon->m_pModifier->m_pWeaponUnlockAsset))
			{
				*(int*)(Addresses->_0x897C1510) = (int)(Target->m_pControlledControllable->m_ClientSoliderWeaponComponent->GetActiveWeapon()->m_pWeapon->m_pModifier->m_pWeaponUnlockAsset);
			}
		}
		else
			*(int*)(Addresses->_0x897C1510) = (int)(Weapon);

		int Health = (int)Target->m_pControlledControllable->m_pBFClientSoldierHealthComponent;

		SendClientDamageMessage(Health, LocalPlayer->getId(), Damage, 1, Target, 0, HitType, damage);

		delete Damage;
	}
}