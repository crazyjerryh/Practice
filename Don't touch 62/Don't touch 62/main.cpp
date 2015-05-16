#include <iostream>
#include <memory.h>
using namespace std;
#define maxn 10

int dp[maxn];
int buffer[maxn];
int a[maxn][maxn];
int digit[maxn];
int first,second;
int cnt;

int dfs(int n)
{
	int result=0;
    if(n==cnt){
		for(int i=1;i<=digit[n]-1;i++){
			result+=a[cnt][i];
		}
	}	
	else
	{
		if(n!=cnt-1){
			for(int i=cnt-1;i>n;i--)
				if(digit[i]==2&&digit[i+1]==6)
					return 0;
		}
		for(int i=0;i<=digit[n]-1;i++){
			if(i==2&&digit[n+1]==6)
				result+=0;
			else
				result+=a[n][i];
		}
		
		if(n==1&&digit[n]!=4)
			result+=1;
	}

	return result;
}

int calc(int n)
{
   	memset(dp,0,sizeof(dp));
	memset(a,0,sizeof(a));
    memset(buffer,0,sizeof(buffer));

	int result=0;

	if(n==0)
		return 1;
	if(n==-1)
		return 0;

	cnt=0;
	while(n){
		digit[++cnt]=n%10;
		n=n/10;
	}

	if(cnt==1)
		return digit[1]>=4?digit[1]:digit[1]+1;

	dp[0]=1;
	buffer[0]=1;
	a[0][0]=0;

	dp[1]=8;
	result=9;
	buffer[1]=buffer[0]+dp[1];
	for(int i=0;i<=9;i++){
		a[1][i]=1;
		if(i==4)
			a[1][4]=0;
	}

	for(int i=2;i<=cnt;i++){
		for(int j=0;j<=9;j++){
			 for(int k=0;k<=9;k++)
				 a[i][j]+=a[i-1][k];

		     if(j==4)
				 a[i][j]=0;
			 else if(j==6)
				 a[i][j]-=a[i-1][2];
		}
		if(i<cnt){
		for(int j=1;j<=9;j++)
			result+=a[i][j];
		}
	}
	for(int i=cnt;i>=1;i--){
		result+=dfs(i);
	}
	return result;
}

int main(void)
{
	while(cin>>first>>second)
	{
	     if(first==0&&second==0)  break;
		 cout<<calc(second)-calc(first-1)<<endl;
	}
	return 0;
}