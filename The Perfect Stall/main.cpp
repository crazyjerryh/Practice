#include <stdio.h>
#include <memory.h>
//using namespace std;
#define maxn 210

int mat[maxn][maxn];
int vis[maxn],match[maxn];
int n,m;

bool dfs(int a)
{
	for(int i=1;i<=m;i++){
		if(mat[a][i]&&!vis[i]){
			vis[i]=1;
			if(match[i]==-1||dfs(match[i])){
				match[i]=a;
				return true;
			} 
		} 
	}
	return false;
} 

int solve(){
	memset(match,-1,sizeof(match));
	int ans=0;
	for(int i=1;i<=n;i++){
		memset(vis,0,sizeof(vis));
		if(dfs(i)) ans++;
	} 
	return ans;
}

int main(void){
	//freopen("debug.txt","r",stdin);
	while(scanf("%d%d",&n,&m)!=EOF){
		memset(mat,0,sizeof(mat));
	    for(int i=1;i<=n;i++){
	         int k;
	         scanf("%d",&k);
	         for(int j=1;j<=k;j++){
	         	  int a;
	         	  scanf("%d",&a);
	         	  mat[i][a]=1;
			 } 
		}
		
		int ans=solve();
		printf("%d\n",ans); 
	}
} 
