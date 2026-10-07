#include<Windows.h>
#include<cstdio>
#include"resource.h"

CONST CHAR* g_szVALUES[] = { "This", "is", "my", "Frist", "Combo", "Box" };

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMag, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR ipCmdLine, INT nCmdShow)
{
	DialogBoxParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG_MAIN), NULL, (DLGPROC)DlgProc, NULL);
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMag, WPARAM wParam, LPARAM lParam)
{
	switch (uMag)
	{
	case WM_INITDIALOG:
	{
		HICON hIcon = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1));
		SendMessage(hwnd, WM_SETICON, 0, (LPARAM)hIcon);

		HWND hCombo = GetDlgItem(hwnd, IDC_COMBO1);
		for (int i = 0; i < sizeof(g_szVALUES) / sizeof(g_szVALUES[0]); i++)
		{
			SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)g_szVALUES[i]);
		}
	}
	
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			CONST INT SIZE = 256;
			CHAR szBuffer[SIZE] = {};
			CHAR szMessage[SIZE] = {};
			HWND hCombo = GetDlgItem(hwnd, IDC_COMBO1);
			INT i = SendMessage(hCombo, CB_GETCURSEL, 0, 0);  //Get current selection
			SendMessage(hCombo, CB_GETLBTEXT, i, (LPARAM)szBuffer);
			sprintf
			(
				szMessage,
				"Вы выбрали элемент номер N%i со значением '%s'.", i, szBuffer
			);
			MessageBox(hwnd, szMessage, "Info", MB_OK | MB_ICONINFORMATION);
		}
			break;
		case IDCANCEL: EndDialog(hwnd, 0);
		}
			break;
	case WM_CLOSE: EndDialog(hwnd, 0);
		break;
	}
	return FALSE;
}