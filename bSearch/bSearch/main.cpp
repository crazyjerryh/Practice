#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

#define maxn 100
int a[maxn];
int n;
ifstream fin("debug.txt");
#define cin fin

int main(void)
{
	cin>>n;
	for(int i=0;i<n;i++)
		cin>>a[i];
	
	sort(a,a+n);
	for(int i=0;i<n;i++)
		cout<<a[i]<<" ";
	cout<<endl;
	int m;
	cin>>m;
    for(int i=0;i<m;i++){
	    int q;
		cin>>q;
		
		int l=0,r=n-1,mid=0;
		int ans=0;
		while(l<=r){
			mid=(l+r)>>1;
			if(a[mid]<=q)
			{
				ans=a[mid];
				l=mid+1;
			}
			else
				r=mid-1;
		}
		cout<<ans<<endl;

		l=0,r=n-1,mid=0;
		ans=0;
		while(l<=r){
			mid=(l+r)>>1;
			if(a[mid]<q){
				l=mid+1;
			}
			else
			{
				ans=a[mid];
				r=mid-1;
			}
		}
		cout<<ans<<endl;
	}
	return 0;
}