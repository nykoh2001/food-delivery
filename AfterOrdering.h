#ifndef AFTERORDERING_H
#define AFTERORDERING_H

#include "Common.h"

class AfterOrdering : public Common {
	// 음식 주문 후에 나타나는 여러가지 선택 사항에 관한 클래스
public:
	void OrderCompleted();
	// 주문이 완료되면 호출되는 함수
	void expectedTime();
	// 예상 소요 시간을 알려주는 함수
	void deliveryNow(int time);
	// 배달 현황을 알려주는 함수
	void writeReview();
	// 배달 완료 후 리뷰를 작성하는 함수
};

#endif 