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
#define maxn 200

int s[maxn];
int n;
int dp[maxn][maxn];
int main(void){
	//freopen("debug.txt","r",stdin);
	while(~scanf("%d",&n)){
		for(int i=1;i<=n;i++) scanf("%d",&s[i]);
		if(n<3) {
			printf("0\n");
			continue;
		}

		memset(dp,0,sizeof(dp));
		for(int i=3;i<=n;i++){
			for(int j=i-2;j>=1;j--){
				dp[j][i]=inf;
				for(int k=j+1;k<i;k++){
					dp[j][i]=min(dp[j][i],dp[j][k]+dp[k][i]+s[i]*s[k]*s[j]);
				}
			}
		}
		printf("%d\n",dp[1][n]);
	}
	return 0;
}