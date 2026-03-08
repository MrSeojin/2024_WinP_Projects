#include <windows.h>
#include <tchar.h>
#include <time.h>
#include <cstdlib>
HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Programming 2-9";
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

	RECT rect_0 = { 300, 200, 500, 400 };
	RECT Srect[4] = {
		{150, 250, 250, 350},
		{350, 50, 450, 150},
		{550, 250, 650, 350},
		{350, 450, 450, 550}
	};

	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;

	static int PaintSet[4] = { 1,2,3,4 };
	static int Take = 0;
	static int DrawCenter;

	static COLORREF PenColor = RGB(0, 0, 0);
	static COLORREF TriangleBRUSH = RGB(255, 0, 0),
		SandBRUSH = RGB(255, 255, 0),
		PentagonBRUSH = RGB(0, 255, 0),
		ArcBRUSH = RGB(0, 0, 255);

	switch (uMsg) {
	case WM_CREATE:
		srand(time(NULL));
		DrawCenter = rand() % 4;
		break;
	case WM_KEYDOWN:
		hDC = GetDC(hWnd);
		if (wParam == VK_LEFT) {								// 왼방향
			for (int i = 0; i < 4; ++i) {
				if (PaintSet[i] == 4)
					PaintSet[i] = 1;
				else
					PaintSet[i] += 1;
			}
		}
		else if (wParam == VK_RIGHT) {								// 우방향
			for (int i = 0; i < 4; ++i) {
				if (PaintSet[i] == 1)
					PaintSet[i] = 4;
				else
					PaintSet[i] -= 1;
			}
		}
		else if (wParam == 't' || wParam == 'T') {
			Take = 1;
			TriangleBRUSH = RGB(rand() % 255, rand() % 255, rand() % 255);
		}
		else if (wParam == 's' || wParam == 'S') {
			Take = 2;
			SandBRUSH = RGB(rand() % 255, rand() % 255, rand() % 255);
		}
		else if (wParam == 'p' || wParam == 'P') {
			Take = 3;
			PentagonBRUSH = RGB(rand() % 255, rand() % 255, rand() % 255);
		}
		else if (wParam == 'e' || wParam == 'E') {
			Take = 4;
			ArcBRUSH = RGB(rand() % 255, rand() % 255, rand() % 255);
		}
		InvalidateRect(hWnd, NULL, true);
		ReleaseDC(hWnd, hDC);
		break;
	case WM_KEYUP:
		hDC = GetDC(hWnd);

		if (wParam == 't' || wParam == 'T')
			TriangleBRUSH = RGB(255, 0, 0);
		else if (wParam == 's' || wParam == 'S')
			SandBRUSH = RGB(255, 255, 0);
		else if (wParam == 'p' || wParam == 'P')
			PentagonBRUSH = RGB(0, 255, 0);
		else if (wParam == 'e' || wParam == 'E')
			ArcBRUSH = RGB(0, 0, 255);
		else;

		Take = 0;

		InvalidateRect(hWnd, NULL, true);
		ReleaseDC(hWnd, hDC);
		break;
	case WM_CHAR:
		hDC = GetDC(hWnd);

		srand(time(NULL));
		if (wParam == 'q' || wParam == 'Q') {
			PostQuitMessage(0);
			break;
		}
		else;
		InvalidateRect(hWnd, NULL, TRUE);
		ReleaseDC(hWnd, hDC);
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);

		// 상자-----------------------------------------------------------------------------------------------------
		hPen = CreatePen(PS_SOLID, 3, PenColor); // 새로운 객체 만들기: 펜
		oldPen = (HPEN)SelectObject(hDC, hPen);
		hBrush = (HBRUSH)GetStockObject(LTGRAY_BRUSH); // 윈도우가 제공하는 객체 가져오기
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

		Rectangle(hDC, rect_0.left, rect_0.top, rect_0.right, rect_0.bottom);

		SelectObject(hDC, oldBrush);
		hBrush = (HBRUSH)GetStockObject(HOLLOW_BRUSH); // 윈도우가 제공하는 객체 가져오기
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

		for (int i = 0; i < 4; ++i)
			Rectangle(hDC, Srect[i].left, Srect[i].top, Srect[i].right, Srect[i].bottom);

		SelectObject(hDC, oldBrush);
		SelectObject(hDC, oldPen); // 제자리 돌아가기
		DeleteObject(hPen); // 새로운 객체 삭제
		// 5개의 그림------------------------------------------------------------------------------------------------
		hPen = CreatePen(PS_SOLID, 1, PenColor); // 새로운 객체 만들기: 펜
		oldPen = (HPEN)SelectObject(hDC, hPen);
		for (int i = 0; i < 4; ++i) {
			if (PaintSet[i] == 1) {
				hBrush = CreateSolidBrush(TriangleBRUSH); // 새로운 객체 만들기: 브러쉬
				oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

				POINT TriangleP[3] = {
					{ (Srect[i].left + Srect[i].right) / 2, Srect[i].top },
					{Srect[i].left, Srect[i].bottom},
					{Srect[i].right, Srect[i].bottom}
				};
				Polygon(hDC, TriangleP, 3);
				SelectObject(hDC, oldBrush);
				DeleteObject(hBrush);
			}
			else if (PaintSet[i] == 2) {
				hBrush = CreateSolidBrush(SandBRUSH); // 새로운 객체 만들기: 브러쉬
				oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
				POINT SandPt[3] = {
					{(Srect[i].left + Srect[i].right) / 2,(Srect[i].top + Srect[i].bottom) / 2},
					{Srect[i].left, Srect[i].top},
					{Srect[i].right, Srect[i].top} };
				POINT SandPb[3] = {
					{(Srect[i].left + Srect[i].right) / 2,(Srect[i].top + Srect[i].bottom) / 2},
					{Srect[i].left, Srect[i].bottom},
					{Srect[i].right, Srect[i].bottom} };
				Polygon(hDC, SandPt, 3);
				Polygon(hDC, SandPb, 3);
				SelectObject(hDC, oldBrush);
				DeleteObject(hBrush);
			}
			else if (PaintSet[i] == 3) {
				hBrush = CreateSolidBrush(PentagonBRUSH); // 새로운 객체 만들기: 브러쉬
				oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
				POINT PentagonP[5] = {
					{(Srect[i].left + Srect[i].right) / 2, Srect[i].top},
					{Srect[i].left, (Srect[i].top + Srect[i].bottom) / 2},
					{Srect[i].left + (Srect[i].right - Srect[i].left) / 6,Srect[i].bottom},
					{Srect[i].right - (Srect[i].right - Srect[i].left) / 6,Srect[i].bottom},
					{Srect[i].right,(Srect[i].top + Srect[i].bottom) / 2}
				};
				Polygon(hDC, PentagonP, 5);
				SelectObject(hDC, oldBrush);
				DeleteObject(hBrush);
			}
			else if (PaintSet[i] == 4) {
				hBrush = CreateSolidBrush(ArcBRUSH); // 새로운 객체 만들기: 브러쉬
				oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
				Pie(hDC, Srect[i].left, Srect[i].top, Srect[i].right, Srect[i].bottom, (Srect[i].left + Srect[i].right) / 2, Srect[i].top, Srect[i].right, (Srect[i].top + Srect[i].bottom) / 2);
				SelectObject(hDC, oldBrush);
				DeleteObject(hBrush);
			}
		}
		if (Take == 0) {
			if (PaintSet[DrawCenter] == 1) {
				hBrush = CreateSolidBrush(TriangleBRUSH); // 새로운 객체 만들기: 브러쉬
				oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

				POINT Triangle[3] = {
				{ (rect_0.left + rect_0.right) / 2, rect_0.top },
				{rect_0.left, rect_0.bottom},
				{rect_0.right, rect_0.bottom}
				};
				Polygon(hDC, Triangle, 3);

				SelectObject(hDC, oldBrush);
				DeleteObject(hBrush);
			}
			else if (PaintSet[DrawCenter] == 2) {
				hBrush = CreateSolidBrush(SandBRUSH); // 새로운 객체 만들기: 브러쉬
				oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
				POINT Sandt[3] = {
				{ (rect_0.left + rect_0.right) / 2, (rect_0.top + rect_0.bottom) / 2 },
				{rect_0.left, rect_0.top},
				{rect_0.right, rect_0.top} };
				POINT Sandb[3] = {
				{ (rect_0.left + rect_0.right) / 2, (rect_0.top + rect_0.bottom) / 2 },
				{rect_0.left, rect_0.bottom},
				{rect_0.right, rect_0.bottom} };

				Polygon(hDC, Sandt, 3);
				Polygon(hDC, Sandb, 3);
				SelectObject(hDC, oldBrush);
				DeleteObject(hBrush);
			}
			else if (PaintSet[DrawCenter] == 3) {
				hBrush = CreateSolidBrush(PentagonBRUSH); // 새로운 객체 만들기: 브러쉬
				oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
				POINT Pentagon[5] = {
				{(rect_0.left + rect_0.right) / 2, rect_0.top},
				{rect_0.left, (rect_0.top + rect_0.bottom) / 2},
				{rect_0.left + (rect_0.right - rect_0.left) / 6, rect_0.bottom},
				{rect_0.right - (rect_0.right - rect_0.left) / 6, rect_0.bottom},
				{rect_0.right,(rect_0.top + rect_0.bottom) / 2}
				};
				Polygon(hDC, Pentagon, 5);
				SelectObject(hDC, oldBrush);
				DeleteObject(hBrush);
			}
			else if (PaintSet[DrawCenter] == 4) {
				hBrush = CreateSolidBrush(ArcBRUSH); // 새로운 객체 만들기: 브러쉬
				oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
				Pie(hDC, rect_0.left, rect_0.top, rect_0.right, rect_0.bottom, (rect_0.left + rect_0.right) / 2, rect_0.top, rect_0.right, (rect_0.top + rect_0.bottom) / 2);
				SelectObject(hDC, oldBrush);
				DeleteObject(hBrush);
			}
		}
		else {
			if (Take == 1) {
				hBrush = CreateSolidBrush(TriangleBRUSH); // 새로운 객체 만들기: 브러쉬
				oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

				POINT Triangle[3] = {
				{ (rect_0.left + rect_0.right) / 2, rect_0.top },
				{rect_0.left, rect_0.bottom},
				{rect_0.right, rect_0.bottom}
				};
				Polygon(hDC, Triangle, 3);

				SelectObject(hDC, oldBrush);
				DeleteObject(hBrush);
			}
			else if (Take == 2) {
				hBrush = CreateSolidBrush(SandBRUSH); // 새로운 객체 만들기: 브러쉬
				oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
				POINT Sandt[3] = {
				{ (rect_0.left + rect_0.right) / 2, (rect_0.top + rect_0.bottom) / 2 },
				{rect_0.left, rect_0.top},
				{rect_0.right, rect_0.top} };
				POINT Sandb[3] = {
				{ (rect_0.left + rect_0.right) / 2, (rect_0.top + rect_0.bottom) / 2 },
				{rect_0.left, rect_0.bottom},
				{rect_0.right, rect_0.bottom} };

				Polygon(hDC, Sandt, 3);
				Polygon(hDC, Sandb, 3);
				SelectObject(hDC, oldBrush);
				DeleteObject(hBrush);
			}
			else if (Take == 3) {
				hBrush = CreateSolidBrush(PentagonBRUSH); // 새로운 객체 만들기: 브러쉬
				oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
				POINT Pentagon[5] = {
				{(rect_0.left + rect_0.right) / 2, rect_0.top},
				{rect_0.left, (rect_0.top + rect_0.bottom) / 2},
				{rect_0.left + (rect_0.right - rect_0.left) / 6, rect_0.bottom},
				{rect_0.right - (rect_0.right - rect_0.left) / 6, rect_0.bottom},
				{rect_0.right,(rect_0.top + rect_0.bottom) / 2}
				};
				Polygon(hDC, Pentagon, 5);
				SelectObject(hDC, oldBrush);
				DeleteObject(hBrush);
			}
			else if (Take == 4) {
				hBrush = CreateSolidBrush(ArcBRUSH); // 새로운 객체 만들기: 브러쉬
				oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
				Pie(hDC, rect_0.left, rect_0.top, rect_0.right, rect_0.bottom, (rect_0.left + rect_0.right) / 2, rect_0.top, rect_0.right, (rect_0.top + rect_0.bottom) / 2);
				SelectObject(hDC, oldBrush);
				DeleteObject(hBrush);
			}
		}

		SelectObject(hDC, oldPen);
		DeleteObject(hPen);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}