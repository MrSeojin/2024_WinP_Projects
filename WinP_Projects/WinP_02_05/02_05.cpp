#include <windows.h>
#include <winuser.h>
#include <tchar.h>
#include <iostream>
HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Programming 2-5";
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;
	g_hInst = hInstance;
	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&WndClass);
	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 800, 600, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hDC;
	static TCHAR str[10][30];
	static int xCount;
	static int yCount;
	static SIZE size;

	switch (uMsg) {
	case WM_CREATE:
		CreateCaret(hWnd, NULL, 5, 15);
		ShowCaret(hWnd);
		xCount = 0;
		yCount = 0;
		GetCaretBlinkTime();
		break;
	case WM_CHAR:
		hDC = GetDC(hWnd);

		if (wParam == VK_RETURN || xCount == 29) {
			if (yCount == 9)
				yCount = 0;
			else
				yCount++;
			xCount = 0;
		}
		else if (wParam == VK_BACK)
			xCount--;
		else if (wParam == 'q') {
			PostQuitMessage(0);
			break;
		}
		else
			str[yCount][xCount++] = wParam;
		str[yCount][xCount] = '\0';

		InvalidateRect(hWnd, NULL, true);
		ReleaseDC(hWnd, hDC);
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		//		wsprintf(str, TEXT("%d %d %d %d"), nums[0], nums[1], nums[2], nums[3]);
		GetTextExtentPoint32(hDC, str[yCount], lstrlen(str[yCount]), &size);
		for (int i = 0; i <= yCount; ++i)
			TextOut(hDC, 0, (yCount - i) * 20, str[yCount - i], _tcslen(str[yCount - i]));
		SetCaretPos(size.cx, yCount * 20);
		SetCaretBlinkTime(1000);

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		HideCaret(hWnd);
		DestroyCaret();
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
