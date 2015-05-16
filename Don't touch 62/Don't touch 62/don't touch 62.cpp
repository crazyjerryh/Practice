#include <iostream>
#include <memory.h>
using namespace std;

#define maxn 10
int dp[maxn][maxn];
int digit[maxn];
int cnt;
int first,second;
int calc(int n)
{
    memset(dp,0,sizeof(dp));
	memset(digit,0,sizeof(digit));
	cnt=0;
	int result=0;
	
	if(n==0)
		return 0;

	while(n){
		digit[++cnt]=n%10;
		n=n/10;
	}

	dp[0][0]=1;
	for(int i=1;i<=cnt;i++){
			for(int j=0;j<=9;j++){
				for(int k=0;k<=9;k++){
					if(j!=4&&!(j==6&&k==2))
						dp[i][j]+=dp[i-1][k];
				}
			}
	}

	for(int i=cnt;i>=1;i--){
		for(int j=0;j<digit[i];j++){
			if(j!=4&&!(digit[i+1]==6&&j==2))
				result+=dp[i][j];
		}
		
		if(digit[i]==4||(digit[i+1]==6&&digit[i]==2)) break;
	}

	return result;
}

int main(void)
{
	while(cin>>first>>second)
	{
		if(first==0&&second==0) break;
		 cout<<calc(second+1)-calc(first)<<endl;
	}
	return 0;
}