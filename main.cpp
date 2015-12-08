#include <Windows.h>
#include <cstdio>

//Начало-Прототипы
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam); // Главная функция
int createWindowMP(HINSTANCE hInstacne);
void upWindow(int &nCmdShow);
void WindowFormMgmt(HINSTANCE hInstacne);
void OpenAndCreate(HWND hwnd, WPARAM wParam);

void ReadORWrite(int cheak, char *fileBuffer, FILE *fileOpen);
void Check_ReadORWrite();
//---
LRESULT CALLBACK CBTProc(INT nCode, WPARAM wParam, LPARAM lParam);
int CBTMessageBox(HWND hwnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType);
//Конец--Прототипы----

//Начало-Структуры
struct HWND_MAIN { HWND hMainWnd; HWND hStat; HWND hButton; struct edit { HWND hEdit1; HWND hEdit2; HWND hEdit3; }EDIT; }hWND; // Структуры Хендлов
struct SizeWindow { float Width; float Height; }MainWindow; // Тут будит размер окна, кнопок и тд
struct ENUM { enum button { OpenOneButton = 101 }; }cllB; // Struct the enum!
//Конец--Структуры----

//Начало-ГлобалПеременные
//Конец--ГлобалПеременные----

//Начало-Макросы
//Конец--Макросы----

int WinMain(HINSTANCE hInstacne, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	createWindowMP(hInstacne); // Filling struct window, create window, call global functions
	//---------
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)upWindow, &nCmdShow, 0, 0); //Поток для обновление окна
	//---------

	MSG msg; //Структура сообщения
	while (GetMessage(&msg, NULL, NULL, NULL)){ /*TranslateMessage(&msg); */ DispatchMessage(&msg); } return msg.wParam;
}

void upWindow(int &nCmdShow)
{
	ShowWindow(hWND.hMainWnd, nCmdShow); //Показываем окно
	while (true) // Беск цикл для обнов окна
	{
		UpdateWindow(hWND.hMainWnd); Sleep(10); //Обновляем и спим 0.10 сек
	}
}

int createWindowMP(HINSTANCE hInstacne)
{
	const TCHAR const *NameClass = "My Classs";
	//-------------------------------------------------------------------- Заполение структуры
	WNDCLASSEX wc; // Создание объекта
	wc.cbSize = sizeof(wc); //Размер структуры
	wc.style = CS_HREDRAW | CS_VREDRAW; // Стиль
	wc.lpfnWndProc = WndProc; // Даем ей адресс функции
	wc.lpszMenuName = NULL; // Меню
	wc.lpszClassName = NameClass; // Имя класса
	wc.cbWndExtra = NULL; //
	wc.cbClsExtra = NULL; //
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO); // Загружаем иконку
	wc.hIconSm = LoadIcon(NULL, IDI_WINLOGO); // Загружаем иконку
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); // Загружаем Курсор
	wc.hbrBackground = (HBRUSH)(3); //Цвет фона окна
	wc.hInstance = hInstacne; //дескриптор нашей проги
	if (!RegisterClassEx(&wc)) { MessageBox(NULL, "No Register Class!", "ERROR", MB_OK); return NULL; } // А заполнена структура?
	//--------------------------------------------------------------------

	MainWindow.Width = 800; //X
	MainWindow.Height = 600;//Y

	hWND.hMainWnd = CreateWindow(NameClass, "My Training", WS_OVERLAPPEDWINDOW, 100, 100, MainWindow.Width, MainWindow.Height, NULL, NULL, hInstacne, NULL); // Создание Окна

	WindowFormMgmt(hInstacne); //Кнопочки и тд

	Check_ReadORWrite(); // Загружаем данные!
}

