#include <iostream>
#include <fstream>
#include <memory.h>
#include <vector>
using namespace std;
#define maxn 40010
//ifstream fin("debug.txt");
//#define cin fin

struct _graph
{
	int u,v,w;
	int next;
}edge[maxn<<1];   //adj

typedef struct _graph graph;
int tcase;
int n,m;
int father[maxn];
int vis[maxn];
int depth[maxn];
int head[maxn];
int cnt;

void addedge(int a,int b,int w)
{
	edge[cnt].u=a,edge[cnt].v=b,edge[cnt].w=w;
	edge[cnt].next=head[a];head[a]=cnt++;
	edge[cnt].u=b,edge[cnt].v=a,edge[cnt].w=w;
	edge[cnt].next=head[b];head[b]=cnt++;
}

void dfs(int u,int p)
{
	for(int i=head[u];i!=0;i=edge[i].next){
		if(edge[i].v!=p){
			father[edge[i].v]=u;
			depth[edge[i].v]=depth[u]+edge[i].w;
			dfs(edge[i].v,u);
		}
	}
}

int query(int a,int b)
{
	 int a1,b1;
	 a1=a,b1=b;
	 int a2=a;
	 while(father[a]!=0)
	 {
		  vis[a]=a2;
		  a=father[a];
	 }
	 vis[a]=a2;
	 
	 int len=0;
	 while(vis[b]!=a2){
		 b=father[b];
	 }
	 
	 while(father[a2]!=0){
		 vis[a2]=0;
		 a2=father[a2];
	 }
	 vis[a2]=0;
	 return depth[a1]+depth[b1]-2*depth[b];
}


int main(void)
{
	cin>>tcase;
	while(tcase--)
	{
		cin>>n>>m;
		cnt=1;
		memset(depth,0,sizeof(depth));
		memset(vis,0,sizeof(vis));
		memset(head,0,sizeof(head));
		for(int i=0;i<n-1;i++)
		{
             int a,b,w;
			 cin>>a>>b>>w;
			 addedge(a,b,w);
		}

		father[1]=0;
		dfs(1,0); 

		for(int i=0;i<m;i++)
		{
			int a,b;
			cin>>a>>b;
			int len=query(a,b);
			cout<<len<<endl;
		}

	}
	return 0;
}