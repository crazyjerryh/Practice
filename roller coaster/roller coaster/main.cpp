#include <stdio.h>
#include <memory.h>
#include <algorithm>
using namespace std;
#define maxn 510

int k,m,n;
int graph[maxn][maxn];
int match[maxn],vis[maxn];

bool dfs(int a)
{
	for(int i=1;i<=n;i++){
		if(!vis[i]&&graph[a][i]){
		     vis[i]=1;   //vis function is judge the point is not in the path
			 if(match[i]==0||dfs(match[i])){
			      match[i]=a;
				  return true;
			 } 
		}
	}
	return false;
}

int main(void)
{
	while(scanf("%d",&k)!=EOF){
		  if(k==0)  break;
	      scanf("%d%d",&m,&n);
		  for(int i=0;i<k;i++){
		      int a,b;
			  scanf("%d%d",&a,&b);
			  graph[a][b]=1;
		  }
		  
		  memset(match,0,sizeof(match));
		  memset(vis,0,sizeof(vis));
		  memset(graph,0,sizeof(graph));
		  int ans=0;
		  for(int i=1;i<=m;i++){
			  memset(vis,0,sizeof(vis));
			  if(dfs(i)) ans++;
		  }
		  
		  printf("%d\n",ans);
	}
	return 0;
}