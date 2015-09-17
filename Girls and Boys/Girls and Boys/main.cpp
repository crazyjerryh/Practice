/*!
 * file main.cpp
 * author Rotile_H
 * date 2015/09/17
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
#define maxn 110000

struct edge{
	int v,next;
}edges[maxn<<1];
int head[maxn],match[maxn],vis[maxn];
int n,cnt;

void addedge(int u,int v){
	edges[cnt].v=v,edges[cnt].next=head[u],head[u]=cnt++;
	edges[cnt].v=u,edges[cnt].next=head[v],head[v]=cnt++;
}

bool dfs(int u){
	for(int i=head[u];i!=-1;i=edges[i].next){
		int v=edges[i].v;
		if(vis[v]) continue;
		vis[v]=1;
		if(match[v]==-1||dfs(match[v])){
			match[v]=u;
			return true;
		}
	}
	return false;
}

int main(void){
	//freopen("debug.txt","r",stdin);
	while(~scanf("%d",&n)){
		memset(head,-1,sizeof(head));
		memset(match,-1,sizeof(match));
		cnt=0;
		for(int i=0;i<n;i++){
			int u,v,m;
			scanf("%d",&u);
			scanf(": (%d)",&m);
			for(int j=0;j<m;j++){
				scanf("%d",&v);
				addedge(u,v);
			}
		}
		int tnt=0;
		for(int i=0;i<n;i++)
		{
			memset(vis,0,sizeof(vis));
			if(dfs(i)) tnt++;
		}
		printf("%d\n",n-tnt/2);
	}
}
