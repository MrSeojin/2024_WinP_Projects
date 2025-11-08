#include <iostream>
#include <random>
#include <algorithm>
using namespace std;

default_random_engine dre;
uniform_int_distribution uid(1, 50);

int main() 
{
	int num[4][5], numbers[20];

	for (int i = 0; i < 20; ++i) {
		numbers[i] = uid(dre);
		for (int j = 0; j < i; ++j) {
			if (numbers[i] == numbers[j])
				i--;
			else;
		}
	}
	int a = 0;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 5; ++j) {
			num[i][j] = numbers[a];
			++a;
		}
	}
	cout << "행렬값: \n";

	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 5; ++j) {
			cout << '\t' << num[i][j];
		}
		cout << '\n';
	}

	int out=1;
	while (out) {
		cout << "명령어: ";
		char ch{};
		cin >> ch;
		switch (ch) {
		case 'a':
			sort(&num[0][0], &num[3][4]);
			for (int i = 0; i < 4; ++i) {
				for (int j = 0; j < 5; ++j)
					cout << '\t' << num[i][j];
				cout << '\n';
			}
			break;
		case 'd':
			sort(&num[0][0], &num[3][5]);
			if (true) {
				int I = -1, J = 4;
				int x = 4;
				int y = 3;
				int count = 1;
				for (int z = 0; z < 20; ++z) {
					if (J == x)
						J--;
					++I;
					cout << '\t' << num[I][J];
					//			cout << "( " << i << ',' << j << " )";
					--J;
					if ((z + 1) % 4 == 0) {
						x -= 1;
						J = 4;
					}
					if ((z + 1) % 5 == 0) {
						cout << '\n';
						I = -1;
					}
					if (y == I) {
						--I;
						--y;
					}
				}
			}
			break;
		case 'e':
			for (int i = 0; i < 4; ++i) {
				for (int j = 0; j < 5; ++j) {
					if (num[i][j] % 2 == 0)
						cout << '\t' << num[i][j];
					else
						cout << '\t' << 0;
				}
				cout << '\n';
			}
			break;
		case 'o':
			for (int i = 0; i < 4; ++i) {
				for (int j = 0; j < 5; ++j) {
					if (num[i][j] % 2 == 1)
						cout << '\t' << num[i][j];
					else
						cout << '\t' << 0;
				}
				cout << '\n';
			}
			break;
		case 'm':
			if (true) {
				int max = *max_element(numbers, numbers + 20);
				for (int i = 0; i < 4; ++i) {
					for (int j = 0; j < 5; ++j) {
						cout << '\t' << num[i][j] + max;
					}
					cout << '\n';
				}
			}
			break;
		case 'n':
			if (true) {
				int min = *min_element(numbers, numbers + 20);
				for (int i = 0; i < 4; ++i) {
					for (int j = 0; j < 5; ++j) {
						cout << '\t' << num[i][j] - min;
					}
					cout << '\n';
				}
			}
			break;
		case 'p':
			for (int i = 0; i < 4; ++i) {
				for (int j = 0; j < 5; ++j)
					num[i][0] += num[i][j];
			}
			for (int i = 0; i < 4; ++i) {
				for (int j = 0; j < 5; ++j) {
					cout << '\t' << num[i][j];
				}
				cout << '\n';
			}
			break;
		case 'u':
			for (int i = 0; i < 5; ++i) {
				for (int j = 0; j < 3; ++j)
					num[3][i] *= num[j][i];
			}
			for (int i = 0; i < 4; ++i) {
				for (int j = 0; j < 5; ++j) {
					cout << '\t' << num[i][j];
				}
				cout << '\n';
			}
			break;
		case 'r':
			if (true) {
				default_random_engine dre;
				uniform_int_distribution uid(0, 19);
				int sec[20];
				for (int i = 0; i < 20; ++i) {
					sec[i] = numbers[uid(dre)];
					for (int j = 0; j < i; ++j) {
						if (sec[i] == sec[j])
							i--;
						else;
					}
				}
				int a = 0;
				for (int i = 0; i < 4; ++i) {
					for (int j = 0; j < 5; ++j) {
						num[i][j] = sec[a];
						++a;
					}
				}

				for (int i = 0; i < 4; ++i) {
					for (int j = 0; j < 5; ++j) {
						cout << '\t' << num[i][j];
					}
					cout << '\n';
				}
			}
			break;
		case 's':
			if (true) {
				for (int i = 0; i < 20; ++i) {
					numbers[i] = uid(dre);
					for (int j = 0; j < i; ++j) {
						if (numbers[i] == numbers[j])
							i--;
						else;
					}
				}
				int a = 0;
				for (int i = 0; i < 4; ++i) {
					for (int j = 0; j < 5; ++j) {
						num[i][j] = numbers[a];
						++a;
					}
				}
				for (int i = 0; i < 4; ++i) {
					for (int j = 0; j < 5; ++j) {
						cout << '\t' << num[i][j];
					}
					cout << '\n';
				}
			}
			break;
		default:
			out = 0;
			break;
		}
	}
}