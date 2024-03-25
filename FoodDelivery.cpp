#include <iostream>
#include <string>
#include <fstream>
#include "Common.h"
#include "FoodDelivery.h"
#include "split.h"
#include "error.h"

using namespace std;

void FoodDelivery::MenuList() {
	cout << "���� ������ �޴� ���: " << endl;
	ifstream menu;
	menu.open("menu.txt");
	// ������ �ִ� menu.txt ������ ����

	if (!menu) {
		fileError();
		// ���� ������ ������ �ʴ´ٸ� ���� ���� ��� �� ����
	}
	string str;
	// ���Ͽ� �ִ� ������ �ӽ÷� �޾ƿ� str ���� ����
	while (!menu.eof()) {
		getline(menu, str);
		cout << str << endl;
		// menu.txt�� �� �پ� ���
	}
	menu.close();

	string choice;
	cout << endl << "���ϴ� �޴��� ��ȣ �Ǵ� �̸��� �Է��ϼ���: ";
	getline(cin, choice);
	cout << endl;

	if (choice == "1" || choice == "���") {
		selectStore("���");
	}
	else if (choice == "2" || choice == "ġŲ") {
		selectStore("ġŲ");
	}
	else if (choice == "3" || choice == "����") {
		selectStore("����");
	}
	else if (choice == "4" || choice == "������") {
		selectStore("������");
	}
	else {
		selectError();
	}
	// ���� ���� ���� selectStore�� �Է� ���� �ٸ��� �Ͽ� ȣ��
}

void FoodDelivery::selectStore(string menu) {
	// ���õ� �޴��� �Ǹ��ϴ� ���Ը� �����ϴ� ��� �Լ�

	ifstream store;
	store.open(menu + ".txt");
	// �޴��� �Ǹ��ϴ� ���� ��Ͽ� ���� ������ �б� �������� ����

	string str;
	// ���Ͽ� �ִ� �� ������ �ӽ÷� ������ ���� str ����
	string* options;
	// ���Ե��� ����� string �迭�� ���� ������ ���� options ����

	options = new string[3];

	if (!store) {
		fileError();
	}
	for (int i = 0; i < 3; i++) {
		getline(store, str);
		options[i] = str;
		// options�� �� �پ� ����
		cout << str << endl;
	}
	cout << endl << "�ֹ��� ������ ��ȣ�� �Է��ϼ���: ";
	int choice;
	cin >> choice;
	cin.ignore();
	// ���� �� �Է� �ޱ�
	cout << endl;
	ofstream choice_file;
	choice_file.open("choice.txt");

	if (!choice_file) {
		fileError();
	}
	choice_file << options[choice - 1] + "\n";
	// �Է� ���� �ش��ϴ� ������ ������ choice.txt�� ����
	choice_file.close();
	// choice.txt �ݱ�
	selectDetails(menu);
	// �Ű� ������ �Է� ���� menu�� �ٽ� selectDetails�� �Է��Ͽ� ȣ��
	delete[] options;
	// �������� �޸𸮸� �Ҵ��� tmp�� ���� �޸� ����
}

void FoodDelivery::selectDetails(string menu) {
	int price = 0;
	// ������ �ݾ׿� ���� ���� price ���� �� 0���� �ʱ�ȭ
	ifstream detail;
	detail.open(menu + "_����.txt");
	// �б� �������� (�޴��̸�)_����.txt ����

	if (!detail) {
		fileError();
	}

	fstream choice_file;
	choice_file.open("choice.txt", ios::app);
	// ���� ���� ���� ������ choice.txt�� �ݾ��� �̾�� ���� app���� ����

	if (!choice_file) {
		fileError();
	}

	string line;
	int response;
	int index = 0;

	string* options = new string[4];
	// ���� ���׵��� ���� string �迭 options ���� �Ҵ�
	string s;
	// �� ���� ������ ���� �� ��� ���� ������ ù��° ���û����� ���� ���� s ����
	
	while (!detail.eof()) {
		// ������ ����������
		getline(detail, line);
		s = line;
		// s�� �ӽ� ����
		options[index++] = line;

		if (line[0] - '0' == 1 && index > 1) {
			// ���� �� ���� ���� 1�� �����ϰ� options�� ����� ���Ұ� 2�� �̻��̶��
			cout << "��ȣ�� �������ּ���: ";
			cin >> response;
			cin.ignore();
			cout << endl;

			choice_file << options[response - 1] << endl;
			// ������ ������ ���Ͽ� ����

			addPrice(price, options[response - 1]);
			// ������ ���׿� �ش�Ǵ� �ݾ� ���ϱ�

			delete[] options;
			options = new string[4];
			// �޸� ���� �� ���Ҵ�
			// ����� ���� �ʱ�ȭ

			options[0] = s;
			// �������� s�� ����� ���� ���� ���ÿ� �ʿ��� ù��° ���û����̹Ƿ�
			
			index = 1;
			// options[0]�� �̹� ���� ����Ǿ����Ƿ� index�� 1�� ����
		}
		cout << line << endl;
	}
	cout << "��ȣ�� �������ּ���: ";
	cin >> response;
	cin.ignore();
	cout << endl;

	if (response > 3 || response < 1) {
		selectError();
		// ���û����� ������ �ƴ� ���
	}

	choice_file << options[response - 1] << endl;
	addPrice(price, options[response - 1]);
	// ������ ���û��׿� ���� �ѹ� �� ó��

	delete[] options;

	choice_file << "�ݾ�: " << price;
	// �ݾ� �� choice.txt�� ����

	choice_file.close();
	detail.close();

	addChoice();
	// choice.txt�� ����� ���� �ϳ��� ���� ���û��׵��� final_choice.txt�� �����ϴ� �Լ� addChoice ȣ��
	
	ShopOrOrder(price);
	// ���Ӱ� �߰��Ǵ� ������ ���ݰ� �Բ� ��ٱ��Ͽ� ���� ������ �ֹ��� ������ �����ϵ��� �ϴ� �Լ� ShopOrOrder ȣ��
}

