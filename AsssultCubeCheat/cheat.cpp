#include "sdk.hpp"
#include <windows.h>
#include <vector>
#include <thread>
#include "hook.hpp"
#include "openGlDrawer.hpp"


game* GameHandler = nullptr;

float* viewMatrix;

typedef int(__stdcall* TD_ORIGSWAPBUF)(HDC);

TD_ORIGSWAPBUF ogTramp;

void esp() {

	GameHandler->localplayer->health = 100;

	for (int i = 1; i < GameHandler->playerCount; i++) {

		if (GameHandler->otherplayers[i]->health > 300) {
			continue;
		}

		Vector2 playerScreenPos;
		if (WorldToScreen(GameHandler->otherplayers[i]->playerPos, playerScreenPos, viewMatrix)) {
			printf("PLAYER: %f %f\n", playerScreenPos.x, playerScreenPos.y);
			Vector2 headScreenPos;
			if (WorldToScreen(GameHandler->otherplayers[i]->headPos, headScreenPos, viewMatrix)) {
				printf("HEAD: %f %f\n", headScreenPos.x, headScreenPos.y);
				float height = headScreenPos.y - playerScreenPos.y;
				drawPlayer(playerScreenPos.x, playerScreenPos.y, height, height / 2);
				GLubyte color[3] = { 255, 0, 0 };
			}
		}

	}

}

int __stdcall swapHookHandler(HDC hDC) {


	initDrawer();

	esp();

	restoreDrawer();


	return ogTramp(hDC);
}

void init() {
	HMODULE hm = GetModuleHandle(L"ac_client.exe");

	if (hm == NULL) {
		return;
	}

	DWORD gameBase = (DWORD)hm;

	DWORD gameInstanceAddr = gameBase + 0x18AC00; // offset for game object instance 

	DWORD viewMatrixAddr = gameBase + 0x17DFD0;

	viewMatrix = (float*)viewMatrixAddr;

	GameHandler = (game*)gameInstanceAddr;

	HMODULE opengl = GetModuleHandle(L"opengl32.dll");

	if (opengl == NULL) {
		printf("couldnt open opengl\n");
		return;
	}

	LPVOID swapBufferAddr = (LPVOID)GetProcAddress(opengl, "wglSwapBuffers");

	if (swapBufferAddr == NULL) {
		printf("couldnt open swapbuffer\n");
		return;
	}

	ogTramp = (TD_ORIGSWAPBUF)Trampoline((DWORD)swapBufferAddr, (DWORD)swapHookHandler);

	return;

}