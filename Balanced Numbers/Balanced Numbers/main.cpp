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
#define ll long long
#define maxn 20
int bit[maxn];
ll dp[maxn][1<<10][1<<10];

int tcase;

int isok(int s,int w)
{
	if(!w)   return 0;
	for(int i=0; i<10; i++) 
	{
		if( i%2==0 && (w&(1<<i)) && (s&(1<<i))==0 ) return 0;    //Å¼Êý
		if( i%2!=0 && (w&(1<<i)) && (s&(1<<i))!=0 ) return 0;
	}
	return 1;
} 
ll dfs(int i,int s,int w,int sum,bool e)
{
	if(i==0)            return isok(s,w);
	if(!e&&dp[i][s][w]!=-1) return dp[i][s][w];

	ll ans=0;
	int u= e? bit[i]: 9;
	for(int d=0; d<=u; d++)
	{
		int ww=w, ss=s;
		if( sum+d!=0 ) ww|=1<<d,ss^=1<<d;
		ans+=dfs(i-1, ss, ww, sum+d, e&&d==u);
	}
	return e? ans: dp[i][s][w]=ans;
}

ll solve(ll n){
	int len=0;
	if(n==0) return 0;
	while(n){
		bit[++len]=n%10;
		n=n/10;
	}
	return dfs(len,0,0,0,1);
}

int main(void){
	//freopen("debug.txt","r",stdin);
	memset(dp,-1,sizeof(dp));
	scanf("%d",&tcase);
	while(tcase--){
		ll l,r;
		cin>>l>>r;
		ll ans=solve(r)-solve(l-1);
		cout<<ans<<endl;
	}
	return 0;
}
