#include<iostream>
#include<string>
#include<random>
using namespace std;

random_device rd;
default_random_engine dre(rd());
uniform_int_distribution<int> uid(1, 4);

string space(string);
string change_star(string, char, string);
string space_random(string);
void word(string);
string change_char(string);
string move_left(string);
string move_right(string);

int main() {
	string sentence, result_sentence;

	cout << "input sentence: ";
	while (true) {
		string input_sentence{};
		getline(cin, input_sentence, '.');

		sentence = space(input_sentence);
		if (sentence.back() != '.')sentence.push_back('.');

		if (sentence.size() > 60) {
			cout << "error- sentence is too long\n";
			cout << "input sentence:";
			continue;
		}
		else break;
	}
	cout << "sentence: " << sentence << '\n';

	result_sentence = sentence;

	bool out = true;
	while (out) {
		cout << "명령어: ";
		char cmd;
		cin >> cmd;

		switch (cmd) {
		case '1':
			sentence = space_random(sentence);
			cout << sentence << '\n';
			break;
		case '2':
			word(result_sentence);
			break;
		case '3':
			sentence = change_char(sentence);
			cout << sentence << '\n';
			break;
		case '4':
			sentence = move_left(sentence);
			cout << sentence << '\n';
			break;
		case '5':
			sentence = move_right(sentence);
			cout << sentence << '\n';
			break;
		case '0':
			out = false;
			break;
		default:
			if (('a' <= cmd && cmd <= 'z') || ('A' <= cmd && cmd <= 'Z')) {
				sentence = change_star(sentence, cmd, result_sentence);
				cout << sentence << '\n';
			}
			else
				cout << "command error" << '\n';
			break;
		}
	}
}

string change_star(string str, char c, string def_str)	// 입력 문자(a~z)를 *로 바꾸고 출력
{
	for (int i = 0; i < str.length(); ++i) {
		if ((toupper(c) == toupper(str[i])) || (tolower(c) == tolower(str[i])))
			str[i] = '*';
		else if (str[i] == '*')
			return def_str;
	}

	return str;
}

string space_random(string str)	// 공백에 랜덤 문자 삽입
{
	for (int i = 0; i < str.length(); ++i) {
		if (str[i] == ' ') {
			switch (uid(dre)) {
			case 1: 
				str[i] = '@';
				break;
			case 2:
				str[i] = '#';
				break;
			case 3:
				str[i] = '%';
				break;
			case 4:
				str[i] = '.';
				break;
			}
		}
		else if (str[i] == '@' || str[i] == '#' || str[i] == '%' || str[i] == '.') {
			if (i != str.length() - 1)
				str[i] = ' ';
		}
	}

	return str;
}

void word(string str)	// 단어 개수
{
	int cnt{};
	for (int i = 1; i < str.length(); ++i) {
		if (str[i] == ' ' && str[i - 1] != ' ')
			++cnt;
	}

	cout << cnt + 1 << "words" << '\n';
}

string change_char(string str)	// 소문자->대문자&대문자->소문자
{
	for (int i = 0; i < str.length(); ++i){
		if (isupper(str[i]))
			str[i] = tolower(str[i]);
		else
			str[i] = toupper(str[i]);
	}

	return str;
}

string move_left(string str)	// 좌측으로 한 문자씩 이동
{
	str.push_back(str.front());
	str.erase(str.begin());

	return str;
}

string move_right(string str)	// 우측으로 한 문자씩 이동
{
	str.insert(str.begin(), str.back());
	str.pop_back();

	return str;
}

string space(string str)
{
	for (int i = 1; i < str.length(); ++i) {
		if (str[i] == ' ' && str[i - 1] == ' ')
			str.erase(i--, 1);
	}

	return str;
}

// [1차원 배열 사용] 문자열 다루기
// 입력 받는 것: 영어 대소문자, 띄어쓰기만으로 이루어진 마침표로 끝나는 문장 (최대 60자::최대 길이 변경 가능)
// 입력 받은 문장을 1차원 배열에 저장
// 단어 구분: 띄어쓰기(연속 공백일 경우 1개의 공백으로 처리)
// 마침표는 항상 문장 마지막에
// 명령어 재입력 시 원상태로
