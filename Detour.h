#pragma once

class Detour
{
public:
	Detour();
	~Detour();
	void* HookFunction(unsigned int Address, void* Hook);
	void RestoreFunction();
	void PatchInJump(unsigned int Address, unsigned int Destination, bool Linked);
private:
	int IndexDetour;
	static int DetourCount;
	static unsigned char DetourSection[0x10000];
	int BranchResolve(int Instruction, int BranchAddress);
	int* StubAddress;
	void* Destination;
	void* HookAddress;
	int OriginalInstructions[4];
	bool isHooked;
};
