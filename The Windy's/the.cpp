#include <stdio.h>
#include <memory.h>
#include <algorithm>
using namespace std;

#define maxn 100
#define inf 0x3f3f3f3f

int n,m,tcase;
int mat[maxn][maxn];
int match[maxn],slack[maxn],lx[maxn],ly[maxn];
int vx[maxn],vy[maxn];

bool dfs(int a)
{
	vx[a]=1;
	for(int i=0;i<m;i++){
		if(!vy[i]){
			  int t=lx[a]+ly[i]-mat[a][i];
			  if(t==0){
				 if(match[i]==-1||dfs(match[i])){
					 match[i]=a;
					 return true;
				 }
              }
			  else if(slack[i]>t)
				  slack[i]=t;
		}
	}
	return false;
}

int solve()
{
	memset(lx,0,sizeof(lx));
	memset(ly,0,sizeof(ly));
	memset(match,-1,sizeof(match));
	for(int i=0;i<n;i++){
		while(1){
			memset(vx,0,sizeof(vx));
			memset(vy,0,sizeof(vy));
			for(int j=0;j<m;j++)
				 slack[j]=inf;
			if(dfs(i)) break;
			int d=inf;
			for(int j=0;j<m;j++)
				 if(slack[j]<d)   d=slack[j];

			for(int j=0;j<n;j++)
				 if(vx[j]) lx[j]-=d;

			for(int j=0;j<m;j++)
				 if(!vy[j]) ly[j]+=d;
		}
	}
	
	int ans=0;
	for(int i=0;i<m;i++)
		 if(match[i]!=-1)
			 ans+=mat[match[i]][i];
	return ans;
}

int main(void){
	scanf("%d",&tcase);
	while(tcase--){
		scanf("%d%d",&n,&m);
		for(int i=0;i<n;i++)
			for(int j=0;j<m;j++)
				scanf("%d",&mat[i][j]);

		int ans=solve();
		printf("%d\n",ans);
	}
	return 0;
}
