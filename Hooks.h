#pragma once

typedef int(*pRayCastHook)(int r3, int r4, int r5, int r6, int r7, int r8, int r9, int r10);

typedef int(*pBulletHook)(int r3, int r4, int r5, int r6, int r7);

extern Detour* RayCastHookDetour;

extern pBulletHook Bullet;

extern Detour* BulletHookDetour;

extern pRayCastHook RayCastHookStub;

extern Detour* DrawingDetour;

extern UIRender Drawing;

typedef void(*pUnkDrawingHook)(int r3, int r4, int r5, int r6, int r7, int r8, int r9, int r10, int r11, int r12, int r13, int r14, int r15, int r16, int r17, int r18, int r19, int r20, int r21, int r22, int r23, int r24, int r25, int r26, int r27, int r28, int r29, int r30);

extern Detour* UNKDrawingCrash;
extern pUnkDrawingHook pUnkDrawingStub;

extern ClientPlayer* AimTarget;
extern int ClientCount;

extern bool setBitFlag;
extern bool bTriggerBot;

typedef int(*AddMoveStub)(int p_r3, int p_r4);
extern AddMoveStub AddMoveOriginal;
extern Detour* AddMoveHook;

extern Detour* XamInputGetStateDetour;

typedef int(*XamInputGetStateStub)(DWORD dwUserIndex, DWORD r4, PXINPUT_STATE pState);
extern XamInputGetStateStub XamInputGetStateOriginal;

int BulletHook(int r3, int r4, int r5, int r6, int r7);

int AddMove(int * streammanagermoveclient, EntryInputState * pMove);

int DrawingHook(int r3, int r4, int r5, int r6);

int filter(const char* cpp, const char* function, EXCEPTION_POINTERS *ExceptionInfo);

void DrawingFix(int r3, int r4, int r5, int r6, int r7, int r8, int r9, int r10, int r11, int r12, int r13, int r14, int r15, int r16, int r17, int r18, int r19, int r20, int r21, int r22, int r23, int r24, int r25, int r26, int r27, int r28, int r29, int r30);

int RayCastHook(int r3, int r4, int r5, int r6, int r7, int r8, int r9, int r10);

DWORD XamInputGetStateHook(DWORD dwUserIndex, DWORD r4, PXINPUT_STATE pState);
