/*!
 * file main.cpp
 * author Rotile_H
 * date 2015/09/12
 *  tree dp
 */
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <string>
#include <algorithm>
#include <memory.h>

using namespace std;
#define inf 0x3f3f3f3f
#define maxn 6100
int rate[maxn];
struct edge{
	int v,w;
	int next;
}edges[maxn<<1];
int cnt,n;
int head[maxn],dp[maxn][2];
int vis[maxn];

void addegde(int u,int v,int w){
	edges[cnt].v=v,edges[cnt].w=w,edges[cnt].next=head[u],head[u]=cnt++;
}

void dfs(int u,int fa){
	dp[u][0]=0,dp[u][1]=rate[u];
    for(int i=head[u];i!=-1;i=edges[i].next){
		int v=edges[i].v;
		if(v!=fa){
			dfs(v,u);
			dp[u][1]+=dp[v][0];
			dp[u][0]+=max(dp[v][1],dp[v][0]);
		}
	}
}

int main(void){
	//freopen("debug.txt","r",stdin);
	while(~scanf("%d",&n)){
		cnt=0;
		memset(head,-1,sizeof(head));
		memset(vis,0,sizeof(vis));
		for(int i=1;i<=n;i++) scanf("%d",&rate[i]);
			int u,v;
		while(scanf("%d%d",&u,&v)){
			if(u==0&&v==0) break;
			addegde(v,u,0);
			vis[u]=1;
		}
		memset(dp,0,sizeof(dp));
		int root;
		for(int i=1;i<=n;i++) if(!vis[i]){
			root=i;
			break;
		}
		dfs(root,0);
		printf("%d\n",max(dp[root][0],dp[root][1]));
	}
}