#include <iostream>
#include <string>
#include "Home.h"

using namespace std;

Home::Home() {
	sign_up_status = true;
	// ȸ�� ������ �Ǿ��ִ� ���·� ��ȯ

	cout << "������� " << username << "��" << endl;
	// ���� �� ���� ���

	setHome();
}