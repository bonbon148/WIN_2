#include<Windows.h>
#include<stdio.h> //sprintf()
#include"resource.h"

CONST CHAR* g_sz_VALUES[] = { "This", "is", "my", "frist", "List", "Box" };

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgProcAdd(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgProcEdit(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


INT WINAPI WinMain(HINSTANCE hIstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	DialogBoxParam(hIstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc, 0);
	return 0; 
}

BOOL CALLBACK DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HWND hListBox = GetDlgItem(hwnd, IDC_LIST_BOX);
		for (int i = 0; i < sizeof(g_sz_VALUES) / sizeof(g_sz_VALUES[0]); i++)
			SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)g_sz_VALUES[i]);
	}
		break;
	case WM_COMMAND:
	{
		HWND hListBox = GetDlgItem(hwnd, IDC_LIST_BOX);
		switch (LOWORD(wParam))
		{
		case IDC_LIST_BOX:
			if (HIWORD(wParam) == LBN_DBLCLK)
				DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG_ADD), hwnd, (DLGPROC)DlgProcEdit, 0);
			break;
		case IDC_BUTTON_ADD:
			DialogBoxParam(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_DIALOG_ADD), hwnd,(DLGPROC)DlgProcAdd, 0);
			break;
		case IDC_BUTTON_DELETE:
			SendMessage(hListBox, LB_DELETESTRING, SendMessage(hListBox, LB_GETCURSEL, 0, 0), 0);
		break;
		case IDOK:
		{
			INT i = SendMessage(hListBox, LB_GETCURSEL, 0, 0); //Get Current Selection 
			CHAR sz_buffer[256] = {};
			SendMessage(hListBox, LB_GETTEXT, i, (WPARAM)sz_buffer);
			CHAR sz_message[256] = {};
			sprintf(sz_message, "Вы выбрали вариант №%i со значением '%s'.", i, sz_buffer);
			MessageBox(hwnd, sz_message, "Выбранный элемент", MB_OK | MB_ICONINFORMATION);
		}
			break;
		case IDCANCEL:EndDialog(hwnd, 0);
		}
	}
		break;
	case WM_CLOSE:EndDialog(hwnd, 0);
	}
	return FALSE;
}
BOOL CALLBACK DlgProcAdd(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		SetFocus(GetDlgItem(hwnd, IDC_EDIT_ELEMENT));
		break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			CHAR sz_buffer[256] = {};
			HWND hEditElement = GetDlgItem(hwnd, IDC_EDIT_ELEMENT);
			SendMessage(hEditElement, WM_GETTEXT, 256, (LPARAM)sz_buffer);

			HWND hParent = GetParent(hwnd);
			HWND hListBox = GetDlgItem(hParent, IDC_LIST_BOX);
			if (SendMessage(hListBox, LB_FINDSTRINGEXACT, -1, (LPARAM)sz_buffer) == LB_ERR)
				SendMessage(hListBox, LB_ADDSTRING, 0, (LPARAM)sz_buffer);
			else
			{
				MessageBox(hwnd, "Такой элемент уже есть в списке", "Info", MB_OK | MB_ICONINFORMATION);
				break;
			}
		}
		case IDCANCEL:EndDialog(hwnd, 0);
		}
	}
	break;
	case WM_CLOSE:EndDialog(hwnd, 0);
	}
	return FALSE;

}
BOOL CALLBACK DlgProcEdit(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	
	HWND hEdit = GetDlgItem(hwnd, IDC_EDIT_ELEMENT);
	CHAR sz_buffer[256] = {};
	HWND hParent = GetParent(hwnd);
	HWND hListBox = GetDlgItem(hParent, IDC_LIST_BOX);
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)"Изменение элемента");
		INT i = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
		SendMessage(hListBox, LB_GETTEXT, i, (LPARAM)sz_buffer);
		SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		DWORD dwError = GetLastError();
		SetFocus(hEdit);
		DWORD start = 0;
		DWORD n = SendMessage(hEdit, EM_LINELENGTH, -1, 0);
		SendMessage(hEdit, EM_SETSEL, (WPARAM)&start, (LPARAM)&n);
	}
	break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		{
			SendMessage(hEdit, WM_GETTEXT, 256, (LPARAM)sz_buffer);
			INT i = SendMessage(hListBox, LB_GETCURSEL, 0, 0);
			SendMessage(hListBox, LB_DELETESTRING, i, 0);
			SendMessage(hListBox, LB_INSERTSTRING, i, (LPARAM)sz_buffer);
		}
		case IDCANCEL:EndDialog(hwnd, 0);
		}
		break;
	case WM_CLOSE:EndDialog(hwnd, 0);
	}
	return FALSE;
}