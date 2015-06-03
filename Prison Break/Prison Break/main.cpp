#include <iostream>
#include <queue>
#include <memory.h>
using namespace std;
#define maxn 110
#define min(a,b) a<b?a:b
#define INF 0xfffff

struct _edge{
	int u,v,w;
	int next;
}edges[maxn<<1];

typedef struct _node
{
	int u;
	_node(){}
	_node(int _u):u(_u){}
}node;

int head[maxn];
int vis[maxn];
int price[maxn];
int dp[maxn][maxn];
int n,m;
int tcase;
int cnt;
int q;
int s,t,cap;

void addedge(int u,int v,int w)
{
     edges[cnt].u=u,edges[cnt].v=v,edges[cnt].w=w;
	 edges[cnt].next=head[u],head[u]=cnt++;
	 edges[cnt].u=v,edges[cnt].v=u,edges[cnt].w=w;
	 edges[cnt].next=head[v],head[v]=cnt++;
}

void spfa()
{
	queue<node> Q;
	node nnode;
	nnode.u=s;
	dp[s][0]=0;
	Q.push(nnode);
	
	while(!Q.empty())
	{
		node top=Q.front();
		vis[top.u]=0;
		Q.pop();

		for(int i=1;i<=cap;i++)
			dp[top.u][i]=min(dp[top.u][i-1]+price[top.u],dp[top.u][i]);
	
		int u=top.u;
		for(int i=head[u];i!=-1;i=edges[i].next)
		{
			int v=edges[i].v;
			int w=edges[i].w;
			bool flag=true;
			for(int j=w;j<=cap;j++){
				if(dp[v][j-w]>dp[u][j]){
					dp[v][j-w]=dp[u][j];
					flag=false;
				}
			}
			if(!flag&&!vis[v]){
				vis[v]=1;
				Q.push(node(v));
			}
		}
	}
	
}

int main(void)
{
	cin>>tcase;
	for(int tt=1;tt<=tcase;tt++){
		cin>>n>>m;
		for(int i=0;i<maxn;i++)
			head[i]=-1;

		for(int i=0;i<n;i++)
			cin>>price[i];
		
		cnt=0;
		for(int i=0;i<m;i++){
			int u,v,w;
			cin>>u>>v>>w;
		    addedge(u,v,w);
		}
		
		cin>>q;
		cout<<"Case "<<tt<<":"<<endl;
		for(int i=0;i<q;i++){
			for(int j=0;j<maxn;j++)
				for(int k=0;k<maxn;k++){
					 dp[j][k]=INF;
				}
			memset(vis,0,sizeof(vis));
			cin>>cap>>s>>t;
			spfa();
			if(dp[t][0]<INF)
				cout<<dp[t][0]<<endl;
			else
				cout<<"impossible"<<endl;
		}

	}
	return 0;
}