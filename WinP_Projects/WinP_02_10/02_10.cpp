#include <windows.h>
#include <tchar.h>
#include <time.h>
#include <cstdlib>
HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Programming 2-10";
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

	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;
	struct Rock {
		int x;
		int y;
		int Size;
		int Shape;
		COLORREF Color;
	};

	static Rock player;
	static Rock Goal;

	static Rock Block[9];
	static Rock ChangeColor[6];
	static Rock SizeChange[2];
	static Rock ShapeChange[3];

	static int Return = 0;

	srand(time(NULL));

	switch (uMsg) {
	case WM_CREATE:
		player.x = 60;
		player.y = 60;
		player.Size = (rand() % 3 + 1) * 5;
		player.Shape = rand() % 4;
		player.Color = RGB(rand() % 100, rand() % 100, rand() % 100);

		Goal.x = 740;
		Goal.y = 540;
		Goal.Size = (rand() % 3 + 1) * 5;
		Goal.Shape = rand() % 4;
		Goal.Color = RGB(rand() % 100 + 100, rand() % 100 + 100, rand() % 100 + 100);

		static int firstPtr[22][2];
		firstPtr[0][0] = 60;
		firstPtr[0][1] = 60;
		firstPtr[1][0] = 740;
		firstPtr[1][1] = 540;

		for (int i = 2; i < 22; ++i) {
			firstPtr[i][0] = (rand() % 18 + 1) * 40 + 20;
			firstPtr[i][1] = (rand() % 13 + 1) * 40 + 20;
			for (int j = 0; j < i; ++j) {
				if (firstPtr[i][0] == firstPtr[j][0] && firstPtr[i][1] == firstPtr[j][1]) {
					--i;
					break;
				}
			}
		}

		for (int i = 0; i < 9; ++i) {
			Block[i].x = firstPtr[2 + i][0];
			Block[i].y = firstPtr[2 + i][1];
			Block[i].Size = 20;
			Block[i].Shape = 0;
			Block[i].Color = RGB(255, 0, 0);
		}
		for (int i = 0; i < 6; ++i) {
			ChangeColor[i].x = firstPtr[11 + i][0];
			ChangeColor[i].y = firstPtr[11 + i][1];
			ChangeColor[i].Size = 20;
			ChangeColor[i].Shape = 0;
			ChangeColor[i].Color = RGB(rand() % 225, rand() % 225, rand() % 225);
		}
		ChangeColor[0].Color = Goal.Color;
		for (int i = 0; i < 2; ++i) {
			SizeChange[i].x = firstPtr[17 + i][0];
			SizeChange[i].y = firstPtr[17 + i][1];
			SizeChange[i].Size = 20;
			SizeChange[i].Shape = 0;
		}
		SizeChange[0].Color = RGB(225, 225, 0);
		SizeChange[1].Color = RGB(0, 0, 225);
		for (int i = 0; i < 3; ++i) {
			ShapeChange[i].x = firstPtr[19 + i][0];
			ShapeChange[i].y = firstPtr[19 + i][1];
			ShapeChange[i].Size = 20;
			ShapeChange[i].Shape = 0;
			ShapeChange[i].Color = RGB(255, 127, 0);
		}
	case WM_CHAR:
		hDC = GetDC(hWnd);

		if (wParam == 'r' || Return == 1) {
			player.x = 60;
			player.y = 60;
			player.Size = (rand() % 4 + 1) * 5;
			player.Shape = rand() % 4;
			player.Color = RGB(rand() % 100, rand() % 100, rand() % 100);

			Goal.x = 740;
			Goal.y = 540;
			Goal.Size = (rand() % 4 + 1) * 5;
			Goal.Shape = rand() % 4;
			Goal.Color = RGB(rand() % 100 + 100, rand() % 100 + 100, rand() % 100 + 100);

			static int firstPtr[22][2];
			firstPtr[0][0] = 60;
			firstPtr[0][1] = 60;
			firstPtr[1][0] = 740;
			firstPtr[1][1] = 540;

			for (int i = 2; i < 22; ++i) {
				firstPtr[i][0] = (rand() % 17 + 1) * 40 + 20;
				firstPtr[i][1] = (rand() % 13 + 1) * 40 + 20;
				if (firstPtr[i][0] == firstPtr[i - 1][0] && firstPtr[i][1] == firstPtr[i - 0][1]) i--;
			}

			for (int i = 0; i < 9; ++i) {
				Block[i].x = firstPtr[2 + i][0];
				Block[i].y = firstPtr[2 + i][1];
			}
			for (int i = 0; i < 6; ++i) {
				ChangeColor[i].x = firstPtr[11 + i][0];
				ChangeColor[i].y = firstPtr[11 + i][1];
				ChangeColor[i].Color = RGB(rand() % 225, rand() % 225, rand() % 225);
			}
			ChangeColor[0].Color = Goal.Color;
			for (int i = 0; i < 2; ++i) {
				SizeChange[i].x = firstPtr[17 + i][0];
				SizeChange[i].y = firstPtr[17 + i][1];
			}
			for (int i = 0; i < 3; ++i) {
				ShapeChange[i].x = firstPtr[19 + i][0];
				ShapeChange[i].y = firstPtr[19 + i][1];
			}
			Return = 0;
		}
		else if (wParam == 'w') {
			if (player.y == 60)
				player.y = 540;
			else
				player.y -= 40;
			for (int i = 0; i < 9; ++i) {
				if (player.x == Block[i].x && player.y == Block[i].y)
					player.y += 40;
			}
		}
		else if (wParam == 'a') {
			if (player.x == 60)
				player.x = 740;
			else
				player.x -= 40;
			for (int i = 0; i < 9; ++i) {
				if (player.x == Block[i].x && player.y == Block[i].y)
					player.x += 40;
			}
		}
		else if (wParam == 's') {
			if (player.y == 540)
				player.y = 60;
			else
				player.y += 40;
			for (int i = 0; i < 9; ++i) {
				if (player.x == Block[i].x && player.y == Block[i].y)
					player.y -= 40;
			}
		}
		else if (wParam == 'd') {
			if (player.x == 740)
				player.x = 60;
			else
				player.x += 40;
			for (int i = 0; i < 9; ++i) {
				if (player.x == Block[i].x && player.y == Block[i].y)
					player.x -= 40;
			}
		}
		else if (wParam == 'q' || wParam == 'Q') {
			PostQuitMessage(0);
			break;
		}

		InvalidateRect(hWnd, NULL, TRUE);
		ReleaseDC(hWnd, hDC);
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);

		//MAP----------------------------------------------------------------

		for (int j = 1; j < 14; ++j) {
			for (int i = 1; i < 19; ++i)
				Rectangle(hDC, 40 * i, 40 * j, 40 * (i + 1), 40 * (j + 1));
		}

		//객체---------------------------------------------------------------
		{
			hBrush = CreateSolidBrush(player.Color); // 윈도우가 제공하는 객체 가져오기
			oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
			{
				if (player.Shape == 0) 				//Squire
					Rectangle(hDC, player.x - player.Size, player.y - player.Size, player.x + player.Size, player.y + player.Size);
				else if (player.Shape == 1) {		//Triangle
					POINT Triangle[3] = {
						{ player.x , player.y - player.Size },
						{player.x - player.Size, player.y + player.Size},
						{player.x + player.Size, player.y + player.Size}
					};
					Polygon(hDC, Triangle, 3);
				}
				else if (player.Shape == 2) {		//Circle
					Ellipse(hDC, player.x - player.Size, player.y - player.Size, player.x + player.Size, player.y + player.Size);
				}
				else if (player.Shape == 3) {		//Cross
					Rectangle(hDC, player.x - player.Size / 3, player.y - player.Size, player.x + player.Size / 3, player.y + player.Size);
					Rectangle(hDC, player.x - player.Size, player.y - player.Size / 3, player.x + player.Size, player.y + player.Size / 3);
				}
			}
			SelectObject(hDC, oldBrush);
			DeleteObject(hBrush);

			hBrush = CreateSolidBrush(Goal.Color); // 윈도우가 제공하는 객체 가져오기
			oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
			{
				if (Goal.Shape == 0) 				//Squire
					Rectangle(hDC, Goal.x - Goal.Size, Goal.y - Goal.Size, Goal.x + Goal.Size, Goal.y + Goal.Size);
				else if (Goal.Shape == 1) {		//Triangle
					POINT Triangle[3] = {
						{ Goal.x , Goal.y - Goal.Size },
						{Goal.x - Goal.Size, Goal.y + Goal.Size},
						{Goal.x + Goal.Size, Goal.y + Goal.Size}
					};
					Polygon(hDC, Triangle, 3);
				}
				else if (Goal.Shape == 2) {		//Circle
					Ellipse(hDC, Goal.x - Goal.Size, Goal.y - Goal.Size, Goal.x + Goal.Size, Goal.y + Goal.Size);
				}
				else if (Goal.Shape == 3) {		//Cross
					Rectangle(hDC, Goal.x - Goal.Size / 3, Goal.y - Goal.Size, Goal.x + Goal.Size / 3, Goal.y + Goal.Size);
					Rectangle(hDC, Goal.x - Goal.Size, Goal.y - Goal.Size / 3, Goal.x + Goal.Size, Goal.y + Goal.Size / 3);
				}
			}
			SelectObject(hDC, oldBrush);
			DeleteObject(hBrush);
			for (int i = 0; i < 9; ++i) {
				hBrush = CreateSolidBrush(Block[i].Color); // 윈도우가 제공하는 객체 가져오기
				oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
				Rectangle(hDC, Block[i].x - 20, Block[i].y - 20, Block[i].x + 20, Block[i].y + 20);
				SelectObject(hDC, oldBrush);
				DeleteObject(hBrush);
			}
			for (int i = 0; i < 6; ++i) {
				hBrush = CreateSolidBrush(ChangeColor[i].Color); // 윈도우가 제공하는 객체 가져오기
				oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
				Rectangle(hDC, ChangeColor[i].x - 20, ChangeColor[i].y - 20, ChangeColor[i].x + 20, ChangeColor[i].y + 20);
				SelectObject(hDC, oldBrush);
				DeleteObject(hBrush);
			}
			for (int i = 0; i < 2; ++i) {
				hBrush = CreateSolidBrush(SizeChange[i].Color); // 윈도우가 제공하는 객체 가져오기
				oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
				Rectangle(hDC, SizeChange[i].x - 20, SizeChange[i].y - 20, SizeChange[i].x + 20, SizeChange[i].y + 20);
				SelectObject(hDC, oldBrush);
				DeleteObject(hBrush);
			}
			for (int i = 0; i < 3; ++i) {
				hBrush = CreateSolidBrush(ShapeChange[i].Color); // 윈도우가 제공하는 객체 가져오기
				oldBrush = (HBRUSH)SelectObject(hDC, hBrush);
				Rectangle(hDC, ShapeChange[i].x - 20, ShapeChange[i].y - 20, ShapeChange[i].x + 20, ShapeChange[i].y + 20);
				SelectObject(hDC, oldBrush);
				DeleteObject(hBrush);
			}
		}

		if (player.x == Goal.x && player.y == Goal.y) {
			if (player.Color == Goal.Color && player.Size == Goal.Size && player.Shape == Goal.Size) {
				static RECT rect = { 0,0,800,600 };
				DrawText(hDC, _T("이기셨습니다."), _tcslen(_T("이기셨습니다.")), &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
				Return = 1;
			}
			else {
				static RECT rect = { 0,0,800,600 };
				DrawText(hDC, _T("Lose"), _tcslen(_T("Lose")), &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
				Return = 1;
			}
		}
		for (int i = 0; i < 6; ++i) {
			if (player.x == ChangeColor[i].x && player.y == ChangeColor[i].y) {
				player.Color = ChangeColor[i].Color;
			}
		}
		if (player.x == SizeChange[0].x && player.y == SizeChange[0].y) {
			if (player.Size == 5) {
				player.Size += 5;
			}
			else
				player.Size -= 5;
		}
		if (player.x == SizeChange[1].x && player.y == SizeChange[1].y) {
			if (player.Size == 20) {
				player.Size -= 5;
			}
			else
				player.Size += 5;
		}
		for (int i = 0; i < 3; ++i) {
			if (player.x == ShapeChange[i].x && player.y == ShapeChange[i].y) {
				if (player.Shape == 3) {
					player.Shape = 0;
				}
				else
					player.Shape += 1;
			}
		}

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
