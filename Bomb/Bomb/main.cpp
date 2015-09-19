/*
* author Rotile_H
* file E:\POJ\Practice\Bomb\Bomb\main.cpp
* 2015 9 16
*/
#include <stdio.h>
#include <memory.h>
#include <algorithm>
#include <string.h>

using namespace std;
#define inf 0x3f3f3f3f
#define maxn 70
#define ll __int64

ll dp[maxn][20];
int bit[maxn];
int tcase;
ll n;

ll dfs(int p,int num,int status,int limit){
	if(p<=0){
		if(status==1&&num==9) dp[p][num]=0;
		else dp[p][num]=1;
		return dp[p][num];
	}

	if(status==1&&num==9)  return 0;
	if(!limit&&dp[p][num]) return dp[p][num];
	int len=limit?bit[p-1]:9;
	ll ans=0;
	for(int i=0;i<=len;i++){
		//if(i==9&&num==4) continue;
		ans+=dfs(p-1,i,num==4,limit&&(i==len));
	}

	return dp[p][num]=ans;
}

int main(void){
	//freopen("debug.txt","r",stdin);
	scanf("%d",&tcase);
	while(tcase--){
		scanf("%I64d",&n);
		ll tmp=n;
		if(n==0){
			printf("0\n");
			continue;
		}
		
		int len=0;
		while(n){
			bit[len++]=n%10;
			n=n/10;
		}
		memset(dp,0,sizeof(dp));
		ll ans=dfs(len,0,0,1);
		printf("%I64d\n",tmp+1-ans);
	}
	return 0;
}