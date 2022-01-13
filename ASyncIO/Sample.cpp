#include <windows.h>
#include <iostream>

void main()
{
	HANDLE hFile = CreateFile(L"test.txt", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile != NULL)
	{
		WriteFile();//인자로 소캣을 넘겨주느냐 파일을 넘겨주느냐만 다르고 동일하다
		ReadFile();
	}
	
	CloseHandle(hFile);
}