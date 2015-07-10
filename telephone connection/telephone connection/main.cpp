#include <stdio.h>
#include <memory.h>
#include <algorithm>
using namespace std;
#define maxn 120
#define inf 0x3f3f3f3f
int mat[maxn][maxn];
int vis[maxn],dis[maxn],pre[maxn];
int resa[maxn],resb[maxn],val[maxn];
int n,num,cnt,ans;

void prim(){
	for(int i=0;i<maxn;i++)
		dis[i]=inf;
	memset(vis,0,sizeof(vis));
	vis[1]=true;
	for(int i=1;i<=n;i++){
		if(!vis[i]) { dis[i]=mat[1][i]; pre[i]=1;}
	}

	for(int i=1;i<n;i++){
		int mmin=inf,pos=-1;
		for(int j=1;j<=n;j++){
			if(dis[j]<mmin&&!vis[j]) {
				 mmin=dis[j],pos=j;
			}
		}
		vis[pos]=true;
		resa[cnt]=pre[pos],resb[cnt]=pos,val[cnt++]=mmin;
		ans+=mmin;
		for(int j=1;j<=n;j++){
			if(!vis[j]&&dis[j]>mat[pos][j]) 
				dis[j]=mat[pos][j],pre[j]=pos;
		}
	}
}

void solve(){
	num=0,cnt=0,ans=0;
	prim();
	for(int i=0;i<cnt;i++)
		if(val[i]!=0)
			 num++;

	printf("%d\n",num);
	for(int i=0;i<cnt;i++){
		if(val[i]!=0){
			if(resa[i]>resb[i])  std::swap(resa[i],resb[i]);
			 printf("%d %d\n",resa[i],resb[i]);
		}
	}
	printf("%d\n",ans);
}

int main(void){
	while(scanf("%d",&n)!=EOF){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				int tmp;
				scanf("%d",&tmp);
				mat[i][j]=tmp;
			}
		}
		solve();
	}
	return 0;
}