#ifndef COMMON_H
#define COMMON_H

using namespace std;

class Common {
	// 두 개 이상의 클래스가 공통으로 갖는 멤버를 담는 클래스
public:
	static int deposit;
	// 예치금
	static string username;
	// 사용자의 닉네임
	// 객체 생성 없이 사용되므로 static 선언
	static void login();
	// 사용자가 프로그램 실행 시 처음 호출되는 함수
	// 사용자가 로그인할 수 있도록 하는 함수
	static void signUp();
	// 회원가입하는 함수
	static bool sign_up_status;
	// 회원가입 여부를 나타내는 변수: false로 초기화
	static string response;
	// 사용자가 선택하는 값을 담을 string 변수 response
	static void setHome();
	// 사용자에게 선택 목록을 보여주고 선택 값을 입력 받아 그에 해당하는 특정 값 대입
	static void exitProgram();
	// 프로그램을 종료하는 함수
};

#endif