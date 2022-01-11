#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define BUF_SIZE 30
typedef enum Num {
	ROCK,
	SCISSORS,
	PAPER
}Num;
typedef struct gycchang* p_gyc;
struct gycchang {
	Num enumObj;
	int intResult;
};
typedef struct gycchang gycchang;
int strcmpprinciple(const char* str1, const char* str2);
void SetString_Int(p_gyc gyc, Num enumObj)
{
	switch (enumObj) {
	case ROCK:
		gyc->enumObj = enumObj;
		gyc->intResult = 0;
		break;
	case SCISSORS:
		gyc->enumObj = enumObj;
		gyc->intResult = 1;
		break;
	case PAPER:
		gyc->enumObj = enumObj;
		gyc->intResult = 2;
		break;
	default:
		break;
	}

}
int main(void)
{
	enum Num enumObj;
	gycchang gyc;
	char message[BUF_SIZE];
	printf("rock, scissors, paper �߿� �Է����ּ��� : ");
	fgets(message, BUF_SIZE, stdin);
	fputs(message, stdout);
	if (!strcmpprinciple(message, (char*)"ROCK"))
	{
		enumObj = ROCK;
		SetString_Int(&gyc, enumObj);
	}
	else if (!strcmpprinciple(message, (char*)"SCISSOR")) {
		enumObj = SCISSORS;
		SetString_Int(&gyc, enumObj);
	}
	else if (!strcmpprinciple(message, (char*)"PAPER")) {
		enumObj = PAPER;
		SetString_Int(&gyc, enumObj);
	}
	else {
		printf("rock, scissors, paper �߿��� ����ּ���\n");
	}

	return 0;
}
int strcmpprinciple(const char* str1, const char* str2)
{
	int len = strlen(str1);
	if (strlen(str2) < len)
		len = strlen(str2);
	for (int i = 0; i < len; i++) {
		//�ι��ڱ��� ���ϸ� �� ª�� ���ڿ��� �ι��ڰ� �񱳵ǹǷ� �ι��ڴ� ���� ���� �ƽ�Ű�ڵ带 �ֱ� ������ �ι��ڱ��� �񱳰� �Ǿ�� �Ѵ�
		//���� �ι����� �ε����� len(��ª�����ڿ���)-1�̶� len�����ص��ȴ�
		int ascii_diff;
		ascii_diff = str1[i] - str2[i];
		if (ascii_diff < 0)	return -1;//A a -> ascii�ڵ� �������� �� ���� ->������ �켱������ �� ����
		else if (ascii_diff > 0)	return 1;//a A -> ascii�ڵ� ������ �� ŭ->������ �켱������ �� ����
		else
			continue;
	}
	//for���� �� ���� ���͵� ��ȯ�� �ȵǸ� �� ���ڿ��� ����
	return 0;
}