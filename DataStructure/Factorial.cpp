#include<iostream>
using namespace std;
int Factorial(int val)
{
	if (val == 1)return 1;
	int ret = Factorial(val-1);//����Լ� �Լ��ȿ��� �ڽ����Լ��� ȣ��
	return val * ret;
}
void main()
{
	//���丮�� 5! = 5*4*3*2*1
	int sum = 1;
	for (int i = 1; i <= 5; i++)
	{
		sum = sum * i;
	}
	cout << sum;
	cout << Factorial(10);

}