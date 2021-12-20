#include<iostream>
using namespace std;
int Factorial(int val)
{
	if (val == 1)return 1;
	int ret = Factorial(val-1);//재귀함수 함수안에서 자신의함수를 호출
	return val * ret;
}
void main()
{
	//팩토리얼 5! = 5*4*3*2*1
	int sum = 1;
	for (int i = 1; i <= 5; i++)
	{
		sum = sum * i;
	}
	cout << sum;
	cout << Factorial(10);

}