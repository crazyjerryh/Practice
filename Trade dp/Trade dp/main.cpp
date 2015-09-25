/*!
 * file main.cpp
 * author Rotile_H
 * date 2015/09/25
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
#define maxn  2100
struct node{
	int pos,f;
};

int tcase;
int t,w,maxp;
int Ap[maxn],Bp[maxn],As[maxn],Bs[maxn];
int dp[maxn][maxn];
node q[maxn];
int head,tail;
int main(void){
	//freopen("debug.txt","r",stdin);
	scanf("%d",&tcase);
	while(tcase--){
		scanf("%d%d%d",&t,&maxp,&w);
		for(int i=1;i<=t;i++) scanf("%d%d%d%d",&Ap[i],&Bp[i],&As[i],&Bs[i]);
		for(int i=0;i<=t;i++)
			for(int j=0;j<=maxp;j++)
				 dp[i][j]=-inf;
		
		for(int i=1;i<=w+1;i++)
			for(int j=0;j<=(min(As[i],maxp));j++)
				 dp[i][j]=-Ap[i]*j;

		dp[0][0]=0;
		for(int i=1;i<=t;i++){
			for(int j=0;j<=maxp;j++)
				  dp[i][j]=max(dp[i-1][j],dp[i][j]);
			
			if(i<=w+1) continue;
			int pre=i-w-1;

			head=tail=0;
			for(int j=0;j<=maxp;j++){
				int nowf=dp[pre][j]+j*Ap[i];
				while(head<tail&&q[tail-1].f<nowf) tail--;
				q[tail].f=nowf,q[tail++].pos=j;
				while(head<tail&&q[head].pos+As[i]<j) head++;
				dp[i][j]=max(dp[i][j],q[head].f-j*Ap[i]);
			}

			head=tail=0;
			for(int j=maxp;j>=0;j--){
				int nowf=dp[pre][j]+j*Bp[i];
				while(head<tail&&q[tail-1].f<nowf) tail--;
				q[tail].f=nowf,q[tail++].pos=j;
				while(head<tail&&q[head].pos-Bs[i]>j) head++;
				dp[i][j]=max(dp[i][j],q[head].f-j*Bp[i]);
			}
		}
		int ans=0;
		for(int i=0;i<=maxp;i++) 
			ans=max(ans,dp[t][i]);
		printf("%d\n",ans);
		
	}
	return 0;
}