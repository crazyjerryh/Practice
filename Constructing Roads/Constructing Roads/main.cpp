#include <iostream>
#include <memory.h>
using namespace std;

#define maxn  105 
#define maxm 0xffff
int n,m;
int map[maxn][maxn];

int visited[maxn];
int path[maxn];
int minlen=0;

void prim()
{
	visited[1]=1;
	for(int i=1;i<=n;i++){
		if(!visited[i])
			path[i]=map[1][i];
	}
	
	for(int i=2;i<=n;i++)
	{
		int min=maxm;
		int cur;
		for(int i=1;i<=n;i++){
			if(!visited[i]&&min>path[i])
			{
				min=path[i];
				cur=i;
			}
		}

		visited[cur]=1;
		minlen+=path[cur];  //当前最短的边长
		for(int i=1;i<=n;i++)
		{
			if(!visited[i]&&path[i]>map[cur][i])
				path[i]=map[cur][i];
		}
	}
}

int main(void)
{
	while(scanf("%d",&n)!=EOF){
	for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)
			scanf("%d",&map[i][j]);
	}

	scanf("%d",&m);
	for(int i=0;i<m;i++)
	{
		int a,b;
	    scanf("%d%d",&a,&b);
		map[a][b]=0,map[b][a]=0;
	}

	memset(visited,0,sizeof(visited));
	for(int i=1;i<maxn;i++)
		path[i]=maxm; 

	minlen=0;
	prim();
	printf("%d\n",minlen);
	}
	return 0;
}