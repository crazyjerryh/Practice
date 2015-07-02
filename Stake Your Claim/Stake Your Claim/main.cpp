#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <memory.h>
using namespace std;
#define maxn 9
#define inf 0xffff
struct _point
{
     int x,y;
	 _point(int _x,int _y):x(_x),y(_y){}
	 _point(){}
}points[20];
typedef struct _point point;

char map[maxn][maxn];
int vis[maxn][maxn];
int hashtable[60010],dp[60010];
int n,m;
int cnt;
int best;
point ansp;
int dir[][2]={{0,-1},{-1,0},{0,1},{1,0}};
int pw3[13];


int dfs(int x,int y,int color)
{
	if(x<0||y<0||x>=n||y>=n||vis[x][y]||map[x][y]!=color)  return 0;
	
	int count=1;
	vis[x][y]=1;
	for(int i=0;i<4;i++){
		int a,b;
		a=x+dir[i][0];
		b=y+dir[i][1];
		
		count+=dfs(a,b,color);
	}
	return count;
}

int minsearch(int ,int ,int ,int);
int maxsearch(int ,int ,int ,int);

int minsearch(int status,int depth,int now,int alpha)
{
	if(depth>=m)
	{
		memset(vis,0,sizeof(vis));
		int n1,n2;
		n1=n2=0;
	    for(int i=0;i<n;i++)
			for(int j=0;j<n;j++){
				if(!vis[i][j]){
					 int data=dfs(i,j,map[i][j]);
				     if(map[i][j]=='0')
						 n1=max(n1,data);
					 else
						 n2=max(n2,data);
				}
			}
		return dp[status]=n1-n2;
	}

	if(dp[now]!=inf) return dp[now];
	int beta=inf;
	const int STATUS=(1<<m)-1;
	int remain=(~status)&STATUS;
	while(remain)
	{
		int seg=remain&(-remain);
		int v=(int)(log(seg*1.0)/log(2.0));
		int x=points[v].x; int y=points[v].y;
		map[x][y]='1';
		int tmp=maxsearch(status|seg,depth+1,now+2*pw3[v],beta);
		map[x][y]='.';
		if(tmp<beta) 
			beta=tmp;	
		if(tmp<=alpha) return beta;
		remain-=seg;
	}
	return dp[now]=beta;
}

int maxsearch(int status,int depth,int now,int beta)
{
	if(depth>=m){
		memset(vis,0,sizeof(vis));
		int n1,n2;
		n1=n2=0;
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
			{
				if(!vis[i][j]){
					int data=dfs(i,j,map[i][j]);
					if(map[i][j]=='0')
						n1=max(n1,data);
					else
						n2=max(n2,data);
				}
			}
		return dp[status]=n1-n2;
	}
	

	if(dp[now]!=inf) return dp[now];
	int alpha=-inf;
	const int STATUS=(1<<m)-1;
	int remain=(~status)&STATUS;
	while(remain)
	{
		int seg=remain&(-remain);
		int v=(int)(log(seg*1.0)/log(2.0));
		int x=points[v].x; int y=points[v].y;
		map[x][y]='0';
		int tmp=minsearch(status|seg,depth+1,now+pw3[v],alpha);
		map[x][y]='.';
		if(tmp>alpha) 
			alpha=tmp;

		if(tmp>=beta) return alpha;
		if(depth==0){
			if(alpha>best||((alpha==best&&ansp.x>points[v].x)||(alpha==best&&ansp.x==points[v].x&&ansp.y>points[v].y)))
			{
				best=alpha;
				ansp=points[v];
			}
		}
		remain-=seg;
	}
	return dp[now]=alpha;
}

int main(void)
{
	pw3[0]=1;
    for(int i=1;i<13;i++)
		pw3[i]=pw3[i-1]*3;
	
	while(scanf("%d",&n)!=EOF)
	{
		if(n==0)  break;
		cnt=0;
		int m1,m2;
		m1=m2=0;
		m=0;
		getchar();
		memset(hashtable,0,sizeof(hashtable));
		for(int i=0;i<60000;i++)
			dp[i]=inf;

		char c;
		for(int i=0;i<n;i++)
		{
			for(int j=0;j<n;j++){
				scanf("%c",&c);
				if(c=='.')
				{
					map[i][j]='.';
					points[cnt++]=point(i,j);
					m++;
				}
				else if(c=='0')
				{
				    map[i][j]='0';
					m1++;
				}
				else
				{
					map[i][j]='1';
					m2++;
				}
			}
			getchar();
		}
		int status=0;
		if(m1>m2)
		{
			for(int i=0;i<n;i++)
				for(int j=0;j<n;j++)
					if(map[i][j]=='0')
						map[i][j]='1';
					else if(map[i][j]=='1')
						map[i][j]='0';
		}
		best=-inf;
		int rnt=maxsearch(0,0,0,inf);
		printf("(%d,%d) %d\n",ansp.x,ansp.y,best);
	}
	return 0;
}