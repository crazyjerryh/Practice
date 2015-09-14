/*!
 * file main.cpp
 * author Rotile_H
 * date 2015/09/12
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
#define maxn 200100

int tree[maxn],child[maxn][2],sz[maxn],fa[maxn],rev[maxn];
int tot,a[maxn],n,q;

void init(){
	memset(tree,0,sizeof(tree));
	memset(child,0,sizeof(child));
	memset(sz,0,sizeof(sz));
	memset(fa,0,sizeof(fa));
	memset(rev,0,sizeof(rev));
}

void push_up(int rt){
    sz[rt]=sz[child[rt][0]]+sz[child[rt][1]]+1;	
}

bool isroot(int x){
	if(fa[x]&&(child[fa[x]][0]==x||child[fa[x]][1]==x)) return false;
	return true;
}

void push_down(int x){

}

void rotate(int x,int kind){
	int y=fa[x];
	if(isroot(x))return;
	else{
		int y=fa[x];
		child[y][!kind]=child[x][kind];
		if(child[x][kind]) fa[child[x][kind]]=y;
		child[x][kind]=y;
		if(!isroot(y)){
			if(fa[y]){
				if(child[fa[y]][0]==y)
					child[fa[y]][0]=x;
				else if(child[fa[y]][1]==y)
					child[fa[y]][1]=x;
			}
		}
		fa[x]=fa[y];
		fa[y]=x;
	}
	push_up(y);
}

void splay(int x)
{
	int y,z;
	int kind;
	push_down(x);
	while(!isroot(x))
	{
		y=fa[x],z=fa[y];
		if(isroot(y))
		{
			push_down(y);push_down(x);
			kind=(child[fa[x]][0]==x);
			rotate(x,kind);
		}
		else
		{
			push_down(z);push_down(y);push_down(x);
			kind=(child[fa[y]][0]==y);
			if(child[y][kind]==x){
				rotate(x,!kind);
				rotate(x,kind);
			}
			else{
				rotate(x,kind);
				rotate(x,kind);
			}
		}
	}
	push_up(x);
}

int access(int u){
	int v=0;
	for(;u;u=fa[u]){
		splay(u);
		child[u][1]=v;
		v=u;
		push_up(u);
	}
	return v;
}

void link(int x,int y){
	splay(y);
	fa[y]=x;
	access(y);
}

void cut(int x){
	access(x);
	splay(x);
	fa[child[x][0]]=0;
	child[x][0]=0;
	push_up(x);
}

int query(int x){
	access(x);
	splay(x);
	return sz[child[x][0]]+1;
}

int main(void){
	//freopen("debug.txt","r",stdin);
	while(~scanf("%d",&n)){
		init();
		for(int i=1;i<=n;i++) scanf("%d",&a[i]);
		sz[0]=0;
		for(int i=n;i>=1;i--){
			if(a[i]+i>n) fa[i]=0;
			else fa[i]=a[i]+i;
			sz[i]=1;
		}

		scanf("%d",&q);
		for(int i=1;i<=q;i++){
			int c,s,w;
			scanf("%d",&c);
			if(c==1){
				scanf("%d",&s);
				s++;
				printf("%d\n",query(s));
			}
			else
			{
				scanf("%d%d",&s,&w);
				s++;
				if(s+a[s]<=n)  cut(s);
				a[s]=w;
				if(s+a[s]<=n) link(s+a[s],s);
			}
		}
	}
	return 0;
}
