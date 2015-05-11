#include <iostream>
#include <memory.h>
using namespace std;

#define maxn 1001
int n;
int dp[2][maxn][maxn];

int main(void)
{
	while(cin>>n){
		if(n==0)  break;
		memset(dp,0,sizeof(dp));
		dp[0][1][0]=1;

		int first,second;
		first=0;
		for(int i=1;i<2*n;i++){
			second=(first+1)%2;

			memset(dp[second],0,sizeof(dp[second]));
			for(int j=1;j<=i;j++){
				dp[second][j+1][i-j]+=dp[first][j][i-j]; 
				if(i-j<j)
					dp[second][j][i-j+1]+=dp[first][j][i-j];
				else
					dp[second][j][i-j+1]=0;
			}
			first=second;

			for(int j=0;j<=i+1;j++)
				cout<<dp[second][j][i-j+1]<<" ";
			cout<<endl;
		}

		cout<<"result: "<<dp[second][n][n]<<endl;
	}
	return 0;
}