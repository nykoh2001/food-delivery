#ifndef AFTERORDERING_H
#define AFTERORDERING_H

#include "Common.h"

class AfterOrdering : public Common {
	// ���� �ֹ� �Ŀ� ��Ÿ���� �������� ���� ���׿� ���� Ŭ����
public:
	void OrderCompleted();
	// �ֹ��� �Ϸ�Ǹ� ȣ��Ǵ� �Լ�
	void expectedTime();
	// ���� �ҿ� �ð��� �˷��ִ� �Լ�
	void deliveryNow(int time);
	// ��� ��Ȳ�� �˷��ִ� �Լ�
	void writeReview();
	// ��� �Ϸ� �� ���並 �ۼ��ϴ� �Լ�
};

#endif 