#include <iostream>
#include <string>
#include <sstream>

using namespace std;

string* split(string str, int size) {
	string* split = new string[size];
	// ���ҵ� ���ڿ��� �����ϴ� split

	stringstream ss(str);
	// ���ϴ� �κ��� �и��ϱ� ���� stringstream ���
	// ���ڿ� str���� �ʱ�ȭ

	int index = 0;
	while (ss.good() && index < size) {
		ss >> split[index++];
	}
	// ������ �������� �κ� ���ڿ���� �и� �� split�� ���ҷ� ����

	return split;
	// �κ� ���ڿ����� �迭 ��ȯ
}