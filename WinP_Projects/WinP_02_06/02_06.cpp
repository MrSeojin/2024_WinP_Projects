#include <windows.h>
#include <tchar.h>
#include <time.h>
#include <cstdlib>
HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Programming 2-6";
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
	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 815, 640, NULL, (HMENU)NULL, hInstance, NULL);
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
	static RECT rect;
	int x = rand() % 8 + 2;
	int y = rand() % 8 + 2;
	static SIZE size;
	static int Random;

	static HPEN hPen{}, oldPen{};
	static HBRUSH hBrush{}, oldBrush{};

	switch (uMsg) {
	case WM_CREATE:
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);

		static int r;
		static int g;
		static int b;
		for (int j = 0; j < y; ++j) {
			for (int i = 0; i < x; ++i) {

				r = rand() % 255;
				g = rand() % 255;
				b = rand() % 255;
				hPen = CreatePen(PS_SOLID, 3, RGB(r, g, b)); // 새로운 객체 만들기: 펜
				oldPen = (HPEN)SelectObject(hDC, hPen);
				r = rand() % 255;
				g = rand() % 255;
				b = rand() % 255;
				hBrush = CreateSolidBrush(RGB(r, g, b)); // 새로운 객체 만들기: 브러쉬
				oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

				static RECT rect{};
				rect.left = (800 / x) * i;
				rect.top = (600 / y) * j;
				rect.right = (800 / x) * (i + 1);
				rect.bottom = (600 / y) * (j + 1);
				Rectangle(hDC, rect.left, rect.top, rect.right, rect.bottom);
				//FrameRect(hDC, &rect, hBrush);

				SelectObject(hDC, oldPen); // 제자리 돌아가기
				DeleteObject(hPen); // 새로운 객체 삭제
				SelectObject(hDC, oldBrush);
				DeleteObject(hBrush);

				Random = rand() % 6;

				r = rand() % 255;
				g = rand() % 255;
				b = rand() % 255;
				hPen = CreatePen(PS_SOLID, 5, RGB(r, g, b)); // 새로운 객체 만들기: 펜
				oldPen = (HPEN)SelectObject(hDC, hPen);
				r = rand() % 255;
				g = rand() % 255;
				b = rand() % 255;
				hBrush = CreateSolidBrush(RGB(r, g, b)); // 새로운 객체 만들기: 브러쉬
				oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

				switch (Random) {
				case 0:											// x
					MoveToEx(hDC, rect.left, rect.top, NULL);
					LineTo(hDC, rect.right, rect.bottom);
					MoveToEx(hDC, rect.right, rect.top, NULL);
					LineTo(hDC, rect.left, rect.bottom);
					break;
				case 1:											//ㄹ
					MoveToEx(hDC, rect.left + 80 / x, rect.top + 60 / y, NULL);
					LineTo(hDC, rect.right - 80 / x, rect.top + 60 / y);
					LineTo(hDC, rect.right - 80 / x, (rect.top + rect.bottom) / 2);
					LineTo(hDC, rect.left + 80 / x, (rect.top + rect.bottom) / 2);
					LineTo(hDC, rect.left + 80 / x, rect.bottom - 60 / y);
					LineTo(hDC, rect.right - 80 / x, rect.bottom - 60 / y);
					break;
				case 2:											//마름모
					{
						POINT point[8] = { {rect.right, (rect.top + rect.bottom) / 2},{(rect.right + rect.left) / 2, rect.top},{rect.left,(rect.top + rect.bottom) / 2},{(rect.right + rect.left) / 2, rect.bottom} };
						Polygon(hDC, point, 4);
					}
					break;
				case 3:											//위
					{
						POINT point_1[3] = { {(rect.right + rect.left) / 2, rect.top},{rect.left, (rect.top + rect.bottom) / 2},{rect.right, (rect.top + rect.bottom) / 2} };
						Polygon(hDC, point_1, 3);
						POINT point_2[3] = { { (rect.right + rect.left) / 2, (rect.top + rect.bottom) / 2},{rect.left, rect.bottom},{rect.right, rect.bottom} };
						Polygon(hDC, point_2, 3);
					}
					break;
				case 4:											//나비
					{
						POINT point_1[3] = { {(rect.right + rect.left) / 2, (rect.top + rect.bottom) / 2},{rect.left, rect.top},{rect.left, rect.bottom} };
						Polygon(hDC, point_1, 3);
						POINT point_2[3] = { { (rect.right + rect.left) / 2, (rect.top + rect.bottom) / 2},{rect.right, rect.top},{rect.right, rect.bottom} };
						Polygon(hDC, point_2, 3);
					}
					break;
				case 5:											//네모셋
					Rectangle(hDC, rect.left, rect.top, rect.right - (rect.right - rect.left) * 4 / 5, rect.bottom);
					Rectangle(hDC, rect.left + (rect.right - rect.left) * 2 / 5, rect.top, rect.right - (rect.right - rect.left) * 2 / 5, rect.bottom);
					Rectangle(hDC, rect.left + (rect.right - rect.left) * 4 / 5, rect.top, rect.right, rect.bottom);
					break;
				}
				SelectObject(hDC, oldPen); // 제자리 돌아가기
				DeleteObject(hPen); // 새로운 객체 삭제
				SelectObject(hDC, oldBrush);
				DeleteObject(hBrush);

				hPen = {};
				oldPen = {};
				hBrush = {};
				oldBrush = {};

			}
		}
		EndPaint(hWnd, &ps);
		break;
	case WM_CHAR:
		hDC = GetDC(hWnd);
		if (wParam == VK_RETURN)
		{
			srand(time(NULL));
			x = rand() % 8 + 2;
			y = rand() % 8 + 2;

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
