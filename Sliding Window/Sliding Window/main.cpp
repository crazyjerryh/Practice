/*!
 * file main.cpp
 * author Rotile_H
 * date 2015/09/19
 * 
 */
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <string>
#include <algorithm>
#include <memory.h>

using namespace std;
#define inf 0x3f3f3f3f
#define maxn 1000010

int n,k;
int s[maxn],qmax[maxn],qmin[maxn];
int f1,b1,f2,b2;
int main(void){
	/*freopen("debug.txt","r",stdin);*/
	while(~scanf("%d%d",&n,&k)){
		for(int i=1;i<=n;i++)  scanf("%d",&s[i]);
		f1=b1=f2=b2=0;
		bool flag1=true;
		for(int i=1;i<=n;i++){
			while(f2<b2&&s[qmin[b2-1]]>=s[i]) b2--;
			qmin[b2++]=i;
			if(i<k) continue;
			if(qmin[b2-1]-qmin[f2]>=k) f2++;
			if(flag1)
				printf("%d",s[qmin[f2]]),flag1=false;
			else
				printf(" %d",s[qmin[f2]]);
		}
		printf("\n");
		flag1=true;
		for(int i=1;i<=n;i++){
			while(f1<b1&&s[qmax[b1-1]]<=s[i]) b1--;
			qmax[b1++]=i;
		    if(i<k) continue;
			if(qmax[b1-1]-qmax[f1]>=k) f1++;
			if(flag1)
				printf("%d",s[qmax[f1]]),flag1=false;
			else
				printf(" %d",s[qmax[f1]]);
		}
		printf("\n");
		
	}
	return 0;
}
