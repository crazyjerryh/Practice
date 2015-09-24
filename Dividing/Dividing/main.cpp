/*!
 * file main.cpp
 * author Rotile_H
 * date 2015/09/24
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
#define maxn 240000
int dp[maxn]; 
int num[7],w[1000];
int cnt;

int main(void){
	//freopen("debug.txt","r",stdin);
	int tcase=0;
	while(true){
		for(int i=1;i<=6;i++) scanf("%d",&num[i]);
		if(num[1]==0&&num[2]==0&&num[3]==0&&num[4]==0&&num[5]==0&&num[6]==0) break;
		int sum=0;
		for(int i=1;i<=6;i++) sum+=num[i]*i;
		if(sum&1){
			printf("Collection #%d:\nCan't be divided.\n\n",++tcase);
			continue;;
		}
	 
		//change to 01 pack
		memset(dp,0,sizeof(dp));
		cnt=0;
		for(int i=1;i<=6;i++){
			if(!num[i]) continue;
			int k=1;
			int count=num[i];
			while(k<count){
				w[cnt++]=k*i;
				count-=k;
				k=k*2;
			}
			w[cnt++]=count*i;;
		}
		
		//01 pack
		sum=sum/2;
		for(int i=0;i<cnt;i++){
			for(int j=sum;j>=w[i];j--){
				dp[j]=max(dp[j],dp[j-w[i]]+w[i]);
			}
		}
		if(dp[sum]!=sum)
			 printf("Collection #%d:\nCan't be divided.\n\n",++tcase);
		else 
			printf("Collection #%d:\nCan be divided.\n\n",++tcase);
	}
}
