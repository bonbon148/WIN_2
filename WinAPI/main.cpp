#include<Windows.h>

INT WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	MessageBox
	(	
		NULL,   //Родительское окно.
		"Hello WinAPI!\nРфзрабокта настольных приложений для Windows.", //Сообщение выводимое пользователю.
		"Hello", //Заголовок окна.
		//Флаги, которые определяют значок, выводимый в окне, набор кнопок и некоторые доп.параметры.
		MB_YESNOCANCEL | MB_HELP | MB_ICONERROR | MB_DEFBUTTON3 | MB_SYSTEMMODAL
	);
}