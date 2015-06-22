#include <stdio.h>
#include <memory.h>
#include <algorithm>
using namespace std;
#define maxn 110
#define inf 0xfffff

int m,n;
int k;
int mat[maxn][maxn];
int match[maxn],vis[maxn];

bool dfs(int a){
	for(int i=0;i<n;i++){
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
	for(int i=0;i<m;i++){
		memset(vis,0,sizeof(vis));
		if(dfs(i))  ans++;
	}
	return ans;
}

int main(void)
{	
	//freopen("debug.txt","r",stdin);
	while(scanf("%d",&m)!=EOF){
		if(m==0)  break;
		scanf("%d%d",&n,&k);
		memset(mat,0,sizeof(mat));
		for(int i=0;i<k;i++){
			int t,a,b;
			scanf("%d%d%d",&t,&a,&b);
			mat[a][b]=1;
		}
		
		mat[0][0]=1;  //must decrease the first one 
		int ans=solve();
		printf("%d\n",ans-1);
		
	}
	return 0;
}