void FoodDelivery::addPrice(int& price, string new_one) {
	// ������ �������� ���� ������ �Ű������� �޾� �ݾ��� ����ϴ� �Լ�
	
	string number = "";
	// ���ݿ� �ش��ϴ� �κ��� ������ ���ڿ� ���� number

	string* splits = split(new_one, 10);
	// ���ڿ��� ���� �迭�� ���� ���ڿ� ������ ���� splits
	// split �Լ� ȣ��

	if (splits[2] != "") {
		// split �迭�� 2��° ����(����)�� �����Ѵٸ�

		int i;
		// ���ڰ� ���۵Ǵ� �ε����� ��Ÿ���� ������ ���� i
		for (i = 0; i < splits[2].length(); i++) {

			if (splits[2][i] < '0' || splits[2][i] > '9') {
				// ���� �ش� ���ڰ� ���ڸ� ��Ÿ���� ������ �ƴ϶��
				continue;
			}

			else break;
			// ���ڰ� ���ڸ� ��Ÿ���� ������ �����ϴ� ��� �ݺ��� ����
		}

		// ���� i�� ���� ������ ��Ÿ���� �κ��� ���۵Ǵ� �ε����� ��

		for (int j = i; j < splits[2].length(); j++) {

			if (splits[2][j] >= '0' && splits[2][j] <= '9') {
				// ���� ���� ���ڰ� ���ڷ� ǥ�� �����ϴٸ�
				number += splits[2][j];
				// number ���ڿ��� ���� �߰�
			}

			else break;
			// �ٽ� ���ڰ� �ƴ� �κ��� ������ ����
		}
		// number�� ���ݿ� �ش��ϴ� �κ� ���ڿ� �����

		price += stoi(number);
		// price�� number��ŭ�� �ݾ� �߰�
	}
}

void FoodDelivery::addChoice() {
	ifstream choice;
	choice.open("choice.txt");
	string line;

	ofstream final_choice;
	final_choice.open("final_choice.txt", ios::app);
	// ������ �״�� ������ä�� �̾ ���� ���� ios::app ���� ����

	if (!choice || !final_choice) {
		fileError();
	}

	while (!choice.eof()) {
		getline(choice, line);
		final_choice << line << endl;
	}
	// choice.txt�� ����� ���� �ϳ��� ���� ���û��׵��� ���� �� final_choice.txt�� ����
	choice.close();
	final_choice.close();
}

void FoodDelivery::ShopOrOrder(int price) {
	cout << "�����ϼ���(1. ��ٱ��� ���, 2. �ٷ� �ֹ��ϱ�)>> ";
	int response;
	cin >> response;
	cin.ignore();
	cout << endl;
	if (response == 1) {
		ofstream reset_choice;
		reset_choice.open("choice.txt");
		reset_choice.close();
		Shopping(price);
		// ���� ��ٱ��Ͽ� ��⸦ �����ߴٸ� choice.txt ���� �ʱ�ȭ �� Shopping �Լ� ȣ��
	}
	else if (response == 2) {
		ofstream reset_choice;
		reset_choice.open("choice.txt");
		reset_choice.close();
		Ordering(price);
		// ���� �ٷ� �ֹ��ϱ⸦ �����ߴٸ� choice.txt ���� �ʱ�ȭ �� Ordering �Լ� ȣ��
	}
	else {
		selectError();
	}
}

