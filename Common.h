#ifndef COMMON_H
#define COMMON_H

using namespace std;

class Common {
	// �� �� �̻��� Ŭ������ �������� ���� ����� ��� Ŭ����
public:
	static int deposit;
	// ��ġ��
	static string username;
	// ������� �г���
	// ��ü ���� ���� ���ǹǷ� static ����
	static void login();
	// ����ڰ� ���α׷� ���� �� ó�� ȣ��Ǵ� �Լ�
	// ����ڰ� �α����� �� �ֵ��� �ϴ� �Լ�
	static void signUp();
	// ȸ�������ϴ� �Լ�
	static bool sign_up_status;
	// ȸ������ ���θ� ��Ÿ���� ����: false�� �ʱ�ȭ
	static string response;
	// ����ڰ� �����ϴ� ���� ���� string ���� response
	static void setHome();
	// ����ڿ��� ���� ����� �����ְ� ���� ���� �Է� �޾� �׿� �ش��ϴ� Ư�� �� ����
	static void exitProgram();
	// ���α׷��� �����ϴ� �Լ�
};

#endif