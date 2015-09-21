/*!
 * file main.cpp
 * author Rotile_H
 * date 2015/09/21
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
#define maxn 510
#define maxm 100110

int dp[2][maxm];

int n,w;
int weight[maxn],val[maxn];
int main(void){
	//freopen("debug.txt","r",stdin);
	while(~scanf("%d%d",&n,&w)){
		for(int i=0;i<n;i++){
		    scanf("%d%d",&weight[i],&val[i]);	
		}
		
		memset(dp,0,sizeof(dp));
		int turn =0;
		for(int i=0;i<n;i++){
			for(int j=0;j<=w;j++){
				if(j-weight[i]>=0)
				    dp[(turn+1)%2][j]=max(dp[turn][j],dp[turn][j-weight[i]]+val[i]);
				else 
					dp[(turn+1)%2][j]=dp[turn][j];
			}
			turn=(turn+1)%2;
		}

		int mmax=-1;
		for(int i=0;i<=w;i++){
			if(mmax<dp[turn][i])  mmax=dp[turn][i];
		}
		printf("%d\n",mmax);
	}
	return 0;
}