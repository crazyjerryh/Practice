//3-dimension
#include <iostream>
#include <memory.h>
using namespace std;

#define MAXN  110
#define ninf -0xffffff
int map[MAXN][MAXN];


int prefix[MAXN][MAXN];
int dp[MAXN][MAXN];
int sum[MAXN][MAXN];
int pre[MAXN][MAXN];
int n;
int main(void)
{
	cin>>n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			cin>>map[i][j];
   
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			dp[i][j]=ninf;
			pre[i][j]=1;
		}

	memset(sum,0,sizeof(sum));
	memset(prefix,0,sizeof(prefix));
	
	for(int i=1;i<=n;i++)
		sum[1][i]+=sum[1][i-1]+map[i][1];

	
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++){
			 if(dp[i][j]<sum[1][j]-sum[1][i]+map[i][1])
				 dp[i][j]=sum[1][j]-sum[1][i]+map[i][1];

			 if(dp[i][j]<0){
				  prefix[i][j]=0;
				  pre[i][j]++;
			 }
			 else
				 prefix[i][j]=dp[i][j];
		}
	}

	
	
	for(int i=2;i<=n;i++){
		for(int j=1;j<=n;j++){
			sum[i][j]+=sum[i][j-1]+map[j][i];
		}


		for(int j=1;j<=n;j++){
			for(int k=j;k<=n;k++){
				int tmp=sum[i][k]-sum[i][j]+map[j][i];
				if(prefix[j][k]+tmp>dp[j][k])
					dp[j][k]=prefix[j][k]+tmp;

				prefix[j][k]+=tmp;
				while(pre[j][k]<=i&&prefix[j][k]<0){
					int num=sum[pre[j][k]][k]-sum[pre[j][k]][j]+map[j][pre[j][k]];
					prefix[j][k]-=num;
					pre[j][k]++;
				}
				
			}
		}
	}

	int mmax=ninf;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			if(dp[i][j]>mmax)
				mmax=dp[i][j];
		}
	cout<<mmax<<endl;
	return 0;
}