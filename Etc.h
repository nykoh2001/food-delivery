#ifndef ETC_H
#define ETC_H

#include "Common.h"

using namespace std;

class Etc : public Common {
public:
	Etc();
	// response�� ���� �ش��ϴ� ��� �Լ��� ȣ���ϴ� ������
	void showGrade();
	// ȸ���� ����� �����ִ� �Լ�
	void getCoupon();
	// ������ �߱��ϴ� �Լ�
	void giftCoupon();
	// ������ �����ϴ� �Լ�
	string getAddress();
	// �ּҷ��� ����ϰ� ����ڰ� ������ �����Ϸ��� ����� �̸��� ��ȯ�ϴ� �Լ�
	void Secession();
	// ȸ������ Ż���ϴ� �Լ�
};

#endif