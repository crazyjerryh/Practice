/*!
 * file main'.cpp
 * author Rotile_H
 * date 2015/09/09
 * dp
 */
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <string>
#include <algorithm>
#include <memory.h>

using namespace std;
#define inf 0x3f3f3f3f
#define maxn 1110

int n,m,q;
int w[maxn];
int dp[maxn][maxn];
int base[11]={0,1,3,7,15,31,63,127,255,511,1023};

bool check(int x){
	int bit[20];
	for(int i=0;i<m;i++)  {
		bit[i]=x%2;
		x=x/2;
	}

	int tot=0;
	for(int i=0;i<m;i++)
		if(bit[i])  ++tot;
	
	return tot<=q;
}

int main(void){
    //freopen("debug.txt","r",stdin);
	while(~scanf("%d%d%d",&n,&m,&q)){
		for(int i=1;i<=n;i++)  scanf("%d",&w[i]);
		memset(dp,0,sizeof(dp));
		
		for(int i=1;i<=n;i++){
			for(int j=0;j<=base[m];j++){
				if(!check(j))  continue;
				int status=base[m]&(j<<1);
				dp[i][status]=max(dp[i][status],dp[i-1][j]);
				//1 status
				status=base[m]&((j<<1)|1);
				if(check(status))  dp[i][status]=max(dp[i][status],dp[i-1][j]+w[i]); 
			}
		}
		int ans=0;
		for(int i=0;i<=base[m];i++)
		    ans=max(ans,dp[n][i]);
		printf("%d\n",ans);
	}
}
