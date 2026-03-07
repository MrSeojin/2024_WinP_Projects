#include <windows.h>
#include <winuser.h>
#include <tchar.h>
#include <time.h>
HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Programming 2_2";
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
	COLORREF text_color;
	RECT rect;
	TCHAR str[26];

	switch (uMsg) {
	case WM_CREATE:
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		if (true) {
			int px = 0, py = 0;
			srand(time(NULL));
			int n = rand() % 9 + 2, m = rand() % 9 + 2;
			for (int i = 0; i < m; ++i) {
				for (int j = 0; j < n; ++j) {

					if ((i + j + 1) % 2) {
						for (int a = 0; a < 26; ++a)
							str[a] = a + 65;
					}
					else {
						for (int a = 0; a < 26; ++a)
							str[a] = a + 97;
					}
					rect.left = (px + 1);
					rect.top = (py + 1);
					rect.right = (px + (800 / n));
					rect.bottom = (py + (600 / n));
					//HBRUSH hbrush = CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256));

					SetTextColor(hDC, RGB(rand() % 256, rand() % 256, rand() % 256));
					SetBkColor(hDC, RGB(rand() % 256, rand() % 256, rand() % 256));
					//fillRect(hDC, &rect, hbrush);
					DrawText(hDC, str, _tcslen(str), &rect, DT_WORDBREAK | DT_EDITCONTROL | DT_CENTER);

					px += (800 / n);
				}
				px = 0;
				py += (600 / m);
			}
		}
		//deleteObject(hbrush);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