void WindowFormMgmt(HINSTANCE hInstacne)
{
	const TCHAR const *NameStatic = "static";
	const unsigned short const StaticConstVar = 10000;
	//Begin-Static-
	hWND.hStat = CreateWindow(NameStatic, " Тренировочный день", WS_CHILD | WS_VISIBLE, 6, 8, 149, 20, hWND.hMainWnd, 0, hInstacne, NULL);
	hWND.hStat = CreateWindow(NameStatic, " Упражнение", WS_CHILD | WS_VISIBLE, 195, 8, 90, 20, hWND.hMainWnd, 0, hInstacne, NULL);
	hWND.hStat = CreateWindow(NameStatic, " Кол-во подходов", WS_CHILD | WS_VISIBLE, 345, 8, 125, 20, hWND.hMainWnd, 0, hInstacne, NULL);
	hWND.hStat = CreateWindow(NameStatic, " Выполнено? ", WS_CHILD | WS_VISIBLE, 500, 8, 90, 20, hWND.hMainWnd, 0, hInstacne, NULL);
	hWND.hStat = CreateWindow(NameStatic, "", WS_CHILD | WS_VISIBLE, 160, 0, 5, StaticConstVar, hWND.hMainWnd, 0, hInstacne, NULL);
	hWND.hStat = CreateWindow(NameStatic, "", WS_CHILD | WS_VISIBLE, 0, 35, StaticConstVar, 5, hWND.hMainWnd, 0, hInstacne, NULL);
	hWND.hStat = CreateWindow(NameStatic, "", WS_CHILD | WS_VISIBLE, 325, 0, 5, StaticConstVar, hWND.hMainWnd, 0, hInstacne, NULL);
	hWND.hStat = CreateWindow(NameStatic, "", WS_CHILD | WS_VISIBLE, 490, 0, 5, StaticConstVar, hWND.hMainWnd, 0, hInstacne, NULL);
	hWND.hStat = CreateWindow(NameStatic, "", WS_CHILD | WS_VISIBLE, 600, 0, 5, StaticConstVar, hWND.hMainWnd, 0, hInstacne, NULL);
	//End---Static-

	//Begin-EDIT-
	hWND.hButton = CreateWindow("button", "Обновить", WS_CHILD | WS_VISIBLE | BS_DEFPUSHBUTTON, 610, 3, 100, 30, hWND.hMainWnd, (HMENU)cllB.OpenOneButton, hInstacne, NULL);
	/* 1 */hWND.EDIT.hEdit1 = CreateWindow("Edit", "", WS_CHILD |  WS_VISIBLE
		| WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL, 5, 45, 150, 520,   hWND.hMainWnd, NULL, hInstacne, NULL);

	/* 2 */hWND.EDIT.hEdit2 = CreateWindow("Edit", "", WS_CHILD | WS_VISIBLE 
		| WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL, 170, 45, 150, 520, hWND.hMainWnd, NULL, hInstacne, NULL);

	/* 3 */hWND.EDIT.hEdit3 = CreateWindow("Edit", "", WS_CHILD | WS_VISIBLE
		| WS_BORDER | ES_MULTILINE | ES_AUTOVSCROLL, 335, 45, 150, 520, hWND.hMainWnd, NULL, hInstacne, NULL);
	//End---EDIT-
}

int CBTMessageBox(HWND hwnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType)
{
	SetWindowsHookEx(WH_CBT, &CBTProc, 0, GetCurrentThreadId());
	return ::MessageBox(hwnd, lpText, lpCaption, uType);
}
HHOOK hhk;
LRESULT CALLBACK CBTProc(INT nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode == HCBT_ACTIVATE)
	{
		HWND hChildWnd = (HWND)wParam;

		if (GetDlgItem(hChildWnd, IDOK)) SetDlgItemText(hChildWnd, IDOK, "Создать");
		UnhookWindowsHookEx(hhk);
	}
	else { CallNextHookEx(hhk, nCode, wParam, lParam); }
	return 0;
}

