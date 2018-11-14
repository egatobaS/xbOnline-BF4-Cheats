#include "main.h"

jmp_buf jump_buffer;

Detour* GameUnhandledExceptionFilterDetour;
Detour* UnhandledExceptionFilterDetour;

pUnhandledExceptionFilter UnhandledExceptionFilterStub;
pUnhandledExceptionFilter GameUnhandledExceptionFilterStub;

int NewUnhandledExceptionFilter(EXCEPTION_POINTERS * ExceptionInfo)
{
	
	printf("ExceptionAddress %X\n", ExceptionInfo->ExceptionRecord->ExceptionAddress);

	ExitThread(0);

	return UnhandledExceptionFilterStub(ExceptionInfo);
}

int GameUnhandledExceptionFilter(EXCEPTION_POINTERS * ExceptionInfo)
{
	printf("ExceptionAddress %X\n", ExceptionInfo->ExceptionRecord->ExceptionAddress);

	//RestoreHooks();

	longjmp(jump_buffer, (int)ExceptionInfo->ExceptionRecord->ExceptionAddress);

	return GameUnhandledExceptionFilterStub(ExceptionInfo);
}