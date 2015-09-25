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

#define maxn 100100
int dp[maxn],n,w;
int w1[maxn],v[maxn];
int main(void){
	//freopen("debug.txt","r",stdin);
	while(~scanf("%d%d",&n,&w)){
	for(int i=1;i<=n;i++) scanf("%d%d",&w1[i],&v[i]);
	memset(dp,0,sizeof(dp));
	for(int i=1;i<=n;i++){
		for(int j=w1[i];j<=w;j++)
			dp[j]=max(dp[j],dp[j-w1[i]]+v[i]);
	}
	printf("%d\n",dp[w]);
	}
	return 0;
}