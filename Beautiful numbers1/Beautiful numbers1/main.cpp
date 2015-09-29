/*
* author Rotile_H
* file E:\POJ\Practice\Beautiful numbers1\Beautiful numbers1\main.cpp
* 2015 9 29
*/
#include <stdio.h>
#include <memory.h>
#include <algorithm>
#include <string.h>

using namespace std;
#define inf 0x3f3f3f3f
#define maxnd 2520
#define ll long long 

ll dp[20][1<<8][2520];
int bit[20];
int tcase;
ll l,r;


ll dfs(int pos,int limits,int mark,int mod){
	if(!pos){
		for(int i=0;i<8;i++){
			if(mark&(1<<i)&&mod%(i+2)!=0) return 0;
		}
		return 1;
	}
	if(!limits&&dp[pos][mark][mod]!=-1) return dp[pos][mark][mod];
	int len=limits?bit[pos]:9;
	ll ans=0;
	for(int i=0;i<=len;i++){
		ans+=dfs(pos-1,limits&&(bit[pos]==i),i<2?mark:mark|(1<<(i-2)),(mod*10+i)%maxnd);
	}
	if(!limits)  dp[pos][mark][mod]=ans;
	return ans;
}



ll solve(ll n){
 	int len=0;
	while(n){
		bit[++len]=n%10;
		n=n/10;
	}
	return dfs(len,1,0,0);
}

int main(void){
	freopen("debug.txt","r",stdin);
	memset(dp,-1,sizeof(dp));
	scanf("%d",&tcase);
	while(tcase--){
		scanf("%I64d%I64d",&l,&r);
		printf("%I64d\n",solve(r)-solve(l-1));
	}
	return 0;
}