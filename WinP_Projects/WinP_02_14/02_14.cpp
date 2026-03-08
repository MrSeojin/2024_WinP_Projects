#include <windows.h>
#include <winuser.h>
#include <tchar.h>
#include <time.h>
#include <cstdlib>
HINSTANCE g_hInst;
LPCTSTR lpszClass = L"Window Class Name";
LPCTSTR lpszWindowName = L"Window Programming 2-14";
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
	struct NumAlp {
		int print;
		RECT rect;
		int Cheak;
	};
	static RECT player;
	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;
	static int Mod;

	static NumAlp num[10];
	static NumAlp alp[26];

	switch (uMsg) {
	case WM_CREATE:
		Mod = 3;

		player = { 40, 30, 85, 75 };
		srand(time(NULL));
		for (int i = 0; i < 10; ++i) {
			num[i].print = i;
			num[i].rect.left = (rand() % 20 * 45) + 40;
			num[i].rect.top = (rand() % 20 * 45) + 30;
			num[i].rect.right = num[i].rect.left + 45;
			num[i].rect.bottom = num[i].rect.top + 45;
			num[i].Cheak = 1;
			if (num[i].rect.top == player.top && num[i].rect.left == player.left)
				i--;
			else {
				for (int j = 0; j < i; ++j) {
					if (num[i].rect.top == num[j].rect.top && num[i].rect.left == num[j].rect.left) {
						i--;
						break;
					}
				}
			}
		}
		for (int i = 0; i < 26; ++i) {
			alp[i].print = i + 97;
			alp[i].rect.left = (rand() % 20 * 45) + 40;
			alp[i].rect.top = (rand() % 20 * 45) + 30;
			alp[i].rect.right = alp[i].rect.left + 45;
			alp[i].rect.bottom = alp[i].rect.top + 45;
			alp[i].Cheak = 1;
			if (player.top == alp[i].rect.top && player.left == alp[i].rect.left)
				i--;
			else {
				for (int j = 0; j < 10; ++j) {
					if (alp[i].rect.left == num[j].rect.left && alp[i].rect.top == num[j].rect.top) {
						i--;
						break;
					}
				}
				for (int j = 0; j < i; ++j) {
					if (alp[i].rect.left == alp[j].rect.left && alp[i].rect.top == alp[j].rect.top) {
						i--;
						break;
					}
				}
			}
		}
		break;
	case WM_CHAR:
		hDC = GetDC(hWnd);

		if (wParam == '1')									// 모드 1
			Mod = 1;
		else if (wParam == '2')								// 모드 2
			Mod = 2;
		else if (wParam == '3') 							// 모드 3
			Mod = 3;
		else if (wParam == 'w') {							// 상

			// player 이동
			if (player.top == 30) {
				player.bottom = 930;
				player.top = 885;
			}
			else {
				player.bottom -= 45;
				player.top -= 45;
			}

			// num[i]
			for (int i = 0; i < 10; ++i) {
				if (num[i].Cheak == 0);
				else {
					if (num[i].rect.top == player.top && num[i].rect.left == player.left) {
						if (num[i].rect.top == 30) {
							num[i].rect.bottom = 930;
							num[i].rect.top = 885;
						}
						else {
							num[i].rect.bottom -= 45;
							num[i].rect.top -= 45;
						}
						// num->num
						for (int j = 0; j < 10; ++j) {
							if (num[j].Cheak == 0 || i == j);
							else {
								if (num[i].rect.top == num[j].rect.top && num[i].rect.left == num[j].rect.left) {
									if (Mod == 1 || Mod == 3) {
										num[j].print += num[i].print;
										if (num[j].print >= 10)
											num[j].print -= 10;
										num[i].Cheak = 0;
									}
									else if (Mod == 2) {
										// player
										if (player.bottom == 930) {
											player.top = 30;
											player.bottom = 75;
										}
										else {
											player.bottom += 45;
											player.top += 45;
										}
										// num
										if (num[i].rect.bottom == 930) {
											num[i].rect.top = 30;
											num[i].rect.bottom = 75;
										}
										else {
											num[i].rect.bottom += 45;
											num[i].rect.top += 45;
										}
									}
									break;
								}
								else;
							}
						}
						// num->alp
						for (int j = 0; j < 26; ++j) {
							if (alp[j].Cheak == 0);
							else {
								if (num[i].rect.top == alp[j].rect.top && num[i].rect.left == alp[j].rect.left) {
									if (Mod == 3) {
										alp[j].print += num[i].print;
										if (alp[j].print > 122)
											alp[j].print -= 26;
										num[i].Cheak = 0;
									}
									else if (Mod == 1 || Mod == 2) {
										// player
										if (player.bottom == 930) {
											player.top = 30;
											player.bottom = 75;
										}
										else {
											player.bottom += 45;
											player.top += 45;
										}
										// num
										if (num[i].rect.bottom == 930) {
											num[i].rect.top = 30;
											num[i].rect.bottom = 75;
										}
										else {
											num[i].rect.bottom += 45;
											num[i].rect.top += 45;
										}
									}
									break;
								}
								else;
							}
						}
						break;
					}
				}
			}
			// alp[i]
			for (int i = 0; i < 26; ++i) {
				if (alp[i].Cheak == 0);
				else {
					if (alp[i].rect.top == player.top && alp[i].rect.left == player.left) {
						if (alp[i].rect.top == 30) {
							alp[i].rect.bottom = 930;
							alp[i].rect.top = 885;
						}
						else {
							alp[i].rect.bottom -= 45;
							alp[i].rect.top -= 45;
						}
						// alp->num
						for (int j = 0; j < 10; ++j) {
							if (num[j].Cheak == 0);
							else {
								if (alp[i].rect.top == num[j].rect.top && alp[i].rect.left == num[j].rect.left) {
									if (Mod == 3) {
										num[j].print += alp[i].print;
										while (num[j].print >= 10)
											num[j].print -= 10;
										alp[i].Cheak = 0;
									}
									else if (Mod == 1 || Mod == 2) {
										// player
										if (player.bottom == 930) {
											player.top = 30;
											player.bottom = 75;
										}
										else {
											player.bottom += 45;
											player.top += 45;
										}
										// num
										if (alp[i].rect.bottom == 930) {
											alp[i].rect.top = 30;
											alp[i].rect.bottom = 75;
										}
										else {
											alp[i].rect.bottom += 45;
											alp[i].rect.top += 45;
										}
									}
									break;
								}
							}
						}
						// alp->alp
						for (int j = 0; j < 26; ++j) {
							if (alp[j].Cheak == 0 || j == i);
							else {
								if (alp[i].rect.top == alp[j].rect.top && alp[i].rect.left == alp[j].rect.left) {
									if (Mod == 2 || Mod == 3) {
										alp[j].print += (alp[i].print - 96);
										if (alp[j].print > 122)
											alp[j].print -= 26;
										alp[i].Cheak = 0;
									}
									else if (Mod == 1) {
										// player
										if (player.bottom == 930) {
											player.top = 30;
											player.bottom = 75;
										}
										else {
											player.bottom += 45;
											player.top += 45;
										}
										// num
										if (alp[i].rect.bottom == 930) {
											alp[i].rect.top = 30;
											alp[i].rect.bottom = 75;
										}
										else {
											alp[i].rect.bottom += 45;
											alp[i].rect.top += 45;
										}
									}
									break;
								}
							}
						}
						break;
					}
				}
			}
		}
		else if (wParam == 'a') {							// 좌
			// player 이동
			if (player.left == 40) {
				player.right = 940;
				player.left = 895;
			}
			else {
				player.right -= 45;
				player.left -= 45;
			}
			//------------

			// num[i]
			for (int i = 0; i < 10; ++i) {
				if (num[i].Cheak == 0);
				else {
					// num
					if (num[i].rect.top == player.top && num[i].rect.left == player.left) {
						if (num[i].rect.left == 40) {
							num[i].rect.right = 940;
							num[i].rect.left = 895;
						}
						else {
							num[i].rect.right -= 45;
							num[i].rect.left -= 45;
						}
						// num->num
						for (int j = 0; j < 10; ++j) {
							if (num[j].Cheak == 0 || i == j);
							else {
								if (num[i].rect.top == num[j].rect.top && num[i].rect.left == num[j].rect.left) {
									if (Mod == 1 || Mod == 3) {
										num[j].print += num[i].print;
										if (num[j].print >= 10)
											num[j].print -= 10;
										else;
										num[i].Cheak = 0;
									}
									else if (Mod == 2) {
										// player
										if (player.right == 940) {
											player.left = 40;
											player.right = 85;
										}
										else {
											player.right += 45;
											player.left += 45;
										}
										// num
										if (num[i].rect.right == 940) {
											num[i].rect.left = 40;
											num[i].rect.right = 85;
										}
										else {
											num[i].rect.right += 45;
											num[i].rect.left += 45;
										}
									}
									break;
								}
								else;
							}
						}
						// num->alp
						for (int j = 0; j < 26; ++j) {
							if (alp[j].Cheak == 0);
							else {
								if (num[i].rect.top == alp[j].rect.top && num[i].rect.left == alp[j].rect.left) {
									if (Mod == 3) {
										alp[j].print += num[i].print;
										while (alp[j].print > 122)
											alp[j].print -= 26;
										num[i].Cheak = 0;
									}
									else if (Mod == 1 || Mod == 2) {
										// player
										if (player.right == 940) {
											player.left = 40;
											player.right = 85;
										}
										else {
											player.right += 45;
											player.left += 45;
										}
										// num
										if (num[i].rect.right == 940) {
											num[i].rect.left = 40;
											num[i].rect.right = 85;
										}
										else {
											num[i].rect.right += 45;
											num[i].rect.left += 45;
										}
									}
									break;
								}
								else;
							}
						}
						break;
					}
				}
			}
			// alp[i]
			for (int i = 0; i < 26; ++i) {
				if (alp[i].Cheak == 0);
				else {
					if (alp[i].rect.top == player.top && alp[i].rect.left == player.left) {
						if (alp[i].rect.left == 40) {
							alp[i].rect.right = 940;
							alp[i].rect.left = 895;
						}
						else {
							alp[i].rect.right -= 45;
							alp[i].rect.left -= 45;
						}
						// alp->num
						for (int j = 0; j < 10; ++j) {
							if (num[j].Cheak == 0);
							else {
								if (alp[i].rect.top == num[j].rect.top && alp[i].rect.left == num[j].rect.left) {
									if (Mod == 3) {
										num[j].print += alp[i].print;
										while (num[j].print >= 10)
											num[j].print -= 10;
										alp[i].Cheak = 0;
									}
									else if (Mod == 1 || Mod == 2) {
										// player
										if (player.right == 940) {
											player.left = 40;
											player.right = 85;
										}
										else {
											player.right += 45;
											player.left += 45;
										}
										// num
										if (alp[i].rect.right == 940) {
											alp[i].rect.left = 40;
											alp[i].rect.right = 85;
										}
										else {
											alp[i].rect.right += 45;
											alp[i].rect.left += 45;
										}
									}
									break;
								}
							}
						}
						// alp->alp
						for (int j = 0; j < 26; ++j) {
							if (alp[j].Cheak == 0 || j == i);
							else {
								if (alp[i].rect.top == alp[j].rect.top && alp[i].rect.left == alp[j].rect.left) {
									if (Mod == 2 || Mod == 3) {
										alp[j].print += (alp[i].print - 96);
										if (alp[j].print > 122)
											alp[j].print -= 26;
										alp[i].Cheak = 0;
									}
									else if (Mod == 1) {
										// player
										if (player.right == 940) {
											player.left = 40;
											player.right = 85;
										}
										else {
											player.right += 45;
											player.left += 45;
										}
										// num
										if (alp[i].rect.right == 940) {
											alp[i].rect.left = 40;
											alp[i].rect.right = 85;
										}
										else {
											alp[i].rect.right += 45;
											alp[i].rect.left += 45;
										}
									}
									break;
								}
							}
						}
						break;
					}
				}
			}
		}
		else if (wParam == 's') {							// 하
			// player 이동
			if (player.bottom == 930) {
				player.top = 30;
				player.bottom = 75;
			}
			else {
				player.bottom += 45;
				player.top += 45;
			}
			//------------

			// num[i]
			for (int i = 0; i < 10; ++i) {
				if (num[i].Cheak == 0);
				else {
					// num
					if (num[i].rect.top == player.top && num[i].rect.left == player.left) {
						if (num[i].rect.bottom == 930) {
							num[i].rect.top = 30;
							num[i].rect.bottom = 75;
						}
						else {
							num[i].rect.bottom += 45;
							num[i].rect.top += 45;
						}

						// num->num
						for (int j = 0; j < 10; ++j) {
							if (num[j].Cheak == 0 || i == j);
							else {
								if (num[i].rect.top == num[j].rect.top && num[i].rect.left == num[j].rect.left) {
									if (Mod == 1 || Mod == 3) {
										num[j].print += num[i].print;
										if (num[j].print >= 10)
											num[j].print -= 10;
										else;
										num[i].Cheak = 0;
									}
									else if (Mod == 2) {
										// player
										if (player.top == 30) {
											player.bottom = 930;
											player.top = 895;
										}
										else {
											player.bottom -= 45;
											player.top -= 45;
										}
										// num
										if (num[i].rect.top == 30) {
											num[i].rect.bottom = 930;
											num[i].rect.top = 895;
										}
										else {
											num[i].rect.bottom += 45;
											num[i].rect.top += 45;
										}
									}
									break;
								}
								else;
							}
						}
						// num->alp
						for (int j = 0; j < 26; ++j) {
							if (alp[j].Cheak == 0);
							else {
								if (num[i].rect.top == alp[j].rect.top && num[i].rect.left == alp[j].rect.left) {
									if (Mod == 3) {
										alp[j].print += num[i].print;
										while (alp[j].print > 122)
											alp[j].print -= 26;
										num[i].Cheak = 0;
									}
									else if (Mod == 1 || Mod == 2) {
										// player
										if (player.top == 30) {
											player.bottom = 930;
											player.top = 895;
										}
										else {
											player.bottom -= 45;
											player.top -= 45;
										}
										// num
										if (num[i].rect.top == 30) {
											num[i].rect.bottom = 930;
											num[i].rect.top = 895;
										}
										else {
											num[i].rect.bottom += 45;
											num[i].rect.top += 45;
										}
									}
									break;
								}
								else;
							}
						}
						break;

					}
				}
			}
			// alp[i]
			for (int i = 0; i < 26; ++i) {
				if (alp[i].Cheak == 0);
				else {
					// num
					if (alp[i].rect.top == player.top && alp[i].rect.left == player.left) {
						if (alp[i].rect.bottom == 930) {
							alp[i].rect.top = 30;
							alp[i].rect.bottom = 75;
						}
						else {
							alp[i].rect.bottom += 45;
							alp[i].rect.top += 45;
						}

						// alp->num
						for (int j = 0; j < 10; ++j) {
							if (num[j].Cheak == 0);
							else {
								if (alp[i].rect.top == num[j].rect.top && alp[i].rect.left == num[j].rect.left) {
									if (Mod == 3) {
										num[j].print += alp[i].print;
										while (num[j].print >= 10)
											num[j].print -= 10;
										alp[i].Cheak = 0;
									}
									else if (Mod == 1 || Mod == 2) {
										// player
										if (player.top == 30) {
											player.bottom = 930;
											player.top = 895;
										}
										else {
											player.bottom -= 45;
											player.top -= 45;
										}
										// alp
										if (alp[i].rect.top == 30) {
											alp[i].rect.bottom = 930;
											alp[i].rect.top = 895;
										}
										else {
											alp[i].rect.bottom += 45;
											alp[i].rect.top += 45;
										}
									}
									break;
								}
							}
						}
						// alp->alp
						for (int j = 0; j < 26; ++j) {
							if (alp[j].Cheak == 0 || j == i);
							else {
								if (alp[i].rect.top == alp[j].rect.top && alp[i].rect.left == alp[j].rect.left) {
									if (Mod == 2 || Mod == 3) {
										alp[j].print += (alp[i].print - 96);
										if (alp[j].print > 122)
											alp[j].print -= 26;
										alp[i].Cheak = 0;
									}
									else if (Mod == 1) {
										// player
										if (player.top == 30) {
											player.bottom = 930;
											player.top = 895;
										}
										else {
											player.bottom -= 45;
											player.top -= 45;
										}
										// alp
										if (alp[i].rect.top == 30) {
											alp[i].rect.bottom = 930;
											alp[i].rect.top = 895;
										}
										else {
											alp[i].rect.bottom += 45;
											alp[i].rect.top += 45;
										}
									}
									break;
								}
							}
						}
						break;
					}
				}
			}
		}
		else if (wParam == 'd') {							// 우
			// player 이동
			if (player.right == 940) {
				player.left = 40;
				player.right = 85;
			}
			else {
				player.right += 45;
				player.left += 45;
			}
			//------------

			// num[i]
			for (int i = 0; i < 10; ++i) {
				if (num[i].Cheak == 0);
				else {
					// num
					if (num[i].rect.top == player.top && num[i].rect.left == player.left) {
						if (num[i].rect.right == 940) {
							num[i].rect.left = 40;
							num[i].rect.right = 85;
						}
						else {
							num[i].rect.right += 45;
							num[i].rect.left += 45;
						}

						for (int j = 0; j < 10; ++j) {
							if (num[j].Cheak == 0 || i == j);
							else {
								if (num[i].rect.top == num[j].rect.top && num[i].rect.left == num[j].rect.left) {
									if (Mod == 1 || Mod == 3) {
										num[j].print += num[i].print;
										if (num[j].print >= 10)
											num[j].print -= 10;
										else;
										num[i].Cheak = 0;
									}
									else if (Mod == 2) {
										// player
										if (player.left == 40) {
											player.right = 940;
											player.left = 895;
										}
										else {
											player.right -= 45;
											player.left -= 45;
										}
										// num
										if (num[i].rect.left == 40) {
											num[i].rect.right = 940;
											num[i].rect.left = 885;
										}
										else {
											num[i].rect.right += 45;
											num[i].rect.left += 45;
										}
									}
									break;
								}
								else;
							}
						}
						// num->alp
						for (int j = 0; j < 26; ++j) {
							if (alp[j].Cheak == 0);
							else {
								if (num[i].rect.top == alp[j].rect.top && num[i].rect.left == alp[j].rect.left) {
									if (Mod == 3) {
										alp[j].print += num[i].print;
										while (alp[j].print > 122)
											alp[j].print -= 26;
										num[i].Cheak = 0;
									}
									else if (Mod == 1 || Mod == 2) {
										// player
										if (player.left == 40) {
											player.right = 940;
											player.left = 895;
										}
										else {
											player.right -= 45;
											player.left -= 45;
										}
										// num
										if (num[i].rect.left == 40) {
											num[i].rect.right = 940;
											num[i].rect.left = 885;
										}
										else {
											num[i].rect.right += 45;
											num[i].rect.left += 45;
										}
									}
									break;
								}
								else;
							}
						}
						break;
					}
					else;
				}
			}
			// alp[i]
			for (int i = 0; i < 26; ++i) {
				if (alp[i].Cheak == 0);
				else {
					// num
					if (alp[i].rect.top == player.top && alp[i].rect.left == player.left) {
						if (alp[i].rect.right == 940) {
							alp[i].rect.left = 40;
							alp[i].rect.right = 85;
						}
						else {
							alp[i].rect.right += 45;
							alp[i].rect.left += 45;
						}

						// alp->num
						for (int j = 0; j < 10; ++j) {
							if (num[j].Cheak == 0);
							else {
								if (alp[i].rect.top == num[j].rect.top && alp[i].rect.left == num[j].rect.left) {
									if (Mod == 3) {
										num[j].print += alp[i].print;
										while (num[j].print >= 10)
											num[j].print -= 10;
										alp[i].Cheak = 0;
									}
									else if (Mod == 1 || Mod == 2) {
										// player
										if (player.left == 40) {
											player.right = 940;
											player.left = 895;
										}
										else {
											player.right -= 45;
											player.left -= 45;
										}
										// num
										if (alp[i].rect.left == 40) {
											alp[i].rect.right = 940;
											alp[i].rect.left = 885;
										}
										else {
											alp[i].rect.right += 45;
											alp[i].rect.left += 45;
										}
									}
									break;
								}
							}
						}
						// alp->alp
						for (int j = 0; j < 26; ++j) {
							if (alp[j].Cheak == 0 || j == i);
							else {
								if (alp[i].rect.top == alp[j].rect.top && alp[i].rect.left == alp[j].rect.left) {
									if (Mod == 2 || Mod == 3) {
										alp[j].print += (alp[i].print - 96);
										if (alp[j].print > 122)
											alp[j].print -= 26;
										alp[i].Cheak = 0;
									}
									else if (Mod == 1) {
										// player
										if (player.left == 40) {
											player.right = 940;
											player.left = 895;
										}
										else {
											player.right -= 45;
											player.left -= 45;
										}
										// num
										if (alp[i].rect.left == 40) {
											alp[i].rect.right = 940;
											alp[i].rect.left = 885;
										}
										else {
											alp[i].rect.right += 45;
											alp[i].rect.left += 45;
										}
									}
									break;
								}
							}
						}
						break;
					}
					else;
				}
			}
		}
		else if (wParam == 'p') {							// 새롭게 시작
			Mod = 3;
			player = { 40, 30, 85, 75 };
			for (int i = 0; i < 10; ++i) {
				num[i].print = i;
				num[i].rect.left = (rand() % 20 * 45) + 40;
				num[i].rect.top = (rand() % 20 * 45) + 30;
				num[i].rect.right = num[i].rect.left + 45;
				num[i].rect.bottom = num[i].rect.top + 45;
				num[i].Cheak = 1;
				for (int j = 0; j < i; ++j) {
					if (num[i].rect.top == num[j].rect.top && num[i].rect.left == num[j].rect.left) {
						i--;
						break;
					}
				}
				if (num[i].rect.top == player.top && num[i].rect.left == player.left)
					i--;
			}
			for (int i = 0; i < 26; ++i) {
				alp[i].print = i + 97;
				alp[i].rect.left = (rand() % 20 * 45) + 40;
				alp[i].rect.top = (rand() % 20 * 45) + 30;
				alp[i].rect.right = alp[i].rect.left + 45;
				alp[i].rect.bottom = alp[i].rect.top + 45;
				alp[i].Cheak = 1;
				if (alp[i].rect.top == player.top && alp[i].rect.left == player.left)
					i--;
				else {
					for (int j = 0; j < 10; ++j) {
						if (alp[i].rect.left == num[j].rect.left && alp[i].rect.top == num[j].rect.top) {
							i--;
							break;
						}
					}
					for (int j = 0; j < i; ++j) {
						if (alp[i].rect.left == num[j].rect.left && alp[i].rect.top == num[j].rect.top) {
							i--;
							break;
						}
					}
				}
			}
		}
		else if (wParam == 'q') {							// 프로그램 종효
			PostQuitMessage(0);
			break;
		}
		InvalidateRect(hWnd, NULL, true);
		ReleaseDC(hWnd, hDC);
		break;
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);

		//MAP----------------------------------------------------------------
		for (int j = 0; j < 20; ++j) {
			for (int i = 0; i < 20; ++i)
				Rectangle(hDC, 45 * i + 40, 45 * j + 30, 45 * (i + 1) + 40, 45 * (j + 1) + 30);
		}
		//-------------------------------------------------------------------

		for (int i = 0; i < 10; ++i) {
			if (num[i].Cheak == 0);
			else {
				static TCHAR PrintText[2];
				wsprintf(PrintText, TEXT("%d"), num[i].print);
				DrawText(hDC, PrintText, _tcslen(PrintText), &num[i].rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
			}
		}
		for (int i = 0; i < 26; ++i) {
			if (alp[i].Cheak == 0);
			else {
				static TCHAR PrintText[2];
				wsprintf(PrintText, TEXT("%c"), alp[i].print);
				DrawText(hDC, PrintText, _tcslen(PrintText), &alp[i].rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
				//TextOut(hDC, alp[i].X, alp[i].Y, PrintText, _tcslen(PrintText));
			}
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

		//-------------------------------------------------------------------

		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
