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
#define maxn 200

int dp[maxn][maxn],mat[maxn][maxn];
int n;

int solve(){
   dp[1][1]=mat[1][1];
   for(int i=2;i<=n;i++){
	   for(int j=1;j<=i;j++){
	        dp[i][j]=mat[i][j]+max(dp[i-1][j],dp[i-1][j-1]);
	   }
   }	
   
   int mmax=-1;
   for(int i=1;i<=n;i++){
	   if(mmax<dp[n][i])  mmax=dp[n][i];
   }
   
   return mmax;
}

int main(void){
	//freopen("debug.txt","r",stdin);
	while(~scanf("%d",&n)){
		for(int i=1;i<=n;i++){
			for(int j=1;j<=i;j++){
				scanf("%d",&mat[i][j]);
			}
		}
		
		printf("%d\n",solve());
	}
	return 0;
}
