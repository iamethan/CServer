
#include "stdafx.h"  
#include "FileHelper.h"
#include <vector>
#include <iostream>
#include <string>

char* FileHelper::PrestrainFileHelper(char filePath[128], unsigned short& dataLen, unsigned short& dataCount)
{
	int iReadCount =0;
	dataLen = 0;
	dataCount = 0;

	//unsigned short a =*dataLen;

	FILE* pFile =NULL;
	fopen_s(&pFile, filePath, "rb");

	if(pFile== NULL)
		return NULL;
	fseek(pFile, 0, SEEK_END);
	int iFileLen = ftell(pFile);
	fseek(pFile, 0, SEEK_SET);

	if(iFileLen<=0)
		return NULL;

	iReadCount =fread_s(&dataLen, sizeof(unsigned short), sizeof(unsigned short), 1, pFile);
	iReadCount =fread_s(&dataCount, sizeof(unsigned short), sizeof(unsigned short), 1, pFile);

	char* buffer =new char[dataLen * dataCount];

	iReadCount = fread_s(buffer, dataLen * dataCount, sizeof(unsigned char), dataLen * dataCount, pFile);

	fclose(pFile);
	return buffer;
}