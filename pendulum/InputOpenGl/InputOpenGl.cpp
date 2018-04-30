// InputOpenGl.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "InputOpenGl.h"
#include <time.h> 
#include <GL/glu.h> 
#include <iostream> 
#include "MoveBalans.h"
#include <cstdlib>
#include <ctime>
//Ссылка на поврхность рисование на которой все будет рисоватся
HDC hDC;
//Ссылка на OpenGL через кторую будем передовать пораметор
HGLRC hDLRC;
//Ссылка на окно в котором будем все рисовать
HWND hWnd;
struct {
	const size_t height = 4;
	const size_t width = 5;
}aspectRatio;

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_INPUTOPENGL, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_INPUTOPENGL));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_INPUTOPENGL));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_INPUTOPENGL);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   /* Закоментирую  строку
   HWND hWnd;*/


   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }
   // Весь код инициализации будет находится здесь
   PIXELFORMATDESCRIPTOR pfd = {
	   sizeof(PIXELFORMATDESCRIPTOR),
	   1,
	   PFD_SUPPORT_OPENGL |
	   PFD_DRAW_TO_WINDOW |
	   PFD_DOUBLEBUFFER,
	   PFD_TYPE_RGBA,
	   32,
	   0, 0, 0, 0, 0, 0,
	   0,
	   0,
	   0,
	   0, 0, 0, 0,
	   16,
	   0,
	   0,
	   PFD_MAIN_PLANE,
	   0,
	   0, 0, 0,
   };

   //Получаем ссылку где будем рисовать
   hDC = GetDC(hWnd);
   //Задаем пораметры точек
   int pixelFormat = ChoosePixelFormat(hDC, &pfd);
   //Задаем пораметры точек
   SetPixelFormat(hDC, pixelFormat, &pfd);
   // Сообщаем OpenGL где будем рисовать
   hDLRC = wglCreateContext(hDC);
   //создаем концекст рисования;
   wglMakeCurrent(hDC, hDLRC);
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}
//-----------------------------------------------------------------------

void display(MoveBalans& mBalans)
{
	
	mBalans.calculationAngleBag();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//меняем буфер (двойная буферизация)
	glColor3f(1.0, 0.0, 0.0); // цвет наших линий, в данном слуае - красный 
	glBegin(GL_LINES); // начинаем рисовать и указываем, что это линии 
	glVertex2f(mBalans.getCouplPOS_X()/ aspectRatio.width * aspectRatio.height, mBalans.getCouplPOS_Y());
	glVertex2f(mBalans.getSubjectPOS_X() / aspectRatio.width * aspectRatio.height, mBalans.getSubjectPOS_Y());
	glVertex2f(mBalans.getCouplPOS_X() / aspectRatio.width * aspectRatio.height, mBalans.getCouplPOS_Y());
	glVertex2f(mBalans.getRadius() / aspectRatio.width * aspectRatio.height, mBalans.getCouplPOS_Y());
	glVertex2f(mBalans.getCouplPOS_X() / aspectRatio.width * aspectRatio.height, mBalans.getCouplPOS_Y());
	glVertex2f(mBalans.getCouplPOS_X() / aspectRatio.width * aspectRatio.height, mBalans.getRadius());
	glEnd();
	glFlush();
	
}
// основная функция

//----------------------------------------------------------------------------

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static MoveBalans mBalans(85, 0.65, 0, 0, 1, 1);
	
    switch (message)
    {
	
	case WM_CREATE:
		mBalans.calcFirstCoordinat();
		mBalans.calculationAngleBag();
		srand(time(NULL));
		SetTimer(hWnd, 1, 10, NULL);
    case WM_COMMAND:
        {
	
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
	case WM_TIMER:
		
		SendMessage(hWnd, WM_PAINT, 0, 0);
		
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
			display(mBalans);
            // TODO: Add any drawing code that uses hdc here...
			//Устанавливает очистку черным цветом
			//	glClearColor(1, 0, 1, 1);
			//Очистить буфер точек и буфер глубины
			//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			//меняем буфер (двойная буферизация)
				
			SwapBuffers(hDC);
            EndPaint(hWnd, &ps);
			
        }
        break;
    case WM_DESTROY:
		KillTimer(hWnd, 1);
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
