#include <iostream>
#include <random>
using namespace std;

default_random_engine dre;
uniform_int_distribution<int> uid(1, 2);

int calculator(int a, int b, char op);

int main()
{
	int num[5], result = 0;
	char cul[4];

	cout << "5개의 숫자와 4개의 연산자를 입력해주세요.\nex)1+2-3*4/5\n";
	cin >> num[0] >> cul[0] >> num[1] >> cul[1] >> num[2] >> cul[2] >> num[3] >> cul[3] >> num[4];

	int out = 1;
	while (out) {
		char command;
		cout << "명령어 입력: ";
		cin >> command;
		switch (command) {
		case '1':
			if (true) {
				int next = 1;
				int cheak = 0;
				int n = 1;
				int fur[4]{};
				char cul_3[3]{};
				int tre[3]{};
				char cul_2[2]{};
				int two[2]{};
				char cul_1{};

				for (int i = 0; i < 4; ++i) {
					if (cul[i] == '*' || cul[i] == '/') {
						n = i;
						cheak = 1;
					}
					else;
				}

				if (cheak == 1) {
					for (int i = 0; i < 4; ++i) {
						if (i < n) {
							fur[i] = num[i];
							cul_3[i] = cul[i];
						}
						else if (i == n)
							fur[i] = calculator(num[i], num[i + 1], cul[i]);
						else {
							cul[i - 1] = cul[i];
							fur[i] = num[i + 1];
						}
					}
				}
				else {
					result = num[0];
					for (int i = 0; i < 4; ++i)
						result = calculator(result, num[i + 1], cul[i]);
					next = 0;
				}
				cheak = 0;
				if (next == 1) {
					for (int i = 0; i < 3; ++i) {
						if (cul_3[i] == '*' || cul_3[i] == '/') {
							n = i;
							cheak = 1;
						}
						else;
					}

					if (cheak == 1) {
						for (int i = 0; i < 3; ++i) {
							if (i < n) {
								tre[i] = fur[i];
								cul_2[i] = cul_3[i];
							}
							else if (i == n)
								tre[i] = calculator(fur[i], fur[i + 1], cul_3[i]);
							else {
								cul_2[i - 1] = cul_3[i];
								tre[i] = fur[i + 1];
							}
						}
					}
					else {
						next = 0;
						result = fur[0];
						for (int i = 0; i < 3; ++i)
							result = calculator(result, fur[i + 1], cul_3[i]);
					}
					cheak = 0;
					if (next == 1) {
						for (int i = 0; i < 2; ++i) {
							if (cul_2[i] == '*' || cul_2[i] == '/') {
								n = i;
								cheak = 1;
							}
							else;
						}

						if (cheak == 1) {
							for (int i = 0; i < 2; ++i) {
								if (i < n) {
									two[i] = tre[i];
									cul_1 = cul_2[i];
								}
								else if (i == n)
									two[i] = calculator(tre[i], tre[i + 1], cul_2[i]);
								else {
									cul_1 = cul_2[i];
									two[i] = two[i + 1];
								}
							}
						}
						else {
							next = 0;
							result = tre[0];
							for (int i = 0; i < 2; ++i)
								result = calculator(result, tre[i + 1], cul_2[i]);
						}
						if (next == 1) {
							result = calculator(two[0], two[1], cul_1);
						}
					}
				}
				cout << num[0] << cul[0] << num[1] << cul[1] << num[2] << cul[2] << num[3] << cul[3] << num[4] << " = " << result << '\n';
			}
			break;
		case '2':
			result = num[0];
			for (int i = 0; i < 4; ++i)
				result = calculator(result, num[i + 1], cul[i]);
			cout << "(((" << num[0] << cul[0] << num[1] << ")" << cul[1] << num[2] << ")" << cul[2] << num[3] << ")" << cul[3] << num[4] << " = " << result << '\n';
			break;
		case '3':
			result = num[4];
			for (int i = 3; i >= 0; --i) {
				result = calculator(num[i], result, cul[i]);
			}
			cout << num[0] << cul[0] << "(" << num[1] << cul[1] << "(" << num[2] << cul[2] << "(" << num[3] << cul[3] << num[4] << ")))" << " = " << result << '\n';
			break;
		case '4':
			cout << "5개의 숫자와 4개의 연산자를 입력해주세요.\n";
			cin >> num[0] >> cul[0] >> num[1] >> cul[1] >> num[2] >> cul[2] >> num[3] >> cul[3] >> num[4];
			break;
		case 'q':
			out = 0;
			break;
		}
	}
}

int calculator(int a, int b, char op) {
	int res = 0;

	if (op == '+')
		res = a + b;
	else if (op == '-')
		res = a - b;
	else if (op == '*')
		res = a * b;
	else if (op == '/') {
		if (b != 0)
			res = static_cast<int>(a / b);
		else
			cout << "계산 불가" << '\n';
	}
	return res;
}