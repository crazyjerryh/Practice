/*!
 * file main.cpp
 * author Rotile_H
 * date 2015/10/13
 * http://acm.hust.edu.cn/vjudge/contest/view.action?cid=94846#problem/A
 */
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <string>
#include <algorithm>
#include <memory.h>
#pragma comment(linker, "/STACK:16777216")

using namespace std;
#define inf 0x3f3f3f3f
#define maxn 100100
struct node{
	int v,w;
	int next;
}tree[maxn*2];

int n,cnt;
int head[maxn],sz[maxn];
int csz[maxn];
int ans;
int c1[5],c2[5];
void addedge(int u,int v,int w){
	tree[cnt].v=v,tree[cnt].w=w,tree[cnt].next=head[u],head[u]=cnt++;
}

//mother function
int cal(int cnum){
	if(cnum<=2) return 0;
	memset(c1,0,sizeof(0)),memset(c2,0,sizeof(c2));
	c1[0]=1,c1[1]=csz[1];
	for(int i=2;i<=cnum;i++){
		for(int j=1;j<=4;j++)
			c2[j]=c1[j-1]*csz[i];
		for(int j=0;j<=4;j++) c1[j]+=c2[j];
		memset(c2,0,sizeof(c2));
	}
	return c1[3];
}

void dfs(int u,int pa){
	sz[u]=1;
	int cnum=0;
	for(int i=head[u];i!=-1;i=tree[i].next){
		int v=tree[i].v;
		if(v!=pa){
			dfs(v,u);
			sz[u]+=sz[v];
			csz[++cnum]=sz[v];
		}
	}
	ans+=cal(cnum);
}

int main(void){
	freopen("debug.txt","r",stdin);
	while(~scanf("%d",&n)){
		int u,v;
		cnt=ans=0;
		memset(head,-1,sizeof(head));
		for(int i=0;i<n-1;i++){
			scanf("%d%d",&u,&v);
			addedge(u,v,1);
		}
		dfs(1,0);
		printf("%d\n",ans);
	}
	return 0;
}
