#include <stdio.h>
#include <iostream>
#include <algorithm>
using namespace std;

int n;
int a[10];
int cmp(const void *a,const void *b) 
{
	return *(int *)a-*(int *)b;
}
int main(void)
{
	cin>>n;
	while(n--){
		for(int i=0;i<6;i++)
			cin>>a[i];
		
		qsort(a,6,sizeof(int),cmp);
		if(a[5]+a[4]<=a[3]+a[2]+a[1])
			cout<<"What a sad story!"<<endl;
		else
			cout<<"Grandpa Shawn is the Winner!"<<endl;
	}

	return 0;
}