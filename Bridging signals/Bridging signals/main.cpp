//poj
#include <iostream>
using namespace std;

#define maxn 40040
int dp[maxn];
int a[maxn];
int tcase;
int n;

int bst(int left,int right,int data)
{
   	while(left<right){
		int mid=(left+right)>>1;
		if(dp[mid]>=data)
			right=mid;
		else
			left=mid+1;
	}
	return left;
}

int main(void)
{
	cin>>tcase;
	while(tcase--){
		cin>>n;
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		
		dp[1]=a[1];
		int len=1;
		for(int i=2;i<=n;i++){
		    if(a[i]>dp[len])
				dp[++len]=a[i];
			else
			{
				int j=bst(1,len,a[i]);
				dp[j]=a[i];
			}
		}
		cout<<len<<endl;
	}
	return 0;
}