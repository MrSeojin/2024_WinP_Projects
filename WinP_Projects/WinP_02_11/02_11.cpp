#include <windows.h>
#include <winuser.h>
#include <tchar.h>
#include <time.h>
#include <iostream>
#include <cstdlib>
HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Programming 2-11";
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

	struct Library {
		int Shape;
		RECT rect;
		int Thick;
		COLORREF PenColor, BrushColor;
	};

	static Library pictures[3];

	static TCHAR str[6][5];
	static int count = 0, cheak = 0;
	static int PicCount = 0, Max = 0;
	static SIZE size;
	static int All, prior, next;
	static int NowDraw = 0, error = 0;

	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;
	static COLORREF PenColor, BrushColor;

	switch (uMsg) {
	case WM_CREATE:
		CreateCaret(hWnd, NULL, 5, 15);
		ShowCaret(hWnd);
		count = 0;
		srand(time(NULL));
		PenColor = RGB(rand() % 155, rand() % 255, rand() % 255);
		BrushColor = RGB(rand() % 155, rand() % 255, rand() % 255);
		break;
	case WM_CHAR:
		hDC = GetDC(hWnd);

		if (wParam == VK_BACK && Max == 0) {
			if (count == 0) {
				if (cheak == 0);
				else {
					cheak--;
					count = _tcslen(str[cheak]);
					str[cheak][--count] = '\0';
				}
			}
			else
				str[cheak][--count] = '\0';
		}
		else if ((wParam == VK_SPACE || count == 3) && Max == 0) {
			str[cheak][count++] = ' ';
			str[cheak][count] = '\0';
			cheak++;
			count = 0;

			if (cheak == 6) {
				pictures[PicCount].Shape = _ttoi(str[0]);
				pictures[PicCount].rect.left = _ttoi(str[1]);
				pictures[PicCount].rect.top = _ttoi(str[2]);
				pictures[PicCount].rect.right = _ttoi(str[3]);
				pictures[PicCount].rect.bottom = _ttoi(str[4]);
				pictures[PicCount].Thick = _ttoi(str[5]);

				pictures[PicCount].PenColor = RGB(rand() % 155, rand() % 255, rand() % 255);
				pictures[PicCount].BrushColor = RGB(rand() % 255, rand() % 255, rand() % 255);

				for (int j = 0; j < 6; ++j) {
					for (int i = 0; i < 5; ++i)
						str[j][i] = '\0';
				}
			}
		}
		else if (wParam == 'q' || wParam == 'Q') {
			PostQuitMessage(0);
			break;
		}
		else if (Max == 1) {
			if (wParam == '+') {
				if (pictures[NowDraw].Thick == 10)
					pictures[NowDraw].Thick = 1;
				else
					pictures[NowDraw].Thick += 1;
			}
			else if (wParam == '-') {
				if (pictures[NowDraw].Thick == 1)
					pictures[NowDraw].Thick = 10;
				else
					pictures[NowDraw].Thick -= 1;
			}
			else if (wParam == '1')
				pictures[NowDraw].PenColor = RGB(rand() % 255, rand() % 255, rand() % 255);
			else if (wParam == '2')
				pictures[NowDraw].BrushColor = RGB(rand() % 255, rand() % 255, rand() % 255);
			else if (wParam == 'p') {
				if (NowDraw == 0);
				else
					NowDraw -= 1;
			}
			else if (wParam == 'n') {
				if (NowDraw == 2);
				else
					NowDraw += 1;
			}
			else if (wParam == 'a') {
				if (All == 0) {
					All = 1;
				}
				else
					All = 0;
			}
		}
		else if (wParam == '0' || wParam == '1' || wParam == '2' || wParam == '3' || wParam == '4' || wParam == '5' || wParam == '6' || wParam == '7' || wParam == '8' || wParam == '9') {
			str[cheak][count++] = wParam;
			str[cheak][count] = '\0';
		}
		else {
			error = 1;
		}

		InvalidateRect(hWnd, NULL, true);
		ReleaseDC(hWnd, hDC);
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);

		if (cheak == 6 || Max == 1) {
			if (All == 1) {
				for (int i = 0; i <= PicCount; ++i) {
					hPen = CreatePen(PS_SOLID, pictures[i].Thick, pictures[i].PenColor); // 새로운 객체 만들기: 펜
					oldPen = (HPEN)SelectObject(hDC, hPen);
					hBrush = CreateSolidBrush(pictures[i].BrushColor); // 새로운 객체 만들기: 브러쉬
					oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
					if (pictures[i].Shape == 1) {
						SelectObject(hDC, oldBrush);
						DeleteObject(hBrush);
						hBrush = CreateSolidBrush(PenColor); // 새로운 객체 만들기: 브러쉬
						oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
						if (pictures[i].Thick == 1)
							SetPixel(hDC, (pictures[i].rect.left + pictures[i].rect.right) / 2, (pictures[i].rect.top + pictures[i].rect.bottom) / 2, PenColor);
						else
							Ellipse(hDC, pictures[i].rect.left, pictures[i].rect.top, pictures[i].rect.right + pictures[i].Thick, pictures[i].rect.bottom + pictures[i].Thick);
					}
					else if (pictures[i].Shape == 2) {
						MoveToEx(hDC, pictures[i].rect.left, pictures[i].rect.top, NULL);
						LineTo(hDC, pictures[i].rect.right, pictures[i].rect.bottom);
					}
					else if (pictures[i].Shape == 3) {
						POINT Triangle[3] = {
						{ (pictures[i].rect.left + pictures[i].rect.right) / 2, pictures[i].rect.top },
						{pictures[i].rect.left, pictures[i].rect.bottom},
						{pictures[i].rect.right, pictures[i].rect.bottom}
						};
						Polygon(hDC, Triangle, 3);
					}
					else if (pictures[i].Shape == 4)
						Rectangle(hDC, pictures[i].rect.left, pictures[i].rect.top, pictures[i].rect.right, pictures[i].rect.bottom);
					else if (pictures[i].Shape == 5) {
						POINT Pentagon[5] = {
						{(pictures[i].rect.left + pictures[i].rect.right) / 2, pictures[i].rect.top},
						{pictures[i].rect.left, (pictures[i].rect.top + pictures[i].rect.bottom) / 2},
						{pictures[i].rect.left + (pictures[i].rect.right - pictures[i].rect.left) / 6, pictures[i].rect.bottom},
						{pictures[i].rect.right - (pictures[i].rect.right - pictures[i].rect.left) / 6, pictures[i].rect.bottom},
						{pictures[i].rect.right,(pictures[i].rect.top + pictures[i].rect.bottom) / 2}
						};
						Polygon(hDC, Pentagon, 5);
					}
					else if (pictures[i].Shape == 6)
						Ellipse(hDC, pictures[i].rect.left, pictures[i].rect.top, pictures[i].rect.right, pictures[i].rect.bottom);
					SelectObject(hDC, oldPen);
					DeleteObject(hPen);
					SelectObject(hDC, oldBrush);
					DeleteObject(hBrush);
				}
			}
			else if (prior == 1) {
				if (NowDraw == 0);
				else
					NowDraw -= 1;
				{
					hPen = CreatePen(PS_SOLID, pictures[NowDraw].Thick, pictures[NowDraw].PenColor); // 새로운 객체 만들기: 펜
					oldPen = (HPEN)SelectObject(hDC, hPen);
					hBrush = CreateSolidBrush(pictures[NowDraw].BrushColor); // 새로운 객체 만들기: 브러쉬
					oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

					{
						if (pictures[NowDraw].Shape == 1) {
							SelectObject(hDC, oldBrush);
							DeleteObject(hBrush);
							hBrush = CreateSolidBrush(PenColor); // 새로운 객체 만들기: 브러쉬
							oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
							if (pictures[NowDraw].Thick == 1)
								SetPixel(hDC, (pictures[NowDraw].rect.left + pictures[NowDraw].rect.right) / 2, (pictures[NowDraw].rect.top + pictures[NowDraw].rect.bottom) / 2, PenColor);
							else
								Ellipse(hDC, pictures[NowDraw].rect.left, pictures[NowDraw].rect.top, pictures[NowDraw].rect.right + pictures[NowDraw].Thick, pictures[NowDraw].rect.bottom + pictures[NowDraw].Thick);
						}
						else if (pictures[NowDraw].Shape == 2) {
							MoveToEx(hDC, pictures[NowDraw].rect.left, pictures[NowDraw].rect.top, NULL);
							LineTo(hDC, pictures[NowDraw].rect.right, pictures[NowDraw].rect.bottom);
						}
						else if (pictures[NowDraw].Shape == 3) {
							POINT Triangle[3] = {
							{ (pictures[NowDraw].rect.left + pictures[NowDraw].rect.right) / 2, pictures[NowDraw].rect.top },
							{pictures[NowDraw].rect.left, pictures[NowDraw].rect.bottom},
							{pictures[NowDraw].rect.right, pictures[NowDraw].rect.bottom}
							};
							Polygon(hDC, Triangle, 3);
						}
						else if (pictures[NowDraw].Shape == 4)
							Rectangle(hDC, pictures[NowDraw].rect.left, pictures[NowDraw].rect.top, pictures[NowDraw].rect.right, pictures[NowDraw].rect.bottom);
						else if (pictures[NowDraw].Shape == 5) {
							POINT Pentagon[5] = {
							{(pictures[NowDraw].rect.left + pictures[NowDraw].rect.right) / 2, pictures[NowDraw].rect.top},
							{pictures[NowDraw].rect.left, (pictures[NowDraw].rect.top + pictures[NowDraw].rect.bottom) / 2},
							{pictures[NowDraw].rect.left + (pictures[NowDraw].rect.right - pictures[NowDraw].rect.left) / 6, pictures[NowDraw].rect.bottom},
							{pictures[NowDraw].rect.right - (pictures[NowDraw].rect.right - pictures[NowDraw].rect.left) / 6, pictures[NowDraw].rect.bottom},
							{pictures[NowDraw].rect.right,(pictures[NowDraw].rect.top + pictures[NowDraw].rect.bottom) / 2}
							};
							Polygon(hDC, Pentagon, 5);
						}
						else if (pictures[NowDraw].Shape == 6)
							Ellipse(hDC, pictures[NowDraw].rect.left, pictures[NowDraw].rect.top, pictures[NowDraw].rect.right, pictures[NowDraw].rect.bottom);
					}
					SelectObject(hDC, oldPen);
					DeleteObject(hPen);
					SelectObject(hDC, oldBrush);
					DeleteObject(hBrush);

				}
			}
			else if (next == 1) {
				{
					hPen = CreatePen(PS_SOLID, pictures[NowDraw].Thick, pictures[NowDraw].PenColor); // 새로운 객체 만들기: 펜
					oldPen = (HPEN)SelectObject(hDC, hPen);
					hBrush = CreateSolidBrush(pictures[NowDraw].BrushColor); // 새로운 객체 만들기: 브러쉬
					oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

					{
						if (pictures[NowDraw].Shape == 1) {
							SelectObject(hDC, oldBrush);
							DeleteObject(hBrush);
							hBrush = CreateSolidBrush(PenColor); // 새로운 객체 만들기: 브러쉬
							oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
							if (pictures[NowDraw].Thick == 1)
								SetPixel(hDC, (pictures[NowDraw].rect.left + pictures[NowDraw].rect.right) / 2, (pictures[NowDraw].rect.top + pictures[NowDraw].rect.bottom) / 2, PenColor);
							else
								Ellipse(hDC, pictures[NowDraw].rect.left, pictures[NowDraw].rect.top, pictures[NowDraw].rect.right + pictures[NowDraw].Thick, pictures[NowDraw].rect.bottom + pictures[NowDraw].Thick);
						}
						else if (pictures[NowDraw].Shape == 2) {
							MoveToEx(hDC, pictures[NowDraw].rect.left, pictures[NowDraw].rect.top, NULL);
							LineTo(hDC, pictures[NowDraw].rect.right, pictures[NowDraw].rect.bottom);
						}
						else if (pictures[NowDraw].Shape == 3) {
							POINT Triangle[3] = {
							{ (pictures[NowDraw].rect.left + pictures[NowDraw].rect.right) / 2, pictures[NowDraw].rect.top },
							{pictures[NowDraw].rect.left, pictures[NowDraw].rect.bottom},
							{pictures[NowDraw].rect.right, pictures[NowDraw].rect.bottom}
							};
							Polygon(hDC, Triangle, 3);
						}
						else if (pictures[NowDraw].Shape == 4)
							Rectangle(hDC, pictures[NowDraw].rect.left, pictures[NowDraw].rect.top, pictures[NowDraw].rect.right, pictures[NowDraw].rect.bottom);
						else if (pictures[NowDraw].Shape == 5) {
							POINT Pentagon[5] = {
							{(pictures[NowDraw].rect.left + pictures[NowDraw].rect.right) / 2, pictures[NowDraw].rect.top},
							{pictures[NowDraw].rect.left, (pictures[NowDraw].rect.top + pictures[NowDraw].rect.bottom) / 2},
							{pictures[NowDraw].rect.left + (pictures[NowDraw].rect.right - pictures[NowDraw].rect.left) / 6, pictures[NowDraw].rect.bottom},
							{pictures[NowDraw].rect.right - (pictures[NowDraw].rect.right - pictures[NowDraw].rect.left) / 6, pictures[NowDraw].rect.bottom},
							{pictures[NowDraw].rect.right,(pictures[NowDraw].rect.top + pictures[NowDraw].rect.bottom) / 2}
							};
							Polygon(hDC, Pentagon, 5);
						}
						else if (pictures[NowDraw].Shape == 6)
							Ellipse(hDC, pictures[NowDraw].rect.left, pictures[NowDraw].rect.top, pictures[NowDraw].rect.right, pictures[NowDraw].rect.bottom);
					}
					SelectObject(hDC, oldPen);
					DeleteObject(hPen);
					SelectObject(hDC, oldBrush);
					DeleteObject(hBrush);

				}
			}
			else {
				hPen = CreatePen(PS_SOLID, pictures[NowDraw].Thick, pictures[NowDraw].PenColor); // 새로운 객체 만들기: 펜
				oldPen = (HPEN)SelectObject(hDC, hPen);
				hBrush = CreateSolidBrush(pictures[NowDraw].BrushColor); // 새로운 객체 만들기: 브러쉬
				oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

				{
					if (pictures[NowDraw].Shape == 1) {
						SelectObject(hDC, oldBrush);
						DeleteObject(hBrush);
						hBrush = CreateSolidBrush(PenColor); // 새로운 객체 만들기: 브러쉬
						oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
						if (pictures[NowDraw].Thick == 1)
							SetPixel(hDC, (pictures[NowDraw].rect.left + pictures[NowDraw].rect.right) / 2, (pictures[NowDraw].rect.top + pictures[NowDraw].rect.bottom) / 2, PenColor);
						else
							Ellipse(hDC, pictures[NowDraw].rect.left, pictures[NowDraw].rect.top, pictures[NowDraw].rect.right + pictures[NowDraw].Thick, pictures[NowDraw].rect.bottom + pictures[NowDraw].Thick);
					}
					else if (pictures[NowDraw].Shape == 2) {
						MoveToEx(hDC, pictures[NowDraw].rect.left, pictures[NowDraw].rect.top, NULL);
						LineTo(hDC, pictures[NowDraw].rect.right, pictures[NowDraw].rect.bottom);
					}
					else if (pictures[NowDraw].Shape == 3) {
						POINT Triangle[3] = {
						{ (pictures[NowDraw].rect.left + pictures[NowDraw].rect.right) / 2, pictures[NowDraw].rect.top },
						{pictures[NowDraw].rect.left, pictures[NowDraw].rect.bottom},
						{pictures[NowDraw].rect.right, pictures[NowDraw].rect.bottom}
						};
						Polygon(hDC, Triangle, 3);
					}
					else if (pictures[NowDraw].Shape == 4)
						Rectangle(hDC, pictures[NowDraw].rect.left, pictures[NowDraw].rect.top, pictures[NowDraw].rect.right, pictures[NowDraw].rect.bottom);
					else if (pictures[NowDraw].Shape == 5) {
						POINT Pentagon[5] = {
						{(pictures[NowDraw].rect.left + pictures[NowDraw].rect.right) / 2, pictures[NowDraw].rect.top},
						{pictures[NowDraw].rect.left, (pictures[NowDraw].rect.top + pictures[NowDraw].rect.bottom) / 2},
						{pictures[NowDraw].rect.left + (pictures[NowDraw].rect.right - pictures[NowDraw].rect.left) / 6, pictures[NowDraw].rect.bottom},
						{pictures[NowDraw].rect.right - (pictures[NowDraw].rect.right - pictures[NowDraw].rect.left) / 6, pictures[NowDraw].rect.bottom},
						{pictures[NowDraw].rect.right,(pictures[NowDraw].rect.top + pictures[NowDraw].rect.bottom) / 2}
						};
						Polygon(hDC, Pentagon, 5);
					}
					else if (pictures[NowDraw].Shape == 6)
						Ellipse(hDC, pictures[NowDraw].rect.left, pictures[NowDraw].rect.top, pictures[NowDraw].rect.right, pictures[NowDraw].rect.bottom);
				}
				SelectObject(hDC, oldPen);
				DeleteObject(hPen);
				SelectObject(hDC, oldBrush);
				DeleteObject(hBrush);

				if (PicCount < 2) {
					cheak = 0;
					PicCount++;
					NowDraw = PicCount;
				}
				else if (Max != 1) {
					Max = 1;
					NowDraw = PicCount;
				}
			}
		}
		else {
			if (error == 1) {
				static RECT messageRect = { 0,0,800,600 };
				DrawText(hDC, L"Error", _tcslen(L"Error"), &messageRect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
				error = 0;
			}
			else {
				hBrush = (HBRUSH)GetStockObject(HOLLOW_BRUSH); // 새로운 객체 만들기: 브러쉬
				oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
				int sizeAll = 0;
				for (int i = 0; i <= cheak; ++i) {
					TextOut(hDC, sizeAll + 10, 530, str[i], _tcslen(str[i]));
					GetTextExtentPoint32(hDC, str[i], lstrlen(str[i]), &size);
					sizeAll += size.cx;
				}
				SetCaretPos(sizeAll + 10, 530);
				Rectangle(hDC, 10, 530, sizeAll + 15, 550);
				SelectObject(hDC, oldBrush);
			}
		}
		EndPaint(hWnd, &ps);
		break;
	case WM_KEYDOWN:
		hDC = GetDC(hWnd);
		if (Max == 1) {
			if (wParam == VK_LEFT) {								// 왼방향
				if (pictures[NowDraw].rect.left <= 0);
				else {
					pictures[NowDraw].rect.left -= 10;
					pictures[NowDraw].rect.right -= 10;
				}
			}
			else if (wParam == VK_UP) {									// 위방향
				if (pictures[NowDraw].rect.top <= 0);
				else {
					pictures[NowDraw].rect.top -= 10;
					pictures[NowDraw].rect.bottom -= 10;
				}
			}
			else if (wParam == VK_RIGHT) {								// 우방향
				if (pictures[NowDraw].rect.right >= 800);
				else {
					pictures[NowDraw].rect.left += 10;
					pictures[NowDraw].rect.right += 10;
				}
			}
			else if (wParam == VK_DOWN) {								// 아래방향
				if (pictures[NowDraw].rect.bottom >= 600);
				else {
					pictures[NowDraw].rect.top += 10;
					pictures[NowDraw].rect.bottom += 10;
				}
			}
		}
		InvalidateRect(hWnd, NULL, true);
		ReleaseDC(hWnd, hDC);
		break;
	case WM_DESTROY:
		HideCaret(hWnd);
		DestroyCaret();
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
