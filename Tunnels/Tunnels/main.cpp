/*!
 * file main.cpp
 * author Rotile_H
 * date 2015/09/26
 * 
 */
#include <stdio.h>
#include <iostream>
#include <queue>
#include <string.h>
#include <string>
#include <algorithm>
#include <memory.h>

using namespace std;

struct node{
	int a,b;
	int step;
	node(){}
	node(int _x,int _y,int _z):a(_x),b(_y),step(_z){}
};

#define inf 0x3f3f3f3f
#define maxn 20
int map[maxn][maxn];
char str[maxn];
int n,m;
node ent[maxn],eit[maxn];
int dis[maxn][maxn];
int vis[maxn][maxn];
int dp[1<<16][maxn];
int bestsz;
queue<node> Q;

int pos[4][2]={{1,0},{0,1},{-1,0},{0,-1}};

bool check(int x,int y){
	return x>=0&&y>=0&&x<n&&y<n;
}

int bfs(node s,node e){
	while(!Q.empty()) Q.pop();
	memset(vis,0,sizeof(vis));
	s.step=0;
	vis[s.a][s.b]=1;
	Q.push(s);
	while(!Q.empty()){
		node front=Q.front();
		if(front.a==e.a&&front.b==e.b)  return front.step;
		Q.pop();
		for(int i=0;i<4;i++){
			int x=front.a+pos[i][0];
			int y=front.b+pos[i][1];
			if(check(x,y)&&!vis[x][y]&&map[x][y]!='#'){
				Q.push(node(x,y,front.step+1));
				vis[x][y]=1;
			}
		}
	}
	return -1;
}

int main(void){
    //freopen("debug.txt","r",stdin);
	while(~scanf("%d%d",&n,&m)){
		for(int i=0;i<n;i++)
		{
			scanf("%s",str);
			for(int j=0;j<n;j++)
				map[i][j]=str[j];
		}
		
		for(int i=0;i<m;i++){
			scanf("%d%d",&ent[i].a,&ent[i].b);
			scanf("%d%d",&eit[i].a,&eit[i].b);
			ent[i].a--;
			ent[i].b--;
			eit[i].a--;
			eit[i].b--;
		}
	    
		for(int i=0;i<m;i++)
			for(int j=0;j<m;j++){
				if(i==j)  dis[i][j]=0;
				else
				{
                     int d=bfs(ent[i],eit[j]);
					 if(d==-1) dis[i][j]=inf;
					 else dis[i][j]=d;
				}
			}
  
		//×´Ì¬Ñ¹Ëõdp
		int cnt=(1<<m);
        for(int i=0;i<cnt;i++) 
			for(int j=0;j<m;j++)
				  dp[i][j]=inf;

		for(int i=0;i<m;i++)
			 dp[1<<i][i]=0;
		
        
		for(int i=0;i<cnt;i++){
		    for(int j=0;j<m;j++){
				if(i&(1<<j)) continue;
				for(int k=0;k<m;k++){
					if(!i&(1<<k)) continue;
					dp[i|(1<<j)][j]=min(dp[i|(1<<j)][j],dp[i][k]+dis[k][j]);
				}
			}
		}

		for(int i=0;i<cnt;i++)  
			for(int j=0;j<m;j++)  
			{  
				if(i&(1<<j))  
					continue;  
				for(int k=0;k<m;k++)  
					dp[i|(1<<j)][j]=min(dp[i|(1<<j)][j],dp[i][k]+dis[k][j]);  
			} 
		
		int ans=inf;
		for(int i=0;i<m;i++){
		     ans=min(ans,dp[cnt-1][i]);
		}
		if(ans>=inf)
			printf("-1\n");
		else
			printf("%d\n",ans);
     
	}
	return 0;
}