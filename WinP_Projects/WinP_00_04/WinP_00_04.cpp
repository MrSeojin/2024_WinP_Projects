#include <iostream>
#include <random>
#include <windows.h>
using namespace std;

default_random_engine dre;
uniform_int_distribution<int> uid(0, 4);
uniform_int_distribution<int> leg(0, 9);

int main()
{
	char shape[5] = { 'o','x','#','@','*' };
	char me = shape[0], you = shape[1];
	int me_set[2] = { leg(dre),leg(dre) }, you_set[2] = { leg(dre),leg(dre) };

	cout << "---------------------\n";		// ¹ÙµÏÆÇ
	for (int j = 0; j < 10; j++) {
		for (int i = 0; i < 10; ++i) {
			if (you_set[0] == j && you_set[1] == i)
				cout << '|' << you;
			else if (me_set[0] == j && me_set[1] == i)
				cout << '|' << me;
			else
				cout << '|' << ' ';
		}
		cout << '|' << '\n';
	}
	cout << "---------------------";

	int out = 1;
	while (out) {
		cout << "\ninpit command(player 1): ";
		char mov1;
		cin >> mov1;
		switch (mov1) {
		case 'w':
			if (me_set[0] == 0) {
				me = shape[uid(dre)];
				me_set[0] = 9;
			}
			else
				me_set[0] -= 1;
			break;
		case 's':
			if (me_set[0] == 9) {
				me = shape[uid(dre)];
				me_set[0] = 0;
			}
			else
				me_set[0] += 1;
			break;
		case 'a':
			if (me_set[1] == 0) {
				me = shape[uid(dre)];
				me_set[1] = 9;
			}
			else
				me_set[1] -= 1;
			break;
		case 'd':
			if (me_set[1] == 9) {
				me = shape[uid(dre)];
				me_set[1] = 0;
			}
			else
				me_set[1] += 1;
			break;
		case 'r':
			break;
		case 'q':
			out = 0;
			break;
		default:
			cout << "Àß¸øµÈ ÀÔ·Â." << "\n¼ø¼­°¡ ³Ñ¾î°©´Ï´Ù.";
			break;
		}
		if (me_set[0] == you_set[0] && me_set[1] == you_set[1]) {
			you = shape[uid(dre)];
			cout << '\n' << "»ä!" << '\n';
			Beep(750, 500);
		}

		cout << "---------------------\n";		// ¹ÙµÏÆÇ
		for (int j = 0; j < 10; j++) {
			for (int i = 0; i < 10; ++i) {
				if (me_set[0] == j && me_set[1] == i)
					cout << '|' << me;
				else if (you_set[0] == j && you_set[1] == i)
					cout << '|' << you;
				else
					cout << '|' << ' ';
			}
			cout << '|' << '\n';
		}
		cout << "---------------------";

		cout << "\ninpit command(player 2): ";
		char mov2;
		cin >> mov2;
		switch (mov2) {
		case 'i':
			if (you_set[0] == 0) {
				you = shape[uid(dre)];
				you_set[0] = 9;
			}
			else
				you_set[0] -= 1;
			break;
		case 'k':
			if (you_set[0] == 9) {
				you = shape[uid(dre)];
				you_set[0] = 0;
			}
			else
				you_set[0] += 1;
			break;
		case 'j':
			if (you_set[1] == 0) {
				you = shape[uid(dre)];
				you_set[1] = 9;
			}
			else
				you_set[1] -= 1;
			break;
		case 'l':
			if (you_set[1] == 9) {
				you = shape[uid(dre)];
				you_set[1] = 0;
			}
			else
				you_set[1] += 1;
			break;
		case 'r':
			break;
		case 'q':
			out = 0;
			break;
		default:
			cout << "Àß¸øµÈ ÀÔ·Â." << "\n¼ø¼­°¡ ³Ñ¾î°©´Ï´Ù.\n";
			break;
		}

		if (me_set[0] == you_set[0] && me_set[1] == you_set[1]) {
			me = shape[uid(dre)];
			cout << '\n' << "»ä!" << '\n';
			Beep(750, 500);
		}

		if (mov1 == 'r' || mov2 == 'r') {					// reset
			cout << "¸®¼Â½ÃÅµ´Ï´Ù.\n";
			me = shape[uid(dre)];
			you = shape[uid(dre)];
			me_set[0] = { leg(dre) };
			me_set[1] = { leg(dre) };
			you_set[0] = { leg(dre) };
			you_set[1] = { leg(dre) };
		}

		cout << "---------------------\n";		// ¹ÙµÏÆÇ
		for (int j = 0; j < 10; j++) {
			for (int i = 0; i < 10; ++i) {
				if (you_set[0] == j && you_set[1] == i)
					cout << '|' << you;
				else if (me_set[0] == j && me_set[1] == i)
					cout << '|' << me;
				else
					cout << '|' << ' ';
			}
			cout << '|' << '\n';
		}
		cout << "---------------------";
	}
}