void ReadORWrite(int cheak, char *fileBuffer, FILE *fileOpen)
{
	fgets(fileBuffer, sizeof(fileBuffer), fileOpen);
	fclose(fileOpen);
	switch (cheak)
	{
	case 1:
		SetWindowText(hWND.EDIT.hEdit1, fileBuffer); break;
	case 2:
		SetWindowText(hWND.EDIT.hEdit2, fileBuffer); break;
	case 3:
		SetWindowText(hWND.EDIT.hEdit3, fileBuffer); break;
	}
}

void Check_ReadORWrite()
{
	bool on = true;
//--------------------------------------------------------------------------------------------------
	if (on)
	{
		FILE* fileTrDay;
		char fileTrDayBuffer[4096];
		if ((fileTrDay = fopen("fileTrDay.txt", "r")) == NULL)
		{
			if (CBTMessageBox(NULL, "Файл fileTrDay.txt небыл создан!", "ERROR", IDOK) == IDCANCEL) { ExitProcess(0); }
			if ((fileTrDay = fopen("fileTrDay.txt", "w")) == NULL) { MessageBox(NULL, "EROOR", "EROOR", NULL); ExitProcess(0); 	}
		}
		else
		{
			ReadORWrite(1, fileTrDayBuffer, fileTrDay);
		}
//--------------------------------------------------------------------------------------------------
		if (on)
		{
			FILE* ptrfileExercise;
			char fileExerciseBuffer[4096];
			if ((ptrfileExercise = fopen("fileExercise.txt", "r")) == NULL) 
			{ 
				if (CBTMessageBox(NULL, "Файл fileExercise.txt небыл создан!", "ERROR", IDOK) == IDCANCEL) { ExitProcess(0); }
				if ((fileTrDay = fopen("fileExercise.txt", "w")) == NULL) { MessageBox(NULL, "EROOR", "EROOR", NULL); ExitProcess(0); }
			}
			else
			{
				ReadORWrite(2, fileExerciseBuffer, ptrfileExercise);
			}
//--------------------------------------------------------------------------------------------------
			if (on)
			{
				FILE* ptrfileCountApp;
				char fileCountAppBuffer[4096];
				if((ptrfileCountApp = fopen("fileCountAppBuffer.txt", "r")) == NULL) 
				{ 
					if (CBTMessageBox(NULL, "Файл fileCountAppBuffer.txt небыл создан!", "ERROR", IDOK) == IDCANCEL) { ExitProcess(0); }
					if ((fileTrDay = fopen("fileCountAppBuffer.txt", "w")) == NULL) { MessageBox(NULL, "EROOR", "EROOR", NULL); ExitProcess(0); }
				}
				else
				{
					ReadORWrite(3, fileCountAppBuffer, ptrfileCountApp);
				}
			}
//--------------------------------------------------------------------------------------------------
		}
	}
}

///////////
// Функции(я) управление
void OpenAndCreate(HWND hwnd, WPARAM wParam)
{
	if (LOWORD(wParam) == cllB.OpenOneButton) Check_ReadORWrite();

	//else if (LOWORD(wParam) == OpenTwoButton)
		

	//else if (LOWORD(wParam) == OpenThireButton)
	//	LOLMESSAGE();

	///////////////////////////////////////////////////////////
	//else if (LOWORD(wParam) == Close) ExitProcess(0);///Close//
													 ///////////////////////////////////////////////////////////
}
///////////////////////

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_COMMAND:
		OpenAndCreate(hWnd, wParam);
		break;
	case WM_DESTROY:
		PostQuitMessage(NULL);
		break;

	/* Этой процедурой можно таскать форму за любое место */
	case WM_NCHITTEST:
	{
		LRESULT currentArea = DefWindowProc(hWnd, uMsg, wParam, lParam);
		if (HTCLIENT == currentArea)
			return HTCAPTION;
		return currentArea;
	}
	/* Этой процедурой можно таскать форму за любое место */

	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
}
