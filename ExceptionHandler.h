#pragma once

extern jmp_buf jump_buffer;

typedef int(*pUnhandledExceptionFilter)(EXCEPTION_POINTERS * ExceptionInfo);
extern pUnhandledExceptionFilter UnhandledExceptionFilterStub;

extern pUnhandledExceptionFilter GameUnhandledExceptionFilterStub;

extern Detour* GameUnhandledExceptionFilterDetour;
extern Detour* UnhandledExceptionFilterDetour;

int NewUnhandledExceptionFilter(EXCEPTION_POINTERS * ExceptionInfo);
int GameUnhandledExceptionFilter(EXCEPTION_POINTERS * ExceptionInfo);