#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
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
int GetMyString(char buf[], int limit) {
	unsigned int i;
	for (i = 0; i < limit - 1; i++) {
		buf[i] = getchar();
		if (buf[i] == '\n') {
			buf[i] = 0;
			return 1;
		}
	}
	buf[i] = 0;
	printf("정해주신 문자열의 길이를 넘었습니다\n");
	return 0;
}
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
	srand((unsigned int)time(NULL));
	enum Num enumObj;
	gycchang gyc;
	char message[BUF_SIZE];
	printf("rock, scissors, paper 중에 입력해주세요 : ");
	//fgets(message, BUF_SIZE, stdin);
	GetMyString(message, BUF_SIZE);
	rewind(stdin);
	fputs(message, stdout);
	rewind(stdin);
	if (!strcmpprinciple(message, (char*)"ROCK"))
	{
		enumObj = ROCK;
		SetString_Int(&gyc, enumObj);
	}
	else if (!strcmpprinciple(message, (char*)"SCISSORS")) {
		enumObj = SCISSORS;
		SetString_Int(&gyc, enumObj);
	}
	else if (!strcmpprinciple(message, (char*)"PAPER")) {
		enumObj = PAPER;
		SetString_Int(&gyc, enumObj);
	}
	else {
		printf("rock, scissors, paper 중에서 골라주세요\n");
	}

	return 0;
}
int strcmpprinciple(const char* str1, const char* str2)
{
	int len = strlen(str1);
	//printf("strcmpprinciple:  %s %s\n", str1, str2);
	if (strlen(str2) < len)
		len = strlen(str2);
	for (int i = 0; i < len; i++) {
		//널문자까지 비교하면 더 짧은 문자열의 널문자가 비교되므로 널문자는 가장 작은 아스키코드를 주기 때문에 널문자까지 비교가 되어야 한다
		//따라서 널문자의 인덱스는 len(더짧은문자열명)-1이라서 len으로해도된다
		int ascii_diff;
		ascii_diff = str1[i] - str2[i];
		if (ascii_diff < 0)	return -1;//A a -> ascii코드 오른쪽이 더 높음 ->왼쪽이 우선순위가 더 높음
		else if (ascii_diff > 0)	return 1;//a A -> ascii코드 왼쪽이 더 큼->오른쪽 우선순위가 더 높음
		else
			continue;
	}
	//for문을 다 돌고 나와도 반환이 안되면 두 문자열은 동일
	return 0;
}