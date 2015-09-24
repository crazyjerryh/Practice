/*!
 * file main.cpp
 * author Rotile_H
 * date 2015/09/24
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
#define maxn 3000

int n;
int a[maxn],dp[maxn][maxn];
int main(void){
	//freopen("debug.txt","r",stdin);
	while(~scanf("%d",&n)){
	if(n==0) break;
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	for(int i=1;i<=n;i++) a[i+n]=a[i];
	
	memset(dp,0,sizeof(dp));
	for(int i=1;i<=2*n;i++) dp[i][i]=1;
	for(int len=1;len<=2*n;len++){
		for(int i=1;i+len<=2*n;i++){
			int j=i+len;
			if(a[i]==a[j])
			   dp[i][j]=max(dp[i][j-1],max(dp[i+1][j],2+dp[i+1][j-1]));
			else 
			   dp[i][j]=max(dp[i][j-1],dp[i+1][j]);
		}
	}
	
	int ans=-1;
	for(int i=1;i<=n;i++)
		ans=max(ans,dp[i][i+n-1]);
	
	for(int i=1;i<=n;i++)
		ans=max(ans,1+dp[i][i+n-2]);
	printf("%d\n",ans);
	}
	return 0;
}
