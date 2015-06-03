#include <iostream>
#include <algorithm>
using namespace std;
#define LL long long
#define maxn  40000

LL sum1[maxn],sum2[maxn];
LL a[maxn];
int cnt1,cnt2;
int tcase;
LL n,w;

void dfs(LL dep,LL sum,LL stop)
{
	if(dep>=stop)
	{
		if(stop==n/2)
		    sum1[cnt1++]=sum;
		else
			sum2[cnt2++]=sum;
		return;
	}

	for(int i=0;i<=1;i++)   
		dfs(dep+1,sum+a[dep]*i,stop);
}

int main(void)
{
	cin>>tcase;
	for(int t=1;t<=tcase;t++){
		cin>>n>>w;
		cnt1=cnt2=0;
		for(int i=0;i<n;i++)
			cin>>a[i];
		
		LL stop=n/2;
		dfs(0,0,n/2);
		stop=n;
		dfs(n/2,0,n);
		
		sort(sum2,sum2+cnt2);

		int res=0;
		for(int i=0;i<cnt1;i++)
		{
			LL sum=sum1[i];
			int l=0,r=cnt2-1;
			int ans=0;
			while(l<=r){
				int mid=(l+r)>>1;
				if(sum+sum2[mid]<=w){
					ans=mid+1;
					l=mid+1;
				}
				else
					r=mid-1;
			}
		   res+=ans;
		}
		cout<<"Case "<<t<<": "<<res<<endl;
	}
	return 0;
}
