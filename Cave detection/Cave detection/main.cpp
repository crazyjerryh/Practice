/*!
 * file main.cpp
 * author Rotile_H
 * date 2015/08/07
 * link cut tree first problem
 */

#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <memory.h>

using namespace std;
#define inf 0x3f3f3f3f
#define maxn 100100

int fa[maxn],child[maxn][2],rev[maxn];
int n,m,cnt;

void newnode(){
	++cnt;
	child[cnt][0]=child[cnt][1]=fa[cnt]=rev[cnt]=0;
}

bool isroot(int x){
	if(fa[x]&&(child[fa[x]][0]==x||child[fa[x]][1]==x)) return false;
	return true;
}

void push_down(int x){
	if(!x)  return;
	if(rev[x]){
		swap(child[x][0],child[x][1]);
		rev[child[x][0]]=rev[child[x][0]]^1;
		rev[child[x][1]]=rev[child[x][1]]^1;
		rev[x]=0;
	}
}

void rotate(int x,int kind){
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
}

int access(int u){
	int v=0;
	for(;u;u=fa[u]){
		splay(u);
		child[u][1]=v;
		v=u;
	}
	return v;
}

void make_root(int x){
	int p=access(x);
	rev[p]=rev[p]^1;
	splay(x);
}

int findRoot(int x){
	x=access(x);
    for(;push_down(x),child[x][0]!=0;x=child[x][0]) ;
	splay(x);
	return x;
}

void link(int u,int v){
	if(findRoot(u)==findRoot(v)) return;
	make_root(u);
	fa[u]=v;
	access(u);
}

void cut(int u,int v){
	if(u==v||findRoot(u)!=findRoot(v)) return;
	make_root(u);
    access(v);
	splay(v);
	fa[child[v][0]]=0;
	child[v][0]=0;
}

int main(void){
	freopen("debug.txt","r",stdin);
	while(scanf("%d%d",&n,&m)!=EOF){
		cnt=0;
		for(int i=1;i<=n;i++)  newnode();
		char str[300];
		for(int i=1;i<=m;i++){
			scanf("%s",str);
			int u,v;
			scanf("%d%d",&u,&v);
			if(str[0]=='Q'){
				if(findRoot(u)==findRoot(v)) printf("Yes\n");
				else  printf("No\n");
			}
			else if(str[0]=='C'){
				link(u,v);
			}
			else if(str[0]=='D'){
				cut(u,v);
			}
		}
	}
}