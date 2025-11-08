#include <iostream>
#include <random>

using namespace std;

default_random_engine dre;
uniform_int_distribution<int> uid(0, 8);

int main() {
	string Map[7][7];
	for (int i = 0; i < 7; ++i) {
		for (int j = 0; j < 7; ++j) {
			if (i != j && (i == 3 || j == 3))
				Map[i][j] = "  ";
			else if (i == 0 || i == 6 || j == 0 || j == 6)
				Map[i][j] = "ㅁ";
			else if (i == j || (i + j) == 6)
				Map[i][j] = "ㅁ";
			else
				Map[i][j] = "  ";
		}
	}
	char Start;
	while (true) {
		cout << "명령어: ";
		cin >> Start;
		if (Start == 'p')
			break;
		else
			cout << "-오류-\n";
	}
	string dice[5]{ "도","개","걸","윷","모" };
	int Loc_xy[2][2] = { 6,6,6,6 };

	cout << "\n게임을 시작하겠습니다.\n";
	cout << "player 1-표시: ㅇ\n";
	cout << "player 2-표시: ㅅ\n\n";

	int out = 1;
	while (out) {
		int turn;
		cout << "던지는 플레이어: ";
		cin >> turn;
		int num = uid(dre) / 2;
		switch (turn) {
		case 1:
			cout << "player 1 -> " << dice[num] << '\n';
			break;
		case 2:
			cout << "player 2 -> " << dice[num] << '\n';
			break;
		default:
			cout << "-오류-\n";
			num = 0;
			break;
		}

		for (int i = 0; i < num + 1; ++i) {
			char command;
			cout << "명령어: ";
			cin >> command;
			switch (command) {
			case 'w':
				if ((Loc_xy[turn - 1][1] == 0 || Loc_xy[turn - 1][1] == 6) && Loc_xy[turn - 1][0] != 0) {
					if (Loc_xy[turn - 1][0] == 4)
						Loc_xy[turn - 1][0] -= 2;
					else
						Loc_xy[turn - 1][0]--;
				}
				else {
					cout << "움직일 수 없음\n";
					i--;
				}
				break;
			case 's':
				if ((Loc_xy[turn - 1][1] == 0 || Loc_xy[turn - 1][1] == 6) && Loc_xy[turn - 1][0] != 6) {
					if (Loc_xy[turn - 1][0] == 2)
						Loc_xy[turn - 1][0] += 2;
					else
						Loc_xy[turn - 1][0]++;
				}
				else {
					cout << "움직일 수 없음\n";
					i--;
				}
				break;
			case 'a':
				if ((Loc_xy[turn - 1][0] == 0 || Loc_xy[turn - 1][0] == 6) && Loc_xy[turn - 1][1] != 0) {
					if (Loc_xy[turn - 1][1] == 4)
						Loc_xy[turn - 1][1] -= 2;
					else
						Loc_xy[turn - 1][1]--;
				}
				else {
					cout << "움직일 수 없음\n";
					i--;
				}
				break;
			case 'd':
				if ((Loc_xy[turn - 1][0] == 0 || Loc_xy[turn - 1][0] == 6) && Loc_xy[turn - 1][1] != 6) {
					if (Loc_xy[turn - 1][1] == 2)
						Loc_xy[turn - 1][1] += 2;
					else
						Loc_xy[turn - 1][1]++;
				}
				else {
					cout << "움직일 수 없음\n";
					i--;
				}
				break;
			case 'i':
				if (Loc_xy[turn - 1][0] == 3 && Loc_xy[turn - 1][1] == 3) {
					cout << "방향 선택: ";
					cin >> command;
					if (command == 'a') {
						Loc_xy[turn - 1][0]--;
						Loc_xy[turn - 1][1]--;
					}
					else if (command == 'd') {
						Loc_xy[turn - 1][0]--;
						Loc_xy[turn - 1][1]++;
					}
					else {
						cout << "움직일 수 없음";
						i--;
					}
				}
				else if ((Loc_xy[turn - 1][0] + Loc_xy[turn - 1][1]) == 6 && Loc_xy[turn - 1][0] != 0) {
					Loc_xy[turn - 1][0]--;
					Loc_xy[turn - 1][1]++;
				}
				else if ((Loc_xy[turn - 1][0] == Loc_xy[turn - 1][0]) && Loc_xy[turn - 1][0] != 0) {
					Loc_xy[turn - 1][0]--;
					Loc_xy[turn - 1][1]--;
				}
				else {
					cout << "움직일 수 없음";
					i--;
				}
				break;
			case 'k':
				if ((Loc_xy[turn - 1][0] == 3) && (Loc_xy[turn - 1][1] == 3)) {
					cout << "방향 선택: ";
					cin >> command;
					if (command == 'a') {
						Loc_xy[turn - 1][0]++;
						Loc_xy[turn - 1][1]--;
					}
					else if (command == 'd') {
						Loc_xy[turn - 1][0]++;
						Loc_xy[turn - 1][1]++;
					}
					else {
						cout << "움직일 수 없음";
						i--;
					}
				}
				else if ((Loc_xy[turn - 1][0] + Loc_xy[turn - 1][1]) == 6 && Loc_xy[turn - 1][0] != 6) {
					Loc_xy[turn - 1][0]++;
					Loc_xy[turn - 1][1]--;
				}
				else if (Loc_xy[turn - 1][0] == Loc_xy[turn - 1][0] && Loc_xy[turn - 1][0] != 6) {
					Loc_xy[turn - 1][0]++;
					Loc_xy[turn - 1][1]++;
				}
				else {
					cout << "움직일 수 없음";
					i--;
				}
				break;
			case 'j':
				if (Loc_xy[turn - 1][0] == 3 && Loc_xy[turn - 1][1] == 3) {
					cout << "방향 선택: ";
					cin >> command;
					if (command == 'w') {
						Loc_xy[turn - 1][0]--;
						Loc_xy[turn - 1][1]--;
					}
					else if (command == 's') {
						Loc_xy[turn - 1][0]++;
						Loc_xy[turn - 1][1]--;
					}
					else {
						cout << "움직일 수 없음";
						i--;
					}
				}
				else if ((Loc_xy[turn - 1][0] + Loc_xy[turn - 1][1] == 6) && Loc_xy[turn - 1][1] != 0) {
					Loc_xy[turn - 1][0]++;
					Loc_xy[turn - 1][1]--;
				}
				else if ((Loc_xy[turn - 1][0] == Loc_xy[turn - 1][0]) && Loc_xy[turn - 1][1] != 0) {
					Loc_xy[turn - 1][0]--;
					Loc_xy[turn - 1][1]--;
				}
				else {
					cout << "움직일 수 없음";
					i--;
				}
				break;
			case 'l':
				if (Loc_xy[turn - 1][0] == 3 && Loc_xy[turn - 1][1] == 3) {
					cout << "방향 선택: ";
					cin >> command;
					if (command == 'w') {
						Loc_xy[turn - 1][0]--;
						Loc_xy[turn - 1][1]++;
					}
					else if (command == 's') {
						Loc_xy[turn - 1][0]++;
						Loc_xy[turn - 1][1]++;
					}
					else {
						cout << "움직일 수 없음";
						i--;
					}
				}
				else if (((Loc_xy[turn - 1][0] + Loc_xy[turn - 1][1]) == 6) && Loc_xy[turn - 1][1] != 6) {
					Loc_xy[turn - 1][0]--;
					Loc_xy[turn - 1][1]++;
				}
				else if ((Loc_xy[turn - 1][0] == Loc_xy[turn - 1][0]) && Loc_xy[turn - 1][1] != 6) {
					Loc_xy[turn - 1][0]++;
					Loc_xy[turn - 1][1]++;
				}
				else {
					cout << "움직일 수 없음";
					i--;
				}
				break;
			default:
				cout << "-오류-";
				i--;
				break;
			}
			if (Loc_xy[turn - 1][0] == 6 && Loc_xy[turn - 1][1] == 6) {
				num = 0;
				cout << "player" << turn << " 도착";
			}
			cout << "움직일 수 있는 횟수: " << num - i << '\n';
		}

		if ((Loc_xy[0][0] == Loc_xy[1][0]) && (Loc_xy[0][1] == Loc_xy[1][1])) {
			if (turn == 1) {
				Loc_xy[1][0] = 6;
				Loc_xy[1][1] = 6;
			}
			else if (turn == 2) {
				Loc_xy[0][0] = 6;
				Loc_xy[0][1] = 6;
			}
		}
		else;

		if ((Loc_xy[turn - 1][0] == 6) && (Loc_xy[turn - 1][1] == 6)) {
			cout << "player" << turn << " 승리\n";
			out = 0;
		}
		else {
			//			cout << "player" << turn << "의 위치: x-" << Loc_xy[turn - 1][0] << ", y-" << Loc_xy[turn - 1][1] << '\n';
			for (int i = 0; i < 7; ++i) {
				for (int j = 0; j < 7; ++j) {
					if (i == 6 && j == 6)
						cout << Map[i][j] << '\t';
					else if ((Loc_xy[turn - 1][0] == i) && (Loc_xy[turn - 1][1] == j)) {
						if (turn == 1)
							cout << "ㅇ" << '\t';
						else
							cout << "ㅅ" << '\t';
					}
					else if ((Loc_xy[0][0] == i) && (Loc_xy[0][1] == j))
						cout << "ㅇ" << '\t';
					else if ((Loc_xy[1][0] == i) && (Loc_xy[1][1] == j))
						cout << "ㅅ" << '\t';
					else
						cout << Map[i][j] << '\t';
				}
				cout << "\n\n\n";
			}
		}
	}
	int b = 1;
	while (b) {
		cin >> b;
	}
}