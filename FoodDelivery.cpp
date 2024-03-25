#include <iostream>
#include <string>
#include <fstream>
#include "Common.h"
#include "FoodDelivery.h"
#include "split.h"
#include "error.h"

using namespace std;

void FoodDelivery::MenuList() {
	cout << "선택 가능한 메뉴 목록: " << endl;
	ifstream menu;
	menu.open("menu.txt");
	// 기존에 있던 menu.txt 파일을 열기

	if (!menu) {
		fileError();
		// 만약 파일이 열리지 않는다면 에러 문구 출력 후 종료
	}
	string str;
	// 파일에 있는 문장을 임시로 받아올 str 변수 선언
	while (!menu.eof()) {
		getline(menu, str);
		cout << str << endl;
		// menu.txt를 한 줄씩 출력
	}
	menu.close();

	string choice;
	cout << endl << "원하는 메뉴의 번호 또는 이름을 입력하세요: ";
	getline(cin, choice);
	cout << endl;

	if (choice == "1" || choice == "돈까스") {
		selectStore("돈까스");
	}
	else if (choice == "2" || choice == "치킨") {
		selectStore("치킨");
	}
	else if (choice == "3" || choice == "피자") {
		selectStore("피자");
	}
	else if (choice == "4" || choice == "떡볶이") {
		selectStore("떡볶이");
	}
	else {
		selectError();
	}
	// 선택 값에 따라 selectStore의 입력 값을 다르게 하여 호출
}

void FoodDelivery::selectStore(string menu) {
	// 선택된 메뉴를 판매하는 가게를 선택하는 멤버 함수

	ifstream store;
	store.open(menu + ".txt");
	// 메뉴를 판매하는 가게 목록에 관한 파일을 읽기 전용으로 열기

	string str;
	// 파일에 있는 한 문장을 임시로 저장할 변수 str 선언
	string* options;
	// 가게들이 저장된 string 배열을 담을 포인터 변수 options 선언

	options = new string[3];

	if (!store) {
		fileError();
	}
	for (int i = 0; i < 3; i++) {
		getline(store, str);
		options[i] = str;
		// options에 한 줄씩 저장
		cout << str << endl;
	}
	cout << endl << "주문할 가게의 번호를 입력하세요: ";
	int choice;
	cin >> choice;
	cin.ignore();
	// 선택 값 입력 받기
	cout << endl;
	ofstream choice_file;
	choice_file.open("choice.txt");

	if (!choice_file) {
		fileError();
	}
	choice_file << options[choice - 1] + "\n";
	// 입력 값에 해당하는 가게의 정보를 choice.txt에 쓰기
	choice_file.close();
	// choice.txt 닫기
	selectDetails(menu);
	// 매개 변수로 입력 받은 menu를 다시 selectDetails에 입력하여 호출
	delete[] options;
	// 동적으로 메모리를 할당한 tmp에 대해 메모리 해제
}

void FoodDelivery::selectDetails(string menu) {
	int price = 0;
	// 음식의 금액에 관한 변수 price 선언 및 0으로 초기화
	ifstream detail;
	detail.open(menu + "_세부.txt");
	// 읽기 전용으로 (메뉴이름)_세부.txt 열기

	if (!detail) {
		fileError();
	}

	fstream choice_file;
	choice_file.open("choice.txt", ios::app);
	// 가게 선택 값을 저장한 choice.txt에 금액을 이어쓰기 위해 app으로 열기

	if (!choice_file) {
		fileError();
	}

	string line;
	int response;
	int index = 0;

	string* options = new string[4];
	// 선택 사항들을 담을 string 배열 options 동적 할당
	string s;
	// 한 번의 선택이 끝난 후 담긴 다음 선택의 첫번째 선택사항을 담을 변수 s 선언
	
	while (!detail.eof()) {
		// 파일이 끝날때까지
		getline(detail, line);
		s = line;
		// s에 임시 저장
		options[index++] = line;

		if (line[0] - '0' == 1 && index > 1) {
			// 만약 한 줄이 숫자 1로 시작하고 options에 저장된 원소가 2개 이상이라면
			cout << "번호를 선택해주세요: ";
			cin >> response;
			cin.ignore();
			cout << endl;

			choice_file << options[response - 1] << endl;
			// 선택한 사항을 파일에 저장

			addPrice(price, options[response - 1]);
			// 선택한 사항에 해당되는 금액 더하기

			delete[] options;
			options = new string[4];
			// 메모리 해제 후 재할당
			// 저장된 값의 초기화

			options[0] = s;
			// 마지막에 s에 저장된 값은 다음 선택에 필요한 첫번째 선택사항이므로
			
			index = 1;
			// options[0]에 이미 값이 저장되었으므로 index는 1로 설정
		}
		cout << line << endl;
	}
	cout << "번호를 선택해주세요: ";
	cin >> response;
	cin.ignore();
	cout << endl;

	if (response > 3 || response < 1) {
		selectError();
		// 선택사항의 범위가 아닌 경우
	}

	choice_file << options[response - 1] << endl;
	addPrice(price, options[response - 1]);
	// 마지막 선택사항에 대해 한번 더 처리

	delete[] options;

	choice_file << "금액: " << price;
	// 금액 값 choice.txt에 쓰기

	choice_file.close();
	detail.close();

	addChoice();
	// choice.txt에 저장된 음식 하나에 대한 선택사항들을 final_choice.txt에 저장하는 함수 addChoice 호출
	
	ShopOrOrder(price);
	// 새롭게 추가되는 음식의 가격과 함께 장바구니에 담을 것인지 주문할 것인지 선택하도록 하는 함수 ShopOrOrder 호출
}

