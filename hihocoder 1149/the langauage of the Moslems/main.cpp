#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <algorithm>
using namespace std;
#define maxn 1010
#define tmod 100007

char str[maxn];
int dp[maxn][maxn]; //dp[i][j]  以i,j为首尾的回文串的个数
int n;
int main(void){
	freopen("debug.txt","r",stdin);
    scanf("%d",&n);
	for(int tt=1;tt<=n;tt++){
		scanf("%s",str);
		int len=strlen(str);
		memset(dp,0,sizeof(dp));
		for(int i=0;i<len;i++){
			dp[i][i]=1;
			for(int j=i-1;j>=0;j--){
				 if(str[j]==str[i]){
					 dp[j][i]=(dp[j+1][i]+dp[j][i-1]+1)%tmod;
				 } 
				 else
					 dp[j][i]=((dp[j+1][i]+dp[j][i-1]-dp[j+1][i-1])%tmod+tmod)%tmod; 
			}
		}
		
		printf("Case #%d: %d\n",tt,dp[0][len-1]%tmod);
	}
	return 0;
}