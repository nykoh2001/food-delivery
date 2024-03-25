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
	cout << "ID�� �Է����ּ���>> ";
	getline(cin, id);
	cout << "PW�� �Է����ּ���>> ";
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
			cout << "�α��� �Ǿ����ϴ�." << endl;
			string name = info[2];
			delete[] info;
			username = name;
			return;
		}
		// ���̵�� �н����尡 ��ġ�ϸ� �α��� ó�� �� ���� �ڵ�� �������� ����
	}

	cout << "ȸ�� ������ �����ϴ�. ȸ�� ���� �Ͻðڽ��ϱ�? (y/n)>> ";
	char response;
	cin >> response;
	cin.ignore();
	if (response == 'y')
		return signUp();
	else if (response == 'n')
		exitProgram();
	// �α��ο� ������ ��� ȸ������ �Ǵ� ���α׷� ����
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
	cout << "����� ID�� �Է����ּ��� >> ";
	getline(cin, id);

	while (!userList.eof()) {
		string* info = new string[3];
		getline(userList, line);
		info = split(line, 3);
		if (info[0] == id) {
			cout << "�̹� �����ϴ� ���̵� �Դϴ�." << endl;
			signUp();
			return;
		}
	}
	userList.close();
	// �̹� �����ϴ� ���̵��� ��õ�

	cout << "����� PW�� �Է����ּ��� >> ";
	getline(cin, pw);
	cout << "����� �̸��� �Է����ּ��� >> ";
	getline(cin, nickname);

	ofstream loginInfo("login_info.txt", ios::app);
	if (!loginInfo) {
		fileError();
	}

	loginInfo << id + " " + pw + " " + nickname << endl;
	loginInfo.close();
	username = nickname;
	// ������� ���� ������ login_info.txt�� ����
	// username���� ������� �̸� ����
}

void Common::setHome() {
	ifstream home;
	home.open("Home.txt");

	string line;
	while (!home.eof()) {
		getline(home, line);
		cout << line << endl;
	}
	cout << "���� ������ �Է��ϼ���>> ";
	getline(cin, response);
	cout << endl;

	if (response == "1" || response == "���� �ֹ�" || response == "2" || response == "��ٱ��� ����") {
		// ���� �ֹ��� �����ߴٸ�
		FoodDelivery food;
		// FoodDelivery ��ü ����
	}
	
	else if (response == "8" || response == "���α׷� ����") {
		exitProgram();
	}
	else {
		Etc etc;
	}
	// ������� �Է°��� ���� �׿� �ش��ϴ� �� ��ü ���� �Ǵ� 
}

void Common::exitProgram() {
	cout << "�̿����ּż� �����մϴ�." << endl;
	exit(0);
}