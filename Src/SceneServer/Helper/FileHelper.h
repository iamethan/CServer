#ifndef __G_FILEHELPER_H__
#define __G_FILEHELPER_H__

#include <iostream>

using namespace  std;

class FileHelper
{
public:
	char* PrestrainFileHelper(char filePath[128], unsigned short& dataLen, unsigned short& dataCount);
};

#endif // __G_FILEHELPER_H__