/*!
 * file main.cpp
 * author Rotile_H
 * date 2015/09/08
 * shufenzhi
 */
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <memory.h>

using namespace std;
#define inf 0x3f3f3f3f
#define maxn 10010
struct edge{
	int v,w;
	int next;
}edges[maxn<<1];
int head[maxn],size[maxn],fx[maxn],vis[maxn],dep[maxn]; 
int res[maxn];
int cnt,n,k,root;
int sz; 
int ans,tot;

void addegde(int u,int v,int w){
	edges[cnt].v=v,edges[cnt].w=w,edges[cnt].next=head[u],head[u]=cnt++;
	edges[cnt].v=u,edges[cnt].w=w,edges[cnt].next=head[v],head[v]=cnt++;
}

void getroot(int u,int fa){
	size[u]=1,fx[u]=0;
	for(int i=head[u];i!=-1;i=edges[i].next){
		int v=edges[i].v;
		if(v!=fa&&!vis[v]){
			getroot(v,u);
			size[u]+=size[v];
			fx[u]=max(fx[u],size[v]);
		}
	}
	fx[u]=max(fx[u],sz-size[u]);
	if(fx[u]<fx[root]) root=u;
}

void getdep(int u,int fa){
	res[tot++]=dep[u];
	for(int i=head[u];i!=-1;i=edges[i].next){
		int v=edges[i].v;
		if(v!=fa&&!vis[v]){
			dep[v]=dep[u]+edges[i].w;
			getdep(v,u);
		}
	}
}

int cal(int rt,int now){
	int ans=0;
    dep[rt]=now;
	tot=0;
	getdep(rt,0);
	sort(res,res+tot); 
	int l=0,r=tot-1;
	while(l<r){
		if(res[l]+res[r]<=k) ans+=r-l,l++;
		else r--;
	}
	return ans;
}

void solve(int rt){
	vis[rt]=1;
	ans+=cal(rt,0);
	for(int i=head[rt];i!=-1;i=edges[i].next){
		int v=edges[i].v;
		if(!vis[v]){
			ans-=cal(v,edges[i].w);
			root=0;
			sz=size[v];
			getroot(v,0);
			solve(root);
		}
	}
}

int main(void){
	freopen("debug.txt","r",stdin);
	while(~scanf("%d%d",&n,&k)){
		if(n==0) break;
		memset(head,-1,sizeof(head));
		memset(vis,0,sizeof(vis));
		cnt=0;
		for(int i=1;i<n;i++){
			int u,v,w;
			scanf("%d%d%d",&u,&v,&w);
			addegde(u,v,w);
		}
		ans=0;
		fx[0]=inf;
		root=0;
		sz=n;
		getroot(1,0);
		solve(root);
		printf("%d\n",ans);
	}
	return 0;
}