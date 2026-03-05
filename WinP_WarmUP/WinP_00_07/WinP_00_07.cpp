#include <iostream>

using namespace std;

struct Planet
{
	string name;
	double size, numSatel, Orbit_n, Rotat, Orbit_s, Tilt, sunDis;

public:
	Planet(string Name, double Size, double NumSatel, double OrbitN, double RotaT, double OrbitS, double TilT, double SunDis)
		: name(Name), size(Size), numSatel(NumSatel), Orbit_n(OrbitN), Rotat(RotaT), Orbit_s(OrbitS), Tilt(TilT), sunDis(SunDis) {
	}
	void show() const
	{
		cout << "-----------------------------\n";
		cout << "행성 이름: \t" << name << '\n';
		cout << "행성 크기: \t" << size << '\n';
		cout << "위성의 개수:\t" << numSatel << '\n';
		cout << "공전 주기: \t" << Orbit_n << '\n';
		cout << "자전 주기: \t" << Rotat << '\n';
		cout << "공전 속도: \t" << Orbit_s << '\n';
		cout << "기울기:  \t" << Tilt << '\n';
		cout << "태양과의 거리:\t" << sunDis << '\n';
		cout << "-----------------------------\n";
	}

};

int main()
{

	Planet Mercury = { "수성", 0.383, 0, 88, 59, 47.36, 0.035, 0.4 };
	Planet venus = { "금성", 0.95, 0, 225, 243, 35.02, 177.4, 0.7 };
	Planet Mars = { "화성", 0.532, 2, 687, 1.026, 24.077, 25.19, 1.5 };
	Planet Jupiter = { "목성", 10.97, 95, 4015, 0.410, 13.056, 3.13, 5.2 };
	Planet Saturn = { "토성", 9.14, 145, 10585, 0.426, 9.639, 26.73, 9.6 };
	Planet Uranus = { "천왕성", 3.98, 27, 30660, 0.718, 6.795, 97.77, 19.1 };
	Planet Neptune = { "해왕성", 3.87, 14, 60225, 0.669, 5.43, 119.61, 30 };

	Planet Planets[7] = { Mercury,venus,Mars,Jupiter,Saturn,Uranus,Neptune };

	int out = 1;
	while (out) {
		cout << "명령어: ";
		char command;
		cin >> command;
		switch (command) {
		case 'p':
			for (int i = 0; i < 7; ++i)
				Planets[i].show();
			break;
		case 'a':
			if (true) {
				int Planets_speed[7]{};
				for (int i = 0; i < 7; ++i) {
					for (int j = 0; j < 7; ++j) {
						if (i == 0 || Planets[j].Orbit_s > Planets[Planets_speed[i - 1]].Orbit_s) {
							if (Planets[j].Orbit_s < Planets[Planets_speed[i]].Orbit_s) {
								Planets_speed[i] = j;
							}
							else;
						}
						else;
					}
				}
				for (int i = 0; i < 7; ++i) {
					cout << "-----------------------------\n";
					cout << "행성 이름: \t" << Planets[Planets_speed[i]].name << '\n';
					cout << "공전 속도: \t" << Planets[Planets_speed[i]].Orbit_s << '\n';
					cout << "-----------------------------\n";
				}
			}
			break;
		case 'b':
			if (true) {
				int Planets_size[7]{};
				for (int i = 0; i < 7; ++i) {
					for (int j = 0; j < 7; ++j) {
						if (i == 0 || Planets[j].size < Planets[Planets_size[i - 1]].size) {
							if (Planets[j].size > Planets[Planets_size[i]].size) {
								Planets_size[i] = j;
							}
							else;
						}
						else;
					}
				}
				for (int i = 0; i < 7; ++i) {
					cout << "-----------------------------\n";
					cout << "행성 이름: \t" << Planets[Planets_size[i]].name << '\n';
					cout << "행성 크기: \t" << Planets[Planets_size[i]].size << '\n';
					cout << "-----------------------------\n";
				}
			}
			break;
		case 'c':
			if (true) {
				int Planets_Dis[7]{ 6,6,6,6,6,6,6 };
				for (int i = 1; i < 7; ++i) {
					if (Planets[i].sunDis - Planets[i - 1].sunDis > Planets[0].sunDis)
						Planets_Dis[0] = i;
				}
				for (int i = 1; i < 7; ++i) {
					for (int j = 0; j < 7; ++j) {
						if (i == 0 || Planets[j].sunDis < Planets[Planets_Dis[i - 1]].sunDis) {
							if (j == 0 && (Planets[0].sunDis > (Planets[Planets_Dis[i]].sunDis - Planets[Planets_Dis[i - 1]].sunDis))) {
								Planets_Dis[i] = 0;
							}
							if ((Planets[j].sunDis - Planets[j - 1].sunDis) > (Planets[Planets_Dis[i]].sunDis - Planets[Planets_Dis[i - 1]].sunDis)) {
								Planets_Dis[i] = j;
							}
							else;
						}
						else;
					}
				}
				for (int i = 0; i < 7; ++i) {
					if (Planets_Dis[i] == 0) {
						cout << "태양~" << Planets[Planets_Dis[i]].name << '\n';
					}
					else
						cout << Planets[Planets_Dis[i] - 1].name << '~' << Planets[Planets_Dis[i]].name << '\n';
				}
			}
			break;
		case 'd':
			for (int i = 0; i < 7; ++i) {
				Planets[i].Rotat *= 24;
			}
			for (int i = 0; i < 7; ++i) {
				cout << "-----------------------------\n";
				cout << "행성 이름: \t" << Planets[i].name << '\n';
				cout << "자전 주기: \t" << Planets[i].Rotat << '\n';
				cout << "-----------------------------\n";
			}
			for (int i = 0; i < 7; ++i) {
				Planets[i].Rotat /= 24;
			}
			break;
		case 'e':
			if (true) {
				int Planets_Tilt[7]{ 1,1,1,1,1,1,1 };
				for (int i = 0; i < 7; ++i) {
					for (int j = 0; j < 7; ++j) {
						if (i == 0 || Planets[j].Tilt > Planets[Planets_Tilt[i - 1]].Tilt) {
							if (Planets[j].Tilt < Planets[Planets_Tilt[i]].Tilt) {
								Planets_Tilt[i] = j;
							}
							else;
						}
						else;
					}
				}
				for (int i = 0; i < 7; ++i) {
					cout << "-----------------------------\n";
					cout << "행성 이름: \t" << Planets[Planets_Tilt[i]].name << '\n';
					cout << "기울기:  \t" << Planets[Planets_Tilt[i]].Tilt << '\n';
					cout << "-----------------------------\n";
				}
			}
			break;
		case 'q':
			out = 0;
			break;
		default:
			cout << "잘못 입력\n";
			break;
		}
	}
}