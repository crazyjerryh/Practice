#pragma comment(linker,"/STACK:100000000,100000000")
#include<stdio.h>
#include<iostream>
#include<string.h>
#include<string>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;

#define rep(i,s,t) for(int i=s;i<t;i++)
#define repp(i,s,t) for(int i=s-1;i>=t;i--)
#define clr(a,val) memset(a,val,sizeof(a))
#define N 100005 

struct edge{
	int s,t,w;
}e[N];
struct EDGE{
	int v,next;
}v[N*2];
int n,s,q,op,x,y;
int head[N*2],num;
int dep[N],size[N],son[N],fa[N],top[N],to[N],cnt;

inline void add(int x,int y){
	v[num].v=y,v[num].next=head[x];
	head[x]=num++;
}

inline void dfs1(int now,int pre){
	dep[now]=dep[pre]+1;
	fa[now]=pre;
	size[now]=1;
	son[now]=0;
	for(int i=head[now];i!=-1;i=v[i].next){
		int nxt=v[i].v;
		if(nxt!=pre){
			dfs1(nxt,now);
			size[now]+=size[nxt];
			if(size[son[now]]<size[nxt]){
				son[now]=nxt;
			}
		}
	}
}

inline void dfs2(int now,int tp){
	to[now]=++cnt;
	top[now]=tp;
	if(son[now]) dfs2(son[now],tp);
	for(int i=head[now];i!=-1;i=v[i].next){
		int nxt=v[i].v;
		if(nxt!=son[now] && nxt!=fa[now]){
			dfs2(nxt,nxt);
		}
	}
}

/*************/
int root[N<<2],a[N];
#define L t<<1
#define R t<<1|1

void init(){
	memset(son,-1,sizeof(son));
	memset(head,-1,sizeof(head));
	memset(root,0,sizeof(root));
	num=0,cnt=0;
}


inline void build(int t,int x,int y){
	if(x==y) root[t]=a[x];
	else{
		int mid=(x+y)>>1;
		build(L,x,mid),build(R,mid+1,y);
		root[t]=root[L]+root[R];
	}
}
inline void add(int t,int l,int r,int x,int w){
	if(l==r) root[t]=w;
	else{
		int mid=(l+r)>>1;
		if(x<=mid) add(L,l,mid,x,w);
		else add(R,mid+1,r,x,w);
		root[t]=root[L]+root[R];
	}
}
inline int query(int t,int l,int r,int x,int y){
	if(l>=x && r<=y){
		return root[t];
	}
	else{
		int mid=(l+r)>>1;
		if(y<=mid) return query(L,l,mid,x,y);
		else if(x>mid) return query(R,mid+1,r,x,y);
		else return query(L,l,mid,x,mid)+query(R,mid+1,r,mid+1,y);
	}
}

inline int query(int a,int b)
{
	int temp=0,f1=top[a],f2=top[b];
	while(f1!=f2)
	{
		if(dep[f1]<dep[f2])
		{
			swap(a,b),swap(f1,f2);
		}
		temp+=query(1,1,n,to[f1],to[a]);
		a=fa[f1];
		f1=top[a];
	}
	if(a==b) return temp;
	if(dep[a]>dep[b]) swap(a,b);
	return temp+query(1,1,n,to[son[a]],to[b]);
}

int main(){
	while(~scanf("%d%d%d",&n,&q,&s)){
		init();
		rep(i,1,n){
			scanf("%d%d%d",&e[i].s,&e[i].t,&e[i].w);
			add(e[i].s,e[i].t);
			add(e[i].t,e[i].s);
		}
		dfs1(1,0);
		dfs2(1,1);
		rep(i,1,n){
			if(dep[e[i].s]>dep[e[i].t]){
				swap(e[i].s,e[i].t);
			}
			e[i].t=to[e[i].t];
			a[e[i].t]=e[i].w;
		}
		build(1,1,cnt);
		rep(i,0,q){
			scanf("%d",&op);
			if(op==0){
				scanf("%d",&x);
				printf("%d\n",query(s,x));
				s=x;
			}
			else{
				scanf("%d%d",&x,&y);
				e[x].w=y;
				add(1,1,n,e[x].t,y);
			}
		}
	}
	return 0;
}

