#include <windows.h>
#include <iostream>

void main()
{
	HANDLE hFile = CreateFile(L"test.txt", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile != NULL)
	{
		WriteFile();//���ڷ� ��Ĺ�� �Ѱ��ִ��� ������ �Ѱ��ִ��ĸ� �ٸ��� �����ϴ�
		ReadFile();
	}
	
	CloseHandle(hFile);
}