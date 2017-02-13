#include <stdio.h>

#include "word.h"

void sort(char ** list, int * len, const int listLen)
{
	char * tmpStr;
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

void getLettersFromWords(char ** list, int * len, int listLen, char * let, int * letLen)
{
	*letLen = 0;
	for(int wordIdx = 0; wordIdx < listLen; wordIdx++)
		for(int letIdx = 0; letIdx < len[wordIdx]; letIdx++)
		{
			char c = list[wordIdx][letIdx];
			int contains = 0;
			for(int i = 0; i < *letLen; i++)
				if(c == let[i])
				{
					contains = 1;
					break;
				}
			if(contains)
				continue;
			let[(*letLen)++] = c;
			if(*letLen == MAXLETLEN - 1)
			{
				printf("[ERROR] Too much letter are used\n");
				return;
			}
		}
}
