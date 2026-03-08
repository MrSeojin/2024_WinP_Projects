#include <windows.h>
#include <winuser.h>
#include <tchar.h>
#include <iostream>
HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Programming 2-7";
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
	static TCHAR str[10][81];
	static int xCount;
	static int yCount;
	static SIZE size;
	static int Big = 0, In = 0;
	static int cheak = 0;

	switch (uMsg) {
	case WM_CREATE:
		CreateCaret(hWnd, NULL, 5, 15);
		ShowCaret(hWnd);
		xCount = 0;
		yCount = 0;
		break;
	case WM_KEYDOWN:
		hDC = GetDC(hWnd);
		if (wParam == VK_LEFT) {								// 왼방향
			if (xCount == 0) {
				if (yCount == 0)
					yCount = 9;
				else
					yCount--;
				if (_tcslen(str[yCount]) > 29)
					xCount = 29;
				else
					xCount = _tcslen(str[yCount]);
			}
			else
				xCount--;
		}
		else if (wParam == VK_UP) {									// 위방향
			if (yCount == 0)
				yCount = 9;
			else
				yCount--;
			if (xCount >= _tcslen(str[yCount]))
				xCount = _tcslen(str[yCount]);
		}
		else if (wParam == VK_RIGHT) {								// 우방향
			if (xCount > 29 || xCount >= _tcslen(str[yCount])) {
				if (yCount == 9)
					yCount = 0;
				else
					yCount++;
				xCount = 0;
			}
			else
				xCount++;
		}
		else if (wParam == VK_DOWN) {								// 아래방향
			if (yCount == 9)
				yCount = 0;
			else
				yCount++;
			if (xCount >= _tcslen(str[yCount]))
				xCount = _tcslen(str[yCount]);
		}
		else if (wParam == VK_HOME) 								//HOME
			xCount = 0;
		else if (wParam == VK_END) {								// END
			cheak = 1;
			xCount = _tcslen(str[yCount]);
		}
		else if (wParam == VK_DELETE) {								// DEL
			int start = 0, num = 0;
			for (int i = xCount; i >= 0; --i) {
				if (str[yCount][i] == ' ') {
					start = i;
					break;
				}
				else if (i == 0)
					start = 0;
				else;
			}
			for (int i = start + 1; i < _tcslen(str[yCount]); ++i) {
				++num;
				if (str[yCount][i] == ' ')
					break;
				else;
			}
			for (int i = start + 1; i < _tcslen(str[yCount]) + num; ++i) {
				if (i >= _tcslen(str[yCount]) - num)
					str[yCount][i] = '\0';
				else
					str[yCount][i] = str[yCount][i + num];
			}
			xCount = _tcslen(str[yCount]);
		}
		else if (wParam == VK_F1) {									// F1
			if (Big == 0)
				Big = 1;
			else
				Big = 0;
		}
		else if (wParam == VK_INSERT) {								// INSERT
			if (In == 0)
				In = 1;
			else
				In = 0;
		}

		InvalidateRect(hWnd, NULL, true);
		ReleaseDC(hWnd, hDC);
		break;
	case WM_CHAR:
		hDC = GetDC(hWnd);

		if (wParam == VK_RETURN || (cheak == 0 && _tcslen(str[yCount]) == 30) || (cheak == 1 && _tcslen(str[yCount]) == 80)) {		// ENTER
			if (yCount == 9)
				yCount = 0;
			else
				yCount++;
			xCount = 0;
			if (cheak == 1)
				cheak = 0;
		}
		else if (wParam == VK_BACK)									// BACKSPACE
			str[yCount][--xCount] = '\0';
		else if (wParam == VK_ESCAPE) {								// ESC
			for (int j = 0; j < 10; ++j) {
				for (int i = 0; i < _tcslen(str[j]); ++i)
					str[j][i] = '\0';
			}
			xCount = 0;
			yCount = 0;
		}
		else if (wParam == VK_TAB) {								// TAB
			for (int i = 0; i < 5; ++i)
				str[yCount][xCount++] = ' ';
		}
		else if (wParam == 'q') {
			PostQuitMessage(0);
			break;
		}
		else {
			static TCHAR alp;
			if (Big == 1)
				alp = toupper(wParam);
			else
				alp = tolower(wParam);

			if (In == 1) {
				str[yCount][_tcslen(str[yCount]) + 1] = '\0';
				for (int i = _tcslen(str[yCount]); i > xCount; --i)
					str[yCount][i] = str[yCount][i - 1];
				str[yCount][xCount++] = alp;
			}
			else
				str[yCount][xCount++] = alp;
		}
		if (xCount >= _tcslen(str[yCount]))
			str[yCount][xCount] = '\0';

		InvalidateRect(hWnd, NULL, true);
		ReleaseDC(hWnd, hDC);
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		//		wsprintf(str, TEXT("%d %d %d %d"), nums[0], nums[1], nums[2], nums[3]);
		GetTextExtentPoint32(hDC, str[yCount], xCount, &size);
		for (int i = 0; i < 10; ++i)
			TextOut(hDC, 0, i * 20, str[i], _tcslen(str[i]));
		SetCaretPos(size.cx, yCount * 20);

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
