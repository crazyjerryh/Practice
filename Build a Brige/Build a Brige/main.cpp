#include <stdio.h>
#include <memory.h>
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
#define maxn 60
#define maxm 300
#define inf 0x3f3f3f3f

int n,m;
int mat[maxn][maxn],vis[maxn][maxn];
int ans[maxm][maxm],dis[maxm],flag[maxm];
int dir[8][2]={{1,0},{1,1},{0,1},{-1,1},{-1,0},{-1,-1},{0,-1},{1,-1}};  
int cnt;

void dfs(int x,int y){
	vis[x][y]=cnt;
    for(int i=0;i<8;i++){
		int nowx=x+dir[i][0],nowy=y+dir[i][1];
		if(nowx<1||nowy<1||nowx>n||nowy>m)  continue;
		if(vis[nowx][nowy]!=0||mat[nowx][nowy]==0)  continue;
		dfs(nowx,nowy);
	}	
}

void buildgraph(){
    for(int x=1;x<=n;x++){
		for(int y=1;y<=m;y++){
			 //hold x
			  int clr1=vis[x][y],clr2;
		      for(int i=x-1;i<=x+1;i++){
				  for(int j=1;j<=m;j++){
					   if(i<1||i>n)  continue;
				       if(j==y)  continue;
				       clr2=vis[i][j];
					   if(!clr2)  continue;
					   int dis=abs(y-j)-1;
					   if(ans[clr1][clr2]>dis)  ans[clr1][clr2]=dis,ans[clr2][clr1]=dis;
				  }
			  }
			  //hold y
			  for(int i=1;i<=n;i++){
				  for(int j=y-1;j<=y+1;j++){
				        if(j<1||j>m) continue;
						if(x==i)  continue;
						clr2=vis[i][j];
						if(!clr2)  continue;
						int dis=abs(x-i)-1;
						if(ans[clr1][clr2]>dis)  ans[clr1][clr2]=dis,ans[clr2][clr1]=dis;
				  }
			  }
		}
	}
}

void prime(){
	int num=0,len=0;
	for(int i=1;i<cnt;i++){
		if(flag[i])  continue;
		flag[i]=1;
		for(int j=1;j<=maxm;j++)
			dis[j]=inf;
		for(int j=1;j<cnt;j++){
			if(flag[j]) continue;
			if(ans[i][j]<inf)  dis[j]=ans[i][j];
		}
		
		for(int j=1;j<cnt;j++){
			int mmin=inf,pos=-1;
			for(int k=1;k<cnt;k++){
				if(!flag[k]&&dis[k]<mmin)  mmin=dis[k],pos=k;
			}
			if(pos==-1)  break;
			flag[pos]=1;
			num++,len+=mmin;
			for(int k=1;k<cnt;k++){
				if(!flag[k]&&ans[pos][k]<inf&&dis[k]>ans[pos][k])
					 dis[k]=ans[pos][k];
			}
		}
	}
	printf("%d %d\n",num,len);
}

void solve(){
	memset(vis,0,sizeof(vis));
	cnt=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(mat[i][j]&&!vis[i][j]){  
				dfs(i,j),cnt++;
		    }
		}
	}
	printf("%d\n",cnt-1);
	for(int i=0;i<maxm;i++){
		for(int j=0;j<maxm;j++)
			 ans[i][j]=inf;
	}
	buildgraph();
	memset(flag,0,sizeof(flag));
	prime();
}

int main(void){
   while(cin>>n>>m){
	   for(int i=1;i<=n;i++){
	       for(int j=1;j<=m;j++){
			   char c;
			   cin>>c;
			   if(c=='#')  mat[i][j]=1;
			   else  mat[i][j]=0;
		   }
	   }
	   solve();
   }
}