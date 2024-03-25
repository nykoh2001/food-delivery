#include <iostream>
#include <string>
#include "Home.h"

using namespace std;

Home::Home() {
	sign_up_status = true;
	// 회원 가입이 되어있는 상태로 전환

	cout << "어서오세요 " << username << "님" << endl;
	// 접속 시 문구 출력

	setHome();
}