#include <stdio.h>
#include <string.h>
#include <memory.h>
#define maxn 110
#define max(a,b) a>b?a:b
#define min(a,b) a<b?a:b

char str[maxn];
int dp[maxn][maxn];

char getvalue(char c)
{
	if(c==']')  return '[';
	if(c==')')  return '(';
	return '#';
}

int main(void)
{
	while(scanf("%s",str)!=EOF)
	{
		if(str[0]=='e')  break;
		int len=strlen(str);
		memset(dp,0,sizeof(dp));
		
		for(int i=1;i<len;i++){
			for(int j=i-1;j>=0;j--){
				for(int k=i-1;k>=j;k--){
					if(str[k]==getvalue(str[i]))
						dp[j][i]=max(dp[j][i],dp[j][k-1]+1+dp[k+1][i-1]);
					dp[j][i]=max(dp[j][i],dp[j][k]+dp[k+1][i]);
				}
			}
		}
		printf("%d\n",dp[0][len-1]*2);
	}
	return 0;
}