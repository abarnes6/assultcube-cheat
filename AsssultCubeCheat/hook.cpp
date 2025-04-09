#include "hook.hpp"
#include <windows.h>
#include <iostream>

DWORD targetAddress;
LPVOID returnAddress;
LPVOID allocAddress;

void* Trampoline(DWORD targetFunction, DWORD ourFunction) {

	targetAddress = targetFunction;

	// create a space to save the original bytes, this will be the trampoline space
	allocAddress = VirtualAlloc(NULL, 64, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (allocAddress == NULL) {
		printf("failed to alloc trampoline\n");
		return nullptr;
	}

	memcpy(allocAddress, (void*)targetFunction, 5);

	// add a jmp opcode to targetFunction plus 5 bytes to the end of allocAddress
	char trampJump[5] = { 0xE9, 0 };
	DWORD* jumpRel = (DWORD*)&trampJump[1];

	DWORD jumpTarget = targetFunction + 0x5;

	*jumpRel = jumpTarget - ((DWORD)allocAddress + 0x5 + 0x5);

	memcpy((void*)((DWORD)allocAddress + 0x5), &trampJump[0], 5);

	// replace 6 bytes at target function address with our hook address

	


	char hookJump[5] = { 0xE9, 0 };

	DWORD* hookJumpRel = (DWORD*)&hookJump[1];

	*hookJumpRel = ((DWORD)ourFunction) - ((DWORD)targetFunction + 0x5);

	DWORD oldProt;

	VirtualProtect((LPVOID)targetFunction, 5, PAGE_EXECUTE_READWRITE, &oldProt);

	memcpy((void*)targetFunction, &hookJump[0], 0x5);

	VirtualProtect((LPVOID)targetFunction, 5, oldProt, &oldProt);

	return (void*)allocAddress;

}

void unHook() {

	DWORD oldProt;

	VirtualProtect((LPVOID)targetAddress, 5, PAGE_EXECUTE_READWRITE, &oldProt);

	memcpy((void*)targetAddress, allocAddress, 0x5);

	VirtualProtect((LPVOID)targetAddress, 5, oldProt, &oldProt);
}