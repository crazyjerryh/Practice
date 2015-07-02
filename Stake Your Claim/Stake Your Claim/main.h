#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <memory.h>
using namespace std;
#define maxn 9
#define inf 0xffff
using namespace std;  
struct Point{
	int x,y;
	Point(){}
	Point(int _x,int _y):x(_x),y(_y){}
}p[10],ansp;
int n,tot,best;
char str[10][10];
int vis[10][10],tt;
int way[4][2]={0,1,0,-1,1,0,-1,0};
int pw3[15],dp[60000];
bool check(int x1,int y1,int x2,int y2){
	if(x1>=0&&x2>=0&&x1<n&&x2<n&&str[x1][y1]==str[x2][y2]&&!vis[x1][y1])
		return true;
	return false;
}
void dfs(int i,int j){
	if(vis[i][j]) return;
	tt++;vis[i][j]=1;
	for(int k=0;k<4;k++){
		int ii=i+way[k][0],jj=j+way[k][1];
		if(check(ii,jj,i,j))
			dfs(ii,jj);
	}
}
int get_score(){
	memset(vis,0,sizeof(vis));
	int c1=0,c2=0;
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++){
			tt=0;
			if(vis[i][j]==0)
				dfs(i,j);
			if(str[i][j]=='0') c1=max(c1,tt);
			else c2=max(c2,tt);
		}
		return c1-c2;
}
int MinSearch(int,int,int,int);
int MaxSearch(int,int,int,int);
int MaxSearch(int state,int dep,int now,int alpha){
	//棋盘放满，统计一下当前局面
	if(dep>=tot)return get_score();
	if(dp[now]!=-inf) return dp[now];
	int ans=-inf,st;
	const int STATUS=((1<<tot)-1);
	st=(~state)&STATUS;
	//枚举所有的位置
	while(st){
		int k=st&(-st),pos;
		pos=(int)(log(k*1.0)/log(2.0));
		str[p[pos].x][p[pos].y]='0';
		int tmp=MinSearch(state|k,dep+1,now+pw3[pos],ans);	
		str[p[pos].x][p[pos].y]='.';
		if(tmp>ans) ans=tmp;
		if(tmp>=alpha) return ans;
		//更新一下最优解
		if(dep==0){
			if(ans>best||(ans==best&&(p[pos].x<ansp.x||(p[pos].x==ansp.x&&p[pos].y<ansp.y)))){
				best=ans;
				ansp=p[pos];
			}
		}

		st-=k;
	}
	return dp[now]=ans;
}
int MinSearch(int state,int dep,int now,int beta){
	//棋盘放满，统计一下当前局面
	if(dep>=tot) return get_score();
	//记忆化搜索
	if(dp[now]!=-inf) return dp[now];
	int ans=inf,st;
	const int STATUS=((1<<tot)-1);
	st=(~state)&STATUS;
	//枚举所有的位置
	while(st){
		int k=st&(-st),pos;
		//找一下是第几个点
		pos=(int)(log(k*1.0)/log(2.0));
		//搜索
		str[p[pos].x][p[pos].y]='1';
		int tmp=MaxSearch(state|k,dep+1,now+2*pw3[pos],ans);		
		str[p[pos].x][p[pos].y]='.';
		if(ans>tmp) ans=tmp;
		if(beta>=tmp)  return ans;
		st-=k;
	}
	return dp[now]=ans;
}
int main(){
	pw3[0]=1;
	for(int i=1;i<=10;i++) pw3[i]=pw3[i-1]*3;
	while(scanf("%d",&n)!=EOF&&n){
		int c1=0,c2=0;tot=0;
		for(int i=0;i<n;i++){
			scanf("%s",str[i]);
			for(int j=0;j<n;j++){
				if(str[i][j]=='.') p[tot++]=Point(i,j);
				else if(str[i][j]=='0') c1++;
				else c2++;
			}
		}
		if(c1>c2){
			for(int i=0;i<n;i++)
				for(int j=0;j<n;j++)
					if(str[i][j]=='0') str[i][j]='1';
					else if(str[i][j]=='1')str[i][j]='0';
		}
		best=-inf;
		int ret;
		for(int i=0;i<60000;i++) dp[i]=-inf;
		ret=MaxSearch(0,0,0,inf);
		printf("(%d,%d) %d\n",ansp.x,ansp.y,best);
	}
	return 0;
}