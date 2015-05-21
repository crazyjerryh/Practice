#include <iostream>
using namespace std;

#define max(a,b)  a>b?a:b
#define maxn 1010
int tcase;
int n,m;
int a[maxn],b[maxn];
int dp[maxn][maxn];

int lcis()
{
	int res=0;
	memset(dp,0,sizeof(dp));
	for(int i=0;i<n;i++){
		for(int j=0;j<m;j++){
			if(a[i]==b[j]){
			  dp[i][j]=1;
			  for(int l=0;l<i;l++)
				 for(int r=0;r<j;r++){
					  if(a[l]==b[r]&&a[l]<a
						  [i])
				         dp[i][j]=max(dp[i][j],dp[l][r]+1);	
			     }
			}
			else
			     dp[i][j]=0;

			if(dp[i][j]>res)
				res=dp[i][j];
		}
	}

	return res;
}

int main(void)
{
	cin>>tcase;
	while(tcase--){
		cin>>n;
		for(int i=0;i<n;i++)
			cin>>a[i];
		cin>>m;
		for(int i=0;i<m;i++)
			cin>>b[i];

		cout<<lcis()<<endl;
	}
	return 0;
}