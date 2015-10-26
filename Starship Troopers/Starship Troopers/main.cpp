/*!
 * file main.cpp
 * author Rotile_H
 * date 2015/10/26
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
#define maxn 200
struct edge{
	int v,next;
}tree[maxn<<1];
int w[maxn],p[maxn];
int head[maxn];
int n,sum;
int cnt;
int dp[maxn][maxn];

void addedge(int u,int v){
	tree[cnt].v=v,tree[cnt].next=head[u],head[u]=cnt++;
}

void dfs(int u,int fa){
	for(int i=w[u];i<=sum;i++) dp[u][i]=p[u];
	for(int i=head[u];i!=-1;i=tree[i].next){
		int v=tree[i].v;
		if(v==fa) continue;
		dfs(v,u);
		for(int j=sum;j>=w[u];j--){
			for(int k=1;k<=j-w[u];k++){
				dp[u][j]=max(dp[u][j],dp[u][j-k]+dp[v][k]);
			}
		}
	}
}

int main(void){
	//freopen("debug.txt","r",stdin);
	while(~scanf("%d%d",&n,&sum)){
		if(n==-1&&sum==-1) break;
		memset(head,-1,sizeof(head));
		memset(dp,0,sizeof(dp));
		cnt=0;
		for(int i=1;i<=n;i++){
			scanf("%d%d",&w[i],&p[i]);
			w[i]=(w[i]+19)/20; 
		}
		
		for(int i=0;i<n-1;i++){
			int u,v;
			scanf("%d%d",&u,&v);
			addedge(u,v);
			addedge(v,u);
		}
		memset(dp,0,sizeof(dp));
		if(sum==0){
			printf("0\n");
			continue;
		}
		dfs(1,-1);
		printf("%d\n",dp[1][sum]);
	}
}