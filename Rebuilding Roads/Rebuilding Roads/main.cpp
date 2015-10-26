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
#define maxn 160
struct edge{
	int v,next;
}tree[maxn<<1];

int head[maxn],cnt;
int dp[maxn][maxn];
int n,p;
void addedge(int u,int v){
	tree[cnt].v=v,tree[cnt].next=head[u],head[u]=cnt++;
}

void dfs(int u,int fa){
	dp[u][1]=0;
	for(int i=head[u];i!=-1;i=tree[i].next){
		int v=tree[i].v;
		if(v==fa) continue;
		dfs(v,u);
		for(int j=p;j>=1;j--){
			int tem=dp[u][j]+1;
			for(int k=1;k<j;k++){
				tem=min(dp[u][k]+dp[v][j-k],tem);
			}
			dp[u][j]=tem;
		}
	}
}

int main(void){
	//freopen("debug.txt","r",stdin);
	while(~scanf("%d%d",&n,&p)){
		memset(head,-1,sizeof(head));
		cnt=0;
		for(int i=0;i<n-1;i++){
			int u,v;
			scanf("%d%d",&u,&v);
			addedge(u,v);
			addedge(v,u);
		}
		
		memset(dp,0x3f,sizeof(dp));
		dfs(1,-1);
		int ans=dp[1][p];
		for(int i=1;i<=n;i++)
			ans=min(dp[i][p]+1,ans);

		printf("%d\n",ans);
	}
	return 0;
}
