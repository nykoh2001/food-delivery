#include <iostream>
#include <string>
#include <sstream>

using namespace std;

string* split(string str, int size) {
	string* split = new string[size];
	// 분할된 문자열을 저장하는 split

	stringstream ss(str);
	// 원하는 부분을 분리하기 위해 stringstream 사용
	// 문자열 str으로 초기화

	int index = 0;
	while (ss.good() && index < size) {
		ss >> split[index++];
	}
	// 공백을 기준으로 부분 문자열들로 분리 후 split의 원소로 저장

	return split;
	// 부분 문자열들의 배열 반환
}