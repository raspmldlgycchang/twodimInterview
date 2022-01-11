#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<fcntl.h>
void error_handling(char* message);

#define BUF_SIZE 30
typedef enum Num {
	ROCK,
	SCISSORS,
	PAPER
}Num;
typedef unsigned int HANDLE;
struct HandleData {
	HANDLE h;
	char* mp_string;

};
typedef struct HandleData HandleData;
typedef struct gycchang* p_gyc;
struct gycchang {
	HandleData** mp_users;
	unsigned int m_max_count, m_max_user_cnt;
	Num enumObj;
	int intResult;
	unsigned int m_gen_value;
};
void Init2Dim(p_gyc gyc, unsigned int a_max_user_cnt, unsigned int a_max_count)
{
	gyc->m_max_user_cnt = a_max_user_cnt;
	gyc->m_max_count = a_max_count;
	gyc->mp_users = (HandleData**)malloc(sizeof(HandleData*) * gyc->m_max_count);
	for (unsigned int j = 0; j < gyc->m_max_user_cnt; j++) {
		*(gyc->mp_users + j) = (HandleData*)malloc(sizeof(HandleData) * gyc->m_max_count);
	}
	for (unsigned int j = 0; j < gyc->m_max_user_cnt; j++) {
		memset(*(gyc->mp_users + j), 0, sizeof(HandleData) * gyc->m_max_count);
	}
	gyc->m_gen_value = 1;
}
char* IntToBuf(int i);
int Game(int serv, int clnt);
void Free2Dim(p_gyc gyc)
{
	HandleData* p_handle = gyc->mp_users[0];
	for (unsigned int j = 0; j < gyc->m_max_count; j++) {
		p_handle = gyc->mp_users[j];
		unsigned int i;
		for (i = 0; i < gyc->m_max_count; i++) {
			if (p_handle->h) {
				free(p_handle->mp_string);
				p_handle++;
			}
		}
		free((gyc->mp_users)[j]);
	}
	free(gyc->mp_users);
}
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
	printf("�����ֽ� ���ڿ��� ���̸� �Ѿ����ϴ�\n");
	return 0;
}
int CharToInt(char* message)
{
	int clnt_result;
	if (!strcmp(message, "ROCK"))
		clnt_result = 0;
	else if (!strcmp(message, "SCISSORS"))
		clnt_result = 1;
	else if (!strcmp(message, "PAPER"))
		clnt_result = 2;
	else {
		fputs((const char*)"�߸��� �޼����� �Խ��ϴ�", stderr);
		fputc('\n', stderr);
		clnt_result = -1;
		rewind(stdin);
	}
	return clnt_result;
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
int Game(int serv, int clnt)
{
	if (serv == 1 && clnt == 2)
		return -1;
	else if (serv == 0 && clnt == 1)
		return -1;
	else if (serv == 2 && clnt == 0)
		return -1;
	else if (serv == 0 && clnt == 2)
		return 1;
	else if (serv == 1 && clnt == 0)
		return 1;
	else if (serv == 2 && clnt == 1)
		return 1;
	else
		return 0;
}
char* IntToBuf(int i)
{
	char* Buf = (char*)malloc(1);
	sprintf(Buf, "%d", i);
	return Buf;
}
int main(int argc, char* argv[])
{
	int serv_sock, clnt_sock;
	int clnt_adr_sz;
	struct sockaddr_in serv_adr, clnt_adr;
	int str_len, i;
	char message[BUF_SIZE];
	if (argc != 2) {
		printf("Usage : %s <port> \n", argv[0]);
		exit(1);
	}
	serv_sock = socket(PF_INET, SOCK_STREAM, 0);
	if (serv_sock == -1)
		error_handling("socket() error");

	memset(&serv_adr, 0, sizeof(serv_adr));
	serv_adr.sin_family = AF_INET;
	serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_adr.sin_port = htons(atoi(argv[1]));

	if (bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1)
		error_handling("bind() error");
	if (listen(serv_sock, 5) == -1)
		error_handling("listen() eror");
	clnt_adr_sz = sizeof(clnt_sock);
	clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);
	if (clnt_sock == -1)
		error_handling("accept() error");
	else {
		printf("Connected to client %s\n", argv[1]);
		while (!(str_len = read(clnt_sock, message, BUF_SIZE)))
			write(clnt_sock, message, str_len);
	}
	srand((unsigned int)time(NULL));
	enum Num enumObj;
	gycchang gyc;
	unsigned int m_max_user_cnt, m_max_count;
	fputs("�� ���� ����ڸ� �Է��Ͻðھ��?:", stdout);
	rewind(stdin);
	scanf("%d %d", &m_max_user_cnt, &m_max_count);
	//2��������ü �ʱ�ȭ
	Init2Dim(&gyc, m_max_user_cnt, m_max_count);
	int count = 0;
	while (1) {
		if (count == 3)	break;
		printf("================%d��° ����=================\n", count + 1);
		printf("rock, scissors, paper �߿� �Է����ּ��� : ");
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
			printf("rock, scissors, paper �߿��� ����ּ���\n");
		}
		printf("Ŭ���̾�Ʈ �޼��� �ޱ���\n");
		printf("---------------------------\n");

		str_len = read(clnt_sock, message, BUF_SIZE - 1);
		message[BUF_SIZE] = 0;
		int clnt_result = CharToInt(message);
		char* p;
		p = IntToBuf((&gyc)->enumObj);
		int tmp_int = *p - '0';
		int isWin = Game(tmp_int, clnt_result);

		switch (isWin) {
		case -1:
			printf("���� �¸�\n");
			rewind(stdin);
			break;
		case 0:
			printf("���º�\n");
			rewind(stdin);
			break;
		case 1:
			printf("Ŭ�� �¸�\n");
			rewind(stdin);
			break;
		default:
			break;
		}

		count++;
		printf("==============%d��° ���� ��==============\n", count - 1);

	}
	Free2Dim(&gyc);
	close(clnt_sock);
	//���� ����½�Ʈ������
	close(serv_sock);
	return 0;
}
int strcmpprinciple(const char* str1, const char* str2)
{
	int len = strlen(str1);
	//printf("strcmpprinciple:  %s %s\n", str1, str2);
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
void error_handling(char* msg)
{
	fputs(msg, stderr);
	fputc('\n', stderr);
	exit(1);
}