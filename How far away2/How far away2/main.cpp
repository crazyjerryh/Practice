#include <iostream>
#include <fstream>
#include <cmath>
//#pragma comment(linker, "/STACK:102400000,102400000")
#include <algorithm>
#include <memory.h>
using namespace std;

#define maxn 40010
struct _edge
{
	int u,v,w;
	int next;
}edge[maxn<<1];
int tcase;
int n,m;
int head[maxn];
int first[maxn];
int depth[maxn];
int dp[16][maxn<<1];
int seq[maxn<<1];
int val[maxn<<1];
int cnt;
int cur;

void addedge(int u,int v,int w)
{
	edge[cnt].u=u,edge[cnt].v=v,edge[cnt].w=w;
	edge[cnt].next=head[u],head[u]=cnt++;

	edge[cnt].u=v,edge[cnt].v=u,edge[cnt].w=w;
	edge[cnt].next=head[v],head[v]=cnt++;
}

void dfs(int u,int p,int dep)
{
	if(first[u]==-1)
		first[u]=cur;

	seq[cur]=dep;
	val[cur++]=u;
	for(int i=head[u];i!=0;i=edge[i].next)
	{
		int v=edge[i].v;
		int w=edge[i].w;
		if(v!=p){
			depth[v]=depth[u]+w;
			dfs(v,u,dep+1);
			seq[cur]=dep;
			val[cur++]=u;
		}
	}
}

void RMQ()
{
	int len=log(1.0*cur)/log(2.0);
	for(int i=0;i<cur;i++)
		dp[0][i]=i;
	
	for(int j=1;j<=len;j++){
	  for(int i=0;i<cur;i++){
			int a=dp[j-1][i];
			int b=dp[j-1][i+(1<<(j-1))];
			if(seq[a]<seq[b])
				dp[j][i]=a;
			else
				dp[j][i]=b;
		}
	}

}

int LCA(int u,int v)
{
	int len=log(1.0*(v-u+1))/log(2.0);
	int a=dp[len][u];
	int b=dp[len][v-(1<<len)+1];

	int res;
	if(seq[a]<seq[b])
		res=a;
	else
		res=b;

	return val[res];
}

int main(void)
{
	cin>>tcase;
	for(int t=1;t<=tcase;t++){
		cin>>n>>m;
		memset(head,0,sizeof(head));
		memset(depth,0,sizeof(depth));
		for(int i=0;i<maxn;i++)
			first[i]=-1;

		cnt=1;
		cur=0;

		for(int i=0;i<n-1;i++){
			int u,v,w;
			cin>>u>>v>>w;
			addedge(u,v,w);
		}

		dfs(1,0,0);
		RMQ();
		
		for(int i=0;i<m;i++){
			int u,v,a,b;
			cin>>a>>b;
			u=first[a],v=first[b];
			if(u>v)  std::swap(u,v);
			int lca=LCA(u,v);
			cout<<depth[a]+depth[b]-2*depth[lca]<<endl;
		}
	}
	return 0;
}