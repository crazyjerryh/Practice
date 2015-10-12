/*!
 * file main.cpp
 * author Rotile_H
 * date 2015/10/12
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
#define maxn 1100

int tcase,w,n;
struct node{
	double ratio;
	int a,b;
	int c;
}nodes[maxn];
int dp[maxn*4];

int cmp(const node& a,const node& b){
	return a.ratio<b.ratio;
}

int solve(){
	memset(dp,0,sizeof(dp));
	for(int i=0;i<n;i++){
		for(int j=w;j>=nodes[i].c;j--)
			dp[j]=max(dp[j],dp[j-nodes[i].c]+nodes[i].a-nodes[i].b*j);
	}
	int mmax=-1;
	for(int i=0;i<=w;i++)   mmax=max(mmax,dp[i]);
	return mmax;
}

int main(void){
	freopen("debug.txt","r",stdin);
	scanf("%d",&tcase);
	while(tcase--){
		scanf("%d%d",&n,&w);
		for(int i=0;i<n;i++){
			int a,b,c;
			scanf("%d%d%d",&a,&b,&c);
			nodes[i].ratio=(double)c/(double)b;
			nodes[i].c=c;
			nodes[i].a=a;
			nodes[i].b=b;
		}
		sort(nodes,nodes+n,cmp);
		int ans=solve();
		printf("%d\n",ans);
	}
	return 0;
}