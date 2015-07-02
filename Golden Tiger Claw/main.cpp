#include <stdio.h>
#include <memory.h>
#include <algorithm>
using namespace std;
#define maxn 510
#define inf 1<<30

int n;
int mat[maxn][maxn];
int lx[maxn],ly[maxn],vx[maxn],vy[maxn],match[maxn];
int slack[maxn];

bool dfs(int u){
	vx[u]=1;
	for(int i=1;i<=n;i++){
	     if(vy[i])  continue;
	     int t=lx[u]+ly[i]-mat[u][i];
	     if(t==0){
	     	vy[i]=1;
	     	if(match[i]==-1||dfs(match[i])){
	     		match[i]=u;
	     		return true;
			 }
		 }	
		 else 
		      slack[i]=min(slack[i],t);	 
	}
	return false;
}

void solve()
{
	memset(match,-1,sizeof(match));
	memset(lx,0,sizeof(lx));
	memset(ly,0,sizeof(ly));
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			lx[i]=max(lx[i],mat[i][j]);
		}
	}
	
    for(int i=1;i<=n;i++){
          for(int j=1;j<=n;j++) slack[j]=inf;
		  while(1){
		  	   memset(vx,0,sizeof(vx));
		  	   memset(vy,0,sizeof(vy));
		  	   if(dfs(i)) break;
		  	   int d=inf;
		  	   for(int j=1;j<=n;j++)
		  	       if(!vy[j])  
		  	              d=min(d,slack[j]);
		  	   for(int j=1;j<=n;j++){
		  	       if(vx[j])   lx[j]-=d;
				   if(vy[j])   ly[j]+=d;
			   }
		  }	
	}	
	
	int ans=0;
	printf("%d",lx[1]);
	ans+=lx[1];
	for(int i=2;i<=n;i++)
	     printf(" %d",lx[i]),ans+=lx[i];
	printf("\n");
	
	printf("%d",ly[1]);
	ans+=ly[1];
	for(int i=2;i<=n;i++)
	     printf(" %d",ly[i]),ans+=ly[i];
	printf("\n");
	printf("%d\n",ans);
}

int main(void){
	//freopen("debug.txt","r",stdin);
	while(scanf("%d",&n)!=EOF){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				scanf("%d",&mat[i][j]);
			}
		} 
		solve();
	}
	return 0;
} 
