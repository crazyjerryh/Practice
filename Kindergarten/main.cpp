#include <stdio.h>
#include <memory.h>
#include <algorithm>
using namespace std;

#define maxn 210
int mat[maxn][maxn];
int vis[maxn],match[maxn];
int m,n,k;
bool dfs(int a)
{
	for(int i=1;i<=n;i++){
		if(!vis[i]&&mat[a][i]){
			vis[i]=1;
			if(match[i]==-1||dfs(match[i])){
				match[i]=a;
				return true;
			}
		} 
	}
	return false;
}

int solve()
{
 	int ans=0;
 	memset(match,-1,sizeof(match));
 	for(int i=1;i<=m;i++){
 		memset(vis,0,sizeof(vis));
 		if(dfs(i))  ans++;
	 } 
	 return ans;
}

int main(void)
{
	//freopen("debug.txt","r",stdin);
	int tt=1;
	while(scanf("%d%d%d",&m,&n,&k)!=EOF){
		if(m==0&&n==0&&k==0) break;
		for(int i=1;i<=m;i++){
		    for(int j=1;j<=n;j++)
			     mat[i][j]=1;
		} 
		for(int i=0;i<k;i++){
			int a,b;
			scanf("%d%d",&a,&b);
			mat[a][b]=0;
		}
		
		int ans=solve();
		printf("Case %d: %d\n",tt++,n+m-ans);
	} 
	return 0;
} 
