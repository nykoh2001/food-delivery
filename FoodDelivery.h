#ifndef FOODDELIVERY_H
#define FOODDELIVERY_H
#include "AfterOrdering.h"

using namespace std;

class FoodDelivery : public Common {
	// ���� �ֹ� ���� �� ���Ǵ� Ŭ����
	AfterOrdering* afterOrdering;
public:
	static int total_price;
	FoodDelivery() {
		if (response == "1" || response == "���� �ֹ�") {
			MenuList();
		}
		else if (response == "2" || response == "��ٱ��� ����") {
			Ordering();
		}
	}
	// respone ���� ���� �ش��ϴ� ��� �Լ� ȣ��

	void MenuList();
	// menu.txt ���Ͽ� ����� �޴� ����� �����ִ� ��� �Լ�
	void selectStore(string menu);
	// (���õ� �޴�).txt�� ����� ���� ����� �����ִ� ��� �Լ�
	void selectDetails(string menu);
	// (���õ� �޴�)_����.txt�� ����� ���û��׵��� �����ִ� ��� �Լ�
	void addPrice(int& price, string new_one);
	// selectDetails���� ������ ���׿� ���� ������ �� �ݾ��� ����ϴ� ��� �Լ�
	void addChoice();
	// choice.txt�� ����� ���� ������ final_choice.txt�� �Ű� �����ϴ� ��� �Լ�
	void ShopOrOrder(int price);
	// ��ٱ��Ͽ� ��ų� �ֹ��ϵ��� �ϴ� �Լ�
	void Shopping(int new_price);
	// ��ٱ��Ͽ� ��� �Լ�
	void Ordering(int new_price = 0);
	// �ֹ��ϴ� �Լ�
	void useCoupon();
	// ������ ����ϴ� �Լ�
};
#endif