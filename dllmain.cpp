#include "stdafx.h"
#include "CPatch.h"

HANDLE HndThread;

//v1.1
int* g_Width = (int *)0x6B0D88;
int* g_Height = (int *)0x6B0D8C; 

int g_CameraAspectRatio_x = 0x5069DA;
int g_CameraAspectRatio_y = 0x5069E0;
int g_hud_stretch_x = 0x667CE4;

float hud_stretch_new = 0.0;

int Thread()
{
	Sleep(1000);
	while ( ((char)*(DWORD*)0x66C554 == 255 || !(char)*(DWORD*)0x66C554 == NULL) && ((char)*(DWORD*)0x66D554 == 255 || !(char)*(DWORD*)0x66D554 == NULL) ) //just a random address i found to check whether player is in menu
	{
		Sleep(0);
			if((char)*(DWORD*)0x66C554 == 130) {
				break;
			}
	}
	
	if( !(*(float *)g_CameraAspectRatio_x == 4.0) ) {  //steam demo exe
		g_Width = (int *)0x676BC8;
		g_Height = (int *)0x676BCC; 

		g_CameraAspectRatio_x = 0x4D812A;
		g_CameraAspectRatio_y = 0x4D8130;
		g_hud_stretch_x = 0x635804;
	}

	if( !(*(float *)g_CameraAspectRatio_x == 4.0) ) { //exe v1.0 (+steam)
		g_Width = (int *)0x6B8128;
		g_Height = (int *)0x6B812C; 

		g_CameraAspectRatio_x = 0x50576A;
		g_CameraAspectRatio_y = 0x505770;
		g_hud_stretch_x = 0x666B5C;
	}
	


	if( *(float *)g_CameraAspectRatio_x == 4.0 ) { 

	hud_stretch_new = 1.0/(480.0*(((float)*g_Width) / ((float)*g_Height)));

	CPatch::SetFloat(g_CameraAspectRatio_x, (float)*g_Width);
	CPatch::SetFloat(g_CameraAspectRatio_y, (float)*g_Height);
	CPatch::SetFloat(g_hud_stretch_x, hud_stretch_new);
	}
		
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
