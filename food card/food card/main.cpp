/*!
 * file main.cpp
 * author Rotile_H
 * date 2015/09/22
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
#define maxn 2000

int n,m,s[maxn];
int dp[maxn];
int main(void){
	//freopen("debug.txt","r",stdin);
	while(~scanf("%d",&n)){
		if(n==0) break;
		for(int i=1;i<=n;i++) scanf("%d",&s[i]);
		sort(s+1,s+n+1);
		scanf("%d",&m);
		memset(dp,0,sizeof(dp));
		if(m<5){
			printf("%d\n",m);
			continue;
		}
		for(int i=1;i<n;i++){
			for(int j=m-5;j>=s[i];j--)
				dp[j]=max(dp[j],dp[j-s[i]]+s[i]);
		}
		printf("%d\n",m-dp[m-5]-s[n]);
	}
}
