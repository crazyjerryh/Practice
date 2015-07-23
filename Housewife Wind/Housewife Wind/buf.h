//树链剖分
#pragma comment(linker,"/STACK:100000000,100000000") 
#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <algorithm>
using namespace std;
#define maxn 100110

struct node{
	int u,v,w;
}nodes[maxn];

struct edge{
	int v;
	int next;
}edges[maxn];
int sz[maxn],dep[maxn],fa[maxn],son[maxn],tp[maxn],w[maxn],a[maxn];
int head[maxn],tree[maxn*4];
int n,q,s;
int cnt,tot;

void init(){
	memset(son,-1,sizeof(son));
	memset(head,-1,sizeof(head));
	tot=0,cnt=0;
}

void addedge(int u,int v){
	edges[tot].v=v,edges[tot].next=head[u];
	head[u]=tot++;
}

void push_up(int rt){
	tree[rt]=tree[rt*2]+tree[rt*2+1];
}

void build(int rt,int l,int r){
	if(l==r){
		tree[rt]=val[pp[rk[l]]];
		return;
	}
	int mid=(l+r)>>1;
	build(rt*2,l,mid);
	build(rt*2+1,mid+1,r);
	push_up(rt);
}

int query(int rt,int l,int r,int L,int R){
	if(l==L&&R==r){
		return tree[rt];
	}
	int mid=(L+R)>>1;
	if(r<=mid) return query(2*rt,l,r,L,mid);
	else if(l>mid) return query(2*rt+1,l,r,mid+1,R);
	else return query(2*rt,l,mid,L,mid)+query(2*rt+1,mid+1,r,mid+1,R);
}

void update(int rt,int l,int r,int loc,int data){
	if(l==r){tree[rt]=data; return;}
	int mid=(l+r)>>1;
	if(loc<=mid)  update(2*rt,l,mid,loc,data);
	else update(2*rt+1,mid+1,r,loc,data);
	push_up(rt);
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
	w[u]=++cnt,rk[cnt]=u;
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
		ans+=query(1,w[f1],w[l],1,n);
		l=fa[f1];
		f1=tp[l];
	}
	if(l==r) return ans;
	if(dep[l]>dep[r]) swap(l,r);  //r 在上面
	ans+=query(1,w[son[l]],w[r],1,n);
	return ans;
}

void solve()
{
	dfs1(1,0,0);
	dfs2(1,1);
	build(1,1,n);
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
			scanf("%d%d",&u,&ww);
			update(1,1,n,w[id[u]],ww);
		}
	}
}

int main(void){
	freopen("debug.txt","r",stdin);
	while(scanf("%d%d%d",&n,&q,&s)!=EOF){
		init();
		for(int i=1;i<n;i++){
			scanf("%d%d%d",&nodes[i].u,&nodes[i].v,&nodes[i].w);
			addedge(nodes[i].u,nodes[i].v),addedge(nodes[i].v,nodes[i].u);
		}
		solve();
	}
	return 0;
}