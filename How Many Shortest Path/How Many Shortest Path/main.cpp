#include <stdio.h>
#include <queue>
#include <memory.h>
using namespace std;
#define maxn 330
#define maxm 500000
#define INF  1<<29
#define min(a,b) a<b?a:b
int n;
int map[maxn][maxn];
int dp[maxn][maxn];
//int q[maxm];
int first,tail;

struct _edge
{
	int u,v,w;
	int next;
}edges[maxm];
int head[maxn];
int s,t;
int cnt;
int level[maxn];

typedef struct _edge edge;
void addedge(int u,int v,int w)
{
	edges[cnt].u=u,edges[cnt].v=v,edges[cnt].w=w;
	edges[cnt].next=head[u],head[u]=cnt++;
	edges[cnt].u=v,edges[cnt].v=u,edges[cnt].w=0;
	edges[cnt].next=head[v],head[v]=cnt++;
}

void floyd()
{	
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			for(int k=0;k<n;k++)
			      if((dp[i][j]>dp[i][k]+dp[k][j]||dp[i][j]==-1)&&dp[i][k]!=-1&&dp[k][j]!=-1)
					  dp[i][j]=dp[i][k]+dp[k][j];
}

bool bfs()
{
	queue<int>  q;
	while(!q.empty())
		q.pop();
	memset(level,0,sizeof(level));
	level[s]=1;
	q.push(s);

	while(!q.empty())
	{
		int top=q.front();
		q.pop();
		for(int i=head[top];i!=-1;i=edges[i].next)
		{
			int v=edges[i].v;
			if(level[v]==0&&edges[i].w>0){
				level[v]=level[top]+1;
				q.push(v);
			}
		}
	}

	return level[t]!=0;
}

int dfs(int dep,int f)
{
	if(dep==t)
		return f;
	
	for(int i=head[dep];i!=-1;i=edges[i].next){
		int v=edges[i].v;
		int a;
		if(edges[i].w>0&&level[v]==level[dep]+1)
		{
			int tmp=dfs(v,min(f,edges[i].w));
			if(tmp>0){
			edges[i].w=edges[i].w-a;
			edges[i^1].w=edges[i^1].w+a;
			return tmp;
			}
		}
	}
	level[dep]=0;
	return 0;
}

int dinic()
{
	int ans=0;
	while(bfs()){
		ans+=dfs(s,0xfffff);
	}
	return ans;
}

int main(void)
{
	while(scanf("%d",&n)!=EOF)
	{
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				scanf("%d",&map[i][j]);

		
		scanf("%d%d",&s,&t);
		if(s==t)
		{
            printf("inf\n");
			continue;
		}
		
		for(int i=0;i<maxn;i++)
			head[i]=-1;
		
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
					dp[i][j]=map[i][j];

		for(int i=0;i<n;i++)
			 dp[i][i]=0;
			
		floyd();
		if(dp[s][t]==-1)
		{
			printf("0\n");
			continue;
		}

		cnt=0;
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++){
				if(map[i][j]!=-1&&dp[s][i]+dp[j][t]+map[i][j]==dp[s][t]&&dp[s][t]!=-1&&dp[s][i]!=-1&&dp[j][t]!=-1&&i!=j){
					  addedge(i,j,1);
				}
			}
        
		int res=dinic();
		printf("%d\n",res);
	}
	return 0;
}