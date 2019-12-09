// Keypush.cpp : アプリケーション用のエントリ ポイントの定義
//

#include "stdafx.h"

int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow )
{
	//HWND hWnd = FindWindow("SlotFrame", NULL);

 	//SendMessage(

	while(1){
		keybd_event(VK_SPACE, 0, 0, 0);
		keybd_event(VK_SPACE, 0, KEYEVENTF_KEYUP, 0);
		Sleep(1000);
	}

	return 0;
}



