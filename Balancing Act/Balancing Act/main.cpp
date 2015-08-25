/*!
 * file main.cpp
 * author Rotile_H
 * date 2015/08/25
 * 
 */
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <memory.h>

using namespace std;
#define inf 0x3f3f3f3f
#define maxn 20010

struct edge{
	int v;
	int next;
}edges[maxn<<2];

int tcase,n;
int cnt;
int head[maxn],size[maxn],son[maxn];
void addedge(int u,int v){
	edges[cnt].v=v,edges[cnt].next=head[u],head[u]=cnt++;
	edges[cnt].v=u;edges[cnt].next=head[v],head[v]=cnt++;
}

void dfs(int u,int p){
	size[u]=1;
	for(int i=head[u];i!=-1;i=edges[i].next){
		int v=edges[i].v;
		if(v!=p){
			dfs(v,u);
			size[u]+=size[v];
			if(son[u]<size[v])  son[u]=size[v];
		}
	}
	if(son[u]<n-size[u])  son[u]=n-size[u];
}

int main(void){
	//freopen("debug.txt","r",stdin);
	scanf("%d",&tcase);
	while(tcase--){
		scanf("%d",&n);
		cnt=0;
		memset(head,-1,sizeof(head));
		memset(size,0,sizeof(size));
		memset(son,0,sizeof(son));
		for(int i=0;i<n-1;i++){
			int u,v;
			scanf("%d%d",&u,&v);
			addedge(u,v);
		}
		dfs(1,0);
        int ans=inf,ansi;
		for(int i=1;i<=n;i++)  if(ans>son[i])  ans=son[i],ansi=i;
		printf("%d %d\n",ansi,ans);
	}
}