void FoodDelivery::addPrice(int& price, string new_one) {
	// 가격의 참조형과 선택 사항을 매개변수로 받아 금액을 계산하는 함수
	
	string number = "";
	// 가격에 해당하는 부분을 저장할 문자열 변수 number

	string* splits = split(new_one, 10);
	// 문자열에 대한 배열을 담을 문자열 포인터 변수 splits
	// split 함수 호출

	if (splits[2] != "") {
		// split 배열의 2번째 원소(가격)가 존재한다면

		int i;
		// 숫자가 시작되는 인덱스를 나타내는 정수형 변수 i
		for (i = 0; i < splits[2].length(); i++) {

			if (splits[2][i] < '0' || splits[2][i] > '9') {
				// 만약 해당 문자가 숫자를 나타내는 영역이 아니라면
				continue;
			}

			else break;
			// 문자가 숫자를 나타내는 영역에 존재하는 경우 반복문 종료
		}

		// 현재 i의 값은 가격을 나타내는 부분이 시작되는 인덱스의 값

		for (int j = i; j < splits[2].length(); j++) {

			if (splits[2][j] >= '0' && splits[2][j] <= '9') {
				// 만약 현재 문자가 숫자로 표현 가능하다면
				number += splits[2][j];
				// number 문자열에 문자 추가
			}

			else break;
			// 다시 숫자가 아닌 부분이 나오면 종료
		}
		// number에 가격에 해당하는 부분 문자열 저장됨

		price += stoi(number);
		// price에 number만큼의 금액 추가
	}
}

void FoodDelivery::addChoice() {
	ifstream choice;
	choice.open("choice.txt");
	string line;

	ofstream final_choice;
	final_choice.open("final_choice.txt", ios::app);
	// 내용을 그대로 유지한채로 이어서 쓰기 위해 ios::app 모드로 열기

	if (!choice || !final_choice) {
		fileError();
	}

	while (!choice.eof()) {
		getline(choice, line);
		final_choice << line << endl;
	}
	// choice.txt에 저장된 음식 하나에 대한 선택사항들을 읽은 후 final_choice.txt에 저장
	choice.close();
	final_choice.close();
}

void FoodDelivery::ShopOrOrder(int price) {
	cout << "선택하세요(1. 장바구니 담기, 2. 바로 주문하기)>> ";
	int response;
	cin >> response;
	cin.ignore();
	cout << endl;
	if (response == 1) {
		ofstream reset_choice;
		reset_choice.open("choice.txt");
		reset_choice.close();
		Shopping(price);
		// 만약 장바구니에 담기를 선택했다면 choice.txt 내용 초기화 및 Shopping 함수 호출
	}
	else if (response == 2) {
		ofstream reset_choice;
		reset_choice.open("choice.txt");
		reset_choice.close();
		Ordering(price);
		// 만약 바로 주문하기를 선택했다면 choice.txt 내용 초기화 및 Ordering 함수 호출
	}
	else {
		selectError();
	}
}

void FoodDelivery::Shopping(int new_price) {
	total_price += new_price;
	// 새롭게 추가된 음식의 가격을 총 금액에 더하기

	ofstream expectedTime("expected_time.txt", ios::app);

	if (!expectedTime) {
		fileError();
	}

	expectedTime << to_string(rand() % 31 + 30) << endl;
	expectedTime.close();
	// 예상 소요 시간을 expected_time.txt에 저장

	cout << "선택하세요(1. 바로 주문하기, 2. 다른 메뉴도 담기)>> ";
	int response;
	cin >> response;
	cin.ignore();
	cout << endl;
	// 사용자의 선택 값 받기

	if (response == 1) {
		Ordering();
		// 주문 선택 시 Ordering 함수 호출
	}
	else if (response == 2) {
		MenuList();
		// 다른 메뉴 담기 선택 시 MenuList 호출
	}
	else {
		selectError();
	}
}

