/*!
 * file main.cpp
 * author Rotile_H
 * date 2015/09/21
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
#define maxn 200

struct edge{
	int v,next;
}edges[maxn<<1];
int head[maxn];
int n,m,cnt,tcase;
int cur;
int mat[maxn][maxn];
int vis[maxn],ans[maxn];

void addedged(int u,int v){
	edges[cnt].v=v,edges[cnt].next=head[u],head[u]=cnt++;
}

void dfs(int tnt,int u){
	mat[tnt][u]=1;
	for(int i=head[u];i!=-1;i=edges[i].next){
		int v=edges[i].v;
		dfs(tnt,v);
	}
}

bool dfs1(int u){
     int num=0;
	 for(int i=head[u];i!=-1;i=edges[i].next) ++num;
	 for(int i=0;i<num;i++){
		 int now=-1;
		 for(int i=head[u];i!=-1;i=edges[i].next){
		      int v=edges[i].v;
			  
			  if(!vis[v]&&mat[v][ans[cur]]){
				  cur++;
				  now=v;
				  break;
			  }
			  if(vis[v]&&mat[v][ans[cur]]) return false;
		 }
		 cout<<now<<endl;
		 if(now!=-1){
		     for(int i=head[u];i=-1;i=edges[i].next){
				 int v=edges[i].v;
				 if(!vis[v]){
				      now=v;
					  break;
				 }
			 }
		 }
		 
		 if(!dfs1(now)) return false;
		 vis[now]=1;
	 }
	 return true;
}

void solve(){
	memset(mat,0,sizeof(mat));
	for(int i=1;i<=n;i++)
		dfs(i,i);

    memset(vis,0,sizeof(vis));	
	cur=0;
	bool res=dfs1(1);
	if(res) printf("YES\n");
	else printf("NO\n");
}

int main(void){
	freopen("debug.txt","r",stdin);
	scanf("%d",&tcase);
	while(tcase--){
		scanf("%d",&n);
		cnt=0;
		memset(head,-1,sizeof(head));
		for(int i=1;i<n;i++){
			int u,v;
			scanf("%d%d",&u,&v);
			addedged(u,v);
		}
		
		scanf("%d",&m);
		for(int i=0;i<m;i++)
			scanf("%d",&ans[i]);
		solve();
	}
}