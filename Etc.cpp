#include <iostream>
#include <string>
#include <fstream>
#include "Etc.h"
#include "split.h"
#include "error.h"

using namespace std;

Etc::Etc() {
	if (response == "3" || response == "회원 가입/탈퇴") {
		char response;
		if (sign_up_status) {
			cout << "탈퇴하시겠습니까? (y/n)>>";
			cin >> response;
			cin.ignore();
			if (response == 'y') {
				Secession();
			}
		}
		else {
			cout << "가입하시겠습니까? (y/n)>>";
			cin >> response;
			cin.ignore();
			if (response == 'y') {
				signUp();
			}
		}
		// 이미 가입이 된 상태면 탈퇴 여부를 묻고
		// 가입이 되지 않은 상태면 가입 여부를 물음
		setHome();
	}
	else if (response == "4" || response == "쿠폰 발급") {
		getCoupon();
	}
	else if (response == "5" || response == "선물하기") {
		giftCoupon();
	}
	else if (response == "6" || response == "예치금") {
		cout << "충전할 예치금의 금액을 입력하세요";
		cout << "(보유 예치금: " << deposit << ") >>";
		int price;
		cin >> price;
		cin.ignore();

		deposit += price;
		setHome();
	}
	else if (response == "7" || response == "회원 등급 확인") {
		showGrade();
	}
	// response 값에 따라 적절한 함수 호출

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

	cout << "PW를 입력해주세요 >> ";
	getline(cin, pw);

	while (!loginInfo.eof()) {

		getline(loginInfo, line);
		line_cnt = line.length() + 1;
		// "\n"까지 포함해서 line_cnt 값 대입

		string* splits = split(line, 4);
		if (splits[1] == pw && splits[2] == username) {
			check = true;
			break;
		}

		count += line_cnt;
		// 회원의 정보 전까지의 위치를 count에 저장
	}
	loginInfo.close();

	fstream editInfo("login_info.txt", ios::in | ios::out);
	if (!editInfo) {
		fileError();
	}

	if (check) {

		editInfo.seekp(count + 1);
		// 다음 문자부터 삭제하기 위해 위치 조정
		editInfo.write(blank, line_cnt * sizeof(char) + 1);
		// 삭제할 줄의 바이트만큼 "" 덮어쓰기

		cout << "탈퇴 되었습니다." << endl;
		editInfo.close();
	}
	else {
		cout << "PW가 틀립니다." << endl;
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
				cout << username << "님의 등급은 " << splits[3] << "입니다." << endl;
			}
			else {
				cout << username << "님은 신규 가입 회원입니다." << endl;
			}
			break;
		}
	}
	// 회원의 정보 중 등급 값에 따라 문구 출력

	loginInfo.close();

	setHome();
}

void Etc::getCoupon() {
	ifstream availableCoupon("available_coupon.txt");
	if (!availableCoupon) {
		fileError();
	}

	string line, code;

	cout << "할인 쿠폰 코드를 입력하세요 >>";
	getline(cin, code);

	getline(availableCoupon, line);
	
	if (line == code) {
		ofstream coupon;
		coupon.open("coupon.txt", ios::app);
		getline(availableCoupon, line);
		coupon << line << endl;
		cout << "쿠폰이 등록되었습니다." << endl;
	}
	// 쿠폰 코드가 일치하면 쿠폰 등록

	else {
		cout << "코드가 일치하지 않습니다." << endl;
	}

	cout << endl;
	setHome();
}

void Etc::giftCoupon() {
	string receiver = getAddress();
	// 선물할 사람을 receiver에 저장

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

	cout << "선물할 쿠폰의 종류를 선택하세요>>";
	int response;
	cin >> response;
	cin.ignore();
	if (response < 1 || response > 3) {
		selectError();
	}

	string* splits = split(options[response - 1], 2);
	// split 함수 호출

	string selectedCoupon = splits[1];
	// 쿠폰의 종류에 해당하는 부분 저장

	delete[] options;
	delete[] splits;
	giftCouponList.close();

	cout << receiver << "님께 " << selectedCoupon << "을 선물하였습니다." << endl;
	// 누구에게 어떤 쿠폰을 선물했는지 출력

	setHome();
}

string Etc::getAddress() {
	cout << "주소록:" << endl;
	ifstream address("address.txt");
	// 선물할 수 있는 사람의 목록이 저장된 파일

	string* options = new string[5];
	int index = 0;
	while (!address.eof()) {
		getline(address, options[index]);
		cout << options[index++] << endl;
	}

	cout << "선물할 사람을 선택하세요>> ";
	int response;
	cin >> response;
	cin.ignore();

	string* splits = split(options[response - 1], 2);
	string result = splits[1];
	// 사용자가 쿠폰을 선물할 사람을 result에 저장

	delete[] options;
	delete[] splits;
	address.close();

	return result;
	// result 반환
}