#include <stdio.h>
#include <iostream>
#include <cmath>
using namespace std;
#define INF 0xfffff
#define maxn 1010
#define max(a,b) a>b?a:b
#define min(a,b) a<b?a:b

int m;
int a[maxn];
char str[maxn];
int res[maxn];
int dp[12][maxn];
int pos[12][maxn];
int cnt;
int inx;


void init()
{
	for(int i=1;i<=cnt;i++)
	{
		dp[0][i]=a[i];
		pos[0][i]=i;
	}

    int len=log(cnt*1.0)/log(2.0);
    for(int i=1;i<=len;i++){
        for(int j=1;j<=cnt;j++){
		     dp[i][j]=min(dp[i-1][j],dp[i-1][j+(1<<(i-1))]);
			 if(dp[i][j]==dp[i-1][j])
				 pos[i][j]=pos[i-1][j];
			 else
				 pos[i][j]=pos[i-1][j+(1<<(i-1))];
		}
	}
}

int main(void)
{
	while(scanf("%s%d",str,&m)!=EOF){
	    cnt=strlen(str);
		for(int i=0;i<cnt;i++)
			a[i+1]=str[i]-'0';

		m=cnt-m; 
		for(int i=0;i<12;i++){
			for(int j=0;j<maxn;j++)
				dp[i][j]=INF;
		}
		init();

	    inx=0;
		int start=1;
		int right=m-1;
		for(int i=1;i<=m;i++){
			int end=cnt-right;
			int len=end-start+1;
			int j=log(len*1.0)/log(2.0);
			res[inx]=min(dp[j][start],dp[j][end-(1<<j)+1]);
			if(res[inx]==dp[j][start])
				start=pos[j][start];
			else
				start=pos[j][end-(1<<j)+1];
			start++;
			inx++;
			right--;
		}

		bool flag=false;
		int i;
		for(i=0;i<inx;i++)
		{
			if(res[i]!=0)
				break;
		}
		if(i==inx)
		{
			printf("0");
		}
		else
		{
			for(;i<inx;i++)
				printf("%d",res[i]);
		}
		printf("\n");
	}
	return 0;
}