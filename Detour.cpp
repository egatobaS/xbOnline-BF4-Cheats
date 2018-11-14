#include "main.h"

int Detour::DetourCount = 0;

unsigned char Detour::DetourSection[0x10000] = { 0 };

Detour::Detour()
{
	StubAddress = NULL;
	Destination = NULL;
	HookAddress = NULL;

	memset(OriginalInstructions, 0, sizeof(int) * 4);

	isHooked = false;
}

Detour::~Detour()
{
	if (isHooked)
		memcpy(HookAddress, OriginalInstructions, sizeof(int) * 4);

	isHooked = false;
}

int Detour::BranchResolve(int Instruction, int BranchAddress)
{
	int Address = 0;

	unsigned int CurrentOffset = Instruction & 0x3FFFFFC;

	if (CurrentOffset & (1 << 25))
		CurrentOffset |= 0xFC000000;

	return BranchAddress + CurrentOffset;
}

void Detour::RestoreFunction()
{
	if (isHooked)
		memcpy(HookAddress, OriginalInstructions, sizeof(int) * 4);

	isHooked = false;
}

void Detour::PatchInJump(unsigned int Address, unsigned int Destination, bool Linked)
{
	unsigned int DestinationAddress = (unsigned int)Destination;

	unsigned int* Instructions = (unsigned int*)Address;

	Instructions[0] = 0x3D600000 + ((Destination >> 16) & 0xFFFF); // lis 	%r11, dest>>16

	Instructions[1] = 0x616B0000 + (DestinationAddress & 0xFFFF);

	Instructions[2] = 0x7D6903A6;

	Instructions[3] = 0x4E800420 + Linked;
}

void* Detour::HookFunction(unsigned int Address, void* Hook)
{
	if (!Address || !Hook) return 0;

	Destination = (void*)Hook;

	HookAddress = (void*)Address;

	memcpy(OriginalInstructions, (void*)Address, sizeof(int) * 4);

	unsigned int InstructionWrittenCount = 0;

	IndexDetour = DetourCount;

	DetourCount += (32 * 4);

	StubAddress = (int*)&DetourSection[IndexDetour];

	unsigned int* HookAddress = (unsigned int*)Address;

	for (int i = 0; i < 4; i++)
	{
		if ((HookAddress[i] & 0xF8000000) == 0x48000000)
		{
			PatchInJump((unsigned int)&StubAddress[InstructionWrittenCount], (unsigned int)BranchResolve(HookAddress[i], (int)&HookAddress[i]), true);
			InstructionWrittenCount += 4;
		}
		else
		{
			StubAddress[InstructionWrittenCount] = HookAddress[i];
			InstructionWrittenCount++;
		}
	}

	PatchInJump((unsigned int)&StubAddress[InstructionWrittenCount], (unsigned int)(Address + 0x10), false);

	PatchInJump((unsigned int)Address, (unsigned int)Hook, false);

	isHooked = true;

	return StubAddress;
}