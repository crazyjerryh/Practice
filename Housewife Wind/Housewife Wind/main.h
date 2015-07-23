//树链剖分
#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <algorithm>
using namespace std;
#define maxn 100110

struct edge{
	int v,w;
	int next;
}edges[maxn];
int sz[maxn],dep[maxn],fa[maxn],son[maxn],tp[maxn],w[maxn],val[maxn],id[maxn];
int head[maxn],sum[maxn];
int n,q,s;
int cnt,tot;

void init(){
	memset(son,-1,sizeof(son));
	memset(sum,0,sizeof(sum));
	memset(head,-1,sizeof(head));
	tot=0,cnt=0;
}

void addedge(int u,int v,int w){
	edges[tot].v=v,edges[tot].w=w,edges[tot].next=head[u];
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
			id[edges[i].w]=v;
			dfs1(v,u,dp+1);
			sz[u]+=sz[v];
			if(son[u]==-1||sz[son[u]]<sz[v]) son[u]=v;
		}
	}
}

void dfs2(int u,int top){
	w[u]=++cnt;
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

//查询点
int query(int l,int r){
	int f1=tp[l],f2=tp[r];
	int ans=0;
	while(f1!=f2){
		if(dep[f1]<dep[f2]) swap(l,r),swap(f1,f2);
		ans+=getsum(w[l])-getsum(w[f1]-1); //f1在上面
		l=fa[f1];
		f1=tp[l];
	}
	if(l==r)  return ans;
	if(dep[l]>dep[r]) swap(l,r);  //r 在上面
	ans+=getsum(w[r])-getsum(w[son[l]]-1);
	return ans;
}

void solve()
{
	dfs1(1,0,0);
	dfs2(1,1);
	for(int i=1;i<n;i++)
		update(w[id[i]],val[i]);

	for(int i=0;i<q;i++){
		int u,ww,t;
		scanf("%d",&t);
		if(t==0){
			scanf("%d",&u);
			int ans=query(s,u);
			printf("%d\n",ans);
			s=u;
		}
		else if(t==1){
			scanf("%d%d",&u,&t);
			update(w[id[u]],t-val[u]); //更新边
		}
	}
}

int main(void){
	//freopen("debug.txt","r",stdin);
	while(scanf("%d%d%d",&n,&q,&s)!=EOF){
		init();
		for(int i=1;i<n;i++){
			int u,v;
			scanf("%d%d%d",&u,&v,&val[i]);
			addedge(u,v,i),addedge(v,u,i);
		}
		solve();
	}
	return 0;
}