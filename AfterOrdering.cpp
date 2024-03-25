#include <iostream>
#include <random>
#include <time.h>
#include <string>
#include <fstream>
#include "AfterOrdering.h"
#include "error.h"

using namespace std;

void AfterOrdering::OrderCompleted() {
	cout << "�ֹ��� �Ϸ�Ǿ����ϴ�" << endl;
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
	// expected_time.txt�� ����� �ð��� �� ���� ���� �ɸ��� �ҿ� �ð��� ã�� max_time�� ����

	cout << "���� �ҿ�ð��� " << max_time << "�� �Դϴ�." << endl;
	// ���� �ҿ� �ð� ���

	expectedTime.close();

	ofstream reset_expected_time("expected_time.txt");
	reset_expected_time.close();
	// expected_time.txt �ʱ�ȭ

	deliveryNow(max_time);
	// �ҿ� �ð��� �Ű������� deliveryNow ȣ��

	writeReview();
	// deliveryNow �Լ� ����(��� �Ϸ�) �� writeReview ȣ��
}

void AfterOrdering::deliveryNow(int time) {
	cout << "��� ��Ȳ�� Ȯ���Ͻðڽ��ϱ�? (y/n) >> ";
	char response;
	cin >> response;
	cin.ignore();
	// ��� ��Ȳ Ȯ�� ���� ���� �Է� �ޱ�

	int random = rand() % 30 + 5;
	time -= random;
	// ��� ��Ȳ Ȯ�ο� ���� ���� ���� ��� ���� �ҿ� �ð��� ����

	if (response == 'y') {
		// ��Ȳ�� Ȯ���Ѵٸ�
		if (time > 40) {
			cout << "���� �ð�: " << time << endl;
			cout << "�ֹ��� ���� �� �Դϴ�..." << endl << endl;
			deliveryNow(time);
		}
		else if (time > 20) {
			cout << "���� �ð�: " << time << endl;
			cout << "���� �� �Դϴ�..." << endl << endl;
			deliveryNow(time);
		}
		else if (time > 0) {
			cout << "���� �ð�: " << time << endl;
			cout << "��� �� �Դϴ�..." << endl << endl;
			deliveryNow(time);
		}
		else {
			cout << "����� �Ϸ�Ǿ����ϴ�." << endl << endl;
			return;
		}
		// ���� �ҿ� �ð��� ���� �ش��ϴ� ��� ���
		// ��� �ϷḦ ������ ������ ���� ���ο� �ҿ� �ð��� ���� deliveryNow ��ȣ��
		// ��� �Ϸ��� ��� deliveryNow �Լ� ���� ����
	}
	else if (response == 'n') {
		deliveryNow(time);
	}
	// Ȯ������ �ʴ´ٸ� ��� �Ϸ��� ���¸� Ȯ���� ������ deliveryNow ��ȣ��
	else {
		selectError();
	}
}

void AfterOrdering::writeReview() {
	cout << "���並 �ۼ��Ͻðڽ��ϱ�? (y/n) >>";
	char response;
	cin >> response;
	cin.ignore();

	if (response == 'y') {
		ofstream review("review.txt");

		string star_rating;
		cout << "������ �Է����ּ��� (�ִ� 5��)>>";
		getline(cin, star_rating);
		review << star_rating << endl;

		cout << "���� �ۼ��� (���� �ۼ��� �����Ϸ��� ���͸� �ѹ� �� �Է����ּ���):" << endl;
		string line;
		getline(cin, line);
		while (line != "") {
			review << line << endl;
			getline(cin, line);
		}
		cout << "���� �ۼ��� �Ϸ�Ǿ����ϴ�." << endl;
		// ���͸� �ѹ� �� ������ ������ �Էµ� ������ ��� review.txt�� ����
		review.close();
	}
	else if (response == 'n') { ; }
	else {
		selectError();
	}
	setHome();
}