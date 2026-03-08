#include <windows.h>
#include <winuser.h>
#include <tchar.h>
#include <time.h>
#include <cstdlib>
HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Programming 2-13";
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
	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 820, 590, NULL, (HMENU)NULL, hInstance, NULL);
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

	struct alp {
		TCHAR A;
		int X, Y;
	};
	RECT answerR = { 35 * 9, 25 * 3, 35 * 14, 25 * 4 };
	static RECT player;
	static alp answer[3][5]{
		{{'W', 35 * 9, 25 * 3}, { 'A' , 35 * 10, 25 * 3},{ 'T', 35 * 11, 25 * 3}, {'E', 35 * 12, 25 * 3},{'R', 35 * 13, 25 * 3}},
		{{'A', 35 * 9, 25 * 3},{ 'B', 35 * 10, 25 * 3},{'O', 35 * 11, 25 * 3}, {'U', 35 * 12, 25 * 3},{'T', 35 * 13, 25 * 3}},
		{{'D', 35 * 9, 25 * 3}, {'E', 35 * 10, 25 * 3},{'A', 35 * 11, 25 * 3}, {'T', 35 * 12, 25 * 3},{'H', 35 * 13, 25 * 3}}
	};
	static alp randAlp[10];
	static int ToMove[2];
	static int now, Return = 0;
	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;

	switch (uMsg) {
	case WM_CREATE:
		srand(time(NULL));
		now = rand() % 3;

		static int firstPtr[15][2];
		firstPtr[0][0] = answer[now][0].X;
		firstPtr[0][1] = answer[now][0].Y;
		firstPtr[1][0] = answer[now][1].X;
		firstPtr[1][1] = answer[now][1].Y;

		static int Pos = rand() % 3;
		firstPtr[Pos + 2][0] = answer[now][Pos + 1].X;
		firstPtr[Pos + 2][1] = answer[now][Pos + 1].Y;

		for (int i = 1; i < 4; ++i) {
			if (i == Pos + 1);
			else
				ToMove[1] = i;
		}
		for (int i = 1; i < 4; ++i) {
			if (i == Pos + 1);
			else {
				ToMove[0] = i;
				break;
			}
		}

		for (int i = 2; i < 15; ++i) {
			if (i == Pos + 2);
			else {
				firstPtr[i][0] = (rand() % 21 + 1) * 35;
				firstPtr[i][1] = (rand() % 20 + 1) * 25;
				if (35 * 9 <= firstPtr[i][0] <= 35 * 13 && firstPtr[i][1] == 25 * 3)
					i--;
				else {
					for (int j = 2; j < i; ++j) {
						if (firstPtr[i][0] == firstPtr[j][0] && firstPtr[i][1] == firstPtr[j][1]) {
							i--;
							break;
						}
					}
				}
			}
		}

		for (int i = 1; i < 4; ++i) {
			answer[now][i].X = firstPtr[i + 1][0];
			answer[now][i].Y = firstPtr[i + 1][1];
		}

		for (int i = 0; i < 10; ++i) {
			randAlp[i].X = firstPtr[i + 5][0];
			randAlp[i].Y = firstPtr[i + 5][1];
			randAlp[i].A = rand() % 26 + 65;
			if (randAlp[i].A == answer[now][0].A || randAlp[i].A == answer[now][1].A || randAlp[i].A == answer[now][2].A || randAlp[i].A == answer[now][3].A || randAlp[i].A == answer[now][4].A)
				--i;
		}

		player = { 35 * 11, 25 * 20, 35 * 12, 25 * 21 };

		break;
	case WM_CHAR:
		hDC = GetDC(hWnd);
		{
			if (wParam == 'r' || Return == 1) {
				now = rand() % 3;

				for (int i = 0; i < 3; ++i) {
					for (int j = 0; j < 5; ++j) {
						answer[i][j].X = 35 * (9 + j);
						answer[i][j].Y = 25 * 3;
					}
				}

				for (int i = 1; i < 4; ++i) {
					if (i == Pos + 1);
					else
						ToMove[1] = i;
				}
				for (int i = 1; i < 4; ++i) {
					if (i == Pos + 1);
					else {
						ToMove[0] = i;
						break;
					}
				}

				static int Pos = rand() % 3;
				firstPtr[Pos + 2][0] = answer[now][Pos + 1].X;
				firstPtr[Pos + 2][1] = answer[now][Pos + 1].Y;

				for (int i = 2; i < 15; ++i) {
					if (i == Pos + 2);
					else {
						firstPtr[i][0] = (rand() % 21 + 1) * 35;
						firstPtr[i][1] = (rand() % 20 + 1) * 25;
						if (35 * 9 <= firstPtr[i][0] <= 35 * 13 && firstPtr[i][1] == 25 * 3)
							i--;
						else if (firstPtr[i][0] == player.left && firstPtr[i][1] == player.top)
							i--;
						else {
							for (int j = 2; j < i; ++j) {
								if (firstPtr[i][0] == firstPtr[j][0] && firstPtr[i][1] == firstPtr[j][1]) {
									i--;
									break;
								}
							}
						}
					}
				}

				for (int i = 1; i < 4; ++i) {
					answer[now][i].X = firstPtr[i + 1][0];
					answer[now][i].Y = firstPtr[i + 1][1];
				}

				for (int i = 0; i < 10; ++i) {
					randAlp[i].X = firstPtr[i + 5][0];
					randAlp[i].Y = firstPtr[i + 5][1];
					randAlp[i].A = rand() % 26 + 65;
					if (randAlp[i].A == answer[now][0].A || randAlp[i].A == answer[now][1].A || randAlp[i].A == answer[now][2].A || randAlp[i].A == answer[now][3].A || randAlp[i].A == answer[now][4].A)
						--i;
				}
				Return = 0;
			}
			else if (wParam == 'w') {
				player.top -= 25;
				if (player.top == 0)
					player.top = 25 * 20;
				player.bottom = player.top + 25;
				for (int i = 0; i < 10; i++) {
					if (randAlp[i].X == player.left && randAlp[i].Y == player.top) {
						randAlp[i].Y -= 25;
						if (randAlp[i].Y == 0)
							randAlp[i].Y = 25 * 20;
						for (int j = 0; j < 10; j++) {
							if (i == j);
							else {
								if (randAlp[i].X == randAlp[j].X && randAlp[i].Y == randAlp[j].Y) {
									randAlp[i].Y += 25;
									if (player.top == 25 * 20)
										player.top = 0;
									else
										player.top += 25;
									player.bottom = player.top + 25;
									break;
								}
								else if (answer[now][ToMove[0]].X == randAlp[i].X && answer[now][ToMove[0]].Y == randAlp[i].Y) {
									randAlp[i].Y += 25;
									if (player.top == 25 * 20)
										player.top = 0;
									else
										player.top += 25;
									player.bottom = player.top + 25;
									break;
								}
								else if (answer[now][ToMove[1]].X == randAlp[i].X && answer[now][ToMove[1]].Y == randAlp[i].Y) {
									randAlp[i].Y += 25;
									if (player.top == 25 * 20)
										player.top = 0;
									else
										player.top += 25;
									player.bottom = player.top + 25;
									break;
								}
							}
						}
						break;
					}
				}
				if (answer[now][ToMove[0]].X == player.left && answer[now][ToMove[0]].Y == player.top) {
					answer[now][ToMove[0]].Y -= 25;
					if (answer[now][ToMove[0]].Y == 0)
						answer[now][ToMove[0]].Y = 25 * 20;
					for (int j = 0; j < 10; j++) {
						if (answer[now][ToMove[0]].X == randAlp[j].X && answer[now][ToMove[0]].Y == randAlp[j].Y) {
							answer[now][ToMove[0]].Y += 25;
							if (player.top == 25 * 20)
								player.top = 0;
							else
								player.top += 25;
							player.bottom = player.top + 25;
							break;
						}
						else if (answer[now][ToMove[0]].X == answer[now][ToMove[1]].X && answer[now][ToMove[0]].Y == answer[now][ToMove[1]].Y) {
							answer[now][ToMove[0]].Y += 25;
							if (player.top == 25 * 20)
								player.top = 0;
							else
								player.top += 25;
							player.bottom = player.top + 25;
							break;
						}
					}
				}
				else if (answer[now][ToMove[1]].X == player.left && answer[now][ToMove[1]].Y == player.top) {
					answer[now][ToMove[1]].Y -= 25;
					if (answer[now][ToMove[1]].Y == 0)
						answer[now][ToMove[1]].Y = 25 * 20;
					for (int j = 0; j < 10; j++) {
						if (answer[now][ToMove[1]].X == randAlp[j].X && answer[now][ToMove[1]].Y == randAlp[j].Y) {
							answer[now][ToMove[1]].Y += 25;
							if (player.top == 25 * 20)
								player.top = 0;
							else
								player.top += 25;
							player.bottom = player.top + 25;
							break;
						}
						else if (answer[now][ToMove[0]].X == answer[now][ToMove[1]].X && answer[now][ToMove[0]].Y == answer[now][ToMove[1]].Y) {
							answer[now][ToMove[1]].Y += 25;
							if (player.top == 25 * 20)
								player.top = 0;
							else
								player.top += 25;
							player.bottom = player.top + 25;
							break;
						}
					}
				}
			}
			else if (wParam == 'a') {
				player.left -= 35;
				if (player.left == 0)
					player.left = 35 * 21;
				player.right = player.left + 35;
				for (int i = 0; i < 10; i++) {
					if (randAlp[i].X == player.left && randAlp[i].Y == player.top) {
						randAlp[i].X -= 35;
						if (randAlp[i].X == 0)
							randAlp[i].X = 35 * 21;
						for (int j = 0; j < 10; j++) {
							if (i == j);
							else {
								if (randAlp[i].X == randAlp[j].X && randAlp[i].Y == randAlp[j].Y) {
									randAlp[i].X += 35;
									if (player.left == 35 * 21)
										player.left = 0;
									else
										player.left += 35;
									player.right = player.left + 35;
									break;
								}
								else if (answer[now][ToMove[0]].X == randAlp[i].X && answer[now][ToMove[0]].Y == randAlp[i].Y) {
									randAlp[i].X += 35;
									if (player.left == 35 * 21)
										player.left = 0;
									else
										player.left += 35;
									player.right = player.left + 35;
									break;
								}
								else if (answer[now][ToMove[1]].X == randAlp[i].X && answer[now][ToMove[1]].Y == randAlp[i].Y) {
									randAlp[i].X += 35;
									if (player.left == 35 * 21)
										player.left = 0;
									else
										player.left += 35;
									player.right = player.left + 35;
									break;
								}
							}
						}
						break;
					}
				}
				if (answer[now][ToMove[0]].X == player.left && answer[now][ToMove[0]].Y == player.top) {
					answer[now][ToMove[0]].X -= 35;
					if (answer[now][ToMove[0]].X == 0)
						answer[now][ToMove[0]].X = 35 * 21;
					for (int j = 0; j < 10; j++) {
						if (answer[now][ToMove[0]].X == randAlp[j].X && answer[now][ToMove[0]].Y == randAlp[j].Y) {
							answer[now][ToMove[0]].X += 35;
							if (player.left == 35 * 21)
								player.left = 0;
							else
								player.left += 35;
							player.right = player.left + 35;
							break;
						}
						else if (answer[now][ToMove[0]].X == answer[now][ToMove[1]].X && answer[now][ToMove[0]].Y == answer[now][ToMove[1]].Y) {
							answer[now][ToMove[0]].X += 35;
							if (player.left == 35 * 21)
								player.left = 0;
							else
								player.left += 35;
							player.right = player.left + 35;
							break;
						}
					}
				}
				else if (answer[now][ToMove[1]].X == player.left && answer[now][ToMove[1]].Y == player.top) {
					answer[now][ToMove[1]].X -= 35;
					if (answer[now][ToMove[1]].X == 0)
						answer[now][ToMove[1]].X = 35 * 21;
					for (int j = 0; j < 10; j++) {
						if (answer[now][ToMove[1]].X == randAlp[j].X && answer[now][ToMove[1]].Y == randAlp[j].Y) {
							answer[now][ToMove[1]].X += 35;
							if (player.left == 35 * 21)
								player.left = 0;
							else
								player.left += 35;
							player.right = player.left + 35;
							break;
						}
						else if (answer[now][ToMove[0]].X == answer[now][ToMove[1]].X && answer[now][ToMove[0]].Y == answer[now][ToMove[1]].Y) {
							answer[now][ToMove[1]].X += 35;
							if (player.left == 35 * 21)
								player.left = 0;
							else
								player.left += 35;
							player.right = player.left + 35;
							break;
						}
					}
				}
			}
			else if (wParam == 's') {
				player.top += 25;
				if (player.top == 25 * 21)
					player.top = 25;
				player.bottom = player.top + 25;
				for (int i = 0; i < 10; i++) {
					if (randAlp[i].X == player.left && randAlp[i].Y == player.top) {
						randAlp[i].Y += 25;
						if (randAlp[i].Y == 25 * 21)
							randAlp[i].Y = 25;
						for (int j = 0; j < 10; j++) {
							if (i == j);
							else {
								if (randAlp[i].X == randAlp[j].X && randAlp[i].Y == randAlp[j].Y) {
									randAlp[i].Y -= 25;
									if (player.top == 25 * 21)
										player.top = 25;
									else
										player.top -= 25;
									player.bottom = player.top + 25;
									break;
								}
								else if (answer[now][ToMove[0]].X == randAlp[i].X && answer[now][ToMove[0]].Y == randAlp[i].Y) {
									randAlp[i].Y -= 25;
									if (player.top == 25 * 21)
										player.top = 25;
									else
										player.top -= 25;
									player.bottom = player.top + 25;
									break;
								}
								else if (answer[now][ToMove[1]].X == randAlp[i].X && answer[now][ToMove[1]].Y == randAlp[i].Y) {
									randAlp[i].Y -= 25;
									if (player.top == 25 * 21)
										player.top = 25;
									else
										player.top -= 25;
									player.bottom = player.top + 25;
									break;
								}
							}
						}
						break;
					}
				}
				if (answer[now][ToMove[0]].X == player.left && answer[now][ToMove[0]].Y == player.top) {
					answer[now][ToMove[0]].Y += 25;
					if (answer[now][ToMove[0]].Y == 25 * 21)
						answer[now][ToMove[0]].Y = 25;
					for (int j = 0; j < 10; j++) {
						if (answer[now][ToMove[0]].X == randAlp[j].X && answer[now][ToMove[0]].Y == randAlp[j].Y) {
							answer[now][ToMove[0]].Y -= 25;
							if (player.top == 25 * 21)
								player.top = 25;
							else
								player.top -= 25;
							player.bottom = player.top + 25;
							break;
						}
						else if (answer[now][ToMove[0]].X == answer[now][ToMove[1]].X && answer[now][ToMove[0]].Y == answer[now][ToMove[1]].Y) {
							answer[now][ToMove[0]].Y -= 25;
							if (player.top == 25 * 21)
								player.top = 25;
							else
								player.top -= 25;
							player.bottom = player.top + 25;
							break;
						}
					}
				}
				else if (answer[now][ToMove[1]].X == player.left && answer[now][ToMove[1]].Y == player.top) {
					answer[now][ToMove[1]].Y += 25;
					if (answer[now][ToMove[1]].Y == 25 * 21)
						answer[now][ToMove[1]].Y = 25;
					for (int j = 0; j < 10; j++) {
						if (answer[now][ToMove[1]].X == randAlp[j].X && answer[now][ToMove[1]].Y == randAlp[j].Y) {
							answer[now][ToMove[1]].Y -= 25;
							if (player.top == 25 * 21)
								player.top = 25;
							else
								player.top -= 25;
							player.bottom = player.top + 25;
							break;
						}
						else if (answer[now][ToMove[0]].X == answer[now][ToMove[1]].X && answer[now][ToMove[0]].Y == answer[now][ToMove[1]].Y) {
							answer[now][ToMove[1]].Y -= 25;
							if (player.top == 25 * 21)
								player.top = 25;
							else
								player.top -= 25;
							player.bottom = player.top + 25;
							break;
						}
					}
				}
			}
			else if (wParam == 'd') {
				player.left += 35;
				if (player.left == 35 * 22)
					player.left = 35;
				player.right = player.left + 35;
				for (int i = 0; i < 10; i++) {
					if (randAlp[i].X == player.left && randAlp[i].Y == player.top) {
						randAlp[i].X += 35;
						if (randAlp[i].X == 35 * 22)
							randAlp[i].X = 35;
						for (int j = 0; j < 10; j++) {
							if (i == j);
							else {
								if (randAlp[i].X == randAlp[j].X && randAlp[i].Y == randAlp[j].Y) {
									randAlp[i].X -= 35;
									if (player.left == 35 * 22)
										player.left = 35;
									else
										player.left -= 35;
									player.right = player.left + 35;
									break;
								}
								else if (answer[now][ToMove[0]].X == randAlp[i].X && answer[now][ToMove[0]].Y == randAlp[i].Y) {
									randAlp[i].X -= 35;
									if (player.left == 35 * 22)
										player.left = 35;
									else
										player.left -= 35;
									player.right = player.left + 35;
									break;
								}
								else if (answer[now][ToMove[1]].X == randAlp[i].X && answer[now][ToMove[1]].Y == randAlp[i].Y) {
									randAlp[i].X -= 35;
									if (player.left == 35 * 22)
										player.left = 35;
									else
										player.left -= 35;
									player.right = player.left + 35;
									break;
								}
							}
						}
						break;
					}
				}
				if (answer[now][ToMove[0]].X == player.left && answer[now][ToMove[0]].Y == player.top) {
					answer[now][ToMove[0]].X += 35;
					if (answer[now][ToMove[0]].X == 35 * 22)
						answer[now][ToMove[0]].X = 35;
					for (int j = 0; j < 10; j++) {
						if (answer[now][ToMove[0]].X == randAlp[j].X && answer[now][ToMove[0]].Y == randAlp[j].Y) {
							answer[now][ToMove[0]].X -= 35;
							if (player.left == 35 * 22)
								player.left = 35;
							else
								player.left -= 35;
							player.right = player.left + 35;
							break;
						}
						else if (answer[now][ToMove[0]].X == answer[now][ToMove[1]].X && answer[now][ToMove[0]].Y == answer[now][ToMove[1]].Y) {
							answer[now][ToMove[0]].X -= 35;
							if (player.left == 35 * 22)
								player.left = 35;
							else
								player.left -= 35;
							player.right = player.left + 35;
							break;
						}
					}
				}
				else if (answer[now][ToMove[1]].X == player.left && answer[now][ToMove[1]].Y == player.top) {
					answer[now][ToMove[1]].X += 35;
					if (answer[now][ToMove[1]].X == 35 * 22)
						answer[now][ToMove[1]].X = 35;
					for (int j = 0; j < 10; j++) {
						if (answer[now][ToMove[1]].X == randAlp[j].X && answer[now][ToMove[1]].Y == randAlp[j].Y) {
							answer[now][ToMove[1]].X -= 35;
							if (player.left == 35 * 22)
								player.left = 35;
							else
								player.left -= 35;
							player.right = player.left + 35;
							break;
						}
						else if (answer[now][ToMove[0]].X == answer[now][ToMove[1]].X && answer[now][ToMove[0]].Y == answer[now][ToMove[1]].Y) {
							answer[now][ToMove[1]].X -= 35;
							if (player.left == 35 * 22)
								player.left = 35;
							else
								player.left -= 35;
							player.right = player.left + 35;
							break;
						}
					}
				}
			}
			else if (wParam == 'q' || wParam == 'Q') {
				PostQuitMessage(0);
				break;
			}
		}
		InvalidateRect(hWnd, NULL, true);
		ReleaseDC(hWnd, hDC);
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);

		//MAP----------------------------------------------------------------
		for (int j = 0; j < 20; ++j) {
			for (int i = 0; i < 21; ++i)
				Rectangle(hDC, 35 * (i + 1), 25 * (j + 1), 35 * (i + 2), 25 * (j + 2));
		}
		{
			hPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 255)); // 새로운 객체 만들기: 펜
			oldPen = (HPEN)SelectObject(hDC, hPen);
			hBrush = (HBRUSH)GetStockObject(HOLLOW_BRUSH); // 윈도우가 제공하는 객체 가져오기
			oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

			Rectangle(hDC, answerR.left, answerR.top, answerR.right, answerR.bottom);

			SelectObject(hDC, oldPen);
			DeleteObject(hPen);
			SelectObject(hDC, oldBrush);
		}
		//-------------------------------------------------------------------
		for (int i = 0; i < 5; ++i) {
			static TCHAR PrintText[1];
			RECT printRect = { answer[now][i].X, answer[now][i].Y,answer[now][i].X + 35, answer[now][i].Y + 25 };
			wsprintf(PrintText, TEXT("%c"), answer[now][i].A);
			DrawText(hDC, PrintText, 1, &printRect, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
		}
		for (int i = 0; i < 10; ++i) {
			static TCHAR PrintText[1];
			RECT printRect = { randAlp[i].X, randAlp[i].Y,randAlp[i].X + 35, randAlp[i].Y + 25 };
			wsprintf(PrintText, TEXT("%c"), randAlp[i].A);
			DrawText(hDC, PrintText, 1, &printRect, DT_VCENTER | DT_CENTER | DT_SINGLELINE);
		}

		if (answer[now][ToMove[0]].Y == 25 * 3 && answer[now][ToMove[1]].Y == 25 * 3 && answer[now][ToMove[0]].X == 35 * (9 + ToMove[0]) && answer[now][ToMove[1]].X == 35 * (9 + ToMove[1])) {
			static RECT rect = { 0,0,800,600 };
			DrawText(hDC, _T("You Win!"), _tcslen(_T("You Win!")), &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			Return = 1;
		}

		hPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 255)); // 새로운 객체 만들기: 펜
		oldPen = (HPEN)SelectObject(hDC, hPen);
		hBrush = CreateSolidBrush(RGB(225, 225, 0)); // 윈도우가 제공하는 객체 가져오기
		oldBrush = (HBRUSH)SelectObject(hDC, hBrush);

		Ellipse(hDC, player.left, player.top, player.right, player.bottom);

		SelectObject(hDC, oldPen);
		DeleteObject(hPen);
		SelectObject(hDC, oldBrush);
		DeleteObject(hBrush);

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
