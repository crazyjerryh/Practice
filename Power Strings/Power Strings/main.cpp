#include <stdio.h>
#include <iostream>
#include <string.h>
#include <memory.h>
#include <algorithm>
using namespace std;
#define maxn 1000001
int _next[maxn];
char str[maxn];
int main(void){
	//freopen("debug.txt","r",stdin);
	while(scanf("%s",str)!=EOF){
		if(str[0]=='.') break;
		int n=strlen(str);
		_next[0]=0;
		for(int i=1;i<n;i++){
			int j=_next[i-1];
			while(j>0&&str[i]!=str[j])  j=_next[j-1];
			if(str[i]==str[j]) _next[i]=j+1;
			else  _next[i]=0;
		}
		int tmp=_next[n-1];
		if(n%(n-tmp)==0)  printf("%d\n",n/(n-tmp));
		else  printf("%d\n",1);
	}
}

