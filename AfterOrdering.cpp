#include <iostream>
#include <random>
#include <time.h>
#include <string>
#include <fstream>
#include "AfterOrdering.h"
#include "error.h"

using namespace std;

void AfterOrdering::OrderCompleted() {
	cout << "주문이 완료되었습니다" << endl;
	expectedTime();
}

void AfterOrdering::expectedTime() {
	ifstream expectedTime("expected_time.txt");
	if (!expectedTime) {
		fileError();
	}

	string line;
	int max_time = 0;

	while (!expectedTime.eof()) {
		getline(expectedTime, line);
		if (line == "") break;
		if (max_time < stoi(line)) {
			max_time = stoi(line);
		}
	}
	// expected_time.txt에 저장된 시간들 중 가장 오래 걸리는 소요 시간을 찾아 max_time에 저장

	cout << "예상 소요시간은 " << max_time << "분 입니다." << endl;
	// 예상 소요 시간 출력

	expectedTime.close();

	ofstream reset_expected_time("expected_time.txt");
	reset_expected_time.close();
	// expected_time.txt 초기화

	deliveryNow(max_time);
	// 소요 시간을 매개변수로 deliveryNow 호출

	writeReview();
	// deliveryNow 함수 종료(배달 완료) 후 writeReview 호출
}

void AfterOrdering::deliveryNow(int time) {
	cout << "배달 현황을 확인하시겠습니까? (y/n) >> ";
	char response;
	cin >> response;
	cin.ignore();
	// 배달 현황 확인 선택 여부 입력 받기

	int random = rand() % 30 + 5;
	time -= random;
	// 배달 현황 확인에 대한 선택 여부 상관 없이 소요 시간은 감소

	if (response == 'y') {
		// 현황을 확인한다면
		if (time > 40) {
			cout << "남은 시간: " << time << endl;
			cout << "주문을 접수 중 입니다..." << endl << endl;
			deliveryNow(time);
		}
		else if (time > 20) {
			cout << "남은 시간: " << time << endl;
			cout << "조리 중 입니다..." << endl << endl;
			deliveryNow(time);
		}
		else if (time > 0) {
			cout << "남은 시간: " << time << endl;
			cout << "배달 중 입니다..." << endl << endl;
			deliveryNow(time);
		}
		else {
			cout << "배달이 완료되었습니다." << endl << endl;
			return;
		}
		// 남은 소요 시간에 따라 해당하는 경우 출력
		// 배달 완료를 제외한 나머지 경우는 새로운 소요 시간에 대해 deliveryNow 재호출
		// 배달 완료인 경우 deliveryNow 함수 전부 종료
	}
	else if (response == 'n') {
		deliveryNow(time);
	}
	// 확인하지 않는다면 배달 완료인 상태를 확인할 때까지 deliveryNow 재호출
	else {
		selectError();
	}
}

void AfterOrdering::writeReview() {
	cout << "리뷰를 작성하시겠습니까? (y/n) >>";
	char response;
	cin >> response;
	cin.ignore();

	if (response == 'y') {
		ofstream review("review.txt");

		string star_rating;
		cout << "별점을 입력해주세요 (최대 5개)>>";
		getline(cin, star_rating);
		review << star_rating << endl;

		cout << "리뷰 작성란 (리뷰 작성을 종료하려면 엔터를 한번 더 입력해주세요):" << endl;
		string line;
		getline(cin, line);
		while (line != "") {
			review << line << endl;
			getline(cin, line);
		}
		cout << "리뷰 작성이 완료되었습니다." << endl;
		// 엔터를 한번 더 누르기 전까지 입력된 내용을 모두 review.txt에 저장
		review.close();
	}
	else if (response == 'n') { ; }
	else {
		selectError();
	}
	setHome();
}