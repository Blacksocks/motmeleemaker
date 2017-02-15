#include <stdio.h>

#include "word.h"

void sort(char_t ** list, int * len, const int listLen)
{
	char_t * tmpStr;
	int tmpIdx;
	for(int i = 0; i < listLen - 1; i++)
		for(int j = 0; j < listLen - 1 - i; j++)
			if(len[j] < len[j+1])
			{
				tmpStr = list[j];
				tmpIdx = len[j];
				list[j] = list[j+1];
				len[j] = len[j+1];
				list[j+1] = tmpStr;
				len[j+1] = tmpIdx;
			}
}

void getLettersFromWords(char_t ** list, const int * len, const int listLen, char_t * let, int * letLen)
{
	*letLen = 0;
	for(int wordIdx = 0; wordIdx < listLen; wordIdx++)
		for(int letIdx = 0; letIdx < len[wordIdx]; letIdx++)
		{
			char_t c = list[wordIdx][letIdx];
			int contains = 0;
			for(int i = 0; i < *letLen; i++)
				if(cmpChar(&c, &let[i]))
				{
					contains = 1;
					break;
				}
			if(contains)
				continue;
			setChar(&let[(*letLen)++], &c);
			if(*letLen == MAXLETLEN - 1)
			{
				printf("[ERROR] Too much letter are used\n");
				return;
			}
		}
}

int cmpChar(const char_t * c1, const char_t * c2)
{
	for(int i = 0; i < CHARSIZE; i++)
		if(c1->c[i] != c2->c[i])
			return 0;
	return 1;
}

void setChar(char_t * c1, const char_t * c2)
{
	for(int i = 0; i < CHARSIZE; i++)
		c1->c[i] = c2->c[i];
}
