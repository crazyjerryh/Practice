/*���֮���ڶ�����һ��*/
#include <iostream>
#include <vector>
using namespace std;

int tcase,n;
std::vector<int> cards;
unsigned long long dp[60][60];  //60 Ϊ�˿�������ķ���

int _hash(char a,char b)
{
    int type=0;
	switch(b){
	case 'S':
		type=0;
		break;
	case 'H':
		type=1;
		break;
	case 'D':
		type=2;
		break;
	case 'C':
		type=3;
		break;
	}

	int num=0;
	if(a>='2'&&a<='9')
		num=a-'2';  //ÿһ�����ڵ��±�
	if(a=='T')
		num=8;
	else if(a=='J')
		num=9;
	else if(a=='Q')
		num=10;
	else if(a=='K')
		num=11;
	else if(a=='A')
		num=12;
		
    return type*13+num;
}

