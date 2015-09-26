/*!
 * file main.cpp
 * author Rotile_H
 * date 2015/09/26
 * 
 */
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <string>
#include <algorithm>
#include <memory.h>

using namespace std;
#define inf 0x3f3f3f3f
#define maxn 110
#define maxm 10010

struct node{
	int f;
    int pos;
};

int dp[maxn][maxm];
int n,m,x,t;
int sum[maxn][maxm];
node q[maxm];
int head,tail;

int main(void){
	//freopen("debug.txt","r",stdin);
	while(~scanf("%d%d%d%d",&n,&m,&x,&t)){
		memset(sum,0,sizeof(sum));
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++){
				int tmp;
				scanf("%d",&tmp);
				sum[i][j]=sum[i][j-1]+tmp;
			}
		}
		
		for(int i=1;i<=n;i++){
			for(int j=1;j<=m;j++)
				dp[i][j]=-inf;
		}
		
		dp[1][x]=sum[1][x]-sum[1][x-1];
		for(int i=1;i<=t;i++){
			if(i>=x) break;
			dp[1][x-i]=sum[1][x]-sum[1][x-i-1];
		}

		for(int i=1;i<=t;i++){
			if(x+i>m) break;
			dp[1][x+i]=sum[1][x+i]-sum[1][x-1];
		}
		
		for(int i=2;i<=n;i++){
			head=tail=0;
			for(int j=1;j<=m;j++){
				while(head<tail&&dp[i-1][j]-sum[i][j-1]>q[tail-1].f) tail--;
				q[tail].f=dp[i-1][j]-sum[i][j-1];
				q[tail++].pos=j;
				while(head<tail&&j-q[head].pos>t) head++;
				dp[i][j]=max(dp[i][j],q[head].f+sum[i][j]);
			}
			
			head=tail=0;
			for(int j=m;j>=1;j--){
				while(head<tail&&dp[i-1][j]+sum[i][j]>q[tail-1].f) tail--;
				q[tail].f=dp[i-1][j]+sum[i][j];
				q[tail++].pos=j;
				while(head<tail&&q[head].pos-j>t) head++;
				dp[i][j]=max(dp[i][j],q[head].f-sum[i][j-1]);
			}
		}

		int ans=-inf;
		for(int i=1;i<=m;i++)
			ans=max(ans,dp[n][i]);
		printf("%d\n",ans);
	}
	return 0;
}
