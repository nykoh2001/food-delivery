#include <iostream>
#include <string>
#include <fstream>
#include "Etc.h"
#include "split.h"
#include "error.h"

using namespace std;

Etc::Etc() {
	if (response == "3" || response == "ȸ�� ����/Ż��") {
		char response;
		if (sign_up_status) {
			cout << "Ż���Ͻðڽ��ϱ�? (y/n)>>";
			cin >> response;
			cin.ignore();
			if (response == 'y') {
				Secession();
			}
		}
		else {
			cout << "�����Ͻðڽ��ϱ�? (y/n)>>";
			cin >> response;
			cin.ignore();
			if (response == 'y') {
				signUp();
			}
		}
		// �̹� ������ �� ���¸� Ż�� ���θ� ����
		// ������ ���� ���� ���¸� ���� ���θ� ����
		setHome();
	}
	else if (response == "4" || response == "���� �߱�") {
		getCoupon();
	}
	else if (response == "5" || response == "�����ϱ�") {
		giftCoupon();
	}
	else if (response == "6" || response == "��ġ��") {
		cout << "������ ��ġ���� �ݾ��� �Է��ϼ���";
		cout << "(���� ��ġ��: " << deposit << ") >>";
		int price;
		cin >> price;
		cin.ignore();

		deposit += price;
		setHome();
	}
	else if (response == "7" || response == "ȸ�� ��� Ȯ��") {
		showGrade();
	}
	// response ���� ���� ������ �Լ� ȣ��

	else {
		selectError();
	}
}

void Etc::Secession() {
	ifstream loginInfo("login_info.txt");
	if (!loginInfo) {
		fileError();
	}

	string pw, line;
	char blank[101] = "";
	int count = 0, line_cnt;
	bool check = false;

	cout << "PW�� �Է����ּ��� >> ";
	getline(cin, pw);

	while (!loginInfo.eof()) {

		getline(loginInfo, line);
		line_cnt = line.length() + 1;
		// "\n"���� �����ؼ� line_cnt �� ����

		string* splits = split(line, 4);
		if (splits[1] == pw && splits[2] == username) {
			check = true;
			break;
		}

		count += line_cnt;
		// ȸ���� ���� �������� ��ġ�� count�� ����
	}
	loginInfo.close();

	fstream editInfo("login_info.txt", ios::in | ios::out);
	if (!editInfo) {
		fileError();
	}

	if (check) {

		editInfo.seekp(count + 1);
		// ���� ���ں��� �����ϱ� ���� ��ġ ����
		editInfo.write(blank, line_cnt * sizeof(char) + 1);
		// ������ ���� ����Ʈ��ŭ "" �����

		cout << "Ż�� �Ǿ����ϴ�." << endl;
		editInfo.close();
	}
	else {
		cout << "PW�� Ʋ���ϴ�." << endl;
		editInfo.close();
		setHome();
	}
}

void Etc::showGrade() {
	string line;
	ifstream loginInfo("login_info.txt");
	if (!loginInfo) {
		fileError();
	}

	while (!loginInfo.eof()) {
		getline(loginInfo, line);
		string* splits = split(line, 4);
		if (splits[2] == username) {
			if (splits[3] != "") {
				cout << username << "���� ����� " << splits[3] << "�Դϴ�." << endl;
			}
			else {
				cout << username << "���� �ű� ���� ȸ���Դϴ�." << endl;
			}
			break;
		}
	}
	// ȸ���� ���� �� ��� ���� ���� ���� ���

	loginInfo.close();

	setHome();
}

void Etc::getCoupon() {
	ifstream availableCoupon("available_coupon.txt");
	if (!availableCoupon) {
		fileError();
	}

	string line, code;

	cout << "���� ���� �ڵ带 �Է��ϼ��� >>";
	getline(cin, code);

	getline(availableCoupon, line);
	
	if (line == code) {
		ofstream coupon;
		coupon.open("coupon.txt", ios::app);
		getline(availableCoupon, line);
		coupon << line << endl;
		cout << "������ ��ϵǾ����ϴ�." << endl;
	}
	// ���� �ڵ尡 ��ġ�ϸ� ���� ���

	else {
		cout << "�ڵ尡 ��ġ���� �ʽ��ϴ�." << endl;
	}

	cout << endl;
	setHome();
}

void Etc::giftCoupon() {
	string receiver = getAddress();
	// ������ ����� receiver�� ����

	string* options = new string[3];
	string line;

	ifstream giftCouponList("gift_coupon.txt");
	if (!giftCouponList) {
		fileError();
	}

	int index = 0;
	while (!giftCouponList.eof()) {
		getline(giftCouponList, line);
		cout << line << endl;
		options[index++] = line;
	}

	cout << "������ ������ ������ �����ϼ���>>";
	int response;
	cin >> response;
	cin.ignore();
	if (response < 1 || response > 3) {
		selectError();
	}

	string* splits = split(options[response - 1], 2);
	// split �Լ� ȣ��

	string selectedCoupon = splits[1];
	// ������ ������ �ش��ϴ� �κ� ����

	delete[] options;
	delete[] splits;
	giftCouponList.close();

	cout << receiver << "�Բ� " << selectedCoupon << "�� �����Ͽ����ϴ�." << endl;
	// �������� � ������ �����ߴ��� ���

	setHome();
}

string Etc::getAddress() {
	cout << "�ּҷ�:" << endl;
	ifstream address("address.txt");
	// ������ �� �ִ� ����� ����� ����� ����

	string* options = new string[5];
	int index = 0;
	while (!address.eof()) {
		getline(address, options[index]);
		cout << options[index++] << endl;
	}

	cout << "������ ����� �����ϼ���>> ";
	int response;
	cin >> response;
	cin.ignore();

	string* splits = split(options[response - 1], 2);
	string result = splits[1];
	// ����ڰ� ������ ������ ����� result�� ����

	delete[] options;
	delete[] splits;
	address.close();

	return result;
	// result ��ȯ
}