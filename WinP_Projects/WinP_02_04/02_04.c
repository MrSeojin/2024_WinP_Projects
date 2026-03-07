#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <winuser.h>
#include <tchar.h>
HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Programming 2-4";
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
	int x = 10, y = 10, n = 10, m = 10;
	static TCHAR str[4][5];
	static int count = 0;
	static SIZE size;
	static int cheak = 0;

	switch (uMsg) {
	case WM_CREATE:
		CreateCaret(hWnd, NULL, 5, 15);
		ShowCaret(hWnd);
		count = 0;
		break;
	case WM_CHAR:
		hDC = GetDC(hWnd);

		if (wParam == VK_RETURN) {
		}
		else if (wParam == VK_BACK) {
			if (str[cheak - 1][count - 1] == ' ') {
				cheak--;
			}
			count--;
		}
		else if (wParam == VK_SPACE && cheak < 4) {
			str[cheak][count++] = wParam;
			str[cheak][count] = '\0';
			cheak++;
			count = 0;
		}
		else if (wParam == 'q') {
			PostQuitMessage(0);
			break;
		}
		else if (cheak < 4) {
			str[cheak][count++] = wParam;
			str[cheak][count] = '\0';
		}
		InvalidateRect(hWnd, NULL, TRUE);
		ReleaseDC(hWnd, hDC);
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		//		wsprintf(str, TEXT("%d %d %d %d"), nums[0], nums[1], nums[2], nums[3]);
		//		if (cheak < 4) {

		//	}
		if (cheak == 4) {
			x = _ttoi(str[0]);
			y = _ttoi(str[1]);
			n = _ttoi(str[2]);
			m = _ttoi(str[3]);
			//			static TCHAR nums[50];
			//			wsprintf(nums, TEXT("%d, %d, %d, %d"), x, y, n, m);
			//			TextOut(hDC, 0, 500, nums, _tcslen(nums));
			static TCHAR arr[19][15];
			for (int i = 0; i < m; ++i) {
				wsprintf(arr[i], TEXT("%d  * %d = %d"), n, i + 1, n * (i + 1));
				TextOut(hDC, x, y + (i * 20), arr[i], _tcslen(arr[i]));
			}
			cheak = 0;
		}
		else {
			GetTextExtentPoint32(hDC, str[cheak], lstrlen(str[cheak]), &size);
			for (int i = 0; i <= cheak; ++i) {
				TextOut(hDC, 0, i * 20, str[i], _tcslen(str[i]));
			}
			SetCaretPos(size.cx, cheak * 20);

		}
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
