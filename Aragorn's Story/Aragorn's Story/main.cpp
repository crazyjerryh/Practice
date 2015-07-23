#pragma comment(linker, "/STACK:1024000000,1024000000")
#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <algorithm>
using namespace std;
#define maxn  50010
struct edge{
	int v,next;
}edges[maxn*2];
int sz[maxn],dep[maxn],son[maxn],fa[maxn],w[maxn],val[maxn],rk[maxn],tp[maxn];
int sum[maxn],head[maxn];
int tot,cnt;

int n,m,p;

void init(){
	memset(son,-1,sizeof(son));
	memset(sum,0,sizeof(sum));
	memset(head,-1,sizeof(head));
	tot=0,cnt=0;
}

void addedge(int u,int v){
     edges[tot].v=v,edges[tot].next=head[u];
	 head[u]=tot++;
}

int lowbit(int x){
	return x&-x;
}

int getsum(int x){
	int ans=0;
	while(x>0){
		ans+=sum[x];
		x-=lowbit(x);
	}
	return ans;
}

void update(int x,int data){
	while(x<=n){
		sum[x]+=data;
		x+=lowbit(x);
	}
}

void dfs1(int u,int p,int dp){
	fa[u]=p;
	sz[u]=1;
	dep[u]=dp;
	for(int i=head[u];i!=-1;i=edges[i].next){
		int v=edges[i].v;
		if(v!=p){
			dfs1(v,u,dp+1);
			sz[u]+=sz[v];
			if(son[u]==-1||sz[son[u]]<sz[v]) son[u]=v;
		}
	}
}

void dfs2(int u,int top){
	w[u]=++cnt;rk[cnt]=u;
	tp[u]=top;
	if(son[u]==-1) return;
	dfs2(son[u],top);
	for(int i=head[u];i!=-1;i=edges[i].next){
		int v=edges[i].v;
		if(v!=fa[u]&&v!=son[u]){
			dfs2(v,v);
		}
	}
}


void change(int l,int r,int data){
	int f1=tp[l],f2=tp[r];
	while(f1!=f2){
		if(dep[f1]<dep[f2])  swap(l,r),swap(f1,f2);
		update(w[f1],data);
		update(w[l]+1,-data);
		l=fa[f1];
		f1=tp[l];
	}
	if(dep[l]>dep[r]) swap(l,r);
	update(w[l],data);
	update(w[r]+1,-data);
}

void solve(){
	dfs1(1,0,0);
	dfs2(1,1);
	for(int i=1;i<=n;i++)
		update(w[i],val[i]),update(w[i]+1,-val[i]);

	for(int i=0;i<p;i++){
		char str[10];
		scanf("%s",str);
		if(str[0]=='Q'){
			int u;
			scanf("%d",&u);
			int ans=getsum(w[u]);
			printf("%d\n",ans);
		}
		else if(str[0]=='I'){
			int u,tt,v;
			scanf("%d%d%d",&u,&v,&tt);
			change(u,v,tt);
		}
		else if(str[0]=='D'){
			int u,tt,v;
			scanf("%d%d%d",&u,&v,&tt);
			change(u,v,-tt);
		}

	}
}

int main(void){
	//freopen("debug.txt","r",stdin);
	while(scanf("%d%d%d",&n,&m,&p)==3){
		init();
		for(int i=1;i<=n;i++) scanf("%d",&val[i]);
		for(int i=1;i<=m;i++){
			int a,b;
			scanf("%d%d",&a,&b);
			addedge(a,b),addedge(b,a);
		}
		solve();
	}
}