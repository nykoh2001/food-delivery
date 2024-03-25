#include <iostream>
#include <string>
#include <fstream>
#include "Common.h"
#include "FoodDelivery.h"
#include "Etc.h"
#include "split.h"
#include "error.h"

using namespace std;

void Common::login() {
	string id, pw;
	cout << "ID를 입력해주세요>> ";
	getline(cin, id);
	cout << "PW를 입력해주세요>> ";
	getline(cin, pw);

	ifstream loginInfo("login_info.txt");
	if (!loginInfo) {
		fileError();
	}

	string line;
	while (!loginInfo.eof()) {
		string* info = new string[4];
		getline(loginInfo, line);
		info = split(line, 4);
		if (info[0] == id && info[1] == pw) {
			cout << "로그인 되었습니다." << endl;
			string name = info[2];
			delete[] info;
			username = name;
			return;
		}
		// 아이디와 패스워드가 일치하면 로그인 처리 후 밑의 코드는 실행하지 않음
	}

	cout << "회원 정보가 없습니다. 회원 가입 하시겠습니까? (y/n)>> ";
	char response;
	cin >> response;
	cin.ignore();
	if (response == 'y')
		return signUp();
	else if (response == 'n')
		exitProgram();
	// 로그인에 실패한 경우 회원가입 또는 프로그램 종료
	else {
		selectError();
	}
}

void Common::signUp() {
	ifstream userList("login_info.txt");
	if (!userList) {
		fileError();
	}

	string id, pw, nickname, line;
	cout << "사용할 ID를 입력해주세요 >> ";
	getline(cin, id);

	while (!userList.eof()) {
		string* info = new string[3];
		getline(userList, line);
		info = split(line, 3);
		if (info[0] == id) {
			cout << "이미 존재하는 아이디 입니다." << endl;
			signUp();
			return;
		}
	}
	userList.close();
	// 이미 존재하는 아이디라면 재시도

	cout << "사용할 PW를 입력해주세요 >> ";
	getline(cin, pw);
	cout << "사용할 이름을 입력해주세요 >> ";
	getline(cin, nickname);

	ofstream loginInfo("login_info.txt", ios::app);
	if (!loginInfo) {
		fileError();
	}

	loginInfo << id + " " + pw + " " + nickname << endl;
	loginInfo.close();
	username = nickname;
	// 사용자의 가입 정보를 login_info.txt에 저장
	// username에도 사용자의 이름 대입
}

void Common::setHome() {
	ifstream home;
	home.open("Home.txt");

	string line;
	while (!home.eof()) {
		getline(home, line);
		cout << line << endl;
	}
	cout << "선택 사항을 입력하세요>> ";
	getline(cin, response);
	cout << endl;

	if (response == "1" || response == "음식 주문" || response == "2" || response == "장바구니 가기") {
		// 음식 주문을 선택했다면
		FoodDelivery food;
		// FoodDelivery 객체 생성
	}
	
	else if (response == "8" || response == "프로그램 종료") {
		exitProgram();
	}
	else {
		Etc etc;
	}
	// 사용자의 입력값에 따라 그에 해당하는 값 객체 생성 또는 
}

void Common::exitProgram() {
	cout << "이용해주셔서 감사합니다." << endl;
	exit(0);
}