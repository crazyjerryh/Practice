#include <stdio.h>
#include <memory.h>
#include <string.h>
#include <algorithm>
using namespace std;
#define inf 0x3f3f3f3f
#define maxn 201111

int tcase;
int a[maxn],q[maxn];
int sum[maxn];
int n,k;
int main(void){
	//freopen("debug.txt","r",stdin);
	scanf("%d",&tcase);
	while(tcase--){
		scanf("%d%d",&n,&k);
		for(int i=1;i<=n;i++){
			scanf("%d",&a[i]);
		}
		for(int i=n+1;i<n+k;i++){
			a[i]=a[i-n];
		}
		
		sum[1]=0;
		for(int i=2;i<n+k;i++){
			sum[i]=sum[i-1]+a[i-1];
		}
		
		int front,last;
		front=last=0;
		int ans=-inf,first,second;
		int l,r;
		for(int i=1;i<n+k;i++){
			r=i;
			while(front<last&&sum[q[last-1]]>sum[i])  last--;
			q[last++]=i;
			l=q[front];
			int t=r-l+1;
			while(t>k&&front<last){
				l=q[++front];
				t=r-l+1;
			}
			if(t<=k){
				int tmp;
				if((tmp=sum[r]+a[r]-sum[q[front]])>ans){
					ans=tmp;
					first=q[front],second=r;
				}
			}
	    }
		if(second>n)  second=second%n; 
		printf("%d %d %d\n",ans,first,second);
	}
	return 0;
} 
