/*
 * Word.c
 *
 *  Created on: 2016. 1. 9.
 *      Author: Neutrino Ant
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Word.h"

Word * MakeWord(char *_string)
{
	Word *newWord = (Word *)malloc(sizeof(Word));
	char *string = (char *)malloc( strlen(_string));
	strcpy(string, _string);
	newWord->word = string;
	newWord->count = 1;
	
	return newWord;
}

void ShowWordInfo(Word *word)
{
	printf("%s : %d \n", word->word, word->count);
}

const char *GetWord(Word *word)
{
	return word->word;
}

int GetWordCnt(Word *word)
{
	return word->count;
}

void IncWordCnt(Word *word)
{
	word->count++;
}
