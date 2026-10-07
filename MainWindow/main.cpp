#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<cstdio>

#define IDC_STATIC	1000
#define IDC_EDIT	1001
#define IDC_BUTTON	1002

CONST CHAR g_szMyWindowClass[] = "My Window Class";
INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//1) Регистрация класса окна:
	WNDCLASSEX wClass;
	ZeroMemory(&wClass, sizeof(wClass));
	wClass.style = NULL;
	wClass.cbSize = sizeof(wClass);
	wClass.cbClsExtra = 0;
	wClass.cbWndExtra = 0;

	//wClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	//wClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wClass.hIcon = (HICON)LoadImage
	(
		hInstance,
		"bitcoin.ico", 
		IMAGE_ICON,
		LR_DEFAULTSIZE, LR_DEFAULTSIZE,
		LR_LOADFROMFILE
	);
	wClass.hIconSm = (HICON)LoadImage
	(
		hInstance,
		"litecoin.ico",
		IMAGE_ICON,
		LR_DEFAULTSIZE, LR_DEFAULTSIZE,
		LR_LOADFROMFILE
	);

	wClass.hCursor = (HCURSOR)LoadImage
	(
		hInstance, 
		"starcraft-original\\Working In Background.ani", 
		IMAGE_CURSOR,
		LR_DEFAULTSIZE, LR_DEFAULTSIZE,
		LR_LOADFROMFILE
	);
	//wClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wClass.hbrBackground = (HBRUSH)COLOR_WINDOW;

	wClass.lpszClassName = g_szMyWindowClass;
	wClass.lpszMenuName = NULL;
	wClass.lpfnWndProc = (WNDPROC)WndProc;
	wClass.hInstance = hInstance;

	if (!RegisterClassEx(&wClass))
	{
		MessageBox(NULL, "Class registration failed", NULL, MB_OK | MB_ICONERROR);
		return 0;
	}

	//2) Создание окна:
	int screen_width = GetSystemMetrics(SM_CXSCREEN);
	int screen_height = GetSystemMetrics(SM_CYSCREEN);
	int window_width = screen_width * 3 / 4;
	int window_height = screen_height * 3 / 4;
	int window_start_x = screen_width * 1 / 8;
	int window_start_y = screen_height * 1 / 8;

	HWND hwnd = CreateWindowEx
	(
		NULL,			    //exStyle
		g_szMyWindowClass, //Class name
		g_szMyWindowClass,   //Window title
		WS_OVERLAPPEDWINDOW, //Window style
		window_start_x, window_start_y,		//Position
		window_width, window_height,	   //Window size
		NULL, //Parent Window
		NULL, //hMenu Для главного окна сюда передается ResourceID главного меню.
			  //Для дочернего окна в hMenu передается ResourceID создоваемого элемента главного окна.
			  //По этому Resource_ID мы сможем находить HWND нужного элемента при помощи функции GetDlgItem(hwnd, RESOURCE_ID);
			  //Абсолютно любой Recourse_ID представляет собой целое число (1001) 
		hInstance,
		NULL
	);
	if (hwnd == NULL)
	{
		MessageBox(NULL, "Window creation failed", NULL, MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	//3) Запуск цикла сообщений:
	
	MSG msg;
	while (GetMessage(&msg, 0, 0, NULL) > 0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

INT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		//WM - Window Message
	case WM_CREATE:
	{
		HWND hStatic = CreateWindowEx
		(
			NULL,
			"Static",
			"Этот StaticText создан при помощи функции CreateWindow()",
			WS_CHILD | WS_VISIBLE,
			10, 10,
			500, 25,
			hwnd,
			(HMENU)IDC_STATIC,
			GetModuleHandle(NULL), //hInstance
			NULL
		);
		HWND hEdit = CreateWindowEx
		(
			NULL,
			"Edit",
			"Это текстовое поле создано при помощи функции CreateWindowEx()",
			WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT,
			//WS_ - Window Style
			//ES_ - EditStyle
			10, 38,
			500, 22,
			hwnd,
			(HMENU)IDC_EDIT, 
			GetModuleHandle(NULL),
			NULL
		);
		HWND hButton = CreateWindowEx
		(
			NULL,
			"Button",
			"Применить",
			WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, //BS_ - ButtonStyle
			410, 67,
			100, 32,
			hwnd,
			(HMENU)IDC_BUTTON,
			GetModuleHandle(NULL),
			NULL
		);
		
	}
	break;
	case WM_SIZE:
	case WM_MOVE:
	{
		RECT window_rect;
		GetWindowRect(hwnd, &window_rect);
		INT width = window_rect.right - window_rect.left;
		INT height = window_rect.bottom - window_rect.top;
		CHAR sz_buffer[256] = {};
		sprintf
		(
			sz_buffer, 
			"%s, Size: %ix%i; Position: %ix%i;",
			g_szMyWindowClass,
			width, height,
			window_rect.left, window_rect.top
		);
		SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_buffer);
	}
		break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case 1002:
		{
			CHAR sz_buffer[256] = {};
			HWND hStatic = GetDlgItem(hwnd, 1000);
			HWND hEdit = GetDlgItem(hwnd, 1001);
			SendMessage(hEdit, WM_GETTEXT, 256, (LPARAM)sz_buffer);
			SendMessage(hStatic, WM_SETTEXT, 0, (LPARAM)sz_buffer);
			SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_buffer);
		}
		break;
		}
	}
		break;
	case WM_DESTROY:PostQuitMessage(0);	   break;
	case WM_CLOSE:	DestroyWindow(hwnd);   break;
	default: return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return 0;
}	