void FoodDelivery::Ordering(int new_price) {
	ifstream final_choice;
	final_choice.open("final_choice.txt");

	if (!final_choice) {
		fileError();
	}

	string line;
	cout << "장바구니 목록: " << endl;
	while (!final_choice.eof()) {
		getline(final_choice, line);
		cout << line << endl;
	}
	// final_choice.txt로부터 지금까지 선택한 음식들과 선택 사항들 모두 출력

	total_price += new_price;
	// 새롭게 추가된 음식 값을 총 금액에 추가

	ofstream expectedTime;
	expectedTime.open("expected_time.txt", ios::app);

	if (!expectedTime) {
		fileError();
	}

	expectedTime << to_string(rand() % 31 + 30) << endl;
	expectedTime.close();
	// expected_time.txt에 예상 소요 시간 저장

	cout << "총 금액: " << total_price << endl << endl;
	cout << "주문하시겠습니까? (y/n) >>";
	char response;
	cin >> response;
	cin.ignore();
	cout << endl;
	// 총 금액 출력 후 사용자의 주문 여부 값 입력 받기

	if (response == 'y') {
		// 주문을 선택했으면
		cout << "쿠폰을 사용하시겠습니까? (y/n)>> ";
		cin >> response;
		cin.ignore();
		cout << endl;
		if (response == 'y') {
			useCoupon();
		}
		// 쿠폰 사용 여부를 묻고 선택 값에 따라 useCoupon 호출

		cout << "최종 금액: " << total_price << endl;

		cout << "결제 방법을 선택해주세요. (1. 일반 결제, 2. 예치금) >> ";
		int response;
		cin >> response;
		cin.ignore();
		if (response == 2) {
			if (deposit < total_price) {
				cout << "예치금이 부족합니다. (현재 예치금: " << deposit << ")" << endl;
				setHome();
				return;
			}
			else {
				deposit -= total_price;
				cout << "예치금으로 결제 (결제 후 예치금: " << deposit << ")" << endl;
			}
		}
		else if (response > 2) {
			selectError();
		}

		ofstream reset_final_choice("final_choice.txt");
		if (!reset_final_choice) {
			fileError();
		}
		reset_final_choice.close();
		// 장바구니의 모든 목록 초기화
		total_price = 0;
		// 주문 후 총 금액 초기화

		afterOrdering->OrderCompleted();
		// 주문 완료 후 AfterOrdering 클래스의 객체 포인터 변수인 멤버 변수를 통해 OrderCompleted 호출
	}
	else if (response == 'n') {
		setHome();
	}
	// 주문하지 않겠다는 선택이면 홈 화면으로 돌아간 후 선택 값이 1이면 MenuList 호출
	else {
		selectError();
	}
}

void FoodDelivery::useCoupon() {
	ifstream couponList;
	couponList.open("coupon.txt");

	if (!couponList) {
		fileError();
	}

	string s;
	string* options = new string[10];
	string* splits = new string[10];
	int index = 0, lines = 0;
	while (!couponList.eof()) {
		getline(couponList, s);
		cout << s << endl;
		options[index++] = s;
		lines++;
	}
	// selectDetails와 동일한 방법으로 coupon.txt에 저장된 사용 가능한 쿠폰들 저장

	cout << "번호를 선택하세요>> ";
	int response;
	cin >> response;
	cin.ignore();
	cout << endl;
	if ((response == 1 && total_price < 30000) || (response == 2 && total_price < 50000)) {
		cout << "쿠폰을 사용할 수 없습니다" << endl;
		useCoupon();
		return;
	}
	// 만약 선택한 쿠폰이 사용 조건에 어긋나면 밑에 명령들은 실행하지 않고 useCoupon 재호출
	// 밑의 코드는 실행하지 않도록 return;
	if (response > lines) {
		selectError();
	}

	couponList.close();

	ifstream couponList_again("coupon.txt");
	if (!couponList_again) {
		fileError();
	}

	for (int i = 0; i < lines; i++) {
		getline(couponList_again, s);
		if (response - 1 == i) {
			splits = split(s, 10);
			break;
		}
	}
	couponList_again.close();

	string number = "";
	if (splits[1] != "") {
		for (int i = 0; i < splits[1].length(); i++) {
			if (splits[1][i] >= '0' && splits[1][i] <= '9') {
				number += splits[1][i];
			}
			else break;
		}
	}
	// addPrice와 동일하게 split을 호출하여 선택한 쿠폰에서 가격에 해당하는 부분만 따로 분리

	total_price -= stoi(number);

	delete[] options;
	delete[] splits;
}
