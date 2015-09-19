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
#define ll long long
#define maxn 30
#define tmod 1000000007

struct node{
	ll num,sum;
	node(ll _num,ll _sum):num(_num),sum(_sum){}
	node(){}
};

ll ten[maxn];
int bit[maxn];
node dp[30][30][400];
ll l,r,k;

node dfs(int pos,int s,int zero,int limit,ll sum){
	if(pos<0) return node(k==sum,0);
	else{
		int len=limit?bit[pos]:9;
		if(!limit&&!zero&&dp[pos][s][sum+200].num!=-1) return dp[pos][s][sum+200];
		else
		{
			node ans(0,0);
			for(int i=0;i<=len;i++){
				node tmp(0,0);
				if(zero){
					if(!i) tmp=dfs(pos-1,0,1,limit&&(bit[pos]==i),0); 
					else tmp=dfs(pos-1,1,0,limit&&(bit[pos]==i),i);
				}
				else
				   tmp=dfs(pos-1,s+1,0,limit&&(bit[pos]==i),sum+(s&1?-i:i));
				ans.num=(ans.num+tmp.num)%tmod;
				ans.sum=(ans.sum+tmp.sum+(tmp.num*ten[pos]*i)%tmod)%tmod;
			}
			if(!zero&&!limit) dp[pos][s][sum+200]=ans;
			return ans;
		}
		
	}
}

ll solve(ll x){
	if(x<=0) return 0;
	int len=0;
	while(x){
		bit[len++]=x%10;
		x=x/10;
	}
    node ans=dfs(len-1,0,1,1,0);  
	return ans.sum;
}

int main(void){
	//freopen("debug.txt","r",stdin);
	ten[0]=1;
	for(int i=1;i<maxn;i++) ten[i]=ten[i-1]*10%tmod;
	while(cin>>l>>r>>k){
		for(int i=0;i<30;i++)
			for(int j=0;j<30;j++)
				for(int t=0;t<400;t++) 
					  dp[i][j][t].num=-1,dp[i][j][t].sum=0;
		cout<<(solve(r)-solve(l-1)+tmod)%tmod<<endl;
	}
}
