#ifndef ETC_H
#define ETC_H

#include "Common.h"

using namespace std;

class Etc : public Common {
public:
	Etc();
	// response에 따라 해당하는 멤버 함수를 호출하는 생성자
	void showGrade();
	// 회원의 등급을 보여주는 함수
	void getCoupon();
	// 쿠폰을 발급하는 함수
	void giftCoupon();
	// 쿠폰을 선물하는 함수
	string getAddress();
	// 주소록을 출력하고 사용자가 쿠폰을 선물하려는 사람의 이름을 반환하는 함수
	void Secession();
	// 회원에서 탈퇴하는 함수
};

#endif