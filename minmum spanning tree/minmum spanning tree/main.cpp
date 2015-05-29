#include <stdio.h>
#include <utility>
#include <vector>
#include <algorithm>
#include <memory.h>
#define maxm 100010
#define maxn 300010
using namespace std;

struct _edge
{
	int u,v,w;
}edges[maxn];
typedef struct _edge edge;
int cnt;
int head[maxm];
int ancestor[maxm];
pair<int,int> father[maxm];
vector<pair<int,int>> graph[maxm];
int vis[maxn];
int vvis[maxn];
int w[maxn],s[maxn];
int n,m;
int minval;

int cmp(const void *a,const void *b)
{
	edge a1=*(edge *)a;
	edge b1=*(edge *)b;
	return a1.w>b1.w;
}

int find(int a)
{
    while(ancestor[a]!=-1) a=ancestor[a];
	return a;
}

bool _union(int a,int b)
{
	int fa=find(a);
	int fb=find(b);
	if(fa!=fb)
	{
	   ancestor[fa]=fb;
	   return true;
	}
	return false;
}

void kruskal()
{
	cnt=0;
	for(int i=0;i<m;i++){
		edge now=edges[i];
		if(_union(now.u,now.v))
		{
			vis[i]=true;
			w[cnt]=now.w;
			minval+=w[cnt];
			graph[now.u].push_back(make_pair(now.v,cnt));
			graph[now.v].push_back(make_pair(now.u,cnt));
			cnt++;
		}
	}

	printf("Ê÷\n");
	for(int i=1;i<=n;i++){
		int size=graph[i].size();
		for(int j=0;j<size;j++)
			printf("%d %d ",graph[i][j].first,graph[i][j].second);
		printf("\n");
	}

	printf("buffer\n");
	for(int i=0;i<cnt;i++)
		printf("%d ",w[i]);
	printf("\n");
}

void dfs(int u,int p)
{   	
     int size=graph[u].size();
	 for(int i=0;i<size;i++){
		 int v=graph[u][i].first;
		 if(v!=p){
			 father[v]=make_pair(u,graph[u][i].second);
			 dfs(v,u);
		 }
	 }


}

void link_edge(int u,int v,int w)
{
	printf("link edge\n");
	int a=u,b=v;
	while(father[a].first!=-1)  {
		vvis[a]=u;
		a=father[a].first;
		printf("%d\n",a);
	}
	vvis[a]=u;

	printf("b %d\n",b);
	while(vvis[b]!=u){
		int id=father[b].second;
		if(!s[id])
			s[id]=w;
		b=father[b].first;
		printf("%d\n",b);
	}

	int c=u;
	while(c!=b){
		int id=father[c].second;
		if(!s[id])
			s[id]=w;
		c=father[c].first;
	}
}

void solve()
{
	father[1]=make_pair(-1,-1);
	dfs(1,-1);
	printf("father:\n");
	for(int i=1;i<=n;i++){
		printf("%d %d\n",father[i].first,father[i].second);
	}
	for(int i=0;i<m;i++){
		if(vis[i])  continue;
		int u=edges[i].u;
		int v=edges[i].v;
		
		int w=edges[i].w;
		link_edge(u,v,w);
	}
}

int main(void)
{
	scanf("%d%d",&n,&m);
	cnt=0;
	minval=0;
	memset(head,0,sizeof(head));
	memset(ancestor,-1,sizeof(ancestor));
	memset(s,0,sizeof(s));
	memset(vis,0,sizeof(vis));
	for(int i=0;i<m;i++){
		int u,v,w;
		scanf("%d%d%d",&u,&v,&w);
		edges[i].u=u,edges[i].v=v,edges[i].w=w;
	}
	qsort(edges,m,sizeof(edge),cmp);

	for(int i=0;i<m;i++){
		printf("%d %d %d\n",edges[i].u,edges[i].v,edges[i].w);
	}
	kruskal();

	for(int i=0;i<n;i++){
		if(vis[i])
			printf("%d%d%d\n",edges[i].u,edges[i].v,edges[i].w);
	}

	solve();

	for(int i=0;i<cnt;i++)
		printf("%d ",s[i]);
	printf("\n");
	int mmin=0xffff;
	for(int i=0;i<n-1;i++)
		if(s[i]-w[i]!=0&&mmin>s[i]-w[i])
			mmin=s[i]-w[i];

	printf("%d\n",mmin+minval);
	return 0;
}