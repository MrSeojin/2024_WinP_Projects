#include <windows.h>
#include <winuser.h>
#include <tchar.h>
#include <time.h>
#include <cstdlib>
HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Programming 2-12";
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
	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 1000, 1000, NULL, (HMENU)NULL, hInstance, NULL);
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
		int X, Y, Size;
		COLORREF BrushColor;
		int Change;
	};
	static COLORREF RandColor[15];
	static Library Shapes[10];
	static TCHAR iD[2];
	static int Count = 0, Select = 10;
	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;

	static int columns = 20;				//15

	switch (uMsg) {
	case WM_CREATE:
		srand(time(NULL));
		for (int i = 0; i < 15; ++i) {
			RandColor[i] = RGB(rand() % 225, rand() % 225, rand() % 225);
		}
		break;
	case WM_KEYDOWN:
		hDC = GetDC(hWnd);
		if (wParam == VK_LEFT) {								// 왼방향
			if (Select == 10);
			else {
				if (Shapes[Select].X == 40) {
					Shapes[Select].X = 940;
				}
				Shapes[Select].X -= 900 / columns;
			}
		}
		else if (wParam == VK_UP) {									// 위방향
			if (Select == 10);
			else {
				if (Shapes[Select].Y == 30) {
					Shapes[Select].Y = 930;
				}
				Shapes[Select].Y -= 900 / columns;
			}
		}
		else if (wParam == VK_RIGHT) {								// 우방향
			if (Select == 10);
			else {
				Shapes[Select].X += 900 / columns;
				if (Shapes[Select].X == 940) {
					Shapes[Select].X = 40;
				}
			}
		}
		else if (wParam == VK_DOWN) {								// 아래방향
			if (Select == 10);
			else {
				Shapes[Select].Y += 900 / columns;
				if (Shapes[Select].Y == 930) {
					Shapes[Select].Y = 30;
				}
			}
		}

		InvalidateRect(hWnd, NULL, true);
		ReleaseDC(hWnd, hDC);
		break;
	case WM_CHAR:
		hDC = GetDC(hWnd);

		if (wParam == 's') {
			for (int i = 0; i < 10; i++) {
				if (Shapes[i].Shape == 0);
				else {
					Shapes[i].X -= 40;
					Shapes[i].Y -= 30;
					Shapes[i].X *= columns;
					Shapes[i].Y *= columns;
				}
			}
			columns = 15;					//20
			for (int i = 0; i < 10; i++) {
				if (Shapes[i].Shape == 0);
				else {
					Shapes[i].Size = 900 / columns;
					Shapes[i].X /= columns;
					Shapes[i].Y /= columns;
					Shapes[i].X += 40;
					Shapes[i].Y += 30;
				}
				if (Shapes[i].X >= 940 || Shapes[i].Y >= 930) {
					Shapes[i].X = 900 / columns * (rand() % 15) + 40;
					Shapes[i].Y = 900 / columns * (rand() % 15) + 30;
				}
			}
		}
		else if (wParam == 'm') {
			for (int i = 0; i < 10; i++) {
				if (Shapes[i].Shape == 0);
				else {
					Shapes[i].X -= 40;
					Shapes[i].Y -= 30;
					Shapes[i].X *= columns;
					Shapes[i].Y *= columns;
				}
			}
			columns = 20;					//15
			for (int i = 0; i < 10; i++) {
				if (Shapes[i].Shape == 0);
				else {
					Shapes[i].Size = 900 / columns;
					Shapes[i].X /= columns;
					Shapes[i].Y /= columns;
					Shapes[i].X += 40;
					Shapes[i].Y += 30;
				}
				if (Shapes[i].X >= 940 || Shapes[i].Y >= 930) {
					Shapes[i].X = 900 / columns * (rand() % 15) + 40;
					Shapes[i].Y = 900 / columns * (rand() % 15) + 30;
				}
			}
		}
		else if (wParam == 'l') {
			for (int i = 0; i < 10; i++) {
				if (Shapes[i].Shape == 0);
				else {
					Shapes[i].X -= 40;
					Shapes[i].Y -= 30;
					Shapes[i].X *= columns;
					Shapes[i].Y *= columns;
				}
			}
			columns = 30;					//12
			for (int i = 0; i < 10; i++) {
				if (Shapes[i].Shape == 0);
				else {
					Shapes[i].Size = 900 / columns;
					Shapes[i].X /= columns;
					Shapes[i].Y /= columns;
					Shapes[i].X += 40;
					Shapes[i].Y += 30;
				}
			}
		}
		else if (wParam == 'e') {
			if (Count == Select)
				Select = 10;
			Shapes[Count].Shape = 1;
			if (columns == 15) {
				Shapes[Count].X = 900 / columns * (rand() % 15) + 40;
				Shapes[Count].Y = 900 / columns * (rand() % 15) + 30;
			}
			else if (columns == 20) {
				Shapes[Count].X = 900 / columns * (rand() % 20) + 40;
				Shapes[Count].Y = 900 / columns * (rand() % 20) + 30;
			}
			else if (columns == 30) {
				Shapes[Count].X = 900 / columns * (rand() % 30) + 40;
				Shapes[Count].Y = 900 / columns * (rand() % 30) + 30;
			}
			Shapes[Count].Size = 900 / columns;
			Shapes[Count].BrushColor = RandColor[rand() % 15];
			Shapes[Count].Change = 0;
			if (Count == 9)
				Count = 0;
			else Count++;
		}
		else if (wParam == 't') {
			if (Count == Select)
				Select = 10;
			Shapes[Count].Shape = 2;
			if (columns == 15) {
				Shapes[Count].X = 900 / columns * (rand() % 15) + 40;
				Shapes[Count].Y = 900 / columns * (rand() % 15) + 30;
			}
			else if (columns == 20) {
				Shapes[Count].X = 900 / columns * (rand() % 20) + 40;
				Shapes[Count].Y = 900 / columns * (rand() % 20) + 30;
			}
			else if (columns == 30) {
				Shapes[Count].X = 900 / columns * (rand() % 30) + 40;
				Shapes[Count].Y = 900 / columns * (rand() % 30) + 30;
			}
			Shapes[Count].Size = 900 / columns;
			Shapes[Count].BrushColor = RandColor[rand() % 15];
			Shapes[Count].Change = 0;
			if (Count == 9)
				Count = 0;
			else Count++;
		}
		else if (wParam == 'r') {
			if (Count == Select)
				Select = 10;
			Shapes[Count].Shape = 3;
			if (columns == 15) {
				Shapes[Count].X = 900 / columns * (rand() % 15) + 40;
				Shapes[Count].Y = 900 / columns * (rand() % 15) + 30;
			}
			else if (columns == 20) {
				Shapes[Count].X = 900 / columns * (rand() % 20) + 40;
				Shapes[Count].Y = 900 / columns * (rand() % 20) + 30;
			}
			else if (columns == 30) {
				Shapes[Count].X = 900 / columns * (rand() % 30) + 40;
				Shapes[Count].Y = 900 / columns * (rand() % 30) + 30;
			}
			Shapes[Count].Size = 900 / columns;
			Shapes[Count].BrushColor = RandColor[rand() % 15];
			Shapes[Count].Change = 0;
			if (Count == 9)
				Count = 0;
			else Count++;
		}
		else if (wParam == '0' || wParam == '1' || wParam == '2' || wParam == '3' || wParam == '4' || wParam == '5' || wParam == '6' || wParam == '7' || wParam == '8' || wParam == '9') {
			iD[0] = wParam;
			iD[1] = '\0';
			Select = _ttoi(iD);
		}
		else if (wParam == '+') {
			if (Select == 10);
			else {
				if (Shapes[Select].Size == 900 / columns);
				else {
					Shapes[Select].Size += 5;
				}
			}
		}
		else if (wParam == '-') {
			if (Select == 10);
			else {
				if (Shapes[Select].Size == 5);
				else {
					Shapes[Select].Size -= 5;
				}
			}
		}
		else if (wParam == 'c') {
			if (Shapes[0].Change == 0) {
				for (int i = 0; i < 10; ++i) {
					if (Shapes[i].Shape == 0)
						break;
					for (int j = 0; j < i; ++j) {
						if (Shapes[i].BrushColor == Shapes[j].BrushColor && Shapes[i].Shape == Shapes[j].Shape) {
							Shapes[i].Change = 1;
							Shapes[j].Change = 1;
						}
					}
				}
				if (Shapes[0].Change == 0)
					Shapes[0].Change = 10;
			}
			else {
				for (int i = 0; i < 10; ++i)
					Shapes[i].Change = 0;
			}
		}
		else if (wParam == 'd') {
			if (Select == 10);
			else {
				for (int i = Select; i < 9; ++i) {
					if (Shapes[i].Shape == 0) {
						Shapes[i - 1].Shape = 0;
						Count = i - 1;
						Select = 10;
						break;
					}
					Shapes[i].Shape = Shapes[i + 1].Shape;
					Shapes[i].X = Shapes[i + 1].X;
					Shapes[i].Y = Shapes[i + 1].Y;
					Shapes[i].Size = Shapes[i + 1].Size;
					Shapes[i].BrushColor = Shapes[i + 1].BrushColor;
					Shapes[i].Change = Shapes[i + 1].Change;
				}
			}
		}
		else if (wParam == 'p') {
			columns = 20;
			for (int i = 0; i < 10; ++i)
				Shapes[i].Shape = 0;
			Count = 0;
			Select = 10;
		}
		else if (wParam == 'q' || wParam == 'Q') {
			PostQuitMessage(0);
			break;
		}

		InvalidateRect(hWnd, NULL, true);
		ReleaseDC(hWnd, hDC);
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);

		//MAP----------------------------------------------------------------

		for (int j = 0; j < columns; ++j) {
			for (int i = 0; i < columns; ++i)
				Rectangle(hDC, 900 / columns * i + 40, 900 / columns * j + 30, 900 / columns * (i + 1) + 40, 900 / columns * (j + 1) + 30);
		}

		//-------------------------------------------------------------------

		for (int i = 0; i < 10; ++i) {
			hPen = (HPEN)GetStockObject(BLACK_PEN); // 새로운 객체 만들기: 펜
			oldPen = (HPEN)SelectObject(hDC, hPen);
			hBrush = CreateSolidBrush(Shapes[i].BrushColor); // 새로운 객체 만들기: 브러쉬
			oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
			if (Shapes[i].Shape == 0);
			else if (Shapes[i].Shape == 1) {
				if (Shapes[i].Change == 1) {
					Pie(hDC, Shapes[i].X, Shapes[i].Y, Shapes[i].X + Shapes[i].Size, Shapes[i].Y + Shapes[i].Size, Shapes[i].X + Shapes[i].Size / 2, Shapes[i].Y, Shapes[i].X + Shapes[i].Size, Shapes[i].Y + Shapes[i].Size / 2);
				}
				else
					Ellipse(hDC, Shapes[i].X, Shapes[i].Y, Shapes[i].X + Shapes[i].Size, Shapes[i].Y + Shapes[i].Size);
			}
			else if (Shapes[i].Shape == 2) {
				if (Shapes[i].Change == 1) {
					POINT Triangle[3] = {
					{Shapes[i].X + Shapes[i].Size / 2, Shapes[i].Y + Shapes[i].Size},
					{Shapes[i].X, Shapes[i].Y},
					{Shapes[i].X + Shapes[i].Size, Shapes[i].Y}
					};
					Polygon(hDC, Triangle, 3);
				}
				else {
					POINT Triangle[3] = {
					{Shapes[i].X + Shapes[i].Size / 2, Shapes[i].Y},
					{Shapes[i].X, Shapes[i].Y + Shapes[i].Size},
					{Shapes[i].X + Shapes[i].Size, Shapes[i].Y + Shapes[i].Size}
					};
					Polygon(hDC, Triangle, 3);
				}
			}
			else if (Shapes[i].Shape == 3) {
				if (Shapes[i].Change == 1) {		//Cross
					Rectangle(hDC, Shapes[i].X + Shapes[i].Size / 3, Shapes[i].Y, Shapes[i].X + Shapes[i].Size * 2 / 3, Shapes[i].Y + Shapes[i].Size);
					Rectangle(hDC, Shapes[i].X, Shapes[i].Y + Shapes[i].Size / 3, Shapes[i].X + Shapes[i].Size, Shapes[i].Y + Shapes[i].Size * 2 / 3);
				}
				else
					Rectangle(hDC, Shapes[i].X, Shapes[i].Y, Shapes[i].X + Shapes[i].Size, Shapes[i].Y + Shapes[i].Size);
			}
			SelectObject(hDC, oldPen);
			DeleteObject(hPen);
			SelectObject(hDC, oldBrush);
			DeleteObject(hBrush);
		}
		if (Select < 10) {
			hPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0)); // 새로운 객체 만들기: 펜
			oldPen = (HPEN)SelectObject(hDC, hPen);
			hBrush = CreateSolidBrush(Shapes[Select].BrushColor); // 새로운 객체 만들기: 브러쉬
			oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

			if (Shapes[Select].Shape == 0);
			else if (Shapes[Select].Shape == 1) {
				if (Shapes[Select].Change == 1)
					Pie(hDC, Shapes[Select].X, Shapes[Select].Y, Shapes[Select].X + Shapes[Select].Size, Shapes[Select].Y + Shapes[Select].Size, Shapes[Select].X + Shapes[Select].Size / 2, Shapes[Select].Y, Shapes[Select].X + Shapes[Select].Size, Shapes[Select].Y + Shapes[Select].Size / 2);
				else
					Ellipse(hDC, Shapes[Select].X, Shapes[Select].Y, Shapes[Select].X + Shapes[Select].Size, Shapes[Select].Y + Shapes[Select].Size);
			}
			else if (Shapes[Select].Shape == 2) {
				if (Shapes[Select].Change == 1) {
					POINT Triangle[3] = {
					{Shapes[Select].X + Shapes[Select].Size / 2, Shapes[Select].Y + Shapes[Select].Size},
					{Shapes[Select].X, Shapes[Select].Y},
					{Shapes[Select].X + Shapes[Select].Size, Shapes[Select].Y}
					};
					Polygon(hDC, Triangle, 3);
				}
				else {
					POINT Triangle[3] = {
					{ Shapes[Select].X + Shapes[Select].Size / 2, Shapes[Select].Y},
					{Shapes[Select].X, Shapes[Select].Y + Shapes[Select].Size},
					{Shapes[Select].X + Shapes[Select].Size, Shapes[Select].Y + Shapes[Select].Size}
					};
					Polygon(hDC, Triangle, 3);
				}
			}
			else if (Shapes[Select].Shape == 3) {
				if (Shapes[Select].Change == 1) {		//Cross
					Rectangle(hDC, Shapes[Select].X + Shapes[Select].Size / 3, Shapes[Select].Y, Shapes[Select].X + Shapes[Select].Size * 2 / 3, Shapes[Select].Y + Shapes[Select].Size);
					Rectangle(hDC, Shapes[Select].X, Shapes[Select].Y + Shapes[Select].Size / 3, Shapes[Select].X + Shapes[Select].Size, Shapes[Select].Y + Shapes[Select].Size * 2 / 3);
				}
				else
					Rectangle(hDC, Shapes[Select].X, Shapes[Select].Y, Shapes[Select].X + Shapes[Select].Size, Shapes[Select].Y + Shapes[Select].Size);
			}
			SelectObject(hDC, oldPen);
			DeleteObject(hPen);
			SelectObject(hDC, oldBrush);
			DeleteObject(hBrush);
		}

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
