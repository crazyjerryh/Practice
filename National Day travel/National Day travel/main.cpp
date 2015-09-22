/*
* author Rotile_H
* file E:\POJ\Practice\National Day travel\National Day travel\main.cpp
* 2015 9 22
*/
#include <stdio.h>
#include <memory.h>
#include <vector>
#include <iostream>
#include <bitset>
#include <algorithm>
#include <string.h>

using namespace std;
#define inf 0x3f3f3f3f
#define maxn 200

vector<int> mat[maxn];
bitset<maxn> can[maxn];
int vis[maxn],ans[maxn];
int tcase,n,m,cur;
bool res;

void dfs(int u,int fa){
	 can[u][u]=1;
     for(int i=0;i<mat[u].size();i++){
		 int v=mat[u][i];
		 if(v!=fa){
		      dfs(v,u);
			  can[u]|=can[v];
		 }
	 }
}

void dfs1(int u,int fa){
	if(u==ans[cur]) cur++;
	if(cur==m) {
		res=true;
		return;
	}
	while(true){
		int flag=1;
		for(int i=0;i<mat[u].size();i++){
			if(mat[u][i]==fa)  continue;
		    int v=mat[u][i];
			if(!vis[v]&&can[v][ans[cur]]){
				vis[v]=1;
				dfs1(v,u);
				flag=0;
				break;
			}
		}
		if(flag)  break;
	}
	return;
}

int main(void){
	//freopen("debug.txt","r",stdin);
	scanf("%d",&tcase);
	while(tcase--){
		scanf("%d",&n);
		for(int i=0;i<maxn;i++)  mat[i].clear();
		for(int i=1;i<n;i++){
			int u,v;
			scanf("%d%d",&u,&v);
			mat[u].push_back(v);
			mat[v].push_back(u);
		}
		for(int i = 1;i <= n;i++)  
			can[i].reset(); 
		dfs(1,0);
		scanf("%d",&m);
		for(int i=0;i<m;i++) scanf("%d",&ans[i]);
		memset(vis,0,sizeof(vis));
		cur=0;
		res=0;
		dfs1(1,0);
		if(res) printf("YES\n");
		else printf("NO\n");
	}
}
