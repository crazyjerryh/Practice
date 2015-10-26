/*!
 * file main.cpp
 * author Rotile_H
 * date 2015/10/17
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
#define maxn  10100

struct edge{
	int v,next;
}edges[maxn<<1];
int head[maxn],instack[maxn],dfn[maxn],low[maxn],stk[maxn];
int belong[maxn],degree[maxn]; 
int n,m,tm,tp,scc,cnt;

void addedge(int u,int v){
    edges[cnt].v=v,edges[cnt].next=head[u],head[u]=cnt++;
	edges[cnt].v=u,edges[cnt].next=head[v],head[v]=cnt++;
}

void dfs(int u,int fa){
	low[u]=dfn[u]=++tm;
	stk[++tp]=u;
	instack[u]=1;
	for(int i=head[u];i!=-1;i=edges[i].next){
		    int v=edges[i].v;
			if(v==fa) continue;
			if(!dfn[v]){
				dfs(v,u);
				low[u]=min(low[v],low[u]);
			}
			else if(instack[v]) low[u]=min(low[u],dfn[v]); 
		
	}

	if(dfn[u]==low[u]){
		scc++;
	    while(1){
			int v=stk[tp--];
			belong[v]=scc;
			instack[v]=0;
			if(u==v) break;
		}
	}
}

int tcase;

int main(void){
	//freopen("debug.txt","r",stdin);
	tcase=0;
	while(~scanf("%d%d",&n,&m)){
		cnt=tm=tp=scc=0;
		memset(head,-1,sizeof(head));
		memset(dfn,0,sizeof(dfn));
		memset(dfn,0,sizeof(dfn));
		memset(low,0,sizeof(low));
		memset(instack,0,sizeof(instack));
		memset(degree,0,sizeof(degree));
		for(int i=0;i<m;i++){
			int u,v;
			scanf("%d%d",&u,&v);
			addedge(u,v);
		}
		
		for(int i=1;i<=n;i++)
			if(!dfn[i]) 
				dfs(i,-1);
		
		for(int u=1;u<=n;u++){
			for(int i=head[u];i!=-1;i=edges[i].next){
				int v=edges[i].v;
				if(belong[u]!=belong[v])
					degree[belong[u]]++;
			}
		}

		int ans=0;
		for(int i=1;i<=n;i++)
			if(degree[i]==1) 
				ans++;
		
		printf("%d\n",(ans+1)/2);
	}
	return 0;
}