#include  <stdio.h>
#include <memory.h>
#include <algorithm>
using namespace std;
#define maxn 100050

int n,m;
int a[maxn];

bool check(int mid){
	int ans=0;
	int prev=a[0];
	for(int i=1;i<n;i++){
		 if(a[i]-prev>=mid){
			ans++;
			prev=a[i];
		 }
	}
	if(ans>=m-1)
		return true;
	else
		return false;
}

int solve(){
	int lw,hi;
	lw=0,hi=a[n-1]-a[0];
	int ans;
	while(lw<=hi){
		int mid=(lw+hi)>>1;
		if(check(mid)){
			 ans=mid;
			 lw=mid+1;
		}
		else
			hi=mid-1;
	}
	return ans;
}

int main(void){
	//freopen("debug.txt","r",stdin);
	while(scanf("%d%d",&n,&m)!=EOF){
		 for(int i=0;i<n;i++){
			scanf("%d",&a[i]);
		 }
		 sort(a,a+n);
		 int ans=solve();
		 printf("%d\n",ans);
	}
	return 0;
}
