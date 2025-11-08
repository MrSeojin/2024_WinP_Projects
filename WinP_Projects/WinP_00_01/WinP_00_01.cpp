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
string left(string);
string right(string);

int main() {
	string sentence, result_sentence;

	cout << "input sentence: ";
	while (1) {
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

	while (1) {
		cout << "명령어: ";
		char n;
		cin >> n;

		if ('a' <= n && n <= 'z') {
			sentence = change_star(sentence, n, result_sentence);
			cout << sentence << '\n';
		}
		else if (n == '1') {
			sentence = space_random(sentence);
			cout << sentence << '\n';
		}
		else if (n == '2')
			word(result_sentence);
		else if (n == '3') {
			sentence = change_char(sentence);
			cout << sentence << '\n';
		}
		else if (n == '4') {
			sentence = left(sentence);
			cout << sentence << '\n';
		}
		else if (n == '5') {
			sentence = right(sentence);
			cout << sentence << '\n';
		}
		else if (n == '0')
			break;
		else {
			cout << "command error" << '\n';
			continue;
		}
	}
}

string change_star(string str, char n, string def_str)	// 입력 문자(a~z)를 *로 바꾸고 출력
{
	string star_str;
	int i = 0;

	while (i < str.size()) {
		if (str[i] == n || str[i] == n - 32)
			star_str.push_back('*');
		else if (str[i] == '*')
			return def_str;
		else
			star_str.push_back(str[i]);
		++i;
	}

	return star_str;
}

string space_random(string str)	// 공백에 랜덤 문자 삽입
{
	string random;
	int i = 0;

	while (i < str.size()) {
		if (str[i] == ' ') {
			if (uid(dre) == 1)
				random.push_back('@');
			else if (uid(dre) == 2)
				random.push_back('#');
			else if (uid(dre) == 3)
				random.push_back('%');
			else if (uid(dre) == 4)
				random.push_back('.');
			else {
				random.push_back('.');
			}
		}
		else if (str[i] != ' ') {
			if ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z'))
				random.push_back(str[i]);
			else if (str[i] == '@' || str[i] == '#' || str[i] == '%' || str[i] == '.') {
				if (i == str.size() - 1)
					random.push_back(str[i]);
				else
					random.push_back(' ');
			}
		}
		++i;
	}

	return random;
}

void word(string str)	// 단어 개수
{
	int cnt{ 0 }, i{ 0 };

	while (i < str.size()) {
		if (str[i] == ' ')
			++cnt;
		++i;
	}

	cout << cnt + 1 << "words" << '\n';
}

string change_char(string str)	// 소문자->대문자&대문자->소문자
{
	string C;
	int i{ 0 };

	while (i < str.size()) {
		if (str[i] >= 'a' && str[i] <= 'z') {
			C.push_back(toupper(str[i]));
		}
		else if (str[i] >= 'A' && str[i] <= 'Z') {
			C.push_back(tolower(str[i]));
		}
		else C.push_back(str[i]);

		++i;
	}

	return C;
}

string left(string str)	// 좌측으로 한 문자씩 이동
{
	string lstr;
	int i{ 0 };

	while (i < str.size()) {
		if (i == str.size() - 1) {
			lstr.push_back(str[i]);
		}
		else if (i == str.size() - 2) {
			lstr.push_back(str[0]);
		}
		else {
			lstr.push_back(str[i + 1]);
		}
		++i;
	}

	return lstr;
}

string right(string str)	// 우측으로 한 문자씩 이동
{
	string rstr;
	int i{ 0 };

	while (i < str.size()) {
		if (i == str.size() - 1) {
			rstr.push_back(str[i]);
		}
		else if (i == 0) {
			rstr.push_back(str[str.size() - 2]);
		}
		else {
			rstr.push_back(str[i - 1]);
		}

		++i;
	}

	return rstr;
}

string space(string str)
{
	int i{ 0 };
	string result;

	while (i < str.size()) {
		if (str[i] == ' ') {
			if (str[i - 1] != ' ' && i != 0) {
				result.push_back(str[i]);
			}
			else {
				++i;
				continue;
			}
		}
		else result.push_back(str[i]);
		++i;
	}

	return result;
}

// [1차원 배열 사용] 문자열 다루기
// 입력 받는 것: 영어 대소문자, 띄어쓰기만으로 이루어진 마침표로 끝나는 문장 (최대 60자::최대 길이 변경 가능)
// 입력 받은 문장을 1차원 배열에 저장
// 단어 구분: 띄어쓰기(연속 공백일 경우 1개의 공백으로 처리)
// 마침표는 항상 문장 마지막에
// 명령어 재입력 시 원상태로
