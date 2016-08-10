/*
 * Main.c
 *
 *  Created on: 2016. 1. 9.
 *      Author: Neutrino Ant
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "DLinkedListMod.h"
#include "Word.h"

#define FILE_READ "letter.txt"
#define FILE_WRITE "result.txt"

// 사용자 편의 공지를 출력 //
void PrintNotice(void);
// 메모장을 읽어서 문자열로 반환 //
char * f2s(char *fliename);
// 결과를 메모장에 출력 //
int s2f(char *filename, List *plist);
// 문자열을 단어별로 쪼개고 전부 소문자로 변경 //
void StrLowTok(char *string);
// 정렬순서 규칙 (알파벳순서) //
int WhoIsPrecede(Word *d1, Word *d2);
// 같은 데이터 저장방식 규칙 (데이터수 증가) //
void OverlapBehavior(Word **pdata);

int main(void)
{
	List list;
	Word *data;
	char *Letters;
	char *letter;
	char yesno;

	ListInit(&list);

	SetSortRule(&list, WhoIsPrecede, OverlapBehavior);  // list의 정렬규칙을 정함

	PrintNotice();
	
	while (1)
	{
		// 사용자 편의 메시지 //
		printf("<" FILE_READ "> ");
		printf("파일을 준비해주세요 ... press [Enter key]");
		getchar();

		if ( (Letters = f2s(FILE_READ)) == NULL) {  // 파일->문자열
			printf("[ERROR] 파일이 존재하지 않습니다...\n");
			continue;
		}

		StrLowTok(Letters);  // 문자열 단순화 작업

		// 각각의 단어를 리스트에 저장 //
		if ( (letter=strtok(Letters, " ")) != NULL)
		{
			LInsert(&list, MakeWord(letter));

			while ( (letter = strtok(NULL, " ")) != NULL)
				LInsert(&list, MakeWord(letter));
		}

		// 동적 메모리 반환 // 
		free(Letters);

		// 저장된 단어와 개수 전체 출력 //
		printf("구별되는 단어의 수: %d \n", LCount(&list));

		if(LFirst(&list, &data))
		{
			ShowWordInfo(data);
			
			while(LNext(&list, &data)) 
				ShowWordInfo(data);
		}
		printf("\n");

		// 파일로 저장 요청 //
		printf("결과를 파일로 저장하시겠습니까? (y/n) : ");
		if ( (yesno=fgetc(stdin)) == 'y')
		{
			if ( s2f(FILE_WRITE, &list) == FALSE) {
				printf("[ERROR] 저장 실패.\n");
			} else {
				printf("[COMPLETE] 저장 완료. ");
				printf("<" FILE_WRITE ">\n");
			}
		}
		fflush(stdin);  // 버퍼 비우기
		
		// 리스트 전체 삭제 //
		if (LFirst(&list, &data))
		{
			LRemove(&list);

			while (LNext(&list, &data))
				LRemove(&list);
		}
	}

	return 0;
}

// 정렬순서 정하는 함수 (알파벳순서) //
int WhoIsPrecede(Word *d1, Word *d2)
{
	return strcmp(GetWord(d1), GetWord(d2));
}

// 같은 데이터 저장방식 정하는 함수 //
void OverlapBehavior(Word **pdata)
{
	IncWordCnt(*pdata);
}

// 사용자 편의 공지를 출력 //
void PrintNotice(void)
{
	printf("┌────────────────────┐\n");
	printf("│ 단어의 수 카운팅 프로그램              │\n");
	printf("│ (LinkedList vers.)                     │\n");
	printf("│                       by NeutrinoAnt   │\n");
	printf("└────────────────────┘\n");
}

// 메모장을 읽어서 문자열로 반환  //
// 파일을 찾지 못하면 NULL을 반환 //
char * f2s(char *filename)
{
	FILE *fp;
	char *string;
	char c;
	int len, i;

	if ( (fp=fopen("letter.txt", "rt")) == NULL)  // 파일 열기
		return NULL;

	fseek(fp, 0, SEEK_END);
	len = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	i = 0;
	string = (char *)malloc(len+1);

	while ( (c = fgetc(fp)) != EOF)
		string[i++] = c;
	string[i] = '\0';

	fclose(fp);  // 파일 닫기

	return string;
}

int s2f(char *filename, List *plist)
{
	FILE *fp;
	Word *data;

	if ( (fp=fopen(filename, "wt")) == 0)
		return FALSE;

	// 저장된 단어와 개수 전체 파일에 출력 //
	fprintf(fp, "구별되는 단어의 수: %d \n\n", LCount(plist));

	if(LFirst(plist, &data))
	{
		fprintf(fp, "%s : %d\n", data->word, data->count);
		
		while(LNext(plist, &data)) 
			fprintf(fp, "%s : %d\n", data->word, data->count);
	}
	printf("\n");

	fclose(fp);
	return TRUE;
}

// 문자열에서 
// 알파벳 외의 문자 전부 공백처리,
// 전부 소문자로 변경
void StrLowTok(char *string)
{
	int i;
	char c;

	i = 0;
	do {
		c = string[i];

		if (isalpha(c)) {
			if (isupper(c))                 // 대문자이면
				string[i] = c + ('a'-'A');  // 소문자로 변경
		} else {                            // 영문자가 아니면
			string[i] = ' ';                // 공백처리
		}
	} while (string[++i] != '\0');   // 다음 문자가 끝이면 종료
}

