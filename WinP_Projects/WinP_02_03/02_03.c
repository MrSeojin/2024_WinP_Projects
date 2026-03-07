#include <windows.h>
HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Programming 2_3";
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
	WndClass.hCursor = LoadCursor(NULL, IDC_HAND);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&WndClass);
	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW | WS_HSCROLL | WS_VSCROLL, 0, 0, 800, 600, NULL, (HMENU)NULL, hInstance, NULL);
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
	int x = rand() % 601;
	int y = rand() % 401;
	char n = rand() % 10;
	int count = rand() % 16 + 5;
	TCHAR arr[400];

	struct tagSize {
		LONG cx;
		LONG cy;
	} SIZE;

	switch (uMsg) {
	case WM_CREATE:
		srand(time(NULL));
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		for (int i = 0; i < 400; ++i)
			arr[i] = ' ';

		for (int a = 0; a < count * count; ++a)
			arr[a] = '0' + n;
		GetTextExtentPoint32(hDC, arr, count, &SIZE);
		rect.left = (x);
		rect.top = (y);
		rect.right = (x + SIZE.cx);
		rect.bottom = (y + count * SIZE.cy);
		SetTextColor(hDC, RGB(rand() % 256, rand() % 256, rand() % 256));
		SetBkColor(hDC, RGB(rand() % 256, rand() % 256, rand() % 256));
		DrawText(hDC, arr, count * count, &rect, DT_WORDBREAK | DT_EDITCONTROL | DT_CENTER);

		EndPaint(hWnd, &ps);
		break;
	case WM_CHAR:
		hDC = GetDC(hWnd);
		if (wParam == VK_RETURN)
		{
			int x = rand() % 601;
			int y = rand() % 401;
			int n = rand() % 10;
			int count = rand() % 16 + 5;
		}
		else if (wParam == 'q') {
			PostQuitMessage(0);
			break;
		}
		else;
		InvalidateRect(hWnd, NULL, TRUE);
		ReleaseDC(hWnd, hDC);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}