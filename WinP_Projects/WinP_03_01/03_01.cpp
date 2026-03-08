#include <windows.h>
#include <winuser.h>
#include <math.h>
#include <time.h>
#include <tchar.h>
#include <cstdlib>
#define BSIZE 30
HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Programming 03-01";
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);
float LengthPts(int X1, int Y1, int X2, int Y2)
{
	return (sqrt((X2 - X1) * (X2 - X1) + (Y2 - Y1) * (Y2 - Y1)));
}
BOOL InCircle(int X1, int Y1, int X2, int Y2) {
	if (LengthPts(X1, Y1, X2, Y2) < BSIZE)
		return TRUE;
	else
		return FALSE;
}
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
	hWnd = CreateWindow(lpszClass, lpszWindowName, WS_OVERLAPPEDWINDOW, 0, 0, 800, 800, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&Message, 0, 0, 0)) {
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return Message.wParam;
}
struct block {
	int Shape, x, y;
	COLORREF color;
	int front, back, Mod;
};
struct STOP {
	RECT rect;
	COLORREF color;
	BOOL Selection;
};
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hDC, mDC;
	HBITMAP hBitmap;
	static RECT rectView, range[20];
	static block back_up[21];
	static block player;
	static block fee[20];
	static STOP stop[20];
	static int cheakX, cheakY;
	static int speed, tail, size;
	static int playerX, Cheak;

	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;

	switch (uMsg) {
	case WM_CREATE:
		back_up[0].Mod = 0;
		Cheak = 1;
		GetClientRect(hWnd, &rectView);
		player.Shape = 0;
		player.x = 0;
		player.y = 0;
		player.color = RGB(0, 0, 255);
		player.Mod = 4;
		player.back = 21;
		speed = 100;
		srand(time(NULL));
		for (int i = 0; i < 20; ++i) {
			fee[i].Shape = 1;
			fee[i].x = rand() % 40;
			fee[i].y = rand() % 40;
			fee[i].color = RGB(rand() % 255, rand() % 255, rand() % 255);
			fee[i].front = i;
			fee[i].back = i;
			fee[i].Mod = 4;
			if (fee[i].y == player.y && fee[i].x == player.x)
				i--;
			else {
				for (int j = 0; j < i; ++j) {
					if (fee[i].x == fee[j].x && fee[i].y == fee[j].y) {
						i--;
						break;
					}
				}
			}
		}
		break;
	case WM_LBUTTONDOWN:
		cheakX = LOWORD(lParam);
		cheakY = HIWORD(lParam);

		if (player.back == 21);
		else {
			for (int i = player.back; ; i = fee[i].back) {
				if (i == fee[i].back) {
					tail = i;
					break;
				}
			}
		}

		if (InCircle(player.x * rectView.right / 40, player.y * rectView.bottom / 40, cheakX, cheakY)) {
			SetTimer(hWnd, 3, speed, NULL);
		}
		else if (InCircle(fee[tail].x * rectView.right / 40, fee[tail].y * rectView.bottom / 40, cheakX, cheakY)) {
			if (fee[tail].front == 20) {
				player.back = 21;
			}
			else
				fee[fee[tail].front].back = fee[tail].front;
			fee[tail].front = tail;
			fee[tail].Mod = rand() % 4 + 1;
			if (fee[tail].Mod == 3) {
				if (fee[tail].x < 20) {
					range[tail].left = fee[tail].x;
					range[tail].right = 39 - fee[tail].x;
				}
				else {
					range[tail].left = 39 - fee[tail].x;
					range[tail].right = fee[tail].x;
				}
				if (fee[tail].y < 20) {
					range[tail].top = fee[tail].y;
					range[tail].bottom = 39 - fee[tail].y;
				}
				else {
					range[tail].top = 39 - fee[tail].y;
					range[tail].bottom = fee[tail].y;
				}
			}
		}
		else {
			if (player.Mod == 1) {
				if (player.y < cheakY) {
					if (player.x % 2 == 1) {		//홀수 줄
						player.y -= 1;
					}
				}
				else {
					if (player.x % 2 == 0) {	//짝수 줄
						player.y += 1;
					}
				}
				player.Mod = 2;
			}
			else if (player.Mod == 2) {
				if (player.x < cheakX) {
					if (player.y % 2) {		//홀수 줄
						player.x -= 1;
					}
				}
				else {
					if (player.y % 2 == 0) {	//짝수 줄
						player.x += 1;
					}
				}
				player.Mod = 1;
			}
			if (player.back == 21);
			else {
				for (int i = player.back; ; i = fee[i].back) {
					fee[i].Mod = player.Mod;
					if (i == fee[i].back)
						break;
				}
			}
		}


		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_RBUTTONDOWN:
		cheakX = LOWORD(lParam);
		cheakY = HIWORD(lParam);
		for (int i = 0; i < 40; ++i) {
			if (i * rectView.right / 40 > cheakX) {
				for (int j = 0; j < 40; ++j) {
					if (j * rectView.bottom / 40 > cheakY) {
						for (int a = 0; a < 20; ++a) {
							if (stop[a].Selection == 0) {
								stop[a].rect.top = j;
								stop[a].rect.left = i;
								stop[a].rect.bottom = j + 1;
								stop[a].rect.right = i + 1;
								stop[a].color = RGB(rand() % 255, rand() % 255, rand() % 255);
								stop[a].Selection = 1;
								break;
							}
							InvalidateRect(hWnd, NULL, FALSE);
						}
						break;
					}
					else;
				}
				break;
			}
		}

		break;
	case WM_KEYDOWN:
		hDC = GetDC(hWnd);

		if (wParam == VK_UP) {
			if (player.y == 0);
			else
				player.y -= 1;;
			player.Mod = 2;
		}
		else if (wParam == VK_LEFT) {
			if (player.x == 0);
			else
				player.x -= 1;
			player.Mod = 1;
		}
		else if (wParam == VK_DOWN) {
			if (player.y == 39);
			else
				player.y += 1;
			player.Mod = 2;
		}
		else if (wParam == VK_RIGHT) {
			if (player.x == 39);
			else
				player.x += 1;
			player.Mod = 1;
		}
		if (player.back == 21);
		else {
			for (int i = player.back; ; i = fee[i].back) {
				fee[i].Mod = player.Mod;
				if (i == fee[i].back)
					break;
			}
		}

		InvalidateRect(hWnd, NULL, FALSE);
		ReleaseDC(hWnd, hDC);
		break;
	case WM_CHAR:
		hDC = GetDC(hWnd);

		if (wParam == 's') {				// start
			player.Mod = 1;
			SetTimer(hWnd, 0, speed, NULL);
			SetTimer(hWnd, 1, 500, NULL);
		}
		else if (wParam == '+') {			// speed-up
			KillTimer(hWnd, 0);
			if (speed == 100);
			else
				speed -= 100;
			SetTimer(hWnd, 0, speed, NULL);
		}
		else if (wParam == '-') {			// speed-down
			KillTimer(hWnd, 0);
			if (speed == 5000);
			else
				speed += 100;
			SetTimer(hWnd, 0, speed, NULL);
		}
		else if (wParam == 'j') {			// jump
			if (player.Mod == 1) {
				if (player.x + 1 == 40 && player.y + 1 == 40) {
					player.x = 0;
					player.y = 0;
				}
				if (player.y % 2 == 0) {
					if (player.x == 39)
						player.y += 1;
					else
						player.x += 1;
				}
				else {
					if (player.x == 0)
						player.y += 1;
					else
						player.x -= 1;
				}
				player.Mod = 2;
			}
			else if (player.Mod == 2) {
				if (player.x == 39 && player.y == 39) {
					player.x = 0;
					player.y = 0;
				}
				if (player.x % 2 == 0) {
					if (player.y == 39)
						player.x += 1;
					else
						player.y += 1;
				}
				else {
					if (player.y == 0)
						player.x += 1;
					else
						player.y -= 1;
				}
				for (int i = 0; i < 20; ++i) {
					if (fee[i].x == player.x && fee[i].y == player.y) {
						if (fee[i].Shape == 1) {
							fee[i].Shape = 0;
							fee[i].Mod = rand() % 4 + 1;
							if (fee[i].Mod == 3) {
								if (fee[i].x < 20) {
									range[i].left = fee[i].x;
									range[i].right = 39 - fee[i].x;
								}
								else {
									range[i].left = 39 - fee[i].x;
									range[i].right = fee[i].x;
								}
								if (fee[i].y < 20) {
									range[i].top = fee[i].y;
									range[i].bottom = 39 - fee[i].y;
								}
								else {
									range[i].top = 39 - fee[i].y;
									range[i].bottom = fee[i].y;
								}
							}
						}
						else {
							fee[i].Mod = player.Mod;
							if (player.back == 21) {
								player.back = i;
								fee[i].front = 20;
							}
							else {
								for (int j = player.back; ; j = fee[j].back) {
									if (j == fee[j].back) {
										fee[j].back = i;
										if (fee[i].front == i && fee[i].back == i);
										else if (fee[i].front != i && fee[i].back != i) {
											fee[fee[i].back].front = fee[i].front;
											fee[fee[i].front].back = fee[i].back;
										}
										else if (fee[i].front == i) {
											fee[fee[i].back].front = fee[i].back;
										}
										else if (fee[i].back == i) {
											fee[fee[i].front].back = fee[i].front;
										}
										fee[i].front = j;
										fee[i].back = i;
										break;
									}
								}
							}
						}
						break;
					}
				}
				player.Mod = 1;
			}
			if (player.back == 21);
			else {
				for (int i = player.back; ; i = fee[i].back) {
					fee[i].Mod = player.Mod;
					if (i == fee[i].back)
						break;
				}
			}
		}
		else if (wParam == 't') {			// tail
			if (player.back == 21);
			else {
				COLORREF BackupColor = player.color;
				player.color = fee[player.back].color;
				for (int i = player.back; ; i = fee[i].back) {
					fee[i].color = fee[fee[i].back].color;
					if (i == fee[i].back) {
						fee[i].color = BackupColor;
						break;
					}
				}
			}
		}
		else if (wParam == 'a') {
			//back_up
			for (int i = 0; i < 20; ++i) {
				back_up[i].Shape = fee[i].Shape;
				back_up[i].x = fee[i].x;
				back_up[i].y = fee[i].y;
				back_up[i].color = fee[i].color;
				back_up[i].front = fee[i].front;
				back_up[i].back = fee[i].back;
				back_up[i].Mod = fee[i].Mod;
			}
			back_up[20].Shape = player.Shape;
			back_up[20].x = player.x;
			back_up[20].y = player.y;
			back_up[20].color = player.color;
			back_up[20].front = player.front;
			back_up[20].back = player.back;
			back_up[20].Mod = player.Mod;
			KillTimer(hWnd, 0);
			KillTimer(hWnd, 1);

			player.back = 21;
			//꼬리로 붙이기
			for (int i = 0; i < 20; ++i) {
				if (fee[i].Shape == 1);
				else {
					if (player.back == 21) {
						player.back = i;
						fee[i].front = 20;
						fee[i].back = i;
					}
					else {
						for (int j = 0; j < i; ++j) {
							if (fee[j].back == j && fee[j].Shape == 0) {
								fee[j].back = i;
								fee[i].front = j;
								fee[i].back = i;
							}
						}
					}
				}
			}
			SetTimer(hWnd, 0, 50, NULL);
		}
		else if (wParam == 'q') {							// 프로그램 종료
			PostQuitMessage(0);
			break;
		}

		InvalidateRect(hWnd, NULL, FALSE);
		ReleaseDC(hWnd, hDC);
		break;
	case WM_TIMER:
		switch (wParam) {
		case 0:			// player 그룹
			if (player.Mod == 1) {
				if (player.x == 0 && player.y + 1 == 40) {
					player.x = 0;
					player.y = 0;
				}
				if (player.y % 2 == 0) {
					if (player.x == 39)
						player.y += 1;
					else
						player.x += 1;
				}
				else {
					if (player.x == 0)
						player.y += 1;
					else
						player.x -= 1;
				}
			}
			else if (player.Mod == 2) {
				if (player.x == 39 && player.y == 0) {
					player.x = 0;
					player.y = 0;
				}
				if (player.x % 2 == 0) {
					if (player.y == 39)
						player.x += 1;
					else
						player.y += 1;
				}
				else {
					if (player.y == 0)
						player.x += 1;
					else
						player.y -= 1;
				}
			}
			// 장애물
			if (back_up[0].Mod == 0) {
				for (int i = 0; i < 20; ++i) {
					if (player.x == stop[i].rect.left && player.y == stop[i].rect.top) {
						if (player.Mod == 1) {
							if (player.x == 0 && player.y == 0) {
								player.x = 0;
								player.y = 39;
							}
							if (player.y % 2 == 0) {
								if (player.x == 0)
									player.y -= 1;
								else
									player.x -= 1;
							}
							else {
								if (player.x == 39)
									player.y -= 1;
								else
									player.x += 1;
							}
							player.Mod = 2;
						}
						else if (player.Mod == 2) {
							if (player.x == 0 && player.y == 0) {
								player.x = 39;
								player.y = 0;
							}
							if (player.x % 2 == 0) {
								if (player.y == 0)
									player.x -= 1;
								else
									player.y -= 1;
							}
							else {
								if (player.y == 39)
									player.x -= 1;
								else
									player.y += 1;
							}
							player.Mod = 1;
						}
						if (player.back == 21);
						else {
							for (int i = player.back; ; i = fee[i].back) {
								fee[i].Mod = player.Mod;
								if (i == fee[i].back)
									break;
							}
						}
						break;
					}
				}
			}
			for (int i = 0; i < 20; ++i) {
				//player와
				if (fee[i].x == player.x && fee[i].y == player.y) {
					if (fee[i].Shape == 1) {
						fee[i].Shape = 0;
						fee[i].Mod = rand() % 4 + 1;
						while (fee[i].Mod == player.Mod)
							fee[i].Mod = rand() % 4 + 1;
						if (fee[i].Mod == 3) {
							if (fee[i].x < 20) {
								range[i].left = fee[i].x;
								range[i].right = 39 - fee[i].x;
							}
							else {
								range[i].left = 39 - fee[i].x;
								range[i].right = fee[i].x;
							}
							if (fee[i].y < 20) {
								range[i].top = fee[i].y;
								range[i].bottom = 39 - fee[i].y;
							}
							else {
								range[i].top = 39 - fee[i].y;
								range[i].bottom = fee[i].y;
							}
						}
						//한번 움직이기
						if (player.Mod != fee[i].Shape) {
							if (fee[i].Mod == 1) {
								if (fee[i].x == 0 && fee[i].y + 1 == 40) {
									fee[i].x = 0;
									fee[i].y = 0;
								}
								if (fee[i].y % 2 == 0) {
									if (fee[i].x == 39)
										fee[i].y += 1;
									else
										fee[i].x += 1;
								}
								else {
									if (fee[i].x == 0)
										fee[i].y += 1;
									else
										fee[i].x -= 1;
								}
							}
							else if (fee[i].Mod == 2) {
								if (fee[i].x + 1 == 40 && fee[i].y == 0) {
									fee[i].x = 0;
									fee[i].y = 0;
								}
								if (fee[i].x % 2 == 0) {
									if (fee[i].y == 39)
										fee[i].x += 1;
									else
										fee[i].y += 1;
								}
								else {
									if (fee[i].y == 0)
										fee[i].x += 1;
									else
										fee[i].y -= 1;
								}
							}
						}
						break;
					}
					else {
						fee[i].Mod = player.Mod;
						if (player.back == 21) {
							player.back = i;
							if (fee[i].front != i) {
								if (fee[i].back == i) {
									fee[fee[i].front].back = fee[i].front;
								}
								else
									fee[fee[i].front].back = fee[i].back;
							}
							fee[i].front = 20;
						}
						else {
							fee[i].Mod = player.Mod;
							if (player.back == 21) {
								player.back = i;
								if (fee[i].front != i) {
									if (fee[i].back == i) {
										fee[fee[i].front].back = fee[i].front;
									}
									else
										fee[fee[i].front].back = fee[i].back;
								}
								fee[i].front = 20;
							}
							else {
								for (int j = player.back; ; j = fee[j].back) {
									if (j == fee[j].back) {
										fee[j].back = i;
										if (fee[i].front == i);
										else {
											fee[fee[i].front].back = fee[i].front;
										}
										fee[i].front = j;
										break;
									}
								}
							}
						}
					}
				}
			}
			// player follow 이동
			if (player.back == 21);
			else {
				for (int i = player.back; ; i = fee[i].back) {
					// player
					if (fee[i].front == 20) {
						if (player.Mod == 1) {
							if (player.x == 0 && player.y == 0) {
								fee[i].x = 0;
								fee[i].y = 39;
							}
							if (player.y % 2 == 0) {
								if (player.x == 0) {
									fee[i].y = player.y - 1;
									fee[i].x = player.x;
								}
								else {
									fee[i].x = player.x - 1;
									fee[i].y = player.y;
								}
							}
							else {
								if (player.x == 39) {
									fee[i].y = player.y - 1;
									fee[i].x = player.x;
								}
								else {
									fee[i].x = player.x + 1;
									fee[i].y = player.y;
								}
							}
						}
						else if (player.Mod == 2) {
							if (player.x == 0 && player.y == 0) {
								fee[i].x = 39;
								fee[i].y = 0;
							}
							if (player.x % 2 == 0) {
								if (player.y == 0) {
									fee[i].x = player.x - 1;
									fee[i].y = player.y;
								}
								else {
									fee[i].y = player.y - 1;
									fee[i].x = player.x;
								}
							}
							else {
								if (player.y == 39) {
									fee[i].y = player.y;
									fee[i].x = player.x - 1;
								}
								else {
									fee[i].y = player.y + 1;
									fee[i].x = player.x;
								}
							}
						}
					}
					// fee[i].front의 follow
					else {
						if (player.Mod == 1) {
							if (fee[fee[i].front].x == 0 && fee[fee[i].front].y == 0) {
								fee[i].x = 0;
								fee[i].y = 39;
							}
							if (fee[fee[i].front].y % 2 == 0) {
								if (fee[fee[i].front].x == 0) {
									fee[i].y = fee[fee[i].front].y - 1;
									fee[i].x = fee[fee[i].front].x;
								}
								else {
									fee[i].x = fee[fee[i].front].x - 1;
									fee[i].y = fee[fee[i].front].y;
								}
							}
							else {
								if (fee[fee[i].front].x == 39) {
									fee[i].y = fee[fee[i].front].y - 1;
									fee[i].x = fee[fee[i].front].x;
								}
								else {
									fee[i].x = fee[fee[i].front].x + 1;
									fee[i].y = fee[fee[i].front].y;
								}
							}
						}
						else if (player.Mod == 2) {
							if (fee[fee[i].front].x == 0 && fee[fee[i].front].y == 0) {
								fee[i].x = 39;
								fee[i].y = 0;
							}
							if (fee[fee[i].front].x % 2 == 0) {
								if (fee[fee[i].front].y == 0) {
									fee[i].x = fee[fee[i].front].x - 1;
									fee[i].y = fee[fee[i].front].y;
								}
								else {
									fee[i].y = fee[fee[i].front].y - 1;
									fee[i].x = fee[fee[i].front].x;
								}
							}
							else {
								if (fee[fee[i].front].y == 39) {
									fee[i].y = fee[fee[i].front].y;
									fee[i].x = fee[fee[i].front].x - 1;
								}
								else {
									fee[i].y = fee[fee[i].front].y + 1;
									fee[i].x = fee[fee[i].front].x;
								}
							}
						}
					}
					if (fee[i].back == i)
						break;
				}
			}

			// 겹치면
			//for (int i = 0; i < 20; ++i) {
			//	//player와
			//	if (fee[i].x == player.x && fee[i].y == player.y) {
			//		if (fee[i].Shape == 1) {
			//			fee[i].Shape = 0;
			//			fee[i].Mod = rand() % 4 + 1;
			//			while (fee[i].Mod == player.Mod)
			//				fee[i].Mod = rand() % 4 + 1;
			//			if (fee[i].Mod == 3) {
			//				if (fee[i].x < 20) {
			//					range[i].left = fee[i].x;
			//					range[i].right = 39 - fee[i].x;
			//				}
			//				else {
			//					range[i].left = 39 - fee[i].x;
			//					range[i].right = fee[i].x;
			//				}
			//				if (fee[i].y < 20) {
			//					range[i].top = fee[i].y;
			//					range[i].bottom = 39 - fee[i].y;
			//				}
			//				else {
			//					range[i].top = 39 - fee[i].y;
			//					range[i].bottom = fee[i].y;
			//				}
			//			}
			//			break;
			//		}
			//		else {
			//			fee[i].Mod = player.Mod;
			//			if (player.back == 21) {
			//				player.back = i;
			//				if (fee[i].front != i) {
			//					if (fee[i].back == i) {
			//						fee[fee[i].front].back = fee[i].front;
			//					}
			//					else
			//						fee[fee[i].front].back = fee[i].back;
			//				}
			//				fee[i].front = 20;
			//			}
			//			else {
			//				fee[i].Mod = player.Mod;
			//				if (player.back == 21) {
			//					player.back = i;
			//					if (fee[i].front != i) {
			//						if (fee[i].back == i) {
			//							fee[fee[i].front].back = fee[i].front;
			//						}
			//						else
			//							fee[fee[i].front].back = fee[i].back;
			//					}
			//					fee[i].front = 20;
			//				}
			//				else {
			//					for (int j = player.back; ; j = fee[j].back) {
			//						if (j == fee[j].back) {
			//							fee[j].back = i;
			//							if (fee[i].front == i);
			//							else {
			//								fee[fee[i].front].back = fee[i].front;
			//							}
			//							fee[i].front = j;
			//							break;
			//						}
			//					}
			//				}
			//			}
			//		}
			//	}
			//}
			for (int i = 0; i < 20; ++i) {
				//그 외
				if (fee[i].Shape == 0) {
					for (int j = 0; j < 20; ++j) {
						if (i == j);
						else if (fee[i].back == j || fee[i].front == j);
						else if (fee[j].Shape == 0 && fee[i].x == fee[j].x && fee[i].y == fee[j].y) {
							// Mod 조정
							if (fee[i].Mod == 4)
								fee[i].Mod = rand() % 3 + 1;
							if (fee[i].Mod == 3) {
								if (fee[i].x < 20) {
									range[i].left = fee[i].x;
									range[i].right = 39 - fee[i].x;
								}
								else {
									range[i].left = 39 - fee[i].x;
									range[i].right = fee[i].x;
								}
								if (fee[i].y < 20) {
									range[i].top = fee[i].y;
									range[i].bottom = 39 - fee[i].y;
								}
								else {
									range[i].top = 39 - fee[i].y;
									range[i].bottom = fee[i].y;
								}
							}
							fee[j].Mod = fee[i].Mod;
							if (fee[j].Mod == 3) {
								if (fee[j].x < 20) {
									range[j].left = fee[j].x;
									range[j].right = 39 - fee[j].x;
								}
								else {
									range[j].left = 39 - fee[j].x;
									range[j].right = fee[j].x;
								}
								if (fee[j].y < 20) {
									range[j].top = fee[j].y;
									range[j].bottom = 39 - fee[j].y;
								}
								else {
									range[j].top = 39 - fee[j].y;
									range[j].bottom = fee[j].y;
								}
							}
							// i 앞 뒤 조정
							if (fee[i].front == i && fee[i].back == i);
							else if (fee[i].front != i && fee[i].back != i) {
								if (fee[i].front == 20) {
									player.back = fee[i].back;
								}
								else {
									fee[fee[i].front].back = fee[i].back;
								}
								fee[fee[i].back].front = fee[i].front;
							}
							else if (fee[i].front == i)
								fee[fee[i].back].front = fee[i].back;
							else if (fee[i].back == i) {
								if (fee[i].front == 20)
									player.back = 21;
								else
									fee[fee[i].front].back = fee[i].front;
							}
							// j 앞 뒤 조정
							if (fee[j].front == j && fee[j].back == j);
							else if (fee[j].front != j && fee[j].back != j) {
								fee[fee[j].back].front = fee[j].front;
								if (fee[j].front == 20)
									player.back = fee[j].back;
								else
									fee[fee[j].front].back = fee[j].back;
							}
							else if (fee[j].front == j)
								fee[fee[j].back].front = fee[j].back;
							else if (fee[j].back == j) {
								if (fee[j].front == 20)
									player.back = 21;
								else
									fee[fee[j].front].back = fee[j].front;
							}
							// 합치기
							fee[i].front = i;
							fee[i].back = j;
							fee[j].front = i;
							fee[j].back = j;
							break;
						}
					}
				}
			}
			for (int i = 0; i < 20; ++i) {
				//player와
				if (fee[i].x == player.x && fee[i].y == player.y) {
					if (fee[i].Shape == 1) {
						fee[i].Shape = 0;
						fee[i].Mod = rand() % 4 + 1;
						while (fee[i].Mod == player.Mod)
							fee[i].Mod = rand() % 4 + 1;
						if (fee[i].Mod == 3) {
							if (fee[i].x < 20) {
								range[i].left = fee[i].x;
								range[i].right = 39 - fee[i].x;
							}
							else {
								range[i].left = 39 - fee[i].x;
								range[i].right = fee[i].x;
							}
							if (fee[i].y < 20) {
								range[i].top = fee[i].y;
								range[i].bottom = 39 - fee[i].y;
							}
							else {
								range[i].top = 39 - fee[i].y;
								range[i].bottom = fee[i].y;
							}
						}
						break;
					}
					else {
						fee[i].Mod = player.Mod;
						if (player.back == 21) {
							player.back = i;
							if (fee[i].front != i) {
								if (fee[i].back == i) {
									fee[fee[i].front].back = fee[i].front;
								}
								else
									fee[fee[i].front].back = fee[i].back;
							}
							fee[i].front = 20;
						}
						else {
							fee[i].Mod = player.Mod;
							if (player.back == 21) {
								player.back = i;
								if (fee[i].front != i) {
									if (fee[i].back == i) {
										fee[fee[i].front].back = fee[i].front;
									}
									else
										fee[fee[i].front].back = fee[i].back;
								}
								fee[i].front = 20;
							}
							else {
								for (int j = player.back; ; j = fee[j].back) {
									if (j == fee[j].back) {
										fee[j].back = i;
										if (fee[i].front == i);
										else {
											fee[fee[i].front].back = fee[i].front;
										}
										fee[i].front = j;
										break;
									}
								}
							}
						}
					}
				}
			}
			break;
		case 1:			// else
			for (int i = 0; i < 20; ++i) {
				if (player.back == i) {
					fee[i].front = 20;
				}
				else if (fee[i].Shape == 0 && fee[i].front == i) {
					if (fee[i].Mod == 1) {
						if (fee[i].x == 0 && fee[i].y + 1 == 40) {
							fee[i].x = 0;
							fee[i].y = 0;
						}
						if (fee[i].y % 2 == 0) {
							if (fee[i].x == 39)
								fee[i].y += 1;
							else
								fee[i].x += 1;
						}
						else {
							if (fee[i].x == 0)
								fee[i].y += 1;
							else
								fee[i].x -= 1;
						}
					}
					else if (fee[i].Mod == 2) {
						if (fee[i].x + 1 == 40 && fee[i].y == 0) {
							fee[i].x = 0;
							fee[i].y = 0;
						}
						if (fee[i].x % 2 == 0) {
							if (fee[i].y == 39)
								fee[i].x += 1;
							else
								fee[i].y += 1;
						}
						else {
							if (fee[i].y == 0)
								fee[i].x += 1;
							else
								fee[i].y -= 1;
						}
					}
					else if (fee[i].Mod == 3) {
						if (fee[i].y == range[i].top) {
							if (fee[i].x == range[i].right)
								fee[i].y += 1;
							else
								fee[i].x += 1;
						}
						else if (fee[i].x == range[i].left)
							fee[i].y -= 1;
						else if (fee[i].y == range[i].bottom)
							fee[i].x -= 1;
						else
							fee[i].y += 1;
					}
					else if (fee[i].Mod == 4);
					// 장애물
					for (int j = 0; j < 20; ++j) {
						if (fee[i].x == stop[j].rect.left && fee[i].y == stop[j].rect.top) {
							if (fee[i].Mod == 1) {
								if (fee[i].x == 0 && fee[i].y == 0) {
									fee[i].x = 0;
									fee[i].y = 39;
								}
								if (fee[i].y % 2 == 0) {
									if (fee[i].x == 0)
										fee[i].y -= 1;
									else
										fee[i].x -= 1;
								}
								else {
									if (fee[i].x == 39)
										fee[i].y -= 1;
									else
										fee[i].x += 1;
								}
								fee[i].Mod = 2;
							}
							else if (fee[i].Mod == 2) {
								if (fee[i].x == 0 && fee[i].y == 0) {
									fee[i].x = 39;
									fee[i].y = 0;
								}
								if (fee[i].x % 2 == 0) {
									if (fee[i].y == 0)
										fee[i].x -= 1;
									else
										fee[i].y -= 1;
								}
								else {
									if (fee[i].y == 39)
										fee[i].x -= 1;
									else
										fee[i].y += 1;
								}
								fee[i].Mod = 1;
							}
							else if (fee[i].Mod == 3) {
								if (fee[i].y == range[i].top) {
									if (fee[i].x == range[i].left)
										fee[i].y -= 1;
									else
										fee[i].x -= 1;
								}
								else if (fee[i].x == range[i].right)
									fee[i].y -= 1;
								else if (fee[i].y == range[i].bottom)
									fee[i].x += 1;
								else
									fee[i].y += 1;
							}
							if (fee[j].back == j);
							else {
								for (int a = fee[i].back; ; a = fee[j].back) {
									fee[a].Mod = fee[i].Mod;
									if (a == fee[a].back)
										break;
								}
							}
							break;
						}
					}
					// follow들
					if (fee[i].back == i || fee[i].front == 20);
					else {
						for (int j = fee[i].back; ; j = fee[j].back) {
							// fee[i].front의 follow
							if (fee[j].front != j) {
								if (fee[j].Mod == 1) {
									if (fee[fee[j].front].x == 0 && fee[fee[j].front].y == 0) {
										fee[j].x = 0;
										fee[j].y = 39;
									}
									if (fee[fee[j].front].y % 2 == 0) {
										if (fee[fee[j].front].x == 0) {
											fee[j].y = fee[fee[j].front].y - 1;
											fee[j].x = fee[fee[j].front].x;
										}
										else {
											fee[j].y = fee[fee[j].front].y;
											fee[j].x = fee[fee[j].front].x - 1;
										}
									}
									else {
										if (fee[fee[j].front].x == 39) {
											fee[j].y = fee[fee[j].front].y - 1;
											fee[j].x = fee[fee[j].front].x;
										}
										else {
											fee[j].y = fee[fee[j].front].y;
											fee[j].x = fee[fee[j].front].x + 1;
										}
									}
								}
								else if (fee[j].Mod == 2) {
									if (fee[fee[j].front].x == 0 && fee[fee[j].front].y == 0) {
										fee[fee[j].front].x = 39;
										fee[fee[j].front].y = 0;
									}
									if (fee[fee[j].front].x % 2 == 0) {
										if (fee[fee[j].front].y == 0) {
											fee[j].x = fee[fee[j].front].x - 1;
											fee[j].y = fee[fee[j].front].y;
										}
										else {
											fee[j].y = fee[fee[j].front].y - 1;
											fee[j].x = fee[fee[j].front].x;
										}
									}
									else {
										if (fee[fee[j].front].y == 39) {
											fee[j].y = fee[fee[j].front].y;
											fee[j].x = fee[fee[j].front].x - 1;
										}
										else {
											fee[j].y = fee[fee[j].front].y + 1;
											fee[j].x = fee[fee[j].front].x;
										}
									}
								}
								else if (fee[j].Mod == 3) {
									if (fee[fee[j].front].y == range[fee[j].front].top) {
										if (fee[fee[j].front].x == range[fee[j].front].left) {
											fee[j].x = fee[fee[j].front].x;
											fee[j].y = fee[fee[j].front].y - 1;
										}
										else {
											fee[j].y = fee[fee[j].front].y;
											fee[j].x = fee[fee[j].front].x - 1;
										}
									}
									else if (fee[fee[j].front].x == range[fee[j].front].right) {
										fee[j].y = fee[fee[j].front].y - 1;
										fee[j].x = fee[fee[j].front].x;
									}
									else if (fee[fee[j].front].y == range[fee[j].front].bottom) {
										fee[j].y = fee[fee[j].front].y;
										fee[j].x = fee[fee[j].front].x + 1;
									}
									else {
										fee[j].y = fee[fee[j].front].y + 1;
										fee[j].x = fee[fee[j].front].x;
									}
								}
								else;
								if (fee[j].back == j)
									break;
							}
						}
					}
				}
			}

			// 겹치면
			for (int i = 0; i < 20; ++i) {
				//그 외
				if (fee[i].Shape == 0) {
					for (int j = 0; j < 20; ++j) {
						if (i == j);
						else if (fee[i].back == j || fee[i].front == j);
						else if (fee[j].Shape == 0 && fee[i].x == fee[j].x && fee[i].y == fee[j].y) {
							// Mod 조정
							fee[i].Mod = rand() % 3 + 1;
							if (fee[j].Mod == fee[i].Mod) {
								fee[i].Mod = rand() % 3 + 1;
							}
							if (fee[i].Mod == 3) {
								if (fee[i].x < 20) {
									range[i].left = fee[i].x;
									range[i].right = 39 - fee[i].x;
								}
								else {
									range[i].left = 39 - fee[i].x;
									range[i].right = fee[i].x;
								}
								if (fee[i].y < 20) {
									range[i].top = fee[i].y;
									range[i].bottom = 39 - fee[i].y;
								}
								else {
									range[i].top = 39 - fee[i].y;
									range[i].bottom = fee[i].y;
								}
							}
							fee[j].Mod = fee[i].Mod;
							if (fee[j].Mod == 3) {
								if (fee[j].x < 20) {
									range[j].left = fee[j].x;
									range[j].right = 39 - fee[j].x;
								}
								else {
									range[j].left = 39 - fee[j].x;
									range[j].right = fee[j].x;
								}
								if (fee[j].y < 20) {
									range[j].top = fee[j].y;
									range[j].bottom = 39 - fee[j].y;
								}
								else {
									range[j].top = 39 - fee[j].y;
									range[j].bottom = fee[j].y;
								}
							}
							// i 앞 뒤 조정
							if (fee[i].front == i && fee[i].back == i);
							else if (fee[i].front != i && fee[i].back != i) {
								if (fee[i].front == 20) {
									player.back = fee[i].back;
								}
								else {
									fee[fee[i].front].back = fee[i].back;
								}
								fee[fee[i].back].front = fee[i].front;
							}
							else if (fee[i].front == i)
								fee[fee[i].back].front = fee[i].back;
							else if (fee[i].back == i) {
								if (fee[i].front == 20)
									player.back = 21;
								else
									fee[fee[i].front].back = fee[i].front;
							}
							// j 앞 뒤 조정
							if (fee[j].front == j && fee[j].back == j);
							else if (fee[j].front != j && fee[j].back != j) {
								fee[fee[j].back].front = fee[j].front;
								if (fee[j].front == 20)
									player.back = fee[j].back;
								else
									fee[fee[j].front].back = fee[j].back;
							}
							else if (fee[j].front == j)
								fee[fee[j].back].front = fee[j].back;
							else if (fee[j].back == j) {
								if (fee[j].front == 20)
									player.back = 21;
								else
									fee[fee[j].front].back = fee[j].front;
							}
							// 합치기
							fee[i].front = i;
							fee[i].back = j;
							fee[j].front = i;
							fee[j].back = j;
							break;
						}
					}
				}
			}
			for (int i = 0; i < 20; ++i) {
				//player와
				if (fee[i].x == player.x && fee[i].y == player.y) {
					if (fee[i].Shape == 1) {
						fee[i].Shape = 0;
						fee[i].Mod = rand() % 4 + 1;
						while (fee[i].Mod == player.Mod)
							fee[i].Mod = rand() % 4 + 1;
						if (fee[i].Mod == 3) {
							if (fee[i].x < 20) {
								range[i].left = fee[i].x;
								range[i].right = 39 - fee[i].x;
							}
							else {
								range[i].left = 39 - fee[i].x;
								range[i].right = fee[i].x;
							}
							if (fee[i].y < 20) {
								range[i].top = fee[i].y;
								range[i].bottom = 39 - fee[i].y;
							}
							else {
								range[i].top = 39 - fee[i].y;
								range[i].bottom = fee[i].y;
							}
						}
						break;
					}
					else {
						fee[i].Mod = player.Mod;
						if (player.back == 21) {
							player.back = i;
							if (fee[i].front != i) {
								if (fee[i].back == i) {
									fee[fee[i].front].back = fee[i].front;
								}
								else
									fee[fee[i].front].back = fee[i].back;
							}
							fee[i].front = 20;
						}
						else {
							for (int j = player.back; ; j = fee[j].back) {
								if (j == fee[j].back) {
									fee[j].back = i;
									if (fee[i].front == i);
									else {
										fee[fee[i].front].back = fee[i].front;
									}
									fee[i].front = j;
									break;
								}
							}
						}
					}
				}
			}
			break;
		case 3:
			size += 5;
			break;
		}

		InvalidateRect(hWnd, NULL, FALSE);
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		mDC = CreateCompatibleDC(hDC);
		hBitmap = CreateCompatibleBitmap(hDC, rectView.right, rectView.bottom);
		SelectObject(mDC, (HBITMAP)hBitmap);


		//MAP----------------------------------------------------------------
		for (int j = 0; j < 40; ++j) {
			for (int i = 0; i < 40; ++i)
				Rectangle(mDC, i * rectView.right / 40, j * rectView.bottom / 40, (i + 1) * rectView.right / 40, (j + 1) * rectView.bottom / 40);
		}
		//MAP----------------------------------------------------------------
		//Block--------------------------------------------------------------
		for (int i = 0; i < 20; ++i) {

			hPen = (HPEN)GetStockObject(NULL_PEN); // 새로운 객체 만들기: 펜
			oldPen = (HPEN)SelectObject(mDC, hPen);
			hBrush = CreateSolidBrush(fee[i].color);
			oldBrush = (HBRUSH)SelectObject(mDC, hBrush);

			if (fee[i].Shape == 1)
				Rectangle(mDC, fee[i].x * rectView.right / 40 + 5, fee[i].y * rectView.bottom / 40 + 5, (fee[i].x + 1) * rectView.right / 40 - 5, (fee[i].y + 1) * rectView.bottom / 40 - 5);
			else
				Ellipse(mDC, fee[i].x * rectView.right / 40, fee[i].y * rectView.bottom / 40, (fee[i].x + 1) * rectView.right / 40, (fee[i].y + 1) * rectView.bottom / 40);

			SelectObject(mDC, oldPen);
			DeleteObject(hPen);
			SelectObject(mDC, oldBrush);
			DeleteObject(hBrush);
		}
		//Block--------------------------------------------------------------
		//player-------------------------------------------------------------
		hPen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0)); // 새로운 객체 만들기: 펜
		oldPen = (HPEN)SelectObject(mDC, hPen);
		hBrush = CreateSolidBrush(player.color);
		oldBrush = (HBRUSH)SelectObject(mDC, hBrush);

		Ellipse(mDC, player.x * rectView.right / 40 + size, player.y * rectView.bottom / 40 + size, (player.x + 1) * rectView.right / 40 - size, (player.y + 1) * rectView.bottom / 40 - size);

		SelectObject(mDC, oldPen);
		DeleteObject(hPen);
		SelectObject(mDC, oldBrush);
		DeleteObject(hBrush);
		//player-------------------------------------------------------------
		//STOP---------------------------------------------------------------
		for (int i = 0; i < 20; ++i) {

			hPen = (HPEN)GetStockObject(BLACK_PEN); // 새로운 객체 만들기: 펜
			oldPen = (HPEN)SelectObject(mDC, hPen);
			hBrush = CreateSolidBrush(stop[i].color);
			oldBrush = (HBRUSH)SelectObject(mDC, hBrush);

			if (stop[i].Selection)
				Rectangle(mDC, stop[i].rect.left * rectView.right / 40, stop[i].rect.top * rectView.bottom / 40, stop[i].rect.right * rectView.right / 40, stop[i].rect.bottom * rectView.bottom / 40);

			SelectObject(mDC, oldPen);
			DeleteObject(hPen);
			SelectObject(mDC, oldBrush);
			DeleteObject(hBrush);
		}
		//STOP---------------------------------------------------------------
		if (size == 15) {
			size = 0;
			KillTimer(hWnd, 3);
		}

		if (back_up[0].Mod != 0) {
			if ((player.Mod == 1 && player.x == 0 && player.y == 39) || (player.Mod == 2 && player.x == 39 && player.y == 0)) {
				for (int i = 0; i < 20; ++i) {
					fee[i].Shape = back_up[i].Shape;
					fee[i].x = back_up[i].x;
					fee[i].y = back_up[i].y;
					fee[i].color = back_up[i].color;
					fee[i].front = back_up[i].front;
					fee[i].back = back_up[i].back;
					fee[i].Mod = back_up[i].Mod;
				}
				player.Shape = back_up[20].Shape;
				player.x = back_up[20].x;
				player.y = back_up[20].y;
				player.color = back_up[20].color;
				player.front = back_up[20].front;
				player.back = back_up[20].back;
				player.Mod = back_up[20].Mod;
				KillTimer(hWnd, 0);

				SetTimer(hWnd, 0, speed, NULL);
				SetTimer(hWnd, 1, 500, NULL);
				back_up[0].Mod = 0;
			}
		}
		BitBlt(hDC, 0, 0, rectView.right, rectView.bottom, mDC, 0, 0, SRCCOPY);

		DeleteDC(mDC);
		DeleteObject(hBitmap);

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		KillTimer(hWnd, 0);
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
