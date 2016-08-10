/*
 * DLinkedListMod.c
 *
 *  Created on: 2016. 1. 9.
 *      Author: Neutrino Ant
 */
#include <stdio.h>
#include <stdlib.h>
#include "DLinkedListMod.h"

void ListInit(List * plist)
{
	plist->head = (Node*)malloc(sizeof(Node));
	plist->head->next = NULL;
	plist->comp = NULL;
	plist->overlap = NULL;
	plist->numOfData = 0;
}

void FInsert(List * plist, LData data)
{
	Node * newNode = (Node*)malloc(sizeof(Node));
	newNode->data = data;

	newNode->next = plist->head->next;
	plist->head->next = newNode;

	(plist->numOfData)++;
}

// 같은것이 있을때를 고려한 정렬삽입함수 //
void SDInsert(List * plist, LData data)
{
	Node * newNode = (Node*)malloc(sizeof(Node));
	Node * pred = plist->head;
	newNode->data = data;

	while(pred->next != NULL 
		&& plist->comp(data, pred->next->data) > 0)
	{
		pred = pred->next;
	}

	if (plist->overlap != NULL                        // overlap 함수가 존재하고
		&& pred->next != NULL                         // 비교할 대상이 존재하고
		&& plist->comp(data, pred->next->data) == 0)  // 두 데이터가 같으면
	{
		plist->overlap(&(pred->next->data));
	}
	else
	{
		newNode->next = pred->next;
		pred->next = newNode;
		(plist->numOfData)++;
	}
}


void LInsert(List * plist, LData data)
{
	if(plist->comp == NULL)
		FInsert(plist, data);
	else
		SDInsert(plist, data);
}

int LFirst(List * plist, LData * pdata)
{
	if(plist->head->next == NULL)
		return FALSE;

	plist->before = plist->head;
	plist->cur = plist->head->next;

	*pdata = plist->cur->data;
	return TRUE;
}

int LNext(List * plist, LData * pdata)
{
	if(plist->cur->next == NULL)
		return FALSE;

	plist->before = plist->cur;
	plist->cur = plist->cur->next;

	*pdata = plist->cur->data;
	return TRUE;
}

LData LRemove(List * plist)
{
	Node * rpos = plist->cur;
	LData rdata = rpos->data;

	plist->before->next = plist->cur->next;
	plist->cur = plist->before;

	free(rpos);
	(plist->numOfData)--;
	return rdata;
}

int LCount(List * plist)
{
	return plist->numOfData;
}

void SetSortRule(List * plist, int (*comp)(LData d1, LData d2), void (*overlap)(LData *pdata))
{
	plist->comp = comp;
	plist->overlap = overlap;
}
