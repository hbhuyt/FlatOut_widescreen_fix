#include "stdafx.h"
#include "CPatch.h"

HANDLE HndThread;

int* g_Width = (int *)0x6B0D88;
int* g_Height = (int *)0x6B0D8C; 

int g_CameraAspectRatio_x = 0x5069DA;
int g_CameraAspectRatio_y = 0x5069E0;
int g_hud_stretch_x = 0x667CE4;

#define screen_width (float)*g_Width
#define screen_heigth (float)*g_Height
#define hud_stretch_x (float)*g_hud_stretch_x

float hud_stretch_new = 0.0;

int Thread()
{
	while (!screen_width)
	{
		Sleep(0);
	}


	hud_stretch_new = 1.0/(480.0*(screen_width/screen_heigth));

	CPatch::SetFloat(g_CameraAspectRatio_x, screen_width);
	CPatch::SetFloat(g_CameraAspectRatio_y, screen_heigth);
	CPatch::SetFloat(g_hud_stretch_x, hud_stretch_new);
		
	return 0;
}


BOOL APIENTRY DllMain(HMODULE hModule, DWORD reason, LPVOID lpReserved)
{
    if(reason==DLL_PROCESS_ATTACH)
    {
		HndThread = CreateThread(0,0,(LPTHREAD_START_ROUTINE)&Thread,NULL,0,NULL);
    }
    return TRUE;
}