void FoodDelivery::Shopping(int new_price) {
	total_price += new_price;
	// ���Ӱ� �߰��� ������ ������ �� �ݾ׿� ���ϱ�

	ofstream expectedTime("expected_time.txt", ios::app);

	if (!expectedTime) {
		fileError();
	}

	expectedTime << to_string(rand() % 31 + 30) << endl;
	expectedTime.close();
	// ���� �ҿ� �ð��� expected_time.txt�� ����

	cout << "�����ϼ���(1. �ٷ� �ֹ��ϱ�, 2. �ٸ� �޴��� ���)>> ";
	int response;
	cin >> response;
	cin.ignore();
	cout << endl;
	// ������� ���� �� �ޱ�

	if (response == 1) {
		Ordering();
		// �ֹ� ���� �� Ordering �Լ� ȣ��
	}
	else if (response == 2) {
		MenuList();
		// �ٸ� �޴� ��� ���� �� MenuList ȣ��
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
	cout << "��ٱ��� ���: " << endl;
	while (!final_choice.eof()) {
		getline(final_choice, line);
		cout << line << endl;
	}
	// final_choice.txt�κ��� ���ݱ��� ������ ���ĵ�� ���� ���׵� ��� ���

	total_price += new_price;
	// ���Ӱ� �߰��� ���� ���� �� �ݾ׿� �߰�

	ofstream expectedTime;
	expectedTime.open("expected_time.txt", ios::app);

	if (!expectedTime) {
		fileError();
	}

	expectedTime << to_string(rand() % 31 + 30) << endl;
	expectedTime.close();
	// expected_time.txt�� ���� �ҿ� �ð� ����

	cout << "�� �ݾ�: " << total_price << endl << endl;
	cout << "�ֹ��Ͻðڽ��ϱ�? (y/n) >>";
	char response;
	cin >> response;
	cin.ignore();
	cout << endl;
	// �� �ݾ� ��� �� ������� �ֹ� ���� �� �Է� �ޱ�

	if (response == 'y') {
		// �ֹ��� ����������
		cout << "������ ����Ͻðڽ��ϱ�? (y/n)>> ";
		cin >> response;
		cin.ignore();
		cout << endl;
		if (response == 'y') {
			useCoupon();
		}
		// ���� ��� ���θ� ���� ���� ���� ���� useCoupon ȣ��

		cout << "���� �ݾ�: " << total_price << endl;

		cout << "���� ����� �������ּ���. (1. �Ϲ� ����, 2. ��ġ��) >> ";
		int response;
		cin >> response;
		cin.ignore();
		if (response == 2) {
			if (deposit < total_price) {
				cout << "��ġ���� �����մϴ�. (���� ��ġ��: " << deposit << ")" << endl;
				setHome();
				return;
			}
			else {
				deposit -= total_price;
				cout << "��ġ������ ���� (���� �� ��ġ��: " << deposit << ")" << endl;
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
		// ��ٱ����� ��� ��� �ʱ�ȭ
		total_price = 0;
		// �ֹ� �� �� �ݾ� �ʱ�ȭ

		afterOrdering->OrderCompleted();
		// �ֹ� �Ϸ� �� AfterOrdering Ŭ������ ��ü ������ ������ ��� ������ ���� OrderCompleted ȣ��
	}
	else if (response == 'n') {
		setHome();
	}
	// �ֹ����� �ʰڴٴ� �����̸� Ȩ ȭ������ ���ư� �� ���� ���� 1�̸� MenuList ȣ��
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
	// selectDetails�� ������ ������� coupon.txt�� ����� ��� ������ ������ ����

	cout << "��ȣ�� �����ϼ���>> ";
	int response;
	cin >> response;
	cin.ignore();
	cout << endl;
	if ((response == 1 && total_price < 30000) || (response == 2 && total_price < 50000)) {
		cout << "������ ����� �� �����ϴ�" << endl;
		useCoupon();
		return;
	}
	// ���� ������ ������ ��� ���ǿ� ��߳��� �ؿ� ��ɵ��� �������� �ʰ� useCoupon ��ȣ��
	// ���� �ڵ�� �������� �ʵ��� return;
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
	// addPrice�� �����ϰ� split�� ȣ���Ͽ� ������ �������� ���ݿ� �ش��ϴ� �κи� ���� �и�

	total_price -= stoi(number);

	delete[] options;
	delete[] splits;
}
