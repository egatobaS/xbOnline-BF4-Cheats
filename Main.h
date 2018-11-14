#include <xtl.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include <cstring>
#include <random>
#include <ctime>
#include <vector>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <time.h>
#include <stdarg.h>
#include <xbox.h>
#include <setjmp.h>
#include <stdint.h>

#include "Classes.h"
#include "Addresses.h"
#include "Functions.h"
#include "Aimbot.h"
#include "Detour.h"
#include "Drawing.h"
#include "Menu.h"
#include "Hooks.h"
#include "ExceptionHandler.h"
#include "ClassCustomization.h"
#include "MenuOptions.h"
#include "MenuDrawing.h"
#include "ClientVaultComponent.h"

#include "SimpleIni.h"

extern bool ShouldSetIni;
extern bool ShouldEndThread;



#if defined(_DEBUG)
#define printf DbgPrintf
#else
#define printf DbgPrintf
#endif

//int RestoreHooks();

BOOL WINAPI DllMain(HANDLE ModuleHandle, unsigned int fdwReason, LPVOID lpReserved);
