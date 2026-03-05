#include<iostream>
#include<random>

using namespace std;

int numbers[20]{}, fir[20]{};
int main()
{
	int num;
	cout << "input number: ";
	cin >> num;
	if (num < 100) {
		cout << "error\n100보다 큰 수를 입력해주세요.";
		cin >> num;
	}

	default_random_engine dre;
	uniform_int_distribution<int> uid(0, num);

	for (int i = 0; i < 20; ++i) {
		numbers[i] = uid(dre);
		fir[i] = numbers[i];
		for (int j = 0; j < i; ++j) {
			if (numbers[j] == numbers[i])
				i--;
			else;
		}
	}
	cout << "generated numbers\n";

	for (int i = 0; i < 20; ++i)
		cout << numbers[i] << ' ';

	char com;

	while (true) {
		cout << "\ncommand: ";
		cin >> com;
		if (com == 'a') {
			qsort(numbers, 20, 4, [](const void* a, const void* b) {return *(int*)a - *(int*)b; });
			for (int i = 0; i < 20; ++i)
				cout << numbers[i] << ' ';
		}
		else if (com == 'd') {
			qsort(numbers, 20, 4, [](const void* a, const void* b) {return *(int*)b - *(int*)a; });
			for (int i = 0; i < 20; ++i)
				cout << numbers[i] << ' ';
		}
		else if (com == 'e') {
			qsort(numbers, 20, 4, [](const void* a, const void* b) {return *(int*)a - *(int*)b; });
			int result = 0;
			for (int i = 0; i < 20; ++i) {
				if (numbers[i] % 3 == 0) {
					cout << numbers[i] << ' ';
					result = result + numbers[i];
				}
			}
			cout << " -> " << result;
		}
		else if (com == 'f') {
			int result = 0;
			for (int i = 0; i < 20; ++i) {
				if (numbers[i] % 5 == 0) {
					cout << numbers[i] << ' ';
					result = result + numbers[i];
				}
			}
			cout << " -> " << result;
		}
		else if (com == 'm') {
			for (int i = 0; i < 20; ++i) {
				if (numbers[i] % 3 == 0 || numbers[i] % 5 == 0)
					cout << numbers[i] << ' ';
			}
			cout << "-> ";
			for (int i = 0; i < 20; ++i) {
				if (numbers[i] % 3 == 0 || numbers[i] % 5 == 0)
					cout << numbers[i] + 1 << ' ';
			}
		}
		else if (com == 'n') {
			for (int i = 0; i < 20; ++i) {
				if (numbers[i] % 3 == 0 && numbers[i] % 5 == 0)
					cout << numbers[i] << ' ';
			}
			cout << "-> ";
			for (int i = 0; i < 20; ++i) {
				if (numbers[i] % 3 == 0 && numbers[i] % 5 == 0)
					cout << numbers[i] - 1 << ' ';
			}
		}
		else if (com == 'r') {
			for (int i = 0; i < 20; ++i)
				numbers[i] = fir[i];
			for (int i = 0; i < 20; ++i)
				cout << numbers[i] << ' ';
		}
		else if (com == 'p') {
			cout << "input number: ";
			cin >> num;
			uniform_int_distribution<int> uid(0, num);
			for (int i = 0; i < 20; ++i) {
				numbers[i] = uid(dre);
				fir[i] = numbers[i];
				for (int j = 0; j < i; ++j) {
					if (numbers[j] == numbers[i])
						i--;
					else;
				}
			}
			for (int i = 0; i < 20; ++i)
				cout << numbers[i] << ' ';
		}
		else if (com == 'q')
			break;
		else
			cout << "명령어 잘못 입력\n";
	}
}