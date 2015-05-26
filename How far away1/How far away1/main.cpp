#include <iostream>
#include <memory.h>
#include <fstream>
using namespace std;

#define maxn 40010
#define maxm 210
struct _edge
{
	int u,v,w;
	int next;
}edge[maxn<<1];

struct _ques
{
	int u,v,lca;
	int next;
}ques[maxm<<1];

int tcase;
int n,m;
int cnt;
int qcnt;
int head[maxn];
int qhead[maxn];
int vis[maxn];
int depth[maxn];
int ancestor[maxn];
int LCA[maxm];
//ifstream fin("debug.txt");
//#define cin fin

void addedge(int u,int v,int w)
{
	edge[cnt].u=u,edge[cnt].v=v,edge[cnt].w=w;
	edge[cnt].next=head[u],head[u]=cnt++;
	edge[cnt].u=v,edge[cnt].v=u,edge[cnt].w=w;
	edge[cnt].next=head[v],head[v]=cnt++;
}

void addques(int u,int v,int num)
{
	ques[qcnt].u=u,ques[qcnt].v=v,ques[qcnt].lca=num;
	ques[qcnt].next=qhead[u],qhead[u]=qcnt++;
	ques[qcnt].u=v,ques[qcnt].v=u,ques[qcnt].lca=num;
	ques[qcnt].next=qhead[v],qhead[v]=qcnt++;
}

void dfs(int u,int p)
{
	for(int i=head[u];i!=0;i=edge[i].next){
		int v=edge[i].v;
		if(v!=p){
			depth[v]=depth[u]+edge[i].w;
			dfs(v,u);
		}
	}
}

int find(int a)
{
	while(ancestor[a]!=-1)   a=ancestor[a];
	return a;
}

void _union(int a,int b)
{
	int fa=find(a);
	int fb=find(b);
	
	if(fa!=fb){
		ancestor[fb]=fa;
	}
}

void tarjan(int u)
{
	vis[u]=1;
	for(int i=qhead[u];i!=0;i=ques[i].next){
		int v=ques[i].v;
		if(vis[v]){
			LCA[ques[i].lca]=find(v);
		}
	}

	for(int i=head[u];i!=0;i=edge[i].next){
		  int v=edge[i].v;
		  if(!vis[v]){
		    tarjan(v);
		    ancestor[v]=u;
		  }
	}
}

int main(void)
{
	cin>>tcase;
	while(tcase--){
		cin>>n>>m;
		cnt=1;
		qcnt=1;
		memset(head,0,sizeof(head));
		memset(depth,0,sizeof(depth));
		memset(qhead,0,sizeof(qhead));
		memset(vis,0,sizeof(vis));
		for(int i=0;i<maxn;i++)
			ancestor[i]=-1;

		for(int i=0;i<n-1;i++)
		{
			int u,v,w;
			cin>>u>>v>>w;
			addedge(u,v,w);
		}
		dfs(1,0);


		for(int i=1;i<=m;i++){
		    int a,b;
			cin>>a>>b;
			addques(a,b,i);
		}
		tarjan(1);
		int j=1;
		for(int i=1,j=1;i<qcnt;i+=2,j++){
			int a,b;
			a=ques[i].u;
			b=ques[i].v;
			cout<<depth[a]+depth[b]-2*depth[LCA[j]]<<endl;
		}
	}
	return 0;
}