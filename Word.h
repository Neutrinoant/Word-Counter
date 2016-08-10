/*
 * Word.h
 *
 *  Created on: 2016. 1. 9.
 *      Author: Neutrino Ant
 */
#ifndef __WORD_H__
#define __WORD_H__

typedef struct _word
{
	const char *word;
	int count;
} Word;

Word * MakeWord(char *string);        // 단어 생성
void ShowWordInfo(Word *word);    // 단어 정보 출력
const char * GetWord(Word *word);  // 단어를 반환
int GetWordCnt(Word *word);       // 단어 수를 반환
void IncWordCnt(Word *word);      // 해당 단어의 수 증가

#endif
