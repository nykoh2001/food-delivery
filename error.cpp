#include <iostream>

using namespace std;

void fileError() {
	cout << "파일이 열리지 않습니다." << endl;
	exit(0);
}

void selectError() {
	cout << "입력 값이 잘못되었습니다." << endl;
	exit(0);
}