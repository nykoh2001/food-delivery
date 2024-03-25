#ifndef FOODDELIVERY_H
#define FOODDELIVERY_H
#include "AfterOrdering.h"

using namespace std;

class FoodDelivery : public Common {
	// 음식 주문 선택 시 사용되는 클래스
	AfterOrdering* afterOrdering;
public:
	static int total_price;
	FoodDelivery() {
		if (response == "1" || response == "음식 주문") {
			MenuList();
		}
		else if (response == "2" || response == "장바구니 가기") {
			Ordering();
		}
	}
	// respone 값에 따라 해당하는 멤버 함수 호출

	void MenuList();
	// menu.txt 파일에 저장된 메뉴 목록을 보여주는 멤버 함수
	void selectStore(string menu);
	// (선택된 메뉴).txt에 저장된 가게 목록을 보여주는 멤버 함수
	void selectDetails(string menu);
	// (선택된 메뉴)_세부.txt에 저장된 선택사항들을 보여주는 멤버 함수
	void addPrice(int& price, string new_one);
	// selectDetails에서 선택한 사항에 따라 음식의 총 금액을 계산하는 멤버 함수
	void addChoice();
	// choice.txt에 저장된 선택 사항을 final_choice.txt에 옮겨 저장하는 멤버 함수
	void ShopOrOrder(int price);
	// 장바구니에 담거나 주문하도록 하는 함수
	void Shopping(int new_price);
	// 장바구니에 담는 함수
	void Ordering(int new_price = 0);
	// 주문하는 함수
	void useCoupon();
	// 쿠폰을 사용하는 함수
};
#endif