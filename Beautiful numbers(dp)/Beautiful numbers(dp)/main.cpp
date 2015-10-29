/*!
 * file main.cpp
 * author Rotile_H
 * date 2015/10/29
 * dp
 */
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <string>
#include <algorithm>
#include <memory.h>

using namespace std;
#define inf 0x3f3f3f3f
#define maxn 20
#define tmod 2520
#define ll long long

int bit[maxn];
ll dp[maxn][1<<8][tmod]; 

int tcase;
ll dfs(int pos,int limits,int mask,int num){
	if(pos==0) {
		for(int i=0;i<8;i++){
			if((mask&(1<<i))&&num%(i+2)!=0) return 0;
		}
		return 1;
	}

	if(!limits&&dp[pos][mask][num]!=-1) return dp[pos][mask][num];
	int len=limits?bit[pos]:9;
	ll ans=0;
	for(int i=0;i<=len;i++){
		ans+=dfs(pos-1,limits&&i==bit[pos],i<2?mask:(mask|(1<<(i-2))),(num*10+i)%tmod);
	}
	if(!limits) dp[pos][mask][num]=ans;
	return  ans;
}

ll solve(ll n){
	int len=0;
	while(n){
		bit[++len]=n%10;
		n=n/10;
	}

	ll ans=dfs(len,1,0,0);
	return ans;
}

int main(void){
	memset(dp,-1,sizeof(dp));
	scanf("%d",&tcase);
	while(tcase--){
		ll l,r;
		scanf("%I64d%I64d",&l,&r);
		ll ans=solve(r)-solve(l-1);
		printf("%I64d\n",ans);
	}
	return 0;
}
